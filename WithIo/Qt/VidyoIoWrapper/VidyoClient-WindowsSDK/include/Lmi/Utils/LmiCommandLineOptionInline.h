/**
{file:
	{name: LmiCommandLineOptionInline.h}
	{description: Parsing of command line options.}
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
LMI_INLINE void LmiCommandLineParameterDestruct(LmiCommandLineParameter *p)
{
}

LMI_INLINE LmiCommandLineOption *LmiCommandLineOptionConstructBoolean(LmiCommandLineOption *opt, const char *tag, LmiBool *ptr)
{
	return LmiCommandLineOptionConstructBooleanEx(opt, tag, ptr, LMI_TRUE);
}

LMI_INLINE void LmiCommandLineOptionDestruct(LmiCommandLineOption *opt)
{
	if(opt->parameters == &opt->parameter)
		LmiCommandLineParameterDestruct(&opt->parameter);
}

LMI_INLINE const char *LmiCommandLineOptionGetTag(const LmiCommandLineOption *opt)
{
	return opt->tag;
}
