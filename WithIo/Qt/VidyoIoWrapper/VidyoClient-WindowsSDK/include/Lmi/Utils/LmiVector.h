/**
{file: 
	{name: LmiVector.h}
	{description: Dynamic array container class.}
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

#if !defined(LMI_VECTOR_H_)
#define LMI_VECTOR_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAssert.h>
#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiContainers.h>
#include <Lmi/Utils/LmiIterators.h>
#include <Lmi/Utils/LmiAllocator.h>

LMI_BEGIN_EXTERN_C

/* Name mangling */
#define LmiVector(T_)											LmiTemplate1(LmiVector, T_)
#define LmiVectorSizeType(T_)									LmiClassType(LmiVector(T_), SizeType)
#define LmiVectorDifferenceType(T_)								LmiClassType(LmiVector(T_), DifferenceType)
#define LmiVectorDestruct(T_)									LmiClassFunc(LmiVector(T_), Destruct)
#define LmiVectorConstructDefault(T_)							LmiClassFunc(LmiVector(T_), ConstructDefault)
#define LmiVectorConstructN(T_)									LmiClassFunc(LmiVector(T_), ConstructN)
#define LmiVectorConstructRange(T_)								LmiClassFunc(LmiVector(T_), ConstructRange)
#define LmiVectorConstructRangeOther(T_, InputIterator_)		LmiClassTemplateFunc1(LmiVector(T_), ConstructRangeOther, InputIterator_)
#define LmiVectorConstructCopy(T_)								LmiClassFunc(LmiVector(T_), ConstructCopy)
#define LmiVectorConstructDeepCopy(T_)							LmiClassFunc(LmiVector(T_), ConstructDeepCopy)
#define LmiVectorGetAllocator(T_)								LmiClassFunc(LmiVector(T_), GetAllocator)
#define LmiVectorAssign(T_)										LmiClassFunc(LmiVector(T_), Assign)
#define LmiVectorSwap(T_)										LmiClassFunc(LmiVector(T_), Swap)
#define LmiVectorBegin(T_)										LmiClassFunc(LmiVector(T_), Begin)
#define LmiVectorBeginConst(T_)									LmiClassFunc(LmiVector(T_), BeginConst)
#define LmiVectorEnd(T_)										LmiClassFunc(LmiVector(T_), End)
#define LmiVectorEndConst(T_)									LmiClassFunc(LmiVector(T_), EndConst)
#define LmiVectorRBegin(T_)										LmiClassFunc(LmiVector(T_), RBegin)
#define LmiVectorRBeginConst(T_)								LmiClassFunc(LmiVector(T_), RBeginConst)
#define LmiVectorREnd(T_)										LmiClassFunc(LmiVector(T_), REnd)
#define LmiVectorREndConst(T_)									LmiClassFunc(LmiVector(T_), REndConst)
#define LmiVectorSize(T_)										LmiClassFunc(LmiVector(T_), Size)
#define LmiVectorMaxSize(T_)									LmiClassFunc(LmiVector(T_), MaxSize)
#define LmiVectorEmpty(T_)										LmiClassFunc(LmiVector(T_), Empty)
#define LmiVectorEqual(T_)										LmiClassFunc(LmiVector(T_), Equal)
#define LmiVectorEqualComp(T_, Comp_)							LmiClassTemplateFunc1(LmiVector(T_), EqualComp, Comp_)
#define LmiVectorLess(T_)										LmiClassFunc(LmiVector(T_), Less)
#define LmiVectorLessComp(T_, Comp_)							LmiClassTemplateFunc1(LmiVector(T_), LessComp, Comp_)
#define LmiVectorAt(T_)											LmiClassFunc(LmiVector(T_), At)
#define LmiVectorAtConst(T_)									LmiClassFunc(LmiVector(T_), AtConst)
#define LmiVectorFront(T_)										LmiClassFunc(LmiVector(T_), Front)
#define LmiVectorFrontConst(T_)									LmiClassFunc(LmiVector(T_), FrontConst)
#define LmiVectorBack(T_)										LmiClassFunc(LmiVector(T_), Back)
#define LmiVectorBackConst(T_)									LmiClassFunc(LmiVector(T_), BackConst)
#define LmiVectorInsert(T_)										LmiClassFunc(LmiVector(T_), Insert)
#define LmiVectorInsertN(T_)									LmiClassFunc(LmiVector(T_), InsertN)
#define LmiVectorInsertRange(T_)								LmiClassFunc(LmiVector(T_), InsertRange)
#define LmiVectorErase(T_)										LmiClassFunc(LmiVector(T_), Erase)
#define LmiVectorEraseRange(T_)									LmiClassFunc(LmiVector(T_), EraseRange)
#define LmiVectorClear(T_)										LmiClassFunc(LmiVector(T_), Clear)
#define LmiVectorResize(T_)										LmiClassFunc(LmiVector(T_), Resize)
#define LmiVectorPushBack(T_)									LmiClassFunc(LmiVector(T_), PushBack)
#define LmiVectorPopBack(T_)									LmiClassFunc(LmiVector(T_), PopBack)
#define LmiVectorCapacity(T_)									LmiClassFunc(LmiVector(T_), Capacity)
#define LmiVectorReserve(T_)									LmiClassFunc(LmiVector(T_), Reserve)
#define LmiVectorDump(T_)										LmiClassFunc(LmiVector(T_), Dump)

#define LmiVectorIterator(T_)									LmiIterator(LmiVector(T_))
#define LmiVectorIteratorValueType(T_)							LmiClassType(LmiVectorIterator(T_), ValueType)
#define LmiVectorIteratorPointer(T_)							LmiClassType(LmiVectorIterator(T_), Pointer)
#define LmiVectorIteratorDifferenceType(T_)						LmiClassType(LmiVectorIterator(T_), DifferenceType)
#define LmiVectorIteratorConstructCopy(T_)						LmiClassFunc(LmiVectorIterator(T_), ConstructCopy)
#define LmiVectorIteratorConstructExceptional(T_)				LmiClassFunc(LmiVectorIterator(T_), ConstructExceptional)
#define LmiVectorIteratorDestruct(T_)							LmiClassFunc(LmiVectorIterator(T_), Destruct)
#define LmiVectorIteratorAssign(T_)								LmiClassFunc(LmiVectorIterator(T_), Assign)
#define LmiVectorIteratorSwap(T_)								LmiClassFunc(LmiVectorIterator(T_), Swap)
#define LmiVectorIteratorEqual(T_)								LmiClassFunc(LmiVectorIterator(T_), Equal)
#define LmiVectorIteratorLess(T_)								LmiClassFunc(LmiVectorIterator(T_), Less)
#define LmiVectorIteratorContentOf(T_)							LmiClassFunc(LmiVectorIterator(T_), ContentOf)
#define LmiVectorIteratorContentOfConst(T_)						LmiClassFunc(LmiVectorIterator(T_), ContentOfConst)
#define LmiVectorIteratorIncrement(T_)							LmiClassFunc(LmiVectorIterator(T_), Increment)
#define LmiVectorIteratorDecrement(T_)							LmiClassFunc(LmiVectorIterator(T_), Decrement)
#define LmiVectorIteratorIncrementN(T_)							LmiClassFunc(LmiVectorIterator(T_), IncrementN)
#define LmiVectorIteratorDecrementN(T_)							LmiClassFunc(LmiVectorIterator(T_), DecrementN)
#define LmiVectorIteratorAt(T_)									LmiClassFunc(LmiVectorIterator(T_), At)
#define LmiVectorIteratorAdd(T_)								LmiClassFunc(LmiVectorIterator(T_), Add)
#define LmiVectorIteratorSubtract(T_)							LmiClassFunc(LmiVectorIterator(T_), Subtract)
#define LmiVectorIteratorIsExceptional(T_)						LmiClassFunc(LmiVectorIterator(T_), IsExceptional)

#define LmiVectorConstIterator(T_)								LmiConstIterator(LmiVector(T_))
#define LmiVectorConstIteratorValueType(T_)						LmiClassType(LmiVectorConstIterator(T_), ValueType)
#define LmiVectorConstIteratorPointer(T_)						LmiClassType(LmiVectorConstIterator(T_), Pointer)
#define LmiVectorConstIteratorDifferenceType(T_)				LmiClassType(LmiVectorConstIterator(T_), DifferenceType)
#define LmiVectorConstIteratorConstructCopy(T_)					LmiClassFunc(LmiVectorConstIterator(T_), ConstructCopy)
#define LmiVectorConstIteratorConstructExceptional(T_)			LmiClassFunc(LmiVectorConstIterator(T_), ConstructExceptional)
#define LmiVectorConstIteratorDestruct(T_)						LmiClassFunc(LmiVectorConstIterator(T_), Destruct)
#define LmiVectorConstIteratorAssign(T_)						LmiClassFunc(LmiVectorConstIterator(T_), Assign)
#define LmiVectorConstIteratorSwap(T_)							LmiClassFunc(LmiVectorConstIterator(T_), Swap)
#define LmiVectorConstIteratorEqual(T_)							LmiClassFunc(LmiVectorConstIterator(T_), Equal)
#define LmiVectorConstIteratorLess(T_)							LmiClassFunc(LmiVectorConstIterator(T_), Less)
#define LmiVectorConstIteratorContentOf(T_)						LmiClassFunc(LmiVectorConstIterator(T_), ContentOf)
#define LmiVectorConstIteratorContentOfConst(T_)				LmiClassFunc(LmiVectorConstIterator(T_), ContentOfConst)
#define LmiVectorConstIteratorIncrement(T_)						LmiClassFunc(LmiVectorConstIterator(T_), Increment)
#define LmiVectorConstIteratorDecrement(T_)						LmiClassFunc(LmiVectorConstIterator(T_), Decrement)
#define LmiVectorConstIteratorIncrementN(T_)					LmiClassFunc(LmiVectorConstIterator(T_), IncrementN)
#define LmiVectorConstIteratorDecrementN(T_)					LmiClassFunc(LmiVectorConstIterator(T_), DecrementN)
#define LmiVectorConstIteratorAt(T_)							LmiClassFunc(LmiVectorConstIterator(T_), At)
#define LmiVectorConstIteratorAdd(T_)							LmiClassFunc(LmiVectorConstIterator(T_), Add)
#define LmiVectorConstIteratorSubtract(T_)						LmiClassFunc(LmiVectorConstIterator(T_), Subtract)
#define LmiVectorConstIteratorIsExceptional(T_)					LmiClassFunc(LmiVectorConstIterator(T_), IsExceptional)

