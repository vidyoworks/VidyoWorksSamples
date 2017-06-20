/** 
{file:
	{name: LmiConfigMacOS10XcodeX86_64.h}
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
#ifndef LMI_CONFIG_MAC_OS10_XCODE_X86_64_H_
#define LMI_CONFIG_MAC_OS10_XCODE_X86_64_H_

/* Lmi/Utils/SysDep/LmiConfigMacOS10XcodeX86_64.h.  Similar to the Intel
 * 32-bit version.  This file contains only the changes. */
#include <Lmi/Utils/SysDep/LmiConfigMacOS10Xcode.h>

/* LMI - Define to 1 if va_list is assignable. */
#undef LMI_HAVE_ASSIGNABLE_VA_LIST

/* LMI - The size of a `long', as computed by sizeof. */
#undef LMI_SIZEOF_LONG
#define LMI_SIZEOF_LONG 8

/* LMI - The size of a `unsigned long', as computed by sizeof. */
#undef LMI_SIZEOF_UNSIGNED_LONG
#define LMI_SIZEOF_UNSIGNED_LONG 8

/* LMI - The size of a `void *', as computed by sizeof. */
#undef LMI_SIZEOF_VOID_P
#define LMI_SIZEOF_VOID_P 8

#endif /* LMI_CONFIG_MAC_OS10_XCODE_X86_64_H_ */
