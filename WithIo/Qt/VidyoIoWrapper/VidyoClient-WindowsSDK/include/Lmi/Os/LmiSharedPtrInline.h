/** {file:
	  {name: LmiSharedPtrInline.h}
	  {description: Inline (non-templatized) functions for LmiSharedPtr.}
	  {copyright:
	  	(c) 2009-2015 Vidyo, Inc.,
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

LMI_INLINE LmiSharedPtrRefCount* LmiSharedPtrRefCountConstruct(LmiSharedPtrRefCount* r)
{
	if (LmiAtomicIntegerConstruct(&r->useCount) == NULL)
		return NULL;
	if (LmiAtomicIntegerConstruct(&r->weakCount) == NULL) {
		LmiAtomicIntegerDestruct(&r->useCount);
		return NULL;
	}

	return r;
}


LMI_INLINE void LmiSharedPtrRefCountDestruct(LmiSharedPtrRefCount* r)
{
	LmiAtomicIntegerDestruct(&r->weakCount);
	LmiAtomicIntegerDestruct(&r->useCount);
}


LMI_INLINE void LmiSharedPtrRefCountIncUseCount(LmiSharedPtrRefCount* r)
{
	LmiAtomicIntegerIncrement(&r->useCount);
}


LMI_INLINE LmiBool LmiSharedPtrRefCountDecUseCount(LmiSharedPtrRefCount* r)
{
	LmiInt newVal;
	newVal = LmiAtomicIntegerDecrement(&r->useCount);
	LmiAssert(newVal >= 0);
	return (newVal == 0);
}


LMI_INLINE LmiInt LmiSharedPtrRefCountGetUseCount(const LmiSharedPtrRefCount* r)
{
	return LmiAtomicIntegerGetValue(&r->useCount);
}


LMI_INLINE LmiBool LmiSharedPtrRefCountIncUseCountConditional(LmiSharedPtrRefCount* r)
{
	LmiInt newVal;
	newVal = LmiAtomicIntegerIncrementConditional(&r->useCount);
	return (newVal != 0);
}


LMI_INLINE void LmiSharedPtrRefCountIncWeakCount(LmiSharedPtrRefCount* r)
{
	LmiAtomicIntegerIncrement(&r->weakCount);
}


LMI_INLINE LmiBool LmiSharedPtrRefCountDecWeakCount(LmiSharedPtrRefCount* r)
{
	LmiInt newVal;
	newVal = LmiAtomicIntegerDecrement(&r->weakCount);
	LmiAssert(newVal >= 0);
	return (newVal == 0);
}


DefineInline_LmiSharedPtrFuncs_Internal(void, LMI_INLINE)
DefineInline_LmiSharedPtrFuncs_PublicBase(void, LMI_INLINE)
DefineInline_LmiWeakPtrFuncs_Internal(void, LMI_INLINE)
DefineInline_LmiWeakPtrFuncs_PublicBase(void, LMI_INLINE)
