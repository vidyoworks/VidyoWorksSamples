/**
{file:
	{name: LmiRwLock.h}
 	{description: A reader/writer lock class interface.}
	{copyright:
 		(c) 2012-2014 Vidyo, Inc.,
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

#ifndef LMI_RWLOCK_H_
#define LMI_RWLOCK_H_

#include <Lmi/Utils/LmiTypes.h>

#if defined(LMI_HAVE_PTHREAD_RWLOCK_INIT)
#define LMI_USE_PTHREAD_RWLOCK 1
#elif (LMI_HAVE_INITIALIZESRWLOCK) 
/* Windows.  Windows SRWLock was added in Vista. */
#define LMI_USE_VISTA_RWLOCK 1
#else
#define LMI_USE_GENERIC_RWLOCK 1
#define LMI_NEED_GENERIC_RWLOCK 1
#endif


LMI_BEGIN_EXTERN_C

/**
{type visibility="private": 
	{name: LmiRwLock}
	{parent: Os}
	{include: Lmi/Os/LmiRwLock.h}
	{description: 
		{p: A reader/writer lock.  A reader/writer lock allows either a single writer or multiple readers access to a resource the lock is guarding.} 
		{p: The implementation makes no guarantees with regard to the order it grants access to readers and writers. So requests for writing may or may not take precedence over requests for reading, etc.}
		{p: A given thread can lock a reader/writer lock for reading multiples times.  While this might give the appearance of recursive support, in fact this is simply the reader/writer locks natural behavior that allows multiple readers (regardless of which thread) to access a resource. A given thread may not lock a reader/writer lock for writing multiples times.  In other words writer locks are not recursive. Also, a thread holding a reader lock on a reader/writer lock, may not attempt to lock that reader/writer lock for writing or vice versa.}
	}
}
*/
#if defined(LMI_NEED_GENERIC_RWLOCK)

#include <Lmi/Os/LmiMonitor.h>
#include <Lmi/Os/LmiCondition.h>

typedef struct {
	LmiSemaphore m;
	LmiSemaphore w;
	LmiUint readerCount;
} LmiRwLock_Generic_;

#endif

#if defined(LMI_USE_PTHREAD_RWLOCK)
#include <pthread.h>

typedef pthread_rwlock_t LmiRwLock;

#elif defined(LMI_USE_VISTA_RWLOCK)
#include <winsock2.h>

typedef SRWLOCK LmiRwLock;

#elif defined(LMI_USE_GENERIC_RWLOCK)
typedef LmiRwLock_Generic_ LmiRwLock;

#endif


/**
{function visibility="private":
	{name: LmiRwLockConstruct}
	{parent: LmiRwLock}
	{description: Constructs a reader/writer lock.}
	{prototype: LmiRwLock* LmiRwLockConstruct(LmiRwLock* x)}
	{parameter: {name: x}{description: A pointer to the reader/writer lock to construct.}}
	{return: A pointer to the newly constructed reader/writer lock or NULL on error.}
}
*/
LmiRwLock* LmiRwLockConstruct(LmiRwLock* x);
/**
{function visibility="private":
	{name: LmiRwLockDestruct}
	{parent: LmiRwLock}
	{description: Destructs a reader/writer lock.}
	{prototype: void LmiRwLockDestruct(LmiRwLock* x)}
	{parameter: {name: x}{description: A pointer to the reader/writer lock to destruct.}}
}
*/
void LmiRwLockDestruct(LmiRwLock* x);

/**
{function visibility="private":
	{name: LmiRwLockReadLock}
	{parent: LmiRwLock}
	{description: Lock a reader/writer lock for non-exclusive reading.}
	{prototype: void LmiRwLockReadLock(LmiRwLock* x)}
	{parameter: {name: x}{description: A pointer to the reader/writer lock.}}
}
*/
void LmiRwLockReadLock(LmiRwLock* x);

/**
{function visibility="private":
	{name: LmiRwLockWriteLock}
	{parent: LmiRwLock}
	{description: Lock a reader/writer lock for exclusive writing.}
	{prototype: void LmiRwLockWriteLock(LmiRwLock* x)}
	{parameter: {name: x}{description: A pointer to the reader/writer lock.}}
}
*/
void LmiRwLockWriteLock(LmiRwLock* x);

/**
{function visibility="private":
	{name: LmiRwLockReadUnlock}
	{parent: LmiRwLock}
	{description: Unlock a read lock.}
	{prototype: void LmiRwLockReadUnlock(LmiRwLock* x)}
	{parameter: {name: x}{description: A pointer to the reader/writer lock.}}
}
*/
void LmiRwLockReadUnlock(LmiRwLock* x);

/**
{function visibility="private":
	{name: LmiRwLockWriteUnlock}
	{parent: LmiRwLock}
	{description: Unlock a write lock.}
	{prototype: void LmiRwLockWriteUnlock(LmiRwLock* x)}
	{parameter: {name: x}{description: A pointer to the reader/writer lock.}}
}
*/
void LmiRwLockWriteUnlock(LmiRwLock* x);

LMI_END_EXTERN_C

#endif

