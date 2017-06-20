/** 
{file:
	{name: VidyoLocalMonitor.h}
	{description: Monitor available for sharing. }
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
#ifndef VIDYO_LOCALMONITOR_H_ 
#define VIDYO_LOCALMONITOR_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiRectangle.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoLocalMonitorImpl_;
typedef struct VidyoLocalMonitorImpl_ VidyoLocalMonitorImpl;
Declare_LmiSharedPtr(VidyoLocalMonitorImpl)
Declare_LmiSharedPtrWrapper(VidyoLocalMonitor, VidyoLocalMonitorImpl)
Declare_LmiWeakPtrWrapper(VidyoLocalMonitorHandle, VidyoLocalMonitor, VidyoLocalMonitorImpl)
Declare_LmiVector(VidyoLocalMonitor)
Declare_LmiList(VidyoLocalMonitor)

LMI_END_EXTERN_C

#include "VidyoLocalRenderer.h"
#include "VidyoRemoteRenderer.h"
#include "VidyoLocalWindowShare.h"
#include "VidyoForwardDecl.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C


/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoLocalMonitor}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoLocalMonitor.h}
	{description: This object represents a monitor on the local endpoint.}
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
	{name: VidyoLocalMonitorHandle}
	{parent: VidyoLocalMonitor}
	{description: }
}
*/

/**
{type apigroup="connector simple":
	{name: VidyoLocalMonitorState}
	{parent: VidyoLocalMonitor}
	{description: State of the monitor.}
	{value: {name: VIDYO_LOCALMONITORSTATE_Ok} {description: The monitor is visible and has been fully captured.}}
	{value: {name: VIDYO_LOCALMONITORSTATE_NotVisible} {description: The monitor exists but is not "visible".}}
	{value: {name: VIDYO_LOCALMONITORSTATE_MiscError} {description: Miscellaneous error has occured trying to capture the frame.}}
}
*/
typedef enum {
	VIDYO_LOCALMONITORSTATE_Ok,
	VIDYO_LOCALMONITORSTATE_NotVisible,
	VIDYO_LOCALMONITORSTATE_MiscError
}
VidyoLocalMonitorState;

/**
{callback apigroup="connector simple" visibility="private":
	{name: VidyoLocalMonitorCallback}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: void (*VidyoLocalMonitorCallback)(const VidyoLocalMonitor* m, const VidyoLmiVideoFrame* videoFrame)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: videoFrame}
		{description: }
	}
}
*/
typedef void (*VidyoLocalMonitorCallback)(const VidyoLocalMonitor* m, const VidyoLmiVideoFrame* videoFrame);

