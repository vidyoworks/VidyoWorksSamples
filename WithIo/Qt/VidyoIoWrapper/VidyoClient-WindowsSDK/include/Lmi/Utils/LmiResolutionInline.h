/**
{file:
	{name: LmiResolutionInline.h}
	{description: Resolution object (Width and height).}
	{copyright:
		(c) 2007-2013 Vidyo, Inc.,
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
LMI_INLINE LmiResolution* LmiResolutionConstruct(LmiResolution* r, LmiUint width, LmiUint height, LmiAllocator* a)
{
	r->width = width;
	r->height = height;
	return r;
}

LMI_INLINE void LmiResolutionDestruct(LmiResolution* r)
{
}

LMI_INLINE LmiResolution* LmiResolutionConstructCopy(LmiResolution* r, const LmiResolution* o)
{
	r->height = o->height;
	r->width = o->width;
	return r;
}

LMI_INLINE LmiResolution* LmiResolutionAssign(LmiResolution* r, const LmiResolution* o)
{
	r->height = o->height;
	r->width = o->width;
	return r;
}

LMI_INLINE LmiUint LmiResolutionGetWidth(const LmiResolution* r)
{
	return r->width;
}

LMI_INLINE LmiUint LmiResolutionGetHeight(const LmiResolution* r)
{
	return r->height;
}

LMI_INLINE LmiBool LmiResolutionSetWidth(LmiResolution* r, LmiUint width)
{
	r->width = width;
	return LMI_TRUE;
}

LMI_INLINE LmiBool LmiResolutionSetHeight(LmiResolution* r, LmiUint height)
{
	r->height = height;
	return LMI_TRUE;
}

LMI_INLINE LmiBool LmiResolutionEqual(const LmiResolution* r, const LmiResolution* s)
{
	return (r->width == s->width) && (r->height == s->height);
}
