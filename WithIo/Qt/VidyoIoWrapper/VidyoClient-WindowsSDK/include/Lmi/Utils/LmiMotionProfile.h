/**
{file:
	{name: LmiMotionProfile.h}
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
#ifndef LMI_MOTIONPROFILE_H
#define LMI_MOTIONPROFILE_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

struct LmiMotionProfile_;

/**
{callback visibility="public":
	{name: LmiMotionProfilePlugInGetPositionCallback}
	{parent: LmiMotionProfilePlugIn}
	{description: A callback returning the fraction of the total distance traveled as a function of
		the fraction of total time elapsed. This callback can be used to customize the smoothness of a motion.
		Other effects can be also be achieved, such as overshooting the target and snapping back to it.
		The function should return 0 at t=0 and 1 at t=1. A continuous function should be used in
		most instances, otherwise the animated object will appear to be teleported.}
	{prototype: LmiFloat64 (*LmiMotionProfilePlugInGetPositionCallback)(LmiMotionProfile *mp, LmiFloat64 t)}
	{parameter: {name: mp} {description: The LmiMotionProfile object.}}
	{parameter: {name: t} {description: A value between 0 and 1 representing the fraction of the total time allotted for
		the move that has elapsed.}}
	{return: A value between 0 and 1 representing the fraction of the total distance that has been traveled so far.}
}
*/
typedef LmiFloat64 (*LmiMotionProfilePlugInGetPositionCallback)(struct LmiMotionProfile_ *mp, LmiFloat64 t);

/**
{type visibility="public":
	{name: LmiMotionProfilePlugIn}
	{parent: Utils}
	{include: Lmi/Utils/LmiMotionProfile.h}
	{description: Object used for customizing the behavior of an LmiMotionProfile object.}
}
*/
typedef struct
{
	LmiMotionProfilePlugInGetPositionCallback getPosition;
} LmiMotionProfilePlugIn;

/**
{function visibility="public":
	{name: LmiMotionProfilePlugInConstruct}
	{parent: LmiMotionProfilePlugIn}
	{description: Constructs an LmiMotionProfilePlugIn object.}
	{prototype: LmiMotionProfilePlugIn *LmiMotionProfilePlugInConstruct(LmiMotionProfilePlugIn *plugIn,
		LmiMotionProfilePlugInGetPositionCallback getPosition)}
	{parameter: {name: plugIn} {description: The LmiMotionProfilePlugIn object to construct.}}
	{parameter: {name: getPosition} {description: See LmiMotionProfilePlugInGetPositionCallback.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiMotionProfilePlugIn *LmiMotionProfilePlugInConstruct(LmiMotionProfilePlugIn *plugIn, LmiMotionProfilePlugInGetPositionCallback getPosition);

/**
{function visibility="public":
	{name: LmiMotionProfilePlugInDestruct}
	{parent: LmiMotionProfilePlugIn}
	{description: Destructs an LmiMotionProfilePlugIn object.}
	{prototype: void LmiMotionProfilePlugInDestruct(LmiMotionProfilePlugIn *plugIn)}
	{parameter: {name: plugIn} {description: The LmiMotionProfilePlugIn object to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiMotionProfilePlugInDestruct(LmiMotionProfilePlugIn *plugIn);

/**
{type visibility="public":
	{name: LmiMotionProfile}
	{parent: Utils}
	{include: Lmi/Utils/LmiMotionProfile.h}
	{description: Abstract base class used to customize the speed of an object as it travels along a path.
		This class allows the smoothness of an animation to be controlled independent of the actual path followed.}
}
*/
typedef struct LmiMotionProfile_
{
	LmiMotionProfilePlugIn *plugIn;
} LmiMotionProfile;

