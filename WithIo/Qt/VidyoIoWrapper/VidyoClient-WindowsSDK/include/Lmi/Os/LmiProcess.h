/**
{file:
{name: LmiProcess.h}
	{description: Declarations related to OS processes.}
	{copyright:
		(c) 2007-2015 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef LMI_PROCESS_H
#define LMI_PROCESS_H

#include <Lmi/Utils/LmiTypes.h>

/**
{type:
	{name: LmiProcessId}
	{parent: Os}
	{include: Lmi/Os/LmiProcess.h}
	{description: An operating system process identifier.}
}
*/

/* POSIX */
#if defined(LMI_HAVE_GETPID)
#include <sys/types.h>
#include <unistd.h>

typedef pid_t LmiProcessId;

/* Win32 */
#elif defined(LMI_HAVE_GETCURRENTPROCESSID)
#include <winsock2.h>

typedef DWORD LmiProcessId;

#else
#error Unknown Process implementation
#endif

/**
{function:
	{name: LmiProcessIdConstructCopy}
	{parent: LmiProcessId}
	{description: Construct a process ID from another process ID.}
	{prototype: LmiProcessId* LmiProcessIdConstructCopy(LmiProcessId* x, const LmiProcessId* y)}
	{parameter:
		{name: x}
		{description: The process ID.}
	}
	{parameter:
		{name: y}
		{description: The process ID to initialize from.}
	}
	{return: Returns the constructed object or NULL on error.}
}
*/
LmiProcessId* LmiProcessIdConstructCopy(LmiProcessId* x, const LmiProcessId* y);

/**
{function:
	{name: LmiProcessIdDestruct}
	{parent: LmiProcessId}
	{description: Destructs a process ID.}
	{prototype: void LmiProcessIdDestruct(LmiProcessId* x)}
	{parameter:
		{name: x}
		{description: The process ID.}
	}
}
*/
void LmiProcessIdDestruct(LmiProcessId* x);

/**
{function:
	{name: LmiProcessIdAssign}
	{parent: LmiProcessId}
	{description: Assigns the content of one process ID to another process ID.}
	{prototype: LmiProcessId* LmiProcessIdAssign(LmiProcessId* x, const LmiProcessId* y)}
	{parameter:
		{name: x}
		{description: The process ID to assign.}
	}
	{parameter:
		{name: y}
		{description: The process ID to assign from.}
	}
	{return: Returns a pointer to the assigned to process ID or NULL on error.}
}
*/
LmiProcessId* LmiProcessIdAssign(LmiProcessId* x, const LmiProcessId* y);

/**
{function:
	{name: LmiProcessIdEqual}
	{parent: LmiProcessId}
	{description: Compares two process IDs for equality.}
	{prototype: LmiBool LmiProcessIdEqual(const LmiProcessId* x, const LmiProcessId* y)}
	{parameter:
		{name: x}
		{description: One of the process ID.}
	}
	{parameter:
		{name: y}
		{description: The other process ID.}
	}
	{return: Returns LMI_TRUE if the process IDs are equal or LMI_FALSE otherwise.}
}
*/
LmiBool LmiProcessIdEqual(const LmiProcessId* x, const LmiProcessId* y);

/**
{function:
	{name: LmiProcessIdLess}
	{parent: LmiProcessId}
	{description: Compares two process IDs for less-than equality.}
	{prototype: LmiBool LmiProcessIdLess(const LmiProcessId* x, const LmiProcessId* y)}
	{parameter:
		{name: x}
		{description: One of the process IDs.}
	}
	{parameter:
		{name: y}
		{description: The other process ID.}
	}
	{return: Returns LMI_TRUE if the first process ID is less than the second process ID or LMI_FALSE otherwise. }
}
*/
LmiBool LmiProcessIdLess(const LmiProcessId* x, const LmiProcessId* y);

/**
{function:
	{name: LmiProcessIdSwap}
	{parent: LmiProcessId}
	{description: Swaps two process ID objects.}
	{prototype: LmiBool LmiProcessIdSwap(LmiProcessId* x, LmiProcessId* y)}
	{parameter:
		{name: x}
		{description: One of the process IDs.}
	}
	{parameter:
		{name: y}
		{description: The other process ID.}
	}
	{return: Returns LMI_TRUE if the process IDs were swapped or LMI_FALSE otherwise. }
}
*/
LmiBool LmiProcessIdSwap(LmiProcessId* x, LmiProcessId* y);


/**
{function:
	{name: LmiProcessGetCurrentProcessId}
	{parent: Os}
	{include: Lmi/Os/LmiProcess.h}
	{description: Gets the process ID of the current process.}
	{prototype: LmiProcessId LmiProcessGetCurrentProcessId()}
	{return: Returns the process ID of the current process or 0 on failure.}
}
*/
LmiProcessId LmiProcessGetCurrentProcessId();

#endif

