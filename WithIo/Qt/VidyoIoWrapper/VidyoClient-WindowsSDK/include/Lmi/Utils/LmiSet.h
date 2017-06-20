/**
{file: 
	{name: LmiSet.h}
	{description: Ordered set and multiset containers.}
	{copyright:
		(c) 2014 Vidyo, Inc.,
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

#ifndef LMI_SET_H_
#define LMI_SET_H_

#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/LmiBinaryTree.h>

LMI_BEGIN_EXTERN_C

/*********************************** Set and Multiset **************************************/

/* Set */
#define LmiSet(K_) 											LmiTemplate1(LmiSet, K_)
#define LmiSetIterator(K_) 									LmiIterator(LmiSet(K_))
#define LmiSetConstIterator(K_) 							LmiConstIterator(LmiSet(K_))
#define LmiSetReverseIterator(K_) 							LmiReverseIterator(LmiSet(K_))
#define LmiSetConstReverseIterator(K_) 						LmiConstReverseIterator(LmiSet(K_))
#define LmiSetConstruct(K_)									LmiConstruct(LmiSet(K_))
#define LmiSetConstructRangeOther(K_, InputIterator_)		LmiClassTemplateFunc1(LmiSet(K_), ConstructRangeOther, InputIterator_)
#define LmiSetConstructCopy(K_)								LmiConstructCopy(LmiSet(K_))
#define LmiSetDestruct(K_)									LmiDestruct(LmiSet(K_))
#define LmiSetAssign(K_)									LmiAssign(LmiSet(K_))
#define LmiSetEqual(K_)										LmiEqual(LmiSet(K_))
#define LmiSetSwap(K_)										LmiSwap(LmiSet(K_))
#define LmiSetClear(K_)										LmiClear(LmiSet(K_))
#define LmiSetInsert(K_)									LmiInsert(LmiSet(K_))
#define LmiSetBegin(K_)										LmiBegin(LmiSet(K_))
#define LmiSetEnd(K_)										LmiEnd(LmiSet(K_))
#define LmiSetBeginConst(K_)								LmiBeginConst(LmiSet(K_))
#define LmiSetEndConst(K_)									LmiEndConst(LmiSet(K_))
#define LmiSetFind(K_)										LmiFind(LmiSet(K_))
#define LmiSetFindConst(K_)									LmiFindConst(LmiSet(K_))
#define LmiSetCount(K_)										LmiCount(LmiSet(K_))
#define LmiSetLowerBound(K_)								LmiLowerBound(LmiSet(K_))
#define LmiSetLowerBoundConst(K_)							LmiLowerBoundConst(LmiSet(K_))
#define LmiSetUpperBound(K_)								LmiUpperBound(LmiSet(K_))
#define LmiSetUpperBoundConst(K_)							LmiUpperBoundConst(LmiSet(K_))
#define LmiSetEqualRange(K_)								LmiEqualRange(LmiSet(K_))
#define LmiSetEqualRangeConst(K_)							LmiEqualRangeConst(LmiSet(K_))
#define LmiSetErase(K_)										LmiErase(LmiSet(K_))
#define LmiSetEraseRange(K_)								LmiEraseRange(LmiSet(K_))
#define LmiSetEraseKey(K_)									LmiEraseKey(LmiSet(K_))
#define LmiSetSize(K_)										LmiSize(LmiSet(K_))
#define LmiSetMaxSize(K_)									LmiMaxSize(LmiSet(K_))
#define LmiSetEmpty(K_)										LmiEmpty(LmiSet(K_))
#define LmiSetGetAllocator(K_)								LmiGetAllocator(LmiSet(K_))
#define LmiSetGetNodeSize(K_)								LmiClassFunc(LmiSet(K_), GetNodeSize)
#define LmiSetFront(K_)										LmiFront(LmiSet(K_))
#define LmiSetBack(K_)										LmiBack(LmiSet(K_))

#define LmiSetIteratorConstruct(K_)							LmiConstruct(LmiSetIterator(K_))
#define LmiSetIteratorDestruct(K_)							LmiDestruct(LmiSetIterator(K_))
#define LmiSetIteratorConstructCopy(K_)						LmiConstructCopy(LmiSetIterator(K_))
#define LmiSetIteratorAssign(K_)							LmiAssign(LmiSetIterator(K_))
#define LmiSetIteratorSwap(K_)								LmiSwap(LmiSetIterator(K_))
#define LmiSetIteratorEqual(K_)								LmiEqual(LmiSetIterator(K_))
#define LmiSetIteratorContentOf(K_)							LmiContentOf(LmiSetIterator(K_))
#define LmiSetIteratorContentOfConst(K_)					LmiContentOfConst(LmiSetIterator(K_))
#define LmiSetIteratorIncrement(K_)							LmiIncrement(LmiSetIterator(K_))
#define LmiSetIteratorDecrement(K_)							LmiDecrement(LmiSetIterator(K_))
#define LmiSetIteratorConstructExceptional(K_)				LmiConstructExceptional(LmiSetIterator(K_))
#define LmiSetIteratorIsExceptional(K_)						LmiIsExceptional(LmiSetIterator(K_))

