/** {file:
	  {name: LmiDataBuffer.h}
	  {description: Reference-counted data buffer.}
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
#ifndef LMI_DATA_BUFFER_H_
#define LMI_DATA_BUFFER_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Os/LmiMutex.h>
#include <Lmi/Os/LmiAtomicInteger.h>

LMI_BEGIN_EXTERN_C

typedef struct {
	LmiAtomicInteger referenceCount;
	LmiSizeT capacity;
	LmiAllocator* alloc;
	/* Buffer proper follows -- array of LmiUint8. */
	/* LmiUint8 data[0]; */
} LmiDataBufferImpl_;

/* 8 extra bytes are for the trailing space for ReadBits64. */
#define LMI_DATA_BUFFER_OVERHEAD (sizeof(LmiDataBufferImpl_) + 8)

/* Internal functions for LmiDataBuffer; declared here for inlining. */
LmiDataBufferImpl_* LmiDataBufferImplAlloc_(LmiSizeT capacity,
	LmiAllocator* a);
void LmiDataBufferImplDealloc_(LmiDataBufferImpl_* d);
LMI_INLINE_DECLARATION LmiUint8* LmiDataBufferImplGetData_(LmiDataBufferImpl_* d);
LMI_INLINE_DECLARATION void LmiDataBufferImplIncrementRefCount_(LmiDataBufferImpl_* d);
LMI_INLINE_DECLARATION void LmiDataBufferImplDecrementRefCount_(LmiDataBufferImpl_* d);

/* Define this to allocate a dummy block of memory every time a data buffer
 * is allocated.  This lets you use standard malloc/free checking tools
 * to find places where data buffers aren't deallocated. */
/* #define LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_ 1 */

/* This is chosen to be a sufficiently strange size that it's fairly unique
 * in the allocation statistics. */
#define LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_ 17

/**
   {type:
     {name: LmiDataBuffer}
	 {parent: Os}
	 {include: Lmi/Os/LmiDataBuffer.h}
	 {description: A reference-counted buffer.}
   }
*/
typedef struct {
	LmiDataBufferImpl_* impl;
	LmiUint8* data; /* Pointer into impl->data */
	LmiSizeT length;
	LmiSizeT bitPos;
#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	LmiVoidPtr dummyAlloc;
#endif
} LmiDataBuffer;


