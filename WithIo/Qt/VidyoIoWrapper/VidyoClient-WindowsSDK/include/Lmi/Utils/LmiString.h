/** {file:
      {name: LmiString.h}
      {description: String class.}
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

#ifndef LMI_STRING_H_
#define LMI_STRING_H_

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
     {name: LmiString}
     {parent: Utils}
     {include: Lmi/Utils/LmiString.h}
     {description: Class representing C strings.  Interface largely
       based on C++\'s std::string class.}
     {constant:
       {name: LMI_STRING_NPOS}
       {type: LmiSizeT}
       {description: For value parameters, an invalid value used to represent
         "no position".}}
   }
*/

typedef struct {
  LmiAllocator * allocator;
  char * buf;
  LmiSizeT size;
  LmiSizeT capacity;
} LmiString;

#define LMI_STRING_NPOS LMI_SIZE_T_MAX

/* return value of LmiStringData() and LmiStringCStr() if buf == NULL */
/* declared in the header file so the inline functions can reference it. */
extern const char lmiStringEmptyStr_[];

/**
   {function:
     {name: LmiStringConstructDefault}
     {parent: LmiString}
     {description: Construct an empty LmiString.}
     {prototype: LmiString* LmiStringConstructDefault(LmiString* x, LmiAllocator* a)}
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
LmiString* LmiStringConstructDefault(LmiString* x, LmiAllocator* a);

/**
   {function:
     {name: LmiStringDestruct}
     {parent: LmiString}
     {description: Destruct an LmiString, freeing all associated storage.}
     {prototype: void LmiStringDestruct(LmiString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to destruct.}
     }
   }
*/
void LmiStringDestruct(LmiString* x);

/**
   {function:
     {name: LmiStringConstructCopy}
     {parent: LmiString}
     {description: Construct a copy of an LmiString.}
     {prototype: LmiString* LmiStringConstructCopy(LmiString* x, const LmiString* y)}
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
LmiString* LmiStringConstructCopy(LmiString* x, const LmiString* y);

/**
   {function:
     {name: LmiStringAssign}
     {parent: LmiString}
     {description: Assign the value of one LmiString to another.  The
       previous data stored in the destination is overwritten.}
     {prototype: LmiString* LmiStringAssign(LmiString* x, const LmiString* y)}
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
LmiString* LmiStringAssign(LmiString* x, const LmiString* y);

/**
   {function:
     {name: LmiStringSwap}
     {parent: LmiString}
     {description: Swap the values of two LmiStrings.}
     {prototype: LmiBool LmiStringSwap(LmiString* x, LmiString* y)}
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
LmiBool LmiStringSwap(LmiString* x, LmiString* y);

/**
   {function:
     {name: LmiStringEqual}
     {parent: LmiString}
     {description: Compare the values of two LmiStrings for equality.}
     {prototype: LmiBool LmiStringEqual(const LmiString* x, const LmiString* y)}
     {parameter:
       {name: x}
       {description: A pointer to the first string object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the second string object to compare.}
     }
     {return: LMI_TRUE if the strings are equal, LMI_FALSE otherwise.}
     {note: Comparison is done on a byte-by-byte basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiBool LmiStringEqual(const LmiString* x, const LmiString* y);


/**
   {function:
     {name: LmiStringEqualCStr}
     {parent: LmiString}
     {description: Compare the value of an LmiString with that of a C string
       for equality.}
     {prototype: LmiBool LmiStringEqualCStr(const LmiString* x, const char* y)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the C string to compare.}
     }
     {return: LMI_TRUE if the strings are equal, LMI_FALSE otherwise.}
     {note: Comparison is done on a byte-by-byte basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiBool LmiStringEqualCStr(const LmiString* x, const char* y);

/**
   {function:
     {name: LmiStringEqualCStrLen}
     {parent: LmiString}
     {description: Compare the value of an LmiString with that of a C string
       of a given length for equality.}
     {prototype: LmiBool LmiStringEqualCStrLen(const LmiString* x, const char* y, LmiSizeT ylen)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to an array of char.  The contents of x will be compared to the first {italic:ylen} bytes of y.  The array may include NUL.}
     }
	 {parameter:
	   {name: ylen}
	   {description: The length of the array pointed to by {italic:y}.}
	 }
     {return: LMI_TRUE if the strings are equal, LMI_FALSE otherwise.}
     {note: Comparison is done on a byte-by-byte basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiBool LmiStringEqualCStrLen(const LmiString* x, const char* y, LmiSizeT ylen);

/**
   {function:
     {name: LmiStringLess}
     {parent: LmiString}
     {description: Compare the values of two LmiStrings for ordering.}
     {prototype: LmiBool LmiStringLess(const LmiString* x, const LmiString* y)}
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
     {note: Comparison is done on a byte-by-byte basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiStringLess(const LmiString* x, const LmiString* y);

/* Do we need LmiStringDump? */


/**
	{type:
		{name: LmiStringIterator}
		{parent: LmiString}
		{description: The iterator type of a string.}
		{note: This is a model of LmiRandomAccessIterator.}
	}
*/

/**
{type:
	{name: LmiStringConstIterator}
	{parent: LmiString}
	{description: The read-only iterator type of a string.}
	{note: This is a model of LmiRandomAccessIterator.}
}
*/
/**
{type:
	{name: LmiStringReverseIterator}
	{parent: LmiString}
	{description: The reverse iterator type of a string.}
	{note: This is a model of LmiRandomAccessIterator.}
}
*/

/**
{type:
	{name: LmiStringConstReverseIterator}
	{parent: LmiString}
	{description: The read-only reverse iterator type of a string.}
	{note: This is a model of LmiRandomAccessIterator.}
}
*/

/* An LmiString is a random-access container and a sequence. */
Declare_LmiRandomAccessContainerTypes(LmiString, char, char*, const char*,
	LmiSizeT, LmiDistanceT)
DeclareInline_LmiRandomAccessIterator(LmiStringIterator,
	char, const char, LmiDistanceT, LMI_INLINE_DECLARATION)
DeclareInline_LmiRandomAccessIterator(LmiStringConstIterator,
	const char, const char, LmiDistanceT, LMI_INLINE_DECLARATION)
DeclareInline_LmiRandomAccessIterator(LmiStringReverseIterator,
	char, const char, LmiDistanceT, LMI_INLINE_DECLARATION)
DeclareInline_LmiRandomAccessIterator(LmiStringConstReverseIterator,
	const char, const char, LmiDistanceT, LMI_INLINE_DECLARATION)

