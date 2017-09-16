/**
{file:
    {name: LmiScreenManagerJellybeanListener.java}
    {description: }
    {copyright:
    	(c) 2013 Vidyo, Inc.,
    	433 Hackensack Avenue,
    	Hackensack, NJ  07601.
    
    	All rights reserved.
    
    	The information contained herein is proprietary to Vidyo, Inc.
    	and shall not be reproduced, copied (in whole or in part), adapted,
    	modified, disseminated, transmitted, transcribed, stored in a retrieval
    	system, or translated into any language in any form by any means
    	without the express written consent of Vidyo, Inc.
    	                  ***** CONFIDENTIAL *****
    }
}
*/
package com.vidyo.LmiDeviceManager;

import java.nio.ByteBuffer;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.Point;
import android.hardware.display.DisplayManager;
import android.hardware.display.DisplayManager.DisplayListener;
import android.os.Build;
import android.util.Log;
import android.view.Display;

public class LmiScreenManagerJellybeanListener{
	private static final String TAG = "LmiScreenManagerListenerJava";
	
	public static LmiScreenManager.LmiScreenManagerListener newInstance(final Context context, 
			final ByteBuffer pointerwrapper, LmiScreenManager mgr) {		
		LmiScreenManager.LmiScreenManagerListener listener = null;	
		listener = new LmiJellyBeanMR1Listener(context, pointerwrapper, mgr);
        return listener;
    }
    
	@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
	private static class LmiJellyBeanMR1Listener implements DisplayListener, LmiScreenManager.LmiScreenManagerListener{
		private ByteBuffer pointerwrapper;
		private LmiScreenManager mgr;
		private DisplayManager displayManager;

		public LmiJellyBeanMR1Listener(final Context context, final ByteBuffer pointerwrapper, LmiScreenManager mgr){
			this.pointerwrapper = pointerwrapper;
			this.mgr = mgr;
			displayManager = (DisplayManager) context.getSystemService(Context.DISPLAY_SERVICE);	
			Log.d(TAG, "LmiJellyBeanMR1Listener constructed in java");
		}
		
		@Override
		public void onDisplayAdded(int arg0) {
			Log.d(TAG, "LmiScreenManager display added in java");
			mgr.getDisplays();
			mgr.displayAdded(arg0, pointerwrapper);
		}
	
		@Override
		public void onDisplayChanged(int arg0) {
			Log.d(TAG, "LmiScreenManager display changed in java");
			mgr.getDisplays();
			mgr.displayChanged(arg0, pointerwrapper);
		}
	
		@Override
		public void onDisplayRemoved(int arg0) {
			Log.d(TAG, "LmiScreenManager display removed in java");
			mgr.getDisplays();
			mgr.displayRemoved(arg0, pointerwrapper);
		}
	
		@Override
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
		public boolean start() {
			// TBD: lpeng, temporarily comment out as it causes launch failure
			//displayManager.registerDisplayListener(this, null);
			return true;
		}
	
		@Override
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
		public void stop() {
			// TBD: lpeng, temporarily comment out
			//displayManager.unregisterDisplayListener(this);
		}
	
		@Override
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
		public Display[] getDisplays() {
			Display[] displays = displayManager.getDisplays();
			return displays;
		}
	
		@Override
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
		public int getRealWidth(int displayId) {
			Display d = mgr.getDisplay(displayId);
			if( d == null){
				return 0;
			}
			Point p = new Point();
			d.getRealSize(p);
			return p.x;
		}
	
		@Override
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
		public String getName(int displayId) {
			Display d = mgr.getDisplay(displayId);
			if( d == null){
				return new String("Null Screen");
			}
			return d.getName();
		}
	
		@Override
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
		public int getRealHeight(int displayId) {
			Display d = mgr.getDisplay(displayId);
			if( d == null){
				return 0;
			}
			Point p = new Point();
			d.getRealSize(p);
			return p.y;
		}
	}
}