/** 
{file:
	{name: VidyoVirtualShareManager.h}
	{description: Window available for sharing. }
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
#ifndef VIDYO_VIRTUALSHAREMANAGER_H_ 
#define VIDYO_VIRTUALSHAREMANAGER_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoVirtualShareManagerImpl_;
typedef struct VidyoVirtualShareManagerImpl_ VidyoVirtualShareManagerImpl;
Declare_LmiSharedPtr(VidyoVirtualShareManagerImpl)
Declare_LmiSharedPtrWrapper(VidyoVirtualShareManager, VidyoVirtualShareManagerImpl)
Declare_LmiWeakPtrWrapper(VidyoVirtualShareManagerHandle, VidyoVirtualShareManager, VidyoVirtualShareManagerImpl)
Declare_LmiVector(VidyoVirtualShareManager)
Declare_LmiList(VidyoVirtualShareManager)

LMI_END_EXTERN_C

#include "VidyoLocalWindowShare.h"
#include "VidyoLocalMonitor.h"

#include "VidyoForwardDecl.h"
#include "VidyoEndpoint.h"

LMI_BEGIN_EXTERN_C

/**
{type reference-counted="yes":
	{name: VidyoVirtualShareManager}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoVirtualShareManager.h}
	{description: }
}
*/

/**
{type visibility="private":
	{name: VidyoVirtualShareManagerHandle}
	{parent: VidyoVirtualShareManager}
	{description: }
}
*/

/**
{callback visibility="private":
	{name: VidyoVirtualShareManagerStartCallback}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: LmiBool (*VidyoVirtualShareManagerStartCallback)(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
typedef LmiBool (*VidyoVirtualShareManagerStartCallback)(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint);

/**
{callback visibility="private":
	{name: VidyoVirtualShareManagerStopCallback}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: void (*VidyoVirtualShareManagerStopCallback)(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
}
*/
typedef void (*VidyoVirtualShareManagerStopCallback)(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint);

/**
{callback visibility="private":
	{name: VidyoVirtualShareManagerMediaStateCallback}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: void (*VidyoVirtualShareManagerMediaStateCallback)(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint, VidyoEndpointMediaState state)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void (*VidyoVirtualShareManagerMediaStateCallback)(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint, VidyoEndpointMediaState state);

/**
{function visibility="private":
	{name: VidyoVirtualShareManagerConstruct}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: VidyoVirtualShareManager* VidyoVirtualShareManagerConstruct(VidyoVirtualShareManager* m, VidyoVirtualShareManagerStartCallback onStart, VidyoVirtualShareManagerStopCallback onStop, VidyoVirtualShareManagerMediaStateCallback onMediaState, LmiAllocator* alloc)}
	{parameter:
		{name: m}
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
		{name: onMediaState}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoVirtualShareManager* VidyoVirtualShareManagerConstruct(VidyoVirtualShareManager* m, VidyoVirtualShareManagerStartCallback onStart, VidyoVirtualShareManagerStopCallback onStop, VidyoVirtualShareManagerMediaStateCallback onMediaState, LmiAllocator* alloc);

/**
{function:
	{name: VidyoVirtualShareManagerConstructCopy}
	{parent: VidyoVirtualShareManager}
	{description: Constructs an VidyoVirtualShareManager object as a copy of another.}
	{prototype: VidyoVirtualShareManager* VidyoVirtualShareManagerConstructCopy(VidyoVirtualShareManager* obj, const VidyoVirtualShareManager* other)}
	{parameter: {name: obj} {description: The VidyoVirtualShareManager object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoVirtualShareManagerDestruct}
	{parent: VidyoVirtualShareManager}
	{description: Destructs an VidyoVirtualShareManager object.}
	{prototype: void VidyoVirtualShareManagerDestruct(VidyoVirtualShareManager* obj)}
	{parameter: {name: obj} {description: The VidyoVirtualShareManager object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoVirtualShareManagerAssign}
	{parent: VidyoVirtualShareManager}
	{description: Assigns one VidyoVirtualShareManager object the value of another. }
	{prototype: VidyoVirtualShareManager* VidyoVirtualShareManagerAssign(VidyoVirtualShareManager* obj, const VidyoVirtualShareManager* other)}
	{parameter: {name: obj} {description: The VidyoVirtualShareManager object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoVirtualShareManagerGetHandle}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: VidyoVirtualShareManagerHandle* VidyoVirtualShareManagerGetHandle(VidyoVirtualShareManager* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
VidyoVirtualShareManagerHandle* VidyoVirtualShareManagerGetHandle(VidyoVirtualShareManager* m);

/**
{function visibility="private":
	{name: VidyoVirtualShareManagerSetUserData}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: void VidyoVirtualShareManagerSetUserData(VidyoVirtualShareManager* m, LmiVoidPtr userData)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoVirtualShareManagerSetUserData(VidyoVirtualShareManager* m, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoVirtualShareManagerGetUserData}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: LmiVoidPtr VidyoVirtualShareManagerGetUserData(const VidyoVirtualShareManager* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoVirtualShareManagerGetUserData(const VidyoVirtualShareManager* m);

/**
{function:
	{name: VidyoVirtualShareManagerLocalWindowShareEvent}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: LmiBool VidyoVirtualShareManagerLocalWindowShareEvent(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint, const VidyoLocalWindowShare* windowShare, VidyoDeviceState state)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: windowShare}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoVirtualShareManagerLocalWindowShareEvent(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint, const VidyoLocalWindowShare* windowShare, VidyoDeviceState state);

/**
{function:
	{name: VidyoVirtualShareManagerLocalMonitorEvent}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: LmiBool VidyoVirtualShareManagerLocalMonitorEvent(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint, const VidyoLocalMonitor* monitor, VidyoDeviceState state)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: monitor}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoVirtualShareManagerLocalMonitorEvent(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint, const VidyoLocalMonitor* monitor, VidyoDeviceState state);

/**
{function:
	{name: VidyoVirtualShareManagerMediaFailedEvent}
	{parent: VidyoVirtualShareManager}
	{description: }
	{prototype: LmiBool VidyoVirtualShareManagerMediaFailedEvent(VidyoVirtualShareManager* m, VidyoEndpoint* endpoint)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoVirtualShareManagerMediaFailedEvent(VidyoVirtualShareManager *m, VidyoEndpoint* endpoint);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoVirtualShareManagerInline.h"
#endif

#endif /* VIDYO_VIRTUALSHAREMANAGER_H_ */