#define LmiSetConstIteratorConstruct(K_)					LmiConstruct(LmiSetConstIterator(K_))
#define LmiSetConstIteratorDestruct(K_)						LmiDestruct(LmiSetConstIterator(K_))
#define LmiSetConstIteratorConstructCopy(K_)				LmiConstructCopy(LmiSetConstIterator(K_))
#define LmiSetConstIteratorAssign(K_)						LmiAssign(LmiSetConstIterator(K_))
#define LmiSetConstIteratorSwap(K_)							LmiSwap(LmiSetConstIterator(K_))
#define LmiSetConstIteratorEqual(K_)						LmiEqual(LmiSetConstIterator(K_))
#define LmiSetConstIteratorContentOf(K_)					LmiContentOf(LmiSetConstIterator(K_))
#define LmiSetConstIteratorContentOfConst(K_)				LmiContentOfConst(LmiSetConstIterator(K_))
#define LmiSetConstIteratorIncrement(K_)					LmiIncrement(LmiSetConstIterator(K_))
#define LmiSetConstIteratorDecrement(K_)					LmiDecrement(LmiSetConstIterator(K_))
#define LmiSetConstIteratorConstructExceptional(K_)			LmiConstructExceptional(LmiSetConstIterator(K_))
#define LmiSetConstIteratorIsExceptional(K_)				LmiIsExceptional(LmiSetConstIterator(K_))

#define LmiSetReverseIteratorConstruct(K_)					LmiConstruct(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorDestruct(K_)					LmiDestruct(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorConstructCopy(K_)				LmiConstructCopy(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorAssign(K_)						LmiAssign(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorSwap(K_)						LmiSwap(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorEqual(K_)						LmiEqual(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorContentOf(K_)					LmiContentOf(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorContentOfConst(K_)				LmiContentOfConst(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorIncrement(K_)					LmiIncrement(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorDecrement(K_)					LmiDecrement(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorConstructExceptional(K_)		LmiConstructExceptional(LmiSetReverseIterator(K_))
#define LmiSetReverseIteratorIsExceptional(K_)				LmiIsExceptional(LmiSetReverseIterator(K_))

#define LmiSetConstReverseIteratorConstruct(K_)				LmiConstruct(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorDestruct(K_)				LmiDestruct(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorConstructCopy(K_)			LmiConstructCopy(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorAssign(K_)				LmiAssign(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorSwap(K_)					LmiSwap(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorEqual(K_)					LmiEqual(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorContentOf(K_)				LmiContentOf(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorContentOfConst(K_)		LmiContentOfConst(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorIncrement(K_)				LmiIncrement(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorDecrement(K_)				LmiDecrement(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorConstructExceptional(K_)	LmiConstructExceptional(LmiSetConstReverseIterator(K_))
#define LmiSetConstReverseIteratorIsExceptional(K_)			LmiIsExceptional(LmiSetConstReverseIterator(K_))

#define LmiSetGetKey(v) (v)