/**
   {function:
     {name: LmiDataBufferConstruct}
	 {parent: LmiDataBuffer}
	 {description: Construct a data buffer with the given capacity.}
	 {prototype: LmiDataBuffer* LmiDataBufferConstruct(LmiDataBuffer* b, LmiSizeT capacity, LmiAllocator* a)}
	 {parameter:
	   {name: b}
	   {description: The object to construct.}}
	 {parameter:
	   {name: capacity}
	   {description: The capacity in bytes of the data buffer to allocate.}}
	 {parameter:
	   {name: a}
	   {description: The allocator to use to allocate the buffer.  This
	      will allocate a block of size capacity + LMI_DATA_BUFFER_OVERHEAD,
		  unless capacity == 0.  If capacity == 0, no allocation will be
		  performed, and a may be NULL.}}
	 {return: b on success, NULL on failure.}
	 {note: The buffer\'s length and its read/write position are
	   initialized to 0.}
	 {note: Capacity must not be more than LMI_SIZE_T_MAX / 8, as the type 
	   LmiSizeT is used to represent bit offsets in the buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiDataBuffer* LmiDataBufferConstruct(LmiDataBuffer* b, LmiSizeT capacity, LmiAllocator* a);


/**
   {function:
     {name: LmiDataBufferConstructCopy}
	 {parent: LmiDataBuffer}
	 {description: Construct a copy of a data buffer.}
	 {prototype: LmiDataBuffer* LmiDataBufferConstructCopy(LmiDataBuffer* b, const LmiDataBuffer* orig)}
	 {parameter:
	   {name: b}
	   {description: The object to construct.}}
	 {parameter:
	   {name: orig}
	   {description: An existing data buffer to copy.}}
	 {return: b on success, NULL on failure.}
	 {note: Data buffers are reference-counted.  This constructor increments
	   orig\'s reference count, and does not copy the actual buffer.}
	 {note: The new buffer has its own read/write position, independent of
	   the original buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiDataBuffer* LmiDataBufferConstructCopy(LmiDataBuffer* b, const LmiDataBuffer* orig);


/**
   {function:
     {name: LmiDataBufferConstructSubbuffer}
	 {parent: LmiDataBuffer}
	 {description: Construct a data buffer based on part of another buffer.}
	 {prototype: LmiDataBuffer* LmiDataBufferConstructSubbuffer(LmiDataBuffer* b, const LmiDataBuffer* orig, LmiSizeT pos, LmiSizeT len)}
	 {parameter:
	   {name: b}
	   {description: The object to construct.}}
	 {parameter:
	   {name: orig}
	   {description: The source data buffer.}}
     {parameter:
       {name: pos}
       {description: The initial position of the subbuffer within the source
         string.  This must be less than orig\'s capacity.}}
     {parameter:
       {name: len}
       {description: The length of the substring within the source
         string.  This must be less than orig\'s capacity - pos.}}
	 {return: b on success, NULL on failure.}
	 {note: Data buffers are reference-counted.  This constructor increments
	   orig\'s reference count, and does not copy the actual buffer.}
	 {note: The new buffer has its own read/write position, independent of
	   the original buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiDataBuffer* LmiDataBufferConstructSubbuffer(LmiDataBuffer* b,
	const LmiDataBuffer* orig, LmiSizeT pos, LmiSizeT len);


/**
   {function:
     {name: LmiDataBufferConstructSubbufferAtReadPosition}
	 {parent: LmiDataBuffer}
	 {description: Construct a data buffer based on part of another buffer, adjusting the source buffer\'s read position.}
	 {prototype: LmiDataBuffer* LmiDataBufferConstructSubbufferAtReadPosition(LmiDataBuffer* b, LmiDataBuffer* orig, LmiSizeT len)}
	 {parameter:
	   {name: b}
	   {description: The object to construct.}}
	 {parameter:
	   {name: orig}
	   {description: The source data buffer.  Its read position must
	   	currently be byte-aligned (a multiple of 8).}}
     {parameter:
       {name: len}
       {description: The length of the sub-buffer within the source
         buffer, in bytes.  This must be less than or equal to
		 LmiDataBufferGetRemainingReadableBitCount(orig)/8.}}
	 {return: b on success, NULL on failure.}
	 {note: Data buffers are reference-counted.  This constructor increments
	   orig\'s reference count, and does not copy the actual buffer.}
	 {note: The new buffer has its own read/write position, independent of
	   the original buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiDataBuffer* LmiDataBufferConstructSubbufferAtReadPosition(LmiDataBuffer* b,
	LmiDataBuffer* orig, LmiSizeT len);


/**
   {function:
     {name: LmiDataBufferDestruct}
	 {parent: LmiDataBuffer}
	 {description: Destruct a data buffer.}
	 {prototype: void LmiDataBufferDestruct(LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The object to destruct.}}
	 {note: Data buffers are reference-counted.  The buffer referenced by b
	   has its reference count decremented by one; the data is destroyed only
	   when its reference count reaches 0.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferDestruct(LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferAssign}
	 {parent: LmiDataBuffer}
	 {description: Assign the value of one data buffer to another.}
	 {prototype: LmiDataBuffer* LmiDataBufferAssign(LmiDataBuffer* b, const LmiDataBuffer* orig)}
	 {parameter:
	   {name: b}
	   {description: The object to assign.}}
	 {parameter:
	   {name: orig}
	   {description: An existing data buffer to copy.}}
	 {return: b on success, NULL on failure.}
	 {note: Data buffers are reference-counted.  If b and orig refer to
	   different data buffers, b\'s reference count is decremented, and orig\'s
	   reference count is incremented.  (Thus, unlike most objects' Assign
	   operators, LmiDataBufferAssign causes b to use orig\'s allocator.}
	 {note: This function resets b\'s read/write position.}
   }
*/
LMI_INLINE_DECLARATION LmiDataBuffer* LmiDataBufferAssign(LmiDataBuffer* b, const LmiDataBuffer* orig);


