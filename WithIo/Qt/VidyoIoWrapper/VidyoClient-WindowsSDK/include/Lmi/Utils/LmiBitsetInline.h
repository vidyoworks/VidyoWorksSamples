/**
   {file:
     {name: LmiBitsetInline.h}
     {description: Inline functions for LmiBitset.}
     {copyright:
     	(c) 2005-2008 Vidyo, Inc.,
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

/** {implementation: {name: LmiBitsetConstruct}} */
LMI_INLINE LmiBitset* LmiBitsetConstruct(LmiBitset * b, LmiAllocator* a)
{
	if (LmiVectorConstructDefault(LmiBitsetItem)(&b->items, a) == NULL)
		return NULL;
	return b;
}


/** {implementation: {name: LmiBitsetConstructCopy}} */
LMI_INLINE LmiBitset* LmiBitsetConstructCopy(LmiBitset * b, const LmiBitset * orig)
{
	if (LmiVectorConstructCopy(LmiBitsetItem)(&b->items, &orig->items) == NULL)
		return NULL;
	return b;
}


/** {implementation: {name: LmiBitsetDestruct}} */
LMI_INLINE void LmiBitsetDestruct(LmiBitset * b)
{
	LmiVectorDestruct(LmiBitsetItem)(&b->items);
}


/** {implementation: {name: LmiBitsetConstructCopy}} */
LMI_INLINE LmiBitset* LmiBitsetAssign(LmiBitset * b, const LmiBitset * orig)
{
	if (LmiVectorAssign(LmiBitsetItem)(&b->items, &orig->items) == NULL)
		return NULL;
	return b;
}


/** {implementation: {name: LmiBitsetConstructWithOneValue}} */
LMI_INLINE LmiBitset* LmiBitsetConstructWithOneValue(LmiBitset * b, LmiSizeT v, LmiAllocator *a)
{
	if (LmiBitsetConstruct(b, a) == NULL)
		return NULL;
	if (!LmiBitsetSet(b, v)) {
		LmiBitsetDestruct(b);
		return NULL;
	}
	return b;
}

LMI_INLINE LmiBitsetItem LmiBitsetGetItemConst_(const LmiBitset* b, LmiSizeT itemIdx)
{
	if (itemIdx >= LmiVectorSize(LmiBitsetItem)(&b->items)) {
		return 0;
	}

	return *LmiVectorAtConst(LmiBitsetItem)(&b->items, itemIdx);
}


/** {implementation: {name: LmiBitsetIsSet}} */
LMI_INLINE LmiBool LmiBitsetIsSet(const LmiBitset * b, LmiSizeT v)
{
	LmiSizeT itemIdx = v >> LMI_BITSET_ITEM_SHIFT;
	LmiSizeT bitIdx = v & LMI_BITSET_ITEM_MASK;
	LmiBitsetItem valueMask = (LmiBitsetItem)1 << bitIdx;

	return (LmiBitsetGetItemConst_(b, itemIdx) & valueMask) != 0;
}


/** {implementation: {name: LmiBitsetGetAllocator}} */
LMI_INLINE LmiAllocator* LmiBitsetGetAllocator(const LmiBitset* b)
{
	return LmiVectorGetAllocator(LmiBitsetItem)(&b->items);
}
