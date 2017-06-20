/** {file:
      {name: LmiStdCLib.h}
      {description: Utilities based on ANSI/ISO Standard C Libraries.}
      {copyright:
      	(c) 2005-2014 Vidyo, Inc.,
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

#ifndef LMI_STDCLIB_H_
#define LMI_STDCLIB_H_

#include <Lmi/Utils/LmiTypes.h>

#if LMI_HAVE_STDARG_H
#include <stdarg.h>
#endif

LMI_BEGIN_EXTERN_C

/** {package visibility="private":
      {name: StdCLib}
      {parent: Utils}
      {include: Lmi/Utils/LmiStdCLib.h}
      {description: A package of utilities based on the ANSI/ISO Standard C
        Libraries and their common extensions.}
      {note: On functions where they are available and function correctly,
        these functions are wrappers around the corresponding ANSI/ISO C or
        libc functions.}
    }
*/

/** {function visibility="private":
      {name: LmiStrNCmp}
      {parent: StdCLib}
      {description: Compare the prefixes of two strings lexicographically.}
      {prototype: LmiInt LmiStrNCmp(const char* a, const char* b, LmiSizeT len)}
      {parameter:
        {name: a}
        {description: The first string to compare.}}
      {parameter:
        {name: b}
        {description: The second string to compare.}}
      {parameter:
        {name: len}
        {description: The maximum length of the strings to compare.}}
      {return: A number less than zero, zero, or greater than zero, if the
        first len characters of of a are lexicographically before, equal to,
        or after the first len characters of b, respectively.}
      {note: Characters that appear after a '\\0' character are not
        compared, even if they are prior to length len.}
      {note: The values are compared as unsigned characters; thus, a string
        beginning with the character '\\200' is greater than a string
        beginning with 'a'.}
      {note: Like ISO C strncmp().}
    }
*/
LMI_INLINE_DECLARATION LmiInt LmiStrNCmp(const char* a, const char* b, LmiSizeT len);


/** {function visibility="private":
      {name: LmiStrCmp}
      {parent: StdCLib}
      {description: Compare two strings lexicographically.}
      {prototype: LmiInt LmiStrCmp(const char* a, const char* b)}
      {parameter:
        {name: a}
        {description: The first string to compare.}}
      {parameter:
        {name: b}
        {description: The second string to compare.}}
      {return: A number less than zero, zero, or greater than zero, if a
        is lexicographically before, equal to, or after b, respectively.}
      {note: The values are compared as unsigned characters; thus, a string
        beginning with the character '\\200' is greater than a string
        beginning with 'a'.}
      {note: Like ISO C strcmp().}
    }
*/
LMI_INLINE_DECLARATION LmiInt LmiStrCmp(const char* a, const char* b);


/** {function visibility="private":
      {name: LmiStrCaseCmp}
      {parent: StdCLib}
      {description: Compare two strings case-insensitively.}
      {prototype: LmiInt LmiStrCaseCmp(const char* a, const char* b)}
      {parameter:
        {name: a}
        {description: The first string to compare.}}
      {parameter:
        {name: b}
        {description: The second string to compare.}}
      {return: A number less than zero, zero, or greater than zero, if a
        is lexicographically before, equal to, or after b, respectively, when
        compared case-insensitively.}
      {note: Case-insensitivity is system-dependent for characters outside
        the ASCII range.}
      {note: Like BSD strcasecmp().}
    }
*/
LMI_INLINE_DECLARATION LmiInt LmiStrCaseCmp(const char* a, const char* b);

