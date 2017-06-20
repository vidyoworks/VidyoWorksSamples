/**
{file:
	{name: LmiBase64EncodingInline.h}
	{description: }
	{copyright:
		(c) 2013-2015 Vidyo, Inc.,
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
LMI_INLINE LmiSizeT LmiBase64Encode(const char *input, LmiSizeT inputLen, char *output)
{
	return LmiBase64Encode_(input, inputLen, output, LMI_FALSE);
}

LMI_INLINE LmiSizeT LmiBase64EncodeSafe(const char *input, LmiSizeT inputLen, char *output)
{
	return LmiBase64Encode_(input, inputLen, output, LMI_TRUE);
}

LMI_INLINE LmiBool LmiBase64EncodeToString(const char *input, LmiSizeT inputLen, LmiString *output)
{
	return LmiBase64EncodeToString_(input, inputLen, output, LMI_FALSE);
}

LMI_INLINE LmiBool LmiBase64EncodeToStringSafe(const char *input, LmiSizeT inputLen, LmiString *output)
{
	return LmiBase64EncodeToString_(input, inputLen, output, LMI_TRUE);
}

LMI_INLINE LmiBool LmiBase64EncodeString(const LmiString *input, LmiString *output)
{
	return LmiBase64EncodeToString(LmiStringCStr(input), LmiStringSize(input), output);
}

LMI_INLINE LmiBool LmiBase64EncodeStringSafe(const LmiString *input, LmiString *output)
{
	return LmiBase64EncodeToStringSafe(LmiStringCStr(input), LmiStringSize(input), output);
}

LMI_INLINE LmiBool LmiBase64DecodeString(const LmiString *input, LmiString *output)
{
	return LmiBase64DecodeToString(LmiStringCStr(input), LmiStringSize(input), output);
}

LMI_INLINE void LmiBase16Encode(const char *input, LmiSizeT inputLen, char *output)
{
	LmiBase16Encode_(input, inputLen, output, LMI_FALSE);
}

LMI_INLINE void LmiBase16EncodeLowercase(const char *input, LmiSizeT inputLen, char *output)
{
	LmiBase16Encode_(input, inputLen, output, LMI_TRUE);
}

LMI_INLINE LmiBool LmiBase16EncodeToString(const char *input, LmiSizeT inputLen, LmiString *output)
{
	return LmiBase16EncodeToString_(input, inputLen, output, LMI_FALSE);
}

LMI_INLINE LmiBool LmiBase16EncodeToStringLowercase(const char *input, LmiSizeT inputLen, LmiString *output)
{
	return LmiBase16EncodeToString_(input, inputLen, output, LMI_TRUE);
}

LMI_INLINE LmiBool LmiBase16EncodeString(const LmiString *input, LmiString *output)
{
	return LmiBase16EncodeToString(LmiStringCStr(input), LmiStringSize(input), output);
}

LMI_INLINE LmiBool LmiBase16EncodeStringLowercase(const LmiString *input, LmiString *output)
{
	return LmiBase16EncodeToStringLowercase(LmiStringCStr(input), LmiStringSize(input), output);
}