#define LmiVectorReverseIterator(T_)							LmiReverseIterator(LmiVector(T_))
#define LmiVectorReverseIteratorValueType(T_)					LmiClassType(LmiVectorReverseIterator(T_), ValueType)
#define LmiVectorReverseIteratorPointer(T_)						LmiClassType(LmiVectorReverseIterator(T_), Pointer)
#define LmiVectorReverseIteratorDifferenceType(T_)				LmiClassType(LmiVectorReverseIterator(T_), DifferenceType)
#define LmiVectorReverseIteratorConstructCopy(T_)				LmiClassFunc(LmiVectorReverseIterator(T_), ConstructCopy)
#define LmiVectorReverseIteratorConstructExceptional(T_)		LmiClassFunc(LmiVectorReverseIterator(T_), ConstructExceptional)
#define LmiVectorReverseIteratorDestruct(T_)					LmiClassFunc(LmiVectorReverseIterator(T_), Destruct)
#define LmiVectorReverseIteratorAssign(T_)						LmiClassFunc(LmiVectorReverseIterator(T_), Assign)
#define LmiVectorReverseIteratorSwap(T_)						LmiClassFunc(LmiVectorReverseIterator(T_), Swap)
#define LmiVectorReverseIteratorEqual(T_)						LmiClassFunc(LmiVectorReverseIterator(T_), Equal)
#define LmiVectorReverseIteratorLess(T_)						LmiClassFunc(LmiVectorReverseIterator(T_), Less)
#define LmiVectorReverseIteratorContentOf(T_)					LmiClassFunc(LmiVectorReverseIterator(T_), ContentOf)
#define LmiVectorReverseIteratorContentOfConst(T_)				LmiClassFunc(LmiVectorReverseIterator(T_), ContentOfConst)
#define LmiVectorReverseIteratorIncrement(T_)					LmiClassFunc(LmiVectorReverseIterator(T_), Increment)
#define LmiVectorReverseIteratorDecrement(T_)					LmiClassFunc(LmiVectorReverseIterator(T_), Decrement)
#define LmiVectorReverseIteratorIncrementN(T_)					LmiClassFunc(LmiVectorReverseIterator(T_), IncrementN)
#define LmiVectorReverseIteratorDecrementN(T_)					LmiClassFunc(LmiVectorReverseIterator(T_), DecrementN)
#define LmiVectorReverseIteratorAt(T_)							LmiClassFunc(LmiVectorReverseIterator(T_), At)
#define LmiVectorReverseIteratorAdd(T_)							LmiClassFunc(LmiVectorReverseIterator(T_), Add)
#define LmiVectorReverseIteratorSubtract(T_)					LmiClassFunc(LmiVectorReverseIterator(T_), Subtract)
#define LmiVectorReverseIteratorIsExceptional(T_)				LmiClassFunc(LmiVectorReverseIterator(T_), IsExceptional)

#define LmiVectorConstReverseIterator(T_)						LmiConstReverseIterator(LmiVector(T_))
#define LmiVectorConstReverseIteratorValueType(T_)				LmiClassType(LmiVectorConstReverseIterator(T_), ValueType)
#define LmiVectorConstReverseIteratorPointer(T_)				LmiClassType(LmiVectorConstReverseIterator(T_), Pointer)
#define LmiVectorConstReverseIteratorDifferenceType(T_)			LmiClassType(LmiVectorConstReverseIterator(T_), DifferenceType)
#define LmiVectorConstReverseIteratorConstructCopy(T_)			LmiClassFunc(LmiVectorConstReverseIterator(T_), ConstructCopy)
#define LmiVectorConstReverseIteratorConstructExceptional(T_)	LmiClassFunc(LmiVectorConstReverseIterator(T_), ConstructExceptional)
#define LmiVectorConstReverseIteratorDestruct(T_)				LmiClassFunc(LmiVectorConstReverseIterator(T_), Destruct)
#define LmiVectorConstReverseIteratorAssign(T_)					LmiClassFunc(LmiVectorConstReverseIterator(T_), Assign)
#define LmiVectorConstReverseIteratorSwap(T_)					LmiClassFunc(LmiVectorConstReverseIterator(T_), Swap)
#define LmiVectorConstReverseIteratorEqual(T_)					LmiClassFunc(LmiVectorConstReverseIterator(T_), Equal)
#define LmiVectorConstReverseIteratorLess(T_)					LmiClassFunc(LmiVectorConstReverseIterator(T_), Less)
#define LmiVectorConstReverseIteratorContentOf(T_)				LmiClassFunc(LmiVectorConstReverseIterator(T_), ContentOf)
#define LmiVectorConstReverseIteratorContentOfConst(T_)			LmiClassFunc(LmiVectorConstReverseIterator(T_), ContentOfConst)
#define LmiVectorConstReverseIteratorIncrement(T_)				LmiClassFunc(LmiVectorConstReverseIterator(T_), Increment)
#define LmiVectorConstReverseIteratorDecrement(T_)				LmiClassFunc(LmiVectorConstReverseIterator(T_), Decrement)
#define LmiVectorConstReverseIteratorIncrementN(T_)				LmiClassFunc(LmiVectorConstReverseIterator(T_), IncrementN)
#define LmiVectorConstReverseIteratorDecrementN(T_)				LmiClassFunc(LmiVectorConstReverseIterator(T_), DecrementN)
#define LmiVectorConstReverseIteratorAt(T_)						LmiClassFunc(LmiVectorConstReverseIterator(T_), At)
#define LmiVectorConstReverseIteratorAdd(T_)					LmiClassFunc(LmiVectorConstReverseIterator(T_), Add)
#define LmiVectorConstReverseIteratorSubtract(T_)				LmiClassFunc(LmiVectorConstReverseIterator(T_), Subtract)
#define LmiVectorConstReverseIteratorIsExceptional(T_)			LmiClassFunc(LmiVectorConstReverseIterator(T_), IsExceptional)

/***** Declarations *****/

/**
{type:
	{name: LmiVector}
	{parent: Containers}
	{include: Lmi/Utils/LmiVector.h}
	{description: A parameterized vector container class.}
	{template-prototype: LmiVector(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the vector.}
	}
	{note: 
		This is a LmiRandomAccessContainer and LmiBackInsertionSequence; see 
		LmiContainers and the STL.
	}
	{note: 
		The macro Declare_LmiVector must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type:
	{name: LmiVectorSizeType}
	{parent: LmiVector}
	{description: The size type of a vector.  It is equivalent to the type LmiSizeT.}
	{template-prototype: LmiVectorSizeType(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type:
	{name: LmiVectorDifferenceType}
	{parent: LmiVector}
	{description: The difference type of a vector. It is equivalent to the type LmiDistanceT.}
	{template-prototype: LmiVectorDifferenceType(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type:
	{name: LmiVectorIterator}
	{parent: LmiVector}
	{model-of: LmiRandomAccessIterator}
	{description: The iterator type of a vector.}
	{template-prototype: LmiVectorIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type:
	{name: LmiVectorConstIterator}
	{parent: LmiVector}
	{model-of: LmiRandomAccessIterator}
	{description: The read-only iterator type of a vector.}
	{template-prototype: LmiVectorConstIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type:
	{name: LmiVectorReverseIterator}
	{parent: LmiVector}
	{model-of: LmiReverseBidirectionalIterator}
	{description: The reverse iterator type of a vector.}
	{template-prototype: LmiVectorReverseIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type:
	{name: LmiVectorConstReverseIterator}
	{parent: LmiVector}
	{model-of: LmiReverseBidirectionalIterator}
	{description: The read-only reverse iterator type of a vector.}
	{template-prototype: LmiVectorConstReverseIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{function validate="no":
	{name: Declare_LmiVector}
	{parent: LmiVector}
	{description: Declare a parameterized vector container and its subtypes.}
	{prototype: void Declare_LmiVector(Type T)}
	{parameter:
		{name: T} 
		{description: The type stored in the vector.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate a vector of integers *\/
		Declare_LmiVector(LmiInt)
		LmiVector(LmiInt) numbers;
	}
}
*/

/****** Definitions ******/

