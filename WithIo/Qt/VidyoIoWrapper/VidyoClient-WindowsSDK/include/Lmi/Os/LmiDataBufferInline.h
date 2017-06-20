/** {file:
	  {name: LmiDataBufferInline.h}
	  {description: Inline functions for LmiDataBuffer.}
	  {copyright:
	  	(c) 2006-2007 Vidyo, Inc.,
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

#include <Lmi/Utils/LmiAssert.h>
#include <Lmi/Utils/LmiStdCLib.h>

#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
#include <Lmi/Os/LmiMemory.h>
#endif

/** {implementation: {name: LmiDataBufferImplGetData_}} */
LMI_INLINE LmiUint8* LmiDataBufferImplGetData_(LmiDataBufferImpl_* d)
{
	if (d == NULL) return NULL;
	return ((LmiUint8*)d) + sizeof(LmiDataBufferImpl_);
}

LMI_INLINE void LmiDataBufferImplIncrementRefCount_(LmiDataBufferImpl_* d)
{
	LmiInt newVal;
	if (d == NULL) return;
	newVal = LmiAtomicIntegerIncrement(&d->referenceCount);
	LmiAssert(newVal > 1);
}


LMI_INLINE void LmiDataBufferImplDecrementRefCount_(LmiDataBufferImpl_* d)
{
	LmiInt newVal;

	if (d == NULL) return;

	newVal = LmiAtomicIntegerDecrement(&d->referenceCount);
	LmiAssert(newVal >= 0);

	if (newVal == 0) {
		LmiDataBufferImplDealloc_(d);
	}
}


/** {implementation: {name: LmiDataBufferGetCapacity}} */
LMI_INLINE LmiSizeT LmiDataBufferGetCapacity(const LmiDataBuffer* b)
{
	if (b->impl == NULL) { return 0; }

	return (b->impl->capacity -
		(b->data - LmiDataBufferImplGetData_((LmiDataBufferImpl_*)b->impl)));
}


/** {implementation: {name: LmiDataBufferConstruct}} */
LMI_INLINE LmiDataBuffer*
LmiDataBufferConstruct(LmiDataBuffer* b, LmiSizeT capacity, LmiAllocator* a)
{
	if (capacity == 0) {
		b->impl = NULL;
		b->data = NULL;
		b->length = 0;
		b->bitPos = 0;
#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
		b->dummyAlloc = NULL;
#endif
		return b;
	}

	LmiAssert(capacity < (LMI_SIZE_T_MAX / 8));

	b->impl = LmiDataBufferImplAlloc_(capacity, a);
	if (b->impl == NULL) return NULL;

#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	b->dummyAlloc = LmiMemoryAllocate(LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_);
	if (b->dummyAlloc == NULL) {
		LmiDataBufferImplDealloc_(b->impl);
		return NULL;
	}
#endif

	b->data = LmiDataBufferImplGetData_(b->impl);
	b->length = 0;
	b->bitPos = 0;

	return b;
}


/** {implementation: {name: LmiDataBufferConstructCopy}} */
LMI_INLINE LmiDataBuffer*
LmiDataBufferConstructCopy(LmiDataBuffer* b, const LmiDataBuffer* orig)
{
#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	if (orig->dummyAlloc == NULL) {
		b->dummyAlloc = NULL;
	}
	else {
		b->dummyAlloc =
			LmiMemoryAllocate(LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_);
		if (b->dummyAlloc == NULL) {
			return NULL;
		}
	}
#endif

	LmiDataBufferImplIncrementRefCount_(orig->impl);
	b->impl = orig->impl;
	b->data = orig->data;
	b->length = orig->length;
	b->bitPos = 0;

	return b;
}


