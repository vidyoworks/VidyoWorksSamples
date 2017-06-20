/**
{file:
	{name: LmiQueue.h}
	{description: Queue}
	{copyright:
		(c) 2006-2012 Vidyo, Inc.,
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
#ifndef LMI_QUEUE_H
#define LMI_QUEUE_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Os/LmiCondition.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="private":
	{name: LmiQueuePopStatus}
	{parent: LmiQueue}
	{include: Lmi/Os/LmiQueue.h}
	{description: Provides the status of an LmiQueuePop or LmiQueueTryPop operation.}
	{value: {name: LMI_QUEUEPOPSTATUS_OK} {description: The pop was successful. The popped item has
		been written into the item variable.}}
	{value: {name: LMI_QUEUEPOPSTATUS_Stopped} {description: The queue has been stopped, but there were items
		remaining in the queue. The next item in the queue has been popped and written into the item variable.}}
	{value: {name: LMI_QUEUEPOPSTATUS_Empty} {description: LmiQueueTryPop was called, but the queue was empty (and
		not yet stopped). The item variable will not be set in this case. Note: this code will not be returned by
		LmiQueuePop, which blocks until either an item is pushed or the queue is stopped.}}
	{value: {name: LMI_QUEUEPOPSTATUS_StoppedAndEmpty} {description: The queue has been stopped and there 
		are no items remaining in the queue. The item variable will not be set in this case.}}
}
*/
typedef enum
{
	LMI_QUEUEPOPSTATUS_OK,
	LMI_QUEUEPOPSTATUS_Stopped,
	LMI_QUEUEPOPSTATUS_Empty,
	LMI_QUEUEPOPSTATUS_StoppedAndEmpty
} LmiQueuePopStatus;

/**
{function visibility="private":
	{name: LmiQueuePopStatusGetString}
	{parent: LmiQueuePopStatus}
	{description: Get a string representation of a queue pop status.}
	{prototype: const char* LmiQueuePopStatusGetString(LmiQueuePopStatus status)}
	{parameter: {name: status} {description: The status}}
	{return: A string description of the status.}
}
*/
const char* LmiQueuePopStatusGetString(LmiQueuePopStatus status);

/**
{type visibility="private":
	{name: LmiQueue}
	{parent: Os}
	{include: Lmi/Os/LmiQueue.h}
	{description: Queue}
}
*/
typedef struct
{
	LmiMonitor monitor;
	LmiCondition notEmpty;
	LmiCondition notFull;
	void **data;
	void **dataEnd;
	void **begin;
	void **end;
	LmiBool stopped;
	LmiAllocator *alloc;
} LmiQueue;

/**
{function visibility="private":
	{name: LmiQueueConstruct}
	{parent: LmiQueue}
	{description: Constructs a queue object.}
	{prototype: LmiQueue* LmiQueueConstruct(LmiQueue* queue, LmiSizeT capacity, LmiAllocator* alloc)}
	{parameter: {name: queue} {description: The queue object to construct.}}
	{parameter: {name: capacity} {description: The number of items that the queue can hold at one time.}}
	{parameter: {name: alloc} {description: An allocator used to allocate the queue. One allocation will
		be done of size sizeof(void *) * (capacity + 1).}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiQueue *LmiQueueConstruct(LmiQueue *queue, LmiSizeT capacity, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: LmiQueueDestruct}
	{parent: LmiQueue}
	{description: Destructs a queue object.}
	{prototype: void LmiQueueDestruct(LmiQueue* queue)}
	{parameter: {name: queue} {description: The queue object to destruct.}}
}
*/
void LmiQueueDestruct(LmiQueue *queue);

/**
{function visibility="private":
	{name: LmiQueuePush}
	{parent: LmiQueue}
	{description: Pushes an item onto a queue. The calling thread will block until there is space available in the 
		queue or the queue is stopped.}
	{prototype: LmiBool LmiQueuePush(LmiQueue* queue, void* item)}
	{parameter: {name: queue} {description: The queue object.}}
	{parameter: {name: item} {description: The item to push.}}
	{return: LMI_TRUE if the item was successfully pushed on the queue, LMI_FALSE if the item was not pushed because
		the queue has been stopped.}
}
*/
LmiBool LmiQueuePush(LmiQueue *queue, void *item);

/**
{function visibility="private":
	{name: LmiQueueTryPush}
	{parent: LmiQueue}
	{description: Tries to pushes an item onto a queue, if there is room and the queue has not been stopped.}
	{prototype: LmiBool LmiQueueTryPush(LmiQueue* queue, void* item)}
	{parameter: {name: queue} {description: The queue object.}}
	{parameter: {name: item} {description: The item to push.}}
	{return: LMI_TRUE if the item was successfully pushed on the queue, LMI_FALSE if the item was not pushed because
		the queue is full or has been stopped.}
}
*/
LmiBool LmiQueueTryPush(LmiQueue *queue, void *item);

