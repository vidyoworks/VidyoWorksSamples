/**
{file:
	{name: LmiPointInPolygon.h}
	{description: }
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
#ifndef LMI_POINTINPOLYGON_H
#define LMI_POINTINPOLYGON_H

#include <Lmi/Utils/LmiTypes.h>

typedef enum
{
	LMI_YREGION_ORIGIN_,
	LMI_YREGION_NEGXAXIS_,
	LMI_YREGION_POSXAXIS_,
	LMI_YREGION_NEGY_,
	LMI_YREGION_POSY_,
} LmiYRegion_;

typedef enum
{
	LMI_POLYGONREGION_INTERIOR,
	LMI_POLYGONREGION_EXTERIOR,
	LMI_POLYGONREGION_BOUNDARY,
} LmiPolygonRegion;

#define Define_LmiPointInPolygon(NAME_, FI_, T_, GetX_, GetY_) \
	LMI_STATIC_INLINE LmiYRegion_ NAME_##_PointToRegion(T_ x, T_ y) \
	{ \
		return y == 0 ? \
			(x == 0 ? LMI_YREGION_ORIGIN_ : (x > 0 ? LMI_YREGION_POSXAXIS_ : LMI_YREGION_NEGXAXIS_)) : \
			(y > 0 ? LMI_YREGION_POSY_ : LMI_YREGION_NEGY_); \
	} \
	static LmiPolygonRegion NAME_(FI_ pg, FI_ pgEnd, T_ px, T_ py) \
	{ \
		T_ lastX, lastY; \
		LmiYRegion_ lastRegion, lastYSign; \
		LmiInt w = 0; \
		FI_ cur = pg; \
		FI_ endVertex; \
		LmiBool secondPass = LMI_FALSE; \
	\
		/* Don't start on POSXAXIS. */ \
		for(;;) \
		{ \
			if(cur == pgEnd) \
				return LMI_POLYGONREGION_EXTERIOR; \
			lastX = GetX_(LmiContentOf(FI_)(&cur)) - px; \
			lastY = GetY_(LmiContentOf(FI_)(&cur)) - py; \
			lastRegion = NAME_##_PointToRegion(lastX, lastY); \
			if(lastRegion == LMI_YREGION_ORIGIN_) \
				return LMI_POLYGONREGION_BOUNDARY; \
			if(lastRegion != LMI_YREGION_POSXAXIS_) \
				break; \
			++cur; \
		} \
	\
		lastYSign = lastRegion; \
		endVertex = cur; \
		for(;;) \
		{ \
			if(++cur == pgEnd) \
				cur = pg, secondPass = LMI_TRUE; \
			{ \
			T_ x = GetX_(LmiContentOf(FI_)(&cur)) - px; \
			T_ y = GetY_(LmiContentOf(FI_)(&cur)) - py; \
			LmiYRegion_ region = NAME_##_PointToRegion(x, y); \
			switch(region) \
			{ \
			case LMI_YREGION_POSY_: \
				if(lastRegion == LMI_YREGION_NEGY_) \
				{ \
					T_ xInt = y * lastX - x * lastY; \
					if(xInt == 0) \
						return LMI_POLYGONREGION_BOUNDARY; \
					else if(xInt > 0) \
						++w; \
				} \
				else if(lastRegion == LMI_YREGION_POSXAXIS_ && lastYSign == LMI_YREGION_NEGY_) \
					++w; \
				lastYSign = LMI_YREGION_POSY_; \
				break; \
			case LMI_YREGION_NEGY_: \
				if(lastRegion == LMI_YREGION_POSY_) \
				{ \
					T_ xInt = x * lastY - y * lastX; \
					if(xInt == 0) \
						return LMI_POLYGONREGION_BOUNDARY; \
					else if(xInt > 0) \
						--w; \
				} \
				else if(lastRegion == LMI_YREGION_POSXAXIS_ && lastYSign == LMI_YREGION_POSY_) \
					--w; \
				lastYSign = LMI_YREGION_NEGY_; \
				break; \
			case LMI_YREGION_ORIGIN_: \
				return LMI_POLYGONREGION_BOUNDARY; \
			case LMI_YREGION_NEGXAXIS_: \
				if(lastRegion == LMI_YREGION_POSXAXIS_) \
					return LMI_POLYGONREGION_BOUNDARY; \
				break; \
			case LMI_YREGION_POSXAXIS_: \
				if(lastRegion == LMI_YREGION_NEGXAXIS_) \
					return LMI_POLYGONREGION_BOUNDARY; \
				break; \
			} \
			lastX = x; \
			lastY = y; \
			lastRegion = region; \
			if(secondPass && cur == endVertex) \
				break; \
			} \
		} \
	\
		return w == 0 ? LMI_POLYGONREGION_EXTERIOR : LMI_POLYGONREGION_INTERIOR; \
	}

#endif
