/** 
{file:
	{name: VidyoRoom.h}
	{description: Room Entity Library. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_ROOM_H_ 
#define VIDYO_ROOM_H_ 

#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiUnordered.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoRoomImpl_;
typedef struct VidyoRoomImpl_ VidyoRoomImpl;
Declare_LmiSharedPtr_DummyAlloc(VidyoRoomImpl)
Declare_LmiSharedPtrWrapper(VidyoRoom, VidyoRoomImpl)
Declare_LmiWeakPtrWrapper(VidyoRoomHandle, VidyoRoom, VidyoRoomImpl)
Declare_LmiUnorderedMap(LmiString, VidyoRoomHandle)
Declare_LmiList(VidyoRoom)
Declare_LmiVector(VidyoRoom)
Declare_LmiUnorderedMap(LmiString, VidyoRoom)

LMI_END_EXTERN_C
#include "VidyoChatMessage.h"
#include "VidyoLocalSpeaker.h"
#include "VidyoLocalRenderer.h"

#include "VidyoLocalMicrophone.h"
#include "VidyoLocalCamera.h"
#include "VidyoLocalWindowShare.h"
#include "VidyoLocalMonitor.h"

#include "VidyoRemoteSpeaker.h"
#include "VidyoRemoteRenderer.h"

#include "VidyoRemoteMicrophone.h"
#include "VidyoRemoteCamera.h"
#include "VidyoRemoteWindowShare.h"

#include "VidyoUser.h"
#include "VidyoParticipant.h"
#include "VidyoRoomProperties.h"
#include "VidyoRoomInfo.h"

LMI_BEGIN_EXTERN_C
/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomSearchResult}
	{parent: VidyoRoom}
	{description: Result of get room history.}
	{value: {name: VIDYO_ROOMSEARCHRESULT_OK} {description: Get room history
		operation was successful.}}
	{value: {name: VIDYO_ROOMSEARCHRESULT_NoRecords} {description: Server did
		not return any records.}}
	{value: {name: VIDYO_ROOMSEARCHRESULT_NoResponse} {description: Server did
		not respond in a reasonable amount of time to the get room history request.}}
	{value: {name: VIDYO_ROOMSEARCHRESULT_Unauthorized} {description: User did
		not have the permission to get room history.}}
	{value: {name: VIDYO_ROOMSEARCHRESULT_MiscLocalError} {description: Server is
		rejecting the request to get room history due to some miscellaneous problem with the request.}}
	{value: {name: VIDYO_ROOMSEARCHRESULT_MiscRemoteError} {description: Server is
		rejecting the request to get room history  due to some miscellaneous problem of its own.}}
}
*/
typedef enum
{
	VIDYO_ROOMSEARCHRESULT_OK,
	VIDYO_ROOMSEARCHRESULT_NoRecords,
	VIDYO_ROOMSEARCHRESULT_NoResponse,
	VIDYO_ROOMSEARCHRESULT_Unauthorized,
	VIDYO_ROOMSEARCHRESULT_MiscLocalError,
	VIDYO_ROOMSEARCHRESULT_MiscRemoteError
} VidyoRoomSearchResult;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomEnterResult}
	{parent: VidyoRoom}
	{description: Result of an attempt to enter a VidyoRoom.}
	{value: {name: VIDYO_ROOMENTERRESULT_OK} {description: Room entered successfully.}}
	{value: {name: VIDYO_ROOMENTERRESULT_Cancelled} {description: Enter request was cancelled.}}
	{value: {name: VIDYO_ROOMENTERRESULT_NoResponse} {description: Server did
		not respond in a reasonable amount of time to the request to enter the room.}}
	{value: {name: VIDYO_ROOMENTERRESULT_InvalidPassword} {description: User did not
		provide a password when one was required, or provided an invalid password.}}
	{value: {name: VIDYO_ROOMENTERRESULT_UnknownRoom} {description: Room
		specified by the user does not exist.}}
	{value: {name: VIDYO_ROOMENTERRESULT_RoomFull} {description: Room
		is at full capacity and cannot accept additional members.}}
	{value: {name: VIDYO_ROOMENTERRESULT_NotMember} {description: Room allows
		only certain users to enter, and the user is not one of them.}}
	{value: {name: VIDYO_ROOMENTERRESULT_Banned} {description: User has
		been banned from entering the room.}}
	{value: {name: VIDYO_ROOMENTERRESULT_MiscLocalError} {description: Server is
		rejecting the request to enter due to some miscellaneous problem with the request.}}
	{value: {name: VIDYO_ROOMENTERRESULT_MiscRemoteError} {description: Server is
		rejecting the request to enter due to some miscellaneous problem of its own.}}
}
*/
typedef enum
{
	VIDYO_ROOMENTERRESULT_OK,
	VIDYO_ROOMENTERRESULT_Cancelled,
	VIDYO_ROOMENTERRESULT_NoResponse,
	VIDYO_ROOMENTERRESULT_InvalidPassword,
	VIDYO_ROOMENTERRESULT_UnknownRoom,
	VIDYO_ROOMENTERRESULT_RoomFull,
	VIDYO_ROOMENTERRESULT_NotMember,
	VIDYO_ROOMENTERRESULT_Banned,
	VIDYO_ROOMENTERRESULT_MiscLocalError,
	VIDYO_ROOMENTERRESULT_MiscRemoteError
} VidyoRoomEnterResult;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomExitReason}
	{parent: VidyoRoom}
	{description: Reason why a user is no longer a participant of a VidyoRoom.}
	{value: {name: VIDYO_ROOMEXITREASON_Left} {description: Leave was invoked, and this action
		 completed successfully.}}
	{value: {name: VIDYO_ROOMEXITREASON_ConnectionLost} {description: Connectivity was lost and signaling
		 messages can no longer be sent or received.}}
	{value: {name: VIDYO_ROOMEXITREASON_SessionConnectionLost} {description: Session connectivity was lost.}}
	{value: {name: VIDYO_ROOMEXITREASON_MembershipConnectionLost} {description: Membership connectivity
		was lost.}}
	{value: {name: VIDYO_ROOMEXITREASON_NoResponse} {description: A signaling request was sent, but no
		 response was received within the allotted amount of time.}}
	{value: {name: VIDYO_ROOMEXITREASON_ProtocolViolation} {description: A signaling message was received
		 that could not be understood or otherwise violated the rules of the protocol in use.}}
	{value: {name: VIDYO_ROOMEXITREASON_Booted} {description: User was kicked out of the room. This
		 could be the result of an administrator's action.}}
	{value: {name: VIDYO_ROOMEXITREASON_ShuttingDown} {description: Room or the entire conferencing
		 service is going offline. All users are being removed from the room.}}
	{value: {name: VIDYO_ROOMEXITREASON_MiscLocalError} {description: Some miscellaneous problem occurred
		 with this application.}}
	{value: {name: VIDYO_ROOMEXITREASON_MiscRemoteError} {description: Some miscellaneous problem occurred
		 with the conferencing service.}}
}
*/
typedef enum
{
	VIDYO_ROOMEXITREASON_Left,
	VIDYO_ROOMEXITREASON_ConnectionLost,
	VIDYO_ROOMEXITREASON_SessionConnectionLost,
	VIDYO_ROOMEXITREASON_MembershipConnectionLost,
	VIDYO_ROOMEXITREASON_NoResponse,
	VIDYO_ROOMEXITREASON_ProtocolViolation,
	VIDYO_ROOMEXITREASON_Booted,
	VIDYO_ROOMEXITREASON_ShuttingDown,
	VIDYO_ROOMEXITREASON_MiscLocalError,
	VIDYO_ROOMEXITREASON_MiscRemoteError
} VidyoRoomExitReason;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomMediaFailReason}
	{parent: VidyoRoom}
	{description: This type indicates the reason why an attempt to enable media on a room failed.}
	{value: {name: VIDYO_ROOMMEDIAFAILREASON_Cancelled} {description: Media support was disabled (by calling VidyoRoomDisableMedia)
		before an attempt to enable it completed.}}
	{value: {name: VIDYO_ROOMMEDIAFAILREASON_NoConference} {description: There was an error determining which conference to join.}}
	{value:	{name: VIDYO_ROOMMEDIAFAILREASON_SignalingConnectionLost} {description: Signaling Connection lost on current transport.}}
	{value:	{name: VIDYO_ROOMMEDIAFAILREASON_MediaConnectionLost} {description: Media Connection lost on current transport.}}
	{value: {name: VIDYO_ROOMMEDIAFAILREASON_MiscLocalError} {description: Some miscellaneous problem occurred
		with this application.}}
	{value: {name: VIDYO_ROOMMEDIAFAILREASON_MiscRemoteError} {description: Some miscellaneous problem occurred
		with the conferencing service.}}
}
*/
typedef enum
{
	VIDYO_ROOMMEDIAFAILREASON_Cancelled,
	VIDYO_ROOMMEDIAFAILREASON_NoConference,
	VIDYO_ROOMMEDIAFAILREASON_SignalingConnectionLost,
	VIDYO_ROOMMEDIAFAILREASON_MediaConnectionLost,
	VIDYO_ROOMMEDIAFAILREASON_MiscLocalError,
	VIDYO_ROOMMEDIAFAILREASON_MiscRemoteError
} VidyoRoomMediaFailReason;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomMediaDisableReason}
	{parent: VidyoRoom}
	{description: This type indicates the reason why media support is now disabled on a room.}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_Disabled} {description: Media support was disabled gracefully (after calling
		VidyoRoomEnableMedia).}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_SignalingConnectionLost} {description: Signaling connectivity to the conference server was lost.}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_MediaConnectionLost} {description: Media connectivity to the conference server was lost.}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_Booted} {description: The server is ousting this member
		from the conference. This could be the result of an administrator's action.}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_SessionTerminated} {description: The session that was
		carrying the conferencing protocol has been terminated.}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_ServerShuttingDown} {description: The conference server is
		shutting down. All members of all conferences are being booted.}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_ConferenceDestroyed} {description: The conference is
		being destroyed. All members of the conference are being booted.}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_MiscLocalError} {description: Some miscellaneous problem occurred
		with this application.}}
	{value: {name: VIDYO_ROOMMEDIADISABLEREASON_MiscRemoteError} {description: Some miscellaneous problem occurred
		with the conferencing service.}}
}
*/
typedef enum
{
	VIDYO_ROOMMEDIADISABLEREASON_Disabled,
	VIDYO_ROOMMEDIADISABLEREASON_SignalingConnectionLost,
	VIDYO_ROOMMEDIADISABLEREASON_MediaConnectionLost,
	VIDYO_ROOMMEDIADISABLEREASON_Booted,
	VIDYO_ROOMMEDIADISABLEREASON_SessionTerminated,
	VIDYO_ROOMMEDIADISABLEREASON_ServerShuttingDown,
	VIDYO_ROOMMEDIADISABLEREASON_ConferenceDestroyed,
	VIDYO_ROOMMEDIADISABLEREASON_MiscLocalError,
	VIDYO_ROOMMEDIADISABLEREASON_MiscRemoteError
} VidyoRoomMediaDisableReason;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomGetPropertiesResult}
	{parent: VidyoRoom}
	{description: This type indicates the result of get room properties.}
	{value: {name: VIDYO_ROOMGETPROPERTIESRESULT_OK} {description: The get properties
		operation was successful.}}
	{value: {name: VIDYO_ROOMGETPROPERTIESRESULT_NoResponse} {description: The server did
		not respond in a reasonable amount of time to the request to get room properties.}}
	{value: {name: VIDYO_ROOMGETPROPERTIESRESULT_Unauthorized} {description: The user did
		not have permission to get room properties.}}
	{value: {name: VIDYO_ROOMGETPROPERTIESRESULT_MiscLocalError} {description: The server is
		rejecting the request to get room properties due to some miscellaneous problem with the request.}}
	{value: {name: VIDYO_ROOMGETPROPERTIESRESULT_MiscRemoteError} {description: The server is
		rejecting the request to get room properties  due to some miscellaneous problem of its own.}}
}
*/
typedef enum
{
	VIDYO_ROOMGETPROPERTIESRESULT_OK,
	VIDYO_ROOMGETPROPERTIESRESULT_NoResponse,
	VIDYO_ROOMGETPROPERTIESRESULT_Unauthorized,
	VIDYO_ROOMGETPROPERTIESRESULT_MiscLocalError,
	VIDYO_ROOMGETPROPERTIESRESULT_MiscRemoteError
} VidyoRoomGetPropertiesResult;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomSetPropertiesResult}
	{parent: VidyoRoom}
	{description: This type indicates the result of set room properties.}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_OK} {description: The set properties
		operation was successful.}}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_NoResponse} {description: The server did
		not respond in a reasonable amount of time to the request to set room properties.}}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_Conflict} {description: There was a conflict
		in setting room properties.}}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_Unauthorized} {description: The user did
		not have permission to get room properties.}}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_NotAcceptable} {description: The properties
		set on the room are not acceptable.}}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_NotAllowed} {description: The operation being
		performed on the room using set properties is not allowed.}}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_MiscLocalError} {description: The server is
		rejecting the request to set room properties due to some miscellaneous problem with the request.}}
	{value: {name: VIDYO_ROOMSETPROPERTIESRESULT_MiscRemoteError} {description: The server is
		rejecting the request to set room properties  due to some miscellaneous problem of its own.}}
}
*/
typedef enum
{
	VIDYO_ROOMSETPROPERTIESRESULT_OK,
	VIDYO_ROOMSETPROPERTIESRESULT_NoResponse,
	VIDYO_ROOMSETPROPERTIESRESULT_Conflict,
	VIDYO_ROOMSETPROPERTIESRESULT_Unauthorized,
	VIDYO_ROOMSETPROPERTIESRESULT_NotAcceptable,
	VIDYO_ROOMSETPROPERTIESRESULT_NotAllowed,
	VIDYO_ROOMSETPROPERTIESRESULT_MiscLocalError,
	VIDYO_ROOMSETPROPERTIESRESULT_MiscRemoteError
} VidyoRoomSetPropertiesResult;