/**
{function visibility="private":
	{name: LmiQueuePop}
	{parent: LmiQueue}
	{description: Pops an item from a queue. The calling thread will block until there is an item available in the 
		queue or the queue is stopped.}
	{prototype: LmiQueuePopStatus LmiQueuePop(LmiQueue* queue, void** item)}
	{parameter: {name: queue} {description: The queue object.}}
	{parameter: {name: item} {description: The popped item will be written to this variable.}}
	{return: Returns LMI_QUEUEPOPSTATUS_OK if an item was popped and the queue has not been stopped.
		Returns LMI_QUEUEPOPSTATUS_Stopped if an item was popped but the queue has been stopped.
		Returns LMI_QUEUEPOPSTATUS_StoppedAndEmpty if the queue has been stopped and there are no
		items remaining in the queue. If the return value is LMI_QUEUEPOPSTATUS_StoppedAndEmpty, 
		the item variable will not be set.}
}
*/
LmiQueuePopStatus LmiQueuePop(LmiQueue *queue, void **item);

/**
{function visibility="private":
	{name: LmiQueuePeek}
	{parent: LmiQueue}
	{description: Returns the item at the head of a queue without popping it. Does not block if the
		queue is empty.}
	{prototype: LmiBool LmiQueuePeek(LmiQueue* queue, void** item)}
	{parameter: {name: queue} {description: The queue object.}}
	{parameter: {name: item} {description: The item at the head of the queue will be written to this variable.}}
	{return: Returns LMI_TRUE if there was an item in the queue. Returns LMI_FALSE if the
		queue was empty. The item variable will not be set in this case.}
}
*/
LmiBool LmiQueuePeek(LmiQueue *queue, void **item);

/**
{function visibility="private":
	{name: LmiQueueTryPop}
	{parent: LmiQueue}
	{description: Pops the item at the head of a queue if there are indeed items in the queue. Does not block if the
		queue is empty.}
	{prototype: LmiQueuePopStatus LmiQueueTryPop(LmiQueue* queue, void** item)}
	{parameter: {name: queue} {description: The queue object.}}
	{parameter: {name: item} {description: The popped item will be written to this variable.}}
	{return: Returns LMI_QUEUEPOPSTATUS_OK if an item was popped and the queue has not been stopped.
		Returns LMI_QUEUEPOPSTATUS_Stopped if an item was popped but the queue has been stopped.
		Returns LMI_QUEUEPOPSTATUS_Empty if the queue is empty but has not been stopped.
		Returns LMI_QUEUEPOPSTATUS_StoppedAndEmpty if the queue has been stopped and there are no
		items remaining in the queue. If the return value is LMI_QUEUEPOPSTATUS_Empty or LMI_QUEUEPOPSTATUS_StoppedAndEmpty,
		the item variable will not be set.}
}
*/
LmiQueuePopStatus LmiQueueTryPop(LmiQueue *queue, void **item);

/**
{function visibility="private":
	{name: LmiQueueStop}
	{parent: LmiQueue}
	{description: Causes all calls to LmiQueuePush and LmiQueuePop (on this queue object) to return immediately.
		Any pending or future calls to LmiQueuePush will fail and return LMI_FALSE. Any pending or future calls to
		LmiQueuePop will return LMI_QUEUEPOPSTATUS_Stopped until the queue is emptied. Thereafter calls to
		LmiQueuePop will return LMI_QUEUEPOPSTATUS_StoppedAndEmpty.}
	{prototype: void LmiQueueStop(LmiQueue* queue)}
	{parameter: {name: queue} {description: The queue object.}}
}
*/
void LmiQueueStop(LmiQueue *queue);

/**
{function visibility="private":
	{name: LmiQueueSize}
	{parent: LmiQueue}
	{description: Returns the number of items currently in a queue.}
	{prototype: LmiSizeT LmiQueueSize(LmiQueue* queue)}
	{parameter: {name: queue} {description: The queue object.}}
	{return: The number of items in the queue.}
}
*/
LmiSizeT LmiQueueSize(LmiQueue *queue);

/**
{function visibility="private":
	{name: LmiQueueCapacity}
	{parent: LmiQueue}
	{description: Returns the maximum number of items that a queue can hold at one time.}
	{prototype: LmiSizeT LmiQueueCapacity(LmiQueue* queue)}
	{parameter: {name: queue} {description: The queue object.}}
	{return: The number of items the queue can hold.}
}
*/
LmiSizeT LmiQueueCapacity(LmiQueue *queue);

