/**
   {file:
     {name: LmiConditionInline.h}
     {description: Inline functions for LmiCondition.}
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
LMI_INLINE LmiCondition_Generic_* LmiConditionConstruct_Generic_(LmiCondition_Generic_* x, LmiMonitor_Generic_* monitor) {
	x->monitor = monitor;
	x->waiterCount = 0;
	if (LmiSemaphoreConstruct(&x->waiters, 0) == 0)
		return 0;
	return x;
}
LMI_INLINE void LmiConditionDestruct_Generic_(LmiCondition_Generic_* x) {
	LmiSemaphoreDestruct(&x->waiters);
}
LMI_INLINE LmiInt LmiConditionGetNumWaiting_Generic_(LmiCondition_Generic_* x) {
	return x->waiterCount;
}
LMI_INLINE void LmiConditionWait_Generic_(LmiCondition_Generic_* x) {
	++(x->waiterCount);
	LmiAssert(x->waiterCount > 0);
	LmiMonitorUnlock_Generic_(x->monitor);
	LmiSemaphoreAcquire(&x->waiters);
	LmiAssert(x->waiterCount > 0);
	--(x->waiterCount);
}
LMI_INLINE void LmiConditionNotify_Generic_(LmiCondition_Generic_* x) {
	LmiMonitorAddNotifier_Generic_(x->monitor);
	if (x->waiterCount > 0) {
		LmiSemaphoreRelease(&x->waiters);
		LmiMonitorNotify_Generic_(x->monitor);
	}
	LmiMonitorRemoveNotifier_Generic_(x->monitor);
}
LMI_INLINE void LmiConditionNotifyAll_Generic_(LmiCondition_Generic_* x) {
	LmiMonitorAddNotifier_Generic_(x->monitor);
	while (x->waiterCount > 0) {
		LmiSemaphoreRelease(&x->waiters);
		LmiMonitorNotify_Generic_(x->monitor);
	}
	LmiMonitorRemoveNotifier_Generic_(x->monitor);
}
#endif

#if defined(LMI_USE_PTHREAD_CONDITION)
LMI_INLINE LmiCondition* LmiConditionConstruct_(LmiCondition* x, LmiMonitor* monitor) {
	x->monitor = monitor;
	x->waiterCount = 0;
#if defined(__CYGWIN__)
	x->cond = 0; /* Avoids cygwin bug */
#endif
	if (pthread_cond_init(&x->cond, 0) != 0)
		return 0;
	return x;
}
LMI_INLINE void LmiConditionDestruct_(LmiCondition* x) {
	pthread_cond_destroy(&x->cond);
}
LMI_INLINE LmiMonitor* LmiConditionGetMonitor_(LmiCondition* x) {
	return x->monitor;
}
LMI_INLINE LmiInt LmiConditionGetNumWaiting_(LmiCondition* x) {
	return x->waiterCount;
}
LMI_INLINE void LmiConditionWait_(LmiCondition* x) {
	int ret;
	++(x->waiterCount);
	LmiAssert(x->waiterCount > 0);
	ret = pthread_cond_wait(&x->cond, x->monitor);
	LmiAssert(ret == 0);
	LmiAssert(x->waiterCount > 0);
	--(x->waiterCount);
}
LMI_INLINE void LmiConditionNotify_(LmiCondition* x) {
	int ret;
	ret = pthread_cond_signal(&x->cond);
	LmiAssert(ret == 0);
}
LMI_INLINE void LmiConditionNotifyAll_(LmiCondition* x) {
	int ret;
	ret = pthread_cond_broadcast(&x->cond);
	LmiAssert(ret == 0);
}

#elif defined(LMI_USE_VISTA_CONDITION)
LMI_INLINE LmiCondition* LmiConditionConstruct_(LmiCondition* x, LmiMonitor* monitor) {
    x->monitor = monitor;
    x->waiterCount = 0;
    InitializeConditionVariable(&x->cond);
    return x;
}
LMI_INLINE void LmiConditionDestruct_(LmiCondition* x) {
	/* Nothing needs to be done */
}
LMI_INLINE LmiMonitor* LmiConditionGetMonitor_(LmiCondition* x) {
    return x->monitor;
}
LMI_INLINE LmiInt LmiConditionGetNumWaiting_(LmiCondition* x) {
    return x->waiterCount;
}
LMI_INLINE void LmiConditionWait_(LmiCondition* x) {
    BOOL ret;
    ++(x->waiterCount);
    LmiAssert(x->waiterCount > 0);
    ret = SleepConditionVariableCS(&x->cond, x->monitor, INFINITE);
    LmiAssert(ret);
    LmiAssert(x->waiterCount > 0);
    --(x->waiterCount);
}
LMI_INLINE void LmiConditionNotify_(LmiCondition* x) {
    WakeConditionVariable(&x->cond);
}
LMI_INLINE void LmiConditionNotifyAll_(LmiCondition* x) {
    WakeAllConditionVariable(&x->cond);
}

