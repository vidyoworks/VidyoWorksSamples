/**
{file:
	{name: LmiMacFunction.h}
	{description: }
	{copyright:
		(c) 2008 Vidyo, Inc.,
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

#define LMI_MACFUNCTION_BEGIN NSAutoreleasePool *_p_o_o_l = [[NSAutoreleasePool alloc] init];
#define LMI_MACFUNCTION_END   [_p_o_o_l release];