/**
{type visibility="public":
    {name: VidyoRoomSetFavoriteResult}
    {parent: VidyoRoom}
    {description: This type indicates the result of set favorite room.}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_OK} {description: The set operation was successful.}}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_NoResponse} {description: The server did not respond in a reasonable amount of time to the request to set.}}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_Conflict} {description: There was a conflict in set.}}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_Unauthorized} {description: The user did not have permission to set.}}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_NotAcceptable} {description: The properties set on the room are not acceptable.}}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_NotAllowed} {description: The operation being performed on the room using set properties is not allowed.}}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_MiscLocalError} {description: The server is rejecting the request to set due to some miscellaneous problem with the request.}}
    {value: {name: VIDYO_ROOMSETFAVORITERESULT_MiscRemoteError} {description: The server isrejecting the request to set room properties due to some miscellaneous problem of its own.}}
}
*/
typedef enum
{
    VIDYO_ROOMSETFAVORITERESULT_OK,
    VIDYO_ROOMSETFAVORITERESULT_NoResponse,
    VIDYO_ROOMSETFAVORITERESULT_Conflict,
    VIDYO_ROOMSETFAVORITERESULT_Unauthorized,
    VIDYO_ROOMSETFAVORITERESULT_NotAcceptable,
    VIDYO_ROOMSETFAVORITERESULT_NotAllowed,
    VIDYO_ROOMSETFAVORITERESULT_MiscLocalError,
    VIDYO_ROOMSETFAVORITERESULT_MiscRemoteError
} VidyoRoomSetFavoriteResult;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoRoomDeleteResult}
	{parent: VidyoRoom}
	{description: This type indicates the result of delete room.}
	{value: {name: VIDYO_ROOMDELETERESULT_OK} {description: The delete room operation was successful.}}
	{value: {name: VIDYO_ROOMDELETERESULT_NoResponse} {description: The server did not respond in a reasonable amount of time to the request to delete room.}}
	{value: {name: VIDYO_ROOMDELETERESULT_Unauthorized} {description: The user did not have permission to delete room.}}
	{value: {name: VIDYO_ROOMDELETERESULT_OutOfResources} {description: The server cannot
delete rooms at the current time because it is out of some resource.}}
	{value: {name: VIDYO_ROOMDELETERESULT_MiscError} {description: Some other error occurred.}}
}
*/
typedef enum
{
	VIDYO_ROOMDELETERESULT_OK,
	VIDYO_ROOMDELETERESULT_NoResponse,
	VIDYO_ROOMDELETERESULT_Unauthorized,
	VIDYO_ROOMDELETERESULT_OutOfResources,
	VIDYO_ROOMDELETERESULT_MiscError
} VidyoRoomDeleteResult;

/**
{type:
	{name:  VidyoGenerationDiff}
	{parent: VidyoRoom}
	{description: Represents a remote participant whose selected ranking in a conference has changed.
	When the selected participant list changes, a set of these objects can be used to represent
	the differences between	the old list and the new list. Each object can indicate a new participant
	in the list, a participant that is no longer in the list, or a participant that has changed rank
	within the list.
	}
	{member:
		{name: participant}
		{type: VidyoParticipant}
		{description: }
	}
	{member:
		{name: newIndex}
		{type: LmiInt}
		{description: }
	}
	{member:
		{name: oldIndex}
		{type: LmiInt}
		{description: }
	}
}
*/
typedef struct
{
	VidyoParticipant participant;
	LmiInt newIndex;
	LmiInt oldIndex;
} VidyoGenerationDiff;

/**
{function visibility="private":
	{name: VidyoGenerationDiffConstruct}
	{parent: VidyoGenerationDiff}
	{description: Constructs a VidyoGenerationDiff object.}
	{prototype: VidyoGenerationDiff *VidyoGenerationDiffConstruct(VidyoGenerationDiff* rank, VidyoParticipant* p, LmiInt newIndex, LmiInt oldIndex, LmiAllocator *alloc)}
	{parameter: {name: rank} {description: The VidyoGenerationDiff object to construct.}}
	{parameter: {name: p} {description: The VidyoParticipant object whose rank changed.}}
	{parameter: {name: newIndex} {description: total number of users of the room.}}
	{parameter: {name: oldIndex} {description: total number of users of the room.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoGenerationDiff *VidyoGenerationDiffConstruct(VidyoGenerationDiff* rank, VidyoParticipant* p, LmiInt newIndex, LmiInt oldIndex, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoGenerationDiffConstructCopy}
	{parent: VidyoGenerationDiff}
	{description: Constructs a VidyoGenerationDiff object as a copy of an existing object.}
	{prototype: VidyoGenerationDiff* VidyoGenerationDiffConstructCopy(VidyoGenerationDiff *d, const VidyoGenerationDiff *s)}
	{parameter: {name: d} {description: The VidyoGenerationDiff object to construct.}}
	{parameter: {name: s} {description: The existing VidyoGenerationDiff object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoGenerationDiff *VidyoGenerationDiffConstructCopy(VidyoGenerationDiff *d, const VidyoGenerationDiff *s);

/**
{function visibility="private":
	{name: VidyoGenerationDiffDestruct}
	{parent: VidyoGenerationDiff}
	{description: Destructs a VidyoGenerationDiff object.}
	{prototype: void VidyoGenerationDiffDestruct(VidyoGenerationDiff *p)}
	{parameter: {name: p} {description: The VidyoGenerationDiff object to destruct.}}
}
*/
void VidyoGenerationDiffDestruct(VidyoGenerationDiff *p);