/**
   {function:
     {name: LmiStringConstructCStr}
     {parent: LmiString}
     {description: Construct an LmiString based on a NUL-terminated C
       string.}
     {prototype: LmiString* LmiStringConstructCStr(LmiString* x, const char* str, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: str}
       {description: A NUL-terminated C string.  The initial contents of x will be equal to the value of str up to its terminating NUL.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiString* LmiStringConstructCStr(LmiString* x, const char* str, LmiAllocator* a);

/**
   {function:
     {name: LmiStringConstructCStrLen}
     {parent: LmiString}
     {description: Construct an LmiString based on a C string of a given
       length.}
     {prototype: LmiString* LmiStringConstructCStrLen(LmiString* x, const char* str, LmiSizeT len, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: str}
       {description: A pointer to an array of char.  The initial contents of
       x will be equal to the first {italic:len} bytes of str.  The array
       may include NUL bytes.}}
     {parameter:
       {name: len}
       {description: The number of characters to include from {italic:str}.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiString* LmiStringConstructCStrLen(LmiString* x, const char* str,
                                     LmiSizeT len, LmiAllocator* a);

/**
   {function:
     {name: LmiStringConstructSubstring}
     {parent: LmiString}
     {description: Construct an LmiString based on a substring of another
       LmiString.}
     {prototype: LmiString* LmiStringConstructSubstring(LmiString* x,
       const LmiString* str, LmiSizeT pos, LmiSizeT n, LmiAllocator* a)}
     {parameter:
       {name: x}
       {description: A pointer to the string object to construct.}
     }
     {parameter:
       {name: str}
       {description: The source LmiString object.}}
     {parameter:
       {name: pos}
       {description: The initial position of the substring within the source
         string.}}
     {parameter:
       {name: n}
       {description: The length of the substring within the source
         string.  The value LMI_STRING_NPOS indicates the entire string.}}
     {parameter:
       {name: a}
       {description: The allocator the string should use.}}
     {return: A pointer to the string object, or NULL on failure.}
   }
*/
LmiString* LmiStringConstructSubstring(LmiString* x, const LmiString* str,
                                       LmiSizeT pos, LmiSizeT n, LmiAllocator* a);


/**
   {function:
     {name: LmiStringConstructRange}
     {parent: LmiString}
     {description: Construct an LmiString based on a range of another
       LmiString.}
     {prototype: LmiString* LmiStringConstructRange(LmiString* x,
       LmiStringConstIterator first, LmiStringConstIterator last,
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
LmiString* LmiStringConstructRange(LmiString* x, LmiStringConstIterator first,
                                   LmiStringConstIterator last,
                                   LmiAllocator* a);


/**
   {function:
     {name: LmiStringConstructFormatted}
     {parent: LmiString}
     {description: Construct an LmiString based on a printf-style formatted
       string.}
     {prototype: LmiString* LmiStringConstructFormatted(LmiString* x,
       LmiAllocator* a, const char* fmt, ...)}
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
     {note: Notice that unlike other LmiString constructors, this
       constructor\'s LmiAllocator argument is not its final argument, because
       variadic arguments must come at the end.}
   }
*/
LmiString*
LmiStringConstructFormatted(LmiString* x, LmiAllocator* a,
                            const char* fmt, ...)
  LmiFunctionPrintfLike(3, 4);


/**
   {function:
     {name: LmiStringConstructVFormatted}
     {parent: LmiString}
     {description: Construct an LmiString based on a vprintf-style formatted
       string.}
     {prototype: LmiString* LmiStringConstructVFormatted(LmiString* x,
       const char* fmt, va_list args, LmiAllocator* a)}
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
LmiString*
LmiStringConstructVFormatted(LmiString* x, const char* fmt, va_list args,
                             LmiAllocator* a)
  LmiFunctionVPrintfLike(2);


/**
   {function visibility="private":
     {name: LmiStringConstructWithExternalBuffer}
     {parent: LmiString}
     {description: Construct an LmiString taking ownership of an external buffer.}
     {prototype: LmiString* LmiStringConstructWithExternalBuffer(LmiString* x, char* buffer, LmiSizeT length, LmiSizeT capacity, LmiAllocator* a)}
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
       {description: The length of the data that is currently in the buffer, not including a terminating NUL byte (if any).}
     }
     {parameter:
       {name: capacity}
       {description: The total capacity of the passed-in buffer, including space for a terminating NUL byte, or 0.}
     }
     {parameter:
       {name: a}
       {description: An allocator to use for the string.  Its deallocate callback will be used to deallocate the passed-in buffer when the string is reallocated or destructed.}
     }
     {return: A pointer to the string object, or NULL on failure.}
     {note: If the buffer is not currently NUL-terminated, a NUL byte will be 
	   written at buffer[length] unless capacity == 0; otherwise, the buffer
	   will only be written to when mutating LmiString functions are called
	   on the LmiString.}
   }
*/
LmiString* LmiStringConstructWithExternalBuffer(LmiString* x, char* buffer, LmiSizeT length, LmiSizeT capacity, LmiAllocator* a);


/**
	{function:
		{name: LmiStringConstructUcs4}
		{parent: LmiString}
		{description: Construct a string to have the UTF8-encoded values of a UCS4-encoded wide C string.}
		{prototype: LmiString* LmiStringConstructUcs4(LmiString* x, const LmiWideChar* ucs4, LmiAllocator* a)}
		{parameter:
			{name: x}
			{description: A pointer to the string to construct.}}
		{parameter:
			{name: ucs4}
			{description: A NUL-terminated UCS-4 encoded wide C string.}}
		{parameter:
			{name: a}
			{description: The allocator the string should use.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiString* LmiStringConstructUcs4(LmiString* x, const LmiWideChar* ucs4, LmiAllocator* a);

/**
	{function:
		{name: LmiStringConstructUtf16}
		{parent: LmiString}
		{description: Construct a string to have the UTF8-encoded values of a UTF16-encoded C string.}
		{prototype: LmiString* LmiStringConstructUtf16(LmiString* x, const LmiUint16* utf16, LmiAllocator* a)}
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
LmiString* LmiStringConstructUtf16(LmiString* x, const LmiUint16* utf16, LmiAllocator* a);

/**
   {function:
     {name: LmiStringLength}
     {parent: LmiString}
     {description: Get the length of an LmiString.}
     {prototype: LmiSizeT LmiStringLength(const LmiString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose length is to be
       determined.}
     }
     {return: The length of the string, in characters.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiStringLength(const LmiString* x);

/**
   {function:
     {name: LmiStringSize}
     {parent: LmiString}
     {description: Get the size of an LmiString.}
     {prototype: LmiSizeT LmiStringSize(const LmiString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose size is to be
         determined.}
     }
     {return: The size of the string, in characters.}
     {note: This function is identical to LmiStringLength.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiStringSize(const LmiString* x);


/**
   {function:
     {name: LmiStringMaxSize}
     {parent: LmiString}
     {description: Get the maximum supported length of an LmiString.}
     {prototype: LmiSizeT LmiStringMaxSize(const LmiString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose maximum length is
         to be determined.}
     }
     {return: The maximum length of the string, in characters.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiStringMaxSize(const LmiString* x);

/**
   {function:
     {name: LmiStringGetAllocator}
     {parent: LmiString}
     {description: Get the allocator of an LmiString.}
     {prototype: LmiAllocator* LmiStringGetAllocator(const LmiString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose allocator is
         to be determined.}
     }
     {return: The pointer to the allocator of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiAllocator* LmiStringGetAllocator(const LmiString* x);

/**
   {function:
     {name: LmiStringResize}
     {parent: LmiString}
     {description: Alters the length of an LmiString, either by truncating
       it or extending it.}
     {prototype: LmiBool LmiStringResize(LmiString* x, LmiSizeT n, const char* c)}
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
LmiBool LmiStringResize(LmiString* x, LmiSizeT n, const char* c);


/**
   {function:
     {name: LmiStringCapacity}
     {parent: LmiString}
     {description: Get the size of the allocated storage of an LmiString.}
     {prototype: LmiSizeT LmiStringCapacity(const LmiString* x)}
     {parameter:
       {name: x}
       {description: A pointer to the string object whose capacity is
         to be determined.}
     }
     {return: The capacity of the string, in characters.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiStringCapacity(const LmiString* x);


/**
   {function:
     {name: LmiStringReserve}
     {parent: LmiString}
     {description: Reserve storage for a string.}
     {prototype: LmiBool LmiStringReserve(LmiString* x, LmiSizeT res)}
     {parameter:
       {name: x}
       {description: A pointer to the string object for which storage is to
         be reserved.}}
     {parameter:
       {name: res}
       {description: The number of bytes of memory to reserve for the
         string.  After successful return of this function,
         LmiStringCapacity(x) will be >= res.}}
     {return: LMI_FALSE on allocation failure, otherwise LMI_TRUE.}
     {note: If res is less than the string\'s current capacity, this function
       is a non-binding shrink request.  If res is less than the string\'s
       current size, this function is a non-binding shrink-to-fit request.}
   }
*/
LmiBool LmiStringReserve(LmiString* x, LmiSizeT res);