#elif defined(LMI_USE_GENERIC_CONDITION) 
LMI_INLINE LmiCondition* LmiConditionConstruct_(LmiCondition* x, LmiMonitor* monitor) {
	if (LmiConditionConstruct_Generic_(x, monitor) == NULL)
		return NULL;
	return x;
}
LMI_INLINE void LmiConditionDestruct_(LmiCondition* x) {
	LmiConditionDestruct_Generic_(x);
}
LMI_INLINE LmiMonitor* LmiConditionGetMonitor_(LmiCondition* x) {
	return x->monitor;
}
LMI_INLINE LmiInt LmiConditionGetNumWaiting_(LmiCondition* x) {
	return LmiConditionGetNumWaiting_Generic_(x);
}
LMI_INLINE void LmiConditionWait_(LmiCondition* x) {
	LmiConditionWait_Generic_(x);
}
LMI_INLINE void LmiConditionNotify_(LmiCondition* x) {
	LmiConditionNotify_Generic_(x);
}
LMI_INLINE void LmiConditionNotifyAll_(LmiCondition* x) {
	LmiConditionNotifyAll_Generic_(x);
}
#endif

/* High-level API */
LMI_INLINE LmiCondition* LmiConditionConstruct(LmiCondition* x, LmiMonitor* m) {
	LmiCondition* r;

	LmiLogEnter(LmiLogMutex_);
	r = LmiConditionConstruct_(x, m);
	LmiLogLeave(LmiLogMutex_);
	return r;
}
LMI_INLINE void LmiConditionDestruct(LmiCondition* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiConditionDestruct_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE LmiMonitor* LmiConditionGetMonitor(LmiCondition* x) {
	LmiMonitor* ret;
	LmiLogEnter(LmiLogMutex_);
	ret = LmiConditionGetMonitor_(x);
	LmiLogLeave(LmiLogMutex_);
	return ret;
}
LMI_INLINE LmiInt LmiConditionGetNumWaiting(LmiCondition* x) {
	LmiInt ret;
	LmiLogEnter(LmiLogMutex_);
	ret = LmiConditionGetNumWaiting_(x);
	LmiLogLeave(LmiLogMutex_);
	return ret;
}
LMI_INLINE void LmiConditionWait(LmiCondition* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiLogDebugFormatted(LmiLogMutex_, "x=%p, waiterCount=%d", x, LmiConditionGetNumWaiting_(x));
	LmiConditionWait_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE void LmiConditionNotify(LmiCondition* x) {
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	LmiTime timeBefore = LmiTimeGetCurrentMonotonicTime();
	LmiTime timeAfter, timeElapsed;
#endif
	LmiLogEnter(LmiLogMutex_);
	LmiLogDebugFormatted(LmiLogMutex_, "x=%p, waiterCount=%d", x, LmiConditionGetNumWaiting_(x));
	LmiConditionNotify_(x);
	LmiLogLeave(LmiLogMutex_);
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	timeAfter = LmiTimeGetCurrentMonotonicTime();
	timeElapsed = timeAfter - timeBefore;
	if (timeElapsed > LMI_MUTEX_TIME_WARNING_THRESHOLD) {
		LmiLogWarningFormatted(LmiLogMutex_, "Notify of condition %p took %lld.%06ld ms",
			x,
			(long long)(timeElapsed / LMI_NSECS_PER_MSEC),
			(long)(timeElapsed % LMI_NSECS_PER_MSEC));
	}
#endif
}
LMI_INLINE void LmiConditionNotifyAll(LmiCondition* x) {
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	LmiTime timeBefore = LmiTimeGetCurrentMonotonicTime();
	LmiTime timeAfter, timeElapsed;
#endif
	LmiLogEnter(LmiLogMutex_);
	LmiLogDebugFormatted(LmiLogMutex_, "x=%p, waiterCount=%d", x, LmiConditionGetNumWaiting_(x));
	LmiConditionNotifyAll_(x);
	LmiLogLeave(LmiLogMutex_);
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	timeAfter = LmiTimeGetCurrentMonotonicTime();
	timeElapsed = timeAfter - timeBefore;
	if (timeElapsed > LMI_MUTEX_TIME_WARNING_THRESHOLD) {
		LmiLogWarningFormatted(LmiLogMutex_, "NotifyAll of condition %p took %lld.%06ld ms",
			x,
			(long long)(timeElapsed / LMI_NSECS_PER_MSEC),
			(long)(timeElapsed % LMI_NSECS_PER_MSEC));
	}
#endif
}