/**
{function visibility="private":
	{name: VidyoGenerationDiffAssign}
	{parent: VidyoGenerationDiff}
	{description: Assign the contents of one VidyoGenerationDiff to another.}
	{prototype: VidyoGenerationDiff *VidyoGenerationDiffAssign(VidyoGenerationDiff *d, const VidyoGenerationDiff *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoGenerationDiff *VidyoGenerationDiffAssign(VidyoGenerationDiff *d, const VidyoGenerationDiff *s);

/**
{function visibility="private":
	{name: VidyoGenerationDiffSwap}
	{parent: VidyoGenerationDiff}
	{description: Swap the contents of one VidyoGenerationDiff with other.}
	{prototype: void VidyoGenerationDiffSwap(VidyoGenerationDiff *a, VidyoGenerationDiff *b)}
	{parameter: {name: a} {description: The object to swap.}}
	{parameter: {name: b} {description: The object to swap.}}
}
*/
void VidyoGenerationDiffSwap(VidyoGenerationDiff *a, VidyoGenerationDiff *b);

/**
{function visibility="private":
	{name: VidyoGenerationDiffEqual}
	{parent: VidyoGenerationDiff}
	{description: Check the equality of VidyoGenerationDiff object.}
	{prototype: LmiBool VidyoGenerationDiffEqual(const VidyoGenerationDiff *a, const VidyoGenerationDiff *b)}
	{parameter: {name: a} {description: The VidyoGenerationDiff object to compare.}}
	{parameter: {name: b} {description: The VidyoGenerationDiff object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoGenerationDiffEqual(const VidyoGenerationDiff *a, const VidyoGenerationDiff *b);

Declare_LmiVector(VidyoGenerationDiff)


/**
{type apigroup="simple" reference-counted="yes":
	{name: VidyoRoom}
	{parent: Endpoint}
	{description: Establishes and manages a conference room. See VidyoRoomType for sescription of room types.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique ID that identifies a VidyoRoom at the server.}
	}
	{member:
		{name: type}
		{type: VidyoRoomType}
		{description: Type of VidyoRoom such as topic or Conversation.}
	}
}
*/

/**
{type visibility="private":
	{name: VidyoRoomHandle}
	{parent: VidyoRoom}
	{description: Weak reference to the VidyoRoom object.}
}
*/

/**
{callback apigroup="simple":
	{name: VidyoRoomOnEntered}
	{parent: VidyoRoom}
	{description: Callback that is triggered when entering the VidyoRoom as a result of VidyoRoomEnter() or VidyoRoomAcceptIncoming() request.}
	{prototype: void (*VidyoRoomOnEntered)(VidyoRoom* room, VidyoRoomEnterResult result)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: result}
		{description: Result of an attempt to enter the VidyoRoom. }
	}
}
*/
typedef void (*VidyoRoomOnEntered)(VidyoRoom* room, VidyoRoomEnterResult result);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnExited}
	{parent: VidyoRoom}
	{description: Callback that is triggered when the VidyoUser exited the VidyoRoom or as a result of VidyoRoomLeave() request. }
	{prototype: void (*VidyoRoomOnExited)(VidyoRoom* room, VidyoRoomExitReason reason)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: reason}
		{description: Reason why VidyoUser exited VidyoRoom. }
	}
}
*/
typedef void(*VidyoRoomOnExited)(VidyoRoom* room, VidyoRoomExitReason reason);

/**
{callback:
	{name: VidyoRoomOnMediaRouteAcquired}
	{parent: VidyoRoom}
	{description: Callback that is triggered when media route is discovered as a result of VidyoRoomAcquireMediaRoute() request. }
	{prototype: void (*VidyoRoomOnMediaRouteAcquired)(VidyoRoom* room)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
}
*/
typedef void(*VidyoRoomOnMediaRouteAcquired)(VidyoRoom* room);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMediaEnabled}
	{parent: VidyoRoom}
	{description: Callback that is triggered when media was enabled as a result of VidyoRoomEnableMedia() request. }
	{prototype: void (*VidyoRoomOnMediaEnabled)(VidyoRoom* room)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
}
*/
typedef void(*VidyoRoomOnMediaEnabled)(VidyoRoom* room);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMediaFailed}
	{parent: VidyoRoom}
	{description: Callback that is triggered when media enabling failed as a result of VidyoRoomEnableMedia() request. }
	{prototype: void (*VidyoRoomOnMediaFailed)(VidyoRoom* room, VidyoRoomMediaFailReason reason)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: reason}
		{description: Reason why media failed. }
	}
}
*/
typedef void(*VidyoRoomOnMediaFailed)(VidyoRoom* room, VidyoRoomMediaFailReason reason);


/**
{callback apigroup="simple":
	{name: VidyoRoomOnMediaDisabled}
	{parent: VidyoRoom}
	{description: Callback that is triggered when media has been disbled after a successfully enabling it with VidyoRoomEnableMedia(). }
	{prototype: void (*VidyoRoomOnMediaDisabled)(VidyoRoom* room, VidyoRoomMediaDisableReason reason)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: reason}
		{description: Reason why media had beed disabled. }
	}
}
*/
typedef void(*VidyoRoomOnMediaDisabled)(VidyoRoom* room, VidyoRoomMediaDisableReason reason);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnParticipantJoined}
	{parent: VidyoRoom}
	{description: Callback that is triggered when VidyoParticipant is entering or has been in the room when VidyoUser Entered.}
	{prototype: void (*VidyoRoomOnParticipantJoined)(VidyoRoom* room, VidyoParticipant* participant)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: participant}
		{description: Pointer to the VidyoParticipant object. }
	}
}
*/
typedef void(*VidyoRoomOnParticipantJoined)(VidyoRoom* room, VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnParticipantLeft}
	{parent: VidyoRoom}
	{description: Callback that is triggered when VidyoParticipant is leaving or is being removed when this VidyoUser Exited.}
	{prototype: void (*VidyoRoomOnParticipantLeft)(VidyoRoom* room, VidyoParticipant* participant)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: participant}
		{description: Pointer to the VidyoParticipant object.}
	}
}
*/
typedef void(*VidyoRoomOnParticipantLeft)(VidyoRoom* room, VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnDynamicParticipantChanged}
	{parent: VidyoRoom}
	{description: This callback is invoked to report that the list of dynamically selected participants in a conference has changed.}
	{prototype: void (*VidyoRoomOnDynamicParticipantChanged)(VidyoRoom* room, LmiVector(VidyoParticipant) *dynamicSelectedParticipants, LmiVector(VidyoRemoteCamera) *dynamicSelectedCameras)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: dynamicSelectedParticipants}
		{description: Order of participants that need to be rendered in the dynamic layout.}
	}
	{parameter:
		{name: dynamicSelectedCameras}
		{description: List of cameras for dynamicSelectedParticipants.}
	}
}
*/
typedef void(*VidyoRoomOnDynamicParticipantChanged)(VidyoRoom* room, LmiVector(VidyoParticipant) *dynamicSelectedParticipants, LmiVector(VidyoRemoteCamera) *dynamicSelectedCameras);

/**
 {callback apigroup="simple":
	{name: VidyoRoomOnLoudestParticipantChanged}
	{parent: VidyoRoom}
	{description: This callback is invoked to report that an audio-only participant has gain or lost loudest speaker status.}
	{prototype: void (*VidyoRoomOnLoudestParticipantChanged)(VidyoRoom* room, VidyoParticipant* participant, LmiBool isAudioOnly)}
	{parameter:
        {name: room}
        {description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
        {name: participant}
        {description: Pointer to an audio-only participant.}
	}
	{parameter:
        {name: isAudioOnly}
        {description: LMI_TRUE if the participant is audio only, otherwise LMI_FALSE}
	}
 }
 */
