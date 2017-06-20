
/**
{file:
	{name: LmiMap.h}
	{description: Ordered map and multimap containers.}
	{copyright:
		(c) 2010-2014 Vidyo, Inc.,
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

#ifndef LMI_MAP_H_
#define LMI_MAP_H_

#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/LmiBinaryTree.h>

LMI_BEGIN_EXTERN_C

/* Map */
#define LmiMap(K_, T_)                     LmiTemplate2(LmiMap, K_, T_)
#define LmiMapIterator(K_, T_)             LmiIterator(LmiMap(K_, T_))
#define LmiMapConstIterator(K_, T_)        LmiConstIterator(LmiMap(K_, T_))
#define LmiMapReverseIterator(K_, T_)      LmiReverseIterator(LmiMap(K_, T_))
#define LmiMapConstReverseIterator(K_, T_) LmiConstReverseIterator(LmiMap(K_, T_))

#define LmiMapConstruct(K_, T_)       LmiConstruct(LmiMap(K_, T_))
#define LmiMapConstructCopy(K_, T_)   LmiConstructCopy(LmiMap(K_, T_))
#define LmiMapDestruct(K_, T_)        LmiDestruct(LmiMap(K_, T_))
#define LmiMapAssign(K_, T_)          LmiAssign(LmiMap(K_, T_))
#define LmiMapSwap(K_, T_)            LmiSwap(LmiMap(K_, T_))
#define LmiMapEqual(K_, T_)           LmiEqual(LmiMap(K_, T_))
#define LmiMapClear(K_, T_)           LmiClear(LmiMap(K_, T_))
#define LmiMapInsert(K_, T_)          LmiInsert(LmiMap(K_, T_))
#define LmiMapBegin(K_, T_)           LmiBegin(LmiMap(K_, T_))
#define LmiMapEnd(K_, T_)             LmiEnd(LmiMap(K_, T_))
#define LmiMapBeginConst(K_, T_)      LmiBeginConst(LmiMap(K_, T_))
#define LmiMapEndConst(K_, T_)        LmiEndConst(LmiMap(K_, T_))
#define LmiMapFind(K_, T_)            LmiFind(LmiMap(K_, T_))
#define LmiMapFindConst(K_, T_)       LmiFindConst(LmiMap(K_, T_))
#define LmiMapCount(K_, T_)           LmiCount(LmiMap(K_, T_))
#define LmiMapLowerBound(K_, T_)      LmiLowerBound(LmiMap(K_, T_))
#define LmiMapLowerBoundConst(K_, T_) LmiLowerBoundConst(LmiMap(K_, T_))
#define LmiMapUpperBound(K_, T_)      LmiUpperBound(LmiMap(K_, T_))
#define LmiMapUpperBoundConst(K_, T_) LmiUpperBoundConst(LmiMap(K_, T_))
#define LmiMapEqualRange(K_, T_)      LmiEqualRange(LmiMap(K_, T_))
#define LmiMapEqualRangeConst(K_, T_) LmiEqualRangeConst(LmiMap(K_, T_))
#define LmiMapErase(K_, T_)           LmiErase(LmiMap(K_, T_))
#define LmiMapEraseRange(K_, T_)      LmiEraseRange(LmiMap(K_, T_))
#define LmiMapEraseKey(K_, T_)        LmiEraseKey(LmiMap(K_, T_))
#define LmiMapSize(K_, T_)            LmiSize(LmiMap(K_, T_))
#define LmiMapMaxSize(K_, T_)         LmiMaxSize(LmiMap(K_, T_))
#define LmiMapEmpty(K_, T_)           LmiEmpty(LmiMap(K_, T_))
#define LmiMapGetAllocator(K_, T_)    LmiGetAllocator(LmiMap(K_, T_))
#define LmiMapGetNodeSize(K_, T_)     LmiClassFunc(LmiMap(K_, T_), GetNodeSize)
#define LmiMapCheck(K_, T_)           LmiClassFunc(LmiMap(K_, T_), Check)
#define LmiMapFront(K_, T_)           LmiFront(LmiMap(K_, T_))
#define LmiMapBack(K_, T_)            LmiBack(LmiMap(K_, T_))

#define LmiMapIteratorConstruct(K_, T_)            LmiConstruct(LmiMapIterator(K_, T_))
#define LmiMapIteratorDestruct(K_, T_)             LmiDestruct(LmiMapIterator(K_, T_))
#define LmiMapIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMapIterator(K_, T_))
#define LmiMapIteratorAssign(K_, T_)               LmiAssign(LmiMapIterator(K_, T_))
#define LmiMapIteratorSwap(K_, T_)                 LmiSwap(LmiMapIterator(K_, T_))
#define LmiMapIteratorEqual(K_, T_)                LmiEqual(LmiMapIterator(K_, T_))
#define LmiMapIteratorContentOf(K_, T_)            LmiContentOf(LmiMapIterator(K_, T_))
#define LmiMapIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMapIterator(K_, T_))
#define LmiMapIteratorIncrement(K_, T_)            LmiIncrement(LmiMapIterator(K_, T_))
#define LmiMapIteratorDecrement(K_, T_)            LmiDecrement(LmiMapIterator(K_, T_))
#define LmiMapIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMapIterator(K_, T_))
#define LmiMapIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMapIterator(K_, T_))

