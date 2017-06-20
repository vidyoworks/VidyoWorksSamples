/**
   {file:
     {name: LmiSemaphoreInline.h}
     {description: Inline functions for LmiSemaphore.}
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
#include <Lmi/Os/LmiMutex.h>

/* Mach */
#if defined(LMI_HAVE_SEMAPHORE_CREATE)
LMI_INLINE LmiSemaphore* LmiSemaphoreConstruct_(LmiSemaphore* x, LmiUint initialCount) {
	x->task = mach_task_self();
	if (semaphore_create(x->task, &x->sem, 0, (int)initialCount) != KERN_SUCCESS)
		return 0;
	return x;
}
LMI_INLINE void LmiSemaphoreDestruct_(LmiSemaphore* x) {
	kern_return_t ret = semaphore_destroy(x->task, x->sem);
	LmiAssert(ret == KERN_SUCCESS);
}
LMI_INLINE void LmiSemaphoreAcquire_(LmiSemaphore* x) {
	kern_return_t ret;
	while ((ret = semaphore_wait(x->sem)) == KERN_ABORTED)
		;
	LmiAssert(ret == KERN_SUCCESS);
}
LMI_INLINE void LmiSemaphoreRelease_(LmiSemaphore* x) {
	kern_return_t ret = semaphore_signal(x->sem);
	LmiAssert(ret == KERN_SUCCESS);
}
/* POSIX */
#elif defined(LMI_HAVE_SEM_INIT)
LMI_INLINE LmiSemaphore* LmiSemaphoreConstruct_(LmiSemaphore* x, LmiUint initialCount) {
	if (sem_init(x, 0, (unsigned int)initialCount) != 0)
		return 0;
	return x;
}
LMI_INLINE void LmiSemaphoreDestruct_(LmiSemaphore* x) {
	sem_destroy(x);
}
LMI_INLINE void LmiSemaphoreAcquire_(LmiSemaphore* x) {
	int ret;
	while (((ret = sem_wait(x)) != 0) && (errno == EINTR))
		;
	LmiAssert(ret == 0);
}
LMI_INLINE void LmiSemaphoreRelease_(LmiSemaphore* x) {
	int ret;
	ret = sem_post(x);
	LmiAssert(ret == 0);
}
/* Win32 */
#elif defined(LMI_HAVE_CREATESEMAPHORE)
LMI_INLINE LmiSemaphore* LmiSemaphoreConstruct_(LmiSemaphore* x, LmiUint initialCount) {
	if ((*x = CreateSemaphore(NULL, (LONG)initialCount, 32 * 1024, NULL)) == NULL)
		return 0;
	return x;
}
LMI_INLINE void LmiSemaphoreDestruct_(LmiSemaphore* x) {
	CloseHandle(*x);
}
LMI_INLINE void LmiSemaphoreAcquire_(LmiSemaphore* x) {
	WaitForSingleObject(*x, INFINITE);
}
LMI_INLINE void LmiSemaphoreRelease_(LmiSemaphore* x) {
	BOOL ret;
	ret = ReleaseSemaphore(*x, 1, NULL); 
	LmiAssert(ret);
}
#elif defined(LMI_HAVE_CREATESEMAPHOREEX)
LMI_INLINE LmiSemaphore* LmiSemaphoreConstruct_(LmiSemaphore* x, LmiUint initialCount) {
	if ((*x = CreateSemaphoreExW(NULL, (LONG)initialCount, 32 * 1024, NULL, 0, SEMAPHORE_ALL_ACCESS)) == NULL)
		return 0;
	return x;
}
LMI_INLINE void LmiSemaphoreDestruct_(LmiSemaphore* x) {
	CloseHandle(*x);
}
LMI_INLINE void LmiSemaphoreAcquire_(LmiSemaphore* x) {
	WaitForSingleObjectEx(*x, INFINITE, FALSE);
}
LMI_INLINE void LmiSemaphoreRelease_(LmiSemaphore* x) {
	BOOL ret;
	DWORD error;
	ret = ReleaseSemaphore(*x, 1, NULL); 
	if (!ret) {
		error = GetLastError();
	}
	LmiAssert(ret);
}

#elif defined (LMI_HAVE_TI_CREATESEMAPHORE)

LMI_INLINE LmiSemaphore* LmiSemaphoreConstruct_(LmiSemaphore* x, LmiUint initialCount) {

	return x;
}
LMI_INLINE void LmiSemaphoreDestruct_(LmiSemaphore* x) {

}
LMI_INLINE void LmiSemaphoreAcquire_(LmiSemaphore* x) {

	/*	LmiAssert(ret == KERN_SUCCESS); */
}
LMI_INLINE void LmiSemaphoreRelease_(LmiSemaphore* x) {

}

#else
#error Unknown Semaphore implementation
#endif


LMI_INLINE LmiSemaphore* LmiSemaphoreConstruct(LmiSemaphore* x, LmiUint initialCount) {
	LmiSemaphore* r;

	LmiLogEnter(LmiLogMutex_);
	r = LmiSemaphoreConstruct_(x, initialCount);
	LmiLogLeave(LmiLogMutex_);
	return r;
}
LMI_INLINE void LmiSemaphoreDestruct(LmiSemaphore* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiSemaphoreDestruct_(x);
	LmiLogLeave(LmiLogMutex_);
}

LMI_INLINE void LmiSemaphoreAcquire(LmiSemaphore* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiSemaphoreAcquire_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE void LmiSemaphoreRelease(LmiSemaphore* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiSemaphoreRelease_(x);
	LmiLogLeave(LmiLogMutex_);
}
