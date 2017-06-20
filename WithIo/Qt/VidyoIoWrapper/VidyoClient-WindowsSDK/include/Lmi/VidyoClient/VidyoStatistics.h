/** 
{file:
	{name: VidyoStatistics.h}
	{description: VidyoClient statistics. }
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
#ifndef VIDYO_CLIENTSTATISTICS_H_ 
#define VIDYO_CLIENTSTATISTICS_H_ 

#include <Lmi/Os/LmiTime.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include "VidyoMediaFormats.h"

LMI_BEGIN_EXTERN_C

/**
{package:
	{name: Stats}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoStatistics.h}
	{description: Statistics for VidyoClient}
}
*/

/**
{type apigroup="connector simple":
	{name: VidyoLocalRendererStats}
	{parent: Stats}
	{description: Statistics for a local renderer.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Id. }
	}
	{member:
		{name: width}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: height}
		{type: LmiSizeT}
		{description: Height. }
	}
	{member:
		{name: frameIntervalSet}
		{type: LmiTime}
		{description: Frame interval setting. }
	}
	{member:
		{name: frameIntervalMeasured}
		{type: LmiTime}
		{description: Frame interval measured by the renderer. }
	}
	{member:
		{name: totalFrames}
		{type: LmiUint}
		{description: Total frames rendered. }
	}
	{member:
		{name: totalPixels}
		{type: LmiUint}
		{description: Total pixels rendered. }
	}
	{member:
		{name: format}
		{type: VidyoMediaFormat}
		{description: Format. }
	}
}
*/
typedef struct {
	LmiString name;
	LmiString id;
	LmiSizeT width;
	LmiSizeT height;
	LmiTime frameIntervalSet;
	LmiTime frameIntervalMeasured;
	LmiUint totalFrames;
	LmiUint totalPixels;
	VidyoMediaFormat format;
} VidyoLocalRendererStats;

/**
{function visibility="private":
	{name: VidyoLocalRendererStatsConstructDefault}
	{parent: VidyoLocalRendererStats}
	{description: Constructs VidyoLocalRendererStats object.}
	{prototype: VidyoLocalRendererStats *VidyoLocalRendererStatsConstructDefault(VidyoLocalRendererStats *rendererStats, LmiAllocator *alloc)}
	{parameter: {name: rendererStats} {description: The VidyoLocalRendererStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoLocalRendererStats *VidyoLocalRendererStatsConstructDefault(VidyoLocalRendererStats *rendererStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoLocalRendererStatsConstructCopy}
	{parent: VidyoLocalRendererStats}
	{description: Constructs the VidyoLocalRendererStats object as a copy of another.}
	{prototype: VidyoLocalRendererStats *VidyoLocalRendererStatsConstructCopy(VidyoLocalRendererStats *obj, const VidyoLocalRendererStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalRendererStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalRendererStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoLocalRendererStats *VidyoLocalRendererStatsConstructCopy(VidyoLocalRendererStats *obj, const VidyoLocalRendererStats *other);

/**
{function visibility="private":
	{name: VidyoLocalRendererStatsDestruct}
	{parent: VidyoLocalRendererStats}
	{description: Destructs an VidyoLocalRendererStats object.}
	{prototype: void VidyoLocalRendererStatsDestruct(VidyoLocalRendererStats *rendererStats)}
	{parameter: {name: rendererStats} {description: The VidyoLocalRendererStats object to destruct.}}
}
*/
void VidyoLocalRendererStatsDestruct(VidyoLocalRendererStats *rendererStats);

/**
{function visibility="private":
	{name: VidyoLocalRendererStatsAssign}
	{parent: VidyoLocalRendererStats}
	{description: Assigns one VidyoLocalRendererStats object the value of another. }
	{prototype: VidyoLocalRendererStats *VidyoLocalRendererStatsAssign(VidyoLocalRendererStats *obj, const VidyoLocalRendererStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalRendererStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalRendererStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoLocalRendererStats *VidyoLocalRendererStatsAssign(VidyoLocalRendererStats *obj, const VidyoLocalRendererStats *other);

Declare_LmiVector(VidyoLocalRendererStats)

/**
{type apigroup="connector simple":
	{name: VidyoLocalRendererStreamStats}
	{parent: Stats}
	{description: Statistics for a local renderer.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Id. }
	}
	{member:
		{name: width}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: height}
		{type: LmiSizeT}
		{description: Height. }
	}
	{member:
		{name: bufferSize}
		{type: LmiUint}
		{description: Size of video buffer. }
	}
	{member:
		{name: bufferDropped}
		{type: LmiUint}
		{description: Dropped frames from video buffer. }
	}
}
*/
typedef struct {
	LmiString name;
	LmiString id;
	LmiSizeT width;
	LmiSizeT height;
	LmiUint bufferSize;
	LmiUint bufferDropped;
} VidyoLocalRendererStreamStats;

/**
{function visibility="private":
	{name: VidyoLocalRendererStreamStatsConstructDefault}
	{parent: VidyoLocalRendererStreamStats}
	{description: Constructs VidyoLocalRendererStreamStats object.}
	{prototype: VidyoLocalRendererStreamStats *VidyoLocalRendererStreamStatsConstructDefault(VidyoLocalRendererStreamStats *rendererStreamStats, LmiAllocator *alloc)}
	{parameter: {name: rendererStreamStats} {description: The VidyoLocalRendererStreamStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoLocalRendererStreamStats *VidyoLocalRendererStreamStatsConstructDefault(VidyoLocalRendererStreamStats *rendererStreamStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoLocalRendererStreamStatsConstructCopy}
	{parent: VidyoLocalRendererStreamStats}
	{description: Constructs the VidyoLocalRendererStreamStats object as a copy of another.}
	{prototype: VidyoLocalRendererStreamStats *VidyoLocalRendererStreamStatsConstructCopy(VidyoLocalRendererStreamStats *obj, const VidyoLocalRendererStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalRendererStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalRendererStreamStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoLocalRendererStreamStats *VidyoLocalRendererStreamStatsConstructCopy(VidyoLocalRendererStreamStats *obj, const VidyoLocalRendererStreamStats *other);

/**
{function visibility="private":
	{name: VidyoLocalRendererStreamStatsDestruct}
	{parent: VidyoLocalRendererStreamStats}
	{description: Destructs an VidyoLocalRendererStreamStats object.}
	{prototype: void VidyoLocalRendererStreamStatsDestruct(VidyoLocalRendererStreamStats *rendererStreamStats)}
	{parameter: {name: rendererStreamStats} {description: The VidyoLocalRendererStreamStats object to destruct.}}
}
*/
void VidyoLocalRendererStreamStatsDestruct(VidyoLocalRendererStreamStats *rendererStreamStats);

/**
{function visibility="private":
	{name: VidyoLocalRendererStreamStatsAssign}
	{parent: VidyoLocalRendererStreamStats}
	{description: Assigns one VidyoLocalRendererStreamStats object the value of another. }
	{prototype: VidyoLocalRendererStreamStats *VidyoLocalRendererStreamStatsAssign(VidyoLocalRendererStreamStats *obj, const VidyoLocalRendererStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalRendererStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalRendererStreamStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoLocalRendererStreamStats *VidyoLocalRendererStreamStatsAssign(VidyoLocalRendererStreamStats *obj, const VidyoLocalRendererStreamStats *other);

Declare_LmiVector(VidyoLocalRendererStreamStats)

/**
{type apigroup="connector simple":
	{name: VidyoRemoteRendererStreamStats}
	{parent: Stats}
	{description: Statistics for a remote renderer.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: width}
		{type: LmiSizeT}
		{description: Width determined by the operating point.}
	}
	{member:
		{name: height}
		{type: LmiSizeT}
		{description: Height determined by the operating point.}
	}
	{member:
		{name: fps}
		{type: LmiUint}
		{description: Frame rate determined by the operating point. }
	}
	{member:
		{name: fpsInput}
		{type: LmiUint}
		{description: Frame rate at encoder input. }
	}
	{member:
		{name: fpsSent}
		{type: LmiUint}
		{description: Frame rate at the encoder output. }
	}
	{member:
		{name: framesDropped}
		{type: LmiSizeT}
		{description: Number of frames dropped due to overconstraint or resizing errors. }
	}
	{member:
		{name: lastWidth}
		{type: LmiSizeT}
		{description: Width of the last frame received from the capturing device.}
	}
	{member:
		{name: lastHeight}
		{type: LmiSizeT}
		{description: Height of the last frame received from the capturing device.}
	}
	{member:
		{name: codecName}
		{type: LmiString}
		{description: Codec name.}
	}
	{member:
		{name: codecIFrames}
		{type: LmiUint}
		{description: Codec I frames. }
	}
	{member:
		{name: codecFir}
		{type: LmiUint}
		{description: Codec FIR. }
	}
	{member:
		{name: codecNacks}
		{type: LmiUint}
		{description: Codec nacks. }
	}
	{member:
		{name: codecLayers}
		{type: LmiUint}
		{description: Codec layers. }
	}
	{member:
		{name: sendNetworkBitRate}
		{type: LmiUint}
		{description: Send bitrate. }
	}
	{member:
		{name: sendNetworkRtt}
		{type: LmiTime}
		{description: Round trip time of send network. }
	}
}
*/
typedef struct {
	LmiString name;
    LmiSizeT width;
    LmiSizeT height;
    LmiUint fps;
    LmiUint fpsInput;
    LmiUint fpsSent;
    LmiSizeT framesDropped;
    LmiSizeT lastWidth;
    LmiSizeT lastHeight;

    LmiString codecName;
	LmiUint codecIFrames;
    LmiUint codecFir;
    LmiUint codecNacks;
    LmiUint codecLayers;

    LmiUint sendNetworkBitRate;
    LmiTime sendNetworkRtt;
} VidyoRemoteRendererStreamStats;

