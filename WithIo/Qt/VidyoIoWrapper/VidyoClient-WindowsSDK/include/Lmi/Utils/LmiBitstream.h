/**
{file: 
	{name: LmiBitstream.h}
	{description: Defines the structure and functions used for bitstream reading/writing
	for writing and reading bitstreams, respectively.}
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


#ifndef LMI_BITSTREAM_H_
#define LMI_BITSTREAM_H_


#include <Lmi/Utils/LmiAssert.h>
#include <Lmi/Utils/LmiAllocator.h>

LMI_BEGIN_EXTERN_C

/**
{package visibility="private":
	{name: Bitstream}
	{parent: Utils}
	{include: Lmi/Utils/LmiBitstream.h}
	{description: Functions for bitstream operations.}
}
*/


#define LMI_CODEC_MAX_BITS                    32      /* maximum # of bits to read/write at a time */
#ifndef LMI_CODEC_SupportedMaxBsBufSize               /* can be build parameter */
	#define LMI_CODEC_SupportedMaxBsBufSize     100000  /* default size */
#endif //#ifndef LMI_CODEC_SupportedMaxBsBufSize


LMI_INLINE_DECLARATION LmiUint8 LmiGetCeilLog2(LmiUint32 val);



/**
{type visibility="private":
	{name: LmiBitstream}
	{parent: Bitstream}
	{description: The main structure for storing information regarding coded bits.}
	{note: It's written in the case of encoder and read in the case of decoder.}
}
*/
typedef struct {
    LmiUint8    *buf;           /*< the buffer */
    LmiSizeT    bufLen;         /*< size of the buffer (in bytes) */ 
    LmiSizeT    infoLen;        /*< size of useful information in the buffer (in bytes) */ 
    LmiSizeT    totBits;        /*< total bits written/read except the start code emulation prevention bits */
    LmiSizeT    totBytes;       /*< total bytes written/read except the start code emulation preventions bytes */
    LmiUint     lastByteBit;    /*< bit position of the last byte */
    
    // variables used for encoding only
    LmiUint     zeroBytes;      /*< total number of last zero bytes (used for start code emulation prevention) */
    LmiSizeT    noEmulBytePos;  /*< the last byte position without start code emulation bytes */
} LmiBitstream;

/**
{function visibility="private":
	{name: LmiBitstreamConstruct}
	{parent: LmiBitstream}
	{description: Return a pointer to the bitstream structure.}
	{prototype: LmiBitstream *LmiBitstreamConstruct(LmiBitstream *bs, LmiUint8 *buf, LmiSizeT bufLen, LmiUint isScPreventionNeeded)}
	{parameter: {name: bs} {description: The returned bitstream pointer.}}
	{parameter: {name: buf} {description: Pointer to the buffer to use.}}
	{parameter: {name: bufLen} {description: Size of the buffer.}}
	{parameter: {name: isScPreventionNeeded} {description: Flag indicating whether or not to prevent start code emulation.}}
	{return: Pointer to the bitstream structure.}
}
*/
LmiBitstream *LmiBitstreamConstruct(LmiBitstream *bs, LmiUint8 *buf, LmiSizeT bufLen, LmiUint isScPreventionNeeded);

void LmiBitstreamReset(LmiBitstream *bs);

LmiBool LmiBitstreamMatchBufferSize(LmiBitstream *bs, LmiSizeT targetBufferSize, LmiAllocator *alloc);


/* 
 * The encoder (writing) specific functions.
 * These functions are used for writing into a bitstream.
 */