/**
{function visibility="private":
	{name: LmiQueueIsFull}
	{parent: LmiQueue}
	{description: Checks whether the queue is full.}
	{prototype: LmiBool LmiQueueIsFull(LmiQueue* queue)}
	{parameter: {name: queue} {description: The queue object.}}
	{return: LMI_TRUE if the queue is full, LMI_FALSE otherwise.}
}
*/
LmiBool LmiQueueIsFull(LmiQueue *queue);

/**
{function visibility="private":
	{name: LmiQueueIsStopped}
	{parent: LmiQueue}
	{description: Checks whether the queue has been stopped.}
	{prototype: LmiBool LmiQueueIsStopped(LmiQueue* queue)}
	{parameter: {name: queue} {description: The queue object.}}
	{return: LMI_TRUE if the queue has been stopped, LMI_FALSE otherwise.}
}
*/
LmiBool LmiQueueIsStopped(LmiQueue *queue);

/**
{function visibility="private":
	{name: LmiQueueInitialize}
	{parent: LmiQueue}
	{description: Initialize the queue package.}
	{prototype: LmiBool LmiQueueInitialize(void)}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool LmiQueueInitialize(void);

/**
{function visibility="private":
	{name: LmiQueueUninitialize}
	{parent: LmiQueue}
	{description: Uninitialize the queue package.}
	{prototype: void LmiQueueUninitialize(void)}
}
*/
void LmiQueueUninitialize(void);

/* Low-level (no logging) queue interface */
/* you should use the high-level queue interface unless you have a good reason
   to use the low level interface (such as the implementation of a log listener) */
LmiBool LmiQueuePush_(LmiQueue *queue, void *item);
LmiBool LmiQueueTryPush_(LmiQueue *queue, void *item);
LmiQueuePopStatus LmiQueuePop_(LmiQueue *queue, void **item);
LmiBool LmiQueuePeek_(LmiQueue *queue, void **item);
LmiQueuePopStatus LmiQueueTryPop_(LmiQueue *queue, void **item);
void LmiQueueStop_(LmiQueue *queue);



/* LmiFifo */

/* TODO:
 - Rename LmiFifo to LmiQueue after replacing LmiQueue with LmiPointerQueue
*/

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiDeque.h>
#include <Lmi/Os/LmiCondition.h>

/**
 {type visibility="private":
	{name: LmiFifoPopStatus}
	{parent: LmiFifo}
	{include: Lmi/Os/LmiQueue.h}
	{description: Provides the status of an LmiFifoPop or LmiFifoTryPop operation.}
	{value: {name: LMI_FIFOPOPSTATUS_OK} {description: The pop was successful. The popped item has
 been written into the item variable.}}
	{value: {name: LMI_FIFOPOPSTATUS_Stopped} {description: The queue has been stopped, but there were items
 remaining in the queue. The next item in the queue has been popped and written into the item variable.}}
	{value: {name: LMI_FIFOPOPSTATUS_Empty} {description: LmiQueueTryPop was called, but the queue was empty (and
 not yet stopped). The item variable will not be set in this case. Note: this code will not be returned by
 LmiQueuePop, which blocks until either an item is pushed or the queue is stopped.}}
	{value: {name: LMI_FIFOPOPSTATUS_StoppedAndEmpty} {description: The queue has been stopped and there
 are no items remaining in the queue. The item variable will not be set in this case.}}
 }
 */
typedef enum
{
	LMI_FIFOPOPSTATUS_OK,
	LMI_FIFOPOPSTATUS_Stopped,
	LMI_FIFOPOPSTATUS_Empty,
	LMI_FIFOPOPSTATUS_StoppedAndEmpty
} LmiFifoPopStatus;

/**
 {function visibility="private":
	{name: LmiFifoPopStatusGetString}
	{parent: LmiFifoPopStatus}
	{description: Get a string representation of a queue pop status.}
	{prototype: const char* LmiFifoPopStatusGetString(LmiFifoPopStatus status)}
	{parameter: {name: status} {description: The status}}
	{return: A string description of the status.}
 }
 */
const char* LmiFifoPopStatusGetString(LmiFifoPopStatus status);