#define LmiMapConstIteratorConstruct(K_, T_)            LmiConstruct(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorDestruct(K_, T_)             LmiDestruct(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorAssign(K_, T_)               LmiAssign(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorSwap(K_, T_)                 LmiSwap(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorEqual(K_, T_)                LmiEqual(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorContentOf(K_, T_)            LmiContentOf(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorIncrement(K_, T_)            LmiIncrement(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorDecrement(K_, T_)            LmiDecrement(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMapConstIterator(K_, T_))
#define LmiMapConstIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMapConstIterator(K_, T_))

#define LmiMapReverseIteratorConstruct(K_, T_)            LmiConstruct(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorDestruct(K_, T_)             LmiDestruct(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorAssign(K_, T_)               LmiAssign(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorSwap(K_, T_)                 LmiSwap(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorEqual(K_, T_)                LmiEqual(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorContentOf(K_, T_)            LmiContentOf(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorIncrement(K_, T_)            LmiIncrement(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorDecrement(K_, T_)            LmiDecrement(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMapReverseIterator(K_, T_))
#define LmiMapReverseIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMapReverseIterator(K_, T_))

#define LmiMapConstReverseIteratorConstruct(K_, T_)            LmiConstruct(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorDestruct(K_, T_)             LmiDestruct(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorAssign(K_, T_)               LmiAssign(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorSwap(K_, T_)                 LmiSwap(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorEqual(K_, T_)                LmiEqual(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorContentOf(K_, T_)            LmiContentOf(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorIncrement(K_, T_)            LmiIncrement(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorDecrement(K_, T_)            LmiDecrement(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMapConstReverseIterator(K_, T_))
#define LmiMapConstReverseIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMapConstReverseIterator(K_, T_))

#define LmiMapGetKey(v) (&(v)->first)

#define Declare_LmiMapAt(K_, T_, V_, GetKey, L_) \
	/* TODO */

#define Define_LmiMapAt(K_, T_, V_, GetKey, L_) \
	/* TODO */

#define Declare_LmiMapWithoutPair(K_, T_) \
	Declare_LmiUniqueBinaryTree(LmiMap(K_, T_), K_, LmiPair(K_, T_), LmiMapGetKey, LmiLess(K_)) \
	Declare_LmiMapAt(K_, T_, LmiPair(K_, T_), LmiMapGetKey, LmiLess(K_))

#define Define_LmiMapWithoutPair(K_, T_) \
	Define_LmiUniqueBinaryTree(LmiMap(K_, T_), K_, LmiPair(K_, T_), LmiMapGetKey, LmiLess(K_)) \
	Define_LmiMapAt(K_, T_, LmiPair(K_, T_), LmiMapGetKey, LmiLess(K_))

#define Declare_LmiMap(K_, T_) \
	Declare_LmiPair(K_, T_) \
	Declare_LmiMapWithoutPair(K_, T_)

#define Define_LmiMap(K_, T_) \
	Define_LmiPair(K_, T_) \
	Define_LmiMapWithoutPair(K_, T_)

#define Define_LmiMapCheck(K_, T_, Test) \
	Define_LmiBinaryTreeCheck(LmiMap(K_, T_), LmiMapGetKey, LmiLess(K_), LMI_FALSE, Test)

/* Multimap */
#define LmiMultimap(K_, T_)                     LmiTemplate2(LmiMultimap, K_, T_)
#define LmiMultimapIterator(K_, T_)             LmiIterator(LmiMultimap(K_, T_))
#define LmiMultimapConstIterator(K_, T_)        LmiConstIterator(LmiMultimap(K_, T_))
#define LmiMultimapReverseIterator(K_, T_)      LmiReverseIterator(LmiMultimap(K_, T_))
#define LmiMultimapConstReverseIterator(K_, T_) LmiConstReverseIterator(LmiMultimap(K_, T_))

