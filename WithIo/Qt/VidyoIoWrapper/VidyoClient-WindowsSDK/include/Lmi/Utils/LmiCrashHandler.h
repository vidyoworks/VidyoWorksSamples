/**
{file:
	{name: LmiCrashHandler.h}
	{description: Handles the application crashes. }
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
#ifndef LMI_CRASHHANDLER_H
#define LMI_CRASHHANDLER_H

#include <Lmi/Utils/LmiUtils.h>


/**
   {package:
     {name: CrashHandler}
         {parent: Utils}
     {include: Lmi/Utils/LmiCrashHandler.h}
         {description: Functions and callbacks for handling crashes.}
   }
*/

/**
{callback visibility="private":
	{name: LmiCrashHandlerCallback}
	{parent: CrashHandler}
	{description: Callback that receives a strack trace in the event of an application crash.
	              The callback must not perform any memory allocations or deallocations. }
	{prototype: typedef void (*LmiCrashHandlerCallback)(char *stackTrace)}
	{parameter:
		{name: stackTrace}
		{description: String representation of the stack trace.}
	}
}
*/
typedef void(*LmiCrashHandlerCallback)(char *stackTrace);


/**
{function visibility="private":
	{name: LmiCrashHandler}
    {parent: CrashHandler}
	{description: Registers a callback for receiving a stack trace in the event of an application crash.
	              The callback must not perform any memory allocations or deallocations. }
	{prototype: LmiBool LmiCrashHandler(LmiCrashHandlerCallback callback)}
	{parameter:
		{name: callback}
		{description: The callback to register. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool LmiCrashHandler(LmiCrashHandlerCallback callback);

#endif
