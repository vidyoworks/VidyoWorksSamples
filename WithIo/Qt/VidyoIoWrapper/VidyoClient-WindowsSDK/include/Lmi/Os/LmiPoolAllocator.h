/** {file:
    {name: LmiPoolAllocator.h}
    {description: Interface to pool allocators and deallocators}
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

#ifndef LMI_POOL_ALLOCATOR_H_
#define LMI_POOL_ALLOCATOR_H_

#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiThread.h>

LMI_BEGIN_EXTERN_C

struct LmiPoolAllocatorPageS_;

/**
{type visibility="private":
     {name: LmiPoolAllocatorPageHeader}
     {parent: Os}
     {include: Lmi/Os/LmiPoolAllocator.h}
     {description: A header of pool allocator page.}
}
*/
typedef struct LmiPoolAllocatorPageHeaderS_ {    
	struct LmiPoolAllocatorPageS_* next;
	LmiSizeT	free_block_count;
} LmiPoolAllocatorPageHeader;

/**
{type visibility="private":
     {name: LmiPoolAllocatorPage}
     {parent: Os}
     {include: Lmi/Os/LmiPoolAllocator.h}
     {description: A page that contains multiple blocks allocated by Pool Allocator. Page is the actual 
					physical memory unit allocated when pool allocator runs out of free blocks.}
}
*/
typedef struct LmiPoolAllocatorPageS_ {  
	LmiPoolAllocatorPageHeader header;
	char	blocks_space[1];
} LmiPoolAllocatorPage;

/**
{type visibility="private":
     {name: LmiPoolAllocatorBlockHeader}
     {parent: Os}
     {include: Lmi/Os/LmiPoolAllocator.h}
     {description: A header of pool allocator block.}
}
*/
typedef struct {
	LmiPoolAllocatorPage* host_page;
	LmiBool	is_allocated;
} LmiPoolAllocatorBlockHeader;

/**
{type visibility="private":
     {name: LmiPoolAllocatorBlock}
     {parent: Os}
     {include: Lmi/Os/LmiPoolAllocator.h}
     {description: A block allocated by pool allocator.}
}
*/
typedef struct LmiPoolAllocatorBlockS_ {  
	LmiPoolAllocatorBlockHeader	header;
	union {
		struct	LmiPoolAllocatorBlockS_* next_free;
		char	usr_data[1];
	} u;
} LmiPoolAllocatorBlock;

/* identifier (brand) of a pool allocator) */
#define LMI_POOL_ALLOCATOR_Attribute		"LmiPoolAllocator"
#define LMI_POOL_ALLOCATOR_AttributeLen		sizeof(LMI_POOL_ALLOCATOR_Attribute)

/**
{type visibility="public":
     {name: LmiPoolAllocator}
     {parent: Os}
     {include: Lmi/Os/LmiPoolAllocator.h}
     {description: An allocator that allocates memory using pre-allocates memory pools.}
}
*/
typedef struct {  
	char	attribute[LMI_POOL_ALLOCATOR_AttributeLen];	/* attribute used to identify a pool allocator */
	LmiPoolAllocatorPage* first_page;		/* first page in the pool allocator's list */  
	LmiPoolAllocatorPage* last_page;		/* last page in the pool allocator's list */
	LmiSizeT	usr_data_size;				/* data block size requested by user */
	LmiSizeT	block_size;					/* single block size (including header) */
	LmiSizeT	blocks_per_page;			/* number of blocks per page */
	LmiAllocator*	page_allocator;			/* allocator used for page allocation */
	LmiAllocator*	state_allocator;		/* allocator used for state allocation */
	LmiPoolAllocatorBlock* first_free_block;
	LmiPoolAllocatorBlock* last_free_block;
	LmiThread*	garbageCollectionThread;
	LmiMutex	mutex;
} LmiPoolAllocator;

