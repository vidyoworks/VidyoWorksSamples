/**
   {file: 
	{name: LmiBitstreamInline.h}
	{description: Definition of LmiBitstream inline functions.}
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


LMI_INLINE LmiUint8 LmiGetCeilLog2(LmiUint32 val)
{
	LmiUint8 i = 1;
	if(val > 0) {
		for(val = (val-1) >> 1; val > 0; ++i, val >>= 1) ;
		return i;
	}
	else
		return 0;
}


/* 
 * The encoder (writing) specific functions.
 * These functions are used for writing into a bitstream.
 */

extern const LmiUint8 LmiTblPrefix0s[256];
extern const LmiUint LmiTblLastByte[8];
extern const LmiInt LmiTblCast[33];

/** {implementation: {name: LmiPutBits}} */
LMI_INLINE LmiUint LmiPutBits(LmiBitstream *bs, LmiUint32 val, LmiUint size)
{
    LmiUint32 tmpVal; 
    LmiUint32 lastByte; 
    LmiUint8 *curBufByte = bs->buf + bs->totBytes;

    LmiAssert(size <= LMI_CODEC_MAX_BITS);

    val <<= LMI_CODEC_MAX_BITS - size;
    lastByte = val & LmiTblLastByte[bs->lastByteBit]; 
    tmpVal = val >> bs->lastByteBit;
    curBufByte[0] &= (0xFF << (8-bs->lastByteBit)) & 0xFF;
    curBufByte[0] |= tmpVal >> 24;
    curBufByte[1] = (tmpVal >> 16) & 0xFF;
    curBufByte[2] = (tmpVal >> 8) & 0xFF;
    curBufByte[3] = tmpVal & 0xFF;
    curBufByte[4] = lastByte << (8-bs->lastByteBit);

    bs->totBits += size;
    bs->totBytes = bs->totBits >> 3;
    bs->lastByteBit = (LmiUint)(bs->totBits - (bs->totBytes << 3));
    LmiAssert(bs->lastByteBit < 8);
    return size;
}

/** {implementation: {name: LmiPutOneBit}} */
LMI_INLINE LmiUint LmiPutOneBit(LmiBitstream *bs, LmiUint8 val, LmiUint size)
{
    LmiUint8 *curBufByte = bs->buf + bs->totBytes;
    LmiAssert(size <= 1);
    val <<= (8-size);
    val >>= bs->lastByteBit;
    curBufByte[0] &= (0xFF << (8-bs->lastByteBit)) & 0xFF;
    curBufByte[0] |= val;

    bs->totBits += size;
    bs->totBytes = bs->totBits >> 3;
    bs->lastByteBit = (LmiUint)(bs->totBits - (bs->totBytes << 3));
    LmiAssert(bs->lastByteBit < 8);
    return size;
}

/** {implementation: {name: LmiPutAnAlignedByte}} */
LMI_INLINE LmiUint LmiPutAnAlignedByte(LmiBitstream *bs, LmiUint8 val)
{
    LmiAssert(bs->lastByteBit == 0);
    bs->buf[bs->totBytes++] = val;
    bs->totBits += 8;
    return 8;
}

LMI_INLINE LmiUint LmiPutAlignedBytes(LmiBitstream *bs, LmiUint32 val, LmiUint bytes)
{
    LmiSizeT i;
    LmiAssert(bs->lastByteBit == 0);
    LmiAssert(bytes <= 4);
    for(i=0; i < bytes; ++i) {
        bs->buf[bs->totBytes++] = val >> (8*(bytes -i -1));
        bs->totBits += 8;
    }
    return bytes*8;
}

