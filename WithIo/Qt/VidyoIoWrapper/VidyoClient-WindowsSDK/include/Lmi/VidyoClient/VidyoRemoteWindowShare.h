/** 
{file:
	{name: VidyoRemoteWindowShare.h}
	{description: RemoteWindow available for viewing. }
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
#ifndef VIDYO_REMOTEWINDOWSHARE_H_ 
#define VIDYO_REMOTEWINDOWSHARE_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoRemoteWindowShareImpl_;
typedef struct VidyoRemoteWindowShareImpl_ VidyoRemoteWindowShareImpl;
Declare_LmiSharedPtr(VidyoRemoteWindowShareImpl)
Declare_LmiSharedPtrWrapper(VidyoRemoteWindowShare, VidyoRemoteWindowShareImpl)
Declare_LmiWeakPtrWrapper(VidyoRemoteWindowShareHandle, VidyoRemoteWindowShare, VidyoRemoteWindowShareImpl)
Declare_LmiVector(VidyoRemoteWindowShare)
Declare_LmiList(VidyoRemoteWindowShare)

LMI_END_EXTERN_C

#include "VidyoLocalRenderer.h"
#include "VidyoForwardDecl.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoRemoteWindowShare}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoRemoteWindowShare.h}
	{description: This object represents a window share which belongs to the remote participant.}
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
{callback visibility="private":
	{name: VidyoRemoteWindowShareCallback}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: void (*VidyoRemoteWindowShareCallback)(const VidyoRemoteWindowShare* w, const VidyoLmiVideoFrame* videoFrame)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{parameter:
		{name: videoFrame}
		{description: }
	}
}
*/
typedef void (*VidyoRemoteWindowShareCallback)(const VidyoRemoteWindowShare* w, const VidyoLmiVideoFrame* videoFrame);

