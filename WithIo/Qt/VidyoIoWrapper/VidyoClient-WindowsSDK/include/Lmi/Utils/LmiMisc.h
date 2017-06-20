/**
{file:
	{name: LmiMisc.h}
	{description: Miscellaneous utilities.}
	{copyright:
		(c) 2006-2016 Vidyo, Inc.,
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

#ifndef LMI_MISC_H_
#define LMI_MISC_H_

#include <stddef.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>

LMI_BEGIN_EXTERN_C

#define LMI_PI 3.141592653589793f

/* Macro to determine the number of elements in an array */
/**
	{function visibility="private":
		{name: LmiNumElements}
		{parent: Utils}
		{include: Lmi/Utils/LmiMisc.h}
		{description: Determines the number of elements in a single-dimensional array of arbitrary type elements.}
		{prototype: LmiSizeT LmiNumElements(Type array[])}
		{parameter:
			{name: array}
			{description: The array.}
		}
		{return: The number of elements in the array.}
	}
*/
#define LmiNumElements(a_) (sizeof(a_) / sizeof(a_[0]))

/**
	{function visibility="private":
		{name: LmiMax}
		{parent: Utils}
		{include: Lmi/Utils/LmiMisc.h}
		{description: Calculates the maximum of two values.}
		{prototype: Type LmiMax(Type a, Type b)}
		{parameter:
			{name: a}
			{description: The first value.}
		}
		{parameter:
			{name: b}
			{description: The second value.}
		}
		{return: The greater of a and b.}
		{note: This is implemented as a macro; it is not side-effect safe.}
	}
*/
#define LmiMax(a_, b_) ((a_) > (b_) ? (a_) : (b_))

/**
	{function visibility="private":
		{name: LmiMin}
		{parent: Utils}
		{include: Lmi/Utils/LmiMisc.h}
		{description: Calculates the minimum of two values.}
		{prototype: Type LmiMin(Type a, Type b)}
		{parameter:
			{name: a}
			{description: The first value.}
		}
		{parameter:
			{name: b}
			{description: The second value.}
		}
		{return: The lesser of a and b.}
		{note: This is implemented as a macro; it is not side-effect safe.}
	}
*/
#define LmiMin(a_, b_) ((a_) < (b_) ? (a_) : (b_))

/**
{function visibility="private":
	{name: LmiAbs}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Calculates the absolute value of a number.}
	{prototype: Type LmiAbs(Type x)}
	{parameter: {name: x} {description: The number.}}
	{return: The absolute value of the specified number.}
	{note: This is implemented as a macro; it is not side-effect safe.}
}
*/
#define LmiAbs(x) ((x) < 0 ? -(x) : (x))

/**
{function visibility="private":
	{name: LmiCircularDecrement}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Decrements a number down to 0, from which the next decrement will be (lim-1).}
	{prototype: Type LmiCircularDecrement(Type lim, Type x)}
	{parameter: {name: lim} {description: The limit that cannot be reached.}}
	{parameter: {name: x} {description: The number to decrement.}}
	{return: The decremented number.}
	{note: This is implemented as a macro; it is not side-effect safe.}
}
*/
#define LmiCircularDecrement(lim, x) ((x) == 0 ? ((lim)-1) : ((x)-1))

/**
{function visibility="private":
	{name: LmiCircularIncrement}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Increments a number up to a maximum (lim-1), from which the next increment will be 0.}
	{prototype: Type LmiCircularIncrement(Type lim, Type x)}
	{parameter: {name: lim} {description: The limit that cannot be reached.}}
	{parameter: {name: x} {description: The number to increment.}}
	{return: The incremented number.}
	{note: This is implemented as a macro; it is not side-effect safe.}
}
*/
#define LmiCircularIncrement(lim, x) ((x) < ((lim)-1) ? ((x)+1) : 0)

/**
{function visibility="private":
	{name: LmiLeastCommonMultiple}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Find the least common multiple of two unsigned integers.}
	{prototype: LmiUint LmiLeastCommonMultiple(LmiUint a, LmiUint b)}
	{parameter: {name: a} {description: An unsigned integer.}}
	{parameter: {name: b} {description: An unsigned integer.}}
	{return: The least common multiple.}
}
*/
LmiUint LmiLeastCommonMultiple(LmiUint a, LmiUint b);

