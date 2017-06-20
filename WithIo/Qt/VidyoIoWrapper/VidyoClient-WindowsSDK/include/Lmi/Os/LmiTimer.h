/** {file:
      {name: LmiTimer.h}
      {description: Functionality to support Timers.}
      {copyright:
      	(c) 2006-2015 Vidyo, Inc.,
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

#ifndef LMI_TIMER_H_
#define LMI_TIMER_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiHeap.h>
#include <Lmi/Os/LmiCondition.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiTime.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Os/LmiThread.h>


LMI_BEGIN_EXTERN_C


/**
   {function visibility="private":
     {name: LmiTimerManagerInitialize}
	 {parent: LmiTimerManager}
	 {description: Initialize the timer manager package.}
	 {prototype: LmiBool LmiTimerManagerInitialize(void)}
	 {return: LMI_TRUE on success, LMI_FALSE on failure.}
   }
*/
LmiBool LmiTimerManagerInitialize(void);


/**
   {function visibility="private":
     {name: LmiTimerManagerUninitialize}
	 {parent: LmiTimerManager}
	 {description: Uninitialize the timer manager package.}
	 {prototype: void LmiTimerManagerUninitialize(void)}
   }
*/
void LmiTimerManagerUninitialize(void);

typedef enum {
	LMI_TIMER_INVALID = 0,
	LMI_TIMER_CONSTRUCTED = 1, 
	LMI_TIMER_STARTED,
	LMI_TIMER_STOPPED,
} LmiTimerStatus;

typedef enum {
	LMI_TIMER_STATE_INIT,		/* Default State of a Timer Block not in use */
	LMI_TIMER_STATE_ALIVE,		/* Timer scheduled for expiry at a later time */
	LMI_TIMER_STATE_RUNNING		/* Timer expired and is currently executing the expiry callback */
} LmiTimerState;

/* Forward Declaration */
struct LmiTimer_;
struct LmiTimerManagerThread_;
struct LmiTimerManager_;

/**
   {callback visibility="private":
     {name: LmiTimerExpiryCallback}
     {parent: LmiTimer}
     {description: This is the callback function invoked on timer expiry.}
     {prototype: void (*LmiTimerExpiryCallback)(LmiTimer* timer, LmiVoidPtr userData)}
     {parameter:
       {name: timer}
       {description: A pointer to LmiTimer struct}}
     {parameter:
	   {name: userData}
       {description: pointer to user data}}
   }
*/
typedef void (*LmiTimerExpiryCallback)(struct LmiTimer_ *, LmiVoidPtr);

/* LmiTimerBlock -- Allocated by Timer Manager */
typedef struct LmiTimerBlock_ {
	LmiSizeT			heapIndex;
	LmiTime				absoluteExpiryTime;
	LmiTimerState		timerState;
	struct LmiTimer_	*timer;
} LmiTimerBlock, *LmiTimerBlockPtr;
	
/**
	{type visibility="private":
		{name: LmiTimer}
		{parent: LmiTimerManager}
		{description: 
			A timer used to schedule work sometime in the future. 
		}
	}
*/


/* LmiTimer -- Allocated by User before LmiTimerStart */
typedef struct LmiTimer_ {
	LmiTimerExpiryCallback	expiryCallback;	/* User supplied Callback routine */
	LmiVoidPtr				userData;		/* Pointer to User Data */

	struct LmiTimerManagerThread_	*tmt;	/* Pointer to Timer Manager Thread */
	LmiSizeT				stoppingCount;	/* Threads calling stop. */
	LmiTimerStatus          status;
	/* The following are allocated and used by Timer Manager */
	LmiTimerBlock			*timerBlock;	/* Pointer to internal Timer Block structure */
	LmiTimerBlock			*otherBlock;	/* Pointer to internal Timer Block structure */
} LmiTimer;


LmiBool LmiTimerBlockPtrSwap(LmiTimerBlockPtr *x, LmiTimerBlockPtr *y);
LmiBool LmiTimerBlockPtrLess(const LmiTimerBlockPtr *x, const LmiTimerBlockPtr *y);
LmiTimerBlockPtr* LmiTimerBlockPtrConstructCopy(LmiTimerBlockPtr *a, const LmiTimerBlockPtr *b);
LmiTimerBlockPtr* LmiTimerBlockPtrAssign(LmiTimerBlockPtr *a, const LmiTimerBlockPtr *b);
LmiBool LmiTimerBlockPtrEqual(const LmiTimerBlockPtr *a, const LmiTimerBlockPtr *b);
void LmiTimerBlockPtrDestruct(LmiTimerBlockPtr *a);
void LmiTimerBlockPtrDump(LmiTimerBlockPtr * entry);


