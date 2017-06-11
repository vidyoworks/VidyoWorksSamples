package com.vidyo.vidyosample;

import java.io.File;
import java.io.IOException;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class VidyoSampleApplication extends android.app.Application {
	public static final String TAG = "VidyoSample";
	static Handler hdlr;
	boolean libInitialized;

	public VidyoSampleApplication() {
		libInitialized = false;
	}
	
	public VidyoSampleApplication(Handler h) {
		hdlr = h;
		libInitialized = false;
	}

	public void setHandler(Handler h) {
		hdlr = h;
	}

	private String getAndroidInternalMemDir()  throws IOException {
		File fileDir = getFilesDir(); //crashing
		if (fileDir != null) {
			String filedir=fileDir.toString() + "/";
			Log.d(TAG, "file directory = " + filedir);
			return filedir;
		} else {
			Log.e(TAG, "Something went wrong, filesDir is null");
		}
		return null;
	}

	private String getAndroidCacheDir() throws IOException{
		File cacheDir = getCacheDir();
		if (cacheDir != null) {
			String filedir=cacheDir.toString() + "/";
			return filedir;
		}
		return null;
	}
	
	/**
	* This function is temporary until when we start using internal memory and cache
	*/
	private String getAndroidSDcardMemDir() throws IOException{
	    File sdCard = Environment.getExternalStorageDirectory();
	    File dir = new File (sdCard.getAbsolutePath() + "/VidyoMobile");
	    dir.mkdirs();
	   
	    String sdDir = dir.toString() + "/";
	    return sdDir;
	}
	
	public boolean initialize(String caFileName, String uniqueId, Activity activity) {
		String pathDir;
		try {
			pathDir = getAndroidInternalMemDir();
//			pathDir = getAndroidSDcardMemDir();
		} catch (Exception e) { 
			pathDir = "/data/data/com.vidyo.vidyosample/app_marina/";
		}

		String logDir;
		try {
			logDir = getAndroidCacheDir();
//			logDir = getAndroidSDcardMemDir();
		} catch (Exception e) {
			logDir = "/data/data/com.vidyo.vidyosample/app_marina/";
		}

		libInitialized = Construct(caFileName,logDir, pathDir, uniqueId, activity);
		return libInitialized;
	}
	
	public void uninitialize() {
		Dispose();
	}
	public void cameraSwitchCallback(String name) {
		Message msg = Message.obtain();
		msg.obj = name;
		msg.setTarget(hdlr);
		msg.what = VidyoSampleActivity.SWITCH_CAMERA;
		msg.sendToTarget();	
	}

	public void messageBox(String s) {
		Bundle b = new Bundle();
		b.putString("text", s);
		Message m = Message.obtain();
		m.what = VidyoSampleActivity.MSG_BOX;
		m.setData(b);
		m.setTarget(hdlr);
		m.sendToTarget();
	}

	public void callEndedCallback() {	
		Log.d(TAG, "Call ended received!");
		Message msg = Message.obtain();
		msg.setTarget(hdlr);
		msg.what = VidyoSampleActivity.CALL_ENDED;
		msg.sendToTarget();		
	}
	
	public void callStartedCallback() {	
		Log.d(TAG, "Call started received!");
		Message msg = Message.obtain();
		msg.setTarget(hdlr);
		msg.what = VidyoSampleActivity.CALL_STARTED;
		msg.sendToTarget();		
	}

	public void loginSuccessfulCallback() {	
		Log.d(TAG, "Login Successful received!");
		Message msg = Message.obtain();
		msg.setTarget(hdlr);
		msg.what = VidyoSampleActivity.LOGIN_SUCCESSFUL;
		msg.sendToTarget();		
	}

	public void libraryStartedCallback() {
		Log.d(TAG, "Library started received!");
		Message msg = Message.obtain();
		msg.setTarget(hdlr);
		msg.what = VidyoSampleActivity.LIBRARY_STARTED;
		msg.sendToTarget();
	}

	/*
	 * Native methods that are implemented by the 'VidyoSample' native library,
	 */
	public native boolean Construct(String caFileName, String logDir, String pathDir, String uniqueId, Activity activity);

	public native void Dispose();
	
	public native void AutoStartMicrophone(boolean autoStart);
	public native void AutoStartCamera(boolean autoStart);
	public native void AutoStartSpeaker(boolean autoStart);	

	public native void Login(String vidyoportalName, String userName, String passwordName);
	public native void JoinRoomLink(String vidyoportalName, String keyName, String dispayName, String key);
	
	public native void Render();
	public native void RenderRelease();
	public native void HideToolBar(boolean disablebar);

    public native void SetCameraDevice(int camera);
    public native void SetPreviewModeON(boolean pip);

	public native void DisableAutoLogin();

	public native void Resize(int width, int height);

	public native int SendAudioFrame(byte[] frame, int numSamples,
			int sampleRate, int numChannels, int bitsPerSample);

	public native int GetAudioFrame(byte[] frame, int numSamples,
			int sampleRate, int numChannels, int bitsPerSample);

	public native int SendVideoFrame(byte[] frame, String fourcc, int width,
			int height, int orientation, boolean mirrored);
	
	public native void TouchEvent(int id, int type, int x, int y);
	public native void SetOrientation(int orientation);

	public native void MuteCamera(boolean muteCamera);
	public native void DisableAllVideoStreams();
	public native void EnableAllVideoStreams();
	public native void StartConferenceMedia();
	public native void SetEchoCancellation (boolean aecenable);
	public native void SetSpeakerVolume (int volume);
	public native void DisableShareEvents();
	public native void SetBackgroundColor (int color);
	public native void SetActiveInterface (String interfaceName);
	// load the library - name matches jni/Android.mk
	static {
	    System.loadLibrary("VidyoClientApp");
	    System.loadLibrary("ndkVidyoSample");
	}
}
