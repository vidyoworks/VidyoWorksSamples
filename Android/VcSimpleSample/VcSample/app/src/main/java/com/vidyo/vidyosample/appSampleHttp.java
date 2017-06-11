package com.vidyo.vidyosample;


import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.StatusLine;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicHttpResponse;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.HttpParams;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.EntityUtils;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

import android.util.Log;
import android.widget.Toast;
import android.content.Context;
import android.os.*;

class appSampleHttp extends AsyncTask<appSampleHttp.Arguments, Integer, appSampleHttp.Arguments> 
{
    private final String TAG = "appSampleHttp";
    private final int PROGRESS_STARTING = 100;
    private final int PROGRESS_READINGCERTIFICATES = 70;
    private final int PROGRESS_MERGINGCERTIFICATES = 40;
    private final int PROGRESS_INITNETWORK = 10;
    private final int PROGRESS_DONE = 0;
    
    @Override
    protected void onPreExecute () {
		// start the progress
		publishProgress(PROGRESS_STARTING);
    }

    @Override
    protected appSampleHttp.Arguments doInBackground(appSampleHttp.Arguments... params) {
        Log.i(TAG, "doInBackground Begin");
        String EntityID = "";
        
        String portal="http://";
		if (VidyoSampleActivity.isHttps)
			portal="https://";
	
    	appSampleHttp.Arguments args = params[0];     	
    	String urlString = String.format("%1$s/services/v1_1/VidyoPortalUserService/", args.portalString);
    	portal+=urlString;
    	Log.d(TAG, "Sending request to " + portal);
   
    	String SOAPRequestXML = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:v1=\"http://portal.vidyo.com/user/v1_1\">" +
    			"<soapenv:Header/>" +
    			"<soapenv:Body>" +
    		"<v1:MyAccountRequest/>" +
    		"</soapenv:Body>" +
    		"</soapenv:Envelope>";
    	Log.d(TAG, "SOAP Request = " + SOAPRequestXML);
    	
    	String msgLength = String.format("%1$d", SOAPRequestXML.length());
		publishProgress(PROGRESS_INITNETWORK);

		try {
			HttpPost httppost = new HttpPost(portal); 
			StringEntity se = new StringEntity(SOAPRequestXML, HTTP.UTF_8);

			se.setContentType("text/xml");  
	//		httppost.setHeader("Content-Type","application/soap+xml;charset=UTF-8");
			httppost.setHeader("Content-Type","text/xml;charset=UTF-8");

			httppost.setHeader("SOAPAction", "\"myAccount\"");
	//		httppost.setHeader("Accept-Encoding", "gzip,deflate");
	//		httppost.setHeader("Content-Length", msgLength);
			String auth = "Basic " + android.util.Base64.encodeToString((args.userString + ":" + args.passwordString).getBytes(), android.util.Base64.NO_WRAP);
			httppost.setHeader("Authorization", auth);
			httppost.setEntity(se);  

			HttpClient httpclient = new DefaultHttpClient();
			HttpResponse httpResponse = (HttpResponse) httpclient.execute(httppost);

			Log.d(TAG, httpResponse.getStatusLine().toString());
			Log.d(TAG, "EntityID="+httpResponse.getEntity().toString());
			
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			dbf.setNamespaceAware(true);
			DocumentBuilder db = dbf.newDocumentBuilder();
			InputStream is = httpResponse.getEntity().getContent();
			
			InputSource isrc = new InputSource();
			Document doc = db.parse(is);

			EntityID = getSoapValue(doc,"entityID");
			if (EntityID == null) {
				Log.e(TAG, "EntityID tag not found!");
				Toast mesg = Toast.makeText(args.context, "ENtityID tag not found!", Toast.LENGTH_LONG);
				mesg.show();
			}

		    Log.d(TAG, "EntityID = "+getSoapValue(doc,"entityID"));
		    Log.d(TAG, "OwnerID = "+getSoapValue(doc,"ownerID"));
		    Log.d(TAG, "DisplayName = "+getSoapValue(doc,"displayName"));
		    Log.d(TAG, "extension = "+getSoapValue(doc,"extension"));
	    } catch (Exception e) {
	        e.printStackTrace();
	    }
		
	    JoinConference (args, EntityID);
    	Log.i(TAG, "doInBackground End");
    	return(args);
    }

