/**
{file:
	{name: LmiLocation.h}
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
#ifndef LMI_LOCATION_H
#define LMI_LOCATION_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: LmiLocation}
	{parent: Utils}
	{include: Lmi/Utils/LmiLocation.h}
	{description: An object that represents a geographic location.}
}
*/
typedef struct
{
	LmiFloat64 latitude;
	LmiFloat64 longitude;
	LmiFloat64 altitude;
} LmiLocation;

/**
{function:
	{name: LmiLocationConstructDefault}
	{parent: LmiLocation}
	{description: Construct an LmiLocation object with an arbitrary location.}
	{prototype: LmiLocation *LmiLocationConstructDefault(LmiLocation *loc)}
	{parameter: {name: loc} {description: The location object to be constructed.}}
	{return: The constructed object or NULL on failure.}
}
*/
LmiLocation *LmiLocationConstructDefault(LmiLocation *loc);

/**
{function:
	{name: LmiLocationConstruct}
	{parent: LmiLocation}
	{description: Construct an LmiLocation object.}
	{prototype: LmiLocation *LmiLocationConstruct(LmiLocation *loc, LmiFloat64 latitude, LmiFloat64 longitude, LmiFloat64 altitude)}
	{parameter: {name: loc} {description: The location object to be constructed.}}
	{parameter: {name: latitude} {description: The latitude of the location in degrees.}}
	{parameter: {name: longitude} {description: The longitude of the location in degrees.}}
	{parameter: {name: altitude} {description: The altitude of the location in meters.}}
	{return: The constructed object or NULL on failure.}
}
*/
LmiLocation *LmiLocationConstruct(LmiLocation *loc, LmiFloat64 latitude, LmiFloat64 longitude, LmiFloat64 altitude);

/**
{function:
	{name: LmiLocationConstructCopy}
	{parent: LmiLocation}
	{description: Construct a geographic location object as a copy of an existing object.}
	{prototype: LmiLocation *LmiLocationConstructCopy(LmiLocation *loc, const LmiLocation *other)}
	{parameter: {name: loc} {description: The location object to be constructed.}}
	{parameter: {name: other} {description: The location object to copy.}}
	{return: The constructed object or NULL on failure.}
}
*/
LmiLocation *LmiLocationConstructCopy(LmiLocation *loc, const LmiLocation *other);

/**
{function:
	{name: LmiLocationDestruct}
	{parent: LmiLocation}
	{description: Destruct an LmiLocation object.}
	{prototype: void LmiLocationDestruct(LmiLocation *loc)}
	{parameter: {name: loc} {description: The location object to be destructed.}}
}
*/
LMI_INLINE_DECLARATION void LmiLocationDestruct(LmiLocation *loc);

/**
{function:
	{name: LmiLocationAssign}
	{parent: LmiLocation}
	{description: Assign one geographic location object the value of another.}
	{prototype: LmiLocation *LmiLocationAssign(LmiLocation *loc, const LmiLocation *other)}
	{parameter: {name: loc} {description: The location object to assign to.}}
	{parameter: {name: other} {description: The location object to copy.}}
	{return: The assigned object or NULL on failure.}
}
*/
LmiLocation *LmiLocationAssign(LmiLocation *loc, const LmiLocation *other);

/**
{function:
	{name: LmiLocationGetLatitude}
	{parent: LmiLocation}
	{description: Get the latitude from a geographic location object.}
	{prototype: LmiFloat64 LmiLocationGetLatitude(const LmiLocation *loc)}
	{parameter: {name: loc} {description: The location object.}}
	{return: The latitude in degrees.}
}
*/
LMI_INLINE_DECLARATION LmiFloat64 LmiLocationGetLatitude(const LmiLocation *loc);

/**
{function:
	{name: LmiLocationGetLongitude}
	{parent: LmiLocation}
	{description: Get the longitude from a geographic location object.}
	{prototype: LmiFloat64 LmiLocationGetLongitude(const LmiLocation *loc)}
	{parameter: {name: loc} {description: The location object.}}
	{return: The longitude in degrees.}
}
*/
LMI_INLINE_DECLARATION LmiFloat64 LmiLocationGetLongitude(const LmiLocation *loc);

/**
{function:
	{name: LmiLocationGetAltitude}
	{parent: LmiLocation}
	{description: Get the altitude from a geographic location object.}
	{prototype: LmiFloat64 LmiLocationGetAltitude(const LmiLocation *loc)}
	{parameter: {name: loc} {description: The location object.}}
	{return: The altitude in meters.}
}
*/
LMI_INLINE_DECLARATION LmiFloat64 LmiLocationGetAltitude(const LmiLocation *loc);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiLocationInline.h>
#endif

#endif
