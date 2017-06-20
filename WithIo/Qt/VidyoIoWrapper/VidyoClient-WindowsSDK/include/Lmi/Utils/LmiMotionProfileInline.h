/**
{file:
	{name: LmiMotionProfileInline.h}
	{description: }
	{copyright:
		(c) 2010-2014 Vidyo, Inc.,
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
LMI_INLINE LmiMotionProfilePlugIn *LmiMotionProfilePlugInConstruct(LmiMotionProfilePlugIn *plugIn, LmiMotionProfilePlugInGetPositionCallback getPosition)
{
	plugIn->getPosition = getPosition;
	return plugIn;
}

LMI_INLINE void LmiMotionProfilePlugInDestruct(LmiMotionProfilePlugIn *plugIn)
{
}

LMI_INLINE LmiMotionProfile *LmiMotionProfileConstructBase(LmiMotionProfile *mp, LmiMotionProfilePlugIn *plugIn)
{
	mp->plugIn = plugIn;
	return mp;
}

LMI_INLINE void LmiMotionProfileDestruct(LmiMotionProfile *mp)
{
}

LMI_INLINE LmiFloat64 LmiMotionProfileGetPosition(LmiMotionProfile *mp, LmiFloat64 t)
{
	return mp->plugIn->getPosition(mp, t);
}

LMI_INLINE void LmiConstVelMotionProfileDestruct(LmiConstVelMotionProfile *p)
{
	LmiMotionProfileDestruct(&p->profile);
}

LMI_INLINE LmiMotionProfile *LmiConstVelMotionProfileGetBase(LmiConstVelMotionProfile *p)
{
	return &p->profile;
}

LMI_INLINE LmiConstAccelMotionProfile *LmiConstAccelMotionProfileConstruct(LmiConstAccelMotionProfile *p)
{
	return LmiConstAccelMotionProfileConstructEx(p, 0.25);
}

LMI_INLINE void LmiConstAccelMotionProfileDestruct(LmiConstAccelMotionProfile *p)
{
	LmiMotionProfileDestruct(&p->profile);
}

LMI_INLINE LmiMotionProfile *LmiConstAccelMotionProfileGetBase(LmiConstAccelMotionProfile *p)
{
	return &p->profile;
}

LMI_INLINE LmiConstJerkMotionProfile *LmiConstJerkMotionProfileConstruct(LmiConstJerkMotionProfile *p)
{
	return LmiConstJerkMotionProfileConstructEx(p, 0.375, 0.125);
}

LMI_INLINE void LmiConstJerkMotionProfileDestruct(LmiConstJerkMotionProfile *p)
{
	LmiMotionProfileDestruct(&p->profile);
}

LMI_INLINE LmiMotionProfile *LmiConstJerkMotionProfileGetBase(LmiConstJerkMotionProfile *p)
{
	return &p->profile;
}