/* Alignment macros */
struct LmiAlignments_{
	char a;
	union {
		void        *vp_;
		int         i_;
		long        l_;
		double long dl_;
#if LMI_HAVE_LONG_LONG
		long long   ll_;
#endif
		LmiUint64   u64_;
		void (*fp_)(void);
		struct LmiAlignments_* sp_;
	} u;
};

#define LMI_ALIGN_NATURAL \
	offsetof(struct LmiAlignments_, u)

/**
	{function visibility="private":
		{name: LmiAlignOn}
		{parent: Utils}
		{include: Lmi/Utils/LmiMisc.h}
		{description: Returns a pointer aligned on the next {code: n} byte boundary.}
		{prototype: void* LmiAlignOn(Type* pointer, LmiSizeT n)}
		{parameter:
			{name: pointer}
			{description: The pointer to be aligned.}
		}
		{parameter:
			{name: n}
			{description: The byte boundary to align on.}
		}
		{return: Returns an appropriately aligned pointer.}
	}
*/
#define LmiAlignOn(pointer_, n_) \
	(void*)((LmiDistanceT)(pointer_) + (((n_) - ((LmiDistanceT)(pointer_) % (n_))) & ((n_) - 1)))

/**
	{function visibility="private":
		{name: LmiAlign}
		{parent: Utils}
		{include: Lmi/Utils/LmiMisc.h}
		{description: Returns a pointer aligned on the next natural boundary of the platform.}
		{prototype: void* LmiAlign(Type* pointer)}
		{parameter:
			{name: pointer}
			{description: The pointer to be aligned.}
		}
		{return: An appropriately aligned pointer.}
	}
*/
#define LmiAlign(pointer_) LmiAlignOn((pointer_), LMI_ALIGN_NATURAL)

/**
{type visibility="public":
	{name: LmiInitTable}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Holds an initialization function and its corresponding uninitialization function.}
	{member: {name: init} {type: LmiBool (*)(void)} {description: The initialization function. The function
		should return LMI_TRUE on success and LMI_FALSE on failure. A value of NULL is equivalent to
		an empty function returning LMI_TRUE.}}
	{member: {name: uninit} {type: void (*)(void)} {description: The uninitialization function.
		A value of NULL is equivalent to an empty function.}}
}
*/
typedef struct
{
	LmiBool (*init)(void);
	void (*uninit)(void);
} LmiInitTable;

/**
{function visibility="public":
	{name: LmiInitTableInitialize}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Calls the initialization functions specified in an LmiInitTable sequentially.
		If any initialization function returns LMI_FALSE, no further initialization functions are called
		and any initialization functions that have already returned LMI_TRUE are rolled back by
		calling the matching uninitialization functions in reverse order.}
	{prototype: LmiBool LmiInitTableInitialize(const LmiInitTable* t, LmiSizeT n)}
	{parameter: {name: t} {description: An array of LmiInitTable structures, each containing
		an initialization function and its corresponding uninitialization function.}}
	{parameter: {name: n} {description: The number of elements in the LmiInitTable array.}}
	{return: A boolean set to LMI_TRUE if and only if all initialization functions returned LMI_TRUE.}
}
*/
LmiBool LmiInitTableInitialize(const LmiInitTable *t, LmiSizeT n);

/**
{function visibility="public":
	{name: LmiInitTableUninitialize}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Calls the uninitialization functions specified in an LmiInitTable in reverse order.
		This function will properly uninitialize all initialization done by a successful call
		to LmiInitTableInitialize taking the same parameters.}
	{prototype: void LmiInitTableUninitialize(const LmiInitTable *t, LmiSizeT n)}
	{parameter: {name: t} {description: An array of LmiInitTable structures, each containing
		an initialization function and its corresponding uninitialization function.}}
	{parameter: {name: n} {description: The number of elements in the LmiInitTable array.}}
}
*/
void LmiInitTableUninitialize(const LmiInitTable *t, LmiSizeT n);

