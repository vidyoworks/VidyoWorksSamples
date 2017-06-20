/**
   {file:
     {name: LmiRestrictedBitset.h}
     {description: Functions to maintain a limited-size set of numbered bits.}
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

#ifndef LMI_RESTRICTED_BITSET_H_
#define LMI_RESTRICTED_BITSET_H_

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
   {type visibility="private":
     {name: LmiRestrictedBitset}
     {parent: Utils}
     {include: Lmi/Utils/LmiRestrictedBitset.h}
     {description: A limited-size set of bits.}
     {note: Only supports 64 distinct values.}
	 {note: The maximum value allowed in an LmiRestrictedBitset is given by the constant
	   LMI_RESTRICTEDBITSET_MAXVALUE, currently 63.}
	 {note: See also LmiExtendedBitset.}
   }
*/
typedef LmiUint64 LmiRestrictedBitset;

#define LMI_RESTRICTEDBITSET_MAXVALUE 63

/**
   {type visibility="private":
     {name: LmiRestrictedBitsetValue}
     {parent: LmiRestrictedBitset}
     {description: A value or set of values from an LmiRestrictedBitset.}
     {value:
       {name: LMI_RESTRICTEDBITSET_VALUE_NONE}
       {description: A bitset value with all bits false.}}
     {value:
       {name: LMI_RESTRICTEDBITSET_VALUE_ALL}
       {description: A bitset value with all bits true.}}
     {note: Bitset values may be or\'d together.}
   }
*/
typedef LmiUint64 LmiRestrictedBitsetValue;


#define LMI_RESTRICTEDBITSET_VALUE_NONE ((LmiRestrictedBitsetValue)0)
#define LMI_RESTRICTEDBITSET_VALUE_ALL  (~(LmiRestrictedBitsetValue)0)


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetValueGet}
     {parent: LmiRestrictedBitsetValue}
     {description: Given a value N, return the corresponding LmiRestrictedBitsetValue
       {code: (LmiRestrictedBitsetValue)1 << N}.}
     {prototype: LmiRestrictedBitsetValue LmiRestrictedBitsetValueGet(LmiInt n)}
     {parameter:
       {name: n}
       {description: The value to set.}}
     {return: {code: (LmiRestrictedBitsetValue)1 << N}.}
     {note: This is implemented as a macro, so it can be used in static
       initializers.}
     {note: This is undefined if !LmiRestrictedBitsetValueInRange(n).}
   }
*/
#define LmiRestrictedBitsetValueGet(n) ((LmiRestrictedBitsetValue)1 << (n))


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetValueInRange}
     {parent: LmiRestrictedBitsetValue}
     {description: Test whether a bit number is in range of an LmiRestrictedBitsetValue.}
     {prototype: LmiBool LmiRestrictedBitsetValueInRange(LmiInt n)}
     {parameter:
       {name: n}
       {description: The bit number to test for validity.}}
     {return: LMI_TRUE if the bit number is in the valid range of a set,
       LMI_FALSE otherwise.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetValueInRange(LmiInt n);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetValueFindFirst}
     {parent: LmiRestrictedBitsetValue}
     {description: Find the first (lowest-numbered) bit set in a value mask,
       or -1 if no bit is set.}
     {prototype: LmiInt LmiRestrictedBitsetValueFindFirst(LmiRestrictedBitsetValue v)}
     {parameter:
       {name: v}
       {description: The bitset value mask from which to find the first value.}}
     {return: The position of the lowest-numbered bit set, counting from 0,
       or -1 if no bits are set.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiRestrictedBitsetValueFindFirst(LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetValueFindNth}
     {parent: LmiRestrictedBitsetValue}
     {description: Find the nth (lowest-numbered) bit set in a value mask,
       or -1 if no such bit is set.}
     {prototype: LmiInt LmiRestrictedBitsetValueFindNth(LmiRestrictedBitsetValue v, LmiInt n)}
     {parameter:
       {name: v}
       {description: The bitset value mask from which to find the nth value.}}
     {parameter:
       {name: n}
       {description: The count of the position to find.}}
     {return: The position of the lowest-numbered bit set, counting from 0,
       or -1 if no such bits is set.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiRestrictedBitsetValueFindNth(LmiRestrictedBitsetValue v, LmiInt n);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetValueCountBits}
     {parent: LmiRestrictedBitsetValue}
     {description: Return a count of the number of bits set in a value mask.}
     {prototype: LmiInt LmiRestrictedBitsetValueCountBits(LmiRestrictedBitsetValue v)}
     {parameter:
       {name: v}
       {description: The bitset value mask from which to count the set bits.}}
     {return: The number of set bits in the bitset.}
   }
