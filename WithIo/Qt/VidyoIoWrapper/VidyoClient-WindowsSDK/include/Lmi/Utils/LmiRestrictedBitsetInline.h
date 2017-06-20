/**
   {file:
     {name: LmiRestrictedBitsetInline.h}
     {description: Inline functions for LmiRestrictedBitset.}
     {copyright:
     	(c) 2008-2016 Vidyo, Inc.,
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

/** {implementation: {name: LmiRestrictedBitsetConstruct}} */
LMI_INLINE LmiRestrictedBitset* LmiRestrictedBitsetConstruct(LmiRestrictedBitset * b)
{
	*b = (LmiRestrictedBitset)0;
	return b;
}

/** {implementation: {name: LmiRestrictedBitsetConstructWithOneValue}} */
LMI_INLINE LmiRestrictedBitset* LmiRestrictedBitsetConstructWithOneValue(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v)
{
	*b = v;
	return b;
}

/** {implementation: {name: LmiRestrictedBitsetDestruct}} */
LMI_INLINE void LmiRestrictedBitsetDestruct(LmiRestrictedBitset * b)
{
	/* Nothing to do */
	return;
}

/** {implementation: {name: LmiRestrictedBitsetValueInRange}} */
LMI_INLINE LmiBool LmiRestrictedBitsetValueInRange(LmiInt n)
{
	return (n >= 0 && n < 64);
}


/** {implementation: {name: LmiRestrictedBitsetSet}} */
LMI_INLINE LmiBool LmiRestrictedBitsetSet(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v)
{
	*b |= v;

	return LMI_TRUE;
}


/** {implementation: {name: LmiRestrictedBitsetSetAll}} */
LMI_INLINE void LmiRestrictedBitsetSetAll(LmiRestrictedBitset * b)
{
	*b = LMI_RESTRICTEDBITSET_VALUE_ALL;
}


/** {implementation: {name: LmiRestrictedBitsetClear}} */
LMI_INLINE LmiBool LmiRestrictedBitsetClear(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v)
{
	*b &= ~v;

	return LMI_TRUE;
}


/** {implementation: {name: LmiRestrictedBitsetClearAll}} */
LMI_INLINE void LmiRestrictedBitsetClearAll(LmiRestrictedBitset * b)
{
	*b = (LmiRestrictedBitset)0;
}


/** {implementation: {name: LmiRestrictedBitsetInvert}} */
LMI_INLINE void LmiRestrictedBitsetInvert(LmiRestrictedBitset * b)
{
	*b = ~*b;
}


/** {implementation: {name: LmiRestrictedBitsetInvert}} */
LMI_INLINE void LmiRestrictedBitsetIntersect(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v)
{
	*b &= v;
}


/** {implementation: {name: LmiRestrictedBitsetIsSet}} */
LMI_INLINE LmiBool LmiRestrictedBitsetIsSet(const LmiRestrictedBitset * b, LmiRestrictedBitsetValue v)
{
	return (*b & v) != 0;
}


/** {implementation: {name: LmiRestrictedBitsetContains}} */
LMI_INLINE LmiBool LmiRestrictedBitsetContains(const LmiRestrictedBitset * b, LmiRestrictedBitsetValue v)
{
	return (*b & v) == v;
}


/** {implementation: {name: LmiRestrictedBitsetIsEmpty}} */
LMI_INLINE LmiBool LmiRestrictedBitsetIsEmpty(const LmiRestrictedBitset * b)
{
	return *b == 0;
}


/** {implementation: {name: LmiRestrictedBitsetValueValidMask}} */
LMI_INLINE LmiBool LmiRestrictedBitsetValueValidMask(LmiRestrictedBitsetValue v,
	LmiRestrictedBitsetValue mask)
{
	LmiRestrictedBitset mask_complement = ~mask;
	LmiRestrictedBitset v_mask_bits = (v & mask_complement);

	return (v_mask_bits == mask_complement || v_mask_bits == 0);
}


/** {implementation: {name: LmiRestrictedBitsetValueFindFirst}} */
LMI_INLINE LmiInt LmiRestrictedBitsetValueFindFirst(LmiRestrictedBitsetValue v)
{
	/* We could add a configure test for ffsll, but I don't think it's that
	   common. */
	LmiInt i;
	if (v == 0) return -1;

	for (i = 0; ; i++) {
		if ((LmiRestrictedBitsetValueGet(i) & v) != 0) {
			return i;
		}
	}
	/* NOTREACHED */
}


/** {implementation: {name: LmiRestrictedBitsetValueFindNth}} */
LMI_INLINE LmiInt LmiRestrictedBitsetValueFindNth(LmiRestrictedBitsetValue v, LmiInt n)
{
	LmiInt i;
	if (v == 0) return -1;

	for (i = 0; i <= LMI_RESTRICTEDBITSET_MAXVALUE; i++) {
		if ((LmiRestrictedBitsetValueGet(i) & v) != 0) {
			if (n == 0)
				return i;
			n--;
		}
	}
	return -1;
}


/** {implementation: {name: LmiRestrictedBitsetValueCountSetBits}} */
LMI_INLINE LmiInt LmiRestrictedBitsetValueCountSetBits(LmiRestrictedBitsetValue v)
{
	/* We could add a configure test for __builtin_popcount if it becomes necessary.*/
	LmiInt count;

	/* v & (v - 1) always has exactly one fewer bit set than v. */
	for (count = 0; v != 0; v &= v-1, count++)
		;

	return count;
}


/** {implementation: {name: LmiRestrictedBitsetValueIsExactlyOneValue}} */
LMI_INLINE LmiBool LmiRestrictedBitsetValueIsExactlyOneValue(LmiRestrictedBitsetValue v)
{
	return (v != 0 && (v & (v-1)) == 0);
}
