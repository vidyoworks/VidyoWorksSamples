/** 
{file:
	{name: VidyoRemoteSpeaker.h}
	{description: RemoteSpeaker to which local Sources can be sent. }
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
#ifndef VIDYO_REMOTESPEAKER_H_ 
#define VIDYO_REMOTESPEAKER_H_ 

#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiMisc.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiMallocAllocator.h>
#include <Lmi/Os/LmiOs.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoRemoteSpeakerImpl_;
typedef struct VidyoRemoteSpeakerImpl_ VidyoRemoteSpeakerImpl;
Declare_LmiSharedPtr(VidyoRemoteSpeakerImpl)
Declare_LmiSharedPtrWrapper(VidyoRemoteSpeaker, VidyoRemoteSpeakerImpl)
Declare_LmiWeakPtrWrapper(VidyoRemoteSpeakerHandle, VidyoRemoteSpeaker, VidyoRemoteSpeakerImpl)
Declare_LmiVector(VidyoRemoteSpeaker)
Declare_LmiList(VidyoRemoteSpeaker)

struct VidyoRemoteSpeakerStreamImpl_;
typedef struct VidyoRemoteSpeakerStreamImpl_ VidyoRemoteSpeakerStreamImpl;
Declare_LmiSharedPtr(VidyoRemoteSpeakerStreamImpl)
Declare_LmiSharedPtrWrapper(VidyoRemoteSpeakerStream, VidyoRemoteSpeakerStreamImpl)
Declare_LmiWeakPtrWrapper(VidyoRemoteSpeakerStreamHandle, VidyoRemoteSpeakerStream, VidyoRemoteSpeakerStreamImpl)
Declare_LmiList(VidyoRemoteSpeakerStream)

LMI_END_EXTERN_C

#include "VidyoStatistics.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C

/**
{type reference-counted="yes":
	{name: VidyoRemoteSpeaker}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoRemoteSpeaker.h}
	{description: }
}
*/

/**
{type visibility="private":
	{name: VidyoRemoteSpeakerHandle}
	{parent: VidyoRemoteSpeaker}
	{description: }
}
*/

/**
{function:
	{name: VidyoRemoteSpeakerConstructCopy}
	{parent: VidyoRemoteSpeaker}
	{description: Constructs an VidyoRemoteSpeaker object as a copy of another.}
	{prototype: VidyoRemoteSpeaker *VidyoRemoteSpeakerConstructCopy(VidyoRemoteSpeaker *obj, const VidyoRemoteSpeaker *other)}
	{parameter: {name: obj} {description: The VidyoRemoteSpeaker object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoRemoteSpeakerDestruct}
	{parent: VidyoRemoteSpeaker}
	{description: Destructs an VidyoRemoteSpeaker object.}
	{prototype: void VidyoRemoteSpeakerDestruct(VidyoRemoteSpeaker *obj)}
	{parameter: {name: obj} {description: The VidyoRemoteSpeaker object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerAssign}
	{parent: VidyoRemoteSpeaker}
	{description: Assigns one VidyoRemoteSpeaker object the value of another. }
	{prototype: VidyoRemoteSpeaker *VidyoRemoteSpeakerAssign(VidyoRemoteSpeaker *obj, const VidyoRemoteSpeaker *other)}
	{parameter: {name: obj} {description: The VidyoRemoteSpeaker object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerGetHandle}
	{parent: VidyoRemoteSpeaker}
	{description: }
	{prototype: VidyoRemoteSpeakerHandle* VidyoRemoteSpeakerGetHandle(VidyoRemoteSpeaker* s)}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
VidyoRemoteSpeakerHandle* VidyoRemoteSpeakerGetHandle(VidyoRemoteSpeaker* s);

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerSetUserData}
	{parent: VidyoRemoteSpeaker}
	{description: }
	{prototype: void VidyoRemoteSpeakerSetUserData(VidyoRemoteSpeaker* s, LmiVoidPtr userData)}
	{parameter:
		{name: s}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoRemoteSpeakerSetUserData(VidyoRemoteSpeaker* s, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerGetUserData}
	{parent: VidyoRemoteSpeaker}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteSpeakerGetUserData(const VidyoRemoteSpeaker* s)}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteSpeakerGetUserData(const VidyoRemoteSpeaker* s);

/**
{function:
	{name: VidyoRemoteSpeakerGetId}
	{parent: VidyoRemoteSpeaker}
	{description: }
	{prototype: const LmiString* VidyoRemoteSpeakerGetId(const VidyoRemoteSpeaker* s)}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
const LmiString *VidyoRemoteSpeakerGetId(const VidyoRemoteSpeaker *s);

/**
{function:
	{name: VidyoRemoteSpeakerGetName}
	{parent: VidyoRemoteSpeaker}
	{description: }
	{prototype: const LmiString* VidyoRemoteSpeakerGetName(const VidyoRemoteSpeaker* s)}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
const LmiString* VidyoRemoteSpeakerGetName(const VidyoRemoteSpeaker* s);

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerConstructFromDevice}
	{parent: VidyoRemoteSpeaker}
	{description: }
	{prototype: VidyoRemoteSpeaker *VidyoRemoteSpeakerConstructFromDevice(VidyoRemoteSpeaker* vidyoRemoteSpeaker, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoRemoteSpeaker}
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
VidyoRemoteSpeaker *VidyoRemoteSpeakerConstructFromDevice(VidyoRemoteSpeaker* vidyoRemoteSpeaker, VidyoDevice *device, LmiAllocator* alloc);

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRemoteSpeakerInline.h"
#endif

LMI_END_EXTERN_C

#endif /* VIDYO_REMOTESPEAKER_H_ */