/**
{function visibility="public":
	{name: LmiMotionProfileConstructBase}
	{parent: LmiMotionProfile}
	{description: Constructs an LmiMotionProfile object. Use this function when creating an object
		of a class derived from LmiMotionProfile.}
	{prototype: LmiMotionProfile *LmiMotionProfileConstructBase(LmiMotionProfile *mp, LmiMotionProfilePlugIn *plugIn)}
	{parameter: {name: mp} {description: The LmiMotionProfile object to construct.}}
	{parameter: {name: plugIn} {description: The motion profile plug-in. Typically each derived class will have
		its own plug-in object that is shared between all instances of the class.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiMotionProfile *LmiMotionProfileConstructBase(LmiMotionProfile *mp, LmiMotionProfilePlugIn *plugIn);

/**
{function visibility="public":
	{name: LmiMotionProfileDestruct}
	{parent: LmiMotionProfile}
	{description: Destructs an LmiMotionProfile object.}
	{prototype: void LmiMotionProfileDestruct(LmiMotionProfile *mp)}
	{parameter: {name: mp} {description: The LmiMotionProfile object to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiMotionProfileDestruct(LmiMotionProfile *mp);

/**
{function visibility="public":
	{name: LmiMotionProfileGetPosition}
	{parent: LmiMotionProfile}
	{description: Gets the fraction of the total distance traveled as a function of
		the fraction of total time elapsed.}
	{prototype: LmiFloat64 LmiMotionProfileGetPosition(LmiMotionProfile *mp, LmiFloat64 t)}
	{parameter: {name: mp} {description: The LmiMotionProfile object to construct.}}
	{parameter: {name: t} {description: A value between 0 and 1 representing the fraction of the total time allotted for
		the move that has elapsed.}}
	{return: A value between 0 and 1 representing the fraction of the total distance that has been traveled so far.}
}
*/
LMI_INLINE_DECLARATION LmiFloat64 LmiMotionProfileGetPosition(LmiMotionProfile *mp, LmiFloat64 t);

/**
{type visibility="public":
	{name: LmiConstVelMotionProfile}
	{parent: Utils}
	{derivation-of: LmiMotionProfile}
	{include: Lmi/Utils/LmiMotionProfile.h}
	{description: A constant velocity motion profile.}
}
*/
typedef struct
{
	LmiMotionProfile profile;
} LmiConstVelMotionProfile;

/**
{function visibility="public":
	{name: LmiConstVelMotionProfileConstruct}
	{parent: LmiConstVelMotionProfile}
	{description: Constructs an LmiConstVelMotionProfile object.}
	{prototype: LmiConstVelMotionProfile *LmiConstVelMotionProfileConstruct(LmiConstVelMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstVelMotionProfile object to construct.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
	{note: It should not be necessary to call this function directly. All LmiConstVelMotionProfile objects
		behave the same, so only one is necessary. One is prebuilt, which can be accessed by
		calling LmiConstVelMotionProfileGetDefault.}
}
*/
LmiConstVelMotionProfile *LmiConstVelMotionProfileConstruct(LmiConstVelMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstVelMotionProfileDestruct}
	{parent: LmiConstVelMotionProfile}
	{description: Destructs an LmiConstVelMotionProfile object.}
	{prototype: void LmiConstVelMotionProfileDestruct(LmiConstVelMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstVelMotionProfile object to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiConstVelMotionProfileDestruct(LmiConstVelMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstVelMotionProfileGetBase}
	{parent: LmiConstVelMotionProfile}
	{description: Returns the LmiMotionProfile base class pointer for an LmiConstVelMotionProfile object.
		The base class pointer may be passed to functions that use LmiMotionProfile objects
		in a generic fashion.}
	{prototype: LmiMotionProfile *LmiConstVelMotionProfileGetBase(LmiConstVelMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstVelMotionProfile object.}}
	{return: The LmiMotionProfile base class pointer.}
}
*/
LMI_INLINE_DECLARATION LmiMotionProfile *LmiConstVelMotionProfileGetBase(LmiConstVelMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstVelMotionProfileGetDefault}
	{parent: LmiConstVelMotionProfile}
	{description: Returns an LmiConstVelMotionProfile object with default parameters.}
	{prototype: LmiMotionProfile *LmiConstVelMotionProfileGetDefault(void)}
	{return: A default LmiConstVelMotionProfile object.}
}
*/
LmiMotionProfile *LmiConstVelMotionProfileGetDefault(void);

