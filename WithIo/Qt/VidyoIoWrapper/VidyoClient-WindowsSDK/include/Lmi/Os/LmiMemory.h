/**	
{file:
	{name: LmiMemory.h}
	{description:	Objects	to provide regulated memory	management routines.}
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
#ifndef	LMI_MEMORY_H_
#define	LMI_MEMORY_H_

#include <Lmi/Utils/LmiTypes.h>

/**	
	{package: 
		{name: Memory}
		{parent: Os}
		{include: Lmi/Os/LmiMemory.h}
		{description: A package for requesting, freeing and debugging dynamic memory.}
	}
*/

/**
	{type visibility="private": 
		{name: LmiMemoryBlockStatus}
		{parent: Memory}
		{description: Memory block	status values.}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_Valid}
			{description: Memory block is valid.}
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_HeaderGuardCorrupted}
			{description: Header guard corrupt.}
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_DataStartGuardCorrupted}
			{description: Starting buffer guard corrupt. Possible buffer underrun.}
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_DataEndGuardCorrupted}
			{description: Ending buffer guard corrupt. Possible buffer overrun.}
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_UnallocatedBlock}
			{description: Not an allocated block. }
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_InvalidDataSize}
			{description: Size of block is invalid. }
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_NextPointerCorrupted}
			{description: Link to next memory block is corrupt.}
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_PrevPointerCorrupted}
			{description: Link to previous memory block is corrupt.}
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_CyclicNextPointer}
			{description: Link to next memory block is cyclic (corrupt).}
		}
		{value: 
			{name: LMI_MEMORY_BLOCKSTATUS_CyclicPrevPointer}
			{description: Link to previous memory block is cyclic (corrupt).}
		}
	}
*/
typedef	enum
{
	LMI_MEMORY_BLOCKSTATUS_Valid,
	LMI_MEMORY_BLOCKSTATUS_HeaderGuardCorrupted,
	LMI_MEMORY_BLOCKSTATUS_DataStartGuardCorrupted,
	LMI_MEMORY_BLOCKSTATUS_DataEndGuardCorrupted,	
	LMI_MEMORY_BLOCKSTATUS_UnallocatedBlock,
	LMI_MEMORY_BLOCKSTATUS_InvalidDataSize,
	LMI_MEMORY_BLOCKSTATUS_NextPointerCorrupted,
	LMI_MEMORY_BLOCKSTATUS_PrevPointerCorrupted,
	LMI_MEMORY_BLOCKSTATUS_CyclicNextPointer,
	LMI_MEMORY_BLOCKSTATUS_CyclicPrevPointer,
	LMI_MEMORY_BLOCKSTATUS_NeverValidated = (~0)
} LmiMemoryBlockStatus;

LMI_BEGIN_EXTERN_C

/**	{function visibility="private":
		{name: LmiMemoryAllocate}	 
		{parent: Memory}
		{description: Allocates	memory chunk of	the	specified size.}
		{prototype:	LmiVoidPtr LmiMemoryAllocate(LmiSizeT size)}
		{parameter:	{name: size}
			{description: Size of the memory chunk to be allocated.}}
		{return: Pointer to	the	allocated, or {code: NULL} on failure.}
		{note: This	function should	be used	whenever memory	allocation is required.}
	}
*/
LmiVoidPtr LmiMemoryAllocate(LmiSizeT size);

/**	{function visibility="private":
		{name: LmiMemoryFree}	 
		{parent: Memory}
		{description: Free memory block	previously allocated by	LmiMemoryAllocate function.}
		{prototype:	void LmiMemoryFree(LmiVoidPtr ptr)}
		{parameter:	{name: ptr}
			{description: Pointer to the memory	space to be	deallocated.}}
		{note: This	function should	ONLY be	used to	free memory	allocated using	LmiMemoryAllocate.}
	}
*/
void LmiMemoryFree(LmiVoidPtr ptr);

/**
{callback:
	{name: LmiMemoryExhausted}
	{parent: Memory}
	{description: A callback invoked when "out of memory" condition is encountered.}
	{prototype: LmiBool (*LmiMemoryExhausted)(LmiSizeT bytes)}
	{parameter: {name: bytes} {description: Number of bytes requested to be allocated.}}
	{return: LMI_TRUE or LMI_FALSE depending on whether the function succeeded or not.}
}
*/
typedef	LmiBool (*LmiMemoryExhausted)(LmiSizeT bytes);

/**	{function visibility="private":
		{name: LmiMemoryInitialize}
		{parent: Memory}
		{description: Initializes tables and data structures required for LMI Memory Manager to	operate.}	
		{prototype:	LmiBool LmiMemoryInitialize(void)}
		{return: {code:	LMI_TRUE} on success, or {code:	LMI_FALSE} on failure.}
		{note: This	function must be called	prior to any memory	related	operation.}
	}
*/
LmiBool	LmiMemoryInitialize(void);

