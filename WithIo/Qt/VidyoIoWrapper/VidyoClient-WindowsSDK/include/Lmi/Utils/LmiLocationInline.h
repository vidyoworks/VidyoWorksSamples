/**
{file:
	{name: LmiLocationInline.h}
	{description: Geographic location.}
	{copyright:
		(c) 2014 Vidyo, Inc.,
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
LMI_INLINE void LmiLocationDestruct(LmiLocation *loc)
{
}

LMI_INLINE LmiFloat64 LmiLocationGetLatitude(const LmiLocation *loc)
{
	return loc->latitude;
}

LMI_INLINE LmiFloat64 LmiLocationGetLongitude(const LmiLocation *loc)
{
	return loc->longitude;
}

LMI_INLINE LmiFloat64 LmiLocationGetAltitude(const LmiLocation *loc)
{
	return loc->altitude;
}
