/**
{file:
	{name: LmiThreadPool.h}
	{description: Thread pool}
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
#ifndef LMI_THREADPOOL_H
#define LMI_THREADPOOL_H

#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiPointerVector.h>
#include <Lmi/Utils/LmiString.h>

#include <Lmi/Os/LmiQueue.h>
#include <Lmi/Os/LmiThread.h>
#include <Lmi/Os/LmiMutex.h>

LMI_BEGIN_EXTERN_C
/**
{type:
	{name: LmiThreadPool}
	{parent: Os}
	{include: Lmi/Os/LmiThreadPool.h}
	{description: Thread Pool}
}
*/
typedef struct {
	char *poolName;
	LmiMutex mutex;
	LmiSizeT runningThreads;
	LmiSizeT targetRunningThreads;
	LmiQueue q;
	LmiPointerVector threads;
	LmiThreadPriority p;
	LmiSizeT stackSize;
	LmiBitset affinity;
} LmiThreadPool;


/**
{callback:
	{name: LmiThreadPoolUserFunction}
	{parent: LmiThreadPool}
	{description: A function to be executed by a thread pool.}
	{prototype: void (*LmiThreadPoolUserFunction)( void* userData )}
	{parameter:
		{name: userData}
		{description: The user data for the function.}
	}
}
*/
typedef void (*LmiThreadPoolUserFunction)( void* userData );

/**
{function visibility="private":
	{name: LmiThreadPoolConstruct}
	{parent: LmiThreadPool}
	{description: Constructs a Thread Pool.}
	{prototype: LmiThreadPool *LmiThreadPoolConstruct( LmiThreadPool *threadPool, const char *poolName, LmiThreadPriority priority, LmiSizeT stackSize, LmiSizeT numThreads, LmiSizeT queueSize, LmiAllocator *a )}
	{parameter: {name: threadPool} {description: The Thread Pool object to construct.}}
	{parameter: {name: poolName} {description: A name describing the thread pool.}}
	{parameter: {name: priority} {description: The priority with which threads in the pool will run.}}
	{parameter: {name: stackSize} {description:
						A platform dependent stack size.  Setting stack size to 0 
						(recommended) will create the thread with a system dependent 
						default stack size.}}
	{parameter: {name: numThreads} {description: The number of thread in the pool.}}
	{parameter: {name: queueSize} {description: The maximum number of tasks that can be queued for execution by the thread pool.}}
	{parameter: {name: a} {description: An allocator used to allocate the queue and support data.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiThreadPool *LmiThreadPoolConstruct( LmiThreadPool *threadPool, const char *poolName, LmiThreadPriority priority, LmiSizeT stackSize, LmiSizeT numThreads, LmiSizeT queueSize, LmiAllocator *a );

/**
{function visibility="private":
	{name: LmiThreadPoolConstructWithAffinity}
	{parent: LmiThreadPool}
	{description: Constructs a Thread Pool with Core affinity for the threads in the thread pool.}
	{prototype: LmiThreadPool *LmiThreadPoolConstructWithAffinity( LmiThreadPool *threadPool, const char *poolName, LmiThreadPriority priority, LmiBitset *affinity, LmiSizeT stackSize, LmiSizeT numThreads, LmiSizeT queueSize, LmiAllocator *a )}
	{parameter: {name: threadPool} {description: The Thread Pool object to construct.}}
	{parameter: {name: poolName} {description: A name describing the thread pool.}}
	{parameter: {name: priority} {description: The priority with which threads in the pool will run.}}
	{parameter: {name: affinity} {description: The thread-to-core affinity for each thread in the thread pool. See LmiThreadSetCoreAffinity for more details.}}
	{parameter: {name: stackSize} {description:
						A platform dependent stack size.  Setting stack size to 0 
						(recommended) will create the thread with a system dependent 
						default stack size.}}
	{parameter: {name: numThreads} {description: The number of thread in the pool.}}
	{parameter: {name: queueSize} {description: The maximum number of tasks that can be queued for execution by the thread pool.}}
	{parameter: {name: a} {description: An allocator used to allocate the queue and support data.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiThreadPool *LmiThreadPoolConstructWithAffinity( LmiThreadPool *threadPool, const char *poolName, LmiThreadPriority priority, LmiBitset *affinity, LmiSizeT stackSize, LmiSizeT numThreads, LmiSizeT queueSize, LmiAllocator *a );

/**
{function visibility="private":
	{name: LmiThreadPoolDestruct}
	{parent: LmiThreadPool}
	{description: Destructs a Thread Pool object.}
	{prototype: void LmiThreadPoolDestruct( LmiThreadPool *threadPool )}
	{parameter: {name: threadPool} {description: The thread pool object to destruct.}}
	{note: Any pending functions queued in the thread pool are discarded.  This may cause memory to be leaked.  To shut down a thread pool
		gracefully, call LmiThreadPoolSetNumThreads(threadPool, 0) before destructing it.}
}
*/
void LmiThreadPoolDestruct( LmiThreadPool *threadPool );