/**
{function:
	{name: LmiVectorDestruct}
	{parent: LmiVector}
	{description: Destruct a vector.}
	{prototype: void LmiVectorDestruct(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to destruct. }
	}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorDestruct(T_, STATIC_) \
	STATIC_ void LmiVectorDestruct(T_)(LmiVector(T_)* x) { \
		LmiVectorClear(T_)(x); \
		if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, (x->endBuf - x->begin) * sizeof(T_)); \
	}

/**
{function:
	{name: LmiVectorConstructDefault}
	{parent: LmiVector}
	{description: Construct an empty vector.}
	{prototype: LmiVector(T_)* LmiVectorConstructDefault(T_)(LmiVector(T_)* x, LmiAllocator* a)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to construct.}
	}
	{parameter:
		{name: a}
		{description: The vector's allocator.}
	}
	{return: A pointer to the constructed vector or NULL on error.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorConstructDefault(T_, INLINE_)						\
	INLINE_ LmiVector(T_)* LmiVectorConstructDefault(T_)(LmiVector(T_)* x, LmiAllocator* a) { \
		x->allocator = a; \
		x->begin = x->end = x->endBuf = NULL; \
		return x; \
	}

/**
{function:
	{name: LmiVectorConstructN}
	{parent: LmiVector}
	{description: Construct a vector and initialize the first {italic:n} entries in the vector with copies of {italic:t}.}
	{prototype: LmiVector(T_)* LmiVectorConstructN(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n, const T_* t, LmiAllocator* a)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to construct.}
	}
	{parameter:
		{name: n}
		{description: The number of entries in the vector to initialize.}
	}
	{parameter:
		{name: t}
		{description: The value to initialize the entries in the vector.}
	}
	{parameter:
		{name: a}
		{description: The vector's allocator.}
	}
	{return: A pointer to the constructed vector or NULL on error.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorConstructN(T_, STATIC_) \
	STATIC_ LmiVector(T_)* LmiVectorConstructN(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n, const T_* t, LmiAllocator* a) { \
		x->allocator = a; \
		if (n == 0) { \
			x->begin = x->end = NULL; \
		} else { \
			x->begin = x->end = (T_*)LmiAllocatorAllocate(x->allocator, n * sizeof(T_)); \
			if (x->begin == NULL) return NULL; /* Error */ \
		} \
		x->endBuf = x->begin + n; \
		for (; n > 0; --n, ++(x->end)) { \
			if (LmiConstructCopy(T_)(x->end, t) == NULL) { /* Error */ \
				for (--(x->end); x->end >= x->begin; --(x->end)) LmiDestruct(T_)(x->end); \
				LmiAllocatorDeallocate(x->allocator, x->begin, n * sizeof(T_)); \
				return NULL; \
			} \
		} \
		return x; \
	}

/**
{function:
	{name: LmiVectorConstructRange}
	{parent: LmiVector}
	{description: Construct a vector and initialize it with the range specified.}
	{prototype: LmiVector(T_)* LmiVectorConstructRange(T_)(LmiVector(T_)* x, LmiVectorConstIterator(T_) first, LmiVectorConstIterator(T_) last, LmiAllocator* a)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to construct.}
	}
	{parameter:
		{name: first}
		{description: A read-only random-access iterator to the first element in the range used to initialize the vector.}
	}
	{parameter:
		{name: last}
		{description: A read-only random-access iterator one past the last element in the range used to initialize the vector.}
	}
	{parameter:
		{name: a}
		{description: The vector's allocator.}
	}
	{return: A pointer to the constructed vector or NULL on error.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorConstructRange(T_, STATIC_) \
	STATIC_ LmiVector(T_)* LmiVectorConstructRange(T_)(LmiVector(T_)* x, LmiVectorConstIterator(T_) first, LmiVectorConstIterator(T_) last, LmiAllocator* a) { \
		LmiVectorDifferenceType(T_) n = last - first; \
		LmiAssert(first <= last); \
		x->allocator = a; \
		if (n != 0) { \
			x->begin = x->end = (T_*)LmiAllocatorAllocate(x->allocator, n * sizeof(T_)); \
			if (x->begin == NULL) return NULL; /* Error */ \
		} else \
			x->begin = x->end = NULL; \
		x->endBuf = x->begin + n; \
		for (; first != last; ++first, ++(x->end)) \
			if (LmiConstructCopy(T_)(x->end, first) == NULL) { /* Error */ \
				for(--(x->end); x->end >= x->begin; --(x->end)) LmiDestruct(T_)(x->end); \
				LmiAllocatorDeallocate(x->allocator, x->begin, n * sizeof(T_)); \
				return NULL; \
			} \
		return x; \
	}

/**
{function:
	{name: LmiVectorConstructRangeOther}
	{parent: LmiVector}
	{description: Construct a vector from a range of another container type.}
	{prototype: LmiVector(T_)* LmiVectorConstructRangeOther(T_, InputIterator_)(LmiVector(T_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* a)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
 	{template-parameter:
		{name: InputIterator_}
		{description: The input iterator of range.}
	}
	{parameter:
		{name: x}
		{description: The vector to construct.}
	}
	{parameter:
		{name: first}
		{description: A read-only input iterator to the first element in the range used to initialize the vector.}
	}
	{parameter:
		{name: last}
		{description: A read-only input iterator one past the last element in the range used to initialize the vector.}
	}
	{parameter:
		{name: a}
		{description: The vector's allocator.}
	}
	{return: A pointer to the constructed vector or NULL on error.}
	{note: 
 		The macro Declare_LmiVectorConstructRangeOther must be called at global scope before calling
		LmiVectorConstructRangeOther member functions.  LmiVectorConstructRangeOther is not included 
 		in the default set of LmiVector functions.
	}
}
*/
#define Define_LmiVectorConstructRangeOther_(T_, InputIterator_, STATIC_) \
	STATIC_ LmiVector(T_)* LmiVectorConstructRangeOther(T_, InputIterator_)(LmiVector(T_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* a) { \
		x->allocator = a; \
		x->begin = x->end = x->endBuf = NULL; \
		for (; !LmiEqual(InputIterator_)(&first, &last); LmiIncrement(InputIterator_)(&first)) { \
			T_* t = LmiContentOf(InputIterator_)(&first); \
			if (!LmiVectorPushBack(T_)(x, t)) { /* Error */ \
				LmiVectorClear(T_)(x); \
				if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, (x->endBuf - x->begin) * sizeof(T_)); \
				return NULL; \
			} \
		} \
		return x; \
	}

/**
{function:
	{name: LmiVectorConstructCopy}
	{parent: LmiVector}
	{description: Construct a vector from another vector.}
	{prototype: LmiVector(T_)* LmiVectorConstructCopy(T_)(LmiVector(T_)* x, const LmiVector(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to construct.}
	}
	{parameter:
		{name: y}
		{description: The vector to use to initialize the vector being constructed.}
	}
	{return: A pointer to the constructed vector or NULL on error.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorConstructCopy(T_, STATIC_) \
	STATIC_ LmiVector(T_)* LmiVectorConstructCopy(T_)(LmiVector(T_)* x, const LmiVector(T_)* y) { \
		LmiVectorSizeType(T_) yn = y->end - y->begin; \
		T_* p; \
		x->allocator = y->allocator; \
		if (yn != 0) { \
			x->begin = x->end = (T_*)LmiAllocatorAllocate(x->allocator, yn * sizeof(T_)); \
			if (x->begin == NULL) return NULL; /* Error */ \
			x->endBuf = x->begin + yn; \
			for (p = y->begin; p != y->end; ++p, ++(x->end)) \
				if (LmiConstructCopy(T_)(x->end, p) == NULL) { /* Error */ \
					for(--(x->end); x->end >= x->begin; --(x->end)) LmiDestruct(T_)(x->end); \
					LmiAllocatorDeallocate(x->allocator, x->begin, yn * sizeof(T_)); \
					return NULL; \
				} \
		} else { \
			x->begin = x->end = x->endBuf = NULL; \
		} \
		return x; \
	}

/**
{function:
	{name: LmiVectorAssign}
	{parent: LmiVector}
	{description: Copy one vector to another.}
	{prototype: LmiVector(T_)* LmiVectorAssign(T_)(LmiVector(T_)* x, const LmiVector(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to assign to.}
	}
	{parameter:
		{name: y}
		{description: The vector to assign from.}
	}
	{return: A pointer to the assigned to vector or NULL on error.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorAssign(T_, STATIC_) \
	STATIC_ LmiVector(T_)* LmiVectorAssign(T_)(LmiVector(T_)* x, const LmiVector(T_)* y) { \
		LmiVectorSizeType(T_) yn; \
		LmiVectorSizeType(T_) capacity; \
		T_* xp, * yp; \
		if (x == y) return x; \
		yn = y->end - y->begin; \
		capacity = x->endBuf - x->begin; \
		if (yn > capacity) { \
			LmiVectorClear(T_)(x); \
			if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, capacity * sizeof(T_)); \
			x->begin = x->end = (T_*)LmiAllocatorAllocate(x->allocator, yn * sizeof(T_)); \
			if (x->begin == 0) return NULL; /* Error */ \
			x->endBuf = x->begin + yn; \
			for (yp = y->begin; yp != y->end; ++yp, ++(x->end)) \
				if (LmiConstructCopy(T_)(x->end, yp)== NULL) return NULL; /* Error */ \
		} else { \
			for (xp = x->begin, yp = y->begin; (xp != x->end) && (yp != y->end); ++xp, ++yp) \
				if (LmiAssign(T_)(xp, yp) == NULL) return NULL; /* Error */ \
			/* Destination is bigger than source */ \
			while (xp != x->end) { --(x->end); LmiDestruct(T_)(x->end); } \
			/* Source is bigger than destination */ \
			for (; (yp != y->end); ++yp, ++(x->end)) \
				if (LmiConstructCopy(T_)(x->end, yp) == NULL) return NULL; /* Error */ \
		} \
		return x; \
	}

