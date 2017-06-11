/**
{file:
{name: LmiAudioPlaybackDeviceDeviceInfo.java}
	{description: Audio PlaybackDevice Device Information. }
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

public class LmiAudioPlaybackDeviceDeviceInfo extends LmiAudioDeviceInfo {
	public LmiAudioPlaybackDeviceDeviceInfo() {
		super();
	}
	
	public LmiAudioPlaybackDeviceDeviceInfo(String name, String deviceId, String description) {
		super(name, deviceId, description);
	}
}