/**
{function visibility="private":
	{name: LmiStrNCaseCmp}
	{parent: StdCLib}
	{description: Safely compare two strings case-insensitively.}
	{prototype: LmiInt LmiStrNCaseCmp(const char* a, const char* b, LmiSizeT length)}
	{parameter: 
		{name: a}
		{description: The first string to compare.}
	}
	{parameter: 
		{name: b}
		{description: The second string to compare.}
	}
	{parameter: 
		{name: length}
		{description: The maximum length of the strings to compare.}
	}
	{return: A number less than zero, zero, or greater than zero, if a
		is lexicographically before, equal to, or after b, respectively, when
		compared case-insensitively.}
	{note: Case-insensitivity is system-dependent for characters outside
		the ASCII range.}
	{note: Like BSD strncasecmp().}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiStrNCaseCmp(const char* a, const char* b, LmiSizeT length);


/** {function visibility="private":
      {name: LmiStrLCpy}
      {parent: StdCLib}
      {description: Safely copy a string to a buffer of known size.}
      {prototype: LmiSizeT LmiStrLCpy(char* dst, const char* src, LmiSizeT size)}
      {parameter:
        {name: dst}
        {description: The destination to which to copy the string.}}
      {parameter:
        {name: src}
        {description: The source string to copy from.  This must be a true
          (NUL-terminated) C string.}}
      {parameter:
        {name: size}
        {description: The size of the destination buffer.  At most size-1
          characters will be copied from src to dst.  The result will always
          be NUL-terminated unless size == 0.}}
      {return: The length of the string that the function tried to create,
        i.e. the length of src.  If this is greater than or equal to size,
        the destination string was truncated compared to the source string.}
    }
*/
LmiSizeT LmiStrLCpy(char* dst, const char* src, LmiSizeT size);


/** {function visibility="private":
      {name: LmiStrLCat}
      {parent: StdCLib}
      {description: Safely append a string to a buffer of known size.}
      {prototype: LmiSizeT LmiStrLCat(char* dst, const char* src, LmiSizeT size)}
      {parameter:
        {name: dst}
        {description: The destination to which to append the string.
          Its existing contents must be a true (NUL-terminated) C string.}}
      {parameter:
        {name: src}
        {description: The source string to append.  This must be a true
          (NUL-terminated) C string.}}
      {parameter:
        {name: size}
        {description: The total size of the destination buffer.  At most
          size - strlen(dst) - 1 characters will be copied from src to dst.
          The result will always be NUL-terminated unless size == 0.}}
      {return: The length of the string that the function tried to create,
        i.e. the initial length of dst plus length of src.  If this is greater
        than or equal to size, the appended string was truncated compared to the source
        string.}
    }
*/
LmiSizeT LmiStrLCat(char* dst, const char* src, LmiSizeT size);


/** {function visibility="private":
      {name: LmiStrLen}
      {parent: StdCLib}
      {description: Determine the length of a string.}
      {prototype: LmiSizeT LmiStrLen(const char* s)}
      {parameter:
        {name: s}
        {description: The NUL-terminated string whose length to determine.}}
      {return: The length of the string, not counting the terminating NUL.}
      {note: Like ISO C strlen().}
     }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiStrLen(const char* s);

/** {function visibility="private":
      {name: LmiStrChr}
      {parent: StdCLib}
      {description: Find a character in a C string.}
      {prototype: const char* LmiStrChr(const char* s, char c)}
      {parameter:
        {name: s}
        {description: The NUL-terminated string to be searched.}}
      {parameter:
        {name: c}
        {description: The character to search for.}}
      {return: A pointer to a location in {italic: s} where {italic: c} is found or NULL if not found.}
      {note: Like ISO C strchr(), but returning a const char*.}
     }
*/
LMI_INLINE_DECLARATION const char* LmiStrChr(const char* s, char c);


/** {function visibility="private":
      {name: LmiStrRChr}
      {parent: StdCLib}
      {description: Find the last occurrence of a character in a C string.}
      {prototype: const char* LmiStrRChr(const char* s, char c)}
      {parameter:
        {name: s}
        {description: The NUL-terminated string to be searched.}}
      {parameter:
        {name: c}
        {description: The character to search for.}}
      {return: A pointer to the last location in {italic: s} where {italic: c} is found or NULL if not found.}
      {note: Like ISO C strrchr(), but returning a const char*.}
     }
*/
LMI_INLINE_DECLARATION const char* LmiStrRChr(const char* s, char c);


/** {function visibility="private":
      {name: LmiStrStr}
      {parent: StdCLib}
      {description: Find the first occurrence of one C string inside another.}
      {prototype: const char* LmiStrStr(const char* s1, const char* s2)}
      {parameter:
        {name: s1}
        {description: The NUL-terminated string to be searched.}}
      {parameter:
        {name: s2}
        {description: The NUL-terminated string to search for.}}
      {return: A pointer to a location in {italic: s1} where {italic: s2} is found or NULL if not found.}
      {note: Like ISO C strstr(), but returning a const char*.}
     }
*/
LMI_INLINE_DECLARATION const char* LmiStrStr(const char* s1, const char* s2);