LMI_INLINE LmiUint LmiPutAnAlignedByteWithCarryOver(LmiBitstream *bs, LmiUint8 val, LmiSizeT startBytePos)
{
    LmiAssert(bs->lastByteBit == 0);
    if(bs->totBytes > 0) {
        LmiSizeT i = bs->totBytes -1;
        LmiAssert(startBytePos <= i);
        for(; i > startBytePos && bs->buf[i] == 0xFF; --i)
            bs->buf[i] = 0;

        LmiAssert(bs->buf[i] != 0xFF);
        bs->buf[i] += 1;
    }
    bs->buf[bs->totBytes++] = val;
    bs->totBits += 8;
    return 8;
}

/** {implementation: {name: LmiPutAlignBits}} */
LMI_INLINE LmiUint LmiPutAlignBits(LmiBitstream *bs, LmiUint align, LmiUint val)
{
    LmiUint bits = (LmiUint)(align - (bs->totBits % align));
    LmiAssert(align <= LMI_CODEC_MAX_BITS);
    if(bits < align) {
        if(val)
            return LmiPutBits(bs, 0xFFFFFFFF, bits);
        else
            return LmiPutBits(bs, 0, bits);
    }
    else 
        return 0;
}

/** {implementation: {name: LmiPutUe8}} */
LMI_INLINE LmiUint8 LmiPutUe8(LmiBitstream *bs, LmiUint8 val)
{
    LmiUint8 valTmp = ((LmiUint16)val+1) >> 1;
    LmiUint8 bitsPrefix = LmiTblPrefix0s[valTmp];
  
    LmiPutBits(bs, 0, bitsPrefix);
    LmiPutBits(bs, val+1, bitsPrefix+1);
    return (bitsPrefix<<1) + 1;
}
/** {implementation: {name: LmiPutUe16}} */
LMI_INLINE LmiUint8 LmiPutUe16(LmiBitstream *bs, LmiUint16 val)
{
    LmiUint16 valTmp = ((LmiUint32)val+1) >> 1;
    LmiUint8 isLessThan256 = ((LmiInt32)(val-256) >> 31) & 1;
    LmiUint8 bitsPrefix = LmiTblPrefix0s[valTmp>>8] + ((1-isLessThan256)<<3) + isLessThan256*LmiTblPrefix0s[valTmp&0xFF];

    LmiPutBits(bs, 0, bitsPrefix);
    LmiPutBits(bs, val+1, bitsPrefix+1);
    return (bitsPrefix<<1) + 1;
}
/** {implementation: {name: LmiPutUe32}} */
LMI_INLINE LmiUint8 LmiPutUe32(LmiBitstream *bs, LmiUint32 val)
{
    LmiUint bits = 0, i = 0;
    LmiUint32 tmpVal = (val+1) >> 1;
    LmiAssert(val < 0xFFFFFFFF);
    for(; tmpVal > 0; ++i, tmpVal >>= 1) ;
    bits += LmiPutBits(bs, 0, i);
    bits += LmiPutBits(bs, val+1, i+1);
    return bits;
}

/** {implementation: {name: LmiPutSe8}} */
LMI_INLINE LmiUint8 LmiPutSe8(LmiBitstream *bs, LmiInt8 val)
{
    if(val == 0)
        return LmiPutOneBit(bs, 1, 1);
    else if (val < 0) 
        return LmiPutUe16(bs, (LmiUint16)(-1 * (LmiInt16)val) << 1);
    else 
        return LmiPutUe8(bs, (val<<1)-1);
}
/** {implementation: {name: LmiPutSe16}} */
LMI_INLINE LmiUint8 LmiPutSe16(LmiBitstream *bs, LmiInt16 val)
{
    if(val == 0)
        return LmiPutOneBit(bs, 1, 1);
    else if (val < 0) 
		return LmiPutUe32(bs, (LmiUint32)(-1 * (LmiInt32)val) << 1);
    else 
        return LmiPutUe16(bs, (val<<1)-1);
}

/** {implementation: {name: LmiPutTe8}} */
LMI_INLINE LmiUint8 LmiPutTe8(LmiBitstream *bs, LmiUint8 x, LmiUint8 val)
{
    if(x > 1)
        return LmiPutUe8(bs, val);
    else {
        LmiAssert(val <= 1);
        return LmiPutOneBit(bs, 1-val, 1);
    }
}

