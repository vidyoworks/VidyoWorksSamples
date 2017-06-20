/** 
{file:
	{name: VidyoForwardDecl.h}
	{description: High level client library. }
	{copyright:
		(c) 2015 Vidyo, Inc.,
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

#ifndef VIDYO_FORWARDDECL_H_ 
#define VIDYO_FORWARDDECL_H_ 

#include <Lmi/Utils/SysDep/LmiBaseCompiler.h>

LMI_BEGIN_EXTERN_C

/**
{package visibility="private":
	{name: ForwardDeclarations}
	{parent: VidyoClient}
	{description: Forward declarations hiding low level data structures.}
}
*/

/**
{type visibility="private":
	{name: VidyoLmiEncoderPlugIn}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiEncoderPlugIn}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiDecoderPlugIn}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiDecoderPlugIn}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiVideoCapturer}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiVideoCapturer}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiAudioCapturer}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiAudioCapturer}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiScreen}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiScreen}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiVideoFrame}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiVideoFrame}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiVideoSourceConstraints}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiVideoSourceConstraints}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiConferenceScene}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiConferenceScene}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiConferenceSceneParticipant}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiConferenceSceneParticipant}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiConferenceSceneStreamChange}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiConferenceSceneStreamChange}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiConferenceSceneSlotChange}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiConferenceSceneSlotChange}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiAudioFrame}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiAudioFrame}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiAudioPlaybackDevice}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiAudioPlaybackDevice}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiWindowCapturer}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiWindowCapturer}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiRemoteSource}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiRemoteSource}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiIpAddress}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiIpAddress}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiTransport}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiTransport}
}
*/
/**
{type visibility="private":
	{name: VidyoLmiTransportAddress}
	{parent: ForwardDeclarations}
    {include: Lmi/VidyoClient/VidyoForwardDecl.h}
	{description: synonymous to LmiTransportAddress}
}
*/
typedef struct LmiEncoderPlugIn_               VidyoLmiEncoderPlugIn;
typedef struct LmiDecoderPlugIn_               VidyoLmiDecoderPlugIn;
typedef struct LmiVideoCapturer_               VidyoLmiVideoCapturer;
typedef struct LmiAudioCapturer_               VidyoLmiAudioCapturer;
typedef struct LmiScreen_                      VidyoLmiScreen;
typedef struct LmiVideoFrame_                  VidyoLmiVideoFrame;
typedef struct LmiVideoSourceConstraints_      VidyoLmiVideoSourceConstraints;
typedef struct LmiConferenceScene_             VidyoLmiConferenceScene;
typedef struct LmiConferenceSceneParticipant_  VidyoLmiConferenceSceneParticipant;
typedef struct LmiConferenceSceneStreamChange_ VidyoLmiConferenceSceneStreamChange;
typedef struct LmiConferenceSceneSlotChange_   VidyoLmiConferenceSceneSlotChange;
typedef struct LmiAudioFrame_                  VidyoLmiAudioFrame;
typedef struct LmiAudioPlaybackDevice_         VidyoLmiAudioPlaybackDevice;
typedef struct LmiWindowCapturer_              VidyoLmiWindowCapturer;
typedef struct LmiRemoteSource_                VidyoLmiRemoteSource;
typedef struct LmiIpAddress_                   VidyoLmiIpAddress;
typedef struct LmiTransport_                   VidyoLmiTransport;
typedef struct LmiTransportAddress_            VidyoLmiTransportAddress;
typedef struct LmiJson_                        VidyoLmiJson;


LMI_END_EXTERN_C

#endif /* VIDYO_FORWARDDECL_H_  */

