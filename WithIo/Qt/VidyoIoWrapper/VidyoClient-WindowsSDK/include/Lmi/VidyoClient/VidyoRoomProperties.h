/** 
{file:
	{name: VidyoRoomProperties.h}
	{description: Vidyo Room Properties. }
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_ROOMPROPERTIES_H_ 
#define VIDYO_ROOMPROPERTIES_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C


/**
{type visibility="public":
	{name: VidyoRoomSchedule}
	{parent: VidyoRoomProperties}
	{description: Room schedule describes the scheduling of a room. 
		This is modeled based off iCalendar. Please refer to the 
		iCalendar specification (RFC 2445) for more details.}
	{member:
		{name: eventId}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: startTime}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: endTime}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: duration}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: frequency}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: interval}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: count}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: until}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: byDay}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: byMonthDay}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: byMonth}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: byYearDay}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: byWeekNum}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: bySetPos}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: weekStartDay}
		{type: LmiString}
		{description:}
	}
}
*/
typedef struct {
	LmiString eventId;
	LmiString startTime;
	LmiString endTime;
	LmiString duration;
	LmiString frequency;
	LmiString interval;
	LmiString count;
	LmiString until;
	LmiString byDay;
	LmiString byMonthDay;
	LmiString byMonth;
	LmiString byYearDay;
	LmiString byWeekNum;
	LmiString bySetPos;
	LmiString weekStartDay;
} VidyoRoomSchedule;

/**
{function visibility="private":
	{name: VidyoRoomScheduleConstructDefault}
	{parent: VidyoRoomSchedule}
	{description: Constructs an VidyoRoomSchedule object.}
	{prototype: VidyoRoomSchedule *VidyoRoomScheduleConstructDefault(VidyoRoomSchedule *s, LmiAllocator *alloc)}
	{parameter: {name: s} {description: The VidyoRoomSchedule object to construct.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomSchedule *VidyoRoomScheduleConstructDefault(VidyoRoomSchedule *s, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRoomScheduleConstructCopy}
	{parent: VidyoRoomSchedule}
	{description: Constructs an VidyoRoomSchedule object as a copy of an existing object.}
	{prototype: VidyoRoomSchedule *VidyoRoomScheduleConstructCopy(VidyoRoomSchedule *d, const VidyoRoomSchedule *s)}
	{parameter: {name: d} {description: The VidyoRoomSchedule object to construct.}}
	{parameter: {name: s} {description: The existing VidyoRoomSchedule object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomSchedule *VidyoRoomScheduleConstructCopy(VidyoRoomSchedule *d, const VidyoRoomSchedule *s);

/**
{function visibility="private":
	{name: VidyoRoomScheduleDestruct}
	{parent: VidyoRoomSchedule}
	{description: Destructs an VidyoRoomSchedule object.}
	{prototype: void VidyoRoomScheduleDestruct(VidyoRoomSchedule *s)}
	{parameter: {name: s} {description: The VidyoRoomSchedule object to destruct.}}
}
*/
void VidyoRoomScheduleDestruct(VidyoRoomSchedule *s);

/**
{function visibility="private":
	{name: VidyoRoomScheduleAssign}
	{parent: VidyoRoomSchedule}
	{description: Assign the contents of one VidyoRoomSchedule to another.}
	{prototype: VidyoRoomSchedule *VidyoRoomScheduleAssign(VidyoRoomSchedule *d, const VidyoRoomSchedule *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRoomSchedule *VidyoRoomScheduleAssign(VidyoRoomSchedule *d, const VidyoRoomSchedule *s);

/**
{function visibility="private":
	{name: VidyoRoomScheduleEqual}
	{parent: VidyoRoomSchedule}
	{description: Check the equality of VidyoRoomSchedule object.}
	{prototype: LmiBool VidyoRoomScheduleEqual(const VidyoRoomSchedule *a, const VidyoRoomSchedule *b)}
	{parameter: {name: a} {description: The VidyoRoomSchedule object to compare.}}
	{parameter: {name: b} {description: The VidyoRoomSchedule object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoRoomScheduleEqual(const VidyoRoomSchedule *a, const VidyoRoomSchedule *b);


/**
{type:
	{name: VidyoRoomProfileControlMode}
	{parent: VidyoRoom}
	{description: Describes the profile control mode.}
	{value: {name: VIDYO_ROOMPROFILECONTROLMODE_AlwaysOn} {description: Profile is always ON.}}
	{value: {name: VIDYO_ROOMPROFILECONTROLMODE_AlwaysOff} {description: Profile is always OFF.}}
	{value: {name: VIDYO_ROOMPROFILECONTROLMODE_Default} {description: Profile will take the default behavior.}}
}
*/
typedef enum
{
	VIDYO_ROOMPROFILECONTROLMODE_AlwaysOn,
	VIDYO_ROOMPROFILECONTROLMODE_AlwaysOff,
	VIDYO_ROOMPROFILECONTROLMODE_Default
} VidyoRoomProfileControlMode;

