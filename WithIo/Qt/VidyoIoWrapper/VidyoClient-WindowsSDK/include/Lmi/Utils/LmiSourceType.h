/**
{file:
	{name: LmiSourceType.h}
	{description: }
	{copyright:
		(c) 2011-2015 Vidyo, Inc.,
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
#ifndef LMI_SOURCETYPE_H
#define LMI_SOURCETYPE_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiMediaType.h>

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: LmiSourceType}
	{parent: Utils}
	{include: Lmi/Utils/LmiSourceType.h}
	{description: Describes the source type of a media stream.}
	{value: {name: LMI_SOURCETYPE_InteractiveAudio} {description: An interactive audio source.}}
	{value: {name: LMI_SOURCETYPE_NoninteractiveAudio} {description: A non-interactive audio source.}}
	{value: {name: LMI_SOURCETYPE_InteractiveVideo} {description: An interactive video source.}}
	{value: {name: LMI_SOURCETYPE_NoninteractiveVideo} {description: A non-interactive video source (a.k.a. content).}}
	{value: {name: LMI_SOURCETYPE_InteractiveOther} {description: An interactive application-specific source type.}}
	{value: {name: LMI_SOURCETYPE_NoninteractiveOther} {description: A non-interactive application-specific source type.}}
}
*/

/* Please update sourceTypeStr strings in LmiSourceType.c when modifying these enums */

typedef enum
{
	LMI_SOURCETYPE_InteractiveAudio,
	LMI_SOURCETYPE_NoninteractiveAudio,
	LMI_SOURCETYPE_InteractiveVideo,
	LMI_SOURCETYPE_NoninteractiveVideo,
	LMI_SOURCETYPE_InteractiveOther,
	LMI_SOURCETYPE_NoninteractiveOther,
	LMI_SOURCETYPE_MAX
} LmiSourceType;

const char *LmiSourceTypeToStr(LmiSourceType type);
const char *LmiSourceTypeToSignalingStr(LmiSourceType type);
const char *LmiSourceTypeToEnumStr(LmiSourceType type);
LmiBool LmiSourceTypeGetFromCStr(const char *s, LmiSourceType *type);
LmiBool LmiSourceTypeGetFromSignalingCStr(const char *s, LmiSourceType *type);
LmiBool LmiSourceTypeGetFromEnumCStr(const char *s, LmiSourceType *type);
LmiBool LmiSourceTypeGetMediaType(LmiSourceType type, LmiMediaType *mediaType);

LMI_END_EXTERN_C

#endif