Declare_LmiHeap(LmiTimerBlockPtr)

/**
   {callback visibility="public":
     {name: LmiTimerManagerNotifyFirstExpiryCallback}
     {parent: LmiTimerManager}
     {description: This callback is invoked whenever a new timer started will also be the first to expire.}
     {prototype: void (*LmiTimerManagerNotifyFirstExpiryCallback)(LmiTimerManager* timerManager, LmiVoidPtr userData, LmiTime time)}
     {parameter:
       {name: timerManager}
       {description: A pointer to LmiTimerManager struct}}
     {parameter:
	   {name: userData}
       {description: pointer to user data}}
     {parameter:
	   {name: time}
       {description: next monotonic expiry time}}
   }
*/
typedef void (*LmiTimerManagerNotifyFirstExpiryCallback)(struct LmiTimerManager_ *, LmiVoidPtr, LmiTime);

typedef struct LmiTimerManagerThread_ {
	struct LmiTimerManager_ *tm;                /* Parent timer manager */
	LmiSizeT threadId;							/* This thread's instance id. */
	LmiHeap(LmiTimerBlockPtr) timerBlockHeap;	/* Timer block heap */
	LmiMonitor monitor;							/* Monitor */
	LmiVoidPtr uData;							/* user data to be passed in First expiry call back */
	LmiTimerManagerNotifyFirstExpiryCallback notifyFn; /* call back for earliest expiry */
	LmiCondition		condition;				/* Condition Variable used while in call back processing */
	LmiThreadId	mainThreadId;					/* Thread invoking the LmiTimerManagerExecute; valid if executing == LMI_TRUE */
	LmiTime lastExpiry;                         /* Last expiry time returned from LmiTimerManagerExecute. */
	LmiTime lastNotify;                         /* Last notification time notified by notifyFn. */
	LmiBool executing;							/* True if we're currently in LmiTimerManagerExecute */
} LmiTimerManagerThread;


/**
	{type visibility="public":
		{name: LmiTimerManager}
		{parent: Os}
		{include: Lmi/Os/LmiTimer.h}
		{description: 
			A timer scheduler. 
		}
	}
*/

/* LmiTimerManager -- Created by User before any timer calls */
typedef struct LmiTimerManager_ {
	LmiAllocator * alloc;						/* Allocator */
	LmiTimerManagerThread* threads;				/* Set of timer manager threads. */
	LmiSizeT threadCount;
	LmiSizeT nextThreadAlloc;
	LmiMutex mutex;
} LmiTimerManager;



/**
   {function visibility="private":
     {name: LmiTimerConstruct}
     {parent: LmiTimer}
     {description: Constructs a timer.}
     {prototype: LmiTimer* LmiTimerConstruct(LmiTimer* x, LmiTimerExpiryCallback cb, LmiVoidPtr uData, LmiTimerManager* tm)}
     {parameter:
       {name: x}
       {description: A pointer to the timer to construct.}}       
     {parameter:
	   {name: cb}
       {description: The callback function invoked upon timer expiry.}}
     {parameter:
	   {name: uData}
       {description: A pointer to user data (may be NULL).}}
     {parameter:
	   {name: tm}
       {description: A pointer to timer manager to use for scheduling the timer.}}
	 {return: A pointer to the constructed object or NULL on failure.}
   }
*/
LmiTimer* LmiTimerConstruct(LmiTimer* x, LmiTimerExpiryCallback cb, LmiVoidPtr uData, LmiTimerManager* tm);

/**
   {function visibility="private":
     {name: LmiTimerDestruct}
     {parent: LmiTimer}
     {description: Destructs a timer.  If the timer has been started it is stopped.}
     {prototype: void LmiTimerDestruct(LmiTimer* x)}
     {parameter:
       {name: x}
       {description: A pointer to the timer to destruct.}}
   }
*/
void LmiTimerDestruct(LmiTimer* x);
/**
   {function visibility="private":
     {name: LmiTimerStart}
     {parent: LmiTimer}
     {description: Starts a timer.}
     {prototype: LmiBool LmiTimerStart(LmiTimer* timer, LmiTime expiryTime)}
     {parameter:
       {name: timer}
       {description: A pointer to the timer to start.}}
     {parameter:
	   {name: expiryTime}
       {description: relative expiry time in nanoseconds}}
     {return: LMI_TRUE or success or LMI_FALSE otherwise.}
   }
*/
LmiBool LmiTimerStart(LmiTimer* timer, LmiTime expiryTime);

