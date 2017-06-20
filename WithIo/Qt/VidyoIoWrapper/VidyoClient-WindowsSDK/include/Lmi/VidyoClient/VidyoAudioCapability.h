/** 
{file:
	{name: VidyoAudioCapability.h}
	{description: Audio Capability. }
	{copyright:
		(c) 2013-2015 Vidyo, Inc.,
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
#ifndef VIDYO_AUDIOCAPABILITY_H_ 
#define VIDYO_AUDIOCAPABILITY_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiMediaFormat.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C

/* VidyoAudioCapability */

#define VIDYO_AUDIO_CAPABILITY_DEFAULT_SAMPLE_RATE			32000
#define VIDYO_AUDIO_CAPABILITY_DEFAULT_NUMBER_OF_CHANNELS	1
#define VIDYO_AUDIO_CAPABILITY_DEFAULT_FRAME_INTERVAL		20
#define VIDYO_AUDIO_CAPABILITY_DEFAULT_MEDIA_FORMAT			LMI_MEDIAFORMAT_fl32

typedef struct {
	LmiMediaFormat format;
	LmiUint sampleRate;
	LmiUint numberOfChannels;
	LmiUint bitsPerSample;
	LmiTime frameInterval;
} VidyoAudioCapability;

VidyoAudioCapability* VidyoAudioCapabilityConstruct(VidyoAudioCapability* cap, const LmiMediaFormat* format, LmiUint sampleRate, LmiUint numberOfChannels, LmiTime frameInterval);
VidyoAudioCapability* VidyoAudioCapabilityConstructDefault(VidyoAudioCapability* cap);
VidyoAudioCapability* VidyoAudioCapabilityConstructCopy(VidyoAudioCapability* cap, const VidyoAudioCapability* y);
void VidyoAudioCapabilityDestruct(VidyoAudioCapability* cap);
VidyoAudioCapability* VidyoAudioCapabilityAssign(VidyoAudioCapability* cap, const VidyoAudioCapability* y);
LmiBool VidyoAudioCapabilitySwap(VidyoAudioCapability* cap, VidyoAudioCapability* y);
LmiBool VidyoAudioCapabilityEqual(const VidyoAudioCapability* cap, const VidyoAudioCapability* y);
LmiBool VidyoAudioCapabilityLess(const VidyoAudioCapability* cap, const VidyoAudioCapability* y);
const LmiMediaFormat* VidyoAudioCapabilityGetMediaFormat(const VidyoAudioCapability* cap);
LmiBool VidyoAudioCapabilitySetMediaFormat(VidyoAudioCapability* cap, const LmiMediaFormat* mediaFormat);
LmiUint VidyoAudioCapabilityGetSampleRate(const VidyoAudioCapability* cap);
LmiBool VidyoAudioCapabilitySetSampleRate(VidyoAudioCapability* cap, LmiInt sampleRate);
LmiUint VidyoAudioCapabilityGetNumberOfChannels(const VidyoAudioCapability* cap);
LmiBool VidyoAudioCapabilitySetNumberOfChannels(VidyoAudioCapability* cap, LmiInt numberOfChannels);
LmiTime VidyoAudioCapabilityGetFrameInterval(const VidyoAudioCapability* cap);
LmiBool VidyoAudioCapabilitySetFrameInterval(VidyoAudioCapability* cap, LmiTime frameInterval);

LMI_END_EXTERN_C

#endif /* VIDYO_AUDIOCAPABILITY_H_ */