/** {function visibility="private":
      {name: LmiStrToInt32}
      {parent: StdCLib}
      {description: Convert a string representing a number into a LmiInt32 value.}
      {prototype: LmiInt32 LmiStrToInt32(const char* start, char** end, LmiInt base)}
      {parameter:
        {name: start}
        {description: The NUL-terminated string to be converted.}}
      {parameter:
        {name: end}
        {description: If not specified as NULL, returns a pointer to the character one past the converted number in the string.}}
      {parameter:
        {name: base}
        {description:
		  {p: The radix (number base) of the integer translated.  This
			may be in the range 2 to 36.  For bases greater than 10, the
			letters 'a' to 'z' (or equivalently 'A' to 'Z') indicate the
			values 10 through 35.  Only letters with values less than
			base are permitted.  If base is 16, a leading '0x' is
			permitted.}
		  {p: Alternatively, base may have the value 0.  In this case,
			strings beginning with '0x' are interpreted as being in base
			16; strings beginning with '0' are interpreted as being in
			base 8; otherwise, they are interpreted as being base 10.}}}
      {return: The LmiInt32 value of the string.}
      {note: Like ISO C strtol().}
     }
*/
LMI_INLINE_DECLARATION LmiInt32 LmiStrToInt32(const char* start, char** end, LmiInt base);


/** {function visibility="private":
      {name: LmiStrToUint32}
      {parent: StdCLib}
      {description: Convert a string representing a number into a LmiUint32 value.}
      {prototype: LmiUint32 LmiStrToUint32(const char* start, char** end, LmiInt base)}
      {parameter:
        {name: start}
        {description: The NUL-terminated string to be converted.}}
      {parameter:
        {name: end}
        {description: If not specified as NULL, returns a pointer to the character one past the converted number in the string.}}
      {parameter:
        {name: base}
        {description:
		  {p: The radix (number base) of the integer translated.  This
			may be in the range 2 to 36.  For bases greater than 10, the
			letters 'a' to 'z' (or equivalently 'A' to 'Z') indicate the
			values 10 through 35.  Only letters with values less than
			base are permitted.  If base is 16, a leading '0x' is
			permitted.}
		  {p: Alternatively, base may have the value 0.  In this case,
			strings beginning with '0x' are interpreted as being in base
			16; strings beginning with '0' are interpreted as being in
			base 8; otherwise, they are interpreted as being base 10.}}}
      {return: The LmiUint32 value of the string.}
      {note: Like ISO C strtoul().}
     }
*/
LMI_INLINE_DECLARATION LmiUint32 LmiStrToUint32(const char* start, char** end, LmiInt base);

/** {function visibility="private":
      {name: LmiStrToInt64}
      {parent: StdCLib}
      {description: Convert a string representing a number into a LmiInt64 value.}
      {prototype: LmiInt64 LmiStrToInt64(const char* start, char** end, LmiInt base)}
      {parameter:
        {name: start}
        {description: The NUL-terminated string to be converted.}}
      {parameter:
        {name: end}
        {description: If not specified as NULL, returns a pointer to the character one past the converted number in the string.}}
      {parameter:
        {name: base}
        {description:
		  {p: The radix (number base) of the integer translated.  This
			may be in the range 2 to 36.  For bases greater than 10, the
			letters 'a' to 'z' (or equivalently 'A' to 'Z') indicate the
			values 10 through 35.  Only letters with values less than
			base are permitted.  If base is 16, a leading '0x' is
			permitted.}
		  {p: Alternatively, base may have the value 0.  In this case,
			strings beginning with '0x' are interpreted as being in base
			16; strings beginning with '0' are interpreted as being in
			base 8; otherwise, they are interpreted as being base 10.}}}
      {return: The LmiInt64 value of the string.}
      {note: Like ISO C99 strtoll().}
     }
*/
LMI_INLINE_DECLARATION LmiInt64 LmiStrToInt64(const char* start, char** end, LmiInt base);


