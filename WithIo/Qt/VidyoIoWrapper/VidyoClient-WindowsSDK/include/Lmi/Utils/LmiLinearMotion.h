/**
{file:
	{name: LmiLinearMotion.h}
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
#ifndef LMI_LINEARMOTION_H
#define LMI_LINEARMOTION_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiMotionProfile.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="public":
	{name: LmiLinearMotion}
	{parent: Utils}
	{include: Lmi/Utils/LmiLinearMotion.h}
	{description: Calculates points along a line in any number of dimensions.
		Given an LmiMotionProfile, this class can be used to calculate the position as a function
		of time for an object moving smoothly along a line.}
}
*/
typedef struct
{
	struct LmiLinearMotionAxis_ *axes;
	LmiUint numAxes;
	LmiBool moving;
	LmiFloat64 t0, dt;
	LmiMotionProfile *profile;
	LmiAllocator *alloc;
} LmiLinearMotion;

/**
{function visibility="public":
	{name: LmiLinearMotionConstruct}
	{parent: LmiLinearMotion}
	{description: Constructs an LmiLinearMotion object. This defines the number of axes and the initial position
		of the moving object.}
	{prototype: LmiLinearMotion *LmiLinearMotionConstruct(LmiLinearMotion *lm, const LmiFloat64 *pos, LmiUint numAxes,
		LmiMotionProfile *profile, LmiAllocator *alloc)}
	{parameter: {name: lm} {description: The LmiLinearMotion object to construct.}}
	{parameter: {name: pos} {description: An array of values providing the object's initial position.
		If NULL, this will initialize all values to 0.}}
	{parameter: {name: numAxes} {description: The number of dimensions that the object will be moving through.
		(This should be the number of elements in the pos array.)}}
	{parameter: {name: profile} {description: The motion profile to use. Controls the smoothness of the motion.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiLinearMotion *LmiLinearMotionConstruct(LmiLinearMotion *lm, const LmiFloat64 *pos, LmiUint numAxes,
	LmiMotionProfile *profile, LmiAllocator *alloc);

/**
{function visibility="public":
	{name: LmiLinearMotionDestruct}
	{parent: LmiLinearMotion}
	{description: Destructs an LmiLinearMotion object.}
	{prototype: void LmiLinearMotionDestruct(LmiLinearMotion *lm)}
	{parameter: {name: lm} {description: The LmiLinearMotion object to destruct.}}
}
*/
void LmiLinearMotionDestruct(LmiLinearMotion *lm);

/**
{function visibility="public":
	{name: LmiLinearMotionGetPosition}
	{parent: LmiLinearMotion}
	{description: Gets the current position of a moving object as a function of time.}
	{prototype: LmiBool LmiLinearMotionGetPosition(LmiLinearMotion *lm, LmiFloat64 t, LmiFloat64 *pos)}
	{parameter: {name: lm} {description: The LmiLinearMotion object.}}
	{parameter: {name: t} {description: The current time.}}
	{parameter: {name: pos} {description: The object's position at the specified time is written
		into this array. The array should contain one element for each dimension being tracked.
		Note: only the last programmed move (via LmiLinearMotionMoveTo) is used to determine
		the position; no history of previous moves is kept. If the time passed is earlier than
		the start time of the current move, then the start position of the current move is returned.}}
	{return: A boolean indicating whether the current move has been completed.}
}
*/
LmiBool LmiLinearMotionGetPosition(LmiLinearMotion *lm, LmiFloat64 t, LmiFloat64 *pos);

/**
{function visibility="public":
	{name: LmiLinearMotionSetPosition}
	{parent: LmiLinearMotion}
	{description: Sets the current position for an LmiLinearMotion object. This terminates any move
		in progress and instantaneously moves the object to a new position.}
	{prototype: void LmiLinearMotionSetPosition(LmiLinearMotion *lm, const LmiFloat64 *pos)}
	{parameter: {name: lm} {description: The LmiLinearMotion object.}}
	{parameter: {name: pos} {description: The new position of the object.}}
}
*/
void LmiLinearMotionSetPosition(LmiLinearMotion *lm, const LmiFloat64 *pos);

/**
{function visibility="public":
	{name: LmiLinearMotionMoveTo}
	{parent: LmiLinearMotion}
	{description: Move in a straight line to a new position in a specified amount of time.}
	{prototype: void LmiLinearMotionMoveTo(LmiLinearMotion *lm, LmiFloat64 t0, LmiFloat64 dt, const LmiFloat64 *pos)}
	{parameter: {name: lm} {description: The LmiLinearMotion object.}}
	{parameter: {name: t0} {description: The start time of the motion.}}
	{parameter: {name: dt} {description: The duration of the motion.}}
	{parameter: {name: pos} {description: The target position.}}
	{note: Any units for times and positions can be used.}
}
*/
void LmiLinearMotionMoveTo(LmiLinearMotion *lm, LmiFloat64 t0, LmiFloat64 dt, const LmiFloat64 *pos);

LMI_END_EXTERN_C

#endif
