/**
{file:
{name: LmiAudioCapturer.java}
	{description: Audio Capturer. }
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

import android.annotation.TargetApi;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.media.audiofx.AcousticEchoCanceler;
import android.media.audiofx.AutomaticGainControl;
import android.media.audiofx.NoiseSuppressor;
import android.os.Build;
import android.util.Log;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class LmiAudioCapturer {
	DeviceThread deviceThread;
	private static String TAG = "LmiAudioCapturer";
	private int samplingRate, numberOfChannels, bitsPerSample, packetInterval;
	private int deviceId;
	private final Semaphore completeStartUp = new Semaphore(0, true);
	private boolean isStarted = false;

	BlockingQueue<byte[]> frames = new LinkedBlockingQueue<byte[]>();
	BlockingQueue<byte[]> readyFrames = new LinkedBlockingQueue<byte[]>();

	public LmiAudioCapturer(String id) {
		deviceId = Integer.parseInt(id);
	}

	public int getSampleRate() {
		return 32000; // VMANDRD-1698 bad Audio quality, force to use 32K
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
		deviceThread.setPriority(Thread.MAX_PRIORITY);

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

	@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
	private static int getAudioSourceType() {
		/*
		 * The audio input type depends on what is supported by the Android version.
		 * If the Android SDK version is 11 and newer then use:
		 *   - MediaRecorder.AudioSource.VOICE_COMMUNICATION : Microphone audio source tuned for voice 
		 *     communications such as VoIP. It will for instance take advantage of echo cancellation or 
		 *     automatic gain control if available. It otherwise behaves like DEFAULT if no voice 
		 *     processing is applied. 
		 *     
		 * If the Android SDK version is less than 11 then use:
		 *   - MediaRecorder.AudioSource.MIC : Microphone audio source 
		 */
		String manufacturer = Build.MANUFACTURER.toLowerCase();//special handling for kindle fire HD
		String device = Build.DEVICE.toLowerCase();
		String model = Build.MODEL.toLowerCase();
		if (manufacturer.equalsIgnoreCase("amazon")) 
		{
			if (device.equalsIgnoreCase("d01e"))
				return MediaRecorder.AudioSource.MIC;
		}

		// ====== disable the workaround for Lollipop for now, and revert to original code =====
		/*
		if (Build.VERSION.SDK_INT >= 21) {
			// Started from Lollipop, many devices default MIC might have very weak volume.
			// Use MediaRecorder.AudioSource.CAMCORDER: Microphone audio source with same orientation
			// as camera if available, the main device microphone otherwise
			return MediaRecorder.AudioSource.CAMCORDER;
		} else */
		if (Build.VERSION.SDK_INT >= 16) {
			//TODO: add code to check the echo cancellation and audio gain support
			return MediaRecorder.AudioSource.VOICE_COMMUNICATION;
		} else if (Build.VERSION.SDK_INT >= 11) {
			return MediaRecorder.AudioSource.VOICE_COMMUNICATION;
		} else {
			return MediaRecorder.AudioSource.MIC;
		}
	}

	//TODO: Do this the correct Device Manager way
	@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
	private static void setEchoCancel(AudioRecord record) {
		if (Build.VERSION.SDK_INT >= 16) {
			boolean aecIsAvailable = AcousticEchoCanceler.isAvailable(); 
			Log.i(TAG, "AcousticEchoCanceler.isAvailable() = " + aecIsAvailable); 
			if (aecIsAvailable) { 
				AcousticEchoCanceler aec = AcousticEchoCanceler.create(record.getAudioSessionId());
				//If Echo Cancel is to be enabled then do so
				if (LmiAudioCapturerDeviceInfo.getEnableEchoCancel()) {
					if(!aec.getEnabled()) {
						aec.setEnabled(true);
					}
				} else {
					if (aec.getEnabled()) {
						aec.setEnabled(false);
					}
				}
				
				Log.i(TAG, "AEC_enabled=" + aec.getEnabled() + ", hasControl=" + aec.hasControl()); 
			}
			
			boolean agcIsAvailable = AutomaticGainControl.isAvailable();
			Log.i(TAG, "AutomaticGainControl.isAvailable() = " + agcIsAvailable); 
			if (agcIsAvailable) { 
				AutomaticGainControl agc = AutomaticGainControl.create(record.getAudioSessionId());
				if(!agc.getEnabled()) {
					agc.setEnabled(true);
				}
				Log.i(TAG, "AGC_enabled=" + agc.getEnabled() + ", hasControl=" + agc.hasControl()); 
			}
			
			boolean nsIsAvailable = NoiseSuppressor.isAvailable();
			Log.i(TAG, "NoiseSuppressor.isAvailable() = " + nsIsAvailable); 
			if (nsIsAvailable) {
				NoiseSuppressor ns = NoiseSuppressor.create(record.getAudioSessionId());
				if (LmiAudioCapturerDeviceInfo.getEnableNoiseSuppression()) {
					if (!ns.getEnabled())
						ns.setEnabled(true);
				} else {
					if (ns.getEnabled())
						ns.setEnabled(false);
				}
				Log.i(TAG, "NoiseSuppressor_enabled=" + ns.getEnabled() + ", hasControl=" + ns.hasControl()); 
			}
			
		}
	}
	//TODO: End code that needs to be done the right way

	@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
	private static void logEchoCancelState(AudioRecord record) {
		if (Build.VERSION.SDK_INT >= 16) {
			boolean isAvailable = AcousticEchoCanceler.isAvailable(); 
			Log.i(TAG, "AcousticEchoCanceler.isAvailable() = " + isAvailable); 
		}
	}
	
	private static boolean micIsRunning = false;
	public static boolean micIsRunning() {
		return micIsRunning;
	}

	private static class DeviceThread extends Thread {
		private boolean running = false;
		private AudioRecord record;
		private LmiAudioCapturer audioCapturer;

		public DeviceThread(LmiAudioCapturer audioCapturer) {
			this.audioCapturer = audioCapturer;
		}

		public void run() {
			micIsRunning = true;
			int i, numberOfFrames = 10;
			int capturerSamplingRate;
			int frameSize = (audioCapturer.samplingRate / 1000) * audioCapturer.packetInterval * 2;

			Log.i(TAG, "Microphone Starting");
			try {
				android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
			} catch (Throwable t) {
				Log.w(TAG, "Failed to set the thread priority");
			}
			try {

				int minframeSize = AudioRecord.getMinBufferSize(audioCapturer.samplingRate,
//						AudioFormat.CHANNEL_CONFIGURATION_MONO,
						AudioFormat.CHANNEL_IN_MONO,
						AudioFormat.ENCODING_PCM_16BIT);
				Log.i(TAG, "MinFrameSize: " + String.format("%d", minframeSize)
						+ " FrameSize: " + String.format("%d", frameSize)
						+ " bytes");
				if (minframeSize < 10 * frameSize)
					minframeSize = 10 * frameSize;

				int sourceType = getAudioSourceType();
				
				Log.i(TAG, "Starting audio capture. Rate: "
						+ String.format("%d", audioCapturer.samplingRate)
						+ " BytesPerFrame: " + String.format("%d", frameSize));
				record = new AudioRecord(sourceType, audioCapturer.samplingRate,
						AudioFormat.CHANNEL_IN_MONO,
						AudioFormat.ENCODING_PCM_16BIT, minframeSize);
				
				logEchoCancelState(record);
				
				//TODO: This function needs to be done the right way
				setEchoCancel(record);
				//TODO: End code that needs to be done the right way
				
			} catch (Throwable t) {
				Log.e(TAG, "Failed create audio capturer");
				audioCapturer.completeStartUp.release();
				micIsRunning = false;
				return;
			}

			try {
				record.startRecording();
			} catch (Throwable t) {
				Log.e(TAG, "Failed start capturer");
				record.release();
				audioCapturer.completeStartUp.release();
				micIsRunning = false;
				return;
			}
			capturerSamplingRate = record.getSampleRate();
			if (capturerSamplingRate != audioCapturer.samplingRate) {
				Log.w(TAG, "Requested rate: "
						+ String.format("%d", audioCapturer.samplingRate)
						+ " does not match capturer rate: "
						+ String.format("%d", capturerSamplingRate));
			}
			/* create frame pool */
			for (i = 0; i < numberOfFrames; i++) {
				byte[] frame = new byte[frameSize];
				try {
					audioCapturer.frames.put(frame);
				} catch (Exception e) {
					Log.e(TAG, "unable to add frame" + e.toString());
				}
			}
			running = true;
			audioCapturer.completeStartUp.release();
			int capturedSize;
			while (running == true) {
				/* get a frame form the pool */
				byte[] frame = null;
				try {
					frame = audioCapturer.frames.poll(audioCapturer.packetInterval, TimeUnit.MILLISECONDS);
				} catch (InterruptedException e) {
					Log.i(TAG, "No frames avaialble " + e.toString());
					continue;
				}

				capturedSize = record.read(frame, 0, frameSize);
				if (capturedSize > 0) {
					try {
						audioCapturer.readyFrames.put(frame);
					} catch (Exception e) {
						Log.w(TAG, "unable to add frame" + e.toString());
					}
				}
			}
			Log.i(TAG, "Microphone Stopping");
			record.stop();
			record.release();
			Log.i(TAG, "Microphone Stopped");
			micIsRunning = false;
			
			// Release frames so we do not leak memory
			audioCapturer.frames = null;
			audioCapturer.readyFrames = null;
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
	//		if (frame == null)
	//			Log.e(TAG, "Frames are not ready");
		}
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
}