/**
{function:
	{name: LmiThreadPoolExecute}
	{parent: LmiThreadPool}
	{description: Queue a function for execution by the thread pool.  
					Note that this function may block depending on the number of tasks queued for execution and the 
					queue size specified in the constructor }
	{prototype: LmiBool LmiThreadPoolExecute( LmiThreadPool *threadPool, LmiThreadPoolUserFunction func, void *data )}
	{parameter: {name: threadPool} {description: The thread pool object to use for execution of the function}}
	{parameter: {name: func} {description: The function that the thread pool will execute}}
	{parameter: {name: data} {description: A pointer that will be passed to the user function executed by the thread pool}}
	{return: LMI_TRUE on success, LMI_FALSE on error queueing the function for execution.}
}
*/
LmiBool LmiThreadPoolExecute( LmiThreadPool *threadPool, LmiThreadPoolUserFunction func, void *data );

/**
{function:
	{name: LmiThreadPoolTryExecute}
	{parent: LmiThreadPool}
	{description: Try to queue a function for execution by the thread pool, but fail if the thread pool's task queue is full.}
	{prototype: LmiBool LmiThreadPoolTryExecute( LmiThreadPool *threadPool, LmiThreadPoolUserFunction func, void *data )}
	{parameter: {name: threadPool} {description: The thread pool object to use for execution of the function}}
	{parameter: {name: func} {description: The function that the thread pool will execute}}
	{parameter: {name: data} {description: A pointer that will be passed to the user function executed by the thread pool}}
	{return: LMI_TRUE on success, LMI_FALSE on queue full or error queueing the function for execution.}
}
*/
LmiBool LmiThreadPoolTryExecute( LmiThreadPool *threadPool, LmiThreadPoolUserFunction func, void *data );


/**
{function:
	{name: LmiThreadPoolGetNumThreads}
	{parent: LmiThreadPool}
	{description: Get the number of threads a thread pool is using.}
	{prototype: LmiSizeT LmiThreadPoolGetNumThreads(LmiThreadPool *threadPool )}
	{parameter: {name: threadPool} {description: The thread pool object to query for the number of threads.}}
	{return: The number of threads the thread pool is using.}
}
*/
LmiSizeT LmiThreadPoolGetNumThreads( LmiThreadPool *threadPool );


/**
{function visibility="private":
	{name: LmiThreadPoolSetNumThreads}
	{parent: LmiThreadPool}
	{description: Set the number of threads for a thread pool to use.}
	{prototype: LmiBool LmiThreadPoolSetNumThreads( LmiThreadPool *threadPool, LmiSizeT numThreads )}
	{parameter: {name: threadPool} {description: The thread pool object whose thread count to set.}}
	{parameter: {name: numThreads} {description: The new number of threads for the pool to use.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: If the number of threads is being decreased, this function blocks until all the excess threads in the pool have been stopped.}
}
*/
LmiBool LmiThreadPoolSetNumThreads( LmiThreadPool *threadPool, LmiSizeT numThreads );

/**
{function visibility="private":
	{name: LmiThreadPoolSetThreadParameters}
	{parent: LmiThreadPool}
	{description: Updates the thread parameters for a thread pool.}
	{prototype: LmiBool LmiThreadPoolSetThreadParameters( LmiThreadPool *threadPool, LmiThreadPriority priority, LmiSizeT stackSize )}
	{parameter: {name: threadPool} {description: The Thread Pool object to construct.}}
	{parameter: {name: priority} {description: The priority with which threads in the pool will run.}}
	{parameter: {name: stackSize} {description:
						A platform dependent stack size.  Setting stack size to 0 
						(recommended) will create the thread with a system dependent 
						default stack size.}}
	{return: LMI_TRUE on success, else LMI_FALSE.}
	{note: These settings only affect new threads that are created after this function is set (through calls to LmiThreadPoolSetNumThreads).
		To change parameters for every thread, set the thread pool size to 0 and then reset it to the new desired size.} 
}
*/
LmiBool LmiThreadPoolSetThreadParameters( LmiThreadPool *threadPool, LmiThreadPriority priority, LmiSizeT stackSize );

/**
{function visibility="private":
	{name: LmiThreadPoolSetCoreAffinity}
	{parent: LmiThreadPool}
	{description: }
	{prototype: LmiBool LmiThreadPoolSetCoreAffinity(LmiThreadPool* threadPool, const LmiBitset* cores)}
	{parameter:
		{name: threadPool}
		{description: Pointer to a thread pool object.}
	}
	{parameter:
		{name: cores}
		{description: The affinity mask for the thread. A thread affinity mask 
		 is a bit vector in which each bit represents a logical processor that 
		 a thread is allowed to run on. A thread affinity mask must be a subset 
		 of the process affinity mask for the containing process of a thread. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool LmiThreadPoolSetCoreAffinity(LmiThreadPool* threadPool, const LmiBitset* cores);

/**
{function visibility="private":
	{name: LmiThreadPoolGetCoreAffinity}
	{parent: LmiThreadPool}
	{description: }
	{prototype: LmiBool LmiThreadPoolGetCoreAffinity(LmiThreadPool* threadPool, LmiBitset* cores)}
	{parameter:
		{name: threadPool}
		{description: Pointer to a thread pool object.}
	}
	{parameter:
		{name: cores}
		{description: On successful return, this would contain the affinity mask for the
		 specified thread.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool LmiThreadPoolGetCoreAffinity(LmiThreadPool* threadPool, LmiBitset* cores);

LMI_END_EXTERN_C

#endif /* LMI_THREADPOOL_H */
