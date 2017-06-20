
/** 
{file:
	{name: LmiStack.h}
	{description: A container implementing a LIFO discipline.}
    {copyright:
    	(c) 2006-2007 Vidyo, Inc.,
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
#ifndef LMI_STACK_H_
#define LMI_STACK_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiVector.h>

LMI_BEGIN_EXTERN_C

#define LmiStack(T_)						LmiTemplate1(LmiStack, T_)
#define LmiStackConstructDefault(T_)		LmiClassFunc(LmiStack(T_), ConstructDefault)
#define LmiStackDestruct(T_)				LmiClassFunc(LmiStack(T_), Destruct)
#define LmiStackSize(T_)					LmiClassFunc(LmiStack(T_), Size)
#define LmiStackReserve(T_)					LmiClassFunc(LmiStack(T_), Reserve)
#define LmiStackPush(T_)					LmiClassFunc(LmiStack(T_), Push)
#define LmiStackPop(T_)						LmiClassFunc(LmiStack(T_), Pop)
#define LmiStackTop(T_)						LmiClassFunc(LmiStack(T_), Top)
#define LmiStackClear(T_)					LmiClassFunc(LmiStack(T_), Clear)

#define Declare_LmiStackConstructDefault(T_) \
	LmiStack(T_)* LmiStackConstructDefault(T_)(LmiStack(T_)* x, LmiAllocator* a);
#define Declare_LmiStackDestruct(T_) \
	void LmiStackDestruct(T_)(LmiStack(T_)* x);
#define Declare_LmiStackSize(T_) \
	LmiSizeT LmiStackSize(T_)(LmiStack(T_)* x);
#define Declare_LmiStackReserve(T_) \
	LmiBool LmiStackReserve(T_)(LmiStack(T_)* x, LmiSizeT n);
#define Declare_LmiStackPush(T_) \
	LmiBool LmiStackPush(T_)(LmiStack(T_)* x, const T_* t);
#define Declare_LmiStackPop(T_) \
	void LmiStackPop(T_)(LmiStack(T_)* x);
#define Declare_LmiStackTop(T_) \
	T_* LmiStackTop(T_)(LmiStack(T_)* x);
#define Declare_LmiStackClear(T_) \
	void LmiStackClear(T_)(LmiStack(T_)* x);

#define Declare_LmiStack(T_) \
	Declare_LmiVector(T_) \
	typedef struct { \
		LmiVector(T_) v; \
	} LmiStack(T_); \
	Declare_LmiStackConstructDefault(T_) \
	Declare_LmiStackDestruct(T_) \
	Declare_LmiStackSize(T_) \
	Declare_LmiStackReserve(T_) \
	Declare_LmiStackPush(T_) \
	Declare_LmiStackPop(T_) \
	Declare_LmiStackTop(T_) \
	Declare_LmiStackClear(T_)


#define Define_LmiStackConstructDefault(T_) \
	LmiStack(T_)* LmiStackConstructDefault(T_)(LmiStack(T_)* x, LmiAllocator* a) { \
		LmiVectorConstructDefault(T_)(&(x->v), a); \
		return x; \
	}
#define Define_LmiStackDestruct(T_) \
	void LmiStackDestruct(T_)(LmiStack(T_)* x) { \
		LmiVectorDestruct(T_)(&(x->v)); \
	}
#define Define_LmiStackSize(T_) \
	LmiSizeT LmiStackSize(T_)(LmiStack(T_)* x) { \
		return LmiVectorSize(T_)(&(x->v)); \
	}
#define Define_LmiStackReserve(T_) \
	LmiBool LmiStackReserve(T_)(LmiStack(T_)* x, LmiSizeT n) { \
		return LmiVectorReserve(T_)(&(x->v), n); \
	}
#define Define_LmiStackPush(T_) \
	LmiBool LmiStackPush(T_)(LmiStack(T_)* x, const T_* t) { \
		return LmiVectorPushBack(T_)(&(x->v), t); \
	}
#define Define_LmiStackPop(T_) \
	void LmiStackPop(T_)(LmiStack(T_)* x) { \
		LmiVectorPopBack(T_)(&(x->v)); \
	}
#define Define_LmiStackTop(T_) \
	T_* LmiStackTop(T_)(LmiStack(T_)* x) { \
		return LmiVectorBack(T_)(&(x->v)); \
	}
#define Define_LmiStackClear(T_) \
	void LmiStackClear(T_)(LmiStack(T_)* x) { \
		LmiVectorClear(T_)(&(x->v)); \
	}

#define Define_LmiStack(T_) \
	Define_LmiVector(T_) \
	Define_LmiStackConstructDefault(T_) \
	Define_LmiStackDestruct(T_) \
	Define_LmiStackSize(T_) \
	Define_LmiStackReserve(T_) \
	Define_LmiStackPush(T_) \
	Define_LmiStackPop(T_) \
	Define_LmiStackTop(T_) \
	Define_LmiStackClear(T_)

LMI_END_EXTERN_C

#endif /* LMI_STACK_H_ */
