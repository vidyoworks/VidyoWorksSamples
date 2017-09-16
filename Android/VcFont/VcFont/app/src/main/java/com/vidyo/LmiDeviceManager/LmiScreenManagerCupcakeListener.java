/**
{file:
    {name: LmiScreenManagerCupcakeListener.java}
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

import android.content.Context;
import android.util.Log;
import android.view.Display;
import android.view.WindowManager;

public class LmiScreenManagerCupcakeListener implements LmiScreenManager.LmiScreenManagerListener{
	private static final String TAG = "LmiScreenManagerListenerJava";
	private LmiScreenManager screenManager;
	private WindowManager windowManager;
	private ByteBuffer pointerwrapper;

	private LmiScreenManagerCupcakeListener(final Context context, 
			final ByteBuffer pointerwrapper, LmiScreenManager mgr){
		windowManager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
		this.pointerwrapper = pointerwrapper;
		screenManager = mgr;
		Log.d(TAG, "LmiCupcakeListener constructed in java");		
	}
	
	public static LmiScreenManagerCupcakeListener newInstance(final Context context, 
			final ByteBuffer pointerwrapper, LmiScreenManager l) {		
		LmiScreenManagerCupcakeListener listener = new LmiScreenManagerCupcakeListener(context, pointerwrapper, l);
        return listener;
    }
	
	@Override
	public boolean start() {
		return true;
	}

	@Override
	public void stop() {	
	}

	@Override
	public Display[] getDisplays() {
		Display[] displays = new Display[1];
		displays[0] = windowManager.getDefaultDisplay();
		return displays;
	}

	@Override
	public int getRealWidth(int displayId) {
		Display d = screenManager.getDisplay(displayId);
		if( d == null){
			return 0;
		}
		return d.getWidth();
	}

	@Override
	public String getName(int displayId) {
		return new String("Screen_") + displayId;
	}

	@Override
	public int getRealHeight(int displayId) {
		Display d = screenManager.getDisplay(displayId);
		if( d == null){
			return 0;
		}
		return d.getHeight();
	}
}