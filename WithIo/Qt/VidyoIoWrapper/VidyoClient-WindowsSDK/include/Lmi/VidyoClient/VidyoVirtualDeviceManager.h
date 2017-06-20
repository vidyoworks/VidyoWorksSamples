/** 
{file:
	{name: VidyoVirtualDeviceManager.h}
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
#ifndef VIDYO_VIRTUALDEVICEMANAGER_H_ 
#define VIDYO_VIRTUALDEVICEMANAGER_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoVirtualDeviceManagerImpl_;
typedef struct VidyoVirtualDeviceManagerImpl_ VidyoVirtualDeviceManagerImpl;
Declare_LmiSharedPtr(VidyoVirtualDeviceManagerImpl)
Declare_LmiSharedPtrWrapper(VidyoVirtualDeviceManager, VidyoVirtualDeviceManagerImpl)
Declare_LmiWeakPtrWrapper(VidyoVirtualDeviceManagerHandle, VidyoVirtualDeviceManager, VidyoVirtualDeviceManagerImpl)
Declare_LmiVector(VidyoVirtualDeviceManager)
Declare_LmiList(VidyoVirtualDeviceManager)

LMI_END_EXTERN_C

#include "VidyoLocalCamera.h"
#include "VidyoLocalMicrophone.h"
#include "VidyoLocalSpeaker.h"

#include "VidyoForwardDecl.h"
#include "VidyoEndpoint.h"

LMI_BEGIN_EXTERN_C

/**
{type reference-counted="yes":
	{name: VidyoVirtualDeviceManager}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoVirtualDeviceManager.h}
	{description: }
}
*/

/**
{type visibility="private":
	{name: VidyoVirtualDeviceManagerHandle}
	{parent: VidyoVirtualDeviceManager}
	{description: }
}
*/

/**
{callback visibility="private":
	{name: VidyoVirtualDeviceManagerStartCallback}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: LmiBool (*VidyoVirtualDeviceManagerStartCallback)(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint)}
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
typedef LmiBool (*VidyoVirtualDeviceManagerStartCallback)(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint);

/**
{callback visibility="private":
	{name: VidyoVirtualDeviceManagerStopCallback}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: void (*VidyoVirtualDeviceManagerStopCallback)(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint)}
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
typedef void (*VidyoVirtualDeviceManagerStopCallback)(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint);

/**
{callback visibility="private":
	{name: VidyoVirtualDeviceManagerMediaStateCallback}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: void (*VidyoVirtualDeviceManagerMediaStateCallback)(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, VidyoEndpointMediaState state)}
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
typedef void (*VidyoVirtualDeviceManagerMediaStateCallback)(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, VidyoEndpointMediaState state);

/**
{function visibility="private":
	{name: VidyoVirtualDeviceManagerConstruct}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: VidyoVirtualDeviceManager* VidyoVirtualDeviceManagerConstruct(VidyoVirtualDeviceManager* m, VidyoVirtualDeviceManagerStartCallback onStart, VidyoVirtualDeviceManagerStopCallback onStop, VidyoVirtualDeviceManagerMediaStateCallback onMediaState, LmiAllocator* alloc)}
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
VidyoVirtualDeviceManager* VidyoVirtualDeviceManagerConstruct(VidyoVirtualDeviceManager* m, VidyoVirtualDeviceManagerStartCallback onStart, VidyoVirtualDeviceManagerStopCallback onStop, VidyoVirtualDeviceManagerMediaStateCallback onMediaState, LmiAllocator* alloc);

/**
{function:
	{name: VidyoVirtualDeviceManagerConstructCopy}
	{parent: VidyoVirtualDeviceManager}
	{description: Constructs an VidyoVirtualDeviceManager object as a copy of another.}
	{prototype: VidyoVirtualDeviceManager* VidyoVirtualDeviceManagerConstructCopy(VidyoVirtualDeviceManager* obj, const VidyoVirtualDeviceManager* other)}
	{parameter: {name: obj} {description: The VidyoVirtualDeviceManager object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoVirtualDeviceManagerDestruct}
	{parent: VidyoVirtualDeviceManager}
	{description: Destructs an VidyoVirtualDeviceManager object.}
	{prototype: void VidyoVirtualDeviceManagerDestruct(VidyoVirtualDeviceManager* obj)}
	{parameter: {name: obj} {description: The VidyoVirtualDeviceManager object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoVirtualDeviceManagerAssign}
	{parent: VidyoVirtualDeviceManager}
	{description: Assigns one VidyoVirtualDeviceManager object the value of another. }
	{prototype: VidyoVirtualDeviceManager* VidyoVirtualDeviceManagerAssign(VidyoVirtualDeviceManager* obj, const VidyoVirtualDeviceManager* other)}
	{parameter: {name: obj} {description: The VidyoVirtualDeviceManager object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoVirtualDeviceManagerGetHandle}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: VidyoVirtualDeviceManagerHandle* VidyoVirtualDeviceManagerGetHandle(VidyoVirtualDeviceManager* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
VidyoVirtualDeviceManagerHandle* VidyoVirtualDeviceManagerGetHandle(VidyoVirtualDeviceManager* m);

/**
{function visibility="private":
	{name: VidyoVirtualDeviceManagerSetUserData}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: void VidyoVirtualDeviceManagerSetUserData(VidyoVirtualDeviceManager* m, LmiVoidPtr userData)}
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
void VidyoVirtualDeviceManagerSetUserData(VidyoVirtualDeviceManager* m, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoVirtualDeviceManagerGetUserData}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: LmiVoidPtr VidyoVirtualDeviceManagerGetUserData(const VidyoVirtualDeviceManager* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoVirtualDeviceManagerGetUserData(const VidyoVirtualDeviceManager* m);

/**
{function:
	{name: VidyoVirtualDeviceManagerLocalCameraEvent}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: LmiBool VidyoVirtualDeviceManagerLocalCameraEvent(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, const VidyoLocalCamera* camera, VidyoDeviceState state)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: camera}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoVirtualDeviceManagerLocalCameraEvent(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, const VidyoLocalCamera* camera, VidyoDeviceState state);

/**
{function:
	{name: VidyoVirtualDeviceManagerLocalMicrophoneEvent}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: LmiBool VidyoVirtualDeviceManagerLocalMicrophoneEvent(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, const VidyoLocalMicrophone* microphone, VidyoDeviceState state)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: microphone}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoVirtualDeviceManagerLocalMicrophoneEvent(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, const VidyoLocalMicrophone* microphone, VidyoDeviceState state);

/**
{function:
	{name: VidyoVirtualDeviceManagerLocalSpeakerEvent}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: LmiBool VidyoVirtualDeviceManagerLocalSpeakerEvent(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, const VidyoLocalSpeaker* speaker, VidyoDeviceState state)}
	{parameter:
		{name: m}
		{description: }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: speaker}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoVirtualDeviceManagerLocalSpeakerEvent(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint, const VidyoLocalSpeaker* speaker, VidyoDeviceState state);

/**
{function:
	{name: VidyoVirtualDeviceManagerMediaFailedEvent}
	{parent: VidyoVirtualDeviceManager}
	{description: }
	{prototype: LmiBool VidyoVirtualDeviceManagerMediaFailedEvent(VidyoVirtualDeviceManager* m, VidyoEndpoint* endpoint)}
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
LmiBool VidyoVirtualDeviceManagerMediaFailedEvent(VidyoVirtualDeviceManager *m, VidyoEndpoint* endpoint);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoVirtualDeviceManagerInline.h"
#endif

#endif /* VIDYO_VIRTUALDEVICEMANAGER_H_ */