/**
{function:
	{name: LmiVectorSwap}
	{parent: LmiVector}
	{description: Swap two vectors.}
	{prototype: LmiBool LmiVectorSwap(T_)(LmiVector(T_)* x, LmiVector(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to swap.}
	}
	{parameter:
		{name: y}
		{description: The other vector to swap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorSwap(T_, STATIC_) \
	STATIC_ LmiBool LmiVectorSwap(T_)(LmiVector(T_)* x, LmiVector(T_)* y) { \
		LmiVectorSizeType(T_) xn = x->end - x->begin; \
		LmiVectorSizeType(T_) yn = y->end - y->begin; \
		if ((xn == 0) && (yn == 0)) { \
			return LMI_TRUE; \
		} else if (x->allocator == y->allocator) { \
			LmiVector(T_) z = *x; *x = *y; *y = z; \
		} else { \
			T_* s, * d, * b; \
			LmiVectorSizeType(T_) n; \
			if (xn < yn) { \
				n = yn; \
				b = (T_*)LmiAllocatorAllocate(x->allocator, n * sizeof(T_)); \
				if (b == 0) goto FAIL0; /* Error */ \
				/* Copy vector y to temporary buffer */ \
				for (s = y->begin, d = b; s != y->end; ++s, ++d) \
					if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL2; /* Error */ \
				/* Copy vector x to vector y */ \
				LmiVectorClear(T_)(y); \
				for (s = x->begin; s != x->end; ++s, ++(y->end)) \
					if (LmiAssign(T_)(y->end, s) == NULL) goto FAIL2; /* Error */ \
				/* Replace vector x's buffer with the temporary buffer */ \
				if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, xn * sizeof(T_)); \
				x->begin = b; \
				x->end = x->begin + yn; \
				x->endBuf = x->begin + yn; \
			} else { \
				n = xn; \
				b = (T_*)LmiAllocatorAllocate(x->allocator, n * sizeof(T_)); \
				if (b == 0) goto FAIL0; /* Error */ \
				/* Copy vector x to temporary buffer */ \
				for (s = x->begin, d = b; s != x->end; ++s, ++d) \
					if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL2; /* Error */ \
				/* Copy vector y to vector x */ \
				LmiVectorClear(T_)(x); \
				for (s = y->begin; s != y->end; ++s, ++(x->end)) \
					if (LmiAssign(T_)(x->end, s) == NULL) goto FAIL2; /* Error */ \
				/* Replace vector y's buffer with the temporary buffer */ \
				if (y->begin) LmiAllocatorDeallocate(y->allocator, y->begin, yn * sizeof(T_)); \
				y->begin = b; \
				y->end = y->begin + xn; \
				y->endBuf = y->begin + xn; \
			} \
			return LMI_TRUE; \
		FAIL2: \
			for (--d; d >= b; --d) LmiDestruct(T_)(d); \
			LmiAllocatorDeallocate(x->allocator, b, n * sizeof(T_)); \
		FAIL0: \
			return LMI_FALSE; \
		} \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiVectorGetAllocator}
	{parent: LmiVector}
	{description: Gets a pointer to the vector's allocator.}
	{prototype: LmiAllocator* LmiVectorGetAllocator(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A pointer to the vector's allocator.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorGetAllocator(T_, INLINE_) \
	INLINE_ LmiAllocator* LmiVectorGetAllocator(T_)(const LmiVector(T_)* x) { return x->allocator; }

/**
{function:
	{name: LmiVectorBegin}
	{parent: LmiVector}
	{description: Gets an iterator to the first element in the vector.}
	{prototype: LmiVectorIterator(T_) LmiVectorBegin(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: An iterator to the first element in the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorBegin(T_, INLINE_)                                \
	INLINE_ LmiVectorIterator(T_) LmiVectorBegin(T_)(LmiVector(T_)* x) { return x->begin; }

/**
{function:
	{name: LmiVectorBeginConst}
	{parent: LmiVector}
	{description: Gets a read-only iterator to the first element in the vector.}
	{prototype: LmiVectorConstIterator(T_) LmiVectorBeginConst(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A read-only iterator to the first element in the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorBeginConst(T_, INLINE_)                           \
	INLINE_ LmiVectorConstIterator(T_) LmiVectorBeginConst(T_)(const LmiVector(T_)* x) { return x->begin; }

/**
{function:
	{name: LmiVectorEnd}
	{parent: LmiVector}
	{description: Gets an iterator to the element one past the last element in the vector.}
	{prototype: LmiVectorIterator(T_) LmiVectorEnd(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: An iterator to the element one past the last element in the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorEnd(T_, INLINE_)                                  \
	INLINE_ LmiVectorIterator(T_) LmiVectorEnd(T_)(LmiVector(T_)* x) { return x->end; }

/**
{function:
	{name: LmiVectorEndConst}
	{parent: LmiVector}
	{description: Gets a read-only iterator to the element one past the last element in the vector.}
	{prototype: LmiVectorConstIterator(T_) LmiVectorEndConst(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A read-only iterator to the element one past the last element in the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorEndConst(T_, INLINE_)                             \
	INLINE_ LmiVectorConstIterator(T_) LmiVectorEndConst(T_)(const LmiVector(T_)* x) { return x->end; }

/**
{function:
	{name: LmiVectorRBegin}
	{parent: LmiVector}
	{description: Gets a reverse iterator to the first element in the reversed vector.}
	{prototype: LmiVectorReverseIterator(T_) LmiVectorRBegin(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A reverse iterator to the first element in the reversed vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorRBegin(T_, INLINE_)                               \
	INLINE_ LmiVectorReverseIterator(T_) LmiVectorRBegin(T_)(LmiVector(T_)* x) { return x->end; }

/**
{function:
	{name: LmiVectorRBeginConst}
	{parent: LmiVector}
	{description: Gets a read-only reverse iterator to the first element in the reversed vector.}
	{prototype: LmiVectorConstReverseIterator(T_) LmiVectorRBeginConst(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A read-only reverse iterator to the first element in the reversed vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorRBeginConst(T_, INLINE_)                                \
	INLINE_ LmiVectorConstReverseIterator(T_) LmiVectorRBeginConst(T_)(const LmiVector(T_)* x) { return x->end; }

/**
{function:
	{name: LmiVectorREnd}
	{parent: LmiVector}
	{description: Gets a reverse iterator to the element one past the last element in the reversed vector.}
	{prototype: LmiVectorReverseIterator(T_) LmiVectorREnd(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A reverse iterator to the element one past the last element in the reversed vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorREnd(T_, INLINE_)                                 \
	INLINE_ LmiVectorReverseIterator(T_) LmiVectorREnd(T_)(LmiVector(T_)* x) { return x->begin; }

/**
{function:
	{name: LmiVectorREndConst}
	{parent: LmiVector}
	{description: Gets a read-only reverse iterator to the element one past the last element in the reversed vector.}
	{prototype: LmiVectorConstReverseIterator(T_) LmiVectorREndConst(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A read-only reverse iterator to the element one past the last element in the reversed vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorREndConst(T_, INLINE_)                                  \
	INLINE_ LmiVectorConstReverseIterator(T_) LmiVectorREndConst(T_)(const LmiVector(T_)* x) { return x->begin; }

/**
{function:
	{name: LmiVectorSize}
	{parent: LmiVector}
	{description: Gets the number of elements in the vector.}
	{prototype: LmiVectorSizeType(T_) LmiVectorSize(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: The number of elements in the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorSize(T_, INLINE_)                                       \
	INLINE_ LmiVectorSizeType(T_) LmiVectorSize(T_)(const LmiVector(T_)* x) { return x->end - x->begin; }

/**
{function:
	{name: LmiVectorMaxSize}
	{parent: LmiVector}
	{description: Gets the maximum number of elements the vector could contain.}
	{prototype: LmiVectorSizeType(T_) LmiVectorMaxSize(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: The maximum number of elements the vector could contain.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorMaxSize(T_, INLINE_)                                    \
	INLINE_ LmiVectorSizeType(T_) LmiVectorMaxSize(T_)(const LmiVector(T_)* x) { return (~0U) / sizeof(T_); }

/**
{function:
	{name: LmiVectorEmpty}
	{parent: LmiVector}
	{description: Test whether or not a vector is empty.}
	{prototype: LmiBool LmiVectorEmpty(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to test.}
	}
	{return: LMI_TRUE if the vector is empty or LMI_FALSE if it is not.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorEmpty(T_, INLINE_)                                      \
	INLINE_ LmiBool LmiVectorEmpty(T_)(const LmiVector(T_)* x) { return x->begin == x->end; }

/**
{function:
	{name: LmiVectorEqual}
	{parent: LmiVector}
	{description: Test two vectors for equality.}
	{prototype: LmiBool LmiVectorEqual(T_)(const LmiVector(T_)* x, const LmiVector(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to compare.}
	}
	{parameter:
		{name: y}
		{description: The other vector to compare.}
	}
	{return: LMI_TRUE if the vectors are equal or LMI_FALSE if they are not.}
	{note:
		The macro Declare_LmiVectorEqual must be called at global scope before calling 
		LmiVectorEqual member functions.  LmiVectorEqual is not included in the
		default set of LmiVector functions.  It requires that the contained
		type have an Equal member function.
	}
}
*/
#define Define_LmiVectorEqual_(T_, NAME_, COMP_, STATIC_) \
	STATIC_ LmiBool NAME_(const LmiVector(T_)* x, const LmiVector(T_)* y) { \
		if (LmiVectorSize(T_)(x) == LmiVectorSize(T_)(y)) { \
			T_* p, * q; \
			for (p = x->begin, q = y->begin; (p != x->end) && (q != y->end); ++p, ++q) { \
				if (!COMP_(p, q)) \
					return LMI_FALSE; \
			} \
		} else \
			return LMI_FALSE;\
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiVectorLess}
	{parent: LmiVector}
	{description: Test whether one vector is lexicographically less than another.}
	{prototype: LmiBool LmiVectorLess(T_)(const LmiVector(T_)* x, const LmiVector(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector to compare.}
	}
	{parameter:
		{name: y}
		{description: The other vector to compare.}
	}
	{return: LMI_TRUE if the first vector is lexicographically less than the second vector or LMI_FALSE if it is not.}
	{note: 
		The macro Declare_LmiVectorLess must be called at global scope before calling
		LmiVectorLess member functions.  LmiVectorLess is not included in the
		default set of LmiVector functions.  It requires that the contained
		type be less-than comparable (i.e. have a Less member function).
	}
	{note: Equivalent to calling LmiLexicographicalCompare with the entire range of each vector.}
}
*/
#define Define_LmiVectorLess_(T_, NAME_, COMP_, STATIC_) \
	STATIC_ LmiBool NAME_(const LmiVector(T_)* x, const LmiVector(T_)* y) { \
		T_ *xp = x->begin, *yp = y->begin; \
		for(;;) \
		{ \
			if(yp == y->end) \
				return LMI_FALSE; \
			if(xp == x->end) \
				return LMI_TRUE; \
			if(COMP_(xp, yp)) \
				return LMI_TRUE; \
			if(COMP_(yp, xp)) \
				return LMI_FALSE; \
			++xp, ++yp; \
		} \
	}

/**
{function:
	{name: LmiVectorAt}
	{parent: LmiVector}
	{description: Retrieve a pointer to the element of the vector at index {italic:n}.}
	{prototype: T_* LmiVectorAt(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: n}
		{description: The index of the element to retrieve.}
	}
	{return: A pointer to the element of the vector at index {italic:n}.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorAt(T_, INLINE_)                                         \
	INLINE_ T_* LmiVectorAt(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n) { return x->begin + n; }	/* Add assert */

/**
{function:
	{name: LmiVectorAtConst}
	{parent: LmiVector}
	{description: Retrieve a read-only pointer to the element of the vector at index {italic:n}.}
	{prototype: const T_* LmiVectorAtConst(T_)(const LmiVector(T_)* x, LmiVectorSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: n}
		{description: The index of the element to retrieve.}
	}
	{return: A read-only pointer to the element of the vector at index {italic:n}.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorAtConst(T_, INLINE_)                              \
	INLINE_ const T_* LmiVectorAtConst(T_)(const LmiVector(T_)* x, LmiVectorSizeType(T_) n) { return x->begin + n; }	/* Add assert */

/**
{function:
	{name: LmiVectorFront}
	{parent: LmiVector}
	{description: Retrieve a pointer to the first element of the vector.}
	{prototype: T_* LmiVectorFront(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A pointer to the first element of the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorFront(T_, INLINE_)                                      \
	INLINE_ T_* LmiVectorFront(T_)(LmiVector(T_)* x) { return x->begin; }

/**
{function:
	{name: LmiVectorFrontConst}
	{parent: LmiVector}
	{description: Retrieve a read-only pointer to the first element of the vector.}
	{prototype: const T_* LmiVectorFrontConst(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A read-only pointer to the first element of the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorFrontConst(T_, INLINE_)                                 \
	INLINE_ const T_* LmiVectorFrontConst(T_)(const LmiVector(T_)* x) { return x->begin; }

/**
{function:
	{name: LmiVectorBack}
	{parent: LmiVector}
	{description: Retrieve a pointer to the last element of the vector.}
	{prototype: T_* LmiVectorBack(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A pointer to the last element of the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorBack(T_, INLINE_)                                       \
	INLINE_ T_* LmiVectorBack(T_)(LmiVector(T_)* x) { return (x->end) - 1; }

/**
{function:
	{name: LmiVectorBackConst}
	{parent: LmiVector}
	{description: Retrieve a read-only pointer to the last element of the vector.}
	{prototype: const T_* LmiVectorBackConst(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: A read-only pointer to the last element of the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorBackConst(T_, INLINE_)                                  \
	INLINE_ const T_* LmiVectorBackConst(T_)(const LmiVector(T_)* x) { return (x->end) - 1; }

/**
{function:
	{name: LmiVectorInsert}
	{parent: LmiVector}
	{description: Insert {italic:t} into a vector before {italic:pos}.}
	{prototype: LmiVectorIterator(T_) LmiVectorInsert(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, const T_* t)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: pos}
		{description: An iterator indicating the position where the insertion should take place.}
	}
	{parameter:
		{name: t}
		{description: The value to insert in the vector.}
	}
	{return: An iterator to the newly inserted element.  If an error occurred the iterator returned 
	will be "exceptional".  See LmiVectorIteratorIsExceptional for details on how to determine this condition.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorInsert(T_, STATIC_) \
	STATIC_ LmiVectorIterator(T_) LmiVectorInsert(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, const T_* t) { \
		LmiAssert((pos >= x->begin) && (pos <= x->end)); \
		if (x->end == x->endBuf) { \
			T_* s, * d, * b, * r; \
			LmiVectorSizeType(T_) xn = x->end - x->begin; \
			LmiVectorSizeType(T_) capacity = ((xn == 0) ? 2 : (2 * xn)); \
			if ((b = (T_*)LmiAllocatorAllocate(x->allocator, capacity * sizeof(T_))) == NULL) goto FAIL0; \
			for (s = x->begin, d = b; s != pos; ++s, ++d) if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL1; \
			if ((r = LmiConstructCopy(T_)(d, t)) == NULL) goto FAIL1; \
			for (s = pos, ++d; s != x->end; ++s, ++d) if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL1; \
			LmiVectorClear(T_)(x); \
			if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, (x->endBuf - x->begin) * sizeof(T_)); \
			x->begin = b; \
			x->end = x->begin + xn + 1; \
			x->endBuf = x->begin + capacity; \
			return r; \
FAIL1:		for (; d != b; --d) LmiDestruct(T_)(d - 1); \
			LmiAllocatorDeallocate(x->allocator, b, capacity * sizeof(T_)); \
FAIL0:		return NULL; /* Error */ \
		} else { \
			if (pos == x->end) { /* push_back */ \
				if (LmiConstructCopy(T_)(pos, t) == NULL) return NULL; /* Error */ \
				++(x->end); \
			} else { \
				T_* p = x->end; \
				if (LmiConstructCopy(T_)(p, p - 1) == NULL) return NULL; /* Error */ \
				++(x->end); \
				for (--p; p != pos; --p) \
					if (LmiAssign(T_)(p, p - 1) == NULL) return NULL; /* Error */ \
				if (LmiAssign(T_)(pos, t) == NULL) return NULL; /* Error */ \
			} \
			return pos; \
		} \
	}

/**
{function:
	{name: LmiVectorInsertN}
	{parent: LmiVector}
	{description: Insert {italic:n} copies of {italic:t} into a vector before {italic:pos}.}
	{prototype: LmiBool LmiVectorInsertN(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, LmiVectorSizeType(T_) n, const T_* t)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: pos}
		{description: An iterator indicating the position where the insertion should take place.}
	}
	{parameter:
		{name: n}
		{description: The number of copies to {italic:t} to insert into the vector.}
	}
	{parameter:
		{name: t}
		{description: The value of the newly inserted elements in the vector.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorInsertN(T_, STATIC_) \
	STATIC_ LmiBool LmiVectorInsertN(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, LmiVectorSizeType(T_) n, const T_* t) { \
  		LmiAssert((pos >= x->begin) && (pos <= x->end)); \
		if (n == 0) { \
			return LMI_TRUE; \
		} else if (x->end + n > x->endBuf) { \
			const T_* s; \
			T_* d, * b; \
			LmiVectorSizeType(T_) i; \
			LmiVectorSizeType(T_) xn = x->end - x->begin; \
			LmiVectorSizeType(T_) minCapacity = xn + n; \
			LmiVectorSizeType(T_) capacity = ((x->begin == x->endBuf) ? (2U * n) : (2U * (LmiVectorSizeType(T_))(x->endBuf - x->begin))); \
			capacity = ((capacity < minCapacity) ? minCapacity : capacity); \
			if ((b = (T_*)LmiAllocatorAllocate(x->allocator, capacity * sizeof(T_))) == NULL) goto FAIL0; \
			for (s = x->begin, d = b; s != pos; ++s, ++d) if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL1; \
			for (i = 0; i < n; ++i, ++d) if (LmiConstructCopy(T_)(d, t) == NULL) goto FAIL1; \
			for (s = pos; s != x->end; ++s, ++d) if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL1; \
			LmiVectorClear(T_)(x); \
			if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, (x->endBuf - x->begin) * sizeof(T_)); \
			x->begin = b; \
			x->end = x->begin + xn + n; \
			x->endBuf = x->begin + capacity; \
			return LMI_TRUE; \
FAIL1:		for (; d != b; --d) LmiDestruct(T_)(d - 1); \
			LmiAllocatorDeallocate(x->allocator, b, capacity * sizeof(T_)); \
FAIL0:		return LMI_FALSE; /* Error */ \
		} else { \
			const T_* s; \
			T_* d; \
			LmiVectorConstIterator(T_) const_pos = pos; \
			LmiVectorSizeType(T_) tail = x->end - pos; /* items beyond pos */ \
			LmiVectorSizeType(T_) i; \
			if (tail > n) { \
				for (s = const_pos + (tail - n); s != const_pos + tail; ++s, ++(x->end)) \
					if (LmiConstructCopy(T_)(x->end, s) == NULL) return LMI_FALSE;  /* Error */ \
				for (s = const_pos + (tail - n), d = pos + tail; s != const_pos; --s, --d) \
					if (LmiAssign(T_)(d - 1, s - 1) == NULL) return LMI_FALSE;  /* Error */ \
				for (i = 0; i < n; ++i, ++pos) \
					if (LmiAssign(T_)(pos, t) == NULL) return LMI_FALSE;  /* Error */ \
			} else { \
				for (i = 0; i < n - tail; ++i, ++(x->end)) \
					if (LmiConstructCopy(T_)(x->end, t) == NULL) return LMI_FALSE;  /* Error */ \
				for (s = const_pos; s != const_pos + tail; ++s, ++(x->end)) \
					if (LmiConstructCopy(T_)(x->end, s) == NULL) return LMI_FALSE;  /* Error */ \
				for (i = 0; i < tail; ++i, ++pos) \
					if (LmiAssign(T_)(pos, t) == NULL) return LMI_FALSE; /* Error */ \
			} \
			return LMI_TRUE; \
		} \
	}

