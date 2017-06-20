/**
{file:
	{name: LmiBase64Encoding.h}
	{description: }
	{copyright:
		(c) 2008-2015 Vidyo, Inc.,
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
#ifndef LMI_BASE64ENCODING_H
#define LMI_BASE64ENCODING_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>

LMI_BEGIN_EXTERN_C

#define LMI_BASE64_GetEncodeSize(len) (((len) + 2) / 3 * 4) /* exact */
#define LMI_BASE64_GetMaxDecodeSize(len) ((len) / 4 * 3) /* actual may be shorter */

#define LMI_BASE64_GetEncodedBufferLength(len) (LMI_BASE64_GetEncodeSize(len) + 1)
#define LMI_BASE64_GetDecodedBufferLength(len) (LMI_BASE64_GetMaxDecodeSize(len) + 1)

LmiSizeT LmiBase64Encode_(const char *input, LmiSizeT inputLen, char *output, LmiBool safe);
LMI_INLINE_DECLARATION LmiSizeT LmiBase64Encode(const char *input, LmiSizeT inputLen, char *output);
LMI_INLINE_DECLARATION LmiSizeT LmiBase64EncodeSafe(const char *input, LmiSizeT inputLen, char *output);
LmiBool LmiBase64EncodeToString_(const char *input, LmiSizeT inputLen, LmiString *output, LmiBool safe);
LMI_INLINE_DECLARATION LmiBool LmiBase64EncodeToString(const char *input, LmiSizeT inputLen, LmiString *output);
LMI_INLINE_DECLARATION LmiBool LmiBase64EncodeToStringSafe(const char *input, LmiSizeT inputLen, LmiString *output);
LMI_INLINE_DECLARATION LmiBool LmiBase64EncodeString(const LmiString *input, LmiString *output);
LMI_INLINE_DECLARATION LmiBool LmiBase64EncodeStringSafe(const LmiString *input, LmiString *output);

LmiBool LmiBase64Decode(const char *input, char *output, LmiSizeT *outputLen);
LmiBool LmiBase64DecodeToString(const char *input, LmiSizeT inputLen, LmiString *output);
LMI_INLINE_DECLARATION LmiBool LmiBase64DecodeString(const LmiString *input, LmiString *output);

#define LMI_BASE16_GetEncodeSize(len) (2 * (len)) /* exact */
#define LMI_BASE16_GetEncodedBufferLength(len) (LMI_BASE16_GetEncodeSize(len) + 1)

void LmiBase16Encode_(const char *input, LmiSizeT inputLen, char *output, LmiBool lowercase);
LMI_INLINE_DECLARATION void LmiBase16Encode(const char *input, LmiSizeT inputLen, char *output);
LMI_INLINE_DECLARATION void LmiBase16EncodeLowercase(const char *input, LmiSizeT inputLen, char *output);
LmiBool LmiBase16EncodeToString_(const char *input, LmiSizeT inputLen, LmiString *output, LmiBool lowercase);
LMI_INLINE_DECLARATION LmiBool LmiBase16EncodeToString(const char *input, LmiSizeT inputLen, LmiString *output);
LMI_INLINE_DECLARATION LmiBool LmiBase16EncodeToStringLowercase(const char *input, LmiSizeT inputLen, LmiString *output);
LMI_INLINE_DECLARATION LmiBool LmiBase16EncodeString(const LmiString *input, LmiString *output);
LMI_INLINE_DECLARATION LmiBool LmiBase16EncodeStringLowercase(const LmiString *input, LmiString *output);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiBase64EncodingInline.h>
#endif

#endif
