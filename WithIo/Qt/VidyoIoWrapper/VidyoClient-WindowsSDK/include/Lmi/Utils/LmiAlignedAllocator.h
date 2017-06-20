/** {file:
    {name: LmiAlignedAllocator.h}
    {description: allocator that allocates n-byte-aligned memory.}
    {copyright:
    	(c) 2008-2015 Vidyo, Inc.,
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

#ifndef LMI_ALIGNED_ALLOCATOR_H_
#define LMI_ALIGNED_ALLOCATOR_H_

#include <Lmi/Utils/LmiAllocator.h>

LMI_BEGIN_EXTERN_C

#define LMI_ALIGNEDALLOCATOR_DefaultAlignment (16)

/** {type:
    {name: LmiAlignedAllocator}
    {parent: Allocators}
    {include: Lmi/Utils/LmiAlignedAllocator.h}
    {description: Objects which allocate and deallocate memory aligned to a specific n-byte boundary.}
    }
*/
typedef struct {
    LmiAllocator base;	/* Must be first member */
    LmiAllocator *a;
    LmiUint8 alignment;
} LmiAlignedAllocator;

/**
   {function:
     {name: LmiAlignedAllocatorConstruct}
     {parent: LmiAlignedAllocator}
     {description: Construct a new LmiAlignedAllocator.}
     {prototype: LmiAlignedAllocator *LmiAlignedAllocatorConstruct(LmiAlignedAllocator *x, LmiUint8 alignment, LmiAllocator *a)}
     {parameter:  {name: x}
       {description: A pointer to an uninitialized LmiAlignedAllocator.}}
	{parameter: {name: alignment}
		{description: The alignment (in bytes) to be used when allocating memory. The value specified must be a power of 2.  If this value is 0, LMI_ALIGNEDALLOCATOR_DefaultAlignment will be used.}}
	{parameter: {name: a}
		{description: A pointer to an initialized LmiAllocator. Actual memory allocation will be done through this allocator.}}
	{return: The constructed allocator or {code: NULL} on failure.}
   }
*/
LmiAlignedAllocator *LmiAlignedAllocatorConstruct(LmiAlignedAllocator *x, LmiUint8 alignment, LmiAllocator *a);

/**
   {function:
     {name: LmiAlignedAllocatorConstructCopy}
     {parent: LmiAlignedAllocator}
     {description: ConstructCopy a new LmiAlignedAllocator.}
     {prototype: LmiAlignedAllocator *LmiAlignedAllocatorConstructCopy(LmiAlignedAllocator *x, const LmiAlignedAllocator *y)}
     {parameter:  {name: x}
       {description: A pointer to an uninitialized LmiAlignedAllocator.}}
     {parameter:  {name: y}
       {description: A pointer to an initialized LmiAlignedAllocator.}}
	{return: The constructed allocator or {code: NULL} on failure.}
   }
*/
LmiAlignedAllocator *LmiAlignedAllocatorConstructCopy(LmiAlignedAllocator *x, const LmiAlignedAllocator *y);

/**
   {function:
     {name: LmiAlignedAllocatorDestruct}
     {parent: LmiAlignedAllocator}
     {description: Destruct an aligned allocator.}
     {prototype: void LmiAlignedAllocatorDestruct(LmiAlignedAllocator *x)}
     {parameter:  {name: x}
        {description: A pointer to an LmiAlignedAllocator to destruct.}}
}
*/
void LmiAlignedAllocatorDestruct(LmiAlignedAllocator *x);

/** {function:
    {name: LmiAlignedAllocatorGetAllocator}
    {parent: LmiAlignedAllocator}
    {description: Get the aligned allocator\'s allocator.}
    {prototype: LmiAllocator *LmiAlignedAllocatorGetAllocator(LmiAlignedAllocator *x)}
    {parameter:  {name: x}
      {description: The aligned allocator object from which to get the allocator.}}
	{return: base allocator.}}
*/
LMI_INLINE_DECLARATION LmiAllocator *LmiAlignedAllocatorGetAllocator(LmiAlignedAllocator *x);

/** {function:
    {name: LmiAlignedAllocatorGetBase}
    {parent: LmiAlignedAllocator}
    {description: Get the aligned allocator\'s base allocator.}
    {prototype: LmiAllocator *LmiAlignedAllocatorGetBase(LmiAlignedAllocator *x)}
    {parameter:  {name: x}
      {description: The aligned allocator object from which to get the base allocator.}}
	{return: base allocator.}}
*/
LMI_INLINE_DECLARATION LmiAllocator *LmiAlignedAllocatorGetBase(LmiAlignedAllocator *x);

/** {function:
    {name: LmiAlignedAllocatorGetMaxSize}
    {parent: LmiAlignedAllocator}
    {description: Obtain the size of the largest block of memory allocatable with a given allocator.}
    {prototype: LmiSizeT LmiAlignedAllocatorGetMaxSize(const LmiAlignedAllocator *x)}
    {parameter: {name: x} {description: The aligned allocator to query.}}
    {return: The size of the largest allocatable block.}
    }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiAlignedAllocatorGetMaxSize(const LmiAlignedAllocator *x);

/** {function:
    {name: LmiAlignedAllocatorGetAlignment}
    {parent: LmiAlignedAllocator}
    {description: Obtain the alignment in bytes.}
    {prototype: LmiUint8 LmiAlignedAllocatorGetAlignment(const LmiAlignedAllocator *x)}
    {parameter:  {name: x} {description: The aligned allocator to query.}}
    {return: The align size in bytes.}
    }
*/
LMI_INLINE_DECLARATION LmiUint8 LmiAlignedAllocatorGetAlignment(const LmiAlignedAllocator *x);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiAlignedAllocatorInline.h>
#endif

#endif /* LMI_ALIGNED_ALLOCATOR_H_ */

