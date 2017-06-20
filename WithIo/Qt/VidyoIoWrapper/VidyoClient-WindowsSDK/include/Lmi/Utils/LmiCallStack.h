/**
{file:
	{name: LmiCallStack.h}
	{description: Utilities for reading call stack}
	{copyright:
		(c) 2007-2012 Vidyo, Inc.,
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
#ifndef LMI_CALLSTACK_H
#define LMI_CALLSTACK_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
{function visibility="private":
	{name: LmiCallStack}
	{parent: Utils}
	{include: Lmi/Utils/LmiCallStack.h}
	{description: Gets the current call stack.}
	{prototype: void LmiCallStack(void** callStack, LmiSizeT size, LmiSizeT skip)}
	{parameter: {name: callStack} {description: An array of pointers into which the
		return addresses on the call stack will be written.}}
	{parameter: {name: size} {description: The maximum number of addresses to write.}}
	{parameter: {name: skip} {description: The number of addresses on the call stack
		to skip over before writing addresses into the array. In some instances the first
		few return addresses will always be the same, so it may be desirable to remove
		these from the output.}}
}
*/
void LmiCallStack(void **callStack, LmiSizeT size, LmiSizeT skip);

char **LmiCallStackGetSymbols(void **callStack, LmiSizeT size);

LMI_END_EXTERN_C

#endif
