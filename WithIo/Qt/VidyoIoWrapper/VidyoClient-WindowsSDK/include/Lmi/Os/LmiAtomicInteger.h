/** {file:
	  {name: LmiAtomicInteger.h}
	  {description: Atomic (thread-safe) integer type.}
	  {copyright:
	  	(c) 2006-2015 Vidyo, Inc.,
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
#ifndef LMI_ATOMIC_INTEGER_H_
#define LMI_ATOMIC_INTEGER_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiMutex.h>

LMI_BEGIN_EXTERN_C

/**
   {type visibility="private":
     {name: LmiAtomicInteger}
	 {parent: Os}
	 {include: Lmi/Os/LmiAtomicInteger.h}
	 {description: An atomic (thread-safe) integer type.}
   }
*/

#if LMI_HAVE_INTERLOCKEDCOMPAREEXCHANGE && LMI_HAVE_INTERLOCKEDDECREMENT && LMI_HAVE_INTERLOCKEDINCREMENT && !defined(__CYGWIN__)

#if LMI_HAVE_WINSOCK2_H
#include <winsock2.h>
#elif LMI_HAVE_WINDOWS_H
#include <windows.h>
#endif

#define LMI_ATOMIC_INTEGER_USE_WIN32_ 1

#elif LMI_HAVE_OSATOMICCOMPAREANDSWAP32 && LMI_HAVE_OSATOMICDECREMENT32 && LMI_HAVE_OSATOMICINCREMENT32

#if LMI_HAVE_LIBKERN_OSATOMIC_H
#include <libkern/OSAtomic.h>
#endif

#define LMI_ATOMIC_INTEGER_USE_MACOSX_ 1

#elif LMI_HAVE_GCC_ATOMIC_BUILTINS

#define LMI_ATOMIC_INTEGER_USE_GCC_ATOMIC_BUILTINS 1

#elif defined(__GNUC__) && defined(__i386__)

#define LMI_ATOMIC_INTEGER_USE_GCC_X86_ASM_ 1

#else

#define LMI_ATOMIC_INTEGER_USE_GENERIC_ 1

#endif


#if LMI_ATOMIC_INTEGER_USE_WIN32_

typedef volatile LONG LmiAtomicInteger;

#elif LMI_ATOMIC_INTEGER_USE_MACOSX_

typedef volatile int32_t LmiAtomicInteger;

#elif LMI_ATOMIC_INTEGER_USE_GCC_ATOMIC_BUILTINS

typedef volatile LmiInt LmiAtomicInteger;

#elif LMI_ATOMIC_INTEGER_USE_GCC_X86_ASM_

typedef volatile LmiInt32 LmiAtomicInteger;

#elif LMI_ATOMIC_INTEGER_USE_GENERIC_

typedef struct {
	LmiMutex mutex;
	LmiInt value;
} LmiAtomicInteger;

#endif

/**
   {function visibility="private":
     {name: LmiAtomicIntegerConstruct}
	 {parent: LmiAtomicInteger}
	 {description: Construct an atomic integer, with initial value 0.}
	 {prototype: LmiAtomicInteger* LmiAtomicIntegerConstruct(LmiAtomicInteger* a)}
	 {parameter:
	   {name: a}
	   {description: The object to construct.}}
	 {return: a on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiAtomicInteger* LmiAtomicIntegerConstruct(LmiAtomicInteger* a);


/**
   {function visibility="private":
     {name: LmiAtomicIntegerConstructWithValue}
	 {parent: LmiAtomicInteger}
	 {description: Construct an atomic integer, with a given initial value.}
	 {prototype: LmiAtomicInteger* LmiAtomicIntegerConstructWithValue(LmiAtomicInteger* a, LmiInt val)}
	 {parameter:
	   {name: a}
	   {description: The object to construct.}}
	 {parameter:
	   {name: val}
	   {description: The initial value of the atomic integer.}}
	 {return: a on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiAtomicInteger* LmiAtomicIntegerConstructWithValue(LmiAtomicInteger* a, LmiInt val);


/**
   {function visibility="private":
     {name: LmiAtomicIntegerDestruct}
	 {parent: LmiAtomicInteger}
	 {description: Destruct an atomic integer.}
	 {prototype: void LmiAtomicIntegerDestruct(LmiAtomicInteger* a)}
	 {parameter:
	   {name: a}
	   {description: The object to destruct.}}
   }
*/
LMI_INLINE_DECLARATION void LmiAtomicIntegerDestruct(LmiAtomicInteger* a);


/**
   {function visibility="private":
     {name: LmiAtomicIntegerGetValue}
	 {parent: LmiAtomicInteger}
	 {description: Get the current value of an atomic integer.}
	 {prototype: LmiInt LmiAtomicIntegerGetValue(const LmiAtomicInteger* a)}
	 {parameter:
	   {name: a}
	   {description: The object whose value to get.}}
	 {return: The atomic integer\'s current value.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiAtomicIntegerGetValue(const LmiAtomicInteger* a);


/**
   {function visibility="private":
     {name: LmiAtomicIntegerCompareAndExchange}
	 {parent: LmiAtomicInteger}
	 {description: Set a new value of an atomic integer, if its current value
	   is equal to a given value.}
	 {prototype: LmiBool LmiAtomicIntegerCompareAndExchange(LmiAtomicInteger* a, LmiInt oldVal, LmiInt newVal)}
	 {parameter:
	   {name: a}
	   {description: The object whose value to test and set.}}
	 {parameter:
	   {name: oldVal}
	   {description: The caller\'s belief about the current value of the
	     atomic integer.}}
	 {parameter:
	   {name: newVal}
	   {description: A new value for the atomic integer.}}
	 {return: Whether the compare-and-exchange operation was performed.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiAtomicIntegerCompareAndExchange(LmiAtomicInteger* a,
	LmiInt oldVal, LmiInt newVal);


/**
   {function visibility="private":
     {name: LmiAtomicIntegerIncrement}
	 {parent: LmiAtomicInteger}
	 {description: Increment the value of an atomic integer by one,
	   and return its new value.}
	 {prototype: LmiInt LmiAtomicIntegerIncrement(LmiAtomicInteger* a)}
	 {parameter:
	   {name: a}
	   {description: The object whose value to increment.}}
	 {return: The new value of the atomic integer.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiAtomicIntegerIncrement(LmiAtomicInteger* a);


/**
   {function visibility="private":
     {name: LmiAtomicIntegerDecrement}
	 {parent: LmiAtomicInteger}
	 {description: Decrement the value of an atomic integer by one,
	   and return its new value.}
	 {prototype: LmiInt LmiAtomicIntegerDecrement(LmiAtomicInteger* a)}
	 {parameter:
	   {name: a}
	   {description: The object whose value to decrement.}}
	 {return: The new value of the atomic integer.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiAtomicIntegerDecrement(LmiAtomicInteger* a);


/**
   {function visibility="private":
     {name: LmiAtomicIntegerIncrementConditional}
	 {parent: LmiAtomicInteger}
	 {description: Increment the value of an atomic integer by one iff
	   it is greater than 0, and return its new (or unchanged) value.}
	 {prototype: LmiInt LmiAtomicIntegerIncrementConditional(LmiAtomicInteger* a)}
	 {parameter:
	   {name: a}
	   {description: The object whose value to increment conditionally.}}
	 {return: The new value of the atomic integer.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiAtomicIntegerIncrementConditional(LmiAtomicInteger* a);





LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiAtomicIntegerInline.h>
#endif

#endif /* LMI_ATOMIC_INTEGER_H_ */
