/** {file:
      {name: LmiThread.h}
      {description: Thread object.}
      {copyright:
      	(c) 2005-2015 Vidyo, Inc.,
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
#ifndef LMI_THREAD_H_
#define LMI_THREAD_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiBitset.h>
#include <Lmi/Os/LmiTime.h>

struct LmiThread_;

/**
{type visibility="public":
	{name: LmiThreadPriority}
	{parent: LmiThread}
	{description: 
		A signed integer type containing a system dependent thread priority.
	}
}
*/
typedef LmiInt LmiThreadPriority;

/**
{callback visibility="public":
	{name: LmiThreadFunc}
	{parent: LmiThread}
	{description: 
		A function of this type may be used as the main function associated 
		with an LmiThread object.
	}
	{prototype: void* (*LmiThreadFunc)(LmiThread* t, void* userData)}
	{parameter:
		{name: t}
		{description: A pointer to the thread object.}
	}
	{parameter:
		{name: userData}
		{description: 
			A pointer to user specified memory that was specified at the time
			the thread was constructed.
		}
	}
	{return: 
		A pointer to user specified memory containing the result of the thread 
		functions work.
	}
}
*/
typedef void* (*LmiThreadFunc)(struct LmiThread_* t, void* userData);

/**
{callback visibility="public":
	{name: LmiThreadExitCallback}
	{parent: LmiThread}
	{description: 
		A callback that is called when an LmiThread exits.
	}
	{prototype: void (*LmiThreadExitCallback)(LmiThread* t, void* userData)}
	{parameter:
		{name: t}
		{description: A pointer to the thread object corresponding to the thread that is exiting.}
	}
	{parameter:
		{name: userData}
		{description: 
			A pointer to user specified memory that was specified at the time
			the exit callback was registered.
		}
	}
}
*/
typedef void (*LmiThreadExitCallback)(struct LmiThread_* t, void* userData);

typedef enum {
	LMI_THREAD_STATE_UNBORN,
	LMI_THREAD_STATE_ALIVE,
	LMI_THREAD_STATE_DEAD
} LmiThreadState;

typedef struct {
	char name[32];
	LmiThreadPriority priority;
	LmiSizeT stackSize;
	LmiThreadFunc func;
	void* userData;
	void* returnValue;
	LmiThreadState state;
} LmiThreadBase;

/**
{type visibility="public":
	{name: LmiThread}
	{parent: Os}
	{include: Lmi/Os/LmiThread.h}
	{description: 
		A thread object.
	}
}
*/

 /**
	{type visibility="public":
	  {name: LmiThreadId}
	  {parent: LmiThread}
	  {description: A unique identifier of a thread.}
	}
 */

/* POSIX */
#if defined(LMI_HAVE_PTHREAD_CREATE)
#include <pthread.h>
#include <sched.h>
typedef struct LmiThread_ {
	LmiThreadBase base;
	pthread_attr_t attr;
	pthread_t handle;
} LmiThread;

typedef pthread_t LmiThreadId;

/* Win32 Desktop */
#elif defined(LMI_HAVE__BEGINTHREADEX)
#include <winsock2.h>
#include <process.h>
typedef struct LmiThread_ {
	LmiThreadBase base;
	HANDLE handle;
	unsigned int threadId;
} LmiThread;

typedef DWORD LmiThreadId;

#elif defined(LMI_HAVE_THREAD)
/* C++11 std::thread -- used on Windows Phone 8 */
typedef struct LmiThread_ {
	LmiThreadBase base;
	void* handle;
} LmiThread;

typedef void* LmiThreadId;

#else
#error Unknown Thread implementation
#endif

LMI_BEGIN_EXTERN_C

/* "Static" member functions */
LmiBool LmiThreadInitialize(void);
void LmiThreadUninitialize(void);

/* Internal implementation details */
LmiBool LmiThreadInitializeCommon(void);
void LmiThreadUninitializeCommon(void);
LmiThread* LmiThreadBaseConstruct(LmiThread* x, const char* name, 
  LmiThreadPriority priority, LmiSizeT stackSize, 
  LmiThreadFunc func, void* userData);
void LmiThreadBaseDestruct(LmiThread* x);
const char* LmiThreadBaseGetName(LmiThread* x);
void LmiThreadExecuteExitCallbacks(LmiThread* thisThread);


/**
   {function visibility="public":
     {name: LmiThreadIdGetCurrent}
	 {parent: LmiThreadId}
	 {description: Get an LmiThreadId identifying the current thread.}
	 {prototype: LmiThreadId LmiThreadIdGetCurrent(void)}
	 {return: An LmiThreadId uniquely identifying the current thread.  This
	   value is unique for the lifetime of the thread, but may be re-used
	   once the thread has exited.}
    }
*/
LmiThreadId LmiThreadIdGetCurrent(void);

