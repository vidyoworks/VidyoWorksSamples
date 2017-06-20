/** {file:
      {name: LmiSemaphore.h}
      {description: Objects to provide semaphores.}
      {copyright:
      	(c) 2005-2014 Vidyo, Inc.,
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
#ifndef LMI_SEMAPHORE_H_
#define LMI_SEMAPHORE_H_

#include <Lmi/Utils/LmiTypes.h>

/**
{type visibility="private":
	{name: LmiSemaphore}
	{parent: Os}
	{include: Lmi/Os/LmiSemaphore.h}
	{description:
		A counting semaphore object.
	}
}
*/

#if defined(LMI_HAVE_SEMAPHORE_CREATE)
#include <mach/mach_init.h>
#include <mach/task.h>
#include <mach/semaphore.h>
typedef struct {
	semaphore_t sem;
	task_t task;
} LmiSemaphore;
#elif defined(LMI_HAVE_SEM_INIT)
#include <semaphore.h>
#include <errno.h>
typedef sem_t LmiSemaphore;
#elif defined(LMI_HAVE_CREATESEMAPHORE) || defined(LMI_HAVE_CREATESEMAPHOREEX)
#include <winsock2.h>
typedef HANDLE LmiSemaphore;
#elif defined(LMI_HAVE_TI_CREATESEMAPHORE)
typedef LmiInt LmiSemaphore;
#else
#error Unknown Semaphore implementation
#endif

LMI_BEGIN_EXTERN_C

/* Low-level (no logging) semaphore interface */
/* you should use the high-level semaphore interface unless you have a good reason
   to use the low level interface (such as the implementation of logging) */
LMI_INLINE_DECLARATION LmiSemaphore* LmiSemaphoreConstruct_(LmiSemaphore* x, LmiUint initialCount);
LMI_INLINE_DECLARATION void LmiSemaphoreDestruct_(LmiSemaphore* x);
LMI_INLINE_DECLARATION void LmiSemaphoreAcquire_(LmiSemaphore* x);
LMI_INLINE_DECLARATION void LmiSemaphoreRelease_(LmiSemaphore* x);

/* High-level (with logging) semaphore interface */
/**
{function visibility="private":
	{name: LmiSemaphoreConstruct}
	{parent: LmiSemaphore}
	{description:
		{p: Construct a counting semaphore object.}
	}
	{prototype: LmiSemaphore* LmiSemaphoreConstruct(LmiSemaphore* x, LmiUint initialCount)}
	{parameter:
		{name: x}
		{description: A pointer to the semaphore object to construct.}
	}
	{parameter:
		{name: initialCount}
		{description:
			The initial count of the semaphore which represents the number of
			LmiSemaphoreAcquire operations (without an intervening LmiSemaphoreRelease)
			which will succeed before the semaphore	blocks.
		}
	}
	{return: A pointer to the semaphore object, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiSemaphore* LmiSemaphoreConstruct(LmiSemaphore* x, LmiUint initialCount);

/**
{function visibility="private":
	{name: LmiSemaphoreDestruct}
	{parent: LmiSemaphore}
	{description:
		{p: Destruct a counting semaphore object.}
	}
	{prototype: void LmiSemaphoreDestruct(LmiSemaphore* x)}
	{parameter:
		{name: x}
		{description: A pointer to the semaphore object to destruct.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiSemaphoreDestruct(LmiSemaphore* x);

/**
{function visibility="private":
	{name: LmiSemaphoreAcquire}
	{parent: LmiSemaphore}
	{description:
		{p: Acquire a semaphore object.}
	}
	{prototype: void LmiSemaphoreAcquire(LmiSemaphore* x)}
	{parameter:
		{name: x}
		{description: A pointer to the semaphore object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiSemaphoreAcquire(LmiSemaphore* x);

/**
{function visibility="private":
	{name: LmiSemaphoreRelease}
	{parent: LmiSemaphore}
	{description:
		{p: Release a semaphore object.}
	}
	{prototype: void LmiSemaphoreRelease(LmiSemaphore* x)}
	{parameter:
		{name: x}
		{description: A pointer to the semaphore object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiSemaphoreRelease(LmiSemaphore* x);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiSemaphoreInline.h>
#endif

#endif /* LMI_SEMAPHORE_H_ */