/* Name mangling */
#define LmiFifo(T_)								LmiTemplate1(LmiFifo, T_)
#define LmiFifoSizeType(T_)						LmiClassType(LmiFifo(T_), SizeType)
#define LmiFifoIsFull_(T_)						LmiClassFunc(LmiFifo(T_), IsFull_)
#define LmiFifoPush_(T_)						LmiClassFunc(LmiFifo(T_), Push_)
#define LmiFifoTryPush_(T_)						LmiClassFunc(LmiFifo(T_), TryPush_)
#define LmiFifoPopNoWait_(T_)					LmiClassFunc(LmiFifo(T_), PopNoWait_)
#define LmiFifoPop_(T_)							LmiClassFunc(LmiFifo(T_), Pop_)
#define LmiFifoTryPop_(T_)						LmiClassFunc(LmiFifo(T_), TryPop_)
#define LmiFifoPeek_(T_)						LmiClassFunc(LmiFifo(T_), Peek_)
#define LmiFifoStop_(T_)						LmiClassFunc(LmiFifo(T_), Stop_)
#define LmiFifoDestruct(T_)						LmiClassFunc(LmiFifo(T_), Destruct)
#define LmiFifoConstruct(T_)					LmiClassFunc(LmiFifo(T_), Construct)
#define LmiFifoPush(T_)							LmiClassFunc(LmiFifo(T_), Push)
#define LmiFifoTryPush(T_)						LmiClassFunc(LmiFifo(T_), TryPush)
#define LmiFifoPop(T_)							LmiClassFunc(LmiFifo(T_), Pop)
#define LmiFifoPeek(T_)							LmiClassFunc(LmiFifo(T_), Peek)
#define LmiFifoTryPop(T_)						LmiClassFunc(LmiFifo(T_), TryPop)
#define LmiFifoStop(T_)							LmiClassFunc(LmiFifo(T_), Stop)
#define LmiFifoSize(T_)							LmiClassFunc(LmiFifo(T_), Size)
#define LmiFifoCapacity(T_)						LmiClassFunc(LmiFifo(T_), Capacity)
#define LmiFifoIsFull(T_)						LmiClassFunc(LmiFifo(T_), IsFull)
#define LmiFifoIsStopped(T_)					LmiClassFunc(LmiFifo(T_), IsStopped)

/**
 {type visibility="private":
	{name: LmiFifoSizeType}
	{parent: LmiFifo}
	{include: Lmi/Os/LmiQueue.h}
	{description: The size type of an LmiFifo.}
 	{template-prototype: LmiFifoSizeType(T_)}
 	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
 }
 */

/**
 {type visibility="private":
	{name: LmiFifo}
	{parent: Os}
	{include: Lmi/Os/LmiQueue.h}
	{description: An inter-thread commincation mechanism implementing a FIFO queue discipline.}
 	{template-prototype: LmiFifo(T_)}
 	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
 }
 */
#define Declare_LmiFifo_Types(T_) \
Declare_LmiDeque(T_) \
typedef LmiSizeT LmiFifoSizeType(T_); \
typedef struct { \
	LmiMonitor monitor; \
	LmiCondition notEmpty; \
	LmiCondition notFull; \
	LmiDeque(T_) deque; \
	LmiFifoSizeType(T_) capacity; \
	LmiBool stopped; \
} LmiFifo(T_);

/**
 {function visibility="private":
	{name: LmiFifoConstruct}
	{parent: LmiFifo}
	{description: Constructs a queue object.}
	{prototype: LmiFifo(T_)* LmiFifoConstruct(T_)(LmiFifo(T_)* x, LmiFifoSizeType(T_) capacity, LmiAllocator* alloc)}
	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object to construct.}}
	{parameter: {name: capacity} {description: The maximum number of items that the queue can hold at one time.}}
	{parameter: {name: alloc} {description: An allocator used to allocate the queue.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
 }
 */
#define Declare_LmiFifoConstruct(T_) \
LmiFifo(T_) *LmiFifoConstruct(T_)(LmiFifo(T_)* x, LmiFifoSizeType(T_) capacity, LmiAllocator *alloc);

/**
 {function visibility="private":
	{name: LmiFifoDestruct}
	{parent: LmiFifo}
	{description: Destructs a queue object.}
	{prototype: void LmiFifoDestruct(T_)(LmiFifo(T_)* x)}
	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object to destruct.}}
 }
 */
#define Declare_LmiFifoDestruct(T_) \
void LmiFifoDestruct(T_)(LmiFifo(T_)* x);

/**
 {function visibility="private":
	{name: LmiFifoPush}
	{parent: LmiFifo}
	{description: Pushes an item onto a queue. The calling thread will block until there is space available in the
 queue or the queue is stopped.}
	{prototype: LmiBool LmiFifoPush(T_)(LmiFifo(T_)* x, const T_* item)}
 	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{parameter: {name: item} {description: The item to push.}}
	{return: LMI_TRUE if the item was successfully pushed on the queue, LMI_FALSE if the item was not pushed because
 the queue has been stopped.}
 }
 */