/**
{type visibility="public":
	{name: VidyoRoomParticipantProfile}
	{parent: VidyoRoomProperties}
	{description: Participant's profile describing the source restrictions and the chat restriction.}
	{member:
		{name: userId}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: microphone}
		{type: VidyoRoomProfileControlMode}
		{description:}
	}
	{member:
		{name: camera}
		{type: VidyoRoomProfileControlMode}
		{description:}
	}
	{member:
		{name: windowShare}
		{type: VidyoRoomProfileControlMode}
		{description:}
	}
	{member:
		{name: chat}
		{type: VidyoRoomProfileControlMode}
		{description:}
	}
}
*/
typedef struct {
	LmiString userId;
	VidyoRoomProfileControlMode microphone;
	VidyoRoomProfileControlMode camera;
	VidyoRoomProfileControlMode windowShare;
	VidyoRoomProfileControlMode chat;
} VidyoRoomParticipantProfile;

/**
{function visibility="private":
	{name: VidyoRoomParticipantProfileConstructDefault}
	{parent: VidyoRoomParticipantProfile}
	{description: Constructs an VidyoRoomParticipantProfile object.}
	{prototype: VidyoRoomParticipantProfile *VidyoRoomParticipantProfileConstructDefault(VidyoRoomParticipantProfile *p, LmiAllocator *alloc)}
	{parameter: {name: p} {description: The VidyoRoomParticipantProfile object to construct.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomParticipantProfile *VidyoRoomParticipantProfileConstructDefault(VidyoRoomParticipantProfile *p, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRoomParticipantProfileConstruct}
	{parent: VidyoRoomParticipantProfile}
	{description: Constructs an VidyoRoomParticipantProfile object.}
	{prototype: VidyoRoomParticipantProfile *VidyoRoomParticipantProfileConstruct(VidyoRoomParticipantProfile *p, const char* userId, VidyoRoomProfileControlMode microphone, VidyoRoomProfileControlMode camera, VidyoRoomProfileControlMode windowShare, VidyoRoomProfileControlMode chat, LmiAllocator *alloc)}
	{parameter: {name: p} {description: The VidyoRoomParticipantProfile object to construct.}}
	{parameter: {name: userId} {description: User ID if this is not a default profile.}}
	{parameter: {name: microphone} {description: The Microphone Profile.}}
	{parameter: {name: camera} {description: The Camera Profile.}}
	{parameter: {name: windowShare} {description: The WindowShare Profile.}}
	{parameter: {name: chat} {description: The Chat Profile.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomParticipantProfile *VidyoRoomParticipantProfileConstruct(VidyoRoomParticipantProfile *p, const char* userId, VidyoRoomProfileControlMode microphone, VidyoRoomProfileControlMode camera, VidyoRoomProfileControlMode windowShare, VidyoRoomProfileControlMode chat, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRoomParticipantProfileConstructCopy}
	{parent: VidyoRoomParticipantProfile}
	{description: Constructs an VidyoRoomParticipantProfile object as a copy of an existing object.}
	{prototype: VidyoRoomParticipantProfile *VidyoRoomParticipantProfileConstructCopy(VidyoRoomParticipantProfile *d, const VidyoRoomParticipantProfile *s)}
	{parameter: {name: d} {description: The VidyoRoomParticipantProfile object to construct.}}
	{parameter: {name: s} {description: The existing VidyoRoomParticipantProfile object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomParticipantProfile *VidyoRoomParticipantProfileConstructCopy(VidyoRoomParticipantProfile *d, const VidyoRoomParticipantProfile *s);

/**
{function visibility="private":
	{name: VidyoRoomParticipantProfileDestruct}
	{parent: VidyoRoomParticipantProfile}
	{description: Destructs an VidyoRoomParticipantProfile object.}
	{prototype: void VidyoRoomParticipantProfileDestruct(VidyoRoomParticipantProfile *p)}
	{parameter: {name: p} {description: The VidyoRoomParticipantProfile object to destruct.}}
}
*/
void VidyoRoomParticipantProfileDestruct(VidyoRoomParticipantProfile *p);