/**	{function visibility="public":
    {name: LmiPoolAllocatorConstruct}
    {parent: LmiPoolAllocator}
    {description: Construct an LmiPoolAllocator.}
    {prototype: LmiAllocator* LmiPoolAllocatorConstruct(LmiAllocator* poolAlloc, LmiAllocator* pageAlloc, LmiAllocator* stateAlloc, LmiSizeT maxBlockSize, LmiSizeT numBlocksPerPage)}
    {parameter: {name: poolAlloc}
      {description: A pointer to an uninitialized LmiAllocator object.}}   
    {parameter: {name: pageAlloc}
      {description: A pointer to a {italic: previously constructed} LmiAllocator object responsible for page allocation.}} 
    {parameter: {name: stateAlloc}
      {description: A pointer to a {italic: previously constructed} LmiAllocator object responsible for allocation of pool allocator internal state variables.}} 
    {parameter: {name: maxBlockSize}
      {description: The maximum memory block size allocatable with the pool allocator.}}
    {parameter: {name: numBlocksPerPage}
      {description: The number of blocks contained in each page.}}
    {return: The initialized allocator, or {code: NULL} on failure.}}
*/
LmiAllocator* LmiPoolAllocatorConstruct(LmiAllocator* poolAlloc, LmiAllocator* pageAlloc, LmiAllocator* stateAlloc, LmiSizeT maxBlockSize, LmiSizeT numBlocksPerPage);

/**	{function visibility="public":
	  {name: LmiPoolAllocatorDestruct}
      {parent: LmiPoolAllocator}
      {description: Destruct an LmiPoolAllocator.}
      {prototype: void LmiPoolAllocatorDestruct(LmiAllocator* a)}
      {parameter: {name: a}
        {description: The allocator object to destruct.}}
      {note: The allocator object has to have been previously constructed 
			using LmiPoolAllocatorConstruct.}
	}
*/
void LmiPoolAllocatorDestruct(LmiAllocator* a);

/**	{function visibility="public":
     {name: LmiPoolAllocatorInitialize}
     {parent: LmiPoolAllocator}
     {description: Initialize LmiPoolAllocator.}
     {prototype: LmiBool LmiPoolAllocatorInitialize(void)}
     {return: LMI_TRUE on success, LMI_FALSE on failure.}
   }
*/
LmiBool LmiPoolAllocatorInitialize(void);

/**	{function visibility="public":
     {name: LmiPoolAllocatorUninitialize}
     {parent: LmiPoolAllocator}
     {description: Uninitialize LmiPoolAllocator.}
     {prototype: void LmiPoolAllocatorUninitialize(void)}
   }
*/
void LmiPoolAllocatorUninitialize(void);

void LmiPoolAllocatorGetStats(LmiUint* pages, LmiSizeT* memoryInUse);

LmiBool LmiPoolAllocatorResize(LmiAllocator *a, LmiSizeT maxBlockSize, LmiSizeT numBlocksPerPage);

/* Master Pool Allocator */
typedef struct {
	LmiAllocator *pool;
	LmiBool stale;
	LmiSizeT blockSize;
	LmiTime lastUsedTime;
} LmiPoolAllocatorInfo;

LmiPoolAllocatorInfo* LmiPoolAllocatorInfoConstruct(LmiPoolAllocatorInfo *i, LmiSizeT size, LmiAllocator *p);
LmiPoolAllocatorInfo* LmiPoolAllocatorInfoConstructCopy(LmiPoolAllocatorInfo *i, const LmiPoolAllocatorInfo *p);
LmiPoolAllocatorInfo* LmiPoolAllocatorInfoAssign(LmiPoolAllocatorInfo *i, const LmiPoolAllocatorInfo *p);
void LmiPoolAllocatorInfoDestruct(LmiPoolAllocatorInfo *i);

Declare_LmiVector(LmiPoolAllocatorInfo)

typedef struct LmiMasterPoolAllocator_
{
	LmiMutex mutex;
	LmiVector(LmiPoolAllocatorInfo) pools;
	LmiAllocator *a;
	LmiSizeT numBlocks;
} LmiMasterPoolAllocator;

LmiAllocator* LmiMasterPoolAllocatorConstruct(LmiAllocator *m, LmiAllocator* alloc, LmiSizeT initialBlockSize, LmiSizeT numBlocksPerPage);
void LmiMasterPoolAllocatorDestruct(LmiAllocator *m);

LMI_END_EXTERN_C

#endif /* LMI_POOL_ALLOCATOR_H_ */