/**	{function visibility="private":
		{name: LmiMemoryUninitialize}	 
		{parent: Memory}
		{description: Uninitializes	tables and data	structures required	for	LMI	Memory Manager to operate.}
		{prototype:	void LmiMemoryUninitialize(void)}
	}
*/
void LmiMemoryUninitialize(void);

/**	{function visibility="private":
		{name: LmiMemoryRegisterOutOfMemoryCallback}	
		{parent: Memory}
		{description: Register callback	function that will be invoked whenever "out	of memory" 
						condition is encountered by	LmiMemoryAllocate function.}
		{prototype:	void LmiMemoryRegisterOutOfMemoryCallback(LmiMemoryExhausted outOfMemory)}
		{parameter:	{name: outOfMemory}
			{description: Callback fto call when heap is exhausted.}}
	}
*/
void LmiMemoryRegisterOutOfMemoryCallback(LmiMemoryExhausted outOfMemory);

/**	{function visibility="private":
		{name: LmiMemoryLogBlock}	
		{parent: Memory}
		{description: Logs information about the memory block specified.}
		{prototype:	void LmiMemoryLogBlock(const LmiVoidPtr ptr)}
		{parameter:	{name: ptr}
			{description: A pointer to the memory block.}}
	}
*/
void LmiMemoryLogBlock(const LmiVoidPtr ptr);

/**	{function visibility="private":
		{name: LmiMemoryLogAll}	
		{parent: Memory}
		{description: Logs information about all currently allocated memory blocks.}
		{prototype:	void LmiMemoryLogAll(void)}
	}
*/
void LmiMemoryLogAll(void);

/**	{function visibility="private":
		{name: LmiMemoryPrintAllocatedObjects}	
		{parent: Memory}
		{description: Prints information about all currently allocated objects.}
		{prototype:	void LmiMemoryPrintAllocatedObjects(LmiSizeT objSize, LmiVoidPtr objAddr, const char* name)}
		{parameter:	{name: objSize}
			{description: Minimum size of displayed objects.}}
		{parameter:	{name: objAddr}
			{description: Address of selected object.}}
		{parameter:	{name: name}
			{description: (part of) object\'s name.}}
	}
*/
void LmiMemoryPrintAllocatedObjects(LmiSizeT objSize, LmiVoidPtr objAddr, const char* name);

/**	{function visibility="private":
		{name: LmiMemoryValidateBlock}	
		{parent: Memory}
		{description: Validate memory block by pointer obtained using {code: LmiMemoryAllocate}. 
			In case a problem is detected, block data is logged (or printed on a console).}
		{prototype:	LmiMemoryBlockStatus LmiMemoryValidateBlock(const LmiVoidPtr ptr)}		
		{parameter:	{name: ptr}
			{description: A pointer to the memory block to validate.}}
		{return: LMI_MEMORY_BLOCKSTATUS_Valid if block is valid otherwise a value indicating what failed.}		
	}
*/
LmiMemoryBlockStatus LmiMemoryValidateBlock(const LmiVoidPtr ptr);

/**	{function visibility="private":
		{name: LmiMemoryValidateAll}	
		{parent: Memory}
		{description: Validate all memory blocks allocated by {code: LmiMemoryAllocate}.}		
		{prototype:	LmiBool LmiMemoryValidateAll(void)}				
		{return: {code:	LMI_TRUE} if all blocks are valid, or {code: LMI_FALSE} if a defective block is found.}
	}
*/
LmiBool	LmiMemoryValidateAll(void);

/**	{function visibility="private":
		{name: LmiMemoryLogStats}	
		{parent: Memory}
		{description: Logs all memory statistics.}		
		{prototype:	void LmiMemoryLogStats(void)}				
	}
*/
void LmiMemoryLogStats(void);

/**	{function visibility="private":
		{name: LmiMemoryLogSizes}	
		{parent: Memory}
		{description: Logs sizes of currently allocated memory blocks.}		
		{prototype:	void LmiMemoryLogSizes(void)}				
	}
*/
void LmiMemoryLogSizes(void);

/**	{function visibility="private":
		{name: LmiMemoryGetBytesAllocated}	
		{parent: Memory}
		{description: Get the number of bytes currently allocated.  The value returned 
		includes the sum of the memory request not counting any overhead imposed by 
		LmiMemory or the underlying OS.}
		{prototype:	LmiSizeT LmiMemoryGetBytesAllocated(void)}
		{return: The number of currently allocated bytes.}
	}
*/
LmiSizeT LmiMemoryGetBytesAllocated(void);

/**	{function visibility="private":
		{name: LmiMemoryGetBlocksAllocated}	
		{parent: Memory}
		{description: Get the number of bytes currently allocated. }
		{prototype:	LmiSizeT LmiMemoryGetBlocksAllocated(void)}
		{return: The number of currently allocated blocks.}
	}
*/
LmiSizeT LmiMemoryGetBlocksAllocated();

LMI_END_EXTERN_C

#endif /* LMI_MEMORY_H_	*/