/**
   {function:
     {name: LmiStringData}
     {parent: LmiString}
     {description: Get a read-only buffer corresponding to the contents
        of a string.}
     {prototype: const char* LmiStringData(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose buffer to extract.}}
     {return: A read-only pointer to the string\'s data, as an array of
       LmiStringSize(x) characters.}
     {note: The pointer to the buffer may be invalidated by any non-const
       member function of LmiString, other than LmiStringAt.}
   }
*/
LMI_INLINE_DECLARATION const char* LmiStringData(const LmiString* x);

/**
   {function:
     {name: LmiStringCStr}
     {parent: LmiString}
     {description: Get a NUL-terminated C string corresponding to the contents
        of a string.}
     {prototype: const char* LmiStringCStr(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose C string to obtain.}}
     {return: A read-only array of LmiStringSize(x) characters followed by a
       NUL character.}
     {note: The pointer to the C string may be invalidated by any non-const
       member function of LmiString, other than LmiStringAt.}
   }
*/
LMI_INLINE_DECLARATION const char* LmiStringCStr(const LmiString* x);


/**
   {function:
     {name: LmiStringGetBuffer}
     {parent: LmiString}
     {description: Get a writeable buffer into which data can be written
	   outside the control of the LmiString object.}
     {prototype: char* LmiStringGetBuffer(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose buffer to extract.}}
     {return: A pointer to a buffer.  It is safe to write into
	   LmiStringCapacity(x) - LmiStringLength(x) bytes of this buffer.
       The data in question will be appended to the end of the string.}
     {note: When the caller is done, the function LmiStringReleaseBuffer
		must be called to set the new length of the string.}
     {note: The pointer to the buffer may be invalidated by any non-const
       member function of LmiString, other than LmiStringAt.}
   }
*/
LMI_INLINE_DECLARATION char* LmiStringGetBuffer(LmiString* x);


/**
   {function:
     {name: LmiStringReleaseBuffer}
     {parent: LmiString}
     {description: Release a writeable buffer previously acquired with
	   LmiStringGetBuffer.}
     {prototype: void LmiStringReleaseBuffer(LmiString* x, LmiSizeT buflen)}
     {parameter:
       {name: x}
       {description: The string whose buffer to release.}}
     {parameter:
       {name: buflen}
       {description: The number of bytes written into the buffer.  This
	     must be less than or equal to LmiStringCapacity(x) -
		 LmiStringLength(x). The string\'s length will be adjusted
		 accordingly.}}
   }
*/
void LmiStringReleaseBuffer(LmiString* x, LmiSizeT buflen);


/**
   {function:
     {name: LmiStringAt}
     {parent: LmiString}
     {description: Get a pointer to the character stored at a specific
       position in a string.}
     {prototype: char* LmiStringAt(LmiString* x, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string from which the character should be
         extracted.}}
     {parameter:
       {name: n}
       {description: The position of the character to be extracted.}}
     {return: A pointer to the character to be extracted.  This pointer is
       invalidated if a non-const member function, other than LmiStringAt,
       is invoked on x.  It is not valid to write to this pointer.}
   }
*/
LMI_INLINE_DECLARATION char* LmiStringAt(LmiString* x, LmiSizeT n);


/**
   {function:
     {name: LmiStringAtConst}
     {parent: LmiString}
     {description: Get a constant pointer to the character stored at a
       specific position in a string.}
     {prototype: const char* LmiStringAtConst(const LmiString* x, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string from which the character should be
         extracted.}}
     {parameter:
       {name: n}
       {description: The position of the character to be extracted.}}
     {return: A pointer to the character to be extracted.  This pointer is
       invalidated if a non-const member function, other than LmiStringAt,
       is invoked on x.}
   }
*/
LMI_INLINE_DECLARATION const char* LmiStringAtConst(const LmiString* x, LmiSizeT n);


/**
   {function:
     {name: LmiStringEmpty}
     {parent: LmiString}
     {description: Determine whether a string is empty.}
     {prototype: LmiBool LmiStringEmpty(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose emptiness to determine.}}
     {return: True if the string is empty, else false.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiStringEmpty(const LmiString* x);


/**
   {function:
     {name: LmiStringClear}
     {parent: LmiString}
     {description: Erase the contents of a string.}
     {prototype: void LmiStringClear(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string to clear.}}
     {note: Does not necessarily alter the string's capacity.}
   }
*/
LMI_INLINE_DECLARATION void LmiStringClear(LmiString* x);


/**
   {function:
     {name: LmiStringBegin}
     {parent: LmiString}
     {description: Get an iterator referring to the beginning of a string.}
     {prototype: LmiStringIterator LmiStringBegin(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose begin iterator to obtain.}}
     {return: An iterator referring to the beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringIterator LmiStringBegin(LmiString* x);


/**
   {function:
     {name: LmiStringBeginConst}
     {parent: LmiString}
     {description: Get an iterator referring to the beginning of a
       const string.}
     {prototype: LmiStringConstIterator LmiStringBeginConst(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose const begin iterator to obtain.}}
     {return: A constant iterator referring to the beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringConstIterator LmiStringBeginConst(const LmiString* x);


/**
   {function:
     {name: LmiStringEnd}
     {parent: LmiString}
     {description: Get an iterator referring to the end of a string.}
     {prototype: LmiStringIterator LmiStringEnd(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose end iterator to obtain.}}
     {return: An iterator referring to the end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringIterator LmiStringEnd(LmiString* x);


/**
   {function:
     {name: LmiStringEndConst}
     {parent: LmiString}
     {description: Get an iterator referring to the end of a
       const string.}
     {prototype: LmiStringConstIterator LmiStringEndConst(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose const end iterator to obtain.}}
     {return: A constant iterator referring to the end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringConstIterator LmiStringEndConst(const LmiString* x);


/**
   {function:
     {name: LmiStringRBegin}
     {parent: LmiString}
     {description: Get a reverse iterator referring to the reversed beginning (end) of a string.}
     {prototype: LmiStringReverseIterator LmiStringRBegin(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose reverse begin iterator to obtain.}}
     {return: An iterator referring to the reversed beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringReverseIterator LmiStringRBegin(LmiString* x);


/**
   {function:
     {name: LmiStringRBeginConst}
     {parent: LmiString}
     {description: Get an iterator referring to the reversed beginning (end) of a
       const string.}
     {prototype: LmiStringConstReverseIterator LmiStringRBeginConst(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose const reverse begin iterator to obtain.}}
     {return: A constant iterator referring to the reversed beginning of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringConstReverseIterator LmiStringRBeginConst(const LmiString* x);


/**
   {function:
     {name: LmiStringREnd}
     {parent: LmiString}
     {description: Get an iterator referring to the reversed end (beginning) of a string.}
     {prototype: LmiStringReverseIterator LmiStringREnd(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose reversed end iterator to obtain.}}
     {return: An iterator referring to the reversed end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringIterator LmiStringREnd(LmiString* x);


/**
   {function:
     {name: LmiStringREndConst}
     {parent: LmiString}
     {description: Get an iterator referring to the reversed end (beginning) of a
       const string.}
     {prototype: LmiStringConstReverseIterator LmiStringREndConst(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose const reversed end iterator to obtain.}}
     {return: A constant iterator referring to the reversed end of the string.}
   }
*/
LMI_INLINE_DECLARATION LmiStringConstReverseIterator LmiStringREndConst(const LmiString* x);


