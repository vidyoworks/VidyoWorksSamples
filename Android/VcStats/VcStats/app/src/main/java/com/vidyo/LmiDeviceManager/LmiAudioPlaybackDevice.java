/**
{file:
{name: LmiAudioPlaybackDevice.java}
	{description: Audio PlaybackDevice. }
	{copyright:
		(c) 2006-2009 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
 */
package com.vidyo.LmiDeviceManager;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.media.audiofx.Equalizer;
import android.os.Build;
import android.util.Log;

public class LmiAudioPlaybackDevice {
	DeviceThread deviceThread;
	private static String TAG = "LmiAudioPlaybackDevice";
	private int samplingRate, numberOfChannels, bitsPerSample, packetInterval;
	private int deviceId;
	private final Semaphore completeStartUp = new Semaphore(0, true);

	BlockingQueue<byte[]> frames = new LinkedBlockingQueue<byte[]>();
	BlockingQueue<byte[]> readyFrames = new LinkedBlockingQueue<byte[]>();

	public LmiAudioPlaybackDevice(String id) {
		deviceId = Integer.parseInt(id);
	}

	public int getSampleRate() {
		return 16000;
	}

	public int getNumberOfChannels() {
		return 1;
	}

	public int getBitsPerSample() {
		return 16;
	}

	public boolean start(int samplingRate, int numberOfChannels, int bitsPerSample, int packetInterval) {
		// allocate frames every time we start so that we do not leak memory
		frames = new LinkedBlockingQueue<byte[]>();				//init frame queues and get read of all old rementent left over audio frames
		readyFrames = new LinkedBlockingQueue<byte[]>();        //from previous session
				
		this.samplingRate = samplingRate;
		this.numberOfChannels = numberOfChannels;
		this.bitsPerSample = bitsPerSample;
		this.packetInterval = packetInterval;
		deviceThread = new DeviceThread(this);
		deviceThread.start();

		try {
			this.completeStartUp.acquire();
		} catch (Throwable t) {
			Log.w(TAG, "Startup Interrupted");
		}
		return deviceThread.running;
	}

	public void stop() {
		Log.i(TAG, "STOP");
		deviceThread.halt();
		deviceThread = null;
	}

	public boolean isRunning() {
		if (deviceThread != null)
			return deviceThread.isRunning();

		return false;
	}

	private static class DeviceThread extends Thread {
		private boolean running = false;
		AudioTrack track;
		private LmiAudioPlaybackDevice audioPlaybackDevice;

		public DeviceThread(LmiAudioPlaybackDevice audioPlaybackDevice) {
			this.audioPlaybackDevice = audioPlaybackDevice;
		}