/** {implementation: {name: LmiDataBufferConstructSubbuffer}} */
LMI_INLINE LmiDataBuffer* LmiDataBufferConstructSubbuffer(LmiDataBuffer* b,
	const LmiDataBuffer* orig, LmiSizeT pos, LmiSizeT len)
{
	LmiSizeT origCapacity = LmiDataBufferGetCapacity(orig);
	if (pos > origCapacity || len > origCapacity - pos) {
		return NULL;
	}

#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	if (orig->dummyAlloc == NULL) {
		b->dummyAlloc = NULL;
	}
	else {
		b->dummyAlloc =
			LmiMemoryAllocate(LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_);
		if (b->dummyAlloc == NULL) {
			return NULL;
		}
	}
#endif

	LmiDataBufferImplIncrementRefCount_(orig->impl);
	b->impl = orig->impl;
	b->data = orig->data + pos;
	b->length = len;
	b->bitPos = 0;

	return b;
}


/** {implementation: {name: LmiDataBufferConstructSubbuffer}} */
LMI_INLINE LmiDataBuffer*
LmiDataBufferConstructSubbufferAtReadPosition(LmiDataBuffer* b,
	LmiDataBuffer* orig, LmiSizeT len)
{
	if (orig->bitPos % 8 != 0) {
		return NULL;
	}
	if (len > (orig->length - orig->bitPos / 8)) {
		return NULL;
	}

#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	if (orig->dummyAlloc == NULL) {
		b->dummyAlloc = NULL;
	}
	else {
		b->dummyAlloc =
			LmiMemoryAllocate(LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_);
		if (b->dummyAlloc == NULL) {
			return NULL;
		}
	}
#endif

	LmiDataBufferImplIncrementRefCount_(orig->impl);
	b->impl = orig->impl;
	b->data = orig->data + orig->bitPos / 8;
	b->length = len;
	b->bitPos = 0;

	orig->bitPos += len * 8;

	return b;
}


/** {implementation: {name: LmiDataBufferAssign}} */
LMI_INLINE LmiDataBuffer* LmiDataBufferAssign(LmiDataBuffer* b,
	const LmiDataBuffer* orig)
{
#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	if (orig->dummyAlloc == NULL && b->dummyAlloc != NULL) {
		LmiMemoryFree(b->dummyAlloc);
		b->dummyAlloc = NULL;
	}
	else if (orig->dummyAlloc != NULL && b->dummyAlloc == NULL) {
		b->dummyAlloc =
			LmiMemoryAllocate(LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_);
		if (b->dummyAlloc == NULL) {
			return NULL;
		}
	}
#endif

	if (orig->impl != b->impl) {
		LmiDataBufferImplIncrementRefCount_(orig->impl);
		LmiDataBufferImplDecrementRefCount_(b->impl);
		b->impl = orig->impl;
	}
	b->data = orig->data;
	b->length = orig->length;
	b->bitPos = 0;

	return b;
}


/** {implementation: {name: LmiDataBufferAssignSubbuffer}} */
LMI_INLINE LmiDataBuffer* LmiDataBufferAssignSubbuffer(LmiDataBuffer* b,
	const LmiDataBuffer* orig, LmiSizeT pos, LmiSizeT len)
{
	LmiSizeT origCapacity = LmiDataBufferGetCapacity(orig);
	if (pos > origCapacity || len > origCapacity - pos) {
		return NULL;
	}

#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	if (orig->dummyAlloc == NULL && b->dummyAlloc != NULL) {
		LmiMemoryFree(b->dummyAlloc);
		b->dummyAlloc = NULL;
	}
	else if (orig->dummyAlloc != NULL && b->dummyAlloc == NULL) {
		b->dummyAlloc =
			LmiMemoryAllocate(LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_);
		if (b->dummyAlloc == NULL) {
			return NULL;
		}
	}
#endif

	if (orig->impl != b->impl) {
		LmiDataBufferImplIncrementRefCount_(orig->impl);
		LmiDataBufferImplDecrementRefCount_(b->impl);
		b->impl = orig->impl;
	}
	b->data = orig->data + pos;
	b->length = len;
	b->bitPos = 0;

	return b;
}