/**
   {function:
     {name: LmiStringFront}
     {parent: LmiString}
     {description: Return a pointer to the first character in a string.}
     {prototype: char* LmiStringFront(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose first character to obtain.}}
     {return: A pointer to the first character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION char* LmiStringFront(LmiString* x);


/**
   {function:
     {name: LmiStringFrontConst}
     {parent: LmiString}
     {description: Return a pointer to the first character in a const string.}
     {prototype: const char* LmiStringFrontConst(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose first character to obtain.}}
     {return: A pointer to the first character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION const char* LmiStringFrontConst(const LmiString* x);


/**
   {function:
     {name: LmiStringBack}
     {parent: LmiString}
     {description: Return a pointer to the last character in a string.}
     {prototype: char* LmiStringBack(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose last character to obtain.}}
     {return: A pointer to the last character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION char* LmiStringBack(LmiString* x);


/**
   {function:
     {name: LmiStringBackConst}
     {parent: LmiString}
     {description: Return a pointer to the last character in a const string.}
     {prototype: const char* LmiStringBackConst(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string whose last character to obtain.}}
     {return: A pointer to the last character in the string.}
     {note: If the string is empty this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION const char* LmiStringBackConst(const LmiString* x);


/**
   {function:
     {name: LmiStringAssignChar}
     {parent: LmiString}
     {description: Assign a single character as the new value of an LmiString.}
     {prototype: LmiString* LmiStringAssignChar(LmiString* x, char c)}
     {parameter:
       {name: x}
       {description: The string to assign to.}}
     {parameter:
       {name: c}
       {description: The character to be assigned.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiString* LmiStringAssignChar(LmiString* x, char c);

/**
   {function:
     {name: LmiStringAssignSubstring}
     {parent: LmiString}
     {description: Assign a substring of one LmiString as the new value
       of another.}
     {prototype: LmiString* LmiStringAssignSubstring(LmiString* x, const LmiString* str, LmiSizeT pos, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to assign to.}}
     {parameter:
       {name: str}
       {description: The string of which a substring is to be assigned.}}
     {parameter:
       {name: pos}
       {description: The offset within str of the beginning of the substring.  Must be <= LmiStringLength(str).}}
     {parameter:
       {name: n}
       {description: The length of the substring to be assigned.  If n
         is larger than LmiStringLength(str) - pos, the entire string
         following pos will be inserted.  (In particular, LMI_STRING_NPOS
         indicates the entire rest of the string.)}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiString* LmiStringAssignSubstring(LmiString* x, const LmiString* str,
                                     LmiSizeT pos, LmiSizeT n);

/**
   {function:
     {name: LmiStringAssignCStr}
     {parent: LmiString}
     {description: Assign a NUL-terminated C string as the new value of an LmiString.}
     {prototype: LmiString* LmiStringAssignCStr(LmiString* x, const char* str)}
     {parameter:
       {name: x}
       {description: The string to which to assign {italic: str}.}}
     {parameter:
       {name: str}
       {description: The NUL-terminated C string to assign.}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiString* LmiStringAssignCStr(LmiString* x, const char* s);

/**
   {function:
     {name: LmiStringAssignCStrLen}
     {parent: LmiString}
     {description: Assign a C string of a given length as the new value of
       an LmiString.}
     {prototype: LmiString* LmiStringAssignCStrLen(LmiString* x, const char* str, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to which to assign {italic: str}.}}
     {parameter:
       {name: str}
       {description: The C string to assign.}}
     {parameter:
       {name: n}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure or pos out of range, else {italic:x}.}
   }
*/
LmiString* LmiStringAssignCStrLen(LmiString* x,
                                   const char* str, LmiSizeT n);

/**
   {function:
     {name: LmiStringAssignRange}
     {parent: LmiString}
     {description: Assign a range of characters as the new value of
       an LmiString.}
     {prototype: LmiString* LmiStringAssignRange(LmiString* x, LmiStringConstIterator first, LmiStringConstIterator last)}
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
LmiString* LmiStringAssignRange(LmiString* x, LmiStringConstIterator first,
                                 LmiStringConstIterator last);

/**
	{function:
		{name: LmiStringAssignUcs4}
		{parent: LmiString}
		{description: Assign a string to have the UTF8-encoded values of a UCS4-encoded wide C string.}
		{prototype: LmiString* LmiStringAssignUcs4(LmiString* x, const LmiWideChar* ucs4)}
		{parameter:
			{name: x}
			{description: The string to which to assign the UTF-8 encoding of the wide C string.}}
		{parameter:
			{name: ucs4}
			{description: A NUL-terminated UCS-4 encoded wide C string.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiString* LmiStringAssignUcs4(LmiString* x, const LmiWideChar* ucs4);

/**
	{function:
		{name: LmiStringAssignUtf16}
		{parent: LmiString}
		{description: Assign a string to have the UTF8-encoded values of a UTF16-encoded C string.}
		{prototype: LmiString* LmiStringAssignUtf16(LmiString* x, const LmiUint16* utf16)}
		{parameter:
			{name: x}
			{description: The string to which to assign the UTF-8 encoding of the UTF-16 string.}}
		{parameter:
			{name: utf16}
			{description: A NUL-terminated UTF-16 encoded wide C string.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiString* LmiStringAssignUtf16(LmiString* x, const LmiUint16* utf16);

/**
   {function:
     {name: LmiStringAssignFormatted}
     {parent: LmiString}
     {description: Assign a printf-style formatted string as the new value of
       an LmiString.}
     {prototype: LmiString* LmiStringAssignFormatted(LmiString* x,
       const char* fmt, ...)}
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
LmiString*
LmiStringAssignFormatted(LmiString* x, const char* fmt, ...)
  LmiFunctionPrintfLike(2, 3);


/**
   {function:
     {name: LmiStringAssignVFormatted}
     {parent: LmiString}
     {description: Assign a vprintf-style formatted string as the new value of
       an LmiString.}
     {prototype: LmiString* LmiStringAssignVFormatted(LmiString* x,
       const char* fmt, va_list args)}
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
LmiString*
LmiStringAssignVFormatted(LmiString* x, const char* fmt, va_list args)
  LmiFunctionVPrintfLike(2);


/**
   {function:
     {name: LmiStringAppend}
     {parent: LmiString}
     {description: Append the contents of one LmiString to another.}
     {prototype: LmiString* LmiStringAppend(LmiString* x, const LmiString* str)}
     {parameter:
       {name: x}
       {description: The string to append to.}}
     {parameter:
       {name: str}
       {description: The string to be appended.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiString* LmiStringAppend(LmiString* x, const LmiString* str);

/**
   {function:
     {name: LmiStringAppendChar}
     {parent: LmiString}
     {description: Append a single character to an LmiString.}
     {prototype: LmiString* LmiStringAppendChar(LmiString* x, char c)}
     {parameter:
       {name: x}
       {description: The string to append to.}}
     {parameter:
       {name: c}
       {description: The character to be appended.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiString* LmiStringAppendChar(LmiString* x, char c);

/**
   {function:
     {name: LmiStringAppendSubstring}
     {parent: LmiString}
     {description: Append a substring of one LmiString to another.}
     {prototype: LmiString* LmiStringAppendSubstring(LmiString* x, const LmiString* str, LmiSizeT pos, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to append to.}}
     {parameter:
       {name: str}
       {description: The string of which a substring is to be appended.}}
     {parameter:
       {name: pos}
       {description: The offset within str of the beginning of the substring.  Must be <= LmiStringLength(str).}}
     {parameter:
       {name: n}
       {description: The length of the substring to be appended.  If n
         is larger than LmiStringLength(str) - pos, the entire string
         following pos will be inserted.  (In particular, LMI_STRING_NPOS
         indicates the entire rest of the string.)}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiString* LmiStringAppendSubstring(LmiString* x, const LmiString* str,
                                     LmiSizeT pos, LmiSizeT n);

/**
   {function:
     {name: LmiStringAppendCStr}
     {parent: LmiString}
     {description: Append a NUL-terminated C string to an LmiString.}
     {prototype: LmiString* LmiStringAppendCStr(LmiString* x, const char* str)}
     {parameter:
       {name: x}
       {description: The string to which to append {italic: str}.}}
     {parameter:
       {name: str}
       {description: The NUL-terminated C string to append.}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiString* LmiStringAppendCStr(LmiString* x, const char* s);


/**
   {function:
     {name: LmiStringAppendCStrLen}
     {parent: LmiString}
     {description: Append a C string of a given length to an LmiString.}
     {prototype: LmiString* LmiStringAppendCStrLen(LmiString* x, const char* str, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to which to append {italic: str}.}}
     {parameter:
       {name: str}
       {description: The C string to append.}}
     {parameter:
       {name: n}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure, else {italic:x}.}
   }
*/
LmiString* LmiStringAppendCStrLen(LmiString* x,
                                   const char* str, LmiSizeT n);