/** {implementation: {name: LmiPutTrailingBits}} */
LMI_INLINE LmiUint LmiPutTrailingBits(LmiBitstream *bs)
{
    register LmiUint bits = 0;
    bits += LmiPutOneBit(bs, 1, 1); /* rbsp_stop_one_bit */
    bits += LmiPutAlignBits(bs, 8, 0); /* rbsp_alignment_zero_bit */
    return bits;
}

/* 
 * The encoder (writing) specific functions.
 * These functions are used for calculating bits needed for outputting the syntactic variable.
 */

LMI_INLINE LmiUint8 LmiBitsUe8(LmiUint8 val)
{
    LmiUint8 valTmp = ((LmiUint16)val+1) >> 1;
    LmiUint8 bitsPrefix = LmiTblPrefix0s[valTmp];
    return (bitsPrefix<<1) + 1;
}

LMI_INLINE LmiUint8 LmiBitsUe16(LmiUint16 val)
{
    LmiUint16 valTmp = ((LmiUint32)val+1) >> 1;
    LmiInt8 isLessThan256 = ((LmiInt16)(val-256) >> 15) & 1;
    LmiUint8 bitsPrefix = LmiTblPrefix0s[valTmp>>8] + ((1-isLessThan256)<<3) + isLessThan256*LmiTblPrefix0s[valTmp];
    return (bitsPrefix<<1) + 1;
}

LMI_INLINE LmiUint8 LmiBitsSe8(LmiInt val)
{
    if(val == 0)
        return 1;
    else if (val < 0) 
        return LmiBitsUe8((-1 * val)<<1);
    else 
        return LmiBitsUe8((val<<1)-1);
}

LMI_INLINE LmiUint8 LmiBitsSe16(LmiInt val)
{
    if(val == 0)
        return 1;
    else if (val < 0) 
        return LmiBitsUe16((-1 * val)<<1);
    else 
        return LmiBitsUe16((val<<1)-1);
}

LMI_INLINE LmiUint8 LmiBitsTe8(LmiUint x, LmiUint val)
{
    if(x > 1)
        return LmiBitsUe8(val);
    else 
        return 1;
}


/* 
 * The decoder (parsing) specific functions.
 * These functions are used for parsing from a bitstream.
 * Prior to calling the below functions, each NAL unit must
 * have been processed to strip emulation bytes.
 */

/** {implementation: {name: LmiSkipBits}} */
LMI_INLINE LmiUint LmiSkipBits(LmiBitstream *bs, LmiUint size)
{
    /* LmiAssert(bs->totBits + size <= (bs->bufLen << 3)); */
    bs->totBits += size;
    bs->totBytes = bs->totBits >> 3;
    bs->lastByteBit = (LmiUint)(bs->totBits - (bs->totBytes << 3));
    return size; 
}

/** {implementation: {name: LmiSkipBytes}} */
LMI_INLINE LmiUint LmiSkipBytes(LmiBitstream *bs, LmiUint size)
{
    /* LmiAssert(bs->totBits + (size << 3) <= (bs->bufLen << 3)); */
    bs->totBits += size << 3;
    bs->totBytes += size;
    return size << 3;
}

