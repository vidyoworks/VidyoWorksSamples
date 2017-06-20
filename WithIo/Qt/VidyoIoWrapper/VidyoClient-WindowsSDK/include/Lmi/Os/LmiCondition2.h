/** {file:
      {name: LmiCondition2.h}
      {description: Objects to provide condition variables.}
      {copyright:
      	(c) 2006-2012 Vidyo, Inc.,
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
#ifndef LMI_CONDITION2_H_
#define LMI_CONDITION2_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiSemaphore.h>

LMI_BEGIN_EXTERN_C

/**
   {type visibility="private":
     {name: LmiCondition2}
     {parent: Os}
	 {include: Lmi/Os/LmiCondition2.h}
     {description:
       {p: An alternate implementation of condition variables.}
       {p: The condition variable semantics implemented by LmiCondition have
         several shortcomings.  Notably:
         {h\:ul xmlns\:h="http\://www.w3.org/1999/xhtml":
	   {h\:li: They use a special object LmiMonitor, not the usual LmiMutex
	     object.}
	   {h\:li: LmiConditionNotify[All] releases the monitor while notifying,
	     and all notified threads (and potentially other threads) run before
	     control returns to the notifier.}
	   {h\:li: A notifier is required to hold the monitor while notifying.}
	   {h\:li: During a NotifyAll, threads which start waiting while the
	     NotifyAll is in progress also get notified.  If a thread is looping
	     waiting on a condition variable, this can mean that the same thread
	     gets notified more than once for the same NotifyAll.  In an extreme
	     case, it\'s possible for NotifyAll to go into an infinite loop.}
	 }
	 As a result of this, the semantics of LmiCondition do not match those
	 of Posix\'s pthread_cond_t.}
       {p: LmiCondition2 is an alternate implementation of condition variables
         which do not have these shortcomings.  Its algorithms are based on
	 those of cygwin and of the pthreads-Win32 package, since those packages
	 also need to implement condition variables out of lower-level mutual
	 exclusion predicates.}
       {p: This implementation also has its shortcomings, however.  Notably:
         {h\:ul xmlns\:h="http\://www.w3.org/1999/xhtml":
	   {h\:li: LmiCondition2 objects are larger, and the functions manipulating
	     them are more heavyweight, than those of LmiCondition.}
	   {h\:li: LmiCondition2 uses counting semaphores, whereas LmiCondition
	     requires only binary semaphores.}
	   {h\:li: If a notifier holds the condition\'s controlling mutex, which
	     is the normal case, notified threads (if they are woken up before the
	     notifier releases the mutex) wake up on their semaphore, only to be
	     immediately put back to sleep when they try to acquire the mutex.}
	   {h\:li: Even though LmiMutex is defined as a recursive mutex type,
	     condition variables do not work usefully with recursively-locked
	     mutexes.}
	   {h\:li: The waiters_blocked counter is not always locked by the same
	     mutex when it is modified, and so needs to be guaranteed to be
	     modified atomically; this is not currently done.}
	 }
       }
       {p: We plan to do further performance and requirements evaluation in the
         future, as more of our system is built.}
     }
   }
*/

typedef struct {
  LmiInt waiters_blocked;	/* Number of threads waiting for the condition.  */
  LmiInt waiters_to_unblock;	/* Number of threads signalled but not yet woken */
                                /*   up.                                         */
  LmiSemaphore block_queue;	/* Queue up threads waiting for the condition to */
                                /*   become signalled.                           */
  LmiSemaphore block_lock;	/* Semaphore that guards access to               */
                                /*   waiters_blocked count and block_queue.      */
  LmiMutex unblock_lock;        /* Mutex that guards access to
				 *   waiters_to_unblock count. */
  LmiMutex* mutex;              /* Underlying mutex. */
} LmiCondition2;

/* Low-level (no logging) condition interface */
/* you should use the high-level condition interface unless you have a good reason
   to use the low level interface (such as the implementation of logging) */
LmiCondition2* LmiCondition2Construct_(LmiCondition2* x, LmiMutex* mutex);
void LmiCondition2Destruct_(LmiCondition2* x);
LMI_INLINE_DECLARATION LmiMutex* LmiCondition2GetMutex_(LmiCondition2* x);
LmiInt LmiCondition2GetNumWaiting_(LmiCondition2* x);
void LmiCondition2Wait_(LmiCondition2* x);
void LmiCondition2Notify_(LmiCondition2* x);
void LmiCondition2NotifyAll_(LmiCondition2* x);

/* High-level (with logging) condition interface */
LMI_INLINE_DECLARATION LmiCondition2* LmiCondition2Construct(LmiCondition2* x, LmiMutex* mutex);
LMI_INLINE_DECLARATION void LmiCondition2Destruct(LmiCondition2* x);
LMI_INLINE_DECLARATION LmiMutex* LmiCondition2GetMutex(LmiCondition2* x);
LMI_INLINE_DECLARATION LmiInt LmiCondition2GetNumWaiting(LmiCondition2* x);
LMI_INLINE_DECLARATION void LmiCondition2Wait(LmiCondition2* x);
LMI_INLINE_DECLARATION void LmiCondition2Notify(LmiCondition2* x);
LMI_INLINE_DECLARATION void LmiCondition2NotifyAll(LmiCondition2* x);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiCondition2Inline.h>
#endif

#endif /* LMI_CONDITION2_H_ */

