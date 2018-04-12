/**
{file:
{name: LmiScreenManager.java}
	{description: Screen Manager. }
	{copyright:
		(c) 2013 Vidyo, Inc.,
		433 Hackensack Avenue,
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

import java.nio.ByteBuffer;

import android.content.Context;
import android.hardware.SensorManager;
import android.os.Build;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.OrientationEventListener;

public class LmiScreenManager extends OrientationEventListener {
	private Display[] displays;
	private static String TAG = "LmiScreenManagerJava";
	private ByteBuffer pointerwrapper;
	private int deviceRotation;
	private LmiScreenManagerListener listener;
	
	public LmiScreenManager(final Context context, final ByteBuffer pointerwrapper){
		super(context, SensorManager.SENSOR_DELAY_NORMAL);

		this.pointerwrapper = pointerwrapper;
		deviceRotation = 0;

		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
			listener = LmiScreenManagerJellybeanListener.newInstance(context, pointerwrapper, this);
		}else{
			listener = LmiScreenManagerCupcakeListener.newInstance(context, pointerwrapper, this);
		}
		
		getDisplays();
		Log.d(TAG, "LmiScreenManager construct done in java");
	}

	@Override
	public void onOrientationChanged(int orientation) {
		int oldRotation = deviceRotation;
		if(orientation > 45 && orientation <= 145)
			deviceRotation = 90;
		else if(orientation >145 && orientation <= 225)
			deviceRotation = 180;
		else if(orientation >225 && orientation <= 315)
			deviceRotation = 270;
		else 
			deviceRotation = 0;
		
		if(oldRotation != deviceRotation){
			Log.d(TAG, "LmiScreenManager new rotatation in java");		
			getDisplays();
			rotationChanged(Display.DEFAULT_DISPLAY, pointerwrapper);
		}
	}
	
	public native void rotationChanged(int displayId, ByteBuffer pointerwraper);
	public native void displayAdded(int displayId, ByteBuffer pointerwraper);
	public native void displayRemoved(int displayId, ByteBuffer pointerwraper);
	public native void displayChanged(int displayId, ByteBuffer pointerwraper);

	public boolean start(){
		boolean s = false;
		enable(); // enable orientationEventListener
		s = listener.start();
		
		Log.d(TAG, "LmiScreenManager started in java");
		return s;
	}

	public void stop(){
		listener.stop();
		disable();		
		Log.d(TAG, "LmiScreenManager stopped in java");
	}
	
	public void getDisplays(){
		/*
		 * If the Android SDK version is less than 17, the external display only mirrors the primary one.
		 * else we can get each of them via displayManager
		 */
		displays = listener.getDisplays();
	}
	
	public int[] getDisplayIds(){		
		int[] ids = new int[displays.length];
		int i;
		for(i = 0; i < displays.length; i++){
			ids[i] = displays[i].getDisplayId();
		}
		return ids;
	}
	
	public Display getDisplay(int displayId){
		int i, numDisplays = displays.length;
		for(i = 0; i < numDisplays; i++){
			if(displays[i].getDisplayId() == displayId){
				return displays[i];
			}
		}
		return null;
	}
	
	@SuppressWarnings("deprecation")
	public int getWorkAreaWidth(int displayId){
		Display d = getDisplay(displayId);
		if( d == null){
			return 0;
		}
		return d.getWidth();
	}
	
	@SuppressWarnings("deprecation")
	public int getWorkAreaHeight(int displayId){
		Display d = getDisplay(displayId);
		if( d == null){
			return 0;
		}
		return d.getHeight();
	}
	
	public int getRealWidth(int displayId){
		return listener.getRealWidth(displayId);
	}
	
	public int getRealHeight(int displayId){
		return listener.getRealHeight(displayId);
	}
	
	public int getXdpi(int displayId){
		Display d = getDisplay(displayId);
		if( d == null){
			return 0;
		}
		DisplayMetrics metrics = new DisplayMetrics();
		d.getMetrics(metrics);
		return Math.round(metrics.xdpi);
	}
	
	public int getYdpi(int displayId){
		Display d = getDisplay(displayId);
		if( d == null){
			return 0;
		}
		DisplayMetrics metrics = new DisplayMetrics();
		d.getMetrics(metrics);
		return Math.round(metrics.ydpi);
	}
	
	public boolean isDefaultDisplay(int displayId){
		return Display.DEFAULT_DISPLAY == displayId;
	}
	
	public String getName(int displayId){
		return listener.getName(displayId);
	}
	
	public int getRotation(int displayId){
		if(isDefaultDisplay(displayId)){
			return deviceRotation;
		}else{
			return 0;
		}
	}

    public interface LmiScreenManagerListener{
    	public boolean start();
    	public void stop();
    	public Display[] getDisplays();
    	public int getRealWidth(int displayId);
    	public int getRealHeight(int displayId);
    	public String getName(int displayId);
    }
}

