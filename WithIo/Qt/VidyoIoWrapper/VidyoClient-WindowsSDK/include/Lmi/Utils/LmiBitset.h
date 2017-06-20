/**
   {file:
     {name: LmiBitset.h}
     {description: Functions to maintain a set of numbered bits.}
     {copyright:
     	(c) 2005-2012 Vidyo, Inc.,
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

#ifndef LMI_BITSET_H_
#define LMI_BITSET_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiVector.h>

LMI_BEGIN_EXTERN_C



typedef LmiUint64 LmiBitsetItem;
Declare_LmiBasicType(LmiBitsetItem)
Declare_LmiVector(LmiBitsetItem)

#define LMI_BITSET_ITEM_BITS ((LmiSizeT)64)
#define LMI_BITSET_ITEM_MASK ((LmiSizeT)0x3f)
#define LMI_BITSET_ITEM_SHIFT 6


/**
   {type visibility="private":
     {name: LmiBitset}
     {parent: Utils}
     {include: Lmi/Utils/LmiBitset.h}
     {description: A set of bits.}
   }
*/
typedef struct
{
	LmiVector(LmiBitsetItem) items;
} LmiBitset;


/**
   {function visibility="private":
     {name: LmiBitsetConstruct}
     {parent: LmiBitset}
     {description: Construct (initialize) an LmiBitset with all bits zero.}
     {prototype: LmiBitset* LmiBitsetConstruct(LmiBitset* b, LmiAllocator* a)}
     {parameter:
       {name: b}
       {description: The bitset to construct.}}
	 {parameter:
	   {name: a}
	   {description: An allocator for the bitset.}}
     {return: b on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiBitset* LmiBitsetConstruct(LmiBitset * b, LmiAllocator* a);


/**
   {function visibility="private":
     {name: LmiBitsetConstructCopy}
     {parent: LmiBitset}
     {description: Construct (initialize) an LmiBitset as a copy of another one.}
     {prototype: LmiBitset* LmiBitsetConstructCopy(LmiBitset* b, const LmiBitset* orig)}
     {parameter:
       {name: b}
       {description: The bitset to construct.}}
	 {parameter:
	   {name: orig}
	   {description: A bitset to copy.}}
     {return: b on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiBitset* LmiBitsetConstructCopy(LmiBitset * b, const LmiBitset* orig);


/**
   {function visibility="private":
     {name: LmiBitsetConstructWithOneValue}
     {parent: LmiBitset}
     {description: Construct (initialize) an LmiBitset with one bit set.}
     {prototype: LmiBitset* LmiBitsetConstructWithOneValue(LmiBitset* b, LmiSizeT v, LmiAllocator* a)}
     {parameter:
       {name: b}
       {description: The bitset to construct.}}
     {parameter:
       {name: v}
       {description: The initial bitset value.}}
	 {parameter:
	   {name: a}
	   {description: An allocator for the bitset.}}
     {return: b on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiBitset* LmiBitsetConstructWithOneValue(LmiBitset * b, LmiSizeT v, LmiAllocator *a);


/**
   {function visibility="private":
     {name: LmiBitsetDestruct}
     {parent: LmiBitset}
     {description: Destruct an LmiBitset.}
     {prototype: void LmiBitsetDestruct(LmiBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset to destruct.}}
   }
*/
LMI_INLINE_DECLARATION void LmiBitsetDestruct(LmiBitset * b);


/**
   {function visibility="private":
     {name: LmiBitsetAssign}
     {parent: LmiBitset}
     {description: Assign the value of an LmiBitset as a copy of another one.}
     {prototype: LmiBitset* LmiBitsetAssign(LmiBitset* b, const LmiBitset* orig)}
     {parameter:
       {name: b}
       {description: The bitset to be assigned.}}
	 {parameter:
	   {name: orig}
	   {description: A bitset to copy.}}
     {return: b on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiBitset* LmiBitsetAssign(LmiBitset * b, const LmiBitset* orig);



/**
   {function visibility="private":
     {name: LmiBitsetSet}
     {parent: LmiBitset}
     {description: Set a bit in an LmiBitset.}
     {prototype: LmiBool LmiBitsetSet(LmiBitset* b, LmiSizeT v)}
     {parameter:
       {name: b}
       {description: The bitset in which to set a bit.}}
     {parameter:
       {name: v}
       {description: The bit to set.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiBitsetSet(LmiBitset * b, LmiSizeT v);


/**
   {function visibility="private":
     {name: LmiBitsetReserve}
     {parent: LmiBitset}
     {description: Reserve memory in an LmiBitset.}
     {prototype: LmiBool LmiBitsetReserve(LmiBitset* b, LmiSizeT capacity)}
     {parameter:
       {name: b}
       {description: The bitset in which to reserve capacity.}}
     {parameter:
       {name: capacity}
       {description: The requested capacity.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiBitsetReserve(LmiBitset * b, LmiSizeT capacity);


/**
   {function visibility="private":
     {name: LmiBitsetSetMultiple}
     {parent: LmiBitset}
     {description: Set multiple bits in an LmiBitset.}
     {prototype: LmiBool LmiBitsetSetMultiple(LmiBitset* b, const LmiBitset* toSet)}
     {parameter:
       {name: b}
       {description: The bitset in which to set a bit.}}
     {parameter:
       {name: toSet}
       {description: A bitset containing the bits to set.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiBitsetSetMultiple(LmiBitset * b, const LmiBitset* toSet);


/**
   {function visibility="private":
     {name: LmiBitsetSetRange}
     {parent: LmiBitset}
     {description: Set a range of bits in an LmiBitset.}
     {prototype: LmiBool LmiBitsetSetRange(LmiBitset* b, LmiSizeT low, LmiSizeT high)}
     {parameter:
       {name: b}
       {description: The bitset in which to set a range of bits.}}
     {parameter:
       {name: low}
       {description: The lowest bit index (inclusive) to set.}}
     {parameter:
       {name: high}
       {description: The highest bit index (exclusive) to set.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiBitsetSetRange(LmiBitset * b, LmiSizeT low, LmiSizeT high);


/**
   {function visibility="private":
     {name: LmiBitsetClear}
     {parent: LmiBitset}
     {description: Clear a bit in an LmiBitset.}
     {prototype: LmiBool LmiBitsetClear(LmiBitset* b, LmiSizeT v)}
     {parameter:
       {name: b}
       {description: The bitset in which to clear a bit.}}
     {parameter:
       {name: v}
       {description: The bit to clear.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiBitsetClear(LmiBitset * b, LmiSizeT v);


/**
   {function visibility="private":
     {name: LmiBitsetClearMultiple}
     {parent: LmiBitset}
     {description: Clear multiple bits in an LmiBitset.}
     {prototype: LmiBool LmiBitsetClearMultiple(LmiBitset* b, const LmiBitset* toClear)}
     {parameter:
       {name: b}
       {description: The bitset in which to clear a bit.}}
     {parameter:
       {name: toClear}
       {description: A bitset containing the bits to clear.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiBitsetClearMultiple(LmiBitset * b, const LmiBitset* toClear);


/**
   {function visibility="private":
     {name: LmiBitsetClearAll}
     {parent: LmiBitset}
     {description: Clear all bits in an LmiBitset.}
     {prototype: void LmiBitsetClearAll(LmiBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset in which to clear all the bits.}}
   }
*/
void LmiBitsetClearAll(LmiBitset * b);


