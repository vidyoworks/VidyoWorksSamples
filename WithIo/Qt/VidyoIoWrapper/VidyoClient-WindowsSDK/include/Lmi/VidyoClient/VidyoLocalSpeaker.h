/** 
{file:
	{name: VidyoLocalSpeaker.h}
	{description: Speaker device. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_LOCALSPEAKER_H_ 
#define VIDYO_LOCALSPEAKER_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoLocalSpeakerImpl_;
typedef struct VidyoLocalSpeakerImpl_ VidyoLocalSpeakerImpl;
Declare_LmiSharedPtr(VidyoLocalSpeakerImpl)
Declare_LmiSharedPtrWrapper(VidyoLocalSpeaker, VidyoLocalSpeakerImpl)
Declare_LmiWeakPtrWrapper(VidyoLocalSpeakerHandle, VidyoLocalSpeaker, VidyoLocalSpeakerImpl)
Declare_LmiVector(VidyoLocalSpeaker)
Declare_LmiList(VidyoLocalSpeaker)

struct VidyoLocalSpeakerStreamImpl_;
typedef struct VidyoLocalSpeakerStreamImpl_ VidyoLocalSpeakerStreamImpl;
Declare_LmiSharedPtr(VidyoLocalSpeakerStreamImpl)
Declare_LmiSharedPtrWrapper(VidyoLocalSpeakerStream, VidyoLocalSpeakerStreamImpl)
Declare_LmiWeakPtrWrapper(VidyoLocalSpeakerStreamHandle, VidyoLocalSpeakerStream, VidyoLocalSpeakerStreamImpl)

LMI_END_EXTERN_C

#include "VidyoAudioCapability.h"
#include "VidyoForwardDecl.h"
#include "VidyoEndpoint.h"
#include "VidyoStatistics.h"
#include "VidyoDevice.h"
#include "VidyoParticipant.h"

LMI_BEGIN_EXTERN_C


/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoLocalSpeaker}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoLocalSpeaker.h}
	{description: This object represents a speaker on the local endpoint.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique ID.}
	}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
}
*/

/**
{type apigroup="connector simple" visibility="private":
	{name: VidyoLocalSpeakerHandle}
	{parent: VidyoLocalSpeaker}
	{description: }
}
*/

/**
{callback visibility="private":
	{name: VidyoLocalSpeakerCallback}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void (*VidyoLocalSpeakerCallback)(const VidyoLocalSpeaker* s, const VidyoLmiAudioFrame* audioFrame)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: audioFrame}
		{description: }
	}
}
*/
typedef void (*VidyoLocalSpeakerCallback)(const VidyoLocalSpeaker* s, const VidyoLmiAudioFrame* audioFrame);

