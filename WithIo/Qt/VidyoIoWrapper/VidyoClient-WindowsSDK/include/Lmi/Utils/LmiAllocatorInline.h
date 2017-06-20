/** {file:
	  {name: LmiAllocatorInline.h}
	  {description: Inline functions for LmiAllocator.}
	  {copyright:
	  	(c) 2005-2009 Vidyo, Inc.,
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

/** {implementation: {name: LmiAllocatorGetUserData}} */
LMI_INLINE LmiVoidPtr LmiAllocatorGetUserData(LmiAllocator* a)
{
  return a->userData;
}


/** {implementation: {name: LmiAllocatorAllocate}} */
LMI_INLINE LmiVoidPtr LmiAllocatorAllocate(LmiAllocator * a_, LmiSizeT s_)
{
  return a_->allocate(a_, s_);
}


/** {implementation: {name: LmiAllocatorDeallocate}} */
LMI_INLINE void LmiAllocatorDeallocate(LmiAllocator * a_, LmiVoidPtr p_, LmiSizeT s_)
{
  a_->deallocate(a_, p_, s_);
}


/** {implementation: {name: LmiAllocatorGetMaxSize}} */
LMI_INLINE LmiSizeT LmiAllocatorGetMaxSize(const LmiAllocator * a_)
{
  return a_->maxSize;
}