/**
{function visibility="public":
	{name: LmiInitTableInitializeEx}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: An extension of LmiInitTableInitialize used to ensure that the initialization
		functions specified in an LmiInitTable are not called more than once (without intervening
		uninitializations).}
	{prototype: LmiBool LmiInitTableInitializeEx(const LmiInitTable* t, LmiSizeT n, LmiInt* initCount)}
	{parameter: {name: t} {description: An array of LmiInitTable structures, each containing
		an initialization function and its corresponding uninitialization function.}}
	{parameter: {name: n} {description: The number of elements in the LmiInitTable array.}}
	{parameter: {name: initCount} {description: The address of an integer variable that will contain
		the number of calls to LmiInitTableInitializeEx for this LmiInitTable that have not been
		matched by a call to LmiInitTableUninitializeEx. The variable should be initialized to 0
		and passed to each call of LmiInitTableInitializeEx and LmiInitTableUninitializeEx
		operating on this LmiInitTable.}}
	{return: Returns LMI_TRUE if the initializations specified in the LmiInitTable were completed
		successfully, either just now or in a previous call to LmiInitTableInitializeEx.
		Returns LMI_FALSE if some initialization functions returned LMI_FALSE.}
	{note: This function is not reentrant.}
}
*/
LmiBool LmiInitTableInitializeEx(const LmiInitTable *t, LmiSizeT n, LmiInt *initCount);

/**
{function visibility="public":
	{name: LmiInitTableUninitializeEx}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: An extension of LmiInitTableUninitialize used to ensure that the initialization
		functions specified in an LmiInitTable are not called more than once (without intervening
		uninitializations).}
	{prototype: void LmiInitTableUninitializeEx(const LmiInitTable* t, LmiSizeT n, LmiInt* initCount)}
	{parameter: {name: t} {description: An array of LmiInitTable structures, each containing
		an initialization function and its corresponding uninitialization function.}}
	{parameter: {name: n} {description: The number of elements in the LmiInitTable array.}}
	{parameter: {name: initCount} {description: The address of an integer variable that will contain
		the number of calls to LmiInitTableInitializeEx for this LmiInitTable that have not been
		matched by a call to LmiInitTableUninitializeEx. The variable should be initialized to 0
		and passed to each call of LmiInitTableInitializeEx and LmiInitTableUninitializeEx
		operating on this LmiInitTable.}}
	{note: This function is not reentrant.}
}
*/
void LmiInitTableUninitializeEx(const LmiInitTable *t, LmiSizeT n, LmiInt *initCount);

/**
{function visibility="private":
	{name: LmiUint16FromOctets}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Translate a LmiUint16 from network byte-order octets.}
	{prototype: LmiUint16 LmiUint16FromOctets(const LmiUint8 o[2])}
	{parameter:
		{name: o}
		{description: An array of two octets representing a 16-bit integer in
			network byte order.}}
	{return: The integer represented by the two octets.}
	{note: Unlike LmiUint16NtoH, this does not require its argument to
		be aligned properly for a 16-bit integer.}
}
*/
LMI_INLINE_DECLARATION LmiUint16 LmiUint16FromOctets(const LmiUint8 o[2]);

/**
{function visibility="private":
	{name: LmiUint16FromBuffer}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Read a LmiUint16 from network byte-order octets at a given position in a string.}
	{prototype: LmiBool LmiUint16FromBuffer(const LmiString* b, LmiSizeT* pos, LmiSizeT end, LmiUint16* u16)}
	{parameter:
		{name: b}
		{description: A buffer containing a network byte order 16-bit integer.}}
	{parameter:
		{name: pos}
		{description: A pointer to a position within the string.  On success,
			the position will be incremented by two, to the position after the
			just-read octets.}}
	{parameter:
		{name: end}
		{description: A position within the string.  The function will not
			read beyond this position.  (This position may be LMI_STRING_NPOS
			to indicate that the entire string should be read.)}}
	{parameter:
		{name: u16}
		{description: On success, this will be filled in with the value of the 16-bit integer.}}
	{return: LMI_TRUE on success, LMI_FALSE on not enough bytes in the buffer.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiUint16FromBuffer(const LmiString* b, LmiSizeT* pos, LmiSizeT end, LmiUint16* u16);

/**
{function visibility="private":
	{name: LmiUint16ToOctets}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Translate a LmiUint16 to network byte-order octets.}
	{prototype: void LmiUint16ToOctets(LmiUint16 u16, LmiUint8 o[2])}
	{parameter:
		{name: u16}
		{description: A 16-bit unsigned integer.}}
	{parameter:
		{name: o}
		{description: An array of two octets, into which will be stored
			a network byte-order representation of the integer.}}
	{note: Unlike LmiUint16NtoH, this does not require its target to
	be aligned properly for a 16-bit integer.}
}
*/
LMI_INLINE_DECLARATION void LmiUint16ToOctets(LmiUint16 u16, LmiUint8 o[2]);

