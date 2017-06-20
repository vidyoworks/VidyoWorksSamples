/** 
{file:
	{name: VidyoRemoteRenderer.h}
	{description: RemoteRenderer to which local Sources can be sent. }
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
#ifndef VIDYO_REMOTERENDERER_H_ 
#define VIDYO_REMOTERENDERER_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

#define VIDYOCLIENT_DEFAULTSVC_NumLayers			( 2 )
#define VIDYOCLIENT_FRAMERATE_BUFFER				( 2500000 )

struct VidyoRemoteRendererImpl_;
typedef struct VidyoRemoteRendererImpl_ VidyoRemoteRendererImpl;
Declare_LmiSharedPtr(VidyoRemoteRendererImpl)
Declare_LmiSharedPtrWrapper(VidyoRemoteRenderer, VidyoRemoteRendererImpl)
Declare_LmiWeakPtrWrapper(VidyoRemoteRendererHandle, VidyoRemoteRenderer, VidyoRemoteRendererImpl)
Declare_LmiVector(VidyoRemoteRenderer)
Declare_LmiList(VidyoRemoteRenderer)

struct VidyoRemoteRendererStreamImpl_;
typedef struct VidyoRemoteRendererStreamImpl_ VidyoRemoteRendererStreamImpl;
Declare_LmiSharedPtr(VidyoRemoteRendererStreamImpl)
Declare_LmiSharedPtrWrapper(VidyoRemoteRendererStream, VidyoRemoteRendererStreamImpl)
Declare_LmiWeakPtrWrapper(VidyoRemoteRendererStreamHandle, VidyoRemoteRendererStream, VidyoRemoteRendererStreamImpl)
Declare_LmiList(VidyoRemoteRendererStream)

LMI_END_EXTERN_C

#include "VidyoStatistics.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C

/**
{type reference-counted="yes":
	{name: VidyoRemoteRenderer}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoRemoteRenderer.h}
	{description: }
	{member:
		{name: id}
		{type: LmiString}
		{description: }
	}
	{member:
		{name: name}
		{type: LmiString}
		{description: }
	}
}
*/

/**
{type visibility="private":
	{name: VidyoRemoteRendererHandle}
	{parent: VidyoRemoteRenderer}
	{description: }
}
*/

/**
{function:
	{name: VidyoRemoteRendererConstructCopy}
	{parent: VidyoRemoteRenderer}
	{description: Constructs an VidyoRemoteRenderer object as a copy of another.}
	{prototype: VidyoRemoteRenderer *VidyoRemoteRendererConstructCopy(VidyoRemoteRenderer *obj, const VidyoRemoteRenderer *other)}
	{parameter: {name: obj} {description: The VidyoRemoteRenderer object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoRemoteRendererDestruct}
	{parent: VidyoRemoteRenderer}
	{description: Destructs an VidyoRemoteRenderer object.}
	{prototype: void VidyoRemoteRendererDestruct(VidyoRemoteRenderer *obj)}
	{parameter: {name: obj} {description: The VidyoRemoteRenderer object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoRemoteRendererAssign}
	{parent: VidyoRemoteRenderer}
	{description: Assigns one VidyoRemoteRenderer object the value of another. }
	{prototype: VidyoRemoteRenderer *VidyoRemoteRendererAssign(VidyoRemoteRenderer *obj, const VidyoRemoteRenderer *other)}
	{parameter: {name: obj} {description: The VidyoRemoteRenderer object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoRemoteRendererGetHandle}
	{parent: VidyoRemoteRenderer}
	{description: }
	{prototype: VidyoRemoteRendererHandle* VidyoRemoteRendererGetHandle(VidyoRemoteRenderer* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
VidyoRemoteRendererHandle* VidyoRemoteRendererGetHandle(VidyoRemoteRenderer* r);

/**
{function visibility="private":
	{name: VidyoRemoteRendererSetUserData}
	{parent: VidyoRemoteRenderer}
	{description: }
	{prototype: void VidyoRemoteRendererSetUserData(VidyoRemoteRenderer* r, LmiVoidPtr userData)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoRemoteRendererSetUserData(VidyoRemoteRenderer* r, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoRemoteRendererGetUserData}
	{parent: VidyoRemoteRenderer}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteRendererGetUserData(const VidyoRemoteRenderer* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteRendererGetUserData(const VidyoRemoteRenderer* r);

/**
{function:
	{name: VidyoRemoteRendererGetId}
	{parent: VidyoRemoteRenderer}
	{description: }
	{prototype: const LmiString* VidyoRemoteRendererGetId(const VidyoRemoteRenderer* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
const LmiString* VidyoRemoteRendererGetId(const VidyoRemoteRenderer* r);

/**
{function:
	{name: VidyoRemoteRendererGetName}
	{parent: VidyoRemoteRenderer}
	{description: }
	{prototype: const LmiString* VidyoRemoteRendererGetName(const VidyoRemoteRenderer* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
const LmiString* VidyoRemoteRendererGetName(const VidyoRemoteRenderer* r);

/**
{function visibility="private":
	{name: VidyoRemoteRendererConstructFromDevice}
	{parent: VidyoRemoteRenderer}
	{description: }
	{prototype: VidyoRemoteRenderer *VidyoRemoteRendererConstructFromDevice(VidyoRemoteRenderer* vidyoRemoteRenderer, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoRemoteRenderer}
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
VidyoRemoteRenderer *VidyoRemoteRendererConstructFromDevice(VidyoRemoteRenderer* vidyoRemoteRenderer, VidyoDevice *device, LmiAllocator* alloc);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRemoteRendererInline.h"
#endif

#endif /* VIDYO_REMOTERENDERER_H_ */