/** {function visibility="private":
      {name: LmiStrToUint64}
      {parent: StdCLib}
      {description: Convert a string representing a number into a LmiUint64 value.}
      {prototype: LmiUint64 LmiStrToUint64(const char* start, char** end, LmiInt base)}
      {parameter:
        {name: start}
        {description: The NUL-terminated string to be converted.}}
      {parameter:
        {name: end}
        {description: If not specified as NULL, returns a pointer to the character one past the converted number in the string.}}
      {parameter:
        {name: base}
        {description:
		  {p: The radix (number base) of the integer translated.  This
			may be in the range 2 to 36.  For bases greater than 10, the
			letters 'a' to 'z' (or equivalently 'A' to 'Z') indicate the
			values 10 through 35.  Only letters with values less than
			base are permitted.  If base is 16, a leading '0x' is
			permitted.}
		  {p: Alternatively, base may have the value 0.  In this case,
			strings beginning with '0x' are interpreted as being in base
			16; strings beginning with '0' are interpreted as being in
			base 8; otherwise, they are interpreted as being base 10.}}}
      {return: The LmiUint64 value of the string.}
      {note: Like ISO C99 strtoull().}
     }
*/
LMI_INLINE_DECLARATION LmiUint64 LmiStrToUint64(const char* start, char** end, LmiInt base);


/** {function visibility="private":
      {name: LmiStrToFloat32}
      {parent: StdCLib}
      {description: Convert a string representing a number into a LmiFloat32 value.}
      {prototype: LmiFloat32 LmiStrToFloat32(const char* start, char** end, LmiBool *overflow)}
      {parameter:
        {name: start}
        {description: The NUL-terminated string to be converted.}}
      {parameter:
        {name: end}
        {description: If not specified as NULL, returns a pointer to the character one past the converted number in the string.}}
	  {parameter:
        {name: overflow}
        {description: If not specified as NULL and the correct value is out of the range of representable values for the type,
			will be set to LMI_TRUE, LMI_FALSE otherwise. The returned value in case of overflow will be LMI_FLOAT32_MAX for 
			positive and LMI_FLOAT32_MIN for negative overflow.}}
      {return: The LmiFloat32 value of the string.}
      {note: Like ISO C99 strtof().}
     }
*/
LmiFloat32 LmiStrToFloat32(const char* start, char** end, LmiBool *overflow);

/** {function visibility="private":
      {name: LmiStrToFloat64}
      {parent: StdCLib}
      {description: Convert a string representing a number into a LmiFloat64 value.}
      {prototype: LmiFloat64 LmiStrToFloat64(const char* start, char** end, LmiBool *overflow)}
      {parameter:
        {name: start}
        {description: The NUL-terminated string to be converted.}}
      {parameter:
        {name: end}
        {description: If not specified as NULL, returns a pointer to the character one past the converted number in the string.}}
	  {parameter:
        {name: overflow}
        {description: If not specified as NULL and the correct value is out of the range of representable values for the type,
			will be set to LMI_TRUE, LMI_FALSE otherwise. The returned value in case of overflow will be LMI_FLOAT64_MAX for
			positive and LMI_FLOAT64_MIN for negative overflow.}}
      {return: The LmiFloat64 value of the string.}
      {note: Like ISO C99 strtod().}
     }
*/
LmiFloat64 LmiStrToFloat64(const char* start, char** end, LmiBool *overflow);

/**
{function visibility="private":
	{name: LmiStrConstructWStr}
	{parent: StdCLib}
	{description: 
		Construct a C string from a wide string. Characters in the range above 
		7-bit ASCII are silently removed in the converted C string. 
	}
	{prototype: const char* LmiStrConstructWStr(char* x, LmiUint16* wStr, LmiSizeT size)}
	{parameter: 
		{name: x}
		{description: A C string to store the converted string. }
	}
	{parameter: 
		{name: wStr}
		{description: A wide string to convert.}
	}
	{parameter: 
		{name: size}
		{description: The size of x.}
	}
	{return: A pointer to the converted C string or NULL on error. }
}
*/
const char* LmiStrConstructWStr(char* x, LmiUint16* wStr, LmiSizeT size);

