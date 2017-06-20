/**
{file:
	{name: VidyoDevice.h}
	{description: Device base class. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.

		All rights reserved.

		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.
		                  ***** CONFIDENTIAL *****
	}
}
*/
#ifndef VIDYO_DEVICE_H_
#define VIDYO_DEVICE_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoDeviceImpl_;
typedef struct VidyoDeviceImpl_ VidyoDeviceImpl;
Declare_LmiSharedPtr(VidyoDeviceImpl)
Declare_LmiSharedPtrWrapper(VidyoDevice, VidyoDeviceImpl)
Declare_LmiWeakPtrWrapper(VidyoDeviceHandle, VidyoDevice, VidyoDeviceImpl)
Declare_LmiVector(VidyoDevice)
Declare_LmiList(VidyoDevice)

/**
{package:
	{name: Device}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoDevice.h}
	{description: The VidyoDevice package.}
}
*/

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoDevice}
	{parent: Device}
	{description: A wrapper class for Local and Remote devices. }
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique ID of the device.}
	}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name of the device.}
	}
	{member:
		{name: type}
		{type: VidyoDeviceType}
		{description: Type of the device.}
	}
}
*/

/**
{type:
	{name: VidyoDeviceType}
	{parent: VidyoDevice}
	{description: Device type.}
	{value: {name: VIDYO_DEVICETYPE_LocalCamera}
			{description: local camera device.}
	}
	{value: {name: VIDYO_DEVICETYPE_LocalMicrophone}
			{description: local microphone device.}
	}
	{value: {name: VIDYO_DEVICETYPE_LocalMonitor}
			{description: local screen device.}
	}
	{value: {name: VIDYO_DEVICETYPE_LocalWindowShare}
			{description: local application window device.}
	}
	{value: {name: VIDYO_DEVICETYPE_LocalSpeaker}
			{description: local speaker device.}
	}
	{value: {name: VIDYO_DEVICETYPE_LocalRenderer}
			{description: local renderer device.}
	}
	{value: {name: VIDYO_DEVICETYPE_RemoteCamera}
			{description: remote camera device.}
	}
	{value: {name: VIDYO_DEVICETYPE_RemoteMicrophone}
			{description: remote microphone device.}
	}
	{value: {name: VIDYO_DEVICETYPE_RemoteWindowShare}
			{description: remote application window device.}
	}
	{value: {name: VIDYO_DEVICETYPE_RemoteSpeaker}
			{description: remote speaker device.}
	}
	{value: {name: VIDYO_DEVICETYPE_RemoteRenderer}
			{description: remote renderer device.}
	}
}
*/
typedef enum
{
	VIDYO_DEVICETYPE_LocalCamera,
	VIDYO_DEVICETYPE_LocalMicrophone,
	VIDYO_DEVICETYPE_LocalMonitor,
	VIDYO_DEVICETYPE_LocalWindowShare,
	VIDYO_DEVICETYPE_LocalSpeaker,
	VIDYO_DEVICETYPE_LocalRenderer,
	VIDYO_DEVICETYPE_RemoteCamera,
	VIDYO_DEVICETYPE_RemoteMicrophone,
	VIDYO_DEVICETYPE_RemoteWindowShare,
	VIDYO_DEVICETYPE_RemoteSpeaker,
	VIDYO_DEVICETYPE_RemoteRenderer
} VidyoDeviceType;