/**
{function visibility="private":
	{name: VidyoRemoteRendererStreamStatsConstructDefault}
	{parent: VidyoRemoteRendererStreamStats}
	{description: Constructs VidyoRemoteRendererStreamStats object.}
	{prototype: VidyoRemoteRendererStreamStats *VidyoRemoteRendererStreamStatsConstructDefault(VidyoRemoteRendererStreamStats *rendererStreamStats, LmiAllocator *alloc)}
	{parameter: {name: rendererStreamStats} {description: The VidyoRemoteRendererStreamStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteRendererStreamStats *VidyoRemoteRendererStreamStatsConstructDefault(VidyoRemoteRendererStreamStats *rendererStreamStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRemoteRendererStreamStatsConstructCopy}
	{parent: VidyoRemoteRendererStreamStats}
	{description: Constructs the VidyoRemoteRendererStreamStats object as a copy of another.}
	{prototype: VidyoRemoteRendererStreamStats *VidyoRemoteRendererStreamStatsConstructCopy(VidyoRemoteRendererStreamStats *obj, const VidyoRemoteRendererStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteRendererStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteRendererStreamStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteRendererStreamStats *VidyoRemoteRendererStreamStatsConstructCopy(VidyoRemoteRendererStreamStats *obj, const VidyoRemoteRendererStreamStats *other);

/**
{function visibility="private":
	{name: VidyoRemoteRendererStreamStatsDestruct}
	{parent: VidyoRemoteRendererStreamStats}
	{description: Destructs an VidyoRemoteRendererStreamStats object.}
	{prototype: void VidyoRemoteRendererStreamStatsDestruct(VidyoRemoteRendererStreamStats *rendererStreamStats)}
	{parameter: {name: rendererStreamStats} {description: The VidyoRemoteRendererStreamStats object to destruct.}}
}
*/
void VidyoRemoteRendererStreamStatsDestruct(VidyoRemoteRendererStreamStats *rendererStreamStats);

/**
{function visibility="private":
	{name: VidyoRemoteRendererStreamStatsAssign}
	{parent: VidyoRemoteRendererStreamStats}
	{description: Assigns one VidyoRemoteRendererStreamStats object the value of another. }
	{prototype: VidyoRemoteRendererStreamStats *VidyoRemoteRendererStreamStatsAssign(VidyoRemoteRendererStreamStats *obj, const VidyoRemoteRendererStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteRendererStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteRendererStreamStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRemoteRendererStreamStats *VidyoRemoteRendererStreamStatsAssign(VidyoRemoteRendererStreamStats *obj, const VidyoRemoteRendererStreamStats *other);

Declare_LmiVector(VidyoRemoteRendererStreamStats)

/**
{type apigroup="connector simple":
	{name: VidyoLocalVideoSourceStats}
	{parent: Stats}
	{description: Statistics for a local video source.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Id. }
	}
	{member:
		{name: width}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: height}
		{type: LmiSizeT}
		{description: Height.}
	}
	{member:
		{name: frameIntervalSet}
		{type: LmiTime}
		{description: Frame interval setting. }
	}
	{member:
		{name: frameIntervalMeasured}
		{type: LmiTime}
		{description: Frame interval measured between last 2 frames. }
	}
	{member:
		{name: totalFrames}
		{type: LmiUint}
		{description: Total frames. }
	}
	{member:
		{name: format}
		{type: VidyoMediaFormat}
		{description: Format. }
	}
	{member:
		{name: localRendererStreams}
		{type: LmiVector(VidyoLocalRendererStreamStats)}
		{description: Vector of stats of local renderer streams. }
	}
	{member:
		{name: remoteRendererStreams}
		{type: LmiVector(VidyoRemoteRendererStreamStats)}
		{description: Vector of stats of remote renderer streams. }
	}
}
*/
typedef struct {
	LmiString name;
	LmiString id;
    LmiSizeT width;
    LmiSizeT height;

    LmiTime frameIntervalSet;
	LmiTime frameIntervalMeasured;
	
    LmiUint totalFrames;
    VidyoMediaFormat format;

	LmiVector(VidyoLocalRendererStreamStats) localRendererStreams;
	LmiVector(VidyoRemoteRendererStreamStats) remoteRendererStreams;
} VidyoLocalVideoSourceStats;

/**
{function visibility="private":
	{name: VidyoLocalVideoSourceStatsConstructDefault}
	{parent: VidyoLocalVideoSourceStats}
	{description: Constructs VidyoLocalVideoSourceStats object.}
	{prototype: VidyoLocalVideoSourceStats *VidyoLocalVideoSourceStatsConstructDefault(VidyoLocalVideoSourceStats *videoSourceStats, LmiAllocator *alloc)}
	{parameter: {name: videoSourceStats} {description: The VidyoLocalVideoSourceStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoLocalVideoSourceStats *VidyoLocalVideoSourceStatsConstructDefault(VidyoLocalVideoSourceStats *videoSourceStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoLocalVideoSourceStatsConstructCopy}
	{parent: VidyoLocalVideoSourceStats}
	{description: Constructs the VidyoLocalVideoSourceStats object as a copy of another.}
	{prototype: VidyoLocalVideoSourceStats *VidyoLocalVideoSourceStatsConstructCopy(VidyoLocalVideoSourceStats *obj, const VidyoLocalVideoSourceStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalVideoSourceStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalVideoSourceStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoLocalVideoSourceStats *VidyoLocalVideoSourceStatsConstructCopy(VidyoLocalVideoSourceStats *obj, const VidyoLocalVideoSourceStats *other);

/**
{function visibility="private":
	{name: VidyoLocalVideoSourceStatsDestruct}
	{parent: VidyoLocalVideoSourceStats}
	{description: Destructs an VidyoLocalVideoSourceStats object.}
	{prototype: void VidyoLocalVideoSourceStatsDestruct(VidyoLocalVideoSourceStats *videoSourceStats)}
	{parameter: {name: videoSourceStats} {description: The VidyoLocalVideoSourceStats object to destruct.}}
}
*/
void VidyoLocalVideoSourceStatsDestruct(VidyoLocalVideoSourceStats *videoSourceStats);

/**
{function visibility="private":
	{name: VidyoLocalVideoSourceStatsAssign}
	{parent: VidyoLocalVideoSourceStats}
	{description: Assigns one VidyoLocalVideoSourceStats object the value of another. }
	{prototype: VidyoLocalVideoSourceStats *VidyoLocalVideoSourceStatsAssign(VidyoLocalVideoSourceStats *obj, const VidyoLocalVideoSourceStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalVideoSourceStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalVideoSourceStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoLocalVideoSourceStats *VidyoLocalVideoSourceStatsAssign(VidyoLocalVideoSourceStats *obj, const VidyoLocalVideoSourceStats *other);

Declare_LmiVector(VidyoLocalVideoSourceStats)

/**
{type apigroup="connector simple":
	{name: VidyoRemoteVideoSourceStats}
	{parent: Stats}
	{description: Statistics for a remote video source.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Id. }
	}
	{member:
		{name: width}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: height}
		{type: LmiSizeT}
		{description: Height.}
	}
	{member:
		{name: showState}
		{type: LmiString}
		{description: State of how the source is received from the server (on/off/auto).}
	}
	{member:
		{name: maxStreamWidth}
		{type: LmiUint}
		{description: Width.}
	}
	{member:
		{name: maxStreamHeight}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: maxStreamFrameRate}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: showWidth}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: showHeight}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: showFrameRate}
		{type: LmiUint}
		{description: Width.}
	}
	{member:
		{name: showPixelRate}
		{type: LmiUint}
		{description: Width.}
	}
	{member:
		{name: fpsDecoderInput}
		{type: LmiSizeT}
		{description: Frame rate at decoder input. }
	}
	{member:
		{name: fpsDecoded}
		{type: LmiSizeT}
		{description: Frame rate of decoder output. }
	}
	{member:
		{name: fpsRendered}
		{type: LmiSizeT}
		{description: Frame rate of renderer. }
	}
	{member:
		{name: codecName}
		{type: LmiString}
		{description: Codec name.}
	}
	{member:
		{name: codecIFrames}
		{type: LmiSizeT}
		{description: Codec I frames. }
	}
	{member:
		{name: codecFir}
		{type: LmiSizeT}
		{description: Codec FIR. }
	}
	{member:
		{name: codecNacks}
		{type: LmiSizeT}
		{description: Codec nacks. }
	}
	{member:
		{name: codecLayers}
		{type: LmiSizeT}
		{description: Codec layers. }
	}
	{member:
		{name: receiveNetworkPacketsLost}
		{type: LmiSizeT}
		{description: Number of lost packets. }
	}
	{member:
		{name: receiveNetworkPacketsConcealed}
		{type: LmiSizeT}
		{description: Number of packets concealed. }
	}
	{member:
		{name: receiveNetworkPacketsReordered}
		{type: LmiSizeT}
		{description: Number of packets reordered. }
	}
	{member:
		{name: receiveNetworkBitRate}
		{type: LmiSizeT}
		{description: Source bitrate. }
	}
	{member:
		{name: receiveNetworkRecoveredWithFec}
		{type: LmiSizeT}
		{description: Number of packets recovered with FEC. }
	}
	{member:
		{name: localRendererStreams}
		{type: LmiVector(VidyoLocalRendererStreamStats)}
		{description: Vector of stats of local renderer streams. }
	}
}
*/
typedef struct {
    LmiString name;
	LmiString id;
    LmiSizeT width;
    LmiSizeT height;
	LmiString showState;

	LmiSizeT maxStreamWidth;
	LmiSizeT maxStreamHeight;
	LmiUint maxStreamFrameRate;
	LmiSizeT showWidth;
	LmiSizeT showHeight;
	LmiUint showFrameRate;
	LmiUint64 showPixelRate;
	
    LmiSizeT fpsDecoderInput;
    LmiSizeT fpsDecoded;
    LmiSizeT fpsRendered;

    LmiString codecName;
	LmiSizeT codecIFrames;
    LmiSizeT codecFir;
    LmiSizeT codecNacks;
    LmiSizeT codecLayers;

    LmiSizeT receiveNetworkPacketsLost;
    LmiSizeT receiveNetworkPacketsConcealed;
    LmiSizeT receiveNetworkPacketsReordered;
    LmiSizeT receiveNetworkBitRate;
    LmiSizeT receiveNetworkRecoveredWithFec;

	LmiVector(VidyoLocalRendererStreamStats) localRendererStreams;
} VidyoRemoteVideoSourceStats;

