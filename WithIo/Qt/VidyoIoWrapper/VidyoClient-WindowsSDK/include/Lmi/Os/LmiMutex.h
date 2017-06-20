/**
{file:
    {name: LmiMutex.h}
    {description: Objects to provide (recursive) mutual exclusion.}
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
#ifndef LMI_MUTEX_H_
#define LMI_MUTEX_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiLog.h>
#include <Lmi/Os/LmiTime.h>

/* #define LMI_MUTEX_TIME_WARNING_THRESHOLD LMI_TIME_WARNING_THRESHOLD */

/**
{type visibility="private":
	{name: LmiMutex}
	{parent: Os}
	{include: Lmi/Os/LmiMutex.h}
	{description:
		A recursive mutex object.
	}
}
*/
#if defined(LMI_HAVE_PTHREAD_MUTEX_INIT)
#include <pthread.h>
typedef pthread_mutex_t LmiMutex;
#elif defined(LMI_HAVE_INITIALIZECRITICALSECTION) || defined(LMI_HAVE_INITIALIZECRITICALSECTIONEX)
#include <winsock2.h>
typedef CRITICAL_SECTION LmiMutex;
#else
#error Unknown Mutex implementation
#endif

LMI_BEGIN_EXTERN_C

/* Low-level (no logging) mutex interface */
/* you should use the high-level mutex interface unless you have a good reason
   to use the low level interface (such as the implementation of logging) */
LMI_INLINE_DECLARATION LmiMutex* LmiMutexConstruct_(LmiMutex* x);
LMI_INLINE_DECLARATION void LmiMutexDestruct_(LmiMutex* x);
LMI_INLINE_DECLARATION void LmiMutexLock_(LmiMutex* x);
LMI_INLINE_DECLARATION void LmiMutexUnlock_(LmiMutex* x);

/* High-level (with logging) mutex interface */
extern LmiLogCategory LmiLogMutex_;

/**
{function visibility="private":
	{name: LmiMutexConstruct}
	{parent: LmiMutex}
	{description:
		{p: Construct a recursive mutex object.}
	}
	{prototype: LmiMutex* LmiMutexConstruct(LmiMutex* x)}
	{parameter:
		{name: x}
		{description: A pointer to the mutex object to construct.}
	}
	{return: A pointer to the mutex object, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiMutex* LmiMutexConstruct(LmiMutex* x);

/**
{function visibility="private":
	{name: LmiMutexDestruct}
	{parent: LmiMutex}
	{description:
		{p: Destruct a recursive mutex object.}
	}
	{prototype: void LmiMutexDestruct(LmiMutex* x)}
	{parameter:
		{name: x}
		{description: A pointer to the mutex object to destruct.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiMutexDestruct(LmiMutex* x);

/**
{function visibility="private":
	{name: LmiMutexLock}
	{parent: LmiMutex}
	{description:
		{p: Lock a recursive mutex object.}
	}
	{prototype: void LmiMutexLock(LmiMutex* x)}
	{parameter:
		{name: x}
		{description: A pointer to the mutex object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiMutexLock(LmiMutex* x);

/**
{function visibility="private":
	{name: LmiMutexUnlock}
	{parent: LmiMutex}
	{description:
		{p: Unlock a recursive mutex object.}
	}
	{prototype: void LmiMutexUnlock(LmiMutex* x)}
	{parameter:
		{name: x}
		{description: A pointer to the mutex object.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiMutexUnlock(LmiMutex* x);

/* Initialize LmiMutex, specifically its logs. */
LmiBool LmiMutexInitialize(void);

/* Debugging interfaces to LmiMutex, that do verbose logging */
void LmiMutexLockDebug_(LmiMutex* x, LmiUint stackDepth);
void LmiMutexUnlockDebug_(LmiMutex* x, LmiUint stackDepth);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiMutexInline.h>
#endif

#endif /* LMI_MUTEX_H_ */
