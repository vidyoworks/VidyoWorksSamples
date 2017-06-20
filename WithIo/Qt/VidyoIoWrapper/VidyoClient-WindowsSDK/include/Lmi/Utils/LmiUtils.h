/**
{file:
	{name: LmiUtils.h}
	{description: A package of OS independent utility types, classes and functions.}
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

#ifndef LMI_UTILS_H_
#define LMI_UTILS_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVersion.h>

LMI_BEGIN_EXTERN_C

/**
{package:
	{name: Utils}
	{parent: Lmi}
	{include: Lmi/Utils/LmiUtils.h}
	{library: LmiUtils}
	{description: A package of OS independent utility types, classes and functions.}
}
*/

/**
{function:
	{name: LmiUtilsInitialize}
	{parent: Utils}
	{description: Initialize all operating-system-independent components of the Vidyo SDK.}
	{prototype: LmiBool LmiUtilsInitialize(void)}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: This function is not reentrant.}
	{note: This function may be called multiple times as long as its corresponding LmiUtilsUninitialize function is called the same number of times.}
}
*/
LmiBool LmiUtilsInitialize(void);

/**
{function:
	{name: LmiUtilsUninitialize}
	{parent: Utils}
	{description: Uninitialize all operating-system-independent components of the Vidyo SDK.}
	{prototype: void LmiUtilsUninitialize(void)}
	{note: This function is not reentrant.}
	{note: This function must be called the same number of times as LmiUtilsInitialize was called.}
}
*/
void LmiUtilsUninitialize(void);

/**
{function:
	{name: LmiUtilsGetVersion}
	{parent: Utils}
	{description: Gets the version of the utilities library. }
	{prototype: LmiVersion LmiUtilsGetVersion(void)}
	{return: Returns the version of the utilities library. }
}
*/
LmiVersion LmiUtilsGetVersion(void);

/**
{function:
	{name: LmiUtilsGetVersionString}
	{parent: Utils}
	{description: Gets the version of the utilities library, as a human readable string. }
	{prototype: const char *LmiUtilsGetVersionString(void)}
	{return: Returns the version string of the utilities library. }
}
*/
const char *LmiUtilsGetVersionString(void);

/**
{function visibility="private":
	{name: LmiUtilsGetBuildTag}
	{parent: Utils}
	{description: Gets the tag that was used to check out the code. }
	{prototype: const char *LmiUtilsGetBuildTag(char *buf, LmiSizeT len)}
	{parameter: {name: buf} {description: A buffer to write the tag to.}}
	{parameter: {name: len} {description: Length of the buffer in bytes.}}
	{return: The build tag.}
}
*/
const char *LmiUtilsGetBuildTag(char *buf, LmiSizeT len);

LMI_END_EXTERN_C

#endif /* LMI_UTILS_H_ */