#define Declare_LmiFifoPush(T_) \
LmiBool LmiFifoPush(T_)(LmiFifo(T_)* x, const T_* item);

/**
 {function visibility="private":
	{name: LmiFifoTryPush}
	{parent: LmiFifo}
	{description: Tries to push an item onto a queue, if there is room and the queue has not been stopped.}
	{prototype: LmiBool LmiFifoTryPush(T_)(LmiFifo(T_)* x, const T_* item)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{parameter: {name: item} {description: The item to push.}}
	{return: LMI_TRUE if the item was successfully pushed on the queue, LMI_FALSE if the item was not pushed because
 the queue is full or has been stopped.}
 }
 */
#define Declare_LmiFifoTryPush(T_) \
LmiBool LmiFifoTryPush(T_)(LmiFifo(T_)* x, const T_* item);

/**
 {function visibility="private":
	{name: LmiFifoPop}
	{parent: LmiFifo}
	{description: Pops an item from a queue. The calling thread will block until there is an item available in the
 queue or the queue is stopped.}
	{prototype: LmiFifoPopStatus LmiFifoPop(T_)(LmiFifo(T_)* x, T_* item)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{parameter: {name: item} {description: The popped item will be written to this variable.}}
	{return: Returns LMI_FIFOPOPSTATUS_OK if an item was popped and the queue has not been stopped.
 Returns LMI_FIFOPOPSTATUS_Stopped if an item was popped but the queue has been stopped.
 Returns LMI_FIFOPOPSTATUS_StoppedAndEmpty if the queue has been stopped and there are no
 items remaining in the queue. If the return value is LMI_FIFOPOPSTATUS_StoppedAndEmpty,
 the item variable will not be set.}
 }
 */
#define Declare_LmiFifoPop(T_) \
LmiFifoPopStatus LmiFifoPop(T_)(LmiFifo(T_)* x,  T_* item);

/**
 {function visibility="private":
	{name: LmiFifoTryPop}
	{parent: LmiFifo}
	{description: Pops the item at the head of a queue if there are indeed items in the queue. Does not block if the
 queue is empty.}
	{prototype: LmiFifoPopStatus LmiFifoTryPop(T_)(LmiFifo(T_)* x, T_* item)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{parameter: {name: item} {description: The popped item will be written to this variable.}}
	{return: Returns LMI_FIFOPOPSTATUS_OK if an item was popped and the queue has not been stopped.
 Returns LMI_FIFOPOPSTATUS_Stopped if an item was popped but the queue has been stopped.
 Returns LMI_FIFOPOPSTATUS_Empty if the queue is empty but has not been stopped.
 Returns LMI_FIFOPOPSTATUS_StoppedAndEmpty if the queue has been stopped and there are no
 items remaining in the queue. If the return value is LMI_FIFOPOPSTATUS_Empty or LMI_FIFOPOPSTATUS_StoppedAndEmpty,
 the item variable will not be set.}
 }
 */
#define Declare_LmiFifoTryPop(T_) \
LmiFifoPopStatus LmiFifoTryPop(T_)(LmiFifo(T_)* x, T_* item);

/**
 {function visibility="private":
	{name: LmiFifoPeek}
	{parent: LmiFifo}
	{description: Returns the item at the head of a queue without popping it. Does not block if the
 queue is empty.}
	{prototype: LmiBool LmiFifoPeek(T_)(LmiFifo(T_)* x, T_* item)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{parameter: {name: item} {description: The item at the head of the queue will be written to this variable.}}
	{return: Returns LMI_TRUE if there was an item in the queue. Returns LMI_FALSE if the
 queue was empty. The item variable will not be set in this case.}
 }
 */
#define Declare_LmiFifoPeek(T_) \
LmiBool LmiFifoPeek(T_)(LmiFifo(T_)* x, T_* item);

/**
 {function visibility="private":
	{name: LmiFifoStop}
	{parent: LmiFifo}
	{description: Causes all calls to LmiFifoPush and LmiFifoPop (on this queue object) to return immediately.
 Any pending or future calls to LmiFifoPush will fail and return LMI_FALSE. Any pending or future calls to
 LmiFifoPop will return LMI_FIFOPOPSTATUS_Stopped until the queue is emptied. Thereafter calls to
 LmiFifoPop will return LMI_FIFOPOPSTATUS_StoppedAndEmpty.}
	{prototype: void LmiFifoStop(T_)(LmiFifo(T_)* x)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
 }
 */
#define Declare_LmiFifoStop(T_) \
void LmiFifoStop(T_)(LmiFifo(T_)* x);

