/**
{file:
	{name: LmiCast.h}
	{description: }
	{copyright:
		(c) 2011-2014 Vidyo, Inc.,
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
#ifndef LMI_CAST_H
#define LMI_CAST_H

#include <Lmi/Utils/LmiTypes.h>

/* Use (Declare_LmiDowncast in X.h and Define_LmiDowncast in XInline.h)
or Define_LmiDowncast_Static in X.c. */

#define LmiDowncast(B, D) LmiDowncast_##B##_##D##_
#define LmiDowncastConst(B, D) LmiDowncastConst_##B##_##D##_

#define LmiDowncastEx(B, D, E) LmiDowncast_##B##_##D##_##E##_
#define LmiDowncastExConst(B, D, E) LmiDowncastConst_##B##_##D##E##_

#define Declare_LmiDowncast(B, D) \
	LMI_INLINE_DECLARATION D *LmiDowncast(B, D)(B *b); \
	LMI_INLINE_DECLARATION const D *LmiDowncastConst(B, D)(const B *b);

#define Declare_LmiDowncastEx(B, D) \
	LMI_INLINE_DECLARATION D *LmiDowncastEx(B, D, E)(B *b); \
	LMI_INLINE_DECLARATION const D *LmiDowncastExConst(B, D, E)(const B *b);

#define Define_LmiDowncast_Decl(I, B, D, member, DC, DCC) \
	I D *DC(B *b) \
	{ \
		return (D *)((char *)b - offsetof(D, member)); \
	} \
	I const D *DCC(const B *b) \
	{ \
		return (const D *)((char *)b - offsetof(D, member)); \
	}

#define Define_LmiDowncast(B, D, member) Define_LmiDowncast_Decl(LMI_INLINE, B, D, member, LmiDowncast(B, D), LmiDowncastConst(B, D))
#define Define_LmiDowncast_Static(B, D, member) Define_LmiDowncast_Decl(LMI_POSSIBLY_UNUSED LMI_STATIC_INLINE, B, D, member, LmiDowncast(B, D), LmiDowncastConst(B, D))

#define Define_LmiDowncastEx(B, D, E, member) Define_LmiDowncast_Decl(LMI_INLINE, B, D, member, LmiDowncastEx(B, D, E), LmiDowncastExConst(B, D, E))
#define Define_LmiDowncastEx_Static(B, D, E, member) Define_LmiDowncast_Decl(LMI_POSSIBLY_UNUSED LMI_STATIC_INLINE, B, D, member, LmiDowncastEx(B, D, E), LmiDowncastExConst(B, D, E))

#endif
