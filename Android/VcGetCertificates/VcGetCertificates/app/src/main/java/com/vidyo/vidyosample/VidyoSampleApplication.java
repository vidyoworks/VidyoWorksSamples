package com.vidyo.vidyosample;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.security.KeyStore;
import java.util.Enumeration;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.security.KeyStore;
import java.security.cert.X509Certificate;
import java.util.Enumeration;

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
		logTheCertificates(activity);
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


	/**
	 * Utility function to write the base-64 encoded version of specified input buffer of
	 * specified length to file with specified handle, using specified maximum line length.
	 * Based on LmiBase64Encode, in SDK.
	 * TODO: move to future module AppUtil
	 */
	private void AppUtilBase64EncodeToFile(FileOutputStream output, byte [] input, int lineLen) throws IOException {
		String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		byte [] alphaBytes = alphabet.getBytes();

		int curPos = 0;
		int inputLen = input.length;
		int outputLineLen = 0;
		int a, b, c;

		while (inputLen >= 3)
		{
			a = input[curPos] & 0xFF;
			b = input[curPos+1] & 0xFF;
			c = input[curPos+2] & 0xFF;
			output.write(alphaBytes[a >> 2]);
			output.write(alphaBytes[((a & 0x03) << 4) + (b >> 4)]);
			output.write(alphaBytes[((b & 0x0F) << 2) + (c >> 6)]);
			output.write(alphaBytes[(c & 0x3F)]);
			inputLen -= 3;
			curPos += 3;
			outputLineLen += 4;
			if (outputLineLen >= lineLen)
			{
				output.write('\n');
				outputLineLen = 0;
			}
		}

		if (inputLen == 1)
		{
			a = input[curPos] & 0xFF;
			output.write(alphaBytes[a >> 2]);
			output.write(alphaBytes[(a & 0x03) << 4]);
			output.write('=');
			output.write('=');
			outputLineLen += 4;
		}
		else if(inputLen == 2)
		{
			a = input[curPos] & 0xFF;
			b = input[curPos+1] & 0xFF;
			output.write(alphaBytes[a >> 2]);
			output.write(alphaBytes[((a & 0x03) << 4) + (b >> 4)]);
			output.write(alphaBytes[(b & 0x0F) << 2]);
			output.write('=');
			outputLineLen += 4;
		}

		if (outputLineLen != 0)	{
			output.write('\n');
		}
	}


	private void logTheCertificates(Context context) {

		KeyStore ks = null;
		boolean gotKS = false;
		final String CACERT_SYSTEM_PATH = "system/etc/security/cacerts.bks";
		final String SYSTEM_CACERTS_FILENAME = "system-certificates.crt";
		final String TEMP_CACERTS_FILENAME = "temp-certificates.crt";

			   		/*
			   		 * Open an output file stream to be used to place the system CA Certificates.
			   		 * These will be appended to the application certificate file
			   		 */
		File caCertFileName = context.getFileStreamPath(SYSTEM_CACERTS_FILENAME);

			   		/*
			   		 * If the system certificates file exists already then try to check if the certificate files on the
			   		 * system have been updated.
			   		 */
		if (caCertFileName.exists()) {
			Log.d(TAG, "CA Certs file exists already, skipping system certificate reading!");

			long cafileLastmodified = caCertFileName.lastModified();

			File caCertFile = new File(CACERT_SYSTEM_PATH);
			if (caCertFile.exists()) {
				Log.d(TAG, "cacerts.bks file exists");
				if (caCertFile.lastModified() > cafileLastmodified) {
					Log.d(TAG, "cacerts.bks file modified recently");
				} else {
					return;
				}
			} else {
				return;
			}
		}

		FileOutputStream systemCertsFile;
		try {
			systemCertsFile = new FileOutputStream(caCertFileName);
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
			return;
		}

			   		/*
			   		 * Read the CA Store, ICS way of doing it.  If this is NOT ICS system it will fail
			   		 */
		try {
			ks = KeyStore.getInstance("AndroidCAStore");
			ks.load(null, null);
			gotKS = true;
		} catch (Exception e) {
		}



			   		/*
			   		 * If we did not get the KeyStore using the ICS method, lets try another way.  This is less
			   		 * likely to get what we really need though.
			   		 */
		if (! gotKS) {
			try {
				String pw="VidyoMobile";
				//				char [] pwChar = pw.toCharArray();

				String defaultKSType = KeyStore.getDefaultType();
				ks = KeyStore.getInstance(defaultKSType);
				InputStream trustStoreStream = new FileInputStream(new File(CACERT_SYSTEM_PATH));
				//			    ks.load(trustStoreStream, pwChar);
				ks.load(trustStoreStream, null);

			} catch (Exception e) {
				return;
			}
		}

		if (ks == null)
			return;

			   		/*
			   		 * If the user wants to skip this step then clean up and leave
			   		 */


		try {
			String beginString = "-----BEGIN CERTIFICATE-----\n";
			byte [] beginBytes = beginString.getBytes();
			String endString = "-----END CERTIFICATE-----\n";
			byte [] endBytes = endString.getBytes();

			Enumeration aliases = ks.aliases();
			while (aliases.hasMoreElements()) {
			   				/*
			   				 * If the user wants to skip this step then clean up and leave
			   				 */


				String alias = (String) aliases.nextElement();

				//				LmiTime now = LmiTimeGetCurrentWallTime();
				//				LmiTime notBefore = (LmiTime)(((LARGE_INTEGER*)&certContext->pCertInfo->NotBefore)->QuadPart - LMI_TIME_WIN32_FILE_TIME_OFFSET_) * 100;
				//				LmiTime notAfter = (LmiTime)(((LARGE_INTEGER*)&certContext->pCertInfo->NotAfter)->QuadPart - LMI_TIME_WIN32_FILE_TIME_OFFSET_) * 100;
				//				if (now <= notAfter && now >= notBefore) {

				systemCertsFile.write(beginBytes);

				X509Certificate cert = (X509Certificate)ks.getCertificate(alias);
				//				    Log.d(TAG, "PWC_Cert: Subject DN: " + cert.getSubjectDN().getName());
				//				    Log.d(TAG, "PWC_Cert: Issuer DN: " + cert.getIssuerDN().getName());

				byte [] encoded = cert.getEncoded();
				AppUtilBase64EncodeToFile(systemCertsFile, encoded, 64);

				//				    String certString = cert.toString();
				systemCertsFile.write(endBytes);

				//				}
			}
			systemCertsFile.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
		}
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
	// load the library - name matches jni/Android.mk
	static {
	    System.loadLibrary("VidyoClientApp");
	    System.loadLibrary("ndkVidyoSample");
	}
}
