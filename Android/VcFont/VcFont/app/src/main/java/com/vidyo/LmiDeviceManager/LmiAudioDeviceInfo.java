/**
{file:
{name: LmiAudioDeviceInfo.java}
	{description: Audio Device Information. }
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

public class LmiAudioDeviceInfo {
	String name;
	String deviceId;
	String description;

	public LmiAudioDeviceInfo() {
		name = "";
		deviceId = "";
		description = "";
	}
	
	public LmiAudioDeviceInfo(String name, String deviceId, String description) {
		this.name = name;
		this.deviceId = deviceId;
		this.description = description;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	
	public String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}
	
	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}
}