		public void run() {
		
			int i, numberOfFrames = 10;
			int playbackDeviceSamplingRate;
			int frameSize = (audioPlaybackDevice.samplingRate / 1000) * audioPlaybackDevice.packetInterval * 2;

			Log.i(TAG, "Speaker Starting");
			try {
				android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
			} catch (Throwable t) {
				Log.w(TAG, "Failed to set the thread priority");
				audioPlaybackDevice.completeStartUp.release();
				return;
			}
			try {

				int minframeSize = AudioTrack.getMinBufferSize(audioPlaybackDevice.samplingRate,
						AudioFormat.CHANNEL_CONFIGURATION_MONO,
						AudioFormat.ENCODING_PCM_16BIT);
				Log.i(TAG, "MinFrameSize: " + String.format("%d", minframeSize)
						+ " FrameSize: " + String.format("%d", frameSize)
						+ " bytes");
				if (minframeSize < frameSize)
					minframeSize = frameSize;

				Log.i(TAG, "Starting audio playback. Rate: "
						+ String.format("%d", audioPlaybackDevice.samplingRate)
						+ " BytesPerFrame: " + String.format("%d", frameSize));
				track = new AudioTrack(getValidAudioPlaybackStream(), audioPlaybackDevice.samplingRate,
						AudioFormat.CHANNEL_OUT_MONO,
						AudioFormat.ENCODING_PCM_16BIT, minframeSize,
						AudioTrack.MODE_STREAM);
			} catch (Throwable t) {
				Log.e(TAG, "Failed create audio playbackDevice");
				audioPlaybackDevice.completeStartUp.release();
				return;
			}

			try {
				track.play();
			} catch (Throwable t) {
				Log.e(TAG, "Failed to start playbackDevice");
				track.release();
				audioPlaybackDevice.completeStartUp.release();
				return;
			}
			playbackDeviceSamplingRate = track.getSampleRate();
			if (playbackDeviceSamplingRate != audioPlaybackDevice.samplingRate) {
				Log.w(TAG, "Requested rate: "
						+ String.format("%d", audioPlaybackDevice.samplingRate)
						+ " does not match playbackDevice rate: "
						+ String.format("%d", playbackDeviceSamplingRate));
			}
			/* create frame pool */
			for (i = 0; i < numberOfFrames; i++) {
				byte[] frame = new byte[frameSize];
				try {
					audioPlaybackDevice.readyFrames.put(frame);
				} catch (Exception e) {
					Log.e(TAG, "unable to add frame" + e.toString());
				}
			}
			
			/*
			 * Temporary call to modify volume for devices that may need it.
			 * This call should be done in a better way in the future
			 */
			setupSpeakerNeedsVolumeIncrease(track);
			
			int playedSize;
			running = true;
			audioPlaybackDevice.completeStartUp.release();
			while (running == true) {
				/* get a frame form the pool */
				byte[] frame = null;
				try {
					frame = audioPlaybackDevice.frames.poll(audioPlaybackDevice.packetInterval, TimeUnit.MILLISECONDS);
				} catch (InterruptedException e) {
					Log.i(TAG, "No frames avaialble " + e.toString());
					continue;
				}

				playedSize = track.write(frame, 0, frameSize);
				if (playedSize > 0) {
					try {
						audioPlaybackDevice.readyFrames.put(frame);
					} catch (Exception e) {
						Log.e(TAG, "unable to add frame" + e.toString());
					}
				}
			}
			Log.i(TAG, "Speaker Stopping");
			track.stop();
			track.release();
			
			// release use of frames so that we do not leak memory
			audioPlaybackDevice.frames = null;
			audioPlaybackDevice.readyFrames = null;

			Log.i(TAG, "Speaker Stopped");
		}

		public void halt() {
			running = false;
			try {
				join();
			} catch (Throwable t) {
				Log.e(TAG, "Failed to join");
			}
		}

		public boolean isRunning() {
			return running;
		}
	}

	public byte[] aquireFrame() {
		byte[] frame = null;
		if (readyFrames != null) {
			try {
				frame = readyFrames.poll(packetInterval, TimeUnit.MILLISECONDS);
			} catch (InterruptedException e) {
				Log.i(TAG, "Frames are not ready " + e.toString());
			}
		}
		if (frame == null)
			Log.e(TAG, "Frames are not ready");
		return frame;
	}

	public void releaseFrame(byte[] frame) {
		if (frames != null) {
			try {
				frames.put(frame);
			} catch (Exception e) {
				Log.e(TAG, "unable to release captured frame" + e.toString());
			}
		}
	}


	/*
	 * Saved Track and Equalizer information
	 */
	private static AudioTrack activeTrack = null;
	private static boolean needsIncrease = false;
	private static int currentSessID = 0;
	private static Equalizer currentEqualizer = null;
	private static Equalizer.Settings savedEqualizerSetting = null;
	private static boolean currentlyUsingSpeaker = false;
	private static String [][] volumeBoostDevices = {
//		{ "asus", "nexus 7", },
//		{ "lge", "lg-e980", },
//		{ "lge", "nexus 4", },
//		{ "samsung", "gt-n7100", },
		{ "samsung", "sch-i915", },
//		{ "model", "device", },
	};
	
