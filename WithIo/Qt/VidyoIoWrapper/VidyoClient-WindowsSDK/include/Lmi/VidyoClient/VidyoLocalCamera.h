/** 
{file:
	{name: VidyoLocalCamera.h}
	{description: Camera device. }
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
#ifndef VIDYO_LOCALCAMERA_H_ 
#define VIDYO_LOCALCAMERA_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

#define VIDYOCLIENT_RESOURCEMANAGER_CapabilityScaleMultiple		( 2.0 )

struct VidyoVideoFrameNormalizationDataImpl_;
typedef struct VidyoVideoFrameNormalizationDataImpl_ VidyoVideoFrameNormalizationDataImpl;
Declare_LmiSharedPtr(VidyoVideoFrameNormalizationDataImpl)
Declare_LmiSharedPtrWrapper(VidyoVideoFrameNormalizationData, VidyoVideoFrameNormalizationDataImpl)
Declare_LmiWeakPtrWrapper(VidyoVideoFrameNormalizationDataHandle, VidyoVideoFrameNormalizationData, VidyoVideoFrameNormalizationDataImpl)
Declare_LmiVector(VidyoVideoFrameNormalizationData)

struct VidyoLocalCameraImpl_;
typedef struct VidyoLocalCameraImpl_ VidyoLocalCameraImpl;
Declare_LmiSharedPtr(VidyoLocalCameraImpl)
Declare_LmiSharedPtrWrapper(VidyoLocalCamera, VidyoLocalCameraImpl)
Declare_LmiWeakPtrWrapper(VidyoLocalCameraHandle, VidyoLocalCamera, VidyoLocalCameraImpl)
Declare_LmiVector(VidyoLocalCamera)
Declare_LmiList(VidyoLocalCamera)

LMI_END_EXTERN_C

#include "VidyoEndpoint.h"
#include "VidyoVideoCapability.h"
#include "VidyoLocalRenderer.h"
#include "VidyoRemoteRenderer.h"
#include "VidyoForwardDecl.h"
#include "VidyoStatistics.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoLocalCamera}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoLocalCamera.h}
	{description: This object represents a camera on the local endpoint.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique ID.}
	}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name. }
	}
}
*/

/**
{type apigroup="connector simple" visibility="private":
	{name: VidyoLocalCameraHandle}
	{parent: VidyoLocalCamera}
	{description: }
}
*/

/**
{callback visibility="private":
	{name: VidyoLocalCameraCallback}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void (*VidyoLocalCameraCallback)(const VidyoLocalCamera* c, const VidyoLmiVideoFrame* videoFrame)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: videoFrame}
		{description: }
	}
}
*/
typedef void (*VidyoLocalCameraCallback)(const VidyoLocalCamera* c, const VidyoLmiVideoFrame* videoFrame);

/**
{callback visibility="private":
	{name: VidyoLocalCameraStartCallback}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void (*VidyoLocalCameraStartCallback)(const VidyoLocalCamera* c, LmiSizeT width, LmiSizeT height, LmiTime frameInterval, LmiMediaFormat *mediaFormat, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
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
	{parameter:
		{name: mediaFormat}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalCameraStartCallback)(const VidyoLocalCamera* c, LmiSizeT width, LmiSizeT height, LmiTime frameInterval, LmiMediaFormat *mediaFormat, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalCameraReconfigureCallback}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void (*VidyoLocalCameraReconfigureCallback)(const VidyoLocalCamera* c, LmiSizeT width, LmiSizeT height, LmiTime frameInterval, const LmiMediaFormat *mediaFormat, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
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
	{parameter:
		{name: mediaFormat}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalCameraReconfigureCallback)(const VidyoLocalCamera* c, LmiSizeT width, LmiSizeT height, LmiTime frameInterval, const LmiMediaFormat *mediaFormat, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalCameraStopCallback}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void (*VidyoLocalCameraStopCallback)(const VidyoLocalCamera* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalCameraStopCallback)(const VidyoLocalCamera* c, LmiVoidPtr userData);

/**
{type apigroup="connector simple":
	{name: VidyoLocalCameraPosition}
	{parent: VidyoLocalCamera}
	{description: Position of the camera. }
	{value: {name: VIDYO_LOCALCAMERAPOSITION_Unknown} {description: Position is unknown. }}
	{value: {name: VIDYO_LOCALCAMERAPOSITION_Front} {description: Facing towards the screen. }}
	{value: {name: VIDYO_LOCALCAMERAPOSITION_Back} {description: Facing away from the screen. }}
}
*/
typedef enum {
	VIDYO_LOCALCAMERAPOSITION_Unknown,
	VIDYO_LOCALCAMERAPOSITION_Front,
	VIDYO_LOCALCAMERAPOSITION_Back
}
VidyoLocalCameraPosition;

