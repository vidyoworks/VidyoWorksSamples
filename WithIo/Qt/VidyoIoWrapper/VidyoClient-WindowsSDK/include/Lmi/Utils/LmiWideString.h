/** {file:
      {name: LmiWideString.h}
      {description: WideString class.}
      {copyright:
      	(c) 2014-2015 Vidyo, Inc.,
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

#ifndef LMI_WIDE_STRING_H_
#define LMI_WIDE_STRING_H_

#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/LmiContainers.h>
#include <Lmi/Utils/LmiIterators.h>

#if LMI_HAVE_STDARG_H
#include <stdarg.h>
#endif

LMI_BEGIN_EXTERN_C

/**
   {type:
     {name: LmiWideString}
     {parent: Utils}
     {include: Lmi/Utils/LmiWideString.h}
     {description: Class representing C wide strings.  Interface largely
       based on C++\'s std::wstring (i.e., std::basic_string<wchar_t>) class.}
     {constant:
       {name: LMI_WIDE_STRING_NPOS}
       {type: LmiSizeT}
       {description: For value parameters, an invalid value used to represent
         "no position".}}
   }
*/

typedef struct {
  LmiAllocator * allocator;
  LmiWideChar * buf;
  LmiSizeT size;
  LmiSizeT capacity;
} LmiWideString;

#define LMI_WIDE_STRING_NPOS LMI_SIZE_T_MAX

/* return value of LmiWideStringData() and LmiWideStringCStr() if buf == NULL */
/* declared in the header file so the inline functions can reference it. */
extern const LmiWideChar lmiWideStringEmptyStr_[];

/**
   {function:
     {name: LmiWideStringConstructDefault}
     {parent: LmiWideString}
     {description: Construct an empty LmiWideString.}
     {prototype: LmiWideString* LmiWideStringConstructDefault(LmiWideString* x, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiWideString* LmiWideStringConstructDefault(LmiWideString* x, LmiAllocator* a);

/**
   {function:
     {name: LmiWideStringDestruct}
     {parent: LmiWideString}
     {description: Destruct an LmiWideString, freeing all associated storage.}
     {prototype: void LmiWideStringDestruct(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to destruct.}
     }
   }
*/
void LmiWideStringDestruct(LmiWideString* x);

/**
   {function:
     {name: LmiWideStringConstructCopy}
     {parent: LmiWideString}
     {description: Construct a copy of an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringConstructCopy(LmiWideString* x, const LmiWideString* y)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the string object to copy.}
     }
     {return: A pointer to the string object, or NULL on failure.}
     {note: The newly-constructed string uses the same allocator as the
       source string did.}
   }
*/
LmiWideString* LmiWideStringConstructCopy(LmiWideString* x, const LmiWideString* y);

/**
   {function:
     {name: LmiWideStringAssign}
     {parent: LmiWideString}
     {description: Assign the value of one LmiWideString to another.  The
       previous data stored in the destination is overwritten.}
     {prototype: LmiWideString* LmiWideStringAssign(LmiWideString* x, const LmiWideString* y)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the string object to copy.}
     }
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiWideString* LmiWideStringAssign(LmiWideString* x, const LmiWideString* y);

/**
   {function:
     {name: LmiWideStringSwap}
     {parent: LmiWideString}
     {description: Swap the values of two LmiWideStrings.}
     {prototype: LmiBool LmiWideStringSwap(LmiWideString* x, LmiWideString* y)}
     {parameter:
       {name: x}
       {description: A pointer to the first string object to swap.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the second string object to swap.}
     }
	 {return: LMI_TRUE on success, LMI_FALSE otherwise.}
     {note: The strings\' allocators are also swapped.}
   }
*/
LmiBool LmiWideStringSwap(LmiWideString* x, LmiWideString* y);

/**
   {function:
     {name: LmiWideStringEqual}
     {parent: LmiWideString}
     {description: Compare the values of two LmiWideStrings for equality.}
     {prototype: LmiBool LmiWideStringEqual(const LmiWideString* x, const LmiWideString* y)}
     {parameter:
       {name: x}
       {description: A pointer to the first string object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the second string object to compare.}
     }
     {return: LMI_TRUE if the strings are equal, LMI_FALSE otherwise.}
     {note: Comparison is done on a character-by-character basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiBool LmiWideStringEqual(const LmiWideString* x, const LmiWideString* y);


/**
   {function:
     {name: LmiWideStringEqualCStr}
     {parent: LmiWideString}
     {description: Compare the value of an LmiWideString with that of a C wide string
       for equality.}
     {prototype: LmiBool LmiWideStringEqualCStr(const LmiWideString* x, const LmiWideChar* y)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiWideString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the C string to compare.}
     }
     {return: LMI_TRUE if the strings are equal, LMI_FALSE otherwise.}
     {note: Comparison is done on a character-by-character basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiBool LmiWideStringEqualCStr(const LmiWideString* x, const LmiWideChar* y);

/**
   {function:
     {name: LmiWideStringEqualCStrLen}
     {parent: LmiWideString}
     {description: Compare the value of an LmiWideString with that of a C wide string
       of a given length for equality.}
     {prototype: LmiBool LmiWideStringEqualCStrLen(const LmiWideString* x, const LmiWideChar* y, LmiSizeT ylen)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiWideString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to an array of LmiWideChar.  The contents of x will be compared to the first {italic:ylen} characters of y.  The array may include NUL.}
     }
	 {parameter:
	   {name: ylen}
	   {description: The length of the array pointed to by {italic:y}.}
	 }
     {return: LMI_TRUE if the strings are equal, LMI_FALSE otherwise.}
     {note: Comparison is done on a character-by-character basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiBool LmiWideStringEqualCStrLen(const LmiWideString* x, const LmiWideChar* y, LmiSizeT ylen);

/**
   {function:
     {name: LmiWideStringLess}
     {parent: LmiWideString}
     {description: Compare the values of two LmiWideStrings for ordering.}
     {prototype: LmiBool LmiWideStringLess(const LmiWideString* x, const LmiWideString* y)}
     {parameter:
       {name: x}
       {description: A pointer to the first string object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the second string object to compare.}
     }
     {return: LMI_TRUE if x is lexicographically less than y, LMI_FALSE
       otherwise.}
     {note: Comparison is done on a character-by-character basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiWideStringLess(const LmiWideString* x, const LmiWideString* y);

/* Do we need LmiWideStringDump? */


/**
	{type:
		{name: LmiWideStringIterator}
		{parent: LmiWideString}
		{description: The iterator type of a string.}
		{note: This is a model of LmiRandomAccessIterator.}
	}
*/

/**
{type:
	{name: LmiWideStringConstIterator}
	{parent: LmiWideString}
	{description: The read-only iterator type of a string.}
	{note: This is a model of LmiRandomAccessIterator.}
}
*/
/**
{type:
	{name: LmiWideStringReverseIterator}
	{parent: LmiWideString}
	{description: The reverse iterator type of a string.}
	{note: This is a model of LmiRandomAccessIterator.}
}
*/

/**
{type:
	{name: LmiWideStringConstReverseIterator}
	{parent: LmiWideString}
	{description: The read-only reverse iterator type of a string.}
	{note: This is a model of LmiRandomAccessIterator.}
}
*/

/* An LmiWideString is a random-access container and a sequence. */
Declare_LmiRandomAccessContainerTypes(LmiWideString, LmiWideChar, LmiWideChar*, const LmiWideChar*,
	LmiSizeT, LmiDistanceT)
DeclareInline_LmiRandomAccessIterator(LmiWideStringIterator,
	LmiWideChar, const LmiWideChar, LmiDistanceT, LMI_INLINE_DECLARATION)
DeclareInline_LmiRandomAccessIterator(LmiWideStringConstIterator,
	const LmiWideChar, const LmiWideChar, LmiDistanceT, LMI_INLINE_DECLARATION)
DeclareInline_LmiRandomAccessIterator(LmiWideStringReverseIterator,
	LmiWideChar, const LmiWideChar, LmiDistanceT, LMI_INLINE_DECLARATION)
DeclareInline_LmiRandomAccessIterator(LmiWideStringConstReverseIterator,
	const LmiWideChar, const LmiWideChar, LmiDistanceT, LMI_INLINE_DECLARATION)

