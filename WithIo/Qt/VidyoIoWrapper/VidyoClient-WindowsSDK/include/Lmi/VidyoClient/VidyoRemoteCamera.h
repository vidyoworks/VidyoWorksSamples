/** 
{file:
	{name: VidyoRemoteCamera.h}
	{description: RemoteCamera device. }
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
#ifndef VIDYO_REMOTECAMERA_H_ 
#define VIDYO_REMOTECAMERA_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoRemoteCameraImpl_;
typedef struct VidyoRemoteCameraImpl_ VidyoRemoteCameraImpl;
Declare_LmiSharedPtr(VidyoRemoteCameraImpl)
Declare_LmiSharedPtrWrapper(VidyoRemoteCamera, VidyoRemoteCameraImpl)
Declare_LmiWeakPtrWrapper(VidyoRemoteCameraHandle, VidyoRemoteCamera, VidyoRemoteCameraImpl)
Declare_LmiVector(VidyoRemoteCamera)
Declare_LmiList(VidyoRemoteCamera)

LMI_END_EXTERN_C

#include "VidyoParticipant.h"
#include "VidyoLocalRenderer.h"
#include "VidyoForwardDecl.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C


/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoRemoteCamera}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoRemoteCamera.h}
	{description: This object represents a camera which belongs to the remote participant.}
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
	{name: VidyoRemoteCameraCallback}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: void (*VidyoRemoteCameraCallback)(const VidyoRemoteCamera* c, const VidyoLmiVideoFrame* videoFrame)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{parameter:
		{name: videoFrame}
		{description: }
	}
}
*/
typedef void (*VidyoRemoteCameraCallback)(const VidyoRemoteCamera* c, const VidyoLmiVideoFrame* videoFrame);

/**
{type:
	{name: VidyoRemoteCameraMode}
	{parent: VidyoRemoteCamera}
	{description: }
	{value: {name: VIDYO_REMOTECAMERAMODE_Dynamic} {description: }}
	{value: {name: VIDYO_REMOTECAMERAMODE_Static} {description: }}
}
*/
typedef enum {
	VIDYO_REMOTECAMERAMODE_Dynamic,
	VIDYO_REMOTECAMERAMODE_Static
} VidyoRemoteCameraMode;

/**
{type apigroup="connector simple":
	{name: VidyoRemoteCameraPosition}
	{parent: VidyoRemoteCamera}
	{description: Position of the camera.}
	{value: {name: VIDYO_REMOTECAMERAPOSITION_Unknown} {description: Position is unknown. }}
	{value: {name: VIDYO_REMOTECAMERAPOSITION_Front} {description: Facing towards the screen. }}
	{value: {name: VIDYO_REMOTECAMERAPOSITION_Back} {description: Facing away from the screen. }}
}
*/
typedef enum {
	VIDYO_REMOTECAMERAPOSITION_Unknown,
	VIDYO_REMOTECAMERAPOSITION_Front,
	VIDYO_REMOTECAMERAPOSITION_Back
} VidyoRemoteCameraPosition;