/**
{type visibility="public":
	{name: LmiConstAccelMotionProfile}
	{parent: Utils}
	{derivation-of: LmiMotionProfile}
	{include: Lmi/Utils/LmiMotionProfile.h}
	{description: A motion profile where the magnitude of the acceleration is either 0 or some fixed value.}
}
*/
typedef struct
{
	LmiMotionProfile profile;
	LmiFloat64 P;
	LmiFloat64 traj1[3];
	LmiFloat64 traj2[2];
} LmiConstAccelMotionProfile;

/**
{function visibility="public":
	{name: LmiConstAccelMotionProfileConstruct}
	{parent: LmiConstAccelMotionProfile}
	{description: Constructs an LmiConstAccelMotionProfile object with default parameters. The acceleration
		and deceleration stages will each be 1/4 of the total time for the move.}
	{prototype: LmiConstAccelMotionProfile *LmiConstAccelMotionProfileConstruct(LmiConstAccelMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstAccelMotionProfile object to construct.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
	{note: It should not be necessary to call this function directly. One LmiConstAccelMotionProfile object
		with default parameters is prebuilt, which can be accessed by calling LmiConstAccelMotionProfileGetDefault.
		Use LmiConstAccelMotionProfileConstructEx to create the object with custom parameters.}
}
*/
LMI_INLINE_DECLARATION LmiConstAccelMotionProfile *LmiConstAccelMotionProfileConstruct(LmiConstAccelMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstAccelMotionProfileConstructEx}
	{parent: LmiConstAccelMotionProfile}
	{description: Constructs an LmiConstAccelMotionProfile object with custom parameters.}
	{prototype: LmiConstAccelMotionProfile *LmiConstAccelMotionProfileConstructEx(LmiConstAccelMotionProfile *p, LmiFloat64 tAccel)}
	{parameter: {name: p} {description: The LmiConstAccelMotionProfile object to construct.}}
	{parameter: {name: tAccel} {description: Represents the duration of the acceleration stage of the profile as a
		fraction of the total time for the move. (The same duration will be used for the deceleration stage.)
		Must be greater than 0 and less than 0.5.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiConstAccelMotionProfile *LmiConstAccelMotionProfileConstructEx(LmiConstAccelMotionProfile *p, LmiFloat64 tAccel);

/**
{function visibility="public":
	{name: LmiConstAccelMotionProfileDestruct}
	{parent: LmiConstAccelMotionProfile}
	{description: Destructs an LmiConstAccelMotionProfile object.}
	{prototype: void LmiConstAccelMotionProfileDestruct(LmiConstAccelMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstAccelMotionProfile object to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiConstAccelMotionProfileDestruct(LmiConstAccelMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstAccelMotionProfileGetBase}
	{parent: LmiConstAccelMotionProfile}
	{description: Returns the LmiMotionProfile base class pointer for an LmiConstAccelMotionProfile object.
		The base class pointer may be passed to functions that use LmiMotionProfile objects
		in a generic fashion.}
	{prototype: LmiMotionProfile *LmiConstAccelMotionProfileGetBase(LmiConstAccelMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstAccelMotionProfile object.}}
	{return: The LmiMotionProfile base class pointer.}
}
*/
LMI_INLINE_DECLARATION LmiMotionProfile *LmiConstAccelMotionProfileGetBase(LmiConstAccelMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstAccelMotionProfileGetDefault}
	{parent: LmiConstAccelMotionProfile}
	{description: Returns an LmiConstAccelMotionProfile object with default parameters.}
	{prototype: LmiMotionProfile *LmiConstAccelMotionProfileGetDefault(void)}
	{return: A default LmiConstAccelMotionProfile object.}
}
*/
LmiMotionProfile *LmiConstAccelMotionProfileGetDefault(void);

/**
{type visibility="public":
	{name: LmiConstJerkMotionProfile}
	{parent: Utils}
	{derivation-of: LmiMotionProfile}
	{include: Lmi/Utils/LmiMotionProfile.h}
	{description: A motion profile where the magnitude of the jerk (rate of change of acceleration) is either 0 or some fixed value.}
}
*/
typedef struct
{
	LmiMotionProfile profile;
	LmiFloat64 P, Q, R;
	LmiFloat64 traj1[4];
	LmiFloat64 traj2[3];
	LmiFloat64 traj3[4];
	LmiFloat64 traj4[2];
} LmiConstJerkMotionProfile;

/**
{function visibility="public":
	{name: LmiConstJerkMotionProfileConstruct}
	{parent: LmiConstJerkMotionProfile}
	{description: Constructs an LmiConstJerkMotionProfile object with default parameters. The acceleration
		and deceleration stages will each be 3/8 of the total time for the move. The periods of nonzero
		jerk will each be 1/8 of the total time for the move.}
	{prototype: LmiConstJerkMotionProfile *LmiConstJerkMotionProfileConstruct(LmiConstJerkMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstAccelMotionProfile object to construct.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
	{note: It should not be necessary to call this function directly. One LmiConstJerkMotionProfile object
		with default parameters is prebuilt, which can be accessed by calling LmiConstJerkMotionProfileGetDefault.
		Use LmiConstJerkMotionProfileConstructEx to create the object with custom parameters.}
}
*/
LMI_INLINE_DECLARATION LmiConstJerkMotionProfile *LmiConstJerkMotionProfileConstruct(LmiConstJerkMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstJerkMotionProfileConstructEx}
	{parent: LmiConstJerkMotionProfile}
	{description: Constructs an LmiConstJerkMotionProfile object with custom parameters.}
	{prototype: LmiConstJerkMotionProfile *LmiConstJerkMotionProfileConstructEx(LmiConstJerkMotionProfile *p, LmiFloat64 tAccel, LmiFloat64 tJerk)}
	{parameter: {name: p} {description: The LmiConstAccelMotionProfile object to construct.}}
	{parameter: {name: tAccel} {description: Represents the duration of the acceleration stages of the profile as a
		fraction of the total time for the move. (The same duration will be used for the deceleration stages.)
		Must be greater than 0 and less than 0.5.}}
	{parameter: {name: tJerk} {description: Represents the duration of each of the stages where the acceleration is changing, as a
		fraction of the total time for the move. Must be greater than 0 and less than (tAccel / 2).}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiConstJerkMotionProfile *LmiConstJerkMotionProfileConstructEx(LmiConstJerkMotionProfile *p, LmiFloat64 tAccel, LmiFloat64 tJerk);

/**
{function visibility="public":
	{name: LmiConstJerkMotionProfileDestruct}
	{parent: LmiConstJerkMotionProfile}
	{description: Destructs an LmiConstJerkMotionProfile object.}
	{prototype: void LmiConstJerkMotionProfileDestruct(LmiConstJerkMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstJerkMotionProfile object to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiConstJerkMotionProfileDestruct(LmiConstJerkMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstJerkMotionProfileGetBase}
	{parent: LmiConstJerkMotionProfile}
	{description: Returns the LmiMotionProfile base class pointer for an LmiConstJerkMotionProfile object.
		The base class pointer may be passed to functions that use LmiMotionProfile objects
		in a generic fashion.}
	{prototype: LmiMotionProfile *LmiConstJerkMotionProfileGetBase(LmiConstJerkMotionProfile *p)}
	{parameter: {name: p} {description: The LmiConstJerkMotionProfile object.}}
	{return: The LmiMotionProfile base class pointer.}
}
*/
LMI_INLINE_DECLARATION LmiMotionProfile *LmiConstJerkMotionProfileGetBase(LmiConstJerkMotionProfile *p);

/**
{function visibility="public":
	{name: LmiConstJerkMotionProfileGetDefault}
	{parent: LmiConstJerkMotionProfile}
	{description: Returns an LmiConstJerkMotionProfile object with default parameters.}
	{prototype: LmiMotionProfile *LmiConstJerkMotionProfileGetDefault(void)}
	{return: A default LmiConstJerkMotionProfile object.}
}
*/
LmiMotionProfile *LmiConstJerkMotionProfileGetDefault(void);

LmiBool LmiMotionProfileInitialize_(void);
void LmiMotionProfileUninitialize_(void);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiMotionProfileInline.h>
#endif

#endif