/** 
{function visibility="private":
	{name: LmiStrToUpper}
	{parent: StdCLib}
	{description: Convert the C string to upper case.}
	{prototype: char* LmiStrToUpper(char *x)}
	{parameter:
	{name: x}
		{description: The NUL-terminated string which has to be converted to upper case.}}
	{return: A pointer to the converted C string.}
}
*/
char* LmiStrToUpper(char *x);

/** 
{function visibility="private":
	{name: LmiStrToLower}
	{parent: StdCLib}
	{description: Convert the C string to lower case.}
	{prototype: char* LmiStrToLower(char *x)}
	{parameter:
	{name: x}
		{description: The NUL-terminated string which has to be converted to lower case.}}
	{return: A pointer to the converted C string.}
}
*/
char* LmiStrToLower(char *x);


/** {function visibility="private":
      {name: LmiMemCpy}
      {parent: StdCLib}
      {description: Copy bytes from one memory range to another.  If the
	    source and destination memory ranges overlap, the result is undefined. }
      {prototype: void* LmiMemCpy(void* s1, const void* s2, LmiSizeT n)}
      {parameter:
		{name: s1}
		{description: A pointer to the starting location of a memory range to copy to.}}
	  {parameter:
		{name: s2}
		{description: A pointer to the starting location of a memory range to copy from.}}
	  {parameter:
		{name: n}
		{description: The number of bytes to copy.}}
	  {return: A pointer to the starting location of the memory range copied to. }
      {note: Like ISO C memcpy().}
    }
*/
LMI_INLINE_DECLARATION void* LmiMemCpy(void* s1, const void* s2, LmiSizeT n);


/** {function visibility="private":
      {name: LmiMemMove}
      {parent: StdCLib}
      {description: Copy bytes from one memory range to another, possibly
        overlapping, memory range.}
      {prototype: void* LmiMemMove(void* s1, const void* s2, LmiSizeT n)}
      {parameter:
		{name: s1}
		{description: A pointer to the starting location of a memory range to copy to.}}
	  {parameter:
		{name: s2}
		{description: A pointer to the starting location of a memory range to copy from.}}
	  {parameter:
		{name: n}
		{description: The number of bytes to copy.}}
	  {return: A pointer to the starting location of the memory range copied to. }
      {note: Like ISO C memmove().}
    }
*/
LMI_INLINE_DECLARATION void* LmiMemMove(void* s1, const void* s2, LmiSizeT n);


/** {function visibility="private":
      {name: LmiMemCmp}
      {parent: StdCLib}
      {description: Compare the first n bytes of two memory ranges.}
      {prototype: LmiInt LmiMemCmp(const void* s1, const void* s2, LmiSizeT n)}
      {parameter:
		{name: s1}
		{description: A pointer to the starting location of the first memory range to compare.}}
	  {parameter:
		{name: s2}
		{description: A pointer to the starting location of the second memory range to compare.}}
	  {parameter:
		{name: n}
		{description: The number of bytes to compare.}}
      {return: A value less than zero if the first memory range is less than the second,
	    a value greater than zero if the first memory range is greater than the second, or
		a value of zero if the memory ranges are equal. }
      {note: Like ISO C memcmp().}
    }
*/
LMI_INLINE_DECLARATION LmiInt LmiMemCmp(const void* s1, const void* s2, LmiSizeT n);


/** {function visibility="private":
      {name: LmiMemSet}
      {parent: StdCLib}
      {description: Set the first n bytes of a memory range to a given value.}
      {prototype: void* LmiMemSet(void* s, LmiInt c, LmiSizeT n)}
      {parameter:
		{name: s}
		{description: A pointer to the starting location of the memory range to be set.}}
	  {parameter:
		{name: c}
		{description: A byte value to copy into each byte in the memory range.}}
	  {parameter:
		{name: n}
		{description: The number of bytes in the memory range to set.}}
      {return: A pointer to the starting location of the memory range.}
      {note: Like ISO C memset().}
    }
*/
LMI_INLINE_DECLARATION void* LmiMemSet(void* s, LmiInt c, LmiSizeT n);


