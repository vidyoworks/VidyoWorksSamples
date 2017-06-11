package com.internetconnection_demo;

import android.content.Context;
import android.content.IntentFilter;
import android.graphics.Color;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
	private static TextView internetStatus;
	InternetConnector_Receiver mReceiver;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		internetStatus = (TextView) findViewById(R.id.internet_status);

		// At activity startup we manually check the internet status and change
		// the text status
		ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo networkInfo = connectivityManager.getActiveNetworkInfo();
		if (networkInfo != null && networkInfo.isConnected()) {
			changeTextStatus(true);
		} else {
			changeTextStatus(false);
		}

		mReceiver = new InternetConnector_Receiver();
		final IntentFilter filters = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
		//filters.addAction("android.net.wifi.WIFI_STATE_CHANGED");
		//filters.addAction("android.net.wifi.STATE_CHANGE");
		super.registerReceiver(mReceiver, filters);

	}

	// Method to change the text status
	public void changeTextStatus(boolean isConnected) {

		// Change status according to boolean value
		if (isConnected) {
			internetStatus.setText("Internet Connected.");
			internetStatus.setTextColor(Color.parseColor("#00ff00"));
		} else {
			internetStatus.setText("Internet Disconnected.");
			internetStatus.setTextColor(Color.parseColor("#ff0000"));
		}
	}

	@Override
	protected void onPause() {

		super.onPause();
		MyApplication.activityPaused();// On Pause notify the Application
	}

	@Override
	protected void onResume() {

		super.onResume();
		MyApplication.activityResumed();// On Resume notify the Application
	}

}
