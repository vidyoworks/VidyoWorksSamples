/**
   {file:
     {name: LmiCondition2Inline.h}
     {description: Inline functions for LmiCondition2.}
     {copyright:
     	(c) 2006-2008 Vidyo, Inc.,
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

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAssert.h>
#include <Lmi/Os/LmiLog.h>

LMI_INLINE LmiMutex* LmiCondition2GetMutex_(LmiCondition2* x) {
	return x->mutex;
}

/* High-level API */
LMI_INLINE LmiCondition2* LmiCondition2Construct(LmiCondition2* x, LmiMutex* m) {
	LmiCondition2* r;

	LmiLogEnter(LmiLogMutex_);
	r = LmiCondition2Construct_(x, m);
	LmiLogLeave(LmiLogMutex_);
	return r;
}
LMI_INLINE void LmiCondition2Destruct(LmiCondition2* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiCondition2Destruct_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE LmiMutex* LmiCondition2GetMutex(LmiCondition2* x) {
	LmiMutex* ret;
	LmiLogEnter(LmiLogMutex_);
	ret = LmiCondition2GetMutex_(x);
	LmiLogLeave(LmiLogMutex_);
	return ret;
}
LMI_INLINE LmiInt LmiCondition2GetNumWaiting(LmiCondition2* x) {
	LmiInt ret;
	LmiLogEnter(LmiLogMutex_);
	ret = LmiCondition2GetNumWaiting_(x);
	LmiLogLeave(LmiLogMutex_);
	return ret;
}
LMI_INLINE void LmiCondition2Wait(LmiCondition2* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiCondition2Wait_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE void LmiCondition2Notify(LmiCondition2* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiCondition2Notify_(x);
	LmiLogLeave(LmiLogMutex_);
}
LMI_INLINE void LmiCondition2NotifyAll(LmiCondition2* x) {
	LmiLogEnter(LmiLogMutex_);
	LmiCondition2NotifyAll_(x);
	LmiLogLeave(LmiLogMutex_);
}

