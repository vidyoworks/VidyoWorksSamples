/** {file:
	  {name: LmiCallbackGuard.h}
	  {description: Guard object to prevent deadlocks on callbacks.}
	  {copyright:
	  	(c) 2007-2015 Vidyo, Inc.,
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
#ifndef LMI_CALLBACK_GUARD_H_
#define LMI_CALLBACK_GUARD_H_

#include <Lmi/Os/LmiMonitor.h>
#include <Lmi/Os/LmiCondition.h>
#include <Lmi/Os/LmiThread.h>

#include <Lmi/Utils/LmiUnordered.h>

LMI_BEGIN_EXTERN_C

Declare_LmiUnorderedMap(LmiThreadId, LmiSizeT)

/**
	{type visibility="private":
    	{name: LmiCallbackGuard}
		{parent: Os}
		{include: Lmi/Os/LmiCallbackGuard.h}
		{description:
		  {p: An object to prevent deadlocks on callbacks.}
		  {p: The differences between this and LmiCallerGuard are as follows:
		    {h\:ul xmlns\:h="http\://www.w3.org/1999/xhtml":
		        {h\:li: LmiCallbackGuardStopCallbacks returns immediately without
				   waiting for callback threads to finish if invoked from
				   within a callback thread. The behavior is idempotent, i.e.,
				   subsequent calls behave the same as the first one.}
				{h\:li: First call to LmiCallerGuardStop blocks until callback threads
				   (other than the one it's invoked from) are finished and returns
				   LMI_TRUE. Subsequent calls to LmiCallerGuardStop return LMI_FALSE
				   immediately, i.e., without waiting for callback threads to finish.}
				{h\:li: LmiCallbackGuard can be reset with LmiCallbackGuardReset.}
			}
		  }
		  {p: If you're not sure which one to use, you almost certainly want to use LmiCallerGuard.}
		}
   }
*/
typedef struct {
	LmiMonitor monitor;
	LmiCondition condition;
	LmiSizeT runningCount;
	LmiBool stopping;
	LmiThreadId mainCallbackThread;
	LmiSizeT mainCallbackRunningCount;
	LmiUnorderedMap(LmiThreadId, LmiSizeT) otherThreads;
} LmiCallbackGuard;


/**
	{function visibility="private":
		{name: LmiCallbackGuardConstruct}
		{parent: LmiCallbackGuard}
		{description: Construct a callback guard object.}
		{prototype: LmiCallbackGuard* LmiCallbackGuardConstruct(LmiCallbackGuard* g, LmiAllocator* a)}
		{parameter:
			{name: g}
			{description: The object to construct.}}
		{parameter:
			{name: a}
			{description: An allocator to use for dynamic data of the callback guard.}}
		{return: g on success, NULL on failure.}
	}
*/
LmiCallbackGuard* LmiCallbackGuardConstruct(LmiCallbackGuard* g, LmiAllocator* a);


/**
	{function visibility="private":
		{name: LmiCallbackGuardDestruct}
		{parent: LmiCallbackGuard}
		{description: Destruct a callback guard.}
		{prototype: void LmiCallbackGuardDestruct(LmiCallbackGuard* g)}
		{parameter:
			{name: g}
			{description: The object to destruct.}}
	}
*/
void LmiCallbackGuardDestruct(LmiCallbackGuard* g);


/* Internal (non-inlined) helpers for these functions */
LmiBool LmiCallbackGuardEnterCallback_(LmiCallbackGuard* g, LmiThreadId currentThread);
void LmiCallbackGuardLeaveCallback_(LmiCallbackGuard* g, LmiThreadId currentThread);

/**
	{function visibility="private":
		{name: LmiCallbackGuardEnterCallback}
		{parent: LmiCallbackGuard}
		{description: Inform the callback guard that a callback is being
			entered, checking whether callbacks have been stopped.}
		{prototype: LmiBool LmiCallbackGuardEnterCallback(LmiCallbackGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard for the callback being entered.}}
		{return: Whether the callback guard was successfully entered.  If
			this function returned false, LmiCallbackGuardStopCallbacks has been
			invoked; the function using the callback guard should return
			without taking any actions.}
		{note: Matching calls to LmiCallbackGuardLeaveCallback must be called
			for every call to LmiCallbackGuardEnterCallback that returns
			LMI_TRUE.}
	}
*/
LmiBool LmiCallbackGuardEnterCallback(LmiCallbackGuard* a);


/**
	{function visibility="private":
		{name: LmiCallbackGuardLeaveCallback}
		{parent: LmiCallbackGuard}
		{description: Inform the callback guard that a callback is being left.}
		{prototype: LmiBool LmiCallbackGuardLeaveCallback(LmiCallbackGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard for the callback being left.}}
		{return: LMI_TRUE if this is the final departure from a stopped callback guard;
			LMI_FALSE otherwise.}
	}
*/
LmiBool LmiCallbackGuardLeaveCallback(LmiCallbackGuard* g);


/**
	{function visibility="private":
		{name: LmiCallbackGuardStopCallbacks}
		{parent: LmiCallbackGuard}
		{description: Inform a callback guard that callbacks are being stopped.
			Subsequent calls to LmiCallbackGuardEnterCallback for this guard
			will return LMI_FALSE.  If a callback is currently executing
			(i.e., LmiCallbackGuardEnterCallback has been invoked, but its
			matching LmiCallbackGuardLeaveCallback has not), this function will
			block until LmiCallbackGuardLeaveCallback is called, unless
			StopCallbacks is invoked in the same thread as EnterCallback was.}
		{prototype: void LmiCallbackGuardStopCallbacks(LmiCallbackGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard for the callbacks being stopped.}}
	}
*/
void LmiCallbackGuardStopCallbacks(LmiCallbackGuard* g);


/**
	{function visibility="private":
		{name: LmiCallbackGuardInCallbackThread}
		{parent: LmiCallbackGuard}
		{description: Query whether we are currently executing in the context
			of a thread which is currently executing a callback for this
			callback guard, i.e. a call to EnterCallback has been made without
			a matching call to LeaveCallback.  This is exactly the scenario
			in which LmiCallbackGuardStopCallbacks will not wait for
			completion of an outstanding callback.}
		{prototype: LmiBool LmiCallbackGuardInCallbackThread(LmiCallbackGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard to query whether we are executing
				in a callback\'s thread.}}
		{return: Whether we are executing in a callback\'s thread.}
	}
*/
LmiBool LmiCallbackGuardInCallbackThread(LmiCallbackGuard* g);


/**
	{function visibility="private":
		{name: LmiCallbackGuardReset}
		{parent: LmiCallbackGuard}
		{description: Reset an LmiCallbackGuard object, returning it to the
			state it has on construction.}
		{prototype: void LmiCallbackGuardReset(LmiCallbackGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard to reset.}}
	}
*/
void LmiCallbackGuardReset(LmiCallbackGuard* g);


/**
	{function visibility="private":
		{name: LmiCallbackGuardIsStopping}
		{parent: LmiCallbackGuard}
		{description: Return whether an LmiCallbackGuard object has been stopped (and not reset).}
		{prototype: LmiBool LmiCallbackGuardIsStopping(LmiCallbackGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard to test.}}
		{return: Whether the callback guard is stopping.}
	}
*/
LmiBool LmiCallbackGuardIsStopping(LmiCallbackGuard* g);


LMI_END_EXTERN_C

#endif /* LMI_CALLBACK_GUARD_H_ */