/**
   {function visibility="public":
     {name: LmiThreadIdIsCurrent}
	 {parent: LmiThreadId}
	 {description: Determine whether an LmiThreadId identifies the current thread.}
	 {prototype: LmiBool LmiThreadIdIsCurrent(const LmiThreadId* t)}
	 {parameter:
	   {name: t}
	   {description: The thread ID to query whether it identifies the current thread.}}
	 {return: LMI_TRUE if the thread identifies the current thread; LMI_FALSE if not.}
   }
*/
LmiBool LmiThreadIdIsCurrent(const LmiThreadId* t);

/**
   {function visibility="public":
     {name: LmiThreadIdEqual}
	 {parent: LmiThreadId}
	 {description: Compare two LmiThreadIds for equality.}
	 {prototype: LmiBool LmiThreadIdEqual(const LmiThreadId* a, const LmiThreadId* b)}
	 {parameter:
	   {name: a}
	   {description: The first thread identifier to compare.}}
	 {parameter:
	   {name: b}
	   {description: The second thread identifier to compare.}}
	 {return: LMI_TRUE if the identifiers refer to the same thread, LMI_FALSE
	   otherwise.}
	 {note: If either thread identifier refers to a thread that has exited,
	   the result is undefined.}
    }
*/
LmiBool LmiThreadIdEqual(const LmiThreadId* a, const LmiThreadId* b);

/**
   {function visibility="private":
     {name: LmiThreadIdHash}
	 {parent: LmiThreadId}
	 {description: Hash an LmiThreadId value (for use in an LmiUnorderedMap).}
	 {prototype: LmiSizeT LmiThreadIdHash(const LmiThreadId* t)}
	 {parameter:
	   {name: t}
	   {description: The thread identifier to hash.}}
	 {return: A hashed value representing the thread id.}
    }
*/
LmiSizeT LmiThreadIdHash(const LmiThreadId* t);

/* Used for hash; private. */
void LmiThreadIdDestruct(LmiThreadId * obj_);
LmiThreadId* LmiThreadIdConstructCopy(LmiThreadId * dst_, const LmiThreadId * src_);
LmiThreadId* LmiThreadIdAssign(LmiThreadId * dst_, const LmiThreadId * src_);
LmiBool LmiThreadIdLess(const LmiThreadId * a_, const LmiThreadId * b);

/**
{function visibility="public":
	{name: LmiThreadSelf}
	{parent: LmiThread}
	{description: 
		{p: Get a pointer to the LmiThread object of the current thread.}
	}
	{prototype: LmiThread* LmiThreadSelf(void)}
	{return: 
		A pointer to the LmiThread object of the current thread or NULL if the
		thread is not associated with an LmiThread object.
	}
}
*/
LmiThread* LmiThreadSelf(void);

/**
{function visibility="public":
	{name: LmiThreadSleep}
	{parent: LmiThread}
	{description: 
		{p: Put the current thread to sleep for a specified number of nanoseconds.}
	}
	{prototype: void LmiThreadSleep(LmiTime ns)}
	{parameter:
		{name: ns}
		{description: The number of nanoseconds to sleep.}
	}
}
*/
void LmiThreadSleep(LmiTime ns);

/**
{function visibility="public":
	{name: LmiThreadSleepUntil}
	{parent: LmiThread}
	{description: 
		{p: Put the current thread to sleep until a specified monotonic time.}
	}
	{prototype: void LmiThreadSleepUntil(LmiTime wakeTime)}
	{parameter:
		{name: wakeTime}
		{description: The time to wake up.}
	}
	{note: If wakeTime is in the past, this function does the equivalent of
		LmiThreadSleep(0); the result of this is Operating System-dependent.}
}
*/
void LmiThreadSleepUntil(LmiTime wakeTime);

/**
{function visibility="public":
	{name: LmiThreadGetPriorityMin}
	{parent: LmiThread}
	{description: 
		{p: 
			Get the minimum thread priority value supported by the platform's 
			scheduler.
		}
		{p: 
			The minimum thread priority value may be numerically higher in 
			value then the maximum thread priority value on systems where
			higher priority values are represented by lower numeric values.  
		}
	}
	{prototype: LmiThreadPriority LmiThreadGetPriorityMin(void)}
	{return: The minimum thread priority value of the platform's scheduler.}
	{note: 
		On WindowsTM operating systems the priority values THREAD_PRIORITY_TIME_IDLE 
		and THREAD_PRIORITY_TIME_CRITICAL are not included in the range formed by 
		[LmiThreadGetPriorityMin(), LmiThreadGetPriorityMax()]. 
	}
}
*/
LmiThreadPriority LmiThreadGetPriorityMin(void);