#define LmiMultimapConstruct(K_, T_)       LmiConstruct(LmiMultimap(K_, T_))
#define LmiMultimapConstructCopy(K_, T_)   LmiConstructCopy(LmiMultimap(K_, T_))
#define LmiMultimapDestruct(K_, T_)        LmiDestruct(LmiMultimap(K_, T_))
#define LmiMultimapAssign(K_, T_)          LmiAssign(LmiMultimap(K_, T_))
#define LmiMultimapSwap(K_, T_)            LmiSwap(LmiMultimap(K_, T_))
#define LmiMultimapClear(K_, T_)           LmiClear(LmiMultimap(K_, T_))
#define LmiMultimapInsert(K_, T_)          LmiInsert(LmiMultimap(K_, T_))
#define LmiMultimapBegin(K_, T_)           LmiBegin(LmiMultimap(K_, T_))
#define LmiMultimapEnd(K_, T_)             LmiEnd(LmiMultimap(K_, T_))
#define LmiMultimapBeginConst(K_, T_)      LmiBeginConst(LmiMultimap(K_, T_))
#define LmiMultimapEndConst(K_, T_)        LmiEndConst(LmiMultimap(K_, T_))
#define LmiMultimapFind(K_, T_)            LmiFind(LmiMultimap(K_, T_))
#define LmiMultimapFindConst(K_, T_)       LmiFindConst(LmiMultimap(K_, T_))
#define LmiMultimapCount(K_, T_)           LmiCount(LmiMultimap(K_, T_))
#define LmiMultimapLowerBound(K_, T_)      LmiLowerBound(LmiMultimap(K_, T_))
#define LmiMultimapLowerBoundConst(K_, T_) LmiLowerBoundConst(LmiMultimap(K_, T_))
#define LmiMultimapUpperBound(K_, T_)      LmiUpperBound(LmiMultimap(K_, T_))
#define LmiMultimapUpperBoundConst(K_, T_) LmiUpperBoundConst(LmiMultimap(K_, T_))
#define LmiMultimapEqualRange(K_, T_)      LmiEqualRange(LmiMultimap(K_, T_))
#define LmiMultimapEqualRangeConst(K_, T_) LmiEqualRangeConst(LmiMultimap(K_, T_))
#define LmiMultimapErase(K_, T_)           LmiErase(LmiMultimap(K_, T_))
#define LmiMultimapEraseRange(K_, T_)      LmiEraseRange(LmiMultimap(K_, T_))
#define LmiMultimapEraseKey(K_, T_)        LmiEraseKey(LmiMultimap(K_, T_))
#define LmiMultimapSize(K_, T_)            LmiSize(LmiMultimap(K_, T_))
#define LmiMultimapMaxSize(K_, T_)         LmiMaxSize(LmiMultimap(K_, T_))
#define LmiMultimapEmpty(K_, T_)           LmiEmpty(LmiMultimap(K_, T_))
#define LmiMultimapGetAllocator(K_, T_)    LmiGetAllocator(LmiMultimap(K_, T_))
#define LmiMultimapGetNodeSize(K_, T_)     LmiClassFunc(LmiMultimap(K_, T_), GetNodeSize)
#define LmiMultimapCheck(K_, T_)           LmiClassFunc(LmiMultimap(K_, T_), Check)
#define LmiMultimapFront(K_, T_)           LmiFront(LmiMultimap(K_, T_))
#define LmiMultimapBack(K_, T_)            LmiBack(LmiMultimap(K_, T_))

#define LmiMultimapIteratorConstruct(K_, T_)            LmiConstruct(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorDestruct(K_, T_)             LmiDestruct(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorAssign(K_, T_)               LmiAssign(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorSwap(K_, T_)                 LmiSwap(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorEqual(K_, T_)                LmiEqual(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorContentOf(K_, T_)            LmiContentOf(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorIncrement(K_, T_)            LmiIncrement(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorDecrement(K_, T_)            LmiDecrement(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMultimapIterator(K_, T_))
#define LmiMultimapIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMultimapIterator(K_, T_))

#define LmiMultimapConstIteratorConstruct(K_, T_)            LmiConstruct(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorDestruct(K_, T_)             LmiDestruct(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorAssign(K_, T_)               LmiAssign(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorSwap(K_, T_)                 LmiSwap(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorEqual(K_, T_)                LmiEqual(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorContentOf(K_, T_)            LmiContentOf(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorIncrement(K_, T_)            LmiIncrement(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorDecrement(K_, T_)            LmiDecrement(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMultimapConstIterator(K_, T_))
#define LmiMultimapConstIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMultimapConstIterator(K_, T_))

#define LmiMultimapReverseIteratorConstruct(K_, T_)            LmiConstruct(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorDestruct(K_, T_)             LmiDestruct(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorAssign(K_, T_)               LmiAssign(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorSwap(K_, T_)                 LmiSwap(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorEqual(K_, T_)                LmiEqual(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorContentOf(K_, T_)            LmiContentOf(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorIncrement(K_, T_)            LmiIncrement(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorDecrement(K_, T_)            LmiDecrement(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMultimapReverseIterator(K_, T_))
#define LmiMultimapReverseIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMultimapReverseIterator(K_, T_))

#define LmiMultimapConstReverseIteratorConstruct(K_, T_)            LmiConstruct(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorDestruct(K_, T_)             LmiDestruct(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorConstructCopy(K_, T_)        LmiConstructCopy(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorAssign(K_, T_)               LmiAssign(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorSwap(K_, T_)                 LmiSwap(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorEqual(K_, T_)                LmiEqual(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorContentOf(K_, T_)            LmiContentOf(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorContentOfConst(K_, T_)       LmiContentOfConst(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorIncrement(K_, T_)            LmiIncrement(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorDecrement(K_, T_)            LmiDecrement(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorConstructExceptional(K_, T_) LmiConstructExceptional(LmiMultimapConstReverseIterator(K_, T_))
#define LmiMultimapConstReverseIteratorIsExceptional(K_, T_)        LmiIsExceptional(LmiMultimapConstReverseIterator(K_, T_))