/**
{function visibility="private":
	{name: VidyoRemoteWindowShareConstruct}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: VidyoRemoteWindowShare* VidyoRemoteWindowShareConstruct(VidyoRemoteWindowShare* w, VidyoLmiRemoteSource* remoteSource, VidyoParticipant *participant, LmiAllocator* alloc)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{parameter:
		{name: remoteSource}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoRemoteWindowShare *VidyoRemoteWindowShareConstruct(VidyoRemoteWindowShare *w, VidyoLmiRemoteSource *remoteSource, VidyoParticipant *participant, LmiAllocator *alloc);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteWindowShareConstructCopy}
	{parent: VidyoRemoteWindowShare}
	{description: Constructs an VidyoRemoteWindowShare object as a copy of another.}
	{prototype: VidyoRemoteWindowShare *VidyoRemoteWindowShareConstructCopy(VidyoRemoteWindowShare *obj, const VidyoRemoteWindowShare *other)}
	{parameter: {name: obj} {description: The VidyoRemoteWindowShare object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoRemoteWindowShareDestruct}
	{parent: VidyoRemoteWindowShare}
	{description: Destructs an VidyoRemoteWindowShare object.}
	{prototype: void VidyoRemoteWindowShareDestruct(VidyoRemoteWindowShare *obj)}
	{parameter: {name: obj} {description: The VidyoRemoteWindowShare object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoRemoteWindowShareAssign}
	{parent: VidyoRemoteWindowShare}
	{description: Assigns one VidyoRemoteWindowShare object the value of another. }
	{prototype: VidyoRemoteWindowShare *VidyoRemoteWindowShareAssign(VidyoRemoteWindowShare *obj, const VidyoRemoteWindowShare *other)}
	{parameter: {name: obj} {description: The VidyoRemoteWindowShare object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoRemoteWindowShareGetName}
	{parent: VidyoRemoteWindowShare}
	{description: Gets the name of the window share.}
	{prototype: const LmiString* VidyoRemoteWindowShareGetName(const VidyoRemoteWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{return: Name of the window share.}
}
*/
const LmiString* VidyoRemoteWindowShareGetName(const VidyoRemoteWindowShare* w);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteWindowShareGetId}
	{parent: VidyoRemoteWindowShare}
	{description: Gets the unique ID of the window share.}
	{prototype: const LmiString* VidyoRemoteWindowShareGetId(const VidyoRemoteWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{return: Unique ID of the window share.}
}
*/
const LmiString* VidyoRemoteWindowShareGetId(const VidyoRemoteWindowShare* w);

/**
{function visibility="private":
	{name: VidyoRemoteWindowShareSetUserData}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: void VidyoRemoteWindowShareSetUserData(VidyoRemoteWindowShare* w, LmiVoidPtr userData)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoRemoteWindowShareSetUserData(VidyoRemoteWindowShare* w, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoRemoteWindowShareGetUserData}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteWindowShareGetUserData(const VidyoRemoteWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteWindowShareGetUserData(const VidyoRemoteWindowShare* w);

/**
{function visibility="private":
	{name: VidyoRemoteWindowShareSetCallback}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: void VidyoRemoteWindowShareSetCallback(VidyoRemoteWindowShare* w, VidyoRemoteWindowShareCallback callback)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoRemoteWindowShareSetCallback(VidyoRemoteWindowShare* w, VidyoRemoteWindowShareCallback callback);

/**
{function visibility="private":
	{name: VidyoRemoteWindowShareGetParticipant}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: VidyoParticipant *VidyoRemoteWindowShareGetParticipant(VidyoRemoteWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{return: }
}
*/
VidyoParticipant *VidyoRemoteWindowShareGetParticipant(VidyoRemoteWindowShare *w);

/**
{function:
	{name: VidyoRemoteWindowShareAddToLocalRenderer}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteWindowShareAddToLocalRenderer(VidyoRemoteWindowShare* w, const VidyoLocalRenderer* renderer)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{parameter:
		{name: renderer}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteWindowShareAddToLocalRenderer(VidyoRemoteWindowShare* w, const VidyoLocalRenderer* renderer);

/**
{function:
	{name: VidyoRemoteWindowShareRemoveFromLocalRenderer}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: LmiBool VidyoRemoteWindowShareRemoveFromLocalRenderer(VidyoRemoteWindowShare* w, const VidyoLocalRenderer* renderer)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{parameter:
		{name: renderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRemoteWindowShareRemoveFromLocalRenderer(VidyoRemoteWindowShare* w, const VidyoLocalRenderer* renderer);

/**
{function:
	{name: VidyoRemoteWindowShareSetPositionInLocalRenderer}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: LmiBool VidyoRemoteWindowShareSetPositionInLocalRenderer(VidyoRemoteWindowShare *w, const VidyoLocalRenderer *localRenderer, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval)}
	{parameter:
		{name: w}
		{description: The VidyoRemoteWindowShare object. }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
	{parameter:
		{name: x}
		{description: }
	}
	{parameter:
		{name: y}
		{description: }
	}
	{parameter:
		{name: width}
		{description: }
	}
	{parameter:
		{name: height}
		{description: }
	}
	{parameter:
		{name: frameInterval}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRemoteWindowShareSetPositionInLocalRenderer(VidyoRemoteWindowShare *w, const VidyoLocalRenderer *localRenderer, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval);

/**
{function visibility="private":
	{name: VidyoRemoteWindowShareConstructFromDevice}
	{parent: VidyoRemoteWindowShare}
	{description: }
	{prototype: VidyoRemoteWindowShare *VidyoRemoteWindowShareConstructFromDevice(VidyoRemoteWindowShare* vidyoRemoteWindowShare, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoRemoteWindowShare}
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
VidyoRemoteWindowShare *VidyoRemoteWindowShareConstructFromDevice(VidyoRemoteWindowShare* vidyoRemoteWindowShare, VidyoDevice *device, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoRemoteWindowShareGetStats}
	{parent: VidyoRemoteWindowShare}
	{description: Fill in stats data in VidyoRemoteVideoSourceStats from a remote window share.}
	{prototype: LmiBool VidyoRemoteWindowShareGetStats(VidyoRemoteWindowShare *windowShare, VidyoRemoteVideoSourceStats *stats)}
	{parameter: {name: windowShare} {description: The remote window share object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoRemoteWindowShareGetStats(VidyoRemoteWindowShare *windowShare, VidyoRemoteVideoSourceStats *stats);

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRemoteWindowShareInline.h"
#endif

LMI_END_EXTERN_C

#endif /* VIDYO_REMOTEWINDOWSHARE_H_ */