/**
 {function visibility="private":
	{name: LmiFifoSize}
	{parent: LmiFifo}
	{description: Returns the number of items currently in a queue.}
	{prototype: LmiFifoSizeType(T_) LmiFifoSize(T_)(const LmiFifo(T_)* x)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{return: The number of items in the queue.}
 }
 */
#define Declare_LmiFifoSize(T_) \
LmiFifoSizeType(T_) LmiFifoSize(T_)(const LmiFifo(T_)* x);

/**
 {function visibility="private":
	{name: LmiFifoCapacity}
	{parent: LmiFifo}
	{description: Returns the maximum number of items that a queue can hold at one time.}
	{prototype: LmiFifoSizeType(T_) LmiFifoCapacity(T_)(const LmiFifo(T_)* x)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{return: The number of items the queue can hold.}
 }
 */
#define Declare_LmiFifoCapacity(T_) \
LmiFifoSizeType(T_) LmiFifoCapacity(T_)(const LmiFifo(T_)* x);

/**
 {function visibility="private":
	{name: LmiFifoIsFull}
	{parent: LmiFifo}
	{description: Checks whether the queue is full.}
	{prototype: LmiBool LmiFifoIsFull(T_)(const LmiFifo(T_)* x)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{return: LMI_TRUE if the queue is full, LMI_FALSE otherwise.}
 }
 */
#define Declare_LmiFifoIsFull(T_) \
LmiBool LmiFifoIsFull(T_)(const LmiFifo(T_)* x);

/**
 {function visibility="private":
	{name: LmiFifoIsStopped}
	{parent: LmiFifo}
	{description: Checks whether the queue has been stopped.}
	{prototype: LmiBool LmiFifoIsStopped(T_)(const LmiFifo(T_)* x)}
  	{template-parameter: {name: T_} {description: The type of the items stored in the queue.}}
	{parameter: {name: x} {description: The queue object.}}
	{return: LMI_TRUE if the queue has been stopped, LMI_FALSE otherwise.}
 }
 */
#define Declare_LmiFifoIsStopped(T_) \
LmiBool LmiFifoIsStopped(T_)(const LmiFifo(T_)* x);

#define Declare_LmiFifo(T_) \
	Declare_LmiFifo_Types(T_) \
	Declare_LmiFifoConstruct(T_) \
	Declare_LmiFifoDestruct(T_) \
	Declare_LmiFifoPush(T_) \
	Declare_LmiFifoTryPush(T_) \
	Declare_LmiFifoPop(T_) \
	Declare_LmiFifoTryPop(T_) \
	Declare_LmiFifoPeek(T_) \
	Declare_LmiFifoStop(T_) \
	Declare_LmiFifoSize(T_) \
	Declare_LmiFifoCapacity(T_) \
	Declare_LmiFifoIsFull(T_) \
	Declare_LmiFifoIsStopped(T_)

extern LmiLogCategory lmiLogFifo_;

#define Define_LmiFifoIsFull_(T_) \
static LmiBool LmiFifoIsFull_(T_)(const LmiFifo(T_)* x) { \
	return (LmiDequeSize(T_)(&x->deque) == x->capacity); \
}

#define Define_LmiFifoPopNoWait_(T_) \
static LmiFifoPopStatus LmiFifoPopNoWait_(T_)(LmiFifo(T_)* x, T_* item) { \
	LmiFifoPopStatus r = LMI_FIFOPOPSTATUS_Stopped; \
	LmiAssert(!LmiDequeEmpty(T_)(&x->deque)); \
	LmiAssign(T_)(item, LmiDequeFront(T_)(&x->deque));	/* TODO: Error handling */ \
	LmiDequePopFront(T_)(&x->deque); \
	if (!x->stopped) { \
		LmiConditionNotify(&x->notFull); \
		return LMI_FIFOPOPSTATUS_OK; \
	} \
	return r; \
}

#define Define_LmiFifoConstruct(T_) \
LmiFifo(T_) *LmiFifoConstruct(T_)(LmiFifo(T_)* x, LmiFifoSizeType(T_) capacity, LmiAllocator *alloc) { \
	x->stopped = LMI_FALSE; \
	x->capacity = capacity; \
	if (LmiMonitorConstruct(&x->monitor) == NULL) \
		goto FAIL0; \
	if (LmiConditionConstruct(&x->notEmpty, &x->monitor) == NULL) \
		goto FAIL1; \
	if (LmiConditionConstruct(&x->notFull, &x->monitor) == NULL) \
		goto FAIL2; \
	if (LmiDequeConstruct(T_)(&x->deque, alloc) == NULL) \
		goto FAIL3; \
	if (!LmiDequeReserve(T_)(&x->deque, x->capacity)) \
		goto FAIL4; \
	return x; \
FAIL4: LmiDequeDestruct(T_)(&x->deque); \
FAIL3: LmiConditionDestruct(&x->notFull); \
FAIL2: LmiConditionDestruct(&x->notEmpty); \
FAIL1: LmiMonitorDestruct(&x->monitor); \
FAIL0: return NULL; \
}

