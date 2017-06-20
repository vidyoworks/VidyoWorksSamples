/** {file:
	  {name: LmiTimerLoop.h}
	  {description: Core loop for executing timers.}
	  {copyright:
	  	(c) 2009-2015 Vidyo, Inc.,
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
#ifndef LMI_TIMER_LOOP_H_
#define LMI_TIMER_LOOP_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiTimer.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiThread.h>
#include <Lmi/Os/LmiInterruptableSleeper.h>


LMI_BEGIN_EXTERN_C

/* Internal */
typedef enum {
	LMI_TIMER_LOOP_THREAD_STARTING_,
	LMI_TIMER_LOOP_THREAD_RUNNING_,
	LMI_TIMER_LOOP_THREAD_STOPPING_,
	LMI_TIMER_LOOP_THREAD_STOPPED_
} LmiTimerLoopThreadState_;
  

typedef struct {
	LmiMutex mutex;
	struct LmiTimerLoop_* tl;
	LmiInterruptableSleeper sleeper;
	LmiThread thread;
	LmiTimerLoopThreadState_ state;
	LmiSizeT idx;
	LmiUint64 sleepCount;
} LmiTimerLoopThread_;

/**
   {type:
     {name: LmiTimerLoop}
	 {parent: Os}
	 {include: Lmi/Os/LmiTimerLoop.h}
	 {description: This object creates a thread that executes an
	 LmiTimerManager as needed.}
   }
*/
typedef struct LmiTimerLoop_ {
	LmiTimerManager tm;
	LmiTimerLoopThread_* threads;
	LmiSizeT numThreads;
} LmiTimerLoop;


/**
   {function:
     {name: LmiTimerLoopConstruct}
	 {parent: LmiTimerLoop}
	 {description: Construct an LmiTimerLoop object.}
	 {prototype: LmiTimerLoop* LmiTimerLoopConstruct(LmiTimerLoop* tl, const char *name, LmiThreadPriority priority, LmiSizeT numThreads, LmiAllocator* alloc)}
	 {parameter:
	   {name: tl}
	   {description: The LmiTimerLoop object to construct.}}
	 {parameter:
	   {name: name}
	   {description: Application given name (no more than 31-[max number of digits in thread num] chars long) for the timer threads.}}
	 {parameter:
	   {name: priority}
	   {description: The priority to use for the LmiTimerLoop threads.}}
	 {parameter:
	   {name: numThreads}
	   {description: The number of timer threads to start.}}
	 {parameter:
	   {name: alloc}
	   {description: The allocator to use.}}
	 {return: tl on success, NULL on failure.}
   }
*/
LmiTimerLoop* LmiTimerLoopConstruct(LmiTimerLoop* tl, const char *name, LmiThreadPriority priority, LmiSizeT numThreads, LmiAllocator* alloc);


/**
   {function:
     {name: LmiTimerLoopDestruct}
	 {parent: LmiTimerLoop}
	 {description: Destruct an LmiTimerLoop object.}
	 {prototype: void LmiTimerLoopDestruct(LmiTimerLoop* tl)}
	 {parameter:
	   {name: tl}
	   {description: The LmiTimerLoop object to destruct.}}
   }
*/
void LmiTimerLoopDestruct(LmiTimerLoop* tl);

/**
{function:
	{name: LmiTimerLoopGetTimerManager}
	{parent: LmiTimerLoop}
	{description: Get the timer manager created by the LmiTimerLoop object.}
	{prototype: LmiTimerManager* LmiTimerLoopGetTimerManager(LmiTimerLoop* tl)}
	{parameter: {name: tl} {description: The LmiTimerLoop object.}}
	{return: The timer manager object.}
	{note: The LmiTimerLoop object sets the timer manager\'s first
		expiry callback. If any other code subsequently resets the timer manager\'s callback
		to something else, the LmiTimerLoop will misbehave.}
}
*/
LmiTimerManager *LmiTimerLoopGetTimerManager(LmiTimerLoop *tl);

/**
   {function:
     {name: LmiTimerLoopStop}
	 {parent: LmiTimerLoop}
	 {description: Stop an LmiTimerLoop object.  This causes
	   all the LmiTimerLoop threads to exit.}
	 {prototype: void LmiTimerLoopStop(LmiTimerLoop* tl)}
	 {parameter:
	   {name: tl}
	   {description: The LmiTimerLoop to stop.}}
   }
*/
void LmiTimerLoopStop(LmiTimerLoop *tl);

/**
   {function:
     {name: LmiTimerLoopGetSleepCount}
	 {parent: LmiTimerLoop}
	 {description: Get the number of times the timer loop has slept,
	   since it was started.}
	 {prototype: LmiUint64 LmiTimerLoopGetSleepCount(LmiTimerLoop* tl)}
	 {parameter:
	   {name: tl}
	   {description: The LmiTimerLoop whose sleep count to get.}}
	 {return: The number of times the timer loop has slept, since it was started.}
	 {note: This number is an aggregation across all the timer loop's threads.}
   }
*/
LmiUint64 LmiTimerLoopGetSleepCount(LmiTimerLoop* se);


LMI_END_EXTERN_C

#endif /* LMI_TIMER_LOOP_H_ */
