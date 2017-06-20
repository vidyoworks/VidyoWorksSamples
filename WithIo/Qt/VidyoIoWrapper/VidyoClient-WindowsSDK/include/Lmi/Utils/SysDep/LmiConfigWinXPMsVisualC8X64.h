/** 
{file:
	{name: LmiConfigWinXPMsVisualC8X64.h}
	{description: N/A}
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
#ifndef LMI_CONFIG_WINXP_MS_VISUAL_C_8_X64_H_
#define LMI_CONFIG_WINXP_MS_VISUAL_C_8_X64_H_

/* Lmi/Utils/SysDep/LmiConfigWinXPMsVisualC8X64.h.   Similar to Visual C 8 for X86/32,
 * with minor differences.  This file contains only the changes. */
#include <Lmi/Utils/SysDep/LmiConfigWinXPMsVisualC8.h>

/* LMI - Define to 1 to assume SSE2 support for CPU-optimized functions */
#define LMI_OPTFNS_ASSUME_SSE2 1

/* LMI - The size of a `void *', as computed by sizeof. */
#undef LMI_SIZEOF_VOID_P
#define LMI_SIZEOF_VOID_P 8

#endif /* LMI_CONFIG_WINXP_MS_VISUAL_C_8_X64_H_ */
