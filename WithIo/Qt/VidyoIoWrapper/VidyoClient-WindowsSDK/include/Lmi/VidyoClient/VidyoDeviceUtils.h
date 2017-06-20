/**
{file:
	{name: VidyoDeviceUtils.h}
	{description: Device Utilities. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
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
#ifndef VIDYO_DEVICEUTILS_H_
#define VIDYO_DEVICEUTILS_H_

#include <Lmi/Os/LmiThreadPool.h>
#include <Lmi/Os/LmiProperties.h>

LMI_BEGIN_EXTERN_C

struct VidyoAsyncImpl_;
typedef struct VidyoAsyncImpl_ VidyoAsyncImpl;
Declare_LmiSharedPtr(VidyoAsyncImpl)
Declare_LmiSharedPtrWrapper(VidyoAsync, VidyoAsyncImpl)
Declare_LmiWeakPtrWrapper(VidyoAsyncHandle, VidyoAsync, VidyoAsyncImpl)

/**
{type visibility="private":
	{name: VidyoAsync}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoDeviceUtils.h}
	{description: Run function "asynchronously". The function will be run on a separate thread. }
}
*/

/**
{callback visibility="private":
	{name: VidyoAsyncFunction}
	{parent: VidyoAsync}
	{description: Function that will be called asynchronously on a spawned thread. }
	{prototype: void (*VidyoAsyncFunction)(LmiProperties* properties)}
	{parameter: {name: properties} {description: Properties that were set when the request was sent with VidyoAsyncRun(). }}
}
*/
typedef void (*VidyoAsyncFunction)(LmiProperties* properties);

/**
{function visibility="private":
	{name: VidyoAsyncConstruct}
	{parent: VidyoAsync}
	{description: Initialize an instance of VidyoAsync}
	{prototype: VidyoAsync* VidyoAsyncConstruct(VidyoAsync* async, LmiSizeT numThreads, LmiSizeT queueSize, LmiAllocator* alloc)}
	{parameter: {name: async} {description: Pointer to the VidyoAsync object to construct.}}
	{parameter: {name: numThreads} {description: Number of threads to run. }}
	{parameter: {name: queueSize} {description: Size of the queue. }}
	{parameter: {name: alloc} {description: allocator}}
	{return: Properly initialized object or NULL on failure.}
}
*/
VidyoAsync* VidyoAsyncConstruct(VidyoAsync* async, LmiSizeT numThreads, LmiSizeT queueSize, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoAsyncDestruct}
	{parent: VidyoAsync}
	{description: Destruct an instance of VidyoAsync. This may block until there are no more threads running.}
	{prototype: void VidyoAsyncDestruct(VidyoAsync* async)}
	{parameter: {name: async} {description: Pointer to the VidyoAsync object to destruct.}}
}
*/
void VidyoAsyncDestruct(VidyoAsync* async);

/**
{function visibility="private":
	{name: VidyoAsyncRun}
	{parent: VidyoAsync}
	{description: Schedule an async function to be executed on a separate thread. }
	{prototype: LmiBool VidyoAsyncRun(VidyoAsync* async, VidyoAsyncFunction func, LmiProperties* properties, LmiBool useMainThread)}
	{parameter: {name: async} {description: Pointer to the VidyoAsync object.}}
	{parameter: {name: func} {description: Function to be executed }}
	{parameter: {name: properties} {description: Properties to be passed to the function}}
	{parameter: {name: useMainThread} {description: Attempt to run the funciton on the main thread of the application. }}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: useMainThread may not be available on every platform in which case it will execute in a normal thread. }
}
*/
LmiBool VidyoAsyncRun(VidyoAsync* async, VidyoAsyncFunction func, LmiProperties* properties, LmiBool useMainThread);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoDeviceUtilsInline.h"
#endif

#endif /* VIDYO_DEVICEUTILS_H_ */
