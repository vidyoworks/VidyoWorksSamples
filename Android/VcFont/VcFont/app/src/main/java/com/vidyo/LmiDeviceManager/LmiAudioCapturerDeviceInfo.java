/**
{file:
{name: LmiAudioCapturerDeviceInfo.java}
	{description: Audio Capturer Device Information. }
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

public class LmiAudioCapturerDeviceInfo extends LmiAudioDeviceInfo {
	String name;
	String deviceId;
	String description;

	public LmiAudioCapturerDeviceInfo() {
		super();
	}
	
	public LmiAudioCapturerDeviceInfo(String name, String deviceId, String description) {
		super(name, deviceId, description);
	}

	//TODO: figure out way to do these operations the correct way
	private static boolean enableEchoCancel = false;
	
	//TODO: figure out way to do these operations the correct way
	public static boolean getEnableEchoCancel() {
		return enableEchoCancel;
	}

	//TODO: figure out way to do these operations the correct way
	public static void setEnableEchoCancel(boolean enable) {
		enableEchoCancel = enable;
	}
	
	//TODO: figure out way to do these operations the correct way
	private static boolean enableAutomaticGainControl = false;
	
	//TODO: figure out way to do these operations the correct way
	public static boolean getEnableAutomaticGainControl() {
		return enableAutomaticGainControl;
	}

	//TODO: figure out way to do these operations the correct way
	public static void setEnableAutomaticGainControl(boolean enable) {
		enableAutomaticGainControl = enable;
	}
	
	//TODO: figure out way to do these operations the correct way
	private static boolean enableNoiseSuppression = true;
	
	//TODO: figure out way to do these operations the correct way
	public static boolean getEnableNoiseSuppression() {
		return enableNoiseSuppression;
	}
	
	//TODO: figure out way to do these operations the correct way
	public static void setEnableNoiseSuppression(boolean enable) {
		enableNoiseSuppression = enable;
	}
}
