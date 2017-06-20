/**
{file:
	{name: LmiRectangleInline.h}
	{description: Inline functions for LmiRectangle.}
	{copyright:
		(c) 2010-2012 Vidyo, Inc.,
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
LMI_INLINE LmiRectangle *LmiRectangleConstructDefault(LmiRectangle *r)
{
	r->x0 = 0;
	r->y0 = 0;
	r->x1 = 0;
	r->y1 = 0;
	return r;
}

LMI_INLINE LmiRectangle *LmiRectangleConstructCopy(LmiRectangle *d, const LmiRectangle *s)
{
	*d = *s;
	return d;
}

LMI_INLINE void LmiRectangleDestruct(LmiRectangle *r)
{
}

LMI_INLINE LmiRectangle *LmiRectangleAssign(LmiRectangle *d, const LmiRectangle *s)
{
	*d = *s;
	return d;
}

LMI_INLINE LmiBool LmiRectangleEqual(const LmiRectangle *a, const LmiRectangle *b)
{
	return a->x0 == b->x0
		&& a->y0 == b->y0
		&& a->x1 == b->x1
		&& a->y1 == b->y1;
}

LMI_INLINE void LmiRectangleSetMinX(LmiRectangle *r, LmiInt x)
{
	r->x0 = x;
}

LMI_INLINE void LmiRectangleSetMinY(LmiRectangle *r, LmiInt y)
{
	r->y0 = y;
}

LMI_INLINE void LmiRectangleSetMin(LmiRectangle *r, LmiInt x, LmiInt y)
{
	r->x0 = x;
	r->y0 = y;
}

LMI_INLINE void LmiRectangleSetMaxX(LmiRectangle *r, LmiInt x)
{
	r->x1 = x;
}

LMI_INLINE void LmiRectangleSetMaxY(LmiRectangle *r, LmiInt y)
{
	r->y1 = y;
}

LMI_INLINE void LmiRectangleSetMax(LmiRectangle *r, LmiInt x, LmiInt y)
{
	r->x1 = x;
	r->y1 = y;
}

LMI_INLINE void LmiRectangleMoveToMinX(LmiRectangle *r, LmiInt x)
{
	r->x1 += x - r->x0;
	r->x0 = x;
}

LMI_INLINE void LmiRectangleMoveToMinY(LmiRectangle *r, LmiInt y)
{
	r->y1 += y - r->y0;
	r->y0 = y;
}

LMI_INLINE void LmiRectangleMoveToMin(LmiRectangle *r, LmiInt x, LmiInt y)
{
	LmiRectangleMoveToMinX(r, x);
	LmiRectangleMoveToMinY(r, y);
}

LMI_INLINE void LmiRectangleMoveToMaxX(LmiRectangle *r, LmiInt x)
{
	r->x0 += x - r->x1;
	r->x1 = x;
}

LMI_INLINE void LmiRectangleMoveToMaxY(LmiRectangle *r, LmiInt y)
{
	r->y0 += y - r->y1;
	r->y1 = y;
}

LMI_INLINE void LmiRectangleMoveToMax(LmiRectangle *r, LmiInt x, LmiInt y)
{
	LmiRectangleMoveToMaxX(r, x);
	LmiRectangleMoveToMaxY(r, y);
}

LMI_INLINE void LmiRectangleMoveTo(LmiRectangle *r, LmiInt x, LmiInt y)
{
	LmiRectangleMoveToMin(r, x, y);
}

LMI_INLINE void LmiRectangleResizeFromMinX(LmiRectangle *r, LmiUint width)
{
	r->x1 = r->x0 + (LmiInt)width;
}

LMI_INLINE void LmiRectangleResizeFromMinY(LmiRectangle *r, LmiUint height)
{
	r->y1 = r->y0 + (LmiInt)height;
}

LMI_INLINE void LmiRectangleResizeFromMin(LmiRectangle *r, LmiUint width, LmiUint height)
{
	r->x1 = r->x0 + (LmiInt)width;
	r->y1 = r->y0 + (LmiInt)height;
}

LMI_INLINE void LmiRectangleResizeFromMaxX(LmiRectangle *r, LmiUint width)
{
	r->x0 = r->x1 - (LmiInt)width;
}

LMI_INLINE void LmiRectangleResizeFromMaxY(LmiRectangle *r, LmiUint height)
{
	r->y0 = r->y1 - (LmiInt)height;
}

LMI_INLINE void LmiRectangleResizeFromMax(LmiRectangle *r, LmiUint width, LmiUint height)
{
	r->x0 = r->x1 - (LmiInt)width;
	r->y0 = r->y1 - (LmiInt)height;
}

LMI_INLINE void LmiRectangleSetMinAndMaxX(LmiRectangle *r, LmiInt xMin, LmiInt xMax)
{
	r->x0 = xMin;
	r->x1 = xMax;
}

LMI_INLINE void LmiRectangleSetMinAndMaxY(LmiRectangle *r, LmiInt yMin, LmiInt yMax)
{
	r->y0 = yMin;
	r->y1 = yMax;
}

LMI_INLINE void LmiRectangleSetMinAndMax(LmiRectangle *r, LmiInt xMin, LmiInt yMin, LmiInt xMax, LmiInt yMax)
{
	LmiRectangleSetMinAndMaxX(r, xMin, xMax);
	LmiRectangleSetMinAndMaxY(r, yMin, yMax);
}

LMI_INLINE void LmiRectangleSetMinAndSizeX(LmiRectangle *r, LmiInt x, LmiUint width)
{
	r->x0 = x;
	r->x1 = x + (LmiInt)width;
}

LMI_INLINE void LmiRectangleSetMinAndSizeY(LmiRectangle *r, LmiInt y, LmiUint height)
{
	r->y0 = y;
	r->y1 = y + (LmiInt)height;
}

LMI_INLINE void LmiRectangleSetMinAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)
{
	LmiRectangleSetMinAndSizeX(r, x, width);
	LmiRectangleSetMinAndSizeY(r, y, height);
}

LMI_INLINE void LmiRectangleSetMaxAndSizeX(LmiRectangle *r, LmiInt x, LmiUint width)
{
	r->x0 = x - (LmiInt)width;
	r->x1 = x;
}

LMI_INLINE void LmiRectangleSetMaxAndSizeY(LmiRectangle *r, LmiInt y, LmiUint height)
{
	r->y0 = y - (LmiInt)height;
	r->y1 = y;
}

LMI_INLINE void LmiRectangleSetMaxAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)
{
	LmiRectangleSetMaxAndSizeX(r, x, width);
	LmiRectangleSetMaxAndSizeY(r, y, height);
}

LMI_INLINE LmiRectangle *LmiRectangleConstructMinAndMax(LmiRectangle *r, LmiInt xMin, LmiInt yMin, LmiInt xMax, LmiInt yMax)
{
	LmiRectangleSetMinAndMax(r, xMin, yMin, xMax, yMax);
	return r;
}

LMI_INLINE LmiRectangle *LmiRectangleConstructMinAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)
{
	LmiRectangleSetMinAndSize(r, x, y, width, height);
	return r;
}

LMI_INLINE LmiRectangle *LmiRectangleConstruct(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)
{
	return LmiRectangleConstructMinAndSize(r, x, y, width, height);
}

LMI_INLINE LmiRectangle *LmiRectangleConstructMaxAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)
{
	LmiRectangleSetMaxAndSize(r, x, y, width, height);
	return r;
}

LMI_INLINE LmiInt LmiRectangleGetMinX(const LmiRectangle *r)
{
	return r->x0;
}

LMI_INLINE LmiInt LmiRectangleGetMinY(const LmiRectangle *r)
{
	return r->y0;
}

LMI_INLINE LmiInt LmiRectangleGetMaxX(const LmiRectangle *r)
{
	return r->x1;
}

LMI_INLINE LmiInt LmiRectangleGetMaxY(const LmiRectangle *r)
{
	return r->y1;
}

LMI_INLINE LmiInt LmiRectangleGetLeft(const LmiRectangle *r)
{
	return r->x0;
}

LMI_INLINE LmiInt LmiRectangleGetTop(const LmiRectangle *r)
{
	return r->y0;
}

LMI_INLINE LmiInt LmiRectangleGetRight(const LmiRectangle *r)
{
	return r->x1;
}

LMI_INLINE LmiInt LmiRectangleGetBottom(const LmiRectangle *r)
{
	return r->y1;
}

LMI_INLINE void LmiRectangleSetLeft(LmiRectangle *r, LmiInt x)
{
	r->x0 = x;
}

LMI_INLINE void LmiRectangleSetTop(LmiRectangle *r, LmiInt y)
{
	r->y0 = y;
}

LMI_INLINE void LmiRectangleSetRight(LmiRectangle *r, LmiInt x)
{
	r->x1 = x;
}

LMI_INLINE void LmiRectangleSetBottom(LmiRectangle *r, LmiInt y)
{
	r->y1 = y;
}

LMI_INLINE LmiUint LmiRectangleGetWidth(const LmiRectangle *r)
{
	return (LmiUint)(r->x1 - r->x0);
}

LMI_INLINE LmiUint LmiRectangleGetHeight(const LmiRectangle *r)
{
	return (LmiUint)(r->y1 - r->y0);
}

LMI_INLINE void LmiRectangleSetWidth(LmiRectangle *r, LmiUint width)
{
	r->x1 = r->x0 + (LmiInt)width;
}

LMI_INLINE void LmiRectangleSetHeight(LmiRectangle *r, LmiUint height)
{
	r->y1 = r->y0 + (LmiInt)height;
}

LMI_INLINE LmiUint LmiRectangleGetArea(const LmiRectangle *r)
{
	return LmiRectangleGetWidth(r) * LmiRectangleGetHeight(r);
}

LMI_INLINE LmiBool LmiRectangleContains(const LmiRectangle *r, LmiInt x, LmiInt y)
{
	return r->x0 <= x && x < r->x1 && r->y0 <= y && y < r->y1;
}

#ifdef LMI_HAVE_CREATEWINDOWEXA

LMI_INLINE void LmiRectangleFromRECT(LmiRectangle *r, const RECT *wr)
{
	r->x0 = wr->left;
	r->y0 = wr->top;
	r->x1 = wr->right;
	r->y1 = wr->bottom;
}

LMI_INLINE void LmiRectangleToRECT(const LmiRectangle *r, RECT *wr)
{
	wr->left   = r->x0;
	wr->top    = r->y0;
	wr->right  = r->x1;
	wr->bottom = r->y1;
}

LMI_INLINE void LmiRectangleFromRECTWithScale(LmiRectangle *r, const RECT *wr, LmiFloat32 scale)
{
	LmiRectangleFromRECT(r, wr);
	LmiRectangleScale(r, 1 / scale);
}


#endif

