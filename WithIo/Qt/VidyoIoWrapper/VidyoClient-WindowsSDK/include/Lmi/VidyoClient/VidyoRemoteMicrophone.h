/** 
{file:
	{name: VidyoRemoteMicrophone.h}
	{description: RemoteMicrophone device. }
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
#ifndef VIDYO_REMOTEMICROPHONE_H_ 
#define VIDYO_REMOTEMICROPHONE_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoRemoteMicrophoneImpl_;
typedef struct VidyoRemoteMicrophoneImpl_ VidyoRemoteMicrophoneImpl;
Declare_LmiSharedPtr(VidyoRemoteMicrophoneImpl)
Declare_LmiSharedPtrWrapper(VidyoRemoteMicrophone, VidyoRemoteMicrophoneImpl)
Declare_LmiWeakPtrWrapper(VidyoRemoteMicrophoneHandle, VidyoRemoteMicrophone, VidyoRemoteMicrophoneImpl)
Declare_LmiVector(VidyoRemoteMicrophone)
Declare_LmiList(VidyoRemoteMicrophone)

LMI_END_EXTERN_C

#include "VidyoLocalSpeaker.h"
#include "VidyoForwardDecl.h"
#include "VidyoDevice.h"
#include "VidyoParticipant.h"

LMI_BEGIN_EXTERN_C

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoRemoteMicrophone}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoRemoteMicrophone.h}
	{description: This object represents a microphone which belongs to the remote participant.}
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
	{member:
		{name: signalType}
		{type: VidyoDeviceAudioSignalType}
		{description: Signal Type.}
	}
}
*/

/**
{callback visibility="private":
	{name: VidyoRemoteMicrophoneCallback}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: void (*VidyoRemoteMicrophoneCallback)(const VidyoRemoteMicrophone* m, const VidyoLmiAudioFrame* audioFrame)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{parameter:
		{name: audioFrame}
		{description: }
	}
}
*/
typedef void (*VidyoRemoteMicrophoneCallback)(const VidyoRemoteMicrophone* m, const VidyoLmiAudioFrame* audioFrame);