/**
{function visibility="private":
	{name: VidyoRemoteCameraConstruct}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: VidyoRemoteCamera* VidyoRemoteCameraConstruct(VidyoRemoteCamera* c, VidyoLmiRemoteSource* remoteSource, VidyoParticipant *participant, LmiAllocator* alloc)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
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
VidyoRemoteCamera* VidyoRemoteCameraConstruct(VidyoRemoteCamera* c, VidyoLmiRemoteSource* remoteSource, VidyoParticipant *participant, LmiAllocator* alloc);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteCameraConstructCopy}
	{parent: VidyoRemoteCamera}
	{description: Constructs an VidyoRemoteCamera object as a copy of another.}
	{prototype: VidyoRemoteCamera *VidyoRemoteCameraConstructCopy(VidyoRemoteCamera *obj, const VidyoRemoteCamera *other)}
	{parameter: {name: obj} {description: The VidyoRemoteCamera object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoRemoteCameraDestruct}
	{parent: VidyoRemoteCamera}
	{description: Destructs an VidyoRemoteCamera object.}
	{prototype: void VidyoRemoteCameraDestruct(VidyoRemoteCamera *obj)}
	{parameter: {name: obj} {description: The VidyoRemoteCamera object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoRemoteCameraAssign}
	{parent: VidyoRemoteCamera}
	{description: Assigns one VidyoRemoteCamera object the value of another. }
	{prototype: VidyoRemoteCamera *VidyoRemoteCameraAssign(VidyoRemoteCamera *obj, const VidyoRemoteCamera *other)}
	{parameter: {name: obj} {description: The VidyoRemoteCamera object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoRemoteCameraGetName}
	{parent: VidyoRemoteCamera}
	{description: Gets the name of the camera.}
	{prototype: const LmiString* VidyoRemoteCameraGetName(const VidyoRemoteCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{return: Name of the camera.}
}
*/
const LmiString* VidyoRemoteCameraGetName(const VidyoRemoteCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteCameraGetId}
	{parent: VidyoRemoteCamera}
	{description: Gets the unique ID of the camera.}
	{prototype: const LmiString* VidyoRemoteCameraGetId(const VidyoRemoteCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{return: Unique ID of the camera.}
}
*/
const LmiString* VidyoRemoteCameraGetId(const VidyoRemoteCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteCameraGetPosition}
	{parent: VidyoRemoteCamera}
	{description: Gets the position of the camera.}
	{prototype: VidyoRemoteCameraPosition VidyoRemoteCameraGetPosition(const VidyoRemoteCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{return: Position of the camera.}
}
*/
VidyoRemoteCameraPosition VidyoRemoteCameraGetPosition(const VidyoRemoteCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteCameraIsControllable}
	{parent: VidyoRemoteCamera}
	{description: Checks if the remote camera is controllable.}
	{prototype: LmiBool VidyoRemoteCameraIsControllable(VidyoRemoteCamera *c)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{return: LMI_TRUE if controllable, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoRemoteCameraIsControllable(VidyoRemoteCamera *c);

/**
{function apigroup="connector simple":
	{name: VidyoRemoteCameraControlPTZ}
	{parent: VidyoRemoteCamera}
	{description: Send the PTZ Nudge commands to the remote camera.}
	{prototype: LmiBool VidyoRemoteCameraControlPTZ(VidyoRemoteCamera *c, LmiInt pan, LmiInt tilt, LmiInt zoom)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{parameter:
		{name: pan}
		{description: Number of nudges to pan the camera. }
	}
	{parameter:
		{name: tilt}
		{description: Number of nudges to tilt the camera. }
	}
	{parameter:
		{name: zoom}
		{description: Number of nudges to zoom the camera. }
	}
	{return: LMI_TRUE when the control command was sent, LMI_FALSE otherwise.}
	{note: Positive numbers increase the nudge, and negative numbers decrease the nudge for left/right up/down zoom in/out. }
}
*/
LmiBool VidyoRemoteCameraControlPTZ(VidyoRemoteCamera *c, LmiInt pan, LmiInt tilt, LmiInt zoom);

/**
{function apigroup="connector simple" visibility="public":
	{name: VidyoRemoteCameraShowCameraControl}
	{parent: VidyoRemoteCamera}
	{description: Shows camera control when rendering remote camera. }
	{prototype: LmiBool VidyoRemoteCameraShowCameraControl(VidyoRemoteCamera* c, LmiBool show)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object.}
	}
	{parameter:
		{name: show}
		{description: Show or hide camera controls. }
	}
	{return: LMI_TRUE on success.}
	{note: Applies to Composite and Custom rendering layouts. }
}
*/
LmiBool VidyoRemoteCameraShowCameraControl(VidyoRemoteCamera* c, LmiBool show);

/**
{function visibility="private":
	{name: VidyoRemoteCameraSetUserData}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: void VidyoRemoteCameraSetUserData(VidyoRemoteCamera* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoRemoteCameraSetUserData(VidyoRemoteCamera* c, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoRemoteCameraGetUserData}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteCameraGetUserData(const VidyoRemoteCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteCameraGetUserData(const VidyoRemoteCamera* c);

/**
{function visibility="private":
	{name: VidyoRemoteCameraSetCallback}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: void VidyoRemoteCameraSetCallback(VidyoRemoteCamera* c, VidyoRemoteCameraCallback callback)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoRemoteCameraSetCallback(VidyoRemoteCamera* c, VidyoRemoteCameraCallback callback);

/**
{function visibility="private":
	{name: VidyoRemoteCameraGetParticipant}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: VidyoParticipant *VidyoRemoteCameraGetParticipant(VidyoRemoteCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{return: }
}
*/
VidyoParticipant *VidyoRemoteCameraGetParticipant(VidyoRemoteCamera *c);

/**
{function:
	{name: VidyoRemoteCameraAddToLocalRenderer}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteCameraAddToLocalRenderer(VidyoRemoteCamera* c, const VidyoLocalRenderer* localRenderer, VidyoRemoteCameraMode mode)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
	{parameter:
		{name: mode}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteCameraAddToLocalRenderer(VidyoRemoteCamera* c, const VidyoLocalRenderer* localRenderer, VidyoRemoteCameraMode mode);

/**
{function:
	{name: VidyoRemoteCameraRemoveFromLocalRenderer}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: LmiBool VidyoRemoteCameraRemoveFromLocalRenderer(VidyoRemoteCamera* c, const VidyoLocalRenderer* localRenderer)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRemoteCameraRemoveFromLocalRenderer(VidyoRemoteCamera* c, const VidyoLocalRenderer* localRenderer);

/**
{function:
	{name: VidyoRemoteCameraSetPositionInLocalRenderer}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: LmiBool VidyoRemoteCameraSetPositionInLocalRenderer(VidyoRemoteCamera *c, const VidyoLocalRenderer *localRenderer, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
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
LmiBool VidyoRemoteCameraSetPositionInLocalRenderer(VidyoRemoteCamera *c, const VidyoLocalRenderer *localRenderer, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval);

/**
{function:
	{name: VidyoRemoteCameraGetLocalRenderingStreamId}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: LmiVoidPtr VidyoRemoteCameraGetLocalRenderingStreamId(VidyoRemoteCamera* c, LmiInt index)}
	{parameter:
		{name: c}
		{description: The VidyoRemoteCamera object. }
	}
	{parameter:
		{name: index}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRemoteCameraGetLocalRenderingStreamId(VidyoRemoteCamera *c, LmiInt index);

/**
{function visibility="private":
	{name: VidyoRemoteCameraConstructFromDevice}
	{parent: VidyoRemoteCamera}
	{description: }
	{prototype: VidyoRemoteCamera *VidyoRemoteCameraConstructFromDevice(VidyoRemoteCamera* vidyoRemoteCamera, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoRemoteCamera}
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
VidyoRemoteCamera *VidyoRemoteCameraConstructFromDevice(VidyoRemoteCamera* vidyoRemoteCamera, VidyoDevice *device, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoRemoteCameraGetStats}
	{parent: VidyoRemoteCamera}
	{description: Fill in stats data in VidyoRemoteVideoSourceStats from a remote camera.}
	{prototype: LmiBool VidyoRemoteCameraGetStats(VidyoRemoteCamera *camera, VidyoRemoteVideoSourceStats *stats)}
	{parameter: {name: camera} {description: The remote camera object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoRemoteCameraGetStats(VidyoRemoteCamera *camera, VidyoRemoteVideoSourceStats *stats);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRemoteCameraInline.h"
#endif

#endif /* VIDYO_REMOTECAMERA_H_ */
