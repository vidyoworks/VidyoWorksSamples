/**
{file:
	{name: LmiMain.h}
	{description: }
	{copyright:
		(c) 2012-2013 Vidyo, Inc.,
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
#ifndef LMI_MAIN_H
#define LMI_MAIN_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

typedef int (*LmiMainFunction)(int argc, char **argv);
typedef void (*LmiQuitFunction)(void);

int LmiMain(LmiMainFunction f, int argc, char **argv);
int LmiMainEx(LmiMainFunction f, int argc, char **argv, LmiQuitFunction q);

LMI_END_EXTERN_C

#endif