/**
   {function:
     {name: LmiStringAppendN}
	 {parent: LmiString}
	 {description: Append multiple copies of a character to an LmiString.}
	 {prototype: LmiString* LmiStringAppendN(LmiString* x, LmiSizeT n, char c)}
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
LmiString* LmiStringAppendN(LmiString* x, LmiSizeT n, char c);


/**
   {function:
     {name: LmiStringAppendRange}
     {parent: LmiString}
     {description: Append a range of characters to a string.}
     {prototype: LmiString* LmiStringAppendRange(LmiString* x, LmiStringConstIterator first, LmiStringConstIterator last)}
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
LmiString* LmiStringAppendRange(LmiString* x, LmiStringConstIterator first,
                                 LmiStringConstIterator last);


/**
	{function:
		{name: LmiStringAppendUcs4}
		{parent: LmiString}
		{description: Append the UTF8-encoded values of a UCS4-encoded wide C string to a string.}
		{prototype: LmiString* LmiStringAppendUcs4(LmiString* x, const LmiWideChar* ucs4)}
		{parameter:
			{name: x}
			{description: The string to which to append the wide C string.}}
		{parameter:
			{name: ucs4}
			{description: A NUL-terminated UCS-4 encoded wide C string.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiString* LmiStringAppendUcs4(LmiString* x, const LmiWideChar* ucs4);

/**
	{function:
		{name: LmiStringAppendUtf16}
		{parent: LmiString}
		{description: Append the UTF8-encoded values of a UTF16-encoded C string to a string.}
		{prototype: LmiString* LmiStringAppendUtf16(LmiString* x, const LmiUint16* utf16)}
		{parameter:
			{name: x}
			{description: The string to which to append the UTF-8 encoding of the UTF-16 string.}}
		{parameter:
			{name: utf16}
			{description: A NUL-terminated UTF-16 encoded wide C string.}}
		{return: A pointer to the string object, or NULL on failure.}
	}
*/
LmiString* LmiStringAppendUtf16(LmiString* x, const LmiUint16* utf16);


/**
   {function:
     {name: LmiStringAppendFormatted}
     {parent: LmiString}
     {description: Append a printf-style formatted string to an LmiString.}
     {prototype: LmiString* LmiStringAppendFormatted(LmiString* x,
       const char* fmt, ...)}
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
LmiString*
LmiStringAppendFormatted(LmiString* x, const char* fmt, ...)
  LmiFunctionPrintfLike(2, 3);


/**
   {function:
     {name: LmiStringAppendVFormatted}
     {parent: LmiString}
     {description: Append a vprintf-style formatted string to an LmiString.}
     {prototype: LmiString* LmiStringAppendVFormatted(LmiString* x,
       const char* fmt, va_list args)}
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
LmiString*
LmiStringAppendVFormatted(LmiString* x, const char* fmt, va_list args)
  LmiFunctionVPrintfLike(2);


/**
   {function:
     {name: LmiStringInsert}
     {parent: LmiString}
     {description: Insert a single character into a string.}
     {prototype: LmiStringIterator LmiStringInsert(LmiString* x,
                                                   LmiStringIterator pos,
                                                   const char* c)}
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
LmiStringIterator LmiStringInsert(LmiString* x, LmiStringIterator pos,
                                  const char* c);

/**
   {function:
     {name: LmiStringInsertRange}
     {parent: LmiString}
     {description: Insert a range of characters into a string.}
     {prototype: LmiBool LmiStringInsertRange(LmiString* x, LmiStringIterator pos, LmiStringConstIterator first, LmiStringConstIterator last)}
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
LmiBool LmiStringInsertRange(LmiString* x, LmiStringIterator pos,
                             LmiStringConstIterator first,
                             LmiStringConstIterator last);

/**
   {function:
     {name: LmiStringInsertString}
     {parent: LmiString}
     {description: Insert the contents of one LmiString into another.}
     {prototype: LmiString* LmiStringInsertString(LmiString* x, LmiSizeT pos, const LmiString* str)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert {italic: str}. Must be
         <= LmiStringLength(x).}}
     {parameter:
       {name: str}
       {description: The string to insert.}}
     {return: NULL on allocation failure or pos out of range,
       else {italic: x}.}
   }
*/
LmiString* LmiStringInsertString(LmiString* x, LmiSizeT pos,
                                  const LmiString* str);

/**
   {function:
     {name: LmiStringInsertChar}
     {parent: LmiString}
     {description: Insert a single character in an LmiString.}
     {prototype: LmiString* LmiStringInsertChar(LmiString* x, LmiSizeT pos, char c)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert {italic: c}. Must be
         <= LmiStringLength(x).}}
     {parameter:
       {name: c}
       {description: The character to insert.}}
     {return: NULL on allocation failure or pos out of range,
       else {italic: x}.}
   }
*/
LmiString* LmiStringInsertChar(LmiString* x, LmiSizeT pos, char c);