/**
{callback visibility="private":
	{name: VidyoLocalSpeakerStartCallback}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void (*VidyoLocalSpeakerStartCallback)(const VidyoLocalSpeaker* s, LmiUint sampleRate, LmiUint numberOfChannels, const LmiMediaFormat *mediaFormat, LmiTime frameInterval, LmiVoidPtr userData)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: sampleRate}
		{description: }
	}
	{parameter:
		{name: numberOfChannels}
		{description: }
	}
	{parameter:
		{name: mediaFormat}
		{description: }
	}
	{parameter:
		{name: frameInterval}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalSpeakerStartCallback)(const VidyoLocalSpeaker* s, LmiUint sampleRate, LmiUint numberOfChannels, const LmiMediaFormat *mediaFormat, LmiTime frameInterval, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalSpeakerStopCallback}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void (*VidyoLocalSpeakerStopCallback)(const VidyoLocalSpeaker* s, LmiVoidPtr userData)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalSpeakerStopCallback)(const VidyoLocalSpeaker* s, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalSpeakerStreamAddedCallback}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: LmiVoidPtr (*VidyoLocalSpeakerStreamAddedCallback)(const VidyoLocalSpeaker* s, const VidyoParticipant *participant, const VidyoDevice *device, LmiVoidPtr userData)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: participant}
		{description: }
	}
	{parameter:
		{name: device}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
	{return: streamUserData}
}
*/
typedef LmiVoidPtr (*VidyoLocalSpeakerStreamAddedCallback)(const VidyoLocalSpeaker* s, const VidyoParticipant *participant, const VidyoDevice *device, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalSpeakerStreamRemovedCallback}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void (*VidyoLocalSpeakerStreamRemovedCallback)(const VidyoLocalSpeaker* s, const VidyoParticipant *participant, const VidyoDevice *device, LmiVoidPtr userData, LmiVoidPtr streamUserData)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: participant}
		{description: }
	}
	{parameter:
		{name: device}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
	{parameter:
		{name: streamUserData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalSpeakerStreamRemovedCallback)(const VidyoLocalSpeaker* s, const VidyoParticipant *participant, const VidyoDevice *device, LmiVoidPtr userData, LmiVoidPtr streamUserData);

/**
{callback visibility="private":
	{name: VidyoLocalSpeakerStreamAddAudioFrameCallback}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void (*VidyoLocalSpeakerStreamAddAudioFrameCallback)(const VidyoLocalSpeaker* s, const VidyoParticipant *participant, const VidyoDevice *device, LmiVoidPtr userData, LmiVoidPtr streamUserData, const VidyoLmiAudioFrame *audioFrame)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: participant}
		{description: }
	}
	{parameter:
		{name: device}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
	{parameter:
		{name: streamUserData}
		{description: }
	}
	{parameter:
		{name: audioFrame}
		{description: }
	}
}
*/
typedef void (*VidyoLocalSpeakerStreamAddAudioFrameCallback)(const VidyoLocalSpeaker* s, const VidyoParticipant *participant, const VidyoDevice *device, LmiVoidPtr userData, LmiVoidPtr streamUserData, const VidyoLmiAudioFrame *audioFrame);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerConstruct}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: VidyoLocalSpeaker* VidyoLocalSpeakerConstruct(VidyoLocalSpeaker* s, VidyoEndpoint *endpoint, VidyoLmiAudioPlaybackDevice* playbackDevice, LmiAllocator* alloc)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: playbackDevice}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalSpeaker* VidyoLocalSpeakerConstruct(VidyoLocalSpeaker* s, VidyoEndpoint *endpoint, VidyoLmiAudioPlaybackDevice* playbackDevice, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerConstructVirtual}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: VidyoLocalSpeaker *VidyoLocalSpeakerConstructVirtual(VidyoLocalSpeaker *s, VidyoEndpoint *endpoint, LmiString *id, LmiString *name, VidyoLocalSpeakerStartCallback onStart, VidyoLocalSpeakerStopCallback onStop, VidyoLocalSpeakerStreamAddedCallback onStreamAdded, VidyoLocalSpeakerStreamRemovedCallback onStreamRemoved, VidyoLocalSpeakerStreamAddAudioFrameCallback onStreamAddAudioFrame, LmiVoidPtr virtualUserData, LmiAllocator *alloc)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: id}
		{description: }
	}
	{parameter:
		{name: name}
		{description: }
	}
	{parameter:
		{name: onStart}
		{description: }
	}
	{parameter:
		{name: onStop}
		{description: }
	}
	{parameter:
		{name: onStreamAdded}
		{description: }
	}
	{parameter:
		{name: onStreamRemoved}
		{description: }
	}
	{parameter:
		{name: onStreamAddAudioFrame}
		{description: }
	}
	{parameter:
		{name: virtualUserData}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalSpeaker *VidyoLocalSpeakerConstructVirtual(VidyoLocalSpeaker *s, VidyoEndpoint *endpoint, LmiString *id, LmiString *name, VidyoLocalSpeakerStartCallback onStart, VidyoLocalSpeakerStopCallback onStop, VidyoLocalSpeakerStreamAddedCallback onStreamAdded, VidyoLocalSpeakerStreamRemovedCallback onStreamRemoved, VidyoLocalSpeakerStreamAddAudioFrameCallback onStreamAddAudioFrame, LmiVoidPtr virtualUserData, LmiAllocator *alloc);

/**
{function apigroup="connector simple":
	{name: VidyoLocalSpeakerConstructCopy}
	{parent: VidyoLocalSpeaker}
	{description: Constructs an VidyoLocalSpeaker object as a copy of another.}
	{prototype: VidyoLocalSpeaker *VidyoLocalSpeakerConstructCopy(VidyoLocalSpeaker *obj, const VidyoLocalSpeaker *other)}
	{parameter: {name: obj} {description: The VidyoLocalSpeaker object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoLocalSpeakerDestruct}
	{parent: VidyoLocalSpeaker}
	{description: Destructs an VidyoLocalSpeaker object.}
	{prototype: void VidyoLocalSpeakerDestruct(VidyoLocalSpeaker *obj)}
	{parameter: {name: obj} {description: The VidyoLocalSpeaker object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalSpeakerAssign}
	{parent: VidyoLocalSpeaker}
	{description: Assigns one VidyoLocalSpeaker object the value of another. }
	{prototype: VidyoLocalSpeaker *VidyoLocalSpeakerAssign(VidyoLocalSpeaker *obj, const VidyoLocalSpeaker *other)}
	{parameter: {name: obj} {description: The VidyoLocalSpeaker object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalSpeakerGetHandle}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: VidyoLocalSpeakerHandle* VidyoLocalSpeakerGetHandle(VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{return: }
}
*/
VidyoLocalSpeakerHandle* VidyoLocalSpeakerGetHandle(VidyoLocalSpeaker* s);

/**
{function apigroup="connector simple":
	{name: VidyoLocalSpeakerGetName}
	{parent: VidyoLocalSpeaker}
	{description: Gets the name of the speaker.}
	{prototype: const LmiString* VidyoLocalSpeakerGetName(const VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{return: Name of the speaker. }
}
*/
const LmiString* VidyoLocalSpeakerGetName(const VidyoLocalSpeaker* s);

/**
{function apigroup="connector simple":
	{name: VidyoLocalSpeakerGetId}
	{parent: VidyoLocalSpeaker}
	{description: Gets the unique ID of the speaker.}
	{prototype: const LmiString* VidyoLocalSpeakerGetId(const VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{return: Unique ID of the speaker.}
}
*/
const LmiString* VidyoLocalSpeakerGetId(const VidyoLocalSpeaker* s);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalSpeakerSetUserData}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void VidyoLocalSpeakerSetUserData(VidyoLocalSpeaker* s, LmiVoidPtr userData)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoLocalSpeakerSetUserData(VidyoLocalSpeaker* s, LmiVoidPtr userData);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalSpeakerGetUserData}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalSpeakerGetUserData(const VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalSpeakerGetUserData(const VidyoLocalSpeaker* s);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerSetCallback}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void VidyoLocalSpeakerSetCallback(VidyoLocalSpeaker* s, VidyoLocalSpeakerCallback callback)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoLocalSpeakerSetCallback(VidyoLocalSpeaker* s, VidyoLocalSpeakerCallback callback);

