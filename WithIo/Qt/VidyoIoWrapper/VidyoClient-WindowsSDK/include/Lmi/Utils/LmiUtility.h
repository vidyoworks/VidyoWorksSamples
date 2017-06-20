
/** 
{file:
	{name: LmiUtility.h}
	{description: Utility interfaces.}
    {copyright:
    	(c) 2005-2015 Vidyo, Inc.,
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
#ifndef LMI_UTILITY_H_
#define LMI_UTILITY_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>

/* Name mangling */
#define LmiPair(T1_, T2_)					LmiTemplate2(LmiPair, T1_, T2_)
#define LmiPairConstruct(T1_, T2_)			LmiConstruct(LmiPair(T1_, T2_))
#define LmiPairConstructCopy(T1_, T2_)		LmiConstructCopy(LmiPair(T1_, T2_))
#define LmiPairDestruct(T1_, T2_)			LmiDestruct(LmiPair(T1_, T2_))
#define LmiPairAssign(T1_, T2_)				LmiAssign(LmiPair(T1_, T2_))
#define LmiPairSwap(T1_, T2_)				LmiSwap(LmiPair(T1_, T2_))
#define LmiPairEqual(T1_, T2_)				LmiEqual(LmiPair(T1_, T2_))
#define LmiPairLess(T1_, T2_)				LmiLess(LmiPair(T1_, T2_))

/**
{type:
	{name: LmiPair}
	{parent: Utils}
	{include: Lmi/Utils/LmiUtility.h}
	{description: An object that contains two other objects, possibly of different types.}
	{template-prototype: LmiPair(T1_, T2_)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{member:
		{name: first}
		{type: T1_}
		{description: The first item of the pair.}
	}
	{member:
		{name: second}
		{type: T2_}
		{description: The second item of the pair.}
	}
}
*/
#define Declare_LmiPairTypes(T1_, T2_) \
	typedef struct { \
		T1_ first; \
		T2_ second; \
	} LmiPair(T1_, T2_);

/**
{function: 
	{name: LmiPairConstruct}
	{parent: LmiPair}
	{description: Constructs a pair.}
	{prototype: LmiPair(T1_, T2_)* LmiPairConstruct(T1_, T2_)(LmiPair(T1_, T2_)* x, const T1_* first, const T2_* second)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{parameter:
		{name: x}
		{description: A pointer to the pair to construct.}
	}
	{parameter:
		{name: first}
		{description: The value to initialize the first item of the pair to.}
	}
	{parameter:
		{name: second}
		{description: The value to initialize the second item of the pair to.}
	}
	{return: A pointer to the constructed object or NULL on failure.}
}
*/
#define DefineInline_LmiPairConstruct(T1_, T2_, INLINE_)					\
INLINE_ LmiPair(T1_, T2_)* LmiPairConstruct(T1_, T2_)(LmiPair(T1_, T2_)* x, const T1_* first, const T2_* second) { \
	if (LmiConstructCopy(T1_)(&x->first, first) == NULL) \
		return NULL;									 \
	if (LmiConstructCopy(T2_)(&x->second, second) == NULL) { \
		LmiDestruct(T1_)(&x->first); 					 \
		return NULL;									 \
	}													 \
	return x;											 \
}

/**
{function: 
	{name: LmiPairConstructCopy}
	{parent: LmiPair}
	{description: Constructs a pair, initializing it with the value of another pair.}
	{prototype: LmiPair(T1_, T2_)* LmiPairConstructCopy(T1_, T2_)(LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{parameter:
		{name: x}
		{description: A pointer to the pair to construct.}
	}
	{parameter:
		{name: y}
		{description: A pointer to the pair to use to initialize the constructed pair.}
	}
	{return: A pointer to the constructed object or NULL on failure.}
}
*/
#define DefineInline_LmiPairConstructCopy(T1_, T2_, INLINE_) \
INLINE_ LmiPair(T1_, T2_)* LmiPairConstructCopy(T1_, T2_)(LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y) { \
	LmiConstructCopy(T1_)(&x->first, &y->first); \
	LmiConstructCopy(T2_)(&x->second, &y->second); \
	return x; \
}

