/** {file:
	  {name: LmiAtomicIntegerInline.h}
	  {description: Inline functions for LmiAtomicInteger.}
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

#if LMI_ATOMIC_INTEGER_USE_WIN32_

/** {implementation: {name: LmiAtomicIntegerConstruct}} */
LMI_INLINE LmiAtomicInteger* LmiAtomicIntegerConstruct(LmiAtomicInteger* a)
{
	*a = 0;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerConstructWithValue}} */
LMI_INLINE LmiAtomicInteger*
LmiAtomicIntegerConstructWithValue(LmiAtomicInteger* a, LmiInt val)
{
	*a = (LONG)val;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerGetValue}} */
LMI_INLINE LmiInt LmiAtomicIntegerGetValue(const LmiAtomicInteger* a)
{
	return (LmiInt)*a;
}


/** {implementation: {name: LmiAtomicIntegerDestruct}} */
LMI_INLINE void LmiAtomicIntegerDestruct(LmiAtomicInteger* a)
{
	/* Nothing needs to be done */
}


/** {implementation: {name: LmiAtomicIntegerCompareAndExchange}} */
LMI_INLINE LmiBool LmiAtomicIntegerCompareAndExchange(LmiAtomicInteger* a,
	LmiInt oldVal, LmiInt newVal)
{
	return InterlockedCompareExchange(a, (LONG)newVal, (LONG)oldVal) == oldVal;
}

/** {implementation: {name: LmiAtomicIntegerIncrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerIncrement(LmiAtomicInteger* a)
{
	return (LmiInt)InterlockedIncrement(a);
}


/** {implementation: {name: LmiAtomicIntegerDecrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerDecrement(LmiAtomicInteger* a)
{
	return (LmiInt)InterlockedDecrement(a);
}


#elif LMI_ATOMIC_INTEGER_USE_MACOSX_

/** {implementation: {name: LmiAtomicIntegerConstruct}} */
LMI_INLINE LmiAtomicInteger* LmiAtomicIntegerConstruct(LmiAtomicInteger* a)
{
	*a = 0;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerConstructWithValue}} */
LMI_INLINE LmiAtomicInteger*
LmiAtomicIntegerConstructWithValue(LmiAtomicInteger* a, LmiInt val)
{
	*a = (int32_t)val;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerGetValue}} */
LMI_INLINE LmiInt LmiAtomicIntegerGetValue(const LmiAtomicInteger* a)
{
	return (LmiInt)*a;
}


/** {implementation: {name: LmiAtomicIntegerDestruct}} */
LMI_INLINE void LmiAtomicIntegerDestruct(LmiAtomicInteger* a)
{
	/* Nothing needs to be done */
}


/** {implementation: {name: LmiAtomicIntegerCompareAndExchange}} */
LMI_INLINE LmiBool LmiAtomicIntegerCompareAndExchange(LmiAtomicInteger* a,
	LmiInt oldVal, LmiInt newVal)
{
	return OSAtomicCompareAndSwap32((int32_t)oldVal, (int32_t)newVal,
#ifndef OS_ATOMIC_QUEUE_INIT
	/* Hack -- on MacOS X pre-Tiger, the argument to the OSAtomic*
	   functions isn't volatile, even though it conceptually should
	   be.  The version of libkern/OSAtomic.h that has the volatile
	   arguments is also the one that introduced OS_ATOMIC_QUEUE_INIT,
	   so use that as an indicator. */
		(int32_t*)
#endif
		a);
}

/** {implementation: {name: LmiAtomicIntegerIncrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerIncrement(LmiAtomicInteger* a)
{
	return (LmiInt)OSAtomicIncrement32(
#ifndef OS_ATOMIC_QUEUE_INIT
	/* Hack -- see comment in LmiAtomicIntegerCompareAndExchange above. */
									   (int32_t*)
#endif
									   a);
}


/** {implementation: {name: LmiAtomicIntegerDecrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerDecrement(LmiAtomicInteger* a)
{
	return (LmiInt)OSAtomicDecrement32(
#ifndef OS_ATOMIC_QUEUE_INIT
	/* Hack -- see comment in LmiAtomicIntegerCompareAndExchange above. */
									   (int32_t*)
#endif
									   a);
}

#elif LMI_ATOMIC_INTEGER_USE_GCC_ATOMIC_BUILTINS

/** {implementation: {name: LmiAtomicIntegerConstruct}} */
LMI_INLINE LmiAtomicInteger* LmiAtomicIntegerConstruct(LmiAtomicInteger* a)
{
	*a = 0;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerConstructWithValue}} */
LMI_INLINE LmiAtomicInteger*
LmiAtomicIntegerConstructWithValue(LmiAtomicInteger* a, LmiInt val)
{
	*a = val;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerGetValue}} */
LMI_INLINE LmiInt LmiAtomicIntegerGetValue(const LmiAtomicInteger* a)
{
	return *a;
}


/** {implementation: {name: LmiAtomicIntegerDestruct}} */
LMI_INLINE void LmiAtomicIntegerDestruct(LmiAtomicInteger* a)
{
	/* Nothing needs to be done */
}


/** {implementation: {name: LmiAtomicIntegerCompareAndExchange}} */
LMI_INLINE LmiBool LmiAtomicIntegerCompareAndExchange(LmiAtomicInteger* a,
	LmiInt oldVal, LmiInt newVal)
{
	return __sync_bool_compare_and_swap(a, oldVal, newVal);
}