/**
{function:
	{name: LmiVectorInsertRange}
	{parent: LmiVector}
	{description: Insert the elements in the range [{italic:first}, {italic:last}) into a vector before {italic:pos}.}
	{prototype: LmiBool LmiVectorInsertRange(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, LmiVectorConstIterator(T_) first, LmiVectorConstIterator(T_) last)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: pos}
		{description: An iterator indicating the position where the insertion should take place.}
	}
	{parameter:
		{name: first}
		{description: An iterator to the first element to insert into the vector.}
	}
	{parameter:
		{name: last}
		{description: An iterator one past the last element to insert into the vector.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorInsertRange(T_, STATIC_) \
	STATIC_ LmiBool LmiVectorInsertRange(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, LmiVectorConstIterator(T_) first, LmiVectorConstIterator(T_) last) { \
		LmiVectorSizeType(T_) n = last - first; \
		LmiAssert((pos >= x->begin) && (pos <= x->end)); \
		LmiAssert(first <= last); \
		if (first == last) { \
			return LMI_TRUE; \
		} else if (x->end + n > x->endBuf) { \
			const T_* s; \
			T_* d, * b; \
			LmiVectorSizeType(T_) xn = x->end - x->begin; \
			LmiVectorSizeType(T_) minCapacity = xn + n; \
			LmiVectorSizeType(T_) capacity = ((x->begin == x->endBuf) ? (2U * n) : (2U * (LmiVectorSizeType(T_))(x->endBuf - x->begin))); \
			capacity = ((capacity < minCapacity) ? minCapacity : capacity); \
			if ((b = (T_*)LmiAllocatorAllocate(x->allocator, capacity * sizeof(T_))) == NULL) goto FAIL0; \
			for (s = x->begin, d = b; s != pos; ++s, ++d) if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL1; \
			for (s = first; s != last; ++s, ++d) if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL1; \
			for (s = pos; s != x->end; ++s, ++d) if (LmiConstructCopy(T_)(d, s) == NULL) goto FAIL1; \
			LmiVectorClear(T_)(x); \
			if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, (x->endBuf - x->begin) * sizeof(T_)); \
			x->begin = b; \
			x->end = x->begin + xn + n; \
			x->endBuf = x->begin + capacity; \
			return LMI_TRUE; \
FAIL1:		for (; d != b; --d) LmiDestruct(T_)(d - 1); \
			LmiAllocatorDeallocate(x->allocator, b, capacity * sizeof(T_)); \
FAIL0:		return LMI_FALSE; /* Error */ \
		} else { \
			const T_* s; \
			T_* d; \
			LmiVectorConstIterator(T_) const_pos = pos; \
			LmiVectorSizeType(T_) tail = x->end - pos; /* items beyond pos */ \
			if (tail > n) { \
				for (s = const_pos + (tail - n); s != const_pos + tail; ++s,++(x->end)) \
					if (LmiConstructCopy(T_)(x->end, s) == NULL) return LMI_FALSE; /* Error */ \
				for (s = const_pos + (tail - n), d = pos + tail; s != const_pos; --s, --d) \
					if (LmiAssign(T_)(d - 1, s - 1) == NULL) return LMI_FALSE; /* Error */ \
				for (s = first; s != last; ++s, ++pos) \
					if (LmiAssign(T_)(pos, s) == NULL) return LMI_FALSE; /* Error */ \
			} else { \
				for (s = first + tail; s != last; ++s, ++(x->end)) \
					if (LmiConstructCopy(T_)(x->end, s) == NULL) return LMI_FALSE; /* Error */ \
				for (s = const_pos; s != const_pos + tail; ++s, ++(x->end)) \
					if (LmiConstructCopy(T_)(x->end, s) == NULL) return LMI_FALSE; /* Error */ \
				for (s = first; s != first + tail; ++s, ++pos) \
					if (LmiAssign(T_)(pos, s) == NULL) return LMI_FALSE; /* Error */ \
			} \
			return LMI_TRUE; \
		} \
	}

