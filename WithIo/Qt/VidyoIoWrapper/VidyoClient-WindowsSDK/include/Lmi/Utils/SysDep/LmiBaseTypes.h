/**
{file: 
	{name: LmiBaseTypes.h}
	{description: basic type definitions for LMI software.}
	{copyright:
		(c) 2011-2016 Vidyo, Inc.,
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
#ifndef LMI_BASE_TYPES_H_
#define LMI_BASE_TYPES_H_

#include <stdlib.h> /* NULL, size_t */
#include <stddef.h> /* ptrdiff_t */
#include <limits.h> /* CHAR_BIT */

#include <Lmi/Utils/SysDep/LmiBaseCompiler.h>

#if LMI_HAVE_FLOAT_H
#include <float.h>	/* FLT_MAX, DBL_MAX */
#endif

#if LMI_HAVE_WCHAR_H
#include <wchar.h>
#endif

LMI_BEGIN_EXTERN_C

/* Note: docblocks for all these types are in Lmi/Utils/LmiTypes.h, which also
 * constains the declarations of the LmiObject functions for the basic types.
 * In almost all cases other files should include Lmi/Utils/LmiTypes.h rather than
 * this file.  */

typedef unsigned char LmiBool;

#define LMI_FALSE 0
#define LMI_TRUE 1


typedef int LmiInt;

#define LMI_INT_MAX ((LmiInt)(~0U >> 1))
#define LMI_INT_MIN (~LMI_INT_MAX)


#if CHAR_BIT != 8
/* Ensure that the LMI_SIZEOF measurements computed by autoconf
   correspond to the values we think they do. */
#error "The LMI SDK does not currently support platforms non-8-bit bytes"
#endif

typedef signed char LmiInt8;


#if LMI_SIZEOF_SHORT == 2
typedef signed short LmiInt16;
#elif LMI_SIZEOF_INT == 2 /* Do such platforms really still exist? */
typedef signed int LmiInt16;
#else
#error "Unable to determine a 16-bit type for LmiInt16"
#endif


#if LMI_SIZEOF_INT == 4
typedef signed int LmiInt32;
#elif LMI_SIZEOF_LONG == 4
typedef signed long LmiInt32;
#else
#error "Unable to determine a 32-bit type for LmiInt32"
#endif


#if LMI_SIZEOF_LONG == 8
typedef signed long LmiInt64;
#define LMI_INT64_C(val) (LmiInt64)(val ## L)

#elif defined(LMI_HAVE_LONG_LONG) && LMI_SIZEOF_LONG_LONG == 8
typedef signed long long LmiInt64;
#define LMI_INT64_C(val) (LmiInt64)(val ## LL)

#elif defined(LMI_HAVE___INT64)
typedef __int64 LmiInt64;
#define LMI_INT64_C(val) (LmiInt64)(val ## i64)

#else
#error "Unable to determine a 64-bit type for LmiInt64"
#endif

#if LMI_SIZEOF_VOID_P == 8
typedef LmiInt64 LMI_ATTRIBUTE_W64 LmiIntPtrT;
#elif LMI_SIZEOF_VOID_P == 4
typedef LmiInt32 LMI_ATTRIBUTE_W64 LmiIntPtrT;
#else
#error "Unable to determine a type for LmiIntPtrT"
#endif


typedef unsigned int LmiUint;


typedef unsigned char LmiUint8;


#if LMI_SIZEOF_SHORT == 2
typedef unsigned short LmiUint16;
#elif LMI_SIZEOF_UNSIGNED_INT == 2 /* Do such platforms really still exist? */
typedef unsigned int LmiUint16;
#else
#error "Unable to determine a 16-bit unsigned type for LmiUint16"
#endif


#if LMI_SIZEOF_UNSIGNED_INT == 4
typedef unsigned int LmiUint32;
#elif LMI_SIZEOF_UNSIGNED_LONG == 4
typedef unsigned long LmiUint32;
#else
#error "Unable to determine a 32-bit unsigned type for LmiUint32"
#endif


#if LMI_SIZEOF_UNSIGNED_LONG == 8
typedef unsigned long LmiUint64;
#define LMI_UINT64_C(val) (LmiUint64)(val ## UL)

#elif defined(LMI_HAVE_UNSIGNED_LONG_LONG) && LMI_SIZEOF_UNSIGNED_LONG_LONG == 8
typedef unsigned long long LmiUint64;
#define LMI_UINT64_C(val) (LmiUint64)(val ## ULL)

#elif defined(LMI_HAVE_UNSIGNED___INT64)
typedef unsigned __int64 LmiUint64;
#define LMI_UINT64_C(val) (LmiUint64)(val ## Ui64)

#else
#error "Unable to determine a 64-bit unsigned type for LmiUint64"
#endif

#define LMI_UINT64_MAX LMI_UINT64_C(~0)

#if LMI_SIZEOF_VOID_P == 8
typedef LmiUint64 LMI_ATTRIBUTE_W64 LmiUintPtrT;
#elif LMI_SIZEOF_VOID_P == 4
typedef LmiUint32 LMI_ATTRIBUTE_W64 LmiUintPtrT;
#else
#error "Unable to determine a type for LmiUintPtrT"
#endif


typedef size_t LmiSizeT;

#define LMI_SIZET_MAX ((LmiSizeT)~0)
#define LMI_SIZE_T_MAX LMI_SIZET_MAX


typedef ptrdiff_t LmiDistanceT;


typedef void * LmiVoidPtr;


#if LMI_HAVE_WCHAR_T && LMI_SIZEOF_WCHAR_T == 4
typedef wchar_t LmiWideChar;
#define LMI_WIDECHAR_IS_WCHAR_T_ 1
#else
typedef LmiInt32 LmiWideChar;
#endif


typedef float  LmiFloat32;
typedef double LmiFloat64;

#define LMI_FLOAT32_MAX			( FLT_MAX )
#define LMI_FLOAT32_MIN			( -FLT_MAX )
#define LMI_FLOAT32_UNDERFLOW	( FLT_MIN )

#define LMI_FLOAT64_MAX			( DBL_MAX )
#define LMI_FLOAT64_MIN			( -DBL_MIN )
#define LMI_FLOAT64_UNDERFLOW	( DBL_MIN )

LMI_END_EXTERN_C

#endif /* LMI_BASE_TYPES_H_ */
