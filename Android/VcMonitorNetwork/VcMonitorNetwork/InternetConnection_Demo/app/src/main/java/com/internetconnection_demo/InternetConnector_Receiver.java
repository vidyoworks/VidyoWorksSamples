package com.internetconnection_demo;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

import static android.net.ConnectivityManager.TYPE_WIFI;

public class InternetConnector_Receiver extends BroadcastReceiver {
	public InternetConnector_Receiver() {
	}


	int getConnectivityStatus(Context context) {
		ConnectivityManager cm = (ConnectivityManager) context
				.getSystemService(Context.CONNECTIVITY_SERVICE);

		NetworkInfo activeNetwork = cm.getActiveNetworkInfo();
		if (null != activeNetwork) {
			if(activeNetwork.getType() == TYPE_WIFI)
				return 0;

			if(activeNetwork.getType() == ConnectivityManager.TYPE_MOBILE)
				return 1;
		}

		Log.e("xxxx", "network interface =  " + activeNetwork.getType());
		return 2;
	}


	@Override
	public void onReceive(Context context, Intent intent) {
		try {

			boolean isVisible = MyApplication.isActivityVisible();// Check if
																	// activity
																	// is
																	// visible
																	// or not
			Log.i("Activity is Visible ", "Is activity visible : " + isVisible);
			getConnectivityStatus(context);

			// If it is visible then trigger the task else do nothing
			if (isVisible == true) {
				ConnectivityManager connectivityManager = (ConnectivityManager) context
						.getSystemService(Context.CONNECTIVITY_SERVICE);
				NetworkInfo networkInfo = connectivityManager
						.getActiveNetworkInfo();

				// Check internet connection and accrding to state change the
				// text of activity by calling method
				if (networkInfo != null && networkInfo.isConnected()) {

					new MainActivity().changeTextStatus(true);
				} else {
					new MainActivity().changeTextStatus(false);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}