#define LmiMultimapGetKey(v) (&(v)->first)

#define Declare_LmiMultimapWithoutPair(K_, T_) \
	Declare_LmiMultipleBinaryTree(LmiMultimap(K_, T_), K_, LmiPair(K_, T_), LmiMultimapGetKey, LmiLess(K_))

#define Define_LmiMultimapWithoutPair(K_, T_) \
	Define_LmiMultipleBinaryTree(LmiMultimap(K_, T_), K_, LmiPair(K_, T_), LmiMultimapGetKey, LmiLess(K_))

#define Declare_LmiMultimap(K_, T_) \
	Declare_LmiPair(K_, T_) \
	Declare_LmiMultimapWithoutPair(K_, T_)

#define Define_LmiMultimap(K_, T_) \
	Define_LmiPair(K_, T_) \
	Define_LmiMultimapWithoutPair(K_, T_)

#define Define_LmiMultimapCheck(K_, T_, Test) \
	Define_LmiBinaryTreeCheck(LmiMultimap(K_, T_), LmiMultimapGetKey, LmiLess(K_), LMI_TRUE, Test)

/* LmiMap */

/**
{function visibility="private" validate="no":
	{name: Declare_LmiMap}
	{parent: LmiMap}
	{description: Declare a parameterized map container and its subtypes.}
	{prototype: void Declare_LmiMap(Type K, Type T)}
	{parameter:
		{name: K}
		{description: The map's element key type.}
	}
	{parameter:
		{name: T}
		{description: The map's element value type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate a map of integers keyed by LmiString *\/
		Declare_LmiMap(LmiString, LmiInt)
		void func() \{
			LmiMap(LmiString, LmiInt) numbers;
		\}
	}
}
*/

/**
{type visibility="private":
	{name: LmiMap}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiMap.h}
	{description:
		A map (a.k.a binary tree) is a container that contains a
		set of elements that can be inserted and retrieved in O(log N)
		time (on average).
		Elements are ordered by key values, and the container can be
		traversed in order.
	}
	{template-prototype: LmiMap(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{note:
		The macro Declare_LmiMap must be called before declaring an
		object of this type.
	}
}
*/

/**
{type visibility="private":
	{name: LmiMapSizeType}
	{parent: LmiMap}
	{description: The size type for map.}
	{template-prototype: LmiMapSizeType(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{note:
		The macro Declare_LmiMap must be called before declaring an
		object of this type.
	}
}
*/

/**
{type visibility="private":
	{name: LmiMapValueType}
	{parent: LmiMap}
	{description: The value type for map.  This is equivalent
	to LmiPair(K_, T_).}
	{template-prototype: LmiMapValueType(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{note:
		The macro Declare_LmiMap must be called before declaring an
		object of this type.
	}
}
*/