/**
{type apigroup="connector simple":
	{name: VidyoDeviceState}
	{parent: VidyoDevice}
	{description: Operational state of a device.}
	{value: {name: VIDYO_DEVICESTATE_Added}
			{description: The device was added to the system.}
	}
	{value: {name: VIDYO_DEVICESTATE_Removed}
			{description: The device was removed from the system.}
	}
	{value: {name: VIDYO_DEVICESTATE_Started}
			{description: The device started successfully.}
	}
	{value: {name: VIDYO_DEVICESTATE_Stopped}
			{description: The device stopped.}
	}
	{value: {name: VIDYO_DEVICESTATE_Suspended}
			{description: The device was suspended and the frames can no longer be captured.}
	}
	{value: {name: VIDYO_DEVICESTATE_Unsuspended}
			{description: The device was unsuspended.}
	}
	{value: {name: VIDYO_DEVICESTATE_Paused}
			{description: The device was paused (muted) and no media will be sent.}
	}
	{value: {name: VIDYO_DEVICESTATE_Resumed}
			{description: The device was resumed (unmuted) and media will be sent.}
	}
	{value: {name: VIDYO_DEVICESTATE_Controllable}
			{description: The device PTZ is controllable.}
	}
	{value: {name: VIDYO_DEVICESTATE_NotControllable}
			{description: The device PTZ is not controllable.}
	}
	{value: {name: VIDYO_DEVICESTATE_DefaultChanged}
			{description: The device default device has changed.}
	}
	{value: {name: VIDYO_DEVICESTATE_ConfigureSuccess}
			{description: The device configured successfully.}
	}
	{value: {name: VIDYO_DEVICESTATE_ConfigureError}
			{description: The device configuring failed.}
	}
	{value: {name: VIDYO_DEVICESTATE_Error}
			{description: The device failed.}
	}
}
*/
typedef enum
{
	VIDYO_DEVICESTATE_Added,
	VIDYO_DEVICESTATE_Removed,
	VIDYO_DEVICESTATE_Started,
	VIDYO_DEVICESTATE_Stopped,
	VIDYO_DEVICESTATE_Suspended,
	VIDYO_DEVICESTATE_Unsuspended,
	VIDYO_DEVICESTATE_Paused,
	VIDYO_DEVICESTATE_Resumed,
	VIDYO_DEVICESTATE_Controllable,
	VIDYO_DEVICESTATE_NotControllable,
	VIDYO_DEVICESTATE_DefaultChanged,
	VIDYO_DEVICESTATE_ConfigureSuccess,
	VIDYO_DEVICESTATE_ConfigureError,
	VIDYO_DEVICESTATE_Error
} VidyoDeviceState;


/**
{type apigroup="connector simple":
	{name: VidyoDeviceAudioSignalType}
	{parent: VidyoDevice}
	{description: Sets the type of the auido signal which determines how it is processed such as noise suppression, echo cancellation etc. }
	{value: {name: VIDYO_DEVICEAUDIOSIGNALTYPE_Voice} {description: Default type which will do echo cancellation, noise suppresstion etc. }}
	{value: {name: VIDYO_DEVICEAUDIOSIGNALTYPE_Unprocessed} {description: Does not alter audio singal by having all the audio processing disabled. }}
}
*/
typedef enum {
	VIDYO_DEVICEAUDIOSIGNALTYPE_Voice,
	VIDYO_DEVICEAUDIOSIGNALTYPE_Unprocessed
}
VidyoDeviceAudioSignalType;

LMI_END_EXTERN_C

/* sinks */
#include "VidyoLocalSpeaker.h"
#include "VidyoRemoteSpeaker.h"
#include "VidyoLocalRenderer.h"
#include "VidyoRemoteRenderer.h"

/* sources */
#include "VidyoLocalCamera.h"
#include "VidyoLocalMicrophone.h"
#include "VidyoRemoteMicrophone.h"
#include "VidyoDevice.h"
#include "VidyoRemoteCamera.h"
#include "VidyoLocalWindowShare.h"
#include "VidyoRemoteWindowShare.h"
#include "VidyoLocalMonitor.h"

LMI_BEGIN_EXTERN_C

/**
{function visibility="private":
	{name: VidyoDeviceConstruct}
	{parent: VidyoDevice}
	{description: Initialize an instance of VidyoDevice}
	{prototype: VidyoDevice* VidyoDeviceConstruct(VidyoDevice* device, const LmiSharedVoidPtr* devicePtr, VidyoDeviceType type, LmiAllocator* alloc)}
	{parameter: {name: device} {description: Pointer to the VidyoDevice object to construct.}}
	{parameter: {name: devicePtr} {description: }}
	{parameter: {name: type} {description: }}
	{parameter: {name: alloc} {description: allocator}}
	{return: Properly initialized object or NULL on failure.}
}
*/
VidyoDevice* VidyoDeviceConstruct(VidyoDevice* device, const LmiSharedVoidPtr* devicePtr, VidyoDeviceType type, LmiAllocator* alloc);

/**
{function:
	{name: VidyoDeviceConstructCopy}
	{parent: VidyoDevice}
	{description: Constructs an VidyoDevice object as a copy of another.}
	{prototype: VidyoDevice *VidyoDeviceConstructCopy(VidyoDevice *obj, const VidyoDevice *other)}
	{parameter: {name: obj} {description: The VidyoDevice object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoDevice *VidyoDeviceConstructCopy(VidyoDevice *obj, const VidyoDevice *other);

/**
{function:
	{name: VidyoDeviceDestruct}
	{parent: VidyoDevice}
	{description: Destruct an instance of VidyoDevice. This may block until there are no more threads running.}
	{prototype: void VidyoDeviceDestruct(VidyoDevice* device)}
	{parameter: {name: device} {description: Pointer to the VidyoDevice object to destruct.}}
}
*/
void VidyoDeviceDestruct(VidyoDevice* device);

