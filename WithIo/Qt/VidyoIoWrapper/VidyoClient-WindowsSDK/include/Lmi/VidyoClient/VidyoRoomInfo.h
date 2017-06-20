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
#ifndef VIDYO_ROOMINFO_H_
#define VIDYO_ROOMINFO_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Os/LmiTime.h>
#include "VidyoChatMessage.h"
LMI_BEGIN_EXTERN_C

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomType}
	{parent: VidyoRoom}
	{description: This indicates the type of the room.}
	{value: {name: VIDYO_ROOMTYPE_Unknown} {description: This indicates that room type is unknown.}}
	{value: {name: VIDYO_ROOMTYPE_Conversation} {description: This room is for private chat between users speicfied in the VidyoUserGetConversationRoom method. It is auto-created and the access is permanently limited to the list of users specified so that no other participants can be invited outside of the original user list. If the list of users needs to be modified, another CONVERSATION room must be created with the new list.}}
	{value: {name: VIDYO_ROOMTYPE_Topic} {description: This room is created using the VidyoUserCreateTopicRoom method for topic discussions. The user creating the room will usually become the owner and can moderate/invite other users. The access and properties of this room can be modified by privileged users and others can join/leave this room based on those properties such as guest access or member only. }}
	{value: {name: VIDYO_ROOMTYPE_Scheduled} {description: This indicates that room is of type scheduled.}}
}
*/
typedef enum
{
	VIDYO_ROOMTYPE_Unknown,
	VIDYO_ROOMTYPE_Conversation,
	VIDYO_ROOMTYPE_Topic,
	VIDYO_ROOMTYPE_Scheduled,
} VidyoRoomType;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomInfo}
	{parent: Endpoint}
	{include: Lmi/VidyoClient/VidyoRoomInfo.h}
	{description: descriptive details of a room.}
	{member:
		{name: id}
		{type: LmiString}
		{description:}
	}
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
		{name: type}
		{type: VidyoRoomType}
		{description:}
	}
	{member:
		{name: IsPublic}
		{type: LmiBool}
		{description:}
	}
    {member:
        {name: IsFavorite}
        {type: LmiBool}
        {description:}
	}
	{member:
		{name: numUsers}
		{type: LmiInt}
		{description: Total number of users of the room.}
	}
	{member:
		{name: ownerList}
		{type: LmiVector(LmiString)}
		{description: List of owners of the room.}
	}
	{member:
		{name: userList}
		{type: LmiVector(LmiString)}
		{description: few people ever joined the room.}
	}
	{member:
		{name: messageList}
		{type: LmiVector(VidyoChatMessage)}
		{description: few messages send in the room.}
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
	LmiString id;
	LmiString name;
	LmiString description;
	LmiString language;
	VidyoRoomType type;
	LmiBool IsPublic;
    LmiBool IsFavorite;
	LmiInt numUsers;
	LmiVector(LmiString) ownerList;
	LmiVector(LmiString) userList;
	LmiVector(VidyoChatMessage) messageList;
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
													LmiBool IsPublic, LmiBool IsFavorite, LmiInt numUsers, LmiVector(LmiString)* ownerList, LmiVector(LmiString)* userList, LmiVector(VidyoChatMessage)* messageList, LmiTime creationTime, LmiAllocator *alloc)}
	{parameter: {name: info} {description: The VidyoRoomInfo object to construct.}}
	{parameter: {name: id} {description: id of room.}}
	{parameter: {name: name} {description: name of room.}}
	{parameter: {name: description} {description: description of room.}}
	{parameter: {name: language} {description: language of room.}}
	{parameter: {name: type} {description: type of room.}}
	{parameter: {name: IsPublic} {description: visibility of room.}}
    {parameter: {name: IsFavorite} {description: whether the room is in user's favorite list.}}
	{parameter: {name: numUsers} {description: total number of users of the room.}}
	{parameter: {name: ownerList} {description: owners of the room.}}
	{parameter: {name: userList} {description: few users of room.}}
	{parameter: {name: messageList} {description: few messages shared in the room.}}
	{parameter: {name: creationTime} {description: creation time of room.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoRoomInfo *VidyoRoomInfoConstruct(VidyoRoomInfo* info, LmiString* id, LmiString* name, LmiString* description, LmiString* language, VidyoRoomType type,
	LmiBool IsPublic, LmiBool IsFavorite, LmiInt numUsers, LmiVector(LmiString)* ownerList, LmiVector(LmiString)* userList, LmiVector(VidyoChatMessage)* messageList, LmiTime creationTime, LmiAllocator *alloc);


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