/**
{type:
	{name: VidyoRemoteMicrophoneMode}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{value: {name: VIDYO_REMOTEMICROPHONEMODE_Dynamic} {description: }}
	{value: {name: VIDYO_REMOTEMICROPHONEMODE_Static} {description: }}
}
*/
typedef enum {
	VIDYO_REMOTEMICROPHONEMODE_Dynamic,
	VIDYO_REMOTEMICROPHONEMODE_Static
}
VidyoRemoteMicrophoneMode;

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneConstruct}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: VidyoRemoteMicrophone* VidyoRemoteMicrophoneConstruct(VidyoRemoteMicrophone* m, VidyoParticipant *p, VidyoLmiRemoteSource* remoteSource, LmiAllocator* alloc)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{parameter:
		{name: p}
		{description: }
	}
	{parameter:
		{name: remoteSource}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoRemoteMicrophone* VidyoRemoteMicrophoneConstruct(VidyoRemoteMicrophone* m, VidyoParticipant *p, VidyoLmiRemoteSource* remoteSource, LmiAllocator* alloc);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteMicrophoneConstructCopy}
	{parent: VidyoRemoteMicrophone}
	{description: Constructs an VidyoRemoteMicrophone object as a copy of another.}
	{prototype: VidyoRemoteMicrophone *VidyoRemoteMicrophoneConstructCopy(VidyoRemoteMicrophone *obj, const VidyoRemoteMicrophone *other)}
	{parameter: {name: obj} {description: The VidyoRemoteMicrophone object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoRemoteMicrophoneDestruct}
	{parent: VidyoRemoteMicrophone}
	{description: Destructs an VidyoRemoteMicrophone object.}
	{prototype: void VidyoRemoteMicrophoneDestruct(VidyoRemoteMicrophone *obj)}
	{parameter: {name: obj} {description: The VidyoRemoteMicrophone object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoRemoteMicrophoneAssign}
	{parent: VidyoRemoteMicrophone}
	{description: Assigns one VidyoRemoteMicrophone object the value of another. }
	{prototype: VidyoRemoteMicrophone *VidyoRemoteMicrophoneAssign(VidyoRemoteMicrophone *obj, const VidyoRemoteMicrophone *other)}
	{parameter: {name: obj} {description: The VidyoRemoteMicrophone object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoRemoteMicrophoneGetName}
	{parent: VidyoRemoteMicrophone}
	{description: Gets the name of the microphone.}
	{prototype: const LmiString* VidyoRemoteMicrophoneGetName(const VidyoRemoteMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{return: Name of the microphone.}
}
*/
const LmiString* VidyoRemoteMicrophoneGetName(const VidyoRemoteMicrophone* m);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteMicrophoneGetId}
	{parent: VidyoRemoteMicrophone}
	{description: Gets the unique ID of the microphone.}
	{prototype: const LmiString* VidyoRemoteMicrophoneGetId(const VidyoRemoteMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{return: Unique ID of the microphone.}
}
*/
const LmiString* VidyoRemoteMicrophoneGetId(const VidyoRemoteMicrophone* m);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoRemoteMicrophoneSetUserData}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: void VidyoRemoteMicrophoneSetUserData(VidyoRemoteMicrophone* m, LmiVoidPtr userData)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoRemoteMicrophoneSetUserData(VidyoRemoteMicrophone* m, LmiVoidPtr userData);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoRemoteMicrophoneGetUserData}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteMicrophoneGetUserData(const VidyoRemoteMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteMicrophoneGetUserData(const VidyoRemoteMicrophone* m);

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneSetCallback}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: void VidyoRemoteMicrophoneSetCallback(VidyoRemoteMicrophone* m, VidyoRemoteMicrophoneCallback callback)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoRemoteMicrophoneSetCallback(VidyoRemoteMicrophone* m, VidyoRemoteMicrophoneCallback callback);

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneGetParticipant}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: VidyoParticipant *VidyoRemoteMicrophoneGetParticipant(VidyoRemoteMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{return: }
}
*/
VidyoParticipant *VidyoRemoteMicrophoneGetParticipant(VidyoRemoteMicrophone *m);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteMicrophoneGetSignalType}
	{parent: VidyoRemoteMicrophone}
	{description: Gets signal type of the microphone, which affects how the audio is processed.}
	{prototype: VidyoDeviceAudioSignalType VidyoRemoteMicrophoneGetSignalType(const VidyoRemoteMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{return: The signal type of the microphone.}
}
*/
VidyoDeviceAudioSignalType VidyoRemoteMicrophoneGetSignalType(const VidyoRemoteMicrophone* m);

/**
{function:
	{name: VidyoRemoteMicrophoneAddToLocalSpeaker}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: LmiBool VidyoRemoteMicrophoneAddToLocalSpeaker(VidyoRemoteMicrophone* m, const VidyoLocalSpeaker* speaker, VidyoRemoteMicrophoneMode mode)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{parameter:
		{name: speaker}
		{description: }
	}
	{parameter:
		{name: mode}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRemoteMicrophoneAddToLocalSpeaker(VidyoRemoteMicrophone* m, const VidyoLocalSpeaker* speaker, VidyoRemoteMicrophoneMode mode);

/**
{function:
	{name: VidyoRemoteMicrophoneRemoveFromLocalSpeaker}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: LmiBool VidyoRemoteMicrophoneRemoveFromLocalSpeaker(VidyoRemoteMicrophone* m, const VidyoLocalSpeaker* speaker)}
	{parameter:
		{name: m}
		{description: The VidyoRemoteMicrophone object. }
	}
	{parameter:
		{name: speaker}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRemoteMicrophoneRemoveFromLocalSpeaker(VidyoRemoteMicrophone* m, const VidyoLocalSpeaker* speaker);

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneConstructFromDevice}
	{parent: VidyoRemoteMicrophone}
	{description: }
	{prototype: VidyoRemoteMicrophone *VidyoRemoteMicrophoneConstructFromDevice(VidyoRemoteMicrophone* vidyoRemoteMicrophone, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoRemoteMicrophone}
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
VidyoRemoteMicrophone *VidyoRemoteMicrophoneConstructFromDevice(VidyoRemoteMicrophone* vidyoRemoteMicrophone, VidyoDevice *device, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneGetStats}
	{parent: VidyoRemoteMicrophone}
	{description: Fill in data in VidyoRemoteMicrophoneStats from a remote microphone.}
	{prototype: LmiBool VidyoRemoteMicrophoneGetStats(VidyoRemoteMicrophone *microphone, VidyoRemoteMicrophoneStats *stats)}
	{parameter: {name: microphone} {description: The remote microphone object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoRemoteMicrophoneGetStats(VidyoRemoteMicrophone *microphone, VidyoRemoteMicrophoneStats *stats);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRemoteMicrophoneInline.h"
#endif

#endif /* VIDYO_REMOTEMICROPHONE_H_ */