/**
   {function:
     {name: LmiDataBufferAssignSubbuffer}
	 {parent: LmiDataBuffer}
	 {description: Assign the value of a data buffer based on part of another buffer.}
	 {prototype: LmiDataBuffer* LmiDataBufferAssignSubbuffer(LmiDataBuffer* b, const LmiDataBuffer* orig, LmiSizeT pos, LmiSizeT len)}
	 {parameter:
	   {name: b}
	   {description: The object to assign.}}
	 {parameter:
	   {name: orig}
	   {description: The source data buffer.}}
     {parameter:
       {name: pos}
       {description: The initial position of the subbuffer within the source
         string.  This must be less than orig\'s capacity.}}
     {parameter:
       {name: len}
       {description: The length of the substring within the source
         string.  This must be less than orig\'s capacity - pos.}}
	 {return: b on success, NULL on failure.}
	 {note: Data buffers are reference-counted.  If b and orig refer to
	   different data buffers, b\'s reference count is decremented, and orig\'s
	   reference count is incremented.  (Thus, unlike most objects' Assign
	   operators, LmiDataBufferAssign causes b to use orig\'s allocator.}
	 {note: This function resets b\'s read/write position.}
   }
*/
LMI_INLINE_DECLARATION LmiDataBuffer* LmiDataBufferAssignSubbuffer(LmiDataBuffer* b,
	const LmiDataBuffer* orig, LmiSizeT pos, LmiSizeT len);


/**
   {function:
     {name: LmiDataBufferAssignSubbufferAtReadPosition}
	 {parent: LmiDataBuffer}
	 {description: Assign a data buffer based on part of another buffer, adjusting the source buffer\'s read position.}
	 {prototype: LmiDataBuffer* LmiDataBufferAssignSubbufferAtReadPosition(LmiDataBuffer* b, LmiDataBuffer* orig, LmiSizeT len)}
	 {parameter:
	   {name: b}
	   {description: The object to assign.}}
	 {parameter:
	   {name: orig}
	   {description: The source data buffer.  Its read position must
	   	currently be byte-aligned (a multiple of 8).}}
     {parameter:
       {name: len}
       {description: The length of the sub-buffer within the source
         buffer, in bytes.  This must be less than or equal to
		 LmiDataBufferGetRemainingReadableBitCount(orig)/8.}}
	 {return: b on success, NULL on failure.}
	 {note: Data buffers are reference-counted.  If b and orig refer to
	   different data buffers, b\'s reference count is decremented, and orig\'s
	   reference count is incremented.  (Thus, unlike most objects' Assign
	   operators, LmiDataBufferAssign causes b to use orig\'s allocator.}
	 {note: The new buffer has its own read/write position, independent of
	   the original buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiDataBuffer* LmiDataBufferAssignSubbufferAtReadPosition(LmiDataBuffer* b,
	LmiDataBuffer* orig, LmiSizeT len);


/**
   {function:
     {name: LmiDataBufferEqual}
     {parent: LmiDataBuffer}
     {description: Compare the contents of two LmiDataBuffers (up to their
	   lengths) for equality.}
     {prototype: LmiBool LmiDataBufferEqual(const LmiDataBuffer* x, const LmiDataBuffer* y)}
     {parameter:
       {name: x}
       {description: A pointer to the first data buffer to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the second data buffer to compare.}
     }
     {return: LMI_TRUE if the data buffers are equal, LMI_FALSE otherwise.}
	 {note: The buffers\' read/write positions do not affect their equality.}
   }
*/
LmiBool LmiDataBufferEqual(const LmiDataBuffer* x, const LmiDataBuffer* y);


/**
   {function:
     {name: LmiDataBufferLess}
     {parent: LmiDataBuffer}
     {description: Compare the contents of two LmiDataBuffers (up to their
	   lengths) for ordering.}
     {prototype: LmiBool LmiDataBufferLess(const LmiDataBuffer* x, const LmiDataBuffer* y)}
     {parameter:
       {name: x}
       {description: A pointer to the first data buffer to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the second data buffer to compare.}
     }
     {return: LMI_TRUE if x is lexicographically less than y, LMI_FALSE
       otherwise.}
	 {note: The buffers\' read/write positions do not affect their ordering.}
   }
*/
LmiBool LmiDataBufferLess(const LmiDataBuffer* x, const LmiDataBuffer* y);