/**
   {function:
     {name: LmiWideStringConstructCStr}
     {parent: LmiWideString}
     {description: Construct an LmiWideString based on a NUL-terminated C wide
       string.}
     {prototype: LmiWideString* LmiWideStringConstructCStr(LmiWideString* x, const LmiWideChar* str, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: str}
       {description: A NUL-terminated C wide string.  The initial contents of x will be equal to the value of str up to its terminating NUL.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiWideString* LmiWideStringConstructCStr(LmiWideString* x, const LmiWideChar* str, LmiAllocator* a);

/**
   {function:
     {name: LmiWideStringConstructCStrLen}
     {parent: LmiWideString}
     {description: Construct an LmiWideString based on a C wide string of a given
       length.}
     {prototype: LmiWideString* LmiWideStringConstructCStrLen(LmiWideString* x, const LmiWideChar* str, LmiSizeT len, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: str}
       {description: A pointer to an array of LmiWideChar.  The initial contents of
       x will be equal to the first {italic:len} characters of str.  The array
       may include NUL characters.}}
     {parameter:
       {name: len}
       {description: The number of characters to include from {italic:str}.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiWideString* LmiWideStringConstructCStrLen(LmiWideString* x, const LmiWideChar* str,
                                     LmiSizeT len, LmiAllocator* a);

/**
   {function:
     {name: LmiWideStringConstructSubstring}
     {parent: LmiWideString}
     {description: Construct an LmiWideString based on a substring of another
       LmiWideString.}
     {prototype: LmiWideString* LmiWideStringConstructSubstring(LmiWideString* x,
       const LmiWideString* str, LmiSizeT pos, LmiSizeT n, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: str}
       {description: The source LmiWideString object.}}
     {parameter:
       {name: pos}
       {description: The initial position of the substring within the source
         string.}}
     {parameter:
       {name: n}
       {description: The length of the substring within the source
         string.  The value LMI_WIDE_STRING_NPOS indicates the entire string.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiWideString* LmiWideStringConstructSubstring(LmiWideString* x, const LmiWideString* str,
                                       LmiSizeT pos, LmiSizeT n, LmiAllocator* a);


/**
   {function:
     {name: LmiWideStringConstructRange}
     {parent: LmiWideString}
     {description: Construct an LmiWideString based on a range of another
       LmiWideString.}
     {prototype: LmiWideString* LmiWideStringConstructRange(LmiWideString* x,
       LmiWideStringConstIterator first, LmiWideStringConstIterator last,
       LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}}
     {parameter:
       {name: first}
       {description: The beginning of the source range.}}
     {parameter:
       {name: last}
       {description: The end of the source range.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiWideString* LmiWideStringConstructRange(LmiWideString* x, LmiWideStringConstIterator first,
                                   LmiWideStringConstIterator last,
                                   LmiAllocator* a);


/* * - Not currently supported for wide strings 
   {function:
     {name: LmiWideStringConstructFormatted}
     {parent: LmiWideString}
     {description: Construct an LmiWideString based on a printf-style formatted
       string.}
     {prototype: LmiWideString* LmiWideStringConstructFormatted(LmiWideString* x,
       LmiAllocator* a, const LmiWideChar* fmt, ...)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the constructed string\'s
         contents.}}
	 {parameter:
	   {name: ...}
	   {description:  The arguments to {italic:fmt}.}}
     {return: A pointer to the string object, or NULL on failure.}
     {note: Notice that unlike other LmiWideString constructors, this
       constructor\'s LmiAllocator argument is not its final argument, because
       variadic arguments must come at the end.}
   }
*/
/* 
LmiWideString*
LmiWideStringConstructFormatted(LmiWideString* x, LmiAllocator* a,
                            const LmiWideChar* fmt, ...)
  LmiFunctionPrintfLike(3, 4);
*/

/* * - Not currently supported for wide strings 
   {function:
     {name: LmiWideStringConstructVFormatted}
     {parent: LmiWideString}
     {description: Construct an LmiWideString based on a vprintf-style formatted
       string.}
     {prototype: LmiWideString* LmiWideStringConstructVFormatted(LmiWideString* x,
       const LmiWideChar* fmt, va_list args, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the constructed string\'s
       contents.}}
     {parameter:
       {name: args}
       {description: The arguments to {italic:fmt}, as constructed by
         the functions of <stdarg.h>.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringConstructVFormatted(LmiWideString* x, const LmiWideChar* fmt, va_list args,
                             LmiAllocator* a)
  LmiFunctionVPrintfLike(2);
*/

/**
   {function visibility="private":
     {name: LmiWideStringConstructWithExternalBuffer}
     {parent: LmiWideString}
     {description: Construct an LmiWideString taking ownership of an external buffer.}
     {prototype: LmiWideString* LmiWideStringConstructWithExternalBuffer(LmiWideString* x, LmiWideChar* buffer, LmiSizeT length, LmiSizeT capacity, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: buffer}
       {description: A buffer which the new string object should take ownership of.  If capacity == 0 this may be NULL.}
     }
     {parameter:
       {name: length}
       {description: The length of the data that is currently in the buffer, not including a terminating NUL character (if any).}
     }
     {parameter:
       {name: capacity}
       {description: The total capacity of the passed-in buffer, including space for a terminating NUL character, or 0.}
     }
     {parameter:
       {name: a}
       {description: An allocator to use for the string.  Its deallocate callback will be used to deallocate the passed-in buffer when the string is reallocated or destructed.}
     }
     {return: A pointer to the string object, or NULL on failure.}
     {note: If the buffer is not currently NUL-terminated, a NUL character will be 
	   written at buffer[length] unless capacity == 0; otherwise, the buffer
	   will only be written to when mutating LmiWideString functions are called
	   on the LmiWideString.}
   }
*/
LmiWideString* LmiWideStringConstructWithExternalBuffer(LmiWideString* x, LmiWideChar* buffer, LmiSizeT length, LmiSizeT capacity, LmiAllocator* a);


/**
	{function:
		{name: LmiWideStringConstructUtf8}
		{parent: LmiWideString}
		{description: Construct a wide string to have the Unicode values of a UTF8-encoded narrow C string.}
		{prototype: LmiWideString* LmiWideStringConstructUtf8(LmiWideString* x, const char* utf8, LmiAllocator* a)}
		{parameter:
			{name: x}
			{description: A pointer to the string to construct.}}
		{parameter:
			{name: utf8}
			{description: A NUL-terminated UTF-8 encoded narrow C string.}}
		{parameter:
			{name: a}
			{description: The allocator the string should use.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiWideString* LmiWideStringConstructUtf8(LmiWideString* x, const char* utf8, LmiAllocator* a);

/**
	{function:
		{name: LmiWideStringConstructUtf8Len}
		{parent: LmiWideString}
		{description: Construct a wide string to have the Unicode values of a UTF8-encoded narrow C string of a given length.}
		{prototype: LmiWideString* LmiWideStringConstructUtf8Len(LmiWideString* x, const char* utf8, LmiSizeT len, LmiAllocator* a)}
		{parameter:
			{name: x}
			{description: A pointer to the string to construct.}}
		{parameter:
			{name: utf8}
			{description: A UTF-8 encoded narrow C string.  This may contain NUL bytes.}}
		{parameter:
			{name: len}
			{description: The length of the UTF-8 encoded narrow C string, in bytes.  This length must encompass entire
				well-formed UTF-8 characters.}}
		{parameter:
			{name: a}
			{description: The allocator the string should use.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiWideString* LmiWideStringConstructUtf8Len(LmiWideString* x, const char* utf8, LmiSizeT len, LmiAllocator* a);

/**
	{function:
		{name: LmiWideStringConstructUtf16}
		{parent: LmiWideString}
		{description: Construct a wide string to have the Unicode values of a UTF16-encoded C string.}
		{prototype: LmiWideString* LmiWideStringConstructUtf16(LmiWideString* x, const LmiUint16* utf16, LmiAllocator* a)}
		{parameter:
			{name: x}
			{description: A pointer to the string to construct.}}
		{parameter:
			{name: utf16}
			{description: A NUL-terminated UTF-16 encoded C string.}}
		{parameter:
			{name: a}
			{description: The allocator the string should use.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiWideString* LmiWideStringConstructUtf16(LmiWideString* x, const LmiUint16* utf8, LmiAllocator* a);

/**
   {function:
     {name: LmiWideStringLength}
     {parent: LmiWideString}
     {description: Get the length of an LmiWideString.}
     {prototype: LmiSizeT LmiWideStringLength(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose length is to be
       determined.}
     }
     {return: The length of the string, in characters.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiWideStringLength(const LmiWideString* x);

/**
   {function:
     {name: LmiWideStringSize}
     {parent: LmiWideString}
     {description: Get the size of an LmiWideString.}
     {prototype: LmiSizeT LmiWideStringSize(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose size is to be
         determined.}
     }
     {return: The size of the string, in characters.}
     {note: This function is identical to LmiWideStringLength.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiWideStringSize(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringMaxSize}
     {parent: LmiWideString}
     {description: Get the maximum supported length of an LmiWideString.}
     {prototype: LmiSizeT LmiWideStringMaxSize(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose maximum length is
         to be determined.}
     }
     {return: The maximum length of the string, in characters.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiWideStringMaxSize(const LmiWideString* x);

/**
   {function:
     {name: LmiWideStringGetAllocator}
     {parent: LmiWideString}
     {description: Get the allocator of an LmiWideString.}
     {prototype: LmiAllocator* LmiWideStringGetAllocator(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose allocator is
         to be determined.}
     }
     {return: The pointer to the allocator of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiAllocator* LmiWideStringGetAllocator(const LmiWideString* x);

/**
   {function:
     {name: LmiWideStringResize}
     {parent: LmiWideString}
     {description: Alters the length of an LmiWideString, either by truncating
       it or extending it.}
     {prototype: LmiBool LmiWideStringResize(LmiWideString* x, LmiSizeT n, const LmiWideChar* c)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to resize.}}
     {parameter:
       {name: n}
       {description: The new length for the string.  If this is greater than
         the current length of the string, the additional contents of the
         string will be set to 'c'.}}
     {parameter:
       {name: c}
       {description: A pointer to the character value with which to fill the string, if
         the string is being extended.}}
     {return: LMI_FALSE on allocation failure, otherwise LMI_TRUE.}
   }
*/
LmiBool LmiWideStringResize(LmiWideString* x, LmiSizeT n, const LmiWideChar* c);


