/** 
{file:
	{name: VidyoLocalWindowShare.h}
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
#ifndef VIDYO_LOCALWINDOWSHARE_H_ 
#define VIDYO_LOCALWINDOWSHARE_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoLocalWindowShareImpl_;
typedef struct VidyoLocalWindowShareImpl_ VidyoLocalWindowShareImpl;
Declare_LmiSharedPtr(VidyoLocalWindowShareImpl)
Declare_LmiSharedPtrWrapper(VidyoLocalWindowShare, VidyoLocalWindowShareImpl)
Declare_LmiWeakPtrWrapper(VidyoLocalWindowShareHandle, VidyoLocalWindowShare, VidyoLocalWindowShareImpl)
Declare_LmiVector(VidyoLocalWindowShare)
Declare_LmiList(VidyoLocalWindowShare)

LMI_END_EXTERN_C

#include "VidyoLocalRenderer.h"
#include "VidyoRemoteRenderer.h"
#include "VidyoForwardDecl.h"
#include "VidyoEndpoint.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoLocalWindowShare}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoLocalWindowShare.h}
	{description: This object represents a window share on the local endpoint. }
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique ID.}
	}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name of the window share.}
	}
	{member:
		{name: applicationName}
		{type: LmiString}
		{description: Name of the application which owns the window. }
	}
}
*/

/**
{type apigroup="connector simple" visibility="private":
	{name: VidyoLocalWindowShareHandle}
	{parent: VidyoLocalWindowShare}
	{description: }
}
*/

/**
{type apigroup="connector simple":
	{name: VidyoLocalWindowShareState}
	{parent: VidyoLocalWindowShare}
	{description: State of the window share.}
	{value: {name: VIDYO_LOCALWINDOWSHARESTATE_Ok} {description: The window is visible and has been fully captured.}}
	{value: {name: VIDYO_LOCALWINDOWSHARESTATE_NotVisible} {description: The window exists but is not "visible".}}
	{value: {name: VIDYO_LOCALWINDOWSHARESTATE_Minimized} {description: The window is minimized and "visible" but its content may not be accessible.}}
	{value: {name: VIDYO_LOCALWINDOWSHARESTATE_Closed} {description: The window is closed and is no longer accessible.}}
	{value: {name: VIDYO_LOCALWINDOWSHARESTATE_MiscError} {description: Miscellaneous error has occured trying to capture the frame.}}
}
*/
typedef enum {
	VIDYO_LOCALWINDOWSHARESTATE_Ok,
	VIDYO_LOCALWINDOWSHARESTATE_NotVisible,
	VIDYO_LOCALWINDOWSHARESTATE_Minimized,
	VIDYO_LOCALWINDOWSHARESTATE_Closed,
	VIDYO_LOCALWINDOWSHARESTATE_MiscError
}
VidyoLocalWindowShareState;

/**
{callback visibility="private":
	{name: VidyoLocalWindowShareCallback}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void (*VidyoLocalWindowShareCallback)(const VidyoLocalWindowShare* w, const VidyoLmiVideoFrame* videoFrame, VidyoLocalWindowShareState state)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
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
typedef void (*VidyoLocalWindowShareCallback)(const VidyoLocalWindowShare* w, const VidyoLmiVideoFrame* videoFrame, VidyoLocalWindowShareState state);

/**
{callback visibility="private":
	{name: VidyoLocalWindowShareStartCallback}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void(*VidyoLocalWindowShareStartCallback)(const VidyoLocalWindowShare* w, LmiBool showCursor, LmiBool redactOccludedAreas, LmiTime frameInterval, LmiMediaFormat *mediaFormat, LmiVoidPtr userData)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: showCursor}
		{description: }
	}
	{parameter:
		{name: redactOccludedAreas}
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
typedef void(*VidyoLocalWindowShareStartCallback)(const VidyoLocalWindowShare* w, LmiBool showCursor, LmiBool redactOccludedAreas, LmiTime frameInterval, LmiMediaFormat *mediaFormat, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalWindowShareReconfigureCallback}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void(*VidyoLocalWindowShareReconfigureCallback)(const VidyoLocalWindowShare* w, LmiBool showCursor, LmiBool redactOccludedAreas, LmiTime frameInterval, const LmiMediaFormat *mediaFormat, LmiVoidPtr userData)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: showCursor}
		{description: }
	}
	{parameter:
		{name: redactOccludedAreas}
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
typedef void(*VidyoLocalWindowShareReconfigureCallback)(const VidyoLocalWindowShare* w, LmiBool showCursor, LmiBool redactOccludedAreas, LmiTime frameInterval, const LmiMediaFormat *mediaFormat, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalWindowShareGetPreviewFrameCallback}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool(*VidyoLocalWindowShareGetPreviewFrameCallback)(const VidyoLocalWindowShare* w, VidyoLocalWindowShareState* windowState, VidyoLmiVideoFrame* videoFrame)}
		{parameter:
			{name: w}
			{description: }
		}
		{parameter:
			{name: windowState}
			{description: }
		}
		{parameter:
			{name: videoFrame}
			{description: }
		}
		{return: LMI_TRUE on successfully getting the preview frame else LMI_FALSE}
	}
*/
typedef LmiBool(*VidyoLocalWindowShareGetPreviewFrameCallback)(const VidyoLocalWindowShare* w, VidyoLocalWindowShareState* windowState, VidyoLmiVideoFrame* videoFrame);