#define Define_LmiFifoDestruct(T_) \
void LmiFifoDestruct(T_)(LmiFifo(T_)* x) { \
	LmiDequeDestruct(T_)(&x->deque); \
	LmiConditionDestruct(&x->notFull); \
	LmiConditionDestruct(&x->notEmpty); \
	LmiMonitorDestruct(&x->monitor); \
}

#define Define_LmiFifoPush(T_) \
static LmiBool LmiFifoPush_(T_)(LmiFifo(T_)* x, const T_* item) { \
	LmiBool r = LMI_FALSE; \
	LmiMonitorLock(&x->monitor); \
	while (!x->stopped && LmiFifoIsFull_(T_)(x)) \
		LmiConditionWait(&x->notFull); \
	if (!x->stopped) { \
		LmiDequePushBack(T_)(&x->deque, item); \
		LmiConditionNotify(&x->notEmpty); \
		r = LMI_TRUE; \
	} \
	LmiMonitorUnlock(&x->monitor); \
	return r; \
} \
LmiBool LmiFifoPush(T_)(LmiFifo(T_)* x, const T_* item) { \
	LmiBool r = LmiFifoPush_(T_)(x, item); \
	LmiLogDebugFormatted(lmiLogFifo_, "Pushing item %p onto queue %p: %s", item, x, (r) ? "success" : "error"); \
	return r; \
}

#define Define_LmiFifoTryPush(T_) \
static LmiBool LmiFifoTryPush_(T_)(LmiFifo(T_)* x, const T_* item) { \
	LmiBool r = LMI_FALSE; \
	LmiMonitorLock(&x->monitor); \
	if (!x->stopped) { \
		if (!LmiFifoIsFull_(T_)(x)) { \
			LmiDequePushBack(T_)(&x->deque, item); \
			LmiConditionNotify(&x->notEmpty); \
			r = LMI_TRUE; \
		} \
	} \
	LmiMonitorUnlock(&x->monitor); \
	return r; \
} \
LmiBool LmiFifoTryPush(T_)(LmiFifo(T_)* x, const T_* item) { \
	LmiBool r = LmiFifoTryPush_(T_)(x, item);	\
	LmiLogDebugFormatted(lmiLogFifo_, "Trying to push item %p onto queue %p: %s", item, x, (r) ? "success" : "error"); \
	return r; \
}

#define Define_LmiFifoPop(T_) \
static LmiFifoPopStatus LmiFifoPop_(T_)(LmiFifo(T_)* x, T_* item) { \
	LmiFifoPopStatus r; \
	LmiMonitorLock(&x->monitor); \
	while (!x->stopped && LmiDequeEmpty(T_)(&x->deque)) \
		LmiConditionWait(&x->notEmpty); \
	if (LmiDequeEmpty(T_)(&x->deque)) { \
		LmiAssert(x->stopped); \
		r = LMI_FIFOPOPSTATUS_StoppedAndEmpty; \
	} else { \
		r = LmiFifoPopNoWait_(T_)(x, item); \
	} \
	LmiMonitorUnlock(&x->monitor); \
	return r; \
} \
LmiFifoPopStatus LmiFifoPop(T_)(LmiFifo(T_)* x, T_* item) { \
	LmiFifoPopStatus r = LmiFifoPop_(T_)(x, item); \
	LmiLogDebugFormatted(lmiLogFifo_, "Popping item from queue %p: %s; *item=%p", x, LmiFifoPopStatusGetString(r), (r != LMI_FIFOPOPSTATUS_StoppedAndEmpty) ? item : NULL); \
	return r; \
}

#define Define_LmiFifoTryPop(T_) \
static LmiFifoPopStatus LmiFifoTryPop_(T_)(LmiFifo(T_)* x, T_* item) { \
	LmiFifoPopStatus r; \
	LmiMonitorLock(&x->monitor); \
	if (LmiDequeEmpty(T_)(&x->deque)) { \
		r = (x->stopped) ? LMI_FIFOPOPSTATUS_StoppedAndEmpty : LMI_FIFOPOPSTATUS_Empty; \
	} else { \
		r = LmiFifoPopNoWait_(T_)(x, item); \
	} \
	LmiMonitorUnlock(&x->monitor); \
	return r; \
} \
LmiFifoPopStatus LmiFifoTryPop(T_)(LmiFifo(T_)* x, T_* item) { \
	LmiFifoPopStatus r = LmiFifoTryPop_(T_)(x, item); \
	LmiLogDebugFormatted(lmiLogFifo_, "Trying to pop item from queue %p: %s; *item=%p", x, LmiFifoPopStatusGetString(r), \
	  (r != LMI_FIFOPOPSTATUS_Empty && r != LMI_FIFOPOPSTATUS_StoppedAndEmpty) ? item : NULL); \
	return r; \
}