/**
   {function:
     {name: LmiStringInsertSubstring}
     {parent: LmiString}
     {description: Insert part of the content of one LmiString into another.}
     {prototype: LmiString* LmiStringInsertSubstring(LmiString* x, LmiSizeT pos1, const LmiString* str, LmiSizeT pos2, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos1}
       {description: The offset at which to insert the substring of
         {italic: str}. Must be <= LmiStringLength(x).}}
     {parameter:
       {name: str}
       {description: The string to insert.}}
     {parameter:
       {name: pos2}
       {description: The offset within {italic: str} to begin the
         substring.  Must be <= LmiStringLength(str).}}
     {parameter:
       {name: n}
       {description: The length of the substring within {italic: str}.
         If this is larger than LmiStringLength(str) - pos2, the entire string
         following pos2 will be inserted.  (In particular, LMI_STRING_NPOS
         indicates the entire rest of the string.)}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiString* LmiStringInsertSubstring(LmiString* x, LmiSizeT pos1,
                                     const LmiString* str, LmiSizeT pos2,
                                     LmiSizeT n);

/**
   {function:
     {name: LmiStringInsertCStr}
     {parent: LmiString}
     {description: Insert a NUL-terminated C string into an LmiString.}
     {prototype: LmiString* LmiStringInsertCStr(LmiString* x, LmiSizeT pos, const char* str)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert the substring of
         {italic: str}. Must be <= LmiStringLength(x).}}
     {parameter:
       {name: str}
       {description: The NUL-terminated C string to insert.}}
     {return: NULL on allocation failure, else {italic: x}.}
   }
*/
LmiString* LmiStringInsertCStr(LmiString* x, LmiSizeT pos, const char* s);


/**
   {function:
     {name: LmiStringInsertCStrLen}
     {parent: LmiString}
     {description: Insert a C string of a given length into an LmiString.}
     {prototype: LmiString* LmiStringInsertCStrLen(LmiString* x, LmiSizeT pos, const char* str, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string into which to insert {italic: str}.}}
     {parameter:
       {name: pos}
       {description: The offset at which to insert the substring of
         {italic: str}. Must be <= LmiStringLength(x).}}
     {parameter:
       {name: str}
       {description: The C string to insert.}}
     {parameter:
       {name: n}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure or pos out of range, else {italic:x}.}
   }
*/
LmiString* LmiStringInsertCStrLen(LmiString* x, LmiSizeT pos,
                                   const char* s, LmiSizeT n);


/* *  not a docblock
   {function:
     {name: LmiStringInsertN}
     {parent: LmiString}
     {description: Insert several copies of a character into a string.}
     {prototype: LmiBool LmiStringInsertN(LmiString* x, LmiStringIterator pos, LmiSizeT n, const char* c)}
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
LmiBool LmiStringInsertN(LmiString* x, LmiStringIterator pos,
                         LmiSizeT n, const char* c);
*/

/**
   {function:
     {name: LmiStringInsertFormatted}
     {parent: LmiString}
     {description: Insert a printf-style formatted string into an LmiString.}
     {prototype: LmiString* LmiStringInsertFormatted(LmiString* x,
       LmiSizeT pos, const char* fmt, ...)}
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
LmiString*
LmiStringInsertFormatted(LmiString* x, LmiSizeT pos, const char* fmt, ...)
  LmiFunctionPrintfLike(3, 4);


/**
   {function:
     {name: LmiStringInsertVFormatted}
     {parent: LmiString}
     {description: Insert a vprintf-style formatted string into an LmiString.}
     {prototype: LmiString* LmiStringInsertVFormatted(LmiString* x,
	   LmiSizeT pos, const char* fmt, va_list args)}
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
LmiString*
LmiStringInsertVFormatted(LmiString* x, LmiSizeT pos, const char* fmt,
                          va_list args)
  LmiFunctionVPrintfLike(3);


/**
   {function:
     {name: LmiStringReplaceString}
     {parent: LmiString}
     {description: Replace part of an LmiString with another LmiString.}
     {prototype: LmiString* LmiStringReplaceString(LmiString* x,
       LmiSizeT pos1, LmiSizeT n1, const LmiString* str)}
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
LmiString*
LmiStringReplaceString(LmiString* x, LmiSizeT pos1, LmiSizeT n1,
                       const LmiString* str);

/**
   {function:
     {name: LmiStringReplaceChar}
     {parent: LmiString}
     {description: Replace part of an LmiString with a single character.}
     {prototype: LmiString* LmiStringReplaceChar(LmiString* x,
       LmiSizeT pos1, LmiSizeT n1, char c)}
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
LmiString*
LmiStringReplaceChar(LmiString* x, LmiSizeT pos1, LmiSizeT n1, char c);

/**
   {function:
     {name: LmiStringReplaceSubstring}
     {parent: LmiString}
     {description: Replace part of an LmiString with part of another
       LmiString.}
     {prototype: LmiString* LmiStringReplaceSubstring(LmiString* x,
       LmiSizeT pos1, LmiSizeT n1, const LmiString* str, LmiSizeT pos2,
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
LmiString*
LmiStringReplaceSubstring(LmiString* x, LmiSizeT pos1, LmiSizeT n1,
                          const LmiString* str, LmiSizeT pos2, LmiSizeT n2);

/**
   {function:
     {name: LmiStringReplaceCStr}
     {parent: LmiString}
     {description: Replace part of an LmiString with a C string.}
     {prototype: LmiString* LmiStringReplaceCStr(LmiString* x,
       LmiSizeT pos1, LmiSizeT n1, const char* str)}
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
       {description: The NUL-terminated C string to insert.}}
     {return: NULL on allocation failure or pos1 out of range, else x.}
   }
*/
LmiString*
LmiStringReplaceCStr(LmiString* x, LmiSizeT pos1, LmiSizeT n1,
                     const char* str);

/**
   {function:
     {name: LmiStringReplaceCStrLen}
     {parent: LmiString}
     {description: Replace part of an LmiString with a C string of a given length.}
     {prototype: LmiString* LmiStringReplaceCStrLen(LmiString* x,
       LmiSizeT pos1, LmiSizeT n1, const char* str, LmiSizeT n2)}
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
       {description: The C string to insert.}}
     {parameter:
       {name: n2}
       {description: The length of {italic: str}.}}
     {return: NULL on allocation failure or pos1 out of range, else x.}
   }
*/
LmiString*
LmiStringReplaceCStrLen(LmiString* x, LmiSizeT pos1, LmiSizeT n1,
                        const char* str, LmiSizeT n2);