	public void JoinConference(appSampleHttp.Arguments args, String EntityId) {
		String portal="http://";
		if (VidyoSampleActivity.isHttps)
			portal="https://";
			
		String urlString = String.format("%1$s/services/v1_1/VidyoPortalUserService/", args.portalString);
		portal += urlString;
		String SOAPRequestXML = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:v1=\"http://portal.vidyo.com/user/v1_1\">" +
			"<soapenv:Header/>" +
			"<soapenv:Body>" +
			"<v1:JoinConferenceRequest>" +
				"<v1:conferenceID>" + EntityId +
			"</v1:conferenceID>"+
			"</v1:JoinConferenceRequest>"+
			"</soapenv:Body>" +
			"</soapenv:Envelope>";
		Log.d(TAG, "SOAP Request = " + SOAPRequestXML);

		String msgLength = String.format("%1$d", SOAPRequestXML.length());
		publishProgress(PROGRESS_INITNETWORK);

		try {
			HttpPost httppost = new HttpPost(portal);
			StringEntity se = new StringEntity(SOAPRequestXML, HTTP.UTF_8);

			se.setContentType("text/xml");

			httppost.setHeader("Content-Type","text/xml;charset=UTF-8");

			httppost.setHeader("SOAPAction", "\"JoinConference\"");

			String auth = "Basic " + android.util.Base64.encodeToString((args.userString + ":" + args.passwordString).getBytes(), android.util.Base64.NO_WRAP);
			httppost.setHeader("Authorization", auth);

			httppost.setEntity(se);

			HttpClient httpclient = new DefaultHttpClient();
			HttpResponse httpResponse = (HttpResponse) httpclient.execute(httppost);

			StatusLine status = httpResponse.getStatusLine();
			Log.d(TAG, "Join status code = " + status.getStatusCode());

			Log.d(TAG, httpResponse.getStatusLine().toString());
			Log.d(TAG, "Staus="+httpResponse.getEntity().toString());

			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			InputStream is = httpResponse.getEntity().getContent();
			
			InputSource isrc = new InputSource();
			Document doc = db.parse(is);

			//   Log.d(TAG, "EntityID = "+getSoapValue(doc,"ns1:entityID"));
			//   Log.d(TAG, "OwnerID = "+getSoapValue(doc,"ns1:ownerID"));
			//  Log.d(TAG, "DisplayName = "+getSoapValue(doc,"ns1:displayName"));
			//  Log.d(TAG, "extension = "+getSoapValue(doc,"ns1:extension"));
	    } catch (Exception e) {
	        e.printStackTrace();
	    }

    	Log.i(TAG, "JoinConference End"); 
	}

    public String getSoapValue(Document doc, String name) {
		NodeList nodes = doc.getElementsByTagNameNS("*", name);
		if (nodes.getLength() > 0) {
			Element element = (Element) nodes.item(0);
		
			NodeList entityIDs = element.getChildNodes();

			Node entityID = entityIDs.item(0);
			String nodevalue = entityID.getNodeValue();
			return nodevalue;
		}
		return null;
    }

    @Override
	protected void onCancelled() {
		// stop the progress
		publishProgress(PROGRESS_DONE);
	}

    @Override
    protected void onProgressUpdate(Integer... progress) {
    	switch (progress[0]) {
			case PROGRESS_DONE:
			case PROGRESS_READINGCERTIFICATES:
			case PROGRESS_MERGINGCERTIFICATES:
			case PROGRESS_INITNETWORK:
			case PROGRESS_STARTING:
	    		break;
    	}
    }
    
    @Override
    protected void onPostExecute(appSampleHttp.Arguments result) {
		publishProgress(PROGRESS_DONE);

    	if (result == null)
    		return;
    	
//		Conference.start(result.context);

        Log.i(TAG, "onPostExecute End");
    }
	
    public static class Arguments {
    	String portalString;
    	String userString;
    	String passwordString;
    	Context context;

        public Arguments(String portal, String user, String password, Context context) {
        	portalString = portal;
        	userString = user;
        	passwordString = password;
        	this.context = context;
        }
    }
}
