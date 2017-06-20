/** 
{file:
	{name: LmiConfigWin7MsVisualC14.h}
	{description: This file contains only the differences from Visual Studio 2013 (v12).}
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
#ifndef LMI_CONFIG_WIN7_MS_VISUAL_C_14_H_
#define LMI_CONFIG_WIN7_MS_VISUAL_C_14_H_

/* Only the differences from Visual Studio 2013 (v12). Note there was no v13. */
#include <Lmi/Utils/SysDep/LmiConfigWinXPMsVisualC12.h>

/* LMI - Define to 1 if the system has the type `char16_t'. */
/* #undef LMI_HAVE_CHAR16_T */
#define LMI_HAVE_CHAR16_T 1

/* LMI - Define to 1 if the system has the type `char32_t'. */
/* #undef LMI_HAVE_CHAR32_T */
#define LMI_HAVE_CHAR32_T 1

/* LMI - Define to 1 if you have the <uchar.h> header file. */
#define LMI_HAVE_UCHAR_H 1

#endif /* LMI_CONFIG_WIN7_MS_VISUAL_C_14_H_ */