/** {function visibility="private":
	  {name: LmiMemChr}
	  {parent: StdCLib}
	  {description: Find a byte value in a memory range.}
	  {prototype: const void* LmiMemChr(const void* s, LmiInt c, LmiSizeT n)}
      {parameter:
		{name: s}
		{description: A pointer to the starting location of the memory range to search.}}
	  {parameter:
		{name: c}
		{description: A byte value to search for in the memory range.}}
	  {parameter:
		{name: n}
		{description: The number of bytes in the memory range to search.}}
      {return: A pointer to the first memory location in the memory range where the byte
	    value is found.}
	  {note: Like ISO C memchr(), but returning a const void*.}
	}
*/
LMI_INLINE_DECLARATION const void* LmiMemChr(const void* s, LmiInt c, LmiSizeT n);


/** {function visibility="private":
	  {name: LmiMemMem}
	  {parent: StdCLib}
	  {description: Find the first occurrence of one memory range inside
	  	another.}
	  {prototype: const void* LmiMemMem(const void* s1, LmiSizeT len1, const void* s2, LmiSizeT len2)}
      {parameter:
		{name: s1}
		{description: A pointer to the starting location of the memory range
			to search.}}
      {parameter:
		{name: len1}
		{description: The number of bytes to search.}}
	  {parameter:
		{name: s2}
		{description: A pointer to the data for which to search.}}
	  {parameter:
		{name: len2}
		{description: The number of bytes for which to search.}}
      {return: A pointer to the first memory location in s1
	  	matching the len2 bytes after s2, or NULL.}
	  {note: Like GNU libc\'s memmem(), but returning a const void*.}
	}
*/
#if LMI_HAVE_MEMMEM
LMI_INLINE_DECLARATION
#endif
const void* LmiMemMem(const void* s1, LmiSizeT len1, const void* s2, LmiSizeT len2);

LMI_INLINE_DECLARATION LmiBool LmiIsAlnum(LmiInt c);

/** {function visibility="private":
      {name: LmiSNPrintf}
      {parent: StdCLib}
      {description: Safely print a formatted string to a buffer.}
      {prototype: LmiSizeT LmiSNPrintf(char* str, LmiSizeT size, const char* format, ...)}
      {parameter:
        {name: str}
        {description: The buffer to which to print the string.  If size == 0,
          this may be NULL.}}
      {parameter:
        {name: size}
        {description: The size of the buffer pointed to by str.  No more than
          size bytes will be written to str, including the terminating NUL
          byte.}}
      {parameter:
        {name: format}
        {description: A printf-style format string.}}
	  {parameter:
	    {name: ...}
	    {description:  The arguments to the format string.}}
      {return: The number of characters that would be printed if size were
        unlimited (not counting the final NUL).  If this is greater than
        or equal to size, the formatted string was truncated.}
      {note: This function will never fail.  If the underlying system\'s
        formatting string printing routine fails, which should never happen,
        LmiSNPrintf will call LmiAssert.}
    }
*/
LmiSizeT LmiSNPrintf(char* str, LmiSizeT size, const char* format, ...)
  LmiFunctionPrintfLike(3, 4);


/** {function visibility="private":
      {name: LmiVSNPrintf}
      {parent: StdCLib}
      {description: Safely print a formatted string to a buffer, passing a
        va_list for the format arguments.}
      {prototype: LmiSizeT LmiVSNPrintf(char* str, LmiSizeT size,
        const char* format, va_list args)}
      {parameter:
        {name: str}
        {description: The buffer to which to print the string.  If size == 0,
          this may be NULL.}}
      {parameter:
        {name: size}
        {description: The size of the buffer pointed to by str.  No more than
          size bytes will be written to str, including the terminating NUL
          byte.}}
      {parameter:
        {name: format}
        {description: A printf-style format string.}}
      {parameter:
        {name: args}
        {description: A stdarg.h collection of arguments.}}
      {return: The number of characters that would be printed if size were
        unlimited (not counting the final NUL).  If this is greater than
        or equal to size, the formatted string was truncated.}
      {note: This function will never fail.  If the underlying system\'s
        formatting string printing routine fails, which should never happen,
        LmiSNPrintf will call LmiAssert.}
    }
*/
LmiSizeT LmiVSNPrintf(char* str, LmiSizeT size, const char* format,
                      va_list args)
  LmiFunctionVPrintfLike(3);