/** {implementation: {name: LmiNextBits}} */
LMI_INLINE LmiUint32 LmiNextBits(LmiBitstream *bs, LmiUint size) 
{
    LmiUint32 val = 0;
    LmiUint8 *curBufByte = bs->buf + bs->totBytes;
    /* static const LmiInt tblCast[33] = {
        0x00000000, 
        0x00000001, 0x00000003, 0x00000007, 0x0000000F, 0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF,
        0x000001FF, 0x000003FF, 0x000007FF, 0x00000FFF, 0x00001FFF, 0x00003FFF, 0x00007FFF, 0x0000FFFF,
        0x0001FFFF, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF, 0x001FFFFF, 0x003FFFFF, 0x007FFFFF, 0x00FFFFFF, 
        0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF, 0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF, 
    }; */
    /*  LmiAssert(size <= LMI_CODEC_MAX_BITS); */
    /*  LmiAssert(bs->totBits + size <= (bs->bufLen << 3)); */
    val = ((curBufByte[0] << 24) | (curBufByte[1] << 16) | (curBufByte[2] << 8) | curBufByte[3]) << bs->lastByteBit;
    val |= curBufByte[4] >> (8-bs->lastByteBit);
    return (val >> (LMI_CODEC_MAX_BITS-size))&LmiTblCast[size];
}

/** {implementation: {name: LmiNext3Bytes}} */
LMI_INLINE LmiUint32 LmiNext3Bytes(LmiBitstream *bs) 
{
    LmiUint8 *curBufByte = bs->buf + bs->totBytes;
    return (curBufByte[0] << 16) | (curBufByte[1] << 8) | curBufByte[2];
}

/** {implementation: {name: LmiGetBits}} */
LMI_INLINE LmiUint32 LmiGetBits(LmiBitstream *bs, LmiUint size)
{
    LmiUint32 val = LmiNextBits(bs, size);
    LmiSkipBits(bs, size);
    return val;
}

/** {implementation: {name: LmiGetOneBit}} */
LMI_INLINE LmiUint8 LmiGetOneBit(LmiBitstream *bs)
{
    LmiUint8 val = bs->buf[bs->totBytes];
    val = (val >> (7-bs->lastByteBit))&1;
    LmiSkipBits(bs, 1);
    return val;
}

/** {implementation: {name: LmiGetAnAlignedByte}} */
LMI_INLINE LmiUint8 LmiGetAnAlignedByte(LmiBitstream *bs)
{
    LmiAssert(bs->lastByteBit == 0);
    if(bs->totBytes < bs->infoLen) {
        bs->totBits += 8;
        bs->totBytes += 1;
        return bs->buf[bs->totBytes -1];
    }
    else
        return 0;
}

LMI_INLINE LmiUint32 LmiGetAlignedBytes(LmiBitstream *bs, LmiSizeT bytes)
{
    LmiUint32 val = 0;
    LmiAssert(bs->lastByteBit == 0 && bytes > 0 && bytes <= 4);
    do {
       --bytes;
        val |= bs->buf[bs->totBytes] << (bytes << 3);
        bs->totBits += 8;
        bs->totBytes += 1;
    } while(bytes);
    return val;
}

/** {implementation: {name: LmiGetAlignBits}} */
LMI_INLINE LmiUint LmiGetAlignBits(LmiBitstream *bs, LmiUint align)
{
    LmiUint bits = (LmiUint)(align - (bs->totBits % align));
    if(bits < align) 
        return LmiSkipBits(bs, bits);
    else
        return 0;
}

/** {implementation: {name: LmiGetUe8}} */
LMI_INLINE LmiUint8 LmiGetUe8(LmiBitstream *bs, LmiUint8 *val)
{
    LmiUint i = 0;
    for(; LmiGetOneBit(bs) == 0; ++i) ;
    *val = (1<<i) - 1 + LmiGetBits(bs, i&0xF);
    return (i<<1) + 1;
}
/** {implementation: {name: LmiGetUe16}} */
LMI_INLINE LmiUint8 LmiGetUe16(LmiBitstream *bs, LmiUint16 *val)
{
    LmiUint i = 0;
    for(; LmiGetOneBit(bs) == 0; ++i) ;
    *val = (1<<i) - 1 + LmiGetBits(bs, i&0x1F);
    return (i<<1) + 1;
}
/** {implementation: {name: LmiGetUe32}} */
LMI_INLINE LmiUint8 LmiGetUe32(LmiBitstream *bs, LmiUint32 *val)
{
    LmiUint i = 0;
    for(; LmiGetOneBit(bs) == 0; ++i) ;
    *val = (1<<i) - 1 + LmiGetBits(bs, i&0x3F);
    return (i<<1) + 1;
}