/**
{function visibility="private" validate="no":
	{name: Define_LmiMap}
	{parent: LmiMap}
	{description: Define a parameterized map container and its subtypes.}
	{prototype: void Define_LmiMap(Type K, Type T)}
	{parameter:
		{name: K}
		{description: The map's element key type.}
	}
	{parameter:
		{name: T}
		{description: The map's element value type.}
	}
	{example:
		/\* Instantiate a map of integers container class *\/
		Define_LmiMap(LmiString, LmiInt)
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four",
			  "five", "six", "seven", "eight", "nine"
			\};
			LmiMap(LmiString, LmiInt) numbers;
			LmiInt i;
			LmiMapConstruct(LmiString, LmiInt)(&numbers, LmiMallocAllocatorGet());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiPair(LmiString, LmiInt) p;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGet());
				LmiPairConstruct(LmiString, LmiInt)(&p, &name, &i);
				LmiMapInsert(LmiString, LmiInt)(&numbers, &p);
			\}
			LmiMapDestruct(LmiString, LmiInt)(&numbers);
		\}
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapConstruct}
	{parent: LmiMap}
	{description:
		Construct a map.
	}
	{prototype: LmiMap(K_, T_)* LmiMapConstruct(K_, T_)(LmiMap(K_, T_)* x, LmiAllocator* alloc)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: alloc}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiMapGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed map or NULL on error.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapConstructCopy}
	{parent: LmiMap}
	{description: Construct a map from another map.}
	{prototype: LmiMap(K_, T_)* LmiMapConstructCopy(K_, T_)(LmiMap(K_, T_)* x, const LmiMap(K_, T_)* y)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: y}
		{description: The map to use to initialize the map being constructed. }
	}
	{return: A pointer to the constructed map or NULL on error.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapDestruct}
	{parent: LmiMap}
	{description: Destruct a map.}
	{prototype: void LmiMapDestruct(K_, T_)(LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapAssign}
	{parent: LmiMap}
	{description: Copy one map to another map.}
	{prototype: LmiMap(K_, T_)* LmiMapAssign(K_, T_)(LmiMap(K_, T_)* x, const LmiMap(K_, T_)* y)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: y}
		{description: The map to assign from.}
	}
	{return: A pointer to the constructed map or NULL on error.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapSwap}
	{parent: LmiMap}
	{description: Swap two maps.}
	{prototype: LmiBool LmiMapSwap(K_, T_)(LmiMap(K_, T_)* x, LmiMap(K_, T_)* y)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: y}
		{description: The other map.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapBegin}
	{parent: LmiMap}
	{description: Gets an iterator to the first element in the map.}
	{prototype: LmiMapIterator(K_, T_) LmiMapBegin(K_, T_)(LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: An iterator to the first element in the map.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapBeginConst}
	{parent: LmiMap}
	{description: Gets a read-only iterator to the first element in the map.}
	{prototype: LmiMapConstIterator(K_, T_) LmiMapBeginConst(K_, T_)(const LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: A read-only iterator to the first element in the map.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapEnd}
	{parent: LmiMap}
	{description: Gets an iterator to the element one past the last element in the map.}
	{prototype: LmiMapIterator(K_, T_) LmiMapEnd(K_, T_)(LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: An iterator to the element one past the last element in the map.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapEndConst}
	{parent: LmiMap}
	{description: Gets a read-only iterator to the element one past the last element in the map.}
	{prototype: LmiMapConstIterator(K_, T_) LmiMapEndConst(K_, T_)(const LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: A read-only iterator to the element one past the last element in the map.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapEmpty}
	{parent: LmiMap}
	{description: Determines whether the map contains any elements.}
	{prototype: LmiBool LmiMapEmpty(K_, T_)(const LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: LMI_TRUE if the map is empty or LMI_FALSE if it is not.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapSize}
	{parent: LmiMap}
	{description: Gets the number of elements in the map.}
	{prototype: LmiMapSizeType(K_, T_) LmiMapSize(K_, T_)(const LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: The number of elements in the map.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapMaxSize}
	{parent: LmiMap}
	{description: Gets the maximum size that the map can be.}
	{prototype: LmiMapSizeType(K_, T_) LmiMapMaxSize(K_, T_)(const LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: The maximum number of elements that the map can hold.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapCount}
	{parent: LmiMap}
	{description: Gets the number of elements in the map with a given key. }
	{prototype: LmiMapSizeType(K_, T_) LmiMapCount(K_, T_)(const LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the map with the specified key.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapClear}
	{parent: LmiMap}
	{description: Removes all elements from the map.}
	{prototype: void LmiMapClear(K_, T_)(LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapErase}
	{parent: LmiMap}
	{description: Removes the specified element from the map.}
	{prototype: LmiMapIterator(K_, T_) LmiMapErase(K_, T_)(LmiMap(K_, T_)* x, LmiMapIterator(K_, T_) pos)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapEraseRange}
	{parent: LmiMap}
	{description: Removes all elements in the specified range from the map.}
	{prototype: LmiMapIterator(K_, T_) LmiMapEraseRange(K_, T_)(LmiMap(K_, T_)* x, LmiMapIterator(K_, T_) f, LmiMapIterator(K_, T_) l)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
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
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapEraseKey}
	{parent: LmiMap}
	{description: Remove all elements in the map with a specified key.}
	{prototype: LmiMapSizeType(K_, T_) LmiMapEraseKey(K_, T_)(LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapLowerBound}
	{parent: LmiMap}
	{description:
		Gets an iterator to the first element in the map that is not before the specified key.  If map contains
		an element with that matches the key the first element that matches is returned, otherwise the element that comes
		after is returned.
	}
	{prototype: LmiMapIterator(K_, T_) LmiMapLowerBound(K_, T_)(LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: An iterator to the lower bounding element.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapLowerBoundConst}
	{parent: LmiMap}
	{description:
		Gets a read-only iterator to the first element in the map that is not before the specified key.  If map contains
		an element with that matches the key the first element that matches is returned, otherwise the element that comes
		after is returned.
	}
	{prototype: LmiMapConstIterator(K_, T_) LmiMapLowerBoundConst(K_, T_)(LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: A read-only iterator to the lower bounding element.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapUpperBound}
	{parent: LmiMap}
	{description: Gets a read-only iterator to the first element in the map that is after the specified key.}
	{prototype: LmiMapIterator(K_, T_) LmiMapUpperBound(K_, T_)(LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: An iterator to the upper bounding element.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapUpperBoundConst}
	{parent: LmiMap}
	{description: Gets a read-only iterator to the first element in the map that is after the specified key.}
	{prototype: LmiMapConstIterator(K_, T_) LmiMapUpperBoundConst(K_, T_)(LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: A read-only iterator to the upper bounding element.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapEqualRange}
	{parent: LmiMap}
	{description: Gets a pair of iterators pointing to all elements in the map with the specified key.}
	{prototype: LmiPair(LmiMapIterator(K_, T_), LmiMapIterator(K_, T_)) LmiMapEqualRange(K_, T_)(LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapEqualRangeConst}
	{parent: LmiMap}
	{description: Gets a pair of read-only iterators pointing to all elements in the map with the specified key.}
	{prototype: LmiPair(LmiMapConstIterator(K_, T_), LmiMapConstIterator(K_, T_)) LmiMapEqualRangeConst(K_, T_)(const LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapFind}
	{parent: LmiMap}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiMapIterator(K_, T_) LmiMapFind(K_, T_)(LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the map whose key matches the specified key.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapFindConst}
	{parent: LmiMap}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiMapConstIterator(K_, T_) LmiMapFindConst(K_, T_)(const LmiMap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the map whose key matches the specified key.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapInsert}
	{parent: LmiMap}
	{description: Inserts an element into the map.}
	{prototype: LmiPair(LmiMapIterator(K_, T_), LmiBool) LmiMapInsert(K_, T_)(LmiMap(K_, T_)* x, const LmiMapValueType(K_, T_)* value)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: value}
		{description: A pair whose first member is the element's key and the whose second member is the element's value.}
	}
	{return:
		Returns a pair containing an iterator and a boolean.  Upon successful
		insertion the pair's iterator points to the newly inserted element and
		the pair's boolean value is set to LMI_TRUE.  If the element is already
		present in the map, then the pair's iterator points to that
		element and the pair's boolean value is set to LMI_FALSE.  If any other
		error (such as memory exhaustion) occurs, the pair's iterator is set to
		NULL and the pair's boolean value is set to LMI_FALSE.
	}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapGetNodeSize}
	{parent: LmiMap}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiMapSizeType(K_, T_) LmiMapGetNodeSize(K_, T_)(const LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMapGetAllocator}
	{parent: LmiMap}
	{description: Gets a map\'s allocator.}
	{prototype: LmiAllocator* LmiMapGetAllocator(K_, T_)(LmiMap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{return: The allocator passed to the map\'s constructor.}
	{note:
		The macro Define_LmiMap must be called at global scope before calling
		any LmiMap member functions.
	}
}
*/

