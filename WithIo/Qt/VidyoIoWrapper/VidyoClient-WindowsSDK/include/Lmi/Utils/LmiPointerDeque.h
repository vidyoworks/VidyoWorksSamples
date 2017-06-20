/**
{file:
	{name: LmiPointerDeque.h}
	{description: Deque of LmiVoidPtr.}
	{copyright:
		(c) 2009-2015 Vidyo, Inc.,
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
#ifndef LMI_POINTERDEQUE_H
#define LMI_POINTERDEQUE_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiDeque.h>
#include <Lmi/Utils/LmiBasicTypesContainer.h>

LMI_BEGIN_EXTERN_C

#define LmiPointerDeque                 LmiDeque(LmiVoidPtr)
#define LmiPointerDequeConstruct        LmiDequeConstruct(LmiVoidPtr)
#define LmiPointerDequeConstructCopy    LmiDequeConstructCopy(LmiVoidPtr)
#define LmiPointerDequeDestruct         LmiDequeDestruct(LmiVoidPtr)
#define LmiPointerDequeFront            LmiDequeFront(LmiVoidPtr)
#define LmiPointerDequeFrontConst       LmiDequeFrontConst(LmiVoidPtr)
#define LmiPointerDequeBack             LmiDequeBack(LmiVoidPtr)
#define LmiPointerDequeBackConst        LmiDequeBackConst(LmiVoidPtr)
#define LmiPointerDequeAt               LmiDequeAt(LmiVoidPtr)
#define LmiPointerDequeAtConst          LmiDequeAtConst(LmiVoidPtr)
#define LmiPointerDequePushFront        LmiDequePushFront(LmiVoidPtr)
#define LmiPointerDequePushBack         LmiDequePushBack(LmiVoidPtr)
#define LmiPointerDequePopFront         LmiDequePopFront(LmiVoidPtr)
#define LmiPointerDequePopBack          LmiDequePopBack(LmiVoidPtr)
#define LmiPointerDequeSize             LmiDequeSize(LmiVoidPtr)
#define LmiPointerDequeCapacity         LmiDequeCapacity(LmiVoidPtr)
#define LmiPointerDequeReserve          LmiDequeReserve(LmiVoidPtr)
#define LmiPointerDequeEmpty            LmiDequeEmpty(LmiVoidPtr)
#define LmiPointerDequeClear            LmiDequeClear(LmiVoidPtr)

LMI_END_EXTERN_C

#endif