/** {implementation: {name: LmiDataBufferAssignSubbuffer}} */
LMI_INLINE LmiDataBuffer*
LmiDataBufferAssignSubbufferAtReadPosition(LmiDataBuffer* b,
	LmiDataBuffer* orig, LmiSizeT len)
{
	if (orig->bitPos % 8 != 0) {
		return NULL;
	}
	if (len > (orig->length - orig->bitPos / 8)) {
		return NULL;
	}

#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	if (orig->dummyAlloc == NULL && b->dummyAlloc != NULL) {
		LmiMemoryFree(b->dummyAlloc);
		b->dummyAlloc = NULL;
	}
	else if (orig->dummyAlloc != NULL && b->dummyAlloc == NULL) {
		b->dummyAlloc =
			LmiMemoryAllocate(LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_SIZE_);
		if (b->dummyAlloc == NULL) {
			return NULL;
		}
	}
#endif

	if (orig->impl != b->impl) {
		LmiDataBufferImplIncrementRefCount_(orig->impl);
		LmiDataBufferImplDecrementRefCount_(b->impl);
		b->impl = orig->impl;
	}

	b->data = orig->data + orig->bitPos / 8;
	b->length = len;
	b->bitPos = 0;

	orig->bitPos += len * 8;

	return b;
}


/** {implementation: {name: LmiDataBufferDestruct}} */
LMI_INLINE void LmiDataBufferDestruct(LmiDataBuffer* b)
{
#if LMI_DATA_BUFFER_DEBUG_DUMMY_ALLOC_
	if (b->dummyAlloc != NULL) {
		LmiMemoryFree(b->dummyAlloc);
	}
#endif

	LmiDataBufferImplDecrementRefCount_(b->impl);
}


/** {implementation: {name: LmiDataBufferSwap}} */
LMI_INLINE LmiBool LmiDataBufferSwap(LmiDataBuffer* a, LmiDataBuffer* b)
{
	/* Swapping changes neither buffer's impl's count, so we can just copy
	   fields. */
	LmiDataBuffer tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

	return LMI_TRUE;
}


/** {implementation: {name: LmiDataBufferGetData}} */
LMI_INLINE LmiUint8* LmiDataBufferGetData(LmiDataBuffer* b)
{
	return b->data;
}


/** {implementation: {name: LmiDataBufferGetDataConst}} */
LMI_INLINE const LmiUint8* LmiDataBufferGetDataConst(const LmiDataBuffer* b)
{
	return b->data;
}


/** {implementation: {name: LmiDataBufferGetLength}} */
LMI_INLINE LmiSizeT LmiDataBufferGetLength(const LmiDataBuffer* b)
{
	return b->length;
}


/** {implementation: {name: LmiDataBufferSetLength}} */
LMI_INLINE LmiBool LmiDataBufferSetLength(LmiDataBuffer* b, LmiSizeT len)
{
	if (len > LmiDataBufferGetCapacity(b)) {
		return LMI_FALSE;
	}
	b->length = len;

	return LMI_TRUE;
}



/** {implementation: {name: LmiDataBufferSkipBits}} */
LMI_INLINE void LmiDataBufferSkipBits(LmiDataBuffer* b, LmiSizeT nBits)
{
	b->bitPos += nBits;
}


/** {implementation: {name: LmiDataBufferSkipBytes}} */
LMI_INLINE void LmiDataBufferSkipBytes(LmiDataBuffer* b, LmiSizeT nBytes)
{
	b->bitPos += nBytes * 8;
}


/** {implementation: {name: LmiDataBufferSkipAlignBits}} */
LMI_INLINE LmiSizeT LmiDataBufferSkipAlignBits(LmiDataBuffer* b,
	LmiSizeT nAlign)
{
    LmiSizeT nBits = nAlign - (b->bitPos % nAlign);

    if (nBits < nAlign) {
        LmiDataBufferSkipBits(b, nBits);
		return nBits;
	}
    else
        return 0;
}



/** {implementation: {name: LmiDataBufferSetBitPosition}} */
LMI_INLINE void LmiDataBufferSetBitPosition(LmiDataBuffer* b, LmiSizeT pos)
{
	b->bitPos = pos;
}