/* MapIterator */

/**
{type visibility="private":
	{name: LmiMapIterator}
	{parent: LmiMap}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for map.}
	{template-prototype: LmiMapIterator(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{note:
		The macro Declare_LmiMap must be called before declaring an
		object of this type.
	}
}
*/

/* MapConstIterator */

/**
{type visibility="private":
	{name: LmiMapConstIterator}
	{parent: LmiMap}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for map.}
	{template-prototype: LmiMapConstIterator(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{note:
		The macro Declare_LmiMap must be called before declaring an
		object of this type.
	}
}
*/
/* Multimap */

/**
{function visibility="private" validate="no":
	{name: Declare_LmiMultimap}
	{parent: LmiMultimap}
	{description: Declare a parameterized multimap container and its subtypes.}
	{prototype: void Declare_LmiMultimap(Type K, Type T)}
	{parameter:
		{name: K}
		{description: The multimap's element key type.}
	}
	{parameter:
		{name: T}
		{description: The multimap's element value type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate a multimap of integers keyed by LmiString *\/
		Declare_LmiMultimap(LmiString, LmiInt)
		void func() \{
			LmiMultimap(LmiString, LmiInt) numbers;
		\}
	}
}
*/

/**
{type visibility="private":
	{name: LmiMultimap}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiMap.h}
	{description:
		A multimap (a.k.a binary tree) is a container that contains a
		set of elements that can be retrieved in O(Log N) time (on average).
		Elements are ordered by key values, and the container can be traversed in order.  Multiple elements with the same
		key may be stored in the multimap.
	}
	{template-prototype: LmiMultimap(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{note:
		The macro Declare_LmiMultimap must be called before declaring an
		object of this type.
	}
}
*/

/**
{type visibility="private":
	{name: LmiMultimapSizeType}
	{parent: LmiMultimap}
	{description: The size type for multimap.}
	{template-prototype: LmiMultimapSizeType(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{note:
		The macro Declare_LmiMultimap must be called before declaring an
		object of this type.
	}
}
*/

/**
{type visibility="private":
	{name: LmiMultimapValueType}
	{parent: LmiMultimap}
	{description: The value type for multimap.  This is equivalent
	to LmiPair(K_, T_).}
	{template-prototype: LmiMultimapValueType(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{note:
		The macro Declare_LmiMultimap must be called before declaring an
		object of this type.
	}
}
*/