/**
{callback visibility="private":
	{name: VidyoLocalWindowShareGetWindowNameCallback}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool(*VidyoLocalWindowShareGetWindowNameCallback)(const VidyoLocalWindowShare* w, LmiString* windowName)}
		{parameter:
			{name: w}
			{description: }
		}
		{parameter:
			{name: windowName}
			{description: }
		}
		{return: LMI_TRUE on successfully getting the window name else LMI_FALSE}
}
*/
typedef LmiBool(*VidyoLocalWindowShareGetWindowNameCallback)(const VidyoLocalWindowShare* w, LmiString* windowName);

/**
{callback visibility="private":
	{name: VidyoLocalWindowShareStopCallback}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void(*VidyoLocalWindowShareStopCallback)(const VidyoLocalWindowShare* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void(*VidyoLocalWindowShareStopCallback)(const VidyoLocalWindowShare* c, LmiVoidPtr userData);

/**
{callback:
	{name: VidyoLocalWindowShareOnPreviewDataUriComplete}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void (*VidyoLocalWindowShareOnPreviewDataUriComplete)(const VidyoLocalWindowShare* w, const LmiString* videoFrame, VidyoLocalWindowShareState state)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
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
typedef void (*VidyoLocalWindowShareOnPreviewDataUriComplete)(const VidyoLocalWindowShare* w, const LmiString* videoFrame, VidyoLocalWindowShareState state);

/**
{callback:
	{name: VidyoLocalWindowShareOnApplicationIconDataUriComplete}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void (*VidyoLocalWindowShareOnApplicationIconDataUriComplete)(const VidyoLocalWindowShare* w, const LmiString* icon)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: icon}
		{description: }
	}
}
*/
typedef void (*VidyoLocalWindowShareOnApplicationIconDataUriComplete)(const VidyoLocalWindowShare* w, const LmiString* icon);

