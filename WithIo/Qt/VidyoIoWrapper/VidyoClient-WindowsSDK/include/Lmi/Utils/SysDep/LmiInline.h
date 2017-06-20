/** {file:
      {name: LmiInline.h}
      {description: File that portably defines the LMI_INLINE macro.}
      {copyright:
      	(c) 2005-2013 Vidyo, Inc.,
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

#ifndef LMI_INLINE_H_
#define LMI_INLINE_H_

/*
 * The LMI_INLINE macro is a portable way of defining inline functions,
 * where available, across many different compilers.
 * 
 * On any compiler, LMI_INLINE and LMI_INLINE_DECLARATION must be
 * defined so that it is always valid for an LMI_INLINE definition of
 * a function to follow an LMI_INLINE_DECLARATION declaration of the
 * function in multiple translation units.  If this is not possible,
 * inlining should be disabled.  (This constraint is achievable in
 * GCC, in C++, and in Microsoft Visual C, and is implemented in this
 * file for each of those targets.  It does not appear to be
 * achievable in an ISO C 99 compiler without vendor extensions.)
 * 
 * To support compilers without inline, and to support the need for
 * non-inlined "backup" function definitions in some compilers, potentially
 * inlined functions may need to appear both in a .h file and a .c file.
 * 
 * Functions to be inlined should generally be written as follows.
 *
 * In a file LmiExampleInline.h:
 *
 * LMI_INLINE void LmiExampleFunction(void) { DoSomething(); }
 *
 * Note that this file should *not* have multiple-include guards.
 *
 *
 * In a file LmiExample.h:
 * #ifndef LMI_EXAMPLE_H_
 * #define LMI_EXAMPLE_H_ 
 * ...
 * #include <LmiInline.h>
 * ...
 * LMI_INLINE_DECLARATION void LmiExampleFunction(void);
 * ...
 * #if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
 * #include <LmiExampleInline.h>
 * #endif
 * ...
 * #endif (LMI_EXAMPLE_H_)
 *
 *
 * In a file LmiExample.c:
 * #include <LmiExample.h>
 *   ... all other necessary #includes ... 
 * #if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
 * #undef LMI_INLINE
 * #define LMI_INLINE LMI_INLINE_SOURCE_FILE
 * #include <LmiExampleInline.h>
 * #endif
 *
 * If the inlined definitions are being defined by a macro (as they are for
 * the LMI container classes, for example), the separate include files are
 * not necessary; the macros can simply be expanded (guarded as above) both
 * in the header file and in the source file.
 *
 * For inline functions in a single file, you can use LMI_STATIC_INLINE
 * instead.  This should be used on every declaration and definition of a
 * function.
 */

#if defined(LMI_USE_ALL_STATIC_INLINES)
/* Force all inlines to be static inlines.  Causes redundant definitions
 * and can break pointer comparison, but more compatible. */
#define LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS 1
#define LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS 0

#define LMI_INLINE static inline
#define LMI_INLINE_SOURCE_FILE !!!SOURCE FILE INLINE NOT USED IN THIS MODE!!!

#define LMI_STATIC_INLINE static inline

#define LMI_INLINE_DECLARATION static inline

#elif defined(__cplusplus)
/* C++ inline.  C++ inline functions have vague linkage, i.e. the compiler
 * can emit them more than once if necessary. */
#define LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS 1
#define LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS 0

#define LMI_INLINE inline
#define LMI_INLINE_SOURCE_FILE !!!SOURCE FILE INLINE NOT USED IN THIS MODE!!!

#define LMI_STATIC_INLINE static inline

#define LMI_INLINE_DECLARATION inline

#elif defined(__GNUC__)
#if defined(LMI_USE_GCC_ALWAYS_INLINE)
/* GNU C "__always_inline__" mode. */
#define LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS 1
#define LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS 0

#if defined(__GNUC_STDC_INLINE__)
/* GCC 4.2 or later in C99 mode.  Use GNU89 inline semantics. */
#define LMI_INLINE extern __inline__ __attribute__((__gnu_inline__,__always_inline__))
#else
/* __inline__ works even in GNU C's strict-ansi mode. */
#define LMI_INLINE extern __inline__ __attribute__((__always_inline__))
#endif

#define LMI_INLINE_SOURCE_FILE  !!!SOURCE FILE INLINE NOT USED IN THIS MODE!!!

#define LMI_STATIC_INLINE static __inline__ __attribute__((__always_inline__))

#define LMI_INLINE_DECLARATION LMI_INLINE


#else

/* GNU C inline.  GNU C extern inline needs an explicit backup definition
 * for the cases when the compiler couldn't inline the function. */
#define LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS 1
#define LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS 1

#if defined(__GNUC_STDC_INLINE__)
/* GCC 4.2 or later in C99 mode.  Use GNU89 inline semantics. */
#define LMI_INLINE extern __inline__ __attribute__((__gnu_inline__))
#else
/* __inline__ works even in GNU C's strict-ansi mode. */
#define LMI_INLINE extern __inline__
#endif

#define LMI_INLINE_SOURCE_FILE /* (defined as empty) */

#define LMI_STATIC_INLINE static __inline__

#define LMI_INLINE_DECLARATION LMI_INLINE

#endif

#elif defined(_MSC_VER)
/* Microsoft Visual C. (Visual C++ is caught by __cplusplus above.) */
/* Visual C appears to implement the same vague linkage (COMDAT) semantics
 * as C++. */
#define LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS 1
#define LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS 0

#define LMI_INLINE __inline
#define LMI_INLINE_SOURCE_FILE !!!SOURCE FILE INLINE NOT USED IN THIS MODE!!!

#define LMI_STATIC_INLINE static __inline

#define LMI_INLINE_DECLARATION /* (defined as empty) */

/* If other inline schemes are discovered, add support for them here. */

#else
/* No inline support.  Include definitions in the source file only. */

#define LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS 0
#define LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS 1

#define LMI_INLINE !!!HEADER FILE INLINE NOT USED IN THIS MODE!!!
#define LMI_INLINE_SOURCE_FILE /* (defined as empty) */

#define LMI_STATIC_INLINE static

#define LMI_INLINE_DECLARATION /* (defined as empty) */

#endif


/* Macro that expands to nothing, to use as an argument to macros that
 * might or might not want inline arguments, because C90 doesn't allow
 * empty macro arguments. */

#define LMI_NO_INLINE /* (defined as empty) */

#endif /* LMI_INLINE_H_ */