/** {implementation: {name: LmiDataBufferGetBitPosition}} */
LMI_INLINE LmiSizeT LmiDataBufferGetBitPosition(const LmiDataBuffer* b)
{
	return b->bitPos;
}


/** {implementation: {name: LmiDataBufferGetRemainingReadableBitCount}} */
LMI_INLINE LmiSizeT LmiDataBufferGetRemainingReadableBitCount(const LmiDataBuffer* b)
{
	LmiSizeT bitLength = b->length * 8;

	if (bitLength < b->bitPos) {
		return 0;
	}
	return bitLength - b->bitPos;
}


/** {implementation: {name: LmiDataBufferGetRemainingWritableBitCount}} */
LMI_INLINE LmiSizeT LmiDataBufferGetRemainingWritableBitCount(const LmiDataBuffer* b)
{
	LmiSizeT bitCapacity = LmiDataBufferGetCapacity(b) * 8;

	LmiAssert(bitCapacity >= b->bitPos);

	return bitCapacity - b->bitPos;

}


/** {implementation: {name: LmiDataBufferGetRemainingWritableByteCount}} */
LMI_INLINE LmiSizeT LmiDataBufferGetRemainingWritableByteCount(const LmiDataBuffer* b)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT capacity = LmiDataBufferGetCapacity(b);

	LmiAssert(bytePos <= capacity);

	return capacity - bytePos;
}


/** {implementation: {name: LmiDataBufferPeekBits8}} */
LMI_INLINE LmiUint8 LmiDataBufferPeekBits8(const LmiDataBuffer* b,
	LmiSizeT nBits)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    const LmiUint8* pVal = b->data + bytePos;
    LmiUint8 ret;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 8);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
	ret = (LmiUint8)(pVal[0] << lastByteBit);
    ret |= (LmiUint8)(pVal[1] >> (8 - lastByteBit));
    return (LmiUint8)(ret >> (8 - nBits));
}


/** {implementation: {name: LmiDataBufferReadBits8}} */
LMI_INLINE LmiUint8 LmiDataBufferReadBits8(LmiDataBuffer* b, LmiSizeT nBits)
{
	LmiUint8 ret;

	ret = LmiDataBufferPeekBits8(b, nBits);
	LmiDataBufferSkipBits(b, nBits);
	return ret;
}


/** {implementation: {name: LmiDataBufferPeekBits16}} */
LMI_INLINE LmiUint16 LmiDataBufferPeekBits16(const LmiDataBuffer* b,
	LmiSizeT nBits)
{
    LmiUint16 ret;
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    const LmiUint8* pVal = b->data + bytePos;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 16);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
	ret = (LmiUint16)((((LmiUint16)(pVal[0]) << 8) | (LmiUint16)(pVal[1])) << lastByteBit);
	ret |= (LmiUint16)(pVal[2]) >> (8 - lastByteBit);
    return (LmiUint16)(ret >> (16 - nBits));
}


/** {implementation: {name: LmiDataBufferReadBits16}} */
LMI_INLINE LmiUint16 LmiDataBufferReadBits16(LmiDataBuffer* b, LmiSizeT nBits)
{
	LmiUint16 ret;

	ret = LmiDataBufferPeekBits16(b, nBits);
	LmiDataBufferSkipBits(b, nBits);
	return ret;
}


/** {implementation: {name: LmiDataBufferPeekBits32}} */
LMI_INLINE LmiUint32 LmiDataBufferPeekBits32(const LmiDataBuffer* b,
	LmiSizeT nBits)
{
    LmiUint32 ret;
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    const LmiUint8* pVal = b->data + bytePos;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 32);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
	ret = (LmiUint32)((((LmiUint32)(pVal[0]) << 24) | ((LmiUint32)(pVal[1]) << 16) |
		((LmiUint32)(pVal[2]) << 8) | (LmiUint32)(pVal[3])) << lastByteBit);
    ret |= (LmiUint32)((LmiUint32)(pVal[4]) >> (8 - lastByteBit));
    return (LmiUint32)(ret >> (32 - nBits));
}