typedef void(*VidyoRoomOnLoudestParticipantChanged)(VidyoRoom* room, VidyoParticipant* participant, LmiBool isAudioOnly);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnGetRoomPropertiesResult}
	{parent: VidyoRoom}
	{description: Callback that is triggered when VidyoRoomGetRoomProperties() request completes. }
	{prototype: void (*VidyoRoomOnGetRoomPropertiesResult)(VidyoRoom* room, VidyoRoomGetPropertiesResult result, const VidyoRoomProperties* roomProperties)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: result}
		{description: Result of the VidyoRoomGetRoomProperties request. }
	}
	{parameter:
		{name: roomProperties}
		{description: Pointer to the VidyoRoomProperties object or NULL on failure.}
	}
}
*/
typedef void(*VidyoRoomOnGetRoomPropertiesResult)(VidyoRoom* room, VidyoRoomGetPropertiesResult result, const VidyoRoomProperties* roomProperties);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnSetRoomPropertiesResult}
	{parent: VidyoRoom}
	{description: Callback that is triggered when VidyoRoomSetProperties request completes.}
	{prototype: void (*VidyoRoomOnSetRoomPropertiesResult)(VidyoRoom* room, VidyoRoomSetPropertiesResult result)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: result}
		{description: Result of the VidyoRoomSetProperties request.}
	}
}
*/
typedef void(*VidyoRoomOnSetRoomPropertiesResult)(VidyoRoom* room, VidyoRoomSetPropertiesResult result);

/**
 {callback apigroup="simple":
	{name: VidyoRoomOnRoomPropertiesChanged}
	{parent: VidyoRoom}
	{description: Callback that is triggered when VidyoRoomProperties is changed on the server side.}
	{prototype: void (*VidyoRoomOnRoomPropertiesChanged)(VidyoRoom* room, const VidyoRoomProperties* roomProperties)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: roomProperties}
		{description: Updated room properties.}
	}
 }
 */
typedef void(*VidyoRoomOnRoomPropertiesChanged)(VidyoRoom* room, const VidyoRoomProperties* roomProperties);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnSetSubject}
	{parent: VidyoRoom}
	{description: Callback that is triggered when the subject of the VidyoRoom has changed.}
	{prototype: void (*VidyoRoomOnSetSubject)(VidyoRoom* room, const char* subject)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: subject}
		{description: New subject of the VidyoRoom.}
	}
}
*/
typedef void(*VidyoRoomOnSetSubject)(VidyoRoom* room, const char* subject);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMessageReceived}
	{parent: VidyoRoom}
	{description: Callback that is triggered for every VidyoChatMessage that was sent to the VidyoRoom by every other VidyoParticipant after the VidyoRoomOnEntered returned successfully. }
	{prototype: void (*VidyoRoomOnMessageReceived)(VidyoRoom* room, VidyoParticipant* participant, VidyoChatMessage* chatMessage)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: participant}
		{description: Pointer to the VidyoParticipant object that sent the message.}
	}
	{parameter:
		{name: chatMessage}
		{description: Pointer to the VidyoChatMessage object containing the message.}
	}
}
*/
typedef void(*VidyoRoomOnMessageReceived)(VidyoRoom* room, VidyoParticipant* participant, VidyoChatMessage* chatMessage);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMessageAcknowledged}
	{parent: VidyoRoom}
	{description: Callback that is triggered when a VidyoChatMessage is delivered to the VidyoRoom on the server. }
	{prototype: void (*VidyoRoomOnMessageAcknowledged)(VidyoRoom* room, VidyoChatMessage* chatMessage)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: chatMessage}
		{description: Pointer to the VidyoChatMessage object created by the server from VidyoRoomSendMessage() call. }
	}
	{note: The VidyoChatMessage has the messageId that was assigned by the server which can be referenced by the VidyoRoomOnMessageRead callback. Currently the only way to correlate the message that was sent with VidyoRoomSendMessage() to the acknowledged message is with the message body. }
}
*/
typedef void(*VidyoRoomOnMessageAcknowledged)(VidyoRoom* room, VidyoChatMessage* chatMessage);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMessageRead}
	{parent: VidyoRoom}
	{description: Callback that is triggered when a message that was acknowledged by the server was read by the other VidyoParticipant in the room. }
	{prototype: void (*VidyoRoomOnMessageRead)(VidyoRoom* room, VidyoParticipant* participant, LmiInt64 messageId)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: participant}
		{description: Pointer to the VidyoParticipant object that read the message.}
	}
	{parameter:
		{name: messageId}
		{description: The ID of the VidyoChatMessage that was read. }
	}
}
*/
typedef void(*VidyoRoomOnMessageRead)(VidyoRoom* room, VidyoParticipant* participant, LmiInt64 messageId);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMessageTypingIndication}
	{parent: VidyoRoom}
	{description: Callback that is triggered when typing state of a remote VidyoParticipant changes. }
	{prototype: void (*VidyoRoomOnMessageTypingIndication)(VidyoRoom* room, VidyoParticipant* participant, VidyoChatMessageTypingIndication typingIndication)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: participant}
		{description: Pointer to the VidyoParticipant object whose typing state changed. }
	}
	{parameter:
		{name: typingIndication}
		{description: New typing state of the VidyoParticipant. }
	}
}
*/
typedef void(*VidyoRoomOnMessageTypingIndication)(VidyoRoom* room, VidyoParticipant* participant, VidyoChatMessageTypingIndication typingIndication);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnGetHistoryResults}
	{parent: VidyoRoom}
	{description:  Callback that is triggered as a result of VidyoRoomGetHistory() call.}
	{prototype: void (*VidyoRoomOnGetHistoryResults)(VidyoRoom* room, const LmiVector(VidyoChatMessage) *records,
		LmiInt64 historySize, VidyoRoomSearchResult result)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: records}
		{description: Pointer to the vector of VidyoChatMessage records.}
	}
	{parameter:
		{name: historySize}
		{description: Total number of records in the room history.}
	}
	{parameter:
		{name: result}
		{description: Result of VidyoRoomGetHistory() call.}
	}
}
*/
typedef void (*VidyoRoomOnGetHistoryResults)(VidyoRoom* room, const LmiVector(VidyoChatMessage) *records,
	LmiInt64 historySize, VidyoRoomSearchResult result);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMessageSearchResults}
	{parent: VidyoRoom}
	{description: Callback that is triggered as a result of VidyoRoomSearch() call.}
	{prototype: void (*VidyoRoomOnMessageSearchResults)(VidyoRoom* room, const char* searchText, const LmiVector(VidyoChatMessage)* records, VidyoRoomSearchResult result)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: searchText}
		{description: Case insensitive text used for the search.}
	}
	{parameter:
		{name: records}
		{description: Pointer to the vector of VidyoChatMessage records.}
	}
	{parameter:
		{name: result}
		{description: Results of VidyoRoomSearch() call.}
	}
}
*/
typedef void(*VidyoRoomOnMessageSearchResults)(VidyoRoom* room, const char* searchText, const LmiVector(VidyoChatMessage)* records, VidyoRoomSearchResult result);

/**
 {callback:
	{name: VidyoRoomOnSetFavoriteResult}
	{parent: VidyoRoom}
	{description: Callback that is triggered when server acknowleges a VidyoRoom's favorite status for current logged-in user has changed. }
	{prototype: void (*VidyoRoomOnSetFavoriteResult)(VidyoRoom* room, LmiBool isFavorite, VidyoRoomSetFavoriteResult result)}
	{parameter:
        {name: room}
        {description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
        {name: isFavorite}
        {description: }
	}
    {parameter:
        {name: result}
        {description: }
	}
 }
 */
typedef void (*VidyoRoomOnSetFavoriteResult)(VidyoRoom* room, LmiBool isFavorite, VidyoRoomSetFavoriteResult result);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnDeleteResult}
	{parent: VidyoRoom}
	{description: Callback that is triggered when server acknowleges a VidyoRoom has been deleted on the server. }
	{prototype: void (*VidyoRoomOnDeleteResult)(VidyoRoom* room, VidyoRoomDeleteResult result)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: result}
		{description: result of the operation to delete the room on the server. }
	}
}
*/
typedef void(*VidyoRoomOnDeleteResult)(VidyoRoom* room, VidyoRoomDeleteResult result);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnAvailableResourcesChanged}
	{parent: VidyoRoom}
	{description: Callback that is triggered when the available resources such as CPU and bandwidth change when media is enabled. }
	{prototype: void (*VidyoRoomOnAvailableResourcesChanged)(VidyoRoom* room, LmiUint cpuEncode, LmiUint cpuDecode, LmiUint bandwidthSend, LmiUint bandwidthReceive)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: cpuEncode}
		{description: Percent of maximum CPU available to encode the streams.}
	}
	{parameter:
		{name: cpuDecode}
		{description: Percent of maximum CPU available to decode the streams.}
	}
	{parameter:
		{name: bandwidthSend}
		{description: Percentage of maximum bandwidth avaialble to transmit the streams.}
	}
	{parameter:
		{name: bandwidthReceive}
		{description: Percentage of maximum bandwidth avaialble to receive the streams.}
	}
}
*/
typedef void(*VidyoRoomOnAvailableResourcesChanged)(VidyoRoom* room, LmiUint cpuEncode, LmiUint cpuDecode, LmiUint bandwidthSend, LmiUint bandwidthReceive);

/**
{callback apigroup="simple":
	{name: VidyoRoomOnMaxRemoteSourcesChanged}
	{parent: VidyoRoom}
	{description: Callback that is triggered when maximum decoding capability changes when media is enabled. }
	{prototype: void (*VidyoRoomOnMaxRemoteSourcesChanged)(VidyoRoom* room, LmiUint maxRemoteSources)}
	{parameter:
		{name: room}
		{description: Pointer to the VidyoRoom that triggered the callback. }
	}
	{parameter:
		{name: maxRemoteSources}
		{description: Maximum number of remote video sources that can be recived both statically and dynamically.}
	}
}
*/
typedef void(*VidyoRoomOnMaxRemoteSourcesChanged)(VidyoRoom* room, LmiUint maxRemoteSources);

