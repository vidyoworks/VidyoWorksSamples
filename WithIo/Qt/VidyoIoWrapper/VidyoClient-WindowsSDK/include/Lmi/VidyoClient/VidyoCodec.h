/** 
{file:
	{name: VidyoCodec.h}
	{description: High level client library. }
	{copyright:
		(c) 2013-2015 Vidyo, Inc.,
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
#ifndef VIDYO_CODEC_H_ 
#define VIDYO_CODEC_H_ 

#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiMisc.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiProperty.h>
#include <Lmi/Os/LmiSharedPtr.h>

#include "VidyoForwardDecl.h"

LMI_BEGIN_EXTERN_C

struct VidyoCodecVideoImpl_;
typedef struct VidyoCodecVideoImpl_ VidyoCodecVideoImpl;
Declare_LmiSharedPtr(VidyoCodecVideoImpl)
Declare_LmiSharedPtrWrapper(VidyoCodecVideo, VidyoCodecVideoImpl)
Declare_LmiVector(VidyoCodecVideo)

/**
{type visibility="private" reference-counted="yes":
	{name: VidyoCodecVideo}
	{parent: Endpoint}
	{description: }
	{member:
		{name: id}
		{type: LmiString}
		{description: }
	}
	{member:
		{name: mimeType}
		{type: LmiString}
		{description: }
	}
	{member:
		{name: clockRate}
		{type: LmiUint}
		{description: }
	}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecVideoConstruct}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: VidyoCodecVideo* VidyoCodecVideoConstruct(VidyoCodecVideo* c, const char* mimeType, VidyoLmiEncoderPlugIn* encoderPlugIn, void* encoderPlugInData, VidyoLmiDecoderPlugIn* decoderPlugIn, void* decoderPlugInData, LmiVector(LmiProperty)* properties, LmiUint clockRate, LmiAllocator* alloc)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: mimeType}
		{description: }
	}
	{parameter:
		{name: encoderPlugIn}
		{description: }
	}
	{parameter:
		{name: encoderPlugInData}
		{description: }
	}
	{parameter:
		{name: decoderPlugIn}
		{description: }
	}
	{parameter:
		{name: decoderPlugInData}
		{description: }
	}
	{parameter:
		{name: properties}
		{description: }
	}
	{parameter:
		{name: clockRate}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoCodecVideo* VidyoCodecVideoConstruct(VidyoCodecVideo* c, const char* mimeType, VidyoLmiEncoderPlugIn* encoderPlugIn, void* encoderPlugInData, VidyoLmiDecoderPlugIn* decoderPlugIn, void* decoderPlugInData, LmiVector(LmiProperty)* properties, LmiUint clockRate, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoCodecVideoConstructCopy}
	{parent: VidyoCodecVideo}
	{description: Constructs an VidyoCodecVideo object as a copy of another.}
	{prototype: VidyoCodecVideo *VidyoCodecVideoConstructCopy(VidyoCodecVideo *obj, const VidyoCodecVideo *other)}
	{parameter: {name: obj} {description: The VidyoCodecVideo object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecVideoDestruct}
	{parent: VidyoCodecVideo}
	{description: Destructs an VidyoCodecVideo object.}
	{prototype: void VidyoCodecVideoDestruct(VidyoCodecVideo *obj)}
	{parameter: {name: obj} {description: The VidyoCodecVideo object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecVideoAssign}
	{parent: VidyoCodecVideo}
	{description: Assigns one VidyoCodecVideo object the value of another. }
	{prototype: VidyoCodecVideo *VidyoCodecVideoAssign(VidyoCodecVideo *obj, const VidyoCodecVideo *other)}
	{parameter: {name: obj} {description: The VidyoCodecVideo object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecVideoGetId}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: LmiString* VidyoCodecVideoGetId(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiString* VidyoCodecVideoGetId(VidyoCodecVideo* c);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetDebugString}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: LmiString* VidyoCodecVideoGetDebugString(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiString* VidyoCodecVideoGetDebugString(VidyoCodecVideo* c);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetMimeType}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: const char* VidyoCodecVideoGetMimeType(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
const char* VidyoCodecVideoGetMimeType(VidyoCodecVideo* c);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetEncoderPlugIn}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: VidyoLmiEncoderPlugIn* VidyoCodecVideoGetEncoderPlugIn(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
VidyoLmiEncoderPlugIn* VidyoCodecVideoGetEncoderPlugIn(VidyoCodecVideo* c);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetEncoderPlugInData}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: void* VidyoCodecVideoGetEncoderPlugInData(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
void* VidyoCodecVideoGetEncoderPlugInData(VidyoCodecVideo* c);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetDecoderPlugIn}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: VidyoLmiDecoderPlugIn* VidyoCodecVideoGetDecoderPlugIn(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
VidyoLmiDecoderPlugIn* VidyoCodecVideoGetDecoderPlugIn(VidyoCodecVideo* c);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetDecoderPlugInData}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: void* VidyoCodecVideoGetDecoderPlugInData(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
void* VidyoCodecVideoGetDecoderPlugInData(VidyoCodecVideo* c);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetProperties}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: LmiBool VidyoCodecVideoGetProperties(VidyoCodecVideo* c, LmiVector(LmiProperty)* properties)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: properties}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoCodecVideoGetProperties(VidyoCodecVideo* c, LmiVector(LmiProperty)* properties);

/**
{function visibility="private":
	{name: VidyoCodecVideoGetClockRate}
	{parent: VidyoCodecVideo}
	{description: }
	{prototype: LmiUint VidyoCodecVideoGetClockRate(VidyoCodecVideo* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiUint VidyoCodecVideoGetClockRate(VidyoCodecVideo* c);

struct VidyoCodecAudioImpl_;
typedef struct VidyoCodecAudioImpl_ VidyoCodecAudioImpl;
Declare_LmiSharedPtr(VidyoCodecAudioImpl)
Declare_LmiSharedPtrWrapper(VidyoCodecAudio, VidyoCodecAudioImpl)
Declare_LmiVector(VidyoCodecAudio)

/**
{type visibility="private" reference-counted="yes":
	{name: VidyoCodecAudio}
	{parent: Endpoint}
	{description: }
	{member:
		{name: id}
		{type: LmiString}
		{description: }
	}
	{member:
		{name: mimeType}
		{type: LmiString}
		{description: }
	}
	{member:
		{name: hasRedCodec}
		{type: LmiBool}
		{description: }
	}
	{member:
		{name: clockRate}
		{type: LmiUint}
		{description: }
	}
	{member:
		{name: numberOfChannels}
		{type: LmiUint}
		{description: }
	}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecAudioConstruct}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: VidyoCodecAudio* VidyoCodecAudioConstruct(VidyoCodecAudio* c, const char* mimeType, VidyoLmiEncoderPlugIn* encoderPlugIn, void* encoderPlugInData, VidyoLmiDecoderPlugIn* decoderPlugIn, void* decoderPlugInData, LmiUint clockRate, LmiUint numberOfChannels, VidyoCodecAudio* redCodec, LmiAllocator* alloc)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: mimeType}
		{description: }
	}
	{parameter:
		{name: encoderPlugIn}
		{description: }
	}
	{parameter:
		{name: encoderPlugInData}
		{description: }
	}
	{parameter:
		{name: decoderPlugIn}
		{description: }
	}
	{parameter:
		{name: decoderPlugInData}
		{description: }
	}
	{parameter:
		{name: clockRate}
		{description: }
	}
	{parameter:
		{name: numberOfChannels}
		{description: }
	}
	{parameter:
		{name: redCodec}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoCodecAudio* VidyoCodecAudioConstruct(VidyoCodecAudio* c, const char* mimeType, VidyoLmiEncoderPlugIn* encoderPlugIn, void* encoderPlugInData, VidyoLmiDecoderPlugIn* decoderPlugIn, void* decoderPlugInData, LmiUint clockRate, LmiUint numberOfChannels, VidyoCodecAudio* redCodec, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoCodecAudioConstructCopy}
	{parent: VidyoCodecAudio}
	{description: Constructs an VidyoCodecAudio object as a copy of another.}
	{prototype: VidyoCodecAudio *VidyoCodecAudioConstructCopy(VidyoCodecAudio *obj, const VidyoCodecAudio *other)}
	{parameter: {name: obj} {description: The VidyoCodecAudio object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecAudioDestruct}
	{parent: VidyoCodecAudio}
	{description: Destructs an VidyoCodecAudio object.}
	{prototype: void VidyoCodecAudioDestruct(VidyoCodecAudio *obj)}
	{parameter: {name: obj} {description: The VidyoCodecAudio object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecAudioAssign}
	{parent: VidyoCodecAudio}
	{description: Assigns one VidyoCodecAudio object the value of another. }
	{prototype: VidyoCodecAudio *VidyoCodecAudioAssign(VidyoCodecAudio *obj, const VidyoCodecAudio *other)}
	{parameter: {name: obj} {description: The VidyoCodecAudio object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoCodecAudioGetId}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: LmiString* VidyoCodecAudioGetId(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiString* VidyoCodecAudioGetId(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetDebugString}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: LmiString* VidyoCodecAudioGetDebugString(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiString* VidyoCodecAudioGetDebugString(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetMimeType}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: const char* VidyoCodecAudioGetMimeType(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
const char* VidyoCodecAudioGetMimeType(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetEncoderPlugIn}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: VidyoLmiEncoderPlugIn* VidyoCodecAudioGetEncoderPlugIn(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
VidyoLmiEncoderPlugIn* VidyoCodecAudioGetEncoderPlugIn(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetEncoderPlugInData}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: void* VidyoCodecAudioGetEncoderPlugInData(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
void* VidyoCodecAudioGetEncoderPlugInData(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetDecoderPlugIn}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: VidyoLmiDecoderPlugIn* VidyoCodecAudioGetDecoderPlugIn(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
VidyoLmiDecoderPlugIn* VidyoCodecAudioGetDecoderPlugIn(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetDecoderPlugInData}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: void* VidyoCodecAudioGetDecoderPlugInData(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
void* VidyoCodecAudioGetDecoderPlugInData(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetClockRate}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: LmiUint VidyoCodecAudioGetClockRate(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiUint VidyoCodecAudioGetClockRate(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetNumberOfChannels}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: LmiUint VidyoCodecAudioGetNumberOfChannels(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiUint VidyoCodecAudioGetNumberOfChannels(VidyoCodecAudio* c);

/**
{function visibility="private":
	{name: VidyoCodecAudioGetRedCodec}
	{parent: VidyoCodecAudio}
	{description: }
	{prototype: VidyoCodecAudio* VidyoCodecAudioGetRedCodec(VidyoCodecAudio* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
VidyoCodecAudio* VidyoCodecAudioGetRedCodec(VidyoCodecAudio* c);


LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoCodecInline.h"
#endif

#endif /* VIDYO_CODEC_H_ */