/**
{function: 
	{name: LmiPairDestruct}
	{parent: LmiPair}
	{description: Destructs a pair.}
	{prototype: void LmiPairDestruct(T1_, T2_)(LmiPair(T1_, T2_)* x)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{parameter:
		{name: x}
		{description: A pointer to the pair to destruct.}
	}
}
*/
#define DefineInline_LmiPairDestruct(T1_, T2_, INLINE_) \
INLINE_ void LmiPairDestruct(T1_, T2_)(LmiPair(T1_, T2_)* x) { \
	LmiDestruct(T1_)(&x->first); \
	LmiDestruct(T2_)(&x->second); \
} 

/**
{function: 
	{name: LmiPairAssign}
	{parent: LmiPair}
	{description: Assign the value of one pair to another pair.}
	{prototype: LmiPair(T1_, T2_)* LmiPairAssign(T1_, T2_)(LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{parameter:
		{name: x}
		{description: A pointer to the pair to assign to.}
	}
	{parameter:
		{name: y}
		{description: A pointer to the pair to assign from.}
	}
	{return: A pointer to the assigned to object or NULL on failure.}
}
*/
#define DefineInline_LmiPairAssign(T1_, T2_, INLINE_) \
INLINE_ LmiPair(T1_, T2_)* LmiPairAssign(T1_, T2_)(LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y) { \
	LmiAssign(T1_)(&x->first, &y->first); \
	LmiAssign(T2_)(&x->second, &y->second); \
	return x; \
}

/**
{function: 
	{name: LmiPairSwap}
	{parent: LmiPair}
	{description: Swap the value of two pairs.}
	{prototype: LmiPair(T1_, T2_)* LmiPairSwap(T1_, T2_)(LmiPair(T1_, T2_)* x, LmiPair(T1_, T2_)* y)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{parameter:
		{name: x}
		{description: A pointer to one of the pairs to swap.}
	}
	{parameter:
		{name: y}
		{description: A pointer to the other pair to swap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
}
*/
#define DefineInline_LmiPairSwap(T1_, T2_, INLINE_) \
INLINE_ LmiBool LmiPairSwap(T1_, T2_)(LmiPair(T1_, T2_)* x, LmiPair(T1_, T2_)* y) { \
	LmiPair(T1_, T2_) z; \
	LmiPairConstructCopy(T1_, T2_)(&z, x); \
	LmiPairAssign(T1_, T2_)(x, y); \
	LmiPairAssign(T1_, T2_)(y, &z); \
	LmiPairDestruct(T1_, T2_)(&z); \
	return LMI_TRUE; \
}

/**
{function: 
	{name: LmiPairEqual}
	{parent: LmiPair}
	{description: Compare two pairs for equality.}
	{prototype: LmiPair(T1_, T2_)* LmiPairEqual(T1_, T2_)(const LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{parameter:
		{name: x}
		{description: A pointer to one of the pairs to compare.}
	}
	{parameter:
		{name: y}
		{description: A pointer to the other pair to compare.}
	}
	{return: LMI_TRUE if the pairs are equal or LMI_FALSE if they are not.}
}
*/
#define DefineInline_LmiPairEqual(T1_, T2_, INLINE_) \
INLINE_ LmiBool LmiPairEqual(T1_, T2_)(const LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y) { \
	return LmiEqual(T1_)(&x->first, &y->first) && LmiEqual(T2_)(&x->second, &y->second); \
}