/**
{function visibility="private":
	{name: VidyoRemoteVideoSourceStatsConstructDefault}
	{parent: VidyoRemoteVideoSourceStats}
	{description: Constructs VidyoRemoteVideoSourceStats object.}
	{prototype: VidyoRemoteVideoSourceStats *VidyoRemoteVideoSourceStatsConstructDefault(VidyoRemoteVideoSourceStats *cameraStats, LmiAllocator *alloc)}
	{parameter: {name: cameraStats} {description: The VidyoRemoteVideoSourceStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteVideoSourceStats *VidyoRemoteVideoSourceStatsConstructDefault(VidyoRemoteVideoSourceStats *cameraStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRemoteVideoSourceStatsConstructCopy}
	{parent: VidyoRemoteVideoSourceStats}
	{description: Constructs the VidyoRemoteVideoSourceStats object as a copy of another.}
	{prototype: VidyoRemoteVideoSourceStats *VidyoRemoteVideoSourceStatsConstructCopy(VidyoRemoteVideoSourceStats *obj, const VidyoRemoteVideoSourceStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteVideoSourceStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteVideoSourceStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteVideoSourceStats *VidyoRemoteVideoSourceStatsConstructCopy(VidyoRemoteVideoSourceStats *obj, const VidyoRemoteVideoSourceStats *other);

/**
{function visibility="private":
	{name: VidyoRemoteVideoSourceStatsDestruct}
	{parent: VidyoRemoteVideoSourceStats}
	{description: Destructs an VidyoRemoteVideoSourceStats object.}
	{prototype: void VidyoRemoteVideoSourceStatsDestruct(VidyoRemoteVideoSourceStats *speakerStreamStats)}
	{parameter: {name: speakerStreamStats} {description: The VidyoRemoteVideoSourceStats object to destruct.}}
}
*/
void VidyoRemoteVideoSourceStatsDestruct(VidyoRemoteVideoSourceStats *cameraStats);