/**
   {function visibility="private":
     {name: LmiBitsetIntersect}
     {parent: LmiBitset}
     {description: Intersect a bitset with another one.}
     {prototype: LmiBool LmiBitsetIntersect(LmiBitset* b, const LmiBitset* toIntersect)}
     {parameter:
       {name: b}
       {description: The bitset to intersect.}}
     {parameter:
       {name: toIntersect}
       {description: The bitset to be intersected with.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiBitsetIntersect(LmiBitset * b, const LmiBitset* toIntersect);


/**
   {function visibility="private":
     {name: LmiBitsetIsSet}
     {parent: LmiBitset}
     {description: Test a bit in an LmiBitset.}
     {prototype: LmiBool LmiBitsetIsSet(const LmiBitset* b, LmiSizeT v)}
     {parameter:
       {name: b}
       {description: The bitset in which to test some bits.}}
     {parameter:
       {name: v}
       {description: The bit to test.}}
     {return: LMI_TRUE if the bit v is set, LMI_FALSE if not.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiBitsetIsSet(const LmiBitset * b, LmiSizeT v);


/**
   {function visibility="private":
     {name: LmiBitsetContains}
     {parent: LmiBitset}
     {description: Test a set of bits in an LmiBitset.}
     {prototype: LmiBool LmiBitsetContains(const LmiBitset* b, const LmiBitset* toTest)}
     {parameter:
       {name: b}
       {description: The bitset in which to test a set of bits.}}
     {parameter:
       {name: toTest}
       {description: The set of bits.}}
     {return: LMI_TRUE if all the bits in toTest are set in b,
       LMI_FALSE if not.}
   }
*/
LmiBool LmiBitsetContains(const LmiBitset * b, const LmiBitset* toTest);

/**
   {function visibility="private":
     {name: LmiBitsetIsEmpty}
     {parent: LmiBitset}
     {description: Test whether any bit is set in an LmiBitset.}
     {prototype: LmiBool LmiBitsetIsEmpty(const LmiBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset in which to test any bits.}}
     {return: LMI_TRUE if no bits are set in the bitset, LMI_FALSE if at least
	   one bit is set.}
   }
*/
LmiBool LmiBitsetIsEmpty(const LmiBitset * b);


/**
   {function visibility="private":
     {name: LmiBitsetValidMask}
     {parent: LmiBitset}
     {description: Given a bitset, and a mask of valid values
       for that bitset, confirm all the bits not in the mask, through max,
	   are either all set or all cleared.}
     {prototype: LmiBool LmiBitsetValidMask(const LmiBitset* b, const LmiBitset* mask, LmiSizeT max)}
     {parameter:
       {name: b}
       {description: The bitset to test.}}
     {parameter:
       {name: mask}
       {description: The mask of valid values.}}
     {parameter:
       {name: max}
       {description: The maximum bit position (exclusive) to test.}}
     {return: LMI_TRUE if all the bits in b (less than max) that are not set in mask are either all set or all clear.}
    }
*/
LmiBool LmiBitsetValidMask(const LmiBitset* b, const LmiBitset* mask, LmiSizeT max);


/**
   {function visibility="private":
     {name: LmiBitsetGetAllocator}
     {parent: LmiBitset}
     {description: Get a pointer to a bitset\'s allocator.}
     {prototype: LmiAllocator* LmiBitsetGetAllocator(const LmiBitset* b)}
     {parameter:
       {name: b}
       {description: The bitset.}}
     {return: A pointer to the bitset\'s allocator.}
    }
*/
LMI_INLINE_DECLARATION LmiAllocator* LmiBitsetGetAllocator(const LmiBitset* b);


/* Internal */
LMI_INLINE_DECLARATION LmiBitsetItem LmiBitsetGetItemConst_(const LmiBitset* b, LmiSizeT itemIdx);


LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiBitsetInline.h>
#endif

#endif /* LMI_BITSET_H_ */