/** {implementation: {name: LmiDataBufferReadBits32}} */
LMI_INLINE LmiUint32 LmiDataBufferReadBits32(LmiDataBuffer* b, LmiSizeT nBits)
{
	LmiUint32 ret;

	ret = LmiDataBufferPeekBits32(b, nBits);
	LmiDataBufferSkipBits(b, nBits);
	return ret;
}


/** {implementation: {name: LmiDataBufferPeekBits64}} */
LMI_INLINE LmiUint64 LmiDataBufferPeekBits64(const LmiDataBuffer* b, LmiSizeT nBits)
{
    LmiUint64 ret;
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    const LmiUint8* pVal = b->data + bytePos;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 64);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
	ret = (LmiUint64)((((LmiUint64)(pVal[0]) << 56) | ((LmiUint64)(pVal[1]) << 48) |
		((LmiUint64)(pVal[2]) << 40) | ((LmiUint64)(pVal[3]) << 32) |
		((LmiUint64)(pVal[4]) << 24) | ((LmiUint64)(pVal[5]) << 16) |
		((LmiUint64)(pVal[6]) << 8) | (LmiUint64)(pVal[7])) << lastByteBit);
	ret |= (LmiUint64)((LmiUint64)(pVal[8]) >> (8 - lastByteBit));
	return (LmiUint64)(ret >> (64 - nBits));
}


/** {implementation: {name: LmiDataBufferReadBits64}} */
LMI_INLINE LmiUint64 LmiDataBufferReadBits64(LmiDataBuffer* b, LmiSizeT nBits)
{
	LmiUint64 ret;

	ret = LmiDataBufferPeekBits64(b, nBits);
	LmiDataBufferSkipBits(b, nBits);
	return ret;
}


/** {implementation: {name: LmiDataBufferWriteBits8}} */
LMI_INLINE void LmiDataBufferWriteBits8(LmiDataBuffer* b, LmiUint8 val,
	LmiSizeT nBits)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    LmiUint8* pVal = b->data + bytePos;
	LmiUint8 lastByte;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 8);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
    val <<= 8 - nBits;

	lastByte = (LmiUint8)(val & ((LmiUint8)(0xFF) >> (8 - lastByteBit)));
	val >>= lastByteBit;

    pVal[0] &= (LmiUint8)(0xFF << (8 - lastByteBit));
	pVal[0] |= (LmiUint8)(val);
    pVal[1] = (LmiUint8)(lastByte << (8 - lastByteBit));

	b->bitPos += nBits;
	b->length = (b->bitPos - 1)/8 + 1;
}


/** {implementation: {name: LmiDataBufferWriteBits16}} */
LMI_INLINE void LmiDataBufferWriteBits16(LmiDataBuffer* b, LmiUint16 val,
	LmiSizeT nBits)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    LmiUint8* pVal = b->data + bytePos;
	LmiUint8 lastByte;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 16);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
    val <<= 16 - nBits;

	lastByte = (LmiUint8)(val & ((LmiUint8)(0xFF) >> (8 - lastByteBit)));
	val >>= lastByteBit;

    pVal[0] &= (LmiUint8)(0xFF << (8 - lastByteBit));
	pVal[0] |= (LmiUint8)(val >> 8);
    pVal[1] = (LmiUint8)(val);
    pVal[2] = (LmiUint8)(lastByte << (8 - lastByteBit));

	b->bitPos += nBits;
	b->length = (b->bitPos - 1)/8 + 1;
}


/** {implementation: {name: LmiDataBufferWriteBits32}} */
LMI_INLINE void LmiDataBufferWriteBits32(LmiDataBuffer* b, LmiUint32 val,
	LmiSizeT nBits)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    LmiUint8* pVal = b->data + bytePos;
	LmiUint8 lastByte;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 32);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
    val <<= 32 - nBits;

	lastByte = (LmiUint8)(val & ((LmiUint8)(0xFF) >> (8 - lastByteBit)));
	val >>= lastByteBit;

    pVal[0] &= (LmiUint8)(0xFF << (8 - lastByteBit));
	pVal[0] |= (LmiUint8)(val >> 24);
    pVal[1] = (LmiUint8)(val >> 16);
    pVal[2] = (LmiUint8)(val >> 8);
    pVal[3] = (LmiUint8)(val);
    pVal[4] = (LmiUint8)(lastByte << (8 - lastByteBit));

	b->bitPos += nBits;
	b->length = (b->bitPos - 1)/8 + 1;
}