	/**
	 * This is a temporary fix to an issue seen on the Samsung Galaxy Tab 2 10" device.
	 * The output audio on this tablet is very low, since we are opening the speaker with 
	 * AudioManager.STREAM_VOICE_CALL the device is probably assuming some Echo Cancellation 
	 * is active, which will likely reduce the output volume.
	 * 
	 * We are going to force the output volume higher by adding an equalizer and setting the
	 * values higher.
	 * @param track
	 * @return returns true if the device's volume was increased
	 */
	private static boolean setupSpeakerNeedsVolumeIncrease(AudioTrack track) {
		String manufacturer = Build.MANUFACTURER.toLowerCase();
		String device = Build.DEVICE.toLowerCase();
		String model = Build.MODEL.toLowerCase();

		Log.d(TAG, "Manufacturer="+manufacturer+", Device="+device+", Model="+model);
		
		if (activeTrack == null)
			activeTrack = track;
		
		synchronized (activeTrack) {
			needsIncrease = false;

			activeTrack = track;
			if (track == null) {
				return false;
			}

			// See if any of the devices are on the list
			for (int i=0; i<volumeBoostDevices.length; i++) {
				if (manufacturer.equalsIgnoreCase(volumeBoostDevices[i][0]) &&
					model.equalsIgnoreCase(volumeBoostDevices[i][1])) {
					Log.d(TAG, "Device needs a volume boost!");
					needsIncrease = true;
					break;
				}
			}
			
			if (needsIncrease) {
				currentlyUsingSpeaker = false;
				currentSessID = activeTrack.getAudioSessionId();
				currentEqualizer = new Equalizer(10, currentSessID);
				if (currentEqualizer != null) {
					savedEqualizerSetting = currentEqualizer.getProperties();
					for (short level : savedEqualizerSetting.bandLevels) {
						Log.d(TAG, "Equalizer: bandLevels[]="+level);
					}
				} else {
					savedEqualizerSetting = null;
				}

			} else {
				currentSessID = -1;
				currentEqualizer = null;
				savedEqualizerSetting = null;
			}
		}
		return needsIncrease;
	}
	
	public static void setSpeakerNeedsVolumeIncrease(boolean usingSpeaker) {
		if (activeTrack == null)
			return;
		
		synchronized (activeTrack) {
			if (!needsIncrease)
				return;

			if (currentEqualizer == null || savedEqualizerSetting == null)
				return;
			
			if (usingSpeaker) {
				if (!currentlyUsingSpeaker) {
					currentlyUsingSpeaker = true;
					
					try {
						// Force settings to all high
						short [] levelRange = currentEqualizer.getBandLevelRange();
						if (levelRange != null && levelRange.length == 2) {
							Log.d(TAG, "Equalizer: BandLevelRange ="+levelRange[0]+" to "+levelRange[1]);
			
							short [] bandLevels = savedEqualizerSetting.bandLevels;
	
							// Set all the equalizer bands to 4/5ths the max level 
							int temp = levelRange[1];
							temp *= 4;
							temp /= 5;
							
							// The following would set the bands to 100% the max level
							for (short pos=0; pos<bandLevels.length; pos++) {
								currentEqualizer.setBandLevel(pos, (short)temp);
							}
							
							// Print out the current settings
							Equalizer.Settings esettings = currentEqualizer.getProperties();
							for (short level : esettings.bandLevels) {
								Log.d(TAG, "Equalizer: bandLevels[]="+level);
							}
							
							currentEqualizer.setEnabled(true);
						}
					} catch (Exception ex) {
						Log.d(TAG, "getBandLevelRange() exception, ignoring");
					}
				}
			} else {
				if (currentlyUsingSpeaker) {
					currentlyUsingSpeaker = false;
					
					if (currentEqualizer.getEnabled())
						currentEqualizer.setEnabled(false);
				}
			}
		}
	}
	
	// Default audio playback stream type
	private static int playbackStream = AudioManager.STREAM_VOICE_CALL;
	
	public static void setValidAudioPlaybackStream(int pbStream) {
		playbackStream = pbStream;
	}
	
	public static int getValidAudioPlaybackStream() {
		return playbackStream;
	}
}
