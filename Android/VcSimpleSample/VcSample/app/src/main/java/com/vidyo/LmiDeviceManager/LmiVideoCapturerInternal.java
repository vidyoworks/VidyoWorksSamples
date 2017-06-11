/**
{file:
{name: LmiVideoCapturer.java}
	{description: Video Capturer. }
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
import android.os.Build;

import java.io.IOException;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.hardware.Camera.Size;
import android.media.CameraProfile;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.content.SharedPreferences;

public class LmiVideoCapturerInternal extends SurfaceView implements Camera.PreviewCallback, SurfaceHolder.Callback {
	private static String TAG = "LmiVideoCapturerInternal";
	private LmiVideoCapturerCapability[] capabilityArray = null;
	private int deviceId;
	private Camera camera = null;
	private Camera.Size size;
	private PixelFormat pixelFormat;
	private String fourCC;
	SurfaceHolder holder = null;
	Activity activity = null;
	LmiVideoCapturerInternal self;
	List<Integer> formatList;

	BlockingQueue<byte[]> readyFrames = new LinkedBlockingQueue<byte[]>();

	public static final int ORIENTATION_UP = 0;
	public static final int ORIENTATION_DOWN = 1;
	public static final int ORIENTATION_LEFT = 2;
	public static final int ORIENTATION_RIGHT = 3;
	int orientation = ORIENTATION_UP;
	boolean mirrored = false;
	boolean addedSurfaceToLayout = false;
	private static boolean paused = false;
	private boolean stopping = false;
	private boolean active = false;

	private static final int JPEG = 256;
	private static final int NV16 = 16;
	private static final int NV21 = 17;
	private static final int YUY2 = 20;
	private static final int YV12 = 842094169;

	private int width = 0;
	private int height = 0;	
	
	public LmiVideoCapturerInternal(final Context context, final Activity activity, final String id) {
		super(context);
		Log.i(TAG,"constructor for "+ id);
		active = true;
		deviceId = Integer.parseInt(id);
		this.activity = activity;

		holder = getHolder();
		holder.addCallback(this);
		holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		Log.i(TAG,"constructor exit");
	}

	public LmiVideoCapturerCapability[] getCapabilities() {
		Log.i(TAG,"getCapabilities()");
		if(null == capabilityArray)
			enumerateCapabilities(false);
		return capabilityArray;
	}
	
/*	public LmiVideoCapturerCapability[] getCapabilities(boolean anyFormat) {
		Log.i(TAG,"getCapabilities(anyFormat:"+anyFormat+")");
		enumerateCapabilities(anyFormat);
		return capabilityArray;
	}
*/
    private static boolean isSupported(String value, List<String> supported) {
        return supported == null ? false : supported.indexOf(value) >= 0;
    }

    private void setAdvancedCameraParameters() {


        Log.i(TAG, "Setting advanced camera parameters");
        Camera.Parameters mParameters = camera.getParameters();

         // Set flash mode.
        String flashMode = Camera.Parameters.FLASH_MODE_OFF;

        List<String> supportedFlash = mParameters.getSupportedFlashModes();
        if (isSupported(flashMode, supportedFlash))
        {
            mParameters.setFlashMode(flashMode);
        }
        else
        {
            flashMode = mParameters.getFlashMode();
            if (flashMode == null)
            {
                flashMode = Camera.Parameters.FLASH_MODE_OFF;
            }
        }

        // Set white balance parameter.
        String whiteBalance = Camera.Parameters.WHITE_BALANCE_AUTO;
        if (isSupported(whiteBalance,
                mParameters.getSupportedWhiteBalance()))
        {
            mParameters.setWhiteBalance(whiteBalance);
        }
        else
        {
            whiteBalance = mParameters.getWhiteBalance();
            if (whiteBalance == null)
            {
                whiteBalance = Camera.Parameters.WHITE_BALANCE_AUTO;
            }
        }

        // Set zoom.
        if (mParameters.isZoomSupported())
        {
            mParameters.setZoom(0);
        }

        // Set continuous autofocus. API9
		if (Build.MANUFACTURER.toLowerCase().equalsIgnoreCase("amazon") && Build.DEVICE.equalsIgnoreCase("d01e")){
					Log.i(TAG,"support for autofocus is off for amazon kindle HD");
		}else{
			List<String> supportedFocus = mParameters.getSupportedFocusModes();
			 if (isSupported(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO, supportedFocus)) {
				 mParameters.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO);
			 }
		}
 
	if (Build.MANUFACTURER.toLowerCase().equalsIgnoreCase("samsung") && 
			Build.DEVICE.equalsIgnoreCase("manta") &&
			Build.MODEL.equalsIgnoreCase("Nexus 10")){
					Log.i(TAG,"video-stabilization-supported is off for Nexus 10");
		}else{ 
          String stabSupported = mParameters.get("video-stabilization-supported");
          if ("true".equals(stabSupported))
          {
              mParameters.set("video-stabilization", "true");
          }
		} 
 
         // Set JPEG quality.
         int jpegQuality = CameraProfile.getJpegEncodingQualityParameter(CameraProfile.QUALITY_HIGH);
         mParameters.setJpegQuality(jpegQuality);

        camera.setParameters(mParameters);
    }

    private String savedFormat;
    private int savedWidth;
    private int savedHeight;
    private int savedFrameRate;
    
	public boolean start(String format, int width, int height, int frameRate) {
		Camera.Parameters parameters;
		int pixelFormatInt = 0;
		boolean forcedOrientation = false;
		stopping = false;
		Log.i(TAG,"	public boolean start(String format:"+format+", int width:"+width+", int height:"+height+", int frameRate:"+frameRate+")");

		// Save just in case the camera has an error and needs to be restarted
		savedFormat = format;
		savedWidth = width;
		savedHeight = height;
		savedFrameRate = frameRate;
		
		try {
			if (deviceId == LmiVideoCapturerManager.BACK) {
				camera = Camera.open();
				orientation = getOrientation(deviceId);
				forcedOrientation = isOrientationForced(deviceId);
				mirrored = getMirrored(deviceId);
			} else if (deviceId == LmiVideoCapturerManager.FRONT) {
				camera = getFrontCamera();
				orientation = getOrientation(deviceId);
				forcedOrientation = isOrientationForced(deviceId);
				mirrored = getMirrored(deviceId);
			} else {
				camera = getCameraUsingAPI9(deviceId);
			}

			if (camera == null) {
				Log.e(TAG, "Unable to find camera, device Id: " + Integer.toString(deviceId));
				return false;
			}

			/* override orientation if API9 is available */
			if (! forcedOrientation) {
				getOrientationUsingAPI9(deviceId);
			}
			
			/* Check whether the resolution matches a particular capability. */
			boolean resolutionFound = false;
			for(int i = 0; i < capabilityArray.length; i++)
			{
				if( (capabilityArray[i].getWidth() == width) && (capabilityArray[i].getHeight() == height) )
				{
					resolutionFound = true;
					break;
				}
			}
			
			/* If there is no match, pick the resolution which is less than and closest to the resolution set, based on height. */
			if(!resolutionFound)
			{
				int newWidth = 0;
				int newHeight = 0;
				for(int i = 0; i < capabilityArray.length; i++)
				{
					int curHeight = capabilityArray[i].getHeight();
					if( curHeight <= height && curHeight > newHeight)
					{
						newHeight = curHeight;
						newWidth = capabilityArray[i].getWidth();
					}
				}
				width = newWidth;
				height = newHeight;
			}

			
			int minFrameRateMatch = 0;
			int minFrameRate = 0;
			int maxFrameRate = 0;
			
			/* The frame rate provided is the max frame rate, find the min frame rate which is closest to the max frame rate. 
			 * If there is no matching frame rate, choose the one which is less than and closest to the provided frame rate. */
			for(int i = 0; i < capabilityArray.length; i++)
			{	
				int curMaxFrameRate = capabilityArray[i].getSamplingRate();
				int curMinFrameRate = capabilityArray[i].getSamplingRateMin();
				if(curMaxFrameRate == frameRate)
				{
					if(curMinFrameRate > minFrameRateMatch)
						minFrameRateMatch = curMinFrameRate;
					maxFrameRate = curMaxFrameRate;
				}
				else if(curMaxFrameRate < frameRate)
				{
					if(curMaxFrameRate == maxFrameRate)
					{
						if(curMinFrameRate > minFrameRate)
							minFrameRate = curMinFrameRate;
					} 
					else if(curMaxFrameRate > maxFrameRate)
					{
						minFrameRate = curMinFrameRate;
						maxFrameRate = curMaxFrameRate;
					}
				}
			}
			
			/* If there is an exact match, pick the min frame Rate from the one that closely matches the max frame rate. */
			if(maxFrameRate == frameRate)
			{
				minFrameRate = minFrameRateMatch;
			}
			
			Log.d(TAG, "Starting Camera. format: " + format + " width:" + width + " height:" + height + " min-frameRate: " + minFrameRate + " max-frameRate: " + maxFrameRate);

			parameters = camera.getParameters();
			/* Scale up by 1000 while setting fps, as represented by the camera parameters. */
			if (minFrameRate>0 && maxFrameRate<minFrameRate)
				parameters.setPreviewFpsRange(minFrameRate * 1000, maxFrameRate * 1000);
			parameters.setPreviewSize(width, height);

			parameters.setPreviewFormat(pixelFormatFromString(format));

			camera.setParameters(parameters);
			/* get parameters and verify them */

			parameters = camera.getParameters();
			size = parameters.getPreviewSize();
			pixelFormatInt = parameters.getPreviewFormat();
			fourCC = pixelFormatToString(pixelFormatInt);
			
			Log.d(TAG, "Pixel format: "+fourCC);
			pixelFormat = new PixelFormat();
			PixelFormat.getPixelFormatInfo(pixelFormatInt, pixelFormat);

            setAdvancedCameraParameters();
			parameters = camera.getParameters();

			initializeBuffers();
			setPreviewCallbackWithBuffer(this);

			/* the preview should start after the preview surface is created */
			/* without the surface some cameras do not start */
			if (!addedSurfaceToLayout && activity != null) {
				activity.addContentView(this, new LayoutParams(1,1));
				addedSurfaceToLayout = true;
			}
			this.setVisibility(View.VISIBLE);

			Log.i(TAG, "Camera Started");
		} catch (Exception ex) {
			if (camera != null)
				camera.release();
			Log.e(TAG, "Unable to start camera" + ex.toString());
			return false;
		}

		if (camera != null) {
			camera.setErrorCallback(errorCallback);
		}
		return true;
	}
	
	private Camera.ErrorCallback errorCallback = new Camera.ErrorCallback() {
		@Override
		public void onError(int error, Camera camera) {
			Log.e(TAG, "Begin errorCallback.onError");
			
			if (error ==  Camera.CAMERA_ERROR_SERVER_DIED) {
				Log.e(TAG, "Received CAMERA_ERROR_SERVER_DIED");
				stop();
				start(savedFormat, savedWidth, savedHeight, savedFrameRate);
			}

			Log.e(TAG, "End errorCallback.onError");
		}
	};
	
	private void destroyCamera(){
		Log.i(TAG, "destroyCamera");
		synchronized(this) { 
			if(camera != null){
				camera.stopPreview();
				setPreviewCallbackWithBuffer(null);
				camera.release();
				camera = null;	
				Log.i(TAG, "camera destroyed");
			}
		}
	}
	
	public void stop() {
		Log.i(TAG, "stop");
		stopping = true;
		if (camera != null) {
			setVisibility(View.GONE);
			destroyCamera();	
			Log.i(TAG, "stop: Camera stopped");
		}
		
		Log.i(TAG, "stop: draining frames");
		drainFrames();
		
		if (holder != null) {
			holder.removeCallback(this);
			holder = null;
		}
		activity = null;
		capabilityArray = null;
		formatList = null;

		active = false;
	}
	
	public boolean isActive() {
		return active;
	}

	public void surfaceCreated(SurfaceHolder holder) {
			Log.i(TAG,"	surfaceCreated");
		/* wait for a little while to make sure onResume callback has completed execution to make sure that 'paused' flag has been updated */
		try{
			synchronized(this) { 
				wait(500);
			}
	 	} catch (InterruptedException e) {
	 		//e.printStackTrace();
	 	}

		if (camera == null) {
			Log.e(TAG, "Camera Preview Surface created before camera");
			return;
		}
		try {
			//if (!paused) {
				camera.setPreviewDisplay(holder);
			//}
		} catch (IOException e) {
			//e.printStackTrace();
		}
		
		Log.i(TAG, "Camera Preview Starting");

		try {
			camera.startPreview();
		} catch (RuntimeException e) {
			//e.printStackTrace();
		}		
		Log.i(TAG, "Camera Preview Started");
	}

	public void surfaceDestroyed(SurfaceHolder holder) {	
				Log.i(TAG,"	surfaceDestroyed");
	
		/* wait for a little while to make sure onPause callback has completed execution to make sure that 'paused' flag has been updated */
		try{
			synchronized(this) { 
				wait(500);
			}
	 	} catch (InterruptedException e) {
	 		//e.printStackTrace();
	 	}
		
		if (camera == null) {
			Log.e(TAG, "Camera Preview Surface destroyed before camera");
			return;
		}
		Log.i(TAG, "Camera Stopping");
		camera.stopPreview();
		Log.i(TAG, "Camera Preview Stopped");
		
		if (paused && !stopping)
			return;
		
		destroyCamera();
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int w,	int h) {
	}

	private int pixelFormatFromString(String format) {
		int pixelFormatInt = 0;
		if (format.equals("JPEG")) {
			pixelFormatInt = JPEG;
		} else if (format.equals("NV16")) {
			pixelFormatInt = NV16;
		}  else if (format.equals("NV21")) {
			pixelFormatInt = NV21;
		}  else if (format.equals("YUY2")) {
			pixelFormatInt = YUY2;
		}  else if (format.equals("YV12")) {
			pixelFormatInt = YV12;
		}
		return pixelFormatInt;
	}

	private String pixelFormatToString(int formatInt) {
		String format = "";

		switch (formatInt) {
		case JPEG:
			format = "JPEG";
			break;
		case NV16:
			format = "NV16";
			break;
		case NV21:
			format = "NV21";
			break;
		case YUY2:
			format = "NV21"; /* Android's YUY2 is screwed up */
			break;
		case YV12:
			format = "YV12";
			break;
		}
		return format;
	}

	private void enumerateCapabilities(boolean anyFormat) {

		Log.i(TAG, "enumerateCapabilities entry");

		loadEnumratedCapabilities();	//attempt to load capabilities info from storage
		if(capabilityArray != null)		//if we already have that in storage no needs to enumerate it again
			return;
			
		Camera camera = null;
		Camera.Parameters parameters;
		Log.i(TAG, "Enumerating camera capabilities");
		try {
			if (deviceId == LmiVideoCapturerManager.BACK) {
				camera = Camera.open();
			} else if (deviceId == LmiVideoCapturerManager.FRONT) {
				camera = getFrontCamera();
			} else {
				camera = getCameraUsingAPI9(deviceId);
			}
			if (camera == null) {
				Log.e(TAG, "Unable to find camera, device Id: " + Integer.toString(deviceId));
				return;
			}

			parameters = camera.getParameters();

			List<Integer> formatList = parameters.getSupportedPreviewFormats();
			List<Size> sizeList = parameters.getSupportedPreviewSizes();		
			List<int[]> supportedPreviewFps=parameters.getSupportedPreviewFpsRange();
			List<int[]> supportedPreviewMaxFps = new ArrayList<int[]>(); 
			
			for (int[] sfps : supportedPreviewFps)
			{
				boolean alreadyAdded = false;
				for (int[] fps : supportedPreviewMaxFps)
				{
					/* If max fps is already present, mark it so, and if the current min fps is lesser than
					 * the new min fps, use the one with the higher min value */
					if(fps[1] == sfps[1])
					{
						alreadyAdded = true;
						if(fps[0] < sfps[0])
							fps[0] = sfps[0];
						break;
					}						
				}
				if(!alreadyAdded)
				{
					supportedPreviewMaxFps.add(sfps);
				}
			}
			
			if (formatList == null || sizeList == null || supportedPreviewFps == null) {
				Log.e(TAG, "Failed to get capabilities list");
			}
			
			int numCapabilities = 0;
			for (Integer previewFormat : formatList) {
				for (Size previewSize : sizeList) {
					for (int[] sfps : supportedPreviewMaxFps) {
						Log.d(TAG, "Found Configuration format for  " + Integer.toString(deviceId) +": " + Integer.toString(previewFormat) + " size: " + Integer.toString(previewSize.width) + "x" + Integer.toString(previewSize.height) + " min-sample-rate: " + Integer.toString(sfps[0]/1000) + " max-sampling-rate: " + Integer.toString(sfps[1]/1000));
						numCapabilities++;
					}
				}
// 				if(anyFormat){
// 					break;
// 				}
			}

			capabilityArray = new LmiVideoCapturerCapability[numCapabilities];
			int i = 0;
			for (Integer previewFormat : formatList) {
				for (Size previewSize : sizeList) {
					for (int[] sfps : supportedPreviewMaxFps) {
						String format = pixelFormatToString(previewFormat);
						/* Since the frame rate is scaled up by 1000, scale down by the same. */
						capabilityArray[i] = new LmiVideoCapturerCapability(format, previewSize.width, previewSize.height, sfps[0]/1000, sfps[1]/1000);
						i++;
					}
				}
// 				if(anyFormat){
// 					break;
// 				}
			}
			
		Log.d(TAG, "enumerateCapabilities b4 release");

			camera.release();
		Log.d(TAG, "enumerateCapabilities after release");
			
		} catch (Exception ex) {
		if (camera != null)
				camera.release();
		}

		Log.d(TAG, "enumerateCapabilities b4 save");

		saveEnumratedCapabilities();
		Log.d(TAG, "enumerateCapabilities exit");

		return;
	}

	private Camera getFrontCamera() {
		Camera camera;
		Camera.Parameters parameters;
		Log.i(TAG,"	getFrontCamera");

		if ((camera = getSprintTwinCamDevice()) != null) {
			Log.d(TAG, "Found front cameara using TwinCamDevice");
		} else if ((camera = getHtcFrontFacingCamera()) != null) {
			Log.d(TAG, "Found front cameara using HtcFrontFacingCamera");
		} else if ((camera = getFrontFacingCameraUsingAPI9()) != null) {
			Log.d(TAG, "Found front cameara using API Level 9");
		} else if ((camera = getMotorolaFrontFacingCamera()) != null) {
			Log.d(TAG, "Found front cameara using Motorola API");
		} else {
			camera = Camera.open();
			if (setDualCameraSwitch(camera) == true) {
				Log.d(TAG, "Found front cameara using DualCameraSwitch");
			} else {
				/* camera-id 2 for front camera */
				parameters = camera.getParameters();
				parameters.set("camera-id", 2);
				camera.setParameters(parameters);

				parameters = camera.getParameters();
				/* rear camera has to be rotated */
				try {
					if (Integer.parseInt(parameters.get("camera-id")) != 2) {
						Log.d(TAG, "Found rear camera");
					} else {
						/* Samsung Galaxy S */
						Log.d(TAG, "Found front cameara using camera-id");
					}
				} catch (Exception ex) {
					Log.e(TAG, "Front Camera not found.");
					camera.release();
					return null;
				}
			}
		}
		return camera;
	}

	/* HTC EVO 4G */
	private Camera getSprintTwinCamDevice() {
		Log.i(TAG,"getSprintTwinCamDevice()");
		try {
			Method method = Class.forName("com.sprint.hardware.twinCamDevice.FrontFacingCamera").getDeclaredMethod("getFrontFacingCamera", (Class[]) null);
			return(Camera) method.invoke(null, (Object[]) null);
		} catch (Exception ex) {
			return null;
		}
	}

	/* Samsung Epic 4G */
	private Camera getHtcFrontFacingCamera() {
		Log.i(TAG,"getHtcFrontFacingCamera()");
		try {
			Method method = Class.forName("android.hardware.HtcFrontFacingCamera").getDeclaredMethod("getCamera", (Class[]) null);
			return (Camera) method.invoke(null, (Object[]) null);
		} catch (Exception ex) {
			return null;
		}
	}

	/* Motorola Atrix 4g */
	private Camera getMotorolaFrontFacingCamera() {
		Log.i(TAG,"getMotorolaFrontFacingCamera()");
		try {
			Method method = Class.forName("com.motorola.hardware.frontcamera.FrontCamera").getDeclaredMethod("getFrontCamera", (Class[]) null);
			return (Camera) method.invoke(null, (Object[]) null);
		} catch (Exception ex) {
			Log.e(TAG, "Motorola API error: " + ex.toString());
			return null;
		}
	}

	/* Gingerbread API Only get the last camera until there is full support for front/back */
	private Camera getFrontFacingCameraUsingAPI9() {
		Log.i(TAG,"getFrontFacingCameraUsingAPI9()");
		try {
			Method getNumberOfCameras = Class.forName("android.hardware.Camera").getDeclaredMethod("getNumberOfCameras", new Class[]{});
			int cameraIndex = ((Integer)getNumberOfCameras.invoke(null, new Object[]{})).intValue();
			Object cameraInfo = Class.forName("android.hardware.Camera$CameraInfo").newInstance();
			Field fieldFacing = cameraInfo.getClass().getField("facing");
			Method getCameraInfo = Class.forName("android.hardware.Camera").getMethod("getCameraInfo", Integer.TYPE, Class.forName("android.hardware.Camera$CameraInfo"));
			for (int i = 0; i < cameraIndex; i++) {
				getCameraInfo.invoke( null, i, cameraInfo);
				if (fieldFacing.getInt(cameraInfo) == 1) {
					/* front camera */
					Method open = Class.forName("android.hardware.Camera").getDeclaredMethod("open", new Class[]{int.class});
					return (Camera) open.invoke(null, new Object[]{new Integer(i)});
				}
			}
			return null;
		} catch (Exception ex) {
			return null;
		}
	}

	/* Gingerbread API Only get the last camera until there is full support for front/back */
	private Camera getCameraUsingAPI9(int id) {
		Log.i(TAG,"getCameraUsingAPI9()");
		try {
			Method open = Class.forName("android.hardware.Camera").getDeclaredMethod("open", new Class[]{int.class});
			return (Camera) open.invoke(null, new Object[]{new Integer(id)});
		} catch (Exception ex) {
			return null;
		}
	}

	/* Dell Streak */
	private boolean setDualCameraSwitch(Camera mCamera) {
		Log.i(TAG,"setDualCameraSwitch()");
		try {
			Method method = Class.forName("android.hardware.Camera").getMethod("DualCameraSwitch", int.class);
			method.invoke(mCamera, (int)1);
			return true;
		} catch (Exception ex) {
			return false;
		}
	}

	/* Gingerbread API Only get the last camera until there is full support for front/back */
	private void getOrientationUsingAPI9(int id) {
		Log.i(TAG,"getOrientationUsingAPI9()");
		// Kindle Fire HDX devices seem to be returning incorrect orientation, based on being phone oriented
		if (Build.MANUFACTURER.toLowerCase().equalsIgnoreCase("amazon")) {
			String model = Build.MODEL.toLowerCase();
			if (model.equalsIgnoreCase("kfapwa") || model.equalsIgnoreCase("kfapwi") || model.equalsIgnoreCase("kfthwa") || model.equalsIgnoreCase("kfthwi")) {
				orientation = ORIENTATION_UP;
				return;
			}
		}

		try {
			Object cameraInfo = Class.forName("android.hardware.Camera$CameraInfo").newInstance();
			Method getCameraInfo = Class.forName("android.hardware.Camera").getMethod("getCameraInfo", Integer.TYPE, Class.forName("android.hardware.Camera$CameraInfo"));
			Field fieldOrientation = cameraInfo.getClass().getField("orientation");
			getCameraInfo.invoke( null, id, cameraInfo);
			switch(fieldOrientation.getInt(cameraInfo)) {
			case (0):
				orientation = ORIENTATION_UP;
				break;
			case (90):
				orientation = ORIENTATION_RIGHT;
				break;
			case (180):
				orientation = ORIENTATION_DOWN;
				break;
			case (270):
				orientation = ORIENTATION_LEFT;
				break;
			}
		} catch (Exception ex) {
			return;
		}
	}

	/**
	 * Internal method to return the default or forced orientation for the specified camera
	 * @param camera Either LmiVideoCapturerManager.BACK or LmiVideoCapturerManager.FRONT
	 * @return Returns one of ORIENTATION_UP, ORIENTATION_DOWN, ORIENTATION_LEFT, ORIENTATION_RIGHT
	 */
	private int getOrientation(int camera) {
		int orientation;
		if (deviceId == LmiVideoCapturerManager.FRONT) {
			if (bForceOrientationFront)
				orientation = mForcedOrientationFront;
			else
				orientation = ORIENTATION_LEFT; /* default */
		} else if (deviceId == LmiVideoCapturerManager.BACK) {
			if (bForceOrientationBack)
				orientation = mForcedOrientationBack;
			else
				orientation = ORIENTATION_RIGHT; /* default */
		} else {
			orientation = getOrientation();
		}
		return orientation;
	}
	
	/**
	 * this method is used by external entities to get the setting of the orientation value.
	 * @return Returns the currently set orientation.
	 */
	public int getOrientation() {
		return orientation;
	}

	/**
	 * This method identifies if the orientation is forced for the specified camera
	 * @param camera Either LmiVideoCapturerManager.FRONT or LmiVideoCapturerManager.BACK
	 * @return True if orientation is forced, false if not
	 */
	private boolean isOrientationForced(int camera) {
		if (camera == LmiVideoCapturerManager.FRONT)
			return bForceOrientationFront;
		else if (camera == LmiVideoCapturerManager.BACK)
			return bForceOrientationBack;
		return false;
	}


	/**
	 * Definitions for orientation forcing
	 */
	private static boolean bForceOrientationFront = false;
	private static int mForcedOrientationFront;
	private static boolean bForceOrientationBack = false;
	private static int mForcedOrientationBack;
	
	/**
	 * This static method allows the client to force a specific orientation for either of the
	 * cameras.
	 * @param camera The camera to force orientation to either LmiVideoCapturerManager.BACK or 
	 * LmiVideoCapturerManager.FRONT
	 * @param orientation one of ORIENTATION_UP, ORIENTATION_DOWN, ORIENTATION_LEFT, ORIENTATION_RIGHT
	 */
	public static void forceOrientationStart(int camera, int orientation) {
		if (orientation != ORIENTATION_UP && orientation != ORIENTATION_DOWN &&
			orientation != ORIENTATION_LEFT && orientation != ORIENTATION_RIGHT) {
			Log.d(TAG, "forceOrientationStart: invalid orientation ("+orientation+")");
		}
			
		if (camera == LmiVideoCapturerManager.FRONT){
			bForceOrientationFront = true;
			mForcedOrientationFront = orientation;
		} else if (camera == LmiVideoCapturerManager.BACK) {
			bForceOrientationBack = true;
			mForcedOrientationBack = orientation;
		} else {
			Log.d(TAG, "forceOrientationStart: invalid device ("+camera+")");
		}
	}
	
	/**
	 * This static method will stop forcing the orientation for the specified camera.
	 * @param camera The camera to stop forcing orientation. Either LmiVideoCapturerManager.BACK or 
	 * LmiVideoCapturerManager.FRONT
	 */
	public static void forceOrientationStop(int camera) {
		if (camera == LmiVideoCapturerManager.FRONT){
			bForceOrientationFront = false;
		} else if (camera == LmiVideoCapturerManager.BACK) {
			bForceOrientationBack = false;
		} else {
			Log.d(TAG, "forceOrientationStop: invalid device ("+camera+")");
		}
	}

	/**
	 * Internal method to return the default or forced mirroring for the specified camera
	 * @param camera Either LmiVideoCapturerManager.BACK or LmiVideoCapturerManager.FRONT
	 * @return Returns true if mirrored, or false if not
	 */
	private boolean getMirrored(int camera) {
		boolean mirrored;
		if (deviceId == LmiVideoCapturerManager.FRONT) {
			if (bForceMirrorFront)
				mirrored = mForcedMirrorFront;
			else
				mirrored = true; /* default */
		} else if (deviceId == LmiVideoCapturerManager.BACK) {
			if (bForceMirrorBack)
				mirrored = mForcedMirrorBack;
			else
				mirrored = false; /* default */
		} else {
			mirrored = getMirrored();
		}
		return mirrored;
	}

	public boolean getMirrored() {
		return mirrored;
	}

	/**
	 * Definitions for Mirror forcing
	 */
	private static boolean bForceMirrorFront = false;
	private static boolean mForcedMirrorFront;
	private static boolean bForceMirrorBack = false;
	private static boolean mForcedMirrorBack;
	
	/**
	 * This static method allows the client to force a specific Mirror for either of the
	 * cameras.
	 * @param camera The camera to force Mirror to either LmiVideoCapturerManager.BACK or 
	 * LmiVideoCapturerManager.FRONT
	 * @param mirrored True if mirroring is on or false if not mirrored
	 */
	public static void forceMirrorStart(int camera, boolean mirrored) {
		if (camera == LmiVideoCapturerManager.FRONT){
			bForceMirrorFront = true;
			mForcedMirrorFront = mirrored;
		} else if (camera == LmiVideoCapturerManager.BACK) {
			bForceMirrorBack = true;
			mForcedMirrorBack = mirrored;
		} else {
			Log.d(TAG, "forceMirrorStart: invalid device ("+camera+")");
		}
	}
	
	/**
	 * This static method will stop forcing the Mirror for the specified camera.
	 * @param camera The camera to stop forcing Mirror. Either LmiVideoCapturerManager.BACK or 
	 * LmiVideoCapturerManager.FRONT
	 */
	public static void forceMirrorStop(int camera) {
		if (camera == LmiVideoCapturerManager.FRONT){
			bForceMirrorFront = false;
		} else if (camera == LmiVideoCapturerManager.BACK) {
			bForceMirrorBack = false;
		} else {
			Log.d(TAG, "forceMirrorStop: invalid device ("+camera+")");
		}
	}


	private void initializeBuffers() {
		int bufSize = (size.width * size.height * pixelFormat.bitsPerPixel) / 8;

		Log.d(TAG, "Using callback buffers");

		/*
		 * Must call this before calling addCallbackBuffer to get all the
		 * reflection variables setup
		 */
		initializeAddCallbackBufferMethod();

		/*
		 * Add three buffers to the buffer queue. I re-queue them once they are
		 * used in onPreviewFrame, so we should not need many of them.
		 */
		byte[] buffer = new byte[bufSize];
		addCallbackBuffer(buffer);
		buffer = new byte[bufSize];
		addCallbackBuffer(buffer);
		buffer = new byte[bufSize];
		addCallbackBuffer(buffer);
	}

	/**
	 * These variables are re-used over and over by addCallbackBuffer
	 */
	Method mAcb;
	Object[] mArglist;

	private void initializeAddCallbackBufferMethod() {
		try {
			Class mC = Class.forName("android.hardware.Camera");

			Class[] mPartypes = new Class[1];
			mPartypes[0] = (new byte[1]).getClass(); // There is probably a
														// better way to do
														// this.
			mAcb = mC.getMethod("addCallbackBuffer", mPartypes);

			mArglist = new Object[1];
		} catch (Exception e) {
			Log.e(TAG, "Problem setting up for addCallbackBuffer: "
					+ e.toString());
		}
	}

	/**
	 * This method allows you to add a byte buffer to the queue of buffers to be
	 * used by preview. See:
	 * http://android.git.kernel.org/?p=platform/frameworks
	 * /base.git;a=blob;f=core/java/android/hardware/Camera.java;hb=9d
	 * b3d07b9620b4269ab33f78604a36327e536ce1
	 *
	 * @param b
	 *            The buffer to register. Size should be width * height *
	 *            bitsPerPixel / 8.
	 */
	private void addCallbackBuffer(byte[] b) {
		if (stopping)
			return;
		
		/*
		 * Check to be sure initializeAddCallbackBufferMethod has been called to
		 * setup mAcb and mArglist
		 */
		if (mArglist == null) {
			initializeAddCallbackBufferMethod();
		}

		mArglist[0] = b;
		try {
			mAcb.invoke(camera, mArglist);
		} catch (Exception e) {
			Log.e(TAG, "invoking addCallbackBuffer failed: " + e.toString());
		}
	}

	/**
	 * Use this method instead of setPreviewCallback if you want to use manually
	 * allocated buffers. Assumes that "this" implements Camera.PreviewCallback
	 */
	private void setPreviewCallbackWithBuffer(Object previewCallbackObj) {
		try {
			Class c = Class.forName("android.hardware.Camera");

			Method spcwb = null;
			/*
			 * This way of finding our method is a bit inefficient, but I am a
			 * reflection novice, and didn't want to waste the time figuring out
			 * the right way to do it. since this method is only called once,
			 * this should not cause performance issues
			 */
			Method[] m = c.getMethods();
			for (int i = 0; i < m.length; i++) {
				if (m[i].getName().compareTo("setPreviewCallbackWithBuffer") == 0) {
					spcwb = m[i];
					break;
				}
			}

			/*
			 * If we were able to find the setPreviewCallbackWithBuffer method
			 * of Camera, we can now invoke it on our Camera instance, setting
			 * 'this' to be the callback handler
			 */
			if (spcwb != null) {
				Object[] arglist = new Object[1];
				arglist[0] = previewCallbackObj;
				spcwb.invoke(camera, arglist);
				Log.i(TAG, "setPreviewCallbackWithBuffer: Called method");
			} else {
				Log.i(TAG, "setPreviewCallbackWithBuffer: Did not find method");
			}

		} catch (Exception e) {
			/* TODO Auto-generated catch block */
			Log.i(TAG, "setPreviewCallbackWithBuffer error" + e.toString());
		}
	}

	private void drainFrames() {
		if (readyFrames != null)
			readyFrames.clear();
		readyFrames = null;
		mArglist = null;
	}
	
	public void onPreviewFrame(byte[] frame, Camera camera) {
		if (frame == null && !stopping)
			return;

		try {
			readyFrames.put(frame);
		} catch (Exception e) {
			Log.e(TAG, "unable to add captured frame" + e.toString());
		}
	}

	public byte[] aquireFrame() {
		byte[] frame = null;
		if (!stopping) {
			try {
				frame = readyFrames.poll(30, TimeUnit.MILLISECONDS);
			} catch (InterruptedException e) {
				Log.i(TAG, "No frames avaialble " + e.toString());
			}
			if (stopping)
				return null;
		}
		return frame;
	}

	public void releaseFrame(byte[] frame) {
		addCallbackBuffer(frame);
	}
	
	public int getFrameWidth(){
		return size.width;
	}
	
	public int getFrameHeight(){
		return size.height;
	}

	public static void onActivityPause() {
		paused = true;
	}
	
	public static void onActivityResume() {
		paused = false;
	}	

    private static final String PREFERENCES_CAMERA_INFO = "CAMERA_INFO";
    private static final String PREFERENCES_CAMERA_INFO_LENGTH = "CAMERA_INFO_LEN";
    
	private static final String CAMERA_INFO_FORMAT = "CAMERA_INFO_FORMAT";
	private static final String CAMERA_INFO_WIDTH = "CAMERA_INFO_WIDTH";
	private static final String CAMERA_INFO_HEIGHT = "CAMERA_INFO_HEIGHT";
	private static final String CAMERA_INFO_SAMPLING_RATE_MIN = "CAMERA_INFO_RATE_MIN";
	private static final String CAMERA_INFO_SAMPLING_RATE = "CAMERA_INFO_RATE";

	private void saveEnumratedCapabilities(){
		if	(capabilityArray != null && capabilityArray.length > 0){
		
			final SharedPreferences preferences = this.activity.getSharedPreferences(PREFERENCES_CAMERA_INFO+Integer.toString(deviceId), Activity.MODE_PRIVATE);
			SharedPreferences.Editor edit = preferences.edit();
			if(edit != null){
				edit.putInt(PREFERENCES_CAMERA_INFO_LENGTH, capabilityArray.length);			
	
				int i;
				for(i=0; i<capabilityArray.length; i++){
					edit.putString(CAMERA_INFO_FORMAT+Integer.toString(i)			,capabilityArray[i].getFormat());			
					edit.putInt(CAMERA_INFO_WIDTH+Integer.toString(i)				,capabilityArray[i].getWidth());			
					edit.putInt(CAMERA_INFO_HEIGHT+Integer.toString(i)			,capabilityArray[i].getHeight());			
					edit.putInt(CAMERA_INFO_SAMPLING_RATE_MIN+Integer.toString(i)	,capabilityArray[i].getSamplingRateMin());			
					edit.putInt(CAMERA_INFO_SAMPLING_RATE+Integer.toString(i)	,capabilityArray[i].getSamplingRate());
				}
			edit.commit();
			}
		}
	}
	
	//attempt to load capabilities info from storage
	private void loadEnumratedCapabilities(){
		final SharedPreferences preferences = this.activity.getSharedPreferences(PREFERENCES_CAMERA_INFO+Integer.toString(deviceId), Activity.MODE_PRIVATE);
		int infoLen =  preferences.getInt(PREFERENCES_CAMERA_INFO_LENGTH, -1);
		if(infoLen>0){
			capabilityArray = new LmiVideoCapturerCapability[infoLen];
			int i;
			for(i=0; i<infoLen; i++){
				String format 	= preferences.getString(CAMERA_INFO_FORMAT+Integer.toString(i),			"");			
				int width 		= preferences.getInt(CAMERA_INFO_WIDTH+Integer.toString(i),				0);			
				int height 		= preferences.getInt(CAMERA_INFO_HEIGHT+Integer.toString(i),			0);			
				int rateMin 	= preferences.getInt(CAMERA_INFO_SAMPLING_RATE_MIN+Integer.toString(i),	0);		
				int rateMax 	= preferences.getInt(CAMERA_INFO_SAMPLING_RATE+Integer.toString(i),		0);		
				capabilityArray[i] = new LmiVideoCapturerCapability(format,width, height, rateMin, rateMax);
				Log.d(TAG, "Loading Configuration format for  " + Integer.toString(deviceId) +": " +format + " size: " + Integer.toString(width) + "x" + Integer.toString(height) + " min-sample-rate: " + Integer.toString(rateMin) + " max-sampling-rate: " + Integer.toString(rateMax));

			}			
		}
	}
	
	
}
