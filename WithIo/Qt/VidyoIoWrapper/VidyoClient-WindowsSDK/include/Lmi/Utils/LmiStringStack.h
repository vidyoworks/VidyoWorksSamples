/**
{file:
	{name: LmiStringStack.h}
	{description: Contains definitions for a stack of strings.}
	{copyright:
		(c) 2007-2015 Vidyo, Inc.,
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

#ifndef LMI_STRINGSTACK_H
#define LMI_STRINGSTACK_H

#include <Lmi/Utils/LmiStringVector.h>

LMI_BEGIN_EXTERN_C

#if 0
#define LmiStack(T_)						LmiTemplate1(LmiStack, T_)
#define LmiStackConstructDefault(T_)		LmiClassFunc(LmiStack(T_), ConstructDefault)
#define LmiStackDestruct(T_)				LmiClassFunc(LmiStack(T_), Destruct)
#define LmiStackSize(T_)					LmiClassFunc(LmiStack(T_), Size)
#define LmiStackReserve(T_)					LmiClassFunc(LmiStack(T_), Reserve)
#define LmiStackPush(T_)					LmiClassFunc(LmiStack(T_), Push)
#define LmiStackPop(T_)						LmiClassFunc(LmiStack(T_), Pop)
#define LmiStackTop(T_)						LmiClassFunc(LmiStack(T_), Top)
#define LmiStackClear(T_)					LmiClassFunc(LmiStack(T_), Clear)
#endif

#define Declare_LmiStringStackConstructDefault \
	LmiStringStack* LmiStringStackConstructDefault(LmiStringStack* x, LmiAllocator* a);
#define Declare_LmiStringStackDestruct \
	void LmiStringStackDestruct(LmiStringStack* x);
#define Declare_LmiStringStackSize \
	LmiSizeT LmiStringStackSize(LmiStringStack* x);
#define Declare_LmiStringStackReserve \
	LmiBool LmiStringStackReserve(LmiStringStack* x, LmiSizeT n);
#define Declare_LmiStringStackPush \
	LmiBool LmiStringStackPush(LmiStringStack* x, const LmiString* t);
#define Declare_LmiStringStackPop \
	void LmiStringStackPop(LmiStringStack* x);
#define Declare_LmiStringStackTop \
	LmiString* LmiStringStackTop(LmiStringStack* x);
#define Declare_LmiStringStackClear \
	void LmiStringStackClear(LmiStringStack* x);

#define Declare_LmiStringStack \
	typedef struct { \
		LmiStringVector v; \
	} LmiStringStack; \
	Declare_LmiStringStackConstructDefault \
	Declare_LmiStringStackDestruct \
	Declare_LmiStringStackSize \
	Declare_LmiStringStackReserve \
	Declare_LmiStringStackPush \
	Declare_LmiStringStackPop \
	Declare_LmiStringStackTop \
	Declare_LmiStringStackClear


#define Define_LmiStringStackConstructDefault \
	LmiStringStack* LmiStringStackConstructDefault(LmiStringStack* x, LmiAllocator* a) { \
		LmiStringVectorConstructDefault(&(x->v), a); \
		return x; \
	}
#define Define_LmiStringStackDestruct \
	void LmiStringStackDestruct(LmiStringStack* x) { \
		LmiStringVectorDestruct(&(x->v)); \
	}
#define Define_LmiStringStackSize \
	LmiSizeT LmiStringStackSize(LmiStringStack* x) { \
		return LmiStringVectorSize(&(x->v)); \
	}
#define Define_LmiStringStackReserve \
	LmiBool LmiStringStackReserve(LmiStringStack* x, LmiSizeT n) { \
		return LmiStringVectorReserve(&(x->v), n); \
	}
#define Define_LmiStringStackPush \
	LmiBool LmiStringStackPush(LmiStringStack* x, const LmiString* t) { \
		return LmiStringVectorPushBack(&(x->v), t); \
	}
#define Define_LmiStringStackPop \
	void LmiStringStackPop(LmiStringStack* x) { \
		LmiStringVectorPopBack(&(x->v)); \
	}
#define Define_LmiStringStackTop \
	LmiString* LmiStringStackTop(LmiStringStack* x) { \
		return LmiStringVectorBack(&(x->v)); \
	}
#define Define_LmiStringStackClear \
	void LmiStringStackClear(LmiStringStack* x) { \
		LmiStringVectorClear(&(x->v)); \
	}

#define Define_LmiStringStack \
	Define_LmiStringStackConstructDefault \
	Define_LmiStringStackDestruct \
	Define_LmiStringStackSize \
	Define_LmiStringStackReserve \
	Define_LmiStringStackPush \
	Define_LmiStringStackPop \
	Define_LmiStringStackTop \
	Define_LmiStringStackClear



/**
   {type visibility="private":
     {name: LmiStringStack}
     {parent: Containers}
     {include: Lmi/Utils/LmiStringStack.h}
     {description: LmiStringStack is an instantiation of LmiStack over
       LmiString.}
     {note: See LmiStack for descriptions
       of LmiStringStack\'s member functions.}
   }
*/

Declare_LmiStringStack

LMI_END_EXTERN_C

#endif /* LMI_STRINGSTACK_H */