/**
{function:
	{name: LmiVectorErase}
	{parent: LmiVector}
	{description: Erase the element at a given position from the vector.}
	{prototype: LmiVectorIterator(T_) LmiVectorErase(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: pos}
		{description: An iterator pointing to the element to erase from the vector.}
	}
	{return: An iterator to the element after the erased element.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorErase(T_, STATIC_) \
	STATIC_ LmiVectorIterator(T_) LmiVectorErase(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos) { \
		T_* p; \
		LmiAssert((pos >= x->begin) && (pos < x->end)); \
		for (p = pos + 1; p != x->end; ++p) \
			if (LmiAssign(T_)(p - 1, p) == NULL) { x->end = p - 1; return 0; } /* Error */ \
		LmiDestruct(T_)(--(x->end)); \
		return pos; \
	}

/**
{function:
	{name: LmiVectorEraseRange}
	{parent: LmiVector}
	{description: Erase the elements in the range [{italic:first}, {italic:last}) from the vector.}
	{prototype: LmiVectorIterator(T_) LmiVectorEraseRange(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) first, LmiVectorIterator(T_) last)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: first}
		{description: An iterator to the first element to erase from the vector.}
	}
	{parameter:
		{name: last}
		{description: An iterator one past the last element to erase from the vector.}
	}
	{return: An iterator to the element after the erased elements.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorEraseRange(T_, STATIC_) \
	STATIC_ LmiVectorIterator(T_) LmiVectorEraseRange(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) first, LmiVectorIterator(T_) last) { \
		T_* s, * d; \
		LmiAssert(first <= last); \
		LmiAssert((first >= x->begin) && (first <= x->end) && (last >= x->begin) && (last <= x->end)); \
		if (first == last) return last; \
		for (s = last, d = first; s != x->end;  ++s, ++d) \
			if (LmiAssign(T_)(d, s) == NULL) { x->end = d; return NULL; } /* Error */ \
		for (; first != last; ++first) { \
			--(x->end); \
			LmiDestruct(T_)(x->end); \
		} \
		return last; \
	}