/**
   {function:
     {name: LmiStringReplaceRange}
     {parent: LmiString}
     {description: Replace a range of an LmiString with a different range of string iterators.}
     {prototype: LmiString* LmiStringReplaceRange(LmiString* x,
       LmiStringIterator i1, LmiStringIterator i2,
       LmiStringConstIterator j1, LmiStringConstIterator j2)}
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
LmiString*
LmiStringReplaceRange(LmiString* x,
                      LmiStringIterator i1, LmiStringIterator i2,
                      LmiStringConstIterator j1, LmiStringConstIterator j2);

/**
   {function:
     {name: LmiStringReplaceFormatted}
     {parent: LmiString}
     {description: Replace part of an LmiString with a printf-style formatted string.}
     {prototype: LmiString* LmiStringReplaceFormatted(LmiString* x,
       LmiSizeT pos, LmiSizeT n, const char* fmt, ...)}
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
LmiString*
LmiStringReplaceFormatted(LmiString* x, LmiSizeT pos, LmiSizeT n,
                          const char* fmt, ...)
  LmiFunctionPrintfLike(4, 5);


/**
   {function:
     {name: LmiStringReplaceVFormatted}
     {parent: LmiString}
     {description: Replace part of an LmiString with a vprintf-style
       formatted string.}
     {prototype: LmiString* LmiStringReplaceVFormatted(LmiString* x,
       LmiSizeT pos, LmiSizeT n, const char* fmt, va_list args)}
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
LmiString*
LmiStringReplaceVFormatted(LmiString* x, LmiSizeT pos, LmiSizeT n,
                          const char* fmt, va_list args)
  LmiFunctionVPrintfLike(4);


/**
   {function:
     {name: LmiStringErase}
     {parent: LmiString}
     {description: Remove a single character from a string.}
     {prototype: LmiStringIterator LmiStringErase(LmiString* x,
                                                  LmiStringIterator p)}
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
LmiStringIterator LmiStringErase(LmiString* x, LmiStringIterator p);

/**
   {function:
     {name: LmiStringEraseSubstring}
     {parent: LmiString}
     {description: Remove a substring from a string.}
     {prototype: LmiString* LmiStringEraseSubstring(LmiString* x,
                            LmiSizeT pos, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string from which to erase a substring.}}
     {parameter:
       {name: pos}
       {description: The position of the beginning of the range to erase.
         Must be less than or equal to LmiStringLength(x).}}
     {parameter:
       {name: n}
       {description: The number of characters to remove from the string.
         To remove all characters, pass LMI_STRING_NPOS.}}
     {return: The argument passed in, i.e. x.}
   }
*/
LmiString* LmiStringEraseSubstring(LmiString* x, LmiSizeT pos, LmiSizeT n);

/**
   {function:
     {name: LmiStringEraseRange}
     {parent: LmiString}
     {description: Remove a range from a string.}
     {prototype: LmiStringIterator LmiStringEraseRange(LmiString* x,
                            LmiStringIterator b, LmiStringIterator e)}
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
LmiStringIterator LmiStringEraseRange(LmiString* x, LmiStringIterator b,
                                      LmiStringIterator e);


/**
   {function:
     {name: LmiStringCompare}
     {parent: LmiString}
     {description: Compare the values of two LmiStrings for ordering.}
     {prototype: LmiInt LmiStringCompare(const LmiString* x, const LmiString* y)}
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
     {note: Comparison is done on a byte-by-byte basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiInt LmiStringCompare(const LmiString* x, const LmiString* y);


/**
   {function:
     {name: LmiStringCompareCStr}
     {parent: LmiString}
     {description: Compare the value of an LmiString with that of a C string
       for ordering.}
     {prototype: LmiInt LmiStringCompareCStr(const LmiString* x, const char* y)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to the C string to compare.}
     }
     {return: A value <0, 0, or >0, depending on whether x is
       lexicographically less than, equal to, or greater than y, respectively.}
     {note: Comparison is done on a byte-by-byte basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiInt LmiStringCompareCStr(const LmiString* x, const char* y);


/**
   {function:
     {name: LmiStringCompareCStrLen}
     {parent: LmiString}
     {description: Compare the value of an LmiString with that of a C string
       of a given length for ordering.}
     {prototype: LmiInt LmiStringCompareCStrLen(const LmiString* x, const char* y, LmiSizeT ylen)}
     {parameter:
       {name: x}
       {description: A pointer to the LmiString object to compare.}
     }
     {parameter:
       {name: y}
       {description: A pointer to an array of char.  The contents of x will be compared to the first {italic:ylen} bytes of y.  The array may include NUL.}
     }
	 {parameter:
	   {name: ylen}
	   {description: The length of the array pointed to by {italic:y}.}
	 }
     {return: A value <0, 0, or >0, depending on whether x is
       lexicographically less than, equal to, or greater than y, respectively.}
     {note: Comparison is done on a byte-by-byte basis.  No knowledge of
       the strings\' character sets is assumed.  (Among other things, this
       means that the strings are compared case-sensitively.)}
   }
*/
LmiInt LmiStringCompareCStrLen(const LmiString* x, const char* y, LmiSizeT ylen);


/**
   {function:
     {name: LmiStringPushBack}
     {parent: LmiString}
     {description: Push a single character onto the end of a string.}
     {prototype: LmiBool LmiStringPushBack(LmiString* x, const char* c)}
     {parameter:
       {name: x}
       {description: The string onto which to push a character.}}
     {parameter:
       {name: c}
       {description: A pointer to the character to push.}}
     {return: LMI_FALSE on allocation failure, else LMI_TRUE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiStringPushBack(LmiString* x, const char* c);


/**
   {function:
     {name: LmiStringPopBack}
     {parent: LmiString}
     {description: Pop a single character from the end of a string.}
     {prototype: void LmiStringPopBack(LmiString* x)}
     {parameter:
       {name: x}
       {description: The string from which to pop a character.}}
     {note: If the string is empty, this function is undefined.}
   }
*/
LMI_INLINE_DECLARATION void LmiStringPopBack(LmiString* x);

/**
   {function:
     {name: LmiStringFindFirstOf}
     {parent: LmiString}
     {description: Find first location in a string where one of the
	   characters in a second string occurs.}
     {prototype: LmiSizeT LmiStringFindFirstOf(const LmiString* x, LmiSizeT pos, const LmiString* y)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: y}
       {description: The string whose characters are to be searched for.}}
     {return: The first position in x where a character of y occurs or LMI_STRING_NPOS
	 if none of the characters were found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/

LmiSizeT LmiStringFindFirstOf(const LmiString* x, LmiSizeT pos, const LmiString* y);
/**
   {function:
     {name: LmiStringFindFirstOfChar}
     {parent: LmiString}
     {description: Find first location in a string where a given character occurs.}
     {prototype: LmiSizeT LmiStringFindFirstOfChar(const LmiString* x, LmiSizeT pos, char c)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: c}
       {description: The character to be searched for.}}
     {return: The first position in x where a character c occurs or LMI_STRING_NPOS
	 if not found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiStringFindFirstOfChar(const LmiString* x, LmiSizeT pos, char y);

/**
   {function:
     {name: LmiStringFindFirstOfCStr}
     {parent: LmiString}
     {description: Find first location in a string where one of the
	   characters in a C string occurs.}
     {prototype: LmiSizeT LmiStringFindFirstOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: y}
       {description: The C string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The first position in x where a character of y occurs or LMI_STRING_NPOS
	 if none of the characters were found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiStringFindFirstOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n);

/**
   {function:
     {name: LmiStringFindFirstNotOf}
     {parent: LmiString}
     {description: Find first location in a string where one of the
	   characters in a second string does not occur.}
     {prototype: LmiSizeT LmiStringFindFirstNotOf(const LmiString* x, LmiSizeT pos, const LmiString* y)}
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
	 LMI_STRING_NPOS otherwise. }
	 {note: The order of the parameters has been modified from the C++ string class
	 member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }

*/
LmiSizeT LmiStringFindFirstNotOf(const LmiString* x, LmiSizeT pos, const LmiString* y);

