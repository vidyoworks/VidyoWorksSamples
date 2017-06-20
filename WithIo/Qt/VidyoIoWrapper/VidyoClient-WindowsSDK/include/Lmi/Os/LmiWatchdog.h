/** {file:
	  {name: LmiWatchdog.h}
	  {description: Watchdog timer class.}
	  {copyright:
	  	(c) 2013 Vidyo, Inc.,
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
#ifndef LMI_WATCHDOG_H_
#define LMI_WATCHDOG_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiTimer.h>
#include <Lmi/Os/LmiMutex.h>


LMI_BEGIN_EXTERN_C

struct LmiWatchdog_;

/**
	{callback:
		{name: LmiWatchdogExpiryCallback}
		{parent: LmiWatchdog}
		{description: This is the callback function invoked on watchdog expiry.}
		{prototype: void (*LmiWatchdogExpiryCallback)(LmiWatchdog *wd, LmiVoidPtr userData)}
		{parameter:
			{name: wd}
			{description: A pointer to LmiWatchdog struct}}
		{parameter:
			{name: userData}
			{description: pointer to user data}}
	}
*/
typedef void (*LmiWatchdogExpiryCallback)(struct LmiWatchdog_ *wd, LmiVoidPtr userData);


/**
	{type:
		{name: LmiWatchdog}
		{parent: Os}
		{include: Lmi/Os/LmiWatchdog.h}
		{description:
			A watchdog timer class used to monitor the persistence of an activity.}
	}
*/
typedef struct LmiWatchdog_ {	
	LmiTimer timer;
	LmiTime duration;
	LmiBool isActive;
	LmiBool isEnabled;
	LmiWatchdogExpiryCallback	expiryCallback ;
	LmiVoidPtr userData;
	LmiMutex mutex;
	LmiBool isStopping;
	LmiBool isResetting;
} LmiWatchdog;


/**
	{function:
		{name: LmiWatchdogConstruct}
		{parent: LmiWatchdog}
		{description: Construct an LmiWatchdog object.}
		{prototype: LmiWatchdog* LmiWatchdogConstruct(LmiWatchdog* wd, LmiTime expiryTime, LmiWatchdogExpiryCallback cb, LmiVoidPtr userData, LmiTimerManager *tm)}
		{parameter:
			{name: wd}
			{description: The LmiWatchdog object to construct.}}
		{parameter:
			{name: expiryTime}
			{description: Watchdog expiry time in nanoseconds.}}
		{parameter:
			{name: cb}
			{description: The callback function invoked upon watchdog expiry.}}
		{parameter:
			{name: userData}
			{description: A pointer to user data (may be NULL) that will be passed on callback function invocation.}}
		{parameter:
			{name: tm}
			{description: A pointer to timer manager to use for scheduling the timer.}}
		{return: A pointer to the constructed object or NULL on failure.}
}
*/
LmiWatchdog* LmiWatchdogConstruct(LmiWatchdog* wd, LmiTime expiryTime, LmiWatchdogExpiryCallback cb, LmiVoidPtr userData, LmiTimerManager *tm);


/**
	{function:
		{name: LmiWatchdogDestruct}
		{parent: LmiWatchdog}
		{description: Destruct an LmiWatchdog object.}
		{prototype: void LmiWatchdogDestruct(LmiWatchdog* wd)}
		{parameter:
			{name: wd}
			{description: The LmiWatchdog object to destruct.}}
		{note: If the timer has been started, it is stopped.}
	}
*/
void LmiWatchdogDestruct(LmiWatchdog* wd);

/**
	{function:
		{name: LmiWatchdogStart}
		{parent: LmiWatchdog}
		{description: Starts a watchdog.}
		{prototype: LmiBool LmiWatchdogStart(LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: LMI_TRUE or success or LMI_FALSE otherwise.}
		{note: Start has no effect if it is already running.}
	}
*/
LmiBool LmiWatchdogStart(LmiWatchdog *wd);

/**
	{function:
		{name: LmiWatchdogStartWithTime}
		{parent: LmiWatchdog}
		{description: Starts a watchdog with a specific duration.}
		{prototype: LmiBool LmiWatchdogStartWithTime(LmiWatchdog *wd, LmiTime expiryTime)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
			{parameter:
				{name: expiryTime}
				{description: Watchdog expiry time in nanoseconds.}}
		{return: LMI_TRUE or success or LMI_FALSE otherwise.}
		{note: expiryTime will override the existing watchdog duration provided earlier.}
		{note: If the expiryTime is different from the expiry time provided earlier,
			the LmiWatchdogGetDuration called before this function call will become obsolete.}
		{note: Start has no effect if it is already running.}
	}
*/
LmiBool LmiWatchdogStartWithTime(LmiWatchdog *wd, LmiTime expiryTime);

/**
	{function:
		{name: LmiWatchdogStop}
		{parent: LmiWatchdog}
		{description: Stop an LmiWatchdog timer.}
		{prototype: LmiBool LmiWatchdogStop(LmiWatchdog* wd)}
		{parameter:
			{name: wd}
			{description: The LmiWatchdog to stop.}}
		{return: LMI_TRUE or success or LMI_FALSE otherwise.}
	}
*/
LmiBool LmiWatchdogStop(LmiWatchdog *wd);

