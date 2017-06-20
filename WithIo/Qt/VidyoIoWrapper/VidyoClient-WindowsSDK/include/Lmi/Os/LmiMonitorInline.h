/**
   {file:
     {name: LmiMonitorInline.h}
     {description: Inline functions for LmiMonitor.}
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

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAssert.h>
#include <Lmi/Os/LmiLog.h>

#if defined(LMI_NEED_GENERIC_CONDITION)
LMI_INLINE LmiMonitor_Generic_* LmiMonitorConstruct_Generic_(LmiMonitor_Generic_* x) {
	if (LmiSemaphoreConstruct(&x->mutex, 1) != 0) {
		if (LmiSemaphoreConstruct(&x->notifiers, 0) != 0) {
			x->notifierCount = 0;
			return x;
		} else {
			LmiSemaphoreDestruct(&x->mutex);
		}
	}
	return 0;
}

LMI_INLINE void LmiMonitorDestruct_Generic_(LmiMonitor_Generic_* x) {
	LmiSemaphoreDestruct(&x->mutex);
	LmiSemaphoreDestruct(&x->notifiers);
}
LMI_INLINE void LmiMonitorLock_Generic_(LmiMonitor_Generic_* x) {
	LmiSemaphoreAcquire(&x->mutex);
}
LMI_INLINE void LmiMonitorUnlock_Generic_(LmiMonitor_Generic_* x) {
	LmiAssert(x->notifierCount >= 0);
	if (x->notifierCount > 0)
		LmiSemaphoreRelease(&x->notifiers);
	else
		LmiSemaphoreRelease(&x->mutex);
}

/* Protected interface (only LmiCondition should call these functions) */
LMI_INLINE void LmiMonitorAddNotifier_Generic_(LmiMonitor_Generic_* x) {
	++(x->notifierCount);
}
LMI_INLINE void LmiMonitorRemoveNotifier_Generic_(LmiMonitor_Generic_* x) {
	LmiAssert(x->notifierCount > 0);
	--(x->notifierCount);
	
}
LMI_INLINE void LmiMonitorNotify_Generic_(LmiMonitor_Generic_* x) {
	LmiSemaphoreAcquire(&x->notifiers);
}
#endif

#if defined(LMI_USE_PTHREAD_CONDITION)
LMI_INLINE LmiMonitor* LmiMonitorConstruct_(LmiMonitor* x) {	
	LmiMonitor* r = 0;

#if defined(__CYGWIN__)
	*x = 0; /* Avoids cygwin bug */
#endif

	if (pthread_mutex_init(x, NULL) == 0)
		r = x;
	return r;
}


LMI_INLINE void LmiMonitorDestruct_(LmiMonitor* x) {
	pthread_mutex_destroy(x);
}


LMI_INLINE void LmiMonitorLock_(LmiMonitor* x) {
	pthread_mutex_lock(x);
}


LMI_INLINE void LmiMonitorUnlock_(LmiMutex* x) {
	pthread_mutex_unlock(x);
}

#elif defined(LMI_USE_VISTA_CONDITION)
LMI_INLINE LmiMonitor* LmiMonitorConstruct_(LmiMonitor* x) {
	if (InitializeCriticalSectionEx(x, 0, 0) == 0)
		return NULL;
	return x;
}
LMI_INLINE void LmiMonitorDestruct_(LmiMonitor* x) {
	DeleteCriticalSection(x);
}
LMI_INLINE void LmiMonitorLock_(LmiMonitor* x) {
	EnterCriticalSection(x);
}
LMI_INLINE void LmiMonitorUnlock_(LmiMonitor* x) {
	LeaveCriticalSection(x);
} 

#elif defined(LMI_USE_GENERIC_CONDITION)

LMI_INLINE LmiMonitor* LmiMonitorConstruct_(LmiMonitor* x) {
	return LmiMonitorConstruct_Generic_(x);
}

LMI_INLINE void LmiMonitorDestruct_(LmiMonitor* x) {
	LmiMonitorDestruct_Generic_(x);
}
LMI_INLINE void LmiMonitorLock_(LmiMonitor* x) {
	LmiMonitorLock_Generic_(x);
}
LMI_INLINE void LmiMonitorUnlock_(LmiMonitor* x) {
	LmiMonitorUnlock_Generic_(x);
}

#endif

/* High-level API (with logging) */
LMI_INLINE LmiMonitor* LmiMonitorConstruct(LmiMonitor* x) {
	LmiMonitor* r;

	LmiLogEnter(LmiLogMutex_);
	r = LmiMonitorConstruct_(x);
	LmiLogLeave(LmiLogMutex_);
	return r;
}
LMI_INLINE void LmiMonitorDestruct(LmiMonitor* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiMonitorDestruct_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE void LmiMonitorLock(LmiMonitor* x) {
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	LmiTime timeBefore = LmiTimeGetCurrentMonotonicTime();
	LmiTime timeAfter, timeElapsed;
#endif
	LmiLogEnter(LmiLogMutex_);
	LmiMonitorLock_(x);
	LmiLogLeave(LmiLogMutex_);
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	timeAfter = LmiTimeGetCurrentMonotonicTime();
	timeElapsed = timeAfter - timeBefore;
	if (timeElapsed > LMI_MUTEX_TIME_WARNING_THRESHOLD) {
		LmiLogWarningFormatted(LmiLogMutex_, "Lock of monitor %p took %lld.%06ld ms",
			x,
			(long long)(timeElapsed / LMI_NSECS_PER_MSEC),
			(long)(timeElapsed % LMI_NSECS_PER_MSEC));
	}
#endif
}
LMI_INLINE void LmiMonitorUnlock(LmiMonitor* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiMonitorUnlock_(x);
	LmiLogLeave(LmiLogMutex_);
}