/**
{function visibility="private":
	{name: VidyoLocalWindowShareConstruct}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: VidyoLocalWindowShare* VidyoLocalWindowShareConstruct(VidyoLocalWindowShare* w, VidyoEndpoint *endpoint, const VidyoLmiWindowCapturer* windowCapturer, LmiAllocator* alloc)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: windowCapturer}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalWindowShare* VidyoLocalWindowShareConstruct(VidyoLocalWindowShare* w, VidyoEndpoint *endpoint, const VidyoLmiWindowCapturer* windowCapturer, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoLocalWindowShareConstructVirtual}
	{parent: VidyoLocalWindowShare}
	{description:}
	{prototype: VidyoLocalWindowShare* VidyoLocalWindowShareConstructVirtual(VidyoLocalWindowShare *w, VidyoEndpoint *endpoint, LmiString *id, LmiString *windowName, LmiString *applicationName, LmiUint processId, VidyoLocalWindowShareStartCallback onStart, VidyoLocalWindowShareReconfigureCallback onReconfigure, VidyoLocalWindowShareStopCallback onStop, VidyoLocalWindowShareGetPreviewFrameCallback onGetPreviewFrame, VidyoLocalWindowShareGetWindowNameCallback onGetWindowName, LmiVoidPtr virtualUserData, LmiAllocator *alloc)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
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
		{name: windowName}
		{description: }
	}
	{parameter:
		{name: applicationName}
		{description: }
	}
	{parameter:
		{name: processId}
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
		{name: onGetPreviewFrame}
		{description: }
	}
	{parameter:
		{name: onGetWindowName}
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
VidyoLocalWindowShare* VidyoLocalWindowShareConstructVirtual(VidyoLocalWindowShare *w, VidyoEndpoint *endpoint, LmiString *id, LmiString *windowName, LmiString *applicationName, LmiUint processId, VidyoLocalWindowShareStartCallback onStart, VidyoLocalWindowShareReconfigureCallback onReconfigure, VidyoLocalWindowShareStopCallback onStop, VidyoLocalWindowShareGetPreviewFrameCallback onGetPreviewFrame, VidyoLocalWindowShareGetWindowNameCallback onGetWindowName, LmiVoidPtr virtualUserData, LmiAllocator *alloc);

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareConstructCopy}
	{parent: VidyoLocalWindowShare}
	{description: Constructs an VidyoLocalWindowShare object as a copy of another.}
	{prototype: VidyoLocalWindowShare *VidyoLocalWindowShareConstructCopy(VidyoLocalWindowShare *obj, const VidyoLocalWindowShare *other)}
	{parameter: {name: obj} {description: The VidyoLocalWindowShare object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareDestruct}
	{parent: VidyoLocalWindowShare}
	{description: Destructs an VidyoLocalWindowShare object.}
	{prototype: void VidyoLocalWindowShareDestruct(VidyoLocalWindowShare *obj)}
	{parameter: {name: obj} {description: The VidyoLocalWindowShare object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalWindowShareAssign}
	{parent: VidyoLocalWindowShare}
	{description: Assigns one VidyoLocalWindowShare object the value of another. }
	{prototype: VidyoLocalWindowShare *VidyoLocalWindowShareAssign(VidyoLocalWindowShare *obj, const VidyoLocalWindowShare *other)}
	{parameter: {name: obj} {description: The VidyoLocalWindowShare object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalWindowShareCallbackFrame}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void VidyoLocalWindowShareCallbackFrame(VidyoLocalWindowShare *w, VidyoLocalWindowShareState windowState, const VidyoLmiVideoFrame* videoFrame)}
		{parameter:
			{name: w}
			{description: }
		}
		{parameter:
			{name: windowState}
			{description: }
		}
		{parameter:
			{name: videoFrame}
			{description: }
		}
}
*/
void VidyoLocalWindowShareCallbackFrame(VidyoLocalWindowShare *w, VidyoLocalWindowShareState windowState, const VidyoLmiVideoFrame* videoFrame);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalWindowShareGetHandle}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: VidyoLocalWindowShareHandle* VidyoLocalWindowShareGetHandle(VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: }
}
*/
VidyoLocalWindowShareHandle* VidyoLocalWindowShareGetHandle(VidyoLocalWindowShare* w);

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareGetApplicationName}
	{parent: VidyoLocalWindowShare}
	{description: Gets the name of the application which owns the window.}
	{prototype: const LmiString* VidyoLocalWindowShareGetApplicationName(const VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: }
}
*/
const LmiString* VidyoLocalWindowShareGetApplicationName(const VidyoLocalWindowShare* w);

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareIsApplicationNameSet}
	{parent: VidyoLocalWindowShare}
	{description: Checks if the name of the application name is set.}
	{prototype: LmiBool VidyoLocalWindowShareIsApplicationNameSet(const VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: LMI_TRUE when the applicaiton name is set, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoLocalWindowShareIsApplicationNameSet(const VidyoLocalWindowShare* w);

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareGetName}
	{parent: VidyoLocalWindowShare}
	{description: Gets the name of the window share.}
	{prototype: const LmiString* VidyoLocalWindowShareGetName(const VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: Name of the window share.}
}
*/
const LmiString* VidyoLocalWindowShareGetName(const VidyoLocalWindowShare* w);

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareIsNameSet}
	{parent: VidyoLocalWindowShare}
	{description: Checks if the name of the window share is set.}
	{prototype: LmiBool VidyoLocalWindowShareIsNameSet(const VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: LMI_TRUE when the window share name is set, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoLocalWindowShareIsNameSet(const VidyoLocalWindowShare* w);

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareGetId}
	{parent: VidyoLocalWindowShare}
	{description: Gets the unique ID of the window share.}
	{prototype: const LmiString* VidyoLocalWindowShareGetId(const VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: Unique ID of the window share.}
}
*/
const LmiString* VidyoLocalWindowShareGetId(const VidyoLocalWindowShare* w);

/**
{function apigroup="connector simple":
	{name: VidyoLocalWindowShareGetProcessId}
	{parent: VidyoLocalWindowShare}
	{description: Gets the ID of the process which owns the window share.}
	{prototype: LmiUint VidyoLocalWindowShareGetProcessId(VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: ID of the process which owns the window share.}
}
*/
LmiUint VidyoLocalWindowShareGetProcessId(VidyoLocalWindowShare* w);

/**
{function:
	{name: VidyoLocalWindowShareSetCapability}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareSetCapability(VidyoLocalWindowShare* w, LmiTime frameInterval, LmiBool showCursor, LmiBool redactOccludedAreas)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: frameInterval}
		{description: }
	}
	{parameter:
		{name: showCursor}
		{description: }
	}
	{parameter:
		{name: redactOccludedAreas}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalWindowShareSetCapability(VidyoLocalWindowShare* w, LmiTime frameInterval, LmiBool showCursor, LmiBool redactOccludedAreas);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalWindowShareSetUserData}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void VidyoLocalWindowShareSetUserData(VidyoLocalWindowShare* w, LmiVoidPtr userData)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoLocalWindowShareSetUserData(VidyoLocalWindowShare* w, LmiVoidPtr userData);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalWindowShareGetUserData}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalWindowShareGetUserData(const VidyoLocalWindowShare* w)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalWindowShareGetUserData(const VidyoLocalWindowShare* w);

/**
{function visibility="private":
	{name: VidyoLocalWindowShareSetCallback}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void VidyoLocalWindowShareSetCallback(VidyoLocalWindowShare* w, VidyoLocalWindowShareCallback callback)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoLocalWindowShareSetCallback(VidyoLocalWindowShare* w, VidyoLocalWindowShareCallback callback);

/**
{function visibility="private":
	{name: VidyoLocalWindowShareGetPreviewFrame}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: VidyoLocalWindowShareState VidyoLocalWindowShareGetPreviewFrame(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLmiVideoFrame *videoFrame)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
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
	{note: The videoFrame will only contain the new image if VidyoLocalWindowShareState VIDYO_LOCALWINDOWSHARESTATE_Ok, otherwise will will be assigned last valid preview image. }
}
*/
VidyoLocalWindowShareState VidyoLocalWindowShareGetPreviewFrame(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLmiVideoFrame *videoFrame);

/**
{function visibility="private":
	{name: VidyoLocalWindowShareGetPreviewFrameDataUri}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: VidyoLocalWindowShareState VidyoLocalWindowShareGetPreviewFrameDataUri(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, LmiString *videoFrame)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
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
	{note: The videoFrame will only contain the new image if VidyoLocalWindowShareState VIDYO_LOCALWINDOWSHARESTATE_Ok, otherwise will will be assigned last valid preview image. }
}
*/
VidyoLocalWindowShareState VidyoLocalWindowShareGetPreviewFrameDataUri(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, LmiString *videoFrame);


/**
{function visibility="private":
	{name: VidyoLocalWindowShareGetApplicationIconDataUri}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareGetApplicationIconDataUri(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, LmiString *icon)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
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
		{name: icon}
		{description: Icon to which the image will be assigned.}
	}
	{return: }
	{note: The aspect ratio will be preserved. }
	{note: The icon will only contain the new image if there is one that is less then maxWidth or maxHeight. }
}
*/
LmiBool VidyoLocalWindowShareGetApplicationIconDataUri(VidyoLocalWindowShare *w, LmiSizeT maxWidth, LmiSizeT maxHeight, LmiString *icon);

/**
{function:
	{name: VidyoLocalWindowShareGetPreviewFrameDataUriAsync}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareGetPreviewFrameDataUriAsync(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLocalWindowShareOnPreviewDataUriComplete onComplete)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
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
LmiBool VidyoLocalWindowShareGetPreviewFrameDataUriAsync(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLocalWindowShareOnPreviewDataUriComplete onComplete);

/**
{function:
	{name: VidyoLocalWindowShareGetApplicationIconFrameDataUriAsync}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareGetApplicationIconFrameDataUriAsync(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLocalWindowShareOnApplicationIconDataUriComplete onComplete)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: maxWidth}
		{description: Maximum width of the icon image.}
	}
	{parameter:
		{name: maxHeight}
		{description: Maximum height of the icon image.}
	}
	{parameter:
		{name: onComplete}
		{description: Callback that is triggered when a icon frame is captured.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoLocalWindowShareGetApplicationIconFrameDataUriAsync(VidyoLocalWindowShare* w, LmiSizeT maxWidth, LmiSizeT maxHeight, VidyoLocalWindowShareOnApplicationIconDataUriComplete onComplete);

/**
{function:
	{name: VidyoLocalWindowShareSetBoundsConstraints}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareSetBoundsConstraints(VidyoLocalWindowShare* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint maxWidth, LmiUint minWidth, LmiUint maxHeight, LmiUint minHeight)}
	{parameter:
		{name: m}
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
LmiBool VidyoLocalWindowShareSetBoundsConstraints(VidyoLocalWindowShare* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint maxWidth, LmiUint minWidth, LmiUint maxHeight, LmiUint minHeight);

/**
{function:
	{name: VidyoLocalWindowShareSetDiscrerteConstraints}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareSetDiscrerteConstraints(VidyoLocalWindowShare* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint width, LmiUint height, LmiFloat32 scaleFactor)}
	{parameter:
		{name: m}
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
LmiBool VidyoLocalWindowShareSetDiscrerteConstraints(VidyoLocalWindowShare* m, LmiTime maxFrameInterval, LmiTime minFrameInterval, LmiUint width, LmiUint height, LmiFloat32 scaleFactor);

/**
{function:
	{name: VidyoLocalWindowShareClearConstraints}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: void VidyoLocalWindowShareClearConstraints(VidyoLocalWindowShare* m)}
	{parameter:
		{name: m}
		{description: }
	}
}
*/
void VidyoLocalWindowShareClearConstraints(VidyoLocalWindowShare* m);

/**
{function:
	{name: VidyoLocalWindowShareAddToRemoteRenderer}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareAddToRemoteRenderer(VidyoLocalWindowShare* w, const VidyoRemoteRenderer* remoteRenderer)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalWindowShareAddToRemoteRenderer(VidyoLocalWindowShare* w, const VidyoRemoteRenderer* remoteRenderer);

/**
{function:
	{name: VidyoLocalWindowShareRemoveFromRemoteRenderer}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareRemoveFromRemoteRenderer(VidyoLocalWindowShare* w, const VidyoRemoteRenderer* remoteRenderer)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalWindowShareRemoveFromRemoteRenderer(VidyoLocalWindowShare* w, const VidyoRemoteRenderer* remoteRenderer);

/**
{function:
	{name: VidyoLocalWindowShareAddToLocalRenderer}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalWindowShareAddToLocalRenderer(VidyoLocalWindowShare* w, const VidyoLocalRenderer* renderer)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: renderer}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalWindowShareAddToLocalRenderer(VidyoLocalWindowShare* w, const VidyoLocalRenderer* renderer);

/**
{function:
	{name: VidyoLocalWindowShareRemoveFromLocalRenderer}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: LmiBool VidyoLocalWindowShareRemoveFromLocalRenderer(VidyoLocalWindowShare* w, const VidyoLocalRenderer* renderer)}
	{parameter:
		{name: w}
		{description: The VidyoLocalWindowShare object. }
	}
	{parameter:
		{name: renderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalWindowShareRemoveFromLocalRenderer(VidyoLocalWindowShare* w, const VidyoLocalRenderer* renderer);

/**
{function visibility="private":
	{name: VidyoLocalWindowShareConstructFromDevice}
	{parent: VidyoLocalWindowShare}
	{description: }
	{prototype: VidyoLocalWindowShare *VidyoLocalWindowShareConstructFromDevice(VidyoLocalWindowShare* vidyoLocalWindowShare, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoLocalWindowShare}
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
VidyoLocalWindowShare *VidyoLocalWindowShareConstructFromDevice(VidyoLocalWindowShare* vidyoLocalWindowShare, VidyoDevice *device, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoLocalWindowShareGetStats}
	{parent: VidyoLocalWindowShare}
	{description: Fill in stats data in VidyoLocalVideoSourceStats from a local window share.}
	{prototype: LmiBool VidyoLocalWindowShareGetStats(VidyoLocalWindowShare *windowShare, VidyoLocalVideoSourceStats *stats)}
	{parameter: {name: windowShare} {description: The local window share object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoLocalWindowShareGetStats(VidyoLocalWindowShare *windowShare, VidyoLocalVideoSourceStats *stats);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoLocalWindowShareInline.h"
#endif

#endif /* VIDYO_LOCALWINDOWSHARE_H_ */
