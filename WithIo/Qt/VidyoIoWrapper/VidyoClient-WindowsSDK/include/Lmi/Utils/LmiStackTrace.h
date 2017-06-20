/** {file:
      {name: LmiStackTrace.h}
      {description: Utility to get backtrace of a callstack.}
      {copyright:
      	(c) 2006-2013 Vidyo, Inc.,
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

#ifndef LMI_STACK_TRACE_H
#define LMI_STACK_TRACE_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**	{function visibility="private":
		{name: LmiStackTrace}
		{parent: Utils}
		{include: Lmi/Utils/LmiStackTrace.h}
		{description: Fills out the buffer of the specified length with the stack trace info.}	
		{prototype:	char* LmiStackTrace(char* buffer, LmiSizeT buflen, LmiUint depth, LmiBool resolve, const char* separator)}
		{parameter:	
			{name: buffer}
			{description: Pointer to the buffer into which stack trace is to be written.}
		}
		{parameter:	
			{name: buflen}
			{description: Length of the buffer.}
		}
		{parameter:	
			{name: depth}
			{description: Max depth of traced stack.}
		}
		{parameter:	
			{name: resolve}
			{description: Whether to resolve the addresses to symbols.  Note this can be a very expensive operation on some platforms, and is not always possible.}
		}
		{parameter:	
			{name: separator}
			{description: Separator string to use between consecutive stack trace entries.}
		}
		{return: pointer to the buffer passed in as a parameter on success, or {code: NULL} on failure.}
	}
*/
char* LmiStackTrace(char* buffer, LmiSizeT buflen, LmiUint depth, LmiBool resolve, const char* separator);

/**	{function visibility="private":
		{name: LmiStackTraceInitialize}	 
		{parent: Utils}
		{include: Lmi/Utils/LmiStackTrace.h}
		{description: Initializes	Stack Trace module.}
		{prototype:	LmiBool LmiStackTraceInitialize(void)}
		{return: {code:	LMI_TRUE} on success, or {code:	LMI_FALSE} on failure.}
	}
*/
LmiBool LmiStackTraceInitialize(void);

/**	{function visibility="private":
		{name: LmiStackTraceUninitialize}	 
		{parent: Utils}
		{include: Lmi/Utils/LmiStackTrace.h}
		{description: Uninitializes	Stack Trace module.}
		{prototype:	void LmiStackTraceUninitialize(void)}
	}
*/
void LmiStackTraceUninitialize(void);

LMI_END_EXTERN_C

#endif
