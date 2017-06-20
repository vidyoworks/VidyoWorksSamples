/** {file:
	  {name: LmiAlignedAllocatorInline.h}
	  {description: Inline functions for LmiAlignedAllocator.}
	  {copyright:
	  	(c) 2008 Vidyo, Inc.,
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

/** {implementation: {name: LmiAlignedAllocatorGetBase}} */
LMI_INLINE LmiAllocator *LmiAlignedAllocatorGetBase(LmiAlignedAllocator *a)
{
    return &a->base;
}

/** {implementation: {name: LmiAlignedAllocatorGetAllocator}} */
LMI_INLINE LmiAllocator *LmiAlignedAllocatorGetAllocator(LmiAlignedAllocator *x) 
{
	return (x->a);
}

/** {implementation: {name: LmiAlignedAllocatorGetMaxSize}} */
LMI_INLINE LmiSizeT LmiAlignedAllocatorGetMaxSize(const LmiAlignedAllocator *x) 
{
	return LMI_SIZE_T_MAX - x->alignment;
}

/** {implementation: {name: LmiAlignedAllocatorGetAlignment}} */
LMI_INLINE LmiUint8 LmiAlignedAllocatorGetAlignment(const LmiAlignedAllocator *x) 
{
	return x->alignment;
}

