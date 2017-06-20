/** {file:
      {name: LmiInterruptableSleeper.h}
      {description: Objects to provide an interruptable wait.}
      {copyright:
      	(c) 2009-2014 Vidyo, Inc.,
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
#ifndef LMI_INTERRUPTABLE_SLEEPER_H_
#define LMI_INTERRUPTABLE_SLEEPER_H_

/**
{type visibility="private":
	{name: LmiInterruptableSleeper}
	{parent: Os}
	{include: Lmi/Os/LmiInterruptableSleeper.h}
	{description: An object which provides the ability for a thread to sleep
		for a period of time, while allowing other threads to wake the
		thread up early.}
}
*/

#include <Lmi/Os/LmiTime.h>
#include <Lmi/Os/LmiMutex.h>

LMI_BEGIN_EXTERN_C

#if defined(LMI_HAVE_PTHREAD_COND_TIMEDWAIT)

#define LMI_INTERRUPTABLE_SLEEPER_USE_PTHREAD_COND_TIMEDWAIT_ 1

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	LmiBool woken;
} LmiInterruptableSleeper;

#elif defined(LMI_HAVE_CREATESEMAPHORE) || defined(LMI_HAVE_CREATESEMAPHOREEX)
#include <winsock2.h>

typedef HANDLE LmiInterruptableSleeper;

#else

/* TODO: WaitForSingleObject on Windows. */

#endif

/**
	{function visibility="private":
		{name: LmiInterruptableSleeperConstruct}
		{parent: LmiInterruptableSleeper}
		{description: Construct an interruptable sleeper object.}
		{prototype: LmiInterruptableSleeper* LmiInterruptableSleeperConstruct(LmiInterruptableSleeper* s)}
		{parameter:
			{name: s}
			{description: The object to construct.}}
		{return: The object on success, NULL on failure.}
	}
*/
LmiInterruptableSleeper* LmiInterruptableSleeperConstruct(LmiInterruptableSleeper* s);


/**
	{function visibility="private":
		{name: LmiInterruptableSleeperDestruct}
		{parent: LmiInterruptableSleeper}
		{description: Destruct an interruptable sleeper object.}
		{prototype: void LmiInterruptableSleeperDestruct(LmiInterruptableSleeper* s)}
		{parameter:
			{name: s}
			{description: The object to destruct.}}
	}
*/
void LmiInterruptableSleeperDestruct(LmiInterruptableSleeper* s);


/**
	{function visibility="private":
		{name: LmiInterruptableSleeperSleep}
		{parent: LmiInterruptableSleeper}
		{description: Cause a thread to sleep for some duration of time, while allowing other threads to wake the thread early if necessary.}
		{prototype: LmiBool LmiInterruptableSleeperSleep(LmiInterruptableSleeper* s, LmiTime interval)}
		{parameter:
			{name: s}
			{description: The object to use to sleep.}}
		{parameter:
			{name: interval}
			{description: The duration of time to sleep.}}
		{return: LMI_TRUE if the sleep was interrupted, LMI_FALSE 
			if the sleep appears to have completed without interruption.}
		{note: Only one thread at a time is allowed call LmiInterruptableSleeperSleep or LmiInterruptableSleeperSleepUntil on a given LmiInterruptableSleeper.}
	}
*/
LmiBool LmiInterruptableSleeperSleep(LmiInterruptableSleeper* s, LmiTime interval);


/**
	{function visibility="private":
		{name: LmiInterruptableSleeperSleepUntil}
		{parent: LmiInterruptableSleeper}
		{description: Cause a thread to sleep until a specified monotonic time, while allowing other threads to wake the thread early if necessary.}
		{prototype: LmiBool LmiInterruptableSleeperSleepUntil(LmiInterruptableSleeper* s, LmiTime wakeTime)}
		{parameter:
			{name: s}
			{description: The object to use to sleep.}}
		{parameter:
			{name: wakeTime}
			{description: The monotonic time until which to sleep.}}
		{return: LMI_TRUE if the sleep was interrupted, LMI_FALSE 
			if the sleep appears to have completed without interruption.}
		{note: Only one thread at a time is allowed call LmiInterruptableSleeperSleep or LmiInterruptableSleeperSleepUntil on a given LmiInterruptableSleeper.}
	}
*/
LmiBool LmiInterruptableSleeperSleepUntil(LmiInterruptableSleeper* s, LmiTime wakeTime);


/**
	{function visibility="private":
		{name: LmiInterruptableSleeperWake}
		{parent: LmiInterruptableSleeper}
		{description: Wake up another thread that is sleeping on an interruptable sleeper.}
		{prototype: LmiBool LmiInterruptableSleeperWake(LmiInterruptableSleeper* s)}
		{parameter:
			{name: s}
			{description: The LmiInterruptableSleeper to wake.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiInterruptableSleeperWake(LmiInterruptableSleeper* s);



LMI_END_EXTERN_C

#endif /* LMI_INTERRUPTABLE_SLEEPER_H_ */

