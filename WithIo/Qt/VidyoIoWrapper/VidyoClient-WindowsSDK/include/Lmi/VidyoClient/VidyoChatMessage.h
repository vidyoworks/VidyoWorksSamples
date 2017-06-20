/** 
{file:
	{name:  VidyoChatMessage.h}
	{description: Vidyo Chat Message. }
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
#ifndef VIDYO_CHATMESSAGE_H_
#define VIDYO_CHATMESSAGE_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C

/**
{type apigroup="connector simple" visibility="public":
	{name: VidyoChatMessageType}
	{parent: VidyoChatMessage}
	{description: Type of a message. This type will depend on the content of the message or where it originated. }
	{value: {name: VIDYO_CHATMESSAGETYPE_Chat}              {description: Text chat message from another VidyoParticipant.}}
	{value: {name: VIDYO_CHATMESSAGETYPE_MediaStart}        {description: Media was enabled in the room. This indicates that someone enabled their camera/microphone/etc and would like to escalate the VidyoRoom to audio/video.}}
	{value: {name: VIDYO_CHATMESSAGETYPE_MediaStop}         {description: Media was disabled in the room. This indicates that there are no more audio/video in the VidyoRoom.}}
}
*/
typedef enum
{
	VIDYO_CHATMESSAGETYPE_Chat,
	VIDYO_CHATMESSAGETYPE_MediaStart,
	VIDYO_CHATMESSAGETYPE_MediaStop,
} VidyoChatMessageType;

/**
{type apigroup="simple" visibility="public":
	{name:  VidyoChatMessageTypingIndication}
	{parent: VidyoChatMessage}
	{description: Typing indicator of VidyoParticipant state in the VidyoRoom.}
	{value: {name: VIDYO_CHATMESSAGETYPINGINDICATION_Active} {description: Active and responsive.}}
	{value: {name: VIDYO_CHATMESSAGETYPINGINDICATION_Composing} {description: Composing a text message.}}
	{value: {name: VIDYO_CHATMESSAGETYPINGINDICATION_Gone} {description: Closed the chat window.}}
	{value: {name: VIDYO_CHATMESSAGETYPINGINDICATION_Inactive} {description: Inactive for reasons such as the chat is out of focus.}}
	{value: {name: VIDYO_CHATMESSAGETYPINGINDICATION_Paused} {description: Paused composing a message.}}
	{value: {name: VIDYO_CHATMESSAGETYPINGINDICATION_None} {description: Not set.}}
}
*/
typedef enum
{
	VIDYO_CHATMESSAGETYPINGINDICATION_Active,
	VIDYO_CHATMESSAGETYPINGINDICATION_Composing,
	VIDYO_CHATMESSAGETYPINGINDICATION_Gone,
	VIDYO_CHATMESSAGETYPINGINDICATION_Inactive,
	VIDYO_CHATMESSAGETYPINGINDICATION_Paused,
	VIDYO_CHATMESSAGETYPINGINDICATION_None,
} VidyoChatMessageTypingIndication;

/**
{type apigroup="connector simple" visibility="public":
	{name: VidyoChatMessageSenderType}
	{parent: VidyoChatMessage}
	{description: Type of the VidyoChatMessage sender.}
	{value: {name: VIDYO_CHATMESSAGESENDERTYPE_User} {description: VidyoChatMessage is from a VidyoUser represented by VidyoParticipant in VidyoRoom/VidyoCall.}}
	{value: {name: VIDYO_CHATMESSAGESENDERTYPE_Room} {description: VidyoChatMessage is from a VidyoRoom.}}
	{value: {name: VIDYO_CHATMESSAGESENDERTYPE_System} {description: VidyoChatMessage is from the system.}}
	{value: {name: VIDYO_CHATMESSAGESENDERTYPE_None} {description: Sender type is not set.}}
}
*/
typedef enum
{
	VIDYO_CHATMESSAGESENDERTYPE_User,
	VIDYO_CHATMESSAGESENDERTYPE_Room,
	VIDYO_CHATMESSAGESENDERTYPE_System,
	VIDYO_CHATMESSAGESENDERTYPE_None,
} VidyoChatMessageSenderType;

