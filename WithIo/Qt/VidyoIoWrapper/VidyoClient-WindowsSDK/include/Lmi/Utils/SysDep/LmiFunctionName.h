/** {file:
      {name: LmiFunctionName.h}
      {description: File that portably defines the LMI_FUNCTION macro.}
      {copyright:
      	(c) 2006 Vidyo, Inc.,
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

#ifndef LMI_FUNCTION_NAME_H_
#define LMI_FUNCTION_NAME_H_

/* Figure out how to get the name of the current function, if possible. */
#if __STDC_VERSION__ >= 199901L
#define LMI_FUNCTION __func__

#elif defined(__GNUC__)
#define LMI_FUNCTION __FUNCTION__

#elif defined(_MSC_VER)
#if (_MSC_VER < 1300)
#define LMI_FUNCTION __FILE__
#else
#define LMI_FUNCTION __FUNCTION__
#endif

/* Add defines for additional compiler function name support here. */
#else
/* No support available. */
#define LMI_FUNCTION ""
#define LMI_FUNCTION_NAME_UNAVAILABLE

#endif

#endif /* LMI_FUNCTION_NAME_H_ */