/**
{function:
	{name: LmiVectorClear}
	{parent: LmiVector}
	{description: Erase all elements from the vector.}
	{prototype: void LmiVectorClear(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorClear(T_, STATIC_) \
	STATIC_ void LmiVectorClear(T_)(LmiVector(T_)* x) { \
		while (x->end != x->begin) { \
			--(x->end); \
			LmiDestruct(T_)(x->end); \
		} \
	}

/**
{function:
	{name: LmiVectorResize}
	{parent: LmiVector}
	{description: Resize a vector.  If the current size of the vector is less than {italic:n} 
	  then additional copies of {italic:t} are added to the end of the vector.  If the current 
	  size of the vector is greater than {italic:n} then the elements from index {italic:n} to 
	  the end of the vector are erased.}
	{prototype: LmiBool LmiVectorResize(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n, const T_* t)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: n}
		{description: The size to make the vector.}
	}
	{parameter:
		{name: t}
		{description: A point to an object of type {italic:T} to initialize new elements of the vector.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorResize(T_, STATIC_) \
	STATIC_ LmiBool LmiVectorResize(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n, const T_* t) { \
		LmiVectorSizeType(T_) xn = x->end - x->begin; \
		if (n < xn) { \
			T_* p; \
			for (p = (x->end) - 1; p >= (x->begin + n); --p) LmiDestruct(T_)(p); \
			x->end = x->begin + n; \
		} else if (n > xn) { \
			if (!LmiVectorReserve(T_)(x, xn + n)) return LMI_FALSE; /* Error */ \
			for (; x->end < (x->begin + n); ++(x->end)) \
				if (LmiConstructCopy(T_)(x->end, t) == NULL) return LMI_FALSE; /* Error */ \
		} \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiVectorPushBack}
	{parent: LmiVector}
	{description: Add an element to the end of the vector.}
	{prototype: LmiBool LmiVectorPushBack(T_)(LmiVector(T_)* x, const T_* t)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: t}
		{description: A point to an object of type {italic:T} to add to the end of the vector.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorPushBack(T_, INLINE_)						   \
	INLINE_ LmiBool LmiVectorPushBack(T_)(LmiVector(T_)* x, const T_* t) { \
		if (x->end == x->endBuf) { \
			LmiVectorSizeType(T_) capacity = ((x->begin == 0) ? 2 : (2U * (x->end - x->begin))); \
			if (!LmiVectorReserve(T_)(x, capacity)) return LMI_FALSE; /* Error */ \
		} \
		if (LmiConstructCopy(T_)(x->end, t) == NULL) return LMI_FALSE; /* Error */ \
		++(x->end); \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiVectorPopBack}
	{parent: LmiVector}
	{description: Remove the last element from the vector.}
	{prototype: void LmiVectorPopBack(T_)(LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorPopBack(T_, INLINE_) \
	INLINE_ void LmiVectorPopBack(T_)(LmiVector(T_)* x) { \
		--(x->end); \
		LmiDestruct(T_)(x->end); \
	}

/**
{function:
	{name: LmiVectorCapacity}
	{parent: LmiVector}
	{description: Gets the number of elements for which memory has been allocated in the vector.}
	{prototype: LmiVectorSizeType(T_) LmiVectorCapacity(T_)(const LmiVector(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{return: The number of elements for which memory has been allocated in the vector.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define DefineInline_LmiVectorCapacity(T_, INLINE_)                                   \
	INLINE_ LmiVectorSizeType(T_) LmiVectorCapacity(T_)(const LmiVector(T_)* x) { return x->endBuf - x->begin; }

/**
{function:
	{name: LmiVectorReserve}
	{parent: LmiVector}
	{description: Reserves memory capacity in the vector.  If {italic:capacity} is less than or equal to 
	  LmiVectorCapacity(T) this call has no effect.}
	{prototype: LmiBool LmiVectorReserve(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) capacity)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The vector.}
	}
	{parameter:
		{name: capacity}
		{description: The requested memory capacity in number of elements.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiVector must be called at global scope before calling 
		any LmiVector member functions. 
	}
}
*/
#define Define_LmiVectorReserve(T_, STATIC_) \
	STATIC_ LmiBool LmiVectorReserve(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) capacity) { \
		if ((x->begin + capacity) > x->endBuf) { \
			T_* s, * d; \
			LmiVectorSizeType(T_) xn = x->end - x->begin; \
			T_* b = (T_*)LmiAllocatorAllocate(x->allocator, capacity * sizeof(T_)); \
			if (b == 0) return LMI_FALSE; /* Error */ \
			for (s = x->begin, d = b; s != x->end; ++s, ++d) \
				if (LmiConstructCopy(T_)(d, s) == NULL) { \
					for (--d; d >= b; --d) LmiDestruct(T_)(d); \
					LmiAllocatorDeallocate(x->allocator, b, capacity * sizeof(T_)); \
					return LMI_FALSE; /* Error */  \
				} \
			LmiVectorClear(T_)(x); \
			if (x->begin) LmiAllocatorDeallocate(x->allocator, x->begin, (x->endBuf - x->begin) * sizeof(T_)); \
			x->begin = b; \
			x->end = x->begin + xn; \
			x->endBuf = x->begin + capacity; \
		} \
		return LMI_TRUE; \
	}

#if defined(LMI_DEBUG)
#define Define_LmiVectorDump(T_, STATIC_) \
	STATIC_ void LmiVectorDump(T_)(const LmiVector(T_)* x, const char* name, unsigned int tabStop) { \
		LmiSizeT i; \
		char tabs[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"; \
		tabs[tabStop] = '\0'; \
		printf("%sLmiVector(%s) %s = {\n", tabs, #T_, name); \
		printf("%s\t%s* begin = %p;\n", tabs, #T_, x->begin); \
		printf("%s\t%s* end = %p;\n", tabs, #T_, x->end); \
		printf("%s\t%s* endBuf = %p;\n", tabs, #T_, x->endBuf); \
		printf("%s\tLmiSizeType(%s) size = %u;\n", tabs, #T_, (x->end - x->begin)); \
		printf("%s\tLmiSizeType(%s) capacity = %u;\n", tabs, #T_, (x->endBuf - x->begin)); \
		for (i = 0; i < (LmiVectorSizeType(T_))(x->end - x->begin); ++i) { \
			char element[20]; \
			sprintf(element, "buffer[%u]", i); \
			LmiDump(T_)((x->begin + i), element, tabStop + 1); \
		} \
		printf("%s}\n", tabs); \
	}
#else
#define Define_LmiVectorDump(T_, STATIC_) \
	STATIC_ void LmiVectorDump(T_)(const LmiVector(T_)* x, const char* name, unsigned int tabStop) {}
#endif

/**
{function validate="no":
	{name: Define_LmiVector}
	{parent: LmiVector}
	{description: Define a parameterized vector container and its subtypes.}
	{prototype: void Define_LmiVector(Type T)}
	{parameter:
		{name: T} 
		{description: The type stored in the vector.}
	}
	{example:
		/\* Instantiate a vector of integers container class *\/
		Define_LmiVector(LmiInt)
		void func() \{
			LmiVector(LmiInt) numbers;
			LmiInt i;
			LmiVectorConstructDefault(LmiInt)(&numbers, LmiMallocAllocatorGetDefault());
			for (i = 0; i < 10; ++i)
				LmiVectorPushBack(LmiInt)(&numbers, &i);
			LmiVectorDestruct(LmiInt)(&numbers);
		\}
	}
}
*/	

#define Declare_LmiVector_Types_(T_) \
	typedef struct LmiVector(T_) { \
		LmiAllocator* allocator; \
		T_* begin; \
		T_* end; \
		T_* endBuf; \
	} LmiVector(T_); \
	Declare_LmiRandomAccessContainerTypes(LmiVector(T_), T_, T_*, const T_*, LmiSizeT, LmiDistanceT) \

#define Declare_LmiVector_Functions_(T_) \
	DeclareInline_LmiRandomAccessIterator(LmiVectorIterator(T_), T_, const T_, LmiDistanceT, LMI_INLINE_DECLARATION) \
	DeclareInline_LmiRandomAccessIterator(LmiVectorConstIterator(T_), const T_, const T_, LmiDistanceT, LMI_INLINE_DECLARATION) \
	DeclareInline_LmiRandomAccessIterator(LmiVectorReverseIterator(T_), T_, const T_, LmiDistanceT, LMI_INLINE_DECLARATION) \
	DeclareInline_LmiRandomAccessIterator(LmiVectorConstReverseIterator(T_), const T_, const T_, LmiDistanceT, LMI_INLINE_DECLARATION) \
	LMI_INLINE_DECLARATION LmiVector(T_)* LmiVectorConstructDefault(T_)(LmiVector(T_)* x, LmiAllocator* a); \
	LmiVector(T_)* LmiVectorConstructN(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n, const T_* t, LmiAllocator* a); \
	LmiVector(T_)* LmiVectorConstructRange(T_)(LmiVector(T_)* x, LmiVectorConstIterator(T_) first, LmiVectorConstIterator(T_) last, LmiAllocator* a); \
	LmiVector(T_)* LmiVectorConstructCopy(T_)(LmiVector(T_)* x, const LmiVector(T_)* y); \
	void LmiVectorDestruct(T_)(LmiVector(T_)* x); \
	LmiVector(T_)* LmiVectorAssign(T_)(LmiVector(T_)* x, const LmiVector(T_)* y); \
	LmiBool LmiVectorSwap(T_)(LmiVector(T_)* x, LmiVector(T_)* y); \
	LMI_INLINE_DECLARATION LmiAllocator* LmiVectorGetAllocator(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiBool LmiVectorEmpty(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorSizeType(T_) LmiVectorSize(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorSizeType(T_) LmiVectorMaxSize(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorSizeType(T_) LmiVectorCapacity(T_)(const LmiVector(T_)* x); \
	LmiBool LmiVectorReserve(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) capacity); \
	LMI_INLINE_DECLARATION LmiVectorIterator(T_) LmiVectorBegin(T_)(LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorConstIterator(T_) LmiVectorBeginConst(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorIterator(T_) LmiVectorEnd(T_)(LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorConstIterator(T_) LmiVectorEndConst(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorReverseIterator(T_) LmiVectorRBegin(T_)(LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorConstReverseIterator(T_) LmiVectorRBeginConst(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorReverseIterator(T_) LmiVectorREnd(T_)(LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiVectorConstReverseIterator(T_) LmiVectorREndConst(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION T_* LmiVectorAt(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n); \
	LMI_INLINE_DECLARATION const T_* LmiVectorAtConst(T_)(const LmiVector(T_)* x, LmiVectorSizeType(T_) n); \
	LMI_INLINE_DECLARATION T_* LmiVectorFront(T_)(LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION const T_* LmiVectorFrontConst(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION T_* LmiVectorBack(T_)(LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION const T_* LmiVectorBackConst(T_)(const LmiVector(T_)* x); \
	LMI_INLINE_DECLARATION LmiBool LmiVectorPushBack(T_)(LmiVector(T_)* x, const T_* t); \
	LMI_INLINE_DECLARATION void LmiVectorPopBack(T_)(LmiVector(T_)* x); \
	LmiVectorIterator(T_) LmiVectorInsert(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, const T_* t); \
	LmiBool LmiVectorInsertN(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, LmiVectorSizeType(T_) n, const T_* t); \
	LmiBool LmiVectorInsertRange(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos, LmiVectorConstIterator(T_) first, LmiVectorConstIterator(T_) last); \
	LmiVectorIterator(T_) LmiVectorErase(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) pos); \
	LmiVectorIterator(T_) LmiVectorEraseRange(T_)(LmiVector(T_)* x, LmiVectorIterator(T_) first, LmiVectorIterator(T_) last); \
	void LmiVectorClear(T_)(LmiVector(T_)* x); \
	LmiBool LmiVectorResize(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) n, const T_* t); \
	void LmiVectorDump(T_)(const LmiVector(T_)* x, const char* name, unsigned int tabStop); \

#define Define_LmiVector_InlineBodies_(T_, INLINE_) \
	DefineInline_LmiRandomAccessIterator(LmiVectorIterator(T_), T_, const T_, INLINE_) \
	DefineInline_LmiRandomAccessIterator(LmiVectorConstIterator(T_), const T_, const T_, INLINE_) \
	DefineInline_LmiReverseRandomAccessIterator(LmiVectorReverseIterator(T_), LmiVectorIterator(T_), T_, const T_, INLINE_) \
	DefineInline_LmiReverseRandomAccessIterator(LmiVectorConstReverseIterator(T_), LmiVectorConstIterator(T_), const T_, const T_, INLINE_) \
	DefineInline_LmiVectorConstructDefault(T_, INLINE_) \
	DefineInline_LmiVectorGetAllocator(T_, INLINE_) \
	DefineInline_LmiVectorEmpty(T_, INLINE_) \
	DefineInline_LmiVectorSize(T_, INLINE_) \
	DefineInline_LmiVectorMaxSize(T_, INLINE_) \
	DefineInline_LmiVectorCapacity(T_, INLINE_) \
	DefineInline_LmiVectorBegin(T_, INLINE_) \
	DefineInline_LmiVectorBeginConst(T_, INLINE_) \
	DefineInline_LmiVectorEnd(T_, INLINE_) \
	DefineInline_LmiVectorEndConst(T_, INLINE_) \
	DefineInline_LmiVectorRBegin(T_, INLINE_) \
	DefineInline_LmiVectorRBeginConst(T_, INLINE_) \
	DefineInline_LmiVectorREnd(T_, INLINE_) \
	DefineInline_LmiVectorREndConst(T_, INLINE_) \
	DefineInline_LmiVectorAt(T_, INLINE_) \
	DefineInline_LmiVectorAtConst(T_, INLINE_) \
	DefineInline_LmiVectorFront(T_, INLINE_) \
	DefineInline_LmiVectorFrontConst(T_, INLINE_) \
	DefineInline_LmiVectorBack(T_, INLINE_) \
	DefineInline_LmiVectorBackConst(T_, INLINE_) \
	DefineInline_LmiVectorPushBack(T_, INLINE_) \
	DefineInline_LmiVectorPopBack(T_, INLINE_) \

#define Define_LmiVector_Bodies_(T_, STATIC_) \
	Define_LmiVectorConstructN(T_, STATIC_) \
	Define_LmiVectorConstructRange(T_, STATIC_) \
	Define_LmiVectorConstructCopy(T_, STATIC_) \
	Define_LmiVectorDestruct(T_, STATIC_) \
	Define_LmiVectorAssign(T_, STATIC_) \
	Define_LmiVectorSwap(T_, STATIC_) \
	Define_LmiVectorReserve(T_, STATIC_) \
	Define_LmiVectorInsert(T_, STATIC_) \
	Define_LmiVectorInsertN(T_, STATIC_) \
	Define_LmiVectorInsertRange(T_, STATIC_) \
	Define_LmiVectorErase(T_, STATIC_) \
	Define_LmiVectorEraseRange(T_, STATIC_) \
	Define_LmiVectorClear(T_, STATIC_) \
	Define_LmiVectorResize(T_, STATIC_) \
	Define_LmiVectorDump(T_, STATIC_) \

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#define Define_LmiVector_HeaderInlines_(T_) Define_LmiVector_InlineBodies_(T_, LMI_INLINE)
#else
#define Define_LmiVector_HeaderInlines_(T_)
#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
#define Define_LmiVector_SourceInlines_(T_) Define_LmiVector_InlineBodies_(T_, LMI_INLINE_SOURCE_FILE)
#else
#define Define_LmiVector_SourceInlines_(T_)
#endif

#define Declare_LmiVector(T_) \
	Declare_LmiVector_Types_(T_) \
	Declare_LmiVector_Functions_(T_) \
	Define_LmiVector_HeaderInlines_(T_)
#define Declare_LmiVector_NoInlines(T_) \
	Declare_LmiVector_Types_(T_) \
	Declare_LmiVector_Functions_(T_)
#define Declare_LmiVector_Inlines(T_) \
	Define_LmiVector_HeaderInlines_(T_)

#define Define_LmiVector(T_) \
	Define_LmiVector_SourceInlines_(T_) \
	Define_LmiVector_Bodies_(T_, LMI_NO_INLINE)
#define Define_LmiVector_Static(T_) \
	Declare_LmiVector_Types_(T_) \
	Declare_LmiBaseIteratorTypesPart(LmiVectorIterator(T_), T_, LmiDistanceT) \
	Declare_LmiBaseIteratorTypesPart(LmiVectorConstIterator(T_), const T_, LmiDistanceT) \
	Declare_LmiBaseIteratorTypesPart(LmiVectorReverseIterator(T_), T_, LmiDistanceT) \
	Declare_LmiBaseIteratorTypesPart(LmiVectorConstReverseIterator(T_), const T_, LmiDistanceT) \
	static LmiBool LmiVectorReserve(T_)(LmiVector(T_)* x, LmiVectorSizeType(T_) capacity); \
	static void LmiVectorClear(T_)(LmiVector(T_)* x); \
	Define_LmiVector_InlineBodies_(T_, LMI_POSSIBLY_UNUSED LMI_STATIC_INLINE) \
	Define_LmiVector_Bodies_(T_, LMI_POSSIBLY_UNUSED static)

#define Declare_LmiVectorConstructRangeOther(T_, InputIterator_) \
	LmiVector(T_)* LmiVectorConstructRangeOther(T_, InputIterator_)(LmiVector(T_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* a)

#define Define_LmiVectorConstructRangeOther(T_, InputIterator_) Define_LmiVectorConstructRangeOther_(T_, InputIterator_, LMI_NO_INLINE)
#define Define_LmiVectorConstructRangeOther_Static(T_, InputIterator_) Define_LmiVectorConstructRangeOther_(T_, InputIterator_, static)

#define Declare_LmiVectorEqual(T_) \
	LmiBool LmiVectorEqual(T_)(const LmiVector(T_)* x, const LmiVector(T_)* y);
#define Define_LmiVectorEqual(T_)        Define_LmiVectorEqual_(T_, LmiVectorEqual(T_), LmiEqual(T_), LMI_NO_INLINE)
#define Define_LmiVectorEqual_Static(T_) Define_LmiVectorEqual_(T_, LmiVectorEqual(T_), LmiEqual(T_), static)

#define Declare_LmiVectorEqualComp(T_, Comp_) \
	LmiBool LmiVectorEqualComp(T_, Comp_)(const LmiVector(T_)* x, const LmiVector(T_)* y);
#define Define_LmiVectorEqualComp(T_, Comp_)        Define_LmiVectorEqual_(T_, LmiVectorEqualComp(T_, Comp_), Comp_, LMI_NO_INLINE)
#define Define_LmiVectorEqualComp_Static(T_, Comp_) Define_LmiVectorEqual_(T_, LmiVectorEqualComp(T_, Comp_), Comp_, static)

#define Declare_LmiVectorLess(T_) \
	LmiBool LmiVectorLess(T_)(const LmiVector(T_)* x, const LmiVector(T_)* y);
#define Define_LmiVectorLess(T_)        Define_LmiVectorLess_(T_, LmiVectorLess(T_), LmiLess(T_), LMI_NO_INLINE)
#define Define_LmiVectorLess_Static(T_) Define_LmiVectorLess_(T_, LmiVectorLess(T_), LmiLess(T_), static)

#define Declare_LmiVectorLessComp(T_, Comp_) \
	LmiBool LmiVectorLessComp(T_, Comp_)(const LmiVector(T_)* x, const LmiVector(T_)* y);
#define Define_LmiVectorLessComp(T_, Comp_)        Define_LmiVectorLess_(T_, LmiVectorLessComp(T_, Comp_), Comp_, LMI_NO_INLINE)
#define Define_LmiVectorLessComp_Static(T_, Comp_) Define_LmiVectorLess_(T_, LmiVectorLessComp(T_, Comp_), Comp_, static)

/* Append to a vector converted elements of a container of another type. */
/* Use underscore version if calling LmiSize(CB) is an issue for a big LmiList. */
#define LmiVectorTranslate_(A, CB) LmiTemplate2(LmiVectorTranslate_, A, CB)
#define LmiVectorTranslate(A, CB)  LmiTemplate2(LmiVectorTranslate, A, CB)
#define Define_LmiVectorTranslate(A, CB) \
	LMI_POSSIBLY_UNUSED LMI_STATIC_INLINE LmiBool LmiVectorTranslate_(A, CB)(LmiVector(A) *va, const CB *cb, A *(*conv)(A *a, const LmiValueType(CB) *b, LmiAllocator *alloc), LmiAllocator *alloc) \
	{ \
		LmiConstIterator(CB) iter; \
		for(iter = LmiBeginConst(CB)(cb); \
			iter != LmiEndConst(CB)(cb); \
			LmiIncrement(LmiConstIterator(CB))(&iter)) \
		{ \
			A a; \
			if(conv(&a, LmiContentOf(LmiConstIterator(CB))(&iter), alloc) == NULL) \
				return LMI_FALSE; \
			if(!LmiVectorPushBack(A)(va, &a)) \
			{ \
				LmiDestruct(A)(&a); \
				return LMI_FALSE; \
			} \
			LmiDestruct(A)(&a); \
		} \
		return LMI_TRUE; \
	} \
	LMI_POSSIBLY_UNUSED static LmiBool LmiVectorTranslate(A, CB)(LmiVector(A) *va, const CB *cb, A *(*conv)(A *a, const LmiValueType(CB) *b, LmiAllocator *alloc), LmiAllocator *alloc) \
	{ \
		return LmiVectorReserve(A)(va, LmiVectorSize(A)(va) + LmiSize(CB)(cb)) && LmiVectorTranslate_(A, CB)(va, cb, conv, alloc); \
	}

/* Append to a vector converted elements of a range of another type. */
#define LmiVectorTranslateRange(A, BI) LmiTemplate2(LmiVectorTranslateRange, A, BI)
#define Define_LmiVectorTranslateRange(A, BI) \
	static LmiBool LmiVectorTranslateRange(A, BI)(LmiVector(A) *va, BI begin, BI end, A *(*conv)(A *a, LmiValueType(BI) *b, LmiAllocator *alloc_), LmiAllocator *alloc) \
	{ \
		while(begin != end) \
		{ \
			A a; \
			if(conv(&a, LmiContentOf(BI)(&begin), alloc) == NULL) \
				return LMI_FALSE; \
			if(!LmiVectorPushBack(A)(va, &a)) \
			{ \
				LmiDestruct(A)(&a); \
				return LMI_FALSE; \
			} \
			LmiDestruct(A)(&a); \
			LmiIncrement(BI)(&begin); \
		} \
		return LMI_TRUE; \
	}

LMI_END_EXTERN_C

#endif