/**
{function visibility="private":
	{name: VidyoLocalCameraConstruct}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: VidyoLocalCamera* VidyoLocalCameraConstruct(VidyoLocalCamera* c, VidyoEndpoint *endpoint, VidyoLmiVideoCapturer* videoCapturer, LmiAllocator* alloc)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: videoCapturer}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalCamera* VidyoLocalCameraConstruct(VidyoLocalCamera* c, VidyoEndpoint *endpoint, VidyoLmiVideoCapturer* videoCapturer, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoLocalCameraConstructVirtual}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: VidyoLocalCamera *VidyoLocalCameraConstructVirtual(VidyoLocalCamera *c, VidyoEndpoint *endpoint, LmiString *id, LmiString *name, VidyoLocalCameraPosition position, LmiBool isSuspended, LmiVector(VidyoVideoCapability) *capabilities, VidyoLocalCameraStartCallback onStart, VidyoLocalCameraReconfigureCallback onReconfigure, VidyoLocalCameraStopCallback onStop, LmiVoidPtr virtualUserData, LmiAllocator *alloc)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
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
		{name: position}
		{description: }
	}
	{parameter:
		{name: isSuspended}
		{description: }
	}
	{parameter:
		{name: capabilities}
		{description: }
	}
	{parameter:
		{name: onStart}
		{description: }
	}
	{parameter:
		{name: onReconfigure}
		{description: }
	}
	{parameter:
		{name: onStop}
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
VidyoLocalCamera *VidyoLocalCameraConstructVirtual(VidyoLocalCamera *c, VidyoEndpoint *endpoint, LmiString *id, LmiString *name, VidyoLocalCameraPosition position, LmiBool isSuspended, LmiVector(VidyoVideoCapability) *capabilities, VidyoLocalCameraStartCallback onStart, VidyoLocalCameraReconfigureCallback onReconfigure, VidyoLocalCameraStopCallback onStop, LmiVoidPtr virtualUserData, LmiAllocator *alloc);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraConstructCopy}
	{parent: VidyoLocalCamera}
	{description: Constructs an VidyoLocalCamera object as a copy of another.}
	{prototype: VidyoLocalCamera *VidyoLocalCameraConstructCopy(VidyoLocalCamera *obj, const VidyoLocalCamera *other)}
	{parameter: {name: obj} {description: The VidyoLocalCamera object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraDestruct}
	{parent: VidyoLocalCamera}
	{description: Destructs an VidyoLocalCamera object.}
	{prototype: void VidyoLocalCameraDestruct(VidyoLocalCamera *obj)}
	{parameter: {name: obj} {description: The VidyoLocalCamera object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalCameraAssign}
	{parent: VidyoLocalCamera}
	{description: Assigns one VidyoLocalCamera object the value of another. }
	{prototype: VidyoLocalCamera *VidyoLocalCameraAssign(VidyoLocalCamera *obj, const VidyoLocalCamera *other)}
	{parameter: {name: obj} {description: The VidyoLocalCamera object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalCameraGetHandle}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: VidyoLocalCameraHandle* VidyoLocalCameraGetHandle(VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: }
}
*/
VidyoLocalCameraHandle* VidyoLocalCameraGetHandle(VidyoLocalCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraGetName}
	{parent: VidyoLocalCamera}
	{description: Gets the name of the camera.}
	{prototype: const LmiString* VidyoLocalCameraGetName(const VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: Name of the camera.}
}
*/
const LmiString* VidyoLocalCameraGetName(const VidyoLocalCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraGetId}
	{parent: VidyoLocalCamera}
	{description: Gets the unique ID of the camera. }
	{prototype: const LmiString* VidyoLocalCameraGetId(const VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: Unique ID of the camera.}
}
*/
const LmiString* VidyoLocalCameraGetId(const VidyoLocalCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraGetPreviewLabel}
	{parent: VidyoLocalCamera}
	{description: Gets the preview label of the camera. }
	{prototype: const LmiString* VidyoLocalCameraGetPreviewLabel(const VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: Display name of the camera.}
}
*/
const LmiString* VidyoLocalCameraGetPreviewLabel(const VidyoLocalCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraSetPreviewLabel}
	{parent: VidyoLocalCamera}
	{description: Set the preview label of the camera. }
	{prototype: LmiBool VidyoLocalCameraSetPreviewLabel(VidyoLocalCamera* c, const LmiString* previewLabel)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: previewLabel}
		{description: Display name to set on the camera.}
	}
	{return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoLocalCameraSetPreviewLabel(VidyoLocalCamera* c, const LmiString* previewLabel);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraIsSuspended}
	{parent: VidyoLocalCamera}
	{description: Checks if the camera is suspended. }
	{prototype: LmiBool VidyoLocalCameraIsSuspended(const VidyoLocalCamera *c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: LMI_TRUE is suspended, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoLocalCameraIsSuspended(const VidyoLocalCamera *c);

/**
{function:
	{name: VidyoLocalCameraGetVideoCapabilities}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraGetVideoCapabilities(const VidyoLocalCamera* c, LmiVector(VidyoVideoCapability) *capabilities)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: capabilities}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraGetVideoCapabilities(const VidyoLocalCamera* c, LmiVector(VidyoVideoCapability) *capabilities);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraGetPosition}
	{parent: VidyoLocalCamera}
	{description: Gets the position of the camera.}
	{prototype: VidyoLocalCameraPosition VidyoLocalCameraGetPosition(const VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: Position of the camera. }
}
*/
VidyoLocalCameraPosition VidyoLocalCameraGetPosition(const VidyoLocalCamera* c);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalCameraSetUserData}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void VidyoLocalCameraSetUserData(VidyoLocalCamera* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoLocalCameraSetUserData(VidyoLocalCamera* c, LmiVoidPtr userData);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalCameraGetUserData}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalCameraGetUserData(const VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalCameraGetUserData(const VidyoLocalCamera* c);

/**
{function visibility="private":
	{name: VidyoLocalCameraSetCallback}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void VidyoLocalCameraSetCallback(VidyoLocalCamera* c, VidyoLocalCameraCallback callback)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoLocalCameraSetCallback(VidyoLocalCamera* c, VidyoLocalCameraCallback callback);

/**
{function:
	{name: VidyoLocalCameraIsPaused}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraIsPaused(const VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraIsPaused(const VidyoLocalCamera* c);

/**
{function visibility="private":
	{name: VidyoLocalCameraPause}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void VidyoLocalCameraPause(VidyoLocalCamera* c, VidyoLmiVideoFrame *image)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: image}
		{description: }
	}
}
*/
void VidyoLocalCameraPause(VidyoLocalCamera* c, VidyoLmiVideoFrame *image);

/**
{function:
	{name: VidyoLocalCameraResume}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: void VidyoLocalCameraResume(VidyoLocalCamera* c)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
}
*/
void VidyoLocalCameraResume(VidyoLocalCamera* c);

/**
{function apigroup="connector simple":
	{name: VidyoLocalCameraControlPTZ}
	{parent: VidyoLocalCamera}
	{description: Send the PTZ Nudge commands to the local camera.}
	{prototype: LmiBool VidyoLocalCameraControlPTZ(VidyoLocalCamera *c, LmiInt pan, LmiInt tilt, LmiInt zoom)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object. }
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
LmiBool VidyoLocalCameraControlPTZ(VidyoLocalCamera *c, LmiInt pan, LmiInt tilt, LmiInt zoom);

/**
{function apigroup="connector simple" visibility="public":
	{name: VidyoLocalCameraShowCameraControl}
	{parent: VidyoLocalCamera}
	{description: Shows camera control when rendering preview. }
	{prototype: LmiBool VidyoLocalCameraShowCameraControl(VidyoLocalCamera* c, LmiBool show)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: show}
		{description: Show or hide camera controls. }
	}
	{return: LMI_TRUE on success.}
	{note: Applies to Composite and Custom rendering layouts. }
}
*/
LmiBool VidyoLocalCameraShowCameraControl(VidyoLocalCamera* c, LmiBool show);

/**
{function apigroup="connector simple" visibility="public":
	{name: VidyoLocalCameraAllowRemoteCameraControl}
	{parent: VidyoLocalCamera}
	{description: Allows the PTZ conrol of the camera by remote participants. }
	{prototype: LmiBool VidyoLocalCameraAllowRemoteCameraControl(VidyoLocalCamera* c, LmiBool allow)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: allow}
		{description: Allow or prohibit camera control. }
	}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoLocalCameraAllowRemoteCameraControl(VidyoLocalCamera* c, LmiBool allow);

/**
{function:
	{name: VidyoLocalCameraSetConstraints}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraSetConstraints(VidyoLocalCamera* c, LmiUint minWidth, LmiUint minHeight, LmiUint maxWidth, LmiUint maxHeight, 
											LmiUint maxFrameInterval, LmiUint minFrameInterval, LmiUint aspectRatioWidth, LmiUint aspectRatioHeight,
											LmiUint temporalSpatialTradeOff, const LmiVector(VidyoVideoCapability)* capabilities)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: minWidth}
		{description: }
	}
	{parameter:
		{name: minHeight}
		{description: }
	}
	{parameter:
		{name: maxWidth}
		{description: }
	}
	{parameter:
		{name: maxHeight}
		{description: }
	}
	{parameter:
		{name: maxFrameInterval}
		{description: }
	}
	{parameter:
		{name: minFrameInterval}
		{description: }
	}
	{parameter:
		{name: aspectRatioWidth}
		{description: }
	}
	{parameter:
		{name: aspectRatioHeight}
		{description: }
	}
	{parameter:
		{name: temporalSpatialTradeOff}
		{description: }
	}
	{parameter:
		{name: capabilities}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraSetConstraints(VidyoLocalCamera* c, LmiUint minWidth, LmiUint minHeight, LmiUint maxWidth, LmiUint maxHeight,
												LmiUint maxFrameInterval, LmiUint minFrameInterval, LmiUint aspectRatioWidth, LmiUint aspectRatioHeight,
												LmiUint temporalSpatialTradeOff, const LmiVector(VidyoVideoCapability)* capabilities);

/**
{function:
	{name: VidyoLocalCameraSetBoundsConstraint}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraSetBoundsConstraint(VidyoLocalCamera* c, LmiUint minWidth, LmiUint minHeight, LmiUint maxWidth, LmiUint maxHeight, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint aspectRatioWidth, LmiUint aspectRatioHeight, LmiUint temporalSpatialTradeOff)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: minWidth}
		{description: }
	}
	{parameter:
		{name: minHeight}
		{description: }
	}
	{parameter:
		{name: maxWidth}
		{description: }
	}
	{parameter:
		{name: maxHeight}
		{description: }
	}
	{parameter:
		{name: maxFrameInterval}
		{description: }
	}
	{parameter:
		{name: minFrameInterval}
		{description: }
	}
	{parameter:
		{name: aspectRatioWidth}
		{description: }
	}
	{parameter:
		{name: aspectRatioHeight}
		{description: }
	}
	{parameter:
		{name: temporalSpatialTradeOff}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraSetBoundsConstraint(VidyoLocalCamera* c, LmiUint minWidth, LmiUint minHeight, LmiUint maxWidth, LmiUint maxHeight, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint aspectRatioWidth, LmiUint aspectRatioHeight, LmiUint temporalSpatialTradeOff);


/**
{function apigroup="connector simple" visibility="public":
	{name: VidyoLocalCameraSetAspectRatioConstraint}
	{parent: VidyoLocalCamera}
	{description: Sets the aspect ratio constraint on the camera which will adjust local camera frames to match. }
	{prototype: LmiBool VidyoLocalCameraSetAspectRatioConstraint(VidyoLocalCamera* c, LmiUint aspectRatioWidth, LmiUint aspectRatioHeight)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: aspectRatioWidth}
		{description: Width of the aspect ratio. }
	}
	{parameter:
		{name: aspectRatioHeight}
		{description: Height of the aspect ration. }
	}
	{return: LMI_TRUE on success.}
	{note: The default aspect ration is 16x9. }
}
*/
LmiBool VidyoLocalCameraSetAspectRatioConstraint(VidyoLocalCamera* c, LmiUint aspectRatioWidth, LmiUint aspectRatioHeight);

/**
{function:
	{name: VidyoLocalCameraSetCapabilitiesConstraint}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraSetCapabilitiesConstraint(VidyoLocalCamera* c, const LmiVector(VidyoVideoCapability)* capabilities, LmiUint temporalSpatialTradeOff)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: capabilities}
		{description: }
	}
	{parameter:
		{name: temporalSpatialTradeOff}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraSetCapabilitiesConstraint(VidyoLocalCamera* c, const LmiVector(VidyoVideoCapability)* capabilities, LmiUint temporalSpatialTradeOff);


/**
{function apigroup="connector simple" visibility="public":
	{name: VidyoLocalCameraSetMaxConstraint}
	{parent: VidyoLocalCamera}
	{description: Sets the maximum resolution and framerate constraint on the local camera. This overrides the defaults which are based on the CPU profile of the endpoint. }
	{prototype: LmiBool VidyoLocalCameraSetMaxConstraint(VidyoLocalCamera* c, LmiUint width, LmiUint height, LmiTime frameInterval)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: width}
		{description: Maximum width. }
	}
	{parameter:
		{name: height}
		{description: Maximum height. }
	}
	{parameter:
		{name: frameInterval}
		{description: Maximum frame interval. Setting to 0 selects the fastest frame rate. }
	}
	{return: LMI_TRUE on success.}
	{note: The constraint is restricted to 16x9 resoluitons that are available from the camera capabilities. }
}
*/
LmiBool VidyoLocalCameraSetMaxConstraint(VidyoLocalCamera* c, LmiUint width, LmiUint height, LmiTime frameInterval);

/**
{function visibility="private":
	{name: VidyoLocalCameraSetResourceConstraints}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraSetResourceConstraints(VidyoLocalCamera* c, VidyoLmiVideoSourceConstraints* constraints)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: constraints}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraSetResourceConstraints(VidyoLocalCamera* c, VidyoLmiVideoSourceConstraints* constraints);

/**
{function:
	{name: VidyoLocalCameraAddToRemoteRenderer}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraAddToRemoteRenderer(VidyoLocalCamera* c, const VidyoRemoteRenderer* remoteRenderer)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraAddToRemoteRenderer(VidyoLocalCamera* c, const VidyoRemoteRenderer* remoteRenderer);

/**
{function:
	{name: VidyoLocalCameraRemoveFromRemoteRenderer}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraRemoveFromRemoteRenderer(VidyoLocalCamera* c, const VidyoRemoteRenderer* remoteRenderer)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraRemoveFromRemoteRenderer(VidyoLocalCamera* c, const VidyoRemoteRenderer* remoteRenderer);

/**
{function:
	{name: VidyoLocalCameraAddToLocalRenderer}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalCameraAddToLocalRenderer(VidyoLocalCamera* c, const VidyoLocalRenderer* localRenderer)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalCameraAddToLocalRenderer(VidyoLocalCamera* c, const VidyoLocalRenderer* localRenderer);

/**
{function:
	{name: VidyoLocalCameraRemoveFromLocalRenderer}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraRemoveFromLocalRenderer(VidyoLocalCamera* c, const VidyoLocalRenderer* localRenderer)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraRemoveFromLocalRenderer(VidyoLocalCamera* c, const VidyoLocalRenderer* localRenderer);

/**
{function:
	{name: VidyoLocalCameraSetPositionInLocalRenderer}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraSetPositionInLocalRenderer(VidyoLocalCamera *c, const VidyoLocalRenderer *localRenderer, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object. }
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
LmiBool VidyoLocalCameraSetPositionInLocalRenderer(VidyoLocalCamera *c, const VidyoLocalRenderer *localRenderer, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval);


/**
{function visibility="private":
	{name: VidyoLocalCameraGetStats}
	{parent: VidyoLocalCamera}
	{description: Fill in stats data in VidyoLocalVideoSourceStats from a local camera.}
	{prototype: LmiBool VidyoLocalCameraGetStats(VidyoLocalCamera *c, VidyoLocalVideoSourceStats *stats)}
	{parameter: {name: c} {description: The local camera object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoLocalCameraGetStats(VidyoLocalCamera *c, VidyoLocalVideoSourceStats *stats);


/**
{function visibility="private":
	{name: VidyoLocalCameraAddVideoFrame}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: LmiBool VidyoLocalCameraAddVideoFrame(VidyoLocalCamera* c, const VidyoLmiVideoFrame *videoFrame)}
	{parameter:
		{name: c}
		{description: The VidyoLocalCamera object.}
	}
	{parameter:
		{name: videoFrame}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalCameraAddVideoFrame(VidyoLocalCamera *c, const VidyoLmiVideoFrame *videoFrame);

/**
{function visibility="private":
	{name: VidyoLocalCameraConstructFromDevice}
	{parent: VidyoLocalCamera}
	{description: }
	{prototype: VidyoLocalCamera *VidyoLocalCameraConstructFromDevice(VidyoLocalCamera* vidyoLocalCamera, const VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoLocalCamera}
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
VidyoLocalCamera *VidyoLocalCameraConstructFromDevice(VidyoLocalCamera* vidyoLocalCamera, const VidyoDevice *device, LmiAllocator* alloc);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoLocalCameraInline.h"
#endif

#endif /* VIDYO_LOCALCAMERA_H_ */
