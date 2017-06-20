/** 
{file:
	{name: LmiConfigWindowsPhone81MsVisualC12ARM.h}
	{description: N/A}
    {copyright:
    	(c) 2014-2016 Vidyo, Inc.,
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
#ifndef LMI_CONFIG_WINDOWS_PHONE_8_1_MS_VISUAL_C_12_ARM_H_
#define LMI_CONFIG_WINDOWS_PHONE_8_1_MS_VISUAL_C_12_ARM_H_

/* Lmi/Utils/SysDep/LmiConfigWindowsPhone81MsVisualC12ARM.h.  Similar to Windows Phone 8.1 on X86,
   with minor differences.  This file contains only the changes. */
#include <Lmi/Utils/SysDep/LmiConfigWindowsPhone81MsVisualC12X86.h>

/* LMI - Define to 1 if you have the <arm_neon.h> header file. */
#define LMI_HAVE_ARM_NEON_H 1

/* LMI - Define to 1 if you have the <emmintrin.h> header file. */
#undef LMI_HAVE_EMMINTRIN_H

/* LMI - Define to 1 if you have the <immintrin.h> header file. */
#undef LMI_HAVE_IMMINTRIN_H

/* LMI - Define to 1 if you have the <nmmintrin.h> header file. */
#undef LMI_HAVE_NMMINTRIN_H

/* LMI - Define to 1 if you have the <smmintrin.h> header file. */
#undef LMI_HAVE_SMMINTRIN_H

/* LMI - Define to 1 if you have the <tmmintrin.h> header file. */
#undef LMI_HAVE_TMMINTRIN_H

/* LMI - Define to 1 if you have the <wmmintrin.h> header file. */
#undef LMI_HAVE_WMMINTRIN_H

/* LMI - Define to 1 if you have the <xmmintrin.h> header file. */
#undef LMI_HAVE_XMMINTRIN_H

/* LMI - Define to 1 to assume NEON support for CPU-optimized functions */
#define LMI_OPTFNS_ASSUME_NEON 1

/* LMI - Define to 1 to assume SSE support for CPU-optimized functions */
#undef LMI_OPTFNS_ASSUME_SSE

#ifndef /* LMI_CONFIG_WINDOWS_PHONE_8_1_MS_VISUAL_C_12_ARM_H_ */
