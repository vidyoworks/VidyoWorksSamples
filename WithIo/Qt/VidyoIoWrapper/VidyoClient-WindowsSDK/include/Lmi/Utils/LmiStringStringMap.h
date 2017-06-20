/**
{file:
	{name: LmiStringStringMap.h}
	{description: Contains definitions for an map of (String, String) tuples.}
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
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

#ifndef LMI_STRINGSTRINGMAP_H
#define LMI_STRINGSTRINGMAP_H

#include <Lmi/Utils/LmiUnorderedStringStringMap.h>
#include <Lmi/Utils/LmiMap.h>

LMI_BEGIN_EXTERN_C

Declare_LmiMapWithoutPair(LmiString,LmiString)
Declare_LmiMultimapWithoutPair(LmiString, LmiString)

LMI_END_EXTERN_C

#endif /* LMI_STRINGSTRINGMAP_H */