/** {implementation: {name: LmiGetSe8}} */
LMI_INLINE LmiUint8 LmiGetSe8(LmiBitstream *bs, LmiInt8 *val)
{
    LmiUint16 k;
    LmiUint8 bits = LmiGetUe16(bs, &k);
    LmiInt8 sign = k&0x1;
    k = (k+1)>>1;
    *val = sign*k - (1-sign)*k;
    return bits;
}
/** {implementation: {name: LmiGetSe16}} */
LMI_INLINE LmiUint8 LmiGetSe16(LmiBitstream *bs, LmiInt16 *val)
{
    LmiUint32 k;
    LmiUint8 bits = LmiGetUe32(bs, &k);
    LmiInt8 sign = k&0x1;
    k = (k+1)>>1;
    *val = sign*k - (1-sign)*k;
    return bits;    
}
/** {implementation: {name: LmiGetSe32}} */
/* here, the valid values are from -(2^31 - 1) to (2^31 - 1) */
LMI_INLINE LmiUint8 LmiGetSe32(LmiBitstream *bs, LmiInt32 *val)
{
    LmiUint32 k;
    LmiUint8 bits = LmiGetUe32(bs, &k);
    LmiInt8 sign = k&0x1;
    k = (k+1)>>1;
    *val = sign*k - (1-sign)*k; 
    return bits;    
}

/** {implementation: {name: LmiGetTe8}} */
LMI_INLINE LmiUint8 LmiGetTe8(LmiBitstream *bs, LmiUint8 k, LmiUint8 *val)
{
    if(k > 1) 
        return LmiGetUe8(bs, val);
    else  {
        *val = 1 - LmiGetOneBit(bs);
        return 1;
    }
}

/** {implementation: {name: LmiGetTrailingBits}} */
LMI_INLINE LmiUint LmiGetTrailingBits(LmiBitstream *bs)
{
    register LmiUint bits = 0;

    bits += 1;
    LmiGetOneBit(bs); /* rbsp_stop_one_bit */
    while(bs->lastByteBit != 0) {
        bits += 1;
        LmiGetOneBit(bs); /* rbsp_alignment_zero_bit */
    }
    return bits;
}

/** {implementation: {name: LmiMoreDataCavlc}} */
LMI_INLINE LmiInt LmiMoreDataCavlc(LmiBitstream *bs)
{
    if(bs->totBytes >= bs->infoLen)
        return 0;
    if(LmiNextBits(bs, 1) == 1) { /* possible rbsp_stop_one_bit */
        if(!bs->lastByteBit && bs->totBytes >= bs->infoLen)
            return 0;
        else if(LmiNextBits(bs, 8-bs->lastByteBit) == (1U<<(8-bs->lastByteBit-1)) && bs->totBytes+1 >= bs->infoLen)
            return 0;
    }
    return 1;
}

/** {implementation: {name: LmiMoreThan2BytesLeft}} */
LMI_INLINE LmiInt LmiMoreThan2BytesLeft(LmiBitstream *bs)
{
    return (bs->totBytes < bs->infoLen-2);
}

/** {implementation: {name: LmiMoreThan3BytesLeft}} */
LMI_INLINE LmiInt LmiMoreThan3BytesLeft(LmiBitstream *bs)
{
    return (bs->totBytes < bs->infoLen-3);
}

/** {implementation: {name: LmiMoreThan4BytesLeft}} */
LMI_INLINE LmiInt LmiMoreThan4BytesLeft(LmiBitstream *bs)
{
    return (bs->totBytes < bs->infoLen-4);
}

/** {implementation: {name: LmiAtEnd}} */
LMI_INLINE LmiInt LmiAtEnd(LmiBitstream *bs)
{
    return (bs->totBytes >= bs->infoLen);
}