/**
{function visibility="private" validate="no":
	{name: Define_LmiMultimap}
	{parent: LmiMultimap}
	{description: Define a parameterized multimap container and its subtypes.}
	{prototype: void Define_LmiMultimap(Type K, Type T)}
	{parameter:
		{name: K}
		{description: The multimap's element key type.}
	}
	{parameter:
		{name: T}
		{description: The multimap's element value type.}
	}
	{example:
		/\* Instantiate a multimap of integers container class *\/
		Define_LmiMultimap(LmiString, LmiInt)
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four",
			  "five", "six", "seven", "eight", "nine"
			\};
			LmiMultimap(LmiString, LmiInt) numbers;
			LmiInt i;
			LmiMultimapConstruct(LmiString, LmiInt)(&numbers, LmiMallocAllocatorGet());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiPair(LmiString, LmiInt) p;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGet());
				LmiPairConstruct(LmiString, LmiInt)(&p, &name, &i);
				LmiMultimapInsert(LmiString, LmiInt)(&numbers, &p);
			\}
			LmiMultimapDestruct(LmiString, LmiInt)(&numbers);
		\}
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapConstruct}
	{parent: LmiMultimap}
	{description:
		Construct a multimap.}
	{prototype: LmiMultimap(K_, T_)* LmiMultimapConstruct(K_, T_)(LmiMultimap(K_, T_)* x, LmiAllocator* alloc)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: alloc}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiMultimapGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed multimap or NULL on error.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapConstructCopy}
	{parent: LmiMultimap}
	{description: Construct a multimap from another multimap.}
	{prototype: LmiMultimap(K_, T_)* LmiMultimapConstructCopy(K_, T_)(LmiMultimap(K_, T_)* x, const LmiMultimap(K_, T_)* y)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: y}
		{description: The multimap to use to initialize the multimap being constructed. }
	}
	{return: A pointer to the constructed multimap or NULL on error.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapDestruct}
	{parent: LmiMultimap}
	{description: Destruct a multimap.}
	{prototype: void LmiMultimapDestruct(K_, T_)(LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapAssign}
	{parent: LmiMultimap}
	{description: Copy one multimap to another multimap.}
	{prototype: LmiMultimap(K_, T_)* LmiMultimapAssign(K_, T_)(LmiMultimap(K_, T_)* x, const LmiMultimap(K_, T_)* y)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: y}
		{description: The multimap to assign from.}
	}
	{return: A pointer to the constructed multimap or NULL on error.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapSwap}
	{parent: LmiMultimap}
	{description: Swap two multimaps.}
	{prototype: LmiBool LmiMultimapSwap(K_, T_)(LmiMultimap(K_, T_)* x, LmiMultimap(K_, T_)* y)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: y}
		{description: The other multimap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapBegin}
	{parent: LmiMultimap}
	{description: Gets an iterator to the first element in the multimap.}
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapBegin(K_, T_)(LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: An iterator to the first element in the multimap.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapBeginConst}
	{parent: LmiMultimap}
	{description: Gets a read-only iterator to the first element in the multimap.}
	{prototype: LmiMultimapConstIterator(K_, T_) LmiMultimapBeginConst(K_, T_)(const LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: A read-only iterator to the first element in the multimap.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapEnd}
	{parent: LmiMultimap}
	{description: Gets an iterator to the element one past the last element in the multimap.}
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapEnd(K_, T_)(LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: An iterator to the element one past the last element in the multimap.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapEndConst}
	{parent: LmiMultimap}
	{description: Gets a read-only iterator to the element one past the last element in the multimap.}
	{prototype: LmiMultimapConstIterator(K_, T_) LmiMultimapEndConst(K_, T_)(const LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: A read-only iterator to the element one past the last element in the multimap.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapEmpty}
	{parent: LmiMultimap}
	{description: Determines whether the multimap contains any elements.}
	{prototype: LmiBool LmiMultimapEmpty(K_, T_)(const LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: LMI_TRUE if the multimap is empty or LMI_FALSE if it is not.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapSize}
	{parent: LmiMultimap}
	{description: Gets the number of elements in the multimap.}
	{prototype: LmiMultimapSizeType(K_, T_) LmiMultimapSize(K_, T_)(const LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: The number of elements in the multimap.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapMaxSize}
	{parent: LmiMultimap}
	{description: Gets the maximum size that the multimap can be.}
	{prototype: LmiMultimapSizeType(K_, T_) LmiMultimapMaxSize(K_, T_)(const LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: The maximum number of elements that the multimap can hold.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapCount}
	{parent: LmiMultimap}
	{description: Gets the number of elements in the multimap with a given key. }
	{prototype: LmiMultimapSizeType(K_, T_) LmiMultimapCount(K_, T_)(const LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the multimap with the specified key.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapClear}
	{parent: LmiMultimap}
	{description: Removes all elements from the multimap.}
	{prototype: void LmiMultimapClear(K_, T_)(LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapErase}
	{parent: LmiMultimap}
	{description: Removes the specified element from the multimap.}
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapErase(K_, T_)(LmiMultimap(K_, T_)* x, LmiMultimapIterator(K_, T_) pos)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapEraseRange}
	{parent: LmiMultimap}
	{description: Removes all elements in the specified range from the multimap.}
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapEraseRange(K_, T_)(LmiMultimap(K_, T_)* x, LmiMultimapIterator(K_, T_) f, LmiMultimapIterator(K_, T_) l)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
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
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapEraseKey}
	{parent: LmiMultimap}
	{description: Remove all elements in the multimap with a specified key.}
	{prototype: LmiMultimapSizeType(K_, T_) LmiMultimapEraseKey(K_, T_)(LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapLowerBound}
	{parent: LmiMultimap}
	{description:
		Gets an iterator to the first element in the multimap that is not before the specified key.  If map contains
		an element with that matches the key the first element that matches is returned, otherwise the element that comes
		after is returned.
	}
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapLowerBound(K_, T_)(LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: An iterator to the lower bounding element.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapLowerBoundConst}
	{parent: LmiMultimap}
	{description:
		Gets a read-only iterator to the first element in the map that is not before the specified key.  If map contains
		an element with that matches the key the first element that matches is returned, otherwise the element that comes
		after is returned.
	}
	{prototype: LmiMultimapConstIterator(K_, T_) LmiMultimapLowerBoundConst(K_, T_)(LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: A read-only iterator to the lower bounding element.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapUpperBound}
	{parent: LmiMultimap}
	{description: Gets a read-only iterator to the first element in the map that is after the specified key.}
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapUpperBound(K_, T_)(LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: An iterator to the upper bounding element.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapUpperBoundConst}
	{parent: LmiMultimap}
	{description: Gets a read-only iterator to the first element in the map that is after the specified key.}
	{prototype: LmiMultimapConstIterator(K_, T_) LmiMultimapUpperBoundConst(K_, T_)(LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The map's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The map's element value type.}
	}
	{parameter:
		{name: x}
		{description: The map.}
	}
	{parameter:
		{name: key}
		{description: The key to find.}
	}
	{return: A read-only iterator to the upper bounding element.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapEqualRange}
	{parent: LmiMultimap}
	{description: Gets a pair of iterators pointing to all elements in the multimap with the specified key.}
	{prototype: LmiPair(LmiMultimapIterator(K_, T_), LmiMultimapIterator(K_, T_)) LmiMultimapEqualRange(K_, T_)(const LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapEqualRangeConst}
	{parent: LmiMultimap}
	{description: Gets a pair of read-only iterators pointing to all elements in the multimap with the specified key.}
	{prototype: LmiPair(LmiMultimapConstIterator(K_, T_), LmiMultimapConstIterator(K_, T_)) LmiMultimapEqualRangeConst(K_, T_)(const LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapFind}
	{parent: LmiMultimap}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapFind(K_, T_)(LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the multimap whose key matches the specified key.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapFindConst}
	{parent: LmiMultimap}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiMultimapConstIterator(K_, T_) LmiMultimapFindConst(K_, T_)(const LmiMultimap(K_, T_)* x, const K_* key)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the multimap whose key matches the specified key.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapInsert}
	{parent: LmiMultimap}
	{description: Inserts an element into the multimap.}
	{prototype: LmiMultimapIterator(K_, T_) LmiMultimapInsert(K_, T_)(LmiMultimap(K_, T_)* x, const LmiMultimapValueType(K_, T_)* value)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{parameter:
		{name: value}
		{description: A pair whose first member is the element's key and the whose second member is the element's value.}
	}
	{return: An iterator to the newly inserted element or NULL on error.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapGetNodeSize}
	{parent: LmiMultimap}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiMultimapSizeType(K_, T_) LmiMultimapGetNodeSize(K_, T_)(const LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/**
{function visibility="private":
	{name: LmiMultimapGetAllocator}
	{parent: LmiMultimap}
	{description: Gets a multimap\'s allocator.}
	{prototype: LmiAllocator* LmiMultimapGetAllocator(K_, T_)(LmiMultimap(K_, T_)* x)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
	{parameter:
		{name: x}
		{description: The multimap.}
	}
	{return: The allocator passed to the multimap\'s constructor.}
	{note:
		The macro Define_LmiMultimap must be called at global scope before calling
		any LmiMultimap member functions.
	}
}
*/

/* LmiMultimapIterator */

/**
{type visibility="private":
	{name: LmiMultimapIterator}
	{parent: LmiMultimap}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for multimap.}
	{template-prototype: LmiMultimapIterator(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
}
*/
/* LmiMultimapConstIterator */

/**
{type visibility="private":
	{name: LmiMultimapConstIterator}
	{parent: LmiMultimap}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for multimap.}
	{template-prototype: LmiMultimapConstIterator(K_, T_)}
	{template-parameter:
		{name: K_}
		{description: The multimap's element key type.}
	}
	{template-parameter:
		{name: T_}
		{description: The multimap's element value type.}
	}
}
*/

LMI_END_EXTERN_C

#endif /* LMI_MAP_H_ */

