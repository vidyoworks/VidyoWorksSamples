package com.vidyo.vidyosample;

import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.content.BroadcastReceiver;
import android.text.format.Formatter;
import android.util.Log;
import android.widget.Toast;
import java.lang.Object;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

import static android.webkit.WebSettings.PluginState.ON;

public class VidyoNetworkBroadcastReceiver extends BroadcastReceiver {
    public  int TYPE_WIFI = 1;
    public  int TYPE_MOBILE = 2;
    public  int TYPE_NOT_CONNECTED = 0;

    private static boolean on = false;
    private String lastInterface = "";
    private static VidyoSampleApplication appInstance;
    public static void SetPolling(boolean on_){

        on = on_;
    }

    public static void SetApp(VidyoSampleApplication app){

        appInstance = app;
    }

    public static NetworkInterface getActiveNetworkInterface() {

        Enumeration<NetworkInterface> interfaces = null;
        try {
            interfaces = NetworkInterface.getNetworkInterfaces();
        } catch (SocketException e) {
            return null;
        }

        while (interfaces.hasMoreElements()) {
            NetworkInterface iface = interfaces.nextElement();
            Enumeration<InetAddress> inetAddresses = iface.getInetAddresses();

        /* Check if we have a non-local address. If so, this is the active
         * interface.
         *
         * This isn't a perfect heuristic: I have devices which this will
         * still detect the wrong interface on, but it will handle the
         * common cases of wifi-only and Ethernet-only.
         */
            while (inetAddresses.hasMoreElements()) {
                InetAddress addr = inetAddresses.nextElement();

                if (!(addr.isLoopbackAddress() || addr.isLinkLocalAddress())) {
                    try {
                        if(iface.isUp())
                            return iface;
                    } catch (SocketException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

        return null;
    }


    /*public String getLocalIpAddress() {
        String total = "";
        try {
            for (Enumeration<NetworkInterface> en = NetworkInterface
                    .getNetworkInterfaces(); en.hasMoreElements();) {
                NetworkInterface intf = en.nextElement();
                String ninterface = intf.toString();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress()) {
                        String ip = Formatter.formatIpAddress(inetAddress.hashCode());
                        String thisTime = ip +  inetAddress.getHostAddress().toString() + "\n.....\n";
                        total +=  thisTime;
                    }
                }
            }
        } catch (SocketException ex) {}
        return total;
    }*/

    @Override
    public void onReceive(Context context, Intent intent) {
        if(on == false)
            return;

        NetworkInterface curInterface = getActiveNetworkInterface();
        if(curInterface.getName().compareTo(lastInterface) == 0)
            return;
        lastInterface = curInterface.getName();
        /*ConnectivityManager cm = (ConnectivityManager) context
                .getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetwork = cm.getActiveNetworkInfo();

        if(activeNetwork == null)
            return;

        String status = activeNetwork.toString();
        String extra = activeNetwork.getExtraInfo();

        Toast.makeText(context, status, Toast.LENGTH_LONG).show();*/

        Log.d("VidyoSampleActivity", "network interface =  " + curInterface.getName());

        appInstance.SetActiveInterface(curInterface.getName());




    }

    /*int getConnectivityStatus(Context context) {
        ConnectivityManager cm = (ConnectivityManager) context
                .getSystemService(Context.CONNECTIVITY_SERVICE);

        NetworkInfo activeNetwork = cm.getActiveNetworkInfo();

        if (null != activeNetwork) {
            if(activeNetwork.getType() == ConnectivityManager.TYPE_WIFI)
                return TYPE_WIFI;

            if(activeNetwork.getType() == ConnectivityManager.TYPE_MOBILE)
                return TYPE_MOBILE;
        }
        return TYPE_NOT_CONNECTED;
    }*/

    /*public String getConnectivityStatusString(Context context) {
        int conn = getConnectivityStatus(context);
        String status = null;
        if (conn == TYPE_WIFI) {
            status = "Wifi enabled";
        } else if (conn == TYPE_MOBILE) {
            status = "Mobile data enabled";
        } else if (conn == TYPE_NOT_CONNECTED) {
            status = "Not connected to Internet";
        }
        return /Users/dinesh/src/TAGS/ApiSamples/3x/Android/VcMonitorNetwork/VcMonitorNetwork/app/src/main/java/com/vidyo/vidyosample/VidyoNetworkBroadcastReceiver.javastatus;
    }*/
}
