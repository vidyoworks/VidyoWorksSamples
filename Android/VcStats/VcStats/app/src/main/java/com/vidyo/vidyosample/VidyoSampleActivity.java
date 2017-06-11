package com.vidyo.vidyosample;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.preference.PreferenceManager;
import android.view.Gravity;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.PopupWindow;
import android.widget.TextView;
import android.media.AudioManager;
import android.provider.Settings;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.WindowManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import com.vidyo.vidyosample.VidyoSampleApplication;
import com.vidyo.LmiDeviceManager.*;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class VidyoSampleActivity extends Activity implements 
	LmiDeviceManagerView.Callback,  
	SensorEventListener,
	View.OnClickListener {

	private static final String TAG = "VidyoSampleActivity";

	private boolean doRender = false;
	
	private LmiDeviceManagerView bcView; // new 2.2.2
	private boolean bcCamera_started = false;
	private static boolean loginStatus = false;
	private boolean cameraPaused = false;
	private boolean cameraStarted = false;
	public static final int CALL_ENDED = 0;
	public static final int MSG_BOX = 1;
	public static final int CALL_RECEIVED = 2;
	public static final int CALL_STARTED = 3;
	public static final int SWITCH_CAMERA = 4;
	public static final int LOGIN_SUCCESSFUL = 5;
	public static final int LIBRARY_STARTED = 6;
	final float degreePerRadian = (float) (180.0f / Math.PI);
	final int ORIENTATION_UP = 0;
	final int ORIENTATION_DOWN = 1;
	final int ORIENTATION_LEFT = 2;
	final int ORIENTATION_RIGHT = 3;
	private float[] mGData = new float[3];
	private float[] mMData = new float[3];
	private float[] mR = new float[16];
	private float[] mI = new float[16];
	private float[] mOrientation = new float[3];

	final int DIALOG_LOGIN = 0;
	final int DIALOG_MSG = 1;
	final int DIALOG_CALL_RECEIVED = 2;
	final int FINISH_MSG = 4;

	VidyoSampleApplication app;
	Handler message_handler;
	StringBuffer message;
	private int currentOrientation;
	private SensorManager sensorManager;
	StringBuffer serverString;
	StringBuffer keyString;
	StringBuffer displayNameString;
	StringBuffer pinString;
	public static boolean isHttps = false;
	String portaAddString;
	String guestNameString;
	String roomKeyString;
	int usedCamera = 1;

	private boolean mIsOnPause = false;
	private ImageView cameraView;
    private AudioManager audioManager;

	private PopupWindow mPopupWindow;

	private String getAndroidSDcardMemDir() throws IOException{
	    File sdCard = Environment.getExternalStorageDirectory();
	    File dir = new File (sdCard.getAbsolutePath() + "/VidyoMobile");
	    dir.mkdirs();
	   
	    String sdDir = dir.toString() + "/";
	    return sdDir;
	}

	private String getAndroidInternalMemDir() throws IOException {
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

	private String writeCaCertificates() {
		try {
			InputStream caCertStream = getResources().openRawResource(R.raw.ca_certificates);
//			File caCertFileName;
//			caCertFileName = getFileStreamPath("ca-certificates.crt");

			File caCertDirectory;
			try {
				String pathDir = getAndroidInternalMemDir();
				caCertDirectory = new File(pathDir);
			} catch (Exception e) {
				caCertDirectory = getDir("marina",0);
			}
 			File cafile= new File(caCertDirectory,"ca-certificates.crt");
			
			FileOutputStream caCertFile = new FileOutputStream(cafile);
			byte buf[] = new byte[1024];
        	int len;
        	while ((len = caCertStream.read(buf)) != -1) {
        		caCertFile.write(buf, 0, len);
        	}
        	caCertStream.close();
        	caCertFile.close();
        	
        	return cafile.getPath();
		}
		catch (Exception e) {
			return null;
		}
	}

  @Override
  public void onCreate(Bundle savedInstanceState) {
	  Log.d(TAG, "entering onCreate");
	  super.onCreate(savedInstanceState);
	  this.requestWindowFeature(Window.FEATURE_NO_TITLE); // disable title bar for dialog

	  setContentView(R.layout.main);

	  message_handler = new Handler() {
			public void handleMessage(Message msg) {
				Bundle b = msg.getData();
				switch (msg.what) {
					case LIBRARY_STARTED:
						app.DisableAutoLogin();
						break;

					case CALL_STARTED:
						app.StartConferenceMedia();
						app.SetPreviewModeON(true);
						app.SetCameraDevice(usedCamera);
						app.DisableShareEvents();
						startDevices();
						break;

					case CALL_ENDED:
						stopDevices();
						showDialog(DIALOG_LOGIN);
						app.RenderRelease();
						break;

					case MSG_BOX:
						message = new StringBuffer(b.getString("text"));
						showDialog(DIALOG_MSG);
						break;

					case SWITCH_CAMERA:
						String whichCamera = (String)(msg.obj);
						boolean isFrontCam = whichCamera.equals("FrontCamera");
						Log.d(VidyoSampleApplication.TAG, "Got camera switch = " + whichCamera);

						// switch to the next camera, force settings are per device.
						// sample does not get this values
						//	bcCamera.switchCamera(isFrontCam, false, 0, false, false);
						break;


				}
			}
	  };
		
//	  app = new VidyoSampleApplication(message_handler);
	  app = (VidyoSampleApplication) getApplication();
	  app.setHandler(message_handler);

	  getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS,
				WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);// get the full screen size from android

	  setContentView(R.layout.conference);
	  bcView = new LmiDeviceManagerView(this,this);
	  View C = findViewById(R.id.glsurfaceview);
	  ViewGroup parent = (ViewGroup) C.getParent();
	  int index = parent.indexOfChild(C);
	  parent.removeView(C);
	  parent.addView(bcView, index);

	  cameraView = (ImageView)findViewById(R.id.action_camera_icon);
	  cameraView.setOnClickListener(this);

	  /* Camera */
	  usedCamera = 1;

	  ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
	  NetworkInfo netInfo = cm.getActiveNetworkInfo();
	  String caFileName = writeCaCertificates();
	  String dialogMessage;
	  setupAudio(); // will set the audio to high volume level

	  currentOrientation = -1;

	  sensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
	  Sensor gSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
	  Sensor mSensor = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
	  sensorManager.registerListener(this, gSensor, SensorManager.SENSOR_DELAY_FASTEST);
	  sensorManager.registerListener(this, mSensor, SensorManager.SENSOR_DELAY_FASTEST);
	  String uniqueId = Settings.Secure.getString(this.getContentResolver(),
			  Settings.Secure.ANDROID_ID);
        
	  if (netInfo == null || !netInfo.isConnected()) {
		  dialogMessage = new String("Network Unavailable!\n" + "Check network connection.");
		  showDialog(FINISH_MSG);
		  //app = null;
		  return;
	  } else if (app.initialize(caFileName, uniqueId, this) == false) {
		  dialogMessage = new String("Initialization Failed!\n" + "Check network connection.");
		  showDialog(FINISH_MSG);
		  //app = null;
		  return;
	  }

	  if(!loginStatus) {
		  showDialog(DIALOG_LOGIN);
		  loginStatus = true;
		  app.HideToolBar(false);
		  app.SetEchoCancellation(true);
	  }
	  Log.d(TAG, "leaving onCreate");
  }
  
  private void setupAudio() {
		int set_Volume = 65535;
		app.SetSpeakerVolume(set_Volume);
  }

	@Override
	protected void onPause() {
		super.onPause();
		Log.d(TAG, "onPause Begin");

		LmiVideoCapturer.onActivityPause();
		mIsOnPause = true;
		pauseCall();
		if (cameraStarted) {
			cameraPaused = true;
			cameraStarted = false;
		} else {
			cameraPaused = false;
		}
		app.DisableAllVideoStreams();

		if (this.isFinishing()) {
		}

		Log.d(TAG, "onPause End");
		app.EnableAllVideoStreams();
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		stopDevices();
		app.uninitialize();
	}

	@Override
	public void onResume() {
		super.onResume();
		mIsOnPause = false;
		Log.d(TAG, "onResume Begin");
		resumeCall();
		app.EnableAllVideoStreams();
		Log.d(TAG, "onResume End");
	}

	@Override
	public void onBackPressed() {
		super.onBackPressed();
		stopDevices();
		app.uninitialize();
		finish();
	}

	void startDevices() {
		doRender = true;
	}
	
	void stopDevices() {
		doRender = false;
	}

	private void resumeCall() {
		this.bcView.onResume();
	}

	private void pauseCall() {
		this.bcView.onPause();
	}

	@Override
	public void onWindowFocusChanged(final boolean hasWindowFocus) {
		super.onWindowFocusChanged(hasWindowFocus);
		Log.d(TAG, "ACTIVITY ON WINDOW FOCUS CHANGED " + (hasWindowFocus ? "true" : "false"));
		if (hasWindowFocus && !mIsOnPause) {
			resumeCall();
			app.EnableAllVideoStreams();
		}
	}

	protected void ReadCredentials()
	{
		SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);

		serverString   = new StringBuffer(settings.getString("ServerString", "https://vidyocloud.com"));
		keyString = new StringBuffer(settings.getString("KeyString", "TIOdOwI3h2"));
		displayNameString = new StringBuffer(settings.getString("DisplayNameString", "Android user"));
		pinString = new StringBuffer(settings.getString("PinString", ""));
	}

	protected void SaveCredentials()
	{
		SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);
		SharedPreferences.Editor editor = settings.edit();
		editor.putString("ServerString", serverString.toString());
		editor.putString("KeyString", keyString.toString());
		editor.putString("DisplayNameString", displayNameString.toString());
		editor.putString("PinString", pinString.toString());
		editor.commit();
	}


	
	protected Dialog onCreateDialog(int id) {
		if (id == DIALOG_LOGIN) {
			LayoutInflater factory = LayoutInflater.from(this);
			final View textEntryView = factory.inflate(R.layout.custom_dialog, null);
			ReadCredentials();

			final Button roomlink_button = (Button) textEntryView.findViewById(R.id.roomlink_button);
			
			TextView server   = (TextView) textEntryView.findViewById(R.id.vidyoportal_edit);
			TextView key = (TextView) textEntryView.findViewById(R.id.key_edit);
			TextView displayName = (TextView) textEntryView.findViewById(R.id.displayname_edit);
			TextView pin = (TextView) textEntryView.findViewById(R.id.pin_edit);

			server.setText(serverString.subSequence(0, serverString.length()));
			key.setText(keyString.subSequence(0, keyString.length()));
			displayName.setText(displayNameString.subSequence(0, displayNameString.length()));
			pin.setText(pinString.subSequence(0, pinString.length()));

			roomlink_button.setOnClickListener(new View.OnClickListener() {
				
				@Override
				public void onClick(View v) {
					TextView server   = (TextView) textEntryView.findViewById(R.id.vidyoportal_edit);
					TextView key = (TextView) textEntryView.findViewById(R.id.key_edit);
					TextView displayName = (TextView) textEntryView.findViewById(R.id.displayname_edit);
					TextView pin = (TextView) textEntryView.findViewById(R.id.pin_edit);

					serverString   = new StringBuffer(server.getEditableText().toString());
					keyString = new StringBuffer(key.getEditableText().toString());
					displayNameString = new StringBuffer(displayName.getEditableText().toString());
					pinString = new StringBuffer(pin.getEditableText().toString());

					SaveCredentials();

					app.JoinRoomLink(server.getEditableText().toString(),
							key.getEditableText().toString(),
							displayName.getEditableText().toString(),
							pin.getEditableText().toString());
					removeDialog(DIALOG_LOGIN);
				}
			});

			LayoutParams lp = new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT);
			textEntryView.setLayoutParams(lp);
			return new AlertDialog.Builder(this).setTitle("Login to VidyoPortal").setView(textEntryView)
			.setNegativeButton("Exit", 
					new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int whichButton) {
					finish();
					}}).create();
		} else if (id == DIALOG_MSG) {  // Handle network errors - cannot proceed situations
			AlertDialog alert;
			AlertDialog.Builder builder;
			stopDevices();			
			
			builder = new AlertDialog.Builder(this).setTitle(message)
					.setPositiveButton("OK",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog,
										int whichButton) {
									removeDialog(DIALOG_MSG);
									showDialog(DIALOG_LOGIN);
								}
							});
			alert = builder.create();			
			return alert;

		} else if (id == FINISH_MSG) {  // Handle network errors - cannot proceed situations
			AlertDialog alert;
			AlertDialog.Builder builder;
			stopDevices();
		
			builder = new AlertDialog.Builder(this).setTitle(message)
				.setPositiveButton("OK",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int whichButton) {
								removeDialog(FINISH_MSG);
								finish();
							}
						});
			alert = builder.create();
			return alert;
		}

		return null;
	}

	public void LmiDeviceManagerViewRender() {
		if (doRender)
			app.Render();
	}

	public void LmiDeviceManagerViewResize(int width, int height) {
		app.Resize(width, height);
	}

	public void LmiDeviceManagerViewRenderRelease() {
		app.RenderRelease();
	}

	public void LmiDeviceManagerViewTouchEvent(int id, int type, int x, int y) {
		app.TouchEvent(id, type, x, y);
		ShowOrHidePanel();
	}

	public int LmiDeviceManagerCameraNewFrame(byte[] frame, String fourcc,
			int width, int height, int orientation, boolean mirrored) {
		return app.SendVideoFrame(frame, fourcc, width, height, orientation, mirrored);
	}

	public int LmiDeviceManagerMicNewFrame(byte[] frame, int numSamples,
			int sampleRate, int numChannels, int bitsPerSample) {
		return app.SendAudioFrame(frame, numSamples, sampleRate, numChannels,
				bitsPerSample);
	}

	public int LmiDeviceManagerSpeakerNewFrame(byte[] frame, int numSamples,
			int sampleRate, int numChannels, int bitsPerSample) {
		return app.GetAudioFrame(frame, numSamples, sampleRate, numChannels,
				bitsPerSample);
	}

	public void onAccuracyChanged(Sensor sensor, int accuracy) {
	}

	public void onSensorChanged(SensorEvent event) {
		int newOrientation = currentOrientation;

		int type = event.sensor.getType();
		float[] data;
		if (type == Sensor.TYPE_ACCELEROMETER) {
			data = mGData; /* set accelerometer data pointer */
		} else if (type == Sensor.TYPE_MAGNETIC_FIELD) {
			data = mMData; /* set magnetic data pointer */
		} else {
			return;
		}
		/* copy the data to the appropriate array */
		for (int i = 0; i < 3; i++)
			data[i] = event.values[i];		/* copy the data to the appropriate array */

		/*
		 * calculate the rotation data from the latest accelerometer and
		 * magnetic data
		 */
		Boolean ret = SensorManager.getRotationMatrix(mR, mI, mGData, mMData);
		if (ret == false)
			return;
		
		SensorManager.getOrientation(mR, mOrientation);

		Configuration config = getResources().getConfiguration();
		boolean hardKeyboardOrientFix = (config.hardKeyboardHidden == Configuration.HARDKEYBOARDHIDDEN_NO);
		
		int pitch = (int) (mOrientation[1] * degreePerRadian);
		int roll = (int) (mOrientation[2] * degreePerRadian);

		if (pitch < -45) {
			if (hardKeyboardOrientFix)
				newOrientation = ORIENTATION_LEFT;
			else
				newOrientation = ORIENTATION_UP;
		} else if (pitch > 45) {
			if (hardKeyboardOrientFix)
				newOrientation = ORIENTATION_RIGHT;
			else
				newOrientation = ORIENTATION_DOWN;
		} else if (roll < -45 && roll > -135) {
			if (hardKeyboardOrientFix)
				newOrientation = ORIENTATION_UP;
			else
				newOrientation = ORIENTATION_RIGHT;
		} else if (roll > 45 && roll < 135) {
			if (hardKeyboardOrientFix)
				newOrientation = ORIENTATION_DOWN;
			else
				newOrientation = ORIENTATION_LEFT;
		}

		//	Log.d(app.TAG, "Orientation: " + newOrientation + " pitch: " + pitch + " roll: " + roll);
		if (newOrientation != currentOrientation) {
			currentOrientation = newOrientation;
			app.SetOrientation(newOrientation);
		}

		/*
		if (newOrientation != currentOrientation) {
			camera.setCameraOrientation( newOrientation );
			currentOrientation = newOrientation;
		}
		*/
	}

	@Override
	public void onClick(View arg0) {
		// TODO Auto-generated method stub
		switch (arg0.getId()) {
			case R.id.action_camera_icon:
				if (usedCamera == 1) {
					usedCamera = 0;
				} else {
					usedCamera = 1;
				}
				app.SetCameraDevice(usedCamera);

/*				if (bcCamera.isStarted()) {
					if (bcCamera.useFrontCamera) {
						bcCamera.switchCamera(false, false, 0, false, false);
						app.SetCameraDevice(1);
						cameraView.setImageResource(R.drawable.icon_back_camera);
					} else {
						bcCamera.switchCamera(true, false, 0, false, false);
						app.SetCameraDevice(0);
						cameraView.setImageResource(R.drawable.icon_front_camera);
					}
				}
				*/
		}
	}
	
	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		Log.d(TAG, "in onConfigurationChanged");
	}



	long lastUpdate = 0;
	public void ShowOrHidePanel()
	{
		long curTime = System.currentTimeMillis();

		if ((curTime - lastUpdate) < 2000) {
			//make sure we dont handle too frequently
			return;
		}
		lastUpdate = curTime;

		if(mPopupWindow != null)
		{
			//if already showing just hide the panel
			if (mPopupWindow.isShowing()) {
				mPopupWindow.dismiss();
			}
			mPopupWindow = null;
			return;
		}

		//else show it
		LayoutInflater inflater = (LayoutInflater) getApplicationContext().getSystemService(LAYOUT_INFLATER_SERVICE);
		View customView = inflater.inflate(R.layout.activity_popup_toolbox,null);
		mPopupWindow = new PopupWindow(
				customView,
				LayoutParams.WRAP_CONTENT,
				LayoutParams.WRAP_CONTENT
		);


		if(mPopupWindow != null)
			mPopupWindow.showAtLocation(cameraView, Gravity.CENTER,0,0);

		Button btnShowStats =(Button)customView.findViewById(R.id.button_show_stats);
		btnShowStats.setOnClickListener(new View.OnClickListener()
		{
			public void onClick(View v)
			{
				VidyoSampleActivity.this.ShowStats();


			}
		});
	}

	public void ShowStats() {
		app.ShowStats();

	}
}
