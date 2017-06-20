/** {file:
      {name: LmiCondition.h}
      {description: Objects to provide condition variables.}
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
#ifndef LMI_CONDITION_H_
#define LMI_CONDITION_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiSemaphore.h>
#include <Lmi/Os/LmiMonitor.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="private":
	{name: LmiCondition}
	{parent: Os}
	{include: Lmi/Os/LmiCondition.h}
	{description:
		A Condition variable.
	}
	{note: It is unspecified whether LMI condition variables have Hoare or Mesa semantics; Mesa should generally be assumed for safety.}
}
*/
#if defined(LMI_NEED_GENERIC_CONDITION)
typedef struct {
	LmiMonitor_Generic_* monitor;
	LmiSemaphore waiters;
	LmiInt waiterCount;
} LmiCondition_Generic_;
#endif

#if defined(LMI_USE_PTHREAD_CONDITION)
typedef struct {
	LmiMonitor* monitor;
	pthread_cond_t cond;
	LmiInt waiterCount;
} LmiCondition;

#elif defined(LMI_USE_VISTA_CONDITION)
typedef struct {
	LmiMonitor* monitor;
	CONDITION_VARIABLE cond;
	LmiInt waiterCount;
} LmiCondition;

#elif defined(LMI_USE_GENERIC_CONDITION)
typedef LmiCondition_Generic_ LmiCondition;

#endif

/* Low-level (no logging) condition interface */
/* you should use the high-level condition interface unless you have a good reason
   to use the low level interface (such as the implementation of logging) */

LMI_INLINE_DECLARATION LmiCondition* LmiConditionConstruct_(LmiCondition* x, LmiMonitor* monitor);
LMI_INLINE_DECLARATION void LmiConditionDestruct_(LmiCondition* x);
LMI_INLINE_DECLARATION LmiMonitor* LmiConditionGetMonitor_(LmiCondition* x);
LMI_INLINE_DECLARATION LmiInt LmiConditionGetNumWaiting_(LmiCondition* x);
LMI_INLINE_DECLARATION void LmiConditionWait_(LmiCondition* x);
LMI_INLINE_DECLARATION void LmiConditionNotify_(LmiCondition* x);
LMI_INLINE_DECLARATION void LmiConditionNotifyAll_(LmiCondition* x);

#if defined(LMI_NEED_GENERIC_CONDITION)
LMI_INLINE_DECLARATION LmiCondition_Generic_* LmiConditionConstruct_Generic_(LmiCondition_Generic_* x, LmiMonitor_Generic_* monitor);
LMI_INLINE_DECLARATION void LmiConditionDestruct_Generic_(LmiCondition_Generic_* x);
LMI_INLINE_DECLARATION LmiInt LmiConditionGetNumWaiting_Generic_(LmiCondition_Generic_* x);
LMI_INLINE_DECLARATION void LmiConditionWait_Generic_(LmiCondition_Generic_* x);
LMI_INLINE_DECLARATION void LmiConditionNotify_Generic_(LmiCondition_Generic_* x);
LMI_INLINE_DECLARATION void LmiConditionNotifyAll_Generic_(LmiCondition_Generic_* x);
#endif


/* High-level (with logging) condition interface */

/**
{function visibility="private":
	{name: LmiConditionConstruct}
	{parent: LmiCondition}
	{description:
		{p: Construct a condition variable object.}
	}
	{prototype: LmiCondition* LmiConditionConstruct(LmiCondition* x, LmiMonitor* monitor)}
	{parameter:
		{name: x}
		{description: A pointer to the condition variable object to construct.}
	}
	{parameter:
		{name: monitor}
		{description: A pointer to a monitor to use with the constructed condition variable.}
	}
	{return: A pointer to the condition variable object, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiCondition* LmiConditionConstruct(LmiCondition* x, LmiMonitor* monitor);

/**
{function visibility="private":
	{name: LmiConditionDestruct}
	{parent: LmiCondition}
	{description:
		{p: Destruct a condition variable object.}
	}
	{prototype: void LmiConditionDestruct(LmiCondition* x)}
	{parameter:
		{name: x}
		{description: A pointer to the condition variable object to destruct.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiConditionDestruct(LmiCondition* x);

/**
{function visibility="private":
	{name: LmiConditionGetMonitor}
	{parent: LmiCondition}
	{description:
		{p: Get the monitor associated with the condition variable object.}
	}
	{prototype: LmiMonitor* LmiConditionGetMonitor(LmiCondition* x)}
	{parameter:
		{name: x}
		{description: A pointer to the condition variable object.}
	}
	{return: A pointer to the monitor object associated with the condition variable object.}
}
*/
LMI_INLINE_DECLARATION LmiMonitor* LmiConditionGetMonitor(LmiCondition* x);

/**
{function visibility="private":
	{name: LmiConditionGetNumWaiting}
	{parent: LmiCondition}
	{description:
		{p: Get the number of threads waiting on the condition variable object.}
	}
	{prototype: LmiInt LmiConditionGetNumWaiting(LmiCondition* x)}
	{parameter:
		{name: x}
		{description: A pointer to the condition variable object.}
	}
	{return: The number of threads currently waiting on the condition variable object.}
	{note: This value is only reliable if the caller holds the condition's associated monitor.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiConditionGetNumWaiting(LmiCondition* x);

/**
{function visibility="private":
	{name: LmiConditionWait}
	{parent: LmiCondition}
	{description:
		{p: Wait for the condition variable object to be signalled (notified).}
	}
	{prototype: void LmiConditionWait(LmiCondition* x)}
	{parameter:
		{name: x}
		{description: A pointer to the condition variable object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiConditionWait(LmiCondition* x);

/**
{function visibility="private":
	{name: LmiConditionNotify}
	{parent: LmiCondition}
	{description:
		{p: Signal the condition variable object to release one waiting thread.}
	}
	{prototype: void LmiConditionNotify(LmiCondition* x)}
	{parameter:
		{name: x}
		{description: A pointer to the condition variable object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiConditionNotify(LmiCondition* x);

/**
{function visibility="private":
	{name: LmiConditionNotifyAll}
	{parent: LmiCondition}
	{description:
		{p: Signal the condition variable object to release all waiting threads.}
	}
	{prototype: void LmiConditionNotifyAll(LmiCondition* x)}
	{parameter:
		{name: x}
		{description: A pointer to the condition variable object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiConditionNotifyAll(LmiCondition* x);


LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiConditionInline.h>
#endif

#endif /* LMI_CONDITION_H_ */

