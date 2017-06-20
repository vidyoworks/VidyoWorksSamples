
/** 
{file:
	{name: LmiNames.h}
	{description: Canonical names for concept types and functions.}
    {copyright:
    	(c) 2005-2007 Vidyo, Inc.,
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
#if !defined(LMI_NAMES_H_)
#define LMI_NAMES_H_

#include <Lmi/Utils/LmiTemplate.h>

/**
{type visibility="public":
	{name: LmiSizeType}
	{parent: Utils}
	{include: Lmi/Utils/LmiNames.h}
	{description: The size type of the container type T_.}
	{template-prototype: LmiSizeType(T_)}
	{template-parameter: 
		{name: T_}
		{description: The container type.}
	}
}
*/

/**
{type visibility="public":
	{name: LmiDifferenceType}
	{parent: Utils}
	{include: Lmi/Utils/LmiNames.h}
	{description: The difference type of the container type T_.}
	{template-prototype: LmiDifferenceType(T_)}
	{template-parameter: 
		{name: T_}
		{description: The container type.}
	}
}
*/

/* Type Names */
#define LmiValueType(T_)						LmiClassType(T_, ValueType)
#define LmiIterator(T_)							LmiClassType(T_, Iterator)
#define LmiConstIterator(T_)					LmiClassType(T_, ConstIterator)
#define LmiReverseIterator(T_)					LmiClassType(T_, ReverseIterator)
#define LmiConstReverseIterator(T_)				LmiClassType(T_, ConstReverseIterator)
#define LmiPointer(T_)							LmiClassType(T_, Pointer)
#define LmiSizeType(T_)							LmiClassType(T_, SizeType)
#define LmiDifferenceType(T_)					LmiClassType(T_, DifferenceType)
#define LmiKeyType(T_)							LmiClassType(T_, KeyType)
#define LmiDataType(T_)							LmiClassType(T_, DataType)
#define LmiResultType(T_)						LmiClassType(T_, ResultType)
#define LmiHashFunctionType(T_)					LmiClassType(T_, HashFunctionType)

/* Expression Names */
#define LmiConstruct(T_)						LmiClassFunc(T_, Construct)
#define LmiConstructDefault(T_)					LmiClassFunc(T_, ConstructDefault)
#define LmiConstructCopy(T_)					LmiClassFunc(T_, ConstructCopy)
#define LmiConstructN(T_)						LmiClassFunc(T_, ConstructN)
#define LmiConstructRange(T_)					LmiClassFunc(T_, ConstructRange)
#define LmiDestruct(T_)							LmiClassFunc(T_, Destruct)
#define LmiAssign(T_)							LmiClassFunc(T_, Assign)
#define LmiSwap(T_)								LmiClassFunc(T_, Swap)
#define LmiEqual(T_)							LmiClassFunc(T_, Equal)
#define LmiLess(T_)								LmiClassFunc(T_, Less)
#define LmiGetAllocator(T_)						LmiClassFunc(T_, GetAllocator)
#define LmiBegin(T_)							LmiClassFunc(T_, Begin)
#define LmiBeginConst(T_)						LmiClassFunc(T_, BeginConst)
#define LmiEnd(T_)								LmiClassFunc(T_, End)
#define LmiEndConst(T_)							LmiClassFunc(T_, EndConst)
#define LmiSize(T_)								LmiClassFunc(T_, Size)
#define LmiMaxSize(T_)							LmiClassFunc(T_, MaxSize)
#define LmiEmpty(T_)							LmiClassFunc(T_, Empty)
#define LmiRBegin(T_)							LmiClassFunc(T_, RBegin)
#define LmiRBeginConst(T_)						LmiClassFunc(T_, RBeginConst)
#define LmiREnd(T_)								LmiClassFunc(T_, REnd)
#define LmiREndConst(T_)						LmiClassFunc(T_, REndConst)
#define LmiAt(T_)								LmiClassFunc(T_, At)
#define LmiAtConst(T_)							LmiClassFunc(T_, AtConst)
#define LmiFront(T_)							LmiClassFunc(T_, Front)
#define LmiFrontConst(T_)						LmiClassFunc(T_, FrontConst) 
#define LmiBack(T_)								LmiClassFunc(T_, Back)
#define LmiBackConst(T_)						LmiClassFunc(T_, BackConst)
#define LmiInsert(T_)							LmiClassFunc(T_, Insert)
#define LmiInsertN(T_)							LmiClassFunc(T_, InsertN)
#define LmiInsertRange(T_)						LmiClassFunc(T_, InsertRange)
#define LmiErase(T_)							LmiClassFunc(T_, Erase)
#define LmiEraseRange(T_)						LmiClassFunc(T_, EraseRange)
#define LmiEraseKey(T_)							LmiClassFunc(T_, EraseKey)
#define LmiClear(T_)							LmiClassFunc(T_, Clear)
#define LmiResize(T_)							LmiClassFunc(T_, Resize)
#define LmiPushFront(T_)						LmiClassFunc(T_, PushFront)
#define LmiPopFront(T_)							LmiClassFunc(T_, PopFront)
#define LmiPushBack(T_)							LmiClassFunc(T_, PushBack)
#define LmiPopBack(T_)							LmiClassFunc(T_, PopBack)
#define LmiCount(T_)							LmiClassFunc(T_, Count)
#define LmiEqualRange(T_)						LmiClassFunc(T_, EqualRange)
#define LmiEqualRangeConst(T_)					LmiClassFunc(T_, EqualRangeConst)
#define LmiLowerBound(T_)						LmiClassFunc(T_, LowerBound)
#define LmiLowerBoundConst(T_)					LmiClassFunc(T_, LowerBoundConst)
#define LmiUpperBound(T_)						LmiClassFunc(T_, UpperBound)
#define LmiUpperBoundConst(T_)					LmiClassFunc(T_, UpperBoundConst)
#define LmiHashFunction(T_)						LmiClassFunc(T_, HashFunction)
#define LmiFind(T_)								LmiClassFunc(T_, Find)
#define LmiFindConst(T_)						LmiClassFunc(T_, FindConst)
#define LmiBucketCount(T_)						LmiClassFunc(T_, BucketCount)
#define LmiContentOf(T_)						LmiClassFunc(T_, ContentOf)
#define LmiContentOfConst(T_)					LmiClassFunc(T_, ContentOfConst)
#define LmiIncrement(T_)						LmiClassFunc(T_, Increment)
#define LmiDecrement(T_)						LmiClassFunc(T_, Decrement)
#define LmiIncrementN(T_)						LmiClassFunc(T_, IncrementN)
#define LmiDecrementN(T_)						LmiClassFunc(T_, DecrementN)
#define LmiAdd(T_)								LmiClassFunc(T_, Add)
#define LmiSubtract(T_)							LmiClassFunc(T_, Subtract)
#define LmiPredicate(T_)						LmiClassFunc(T_, Predicate)
#define LmiDump(T_)								LmiClassFunc(T_, Dump)
#define LmiConstructExceptional(T_)				LmiClassFunc(T_, ConstructExceptional)
#define LmiIsExceptional(T_)					LmiClassFunc(T_, IsExceptional)

/* Template expression names */
#define LmiConstructIteratorRange(T_, It_)		LmiClassFunc(LmiTemplate1(T_, It_), ConstructIteratorRange)
#define LmiInsertIteratorRange(T_, It_)			LmiClassFunc(LmiTemplate1(T_, It_), InsertIteratorRange)


#endif