/**
{callback apigroup="connector simple":
	{name: VidyoLocalMonitorOnPreviewDataUriComplete}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: void (*VidyoLocalMonitorOnPreviewDataUriComplete)(const VidyoLocalMonitor* w, const LmiString* videoFrame, VidyoLocalMonitorState state)}
	{parameter:
		{name: w}
		{description: }
	}
	{parameter:
		{name: videoFrame}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void (*VidyoLocalMonitorOnPreviewDataUriComplete)(const VidyoLocalMonitor* w, const LmiString* videoFrame, VidyoLocalMonitorState state);

/**
{function visibility="private":
	{name: VidyoLocalMonitorConstruct}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: VidyoLocalMonitor* VidyoLocalMonitorConstruct(VidyoLocalMonitor* m, VidyoEndpoint *endpoint, const VidyoLmiScreen* screen, LmiAllocator* alloc)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: screen}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalMonitor* VidyoLocalMonitorConstruct(VidyoLocalMonitor* m, VidyoEndpoint *endpoint, const VidyoLmiScreen* screen, LmiAllocator* alloc);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMonitorConstructCopy}
	{parent: VidyoLocalMonitor}
	{description: Constructs an VidyoLocalMonitor object as a copy of another.}
	{prototype: VidyoLocalMonitor *VidyoLocalMonitorConstructCopy(VidyoLocalMonitor *obj, const VidyoLocalMonitor *other)}
	{parameter: {name: obj} {description: The VidyoLocalMonitor object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoLocalMonitorDestruct}
	{parent: VidyoLocalMonitor}
	{description: Destructs an VidyoLocalMonitor object.}
	{prototype: void VidyoLocalMonitorDestruct(VidyoLocalMonitor *obj)}
	{parameter: {name: obj} {description: The VidyoLocalMonitor object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMonitorAssign}
	{parent: VidyoLocalMonitor}
	{description: Assigns one VidyoLocalMonitor object the value of another. }
	{prototype: VidyoLocalMonitor *VidyoLocalMonitorAssign(VidyoLocalMonitor *obj, const VidyoLocalMonitor *other)}
	{parameter: {name: obj} {description: The VidyoLocalMonitor object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMonitorGetHandle}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: VidyoLocalMonitorHandle* VidyoLocalMonitorGetHandle(VidyoLocalMonitor* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{return: }
}
*/
VidyoLocalMonitorHandle* VidyoLocalMonitorGetHandle(VidyoLocalMonitor* m);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMonitorGetName}
	{parent: VidyoLocalMonitor}
	{description: Gets the name of the monitor.}
	{prototype: const LmiString* VidyoLocalMonitorGetName(const VidyoLocalMonitor* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{return: Name of the monitor.}
}
*/
const LmiString* VidyoLocalMonitorGetName(const VidyoLocalMonitor* m);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMonitorGetId}
	{parent: VidyoLocalMonitor}
	{description: Gets the unique ID of the monitor.}
	{prototype: const LmiString* VidyoLocalMonitorGetId(const VidyoLocalMonitor* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{return: Unique ID of the monitor. }
}
*/
const LmiString* VidyoLocalMonitorGetId(const VidyoLocalMonitor* m);

/**
{function visibility="private":
	{name: VidyoLocalMonitorGetPosition}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: const LmiRectangle* VidyoLocalMonitorGetPosition(const VidyoLocalMonitor* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{return: }
}
*/
const LmiRectangle* VidyoLocalMonitorGetPosition(const VidyoLocalMonitor* m);

/**
{function visibility="private":
	{name: VidyoLocalMonitorGetWorkArea}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: const LmiRectangle* VidyoLocalMonitorGetWorkArea(const VidyoLocalMonitor* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{return: }
}
*/
const LmiRectangle* VidyoLocalMonitorGetWorkArea(const VidyoLocalMonitor* m);

/**
{function:
	{name: VidyoLocalMonitorSetCaptureInterval}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorSetCaptureInterval(VidyoLocalMonitor* m, LmiTime frameInterval)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: frameInterval}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMonitorSetCaptureInterval(VidyoLocalMonitor* m, LmiTime frameInterval);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMonitorSetUserData}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: void VidyoLocalMonitorSetUserData(VidyoLocalMonitor* m, LmiVoidPtr userData)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoLocalMonitorSetUserData(VidyoLocalMonitor* m, LmiVoidPtr userData);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMonitorGetUserData}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalMonitorGetUserData(const VidyoLocalMonitor* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalMonitorGetUserData(const VidyoLocalMonitor* m);

/**
{function visibility="private":
	{name: VidyoLocalMonitorSetCallback}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: void VidyoLocalMonitorSetCallback(VidyoLocalMonitor* m, VidyoLocalMonitorCallback callback)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoLocalMonitorSetCallback(VidyoLocalMonitor* m, VidyoLocalMonitorCallback callback);

/**
{function visibility="private":
	{name: VidyoLocalMonitorGetPreviewFrame}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: VidyoLocalMonitorState VidyoLocalMonitorGetPreviewFrame(VidyoLocalMonitor *m, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLmiVideoFrame *videoFrame)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: maxWidth}
		{description: Maximum width of the preview image.}
	}
	{parameter:
		{name: maxHeight}
		{description: Maximum height of the preview image.}
	}
	{parameter:
		{name: videoFrame}
		{description: Video Frame to which the image will be assigned.}
	}
	{return: }
	{note: The aspect ratio will be preserved. }
	{note: The videoFrame will only contain the new image if VidyoLocalMonitorState VIDYO_LOCALMONITORSTATE_Ok, otherwise will will be assigned last valid preview image. }
}
*/
VidyoLocalMonitorState VidyoLocalMonitorGetPreviewFrame(VidyoLocalMonitor *m, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLmiVideoFrame *videoFrame);

/**
{function:
	{name: VidyoLocalMonitorGetPreviewFrameDataUri}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: VidyoLocalMonitorState VidyoLocalMonitorGetPreviewFrameDataUri(VidyoLocalMonitor *m, LmiSizeT maxWidth, LmiSizeT maxHeight, LmiString *videoFrame)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: maxWidth}
		{description: Maximum width of the preview image.}
	}
	{parameter:
		{name: maxHeight}
		{description: Maximum height of the preview image.}
	}
	{parameter:
		{name: videoFrame}
		{description: Video Frame to which the image will be assigned.}
	}
	{return: }
	{note: The aspect ratio will be preserved. }
	{note: The videoFrame will only contain the new image if VidyoLocalMonitorState VIDYO_LOCALMONITORSTATE_Ok, otherwise will will be assigned last valid preview image. }
}
*/
VidyoLocalMonitorState VidyoLocalMonitorGetPreviewFrameDataUri(VidyoLocalMonitor *m, LmiSizeT maxWidth, LmiSizeT maxHeight, LmiString *videoFrame);

/**
{function:
	{name: VidyoLocalMonitorGetPreviewFrameDataUriAsync}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorGetPreviewFrameDataUriAsync(VidyoLocalMonitor* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLocalMonitorOnPreviewDataUriComplete onComplete)}
	{parameter:
		{name: w}
		{description: }
	}
	{parameter:
		{name: maxWidth}
		{description: Maximum width of the preview image.}
	}
	{parameter:
		{name: maxHeight}
		{description: Maximum height of the preview image.}
	}
	{parameter:
		{name: onComplete}
		{description: Callback that is triggered when a preview frame is captured.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: The aspect ratio will be preserved. }
}
*/
LmiBool VidyoLocalMonitorGetPreviewFrameDataUriAsync(VidyoLocalMonitor* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLocalMonitorOnPreviewDataUriComplete onComplete);

/**
{function visibility="private":
	{name: VidyoLocalMonitorSetFrameIntervalConstraints}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorSetFrameIntervalConstraints(VidyoLocalMonitor* c, LmiInt maxFrameInterval, LmiInt minFrameInterval, LmiFloat32 scaleFactor)}
	{parameter:
		{name: c}
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
		{name: scaleFactor}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMonitorSetFrameIntervalConstraints(VidyoLocalMonitor* c, LmiInt maxFrameInterval, LmiInt minFrameInterval, LmiFloat32 scaleFactor);

/**
{function:
	{name: VidyoLocalMonitorClearConstraints}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: void VidyoLocalMonitorClearConstraints(VidyoLocalMonitor* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
}
*/
void VidyoLocalMonitorClearConstraints(VidyoLocalMonitor* m);

/**
{function:
	{name: VidyoLocalMonitorSetBoundsConstraints}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorSetBoundsConstraints(VidyoLocalMonitor* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint maxWidth, LmiUint minWidth, LmiUint maxHeight, LmiUint minHeight)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
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
		{name: maxWidth}
		{description: }
	}
	{parameter:
		{name: minWidth}
		{description: }
	}
	{parameter:
		{name: maxHeight}
		{description: }
	}
	{parameter:
		{name: minHeight}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMonitorSetBoundsConstraints(VidyoLocalMonitor* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint maxWidth, LmiUint minWidth, LmiUint maxHeight, LmiUint minHeight);

/**
{function:
	{name: VidyoLocalMonitorSetDiscrerteConstraints}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorSetDiscrerteConstraints(VidyoLocalMonitor* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint width, LmiUint height, LmiFloat32 scaleFactor)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
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
		{name: width}
		{description: }
	}
	{parameter:
		{name: height}
		{description: }
	}
	{parameter:
		{name: scaleFactor}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMonitorSetDiscrerteConstraints(VidyoLocalMonitor* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint width, LmiUint height, LmiFloat32 scaleFactor);

/**
{function:
	{name: VidyoLocalMonitorAddToRemoteRenderer}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorAddToRemoteRenderer(VidyoLocalMonitor* m, const VidyoRemoteRenderer* remoteRenderer)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMonitorAddToRemoteRenderer(VidyoLocalMonitor* m, const VidyoRemoteRenderer* remoteRenderer);

/**
{function:
	{name: VidyoLocalMonitorRemoveFromRemoteRenderer}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorRemoveFromRemoteRenderer(VidyoLocalMonitor* m, const VidyoRemoteRenderer* remoteRenderer)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMonitorRemoveFromRemoteRenderer(VidyoLocalMonitor* m, const VidyoRemoteRenderer* remoteRenderer);

/**
{function:
	{name: VidyoLocalMonitorAddToLocalRenderer}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalMonitorAddToLocalRenderer(VidyoLocalMonitor* m, const VidyoLocalRenderer* renderer)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: renderer}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalMonitorAddToLocalRenderer(VidyoLocalMonitor* m, const VidyoLocalRenderer* renderer);

/**
{function:
	{name: VidyoLocalMonitorRemoveFromLocalRenderer}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: LmiBool VidyoLocalMonitorRemoveFromLocalRenderer(VidyoLocalMonitor* m, const VidyoLocalRenderer* renderer)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: renderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMonitorRemoveFromLocalRenderer(VidyoLocalMonitor* m, const VidyoLocalRenderer* renderer);

/**
{function:
	{name: VidyoLocalMonitorPrecludeWindow}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: void VidyoLocalMonitorPrecludeWindow(VidyoLocalMonitor* m, const VidyoLocalWindowShare* w)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMonitor object. }
	}
	{parameter:
		{name: w}
		{description: }
	}
}
*/
void VidyoLocalMonitorPrecludeWindow(VidyoLocalMonitor* m, const VidyoLocalWindowShare* w);

/**
{function visibility="private":
	{name: VidyoLocalMonitorConstructFromDevice}
	{parent: VidyoLocalMonitor}
	{description: }
	{prototype: VidyoLocalMonitor *VidyoLocalMonitorConstructFromDevice(VidyoLocalMonitor* vidyoLocalMonitor, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoLocalMonitor}
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
VidyoLocalMonitor *VidyoLocalMonitorConstructFromDevice(VidyoLocalMonitor* vidyoLocalMonitor, VidyoDevice *device, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoLocalMonitorGetStats}
	{parent: VidyoLocalMonitor}
	{description: Fill in stats data in VidyoLocalVideoSourceStats from a local monitor.}
	{prototype: LmiBool VidyoLocalMonitorGetStats(VidyoLocalMonitor *monitor, VidyoLocalVideoSourceStats *stats)}
	{parameter: {name: monitor} {description: The local monitor object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoLocalMonitorGetStats(VidyoLocalMonitor *monitor, VidyoLocalVideoSourceStats *stats);

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoLocalMonitorInline.h"
#endif

LMI_END_EXTERN_C

#endif /* VIDYO_LOCALMONITOR_H_ */
