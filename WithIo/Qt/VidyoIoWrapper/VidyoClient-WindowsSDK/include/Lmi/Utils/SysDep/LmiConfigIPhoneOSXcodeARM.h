/** 
{file:
	{name: LmiConfigIPhoneOSXcodeARM.h}
	{description: N/A}
    {copyright:
    	(c) 2010-2016 Vidyo, Inc.,
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
#ifndef LMI_CONFIG_IPHONE_OS_XCODE_ARM_H_
#define LMI_CONFIG_IPHONE_OS_XCODE_ARM_H_

/* Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeARM.h.  Similar to the Intel
 * version.  This file contains only the changes. */
#include <Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeI386.h>

/* LMI - Define to 1 if you have the <arm_neon.h> header file. */
#define LMI_HAVE_ARM_NEON_H 1

/* LMI - Define to 1 if you have the <emmintrin.h> header file. */
#undef LMI_HAVE_EMMINTRIN_H

/* LMI - Define to 1 if you have the <immintrin.h> header file. */
#undef LMI_HAVE_IMMINTRIN_H

/* LMI - Define to 1 if you support AES-NI instructions in inline assembly. */
#undef LMI_HAVE_INLINE_ASM_AESNI

/* LMI - Define to 1 if you have the <netinet/in_var.h> header file. */
#undef LMI_HAVE_NETINET_IN_VAR_H

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

/* LMI - Define to 1 if you have the `_mm256_add_epi32' intrinsic. */
#undef LMI_HAVE__MM256_ADD_EPI32

/* LMI - Define to 1 to assume NEON support for CPU-optimized functions */
#define LMI_OPTFNS_ASSUME_NEON 1

/* LMI - Define to 1 to assume SSE support for CPU-optimized functions */
#undef LMI_OPTFNS_ASSUME_SSE

/* LMI - Define to 1 to assume SSE2 support for CPU-optimized functions */
#undef LMI_OPTFNS_ASSUME_SSE2

/* LMI - Use open SSL in TLS transport plug-in */
#define LMI_USE_OPENSSL

#endif /* LMI_CONFIG_IPHONE_OS_XCODE_ARM_H_ */
