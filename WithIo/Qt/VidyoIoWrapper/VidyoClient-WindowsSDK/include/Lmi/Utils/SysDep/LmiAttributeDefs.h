/** {file:
      {name: LmiAttributeDefs.h}
      {description: File that portably defines several useful function and
        type attributes.}
      {copyright:
      	(c) 2006-2013 Vidyo, Inc.,
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

#ifndef LMI_ATTRIBUTE_DEFS_H_
#define LMI_ATTRIBUTE_DEFS_H_

/* How to describe a function as printf-like or vprintf-like */

/**
   {function visibility="private" validate="no":
     {name: LmiFunctionPrintfLike}
     {parent: Utils}
	 {include: Lmi/Utils/LmiCompiler.h}
     {description: A function attribute indicating that a function takes
       printf-style arguments.}
     {prototype: Type LmiFunctionPrintfLike(LmiInt formatIndex, LmiInt firstArgIndex)}
     {parameter:
       {name: formatIndex}
       {description: The parameter number of the printf format string,
         counting from 1.}}
     {parameter:
       {name: firstArgIndex}
       {description: The parameter number of the first printf argument,
         counting from 1.}}
	 {return: Expands to a function attribute indicating that the function
	   takes printf-style arguments, or to nothing.}
   }
*/

/**
   {function visibility="private" validate="no":
     {name: LmiFunctionVPrintfLike}
     {parent: Utils}
	 {include: Lmi/Utils/LmiCompiler.h}
     {description: A function attribute indicating that a function takes
       vprintf-style arguments.}
     {prototype: Type LmiFunctionVPrintfLike(LmiInt formatIndex)}
     {parameter:
       {name: formatIndex}
       {description: The parameter number of the printf format string,
         counting from 1.}}
	 {return: Expands to a function attribute indicating that the function
	   takes vprintf-style arguments, or to nothing.}
   }
*/


#if defined(__GNUC__)

#define LmiFunctionPrintfLike(formatIndex, firstArgIndex) \
  __attribute__ ((__format__ (__printf__, formatIndex, firstArgIndex)))
#define LmiFunctionVPrintfLike(formatIndex) \
  __attribute__ ((__format__ (__printf__, formatIndex, 0)))

/* Add defines for other compilers' printf-style notations here. */
#else

#define LmiFunctionPrintfLike(formatIndex, firstArgIndex) \
  /* defined as empty */
#define LmiFunctionVPrintfLike(formatIndex) \
  /* defined as empty */

#endif



/* How to annotate an integer type as being 64 bits on 64-bit platforms. */

#if LMI_HAVE_ATTRIBUTE_W64
#define LMI_ATTRIBUTE_W64 __w64
#else
#define LMI_ATTRIBUTE_W64 /* defined as empty */
#endif


/* How to mark a function as deprecated */

#if defined(_MSC_VER)
#if _MSC_VER >= 1400 
#define LMI_DEPRECATED(text) __declspec(deprecated(text))
#else
#define LMI_DEPRECATED(text) __declspec(deprecated)
#endif
#elif defined(__GNUC__)
#define LMI_DEPRECATED(text) __attribute__((__deprecated__))

/* Add additional compiler definitions here */

#else
#define LMI_DEPRECATED(text) /* Nothing */
#endif


/* How to mark an object as aligned. */

#if defined(_MSC_VER)
#define LMI_ALIGN(n) __declspec(align(n))
#elif defined(__GNUC__)
#define LMI_ALIGN(n) __attribute__((__aligned__(n)))

/* Add additional compiler definitions here */

#else
#define LMI_ALIGN(n) /* Nothing */
#endif


/* How to mark a pointer as restricted */

#if defined(_MSC_VER)
#define LMI_RESTRICT __restrict
#elif defined(__GNUC__)
#define LMI_RESTRICT __restrict__

/* Add additional compiler definitions here */

#else
#define LMI_RESTRICT /* Nothing */
#endif


/* How to mark a function so that warnings are given if its result is unused */

#if defined(__GNUC__)
#define LMI_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#else
#define LMI_WARN_UNUSED_RESULT /* Nothing */
#endif

/* How to mark a type as aliasing other types, turning off strict-aliasing. */
#if defined(__GNUC__)
#define LMI_MAY_ALIAS __attribute__((__may_alias__))
#else
#define LMI_MAY_ALIAS /* Nothing */
#endif

/* How to mark a function as needing forcible stack alignment */
/* Note: never needed on Mac OS X, and causes compiler problems with
 * inline assembly on Snow Leopard. */

#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)) && __i386__ && !defined(__APPLE_CC__)
#define LMI_ALIGN_ARG_POINTER __attribute__((__force_align_arg_pointer__))
#else
#define LMI_ALIGN_ARG_POINTER /* Nothing */
#endif


/* How to mark a function as never-returning */
#if defined(__GNUC__)
#define LMI_NO_RETURN __attribute__((__noreturn__))
#elif defined(_MSC_VER)
#define LMI_NO_RETURN __declspec(noreturn)

/* Add additional compiler definitions here */

#else
#define LMI_NO_RETURN /* nothing */
#endif


/* How to mark a function or variable as possibly unused, suppressing
   "unused" warnings.
   Note: this should only be applied in cases where the unused item can't
   just be deleted: e.g., macro output, autogenerated code, code used only
   in conditionally-compiled sections, etc. */
#if defined(__GNUC__)
#define LMI_POSSIBLY_UNUSED __attribute__((__unused__))
#else
#define LMI_POSSIBLY_UNUSED /* Nothing */
#endif


/* How to indicate that a function shouldn't have the address sanitizer
   applied to it.
   The Clang address santizer has problems with inline assembly that
   uses too many registers. */
/* Note though that on Android x86/x86_64 clang segfaults if you pass this
   attribute, even when the address sanitizer isn't enabled.  Since asan is
   broken on Android anyway, disable the attribute there. */
#if defined(__clang__) && !(defined(ANDROID) && (defined(__x86_64__) || defined(__i386__)))
#define LMI_NO_SANITIZE_ADDRESS __attribute__((__no_sanitize_address__))
#else
#define LMI_NO_SANITIZE_ADDRESS /* Nothing */
#endif

#endif /* LMI_ATTRIBUTE_DEFS_H_ */