/**
{type apigroup="connector simple" visibility="public":
	{name:  VidyoChatMessage}
	{parent: Endpoint}
	{include: Lmi/VidyoClient/VidyoChatMessage.h}
	{description: Contains the text message and additional information about who sent it and when.}
	{member:
		{name: userId}
		{type: LmiString}
		{description: Unique ID of a VidyoParticipant who sent the message or NULL depending on the VidyoChatMessageSenderType. }
	}
	{member:
		{name: senderType}
		{type: VidyoChatMessageSenderType}
		{description: The type of the sender. }
	}
	{member:
		{name: id}
		{type: LmiInt64}
		{description: Unique ID of the VidyoChatMessage. }
	}
	{member:
		{name: body}
		{type: LmiString}
		{description: The body of the VidyoChatMessage. }
	}
	{member:
		{name: type}
		{type: VidyoChatMessageType}
		{description: The type of VidyoChatMessage. }
	}
	{member:
		{name: timestamp}
		{type: LmiTime}
		{description: The time when the message was created. }
	}
}
*/
typedef struct
{
	LmiString userId; /* empty if from server or component */
	VidyoChatMessageSenderType senderType;
	LmiInt64 id;
	LmiString body;
	VidyoChatMessageType type;
	LmiTime timestamp;
} VidyoChatMessage;

