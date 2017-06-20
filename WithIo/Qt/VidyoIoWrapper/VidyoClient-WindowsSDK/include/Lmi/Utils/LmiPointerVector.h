/**
   {file: 
     {name: LmiPointerVector.h}
     {description: Vector of generic pointers.}
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

#ifndef LMI_POINTER_VECTOR_H_
#define LMI_POINTER_VECTOR_H_


#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiBasicTypesContainer.h>

LMI_BEGIN_EXTERN_C

#define LmiPointerVector				LmiVector(LmiVoidPtr)
#define LmiPointerVectorSizeType		LmiVectorSizeType(LmiVoidPtr)
#define LmiPointerVectorDifferenceType	LmiVectorDifferenceType(LmiVoidPtr)
#define LmiPointerVectorDestruct		LmiVectorDestruct(LmiVoidPtr)
#define LmiPointerVectorConstructDefault	LmiVectorConstructDefault(LmiVoidPtr)
#define LmiPointerVectorConstructN		LmiVectorConstructN(LmiVoidPtr)
#define LmiPointerVectorConstructRange	LmiVectorConstructRange(LmiVoidPtr)
#define LmiPointerVectorConstructCopy	LmiVectorConstructCopy(LmiVoidPtr)
#define LmiPointerVectorAssign			LmiVectorAssign(LmiVoidPtr)
#define LmiPointerVectorSwap			LmiVectorSwap(LmiVoidPtr)
#define LmiPointerVectorGetAllocator	LmiVectorGetAllocator(LmiVoidPtr)
#define LmiPointerVectorBegin			LmiVectorBegin(LmiVoidPtr)
#define LmiPointerVectorBeginConst		LmiVectorBeginConst(LmiVoidPtr)
#define LmiPointerVectorEnd				LmiVectorEnd(LmiVoidPtr)
#define LmiPointerVectorEndConst		LmiVectorEndConst(LmiVoidPtr)
#define LmiPointerVectorRBegin			LmiVectorRBegin(LmiVoidPtr)
#define LmiPointerVectorRBeginConst		LmiVectorRBeginConst(LmiVoidPtr)
#define LmiPointerVectorREnd			LmiVectorREnd(LmiVoidPtr)
#define LmiPointerVectorREndConst		LmiVectorREndConst(LmiVoidPtr)
#define LmiPointerVectorSize			LmiVectorSize(LmiVoidPtr)
#define LmiPointerVectorMaxSize			LmiVectorMaxSize(LmiVoidPtr)
#define LmiPointerVectorEmpty			LmiVectorEmpty(LmiVoidPtr)
#define LmiPointerVectorEqual			LmiVectorEqual(LmiVoidPtr)
#define LmiPointerVectorLess			LmiVectorLess(LmiVoidPtr)
#define LmiPointerVectorAt				LmiVectorAt(LmiVoidPtr)
#define LmiPointerVectorAtConst			LmiVectorAtConst(LmiVoidPtr)
#define LmiPointerVectorFront			LmiVectorFront(LmiVoidPtr)
#define LmiPointerVectorFrontConst		LmiVectorFrontConst(LmiVoidPtr)
#define LmiPointerVectorBack			LmiVectorBack(LmiVoidPtr)
#define LmiPointerVectorBackConst		LmiVectorBackConst(LmiVoidPtr)
#define LmiPointerVectorInsert			LmiVectorInsert(LmiVoidPtr)
#define LmiPointerVectorInsertN			LmiVectorInsertN(LmiVoidPtr)
#define LmiPointerVectorInsertRange		LmiVectorInsertRange(LmiVoidPtr)
#define LmiPointerVectorErase			LmiVectorErase(LmiVoidPtr)
#define LmiPointerVectorEraseRange		LmiVectorEraseRange(LmiVoidPtr)
#define LmiPointerVectorClear			LmiVectorClear(LmiVoidPtr)
#define LmiPointerVectorResize			LmiVectorResize(LmiVoidPtr)
#define LmiPointerVectorPushBack		LmiVectorPushBack(LmiVoidPtr)
#define LmiPointerVectorPopBack			LmiVectorPopBack(LmiVoidPtr)
#define LmiPointerVectorCapacity		LmiVectorCapacity(LmiVoidPtr)
#define LmiPointerVectorReserve			LmiVectorReserve(LmiVoidPtr)
#define LmiPointerVectorDump			LmiVectorDump(LmiVoidPtr)

#define LmiPointerVectorIterator				LmiVectorIterator(LmiVoidPtr)
#define LmiPointerVectorIteratorValueType		LmiVectorIteratorValueType(LmiVoidPtr)
#define LmiPointerVectorIteratorPointer			LmiVectorIteratorPointer(LmiVoidPtr)
#define LmiPointerVectorIteratorDifferenceType	LmiVectorIteratorDifferenceType(LmiVoidPtr)
#define LmiPointerVectorIteratorConstructCopy	LmiVectorIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerVectorIteratorConstructExceptional	LmiVectorIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerVectorIteratorDestruct		LmiVectorIteratorDestruct(LmiVoidPtr)
#define LmiPointerVectorIteratorAssign			LmiVectorIteratorAssign(LmiVoidPtr)
#define LmiPointerVectorIteratorSwap			LmiVectorIteratorSwap(LmiVoidPtr)
#define LmiPointerVectorIteratorEqual			LmiVectorIteratorEqual(LmiVoidPtr)
#define LmiPointerVectorIteratorLess			LmiVectorIteratorLess(LmiVoidPtr)
#define LmiPointerVectorIteratorContentOf		LmiVectorIteratorContentOf(LmiVoidPtr)
#define LmiPointerVectorIteratorContentOfConst	LmiVectorIteratorContentOfConst(LmiVoidPtr)
#define LmiPointerVectorIteratorIncrement		LmiVectorIteratorIncrement(LmiVoidPtr)
#define LmiPointerVectorIteratorDecrement		LmiVectorIteratorDecrement(LmiVoidPtr)
#define LmiPointerVectorIteratorIncrementN		LmiVectorIteratorIncrementN(LmiVoidPtr)
#define LmiPointerVectorIteratorDecrementN		LmiVectorIteratorDecrementN(LmiVoidPtr)
#define LmiPointerVectorIteratorAt				LmiVectorIteratorAt(LmiVoidPtr)
#define LmiPointerVectorIteratorAdd				LmiVectorIteratorAdd(LmiVoidPtr)
#define LmiPointerVectorIteratorSubtract		LmiVectorIteratorSubtract(LmiVoidPtr)
#define LmiPointerVectorIteratorIsExceptional	LmiVectorIteratorIsExceptional(LmiVoidPtr)

#define LmiPointerVectorConstIterator				LmiVectorConstIterator(LmiVoidPtr)
#define LmiPointerVectorConstIteratorValueType		LmiVectorConstIteratorValueType(LmiVoidPtr)
#define LmiPointerVectorConstIteratorPointer		LmiVectorConstIteratorPointer(LmiVoidPtr)
#define LmiPointerVectorConstIteratorDifferenceType	LmiVectorConstIteratorDifferenceType(LmiVoidPtr)
#define LmiPointerVectorConstIteratorConstructCopy	LmiVectorConstIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerVectorConstIteratorConstructExceptional	LmiVectorConstIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerVectorConstIteratorDestruct		LmiVectorConstIteratorDestruct(LmiVoidPtr)
#define LmiPointerVectorConstIteratorAssign			LmiVectorConstIteratorAssign(LmiVoidPtr)
#define LmiPointerVectorConstIteratorSwap			LmiVectorConstIteratorSwap(LmiVoidPtr)
#define LmiPointerVectorConstIteratorEqual			LmiVectorConstIteratorEqual(LmiVoidPtr)
#define LmiPointerVectorConstIteratorLess			LmiVectorConstIteratorLess(LmiVoidPtr)
#define LmiPointerVectorConstIteratorContentOf		LmiVectorConstIteratorContentOf(LmiVoidPtr)
#define LmiPointerVectorConstIteratorContentOfConst	LmiVectorConstIteratorContentOfConst(LmiVoidPtr)
#define LmiPointerVectorConstIteratorIncrement		LmiVectorConstIteratorIncrement(LmiVoidPtr)
#define LmiPointerVectorConstIteratorDecrement		LmiVectorConstIteratorDecrement(LmiVoidPtr)
#define LmiPointerVectorConstIteratorIncrementN		LmiVectorConstIteratorIncrementN(LmiVoidPtr)
#define LmiPointerVectorConstIteratorDecrementN		LmiVectorConstIteratorDecrementN(LmiVoidPtr)
#define LmiPointerVectorConstIteratorAt				LmiVectorConstIteratorAt(LmiVoidPtr)
#define LmiPointerVectorConstIteratorAdd			LmiVectorConstIteratorAdd(LmiVoidPtr)
#define LmiPointerVectorConstIteratorSubtract		LmiVectorConstIteratorSubtract(LmiVoidPtr)
#define LmiPointerVectorConstIteratorIsExceptional	LmiVectorConstIteratorIsExceptional(LmiVoidPtr)

#define LmiPointerVectorReverseIterator					LmiVectorReverseIterator(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorValueType		LmiVectorReverseIteratorValueType(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorPointer			LmiVectorReverseIteratorPointer(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorDifferenceType	LmiVectorReverseIteratorDifferenceType(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorConstructCopy	LmiVectorReverseIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorConstructExceptional	LmiVectorReverseIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorDestruct			LmiVectorReverseIteratorDestruct(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorAssign			LmiVectorReverseIteratorAssign(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorSwap				LmiVectorReverseIteratorSwap(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorEqual			LmiVectorReverseIteratorEqual(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorLess				LmiVectorReverseIteratorLess(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorContentOf		LmiVectorReverseIteratorContentOf(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorContentOfConst	LmiVectorReverseIteratorContentOfConst(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorIncrement		LmiVectorReverseIteratorIncrement(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorDecrement		LmiVectorReverseIteratorDecrement(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorIncrementN		LmiVectorReverseIteratorIncrementN(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorDecrementN		LmiVectorReverseIteratorDecrementN(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorAt				LmiVectorReverseIteratorAt(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorAdd				LmiVectorReverseIteratorAdd(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorSubtract			LmiVectorReverseIteratorSubtract(LmiVoidPtr)
#define LmiPointerVectorReverseIteratorIsExceptional	LmiVectorReverseIteratorIsExceptional(LmiVoidPtr)

#define LmiPointerVectorConstReverseIterator				LmiVectorConstReverseIterator(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorValueType		LmiVectorConstReverseIteratorValueType(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorPointer			LmiVectorConstReverseIteratorPointer(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorDifferenceType	LmiVectorConstReverseIteratorDifferenceType(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorConstructCopy	LmiVectorConstReverseIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorConstructExceptional	LmiVectorConstReverseIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorDestruct		LmiVectorConstReverseIteratorDestruct(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorAssign			LmiVectorConstReverseIteratorAssign(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorSwap			LmiVectorConstReverseIteratorSwap(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorEqual			LmiVectorConstReverseIteratorEqual(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorLess			LmiVectorConstReverseIteratorLess(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorContentOf		LmiVectorConstReverseIteratorContentOf(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorContentOfConst	LmiVectorConstReverseIteratorContentOfConst(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorIncrement		LmiVectorConstReverseIteratorIncrement(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorDecrement		LmiVectorConstReverseIteratorDecrement(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorIncrementN		LmiVectorConstReverseIteratorIncrementN(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorDecrementN		LmiVectorConstReverseIteratorDecrementN(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorAt				LmiVectorConstReverseIteratorAt(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorAdd				LmiVectorConstReverseIteratorAdd(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorSubtract		LmiVectorConstReverseIteratorSubtract(LmiVoidPtr)
#define LmiPointerVectorConstReverseIteratorIsExceptional	LmiVectorConstReverseIteratorIsExceptional(LmiVoidPtr)

LMI_END_EXTERN_C

#endif /* LMI_POINTER_VECTOR_H_ */
