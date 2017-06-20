/** {file:
      {name: LmiMonitor.h}
      {description: Objects to provide monitors.}
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
#ifndef LMI_MONITOR_H_
#define LMI_MONITOR_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiSemaphore.h>


#if defined(LMI_HAVE_PTHREAD_COND_INIT)
#define LMI_USE_PTHREAD_CONDITION 1
#elif defined(LMI_HAVE_INITIALIZECONDITIONVARIABLE)
/* Windows.  Windows ConditionVariable was added in Vista. */
#define LMI_USE_VISTA_CONDITION 1
#else
#define LMI_USE_GENERIC_CONDITION 1
#define LMI_NEED_GENERIC_CONDITION 1
#endif

LMI_BEGIN_EXTERN_C

/**
{type visibility="private":
	{name: LmiMonitor}
	{parent: Os}
	{include: Lmi/Os/LmiMonitor.h}
	{description:
		A monitor.  A monitor controls access to one or more condition
		variables in much the same way as a mutex. Monitors however
		allow access to be atomically relinquished and the monitor's
		thread put to sleep waiting for a condition variable to be
		signalled.  When the condition variable is signalled, the
		monitor's thread will wake up and atomically re-acquire
		exclusive access.
	}
}
*/
#if defined(LMI_NEED_GENERIC_CONDITION)
typedef struct {
	LmiSemaphore mutex;
	LmiSemaphore notifiers;
	LmiInt notifierCount;
} LmiMonitor_Generic_;
#endif

#if defined(LMI_USE_PTHREAD_CONDITION)
typedef pthread_mutex_t LmiMonitor;
#elif defined(LMI_USE_VISTA_CONDITION)
typedef CRITICAL_SECTION LmiMonitor;
#elif defined(LMI_USE_GENERIC_CONDITION)
typedef LmiMonitor_Generic_ LmiMonitor;
#endif

/* Low-level (no logging) monitor interface */
/* you should use the high-level monitor interface unless you have a good reason
   to use the low level interface (such as the implementation of logging) */
LMI_INLINE_DECLARATION LmiMonitor* LmiMonitorConstruct_(LmiMonitor* x);
LMI_INLINE_DECLARATION void LmiMonitorDestruct_(LmiMonitor* x);
LMI_INLINE_DECLARATION void LmiMonitorLock_(LmiMonitor* x);
LMI_INLINE_DECLARATION void LmiMonitorUnlock_(LmiMonitor* x);

#if defined(LMI_NEED_GENERIC_CONDITION)
/* Implementation (only other LmiCondition functions should call these functions) */
LMI_INLINE_DECLARATION LmiMonitor_Generic_* LmiMonitorConstruct_Generic_(LmiMonitor_Generic_* x);
LMI_INLINE_DECLARATION void LmiMonitorDestruct_Generic_(LmiMonitor_Generic_* x);
LMI_INLINE_DECLARATION void LmiMonitorLock_Generic_(LmiMonitor_Generic_* x);
LMI_INLINE_DECLARATION void LmiMonitorUnlock_Generic_(LmiMonitor_Generic_* x);

/* Protected interface (only LmiCondition should call these functions) */
LMI_INLINE_DECLARATION void LmiMonitorAddNotifier_Generic_(LmiMonitor_Generic_* x);
LMI_INLINE_DECLARATION void LmiMonitorRemoveNotifier_Generic_(LmiMonitor_Generic_* x);
LMI_INLINE_DECLARATION void LmiMonitorNotify_Generic_(LmiMonitor_Generic_* x);
#endif


/* High-level (with logging) monitor interface */

/**
{function visibility="private":
	{name: LmiMonitorConstruct}
	{parent: LmiMonitor}
	{description:
		{p: Construct a monitor object.}
	}
	{prototype: LmiMonitor* LmiMonitorConstruct(LmiMonitor* x)}
	{parameter:
		{name: x}
		{description: A pointer to the monitor object to construct.}
	}
	{return: A pointer to the monitor object, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiMonitor* LmiMonitorConstruct(LmiMonitor* x);

/**
{function visibility="private":
	{name: LmiMonitorDestruct}
	{parent: LmiMonitor}
	{description:
		{p: Destruct a monitor object.}
	}
	{prototype: void LmiMonitorDestruct(LmiMonitor* x)}
	{parameter:
		{name: x}
		{description: A pointer to the monitor object to destruct.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiMonitorDestruct(LmiMonitor* x);

/**
{function visibility="private":
	{name: LmiMonitorLock}
	{parent: LmiMonitor}
	{description:
		{p: Lock a monitor object.}
	}
	{prototype: void LmiMonitorLock(LmiMonitor* x)}
	{parameter:
		{name: x}
		{description: A pointer to the monitor object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiMonitorLock(LmiMonitor* x);

/**
{function visibility="private":
	{name: LmiMonitorUnlock}
	{parent: LmiMonitor}
	{description:
		{p: Unlock a monitor object.}
	}
	{prototype: void LmiMonitorUnlock(LmiMonitor* x)}
	{parameter:
		{name: x}
		{description: A pointer to the monitor object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiMonitorUnlock(LmiMonitor* x);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiMonitorInline.h>
#endif

#endif /* LMI_MONITOR_H_ */