/** {implementation: {name: LmiAtomicIntegerIncrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerIncrement(LmiAtomicInteger* a)
{
	return __sync_add_and_fetch(a, 1);
}


/** {implementation: {name: LmiAtomicIntegerDecrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerDecrement(LmiAtomicInteger* a)
{
	return __sync_sub_and_fetch(a, 1);
}


#elif LMI_ATOMIC_INTEGER_USE_GCC_X86_ASM_

/** {implementation: {name: LmiAtomicIntegerConstruct}} */
LMI_INLINE LmiAtomicInteger* LmiAtomicIntegerConstruct(LmiAtomicInteger* a)
{
	*a = 0;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerConstructWithValue}} */
LMI_INLINE LmiAtomicInteger*
LmiAtomicIntegerConstructWithValue(LmiAtomicInteger* a, LmiInt val)
{
	*a = (LmiInt32)val;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerGetValue}} */
LMI_INLINE LmiInt LmiAtomicIntegerGetValue(const LmiAtomicInteger* a)
{
	return (LmiInt)*a;
}


/** {implementation: {name: LmiAtomicIntegerDestruct}} */
LMI_INLINE void LmiAtomicIntegerDestruct(LmiAtomicInteger* a)
{
	/* Nothing needs to be done */
}


/** {implementation: {name: LmiAtomicIntegerCompareAndExchange}} */
LMI_INLINE LmiBool LmiAtomicIntegerCompareAndExchange(LmiAtomicInteger* a,
	LmiInt oldVal, LmiInt newVal)
{
	LmiUint8 ret;
    __asm__ __volatile__(
		"lock; cmpxchgl %1, %3; sete %0"
		:"=r" (ret)
		:"r" (newVal), "a" (oldVal), "m" (*a)
		:"memory");
	return (LmiBool)(ret);
}

/** {implementation: {name: LmiAtomicIntegerIncrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerIncrement(LmiAtomicInteger* a)
{
	LmiInt32 tmp = 1;
	LmiInt32 result;
    __asm__ __volatile__(
		"lock; xaddl %0, %2"
		:"=r" (result)
		:"0" (tmp), "m" (*a)
		:"memory");
	return (LmiInt)(result+1);
}


/** {implementation: {name: LmiAtomicIntegerDecrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerDecrement(LmiAtomicInteger* a)
{
	LmiInt32 tmp = -1;
	LmiInt32 result;
    __asm__ __volatile__(
		"lock; xaddl %0, %2"
		:"=r" (result)
		:"0" (tmp), "m" (*a)
		:"memory");
	return (LmiInt)(result-1);
}


#elif LMI_ATOMIC_INTEGER_USE_GENERIC_

/** {implementation: {name: LmiAtomicIntegerConstruct}} */
LMI_INLINE LmiAtomicInteger* LmiAtomicIntegerConstruct(LmiAtomicInteger* a)
{
	if (LmiMutexConstruct(&a->mutex) == NULL) {
		return NULL;
	}
	a->value = 0;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerConstructWithValue}} */
LMI_INLINE LmiAtomicInteger*
LmiAtomicIntegerConstructWithValue(LmiAtomicInteger* a, LmiInt val)
{
	if (LmiMutexConstruct(&a->mutex) == NULL) {
		return NULL;
	}
	a->value = val;
	return a;
}


/** {implementation: {name: LmiAtomicIntegerDestruct}} */
LMI_INLINE void LmiAtomicIntegerDestruct(LmiAtomicInteger* a)
{
	LmiMutexDestruct(&a->mutex);
}


/** {implementation: {name: LmiAtomicIntegerGetValue}} */
LMI_INLINE LmiInt LmiAtomicIntegerGetValue(const LmiAtomicInteger* a)
{
	LmiInt ret;
	
	LmiMutexLock(&a->mutex);
	ret = a->value;
	LmiMutexUnlock(&a->mutex);

	return ret;
}


/** {implementation: {name: LmiAtomicIntegerCompareAndExchange}} */
LMI_INLINE LmiBool LmiAtomicIntegerCompareAndExchange(LmiAtomicInteger* a,
	LmiInt oldVal, LmiInt newVal)
{
	LmiInt ret;
	
	LmiMutexLock(&a->mutex);

	ret = (a->value == oldVal);

	if (ret) {
		a->value = newVal;
	}

	LmiMutexUnlock(&a->mutex);

	return ret;
}


/** {implementation: {name: LmiAtomicIntegerIncrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerIncrement(LmiAtomicInteger* a)
{
	LmiInt ret;
	
	LmiMutexLock(&a->mutex);
	a->value++;
	ret = a->value;
	LmiMutexUnlock(&a->mutex);

	return ret;
}


/** {implementation: {name: LmiAtomicIntegerDecrement}} */
LMI_INLINE LmiInt LmiAtomicIntegerDecrement(LmiAtomicInteger* a)
{
	LmiInt ret;
	
	LmiMutexLock(&a->mutex);
	a->value--;
	ret = a->value;
	LmiMutexUnlock(&a->mutex);

	return ret;
}

#endif /* LMI_ATOMIC_INTEGER_USE_GENERIC_ */


LMI_INLINE LmiInt LmiAtomicIntegerIncrementConditional(LmiAtomicInteger* a)
{
	LmiInt val, newVal;

	do {
		val = LmiAtomicIntegerGetValue(a);
		if (val <= 0) {
			return 0;
		}
		newVal = val + 1;
	} while (!LmiAtomicIntegerCompareAndExchange(a, val, newVal));

	return newVal;
}
