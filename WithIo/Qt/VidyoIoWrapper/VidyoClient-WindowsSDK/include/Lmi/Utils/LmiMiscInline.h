/**
{file:
	{name: LmiMiscInline.h}
	{description: Miscellaneous utilities.}
	{copyright:
		(c) 2012 Vidyo, Inc.,
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

/** {implementation: {name: LmiUint16FromOctets}} */
LMI_INLINE LmiUint16 LmiUint16FromOctets(const LmiUint8 o[2])
{
	return (((LmiUint16)(o[0]) << 8) | ((LmiUint16)(o[1])));
}

/** {implementation: {name: LmiUint16FromBuffer}} */
LMI_INLINE LmiBool LmiUint16FromBuffer(const LmiString* b, LmiSizeT* pos, LmiSizeT end, LmiUint16* u16)
{
	if (end < *pos + 2 || LmiStringLength(b) < *pos + 2) {
		return LMI_FALSE;
	}
	*u16 = LmiUint16FromOctets((LmiUint8*)LmiStringAtConst(b, *pos));
	*pos += 2;
	return LMI_TRUE;
}

/** {implementation: {name: LmiUint16ToOctets}} */
LMI_INLINE void LmiUint16ToOctets(LmiUint16 u16, LmiUint8 o[2])
{
	LmiUint8 *u = (LmiUint8*) &u16;
#if LMI_WORDS_BIGENDIAN
	o[0] = u[0];
	o[1] = u[1];
#else
	o[0] = u[1];
	o[1] = u[0];
#endif
}

/** {implementation: {name: LmiUint16ToBuffer}} */
LMI_INLINE LmiBool LmiUint16ToBuffer(LmiUint16 u16, LmiString* b)
{
	LmiUint8 *u = (LmiUint8*) &u16;
#if LMI_WORDS_BIGENDIAN
	if (LmiStringAppendChar(b, (char)u[0]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[1]) == NULL) return LMI_FALSE;
#else
	if (LmiStringAppendChar(b, (char)u[1]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[0]) == NULL) return LMI_FALSE;
#endif
	return LMI_TRUE;
}

/** {implementation: {name: LmiUint32FromOctets}} */
LMI_INLINE LmiUint32 LmiUint32FromOctets(const LmiUint8 o[4])
{
	return (((LmiUint32)(o[0]) << 24) |
		((LmiUint32)(o[1]) << 16) |
		((LmiUint32)(o[2]) <<  8) |
		((LmiUint32)(o[3])));
}

/** {implementation: {name: LmiUint32FromBuffer}} */
LMI_INLINE LmiBool LmiUint32FromBuffer(const LmiString* b, LmiSizeT* pos, LmiSizeT end, LmiUint32* u32)
{
	if (end < *pos + 4 || LmiStringLength(b) < *pos + 4) {
		return LMI_FALSE;
	}
	*u32 = LmiUint32FromOctets((LmiUint8*)LmiStringAtConst(b, *pos));
	*pos += 4;
	return LMI_TRUE;
}

/** {implementation: {name: LmiUint32ToOctets}} */
LMI_INLINE void LmiUint32ToOctets(LmiUint32 u32, LmiUint8 o[4])
{
	LmiUint8 *u = (LmiUint8*) &u32;
#if LMI_WORDS_BIGENDIAN
	o[0] = u[0];
	o[1] = u[1];
	o[2] = u[2];
	o[3] = u[3];
#else
	o[0] = u[3];
	o[1] = u[2];
	o[2] = u[1];
	o[3] = u[0];
#endif
}

/** {implementation: {name: LmiUint32ToBuffer}} */
LMI_INLINE LmiBool LmiUint32ToBuffer(LmiUint32 u32, LmiString* b)
{
	LmiUint8 *u = (LmiUint8*) &u32;
#if LMI_WORDS_BIGENDIAN
	if (LmiStringAppendChar(b, (char)u[0]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[1]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[2]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[3]) == NULL) return LMI_FALSE;
#else
	if (LmiStringAppendChar(b, (char)u[3]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[2]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[1]) == NULL) return LMI_FALSE;
	if (LmiStringAppendChar(b, (char)u[0]) == NULL) return LMI_FALSE;
#endif
	return LMI_TRUE;
}