/**
{function visibility="private":
	{name: LmiPutBits}
	{parent: Bitstream}
	{description: Put bits into the bitstream buffer.}
	{prototype: LmiUint LmiPutBits(LmiBitstream *bs, LmiUint32 val, LmiUint size)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to be written.}}
	{parameter: {name: size} {description: The # of bits to use to represent the value.}}
	{return: The # of bits written.}
	{note: This function assumes that the maximum # of bits to represent any value is LMI_CODEC_MAX_BITS. 
		If val is greater than the maximum possible representable value using size
		bits, then only size least significant bits of val are output.
	}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiPutBits(LmiBitstream *bs, LmiUint32 val, LmiUint size);

/**
{function visibility="private":
	{name: LmiPutOneBit}
	{parent: Bitstream}
	{description: Put one or zero bit into the bitstream buffer.}
	{prototype: LmiUint LmiPutOneBit(LmiBitstream *bs, LmiUint8 val, LmiUint size)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to be written.}}
	{parameter: {name: size} {description: The # of bits to use to represent the value.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiPutOneBit(LmiBitstream *bs, LmiUint8 val, LmiUint size);

/**
{function visibility="private":
	{name: LmiPutAnAlignedByte}
	{parent: Bitstream}
	{description: Put a byte into the bitstream buffer; the buffer must be already byte aligned.}
	{prototype: LmiUint LmiPutAnAlignedByte(LmiBitstream *bs, LmiUint8 val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The byte.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiPutAnAlignedByte(LmiBitstream *bs, LmiUint8 val);
LMI_INLINE_DECLARATION LmiUint LmiPutAlignedBytes(LmiBitstream *bs, LmiUint32 val, LmiUint bytes);
LMI_INLINE_DECLARATION LmiUint LmiPutAnAlignedByteWithCarryOver(LmiBitstream *bs, LmiUint8 val, LmiSizeT startBytePos);

/**
{function visibility="private":
	{name: LmiPutAlignBits}
	{parent: Bitstream}
	{description: Put bits into the bitstream buffer for alignment.}
	{prototype: LmiUint LmiPutAlignBits(LmiBitstream *bs, LmiUint align, LmiUint val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: align} {description: The bitstream will be aligned by align number of bits, e.g., for byte alignment, align = 8.}}
	{parameter: {name: val} {description: The alignment bit: 0 or 1.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiPutAlignBits(LmiBitstream *bs, LmiUint align, LmiUint val);


/**
{function visibility="private":
	{name: LmiPutUe8}
	{parent: Bitstream}
	{description: Put a unsigned Exp-Golomb codeword for a given 8-bit value.}
	{prototype: LmiUint8 LmiPutUe8(LmiBitstream *bs, LmiUint8 val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to output.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiPutUe8(LmiBitstream *bs, LmiUint8 val);
/**
{function visibility="private":
	{name: LmiPutUe16}
	{parent: Bitstream}
	{description: Put a unsigned Exp-Golomb codeword for a given 16-bit value.}
	{prototype: LmiUint8 LmiPutUe16(LmiBitstream *bs, LmiUint16 val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to output.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiPutUe16(LmiBitstream *bs, LmiUint16 val);
/**
{function visibility="private":
	{name: LmiPutUe32}
	{parent: Bitstream}
	{description: Put a unsigned Exp-Golomb codeword for a given 32-bit value (must be < 0xFFFFFFFF).}
	{prototype: LmiUint8 LmiPutUe32(LmiBitstream *bs, LmiUint32 val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to output.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiPutUe32(LmiBitstream *bs, LmiUint32 val);

/**
{function visibility="private":
	{name: LmiPutSe8}
	{parent: Bitstream}
	{description: Put a signed Exp-Golomb codeword for a given 8-bit value.}
	{prototype: LmiUint8 LmiPutSe8(LmiBitstream *bs, LmiInt8 val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to output.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiPutSe8(LmiBitstream *bs, LmiInt8 val);
/**
{function visibility="private":
	{name: LmiPutSe16}
	{parent: Bitstream}
	{description: Put a signed Exp-Golomb codeword for a given 16-bit value.}
	{prototype: LmiUint8 LmiPutSe16(LmiBitstream *bs, LmiInt16 val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to output.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiPutSe16(LmiBitstream *bs, LmiInt16 val);

/**
{function visibility="private":
	{name: LmiPutTe8}
	{parent: Bitstream}
	{description: Put a truncated Exp-Golomb codeword for a given 8-bit value.}
	{prototype: LmiUint8 LmiPutTe8(LmiBitstream *bs, LmiUint8 x, LmiUint8 val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: x} {description: The range upper limit of the syntax element.}}
	{parameter: {name: val} {description: The value to output.}}
	{return: The # of bits written.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiPutTe8(LmiBitstream *bs, LmiUint8 x, LmiUint8 val);

/* 
 * The decoder (parsing) specific functions.
 * These functions are used for parsing from a bitstream.
 * Prior to calling the below functions, each NAL unit must
 * have been processed to strip emulation bytes.
 */

