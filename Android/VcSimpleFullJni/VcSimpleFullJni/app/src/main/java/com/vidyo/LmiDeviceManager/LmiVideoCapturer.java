package com.vidyo.LmiDeviceManager;

import android.app.Activity;
import android.content.Context;
import android.os.Build;
import android.util.Log;

public class LmiVideoCapturer  {
	private static String TAG = "LmiVideoCapturer";
	Object lock=new Object();
	LmiVideoCapturerInternal capturerInternal;
	private boolean cameraStarted = false;
	private boolean internalConstructInProgress = false;
	private boolean cameraStartInProgress = false;
		//these timeout values are intentionally long
		//construction here can  potentially take up to a few seconds
	private final int internalConstructTimeout = 5000;
	private final int cameraStartTimeout = 5000;
	
	public LmiVideoCapturer(final Context context, final Activity activity, final String id)
	{
		Log.i(TAG, "Creating video capturer");
		capturerInternal = null; 
		
		if (Build.MANUFACTURER.toLowerCase().equalsIgnoreCase("amazon")) {
			String dev = Build.DEVICE;
			String model = Build.MODEL;
			Log.d(TAG, "Device is ="+dev);
			Log.d(TAG, "Model is ="+model);
			
			if (model.equalsIgnoreCase("Kindle Fire"))
				return;
		}
		
		internalConstructInProgress = true;
		activity.runOnUiThread(new Runnable(){
			@Override
			public void run(){
				capturerInternal = new LmiVideoCapturerInternal(context, activity, id);													
				synchronized(lock) {
					Log.d(TAG, "calling notify for lock");
					lock.notify();
					internalConstructInProgress = false;
				}
			}
		});

		if (internalConstructInProgress) {
			try{
				synchronized(lock){
					Log.d(TAG, "calling wait for lock");
					lock.wait(internalConstructTimeout);
				}
		 	} catch (InterruptedException e) {
		 		Log.i(TAG, "Video capturer creation interrupted");
		 		//e.printStackTrace();
		 	}
		} else {
			Log.d(TAG, "creation already happened");
		}
		
		if (capturerInternal == null)
			Log.i(TAG, "Video capturer creation failed");
		else
			Log.i(TAG, "Video capturer created successfully");
		
	}
	
	private boolean verifyInternal() {
		if (internalConstructInProgress) {
			try{
			synchronized(lock) { 
					lock.wait(internalConstructTimeout);
				}
		 	} catch (InterruptedException e) {
		 		//e.printStackTrace();
		 	}
		}
		
		if (capturerInternal == null) {
			Log.e(TAG, "Video capturer internal is null");
			return false;
		}
		
		return true;
	}

	public LmiVideoCapturerCapability[] getCapabilities() {
		if (!verifyInternal())
			return null;
		
		return capturerInternal.getCapabilities();
	}
	
public LmiVideoCapturerCapability[] getCapabilities(boolean anyFormat) {
		
		if (!verifyInternal())
			return null;
		
        return capturerInternal.getCapabilities(/*anyFormat*/);
	}

	public boolean start(final String format, final int width, final int height, final int frameRate) {

		Log.e(TAG, "start format: "+format+" width: "+width+" height: "+height+" framerate: "+frameRate);

		cameraStarted = false; 
		
		if (!verifyInternal())
			return false;
		
		cameraStartInProgress = true;
		
		capturerInternal.activity.runOnUiThread(new Runnable(){
			@Override
			public void run(){
				cameraStarted = capturerInternal.start(format, width, height, frameRate);													
				synchronized(lock) {
			 		Log.i(TAG, "Camera start finished");

					lock.notify();
					cameraStartInProgress = false;
				}
			}
		});
				

		if (cameraStartInProgress) {
			try{
				synchronized(lock) { 
			 		Log.i(TAG, "waiting for camera start");
					lock.wait(cameraStartTimeout);
				}
		 	} catch (InterruptedException e) {
		 		Log.i(TAG, "Camera start interrupted");
		 		//e.printStackTrace();
		 	}
		} else {
	 		Log.i(TAG, "NOT waiting for camera start");
		}
		
		if (!cameraStarted)
			Log.i(TAG, "Failed to start camera");
		
		return cameraStarted;
	}

	private boolean stopAlreadyDone = false;

	public void stop() { 
		Log.i(TAG, "Stop");

		if (!verifyInternal())
			return;
		
		while (cameraStartInProgress) {
			try{ 
				lock.wait(100);				
		 	} catch (InterruptedException e) {
		 		//e.printStackTrace();
		 	}
		}	
		
		capturerInternal.activity.runOnUiThread(new Runnable() 
											{
												@Override
												public void run(){
														if (stopAlreadyDone) {
															Log.i(TAG, "----- nothing to do");
															return;
														}
														Log.i(TAG, "----- user thread to stop camera");
													capturerInternal.stop();
													cameraStarted = false;
												}
											}
								);


		// VMANDRD-1953 Black screen appears for 6-7 seconds after click 
		// Revert to the previous (VM 2.3) version, as the below change doesn't bring 
		// much benefit while unnecessarily causing long wait when drop a call. After
		// this revert, it is indeed same as SDK220
		int waitCount = 0;
		
		while (capturerInternal.isActive()) {
			try{
				synchronized(this) {
					Log.d(TAG, "--- Waiting for LmVideoCapturerInternal to stop --- count - " + waitCount);
					wait(500);
					++waitCount;
					if(waitCount > 5)
					{
						Log.d(TAG, "--- situation to try stop manual");
						stopAlreadyDone = true;
						capturerInternal.stop();
						cameraStarted = false;

					}
				}
		 	} catch (InterruptedException e) {
		 		//e.printStackTrace();
		 	}
		}

		capturerInternal = null;
		
	}

	public int getOrientation() {
		if (!verifyInternal())
			return 0;
		
		return capturerInternal.getOrientation();
	}

	public boolean getMirrored() {
		Log.i(TAG, "getMirrored");
	
		if (!verifyInternal()) {
			Log.i(TAG, "getMirrored: verifyInternal failed, returning false");
			return false;
		}
		
		boolean retval = capturerInternal.getMirrored();
		Log.i(TAG, "getMirrored: returning "+retval);
		return retval;
	}

	public byte[] aquireFrame() {
		if (!verifyInternal())
			return null;
		
		return capturerInternal.aquireFrame();
	}

	public void releaseFrame(byte[] frame) {
		if (!verifyInternal())
			return;
		
		capturerInternal.releaseFrame(frame);
	}
	
	public int getFrameWidth(){
		if (!verifyInternal())
			return 0;
		
		return capturerInternal.getFrameWidth();
	}
	
	public int getFrameHeight(){
		if (!verifyInternal())
			return 0;
		
		return capturerInternal.getFrameHeight();
	}
	
	public static void onActivityPause() {
		Log.i(TAG, "onActivityPause");

		LmiVideoCapturerInternal.onActivityPause();
	}
	
	public static void onActivityResume() {
		Log.i(TAG, "onActivityResume");

		LmiVideoCapturerInternal.onActivityResume();
	}	
}