/**
   {function visibility="private":
     {name: LmiTimerStartAbsolute}
     {parent: LmiTimer}
     {description: Start a timer.}
     {prototype: LmiBool LmiTimerStartAbsolute(LmiTimer* timer, LmiTime expiryTime)}
     {parameter:
       {name: timer}
       {description: A pointer to the timer to start.}}
     {parameter:
	   {name: expiryTime}
       {description: absolute expiry time in nanoseconds}}
	 {return: LMI_TRUE or success or LMI_FALSE otherwise.}
   }
*/
LmiBool LmiTimerStartAbsolute(LmiTimer* timer, LmiTime expiryTime);

/**
   {function visibility="private":
     {name: LmiTimerStop}
     {parent: LmiTimer}
     {description: Stops a timer.  If the timer's expiry callback is already in progress, 
	   LmiTimerStop blocks until the callback completes.}
     {prototype: LmiBool LmiTimerStop(LmiTimer* timer)}
     {parameter:
       {name: timer}
       {description: A pointer to the timer to stop.}}
     {return: LMI_TRUE if the timer is stopped successfully. 
		LMI_FALSE if LmiTimerStop was called from within the timer expiry callback.}
   }
*/
LmiBool LmiTimerStop(LmiTimer* timer);

/**
   {function visibility="private":
     {name: LmiTimerReset}
     {parent: LmiTimer}
	 {description: Reset a timer.  If the timer's expiry callback is already in progress, 
	   LmiTimerReset blocks until the callback completes before restarting the timer.}
     {prototype: LmiBool LmiTimerReset(LmiTimer* timer, LmiTime expiryTime, LmiTimerExpiryCallback cb)}
     {parameter:
       {name: timer}
       {description: A pointer to the timer to reset.}}       
     {parameter:
	   {name: expiryTime}
       {description: A relative expiry time in nanoseconds.}}
     {parameter:
	   {name: cb}
		{description: The callback function invoked upon timer expiry, if set to NULL, the previous callback will be used.}}
     {return: LMI_TRUE if the timer is successfully reset, 
		 LMI_FALSE if the timer could not be reset or if reset was called while the timer is being stopped.}
	}
*/
LmiBool LmiTimerReset(LmiTimer* timer, LmiTime expiryTime, LmiTimerExpiryCallback cb);

/**
   {function visibility="private":
     {name: LmiTimerResetAbsolute}
     {parent: LmiTimer}
     {description: Reset a timer to an absolute time.  If the timer's expiry callback is already in progress, 
	   LmiTimerResetAbsolute blocks until the callback completes before restarting the timer.}
     {prototype: LmiBool LmiTimerResetAbsolute(LmiTimer* timer, LmiTime expiryTime, LmiTimerExpiryCallback cb)}
     {parameter:
       {name: timer}
       {description: A pointer to the timer to reset.}}
     {parameter:
	   {name: expiryTime}
       {description: An absolute expiry time in nanoseconds.}}
     {parameter:
	   {name: cb}
		{description: The callback function invoked upon timer expiry, if set to NULL, the previous callback will be used.}}
     {return: LMI_TRUE if the timer is successfully reset, 
		 LMI_FALSE if the timer could not be reset or if reset was called while the timer is being stopped.}
	}
*/
LmiBool LmiTimerResetAbsolute(LmiTimer* timer, LmiTime expiryTime, LmiTimerExpiryCallback cb);


/**
   {function visibility="private":
     {name: LmiTimerPending}
     {parent: LmiTimer}
     {description: Queries a timer object to see if its execution is pending.}
     {prototype: LmiBool LmiTimerPending(const LmiTimer* timer)}
     {parameter:
       {name: timer}
       {description: A pointer to the timer to query.}}
     {return: LMI_TRUE if execution is pending for the timer, LMI_FALSE otherwise.}
	 {note: If a timer is being reset or stopped, this may return false even though the timer event
	   the timer previously referred to has not yet completed.}
	}
*/
LmiBool LmiTimerPending(const LmiTimer* timer);

/**
{function visibility="private":
	{name: LmiTimerIsInTimerCallback}
	{parent: LmiTimer}
	{description: Queries a timer object to see if we are executing within a timer callback. Make sure to call this only if the timer is pending.}
	{prototype: LmiBool LmiTimerIsInTimerCallback(LmiTimer* timer)}
	{parameter: 
		{name: timer}
		{description: A pointer to the timer to query}
	}
	{return: LMI_TRUE if we are in a callback, LMI_FALSE otherwise.}
}
*/
LmiBool LmiTimerIsInTimerCallback(LmiTimer* timer);