LmiBool VidyoRoomInitialize(void);

/**
{function visibility="private":
	{name: VidyoRoomUninitialize}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomUninitialize(void)}
}
*/
void VidyoRoomUninitialize(void);

/**
{type:
	{name: VidyoRoomState}
	{parent: VidyoRoom}
	{description: }
	{value: {name: VIDYO_ROOMSTATE_Creating} {description: }}
	{value: {name: VIDYO_ROOMSTATE_Created} {description: }}
	{value: {name: VIDYO_ROOMSTATE_Entering} {description: }}
	{value: {name: VIDYO_ROOMSTATE_Entered} {description: }}
	{value: {name: VIDYO_ROOMSTATE_MediaRouteAcquiring} {description: }}
	{value: {name: VIDYO_ROOMSTATE_MediaRouteAcquired} {description: }}
	{value: {name: VIDYO_ROOMSTATE_MediaEnabling} {description: }}
	{value: {name: VIDYO_ROOMSTATE_MediaEnabled} {description: }}
	{value: {name: VIDYO_ROOMSTATE_MediaDisabling} {description: }}
	{value: {name: VIDYO_ROOMSTATE_MediaDisabled} {description: }}
	{value: {name: VIDYO_ROOMSTATE_Exiting} {description: }}
	{value: {name: VIDYO_ROOMSTATE_Exited} {description: }}
}
*/
typedef enum {
	VIDYO_ROOMSTATE_Creating,
	VIDYO_ROOMSTATE_Created,
	VIDYO_ROOMSTATE_Entering,
	VIDYO_ROOMSTATE_Entered,
	VIDYO_ROOMSTATE_MediaRouteAcquiring,
	VIDYO_ROOMSTATE_MediaRouteAcquired,
	VIDYO_ROOMSTATE_MediaEnabling,
	VIDYO_ROOMSTATE_MediaEnabled,
	VIDYO_ROOMSTATE_MediaDisabling,
	VIDYO_ROOMSTATE_MediaDisabled,
	VIDYO_ROOMSTATE_Exiting,
	VIDYO_ROOMSTATE_Exited
} VidyoRoomState;


/**
{function apigroup="simple":
	{name: VidyoRoomConstructCopy}
	{parent: VidyoRoom}
	{description: Constructs an VidyoRoom object as a copy of another.}
	{prototype: VidyoRoom *VidyoRoomConstructCopy(VidyoRoom *obj, const VidyoRoom *other)}
	{parameter: {name: obj} {description: The VidyoRoom object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="simple":
	{name: VidyoRoomDestruct}
	{parent: VidyoRoom}
	{description: Destructs an VidyoRoom object.}
	{prototype: void VidyoRoomDestruct(VidyoRoom *obj)}
	{parameter: {name: obj} {description: The VidyoRoom object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoRoomAssign}
	{parent: VidyoRoom}
	{description: Assigns one VidyoRoom object the value of another. }
	{prototype: VidyoRoom *VidyoRoomAssign(VidyoRoom *obj, const VidyoRoom *other)}
	{parameter: {name: obj} {description: The VidyoRoom object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoRoomGetHandle}
	{parent: VidyoRoom}
	{description: }
	{prototype: const VidyoRoomHandle* VidyoRoomGetHandle(const VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
const VidyoRoomHandle* VidyoRoomGetHandle(const VidyoRoom* r);

/**
{function:
	{name: VidyoRoomSetUserData}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomSetUserData(VidyoRoom* r, LmiVoidPtr userData)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoRoomSetUserData(VidyoRoom* r, LmiVoidPtr userData);

/**
{function:
	{name: VidyoRoomGetUserData}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiVoidPtr VidyoRoomGetUserData(const VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoRoomGetUserData(const VidyoRoom* r);

/**
 {function apigroup="simple":
	{name: VidyoRoomRegisterParticipantEventListener}
	{parent: VidyoRoom}
	{description: Registers to get notified about participant events.}
	{prototype: LmiBool VidyoRoomRegisterParticipantEventListener(VidyoRoom* r, VidyoRoomOnParticipantJoined onParticipantJoined, VidyoRoomOnParticipantLeft onParticipantLeft, VidyoRoomOnDynamicParticipantChanged onDynamicParticipantChanged, VidyoRoomOnLoudestParticipantChanged onLoudestParticipantChanged)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{parameter:
		{name: onParticipantJoined}
		{description: Callback that is triggered when another participant joins a conference.}
	}
	{parameter:
		{name: onParticipantLeft}
		{description: Callback that is triggered when an existing participant leaves a conference.}
	}
	{parameter:
		{name: onDynamicParticipantChanged}
		{description: Callback that is triggered when the order of participants has changed, based on their importance according to active speech detection.}
	}
	{parameter:
		{name: onLoudestParticipantChanged}
		{description: Callback that is triggered when a new participant becomes the loudest, based on active speech detection.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomRegisterParticipantEventListener(VidyoRoom* r, VidyoRoomOnParticipantJoined onParticipantJoined, VidyoRoomOnParticipantLeft onParticipantLeft, VidyoRoomOnDynamicParticipantChanged onDynamicParticipantChanged, VidyoRoomOnLoudestParticipantChanged onLoudestParticipantChanged);

/**
 {function apigroup="simple":
	{name: VidyoRoomUnregisterParticipantEventListener}
	{parent: VidyoRoom}
	{description: Unregisters participant event notifications.}
	{prototype: LmiBool VidyoRoomUnregisterParticipantEventListener(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomUnregisterParticipantEventListener(VidyoRoom* r);

/**
 {function apigroup="simple":
	{name: VidyoRoomRegisterResourceManagerEventListener}
	{parent: VidyoRoom}
	{description: Registers to get notified about resource-management events.}
	{prototype: LmiBool VidyoRoomRegisterResourceManagerEventListener(VidyoRoom* r, VidyoRoomOnAvailableResourcesChanged onAvailableResourcesChanged, VidyoRoomOnMaxRemoteSourcesChanged onMaxRemoteSourcesChanged)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{parameter:
		{name: onAvailableResourcesChanged}
		{description: Callback that is triggered when local resource availability changes.}
	}
	{parameter:
		{name: onMaxRemoteSourcesChanged}
		{description: Callback that is triggered when the maximum number of decoded sources changes.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomRegisterResourceManagerEventListener(VidyoRoom* r, VidyoRoomOnAvailableResourcesChanged onAvailableResourcesChanged, VidyoRoomOnMaxRemoteSourcesChanged onMaxRemoteSourcesChanged);

/**
 {function apigroup="simple":
	{name: VidyoRoomUnregisterResourceManagerEventListener}
	{parent: VidyoRoom}
	{description: Unregisters resource manager event notifications.}
	{prototype: LmiBool VidyoRoomUnregisterResourceManagerEventListener(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomUnregisterResourceManagerEventListener(VidyoRoom* r);

/**
{function apigroup="simple":
	{name: VidyoRoomGetId}
	{parent: VidyoRoom}
	{description: }
	{prototype: const LmiString* VidyoRoomGetId(const VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
const LmiString* VidyoRoomGetId(const VidyoRoom* r);

/**
{function apigroup="simple":
	{name: VidyoRoomGetType}
	{parent: VidyoRoom}
	{description: }
	{prototype: VidyoRoomType VidyoRoomGetType(const VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
VidyoRoomType VidyoRoomGetType(const VidyoRoom* r);

/**
{function:
	{name: VidyoRoomGetUser}
	{parent: VidyoRoom}
	{description: }
	{prototype: VidyoUser *VidyoRoomGetUser(VidyoRoom *r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
VidyoUser *VidyoRoomGetUser(VidyoRoom *r);

/**
{function apigroup="simple":
	{name: VidyoRoomAcceptIncoming}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomAcceptIncoming(VidyoRoom* r, VidyoRoomOnEntered onEntered, VidyoRoomOnExited onExited)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: onEntered}
		{description: Callback that is triggered when the enter operation completes. This could be a successful enter or a failure due to permissions, etc.}
	}
	{parameter:
		{name: onExited}
		{description: Callback that is triggered when the room has been exited.}
	}
	{return: }
}
*/
LmiBool VidyoRoomAcceptIncoming(VidyoRoom* r, VidyoRoomOnEntered onEntered, VidyoRoomOnExited onExited);

/**
{function apigroup="simple":
	{name: VidyoRoomRejectIncoming}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomRejectIncoming(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomRejectIncoming(VidyoRoom* r);

/**
{function apigroup="simple":
	{name: VidyoRoomLeave}
	{parent: VidyoRoom}
	{description: Leaves the room. This triggers VidyoRoomOnExited.}
	{prototype: LmiBool VidyoRoomLeave(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomLeave(VidyoRoom* r);

/**
{function apigroup="simple":
	{name: VidyoRoomEnter}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomEnter(VidyoRoom *r, VidyoRoomOnEntered onEntered, VidyoRoomOnExited onExited)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: onEntered}
		{description: Callback that is triggered when the enter operation completes. This could be a successful enter or a failure due to permissions, etc.}
	}
	{parameter:
		{name: onExited}
		{description: Callback that is triggered when the room has been exited.}
	}
	{return: }
}
*/
LmiBool VidyoRoomEnter(VidyoRoom *r, VidyoRoomOnEntered onEntered, VidyoRoomOnExited onExited);