/**
{function visibility="private":
	{name: LmiUint16ToBuffer}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Append a LmiUint16 in network byte order to a buffer.}
	{prototype: LmiBool LmiUint16ToBuffer(LmiUint16 u16, LmiString* b)}
	{parameter:
		{name: u16}
		{description: A 16-bit unsigned integer.}}
	{parameter:
		{name: b}
		{description: A string buffer, to which the value of u16 will be
		appended in network byte order.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiUint16ToBuffer(LmiUint16 u16, LmiString* b);

/**
{function visibility="private":
	{name: LmiUint32FromOctets}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Translate a LmiUint32 from network byte-order octets.}
	{prototype: LmiUint32 LmiUint32FromOctets(const LmiUint8 o[4])}
	{parameter:
		{name: o}
		{description: An array of four octets representing a 32-bit integer in network byte order.}}
	{return: The integer represented by the four octets.}
	{note: Unlike LmiUint32NtoH, this does not require its argument to
		be aligned properly for a 32-bit integer.}
}
*/
LMI_INLINE_DECLARATION LmiUint32 LmiUint32FromOctets(const LmiUint8 o[4]);

/**
{function visibility="private":
	{name: LmiUint32FromBuffer}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Read a LmiUint32 from network byte-order octets at a given
		position in a buffer.}
	{prototype: LmiBool LmiUint32FromBuffer(const LmiString* b, LmiSizeT* pos, LmiSizeT end, LmiUint32* u32)}
	{parameter:
		{name: b}
		{description: A buffer containing a network byte order 32-bit integer.}}
	{parameter:
		{name: pos}
		{description: A pointer to a position within the string.  On success,
			the position will be incremented by four, to the position after the
			just-read octets.}}
	{parameter:
		{name: end}
		{description: A position within the string.  The function will not
			read beyond this position.  (This position may be LMI_STRING_NPOS
			to indicate that the entire string should be read.)}}
	{parameter:
		{name: u32}
		{description: On success, this will be filled in with the value of the 32-bit integer.}}
	{return: LMI_TRUE on success, LMI_FALSE on not enough bytes in the buffer.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiUint32FromBuffer(const LmiString* b, LmiSizeT* pos, LmiSizeT end, LmiUint32* u32);

/**
{function visibility="private":
	{name: LmiUint32ToOctets}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Translate a LmiUint32 to network byte-order octets.}
	{prototype: void LmiUint32ToOctets(LmiUint32 u32, LmiUint8 o[4])}
	{parameter:
		{name: u32}
		{description: A 32-bit unsigned integer.}}
	{parameter:
		{name: o}
		{description: An array of four octets, into which will be stored
			a network byte-order representation of the integer.}}
	{note: Unlike LmiUint32NtoH, this does not require its target to
		be aligned properly for a 32-bit integer.}
}
*/
LMI_INLINE_DECLARATION void LmiUint32ToOctets(LmiUint32 u32, LmiUint8 o[4]);

/**
{function visibility="private":
	{name: LmiUint32ToBuffer}
	{parent: Utils}
	{include: Lmi/Utils/LmiMisc.h}
	{description: Append a LmiUint32 in network byte order to a buffer.}
	{prototype: LmiBool LmiUint32ToBuffer(LmiUint32 u32, LmiString* b)}
	{parameter:
		{name: u32}
		{description: A 32-bit unsigned integer.}}
	{parameter:
		{name: b}
		{description: A string buffer, to which the value of u32 will be
			appended in network byte order.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiUint32ToBuffer(LmiUint32 u32, LmiString* b);

/* Stringify a macro */
#define LmiQuoteName(x)       #x

/* Stringify the expansion of a macro */
#define LmiQuoteValue(x)      LmiQuoteName(x)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiMiscInline.h>
#endif

#endif /* LMI_MISC_H_ */