/** {function visibility="private":
      {name: LmiVaCopy}
      {parent: StdCLib}
      {description: Copy a list of variadic arguments.  The destination is
	  	initialized as a copy of the source, as if the va_start macro had
		been applied to the destination followed by the same sequence of
		uses of the va_arg macro as had previously been used to reach the
		present state of the source.}
      {prototype: void LmiVaCopy(va_list dest, va_list src)}
      {parameter:
        {name: dest}
        {description: The destination list of variadic arguments.}}
      {parameter:
        {name: src}
        {description: The source list of variadic arguments.}}
	  {note: After it is done, va_end must be called on the copied list,
	  	just as for the original list.}
	  {note: Like ISO C99 va_copy().}
    }
*/
#if LMI_HAVE_VA_COPY
#define LmiVaCopy(dest, src) va_copy(dest, src)

#elif LMI_HAVE___VA_COPY
#define LmiVaCopy(dest, src) __va_copy(dest, src)

#elif LMI_HAVE___BUILTIN_VA_COPY
#define LmiVaCopy(dest, src) __builtin_va_copy(dest, src)

#elif LMI_HAVE_ASSIGNABLE_VA_LIST
/* If we don't have any variant on va_copy, but va_list is assignable,
 * assume that simple assignment of a va_list does the right thing. */
/* The only platform we currently support that does not have va_copy is
 * Microsoft Visual C++, where this is true for x86, and appears to be true
 * on all platforms. */
#define LmiVaCopy(dest, src) (dest) = (src)
#else
#error "No definition available for LmiVaCopy"
#endif

/** 
{function visibility="private":
	{name: LmiGetEnv}
	{parent: StdCLib}
	{description: Get the value of an environment variable.}
	{prototype: const char* LmiGetEnv(const char* name)}
	{parameter:
		{name: name}
		{description: The name of the environment variable to retrieve, as a C NUL-terminated string.}}
	{return: The value of the environment variable, as a C NUL-terminated string,
		or NULL if no such environment variable was found.}
	{note: Like ISO C getenv(), but returning a const char*.}
	{note: On platforms that do not support environment variables, this will
		always return NULL.}
}
*/
#if LMI_HAVE_GETENV
LMI_INLINE_DECLARATION
#endif
const char* LmiGetEnv(const char* name);


/** 
{function visibility="private":
	{name: LmiSetEnv}
	{parent: StdCLib}
	{description: Set the value of an environment variable.}
	{prototype: LmiBool LmiSetEnv(const char* name, const char* value, LmiBool overwrite)}
	{parameter:
		{name: name}
		{description: The name of the environment variable to set, as a C NUL-terminated string.}}
	{parameter:
		{name: value}
		{description: The value to set for environment variable, as a C NUL-terminated string.}}
	{parameter:
		{name: overwrite}
		{description: If the environment variable is already set, whether it should be replaced with the existing value.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.  Note that if overwrite is false, the return value will be true even if an existing environment variable is not overwritten.}
	{note: Like POSIX setenv(), but taking an LmiBool argument overwrite and returning LmiBool.}
	{note: On platforms that do not support environment variables, this will
		always return LMI_FALSE.}
}
*/
#if LMI_HAVE_SETENV || LMI_HAVE__PUTENV_S
LMI_INLINE_DECLARATION
#endif
LmiBool LmiSetEnv(const char* name, const char* value, LmiBool overwrite);

/** 
{function visibility="private":
	{name: LmiUnsetEnv}
	{parent: StdCLib}
	{description: Clear the value of an environment variable.}
	{prototype: LmiBool LmiUnsetEnv(const char* name)}
	{parameter:
		{name: name}
		{description: The name of the environment variable to clear, as a C NUL-terminated string.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: Like POSIX unsetenv(), but returning LmiBool.}
	{note: On platforms that do not support environment variables, this will
		always return LMI_FALSE.}
}
*/
#if LMI_HAVE_UNSETENV || LMI_HAVE__PUTENV_S
LMI_INLINE_DECLARATION
#endif
LmiBool LmiUnsetEnv(const char* name);