/**
 {function apigroup="simple":
	{name: VidyoRoomRegisterRoomPropertiesEventListener}
	{parent: VidyoRoom}
	{description: Registers to get notified about participant events.}
	{prototype: LmiBool VidyoRoomRegisterRoomPropertiesEventListener(VidyoRoom* r, VidyoRoomOnRoomPropertiesChanged onRoomPropertiesChanged)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{parameter:
		{name: onRoomPropertiesChanged}
		{description: Callback that is triggered when room properties have changed.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomRegisterRoomPropertiesEventListener(VidyoRoom* r, VidyoRoomOnRoomPropertiesChanged onRoomPropertiesChanged);

/**
 {function apigroup="simple":
	{name: VidyoRoomUnregisterRoomPropertiesEventListener}
	{parent: VidyoRoom}
	{description: Unregisters room properties event notifications.}
	{prototype: LmiBool VidyoRoomUnregisterRoomPropertiesEventListener(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomUnregisterRoomPropertiesEventListener(VidyoRoom* r);

/**
{function apigroup="simple":
	{name: VidyoRoomGetRoomProperties}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomGetRoomProperties(VidyoRoom* r, VidyoRoomOnGetRoomPropertiesResult onGetRoomPropertiesResult)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: onGetRoomPropertiesResult}
		{description: Callback that is triggered when get properties operation completes.}
	}
	{return: }
}
*/
LmiBool VidyoRoomGetRoomProperties(VidyoRoom* r, VidyoRoomOnGetRoomPropertiesResult onGetRoomPropertiesResult);

/**
{function apigroup="simple":
	{name: VidyoRoomSetRoomProperties}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomSetRoomProperties(VidyoRoom* r, const VidyoRoomProperties *roomProperties, VidyoRoomOnSetRoomPropertiesResult onSetRoomPropertiesResult)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: roomProperties}
		{description: }
	}
	{parameter:
		{name: onSetRoomPropertiesResult}
		{description: Callback that is triggered when set properties operation completes.}
	}
	{return: }
}
*/
LmiBool VidyoRoomSetRoomProperties(VidyoRoom* r, const VidyoRoomProperties *roomProperties, VidyoRoomOnSetRoomPropertiesResult onSetRoomPropertiesResult);

/**
{function:
	{name: VidyoRoomAcquireMediaRoute}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomAcquireMediaRoute(VidyoRoom* r, VidyoRoomOnMediaRouteAcquired onMediaRouteAcquired)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: onMediaRouteAcquired}
		{description: Callback that is triggered when the acquire media route operation is complete.}
	}
	{return: }
}
*/
LmiBool VidyoRoomAcquireMediaRoute(VidyoRoom *r, VidyoRoomOnMediaRouteAcquired onMediaRouteAcquired);

/**
{function apigroup="simple":
	{name: VidyoRoomEnableMedia}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomEnableMedia(VidyoRoom* r, VidyoRoomOnMediaEnabled onMediaEnabled, VidyoRoomOnMediaFailed onMediaFailed, VidyoRoomOnMediaDisabled onMediaDisabled)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: onMediaEnabled}
		{description: Callback that is triggered when the media has been successfully enabled.}
	}
	{parameter:
		{name: onMediaFailed}
		{description: Callback that is triggered when the could not be enabled.}
	}
	{parameter:
		{name: onMediaDisabled}
		{description: Callback that is triggered when the media has been disabled after being previously enabled sucessfully.}
	}
	{return: }
}
*/
LmiBool VidyoRoomEnableMedia(VidyoRoom *r, VidyoRoomOnMediaEnabled onMediaEnabled, VidyoRoomOnMediaFailed onMediaFailed, VidyoRoomOnMediaDisabled onMediaDisabled);

/**
{function apigroup="simple":
	{name: VidyoRoomDisableMedia}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomDisableMedia(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomDisableMedia(VidyoRoom* r);

/**
{function:
	{name: VidyoRoomSetMaxAudioSources}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomSetMaxAudioSources(VidyoRoom* r, LmiUint count)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: count}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomSetMaxAudioSources(VidyoRoom* r, LmiUint count);

/**
{function:
	{name: VidyoRoomSetMaxVideoSources}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomSetMaxVideoSources(VidyoRoom* r, LmiUint count)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: count}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomSetMaxVideoSources(VidyoRoom* r, LmiUint count);

/**
{function:
	{name: VidyoRoomSetDynamicLocalRenderer}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomSetDynamicLocalRenderer(VidyoRoom* r, const VidyoLocalRenderer* renderer)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: renderer}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomSetDynamicLocalRenderer(VidyoRoom *r, const VidyoLocalRenderer* renderer);

/**
{function:
	{name: VidyoRoomSetDynamicGenerationPosition}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomSetDynamicGenerationPosition(VidyoRoom *r, LmiUint generation, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: generation}
		{description: }
	}
	{parameter:
		{name: x}
		{description: }
	}
	{parameter:
		{name: y}
		{description: }
	}
	{parameter:
		{name: width}
		{description: }
	}
	{parameter:
		{name: height}
		{description: }
	}
	{parameter:
		{name: frameInterval}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomSetDynamicGenerationPosition(VidyoRoom *r, LmiUint generation, LmiInt x, LmiInt y, LmiUint width, LmiUint height, LmiTime frameInterval);

/**
 {function apigroup="simple":
	{name: VidyoRoomRegisterSubjectEventListener}
	{parent: VidyoRoom}
	{description: Registers to get notified about subject events.}
	{prototype: LmiBool VidyoRoomRegisterSubjectEventListener(VidyoRoom* r, VidyoRoomOnSetSubject onSetSubject)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{parameter:
		{name: onSetSubject}
		{description: Callback that is triggered when the subject has been changed.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomRegisterSubjectEventListener(VidyoRoom* r, VidyoRoomOnSetSubject onSetSubject);

/**
 {function apigroup="simple":
	{name: VidyoRoomUnregisterSubjectEventListener}
	{parent: VidyoRoom}
	{description: Unregisters subject event notifications.}
	{prototype: LmiBool VidyoRoomUnregisterSubjectEventListener(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomUnregisterSubjectEventListener(VidyoRoom* r);

/**
{function apigroup="simple":
	{name: VidyoRoomSetSubject}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomSetSubject(VidyoRoom* r, const char* subject)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: subject}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomSetSubject(VidyoRoom* r, const char* subject);

/**
 {function apigroup="simple":
	{name: VidyoRoomRegisterMessageEventListener}
	{parent: VidyoRoom}
	{description: Registers to get notified about message events.}
	{prototype: LmiBool VidyoRoomRegisterMessageEventListener(VidyoRoom* r, VidyoRoomOnMessageReceived onMessageReceived, VidyoRoomOnMessageAcknowledged onMessageAcknowledged, VidyoRoomOnMessageRead onMessageRead, VidyoRoomOnMessageTypingIndication onMessageTypingIndication)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{parameter:
		{name: onMessageReceived}
		{description: Callback that is triggered when a new message has been received.}
	}
	{parameter:
		{name: onMessageAcknowledged}
		{description: Callback that is triggered when a sent message has been acknowledged.}
	}
	{parameter:
		{name: onMessageRead}
		{description: Callback that is triggered when a sent message has been read.}
	}
	{parameter:
		{name: onMessageTypingIndication}
		{description: Callback that is triggered when a remote participant is typing.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomRegisterMessageEventListener(VidyoRoom* r, VidyoRoomOnMessageReceived onMessageReceived, VidyoRoomOnMessageAcknowledged onMessageAcknowledged, VidyoRoomOnMessageRead onMessageRead, VidyoRoomOnMessageTypingIndication onMessageTypingIndication);

/**
 {function apigroup="simple":
	{name: VidyoRoomUnregisterMessageEventListener}
	{parent: VidyoRoom}
	{description: Unregisters message event notifications.}
	{prototype: LmiBool VidyoRoomUnregisterMessageEventListener(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomUnregisterMessageEventListener(VidyoRoom* r);

/**
 {callback apigroup="simple":
	{name: VidyoRoomRecorderInCall}
	{parent: VidyoRoom}
	{description: Callback that is triggered when the call is recorded or when call recording stops.}
	{prototype: void (*VidyoRoomRecorderInCall)(VidyoRoom* r, LmiBool recorderInCall )}
	{parameter:
		{name: r}
		{description: The VidyoRoom that triggered the callback.}
	}
	{parameter:
		{name: recorderInCall}
		{description: LMI_TRUE when the call is recorded, LMI_FALSE when recording stops}
	}
}
*/
typedef void(*VidyoRoomRecorderInCall)(VidyoRoom* c, LmiBool recorderInCall );