/**
{function visibility="private":
	{name: VidyoRemoteVideoSourceStatsAssign}
	{parent: VidyoRemoteVideoSourceStats}
	{description: Assigns one VidyoRemoteVideoSourceStats object the value of another. }
	{prototype: VidyoRemoteVideoSourceStats *VidyoRemoteVideoSourceStatsAssign(VidyoRemoteVideoSourceStats *obj, const VidyoRemoteVideoSourceStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteVideoSourceStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteVideoSourceStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRemoteVideoSourceStats *VidyoRemoteVideoSourceStatsAssign(VidyoRemoteVideoSourceStats *obj, const VidyoRemoteVideoSourceStats *other);

Declare_LmiVector(VidyoRemoteVideoSourceStats)

/**
{type apigroup="connector simple":
	{name: VidyoLocalSpeakerStats}
	{parent: Stats}
	{description: Staticstics for a local speaker.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Id. }
	}
	{member:
		{name: sampleRateSet}
		{type: LmiUint}
		{description: Sample rate setting.}
	}
	{member:
		{name: sampleRateMeasured}
		{type: LmiUint}
		{description: Sample rate measured.}
	}
	{member:
		{name: bitsPerSample}
		{type: LmiUint}
		{description: Bits per sample. }
	}
	{member:
		{name: numberOfChannels}
		{type: LmiUint}
		{description: Number of channels. }
	}
	{member:
		{name: format}
		{type: VidyoMediaFormat}
		{description: Audio format. }
	}
}
*/
typedef struct {
    LmiString name;
	LmiString id;
	LmiUint sampleRateSet;
	LmiUint sampleRateMeasured;
    LmiUint bitsPerSample;
    LmiUint numberOfChannels;
	VidyoMediaFormat format;
} VidyoLocalSpeakerStats;

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStatsConstructDefault}
	{parent: VidyoLocalSpeakerStats}
	{description: Constructs VidyoLocalSpeakerStats object.}
	{prototype: VidyoLocalSpeakerStats *VidyoLocalSpeakerStatsConstructDefault(VidyoLocalSpeakerStats *speakerStats, LmiAllocator *alloc)}
	{parameter: {name: speakerStats} {description: The VidyoLocalSpeakerStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoLocalSpeakerStats *VidyoLocalSpeakerStatsConstructDefault(VidyoLocalSpeakerStats *speakerStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStatsConstructCopy}
	{parent: VidyoLocalSpeakerStats}
	{description: Constructs the VidyoLocalSpeakerStats object as a copy of another.}
	{prototype: VidyoLocalSpeakerStats *VidyoLocalSpeakerStatsConstructCopy(VidyoLocalSpeakerStats *obj, const VidyoLocalSpeakerStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalSpeakerStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalSpeakerStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoLocalSpeakerStats *VidyoLocalSpeakerStatsConstructCopy(VidyoLocalSpeakerStats *obj, const VidyoLocalSpeakerStats *other);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStatsDestruct}
	{parent: VidyoLocalSpeakerStats}
	{description: Destructs an VidyoLocalSpeakerStats object.}
	{prototype: void VidyoLocalSpeakerStatsDestruct(VidyoLocalSpeakerStats *speakerStats)}
	{parameter: {name: speakerStats} {description: The VidyoLocalSpeakerStats object to destruct.}}
}
*/
void VidyoLocalSpeakerStatsDestruct(VidyoLocalSpeakerStats *speakerStats);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStatsAssign}
	{parent: VidyoLocalSpeakerStats}
	{description: Assigns one VidyoLocalSpeakerStats object the value of another. }
	{prototype: VidyoLocalSpeakerStats *VidyoLocalSpeakerStatsAssign(VidyoLocalSpeakerStats *obj, const VidyoLocalSpeakerStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalSpeakerStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalSpeakerStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoLocalSpeakerStats *VidyoLocalSpeakerStatsAssign(VidyoLocalSpeakerStats *obj, const VidyoLocalSpeakerStats *other);

Declare_LmiVector(VidyoLocalSpeakerStats)

/**
{type apigroup="connector simple":
	{name: VidyoLocalSpeakerStreamStats}
	{parent: Stats}
	{description: Staticstics for a local speaker.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: sampleRate}
		{type: LmiUint}
		{description: Sample rate.}
	}
	{member:
		{name: bitsPerSample}
		{type: LmiUint}
		{description: Bits per sample. }
	}
	{member:
		{name: numberOfChannels}
		{type: LmiUint}
		{description: Number of channels. }
	}
	{member:
		{name: format}
		{type: VidyoMediaFormat}
		{description: Audio format. }
	}
	{member:
		{name: delay}
		{type: LmiTime}
		{description: Audio delay in the stream jitter buffer.}
	}
	{member:
		{name: lowestThreshold}
		{type: LmiTime}
		{description: Lowest threshold of stream jitter buffer under which the stream will be agressively padded to get into the proper range. }
	}
	{member:
		{name: lowThreshold}
		{type: LmiTime}
		{description: Low threshold of stream jitter buffer under which the stream will be gently padded to get into the proper range. }
	}
	{member:
		{name: highThreshold}
		{type: LmiTime}
		{description:  High threshold of stream jitter buffer over which the stream will be gently pared down to get into the proper range. }
	}
	{member:
		{name: highestThreshold}
		{type: LmiTime}
		{description:  Highest threshold of stream jitter buffer over which the stream will be agressively pared down to get into the proper range. }
	}
	{member:
		{name: maxThreshold}
		{type: LmiTime}
		{description:  Maximum threshold of stream jitter buffer over which the stream will be agressively pared down by dropping non-speech frames to get into the proper range. }
	}
	{member:
		{name: played}
		{type: LmiTime}
		{description: Ammount of audio played by the stream. }
	}
	{member:
		{name: underrun}
		{type: LmiTime}
		{description: Ammount of time stream was in the empty but active state. }
	}
	{member:
		{name: overrun}
		{type: LmiTime}
		{description: Ammount of time stream was over the maxThreshold. }
	}
	{member:
		{name: lastPlayed}
		{type: LmiTime}
		{description: Last time audio was played from the stream. }
	}
	{member:
		{name: lastEnergy}
		{type: LmiInt}
		{description: Last energy in dBFS of the stream. }
	}
}
*/
typedef struct {
    LmiString name;
	LmiUint sampleRate;
    LmiUint bitsPerSample;
    LmiUint numberOfChannels;
	VidyoMediaFormat format;

	LmiTime delay;

	LmiTime lowestThreshold;
	LmiTime lowThreshold;
	LmiTime highThreshold;
	LmiTime highestThreshold;
	LmiTime maxThreshold;

	LmiTime played;
	LmiTime underrun;
	LmiTime overrun;
	
	LmiTime lastPlayed;
	LmiInt lastEnergy;
} VidyoLocalSpeakerStreamStats;

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStreamStatsConstructDefault}
	{parent: VidyoLocalSpeakerStreamStats}
	{description: Constructs VidyoLocalSpeakerStreamStats object.}
	{prototype: VidyoLocalSpeakerStreamStats *VidyoLocalSpeakerStreamStatsConstructDefault(VidyoLocalSpeakerStreamStats *speakerStreamStats, LmiAllocator *alloc)}
	{parameter: {name: speakerStreamStats} {description: The VidyoLocalSpeakerStreamStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoLocalSpeakerStreamStats *VidyoLocalSpeakerStreamStatsConstructDefault(VidyoLocalSpeakerStreamStats *speakerStreamStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStreamStatsConstructCopy}
	{parent: VidyoLocalSpeakerStreamStats}
	{description: Constructs the VidyoLocalSpeakerStreamStats object as a copy of another.}
	{prototype: VidyoLocalSpeakerStreamStats *VidyoLocalSpeakerStreamStatsConstructCopy(VidyoLocalSpeakerStreamStats *obj, const VidyoLocalSpeakerStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalSpeakerStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalSpeakerStreamStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoLocalSpeakerStreamStats *VidyoLocalSpeakerStreamStatsConstructCopy(VidyoLocalSpeakerStreamStats *obj, const VidyoLocalSpeakerStreamStats *other);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStreamStatsDestruct}
	{parent: VidyoLocalSpeakerStreamStats}
	{description: Destructs an VidyoLocalSpeakerStreamStats object.}
	{prototype: void VidyoLocalSpeakerStreamStatsDestruct(VidyoLocalSpeakerStreamStats *speakerStreamStats)}
	{parameter: {name: speakerStreamStats} {description: The VidyoLocalSpeakerStreamStats object to destruct.}}
}
*/
void VidyoLocalSpeakerStreamStatsDestruct(VidyoLocalSpeakerStreamStats *speakerStreamStats);

/**
{function visibility="private":
	{name: VidyoLocalSpeakerStreamStatsAssign}
	{parent: VidyoLocalSpeakerStreamStats}
	{description: Assigns one VidyoLocalSpeakerStreamStats object the value of another. }
	{prototype: VidyoLocalSpeakerStreamStats *VidyoLocalSpeakerStreamStatsAssign(VidyoLocalSpeakerStreamStats *obj, const VidyoLocalSpeakerStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalSpeakerStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalSpeakerStreamStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoLocalSpeakerStreamStats *VidyoLocalSpeakerStreamStatsAssign(VidyoLocalSpeakerStreamStats *obj, const VidyoLocalSpeakerStreamStats *other);

Declare_LmiVector(VidyoLocalSpeakerStreamStats)

/**
{type apigroup="connector simple":
	{name: VidyoRemoteSpeakerStreamStats}
	{parent: Stats}
	{description: Staticstics for a remote speaker.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: sampleRate}
		{type: LmiUint}
		{description: Sample rate.}
	}
	{member:
		{name: bitsPerSample}
		{type: LmiUint}
		{description: Bits per sample. }
	}
	{member:
		{name: numberOfChannels}
		{type: LmiUint}
		{description: Number of channels. }
	}
	{member:
		{name: codecName}
		{type: LmiString}
		{description: Codec name.}
	}
	{member:
		{name: codecQualitySetting}
		{type: LmiUint}
		{description: Codec quality setting. }
	}
	{member:
		{name: codecDtx}
		{type: LmiUint}
		{description: Codec DTX. }
	}
	{member:
		{name: sendNetworkBitRate}
		{type: LmiUint}
		{description: Send bitrate. }
	}
	{member:
		{name: sendNetworkRtt}
		{type: LmiTime}
		{description: Round trip time of send network. }
	}
}
*/
typedef struct {
    LmiString name;
	LmiUint sampleRate;
    LmiUint bitsPerSample;
    LmiUint numberOfChannels;

	LmiString codecName;
	LmiUint codecQualitySetting;
    LmiUint codecDtx;

    LmiUint sendNetworkBitRate;
    LmiTime sendNetworkRtt;
} VidyoRemoteSpeakerStreamStats;

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerStreamStatsConstructDefault}
	{parent: VidyoRemoteSpeakerStreamStats}
	{description: Constructs VidyoRemoteSpeakerStreamStats object.}
	{prototype: VidyoRemoteSpeakerStreamStats *VidyoRemoteSpeakerStreamStatsConstructDefault(VidyoRemoteSpeakerStreamStats *speakerStreamStats, LmiAllocator *alloc)}
	{parameter: {name: speakerStreamStats} {description: The VidyoRemoteSpeakerStreamStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteSpeakerStreamStats *VidyoRemoteSpeakerStreamStatsConstructDefault(VidyoRemoteSpeakerStreamStats *speakerStreamStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerStreamStatsConstructCopy}
	{parent: VidyoRemoteSpeakerStreamStats}
	{description: Constructs the VidyoRemoteSpeakerStreamStats object as a copy of another.}
	{prototype: VidyoRemoteSpeakerStreamStats *VidyoRemoteSpeakerStreamStatsConstructCopy(VidyoRemoteSpeakerStreamStats *obj, const VidyoRemoteSpeakerStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteSpeakerStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteSpeakerStreamStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteSpeakerStreamStats *VidyoRemoteSpeakerStreamStatsConstructCopy(VidyoRemoteSpeakerStreamStats *obj, const VidyoRemoteSpeakerStreamStats *other);

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerStreamStatsDestruct}
	{parent: VidyoRemoteSpeakerStreamStats}
	{description: Destructs an VidyoRemoteSpeakerStreamStats object.}
	{prototype: void VidyoRemoteSpeakerStreamStatsDestruct(VidyoRemoteSpeakerStreamStats *speakerStreamStats)}
	{parameter: {name: speakerStreamStats} {description: The VidyoRemoteSpeakerStreamStats object to destruct.}}
}
*/
void VidyoRemoteSpeakerStreamStatsDestruct(VidyoRemoteSpeakerStreamStats *speakerStreamStats);

/**
{function visibility="private":
	{name: VidyoRemoteSpeakerStreamStatsAssign}
	{parent: VidyoRemoteSpeakerStreamStats}
	{description: Assigns one VidyoRemoteSpeakerStreamStats object the value of another. }
	{prototype: VidyoRemoteSpeakerStreamStats *VidyoRemoteSpeakerStreamStatsAssign(VidyoRemoteSpeakerStreamStats *obj, const VidyoRemoteSpeakerStreamStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteSpeakerStreamStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteSpeakerStreamStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRemoteSpeakerStreamStats *VidyoRemoteSpeakerStreamStatsAssign(VidyoRemoteSpeakerStreamStats *obj, const VidyoRemoteSpeakerStreamStats *other);

Declare_LmiVector(VidyoRemoteSpeakerStreamStats)

/**
{type apigroup="connector simple":
	{name: VidyoLocalMicrophoneStats}
	{parent: Stats}
	{description: Staticstics for a local microphone.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Id. }
	}
	{member:
		{name: sampleRateSet}
		{type: LmiUint}
		{description: Sample rate setting.}
	}
	{member:
		{name: sampleRateMeasured}
		{type: LmiUint}
		{description: Measured sample rate.}
	}
	{member:
		{name: bitsPerSample}
		{type: LmiUint}
		{description: Bits per sample. }
	}
	{member:
		{name: numberOfChannels}
		{type: LmiUint}
		{description: Number of channels. }
	}
	{member:
		{name: format}
		{type: VidyoMediaFormat}
		{description: Format. }
	}
	{member:
		{name: aecEchoCoupling}
		{type: LmiUint}
		{description: AEC echo coupling. }
	}
	{member:
		{name: agcAverageGain}
		{type: LmiUint}
		{description: AGC average gain. }
	}
	{member:
		{name: noiseSuppressionSnr}
		{type: LmiUint}
		{description: Noise suppression SNR. }
	}
	{member:
		{name: localSpeakerStreams}
		{type: LmiVector(VidyoLocalSpeakerStreamStats)}
		{description: Vector of stats of local speaker streams. }
	}
	{member:
		{name: remoteSpeakerStreams}
		{type: LmiVector(VidyoRemoteSpeakerStreamStats)}
		{description: Vector of stats of remote speaker streams. }
	}
}
*/
typedef struct {
    LmiString name;
	LmiString id;
	LmiUint sampleRateSet;
	LmiUint sampleRateMeasured;
    LmiUint bitsPerSample;
    LmiUint numberOfChannels;
    VidyoMediaFormat format;

	LmiUint aecEchoCoupling;
	LmiUint agcAverageGain;
    LmiUint noiseSuppressionSnr;

	LmiVector(VidyoLocalSpeakerStreamStats) localSpeakerStreams;
	LmiVector(VidyoRemoteSpeakerStreamStats) remoteSpeakerStreams;
} VidyoLocalMicrophoneStats;

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneStatsConstructDefault}
	{parent: VidyoLocalMicrophoneStats}
	{description: Constructs VidyoLocalMicrophoneStats object.}
	{prototype: VidyoLocalMicrophoneStats *VidyoLocalMicrophoneStatsConstructDefault(VidyoLocalMicrophoneStats *microphoneStats, LmiAllocator *alloc)}
	{parameter: {name: microphoneStats} {description: The VidyoLocalMicrophoneStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoLocalMicrophoneStats *VidyoLocalMicrophoneStatsConstructDefault(VidyoLocalMicrophoneStats *microphoneStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneStatsConstructCopy}
	{parent: VidyoLocalMicrophoneStats}
	{description: Constructs the VidyoLocalMicrophoneStats object as a copy of another.}
	{prototype: VidyoLocalMicrophoneStats *VidyoLocalMicrophoneStatsConstructCopy(VidyoLocalMicrophoneStats *obj, const VidyoLocalMicrophoneStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalMicrophoneStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalMicrophoneStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoLocalMicrophoneStats *VidyoLocalMicrophoneStatsConstructCopy(VidyoLocalMicrophoneStats *obj, const VidyoLocalMicrophoneStats *other);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneStatsDestruct}
	{parent: VidyoLocalMicrophoneStats}
	{description: Destructs an VidyoLocalMicrophoneStats object.}
	{prototype: void VidyoLocalMicrophoneStatsDestruct(VidyoLocalMicrophoneStats *microphoneStats)}
	{parameter: {name: microphoneStats} {description: The VidyoLocalMicrophoneStats object to destruct.}}
}
*/
void VidyoLocalMicrophoneStatsDestruct(VidyoLocalMicrophoneStats *microphoneStats);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneStatsAssign}
	{parent: VidyoLocalMicrophoneStats}
	{description: Assigns one VidyoLocalMicrophoneStats object the value of another. }
	{prototype: VidyoLocalMicrophoneStats *VidyoLocalMicrophoneStatsAssign(VidyoLocalMicrophoneStats *obj, const VidyoLocalMicrophoneStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoLocalMicrophoneStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoLocalMicrophoneStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoLocalMicrophoneStats *VidyoLocalMicrophoneStatsAssign(VidyoLocalMicrophoneStats *obj, const VidyoLocalMicrophoneStats *other);

Declare_LmiVector(VidyoLocalMicrophoneStats)

/**
{type apigroup="connector simple":
	{name: VidyoRemoteMicrophoneStats}
	{parent: Stats}
	{description: Staticstics for a remote microphone.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Id. }
	}
	{member:
		{name: sampleRateSet}
		{type: LmiUint}
		{description: Sample rate setting.}
	}
	{member:
		{name: sampleRateMeasured}
		{type: LmiUint}
		{description: Measured sample rate.}
	}
	{member:
		{name: bitsPerSample}
		{type: LmiUint}
		{description: Bits per sample. }
	}
	{member:
		{name: numberOfChannels}
		{type: LmiUint}
		{description: Number of channels. }
	}
	{member:
		{name: codecName}
		{type: LmiString}
		{description: Codec name.}
	}
	{member:
		{name: codecQualitySetting}
		{type: LmiUint}
		{description: Codec quality setting. }
	}
	{member:
		{name: codecDtx}
		{type: LmiUint}
		{description: Codec DTX. }
	}
	{member:
		{name: receiveNetworkBitRate}
		{type: LmiSizeT}
		{description: Bandwidth of receive network. }
	}
	{member:
		{name: receiveNetworkJitter}
		{type: LmiUint}
		{description: Jitter in receive network. }
	}
	{member:
		{name: receiveNetworkDroppedPackets}
		{type: LmiUint}
		{description: Dropped packets in receive network. }
	}
	{member:
		{name: receiveNetworkDelay}
		{type: LmiTime}
		{description: Delay in receive netowrk. }
	}
	{member:
		{name: localSpeakerStreams}
		{type: LmiVector(VidyoLocalSpeakerStreamStats)}
		{description: Vector of stats of local speaker streams. }
	}
}
*/
typedef struct {
    LmiString name;
	LmiString id;
	LmiUint sampleRateSet;
	LmiUint sampleRateMeasured;
    LmiUint bitsPerSample;
    LmiUint numberOfChannels;

	LmiString codecName;
	LmiUint codecQualitySetting;
    LmiUint codecDtx;

    LmiSizeT receiveNetworkBitRate;
    LmiUint receiveNetworkJitter;
    LmiUint receiveNetworkDroppedPackets;
    LmiTime receiveNetworkDelay;

	LmiVector(VidyoLocalSpeakerStreamStats) localSpeakerStreams;
} VidyoRemoteMicrophoneStats;

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneStatsConstructDefault}
	{parent: VidyoRemoteMicrophoneStats}
	{description: Constructs VidyoRemoteMicrophoneStats object.}
	{prototype: VidyoRemoteMicrophoneStats *VidyoRemoteMicrophoneStatsConstructDefault(VidyoRemoteMicrophoneStats *microphoneStats, LmiAllocator *alloc)}
	{parameter: {name: microphoneStats} {description: The VidyoRemoteMicrophoneStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteMicrophoneStats *VidyoRemoteMicrophoneStatsConstructDefault(VidyoRemoteMicrophoneStats *microphoneStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneStatsConstructCopy}
	{parent: VidyoRemoteMicrophoneStats}
	{description: Constructs the VidyoRemoteMicrophoneStats object as a copy of another.}
	{prototype: VidyoRemoteMicrophoneStats *VidyoRemoteMicrophoneStatsConstructCopy(VidyoRemoteMicrophoneStats *obj, const VidyoRemoteMicrophoneStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteMicrophoneStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteMicrophoneStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoRemoteMicrophoneStats *VidyoRemoteMicrophoneStatsConstructCopy(VidyoRemoteMicrophoneStats *obj, const VidyoRemoteMicrophoneStats *other);

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneStatsDestruct}
	{parent: VidyoRemoteMicrophoneStats}
	{description: Destructs an VidyoRemoteMicrophoneStats object.}
	{prototype: void VidyoRemoteMicrophoneStatsDestruct(VidyoRemoteMicrophoneStats *microphoneStats)}
	{parameter: {name: microphoneStats} {description: The VidyoRemoteMicrophoneStats object to destruct.}}
}
*/
void VidyoRemoteMicrophoneStatsDestruct(VidyoRemoteMicrophoneStats *microphoneStats);

/**
{function visibility="private":
	{name: VidyoRemoteMicrophoneStatsAssign}
	{parent: VidyoRemoteMicrophoneStats}
	{description: Assigns one VidyoRemoteMicrophoneStats object the value of another. }
	{prototype: VidyoRemoteMicrophoneStats *VidyoRemoteMicrophoneStatsAssign(VidyoRemoteMicrophoneStats *obj, const VidyoRemoteMicrophoneStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRemoteMicrophoneStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRemoteMicrophoneStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRemoteMicrophoneStats *VidyoRemoteMicrophoneStatsAssign(VidyoRemoteMicrophoneStats *obj, const VidyoRemoteMicrophoneStats *other);

Declare_LmiVector(VidyoRemoteMicrophoneStats)

/**
{type apigroup="connector simple":
	{name: VidyoParticipantStats}
	{parent: Stats}
	{description: Staticstics for a room.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Current CPU usage. }
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Participant ID.}
	}
	{member:
		{name: userId}
		{type: LmiString}
		{description: ID assosicated with the VidyoUser of that participant.}
	}
	{member:
		{name: remoteCameraStats}
		{type: LmiVector(VidyoRemoteVideoSourceStats)}
		{description: Vector of stats of cameras. }
	}
	{member:
		{name: remoteMicrophoneStats}
		{type: LmiVector(VidyoRemoteMicrophoneStats)}
		{description: Vector of stats of microphones. }
	}
	{member:
		{name: remoteWindowShareStats}
		{type: LmiVector(VidyoRemoteVideoSourceStats)}
		{description: Vector of stats of speakers. }
	}
}
*/
typedef struct {
	LmiString name;
	LmiString id;
	LmiString userId;
	
	LmiVector(VidyoRemoteVideoSourceStats) remoteCameraStats;
	LmiVector(VidyoRemoteMicrophoneStats) remoteMicrophoneStats;
	LmiVector(VidyoRemoteVideoSourceStats) remoteWindowShareStats;
} VidyoParticipantStats;

/**
{function visibility="private":
	{name: VidyoParticipantStatsConstructDefault}
	{parent: VidyoParticipantStats}
	{description: Constructs VidyoParticipantStats object.}
	{prototype: VidyoParticipantStats *VidyoParticipantStatsConstructDefault(VidyoParticipantStats *roomStats, LmiAllocator *alloc)}
	{parameter: {name: roomStats} {description: The VidyoParticipantStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoParticipantStats *VidyoParticipantStatsConstructDefault(VidyoParticipantStats *roomStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoParticipantStatsConstructCopy}
	{parent: VidyoParticipantStats}
	{description: Constructs the VidyoParticipantStats object as a copy of another.}
	{prototype: VidyoParticipantStats *VidyoParticipantStatsConstructCopy(VidyoParticipantStats *obj, const VidyoParticipantStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoParticipantStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoParticipantStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoParticipantStats *VidyoParticipantStatsConstructCopy(VidyoParticipantStats *obj, const VidyoParticipantStats *other);

/**
{function visibility="private":
	{name: VidyoParticipantStatsDestruct}
	{parent: VidyoParticipantStats}
	{description: Destructs an VidyoParticipantStats object.}
	{prototype: void VidyoParticipantStatsDestruct(VidyoParticipantStats *roomStats)}
	{parameter: {name: roomStats} {description: The VidyoParticipantStats object to destruct.}}
}
*/
void VidyoParticipantStatsDestruct(VidyoParticipantStats *roomStats);

/**
{function visibility="private":
	{name: VidyoParticipantStatsAssign}
	{parent: VidyoParticipantStats}
	{description: Assigns one VidyoParticipantStats object the value of another. }
	{prototype: VidyoParticipantStats *VidyoParticipantStatsAssign(VidyoParticipantStats *obj, const VidyoParticipantStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoParticipantStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoParticipantStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoParticipantStats *VidyoParticipantStatsAssign(VidyoParticipantStats *obj, const VidyoParticipantStats *other);

Declare_LmiVector(VidyoParticipantStats)

/**
{type apigroup="connector simple":
	{name: VidyoRateShaperStats}
	{parent: Stats}
	{description: Staticstics for an endpoint rate shaper.}
	{member:
		{name: delayNormal}
		{type: LmiUint}
		{description: Normal delay.}
	}
	{member:
		{name: packetsNormal}
		{type: LmiUint}
		{description: Normal packets. }
	}
	{member:
		{name: dropNormal}
		{type: LmiUint}
		{description: Dropped normal. }
	}
	{member:
		{name: delayRetransmit}
		{type: LmiUint}
		{description: Retransmit delay. }
	}
	{member:
		{name: packetsRetransmit}
		{type: LmiUint}
		{description: Retransmitted packets. }
	}
}
*/
typedef struct {
    LmiUint delayNormal;
    LmiUint packetsNormal;
    LmiUint dropNormal;

    LmiUint delayRetransmit;
    LmiUint packetsRetransmit;
} VidyoRateShaperStats;

/**
{function visibility="private":
	{name: VidyoRateShaperStatsConstructDefault}
	{parent: VidyoRateShaperStats}
	{description: Constructs VidyoRateShaperStats object.}
	{prototype: VidyoRateShaperStats *VidyoRateShaperStatsConstructDefault(VidyoRateShaperStats *rateShaperStats, LmiAllocator *alloc)}
	{parameter: {name: rateShaperStats} {description: The VidyoRateShaperStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRateShaperStats *VidyoRateShaperStatsConstructDefault(VidyoRateShaperStats *rateShaperStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRateShaperStatsConstructCopy}
	{parent: VidyoRateShaperStats}
	{description: Constructs the VidyoRateShaperStats object as a copy of another.}
	{prototype: VidyoRateShaperStats *VidyoRateShaperStatsConstructCopy(VidyoRateShaperStats *obj, const VidyoRateShaperStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRateShaperStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRateShaperStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoRateShaperStats *VidyoRateShaperStatsConstructCopy(VidyoRateShaperStats *obj, const VidyoRateShaperStats *other);

/**
{function visibility="private":
	{name: VidyoRateShaperStatsDestruct}
	{parent: VidyoRateShaperStats}
	{description: Destructs an VidyoRateShaperStats object.}
	{prototype: void VidyoRateShaperStatsDestruct(VidyoRateShaperStats *rateShaperStats)}
	{parameter: {name: rateShaperStats} {description: The VidyoRateShaperStats object to destruct.}}
}
*/
void VidyoRateShaperStatsDestruct(VidyoRateShaperStats *rateShaperStats);

/**
{function visibility="private":
	{name: VidyoRateShaperStatsAssign}
	{parent: VidyoRateShaperStats}
	{description: Assigns one VidyoRateShaperStats object the value of another. }
	{prototype: VidyoRateShaperStats *VidyoRateShaperStatsAssign(VidyoRateShaperStats *obj, const VidyoRateShaperStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRateShaperStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRateShaperStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRateShaperStats *VidyoRateShaperStatsAssign(VidyoRateShaperStats *obj, const VidyoRateShaperStats *other);

/**
{type apigroup="connector simple":
	{name: VidyoBandwidthSummaryStats}
	{parent: Stats}
	{description: Staticstics for an endpoint rate shaper.}
	{member:
		{name: availableBandwidth}
		{type: LmiUint}
		{description: Available bandwidth.}
	}
	{member:
		{name: targetEncoderBitRate}
		{type: LmiUint}
		{description: Target encoder bitrate. }
	}
	{member:
		{name: actualEncoderBitRate}
		{type: LmiUint}
		{description: Actual encoder bitrate. }
	}
	{member:
		{name: retransmitBitRate}
		{type: LmiUint}
		{description: Bitrate used for retransmission. }
	}
	{member:
		{name: totalTransmitBitRate}
		{type: LmiUint}
		{description: Total transmit bitrate. }
	}
	{member:
		{name: leakyBucketDelay}
		{type: LmiUint}
		{description: Leaky bucket delay. }
	}
}
*/
typedef struct {
	LmiSizeT availableBandwidth;
	LmiSizeT targetEncoderBitRate;
	LmiSizeT actualEncoderBitRate;
	LmiSizeT retransmitBitRate;
	LmiSizeT totalTransmitBitRate;
	LmiSizeT leakyBucketDelay;
} VidyoBandwidthSummaryStats;

/**
{function visibility="private":
	{name: VidyoBandwidthSummaryStatsConstructDefault}
	{parent: VidyoBandwidthSummaryStats}
	{description: Constructs VidyoBandwidthSummaryStats object.}
	{prototype: VidyoBandwidthSummaryStats *VidyoBandwidthSummaryStatsConstructDefault(VidyoBandwidthSummaryStats *bandwidthSummaryStats, LmiAllocator *alloc)}
	{parameter: {name: bandwidthSummaryStats} {description: The VidyoBandwidthSummaryStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoBandwidthSummaryStats *VidyoBandwidthSummaryStatsConstructDefault(VidyoBandwidthSummaryStats *bandwidthSummaryStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoBandwidthSummaryStatsConstructCopy}
	{parent: VidyoBandwidthSummaryStats}
	{description: Constructs the VidyoBandwidthSummaryStats object as a copy of another.}
	{prototype: VidyoBandwidthSummaryStats *VidyoBandwidthSummaryStatsConstructCopy(VidyoBandwidthSummaryStats *obj, const VidyoBandwidthSummaryStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoBandwidthSummaryStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoBandwidthSummaryStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoBandwidthSummaryStats *VidyoBandwidthSummaryStatsConstructCopy(VidyoBandwidthSummaryStats *obj, const VidyoBandwidthSummaryStats *other);

/**
{function visibility="private":
	{name: VidyoBandwidthSummaryStatsDestruct}
	{parent: VidyoBandwidthSummaryStats}
	{description: Destructs an VidyoBandwidthSummaryStats object.}
	{prototype: void VidyoBandwidthSummaryStatsDestruct(VidyoBandwidthSummaryStats *bandwidthSummaryStats)}
	{parameter: {name: bandwidthSummaryStats} {description: The VidyoBandwidthSummaryStats object to destruct.}}
}
*/
void VidyoBandwidthSummaryStatsDestruct(VidyoBandwidthSummaryStats *bandwidthSummaryStats);

/**
{function visibility="private":
	{name: VidyoBandwidthSummaryStatsAssign}
	{parent: VidyoBandwidthSummaryStats}
	{description: Assigns one VidyoBandwidthSummaryStats object the value of another. }
	{prototype: VidyoBandwidthSummaryStats *VidyoBandwidthSummaryStatsAssign(VidyoBandwidthSummaryStats *obj, const VidyoBandwidthSummaryStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoBandwidthSummaryStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoBandwidthSummaryStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoBandwidthSummaryStats *VidyoBandwidthSummaryStatsAssign(VidyoBandwidthSummaryStats *obj, const VidyoBandwidthSummaryStats *other);

/**
{type apigroup="connector simple":
	{name: VidyoNetworkInterfaceStats}
	{parent: Stats}
	{description: Staticstics for a network interface.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Interface name.}
	}
	{member:
		{name: type}
		{type: LmiString}
		{description: Interface type such as wifi or wired. }
	}
	{member:
		{name: isUp}
		{type: LmiBool}
		{description: State of the interface. }
	}
}
*/
typedef struct {
	LmiString name;
	LmiString type;
	LmiBool isUp;
} VidyoNetworkInterfaceStats;

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceStatsConstructDefault}
	{parent: VidyoNetworkInterfaceStats}
	{description: Constructs VidyoNetworkInterfaceStats object.}
	{prototype: VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsConstructDefault(VidyoNetworkInterfaceStats *networkInterfaceStats, LmiAllocator *alloc)}
	{parameter: {name: networkInterfaceStats} {description: The VidyoNetworkInterfaceStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsConstructDefault(VidyoNetworkInterfaceStats *networkInterfaceStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceStatsConstruct}
	{parent: VidyoNetworkInterfaceStats}
	{description: Constructs VidyoNetworkInterfaceStats object.}
	{prototype: VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsConstruct(VidyoNetworkInterfaceStats *networkInterfaceStats, const char* name, const char* type, LmiBool isUp, LmiAllocator *alloc)}
	{parameter: {name: networkInterfaceStats} {description: The VidyoNetworkInterfaceStats object to construct.}}
	{parameter: {name: name} {description: Name of the interface.}}
	{parameter: {name: type} {description: Type of the interface.}}
	{parameter: {name: isUp} {description: Interface state.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsConstruct(VidyoNetworkInterfaceStats *networkInterfaceStats, const char* name, const char* type, LmiBool isUp, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceStatsConstructCopy}
	{parent: VidyoNetworkInterfaceStats}
	{description: Constructs the VidyoNetworkInterfaceStats object as a copy of another.}
	{prototype: VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsConstructCopy(VidyoNetworkInterfaceStats *obj, const VidyoNetworkInterfaceStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoNetworkInterfaceStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoNetworkInterfaceStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsConstructCopy(VidyoNetworkInterfaceStats *obj, const VidyoNetworkInterfaceStats *other);

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceStatsDestruct}
	{parent: VidyoNetworkInterfaceStats}
	{description: Destructs an VidyoNetworkInterfaceStats object.}
	{prototype: void VidyoNetworkInterfaceStatsDestruct(VidyoNetworkInterfaceStats *networkInterfaceStats)}
	{parameter: {name: networkInterfaceStats} {description: The VidyoNetworkInterfaceStats object to destruct.}}
}
*/
void VidyoNetworkInterfaceStatsDestruct(VidyoNetworkInterfaceStats *networkInterfaceStats);

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceStatsAssign}
	{parent: VidyoNetworkInterfaceStats}
	{description: Assigns one VidyoNetworkInterfaceStats object the value of another. }
	{prototype: VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsAssign(VidyoNetworkInterfaceStats *obj, const VidyoNetworkInterfaceStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoNetworkInterfaceStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoNetworkInterfaceStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoNetworkInterfaceStats *VidyoNetworkInterfaceStatsAssign(VidyoNetworkInterfaceStats *obj, const VidyoNetworkInterfaceStats *other);

Declare_LmiVector(VidyoNetworkInterfaceStats)

/**
{type apigroup="connector simple":
	{name: VidyoParticipantGenerationStats}
	{parent: Stats}
	{description: Staticstics for a participnat generation, ordered list of dynamic participants.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Participant name.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Participant id. }
	}
	{member:
		{name: cameraName}
		{type: LmiString}
		{description: Camera name.}
	}
	{member:
		{name: cameraId}
		{type: LmiString}
		{description: Camera id. }
	}
	{member:
		{name: width}
		{type: LmiSizeT}
		{description: Width.}
	}
	{member:
		{name: height}
		{type: LmiSizeT}
		{description: Height. }
	}
	{member:
		{name: frameInterval}
		{type: LmiTime}
		{description: Frame interval setting. }
	}
	{member:
		{name: pixelRate}
		{type: LmiUint64}
		{description: Pixel rate to ask for. }
	}
	{member:
		{name: enabled}
		{type: LmiBool}
		{description: State of the generation. }
	}
}
*/
typedef struct {
	LmiString name;
	LmiString id;
	LmiString cameraName;
	LmiString cameraId;
	LmiSizeT width;
	LmiSizeT height;
	LmiTime frameInterval;
	LmiUint64 pixelRate;
	LmiBool enabled;
} VidyoParticipantGenerationStats;

/**
{function visibility="private":
	{name: VidyoParticipantGenerationStatsConstructDefault}
	{parent: VidyoParticipantGenerationStats}
	{description: Constructs VidyoParticipantGenerationStats object.}
	{prototype: VidyoParticipantGenerationStats *VidyoParticipantGenerationStatsConstructDefault(VidyoParticipantGenerationStats *participantGenerationStats, LmiAllocator *alloc)}
	{parameter: {name: participantGenerationStats} {description: The VidyoParticipantGenerationStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoParticipantGenerationStats *VidyoParticipantGenerationStatsConstructDefault(VidyoParticipantGenerationStats *participantGenerationStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoParticipantGenerationStatsConstructCopy}
	{parent: VidyoParticipantGenerationStats}
	{description: Constructs the VidyoParticipantGenerationStats object as a copy of another.}
	{prototype: VidyoParticipantGenerationStats *VidyoParticipantGenerationStatsConstructCopy(VidyoParticipantGenerationStats *obj, const VidyoParticipantGenerationStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoParticipantGenerationStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoParticipantGenerationStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoParticipantGenerationStats *VidyoParticipantGenerationStatsConstructCopy(VidyoParticipantGenerationStats *obj, const VidyoParticipantGenerationStats *other);

/**
{function visibility="private":
	{name: VidyoParticipantGenerationStatsDestruct}
	{parent: VidyoParticipantGenerationStats}
	{description: Destructs an VidyoParticipantGenerationStats object.}
	{prototype: void VidyoParticipantGenerationStatsDestruct(VidyoParticipantGenerationStats *participantGenerationStats)}
	{parameter: {name: participantGenerationStats} {description: The VidyoParticipantGenerationStats object to destruct.}}
}
*/
void VidyoParticipantGenerationStatsDestruct(VidyoParticipantGenerationStats *participantGenerationStats);

/**
{function visibility="private":
	{name: VidyoParticipantGenerationStatsAssign}
	{parent: VidyoParticipantGenerationStats}
	{description: Assigns one VidyoParticipantGenerationStats object the value of another. }
	{prototype: VidyoParticipantGenerationStats *VidyoParticipantGenerationStatsAssign(VidyoParticipantGenerationStats *obj, const VidyoParticipantGenerationStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoParticipantGenerationStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoParticipantGenerationStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoParticipantGenerationStats *VidyoParticipantGenerationStatsAssign(VidyoParticipantGenerationStats *obj, const VidyoParticipantGenerationStats *other);

Declare_LmiVector(VidyoParticipantGenerationStats)

/**
 {type apigroup="connector simple":
	{name: VidyoMediaConnectionTransportInfo}
	{parent: Stats}
	{description: Information about media connection transport.}
	{member:
		{name: connectionId}
		{type: LmiUint}
		{description: Connection ID.}
	}
	{member:
		{name: componentType}
		{type: LmiString}
		{description: Transport component type. }
	}
	{member:
		{name: connectionType}
		{type: LmiString}
		{description: Transport connection type.}
	}
	{member:
		{name: internalLocalAddr}
		{type: LmiString}
		{description: Internal local address.}
	}
	{member:
		{name: internalRemoteAddr}
		{type: LmiString}
		{description: Internal remote address. }
	}
	{member:
		{name: externalLocalAddr}
		{type: LmiString}
		{description: External local address. }
	}
	{member:
		{name: externalRemoteAddr}
		{type: LmiString}
		{description: External remote address. }
	}
	{member:
		{name: interfaceName}
		{type: LmiString}
		{description: Interface name. }
	}
	{member:
		{name: interfaceType}
		{type: LmiString}
		{description: Interface type. }
	}
	{member:
		{name: addressType}
		{type: LmiString}
		{description: Address type. }
	}
	{member:
		{name: transportPlugIn}
		{type: LmiString}
		{description: Transport plugin. }
	}
 }
 */
typedef struct {
	LmiUint connectionId;
	LmiString componentType;
	LmiString connectionType;
	LmiString internalLocalAddr;
	LmiString internalRemoteAddr;
	LmiString externalLocalAddr;
	LmiString externalRemoteAddr;
	LmiString interfaceName;
	LmiString interfaceType;
	LmiString addressType;
	LmiString transportPlugIn;
} VidyoMediaConnectionTransportInfo;

/**
 {function visibility="private":
	{name: VidyoMediaConnectionTransportInfoConstructDefault}
	{parent: VidyoMediaConnectionTransportInfo}
	{description: Constructs VidyoMediaConnectionTransportInfo object.}
	{prototype: VidyoMediaConnectionTransportInfo *VidyoMediaConnectionTransportInfoConstructDefault(VidyoMediaConnectionTransportInfo *transportInfo, LmiAllocator *alloc)}
	{parameter: {name: transportInfo} {description: The VidyoMediaConnectionTransportInfo object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
 }
 */
VidyoMediaConnectionTransportInfo *VidyoMediaConnectionTransportInfoConstructDefault(VidyoMediaConnectionTransportInfo *transportInfo, LmiAllocator *alloc);

/**
 {function visibility="private":
	{name: VidyoMediaConnectionTransportInfoConstructCopy}
	{parent: VidyoMediaConnectionTransportInfo}
	{description: Constructs the VidyoMediaConnectionTransportInfo object as a copy of another.}
	{prototype: VidyoMediaConnectionTransportInfo *VidyoMediaConnectionTransportInfoConstructCopy(VidyoMediaConnectionTransportInfo *obj, const VidyoMediaConnectionTransportInfo *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoMediaConnectionTransportInfo object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoMediaConnectionTransportInfo object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
 }
 */
VidyoMediaConnectionTransportInfo *VidyoMediaConnectionTransportInfoConstructCopy(VidyoMediaConnectionTransportInfo *obj, const VidyoMediaConnectionTransportInfo *other);

/**
 {function visibility="private":
	{name: VidyoMediaConnectionTransportInfoDestruct}
	{parent: VidyoMediaConnectionTransportInfo}
	{description: Destructs an VidyoMediaConnectionTransportInfo object.}
	{prototype: void VidyoMediaConnectionTransportInfoDestruct(VidyoMediaConnectionTransportInfo *transportInfo)}
	{parameter: {name: transportInfo} {description: The VidyoMediaConnectionTransportInfo object to destruct.}}
 }
 */
void VidyoMediaConnectionTransportInfoDestruct(VidyoMediaConnectionTransportInfo *transportInfo);

/**
 {function visibility="private":
	{name: VidyoMediaConnectionTransportInfoAssign}
	{parent: VidyoMediaConnectionTransportInfo}
	{description: Assigns one VidyoMediaConnectionTransportInfo object the value of another. }
	{prototype: VidyoMediaConnectionTransportInfo *VidyoMediaConnectionTransportInfoAssign(VidyoMediaConnectionTransportInfo *obj, const VidyoMediaConnectionTransportInfo *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoMediaConnectionTransportInfo object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoMediaConnectionTransportInfo object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
 }
 */
VidyoMediaConnectionTransportInfo *VidyoMediaConnectionTransportInfoAssign(VidyoMediaConnectionTransportInfo *obj, const VidyoMediaConnectionTransportInfo *other);

Declare_LmiVector(VidyoMediaConnectionTransportInfo)

/**
{type apigroup="connector simple":
	{name: VidyoRoomStats}
	{parent: Stats}
	{description: Staticstics for a room.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Room ID.}
	}
	{member:
		{name: cpuUsage}
		{type: LmiUint}
		{description: Current CPU usage. }
	}
	{member:
		{name: maxEncodePixelRate}
		{type: LmiUint64}
		{description: Max encode pixel rate. }
	}
	{member:
		{name: currentCpuEncodePixelRate}
		{type: LmiUint64}
		{description: Current CPU encode pixel rate. }
	}
	{member:
		{name: currentBandwidthEncodePixelRate}
		{type: LmiUint64}
		{description: Current Bandwidth encode pixel rate. }
	}
	{member:
		{name: maxDecodePixelRate}
		{type: LmiUint64}
		{description: Max decode pixel rate. }
	}
	{member:
		{name: currentCpuDecodePixelRate}
		{type: LmiUint64}
		{description: Current CPU decode pixel rate. }
	}
	{member:
		{name: currentBandwidthDecodePixelRate}
		{type: LmiUint64}
		{description: Current Bandwidth decode pixel rate. }
	}
	{member:
		{name: sendBitRateTotal}
		{type: LmiUint64}
		{description: Available ABA send bandwidth. }
	}
	{member:
		{name: sendBitRateAvailable}
		{type: LmiUint64}
		{description: Actual ABA send bandwidth. }
	}
	{member:
		{name: receiveBitRateTotal}
		{type: LmiUint64}
		{description: Available ABA receive bandwidth. }
	}
	{member:
		{name: receiveBitRateAvailable}
		{type: LmiUint64}
		{description: Actual ABA receive bandwidth. }
	}
	{member:
		{name: maxVideoSources}
		{type: LmiUint}
		{description: Maximum video sources allowed based on the minimum of configured and constrained by resource manager. }
	}
	{member:
		{name: staticSources}
		{type: LmiUint}
		{description: Current ammount of static sources shown. }
	}
	{member:
		{name: bandwidthAudio}
		{type: VidyoBandwidthSummaryStats}
		{description: Bandwidth summary statistics of audio content. }
	}
	{member:
		{name: bandwidthVideo}
		{type: VidyoBandwidthSummaryStats}
		{description: Bandwidth summary statistics of video content. }
	}
	{member:
		{name: bandwidthApp}
		{type: VidyoBandwidthSummaryStats}
		{description: Bandwidth summary statistics of application content. }
	}
	{member:
		{name: rateShaperAudio}
		{type: VidyoRateShaperStats}
		{description: Rate shaper statistics of audio content. }
	}
	{member:
		{name: rateShaperVideo}
		{type: VidyoRateShaperStats}
		{description: Rate shaper statistics of video content. }
	}
	{member:
		{name: rateShaperApp}
		{type: VidyoRateShaperStats}
		{description: Rate shaper statistics of application content. }
	}
	{member:
		{name: participantStats}
		{type: LmiVector(VidyoParticipantStats)}
		{description: Vector of stats of participants. }
	}
	{member:
		{name: participantGenerationStats}
		{type: LmiVector(VidyoParticipantGenerationStats)}
		{description: Ordered list of generations (selected participants). }
	}
	{member:
		{name: reflectorId}
		{type: LmiString}
		{description: ID of the refector to which the media conneciton is established. }
	}
	{member:
		{name: conferenceId}
		{type: LmiString}
		{description: ID conference on the reflector associated with this VidyoRoom. }
	}
	{member:
		{name: transportInformation}
		{type: LmiVector(VidyoMediaConnectionTransportInfo)}
		{description: Vector of media transport information. }
	}
}
*/
typedef struct {
	LmiString id;
	LmiUint cpuUsage;
	LmiUint64 maxEncodePixelRate;
	LmiUint64 currentCpuEncodePixelRate;
	LmiUint64 currentBandwidthEncodePixelRate;
	LmiUint64 maxDecodePixelRate;
	LmiUint64 currentCpuDecodePixelRate;
	LmiUint64 currentBandwidthDecodePixelRate;
	LmiUint64 sendBitRateTotal;
    LmiUint64 sendBitRateAvailable;
	LmiUint64 receiveBitRateTotal;
    LmiUint64 receiveBitRateAvailable;
	
	LmiUint maxVideoSources;
	LmiUint staticSources;
	
	VidyoBandwidthSummaryStats bandwidthAudio;
	VidyoBandwidthSummaryStats bandwidthVideo;
	VidyoBandwidthSummaryStats bandwidthApp;
	
	VidyoRateShaperStats rateShaperAudio;
	VidyoRateShaperStats rateShaperVideo;
	VidyoRateShaperStats rateShaperApp;
	
	LmiVector(VidyoParticipantStats) participantStats;
	LmiVector(VidyoParticipantGenerationStats) participantGenerationStats;
	
	LmiString reflectorId;
	LmiString conferenceId;
	
	LmiVector(VidyoMediaConnectionTransportInfo) transportInformation;
} VidyoRoomStats;

/**
{function visibility="private":
	{name: VidyoRoomStatsConstructDefault}
	{parent: VidyoRoomStats}
	{description: Constructs VidyoRoomStats object.}
	{prototype: VidyoRoomStats *VidyoRoomStatsConstructDefault(VidyoRoomStats *roomStats, LmiAllocator *alloc)}
	{parameter: {name: roomStats} {description: The VidyoRoomStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomStats *VidyoRoomStatsConstructDefault(VidyoRoomStats *roomStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRoomStatsConstructCopy}
	{parent: VidyoRoomStats}
	{description: Constructs the VidyoRoomStats object as a copy of another.}
	{prototype: VidyoRoomStats *VidyoRoomStatsConstructCopy(VidyoRoomStats *obj, const VidyoRoomStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRoomStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRoomStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoRoomStats *VidyoRoomStatsConstructCopy(VidyoRoomStats *obj, const VidyoRoomStats *other);

/**
{function visibility="private":
	{name: VidyoRoomStatsDestruct}
	{parent: VidyoRoomStats}
	{description: Destructs an VidyoRoomStats object.}
	{prototype: void VidyoRoomStatsDestruct(VidyoRoomStats *roomStats)}
	{parameter: {name: roomStats} {description: The VidyoRoomStats object to destruct.}}
}
*/
void VidyoRoomStatsDestruct(VidyoRoomStats *roomStats);

/**
{function visibility="private":
	{name: VidyoRoomStatsAssign}
	{parent: VidyoRoomStats}
	{description: Assigns one VidyoRoomStats object the value of another. }
	{prototype: VidyoRoomStats *VidyoRoomStatsAssign(VidyoRoomStats *obj, const VidyoRoomStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoRoomStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoRoomStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRoomStats *VidyoRoomStatsAssign(VidyoRoomStats *obj, const VidyoRoomStats *other);

Declare_LmiVector(VidyoRoomStats)

/**
{type apigroup="connector simple":
	{name: VidyoUserStats}
	{parent: Stats}
	{description: Statistics for an user.}
	{member:
		{name: id}
		{type: LmiString}
		{description: User ID.}
	}
	{member:
		{name: serviceType}
		{type: LmiString}
		{description: Login service type.}
	}
	{member:
		{name: host}
		{type: LmiString}
		{description: Login host.}
	}
	{member:
		{name: port}
		{type: LmiUint}
		{description: Login Port.}
	}
	{member:
		{name: roomStats}
		{type: LmiVector(VidyoRoomStats)}
		{description: Vector of stats of rooms. }
	}
}
*/
typedef struct {
	LmiString id;
	LmiString serviceType;
	LmiString host;
	LmiUint port;
	LmiVector(VidyoRoomStats) roomStats;
} VidyoUserStats;

/**
{function visibility="private":
	{name: VidyoUserStatsConstructDefault}
	{parent: VidyoUserStats}
	{description: Constructs VidyoUserStats object.}
	{prototype: VidyoUserStats *VidyoUserStatsConstructDefault(VidyoUserStats *userStats, LmiAllocator *alloc)}
	{parameter: {name: userStats} {description: The VidyoUserStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoUserStats *VidyoUserStatsConstructDefault(VidyoUserStats *userStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoUserStatsConstructCopy}
	{parent: VidyoUserStats}
	{description: Constructs the VidyoUserStats object as a copy of another.}
	{prototype: VidyoUserStats *VidyoUserStatsConstructCopy(VidyoUserStats *obj, const VidyoUserStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoUserStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoUserStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoUserStats *VidyoUserStatsConstructCopy(VidyoUserStats *obj, const VidyoUserStats *other);

/**
{function visibility="private":
	{name: VidyoUserStatsDestruct}
	{parent: VidyoUserStats}
	{description: Destructs an VidyoUserStats object.}
	{prototype: void VidyoUserStatsDestruct(VidyoUserStats *userStats)}
	{parameter: {name: userStats} {description: The VidyoUserStats object to destruct.}}
}
*/
void VidyoUserStatsDestruct(VidyoUserStats *userStats);

/**
{function visibility="private":
	{name: VidyoUserStatsAssign}
	{parent: VidyoUserStats}
	{description: Assigns one VidyoUserStats object the value of another. }
	{prototype: VidyoUserStats *VidyoUserStatsAssign(VidyoUserStats *obj, const VidyoUserStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoUserStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoUserStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoUserStats *VidyoUserStatsAssign(VidyoUserStats *obj, const VidyoUserStats *other);

Declare_LmiVector(VidyoUserStats)

/**
{type apigroup="connector simple":
	{name: VidyoEndpointStats}
	{parent: Stats}
	{description: Statistics for an endpoint.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Room ID.}
	}
	{member:
		{name: timeStamp}
		{type: LmiString}
		{description: Gregorian Timestamp when the stats were measured.}
	}
	{member:
		{name: applicationTag}
		{type: LmiString}
		{description: Tag set by the application.}
	}
	{member:
		{name: libraryVersion}
		{type: LmiString}
		{description: Version of the library.}
	}
	{member:
		{name: buildTag}
		{type: LmiString}
		{description: Tag from the build system.}
	}
	{member:
		{name: osName}
		{type: LmiString}
		{description: Name of the operating system.}
	}
	{member:
		{name: osVersion}
		{type: LmiString}
		{description: Version of the operating system.}
	}
	{member:
		{name: processorBrand}
		{type: LmiString}
		{description: CPU brand.}
	}
	{member:
		{name: processorModel}
		{type: LmiString}
		{description: CPU Model.}
	}
	{member:
		{name: processorSpeed}
		{type: LmiUint}
		{description: CPU frequency, in MHz.}
	}
	{member:
		{name: processorPhysicalCores}
		{type: LmiUint}
		{description: Number of physical cores in the CPU (ignoring hyperthreading).}
	}
	{member:
		{name: processorLogicalCores}
		{type: LmiUint}
		{description: Number of logical cores in the CPU (including hyperthreading).}
	}
	{member:
		{name: networkInterfaceStats}
		{type: LmiVector(VidyoNetworkInterfaceStats)}
		{description: Network interfaces on the endpoint. }
	}
	{member:
		{name: userStats}
		{type: LmiVector(VidyoUserStats)}
		{description: Vector of stats of users. }
	}
	{member:
		{name: localCameraStats}
		{type: LmiVector(VidyoLocalVideoSourceStats)}
		{description: Vector of stats of cameras. }
	}
	{member:
		{name: localMicrophoneStats}
		{type: LmiVector(VidyoLocalMicrophoneStats)}
		{description: Vector of stats of microphones. }
	}
	{member:
		{name: localSpeakerStats}
		{type: LmiVector(VidyoLocalSpeakerStats)}
		{description: Vector of stats of speakers. }
	}
	{member:
		{name: localRendererStats}
		{type: LmiVector(VidyoLocalRendererStats)}
		{description: Vector of stats of renderers. }
	}
	{member:
		{name: localWindowShareStats}
		{type: LmiVector(VidyoLocalVideoSourceStats)}
		{description: Vector of stats of window shares. }
	}
	{member:
		{name: localMonitorStats}
		{type: LmiVector(VidyoLocalVideoSourceStats)}
		{description: Vector of stats of monitors. }
	}
}
*/
typedef struct {
	LmiString id;
	LmiString timeStamp;
	LmiString applicationTag;
	LmiString libraryVersion;
	LmiString buildTag;
	LmiString osName;
	LmiString osVersion;
	LmiString processorBrand;
	LmiString processorModel;
	LmiUint processorSpeed;
	LmiUint processorPhysicalCores;
	LmiUint processorLogicalCores;
	LmiVector(VidyoNetworkInterfaceStats) networkInterfaceStats;
	LmiVector(VidyoUserStats) userStats;
	
	LmiVector(VidyoLocalVideoSourceStats) localCameraStats;
	LmiVector(VidyoLocalMicrophoneStats) localMicrophoneStats;
	LmiVector(VidyoLocalSpeakerStats) localSpeakerStats;
	LmiVector(VidyoLocalRendererStats) localRendererStats;
	LmiVector(VidyoLocalVideoSourceStats) localWindowShareStats;
	LmiVector(VidyoLocalVideoSourceStats) localMonitorStats;
} VidyoEndpointStats;

/**
{function visibility="private":
	{name: VidyoEndpointStatsConstructDefault}
	{parent: VidyoEndpointStats}
	{description: Constructs VidyoEndpointStats object.}
	{prototype: VidyoEndpointStats *VidyoEndpointStatsConstructDefault(VidyoEndpointStats *endpointStats, LmiAllocator *alloc)}
	{parameter: {name: endpointStats} {description: The VidyoEndpointStats object to construct.}}
	{parameter: {name: alloc} {description: Allocator.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoEndpointStats *VidyoEndpointStatsConstructDefault(VidyoEndpointStats *endpointStats, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoEndpointStatsConstructCopy}
	{parent: VidyoEndpointStats}
	{description: Constructs the VidyoEndpointStats object as a copy of another.}
	{prototype: VidyoEndpointStats *VidyoEndpointStatsConstructCopy(VidyoEndpointStats *obj, const VidyoEndpointStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoEndpointStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoEndpointStats object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/
VidyoEndpointStats *VidyoEndpointStatsConstructCopy(VidyoEndpointStats *obj, const VidyoEndpointStats *other);

/**
{function visibility="private":
	{name: VidyoEndpointStatsDestruct}
	{parent: VidyoEndpointStats}
	{description: Destructs an VidyoEndpointStats object.}
	{prototype: void VidyoEndpointStatsDestruct(VidyoEndpointStats *endpointStats)}
	{parameter: {name: endpointStats} {description: The VidyoEndpointStats object to destruct.}}
}
*/
void VidyoEndpointStatsDestruct(VidyoEndpointStats *endpointStats);

/**
{function visibility="private":
	{name: VidyoEndpointStatsAssign}
	{parent: VidyoEndpointStats}
	{description: Assigns one VidyoEndpointStats object the value of another. }
	{prototype: VidyoEndpointStats *VidyoEndpointStatsAssign(VidyoEndpointStats *obj, const VidyoEndpointStats *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoEndpointStats object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoEndpointStats object to assign from.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoEndpointStats *VidyoEndpointStatsAssign(VidyoEndpointStats *obj, const VidyoEndpointStats *other);

LMI_END_EXTERN_C

#endif /* VIDYO_CLIENTSTATISTICS_H_ */