/**
   {function:
     {name: LmiWideStringCapacity}
     {parent: LmiWideString}
     {description: Get the size of the allocated storage of an LmiWideString.}
     {prototype: LmiSizeT LmiWideStringCapacity(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose capacity is
         to be determined.}
     }
     {return: The capacity of the string, in characters.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiWideStringCapacity(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringReserve}
     {parent: LmiWideString}
     {description: Reserve storage for a string.}
     {prototype: LmiBool LmiWideStringReserve(LmiWideString* x, LmiSizeT res)}
     {parameter:
       {name: x}
       {description: A pointer to the string object for which storage is to
         be reserved.}}
     {parameter:
       {name: res}
       {description: The number of characters of memory to reserve for the
         string.  After successful return of this function,
         LmiWideStringCapacity(x) will be >= res.}}
     {return: LMI_FALSE on allocation failure, otherwise LMI_TRUE.}
     {note: If res is less than the string\'s current capacity, this function
       is a non-binding shrink request.  If res is less than the string\'s
       current size, this function is a non-binding shrink-to-fit request.}
   }
*/
LmiBool LmiWideStringReserve(LmiWideString* x, LmiSizeT res);

/**
   {function:
     {name: LmiWideStringData}
     {parent: LmiWideString}
     {description: Get a read-only buffer corresponding to the contents
        of a string.}
     {prototype: const LmiWideChar* LmiWideStringData(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose buffer to extract.}}
     {return: A read-only pointer to the string\'s data, as an array of
       LmiWideStringSize(x) characters.}
     {note: The pointer to the buffer may be invalidated by any non-const
       member function of LmiWideString, other than LmiWideStringAt.}
   }
*/
LMI_INLINE_DECLARATION const LmiWideChar* LmiWideStringData(const LmiWideString* x);

/**
   {function:
     {name: LmiWideStringCStr}
     {parent: LmiWideString}
     {description: Get a NUL-terminated C wide string corresponding to the contents
        of a string.}
     {prototype: const LmiWideChar* LmiWideStringCStr(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose C wide string to obtain.}}
     {return: A read-only array of LmiWideStringSize(x) characters followed by a
       NUL character.}
     {note: The pointer to the C string may be invalidated by any non-const
       member function of LmiWideString, other than LmiWideStringAt.}
   }
*/
LMI_INLINE_DECLARATION const LmiWideChar* LmiWideStringCStr(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringGetBuffer}
     {parent: LmiWideString}
     {description: Get a writeable buffer into which data can be written
	   outside the control of the LmiWideString object.}
     {prototype: LmiWideChar* LmiWideStringGetBuffer(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose buffer to extract.}}
     {return: A pointer to a buffer.  It is safe to write into
	   LmiWideStringCapacity(x) - LmiWideStringLength(x) characters of this buffer.
       The data in question will be appended to the end of the string.}
     {note: When the caller is done, the function LmiWideStringReleaseBuffer
		must be called to set the new length of the string.}
     {note: The pointer to the buffer may be invalidated by any non-const
       member function of LmiWideString, other than LmiWideStringAt.}
   }
*/
LMI_INLINE_DECLARATION LmiWideChar* LmiWideStringGetBuffer(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringReleaseBuffer}
     {parent: LmiWideString}
     {description: Release a writeable buffer previously acquired with
	   LmiWideStringGetBuffer.}
     {prototype: void LmiWideStringReleaseBuffer(LmiWideString* x, LmiSizeT buflen)}
     {parameter:
       {name: x}
       {description: The string whose buffer to release.}}
     {parameter:
       {name: buflen}
       {description: The number of characters written into the buffer.  This
	     must be less than or equal to LmiWideStringCapacity(x) -
		 LmiWideStringLength(x). The string\'s length will be adjusted
		 accordingly.}}
   }
*/
void LmiWideStringReleaseBuffer(LmiWideString* x, LmiSizeT buflen);


/**
   {function:
     {name: LmiWideStringAt}
     {parent: LmiWideString}
     {description: Get a pointer to the character stored at a specific
       position in a string.}
     {prototype: LmiWideChar* LmiWideStringAt(LmiWideString* x, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string from which the character should be
         extracted.}}
     {parameter:
       {name: n}
       {description: The position of the character to be extracted.}}
     {return: A pointer to the character to be extracted.  This pointer is
       invalidated if a non-const member function, other than LmiWideStringAt,
       is invoked on x.  It is not valid to write to this pointer.}
   }
*/
LMI_INLINE_DECLARATION LmiWideChar* LmiWideStringAt(LmiWideString* x, LmiSizeT n);


/**
   {function:
     {name: LmiWideStringAtConst}
     {parent: LmiWideString}
     {description: Get a constant pointer to the character stored at a
       specific position in a string.}
     {prototype: const LmiWideChar* LmiWideStringAtConst(const LmiWideString* x, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string from which the character should be
         extracted.}}
     {parameter:
       {name: n}
       {description: The position of the character to be extracted.}}
     {return: A pointer to the character to be extracted.  This pointer is
       invalidated if a non-const member function, other than LmiWideStringAt,
       is invoked on x.}
   }
*/
LMI_INLINE_DECLARATION const LmiWideChar* LmiWideStringAtConst(const LmiWideString* x, LmiSizeT n);