/**
	{function:
		{name: LmiWatchdogReset}
		{parent: LmiWatchdog}
		{description: Reset an LmiWatchdog timer.}
		{prototype: LmiBool LmiWatchdogReset(LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: LMI_TRUE or success or LMI_FALSE otherwise.}
	}
*/
LmiBool LmiWatchdogReset(LmiWatchdog *wd);

/**
	{function:
		{name: LmiWatchdogResetEx}
		{parent: LmiWatchdog}
		{description: Reset an LmiWatchdog timer with modified watchdog parameters.}
		{prototype: LmiBool LmiWatchdogResetEx(LmiWatchdog *wd, LmiTime expiryTime, LmiWatchdogExpiryCallback cb, LmiVoidPtr userData)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{parameter:
			{name: expiryTime}
			{description: Watchdog expiry time in nanoseconds.
				Ignored if zero.}}
		{parameter:
			{name: cb}
			{description: The callback function invoked upon watchdog expiry.
				Ignored if NULL.}}
		{parameter:
			{name: userData}
			{description: A pointer to user data (may be NULL) that will be passed on callback function invocation.
				Ignored if NULL.}}
		{return: LMI_TRUE or success or LMI_FALSE otherwise.}
		{note: expiryTime will override the existing watchdog duration provided earlier.}
		{note: If the expiryTime is different from the expiry time provided earlier,
			the LmiWatchdogGetDuration called before this function call will become obsolete.}
	}
*/
LmiBool LmiWatchdogResetEx(LmiWatchdog *wd, LmiTime expiryTime, LmiWatchdogExpiryCallback cb, LmiVoidPtr userData);

/**
	{function:
		{name: LmiWatchdogDisable}
		{parent: LmiWatchdog}
		{description: Disable LmiWatchdog timer.}
		{prototype: LmiBool LmiWatchdogDisable(LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: LMI_TRUE or success or LMI_FALSE otherwise.}
		{note: LmiWatchdog is enabled by default. Disable has no effect if LmiWatchdog is already disabled}
		{note: If LmiWatchdog is disabled, all the further operations on LmiWatchdog have no effect.}
		{note: If LmiWatchdog is running, disable will stop the LmiWatchdog.}
	}
*/
LmiBool LmiWatchdogDisable(LmiWatchdog *wd);

/**
	{function:
		{name: LmiWatchdogEnable}
		{parent: LmiWatchdog}
		{description: Enable LmiWatchdog timer.}
		{prototype: LmiBool LmiWatchdogEnable(LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: LMI_TRUE or success or LMI_FALSE otherwise.}
		{note: LmiWatchdog is enabled by default. Enable has no effect if LmiWatchdog is already enabled.}
		{note: Enable will not have any effect on the previously issued commands, only the future commands are affected.}
	}
*/
LmiBool LmiWatchdogEnable(LmiWatchdog *wd);


/**
	{function:
		{name: LmiWatchdogIsEnabled}
		{parent: LmiWatchdog}
		{description: Check whether LmiWatchdog is enabled or not.}
		{prototype: LmiBool LmiWatchdogIsEnabled(const LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: LMI_TRUE if enabled, LMI_FALSE otherwise.}
		{note: LmiWatchdog is enabled by default.}
	}
*/
LmiBool LmiWatchdogIsEnabled(const LmiWatchdog *wd);

/**
	{function:
		{name: LmiWatchdogIsActive}
		{parent: LmiWatchdog}
		{description: Check whether LmiWatchdog is running or not.}
		{prototype: LmiBool LmiWatchdogIsActive(const LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: LMI_TRUE if running, LMI_FALSE otherwise.}
	}
*/
LmiBool LmiWatchdogIsActive(const LmiWatchdog *wd);

/**
	{function:
		{name: LmiWatchdogGetDuration}
		{parent: LmiWatchdog}
		{description: Get the duration of LmiWatchdog.}
		{prototype: LmiTime LmiWatchdogGetDuration(const LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: Duration of the LmiWatchdog.}
		{note: Duration provided during construction can be overridden by expiryTime provided
			during further invocations to LmiWatchdogStartWithTime and LmiWatchdogResetEx.
			The latest value provided will be returned.}
	}
*/
LmiTime LmiWatchdogGetDuration(const LmiWatchdog *wd);

/**
	{function:
		{name: LmiWatchdogGetUserData}
		{parent: LmiWatchdog}
		{description: Get the user data of LmiWatchdog.}
		{prototype: LmiVoidPtr LmiWatchdogGetUserData(const LmiWatchdog *wd)}
		{parameter: 
			{name: wd}
			{description: The LmiWatchdog object.}}
		{return: User data of the LmiWatchdog.}
	}
*/
LmiVoidPtr LmiWatchdogGetUserData(const LmiWatchdog *wd);

LMI_END_EXTERN_C

#endif /* LMI_WATCHDOG_H_ */