/**
{function visibility="private":
	{name: LmiSkipBits}
	{parent: Bitstream}
	{description: Skip bits from the bitstream buffer.}
	{prototype: LmiUint LmiSkipBits(LmiBitstream *bs, LmiUint size)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: size} {description: The # of bits to skip.}}
	{return: The # of bits skipped.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiSkipBits(LmiBitstream *bs, LmiUint size);

/**
{function visibility="private":
	{name: LmiSkipBytes}
	{parent: Bitstream}
	{description: Skip bytes from the bitstream buffer.}
	{prototype: LmiUint LmiSkipBytes(LmiBitstream *bs, LmiUint size)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: size} {description: The # of bytes to skip.}}
	{return: The # of bits skipped.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiSkipBytes(LmiBitstream *bs, LmiUint size);

/**
{function visibility="private":
	{name: LmiNextBits}
	{parent: Bitstream}
	{description: Look-ahead read bits from the bitstream buffer.}
	{prototype: LmiUint32 LmiNextBits(LmiBitstream *bs, LmiUint size)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: size} {description: The # of bits to read.}}
	{return: The obtained value, represented as an unsigned integer.}
	{note: This function assumes that the maximum number of bits to represent any value is LMI_CODEC_MAX_BITS.}
}
*/
LMI_INLINE_DECLARATION LmiUint32 LmiNextBits(LmiBitstream *bs, LmiUint size);

/**
{function visibility="private":
	{name: LmiNext3Bytes}
	{parent: Bitstream}
	{description: Look-ahead read next 3 bytes from the bitstream buffer.}
	{prototype: LmiUint32 LmiNext3Bytes(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: The obtained value, represented as an unsigned integer.}
}
*/
LMI_INLINE_DECLARATION LmiUint32 LmiNext3Bytes(LmiBitstream *bs);

/**
{function visibility="private":
	{name: LmiGetBits}
	{parent: Bitstream}
	{description: Read bits from the bitstream buffer.}
	{prototype: LmiUint32 LmiGetBits(LmiBitstream *bs, LmiUint size)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: size} {description: The # of bytes to read.}}
	{return: The obtained value, represented as an unsigned integer.}
	{note: This function assumes that the maximum number of bits to represent any value is LMI_CODEC_MAX_BITS.}
}
*/
LMI_INLINE_DECLARATION LmiUint32 LmiGetBits(LmiBitstream *bs, LmiUint size);