/**
	{function:
		{name: LmiDataBufferSwap}
		{parent: LmiDataBuffer}
		{description: Swap the contents of two LmiDataBuffers.}
		{prototype: LmiBool LmiDataBufferSwap(LmiDataBuffer* a, LmiDataBuffer* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiDataBuffer object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiDataBuffer object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: All of buffers\' state is swapped, including their read/write
			positions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiDataBufferSwap(LmiDataBuffer* a, LmiDataBuffer* b);

/**
   {function:
     {name: LmiDataBufferGetData}
	 {parent: LmiDataBuffer}
	 {description: Get an LmiDataBuffer\'s data.}
	 {prototype: LmiUint8* LmiDataBufferGetData(LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The buffer whose data to get.}}
	 {return: A pointer to the buffer\'s data.}
	 {note: This pointer may be invalidated by a call to
	   LmiDataBufferMakeExclusive, but otherwise persists as long as the
	   data buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiUint8* LmiDataBufferGetData(LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferGetDataConst}
	 {parent: LmiDataBuffer}
	 {description: Get a const LmiDataBuffer\'s data.}
	 {prototype: const LmiUint8* LmiDataBufferGetDataConst(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The buffer whose data to get.}}
	 {return: A pointer to the buffer\'s data.}
	 {note: This pointer may be invalidated by a call to
	   LmiDataBufferMakeExclusive, but otherwise persists as long as the
	   data buffer.}
   }
*/
LMI_INLINE_DECLARATION const LmiUint8* LmiDataBufferGetDataConst(const LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferGetCapacity}
	 {parent: LmiDataBuffer}
	 {description: Get the capacity of an LmiDataBuffer.}
	 {prototype: LmiSizeT LmiDataBufferGetCapacity(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The buffer whose data capacity to get.}}
	 {return: The capacity of the buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferGetCapacity(const LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferGetLength}
	 {parent: LmiDataBuffer}
	 {description: Get the length of an LmiDataBuffer\'s data.}
	 {prototype: LmiSizeT LmiDataBufferGetLength(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The buffer whose data length to get.}}
	 {return: The length of the buffer\'s data.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferGetLength(const LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferSetLength}
	 {parent: LmiDataBuffer}
	 {description: Set the length of an LmiDataBuffer\'s data.}
	 {prototype: LmiBool LmiDataBufferSetLength(LmiDataBuffer* b, LmiSizeT len)}
	 {parameter:
	   {name: b}
	   {description: The buffer whose data length to set.}}
	 {parameter:
	   {name: len}
	   {description: The buffer new data length of the buffer.  This must
	     be less than the buffer\'s capacity.}}
	 {return: LMI_TRUE on success, else LMI_FALSE.}
	 {note:  Other than for the LmiDataBufferEqual and LmiDataBufferLess
	   functions, LmiDataBufferGetRemainingReadableBitCount, and
	   LmiDataBufferWriteBuffer,
	   this value is unused by the LmiDataBuffer object;
	   it is intended only for users of the object, to represent the
	   length of the useful data in the buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiDataBufferSetLength(LmiDataBuffer* b, LmiSizeT len);


/**
   {function:
     {name: LmiDataBufferIsExclusive}
	 {parent: LmiDataBuffer}
	 {description: Test whether an LmiDataBuffer\'s reference count is
	   exactly 1, i.e. whether it is owned exclusively by a single owner.}
	 {prototype: LmiBool LmiDataBufferIsExclusive(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The buffer to test for exclusivity.}}
	 {return: LMI_TRUE if the buffer\'s reference count is exactly 1;
	   LMI_FALSE otherwise.}
   }
*/
LmiBool LmiDataBufferIsExclusive(const LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferMakeExclusive}
	 {parent: LmiDataBuffer}
	 {description: Make an LmiDataBuffer the exclusive owner of its
	   data.  This will copy the data\'s buffer if it was not previously
	   exclusively owned, and thus can invalidate previous data pointers.}
	 {prototype: LmiBool LmiDataBufferMakeExclusive(LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The buffer to test for exclusivity.}}
	 {return: LMI_TRUE on success, else LMI_FALSE.  On failure, the buffer
	   is unchanged.}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function does not affect the data buffer\'s read/write
	   position.}
   }
*/
LmiBool LmiDataBufferMakeExclusive(LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferEnsureExclusiveCapacity}
	 {parent: LmiDataBuffer}
	 {description: Ensure that an LmiDataBuffer is exclusively owned and has
	   a minimum capacity.  If it is not, the buffer will be reallocated.}
	 {prototype: LmiBool LmiDataBufferEnsureExclusiveCapacity(LmiDataBuffer* b, LmiSizeT newCapacity, LmiAllocator* a)}
	 {parameter:
	   {name: b}
	   {description: The buffer for which to ensure exclusive capacity.}}
	 {parameter:
	   {name: newCapacity}
	   {description: The new minimum exclusive capacity to ensure for the buffer.}}
	 {parameter:
	   {name: a}
	   {description: An allocator to use if the buffer needs to be reallocated }}
	 {return: LMI_TRUE on success, else LMI_FALSE.  On failure, the buffer
	   is unchanged.}
   }
*/
LmiBool LmiDataBufferEnsureExclusiveCapacity(LmiDataBuffer* b,
	LmiSizeT newCapacity, LmiAllocator* a);


/**
   {function:
     {name: LmiDataBufferEnsureExclusiveCapacityNoCopy}
	 {parent: LmiDataBuffer}
	 {description: Ensure that an LmiDataBuffer is exclusively owned and has
	   a minimum capacity.  If it is not, the buffer will be reallocated,
	   discarding its current contents and read/write pointer.}
	 {prototype: LmiBool LmiDataBufferEnsureExclusiveCapacityNoCopy(LmiDataBuffer* b, LmiSizeT newCapacity, LmiAllocator* a)}
	 {parameter:
	   {name: b}
	   {description: The buffer for which to ensure exclusive capacity.}}
	 {parameter:
	   {name: newCapacity}
	   {description: The new minimum exclusive capacity to ensure for the buffer.}}
	 {parameter:
	   {name: a}
	   {description: An allocator to use if the buffer needs to be reallocated }}
	 {return: LMI_TRUE on success, else LMI_FALSE.  On failure, the buffer
	   is unchanged.}
   }
*/
LmiBool LmiDataBufferEnsureExclusiveCapacityNoCopy(LmiDataBuffer* b,
	LmiSizeT newCapacity, LmiAllocator* a);


/**
   {function:
     {name: LmiDataBufferReadBits8}
	 {parent: LmiDataBuffer}
	 {description: Read up to 8 bits from an LmiDataBuffer and advance the
	   read position.}
	 {prototype: LmiUint8 LmiDataBufferReadBits8(LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 8.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to read beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint8 LmiDataBufferReadBits8(LmiDataBuffer* b, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferPeekBits8}
	 {parent: LmiDataBuffer}
	 {description: Read up to 8 bits from an LmiDataBuffer without advancing
	   the read position.}
	 {prototype: LmiUint8 LmiDataBufferPeekBits8(const LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 8.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to read beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint8 LmiDataBufferPeekBits8(const LmiDataBuffer* b, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferReadBits16}
	 {parent: LmiDataBuffer}
	 {description: Read up to 16 bits from an LmiDataBuffer and advance the
	   read position.}
	 {prototype: LmiUint16 LmiDataBufferReadBits16(LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 16.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to read beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint16 LmiDataBufferReadBits16(LmiDataBuffer* b, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferPeekBits16}
	 {parent: LmiDataBuffer}
	 {description: Read up to 16 bits from an LmiDataBuffer without advancing
	   the read position.}
	 {prototype: LmiUint16 LmiDataBufferPeekBits16(const LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 16.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to read beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint16 LmiDataBufferPeekBits16(const LmiDataBuffer* b, LmiSizeT nBits);

/**
   {function:
     {name: LmiDataBufferReadBits32}
	 {parent: LmiDataBuffer}
	 {description: Read up to 32 bits from an LmiDataBuffer and advance the
	   read position.}
	 {prototype: LmiUint32 LmiDataBufferReadBits32(LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 32.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to read beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint32 LmiDataBufferReadBits32(LmiDataBuffer* b, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferPeekBits32}
	 {parent: LmiDataBuffer}
	 {description: Read up to 32 bits from an LmiDataBuffer without advancing
	   the read position.}
	 {prototype: LmiUint32 LmiDataBufferPeekBits32(const LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 32.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to read beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint32 LmiDataBufferPeekBits32(const LmiDataBuffer* b, LmiSizeT nBits);

/**
   {function:
     {name: LmiDataBufferReadBits64}
	 {parent: LmiDataBuffer}
	 {description: Read up to 64 bits from an LmiDataBuffer and advance the
	   read position.}
	 {prototype: LmiUint64 LmiDataBufferReadBits64(LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 64.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to ready beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint64 LmiDataBufferReadBits64(LmiDataBuffer* b, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferPeekBits64}
	 {parent: LmiDataBuffer}
	 {description: Read up to 64 bits from an LmiDataBuffer without advancing
	   the read position.}
	 {prototype: LmiUint64 LmiDataBufferPeekBits64(const LmiDataBuffer* b,
	   LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be read.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be read.  This value must not be
	     more than 64.}}
	 {return: The value of the next nBits bits of the buffer.}
	 {note: If an attempt is made to read beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it reads into unmapped
	   memory.)}
	 {note: Reading from allocated but uninitialized memory will return
	   an unspecified value, but will not fail.}
   }
*/
LMI_INLINE_DECLARATION LmiUint64 LmiDataBufferPeekBits64(const LmiDataBuffer* b, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferSkipBits}
	 {parent: LmiDataBuffer}
	 {description: Advance an LmiDataBuffer\'s read position without reading
	   any bits.}
	 {prototype: void LmiDataBufferSkipBits(LmiDataBuffer* b, LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be skipped.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be skipped.}}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferSkipBits(LmiDataBuffer* b, LmiSizeT nBits);	 


/**
   {function:
     {name: LmiDataBufferSkipBytes}
	 {parent: LmiDataBuffer}
	 {description: Advance an LmiDataBuffer\'s read position by a whole number
	   of bytes without reading any bits.}
	 {prototype: void LmiDataBufferSkipBytes(LmiDataBuffer* b, LmiSizeT nBytes)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be skipped.}}
	 {parameter:
	   {name: nBytes}
	   {description: The number of bytes to be skipped.}}
	 {note: This is equivalent to, but potentially more efficient than,
	   LmiDataBufferSkipBits(b, nBytes * 8).}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferSkipBytes(LmiDataBuffer* b, LmiSizeT nBytes);


/**
   {function:
     {name: LmiDataBufferSkipAlignBits}
	 {parent: LmiDataBuffer}
	 {description: Advance an LmiDataBuffer\'s read position so it is aligned
	   to a multiple of a given number of bits, without reading any bits.}
	 {prototype: LmiSizeT LmiDataBufferSkipAlignBits(LmiDataBuffer* b, LmiSizeT nAlign)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which bits are to be skipped.}}
	 {parameter:
	   {name: nAlign}
	   {description: The width to which the read position should be aligned.
	     For example, for byte alignment, nAlign = 8}}
	 {return: The number of bits skipped in order to align the read position.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferSkipAlignBits(LmiDataBuffer* b, LmiSizeT nAlign);



/**
   {function:
     {name: LmiDataBufferSetBitPosition}
	 {parent: LmiDataBuffer}
	 {description: Set an LmiDataBuffer\'s read or write position to a
	   specified absolute position.}
	 {prototype: void LmiDataBufferSetBitPosition(LmiDataBuffer* b, LmiSizeT pos)}
	 {parameter:
	   {name: b}
	   {description: The data buffer in which to set the read or write
	     position.}}
	 {parameter:
	   {name: pos}
	   {description: The position in the buffer at which bits should next be
	     read or written.  This value must not be greater than the buffer\'s
		 capacity in bits.}}
	 {note: If a buffer is both read to and written from, this function
	   must be called between reads and writes, to reset the buffer position.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferSetBitPosition(LmiDataBuffer* b, LmiSizeT pos);	 


/**
   {function:
     {name: LmiDataBufferGetBitPosition}
	 {parent: LmiDataBuffer}
	 {description: Get the current value of an LmiDataBuffer\'s read or
	   write position.}
	 {prototype: LmiSizeT LmiDataBufferGetBitPosition(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which to get the read or write
	     position.}}
	 {return: The position from which bits will next be read or written.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferGetBitPosition(const LmiDataBuffer* b);	 


/**
   {function:
     {name: LmiDataBufferGetRemainingReadableBitCount}
	 {parent: LmiDataBuffer}
	 {description: Get the number of bits remaining to be read in an
	   LmiDataBuffer before its length is reached.}
	 {prototype: LmiSizeT LmiDataBufferGetRemainingReadableBitCount(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which to get the number of 
	     remaining readable bits.}}
	 {return: The number of remaining readable bits in the buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferGetRemainingReadableBitCount(const LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferWriteBits8}
	 {parent: LmiDataBuffer}
	 {description: Write up to 8 bits to an LmiDataBuffer and advance the
	   write position.}
	 {prototype: void LmiDataBufferWriteBits8(LmiDataBuffer* b,
	   LmiUint8 val, LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer to which bits are to be written.}}
	 {parameter:
	   {name: val}
	   {description: The value to be written.  If this is greater than
	     2^nBits, only the nBits least significant bits of val are written.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be written.  This value must not be
	     more than 8.}}
	 {note: If an attempt is made to write beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it writes into unmapped
	   memory.)}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function sets the buffer\'s length to correspond to the byte
	   containing the last bits written.}
	 {note: Any bits previously in the buffer after the write position are
	   undefined after this function is called.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferWriteBits8(LmiDataBuffer* b, LmiUint8 val, LmiSizeT nBits);



/**
   {function:
     {name: LmiDataBufferWriteBits16}
	 {parent: LmiDataBuffer}
	 {description: Write up to 16 bits to an LmiDataBuffer and advance the
	   write position.}
	 {prototype: void LmiDataBufferWriteBits16(LmiDataBuffer* b,
	   LmiUint16 val, LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer to which bits are to be written.}}
	 {parameter:
	   {name: val}
	   {description: The value to be written.  If this is greater than
	     2^nBits, only the nBits least significant bits of val are written.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be written.  This value must not be
	     more than 16.}}
	 {note: If an attempt is made to write beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it writes into unmapped
	   memory.)}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function sets the buffer\'s length to correspond to the byte
	   containing the last bits written.}
	 {note: Any bits previously in the buffer after the write position are
	   undefined after this function is called.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferWriteBits16(LmiDataBuffer* b, LmiUint16 val, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferWriteBits32}
	 {parent: LmiDataBuffer}
	 {description: Write up to 32 bits to an LmiDataBuffer and advance the
	   write position.}
	 {prototype: void LmiDataBufferWriteBits32(LmiDataBuffer* b,
	   LmiUint32 val, LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer to which bits are to be written.}}
	 {parameter:
	   {name: val}
	   {description: The value to be written.  If this is greater than
	     2^nBits, only the nBits least significant bits of val are written.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be written.  This value must not be
	     more than 32.}}
	 {note: If an attempt is made to write beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it writes into unmapped
	   memory.)}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function sets the buffer\'s length to correspond to the byte
	   containing the last bits written.}
	 {note: Any bits previously in the buffer after the write position are
	   undefined after this function is called.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferWriteBits32(LmiDataBuffer* b, LmiUint32 val, LmiSizeT nBits);


/**
   {function:
     {name: LmiDataBufferWriteBits64}
	 {parent: LmiDataBuffer}
	 {description: Write up to 64 bits to an LmiDataBuffer and advance the
	   write position.}
	 {prototype: void LmiDataBufferWriteBits64(LmiDataBuffer* b,
	   LmiUint64 val, LmiSizeT nBits)}
	 {parameter:
	   {name: b}
	   {description: The data buffer to which bits are to be written.}}
	 {parameter:
	   {name: val}
	   {description: The value to be written.  If this is greater than
	     2^nBits, only the nBits least significant bits of val are written.}}
	 {parameter:
	   {name: nBits}
	   {description: The number of bits to be written.  This value must not be
	     more than 64.}}
	 {note: If an attempt is made to write beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it writes into unmapped
	   memory.)}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function sets the buffer\'s length to correspond to the byte
	   containing the last bits written.}
	 {note: Any bits previously in the buffer after the write position are
	   undefined after this function is called.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferWriteBits64(LmiDataBuffer* b, LmiUint64 val, LmiSizeT nBits);

/**
   {function:
     {name: LmiDataBufferWriteAlignBits}
	 {parent: LmiDataBuffer}
	 {description: Write bits to an LmiDataBuffer so its write position
	   is aligned to a multiple of a given number of bits.}
	 {prototype: LmiSizeT LmiDataBufferWriteAlignBits(LmiDataBuffer* b,
	   LmiBool val, LmiSizeT nAlign)}
	 {parameter:
	   {name: b}
	   {description: The data buffer to which bits are to be written.}}
	 {parameter:
	   {name: val}
	   {description: The value to be written.  If this is 1 or LMI_TRUE,
	     the buffer will be filled with 1 bits until the alignment is reached,
		 otherwise (for 0 or LMI_FALSE) it will be filled with 0 bits.}}
	 {parameter:
	   {name: nAlign}
	   {description: The width to which the write position should be aligned.
	     For example, for byte alignment, nAlign = 8.}}
	 {return: The number of bits written in order to align the write position.}
	 {note: If an attempt is made to write beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it writes into unmapped
	   memory.)}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function sets the buffer\'s length to correspond to the byte
	   containing the last bits written.}
	 {note: Any bits previously in the buffer after the write position are
	   undefined after this function is called.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferWriteAlignBits(LmiDataBuffer* b, LmiBool val, LmiSizeT nAlign);


/**
   {function:
     {name: LmiDataBufferWriteBuffer}
	 {parent: LmiDataBuffer}
	 {description: Write the contents of an LmiDataBuffer into another one,
	 	at the latter\'s write position.}
	 {prototype: void LmiDataBufferWriteBuffer(LmiDataBuffer* b,
	   const LmiDataBuffer* src)}
	 {parameter:
	   {name: b}
	   {description: The data buffer into which buffer contents are to be
	     written.  Its bit position must be a multiple of 8.}}
	 {parameter:
	   {name: src}
	   {description: The source buffer to be written.}}
	 {note: If an attempt is made to write beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it writes into unmapped
	   memory.)}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function sets the buffer\'s length to correspond to the
	   last byte written.}
	 {note: Any bits previously in the buffer after the write position are
	   undefined after this function is called.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferWriteBuffer(LmiDataBuffer* b, const LmiDataBuffer* src);


/**
   {function:
	 {name: LmiDataBufferWriteBytes}
	 {parent: LmiDataBuffer}
	 {description: Write the contents of a block of memory to an
	   LmiDataBuffer and advance the write position.}
	 {prototype: void LmiDataBufferWriteBytes(LmiDataBuffer* b,
	   const LmiUint8* data, LmiSizeT numBytes)}
	 {parameter:
	   {name: b}
	   {description: The data buffer into which buffer contents are to be
	     written.  Its bit position must be a multiple of 8.}}
	 {parameter:
	   {name: data}
	   {description: The data buffer to be written.}}
	 {parameter:
	   {name: numBytes}
	   {description: The number of bytes of data to be written.}}
	 {note: If an attempt is made to write beyond the buffer\'s capacity,
	   this function is undefined.  (In debug mode, it will typically trigger
	   an assertion; in release mode, it may crash if it writes into unmapped
	   memory.)}
	 {note: Except in very unusual circumstances, a caller should ensure
	   that it is the exclusive owner of a data buffer before writing to it.}
	 {note: This function sets the buffer\'s length to correspond to the
	   last byte written.}
	 {note: Any bits previously in the buffer after the write position are
	   undefined after this function is called.}
   }
*/
LMI_INLINE_DECLARATION void LmiDataBufferWriteBytes(LmiDataBuffer* b, const LmiUint8* data,
	LmiSizeT numBytes);


/**
   {function:
     {name: LmiDataBufferGetRemainingWritableBitCount}
	 {parent: LmiDataBuffer}
	 {description: Get the number of bits remaining to be written to an
	   LmiDataBuffer before its capacity is reached.}
	 {prototype: LmiSizeT LmiDataBufferGetRemainingWritableBitCount(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which to get the number of 
	     remaining writable bits.}}
	 {return: The number of remaining writable bits in the buffer.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferGetRemainingWritableBitCount(const LmiDataBuffer* b);


/**
   {function:
	 {name: LmiDataBufferGetRemainingWritableByteCount}
	 {parent: LmiDataBuffer}
	 {description: Get the number of bytes remaining to be written to an
	   LmiDataBuffer before its capacity is reached.}
	 {prototype: LmiSizeT LmiDataBufferGetRemainingWritableByteCount(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The data buffer from which to get the number of 
	     remaining writable bytes.}}
	 {return: The number of remaining writable bytes in the buffer.  If the
	   bit position is not aligned to a multiple of 8, this includes the
	   partial byte that remains to be written.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiDataBufferGetRemainingWritableByteCount(const LmiDataBuffer* b);


/**
   {function:
     {name: LmiDataBufferGetAllocator}
	 {parent: LmiDataBuffer}
	 {description: Get the allocator used by an LmiDataBuffer.}
	 {prototype: LmiAllocator* LmiDataBufferGetAllocator(const LmiDataBuffer* b)}
	 {parameter:
	   {name: b}
	   {description: The data buffer whose allocator to get.}}
	 {return: The allocator of the specified LmiDataBuffer.}
   }
*/
LMI_INLINE_DECLARATION LmiAllocator* LmiDataBufferGetAllocator(const LmiDataBuffer* b);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiDataBufferInline.h>
#endif

#endif /* LMI_DATA_BUFFER_H_ */