/** {implementation: {name: LmiDataBufferWriteBits64}} */
LMI_INLINE void LmiDataBufferWriteBits64(LmiDataBuffer* b, LmiUint64 val,
	LmiSizeT nBits)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT lastByteBit = b->bitPos % 8;
    LmiUint8* pVal = b->data + bytePos;
	LmiUint8 lastByte;

	LmiAssert(nBits > 0);
	LmiAssert(nBits <= 64);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= nBits);
	
    val <<= 64 - nBits;

	lastByte = (LmiUint8)(val & ((LmiUint8)(0xFF) >> (8 - lastByteBit)));
	val >>= lastByteBit;

    pVal[0] &= (LmiUint8)(0xFF << (8 - lastByteBit));
	pVal[0] |= (LmiUint8)(val >> 56);
    pVal[1] = (LmiUint8)(val >> 48);
    pVal[2] = (LmiUint8)(val >> 40);
    pVal[3] = (LmiUint8)(val >> 32);
    pVal[4] = (LmiUint8)(val >> 24);
    pVal[5] = (LmiUint8)(val >> 16);
    pVal[6] = (LmiUint8)(val >> 8);
    pVal[7] = (LmiUint8)(val);
    pVal[8] = (LmiUint8)(lastByte << (8 - lastByteBit));

	b->bitPos += nBits;
	b->length = (b->bitPos - 1)/8 + 1;
}


/** {implementation: {name: LmiDataBufferWriteAlignBits}} */
LMI_INLINE LmiSizeT LmiDataBufferWriteAlignBits(LmiDataBuffer* b, LmiBool val,
	LmiSizeT nAlign)
{
	LmiSizeT nBits = nAlign - (b->bitPos % nAlign);
	if (nBits == nAlign) {
		/* Already aligned */
		return 0;
	}
	LmiDataBufferWriteBits64(b, val ? ~(LmiUint64)(0) : (LmiUint64)(0), nBits);
	return nBits;
}


/** {implementation: {name: LmiDataBufferWriteBuffer}} */
LMI_INLINE void LmiDataBufferWriteBuffer(LmiDataBuffer* b,
	const LmiDataBuffer* src)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT srcBytes = LmiDataBufferGetLength(src);
	LmiSizeT srcBits = srcBytes * 8;
    LmiUint8* pVal = b->data + bytePos;

	LmiAssert(b->bitPos % 8 == 0);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= srcBits);

	LmiMemCpy(pVal, LmiDataBufferGetDataConst(src), srcBytes);

	b->bitPos += srcBits;
	b->length += srcBytes;
}


/** {implementation: {name: LmiDataBufferWriteBytes}} */
LMI_INLINE void LmiDataBufferWriteBytes(LmiDataBuffer* b,
	const LmiUint8* src, LmiSizeT srcBytes)
{
	LmiSizeT bytePos = b->bitPos / 8;
	LmiSizeT srcBits = srcBytes * 8;
    LmiUint8* pVal = b->data + bytePos;

	LmiAssert(b->bitPos % 8 == 0);
	LmiAssert(LmiDataBufferGetRemainingWritableBitCount(b) >= srcBits);

	LmiMemCpy(pVal, src, srcBytes);

	b->bitPos += srcBits;
	b->length += srcBytes;
}


/** {implementation: {name: LmiDataBufferGetAllocator}} */
LMI_INLINE LmiAllocator* LmiDataBufferGetAllocator(const LmiDataBuffer* b)
{
	if (b->impl)
		return b->impl->alloc;
	else
		return NULL;	
}