/**
{function visibility="private":
	{name: VidyoRoomParticipantProfileAssign}
	{parent: VidyoRoomParticipantProfile}
	{description: Assign the contents of one VidyoRoomParticipantProfile to another.}
	{prototype: VidyoRoomParticipantProfile *VidyoRoomParticipantProfileAssign(VidyoRoomParticipantProfile *d, const VidyoRoomParticipantProfile *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRoomParticipantProfile *VidyoRoomParticipantProfileAssign(VidyoRoomParticipantProfile *d, const VidyoRoomParticipantProfile *s);

/**
{function visibility="private":
	{name: VidyoRoomParticipantProfileEqual}
	{parent: VidyoRoomParticipantProfile}
	{description: Check the equality of VidyoRoomParticipantProfile object.}
	{prototype: LmiBool VidyoRoomParticipantProfileEqual(const VidyoRoomParticipantProfile *a, const VidyoRoomParticipantProfile *b)}
	{parameter: {name: a} {description: The VidyoRoomParticipantProfile object to compare.}}
	{parameter: {name: b} {description: The VidyoRoomParticipantProfile object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoRoomParticipantProfileEqual(const VidyoRoomParticipantProfile *a, const VidyoRoomParticipantProfile *b);

Declare_LmiVector(VidyoRoomParticipantProfile)

/**
{type visibility="public":
	{name: VidyoRoomProperties}
	{parent: VidyoRoom}
	{include: Lmi/VidyoClient/VidyoRoomProperties.h}
	{description: Properties of a room.}
	{member:
		{name: name}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: description}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: language}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: owners}
		{type: LmiVector(LmiString)}
		{description: An owner of the room. This is the highest clearance. This type of user typically has unlimited privileges in the room.}
	}
	{member:
		{name: administrators}
		{type: LmiVector(LmiString)}
		{description: An administrator in the room.}
	}
	{member:
		{name: moderators}
		{type: LmiVector(LmiString)}
		{description: A member of the room with moderator privileges. A moderator will typically have privileges such as muting users or kicking them out of the room.}
	}
	{member:
		{name: members}
		{type: LmiVector(LmiString)}
		{description: A member of the room.}
	}
	{member:
		{name: outcasts}
		{type: LmiVector(LmiString)}
		{description: The user has been banned from the room.}
	}
	{member:
		{name: isPublic}
		{type: LmiBool}
		{description: The room Public. This room will show up in searches. }
	}
	{member:
		{name: isMembersOnly}
		{type: LmiBool}
		{description: The room is for members only. A user cannot join unless they have a member or better clearance. }
	}
	{member:
		{name: isModerated}
		{type: LmiBool}
		{description: This room is moderated.}
	}
	{member:
		{name: isLoggingEnabled}
		{type: LmiBool}
		{description: The room is being logges and is on the record.}
	}
	{member:
		{name: isPasswordProtected}
		{type: LmiBool}
		{description: The room requres a password to join.}
	}
    {member:
        {name: hasPassword}
        {type: LmiBool}
        {description: if hasPassword is LMI_TRUE, password filed should be examined.
            If password field is empty, it means to clear the password, otherwise, it means set the room with this new password.}
	}
    {member:
        {name: password}
        {type: LmiString}
        {description: The password to join this room.}
	}
	{member:
		{name: maxParticipants}
		{type: LmiUint}
		{description: Maxumum number of concurrent participants.}
	}
	{member:
		{name: schedule}
		{type: VidyoRoomSchedule}
		{description: A schedule for a room in iCalendar format.}
	}
	{member:
		{name: defaultProfile}
		{type: VidyoRoomParticipantProfile}
		{description: Default profile for all participants.}
	}
	{member:
		{name: participantProfiles}
		{type: LmiVector(VidyoRoomParticipantProfile)}
		{description: Profile for specific participants.}
	}
	{member:
		{name: creationTime}
		{type: LmiTime}
		{description: Creation time of the room.}
	}
}
*/
typedef struct
{
	LmiString name;
	LmiString description;
	LmiString language;

	LmiVector(LmiString) owners;
	LmiVector(LmiString) administrators;
	LmiVector(LmiString) moderators;
	LmiVector(LmiString) members;
	LmiVector(LmiString) outcasts;

	LmiBool isPublic;
	LmiBool isMembersOnly;
	LmiBool isModerated;
	LmiBool isLoggingEnabled;
	LmiBool isPasswordProtected;
    
    LmiBool hasPassword;
    LmiString password;

	LmiUint maxParticipants;

	VidyoRoomSchedule schedule;

	VidyoRoomParticipantProfile defaultProfile;
	LmiVector(VidyoRoomParticipantProfile) participantProfiles;

	LmiTime creationTime;
} VidyoRoomProperties;