/**
{function:
	{name: VidyoLocalSpeakerIsPaused}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: LmiBool VidyoLocalSpeakerIsPaused(const VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{return: }
}
*/
LmiBool VidyoLocalSpeakerIsPaused(const VidyoLocalSpeaker* s);

/**
{function:
	{name: VidyoLocalSpeakerPause}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void VidyoLocalSpeakerPause(VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
}
*/
void VidyoLocalSpeakerPause(VidyoLocalSpeaker* s);

/**
{function:
	{name: VidyoLocalSpeakerResume}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void VidyoLocalSpeakerResume(VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
}
*/
void VidyoLocalSpeakerResume(VidyoLocalSpeaker* s);

/**
{function:
	{name: VidyoLocalSpeakerPlayTone}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void VidyoLocalSpeakerPlayTone(VidyoLocalSpeaker* s, char dtmfTone)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: dtmfTone}
		{description: }
	}
}
*/
void VidyoLocalSpeakerPlayTone(VidyoLocalSpeaker* s, char dtmfTone);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerPlaySound}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: LmiBool VidyoLocalSpeakerPlaySound(VidyoLocalSpeaker* s, VidyoLmiAudioFrame* sound, LmiBool loop)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: sound}
		{description: }
	}
	{parameter:
		{name: loop}
		{description: }
	}
    {return: LMI_TRUE is played successfully, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoLocalSpeakerPlaySound(VidyoLocalSpeaker* s, VidyoLmiAudioFrame* sound, LmiBool loop);

/**
{function:
	{name: VidyoLocalSpeakerStopSound}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void VidyoLocalSpeakerStopSound(VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
}
*/
void VidyoLocalSpeakerStopSound(VidyoLocalSpeaker* s);

/**
{function:
	{name: VidyoLocalSpeakerGetVolume}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: LmiUint VidyoLocalSpeakerGetVolume(VidyoLocalSpeaker* s)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{return: }
}
*/
LmiUint VidyoLocalSpeakerGetVolume(VidyoLocalSpeaker* s);

/**
{function:
	{name: VidyoLocalSpeakerSetVolume}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: void VidyoLocalSpeakerSetVolume(VidyoLocalSpeaker* s, LmiUint volumePercent)}
	{parameter:
		{name: s}
		{description: The VidyoLocalSpeaker object. }
	}
	{parameter:
		{name: volumePercent}
		{description: }
	}
}
*/
void VidyoLocalSpeakerSetVolume(VidyoLocalSpeaker* s, LmiUint volumePercent);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerConstructFromDevice}
	{parent: VidyoLocalSpeaker}
	{description: }
	{prototype: VidyoLocalSpeaker *VidyoLocalSpeakerConstructFromDevice(VidyoLocalSpeaker* vidyoLocalSpeaker, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoLocalSpeaker}
		{description: }
	}
	{parameter:
		{name: device}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalSpeaker *VidyoLocalSpeakerConstructFromDevice(VidyoLocalSpeaker* vidyoLocalSpeaker, VidyoDevice *device, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerGetStats}
	{parent: VidyoLocalSpeaker}
	{description: Fill in data in VidyoLocalSpeakerStats from a local speaker.}
	{prototype: LmiBool VidyoLocalSpeakerGetStats(VidyoLocalSpeaker *speaker, VidyoLocalSpeakerStats *stats)}
	{parameter: {name: speaker} {description: The local speaker object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoLocalSpeakerGetStats(VidyoLocalSpeaker *speaker, VidyoLocalSpeakerStats *stats);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoLocalSpeakerInline.h"
#endif

#endif /* VIDYO_LOCALSPEAKER_H_ */
