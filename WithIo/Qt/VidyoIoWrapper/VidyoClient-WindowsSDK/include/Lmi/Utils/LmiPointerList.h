/**
   {file: 
     {name: LmiPointerList.h}
     {description: List of generic pointers.}
     {copyright:
     	(c) 2006-2015 Vidyo, Inc.,
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

#ifndef LMI_POINTER_LIST_H_
#define LMI_POINTER_LIST_H_


#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiBasicTypesContainer.h>

LMI_BEGIN_EXTERN_C

#define LmiPointerList					LmiList(LmiVoidPtr)

#define LmiPointerListConstructDefault	LmiListConstructDefault(LmiVoidPtr)
#define LmiPointerListDestruct			LmiListDestruct(LmiVoidPtr)
#define LmiPointerListConstructCopy		LmiListConstructCopy(LmiVoidPtr)

#define LmiPointerListAssign			LmiListAssign(LmiVoidPtr)
#define LmiPointerListSwap				LmiListSwap(LmiVoidPtr)
#define LmiPointerListEqual				LmiListEqual(LmiVoidPtr)
#define LmiPointerListLess				LmiListLess(LmiVoidPtr)

#define LmiPointerListBegin				LmiListBegin(LmiVoidPtr)
#define LmiPointerListBeginConst		LmiListBeginConst(LmiVoidPtr)
#define LmiPointerListEnd				LmiListEnd(LmiVoidPtr)
#define LmiPointerListEndConst			LmiListEndConst(LmiVoidPtr)
#define LmiPointerListSize				LmiListSize(LmiVoidPtr)
#define LmiPointerListMaxSize			LmiListMaxSize(LmiVoidPtr)
#define LmiPointerListEmpty				LmiListEmpty(LmiVoidPtr)

#define LmiPointerListRBegin			LmiListRBegin(LmiVoidPtr)
#define LmiPointerListRBeginConst		LmiListRBeginConst(LmiVoidPtr)
#define LmiPointerListREnd				LmiListREnd(LmiVoidPtr)
#define LmiPointerListREndConst			LmiListREndConst(LmiVoidPtr)

#define LmiPointerListConstructN		LmiListConstructN(LmiVoidPtr)
#define LmiPointerListConstructRange	LmiListConstructRange(LmiVoidPtr)
#define LmiPointerListFront				LmiListFront(LmiVoidPtr)
#define LmiPointerListFrontConst		LmiListFrontConst(LmiVoidPtr)
#define LmiPointerListInsert			LmiListInsert(LmiVoidPtr)
#define LmiPointerListInsertN			LmiListInsertN(LmiVoidPtr)
#define LmiPointerListInsertRange		LmiListInsertRange(LmiVoidPtr)
#define LmiPointerListErase				LmiListErase(LmiVoidPtr)
#define LmiPointerListEraseRange		LmiListEraseRange(LmiVoidPtr)
#define LmiPointerListClear				LmiListClear(LmiVoidPtr)
#define LmiPointerListResize			LmiListResize(LmiVoidPtr)

#define LmiPointerListPushFront			LmiListPushFront(LmiVoidPtr)
#define LmiPointerListPopFront			LmiListPopFront(LmiVoidPtr)

#define LmiPointerListBack				LmiListBack(LmiVoidPtr)
#define LmiPointerListBackConst			LmiListBackConst(LmiVoidPtr)
#define LmiPointerListPushBack			LmiListPushBack(LmiVoidPtr)
#define LmiPointerListPopBack			LmiListPopBack(LmiVoidPtr)

#define LmiPointerListSplice			LmiListSplice(LmiVoidPtr)
#define LmiPointerListSpliceOne			LmiListSpliceOne(LmiVoidPtr)

#define LmiPointerListGetNodeSize		LmiListGetNodeSize(LmiVoidPtr)
#define LmiPointerListGetAllocator		LmiListGetAllocator(LmiVoidPtr)

#define LmiListConstructIteratorRange(T_, InputIterator_)	LmiConstructIteratorRange(LmiList(T_), InputIterator_)
#define LmiListInsertIteratorRange(T_, InputIterator_)	LmiInsertIteratorRange(LmiList(T_), InputIterator_)


/* List iterator names: */
#define LmiPointerListIterator			LmiListIterator(LmiVoidPtr)
#define LmiPointerListConstIterator		LmiListConstIterator(LmiVoidPtr)
#define LmiPointerListReverseIterator	LmiListReverseIterator(LmiVoidPtr)
#define LmiPointerListConstReverseIterator	LmiListConstReverseIterator(LmiVoidPtr)

