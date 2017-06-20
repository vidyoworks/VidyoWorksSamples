/**
{file:
{name: VidyoRoomInfo.h}
{description: Vidyo Room Descriptive Information. }
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
#ifndef VIDYO_MEETING_PROPERTIES_H_ 
#define VIDYO_MEETING_PROPERTIES_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Os/LmiTime.h>
#include "VidyoUser.h"

LMI_BEGIN_EXTERN_C


/**
{type visibility="public":
	{name: VidyoMeetingProperties}
	{parent: VidyoMeeting}
	{include: Lmi/VidyoClient/VidyoMeetingProperties.h}
	{description: descriptive details of a meeting.}
	{member:
		{name: id}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: organizer}
		{type: VidyoUser}
		{description:}
	}
	{member:
		{name: subject}
		{type: LmiString}
		{description: Subject of the meeting}
	}
	{member:
		{name: attendeeList}
		{type: LmiVector(LmiString)}
		{description: few people ever joined the room.}
	}
	{member:
		{name: creationTime}
		{type: LmiTime}
		{description: Creation time of the meeting.}
	}
}
*/
typedef struct
{
	LmiString id;
	VidyoUser organizer;
	LmiString subject;
	LmiString language;
	LmiVector(LmiString) attendeeList;
	LmiTime creationTime;
} VidyoRoomInfo;

/**
{function visibility="private":
{name: VidyoRoomInfoConstructDefault}
{parent: VidyoRoomInfo}
{description: Constructs a VidyoRoomInfo object.}
{prototype: VidyoRoomInfo* VidyoRoomInfoConstructDefault(VidyoRoomInfo *info, LmiAllocator *alloc)}
{parameter: {name: info} {description: The VidyoRoomInfo object to construct.}}
{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomInfo *VidyoRoomInfoConstructDefault(VidyoRoomInfo* info, LmiAllocator *alloc);

/**
{function visibility="private":
{name: VidyoRoomInfoConstruct}
{parent: VidyoRoomInfo}
{description: Constructs a VidyoRoomInfo object.}
{prototype: VidyoRoomInfo *VidyoRoomInfoConstruct(VidyoRoomInfo* info, LmiString* id, LmiString* name, LmiString* description, LmiString* language, VidyoRoomType type,
LmiBool IsPublic, LmiInt numUsers, LmiVector(LmiString)* userList, LmiVector(LmiString)* messageList, LmiTime creationTime, LmiAllocator *alloc)}
{parameter: {name: info} {description: The VidyoRoomInfo object to construct.}}
{parameter: {name: id} {description: id of room.}}
{parameter: {name: name} {description: name of room.}}
{parameter: {name: description} {description: description of room.}}
{parameter: {name: language} {description: language of room.}}
{parameter: {name: type} {description: type of room.}}
{parameter: {name: IsPublic} {description: visibility of room.}}
{parameter: {name: numUsers} {description: total number of users of the room.}}
{parameter: {name: userList} {description: few users of room.}}
{parameter: {name: messageList} {description: few messages shared in the room.}}
{parameter: {name: creationTime} {description: creation time of room.}}
{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomInfo *VidyoRoomInfoConstruct(VidyoRoomInfo* info, LmiString* id, LmiString* name, LmiString* description, LmiString* language, VidyoRoomType type,
	LmiBool IsPublic, LmiInt numUsers, LmiVector(LmiString)* userList, LmiVector(LmiString)* messageList, LmiTime creationTime, LmiAllocator *alloc);


/**
{function visibility="private":
{name: VidyoRoomInfoConstructCopy}
{parent: VidyoRoomInfo}
{description: Constructs a VidyoRoomInfo object as a copy of an existing object.}
{prototype: VidyoRoomInfo* VidyoRoomInfoConstructCopy(VidyoRoomInfo *d, const VidyoRoomInfo *s)}
{parameter: {name: d} {description: The VidyoRoomInfo object to construct.}}
{parameter: {name: s} {description: The existing VidyoRoomInfo object to copy.}}
{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomInfo *VidyoRoomInfoConstructCopy(VidyoRoomInfo *d, const VidyoRoomInfo *s);

/**
{function visibility="private":
{name: VidyoRoomInfoDestruct}
{parent: VidyoRoomInfo}
{description: Destructs an VidyoRoomInfo object.}
{prototype: void VidyoRoomInfoDestruct(VidyoRoomInfo *p)}
{parameter: {name: p} {description: The VidyoRoomInfo object to destruct.}}
}
*/
void VidyoRoomInfoDestruct(VidyoRoomInfo *p);

/**
{function visibility="private":
{name: VidyoRoomInfoAssign}
{parent: VidyoRoomInfo}
{description: Assign the contents of one VidyoRoomInfo to another.}
{prototype: VidyoRoomInfo *VidyoRoomInfoAssign(VidyoRoomInfo *d, const VidyoRoomInfo *s)}
{parameter: {name: d} {description: The object to assign to.}}
{parameter: {name: s} {description: The object to copy.}}
{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoRoomInfo *VidyoRoomInfoAssign(VidyoRoomInfo *d, const VidyoRoomInfo *s);

/**
{function visibility="private":
{name: VidyoRoomInfoEqual}
{parent: VidyoRoomInfo}
{description: Check the equality of VidyoRoomInfo object.}
{prototype: LmiBool VidyoRoomInfoEqual(const VidyoRoomInfo *a, const VidyoRoomInfo *b)}
{parameter: {name: a} {description: The VidyoRoomInfo object to compare.}}
{parameter: {name: b} {description: The VidyoRoomInfo object to compare.}}
{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoRoomInfoEqual(const VidyoRoomInfo *a, const VidyoRoomInfo *b);

Declare_LmiVector(VidyoRoomInfo)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRoomInfoInline.h"
#endif

#endif /* VIDYO_ROOMINFO_H_ */