/**
{function: 
	{name: LmiPairLess}
	{parent: LmiPair}
	{description: Compare whether one pair is lexicographically less than another.}
	{prototype: LmiPair(T1_, T2_)* LmiPairLess(T1_, T2_)(const LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y)}
	{template-parameter:
		{name: T1_}
		{description: The type of the first item of the pair.}
	}
	{template-parameter:
		{name: T2_}
		{description: The type of the second item of the pair.}
	}
	{parameter:
		{name: x}
		{description: A pointer to one of the pairs to compare.}
	}
	{parameter:
		{name: y}
		{description: A pointer to the other pair to compare.}
	}
	{return: LMI_TRUE if the first pair is less than the second pair or LMI_FALSE if it is not.}
}
*/
#define DefineInline_LmiPairLess(T1_, T2_, INLINE_)							\
INLINE_ LmiBool LmiPairLess(T1_, T2_)(const LmiPair(T1_, T2_)* x, const LmiPair(T1_, T2_)* y) { \
	return LmiLess(T1_)(&x->first, &y->first) || \
		(LmiEqual(T1_)(&y->first, &x->first) && LmiLess(T2_)(&x->second, &y->second)); \
}

#define DefineInline_LmiPair(T1_, T2_, INLINE_) \
	DefineInline_LmiPairConstruct(T1_, T2_, INLINE_) \
	DefineInline_LmiPairConstructCopy(T1_, T2_, INLINE_) \
	DefineInline_LmiPairDestruct(T1_, T2_, INLINE_) \
	DefineInline_LmiPairAssign(T1_, T2_, INLINE_) \
	DefineInline_LmiPairSwap(T1_, T2_, INLINE_)

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#define DefineInlineHeader_LmiPair(T1_, T2_) \
	DefineInline_LmiPair(T1_, T2_, LMI_INLINE)
#define DefineInlineHeader_LmiPairEqual(T1_, T2_) \
	DefineInline_LmiPairEqual(T1_, T2_, LMI_INLINE)
#define DefineInlineHeader_LmiPairLess(T1_, T2_) \
	DefineInline_LmiPairLess(T1_, T2_, LMI_INLINE)
#else
#define DefineInlineHeader_LmiPair(T1_, T2_) /* defined as empty */
#define DefineInlineHeader_LmiPairEqual(T1_, T2_) /* defined as empty */
#define DefineInlineHeader_LmiPairLess(T1_, T2_) /* defined as empty */
#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
#define Define_LmiPair(T1_, T2_) \
	DefineInline_LmiPair(T1_, T2_, LMI_INLINE_SOURCE_FILE)
#define Define_LmiPairEqual(T1_, T2_) \
	DefineInline_LmiPairEqual(T1_, T2_, LMI_INLINE_SOURCE_FILE)
#define Define_LmiPairLess(T1_, T2_) \
	DefineInline_LmiPairLess(T1_, T2_, LMI_INLINE_SOURCE_FILE)
#else
#define Define_LmiPair(T1_, T2_) /* defined as empty */
#define Define_LmiPairEqual(T1_, T2_) /* defined as empty */
#define Define_LmiPairLess(T1_, T2_) /* defined as empty */
#endif

#define Declare_LmiPairFuncs(T1_, T2_) \
	DeclareInline_LmiAssignable(LmiPair(T1_, T2_), LMI_INLINE_DECLARATION)	 \
	LMI_INLINE_DECLARATION LmiPair(T1_, T2_)* LmiPairConstruct(T1_, T2_)(LmiPair(T1_, T2_)* x, const T1_* first, const T2_* second); \
	DefineInlineHeader_LmiPair(T1_, T2_)

#define Declare_LmiPair(T1_, T2_) \
	Declare_LmiPairTypes(T1_, T2_) \
	Declare_LmiPairFuncs(T1_, T2_)

#define Declare_LmiPairEqual(T1_, T2_) \
	DeclareInline_LmiEqualityComparable(LmiPair(T1_, T2_), LMI_INLINE_DECLARATION) \
	DefineInlineHeader_LmiPairEqual(T1_, T2_)

#define Declare_LmiPairLess(T1_, T2_) \
	DeclareInline_LmiLessThanComparable(LmiPair(T1_, T2_), LMI_INLINE_DECLARATION) \
	DefineInlineHeader_LmiPairLess(T1_, T2_)

#endif
