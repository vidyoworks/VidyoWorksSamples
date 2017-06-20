/**
{file:
	{name: LmiUnorderedStringStringMap.h}
	{description: Contains definitions for an unordered map of (String, VoidPtr) tuples.}
	{copyright:
		(c) 2011 Vidyo, Inc.,
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

#ifndef LMI_UNORDEREDSTRINGSTRINGMAP_H
#define LMI_UNORDEREDSTRINGSTRINGMAP_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUnordered.h>
#include <Lmi/Utils/LmiString.h>

LMI_BEGIN_EXTERN_C

Declare_LmiUnorderedMap(LmiString, LmiString)

LMI_END_EXTERN_C

#endif /* LMI_UNORDEREDSTRINGSTRINGMAP_H */