/**
{function visibility="public":
	{name: LmiThreadGetPriorityMax}
	{parent: LmiThread}
	{description: 
		{p: 
			Get the maximum thread priority value supported by the platform's 
			scheduler.
		}
		{p: 
			The maximum thread priority value may be numerically lower in 
			value then the minimum thread priority value on systems where
			higher priority values are represented by lower numeric values.  
		}
	}
	{prototype: LmiThreadPriority LmiThreadGetPriorityMax(void)}
	{return: The maximum thread priority value of the platform's scheduler.}
	{note: 
		On WindowsTM operating systems the priority values THREAD_PRIORITY_TIME_IDLE 
		and THREAD_PRIORITY_TIME_CRITICAL are not included in the range formed by 
		[LmiThreadGetPriorityMin(), LmiThreadGetPriorityMax()]. 
	}
}
*/
LmiThreadPriority LmiThreadGetPriorityMax(void);


/**
{function visibility="public":
	{name: LmiThreadGetPriorityMedium}
	{parent: LmiThread}
	{description: 
		{p: 
			Get an appropriate medium-priority value for the platform's 
			scheduler.
		}
		{p: 
			The medium thread priority will be a value roughly intermediate in
			value between the maximum and minimum thread priorities, as
			returned by LmiThreadGetPriorityMax and LmiThreadGetPriorityMin, respectively.
		}
	}
	{prototype: LmiThreadPriority LmiThreadGetPriorityMedium(void)}
	{return: The maximum thread priority value of the platform's scheduler.}
}
*/
LmiThreadPriority LmiThreadGetPriorityMedium(void);

/**
{function visibility="public":
	{name: LmiThreadAddGlobalExitCallback}
	{parent: LmiThread}
	{description: Add a global exit callback to be called whenever any LmiThread exits.}
	{prototype: LmiBool LmiThreadAddGlobalExitCallback(LmiThreadExitCallback exitCb, void* userData)}
	{parameter:
		{name: exitCb}
		{description: The global exit callback to be called.}}
	{parameter:
		{name: userData}
		{description: A user data pointer that will be passed to the exit callback whenever it is called.  May be NULL.}}
	{return: LMI_TRUE if the exit callback function was successfully added or was already present; LMI_FALSE if there were insufficient system resources.}
	{note: This function must not be called from within an executing exit callback.  In most cases it should be called from system initialization.}
	{note: If an instance of this callback and user data pointer are already present in the list of global exit callbacks, the callback will not be added again.}
}
*/
LmiBool LmiThreadAddGlobalExitCallback(LmiThreadExitCallback exitCb, void* userData);


/**
{function visibility="public":
	{name: LmiThreadRemoveGlobalExitCallback}
	{parent: LmiThread}
	{description: Remove a global exit callback from the list of callbacks to be called whenever any LmiThread exits.}
	{prototype: LmiBool LmiThreadRemoveGlobalExitCallback(LmiThreadExitCallback exitCb, void* userData)}
	{parameter:
		{name: exitCb}
		{description: The exit callback to remove.}}
	{parameter:
		{name: userData}
		{description: The user data pointer that was passed when the exit callback was added.}}
	{return: LMI_TRUE if a global exit callback with the given user data pointer was found and was removed; LMI_FALSE if there was no such global exit callback and user data pointer registered.}
	{note: This function must not be called from within an executing exit callback.  In most cases it should be called from system uninitialization.}	
}
*/
LmiBool LmiThreadRemoveGlobalExitCallback(LmiThreadExitCallback exitCb, void* userData);

/* Member functions */

/**
{function visibility="public":
	{name: LmiThreadConstruct}
	{parent: LmiThread}
	{description: 
		{p: Construct a thread object.}
	}
	{prototype: LmiThread* LmiThreadConstruct(LmiThread* x, const char* name,
	  LmiThreadPriority priority, LmiSizeT stackSize, LmiThreadFunc func,
	  void* userData)}
	{parameter:
		{name: x}
		{description: A pointer to the thread object to construct.}
	}
	{parameter:
		{name: name}
		{description: A C string containing the thread\'s name.}
	}
	{parameter:
		{name: priority}
		{description: 
			A platform dependent priority value, the range of which can be 
			determined by calling LmiThreadGetPriorityMin and LmiThreadGetPriorityMax. 
			On Windows operating systems the priority values THREAD_PRIORITY_TIME_IDLE 
			and THREAD_PRIORITY_TIME_CRITICAL have been remapped such that the range
			of priority values is contiguous.  So applications should use 
			LmiThreadGetPriorityMin() and LmiThreadGetPriorityMax() in place of these 
			values when constructing an LmiThread.
		}
	}
	{parameter:
		{name: stackSize}
		{description: 
			A platform dependent stack size.  Setting stack size to 0 
			(recommended) will create the thread with a system dependent 
			default stack size.
		}
	}
	{parameter:
		{name: func}
		{description: 
			A function pointer containing the code to execute in the created thread.
		}
	}
	{parameter:
		{name: userData}
		{description: 
			A pointer to user specified memory that will be passed to the created 
			threads function pointer when the thread is started.
		}
	}
	{return: A pointer to the thread object, or NULL on failure.}
}
*/
LmiThread* LmiThreadConstruct(LmiThread* x, const char* name, 
  LmiThreadPriority priority, LmiSizeT stackSize, 
  LmiThreadFunc func, void* userData);