#define Define_LmiFifoPeek(T_) \
static LmiBool LmiFifoPeek_(T_)(LmiFifo(T_)* x, T_* item) { \
	LmiBool r; \
	LmiMonitorLock(&x->monitor); \
	r = LmiDequeEmpty(T_)(&x->deque); \
	if (r) \
		LmiAssign(T_)(item, LmiDequeFront(T_)(&x->deque));	/* TODO: Error handling */ \
	LmiMonitorUnlock(&x->monitor); \
	return r; \
} \
LmiBool LmiFifoPeek(T_)(LmiFifo(T_)* x, T_* item) { \
	LmiBool r = LmiFifoPeek_(T_)(x, item); \
	LmiLogDebugFormatted(lmiLogFifo_, "Peeking at item from queue %p: %s; *item=%p", x, (r) ? "ok" : "no item", (r) ? item : NULL); \
	return r; \
}

#define Define_LmiFifoStop(T_) \
static void LmiFifoStop_(T_)(LmiFifo(T_)* x) { \
	LmiMonitorLock(&x->monitor); \
	x->stopped = LMI_TRUE; \
	LmiConditionNotifyAll(&x->notFull); \
	LmiConditionNotifyAll(&x->notEmpty); \
	LmiMonitorUnlock(&x->monitor); \
} \
void LmiFifoStop(T_)(LmiFifo(T_)* x) { \
	LmiFifoStop_(T_)(x); \
	LmiLogDebugFormatted(lmiLogFifo_, "Stopping queue %p", x); \
}

#define Define_LmiFifoSize(T_) \
LmiFifoSizeType(T_) LmiFifoSize(T_)(const LmiFifo(T_)* x) { \
	LmiFifoSizeType(T_) r; \
	LmiFifo(T_)* x_ = (LmiFifo(T_)*)x; /* Cast away const */ \
	LmiMonitorLock(&x_->monitor); \
	r = LmiDequeSize(T_)(&x->deque); \
	LmiMonitorUnlock(&x_->monitor); \
	return r; \
}

#define Define_LmiFifoCapacity(T_) \
LmiFifoSizeType(T_) LmiFifoCapacity(T_)(const LmiFifo(T_)* x) { \
	LmiFifoSizeType(T_) r; \
	LmiFifo(T_)* x_ = (LmiFifo(T_)*)x; /* Cast away const */ \
	LmiMonitorLock(&x_->monitor); \
	r = x->capacity; \
	LmiMonitorUnlock(&x_->monitor); \
	return r; \
}

#define Define_LmiFifoIsFull(T_) \
LmiBool LmiFifoIsFull(T_)(const LmiFifo(T_)* x) { \
	LmiBool r; \
	LmiFifo(T_)* x_ = (LmiFifo(T_)*)x; /* Cast away const */ \
	LmiMonitorLock(&x_->monitor); \
	r = LmiFifoIsFull_(T_)(x); \
	LmiMonitorUnlock(&x_->monitor); \
	return r; \
}

#define Define_LmiFifoIsStopped(T_) \
LmiBool LmiFifoIsStopped(T_)(const LmiFifo(T_)* x) { \
	LmiBool r; \
	LmiFifo(T_)* x_ = (LmiFifo(T_)*)x; /* Cast away const */ \
	LmiMonitorLock(&x_->monitor); \
	r = x->stopped; \
	LmiMonitorUnlock(&x_->monitor); \
	return r; \
}

#define Define_LmiFifo(T_) \
	Define_LmiDeque(T_) \
	Define_LmiFifoIsFull_(T_) \
	Define_LmiFifoPopNoWait_(T_) \
	Define_LmiFifoConstruct(T_) \
	Define_LmiFifoDestruct(T_) \
	Define_LmiFifoPush(T_) \
	Define_LmiFifoTryPush(T_) \
	Define_LmiFifoPop(T_) \
	Define_LmiFifoTryPop(T_) \
	Define_LmiFifoPeek(T_) \
	Define_LmiFifoStop(T_) \
	Define_LmiFifoSize(T_) \
	Define_LmiFifoCapacity(T_) \
	Define_LmiFifoIsFull(T_) \
	Define_LmiFifoIsStopped(T_)

LMI_END_EXTERN_C

#endif