/**
   {function:
     {name: LmiWideStringEmpty}
     {parent: LmiWideString}
     {description: Determine whether a string is empty.}
     {prototype: LmiBool LmiWideStringEmpty(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose emptiness to determine.}}
     {return: True if the string is empty, else false.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiWideStringEmpty(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringClear}
     {parent: LmiWideString}
     {description: Erase the contents of a string.}
     {prototype: void LmiWideStringClear(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string to clear.}}
     {note: Does not necessarily alter the string's capacity.}
   }
*/
LMI_INLINE_DECLARATION void LmiWideStringClear(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringBegin}
     {parent: LmiWideString}
     {description: Get an iterator referring to the beginning of a string.}
     {prototype: LmiWideStringIterator LmiWideStringBegin(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose begin iterator to obtain.}}
     {return: An iterator referring to the beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringIterator LmiWideStringBegin(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringBeginConst}
     {parent: LmiWideString}
     {description: Get an iterator referring to the beginning of a
       const string.}
     {prototype: LmiWideStringConstIterator LmiWideStringBeginConst(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose const begin iterator to obtain.}}
     {return: A constant iterator referring to the beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringConstIterator LmiWideStringBeginConst(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringEnd}
     {parent: LmiWideString}
     {description: Get an iterator referring to the end of a string.}
     {prototype: LmiWideStringIterator LmiWideStringEnd(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose end iterator to obtain.}}
     {return: An iterator referring to the end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringIterator LmiWideStringEnd(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringEndConst}
     {parent: LmiWideString}
     {description: Get an iterator referring to the end of a
       const string.}
     {prototype: LmiWideStringConstIterator LmiWideStringEndConst(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose const end iterator to obtain.}}
     {return: A constant iterator referring to the end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringConstIterator LmiWideStringEndConst(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringRBegin}
     {parent: LmiWideString}
     {description: Get a reverse iterator referring to the reversed beginning (end) of a string.}
     {prototype: LmiWideStringReverseIterator LmiWideStringRBegin(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose reverse begin iterator to obtain.}}
     {return: An iterator referring to the reversed beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringReverseIterator LmiWideStringRBegin(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringRBeginConst}
     {parent: LmiWideString}
     {description: Get an iterator referring to the reversed beginning (end) of a
       const string.}
     {prototype: LmiWideStringConstReverseIterator LmiWideStringRBeginConst(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose const reverse begin iterator to obtain.}}
     {return: A constant iterator referring to the reversed beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringConstReverseIterator LmiWideStringRBeginConst(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringREnd}
     {parent: LmiWideString}
     {description: Get an iterator referring to the reversed end (beginning) of a string.}
     {prototype: LmiWideStringReverseIterator LmiWideStringREnd(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose reversed end iterator to obtain.}}
     {return: An iterator referring to the reversed end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringIterator LmiWideStringREnd(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringREndConst}
     {parent: LmiWideString}
     {description: Get an iterator referring to the reversed end (beginning) of a
       const string.}
     {prototype: LmiWideStringConstReverseIterator LmiWideStringREndConst(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose const reversed end iterator to obtain.}}
     {return: A constant iterator referring to the reversed end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiWideStringConstReverseIterator LmiWideStringREndConst(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringFront}
     {parent: LmiWideString}
     {description: Return a pointer to the first character in a string.}
     {prototype: LmiWideChar* LmiWideStringFront(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose first character to obtain.}}
     {return: A pointer to the first character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION LmiWideChar* LmiWideStringFront(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringFrontConst}
     {parent: LmiWideString}
     {description: Return a pointer to the first character in a const string.}
     {prototype: const LmiWideChar* LmiWideStringFrontConst(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose first character to obtain.}}
     {return: A pointer to the first character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION const LmiWideChar* LmiWideStringFrontConst(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringBack}
     {parent: LmiWideString}
     {description: Return a pointer to the last character in a string.}
     {prototype: LmiWideChar* LmiWideStringBack(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose last character to obtain.}}
     {return: A pointer to the last character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION LmiWideChar* LmiWideStringBack(LmiWideString* x);


/**
   {function:
     {name: LmiWideStringBackConst}
     {parent: LmiWideString}
     {description: Return a pointer to the last character in a const string.}
     {prototype: const LmiWideChar* LmiWideStringBackConst(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string whose last character to obtain.}}
     {return: A pointer to the last character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION const LmiWideChar* LmiWideStringBackConst(const LmiWideString* x);


/**
   {function:
     {name: LmiWideStringAssignChar}
     {parent: LmiWideString}
     {description: Assign a single character as the new value of an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAssignChar(LmiWideString* x, LmiWideChar c)}
     {parameter:
       {name: x}
       {description: The string to assign to.}}
     {parameter:
       {name: c}
       {description: The character to be assigned.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAssignChar(LmiWideString* x, LmiWideChar c);

/**
   {function:
     {name: LmiWideStringAssignSubstring}
     {parent: LmiWideString}
     {description: Assign a substring of one LmiWideString as the new value
       of another.}
     {prototype: LmiWideString* LmiWideStringAssignSubstring(LmiWideString* x, const LmiWideString* str, LmiSizeT pos, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to assign to.}}
     {parameter:
       {name: str}
       {description: The string of which a substring is to be assigned.}}
     {parameter:
       {name: pos}
       {description: The offset within str of the beginning of the substring.  Must be <= LmiWideStringLength(str).}}
     {parameter:
       {name: n}
       {description: The length of the substring to be assigned.  If n
         is larger than LmiWideStringLength(str) - pos, the entire string
         following pos will be inserted.  (In particular, LMI_WIDE_STRING_NPOS
         indicates the entire rest of the string.)}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAssignSubstring(LmiWideString* x, const LmiWideString* str,
                                     LmiSizeT pos, LmiSizeT n);

/**
   {function:
     {name: LmiWideStringAssignCStr}
     {parent: LmiWideString}
     {description: Assign a NUL-terminated C wide string as the new value of an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAssignCStr(LmiWideString* x, const LmiWideChar* str)}
     {parameter:
       {name: x}
       {description: The string to which to assign {italic: str}.}}
     {parameter:
       {name: str}
       {description: The NUL-terminated C wide string to assign.}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiWideString* LmiWideStringAssignCStr(LmiWideString* x, const LmiWideChar* s);

/**
   {function:
     {name: LmiWideStringAssignCStrLen}
     {parent: LmiWideString}
     {description: Assign a C wide string of a given length as the new value of
       an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAssignCStrLen(LmiWideString* x, const LmiWideChar* str, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to which to assign {italic: str}.}}
     {parameter:
       {name: str}
       {description: The C wide string to assign.}}
     {parameter:
       {name: n}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure or pos out of range, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAssignCStrLen(LmiWideString* x,
                                   const LmiWideChar* str, LmiSizeT n);

/**
   {function:
     {name: LmiWideStringAssignRange}
     {parent: LmiWideString}
     {description: Assign a range of characters as the new value of
       an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAssignRange(LmiWideString* x, LmiWideStringConstIterator first, LmiWideStringConstIterator last)}
     {parameter:
       {name: x}
       {description: The string to which to assign the range.}}
     {parameter:
       {name: first}
       {description: The beginning of the range to assign.}}
     {parameter:
       {name: last}
       {description: The (non-inclusive) end of the range to assign.
         \[first,last\) must be a valid range.}}
     {return: NULL on allocation failure, else {italic:x}.}
     {note: It is valid for the replacement range to come from {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAssignRange(LmiWideString* x, LmiWideStringConstIterator first,
                                 LmiWideStringConstIterator last);


/**
	{function:
		{name: LmiWideStringAssignUtf8}
		{parent: LmiWideString}
		{description: Assign a wide string to have the Unicode values of a UTF8-encoded narrow C string.}
		{prototype: LmiWideString* LmiWideStringAssignUtf8(LmiWideString* x, const char* utf8)}
		{parameter:
			{name: x}
			{description: A pointer to the string to construct.}}
		{parameter:
			{name: utf8}
			{description: A NUL-terminated UTF-8 encoded narrow C string.}}
		{return: NULL on allocation or conversion failure, else {italic: x}.}
	}
*/
LmiWideString* LmiWideStringAssignUtf8(LmiWideString* x, const char* utf8);


/**
	{function:
		{name: LmiWideStringAssignUtf8Len}
		{parent: LmiWideString}
		{description: Assign a wide string to have the Unicode values of a UTF8-encoded narrow C string of a given length.}
		{prototype: LmiWideString* LmiWideStringAssignUtf8Len(LmiWideString* x, const char* utf8, LmiSizeT len)}
		{parameter:
			{name: x}
			{description: A pointer to the string to construct.}}
		{parameter:
			{name: utf8}
			{description: A UTF-8 encoded narrow C string.  This may contain NUL bytes.}}
		{parameter:
			{name: len}
			{description: The length of the UTF-8 encoded narrow C string, in bytes.  This length must encompass entire
				well-formed UTF-8 characters.}}
		{return: NULL on allocation or conversion failure, else {italic: x}.}
	}
*/
LmiWideString* LmiWideStringAssignUtf8Len(LmiWideString* x, const char* utf8, LmiSizeT len);

/**
	{function:
		{name: LmiWideStringAssignUtf16}
		{parent: LmiWideString}
		{description: Assign a wide string to have the Unicode values of a UTF16-encoded C string.}
		{prototype: LmiWideString* LmiWideStringAssignUtf16(LmiWideString* x, const LmiUint16* utf16)}
		{parameter:
			{name: x}
			{description: A pointer to the string to construct.}}
		{parameter:
			{name: utf16}
			{description: A NUL-terminated UTF-8 narrow C string.}}
		{return: NULL on allocation or conversion failure, else {italic: x}.}
	}
*/
LmiWideString* LmiWideStringAssignUtf16(LmiWideString* x, const LmiUint16* utf16);


/* * - Not currently supported 
   {function:
     {name: LmiWideStringAssignFormatted}
     {parent: LmiWideString}
     {description: Assign a printf-style formatted string as the new value of
       an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAssignFormatted(LmiWideString* x,
       const LmiWideChar* fmt, ...)}
     {parameter:
       {name: x}
       {description: The string to which to assign a formatted string.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the assigned string.}}
	 {parameter:
	   {name: ...}
	   {description:  The arguments to {italic:fmt}.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringAssignFormatted(LmiWideString* x, const LmiWideChar* fmt, ...)
  LmiFunctionPrintfLike(2, 3);
*/

/* * - Not currently supported
   {function:
     {name: LmiWideStringAssignVFormatted}
     {parent: LmiWideString}
     {description: Assign a vprintf-style formatted string as the new value of
       an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAssignVFormatted(LmiWideString* x,
       const LmiWideChar* fmt, va_list args)}
     {parameter:
       {name: x}
       {description: The string to which to assign a formatted string.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the assigned string.}}
     {parameter:
       {name: args}
       {description: The arguments to {italic:fmt}, as constructed by
         the functions of <stdarg.h>.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringAssignVFormatted(LmiWideString* x, const LmiWideChar* fmt, va_list args)
  LmiFunctionVPrintfLike(2);
*/

/**
   {function:
     {name: LmiWideStringAppend}
     {parent: LmiWideString}
     {description: Append the contents of one LmiWideString to another.}
     {prototype: LmiWideString* LmiWideStringAppend(LmiWideString* x, const LmiWideString* str)}
     {parameter:
       {name: x}
       {description: The string to append to.}}
     {parameter:
       {name: str}
       {description: The string to be appended.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAppend(LmiWideString* x, const LmiWideString* str);

/**
   {function:
     {name: LmiWideStringAppendChar}
     {parent: LmiWideString}
     {description: Append a single character to an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAppendChar(LmiWideString* x, LmiWideChar c)}
     {parameter:
       {name: x}
       {description: The string to append to.}}
     {parameter:
       {name: c}
       {description: The character to be appended.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAppendChar(LmiWideString* x, LmiWideChar c);

/**
   {function:
     {name: LmiWideStringAppendSubstring}
     {parent: LmiWideString}
     {description: Append a substring of one LmiWideString to another.}
     {prototype: LmiWideString* LmiWideStringAppendSubstring(LmiWideString* x, const LmiWideString* str, LmiSizeT pos, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to append to.}}
     {parameter:
       {name: str}
       {description: The string of which a substring is to be appended.}}
     {parameter:
       {name: pos}
       {description: The offset within str of the beginning of the substring.  Must be <= LmiWideStringLength(str).}}
     {parameter:
       {name: n}
       {description: The length of the substring to be appended.  If n
         is larger than LmiWideStringLength(str) - pos, the entire string
         following pos will be inserted.  (In particular, LMI_WIDE_STRING_NPOS
         indicates the entire rest of the string.)}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAppendSubstring(LmiWideString* x, const LmiWideString* str,
                                     LmiSizeT pos, LmiSizeT n);

/**
   {function:
     {name: LmiWideStringAppendCStr}
     {parent: LmiWideString}
     {description: Append a NUL-terminated C wide string to an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAppendCStr(LmiWideString* x, const LmiWideChar* str)}
     {parameter:
       {name: x}
       {description: The string to which to append {italic: str}.}}
     {parameter:
       {name: str}
       {description: The NUL-terminated C wide string to append.}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiWideString* LmiWideStringAppendCStr(LmiWideString* x, const LmiWideChar* s);


/**
   {function:
     {name: LmiWideStringAppendCStrLen}
     {parent: LmiWideString}
     {description: Append a C wide string of a given length to an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAppendCStrLen(LmiWideString* x, const LmiWideChar* str, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to which to append {italic: str}.}}
     {parameter:
       {name: str}
       {description: The C wide string to append.}}
     {parameter:
       {name: n}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAppendCStrLen(LmiWideString* x,
                                   const LmiWideChar* str, LmiSizeT n);


/**
   {function:
     {name: LmiWideStringAppendN}
	 {parent: LmiWideString}
	 {description: Append multiple copies of a character to an LmiWideString.}
	 {prototype: LmiWideString* LmiWideStringAppendN(LmiWideString* x, LmiSizeT n, LmiWideChar c)}
	 {parameter:
	   {name: x}
	   {description: The string to which to append {italic:n} copies of {italic:c}.}}
	 {parameter:
	   {name: n}
	   {description: The number of copies of {italic:c} to append.}}
	 {parameter:
 	   {name: c}
	   {description: The character to append.}}
	 {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAppendN(LmiWideString* x, LmiSizeT n, LmiWideChar c);


/**
   {function:
     {name: LmiWideStringAppendRange}
     {parent: LmiWideString}
     {description: Append a range of characters to a string.}
     {prototype: LmiWideString* LmiWideStringAppendRange(LmiWideString* x, LmiWideStringConstIterator first, LmiWideStringConstIterator last)}
     {parameter:
       {name: x}
       {description: The string to which to append the range.}}
     {parameter:
       {name: first}
       {description: The beginning of the range to insert.}}
     {parameter:
       {name: last}
       {description: The (non-inclusive) end of the range to insert.
         \[first,last\) must be a valid range.}}
     {return: NULL on allocation failure, else {italic:x}.}
     {note: It is valid for the appended range to come from {italic:x}.}
   }
*/
LmiWideString* LmiWideStringAppendRange(LmiWideString* x, LmiWideStringConstIterator first,
                                 LmiWideStringConstIterator last);


/* * - Not currently supported
   {function:
     {name: LmiWideStringAppendFormatted}
     {parent: LmiWideString}
     {description: Append a printf-style formatted string to an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAppendFormatted(LmiWideString* x,
       const LmiWideChar* fmt, ...)}
     {parameter:
       {name: x}
       {description: The string to which to append a formatted string.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the appended string.}}
	 {parameter:
	   {name: ...}
	   {description:  The arguments to {italic:fmt}.}}
     {return: NULL on allocation failure, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringAppendFormatted(LmiWideString* x, const LmiWideChar* fmt, ...)
  LmiFunctionPrintfLike(2, 3);
*/

/* * - Not currently supported
   {function:
     {name: LmiWideStringAppendVFormatted}
     {parent: LmiWideString}
     {description: Append a vprintf-style formatted string to an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringAppendVFormatted(LmiWideString* x,
       const LmiWideChar* fmt, va_list args)}
     {parameter:
       {name: x}
       {description: The string to which to append a formatted string.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the appended string.}}
     {parameter:
       {name: args}
       {description: The arguments to {italic:fmt}, as constructed by
         the functions of <stdarg.h>.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringAppendVFormatted(LmiWideString* x, const LmiWideChar* fmt, va_list args)
  LmiFunctionVPrintfLike(2);
*/

/**
   {function:
     {name: LmiWideStringInsert}
     {parent: LmiWideString}
     {description: Insert a single character into a string.}
     {prototype: LmiWideStringIterator LmiWideStringInsert(LmiWideString* x,
                                                   LmiWideStringIterator pos,
                                                   const LmiWideChar* c)}
     {parameter:
       {name: x}
       {description: The string to which to insert a character.}}
     {parameter:
       {name: pos}
       {description: An iterator pointing to the position at which to insert
         the character. Must be a valid iterator into x.}}
     {parameter:
       {name: c}
       {description: A pointer to the character to insert.}}
     {return: An iterator pointing to the inserted character.  On allocation
       failure, the string is unchanged and an exceptional iterator is
       returned.}
   }
*/
LmiWideStringIterator LmiWideStringInsert(LmiWideString* x, LmiWideStringIterator pos,
                                  const LmiWideChar* c);

/**
   {function:
     {name: LmiWideStringInsertRange}
     {parent: LmiWideString}
     {description: Insert a range of characters into a string.}
     {prototype: LmiBool LmiWideStringInsertRange(LmiWideString* x, LmiWideStringIterator pos, LmiWideStringConstIterator first, LmiWideStringConstIterator last)}
     {parameter:
       {name: x}
       {description: The string to which to insert a range of characters.}}
     {parameter:
       {name: pos}
       {description: An iterator pointing to the position at which to insert
         the range of characters. Must be a valid iterator into x.}}
     {parameter:
       {name: first}
       {description: A constant iterator pointing to the beginning of the
         range to insert.}}
     {parameter:
       {name: last}
       {description: A constant iterator pointing to the end (non-inclusive)
         of the range to insert.  \[first,last\) must be a valid range.}}
     {return: LMI_FALSE on allocation failure, else LMI_TRUE.}
     {note: It is valid for the replacement range to come from {italic:x}.}
   }
*/
LmiBool LmiWideStringInsertRange(LmiWideString* x, LmiWideStringIterator pos,
                             LmiWideStringConstIterator first,
                             LmiWideStringConstIterator last);

/**
   {function:
     {name: LmiWideStringInsertString}
     {parent: LmiWideString}
     {description: Insert the contents of one LmiWideString into another.}
     {prototype: LmiWideString* LmiWideStringInsertString(LmiWideString* x, LmiSizeT pos, const LmiWideString* str)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert {italic: str}. Must be
         <= LmiWideStringLength(x).}}
     {parameter:
       {name: str}
       {description: The string to insert.}}
     {return: NULL on allocation failure or pos out of range,
       else {italic: x}.}
   }
*/
LmiWideString* LmiWideStringInsertString(LmiWideString* x, LmiSizeT pos,
                                  const LmiWideString* str);

/**
   {function:
     {name: LmiWideStringInsertChar}
     {parent: LmiWideString}
     {description: Insert a single character in an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringInsertChar(LmiWideString* x, LmiSizeT pos, LmiWideChar c)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert {italic: c}. Must be
         <= LmiWideStringLength(x).}}
     {parameter:
       {name: c}
       {description: The character to insert.}}
     {return: NULL on allocation failure or pos out of range,
       else {italic: x}.}
   }
*/
LmiWideString* LmiWideStringInsertChar(LmiWideString* x, LmiSizeT pos,
                                  LmiWideChar c);

/**
   {function:
     {name: LmiWideStringInsertSubstring}
     {parent: LmiWideString}
     {description: Insert part of the content of one LmiWideString into another.}
     {prototype: LmiWideString* LmiWideStringInsertSubstring(LmiWideString* x, LmiSizeT pos1, const LmiWideString* str, LmiSizeT pos2, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos1}
       {description: The offset at which to insert the substring of
         {italic: str}. Must be <= LmiWideStringLength(x).}}
     {parameter:
       {name: str}
       {description: The string to insert.}}
     {parameter:
       {name: pos2}
       {description: The offset within {italic: str} to begin the
         substring.  Must be <= LmiWideStringLength(str).}}
     {parameter:
       {name: n}
       {description: The length of the substring within {italic: str}.
         If this is larger than LmiWideStringLength(str) - pos2, the entire string
         following pos2 will be inserted.  (In particular, LMI_WIDE_STRING_NPOS
         indicates the entire rest of the string.)}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiWideString* LmiWideStringInsertSubstring(LmiWideString* x, LmiSizeT pos1,
                                     const LmiWideString* str, LmiSizeT pos2,
                                     LmiSizeT n);

/**
   {function:
     {name: LmiWideStringInsertCStr}
     {parent: LmiWideString}
     {description: Insert a NUL-terminated C wide string into an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringInsertCStr(LmiWideString* x, LmiSizeT pos, const LmiWideChar* str)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert the substring of
         {italic: str}. Must be <= LmiWideStringLength(x).}}
     {parameter:
       {name: str}
       {description: The NUL-terminated C wide string to insert.}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiWideString* LmiWideStringInsertCStr(LmiWideString* x, LmiSizeT pos, const LmiWideChar* s);


/**
   {function:
     {name: LmiWideStringInsertCStrLen}
     {parent: LmiWideString}
     {description: Insert a C wide string of a given length into an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringInsertCStrLen(LmiWideString* x, LmiSizeT pos, const LmiWideChar* str, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert the substring of
         {italic: str}. Must be <= LmiWideStringLength(x).}}
     {parameter:
       {name: str}
       {description: The C wide string to insert.}}
     {parameter:
       {name: n}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure or pos out of range, else {italic:x}.}
   }
*/
LmiWideString* LmiWideStringInsertCStrLen(LmiWideString* x, LmiSizeT pos,
                                   const LmiWideChar* s, LmiSizeT n);


/* *  not a docblock
   {function:
     {name: LmiWideStringInsertN}
     {parent: LmiWideString}
     {description: Insert several copies of a character into a string.}
     {prototype: LmiBool LmiWideStringInsertN(LmiWideString* x, LmiWideStringIterator pos, LmiSizeT n, const LmiWideChar* c)}
     {parameter:
       {name: x}
       {description: The string to which to insert the characters.}}
     {parameter:
       {name: pos}
       {description: An iterator pointing to the position at which to insert
         the characters. Must be a valid iterator into x.}}
     {parameter:
       {name: n}
       {description: The number of copies of c to insert.}}
     {parameter:
       {name: c}
       {description: A pointer to the single character to insert.}}
     {return: LMI_FALSE on allocation failure, else LMI_TRUE.}
   }
*/
/*  -- Not yet implemented --
LmiBool LmiWideStringInsertN(LmiWideString* x, LmiWideStringIterator pos,
                         LmiSizeT n, const LmiWideChar* c);
*/

/* * - Not yet implemented
   {function:
     {name: LmiWideStringInsertFormatted}
     {parent: LmiWideString}
     {description: Insert a printf-style formatted string into an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringInsertFormatted(LmiWideString* x,
       LmiSizeT pos, const LmiWideChar* fmt, ...)}
     {parameter:
       {name: x}
       {description: The string in which to insert a formatted string.}}
     {parameter:
       {name: pos}
       {description: The offset within x at which to insert the formatted
         string.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the inserted string.}}
	 {parameter:
	   {name: ...}
	   {description:  The arguments to {italic:fmt}.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringInsertFormatted(LmiWideString* x, LmiSizeT pos, const LmiWideChar* fmt, ...)
  LmiFunctionPrintfLike(3, 4);
*/

/* * - Not yet implemented
   {function:
     {name: LmiWideStringInsertVFormatted}
     {parent: LmiWideString}
     {description: Insert a vprintf-style formatted string into an LmiWideString.}
     {prototype: LmiWideString* LmiWideStringInsertVFormatted(LmiWideString* x,
	   LmiSizeT pos, const LmiWideChar* fmt, va_list args)}
     {parameter:
       {name: x}
       {description: The string in which to insert a formatted string.}}
     {parameter:
       {name: pos}
       {description: The offset within x at which to insert the formatted
         string.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the inserted string.}}
     {parameter:
       {name: args}
       {description: The arguments to {italic:fmt}, as constructed by
         the functions of <stdarg.h>.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringInsertVFormatted(LmiWideString* x, LmiSizeT pos, const LmiWideChar* fmt,
                          va_list args)
  LmiFunctionVPrintfLike(3);
*/

/**
   {function:
     {name: LmiWideStringReplaceString}
     {parent: LmiWideString}
     {description: Replace part of an LmiWideString with another LmiWideString.}
     {prototype: LmiWideString* LmiWideStringReplaceString(LmiWideString* x,
       LmiSizeT pos1, LmiSizeT n1, const LmiWideString* str)}
     {parameter:
       {name: x}
       {description: The string in which to replace a substring.}}
     {parameter:
       {name: pos1}
       {description: The position within x of the beginning of the substring
         to replace.}}
     {parameter:
       {name: n1}
       {description: The length of the substring to replace.}}
     {parameter:
       {name: str}
       {description: The string to insert.}}
     {return: NULL on allocation failure or pos1 out of range, else x.}
   }
*/
LmiWideString*
LmiWideStringReplaceString(LmiWideString* x, LmiSizeT pos1, LmiSizeT n1,
                       const LmiWideString* str);

/**
   {function:
     {name: LmiWideStringReplaceChar}
     {parent: LmiWideString}
     {description: Replace part of an LmiWideString with a single character.}
     {prototype: LmiWideString* LmiWideStringReplaceChar(LmiWideString* x,
       LmiSizeT pos1, LmiSizeT n1, LmiWideChar c)}
     {parameter:
       {name: x}
       {description: The string in which to replace a substring with a character.}}
     {parameter:
       {name: pos1}
       {description: The position within x of the beginning of the substring
         to replace.}}
     {parameter:
       {name: n1}
       {description: The length of the substring to replace.}}
     {parameter:
       {name: c}
       {description: The character to insert.}}
     {return: NULL on allocation failure or pos1 out of range, else x.}
   }
*/
LmiWideString*
LmiWideStringReplaceChar(LmiWideString* x, LmiSizeT pos1, LmiSizeT n1, LmiWideChar c);

/**
   {function:
     {name: LmiWideStringReplaceSubstring}
     {parent: LmiWideString}
     {description: Replace part of an LmiWideString with part of another
       LmiWideString.}
     {prototype: LmiWideString* LmiWideStringReplaceSubstring(LmiWideString* x,
       LmiSizeT pos1, LmiSizeT n1, const LmiWideString* str, LmiSizeT pos2,
       LmiSizeT n2)}
     {parameter:
       {name: x}
       {description: The string in which to replace a substring.}}
     {parameter:
       {name: pos1}
       {description: The position within x of the beginning of the substring
         to replace.}}
     {parameter:
       {name: n1}
       {description: The length of the substring to replace.}}
     {parameter:
       {name: str}
       {description: The string from which to obtain the replacement
         substring.}}
     {parameter:
       {name: pos2}
       {description: The position within str of the beginning of the
         replacement substring.}}
     {parameter:
       {name: n2}
       {description: The length of the replacement substring.}}
     {return: NULL on allocation failure or pos1 or pos2 out of range, else x.}
   }
*/
LmiWideString*
LmiWideStringReplaceSubstring(LmiWideString* x, LmiSizeT pos1, LmiSizeT n1,
                          const LmiWideString* str, LmiSizeT pos2, LmiSizeT n2);

/**
   {function:
     {name: LmiWideStringReplaceCStr}
     {parent: LmiWideString}
     {description: Replace part of an LmiWideString with a C wide string.}
     {prototype: LmiWideString* LmiWideStringReplaceCStr(LmiWideString* x,
       LmiSizeT pos1, LmiSizeT n1, const LmiWideChar* str)}
     {parameter:
       {name: x}
       {description: The string in which to replace a substring.}}
     {parameter:
       {name: pos1}
       {description: The position within x of the beginning of the substring
         to replace.}}
     {parameter:
       {name: n1}
       {description: The length of the substring to replace.}}
     {parameter:
       {name: str}
       {description: The NUL-terminated C wide string to insert.}}
     {return: NULL on allocation failure or pos1 out of range, else x.}
   }
*/
LmiWideString*
LmiWideStringReplaceCStr(LmiWideString* x, LmiSizeT pos1, LmiSizeT n1,
                     const LmiWideChar* str);

/**
   {function:
     {name: LmiWideStringReplaceCStrLen}
     {parent: LmiWideString}
     {description: Replace part of an LmiWideString with a C wide string of a given length.}
     {prototype: LmiWideString* LmiWideStringReplaceCStrLen(LmiWideString* x,
       LmiSizeT pos1, LmiSizeT n1, const LmiWideChar* str, LmiSizeT n2)}
     {parameter:
       {name: x}
       {description: The string in which to replace a substring.}}
     {parameter:
       {name: pos1}
       {description: The position within x of the beginning of the substring
         to replace.}}
     {parameter:
       {name: n1}
       {description: The length of the substring to replace.}}
     {parameter:
       {name: str}
       {description: The C wide string to insert.}}
     {parameter:
       {name: n2}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure or pos1 out of range, else x.}
   }
*/
LmiWideString*
LmiWideStringReplaceCStrLen(LmiWideString* x, LmiSizeT pos1, LmiSizeT n1,
                        const LmiWideChar* str, LmiSizeT n2);

/**
   {function:
     {name: LmiWideStringReplaceRange}
     {parent: LmiWideString}
     {description: Replace a range of an LmiWideString with a different range of string iterators.}
     {prototype: LmiWideString* LmiWideStringReplaceRange(LmiWideString* x,
       LmiWideStringIterator i1, LmiWideStringIterator i2,
       LmiWideStringConstIterator j1, LmiWideStringConstIterator j2)}
     {parameter:
       {name: x}
       {description: The string in which to replace a range.}}
     {parameter:
       {name: i1}
       {description: The beginning of the range in {italic:x} to be replaced.}}
     {parameter:
       {name: i2}
       {description: The end of the range in {italic:x} to be replaced.}}
     {parameter:
       {name: j1}
       {description: The beginning of the replacement range.}}
     {parameter:
       {name: j2}
       {description: The end of the replacement range.}}
     {return: NULL on allocation failure out of range, else {italic:x}.}
     {note: It is valid for the replacement range to come from {italic:x},
       and even for the ranges to overlap.}
   }
*/
LmiWideString*
LmiWideStringReplaceRange(LmiWideString* x,
                      LmiWideStringIterator i1, LmiWideStringIterator i2,
                      LmiWideStringConstIterator j1, LmiWideStringConstIterator j2);

/* * - Not yet implemented
   {function:
     {name: LmiWideStringReplaceFormatted}
     {parent: LmiWideString}
     {description: Replace part of an LmiWideString with a printf-style formatted string.}
     {prototype: LmiWideString* LmiWideStringReplaceFormatted(LmiWideString* x,
       LmiSizeT pos, LmiSizeT n, const LmiWideChar* fmt, ...)}
     {parameter:
       {name: x}
       {description: The string in which to replace a substring.}}
     {parameter:
       {name: pos}
       {description: The position within x of the beginning of the substring
         to replace.}}
     {parameter:
       {name: n}
       {description: The length of the substring to replace.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the replacement string.}}
	 {parameter:
	   {name: ...}
	   {description:  The arguments to {italic:fmt}.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringReplaceFormatted(LmiWideString* x, LmiSizeT pos, LmiSizeT n,
                          const LmiWideChar* fmt, ...)
  LmiFunctionPrintfLike(4, 5);
*/

/* * - Not yet implemented
   {function:
     {name: LmiWideStringReplaceVFormatted}
     {parent: LmiWideString}
     {description: Replace part of an LmiWideString with a vprintf-style
       formatted string.}
     {prototype: LmiWideString* LmiWideStringReplaceVFormatted(LmiWideString* x,
       LmiSizeT pos, LmiSizeT n, const LmiWideChar* fmt, va_list args)}
     {parameter:
       {name: x}
       {description: The string in which to replace a substring.}}
     {parameter:
       {name: pos}
       {description: The position within x of the beginning of the substring
         to replace.}}
     {parameter:
       {name: n}
       {description: The length of the substring to replace.}}
     {parameter:
       {name: fmt}
       {description: The printf-style format for the replacement string.}}
     {parameter:
       {name: args}
       {description: The arguments to {italic:fmt}, as constructed by
         the functions of <stdarg.h>.}}
     {return: NULL on allocation failure or pos out of range, else x.}
   }
*/
/*
LmiWideString*
LmiWideStringReplaceVFormatted(LmiWideString* x, LmiSizeT pos, LmiSizeT n,
                          const LmiWideChar* fmt, va_list args)
  LmiFunctionVPrintfLike(4);
*/

/**
   {function:
     {name: LmiWideStringErase}
     {parent: LmiWideString}
     {description: Remove a single character from a string.}
     {prototype: LmiWideStringIterator LmiWideStringErase(LmiWideString* x,
                                                  LmiWideStringIterator p)}
     {parameter:
       {name: x}
       {description: The string from which to erase a range.}}
     {parameter:
       {name: p}
       {description: An iterator pointing to the character to erase.
         Must be a valid iterator into x.}}
     {return: An iterator pointing to the element which followed 'p' prior to
       the range being erased.  If no such element exists, end() is returned.}
   }
*/
LmiWideStringIterator LmiWideStringErase(LmiWideString* x, LmiWideStringIterator p);

/**
   {function:
     {name: LmiWideStringEraseSubstring}
     {parent: LmiWideString}
     {description: Remove a substring from a string.}
     {prototype: LmiWideString* LmiWideStringEraseSubstring(LmiWideString* x,
                            LmiSizeT pos, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string from which to erase a substring.}}
     {parameter:
       {name: pos}
       {description: The position of the beginning of the range to erase.
         Must be less than or equal to LmiWideStringLength(x).}}
     {parameter:
       {name: n}
       {description: The number of characters to remove from the string.
         To remove all characters, pass LMI_WIDE_STRING_NPOS.}}
     {return: The argument passed in, i.e. x.}
   }
*/
LmiWideString* LmiWideStringEraseSubstring(LmiWideString* x, LmiSizeT pos, LmiSizeT n);

/**
   {function:
     {name: LmiWideStringEraseRange}
     {parent: LmiWideString}
     {description: Remove a range from a string.}
     {prototype: LmiWideStringIterator LmiWideStringEraseRange(LmiWideString* x,
                            LmiWideStringIterator b, LmiWideStringIterator e)}
     {parameter:
       {name: x}
       {description: The string from which to erase a range.}}
     {parameter:
       {name: b}
       {description: The beginning of the range to erase.  Must be a valid
         iterator into x.}}
     {parameter:
       {name: e}
       {description: The end (non-inclusive) of the range to erase.  Must be
         a valid iterator into x.}}
     {return: An iterator to the element which followed 'e' prior to the
       range being erased.  If no such element exists, end() is returned.}
   }
*/
LmiWideStringIterator LmiWideStringEraseRange(LmiWideString* x, LmiWideStringIterator b,
                                      LmiWideStringIterator e);


/**
   {function:
     {name: LmiWideStringCompare}
     {parent: LmiWideString}
     {description: Compare the values of two LmiWideStrings for ordering.}
     {prototype: LmiInt LmiWideStringCompare(const LmiWideString* x, const LmiWideString* y)}
     {parameter:
       {name: x}
       {description: A pointer to the first string object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the second string object to compare.}
     }
     {return: A value <0, 0, or >0, depending on whether x is
       lexicographically less than, equal to, or greater than y, respectively.}
     {note: Comparison is done on a character-by-character basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiInt LmiWideStringCompare(const LmiWideString* x, const LmiWideString* y);


/**
   {function:
     {name: LmiWideStringCompareCStr}
     {parent: LmiWideString}
     {description: Compare the value of an LmiWideString with that of a C wide string
       for ordering.}
     {prototype: LmiInt LmiWideStringCompareCStr(const LmiWideString* x, const LmiWideChar* y)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiWideString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the C wide string to compare.}
     }
     {return: A value <0, 0, or >0, depending on whether x is
       lexicographically less than, equal to, or greater than y, respectively.}
     {note: Comparison is done on a character-by-character basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiInt LmiWideStringCompareCStr(const LmiWideString* x, const LmiWideChar* y);


/**
   {function:
     {name: LmiWideStringCompareCStrLen}
     {parent: LmiWideString}
     {description: Compare the value of an LmiWideString with that of a C wide string
       of a given length for ordering.}
     {prototype: LmiInt LmiWideStringCompareCStrLen(const LmiWideString* x, const LmiWideChar* y, LmiSizeT ylen)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiWideString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to an array of char.  The contents of x will be compared to the first {italic:ylen} characters of y.  The array may include NUL.}
     }
	 {parameter:
	   {name: ylen}
	   {description: The length of the array pointed to by {italic:y}.}
	 }
     {return: A value <0, 0, or >0, depending on whether x is
       lexicographically less than, equal to, or greater than y, respectively.}
     {note: Comparison is done on a character-by-character basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiInt LmiWideStringCompareCStrLen(const LmiWideString* x, const LmiWideChar* y, LmiSizeT ylen);


/**
   {function:
     {name: LmiWideStringPushBack}
     {parent: LmiWideString}
     {description: Push a single character onto the end of a string.}
     {prototype: LmiBool LmiWideStringPushBack(LmiWideString* x, const LmiWideChar* c)}
     {parameter:
       {name: x}
       {description: The string onto which to push a character.}}
     {parameter:
       {name: c}
       {description: A pointer to the character to push.}}
     {return: LMI_FALSE on allocation failure, else LMI_TRUE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiWideStringPushBack(LmiWideString* x, const LmiWideChar* c);


/**
   {function:
     {name: LmiWideStringPopBack}
     {parent: LmiWideString}
     {description: Pop a single character from the end of a string.}
     {prototype: void LmiWideStringPopBack(LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string from which to pop a character.}}
     {note: If the string is empty, this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION void LmiWideStringPopBack(LmiWideString* x);

/**
   {function:
     {name: LmiWideStringFindFirstOf}
     {parent: LmiWideString}
     {description: Find first location in a string where one of the
	   characters in a second string occurs.}
     {prototype: LmiSizeT LmiWideStringFindFirstOf(const LmiWideString* x, LmiSizeT pos, const LmiWideString* y)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: y}
       {description: The string whose characters are to be searched for.}}
     {return: The first position in x where a character of y occurs or LMI_WIDE_STRING_NPOS
	 if none of the characters were found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/

LmiSizeT LmiWideStringFindFirstOf(const LmiWideString* x, LmiSizeT pos, const LmiWideString* y);
/**
   {function:
     {name: LmiWideStringFindFirstOfChar}
     {parent: LmiWideString}
     {description: Find first location in a string where a given character occurs.}
     {prototype: LmiSizeT LmiWideStringFindFirstOfChar(const LmiWideString* x, LmiSizeT pos, LmiWideChar c)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: c}
       {description: The character to be searched for.}}
     {return: The first position in x where a character c occurs or LMI_WIDE_STRING_NPOS
	 if not found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiWideStringFindFirstOfChar(const LmiWideString* x, LmiSizeT pos, LmiWideChar y);

/**
   {function:
     {name: LmiWideStringFindFirstOfCStr}
     {parent: LmiWideString}
     {description: Find first location in a string where one of the
	   characters in a C wide string occurs.}
     {prototype: LmiSizeT LmiWideStringFindFirstOfCStr(const LmiWideString* x, LmiSizeT pos, const LmiWideChar* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: y}
       {description: The C wide string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The first position in x where a character of y occurs or LMI_WIDE_STRING_NPOS
	 if none of the characters were found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiWideStringFindFirstOfCStr(const LmiWideString* x, LmiSizeT pos, const LmiWideChar* y, LmiSizeT n);

/**
   {function:
     {name: LmiWideStringFindFirstNotOf}
     {parent: LmiWideString}
     {description: Find first location in a string where one of the
	   characters in a second string does not occur.}
     {prototype: LmiSizeT LmiWideStringFindFirstNotOf(const LmiWideString* x, LmiSizeT pos, const LmiWideString* y)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: y}
       {description: The string whose characters are to be searched for.}}
     {return: The first position in x where a character of y does not occur or
	 LMI_WIDE_STRING_NPOS otherwise. }
	 {note: The order of the parameters has been modified from the C++ string class
	 member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }

*/
LmiSizeT LmiWideStringFindFirstNotOf(const LmiWideString* x, LmiSizeT pos, const LmiWideString* y);

/**
   {function:
     {name: LmiWideStringFindFirstNotOfChar}
     {parent: LmiWideString}
     {description: Find first location in a string where a given character does not occur.}
     {prototype: LmiSizeT LmiWideStringFindFirstNotOfChar(const LmiWideString* x, LmiSizeT pos, LmiWideChar c)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: c}
       {description: The character to be searched for.}}
     {return: The first position in x where character c does not occurs or LMI_WIDE_STRING_NPOS otherwise. }
	 {note: The order of the parameters has been modified from the C++ string class
	 member function that this function was derived from, to make the interface
	 more logical within the constraints of the C Programming language.}
   }

*/
LmiSizeT LmiWideStringFindFirstNotOfChar(const LmiWideString* x, LmiSizeT pos, LmiWideChar c);


/**
   {function:
     {name: LmiWideStringFindFirstNotOfCStr}
     {parent: LmiWideString}
     {description: Find first location in a string where one of the
	   characters in a C wide string does not occur.}
     {prototype: LmiSizeT LmiWideStringFindFirstNotOfCStr(const LmiWideString* x, LmiSizeT pos, const LmiWideChar* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: y}
       {description: The C wide string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The first position in x where a character of y does not occur or
	 LMI_WIDE_STRING_NPOS otherwise. }
     {note: The order of the parameters has been modified from the C++ string class
	 member function that this function was derived from, to make the interface
	 more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiWideStringFindFirstNotOfCStr(const LmiWideString* x, LmiSizeT pos, const LmiWideChar* y, LmiSizeT n);

/**
   {function:
     {name: LmiWideStringFindLastOfCStr}
     {parent: LmiWideString}
     {description: Find last location in a string where one of the
	   characters in a C wide string occurs.}
     {prototype: LmiSizeT LmiWideStringFindLastOfCStr(const LmiWideString* x, LmiSizeT pos, const LmiWideChar* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start searching backward from. Set this to
          LMI_WIDE_STRING_NPOS to search the entire string.}}
     {parameter:
       {name: y}
       {description: The C wide string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The last position in x where a character of y occurs or LMI_WIDE_STRING_NPOS
	 if none of the characters were found. }
   }
*/
LmiSizeT LmiWideStringFindLastOfCStr(const LmiWideString* x, LmiSizeT pos, const LmiWideChar* y, LmiSizeT n);

/**
   {function:
     {name: LmiWideStringFindLastOfChar}
     {parent: LmiWideString}
     {description: Find last location in a string where a given character occurs.}
     {prototype: LmiSizeT LmiWideStringFindLastOfChar(const LmiWideString* x, LmiSizeT pos, LmiWideChar c)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start searching backward from. Set this to
          LMI_WIDE_STRING_NPOS to search the entire string.}}
     {parameter:
       {name: c}
       {description: The character to be searched for.}}
     {return: The last position in x where a character c occurs or LMI_WIDE_STRING_NPOS
	 if not found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiWideStringFindLastOfChar(const LmiWideString* x, LmiSizeT pos, LmiWideChar c);


/**
   {function:
     {name: LmiWideStringHash}
     {parent: LmiWideString}
     {description: Hashes a string into an integer.}
     {prototype: LmiSizeT LmiWideStringHash(const LmiWideString* x)}
     {parameter:
       {name: x}
       {description: The string to be hashed.}}
     {return: Unsigned integer value of the hashed string. }
   }
*/
LmiSizeT LmiWideStringHash(const LmiWideString* x);



/*
  ADD IF NEEDED:

   ConstructN
   AssignN
   InsertN
   ReplaceN

   Copy
   SubStr

   Find
   RFind
   FindLastOf
   FindLastNotOf
*/

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiWideStringInline.h>
#endif

#endif /* LMI_WIDE_STRING_H_ */
