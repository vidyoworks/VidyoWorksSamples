/**
{file:
{name: LmiVideoCapturerCapability.java}
	{description: Video Capturer Capability. }
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

public class LmiVideoCapturerCapability {
	String format;
	int width;
	int height;
	int samplingRateMin;
	int samplingRate;

	public LmiVideoCapturerCapability() {
		format = "";
		width = 0;
		height = 0;
		samplingRateMin = 0;
		samplingRate = 0;
	}
	
	public LmiVideoCapturerCapability(String format, int width, int height, int samplingRateMin, int samplingRateMax) {
		this.format = format;
		this.width = width;
		this.height = height;
		this.samplingRateMin = samplingRateMin;
		this.samplingRate = samplingRateMax;
	}

	public String getFormat() {
		return format;
	}

	public void setFormat(String format) {
		this.format = format;
	}
	
	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}
	
	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}
	
	public int getSamplingRateMin() {
		return samplingRateMin;
	}
	public int getSamplingRate() {
		return samplingRate;
	}
	
	public void setSamplingRateMin(int samplingRate) {
		this.samplingRateMin = samplingRate;
	}
	
	public void setSamplingRate(int samplingRate) {
		this.samplingRate = samplingRate;
	}
}
