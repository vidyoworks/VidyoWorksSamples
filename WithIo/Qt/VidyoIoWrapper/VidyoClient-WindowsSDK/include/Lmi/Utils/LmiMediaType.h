/**
{file:
	{name: LmiMediaType.h}
	{description: }
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
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
#ifndef LMI_MEDIATYPE_H
#define LMI_MEDIATYPE_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: LmiMediaType}
	{parent: Utils}
	{include: Lmi/Utils/LmiMediaType.h}
	{description: Media type.}
	{value: {name: LMI_MEDIATYPE_Audio} {description: audio}}
	{value: {name: LMI_MEDIATYPE_Video} {description: video}}
	{value: {name: LMI_MEDIATYPE_Application} {description: application}}
	{value: {name: LMI_MEDIATYPE_Message} {description: message}}
	{value: {name: LMI_MEDIATYPE_Text} {description: text}}
}
*/
/* Please update mediaTypeStr strings in LmiMediaType.c when modifying these enums */
typedef enum
{
	LMI_MEDIATYPE_Audio,
	LMI_MEDIATYPE_Video,
	LMI_MEDIATYPE_Application,
	LMI_MEDIATYPE_Message,
	LMI_MEDIATYPE_Text,
} LmiMediaType;

#define LMI_MEDIATYPE_NUMVALUES 5

LmiBool LmiMediaTypeGetFromCStr(const char *s, LmiMediaType *type);
const char *LmiMediaTypeToCStr(LmiMediaType type);

LMI_END_EXTERN_C

#endif
