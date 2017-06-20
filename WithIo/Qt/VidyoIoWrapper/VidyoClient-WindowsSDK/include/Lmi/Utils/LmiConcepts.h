
/** 
{file:
	{name: LmiConcepts.h}
	{description: Base concepts.}
    {copyright:
    	(c) 2005-2012 Vidyo, Inc.,
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
#if !defined(LMI_CONCEPTS_H_)
#define LMI_CONCEPTS_H_

#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/SysDep/LmiBaseTypes.h>

/* Base Concepts */
#define DeclareInline_LmiDefaultConstructible(X_, INLINE_)		 \
	INLINE_ X_* LmiConstructDefault(X_)(X_* x, LmiAllocator* a); \
	INLINE_ LmiAllocator * LmiGetAllocator(X_)(const X_* x);

#define DeclareInline_LmiDestructible(X_, INLINE_)			\
	INLINE_ void LmiDestruct(X_)(X_* x);

#define DeclareInline_LmiAssignable(X_, INLINE_)		\
	INLINE_ void LmiDestruct(X_)(X_* x); \
	INLINE_ X_* LmiConstructCopy(X_)(X_* x, const X_* y); \
	INLINE_ X_* LmiAssign(X_)(X_* x, const X_* y); \
	INLINE_ LmiBool LmiSwap(X_)(X_* x, X_* y);

#define DeclareInline_LmiEqualityComparable(X_, INLINE_)	\
	INLINE_ LmiBool LmiEqual(X_)(const X_* x, const X_* y);

#define DeclareInline_LmiLessThanComparable(X_, INLINE_)	\
	INLINE_ LmiBool LmiLess(X_)(const X_* x, const X_* y);

#define DeclareInline_LmiDumpable(X_, INLINE_)							\
	INLINE_ void LmiDump(X_)(const X_* x, const char* name, unsigned int tabStop);

#define Declare_LmiDefaultConstructible(X_)		 \
	DeclareInline_LmiDefaultConstructible(X_, LMI_NO_INLINE)

#define Declare_LmiDestructible(X_) \
	DeclareInline_LmiDestructible(X_, LMI_NO_INLINE) 

#define Declare_LmiAssignable(X_) \
	DeclareInline_LmiAssignable(X_, LMI_NO_INLINE)

#define Declare_LmiEqualityComparable(X_) \
	DeclareInline_LmiEqualityComparable(X_, LMI_NO_INLINE)

#define Declare_LmiLessThanComparable(X_) \
	DeclareInline_LmiLessThanComparable(X_, LMI_NO_INLINE)

#define Declare_LmiDumpable(X_) \
	DeclareInline_LmiDumpable(X_, LMI_NO_INLINE)

/**
{type visibility="public":
	{name: LmiPredicate}
	{parent: Utils}
	{include: Lmi/Utils/LmiConcepts.h}
	{description: The predicate concept.  Given template parameter type X_, defines a type of pointer to function {code:LmiBool (*)(const X_*, void*)}}
	{template-prototype: LmiPredicate(X_)}
	{template-parameter: 
		{name: X_}
		{description: The value type of the predicate.}
	}
	{note: 
		The macro Declare_LmiPredicate must be called before declaring an 
		object of this type.  
	}
}
*/
#define Declare_LmiPredicate(X_) \
	typedef LmiBool (*LmiPredicate(X_))(const X_* x, void* data);

/* Basic implementation of base concepts */
#define DefineInline_LmiDestructible(X_, INLINE_) \
	INLINE_ void LmiDestruct(X_)(X_* x) {}

#define DefineInline_LmiAssignable(X_, INLINE_) \
	INLINE_ X_* LmiConstructCopy(X_)(X_* x, const X_* y) {*x = *y; return x; } \
	INLINE_ X_* LmiAssign(X_)(X_* x, const X_* y) { *x = *y; return x; } \
	INLINE_ LmiBool LmiSwap(X_)(X_* x, X_* y) { X_ z = *x; *x = *y; *y = z; return LMI_TRUE; }

#define DefineInline_LmiEqualityComparable(X_, INLINE_) \
	INLINE_ LmiBool LmiEqual(X_)(const X_* x, const X_* y) { return *x == *y; }

#define DefineInline_LmiLessThanComparable(X_, INLINE_) \
	INLINE_ LmiBool LmiLess(X_)(const X_* x, const X_* y) { return *x < *y; }

#endif