/**
   {function visibility="public":
     {name: LmiTimerManagerConstruct}
     {parent: LmiTimerManager}
     {description: Constructs a timer manager.}
     {prototype: LmiTimerManager* LmiTimerManagerConstruct(LmiTimerManager* tm, LmiSizeT numberTimers, LmiSizeT numberTimerThreads, LmiAllocator* a)}
     {parameter:
       {name: tm}
       {description: A pointer to the timer manager to construct.}}       
     {parameter:
	   {name: numberTimers}
       {description: A hint to the number of timers the timer manager is to manage.  If the number of timers exceeds this value
	     the timer manager will grow to meet the demand, but may incur some administrative overhead.}}
     {parameter:
	   {name: numberTimerThreads}
       {description: The number of distinct timer threads the timer manager is to manage.}}
     {parameter:
	   {name: a}
       {description: pointer to the timer manager's allocator.}}
     {return: A pointer to the constructed object or NULL on failure.}
   }
*/
LmiTimerManager* LmiTimerManagerConstruct(LmiTimerManager* tm, LmiSizeT numberTimers, LmiSizeT numberTimerThreads, LmiAllocator* a);

/**
   {function visibility="public":
     {name: LmiTimerManagerDestruct}
     {parent: LmiTimerManager}
     {description: Destructs a timer manager.}
     {prototype: void LmiTimerManagerDestruct(LmiTimerManager* tm)}
     {parameter:
       {name: tm}
       {description: A pointer to LmiTimerManager struct}       
	   }
   }
*/

void LmiTimerManagerDestruct(LmiTimerManager* tm);


/**
   {function visibility="public":
     {name: LmiTimerManagerExecute}
     {parent: LmiTimerManager}
     {description: Determines all timers (allocated to a specific timer manager thread) whose expiry time has passed since the last invocation of 
	   this function and triggers the expiry callbacks on each.  This function is typically called 
	   cyclically by the application.}
     {prototype: LmiTime LmiTimerManagerExecute(LmiTimerManager* tm, LmiSizeT timerThreadNum)}
     {parameter:
       {name: tm}
       {description: A pointer to a timer manager.}
	 }
     {parameter:
       {name: timerThreadNum}
       {description: An identifier of the timer thread number for the timer manager.}
	 }
     {return: The absolute monotonic time when the next timer will expire.}
   }
*/
LmiTime LmiTimerManagerExecute(LmiTimerManager* tm, LmiSizeT timerThreadNum);

/**
   {function visibility="public":
     {name: LmiTimerManagerRegisterFirstExpiryCallback}
     {parent: LmiTimerManager}
     {description: Registers a callback that notifies the application of the absolute monotonic time when the next timer will expire for a given timer manager thread. 
	   This mechanism is used to notify the application when a new timer has been added which is to expire before the absolute monotonic 
	   time returned by the most recent call to LmiTimerManagerExecute.}
     {prototype: void LmiTimerManagerRegisterFirstExpiryCallback(LmiTimerManager* tm, LmiSizeT timerThreadNum, LmiTimerManagerNotifyFirstExpiryCallback cb, LmiVoidPtr userData)}
     {parameter:
       {name: tm}
       {description: A pointer to a timer manager.}
	   }
     {parameter:
       {name: timerThreadNum}
       {description: The timer thread number.}
	   }
     {parameter:
       {name: cb}
       {description: Callback to be invoked.}
	   }
     {parameter:
       {name: userData}
       {description: Any user data to be passed to the callback.}
	   }
	}
*/
void LmiTimerManagerRegisterFirstExpiryCallback(LmiTimerManager* tm, 
	LmiSizeT timerThreadNum, LmiTimerManagerNotifyFirstExpiryCallback cb, LmiVoidPtr userData);

/**
   {function visibility="public":
     {name: LmiTimerManagerGetAllocator}
     {parent: LmiTimerManager}
     {description: Returns the allocator with which a timer manager was constructed.}
     {prototype: LmiAllocator* LmiTimerManagerGetAllocator(LmiTimerManager* tm)}
     {parameter:
       {name: tm}
       {description: A pointer to a timer manager.}
	 }
	 {return: The allocator.}
   }
*/
LmiAllocator* LmiTimerManagerGetAllocator(LmiTimerManager* tm);

/* Internal */
LmiSizeT LmiTimerManagerGetHeapSize(LmiTimerManager* tm, LmiSizeT threadId);


LMI_END_EXTERN_C

#endif /* LMI_TIMER_H_ */