/**
{function visibility="public":
	{name: LmiThreadDestruct}
	{parent: LmiThread}
	{description: 
		{p: Destruct a thread object.}
	}
	{prototype: void LmiThreadDestruct(LmiThread* x)}
	{parameter:
		{name: x}
		{description: A pointer to the thread object to destruct.}
	}
}
*/
void LmiThreadDestruct(LmiThread* x);

/**
{function visibility="public":
	{name: LmiThreadStart}
	{parent: LmiThread}
	{description: 
		{p: Start a thread object.}
	}
	{prototype: LmiBool LmiThreadStart(LmiThread* x)}
	{parameter:
		{name: x}
		{description: A pointer to the thread object.}
	}
	{return: LMI_TRUE if the thread was started or LMI_FALSE if it was not.}
	{note: Only newly constructed threads can be started.  It is not possible
	to restart threads that have completed.}
	{note: All started threads must have LmiThreadJoin called on them.}
}
*/
LmiBool LmiThreadStart(LmiThread* x);

/**
{function visibility="public":
	{name: LmiThreadJoin}
	{parent: LmiThread}
	{description: 
		{p: Wait for a thread object to stop.}
	}
	{prototype: void* LmiThreadJoin(LmiThread* x)}
	{parameter:
		{name: x}
		{description: A pointer to the thread object.}
	}
	{return: The return value of the thread's function.}
	{note: Only one thread may "join" another thread.}
	{note: Calling this function on the current thread will cause the thread to deadlock.}
	{note: This function can not be executed while a call to LmiThreadStart is in progress.}
}
*/
void* LmiThreadJoin(LmiThread* x);

/**
{function visibility="public":
	{name: LmiThreadGetName}
	{parent: LmiThread}
	{description: 
		{p: Get the name of a thread object.}
	}
	{prototype: const char* LmiThreadGetName(LmiThread* x)}
	{parameter:
		{name: x}
		{description: A pointer to the thread object.}
	}
	{return: A C string containing the name of the thread.}
}
*/
const char* LmiThreadGetName(LmiThread* x);

/**
{function visibility="private":
	{name: LmiThreadSetCoreAffinity}
	{parent: LmiThread}
	{description: Sets a processor affinity mask for the specified thread.}
	{prototype: LmiBool LmiThreadSetCoreAffinity(LmiThread* x, const LmiBitset* c)}
	{parameter:
		{name: x}
		{description: A pointer to the thread object.}
	}
	{parameter:
		{name: c}
		{description: The affinity mask for the thread. A thread affinity mask 
		 is a bit vector in which each bit represents a logical processor that 
		 a thread is allowed to run on. A thread affinity mask must be a subset 
		 of the process affinity mask for the containing process of a thread. }
	}
	{return: LMI_TRUE if succeeded or LMI_FALSE if failed or not supported.}
	{note: Not supported on Mac OS X. When called to set the affinity on an 
	 unsupported processor core, the behavior is undefined. Care must be taken
	 by using LmiProcessor APIs to limit the affinity mask to those cores that
	 are actually available.}
}
*/
LmiBool LmiThreadSetCoreAffinity(LmiThread* x, const LmiBitset* c);

/**
{function visibility="private":
	{name: LmiThreadGetCoreAffinity}
	{parent: LmiThread}
	{description: Gets the current processor affinity mask for the specified thread.}
	{prototype: LmiBool LmiThreadGetCoreAffinity(LmiThread* x, LmiBitset* c)}
	{parameter:
		{name: x}
		{description: A pointer to the thread object.}
	}
	{parameter:
		{name: c}
		{description: On successful return, this would contain the affinity mask for the
		 specified thread.}
	}
	{return: LMI_TRUE if succeeded or LMI_FALSE if failed or not supported.}
	{note: Not supported on Mac OS X.}
}
*/
LmiBool LmiThreadGetCoreAffinity(LmiThread* x, LmiBitset* c);

LMI_END_EXTERN_C

#endif /* LMI_THREAD_H_ */