*/
LmiInt LmiRestrictedBitsetValueCountBits(LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetValueIsExactlyOneValue}
     {parent: LmiRestrictedBitsetValue}
     {description: Check whether a bitset value has exactly one bit set.}
     {prototype: LmiBool LmiRestrictedBitsetValueIsExactlyOneValue(LmiRestrictedBitsetValue v)}
     {parameter:
       {name: v}
       {description: The bitset value mask for which to query for exactly one
         value.}}
     {return: LMI_TRUE if exactly one bit is set, else LMI_FALSE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetValueIsExactlyOneValue(LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetValueValidMask}
     {parent: LmiRestrictedBitsetValue}
     {description: Given a bitset value mask, and a mask of valid values
       for that bitset, confirm all the bits not in the mask are either
       all set or all cleared.}
     {prototype: LmiBool LmiRestrictedBitsetValueValidMask(LmiRestrictedBitsetValue v, LmiRestrictedBitsetValue mask)}
     {parameter:
       {name: v}
       {description: The value mask to test.}}
     {parameter:
       {name: mask}
       {description: The mask of valid values.}}
     {return: LMI_TRUE if all the bits in v that are not set in mask are either all set, or all clear.}
    }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetValueValidMask(LmiRestrictedBitsetValue v, LmiRestrictedBitsetValue mask);

/**
   {function visibility="private":
     {name: LmiRestrictedBitsetConstruct}
     {parent: LmiRestrictedBitset}
     {description: Construct (initialize) an LmiRestrictedBitset with all bits zero.}
     {prototype: LmiRestrictedBitset* LmiRestrictedBitsetConstruct(LmiRestrictedBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset to construct.}}
     {return: b on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiRestrictedBitset* LmiRestrictedBitsetConstruct(LmiRestrictedBitset * b);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetConstructWithOneValue}
     {parent: LmiRestrictedBitset}
     {description: Construct (initialize) an LmiRestrictedBitset with one bit set.}
     {prototype: LmiRestrictedBitset* LmiRestrictedBitsetConstructWithOneValue(LmiRestrictedBitset* b, LmiRestrictedBitsetValue v)}
     {parameter:
       {name: b}
       {description: The bitset to construct.}}
     {parameter:
       {name: v}
       {description: The initial bitset value.}}
     {return: b on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiRestrictedBitset* LmiRestrictedBitsetConstructWithOneValue(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetDestruct}
     {parent: LmiRestrictedBitset}
     {description: Destruct an LmiRestrictedBitset.}
     {prototype: void LmiRestrictedBitsetDestruct(LmiRestrictedBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset to destruct.}}
   }
*/
LMI_INLINE_DECLARATION void LmiRestrictedBitsetDestruct(LmiRestrictedBitset * b);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetSet}
     {parent: LmiRestrictedBitset}
     {description: Set some bits in an LmiRestrictedBitset.}
     {prototype: LmiBool LmiRestrictedBitsetSet(LmiRestrictedBitset* b, LmiRestrictedBitsetValue v)}
     {parameter:
       {name: b}
       {description: The bitset in which to set a bit.}}
     {parameter:
       {name: v}
       {description: The mask of bits to set.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetSet(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetSetAll}
     {parent: LmiRestrictedBitset}
     {description: Set all bits in an LmiRestrictedBitset.}
     {prototype: void LmiRestrictedBitsetSetAll(LmiRestrictedBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset in which to set all the bits.}}
   }
*/
LMI_INLINE_DECLARATION void LmiRestrictedBitsetSetAll(LmiRestrictedBitset * b);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetClear}
     {parent: LmiRestrictedBitset}
     {description: Clear some bits in an LmiRestrictedBitset.}
     {prototype: LmiBool LmiRestrictedBitsetClear(LmiRestrictedBitset* b, LmiRestrictedBitsetValue v)}
     {parameter:
       {name: b}
       {description: The bitset in which to clear a bit.}}
     {parameter:
       {name: v}
       {description: The mask of bits to clear.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetClear(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v);

/**
   {function visibility="private":
     {name: LmiRestrictedBitsetClearAll}
     {parent: LmiRestrictedBitset}
     {description: Clear all bits in an LmiRestrictedBitset.}
     {prototype: void LmiRestrictedBitsetClearAll(LmiRestrictedBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset in which to clear all the bits.}}
   }
*/
LMI_INLINE_DECLARATION void LmiRestrictedBitsetClearAll(LmiRestrictedBitset * b);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetIntersect}
     {parent: LmiRestrictedBitset}
     {description: Intersect a bitset with some bitset values.}
     {prototype: void LmiRestrictedBitsetIntersect(LmiRestrictedBitset* b, LmiRestrictedBitsetValue v)}
     {parameter:
       {name: b}
       {description: The bitset to intersect.}}
     {parameter:
       {name: v}
       {description: The value to intersect the bitset with.}}
   }
