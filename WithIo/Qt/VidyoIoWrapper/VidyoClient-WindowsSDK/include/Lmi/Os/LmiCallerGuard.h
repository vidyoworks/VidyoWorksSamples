/**
{file:
	{name: LmiCallerGuard.h}
	{description: Guard object to synchronize objects with callbacks.}
	{copyright:
	  	(c) 2010 Vidyo, Inc.,
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
#ifndef LMI_CALLERGUARD_H
#define LMI_CALLERGUARD_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUnordered.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiSemaphore.h>
#include <Lmi/Os/LmiThread.h>
#include <Lmi/Os/LmiCallbackGuard.h> /* For LmiUnorderedMap(LmiThreadId, LmiUint) declaration only */

LMI_BEGIN_EXTERN_C

typedef enum
{
	LMI_CALLERGUARD_STATE_RUNNING,
	LMI_CALLERGUARD_STATE_STOPPING,
	LMI_CALLERGUARD_STATE_STOPPED
} LmiCallerGuardState;

/**
	{type visibility="private":
    	{name: LmiCallerGuard}
		{parent: Os}
		{include: Lmi/Os/LmiCallerGuard.h}
		{description: Guard object to synchronize objects with callbacks.}
   }
*/
typedef struct
{
	LmiMutex mutex;
	LmiSemaphore sem;
	LmiUnorderedMap(LmiThreadId, LmiSizeT) count;
	LmiCallerGuardState state;
	LmiSizeT total;
	LmiSizeT ignore;
	LmiBool autoClean;                             /* LMI_TRUE to clean up thread info, LMI_FALSE to leave all thread info until destruct */
} LmiCallerGuard;

LmiCallerGuard *LmiCallerGuardConstruct(LmiCallerGuard *g, LmiBool autoClean, LmiAllocator *alloc);
void LmiCallerGuardDestruct(LmiCallerGuard *g);
LmiBool LmiCallerGuardEnterCallback(LmiCallerGuard *g);
void LmiCallerGuardLeaveCallback(LmiCallerGuard *g);
LmiBool LmiCallerGuardStop(LmiCallerGuard *g);

/**
	{function visibility="private":
		{name: LmiCallerGuardConstruct}
		{parent: LmiCallerGuard}
		{description: Construct a callback guard object.}
		{prototype: LmiCallerGuard* LmiCallerGuardConstruct(LmiCallerGuard* g, LmiBool autoClean, LmiAllocator* a)}
		{parameter:
			{name: g}
			{description: The object to construct.}}
		{parameter:
			{name: autoClean}
			{description: LMI_TRUE to cause callback guard to clean up
				thread info as it goes. LMI_FALSE to save thread info until
				callback guard is destructed. Use the LMI_TRUE setting for
				long lived callback guards that are used by large numbers
				of different threads or a dynamically allocated thread pool.
				Use LMI_FALSE for faster operation when the number of
				threads will be small.}}
		{parameter:
			{name: a}
			{description: An allocator to use for dynamic data of the callback guard.}}
		{return: a pointer to the object on success, NULL on failure.}
	}
*/
/**
	{function visibility="private":
		{name: LmiCallerGuardDestruct}
		{parent: LmiCallerGuard}
		{description: Destruct a callback guard.}
		{prototype: void LmiCallerGuardDestruct(LmiCallerGuard* g)}
		{parameter:
			{name: g}
			{description: The object to destruct.}}
	}
*/
/**
	{function visibility="private":
		{name: LmiCallerGuardEnterCallback}
		{parent: LmiCallerGuard}
		{description: Inform the callback guard that a callback is being
			entered, checking whether callbacks have been stopped.}
		{prototype: LmiBool LmiCallerGuardEnterCallback(LmiCallerGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard for the callback being entered.}}
		{return: LMI_TRUE if the callback guard was successfully
			entered. LMI_FALSE if LmiCallerGuardStop has been called
			and no callback should be made.}
		{note: Matching calls to LmiCallerGuardLeaveCallback must be called
			for every call to LmiCallerGuardEnterCallback that returns
			LMI_TRUE.}
	}
*/
/**
	{function visibility="private":
		{name: LmiCallerGuardLeaveCallback}
		{parent: LmiCallerGuard}
		{description: Inform the callback guard that a callback is being left.}
		{prototype: void LmiCallerGuardLeaveCallback(LmiCallerGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard for the callback being left.}}
	}
*/
/**
	{function visibility="private":
		{name: LmiCallerGuardStop}
		{parent: LmiCallerGuard}
		{description: Inform a callback guard that callbacks are being stopped.
			Subsequent calls to LmiCallerGuardEnterCallback for this guard
			will return LMI_FALSE.  If callbacks are currently executing
			on threads other than the one where LmiCallerGuardStop is called on,
			(i.e., LmiCallerGuardEnterCallback has been invoked, but its
			matching LmiCallerGuardLeaveCallback has not), this function will
			block until LmiCallerGuardLeaveCallback is called on those threads.
			If LmiCallerGuardStop is called more than once, subsequent calls
			will return immediately	and return LMI_FALSE.}
		{prototype: LmiBool LmiCallerGuardStop(LmiCallerGuard* g)}
		{parameter:
			{name: g}
			{description: The callback guard for the callbacks being stopped.}}
		{return: LMI_TRUE the first time LmiCallerGuardStop is called, LMI_FALSE
			on subsequent calls.}
	}
*/

LMI_END_EXTERN_C

#endif /* LMI_CALLERGUARD_H */