/**
{function:
	{name: VidyoDeviceAssign}
	{parent: VidyoDevice}
	{description: Assigns one VidyoDevice object the value of another. }
	{prototype: VidyoDevice *VidyoDeviceAssign(VidyoDevice *obj, const VidyoDevice *other)}
	{parameter: {name: obj} {description: The VidyoDevice object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/
VidyoDevice *VidyoDeviceAssign(VidyoDevice *obj, const VidyoDevice *other);

/**
{function:
	{name: VidyoDeviceDerivedEqual}
	{parent: VidyoDevice}
	{description: Compare the values of two derived devices for equality. }
	{prototype: LmiBool VidyoDeviceDerivedEqual(const VidyoDevice *obj, const VidyoDevice *other)}
	{parameter: {name: obj} {description: The VidyoDevice object comparing against.}}
	{parameter: {name: other} {description: The VidyoDevice object comparing.}}
	{return: Whether the pointers contained in the shared void pointer objects are the same.}
}
*/
LmiBool VidyoDeviceDerivedEqual(const VidyoDevice *obj, const VidyoDevice *other);

/**
{function:
	{name: VidyoDeviceGetType}
	{parent: VidyoDevice}
	{description: Gets the device type. }
	{prototype: VidyoDeviceType VidyoDeviceGetType(const VidyoDevice* d)}
	{parameter: {name: d} {description: The VidyoDevice object.}}
	{return: Device Type.}
}
*/
VidyoDeviceType VidyoDeviceGetType(const VidyoDevice* d);

/**
{function:
	{name: VidyoDeviceGetId}
	{parent: VidyoDevice}
	{description: Gets the device id. }
	{prototype: const LmiString *VidyoDeviceGetId(const VidyoDevice* d)}
	{parameter: {name: d} {description: The VidyoDevice object.}}
	{return: Device id.}
}
*/
const LmiString *VidyoDeviceGetId(const VidyoDevice* d);

/**
{function:
	{name: VidyoDeviceGetName}
	{parent: VidyoDevice}
	{description: Gets the device name. }
	{prototype: const LmiString *VidyoDeviceGetName(const VidyoDevice* d)}
	{parameter: {name: d} {description: The VidyoDevice object.}}
	{return: Device name.}
}
*/
const LmiString *VidyoDeviceGetName(const VidyoDevice* d);

/**
{function visibility="private":
	{name: VidyoDeviceSetUserData}
	{parent: VidyoDevice}
	{description: }
	{prototype: void VidyoDeviceSetUserData(VidyoDevice* d, LmiVoidPtr userData)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoDeviceSetUserData(VidyoDevice *d, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoDeviceGetUserData}
	{parent: VidyoDevice}
	{description: }
	{prototype: LmiVoidPtr VidyoDeviceGetUserData(const VidyoDevice* d)}
	{parameter:
		{name: d}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoDeviceGetUserData(const VidyoDevice *d);

/**
{function visibility="private":
	{name: VidyoDeviceAddToLocalRenderer}
	{parent: VidyoDevice}
	{description: }
	{prototype: LmiBool VidyoDeviceAddToLocalRenderer(VidyoDevice* d, VidyoLocalRenderer* r, LmiBool isStatic)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: isStatic}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoDeviceAddToLocalRenderer(VidyoDevice* d, VidyoLocalRenderer* r, LmiBool isStatic);

/**
{function visibility="private":
	{name: VidyoDeviceRemoveFromLocalRenderer}
	{parent: VidyoDevice}
	{description: }
	{prototype: LmiBool VidyoDeviceRemoveFromLocalRenderer(VidyoDevice* d, VidyoLocalRenderer* r)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoDeviceRemoveFromLocalRenderer(VidyoDevice* d, VidyoLocalRenderer* r);

/**
{function visibility="private":
	{name: VidyoDeviceSetPositionInLocalRenderer}
	{parent: VidyoDevice}
	{description: }
	{prototype: LmiBool VidyoDeviceSetPositionInLocalRenderer(VidyoDevice* d, VidyoLocalRenderer* r, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: r}
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
LmiBool VidyoDeviceSetPositionInLocalRenderer(VidyoDevice* d, VidyoLocalRenderer* r, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoDeviceInline.h"
#endif

#endif /* VIDYO_DEVICE_H_ */