*/
LMI_INLINE_DECLARATION void LmiRestrictedBitsetIntersect(LmiRestrictedBitset * b, LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetInvert}
     {parent: LmiRestrictedBitset}
     {description: Invert all bits in an LmiRestrictedBitset.}
     {prototype: void LmiRestrictedBitsetInvert(LmiRestrictedBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset in which to invert all the bits.}}
   }
*/
LMI_INLINE_DECLARATION void LmiRestrictedBitsetInvert(LmiRestrictedBitset * b);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetIsSet}
     {parent: LmiRestrictedBitset}
     {description: Test some bits in an LmiRestrictedBitset.}
     {prototype: LmiBool LmiRestrictedBitsetIsSet(const LmiRestrictedBitset* b, LmiRestrictedBitsetValue v)}
     {parameter:
       {name: b}
       {description: The bitset in which to test some bits.}}
     {parameter:
       {name: v}
       {description: The mask of bits to test.}}
     {return: LMI_TRUE if at least one bit in the mask v is set,
       LMI_FALSE if not.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetIsSet(const LmiRestrictedBitset * b, LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetContains}
     {parent: LmiRestrictedBitset}
     {description: Test a set of bits in an LmiRestrictedBitset.}
     {prototype: LmiBool LmiRestrictedBitsetContains(const LmiRestrictedBitset* b, LmiRestrictedBitsetValue v)}
     {parameter:
       {name: b}
       {description: The bitset in which to test a set of bits.}}
     {parameter:
       {name: v}
       {description: The mask of bits to test.}}
     {return: LMI_TRUE if all the bits in the mask v are set,
       LMI_FALSE if not.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetContains(const LmiRestrictedBitset * b, LmiRestrictedBitsetValue v);


/**
   {function visibility="private":
     {name: LmiRestrictedBitsetIsEmpty}
     {parent: LmiRestrictedBitset}
     {description: Test whether any bit is set in an LmiRestrictedBitset.}
     {prototype: LmiBool LmiRestrictedBitsetIsEmpty(const LmiRestrictedBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset in which to test any bits.}}
     {return: LMI_TRUE if no bits are set in the bitset, LMI_FALSE if at least
	   one bit is set.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiRestrictedBitsetIsEmpty(const LmiRestrictedBitset * b);



LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiRestrictedBitsetInline.h>
#endif

#endif /* LMI_RESTRICTED_BITSET_H_ */