/**
 {function apigroup="simple":
	{name: VidyoRoomRegisterRecoderInCallEventListener}
	{parent: VidyoRoom}
	{description: Registers to get notified when a a call is being recorded.}
	{prototype: LmiBool VidyoRoomRegisterRecoderInCallEventListener(VidyoRoom* r, VidyoRoomRecorderInCall onRecorderInCallChanged)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{parameter:
		{name: onRecorderInCallChanged}
		{description: Callback that is triggered when a recorder joins or leaves the call.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomRegisterRecoderInCallEventListener(VidyoRoom* r, VidyoRoomRecorderInCall onRecorderInCallChanged );

/**
 {function apigroup="simple":
	{name: VidyoRoomUnregisterRecoderInCallEventListener}
	{parent: VidyoRoom}
	{description: Unregisters recorder in call event notifications.}
	{prototype: LmiBool VidyoRoomUnregisterRecoderInCallEventListener(VidyoRoom* r)}
	{parameter:
		{name: r}
		{description: The VidyoRoom object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoRoomUnregisterRecoderInCallEventListener(VidyoRoom* r);

/**
{function apigroup="simple":
	{name: VidyoRoomSendMessage}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomSendMessage(VidyoRoom* r, const char* message)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: message}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomSendMessage(VidyoRoom* r, const char* message);

/**
{function apigroup="simple":
	{name: VidyoRoomSendMessageAcknowledged}
	{parent: VidyoRoom}
	{description: Send the acknowledgement to message in a conference room.}
	{prototype: LmiBool VidyoRoomSendMessageAcknowledged(VidyoRoom *r, LmiInt64 messageId)}
	{parameter: {name: r} {description: The room object.}}
	{parameter: {name: messageId} {description: The message id of message being acknowledged.}}
	{return: LMI_TRUE on success, LMI_FALSE if the server doesn't support the feature.}
	{note: This function is used to acknowledge all the messages until the curser specified by messageId.}
}
*/
LmiBool VidyoRoomSendMessageAcknowledged(VidyoRoom *r, LmiInt64 messageId);

/**
{function apigroup="simple":
	{name: VidyoRoomSendMessageTypingIndication}
	{parent: VidyoRoom}
	{description: Send a typing indication state to all participants of a room.}
	{prototype: LmiBool VidyoRoomSendMessageTypingIndication(VidyoRoom *r, VidyoChatMessageTypingIndication typingIndication)}
	{parameter: {name: r} {description: The room object.}}
	{parameter: {name: typingIndication} {description: The typing indication state.}}
	{return: LMI_TRUE on success, LMI_FALSE on an error.}
}
*/
LmiBool VidyoRoomSendMessageTypingIndication(VidyoRoom *r, VidyoChatMessageTypingIndication typingIndication);

/**
{function apigroup="simple":
	{name: VidyoRoomInvite}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomInvite(VidyoRoom* r, const LmiString* userId, const char* message)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: userId}
		{description: }
	}
	{parameter:
		{name: message}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomInvite(VidyoRoom* r, const LmiString* userId, const char* message);

/**
{function apigroup="simple":
	{name: VidyoRoomInviteN}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomInviteN(VidyoRoom* r, const LmiVector(LmiString)* userIds, const char* message)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: userIds}
		{description: }
	}
	{parameter:
		{name: message}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomInviteN(VidyoRoom* r, const LmiVector(LmiString)* userIds, const char* message);

/**
{function:
	{name: VidyoRoomInviteAll}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomInviteAll(VidyoRoom* r, const char* message)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: message}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomInviteAll(VidyoRoom* r, const char* message);

/**
{function visibility="private":
	{name: VidyoRoomGetRemoteRenderers}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomGetRemoteRenderers(VidyoRoom *r, LmiVector(VidyoRemoteRenderer) *renderers)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: renderers}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomGetRemoteRenderers(VidyoRoom *r, LmiVector(VidyoRemoteRenderer) *renderers);

/**
{function visibility="private":
	{name: VidyoRoomGetRemoteSpeakers}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomGetRemoteSpeakers(VidyoRoom *r, LmiVector(VidyoRemoteSpeaker) *speakers)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: speakers}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomGetRemoteSpeakers(VidyoRoom *r, LmiVector(VidyoRemoteSpeaker) *speakers);

/**
{function visibility="private":
	{name: VidyoRoomGetParticipants}
	{parent: VidyoRoom}
	{description: }
	{prototype: LmiBool VidyoRoomGetParticipants(VidyoRoom *r, LmiVector(VidyoParticipant) *participants)}
	{parameter:
		{name: r}
		{description: }
	}
	{parameter:
		{name: participants}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoRoomGetParticipants(VidyoRoom *r, LmiVector(VidyoParticipant) *participants);

/**
{function apigroup="simple":
	{name: VidyoRoomGetHistory}
	{parent: VidyoRoom}
	{description: Gets the latest history of the room.}
	{prototype: LmiBool VidyoRoomGetHistory(VidyoRoom *r, LmiUint32 numMessages, VidyoRoomOnGetHistoryResults onGetHistoryResults)}
	{parameter:
		{name: r}
		{description: The room object.}
	}
	{parameter:
		{name: numMessages}
		{description: The number of latest messages to request.}
	}
	{parameter:
		{name: onGetHistoryResults}
		{description: Callback that is triggered when history results are ready.}
	}
	{return: LMI_TRUE if the operation is successful, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoRoomGetHistory(VidyoRoom *r, LmiUint32 numMessages, VidyoRoomOnGetHistoryResults onGetHistoryResults);

/**
{function apigroup="simple":
	{name: VidyoRoomGetHistoryById}
	{parent: VidyoRoom}
	{description: Gets the history of the room before and after the messageId.}
	{prototype: LmiBool VidyoRoomGetHistoryById(VidyoRoom *r, LmiInt64 messageId, LmiUint32 numMessagesBefore, LmiUint32 numMessagesAfter, VidyoRoomOnGetHistoryResults onGetHistoryResults)}
	{parameter: {name: r} {description: The room object.}}
	{parameter: {name: messageId} {description: The ID of the message to use as an apex.}}
	{parameter: {name: numMessagesBefore} {description: The number of messages before the apex.}}
	{parameter: {name: numMessagesAfter} {description: The number of messages after the apex.}}
	{parameter:
		{name: onGetHistoryResults}
		{description: Callback that is triggered when history results are ready.}
	}
	{return: LMI_TRUE if the operation is successful, LMI_FALSE otherwise.}}
*/
LmiBool VidyoRoomGetHistoryById(VidyoRoom *r, LmiInt64 messageId, LmiUint32 numMessagesBefore, LmiUint32 numMessagesAfter, VidyoRoomOnGetHistoryResults onGetHistoryResults);

/**
{function apigroup="simple":
	{name: VidyoRoomGetHistoryByTime}
	{parent: VidyoRoom}
	{description: Gets the history of the room before and after the messageId.}
	{prototype: LmiBool VidyoRoomGetHistoryByTime(VidyoRoom *r, LmiTime time, LmiUint32 numMessagesBefore, LmiUint32 numMessagesAfter, VidyoRoomOnGetHistoryResults onGetHistoryResults)}
	{parameter: {name: r} {description: The room object.}}
	{parameter: {name: time} {description: The time to use as an apex.}}
	{parameter: {name: numMessagesBefore} {description: The number of messages before the apex.}}
	{parameter: {name: numMessagesAfter} {description: The number of messages after the apex.}}
	{parameter:
		{name: onGetHistoryResults}
		{description: Callback that is triggered when history results are ready.}
	}
	{return: LMI_TRUE if the operation is successful, LMI_FALSE otherwise.}}
*/
LmiBool VidyoRoomGetHistoryByTime(VidyoRoom *r, LmiTime time, LmiUint32 numMessagesBefore, LmiUint32 numMessagesAfter, VidyoRoomOnGetHistoryResults onGetHistoryResults);

/**
{function apigroup="simple":
	{name: VidyoRoomMessageSearch}
	{parent: VidyoRoom}
	{description: Searches the room for text messages.}
	{prototype: LmiBool VidyoRoomMessageSearch(VidyoRoom *r, const char* searchText, LmiUint index, LmiUint pageSize, VidyoRoomOnMessageSearchResults onMessageSearchResults)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: searchText}
		{description: The text to search the messages in the room.}
	}
	{parameter:
		{name: index}
		{description: The start index from which the recent rooms are required. A value of '0' represents
			rooms starting from the beginning. A value of 'n' represents rooms starting from 'n'th record.
			This is used for paging the response.}
	}
	{parameter:
		{name: pageSize}
		{description: The maximum number of room records that can be sent in the response. 
			This is used for paging the response.}
	}
	{parameter:
		{name: onMessageSearchResults}
		{description: Callback that is triggered when message search results are ready.}
	}
	{return: }
}
*/
LmiBool VidyoRoomMessageSearch(VidyoRoom *r, const char *searchText, LmiUint index, LmiUint pageSize, VidyoRoomOnMessageSearchResults onMessageSearchResults);

/**
{function:
	{name: VidyoRoomAddLocalCamera}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomAddLocalCamera(VidyoRoom *r, const VidyoLocalCamera *localCamera, LmiBool removeOthers)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localCamera}
		{description:}
	}
	{parameter:
		{name: removeOthers}
		{description:}
	}
}
*/
void VidyoRoomAddLocalCamera(VidyoRoom *r, const VidyoLocalCamera *localCamera, LmiBool removeOthers);

/**
{function:
	{name: VidyoRoomRemoveLocalCamera}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomRemoveLocalCamera(VidyoRoom *r, const VidyoLocalCamera *localCamera)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localCamera}
		{description:}
	}
}
*/
void VidyoRoomRemoveLocalCamera(VidyoRoom *r, const VidyoLocalCamera *localCamera);

/**
{function:
	{name: VidyoRoomAddLocalMicrophone}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomAddLocalMicrophone(VidyoRoom *r, const VidyoLocalMicrophone *localMicrophone, LmiBool removeOthers, LmiBool isAES)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localMicrophone}
		{description:}
	}
	{parameter:
		{name: removeOthers}
		{description:}
	}
	{parameter:
		{name: isAES}
		{description:}
	}
}
*/
void VidyoRoomAddLocalMicrophone(VidyoRoom *r, const VidyoLocalMicrophone *localMicrophone, LmiBool removeOthers, LmiBool isAES);