/**
   {function:
     {name: LmiStringFindFirstNotOfChar}
     {parent: LmiString}
     {description: Find first location in a string where a given character does not occur.}
     {prototype: LmiSizeT LmiStringFindFirstNotOfChar(const LmiString* x, LmiSizeT pos, char c)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: c}
       {description: The character to be searched for.}}
     {return: The first position in x where character c does not occur or LMI_STRING_NPOS otherwise. }
	 {note: The order of the parameters has been modified from the C++ string class
	 member function that this function was derived from, to make the interface
	 more logical within the constraints of the C Programming language.}
   }

*/
LmiSizeT LmiStringFindFirstNotOfChar(const LmiString* x, LmiSizeT pos, char c);


/**
   {function:
     {name: LmiStringFindFirstNotOfCStr}
     {parent: LmiString}
     {description: Find first location in a string where one of the
	   characters in a C string does not occur.}
     {prototype: LmiSizeT LmiStringFindFirstNotOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start the search from.}}
     {parameter:
       {name: y}
       {description: The C string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The first position in x where a character of y does not occur or
	 LMI_STRING_NPOS otherwise. }
     {note: The order of the parameters has been modified from the C++ string class
	 member function that this function was derived from, to make the interface
	 more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiStringFindFirstNotOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n);

/**
   {function:
     {name: LmiStringFindLastOfCStr}
     {parent: LmiString}
     {description: Find last location in a string where one of the
	   characters in a C string occurs.}
     {prototype: LmiSizeT LmiStringFindLastOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start searching backward from. Set this to
          LMI_STRING_NPOS to search the entire string.}}
     {parameter:
       {name: y}
       {description: The C string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The last position in x where a character of y occurs or LMI_STRING_NPOS
	 if none of the characters were found. }
   }
*/
LmiSizeT LmiStringFindLastOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n);


/**
   {function:
     {name: LmiStringFindLastOfChar}
     {parent: LmiString}
     {description: Find last location in a string where a given character occurs.}
     {prototype: LmiSizeT LmiStringFindLastOfChar(const LmiString* x, LmiSizeT pos, char c)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start searching backward from. Set this to
          LMI_STRING_NPOS to search the entire string.}}
     {parameter:
       {name: c}
       {description: The character to be searched for.}}
     {return: The last position in x where a character c occurs or LMI_STRING_NPOS
	 if not found. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiStringFindLastOfChar(const LmiString* x, LmiSizeT pos, char c);


/**
   {function:
     {name: LmiStringFindLastNotOfCStr}
     {parent: LmiString}
     {description: Find last location in a string where one of the
	   characters in a C string does not occur.}
     {prototype: LmiSizeT LmiStringFindLastNotOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start searching backward from. Set this to
          LMI_STRING_NPOS to search the entire string.}}
     {parameter:
       {name: y}
       {description: The C string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The last position in x where a character of y does not occur or LMI_STRING_NPOS
	  otherwise. }
   }
*/
LmiSizeT LmiStringFindLastNotOfCStr(const LmiString* x, LmiSizeT pos, const char* y, LmiSizeT n);

/**
   {function:
     {name: LmiStringFindLastNotOfChar}
     {parent: LmiString}
     {description: Find last location in a string where a given character does not occur.}
     {prototype: LmiSizeT LmiStringFindLastNotOfChar(const LmiString* x, LmiSizeT pos, char c)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: pos}
       {description: The position in x to start searching backward from. Set this to
          LMI_STRING_NPOS to search the entire string.}}
     {parameter:
       {name: c}
       {description: The character to be searched for.}}
     {return: The last position in x where a character c does not occur or LMI_STRING_NPOS
	 otherwise. }
     {note: The order of the parameters has been modified from the C++ string class
     member function that this function was derived from, to make the interface
     more logical within the constraints of the C Programming language.}
   }
*/
LmiSizeT LmiStringFindLastNotOfChar(const LmiString* x, LmiSizeT pos, char c);

/**
   {function:
     {name: LmiStringFindCStrLen}
     {parent: LmiString}
     {description: Find a substring.}
     {prototype: LmiSizeT LmiStringFindCStrLen(const LmiString* x, const char* y, LmiSizeT n)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: y}
       {description: The C string whose characters are to be searched for.}}
     {parameter:
       {name: n}
       {description: The number of characters from y to use in the search.}}
     {return: The first position in x where y occurs or LMI_STRING_NPOS otherwise. }
   }
*/
LmiSizeT LmiStringFindCStrLen(const LmiString* x, const char* y, LmiSizeT n);

/**
   {function:
     {name: LmiStringFindCStr}
     {parent: LmiString}
     {description: Find a substring.}
     {prototype: LmiSizeT LmiStringFindCStr(const LmiString* x, const char* y)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: y}
       {description: The C string whose characters are to be searched for.}}
     {return: The first position in x where y occurs or LMI_STRING_NPOS otherwise. }
   }
*/
LmiSizeT LmiStringFindCStr(const LmiString* x, const char* y);

/**
   {function:
     {name: LmiStringFind}
     {parent: LmiString}
     {description: Find a substring.}
     {prototype: LmiSizeT LmiStringFind(const LmiString* x, const LmiString* y)}
     {parameter:
       {name: x}
       {description: The string to be searched.}}
     {parameter:
       {name: y}
       {description: The string whose characters are to be searched for.}}
     {return: The first position in x where y occurs or LMI_STRING_NPOS otherwise. }
   }
*/
LmiSizeT LmiStringFind(const LmiString* x, const LmiString* y);

/**
   {function:
     {name: LmiStringHash}
     {parent: LmiString}
     {description: Hashes a string into an integer.}
     {prototype: LmiSizeT LmiStringHash(const LmiString* x)}
     {parameter:
       {name: x}
       {description: The string to be hashed.}}
     {return: Unsigned integer value of the hashed string. }
   }
*/
LmiSizeT LmiStringHash(const LmiString* x);

/**
   {function:
     {name: LmiStringWriteUtf16}
	 {parent: LmiString}
	 {description: Encode the contents of a string as UTF-16 into a buffer.}
	 {prototype: LmiBool LmiStringWriteUtf16(const LmiString* x, LmiUint16* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
	 {parameter:
		{name: x}
		{description: The string whose contents to encode.  This string must contain valid UTF-8.}}
	 {parameter:
		{name: output}
		{description: A pointer to the buffer to which to write the decoded UTF-16 characters.  May be NULL if outputSize is 0.}}
	 {parameter:
		{name: outputSize}
		{description: The size of the buffer to which the decoded UTF-16 characters should be written.}}
	  {parameter:
		{name: outputLen}
		{description: If not NULL, then on successful return, this will contain the number of UTF-16 codepoints needed to write the contents of the string.  If this is more than outputSize-1, the output was truncated.}}
	  {return: LMI_TRUE if the string's contents were successfully written; LMI_FALSE if not.}
	  {note: If outputSize is greater than 0, the content of the output buffer is always NUL-terminated.}
	}
*/
LmiBool LmiStringWriteUtf16(const LmiString* x, LmiUint16* output, LmiSizeT outputSize, LmiSizeT* outputLen);


/*
  ADD IF NEEDED:

   ConstructN
   AssignN
   InsertN
   ReplaceN

   Copy
   SubStr

   RFind
*/

#if TARGET_OS_MAC

#include <CoreFoundation/CFBase.h>

/* Internal function for macOS / iOS.  Assign the UTF-8 encoding of a CFString to an LmiString. */
LmiString* LmiStringAssignFromCFString(LmiString* x, CFStringRef cfStr);

#endif

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiStringInline.h>
#endif

#endif /* LMI_STRING_H_ */
