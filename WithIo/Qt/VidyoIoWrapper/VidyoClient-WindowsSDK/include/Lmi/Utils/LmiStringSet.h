/**
{file:
	{name: LmiStringSet.h}
	{description: Declarations for a set (and multiset) of strings.}
	{copyright:
		(c) 2013-2017 Vidyo, Inc.,
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

#ifndef LMI_STRINGSET_H
#define LMI_STRINGSET_H

#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiSet.h>

LMI_BEGIN_EXTERN_C

Declare_LmiSet(LmiString)
Declare_LmiMultiset(LmiString)

LMI_END_EXTERN_C

#endif /* LMI_STRINGSET_H */