/**
	{function visibility="private":
		{name: LmiWideStrLen}
		{parent: StdCLib}
		{description: Determine the length of a wide string.}
		{prototype: LmiSizeT LmiWideStrLen(const LmiWideChar* s)}
		{parameter:
			{name: s}
			{description: The NUL-terminated wide string whose length to determine.}}
		{return: The length of the string, not counting the terminating NUL.}
		{note: Like ISO C wcslen(), if wchar_t is 32-bit.}
	}
*/
LmiSizeT LmiWideStrLen(const LmiWideChar* s);


/**
	{function visibility="private":
		{name: LmiWideStrLCpy}
		{parent: StdCLib}
		{description: Safely copy a wide string to a buffer of known size.}
		{prototype: LmiSizeT LmiWideStrLCpy(LmiWideChar* dst, const LmiWideChar* src, LmiSizeT size)}
		{parameter:
			{name: dst}
			{description: The destination to which to copy the wide string.}}
		{parameter:
			{name: src}
			{description: The source string to copy from.  This must be a true
				(NUL-terminated) wide C string.}}
		{parameter:
			{name: size}
			{description: The size of the destination buffer, in characters.  At most
				size-1 characters will be copied from src to dst.  The result will always
				be NUL-terminated unless size == 0.}}
      {return: The length of the string that the function tried to create,
        i.e. the length of src.  If this is greater than or equal to size,
        the destination string was truncated compared to the source string.}
	}
*/
LmiSizeT LmiWideStrLCpy(LmiWideChar* dst, const LmiWideChar* src, LmiSizeT size);


/**
	{function visibility="private":
		{name: LmiWideStrLCat}
		{parent: StdCLib}
		{description: Safely append a string to a buffer of known size.}
		{prototype: LmiSizeT LmiWideStrLCat(LmiWideChar* dst, const LmiWideChar* src, LmiSizeT size)}
		{parameter:
			{name: dst}
			{description: The destination to which to append the string.
				Its existing contents must be a true (NUL-terminated) C wide string.}}
		{parameter:
			{name: src}
			{description: The source string to append.  This must be a true
				(NUL-terminated) C wide string.}}
		{parameter:
			{name: size}
			{description: The total size of the destination buffer, in characters.  At most
				size - LmiWideStrLen(dst) - 1 characters will be copied from src to dst.
				The result will always be NUL-terminated unless size == 0.}}
		{return: The length of the string that the function tried to create,
        	i.e. the initial length of dst plus length of src.  If this is greater
			than or equal to size, the appended string was truncated compared to the source
			string.}
	}
*/
LmiSizeT LmiWideStrLCat(LmiWideChar* dst, const LmiWideChar* src, LmiSizeT size);


/**
	{function visibility="private":
		{name: LmiWideStrCmp}
		{parent: StdCLib}
		{description: Compare two wide strings lexicographically.}
		{prototype: LmiInt LmiWideStrCmp(const LmiWideChar* a, const LmiWideChar* b)}
		{parameter:
			{name: a}
			{description: The first string to compare.}}
		{parameter:
			{name: b}
			{description: The second string to compare.}}
		{return: A number less than zero, zero, or greater than zero, if a
        	is lexicographically before, equal to, or after b, respectively.}
		{note: All the characters of the strings must be valid Unicode characters, i.e.
			with values less than 0x110000.}
		{note: Like ISO C wcscmp(), if wchar_t is 32-bit.}
	}
*/
LmiInt LmiWideStrCmp(const LmiWideChar* a, const LmiWideChar* b);

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#include <stdio.h>

/* stdout and stderr don't end up anywhere useful on Windows Phone.  Wrap them. */
LMI_INLINE_DECLARATION int LmiPrintfWrapWP8_(const char* fmt, ...);
LMI_INLINE_DECLARATION int LmiFPrintfWrapWP8_(FILE* file, const char* fmt, ...);
int LmiVPrintfWrapWP8_(const char* fmt, va_list ap);
int LmiVFPrintfWrapWP8_(FILE* file, const char* fmt, va_list ap);

#define printf LmiPrintfWrapWP8_
#define fprintf  LmiFPrintfWrapWP8_ 
#define vprintf  LmiVPrintfWrapWP8_ 
#define vfprintf LmiVFPrintfWrapWP8_ 

#endif

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiStdCLibInline.h>
#endif

#endif /* LMI_STDCLIB_H_ */