/**
{function:
	{name: VidyoRoomRemoveLocalMicrophone}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomRemoveLocalMicrophone(VidyoRoom *r, const VidyoLocalMicrophone *localMicrophone)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localMicrophone}
		{description:}
	}
}
*/
void VidyoRoomRemoveLocalMicrophone(VidyoRoom *r, const VidyoLocalMicrophone *localMicrophone);

/**
{function:
	{name: VidyoRoomAddLocalSpeaker}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomAddLocalSpeaker(VidyoRoom *r, const VidyoLocalSpeaker *localSpeaker, LmiBool removeOthers, LmiBool isAES)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localSpeaker}
		{description:}
	}
	{parameter:
		{name: removeOthers}
		{description:}
	}
	{parameter:
		{name: isAES}
		{description:}
	}
}
*/
void VidyoRoomAddLocalSpeaker(VidyoRoom *r, const VidyoLocalSpeaker *localSpeaker, LmiBool removeOthers, LmiBool isAES);

/**
{function:
	{name: VidyoRoomRemoveLocalSpeaker}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomRemoveLocalSpeaker(VidyoRoom *r, const VidyoLocalSpeaker *localSpeaker)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localSpeaker}
		{description:}
	}
}
*/
void VidyoRoomRemoveLocalSpeaker(VidyoRoom *r, const VidyoLocalSpeaker *localSpeaker);

/**
{function:
	{name: VidyoRoomAddLocalRenderer}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomAddLocalRenderer(VidyoRoom *r, const VidyoLocalRenderer *localRenderer, LmiBool removeOthers)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localRenderer}
		{description:}
	}
	{parameter:
		{name: removeOthers}
		{description:}
	}
}
*/
void VidyoRoomAddLocalRenderer(VidyoRoom *r, const VidyoLocalRenderer *localRenderer, LmiBool removeOthers);

/**
{function:
	{name: VidyoRoomRemoveLocalRenderer}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomRemoveLocalRenderer(VidyoRoom *r, const VidyoLocalRenderer *localRenderer)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localRenderer}
		{description:}
	}
}
*/
void VidyoRoomRemoveLocalRenderer(VidyoRoom *r, const VidyoLocalRenderer *localRenderer);

/**
{function:
	{name: VidyoRoomAddLocalWindowShare}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomAddLocalWindowShare(VidyoRoom *r, const VidyoLocalWindowShare *localWindowShare, LmiBool removeOthers)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localWindowShare}
		{description:}
	}
	{parameter:
		{name: removeOthers}
		{description:}
	}
}
*/
void VidyoRoomAddLocalWindowShare(VidyoRoom *r, const VidyoLocalWindowShare *localWindowShare, LmiBool removeOthers);

/**
{function:
	{name: VidyoRoomRemoveLocalWindowShare}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomRemoveLocalWindowShare(VidyoRoom *r, const VidyoLocalWindowShare *localWindowShare)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localWindowShare}
		{description:}
	}
}
*/
void VidyoRoomRemoveLocalWindowShare(VidyoRoom *r, const VidyoLocalWindowShare *localWindowShare);

/**
{function:
	{name: VidyoRoomAddLocalMonitor}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomAddLocalMonitor(VidyoRoom *r, const VidyoLocalMonitor *localMonitor, LmiBool removeOthers)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localMonitor}
		{description:}
	}
	{parameter:
		{name: removeOthers}
		{description:}
	}
}
*/
void VidyoRoomAddLocalMonitor(VidyoRoom *r, const VidyoLocalMonitor *localMonitor, LmiBool removeOthers);

/**
{function:
	{name: VidyoRoomRemoveLocalMonitor}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomRemoveLocalMonitor(VidyoRoom *r, const VidyoLocalMonitor *localMonitor)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: localMonitor}
		{description:}
	}
}
*/
void VidyoRoomRemoveLocalMonitor(VidyoRoom *r, const VidyoLocalMonitor *localMonitor);

/**
{function:
	{name: VidyoRoomGetSelectedLocalCameras}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomGetSelectedLocalCameras(VidyoRoom *r, LmiVector(VidyoLocalCamera)* cameras)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: cameras}
		{description:}
	}
}
*/
void VidyoRoomGetSelectedLocalCameras(VidyoRoom *r, LmiVector(VidyoLocalCamera)* cameras);

/**
{function:
	{name: VidyoRoomGetSelectedLocalMicrophones}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomGetSelectedLocalMicrophones(VidyoRoom *r, LmiVector(VidyoLocalMicrophone)* mics)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: mics}
		{description:}
	}
}
*/
void VidyoRoomGetSelectedLocalMicrophones(VidyoRoom *r, LmiVector(VidyoLocalMicrophone)* mics);

/**
{function:
	{name: VidyoRoomGetSelectedLocalSpeakers}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomGetSelectedLocalSpeakers(VidyoRoom *r, LmiVector(VidyoLocalSpeaker)* speakers)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: speakers}
		{description:}
	}
}
*/
void VidyoRoomGetSelectedLocalSpeakers(VidyoRoom *r, LmiVector(VidyoLocalSpeaker)* speakers);

/**
{function:
	{name: VidyoRoomGetSelectedLocalRenderers}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomGetSelectedLocalRenderers(VidyoRoom *r, LmiVector(VidyoLocalRenderer)* renderers)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: renderers}
		{description:}
	}
}
*/
void VidyoRoomGetSelectedLocalRenderers(VidyoRoom *r, LmiVector(VidyoLocalRenderer)* renderers);

/**
{function:
	{name: VidyoRoomGetSelectedLocalWindowShares}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomGetSelectedLocalWindowShares(VidyoRoom *r, LmiVector(VidyoLocalWindowShare)* windowShares)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: windowShares}
		{description:}
	}
}
*/
void VidyoRoomGetSelectedLocalWindowShares(VidyoRoom *r, LmiVector(VidyoLocalWindowShare)* windowShares);

/**
{function:
	{name: VidyoRoomGetSelectedLocalMonitors}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomGetSelectedLocalMonitors(VidyoRoom *r, LmiVector(VidyoLocalMonitor)* monitors)}
	{parameter:
		{name: r}
		{description: Vidyo room object.}
	}
	{parameter:
		{name: monitors}
		{description:}
	}
}
*/
void VidyoRoomGetSelectedLocalMonitors(VidyoRoom *r, LmiVector(VidyoLocalMonitor)* monitors);

/**
 {function:
	{name: VidyoRoomSetFavorite}
	{parent: VidyoRoom}
	{description: }
	{prototype: void VidyoRoomSetFavorite(VidyoRoom *r, LmiBool isFavorite, VidyoRoomOnSetFavoriteResult onSetFavoriteResult)}
	{parameter:
        {name: r}
        {description: Vidyo room object.}
	}
	{parameter:
        {name: isFavorite}
        {description:}
	}
	{parameter:
		{name: onSetFavoriteResult}
		{description: Callback that is triggered when set favorite operation completes.}
	}
 }
 */
void VidyoRoomSetFavorite(VidyoRoom *r, LmiBool isFavorite, VidyoRoomOnSetFavoriteResult onSetFavoriteResult);

/**
 {function apigroup="simple":
	{name: VidyoRoomDelete}
	{parent: VidyoRoom}
	{description: Delete a room. }
	{prototype: void VidyoRoomDelete(VidyoRoom *r, VidyoRoomOnDeleteResult onDeleteResult)}
	{parameter:
        {name: r}
        {description: Vidyo room object.}
	}
	{parameter:
		{name: onDeleteResult}
		{description: Callback that is triggered when delete operation completes.}
	}
 }
 */
void VidyoRoomDelete(VidyoRoom *r, VidyoRoomOnDeleteResult onDeleteResult);

/**
 {function:
	{name: VidyoRoomShowStatisticsDialog}
	{parent: VidyoRoom}
	{description: Shows statistics for a room. }
	{prototype: void VidyoRoomShowStatisticsDialog(VidyoRoom *r)}
	{parameter:
        {name: r}
        {description: Vidyo room object.}
	}
	{note: The dialog is a platform-specific native window that will pop up outside of the application.}
 }
 */
void VidyoRoomShowStatisticsDialog(VidyoRoom *r);

/**
 {function:
	{name: VidyoRoomHideStatisticsDialog}
	{parent: VidyoRoom}
	{description: Hides statistics for a room. }
	{prototype: void VidyoRoomHideStatisticsDialog(VidyoRoom *r)}
	{parameter:
        {name: r}
        {description: Vidyo room object.}
	}
 }
 */
void VidyoRoomHideStatisticsDialog(VidyoRoom *r);

/**
{function:
	{name: VidyoRoomGetStats}
	{parent: VidyoRoom}
	{description: Fill in data in VidyoRoomStats from a room.}
	{prototype: LmiBool VidyoRoomGetStats(VidyoRoom *r, VidyoRoomStats *stats)}
	{parameter: {name: r} {description: The room object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoRoomGetStats(VidyoRoom *r, VidyoRoomStats *stats);

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoRoomInline.h"
#endif

LMI_END_EXTERN_C

#endif /* VIDYO_ROOM_H_ */

