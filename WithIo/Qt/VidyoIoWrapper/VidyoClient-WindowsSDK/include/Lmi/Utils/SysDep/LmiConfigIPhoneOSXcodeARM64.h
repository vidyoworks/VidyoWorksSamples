/** 
{file:
	{name: LmiConfigIPhoneOSXcodeARM64.h}
	{description: N/A}
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
#ifndef LMI_CONFIG_IPHONE_OS_XCODE_ARM64_H_
#define LMI_CONFIG_IPHONE_OS_XCODE_ARM64_H_

/* Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeARM64.h.  Similar to the ARM
 * 32-bit version.  This file contains only the changes. */
#include <Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeARM.h>

/* LMI - Define to 1 if you have the `vaeseq_u8' function. */
#define LMI_HAVE_VAESEQ_U8 1

/* LMI - Define to 1 to assume ARM Crypt support for CPU-optimized functions
   */
#define LMI_OPTFNS_ASSUME_ARM_CRYPT 1

/* LMI - The size of a `long', as computed by sizeof. */
#undef LMI_SIZEOF_LONG
#define LMI_SIZEOF_LONG 8

/* LMI - The size of a `unsigned long', as computed by sizeof. */
#undef LMI_SIZEOF_UNSIGNED_LONG
#define LMI_SIZEOF_UNSIGNED_LONG 8

/* LMI - The size of a `void *', as computed by sizeof. */
#undef LMI_SIZEOF_VOID_P
#define LMI_SIZEOF_VOID_P 8

#endif /* LMI_CONFIG_IPHONE_OS_XCODE_ARM64_H_ */
