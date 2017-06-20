/**
{file:
	{name: LmiMutexInline.h}
	{description: Inline functions for LmiMutex.}
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

/* POSIX */
#if defined(LMI_HAVE_PTHREAD_MUTEX_INIT)
LMI_INLINE LmiMutex* LmiMutexConstruct_(LmiMutex* x) {	
	LmiMutex* r = 0;
	pthread_mutexattr_t attr;

#if defined(__CYGWIN__)
	*x = 0; /* Avoids cygwin bug */
#endif

	if (pthread_mutexattr_init(&attr) == 0) {
		if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) == 0)
			if (pthread_mutex_init(x, &attr) == 0)
				r = x;
		pthread_mutexattr_destroy(&attr);
	}
	return r;
}
LMI_INLINE void LmiMutexDestruct_(LmiMutex* x) {
	pthread_mutex_destroy(x);
}
LMI_INLINE void LmiMutexLock_(LmiMutex* x) {
	pthread_mutex_lock(x);
}
LMI_INLINE void LmiMutexUnlock_(LmiMutex* x) {
	pthread_mutex_unlock(x);
}
/* Win32 */
#elif defined(LMI_HAVE_INITIALIZECRITICALSECTION) || defined(LMI_HAVE_INITIALIZECRITICALSECTIONEX)
#if defined(LMI_HAVE_INITIALIZECRITICALSECTION)
LMI_INLINE LmiMutex* LmiMutexConstruct_(LmiMutex* x) {
	InitializeCriticalSection(x);
	return x;
}
#else
LMI_INLINE LmiMutex* LmiMutexConstruct_(LmiMutex* x) {
	if (InitializeCriticalSectionEx(x, 0, 0) == 0)
		return NULL;
	return x;
}
#endif
LMI_INLINE void LmiMutexDestruct_(LmiMutex* x) {
	DeleteCriticalSection(x);
}
LMI_INLINE void LmiMutexLock_(LmiMutex* x) {
	EnterCriticalSection(x);
}
LMI_INLINE void LmiMutexUnlock_(LmiMutex* x) {
	LeaveCriticalSection(x);
}
#else
#error Unknown Mutex implementation
#endif

LMI_INLINE LmiMutex* LmiMutexConstruct(LmiMutex* x) {
	LmiMutex* r;
	LmiLogEnter(LmiLogMutex_);
	r = LmiMutexConstruct_(x);
	LmiLogLeave(LmiLogMutex_);
	return r;
}
LMI_INLINE void LmiMutexDestruct(LmiMutex* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiMutexDestruct_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE void LmiMutexLock(LmiMutex* x) {
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	LmiTime timeBefore = LmiTimeGetCurrentMonotonicTime();
	LmiTime timeAfter, timeElapsed;
#endif
	LmiLogEnter(LmiLogMutex_);
	LmiMutexLock_(x);
	LmiLogLeave(LmiLogMutex_);
#if defined(LMI_MUTEX_TIME_WARNING_THRESHOLD)
	timeAfter = LmiTimeGetCurrentMonotonicTime();
	timeElapsed = timeAfter - timeBefore;
	if (timeElapsed > LMI_MUTEX_TIME_WARNING_THRESHOLD) {
		LmiLogWarningFormatted(LmiLogMutex_, "Lock of mutex %p took %lld.%06ld ms",
			x,
			(long long)(timeElapsed / LMI_NSECS_PER_MSEC),
			(long)(timeElapsed % LMI_NSECS_PER_MSEC));
	}
#endif
}
LMI_INLINE void LmiMutexUnlock(LmiMutex* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiMutexUnlock_(x);
	LmiLogLeave(LmiLogMutex_);
}
