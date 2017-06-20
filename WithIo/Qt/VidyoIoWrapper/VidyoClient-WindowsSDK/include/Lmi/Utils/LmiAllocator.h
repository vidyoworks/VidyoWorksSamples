/** {file:
    {name: LmiAllocator.h}
    {description: Interface to allocators and deallocators}
    {copyright:
    	(c) 2005-2012 Vidyo, Inc.,
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

#ifndef LMI_ALLOCATOR_H_
#define LMI_ALLOCATOR_H_

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
   {package:
     {name: Allocators}
	 {parent: Utils}
	 {description: Package containing various allocator implementations.}
   }
*/

/* Forward declaration; the callbacks and the allocator mutually depend on
 * each other. */
typedef struct LmiAllocatorS_ LmiAllocator;

/** {callback:
      {name: LmiAllocatorAllocateCallback}
      {parent: LmiAllocator}
      {description: Allocate memory using a given allocator.}
      {prototype: LmiVoidPtr (*LmiAllocatorAllocateCallback)(LmiAllocator* allocator, LmiSizeT size)}
      {parameter: {name: allocator} {description: The allocator from which to allocate the memory.}}
      {parameter: {name: size} {description: Bytes of memory to allocate.}}
      {return: The memory allocated, or {code: NULL} on failure.}
    }
*/
typedef LmiVoidPtr (*LmiAllocatorAllocateCallback)(LmiAllocator * allocator, LmiSizeT size);

/** {callback:
      {name: LmiAllocatorDeallocateCallback}
      {parent: LmiAllocator}
      {description: Free memory previously allocated with the given allocator.}
      {prototype: void (*LmiAllocatorDeallocateCallback)(LmiAllocator* allocator, LmiVoidPtr ptr, LmiSizeT sizeHint)}
      {parameter: {name: allocator} {description: The allocator from which memory was allocated.}}
      {parameter: {name: ptr} {description: The memory to free.}}
      {parameter: {name: sizeHint} {description: The size of the original block of memory allocated, or LMI_SIZE_T_MAX if unknown.}}
      {note: This has no return value; it must always succeed.}
    }
*/
typedef void (*LmiAllocatorDeallocateCallback)(LmiAllocator * allocator, LmiVoidPtr ptr, LmiSizeT sizeHint);

/** {type:
    {name: LmiAllocator}
    {parent: Allocators}
    {include: Lmi/Utils/LmiAllocator.h}
    {description: Objects which allocate and deallocate memory.}
    }
*/

struct LmiAllocatorS_ {
  LmiAllocatorAllocateCallback allocate;
  LmiAllocatorDeallocateCallback deallocate;
  LmiSizeT maxSize;
  LmiVoidPtr userData;
};

/** {function:
    {name: LmiAllocatorConstruct}
    {parent: LmiAllocator}
    {description: Construct an LmiAllocator.}
    {prototype: LmiAllocator* LmiAllocatorConstruct(LmiAllocator* allocator, LmiAllocatorAllocateCallback allocate, LmiAllocatorDeallocateCallback deallocate, LmiSizeT maxSize, LmiVoidPtr userData)}
    {parameter: {name: allocator}
      {description: A pointer to an uninitialized LmiAllocator object.}}
    {parameter: {name: allocate}
      {description: The function to be called when the allocator allocates
      memory.}}
    {parameter: {name: deallocate}
      {description: The function to be called when the allocator deallocates
      memory.}}
    {parameter: {name: maxSize}
      {description: The maximum size block allocatable with the allocator.}}
    {parameter: {name: userData}
      {description: Internal data for use by the allocator.}}
    {return: The initialized allocator, or {code: NULL} on failure.}}
*/
LmiAllocator* LmiAllocatorConstruct(LmiAllocator* a, LmiAllocatorAllocateCallback allocate, LmiAllocatorDeallocateCallback deallocate, LmiSizeT maxSize, LmiVoidPtr user_data);


/** {function:
    {name: LmiAllocatorDestruct}
    {parent: LmiAllocator}
    {description: Destruct an LmiAllocator.}
    {prototype: void LmiAllocatorDestruct(LmiAllocator* allocator)}
    {parameter: {name: allocator}
      {description: The allocator object to destruct.}}
    {note: This does not do deallocate any memory associated with the allocator\'s
           user data field.  As such, this function should generally be
           considered "protected", i.e. it should only be called by specific
           allocators\' destruct functions.}}
*/
void LmiAllocatorDestruct(LmiAllocator* a);


/** {function:
    {name: LmiAllocatorGetUserData}
    {parent: LmiAllocator}
    {description: Get an allocator\'s user data.}
    {prototype: LmiVoidPtr LmiAllocatorGetUserData(LmiAllocator* allocator)}
    {parameter: {name: allocator}
      {description: The allocator object from which to get the user data.}}
	{return: The allocator object\'s user data.}
    {note: This function should generally only be called by the
           implementations of specific allocators.}}
*/
LMI_INLINE_DECLARATION LmiVoidPtr LmiAllocatorGetUserData(LmiAllocator* a);


/** {function:
    {name: LmiAllocatorAllocate}
    {parent: LmiAllocator}
    {description: Allocate memory from a given allocator.}
    {prototype: LmiVoidPtr LmiAllocatorAllocate(LmiAllocator* allocator, LmiSizeT size)}
    {parameter: {name: allocator} {description: The allocator from which to allocate the memory.}}
    {parameter: {name: size} {description: Bytes of memory to allocate.}}
    {return: The memory allocated, or {code: NULL} on failure.}
    }
*/
LMI_INLINE_DECLARATION LmiVoidPtr LmiAllocatorAllocate(LmiAllocator * a_, LmiSizeT s_);


/** {function:
    {name: LmiAllocatorDeallocate}
    {parent: LmiAllocator}
    {description: Deallocate memory previously allocated with the given allocator.}
    {prototype: void LmiAllocatorDeallocate(LmiAllocator* allocator, LmiVoidPtr ptr, LmiSizeT sizeHint)}
    {parameter: {name: allocator} {description: The allocator from which memory was allocated.}}
    {parameter: {name: ptr} {description: The memory to deallocate.}}
    {parameter: {name: sizeHint} {description: The size of the original block of memory allocated, or LMI_SIZE_T_MAX if unknown.}}
    {note: This has no return value; it must always succeed.}
    }
*/
LMI_INLINE_DECLARATION void LmiAllocatorDeallocate(LmiAllocator* a_, LmiVoidPtr p_, LmiSizeT sizeHint);


/** {function:
    {name: LmiAllocatorGetMaxSize}
    {parent: LmiAllocator}
    {description: Obtain the size of the largest block of memory allocatable with a given allocator.}
    {prototype: LmiSizeT LmiAllocatorGetMaxSize(const LmiAllocator* allocator)}
    {parameter: {name: allocator} {description: The allocator to query.}}
    {return: The size of the largest allocatable block.}
    {note: If the allocator has no intrinsic maximum size, e.g. it is limited only by available memory, this will return LMI_SIZE_T_MAX.}
    }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiAllocatorGetMaxSize(const LmiAllocator* a_);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiAllocatorInline.h>
#endif

#endif /* LMI_ALLOCATOR_H_ */