/**
{function visibility="private":
	{name: VidyoChatMessageConstruct}
	{parent: VidyoChatMessage}
	{description: Constructs the VidyoChatMessage.}
	{prototype: VidyoChatMessage *VidyoChatMessageConstruct(VidyoChatMessage *c, const LmiString *senderId, VidyoChatMessageSenderType senderType, LmiInt64 id, const LmiString *body, VidyoChatMessageType type, LmiTime timestamp, LmiAllocator *alloc)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{parameter: {name: senderId} {description: Unique ID of a VidyoParticipant who sent the message or NULL depending on the VidyoChatMessageSenderType.}}
	{parameter: {name: senderType} {description: Type of the sender.}}
	{parameter: {name: id} {description: Unique ID of the VidyoChatMessage.}}
	{parameter: {name: body} {description: The body of the VidyoChatMessage.}}
	{parameter: {name: type} {description: The type of VidyoChatMessage.}}
	{parameter: {name: timestamp} {description: The time when the message was created.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoChatMessage *VidyoChatMessageConstruct(VidyoChatMessage *c, const LmiString *senderId, VidyoChatMessageSenderType senderType, LmiInt64 id, const LmiString *body, VidyoChatMessageType type, LmiTime timestamp, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoChatMessageConstructCopy}
	{parent: VidyoChatMessage}
	{description: Constructs an VidyoChatMessage object as a copy of another.}
	{prototype: VidyoChatMessage *VidyoChatMessageConstructCopy(VidyoChatMessage *d, const VidyoChatMessage *s)}
	{parameter: {name: d} {description: Pointer to the VidyoChatMessage object to construct.}}
	{parameter: {name: s} {description: Pointer to the VidyoChatMessage object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoChatMessage *VidyoChatMessageConstructCopy(VidyoChatMessage *d, const VidyoChatMessage *s);

/**
{function visibility="private":
	{name: VidyoChatMessageDestruct}
	{parent: VidyoChatMessage}
	{description: Destructs an VidyoChatMessage object.}
	{prototype: void VidyoChatMessageDestruct(VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
}
*/
void VidyoChatMessageDestruct(VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageAssign}
	{parent: VidyoChatMessage}
	{description: Assigns one VidyoChatMessage object the value of another.}
	{prototype: VidyoChatMessage *VidyoChatMessageAssign(VidyoChatMessage *d, const VidyoChatMessage *s)}
	{parameter: {name: d} {description: Pointer to the VidyoChatMessage object.}}
	{parameter: {name: s} {description: Pointer to the VidyoChatMessage object to assign.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoChatMessage *VidyoChatMessageAssign(VidyoChatMessage *d, const VidyoChatMessage *s);

/**
{function visibility="private":
	{name: VidyoChatMessageEqual}
	{parent: VidyoChatMessage}
	{description: Compares the values of two VidyoChatMessage objects for equality.}
	{prototype: LmiBool VidyoChatMessageEqual(const VidyoChatMessage* a, const VidyoChatMessage* b)}
	{parameter: 
		{name: a}
		{description: Pointer to the first VidyoChatMessage object to be compared.}
	}
	{parameter: 
		{name: b}
		{description: Pointer to the second VidyoChatMessage object to be compared.}
	}
	{return: LMI_TRUE if the objects pointed to are equal, otherwise LMI_FALSE.}
}
*/
LMI_INLINE_DECLARATION LmiBool VidyoChatMessageEqual(const VidyoChatMessage* a, const VidyoChatMessage* b);

/**
{function visibility="private":
	{name: VidyoChatMessageLess}
	{parent: VidyoChatMessage}
	{description: Finds out if the given VidyoChatMessage object is less than the other object.}
	{prototype: LmiBool VidyoChatMessageLess(const VidyoChatMessage* a, const VidyoChatMessage* b)}
	{parameter: 
		{name: a}
		{description: Pointer to the VidyoChatMessage object.}
	}
	{parameter: 
		{name: b}
		{description: Pointer to the VidyoChatMessage object to be checked against.}
	}
	{return: Returns LMI_TRUE if the object is less, otherwise LMI_FALSE.}
}
*/
LMI_INLINE_DECLARATION LmiBool VidyoChatMessageLess(const VidyoChatMessage* a, const VidyoChatMessage* b);

/**
{function visibility="private":
	{name: VidyoChatMessageGetSenderId}
	{parent: VidyoChatMessage}
	{description: Gets the unique ID of the message sender.}
	{prototype: const LmiString *VidyoChatMessageGetSenderId(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: Pointer to the Unique ID of the message sender.}
}
*/
const LmiString *VidyoChatMessageGetSenderId(const VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageGetSenderIdCStr}
	{parent: VidyoChatMessage}
	{description: Gets the unique ID of the message sender.}
	{prototype: const char *VidyoChatMessageGetSenderIdCStr(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: Pointer to the Unique ID of the message sender. }
}
*/
const char *VidyoChatMessageGetSenderIdCStr(const VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageGetSenderType}
	{parent: VidyoChatMessage}
	{description: Gets the type of the message sender.}
	{prototype: VidyoChatMessageSenderType VidyoChatMessageGetSenderType(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: Type of the message sender.}
}
*/
LMI_INLINE_DECLARATION VidyoChatMessageSenderType VidyoChatMessageGetSenderType(const VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageGetId}
	{parent: VidyoChatMessage}
	{description: Gets the unique ID of the message.}
	{prototype: LmiInt64 VidyoChatMessageGetId(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: Unique ID of the message.}
}
*/
LMI_INLINE_DECLARATION LmiInt64 VidyoChatMessageGetId(const VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageGetBody}
	{parent: VidyoChatMessage}
	{description: Gets the body of the message.}
	{prototype: const LmiString *VidyoChatMessageGetBody(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: Pointer to the body of the message.}
}
*/
LMI_INLINE_DECLARATION const LmiString *VidyoChatMessageGetBody(const VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageGetBodyCStr}
	{parent: VidyoChatMessage}
	{description: Gets the body of the message.}
	{prototype: const char *VidyoChatMessageGetBodyCStr(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: Pointer to the body of the message.}
}
*/
LMI_INLINE_DECLARATION const char *VidyoChatMessageGetBodyCStr(const VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageGetType}
	{parent: VidyoChatMessage}
	{description: Gets the type of the message.}
	{prototype: VidyoChatMessageType VidyoChatMessageGetType(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: The type of the message.}
}
*/
LMI_INLINE_DECLARATION VidyoChatMessageType VidyoChatMessageGetType(const VidyoChatMessage *c);

/**
{function visibility="private":
	{name: VidyoChatMessageGetTimestamp}
	{parent: VidyoChatMessage}
	{description: Gets the timestamp of the message.}
	{prototype: LmiTime VidyoChatMessageGetTimestamp(const VidyoChatMessage *c)}
	{parameter: {name: c} {description: Pointer to the VidyoChatMessage object.}}
	{return: Timestamp of the message.}
}
*/
LMI_INLINE_DECLARATION LmiTime VidyoChatMessageGetTimestamp(const VidyoChatMessage *c);

Declare_LmiVector(VidyoChatMessage)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoChatMessageInline.h"
#endif

#endif /* VIDYO_CHATMESSAGE_H_ */