/**
{function visibility="private":
	{name: VidyoRoomPropertiesConstructDefault}
	{parent: VidyoRoomProperties}
	{description: Constructs an VidyoRoomProperties object.}
	{prototype: VidyoRoomProperties *VidyoRoomPropertiesConstructDefault(VidyoRoomProperties *p, LmiAllocator *alloc)}
	{parameter: {name: p} {description: The VidyoRoomProperties object to construct.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomProperties *VidyoRoomPropertiesConstructDefault(VidyoRoomProperties *p, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoRoomPropertiesConstructCopy}
	{parent: VidyoRoomProperties}
	{description: Constructs an VidyoRoomProperties object as a copy of an existing object.}
	{prototype: VidyoRoomProperties *VidyoRoomPropertiesConstructCopy(VidyoRoomProperties *d, const VidyoRoomProperties *s)}
	{parameter: {name: d} {description: The VidyoRoomProperties object to construct.}}
	{parameter: {name: s} {description: The existing VidyoRoomProperties object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomProperties *VidyoRoomPropertiesConstructCopy(VidyoRoomProperties *d, const VidyoRoomProperties *s);

/**
{function visibility="private":
	{name: VidyoRoomPropertiesDestruct}
	{parent: VidyoRoomProperties}
	{description: Destructs an VidyoRoomProperties object.}
	{prototype: void VidyoRoomPropertiesDestruct(VidyoRoomProperties *p)}
	{parameter: {name: p} {description: The VidyoRoomProperties object to destruct.}}
}
*/
void VidyoRoomPropertiesDestruct(VidyoRoomProperties *p);

/**
{function visibility="private":
	{name: VidyoRoomPropertiesAssign}
	{parent: VidyoRoomProperties}
	{description: Assign the contents of one VidyoRoomProperties to another.}
	{prototype: VidyoRoomProperties *VidyoRoomPropertiesAssign(VidyoRoomProperties *d, const VidyoRoomProperties *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRoomProperties *VidyoRoomPropertiesAssign(VidyoRoomProperties *d, const VidyoRoomProperties *s);

/**
{function visibility="private":
	{name: VidyoRoomPropertiesEqual}
	{parent: VidyoRoomProperties}
	{description: Check the equality of VidyoRoomProperties object.}
	{prototype: LmiBool VidyoRoomPropertiesEqual(const VidyoRoomProperties *a, const VidyoRoomProperties *b)}
	{parameter: {name: a} {description: The VidyoRoomProperties object to compare.}}
	{parameter: {name: b} {description: The VidyoRoomProperties object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoRoomPropertiesEqual(const VidyoRoomProperties *a, const VidyoRoomProperties *b);

Declare_LmiVector(VidyoRoomProperties)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRoomPropertiesInline.h"
#endif

#endif /* VIDYO_ROOMPROPERTIES_H_ */