#define Declare_LmiSetConstructRangeOther(K_, InputIterator_) \
	LmiSet(K_)* LmiSetConstructRangeOther(K_, InputIterator_)(LmiSet(K_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* alloc);

#define Define_LmiSetConstructRangeOther(K_, InputIterator_) \
	LmiSet(K_)* LmiSetConstructRangeOther(K_, InputIterator_)(LmiSet(K_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* alloc) { \
		if (LmiSetConstruct(K_)(x, alloc) == NULL) \
			return NULL; \
		for (; !LmiEqual(InputIterator_)(&first, &last); LmiIncrement(InputIterator_)(&first)) { \
			K_* k = LmiContentOf(InputIterator_)(&first); \
			LmiPair(LmiSetIterator(K_), LmiBool) r = LmiSetInsert(K_)(x, k); \
			if (LmiSetIteratorIsExceptional(K_)(r.first)) { \
				LmiSetDestruct(K_)(x); \
				return NULL; \
			} \
		} \
		return x; \
	}

#define Declare_LmiSetAt(K_, V_, GetKey, L_) \
	/* TODO */

#define Define_LmiSetAt(K_, V_, GetKey, L_) \
	/* TODO */

#define Declare_LmiSet(K_) \
	Declare_LmiUniqueBinaryTree(LmiSet(K_), K_, K_, LmiSetGetKey, LmiLess(K_)) \
	Declare_LmiSetAt(K_, K_, LmiSetGetKey, LmiLess(K_))

#define Define_LmiSet(K_) \
	Define_LmiUniqueBinaryTree(LmiSet(K_), K_, K_, LmiSetGetKey, LmiLess(K_)) \
	Define_LmiSetAt(K_, K_, LmiSetGetKey, LmiLess(K_))


/* Multiset */
#define LmiMultiset(K_) 										LmiTemplate1(LmiMultiset, K_)
#define LmiMultisetIterator(K_) 								LmiIterator(LmiMultiset(K_))
#define LmiMultisetConstIterator(K_) 							LmiConstIterator(LmiMultiset(K_))
#define LmiMultisetReverseIterator(K_) 							LmiReverseIterator(LmiMultiset(K_))
#define LmiMultisetConstReverseIterator(K_) 					LmiConstReverseIterator(LmiMultiset(K_))

#define LmiMultisetConstruct(K_)								LmiConstruct(LmiMultiset(K_))
#define LmiMultisetConstructCopy(K_)							LmiConstructCopy(LmiMultiset(K_))
#define LmiMultisetConstructRangeOther(K_, InputIterator_)		LmiClassTemplateFunc1(LmiMultiset(K_), ConstructRangeOther, InputIterator_)

#define LmiMultisetDestruct(K_)									LmiDestruct(LmiMultiset(K_))
#define LmiMultisetAssign(K_)									LmiAssign(LmiMultiset(K_))
#define LmiMultisetClear(K_)									LmiClear(LmiMultiset(K_))
#define LmiMultisetInsert(K_)									LmiInsert(LmiMultiset(K_))
#define LmiMultisetBegin(K_)									LmiBegin(LmiMultiset(K_))
#define LmiMultisetEnd(K_)										LmiEnd(LmiMultiset(K_))
#define LmiMultisetBeginConst(K_)								LmiBeginConst(LmiMultiset(K_))
#define LmiMultisetEndConst(K_)									LmiEndConst(LmiMultiset(K_))
#define LmiMultisetFind(K_)										LmiFind(LmiMultiset(K_))
#define LmiMultisetFindConst(K_)								LmiFindConst(LmiMultiset(K_))
#define LmiMultisetCount(K_)									LmiCount(LmiMultiset(K_))
#define LmiMultisetLowerBound(K_)								LmiLowerBound(LmiMultiset(K_))
#define LmiMultisetLowerBoundConst(K_)							LmiLowerBoundConst(LmiMultiset(K_))
#define LmiMultisetUpperBound(K_)								LmiUpperBound(LmiMultiset(K_))
#define LmiMultisetUpperBoundConst(K_)							LmiUpperBoundConst(LmiMultiset(K_))
#define LmiMultisetEqualRange(K_)								LmiEqualRange(LmiMultiset(K_))
#define LmiMultisetEqualRangeConst(K_)							LmiEqualRangeConst(LmiMultiset(K_))
#define LmiMultisetErase(K_)									LmiErase(LmiMultiset(K_))
#define LmiMultisetEraseRange(K_)								LmiEraseRange(LmiMultiset(K_))
#define LmiMultisetEraseKey(K_)									LmiEraseKey(LmiMultiset(K_))
#define LmiMultisetSize(K_)										LmiSize(LmiMultiset(K_))
#define LmiMultisetMaxSize(K_)									LmiMaxSize(LmiMultiset(K_))
#define LmiMultisetEmpty(K_)									LmiEmpty(LmiMultiset(K_))
#define LmiMultisetGetAllocator(K_)								LmiGetAllocator(LmiMultiset(K_))
#define LmiMultisetGetNodeSize(K_)								LmiClassFunc(LmiMultiset(K_), GetNodeSize)
#define LmiMultisetFront(K_)									LmiFront(LmiMultiset(K_))
#define LmiMultisetBack(K_)										LmiBack(LmiMultiset(K_))

#define LmiMultisetIteratorConstruct(K_)						LmiConstruct(LmiMultisetIterator(K_))
#define LmiMultisetIteratorDestruct(K_)							LmiDestruct(LmiMultisetIterator(K_))
#define LmiMultisetIteratorConstructCopy(K_)					LmiConstructCopy(LmiMultisetIterator(K_))
#define LmiMultisetIteratorAssign(K_)							LmiAssign(LmiMultisetIterator(K_))
#define LmiMultisetIteratorSwap(K_)								LmiSwap(LmiMultisetIterator(K_))
#define LmiMultisetIteratorEqual(K_)							LmiEqual(LmiMultisetIterator(K_))
#define LmiMultisetIteratorContentOf(K_)						LmiContentOf(LmiMultisetIterator(K_))
#define LmiMultisetIteratorContentOfConst(K_)					LmiContentOfConst(LmiMultisetIterator(K_))
#define LmiMultisetIteratorIncrement(K_)						LmiIncrement(LmiMultisetIterator(K_))
#define LmiMultisetIteratorDecrement(K_)						LmiDecrement(LmiMultisetIterator(K_))
#define LmiMultisetIteratorConstructExceptional(K_)				LmiConstructExceptional(LmiMultisetIterator(K_))
#define LmiMultisetIteratorIsExceptional(K_)					LmiIsExceptional(LmiMultisetIterator(K_))

#define LmiMultisetConstIteratorConstruct(K_)					LmiConstruct(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorDestruct(K_)					LmiDestruct(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorConstructCopy(K_)				LmiConstructCopy(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorAssign(K_)						LmiAssign(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorSwap(K_)						LmiSwap(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorEqual(K_)						LmiEqual(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorContentOf(K_)					LmiContentOf(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorContentOfConst(K_)				LmiContentOfConst(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorIncrement(K_)					LmiIncrement(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorDecrement(K_)					LmiDecrement(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorConstructExceptional(K_)		LmiConstructExceptional(LmiMultisetConstIterator(K_))
#define LmiMultisetConstIteratorIsExceptional(K_)				LmiIsExceptional(LmiMultisetConstIterator(K_))

#define LmiMultisetReverseIteratorConstruct(K_)					LmiConstruct(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorDestruct(K_)					LmiDestruct(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorConstructCopy(K_)				LmiConstructCopy(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorAssign(K_)					LmiAssign(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorSwap(K_)						LmiSwap(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorEqual(K_)						LmiEqual(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorContentOf(K_)					LmiContentOf(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorContentOfConst(K_)			LmiContentOfConst(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorIncrement(K_)					LmiIncrement(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorDecrement(K_)					LmiDecrement(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorConstructExceptional(K_)		LmiConstructExceptional(LmiMultisetReverseIterator(K_))
#define LmiMultisetReverseIteratorIsExceptional(K_)				LmiIsExceptional(LmiMultisetReverseIterator(K_))

#define LmiMultisetConstReverseIteratorConstruct(K_)			LmiConstruct(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorDestruct(K_)				LmiDestruct(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorConstructCopy(K_)		LmiConstructCopy(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorAssign(K_)				LmiAssign(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorSwap(K_)					LmiSwap(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorEqual(K_)				LmiEqual(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorContentOf(K_)			LmiContentOf(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorContentOfConst(K_)		LmiContentOfConst(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorIncrement(K_)			LmiIncrement(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorDecrement(K_)			LmiDecrement(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorConstructExceptional(K_)	LmiConstructExceptional(LmiMultisetConstReverseIterator(K_))
#define LmiMultisetConstReverseIteratorIsExceptional(K_)		LmiIsExceptional(LmiMultisetConstReverseIterator(K_))

#define LmiMultisetGetKey(v) (v)

#define Declare_LmiMultisetConstructRangeOther(K_, InputIterator_) \
	LmiMultiset(K_)* LmiMultisetConstructRangeOther(K_, InputIterator_)(LmiMultiset(K_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* alloc);

#define Define_LmiMultisetConstructRangeOther(K_, InputIterator_) \
	LmiMultiset(K_)* LmiMultisetConstructRangeOther(K_, InputIterator_)(LmiMultiset(K_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* alloc) { \
		if (LmiMultisetConstruct(K_)(x, alloc) == NULL) \
			return NULL; \
		for (; !LmiEqual(InputIterator_)(&first, &last); LmiIncrement(InputIterator_)(&first)) { \
			K_* k = LmiContentOf(InputIterator_)(&first); \
			LmiPair(LmiMultisetIterator(K_), LmiBool) r = LmiMultisetInsert(K_)(x, k); \
			if (LmiMultisetIteratorIsExceptional(K_)(r.first)) { \
				LmiMultisetDestruct(K_)(x); \
				return NULL; \
			} \
		} \
		return x; \
	}

#define Declare_LmiMultiset(K_) \
	Declare_LmiMultipleBinaryTree(LmiMultiset(K_), K_, K_, LmiMultisetGetKey, LmiLess(K_))

#define Define_LmiMultiset(K_) \
	Define_LmiMultipleBinaryTree(LmiMultiset(K_), K_, K_, LmiMultisetGetKey, LmiLess(K_))

/* LmiSet */
/**
{function visibility="private" validate="no":
	{name: Declare_LmiSet}
	{parent: LmiSet}
	{description: Declare a parameterized set container and its subtypes.}
	{prototype: void Declare_LmiSet(Type K_)}
	{parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate a set of integers keyed by LmiString *\/
		Declare_LmiSet(LmiString)
		void func() \{
			LmiSet(LmiString) numbers;
		\}
	}
}
*/
/**
{type visibility="private":
	{name: LmiSet}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiSet.h}
	{description: 
		A set (a.k.a binary tree) is a container that contains a 
		set of elements that can be inserted and retrieved in O(log N)
		time (on average). 
		Elements are ordered by key values, and the container can be
		traversed in order.
	}
	{template-prototype: LmiSet(K_)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{note: 
		The macro Declare_LmiSet must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type visibility="private":
	{name: LmiSetSizeType}
	{parent: LmiSet}
	{description: The size type for set.}
	{template-prototype: LmiSetSizeType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{note: 
		The macro Declare_LmiSet must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiSetValueType}
	{parent: LmiSet}
	{description: The value type for set. }
	{template-prototype: LmiSetValueType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{note: 
		The macro Declare_LmiSet must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{function visibility="private" validate="no":
	{name: Define_LmiSet}
	{parent: LmiSet}
	{description: Define a parameterized set container and its subtypes.}
	{prototype: void Define_LmiSet(Type K_)}
	{parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{example:
		/\* Instantiate a set of strings container class *\/
		Define_LmiSet(LmiString)
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four", 
			  "five", "six", "seven", "eight", "nine" 
			\};
			LmiSet(LmiString) numbers;
			LmiInt i;
			LmiSetConstruct(LmiString)(&numbers, LmiMallocAllocatorGet());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGet());
				LmiSetInsert(LmiString)(&numbers, &name);
			\}
			LmiSetDestruct(LmiString)(&numbers);
		\}
	}
}
*/	

/**
{function visibility="private":
	{name: LmiSetConstruct}
	{parent: LmiSet}
	{description: 
		Construct a set.  
	}
	{prototype: LmiSet(K_)* LmiSetConstruct(K_)(LmiSet(K_)* x, LmiAllocator* alloc)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: alloc}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiSetGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed set or NULL on error.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetConstructRangeOther}
	{parent: LmiSet}
	{description: 
		Construct a set from a range of another container type.  
	}
	{prototype: LmiSet(K_)* LmiSetConstructRangeOther(K_, InputIterator_)(LmiSet(K_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* alloc)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
 	{template-parameter: 
		{name: InputIterator_}
		{description: The input iterator of a range.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
 	{parameter: 
		{name: first}
		{description:  A read-only input iterator to the first element in the range used to initialize the set.}
	}
  	{parameter: 
		{name: last}
		{description:  A read-only input iterator one past the last element in the range used to initialize the set.}
	}
	{parameter: 
		{name: alloc}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiSetGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed set or NULL on error.}
	{note: 
 		The macro Declare_LmiSetConstructRangeOther must be called at global scope before calling
		LmiSetConstructRangeOther member functions.  LmiSetConstructRangeOther is not included
 		in the default set of LmiSet functions.
	}
}
*/


/**
{function visibility="private":
	{name: LmiSetConstructCopy}
	{parent: LmiSet}
	{description: Construct a set from another set.}
	{prototype: LmiSet(K_)* LmiSetConstructCopy(K_)(LmiSet(K_)* x, const LmiSet(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: y}
		{description: The set to use to initialize the set being constructed. }
	}
	{return: A pointer to the constructed set or NULL on error.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetDestruct}
	{parent: LmiSet}
	{description: Destruct a set.}
	{prototype: void LmiSetDestruct(K_)(LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetAssign}
	{parent: LmiSet}
	{description: Copy one set to another set.}
	{prototype: LmiSet(K_)* LmiSetAssign(K_)(LmiSet(K_)* x, const LmiSet(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: y}
		{description: The set to assign from.}
	}
	{return: A pointer to the constructed set or NULL on error.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEqual}
	{parent: LmiSet}
	{description: Compares one set to another for equality.}
	{prototype: LmiBool LmiSetEqual(K_)(const LmiSet(K_)* x, const LmiSet(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: y}
		{description: The set to compare to set {code:x}.}
	}
	{return: Return LMI_TRUE if the sets are equal, or LMI_FALSE otherwise.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetSwap}
	{parent: LmiSet}
	{description: Swap two sets.}
	{prototype: LmiBool LmiSetSwap(K_)(LmiSet(K_)* x, LmiSet(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: y}
		{description: The other set.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetBegin}
	{parent: LmiSet}
	{description: Gets an iterator to the first element in the set.}
	{prototype: LmiSetIterator(K_) LmiSetBegin(K_)(LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: An iterator to the first element in the set.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetBeginConst}
	{parent: LmiSet}
	{description: Gets a read-only iterator to the first element in the set.}
	{prototype: LmiSetConstIterator(K_) LmiSetBeginConst(K_)(const LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: A read-only iterator to the first element in the set.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEnd}
	{parent: LmiSet}
	{description: Gets an iterator to the element one past the last element in the set.}
	{prototype: LmiSetIterator(K_) LmiSetEnd(K_)(LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: An iterator to the element one past the last element in the set.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEndConst}
	{parent: LmiSet}
	{description: Gets a read-only iterator to the element one past the last element in the set.}
	{prototype: LmiSetConstIterator(K_) LmiSetEndConst(K_)(const LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: A read-only iterator to the element one past the last element in the set.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEmpty}
	{parent: LmiSet}
	{description: Determines whether the set contains any elements.}
	{prototype: LmiBool LmiSetEmpty(K_)(const LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: LMI_TRUE if the set is empty or LMI_FALSE if it is not.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetSize}
	{parent: LmiSet}
	{description: Gets the number of elements in the set.}
	{prototype: LmiSetSizeType(K_) LmiSetSize(K_)(const LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: The number of elements in the set.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetMaxSize}
	{parent: LmiSet}
	{description: Gets the maximum size that the set can be.}
	{prototype: LmiSetSizeType(K_) LmiSetMaxSize(K_)(const LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: The maximum number of elements that the set can hold.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetCount}
	{parent: LmiSet}
	{description: Gets the number of elements in the set with a given key. }
	{prototype: LmiSetSizeType(K_) LmiSetCount(K_)(const LmiSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the set with the specified key.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetClear}
	{parent: LmiSet}
	{description: Removes all elements from the set.}
	{prototype: void LmiSetClear(K_)(LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetErase}
	{parent: LmiSet}
	{description: Removes the specified element from the set.}
	{prototype: LmiSetIterator(K_) LmiSetErase(K_)(LmiSet(K_)* x, LmiSetIterator(K_) pos)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEraseRange}
	{parent: LmiSet}
	{description: Removes all elements in the specified range from the set.}
	{prototype: LmiSetIterator(K_) LmiSetEraseRange(K_)(LmiSet(K_)* x, LmiSetIterator(K_) f, LmiSetIterator(K_) l)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: f}
		{description: An iterator to the first element to erase.}
	}
	{parameter: 
		{name: l}
		{description: An iterator to one past the last element to erase.}
	}
	{return: An iterator to the element after the erased elements.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEraseKey}
	{parent: LmiSet}
	{description: Remove all elements in the set with a specified key.}
	{prototype: LmiSetSizeType(K_) LmiSetEraseKey(K_)(LmiSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEqualRange}
	{parent: LmiSet}
	{description: Gets a pair of iterators pointing to all elements in the set with the specified key.}
	{prototype: LmiPair(LmiSetIterator(K_), LmiSetIterator(K_)) LmiSetEqualRange(K_)(LmiSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetEqualRangeConst}
	{parent: LmiSet}
	{description: Gets a pair of read-only iterators pointing to all elements in the set with the specified key.}
	{prototype: LmiPair(LmiSetConstIterator(K_), LmiSetConstIterator(K_)) LmiSetEqualRangeConst(K_)(const LmiSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetFind}
	{parent: LmiSet}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiSetIterator(K_) LmiSetFind(K_)(LmiSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the set whose key matches the specified key.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetFindConst}
	{parent: LmiSet}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiSetConstIterator(K_) LmiSetFindConst(K_)(const LmiSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the set whose key matches the specified key.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetInsert}
	{parent: LmiSet}
	{description: Inserts an element into the set.}
	{prototype: LmiPair(LmiSetIterator(K_), LmiBool) LmiSetInsert(K_)(LmiSet(K_)* x, const LmiSetValueType(K_)* value)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{parameter: 
		{name: value}
		{description: The element to insert.}
	}
	{return: 
		Returns a pair containing an iterator and a boolean.  Upon successful 
		insertion the pair's iterator points to the newly inserted element and 
		the pair's boolean value is set to LMI_TRUE.  If the element is already 
		present in the set, then the pair's iterator points to that 
		element and the pair's boolean value is set to LMI_FALSE.  If any other 
		error (such as memory exhaustion) occurs, the pair's iterator is set to 
		NULL and the pair's boolean value is set to LMI_FALSE.
	}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiSetGetNodeSize}
	{parent: LmiSet}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiSetSizeType(K_) LmiSetGetNodeSize(K_)(const LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/


/**
{function visibility="private":
	{name: LmiSetGetAllocator}
	{parent: LmiSet}
	{description: Gets a set\'s allocator.}
	{prototype: LmiAllocator* LmiSetGetAllocator(K_)(LmiSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The set.}
	}
	{return: The allocator passed to the set\'s constructor.}
	{note: 
		The macro Define_LmiSet must be called at global scope before calling 
		any LmiSet member functions. 
	}
}
*/

/* SetIterator */
/**
{type visibility="private":
	{name: LmiSetIterator}
	{parent: LmiSet}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for set.}
	{template-prototype: LmiSetIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{note: 
		The macro Declare_LmiSet must be called before declaring an 
		object of this type.  
	}
}
*/

/* SetConstIterator */										
/**
{type visibility="private":
	{name: LmiSetConstIterator}
	{parent: LmiSet}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for set.}
	{template-prototype: LmiSetConstIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The set's element key type.}
	}
	{note: 
		The macro Declare_LmiSet must be called before declaring an 
		object of this type.  
	}
}
*/
/* Multiset */
/**
{function visibility="private" validate="no":
	{name: Declare_LmiMultiset}
	{parent: LmiMultiset}
	{description: Declare a parameterized multiset container and its subtypes.}
	{prototype: void Declare_LmiMultiset(Type K)}
	{parameter: 
		{name: K}
		{description: The multiset's element key type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate a multiset of integers keyed by LmiString *\/
		Declare_LmiMultiset(LmiString)
		void func() \{
			LmiMultiset(LmiString) numbers;
		\}
	}
}
*/
/**
{type visibility="private":
	{name: LmiMultiset}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiSet.h}
	{description: 
		A multiset (a.k.a binary tree) is a container that contains a 
		set of elements that can be retrieved in O(Log N) time (on average). 
		Elements are ordered by key values, and the container can be traversed in order.  Multiple elements with the same 
		key may be stored in the multiset.
	}
	{template-prototype: LmiMultiset(K_)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiMultisetSizeType}
	{parent: LmiMultiset}
	{description: The size type for multiset.}
	{template-prototype: LmiMultisetSizeType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiMultisetValueType}
	{parent: LmiMultiset}
	{description: The value type for multiset. }
	{template-prototype: LmiMultisetValueType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{function visibility="private" validate="no":
	{name: Define_LmiMultiset}
	{parent: LmiMultiset}
	{description: Define a parameterized multiset container and its subtypes.}
	{prototype: void Define_LmiMultiset(Type K)}
	{parameter: 
		{name: K}
		{description: The multiset's element key type.}
	}
	{example:
		/\* Instantiate a multiset of strings container class *\/
		Define_LmiMultiset(LmiString)
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four", 
			  "five", "six", "seven", "eight", "nine" 
			\};
			LmiMultiset(LmiString) numbers;
			LmiInt i;
			LmiMultisetConstruct(LmiString)(&numbers, LmiMallocAllocatorGet());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGet());
				LmiMultisetInsert(LmiString)(&numbers, &name);
			\}
			LmiMultisetDestruct(LmiString)(&numbers);
		\}
	}
}
*/	
/**
{function visibility="private":
	{name: LmiMultisetConstruct}
	{parent: LmiMultiset}
	{description: 
		Construct a multiset.}
	{prototype: LmiMultiset(K_)* LmiMultisetConstruct(K_)(LmiMultiset(K_)* x, LmiAllocator* alloc)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: alloc}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiMultisetGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed multiset or NULL on error.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetConstructCopy}
	{parent: LmiMultiset}
	{description: Construct a multiset from another multiset.}
	{prototype: LmiMultiset(K_)* LmiMultisetConstructCopy(K_)(LmiMultiset(K_)* x, const LmiMultiset(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: y}
		{description: The multiset to use to initialize the multiset being constructed. }
	}
	{return: A pointer to the constructed multiset or NULL on error.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetConstructRangeOther}
	{parent: LmiMultiset}
	{description: 
		Construct a multiset from a range of another container type.
	}
	{prototype: LmiMultiset(K_)* LmiMultisetConstructRangeOther(K_, InputIterator_)(LmiMultiset(K_)* x, InputIterator_ first, InputIterator_ last, LmiAllocator* alloc)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
 	{template-parameter: 
		{name: InputIterator_}
		{description: The input iterator of a range.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
 	{parameter: 
		{name: first}
		{description:  A read-only input iterator to the first element in the range used to initialize the multiset.}
	}
  	{parameter: 
		{name: last}
		{description:  A read-only input iterator one past the last element in the range used to initialize the multiset.}
	}
	{parameter: 
		{name: alloc}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiMultisetGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed multiset or NULL on error.}
	{note: 
 		The macro Declare_LmiMultisetConstructRangeOther must be called at global scope before calling
		LmiMultisetConstructRangeOther member functions.  LmiMultisetConstructRangeOther is not included
 		in the default set of LmiMultiset functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetDestruct}
	{parent: LmiMultiset}
	{description: Destruct a multiset.}
	{prototype: void LmiMultisetDestruct(K_)(LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetAssign}
	{parent: LmiMultiset}
	{description: Copy one multiset to another multiset.}
	{prototype: LmiMultiset(K_)* LmiMultisetAssign(K_)(LmiMultiset(K_)* x, const LmiMultiset(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: y}
		{description: The multiset to assign from.}
	}
	{return: A pointer to the constructed multiset or NULL on error.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetSwap}
	{parent: LmiMultiset}
	{description: Swap two multisets.}
	{prototype: LmiBool LmiMultisetSwap(K_)(LmiMultiset(K_)* x, LmiMultiset(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: y}
		{description: The other multiset.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetBegin}
	{parent: LmiMultiset}
	{description: Gets an iterator to the first element in the multiset.}
	{prototype: LmiMultisetIterator(K_) LmiMultisetBegin(K_)(LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: An iterator to the first element in the multiset.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetBeginConst}
	{parent: LmiMultiset}
	{description: Gets a read-only iterator to the first element in the multiset.}
	{prototype: LmiMultisetConstIterator(K_) LmiMultisetBeginConst(K_)(const LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: A read-only iterator to the first element in the multiset.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetEnd}
	{parent: LmiMultiset}
	{description: Gets an iterator to the element one past the last element in the multiset.}
	{prototype: LmiMultisetIterator(K_) LmiMultisetEnd(K_)(LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: An iterator to the element one past the last element in the multiset.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetEndConst}
	{parent: LmiMultiset}
	{description: Gets a read-only iterator to the element one past the last element in the multiset.}
	{prototype: LmiMultisetConstIterator(K_) LmiMultisetEndConst(K_)(const LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: A read-only iterator to the element one past the last element in the multiset.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetEmpty}
	{parent: LmiMultiset}
	{description: Determines whether the multiset contains any elements.}
	{prototype: LmiBool LmiMultisetEmpty(K_)(const LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: LMI_TRUE if the multiset is empty or LMI_FALSE if it is not.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetSize}
	{parent: LmiMultiset}
	{description: Gets the number of elements in the multiset.}
	{prototype: LmiMultisetSizeType(K_) LmiMultisetSize(K_)(const LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: The number of elements in the multiset.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetMaxSize}
	{parent: LmiMultiset}
	{description: Gets the maximum size that the multiset can be.}
	{prototype: LmiMultisetSizeType(K_) LmiMultisetMaxSize(K_)(const LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: The maximum number of elements that the multiset can hold.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetCount}
	{parent: LmiMultiset}
	{description: Gets the number of elements in the multiset with a given key. }
	{prototype: LmiMultisetSizeType(K_) LmiMultisetCount(K_)(const LmiMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the multiset with the specified key.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetClear}
	{parent: LmiMultiset}
	{description: Removes all elements from the multiset.}
	{prototype: void LmiMultisetClear(K_)(LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetErase}
	{parent: LmiMultiset}
	{description: Removes the specified element from the multiset.}
	{prototype: LmiMultisetIterator(K_) LmiMultisetErase(K_)(LmiMultiset(K_)* x, LmiMultisetIterator(K_) pos)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetEraseRange}
	{parent: LmiMultiset}
	{description: Removes all elements in the specified range from the multiset.}
	{prototype: LmiMultisetIterator(K_) LmiMultisetEraseRange(K_)(LmiMultiset(K_)* x, LmiMultisetIterator(K_) f, LmiMultisetIterator(K_) l)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: f}
		{description: An iterator to the first element to erase.}
	}
	{parameter: 
		{name: l}
		{description: An iterator to one past the last element to erase.}
	}
	{return: An iterator to the element after the erased elements.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetEraseKey}
	{parent: LmiMultiset}
	{description: Remove all elements in the multiset with a specified key.}
	{prototype: LmiMultisetSizeType(K_) LmiMultisetEraseKey(K_)(LmiMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetEqualRange}
	{parent: LmiMultiset}
	{description: Gets a pair of iterators pointing to all elements in the multiset with the specified key.}
	{prototype: LmiPair(LmiMultisetIterator(K_), LmiMultisetIterator(K_)) LmiMultisetEqualRange(K_)(LmiMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetEqualRangeConst}
	{parent: LmiMultiset}
	{description: Gets a pair of read-only iterators pointing to all elements in the multiset with the specified key.}
	{prototype: LmiPair(LmiMultisetConstIterator(K_), LmiMultisetConstIterator(K_)) LmiMultisetEqualRangeConst(K_)(const LmiMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetFind}
	{parent: LmiMultiset}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiMultisetIterator(K_) LmiMultisetFind(K_)(LmiMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the multiset whose key matches the specified key.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetFindConst}
	{parent: LmiMultiset}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiMultisetConstIterator(K_) LmiMultisetFindConst(K_)(const LmiMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the multiset whose key matches the specified key.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetInsert}
	{parent: LmiMultiset}
	{description: Inserts an element into the multiset.}
	{prototype: LmiMultisetIterator(K_) LmiMultisetInsert(K_)(LmiMultiset(K_)* x, const LmiMultisetValueType(K_)* value)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{parameter: 
		{name: value}
		{description: The element to insert.}
	}
	{return: An iterator to the newly inserted element or NULL on error.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetGetNodeSize}
	{parent: LmiMultiset}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiMultisetSizeType(K_) LmiMultisetGetNodeSize(K_)(const LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultisetGetAllocator}
	{parent: LmiMultiset}
	{description: Gets a multiset\'s allocator.}
	{prototype: LmiAllocator* LmiMultisetGetAllocator(K_)(LmiMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The multiset.}
	}
	{return: The allocator passed to the multiset\'s constructor.}
	{note: 
		The macro Define_LmiMultiset must be called at global scope before calling 
		any LmiMultiset member functions. 
	}
}
*/

/* LmiMultisetIterator */
/**
{type visibility="private":
	{name: LmiMultisetIterator}
	{parent: LmiMultiset}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for multiset.}
	{template-prototype: LmiMultisetIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
}
*/
/* LmiMultisetConstIterator */
/**
{type visibility="private":
	{name: LmiMultisetConstIterator}
	{parent: LmiMultiset}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for multiset.}
	{template-prototype: LmiMultisetConstIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The multiset's element key type.}
	}
}
*/

LMI_END_EXTERN_C

#endif /* LMI_SET_H_ */