/* Public templatized member functions of LmiListIterator */
#define LmiPointerListIteratorConstruct	LmiListIteratorConstruct(LmiVoidPtr)
#define LmiPointerListIteratorDestruct	LmiListIteratorDestruct(LmiVoidPtr)
#define LmiPointerListIteratorConstructCopy	LmiListIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerListIteratorAssign	LmiListIteratorAssign(LmiVoidPtr)
#define LmiPointerListIteratorSwap		LmiListIteratorSwap(LmiVoidPtr)
#define LmiPointerListIteratorEqual		LmiListIteratorEqual(LmiVoidPtr)
#define LmiPointerListIteratorContentOf	LmiListIteratorContentOf(LmiVoidPtr)
#define LmiPointerListIteratorIncrement	LmiListIteratorIncrement(LmiVoidPtr)
#define LmiPointerListIteratorDecrement	LmiListIteratorDecrement(LmiVoidPtr)
#define LmiPointerListIteratorConstructExceptional	LmiListIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerListIteratorIsExceptional	LmiListIteratorIsExceptional(LmiVoidPtr)

/* Public templatized member functions of LmiListConstIterator */
#define LmiPointerListConstIteratorConstruct		LmiListConstIteratorConstruct(LmiVoidPtr)
#define LmiPointerListConstIteratorDestruct			LmiListConstIteratorDestruct(LmiVoidPtr)
#define LmiPointerListConstIteratorConstructCopy	LmiListConstIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerListConstIteratorAssign			LmiListConstIteratorAssign(LmiVoidPtr)
#define LmiPointerListConstIteratorSwap				LmiListConstIteratorSwap(LmiVoidPtr)
#define LmiPointerListConstIteratorEqual			LmiListConstIteratorEqual(LmiVoidPtr)
#define LmiPointerListConstIteratorContentOf		LmiListConstIteratorContentOf(LmiVoidPtr)
#define LmiPointerListConstIteratorIncrement		LmiListConstIteratorIncrement(LmiVoidPtr)
#define LmiPointerListConstIteratorDecrement		LmiListConstIteratorDecrement(LmiVoidPtr)
#define LmiPointerListConstIteratorConstructExceptional	LmiListConstIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerListConstIteratorIsExceptional	LmiListConstIteratorIsExceptional(LmiVoidPtr)

/* Public templatized member functions of LmiListIterator */
#define LmiPointerListReverseIteratorConstruct		LmiListReverseIteratorConstruct(LmiVoidPtr)
#define LmiPointerListReverseIteratorDestruct		LmiListReverseIteratorDestruct(LmiVoidPtr)
#define LmiPointerListReverseIteratorConstructCopy	LmiListReverseIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerListReverseIteratorAssign			LmiListReverseIteratorAssign(LmiVoidPtr)
#define LmiPointerListReverseIteratorSwap			LmiListReverseIteratorSwap(LmiVoidPtr)
#define LmiPointerListReverseIteratorEqual			LmiListReverseIteratorEqual(LmiVoidPtr)
#define LmiPointerListReverseIteratorContentOf		LmiListReverseIteratorContentOf(LmiVoidPtr)
#define LmiPointerListReverseIteratorIncrement		LmiListReverseIteratorIncrement(LmiVoidPtr)
#define LmiPointerListReverseIteratorDecrement		LmiListReverseIteratorDecrement(LmiVoidPtr)
#define LmiPointerListReverseIteratorConstructExceptional	LmiListReverseIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerListReverseIteratorIsExceptional	LmiListReverseIteratorIsExceptional(LmiVoidPtr)

/* Public templatized member functions of LmiListConstReverseIterator */
#define LmiPointerListConstReverseIteratorConstruct	LmiListConstReverseIteratorConstruct(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorDestruct	LmiListConstReverseIteratorDestruct(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorConstructCopy	LmiListConstReverseIteratorConstructCopy(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorAssign	LmiListConstReverseIteratorAssign(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorSwap		LmiListConstReverseIteratorSwap(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorEqual		LmiListConstReverseIteratorEqual(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorContentOf	LmiListConstReverseIteratorContentOf(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorIncrement	LmiListConstReverseIteratorIncrement(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorDecrement	LmiListConstReverseIteratorDecrement(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorConstructExceptional	LmiListConstReverseIteratorConstructExceptional(LmiVoidPtr)
#define LmiPointerListConstReverseIteratorIsExceptional	LmiListConstReverseIteratorIsExceptional(LmiVoidPtr)

LMI_END_EXTERN_C

#endif /* LMI_POINTER_LIST_H_ */