/**
{function visibility="private":
	{name: LmiGetOneBit}
	{parent: Bitstream}
	{description: Read one bit from the bitstream buffer.}
	{prototype: LmiUint8 LmiGetOneBit(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: The obtained value, represented as an unsigned integer.}
	}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetOneBit(LmiBitstream *bs);

/**
{function visibility="private":
	{name: LmiGetAnAlignedByte}
	{parent: Bitstream}
	{description: Read a byte from the bitstream buffer; the buffer must be already byte aligned.}
	{prototype: LmiUint8 LmiGetAnAlignedByte(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: The obtained byte.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetAnAlignedByte(LmiBitstream *bs);
LMI_INLINE_DECLARATION LmiUint32 LmiGetAlignedBytes(LmiBitstream *bs, LmiSizeT bytes);

/**
{function visibility="private":
	{name: LmiGetAlignBits}
	{parent: Bitstream}
	{description: Align the bitstream buffer.}
	{prototype: LmiUint LmiGetAlignBits(LmiBitstream *bs, LmiUint align)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: align} {description: The bitstream will be aligned by align number of bits, e.g., for byte alignment, align = 8.}}
	{return: The # of bits read}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiGetAlignBits(LmiBitstream *bs, LmiUint align);

/**
{function visibility="private":
	{name: LmiGetUe8}
	{parent: Bitstream}
	{description: Get a unsigned Exp-Golomb codeword and translate it to the corresponding 8-bit value.}
	{prototype: LmiUint8 LmiGetUe8(LmiBitstream *bs, LmiUint8 *val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to obtained.}}
	{return: The # of bits read}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetUe8(LmiBitstream *bs, LmiUint8 *val);
/**
{function visibility="private":
	{name: LmiGetUe16}
	{parent: Bitstream}
	{description: Get a unsigned Exp-Golomb codeword and translate it to the corresponding 16-bit value.}
	{prototype: LmiUint8 LmiGetUe16(LmiBitstream *bs, LmiUint16 *val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to obtained.}}
	{return: The # of bits read}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetUe16(LmiBitstream *bs, LmiUint16 *val);
/**
{function visibility="private":
	{name: LmiGetUe32}
	{parent: Bitstream}
	{description: Get a unsigned Exp-Golomb codeword and translate it to the corresponding 32-bit value.}
	{prototype: LmiUint8 LmiGetUe32(LmiBitstream *bs, LmiUint32 *val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to obtained.}}
	{return: The # of bits read}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetUe32(LmiBitstream *bs, LmiUint32 *val);

/**
{function visibility="private":
	{name: LmiGetSe8}
	{parent: Bitstream}
	{description: Get a signed Exp-Golomb codeword and translate it to the corresponding 8-bit value (from (-2^7) to (+2^7 -1).}
	{prototype: LmiUint8 LmiGetSe8(LmiBitstream *bs, LmiInt8 *val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to obtained.}}
	{return: The # of bits read}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetSe8(LmiBitstream *bs, LmiInt8 *val);
/**
{function visibility="private":
	{name: LmiGetSe16}
	{parent: Bitstream}
	{description: Get a signed Exp-Golomb codeword and translate it to the corresponding 16-bit value (from (-2^15) to (+2^15 -1).}
	{prototype: LmiUint8 LmiGetSe16(LmiBitstream *bs, LmiInt16 *val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to obtained.}}
	{return: The # of bits read}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetSe16(LmiBitstream *bs, LmiInt16 *val);
/**
{function visibility="private":
	{name: LmiGetSe32}
	{parent: Bitstream}
	{description: Get a signed Exp-Golomb codeword and translate it to the corresponding 32-bit value (from (-2^31 +1) to (+2^31 -1).}
	{prototype: LmiUint8 LmiGetSe32(LmiBitstream *bs, LmiInt32 *val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: val} {description: The value to be obtained.}}
	{return: The # of bits read.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetSe32(LmiBitstream *bs, LmiInt32 *val);

/**
{function visibility="private":
	{name: LmiGetTe8}
	{parent: Bitstream}
	{description: Get a truncated Exp-Golomb codeword (max codeword len = 8) and translate it to the corresponding value.}
	{prototype: LmiUint8 LmiGetTe8(LmiBitstream *bs, LmiUint8 k, LmiUint8 *val)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{parameter: {name: k} {description: The range upper limit of the syntax element.}}
	{parameter: {name: val} {description: The value to obtained.}}
	{return: The # of bits read.}
}
*/
LMI_INLINE_DECLARATION LmiUint8 LmiGetTe8(LmiBitstream *bs, LmiUint8 k, LmiUint8 *val);

/**
{function visibility="private":
	{name: LmiMoreDataCavlc}
	{parent: Bitstream}
	{description: Check if there's more data in the bitstream.}
	{prototype: LmiInt LmiMoreDataCavlc(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: If there's more data, return 1, otherwise return 0.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiMoreDataCavlc(LmiBitstream *bs);

/**
{function visibility="private":
	{name: LmiMoreThan2BytesLeft}
	{parent: Bitstream}
	{description: Check if there's more than 2 bytes left.}
	{prototype: LmiInt LmiMoreThan2BytesLeft(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: If there's more than 2 bytes left, return 1, otherwise return 0.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiMoreThan2BytesLeft(LmiBitstream *bs);

/**
{function visibility="private":
	{name: LmiMoreThan3BytesLeft}
	{parent: Bitstream}
	{description: Check if there's more than 3 bytes left in the bitstream.}
	{prototype: LmiInt LmiMoreThan3BytesLeft(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: If there's more than 3 bytes left, return 1, otherwise return 0.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiMoreThan3BytesLeft(LmiBitstream *bs);

/**
{function visibility="private":
	{name: LmiMoreThan4BytesLeft}
	{parent: Bitstream}
	{description: Check if there's more than 4 bytes left in the bitstream.}
	{prototype: LmiInt LmiMoreThan4BytesLeft(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: If there's more than 4 bytes left, return 1, otherwise return 0.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiMoreThan4BytesLeft(LmiBitstream *bs);

/**
{function visibility="private":
	{name: LmiAtEnd}
	{parent: Bitstream}
	{description: Check if it reaches at the end of the bitstream.}
	{prototype: LmiInt LmiAtEnd(LmiBitstream *bs)}
	{parameter: {name: bs} {description: Pointer to the bitstream structure.}}
	{return: If it's the end of bitstream, return 1; otherwise return 0.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiAtEnd(LmiBitstream *bs);


LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiBitstreamInline.h>
#endif


#endif /* LMI_BITSTREAM_H_ */
