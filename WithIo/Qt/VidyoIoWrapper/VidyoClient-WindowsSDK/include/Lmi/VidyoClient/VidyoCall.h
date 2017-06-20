/** 
{file:
	{name: VidyoCall.h}
	{description: Call Entity Library. }
	{copyright:
		(c) 2013-2015 Vidyo, Inc.,
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
#ifndef VIDYO_CALL_H_ 
#define VIDYO_CALL_H_ 

#include <Lmi/Os/LmiSharedPtr.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiUnordered.h>

LMI_BEGIN_EXTERN_C

struct VidyoCallImpl_;
typedef struct VidyoCallImpl_ VidyoCallImpl;
Declare_LmiSharedPtr(VidyoCallImpl)
Declare_LmiSharedPtrWrapper(VidyoCall, VidyoCallImpl)
Declare_LmiWeakPtrWrapper(VidyoCallHandle, VidyoCall, VidyoCallImpl)
Declare_LmiUnorderedMap(LmiString, VidyoCallHandle)
Declare_LmiList(VidyoCall)
Declare_LmiVector(VidyoCall)

LMI_END_EXTERN_C

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


LMI_BEGIN_EXTERN_C

/**
{type visibility="public":
	{name: VidyoCallInitiatedResult}
	{parent: VidyoCall}
	{description: Result of an attempt to enter a VidyoCall.}
	{value: {name: VIDYO_CALLINITIATEDRESULT_OK} {description: Call entered successfully.}}
	{value: {name: VIDYO_CALLINITIATEDRESULT_Cancelled} {description: Enter request was cancelled.}}
	{value: {name: VIDYO_CALLINITIATEDRESULT_NoResponse} {description: Server did
		not respond in a reasonable amount of time to the request to enter the room.}}
	{value: {name: VIDYO_CALLINITIATEDRESULT_UnknownParticipant} {description: Call
		specified by the user does not exist.}}
	{value: {name: VIDYO_CALLINITIATEDRESULT_MiscLocalError} {description: Server is
		rejecting the request to enter due to some miscellaneous problem with the request.}}
	{value: {name: VIDYO_CALLINITIATEDRESULT_MiscRemoteError} {description: Server is
		rejecting the request to enter due to some miscellaneous problem of its own.}}
}
*/
typedef enum
{
	VIDYO_CALLINITIATEDRESULT_OK,
	VIDYO_CALLINITIATEDRESULT_Cancelled,
	VIDYO_CALLINITIATEDRESULT_NoResponse,
	VIDYO_CALLINITIATEDRESULT_UnknownParticipant,
	VIDYO_CALLINITIATEDRESULT_MiscLocalError,
	VIDYO_CALLINITIATEDRESULT_MiscRemoteError
} VidyoCallInitiatedResult;

/**
{type visibility="public":
	{name: VidyoCallEndReason}
	{parent: VidyoCall}
	{description: Reasons why a VidyoCall is ending.}
	{value: {name: VIDYO_CALLENDREASON_Ended} {description: Call was terminated locally.}}
	{value: {name: VIDYO_CALLENDREASON_ConnectionFailed} {description: Local entity
		could not establish a signaling connection to its peer.}}
	{value: {name: VIDYO_CALLENDREASON_ConnectionLost} {description: Signaling connection
		was lost between the local entity and its peer.}}
	{value: {name: VIDYO_CALLENDREASON_ParticipantBusy} {description: Remote peer is busy
		and cannot accept the call.}}
	{value: {name: VIDYO_CALLENDREASON_ParticipantRejected} {description: Remote peer rejected
		the call.}}
	{value: {name: VIDYO_CALLENDREASON_ParticipantEnded} {description: Local entity
		had a call and the remote peer ended it.}}
	{value: {name: VIDYO_CALLENDREASON_MiscError} {description: Miscellaneous error occurred.}}
}
*/
typedef enum
{
	VIDYO_CALLENDREASON_Ended,
	VIDYO_CALLENDREASON_ConnectionFailed,
	VIDYO_CALLENDREASON_ConnectionLost,
	VIDYO_CALLENDREASON_ParticipantBusy,
	VIDYO_CALLENDREASON_ParticipantRejected,
	VIDYO_CALLENDREASON_ParticipantEnded,
	VIDYO_CALLENDREASON_MiscError,
} VidyoCallEndReason;

/**
{type reference-counted="yes":
	{name: VidyoCall}
	{parent: Endpoint}
	{description: Establishes and manages a point-to-point call.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique ID of the VidyoCall.}
	}
}
*/

/**
{type visibility="private":
	{name: VidyoCallHandle}
	{parent: VidyoCall}
	{description: Weak reference to the VidyoCall object.}
}
*/

/**
{callback:
	{name: VidyoCallOnInitiated}
	{parent: VidyoCall}
	{description: Callback that is triggered when initiating a VidyoCall. }
	{prototype: void (*VidyoCallOnInitiated)(VidyoCall* c, VidyoCallInitiatedResult result, VidyoParticipant* p)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall that triggered the callback. }
	}
	{parameter:
		{name: result}
		{description: Result of an attempt to initiate the VidyoCall. }
	}
	{parameter:
		{name: p}
		{description: Pointer to the VidyoParticipant object of the user being called. }
	}
}
*/
typedef void(*VidyoCallOnInitiated)(VidyoCall* c, VidyoCallInitiatedResult result, VidyoParticipant* p);

/**
{callback:
	{name: VidyoCallOnEnded}
	{parent: VidyoCall}
	{description: Callback that is triggered when VidyoCall has ended.}
	{prototype: void (*VidyoCallOnEnded)(VidyoCall* c, VidyoParticipant* p, VidyoCallEndReason reason)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall that triggered the callback.}
	}
	{parameter:
		{name: p}
		{description: Pointer to the VidyoParticipant object of the user being called.}
	}
	{parameter:
		{name: reason}
		{description: Reason why the VidyoCall ended. }
	}
}
*/
typedef void(*VidyoCallOnEnded)(VidyoCall* c, VidyoParticipant* p, VidyoCallEndReason reason);

/**
{callback:
	{name: VidyoCallOnSetSubject}
	{parent: VidyoCall}
	{description: Callback that is triggered when the subject of the VidyoCall has changed. }
	{prototype: void (*VidyoCallOnSetSubject)(VidyoCall* c, const char* subject)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall that triggered the callback.}
	}
	{parameter:
		{name: subject}
		{description: New subject of the VidyoCall. }
	}
}
*/
typedef void(*VidyoCallOnSetSubject)(VidyoCall* c, const char* subject);

/**
{callback:
	{name: VidyoCallOnMessageReceived}
	{parent: VidyoCall}
	{description: Callback that is triggered when a new text message arrives. }
	{prototype: void (*VidyoCallOnMessageReceived)(VidyoCall* c, VidyoParticipant* participant, VidyoChatMessage* chatMessage)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall that triggered the callback.}
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
typedef void(*VidyoCallOnMessageReceived)(VidyoCall* c, VidyoParticipant* participant, VidyoChatMessage* chatMessage);

/**
{callback:
	{name: VidyoCallOnMessageAcknowledged}
	{parent: VidyoCall}
	{description: Callback that is triggered when a VidyoChatMessage is delivered to the VidyoCall on the server. }
	{prototype: void (*VidyoCallOnMessageAcknowledged)(VidyoCall* c, VidyoChatMessage* chatMessage)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall that triggered the callback. }
	}
	{parameter:
		{name: chatMessage}
		{description: Pointer to the VidyoChatMessage object created by the server from VidyoCallSendMessage() call. }
	}
	{note: The VidyoChatMessage has the messageId that was assigned by the server which can be referenced by the VidyoCallOnMessageRead callback. Currently the only way to correlate the message that was sent with VidyoCallSendMessage() to the acknowledged message is with the message body. }
}
*/
typedef void(*VidyoCallOnMessageAcknowledged)(VidyoCall* c, VidyoChatMessage* chatMessage);

/**
{callback:
	{name: VidyoCallOnMessageRead}
	{parent: VidyoCall}
	{description: Callback that is triggered when a message that was acknowledged by the server was read by the other VidyoParticipant in the room. }
	{prototype: void (*VidyoCallOnMessageRead)(VidyoCall* c, VidyoParticipant* participant, LmiInt64 messageId)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall that triggered the callback. }
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
typedef void(*VidyoCallOnMessageRead)(VidyoCall* c, VidyoParticipant* participant, LmiInt64 messageId);

/**
{callback:
	{name: VidyoCallOnMessageTypingIndication}
	{parent: VidyoCall}
	{description: Callback that is triggered when typing state of a remote VidyoParticipant changes. }
	{prototype: void (*VidyoCallOnMessageTypingIndication)(VidyoCall* c, VidyoParticipant* participant, VidyoChatMessageTypingIndication typingIndication)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall that triggered the callback. }
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
typedef void(*VidyoCallOnMessageTypingIndication)(VidyoCall* c, VidyoParticipant* participant, VidyoChatMessageTypingIndication typingIndication);

/**
{function visibility="private":
	{name: VidyoCallInitialize}
	{parent: VidyoCall}
	{description: Initialize all VidyoCall related functionalities of the VidyoClient library.}
	{prototype: LmiBool VidyoCallInitialize(void)}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: This function is not reentrant.}
	{note: This function may be called multiple times as long as its corresponding uninitialize function is called the same number of times.}
}
*/
LmiBool VidyoCallInitialize(void);

/**
{function visibility="private":
	{name: VidyoCallUninitialize}
	{parent: VidyoCall}
	{description: Uninitialize all VidyoCall related functionalities of the VidyoClient library.}
	{prototype: void VidyoCallUninitialize(void)}
	{note: This function is not reentrant.}
	{note: This function must be called the same number of times as initialize function was called.}
}
*/
void VidyoCallUninitialize(void);


/**
{type visibility="private":
	{name: VidyoCallState}
	{parent: VidyoCall}
	{description: Current state of the VidyoCall. }
	{value: {name: VIDYO_CALL_Calling} {description: Call has been initiated. }}
	{value: {name: VIDYO_CALL_Entered} {description: Call has been established. }}
	{value: {name: VIDYO_CALL_Ended} {description: Call has ended. }}
}
*/
typedef enum {
	VIDYO_CALL_Calling,
	VIDYO_CALL_Entered,
	VIDYO_CALL_Ended
} VidyoCallState;

/**
{function:
	{name: VidyoCallConstructCopy}
	{parent: VidyoCall}
	{description: Constructs the VidyoCall object as a copy of another.}
	{prototype: VidyoCall *VidyoCallConstructCopy(VidyoCall *obj, const VidyoCall *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoCall object to construct.}}
	{parameter: {name: other} {description: Pointer to the VidyoCall object to make a copy of.}}
	{return: Pointer to the constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoCallDestruct}
	{parent: VidyoCall}
	{description: Destructs the VidyoCall object.}
	{prototype: void VidyoCallDestruct(VidyoCall *obj)}
	{parameter: {name: obj} {description: Pointer to the VidyoCall object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoCallAssign}
	{parent: VidyoCall}
	{description: Assigns one VidyoCall object the value of another. }
	{prototype: VidyoCall *VidyoCallAssign(VidyoCall *obj, const VidyoCall *other)}
	{parameter: {name: obj} {description: Pointer to the VidyoCall object.}}
	{parameter: {name: other} {description: Pointer to the VidyoCall object to make a copy of.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoCallGetHandle}
	{parent: VidyoCall}
	{description: Gets the Weak reference to the VidyoCall object. }
	{prototype: const VidyoCallHandle* VidyoCallGetHandle(const VidyoCall* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{return: Pointer to the VidyoCallHandle on success, or NULL on failure.}
}
*/
const VidyoCallHandle* VidyoCallGetHandle(const VidyoCall* c);

/**
{function visibility="private":
	{name: VidyoCallSetUserData}
	{parent: VidyoCall}
	{description: Sets a user data pointer that can be retreived later.}
	{prototype: void VidyoCallSetUserData(VidyoCall* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: userData}
		{description: Void pointer that holds opaque application data.}
	}
}
*/
void VidyoCallSetUserData(VidyoCall* c, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoCallGetUserData}
	{parent: VidyoCall}
	{description: Retreives the user data pointer that was previousely set by calling VidyoCallSetUserData.}
	{prototype: LmiVoidPtr VidyoCallGetUserData(const VidyoCall* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{return: Void pointer that holds opaque application data.}
}
*/
LmiVoidPtr VidyoCallGetUserData(const VidyoCall* c);

/**
{function:
	{name: VidyoCallGetId}
	{parent: VidyoCall}
	{description: Gets the unique ID of the VidyoCall}
	{prototype: const LmiString* VidyoCallGetId(const VidyoCall* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{return: Pointer to the unique ID of the VidyoCall.}
}
*/
const LmiString* VidyoCallGetId(const VidyoCall* c);

/**
{function:
	{name: VidyoCallGetUser}
	{parent: VidyoCall}
	{description: }
	{prototype: VidyoUser *VidyoCallGetUser(VidyoCall *c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
VidyoUser *VidyoCallGetUser(VidyoCall *c);

/**
{function:
	{name: VidyoCallInitiate}
	{parent: VidyoCall}
	{description: Initiates a VidyoCall. }
	{prototype: LmiBool VidyoCallInitiate(VidyoCall* c, VidyoCallOnInitiated onInitiated, VidyoCallOnEnded onEnded)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: onInitiated}
		{description: Callback that is triggered when the enter operation completes. This could be a successful enter or a failure due to permissions, etc.}
	}
	{parameter:
		{name: onEnded}
		{description: Callback that is triggered when the room has been exited.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoCallInitiate(VidyoCall* c, VidyoCallOnInitiated onInitiated, VidyoCallOnEnded onEnded);

/**
{function:
	{name: VidyoCallAccept}
	{parent: VidyoCall}
	{description: Accepts an incoming VidyoCall that was notified by the VidyoUserOnCallCreatedByInvite callback. }
	{prototype: LmiBool VidyoCallAccept(VidyoCall* c, VidyoCallOnInitiated onInitiated, VidyoCallOnEnded onEnded)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: onInitiated}
		{description: Callback that is triggered when the enter operation completes. This could be a successful enter or a failure due to permissions, etc.}
	}
	{parameter:
		{name: onEnded}
		{description: Callback that is triggered when the room has been exited.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoCallAccept(VidyoCall* c, VidyoCallOnInitiated onInitiated, VidyoCallOnEnded onEnded);

/**
{function:
	{name: VidyoCallReject}
	{parent: VidyoCall}
	{description: Rejects an incoming VidyoCall that was notified by the VidyoUserFeedbackCallCreatedByInvite callback.}
	{prototype: void VidyoCallReject(VidyoCall* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
}
*/
void VidyoCallReject(VidyoCall* c);

/**
{function:
	{name: VidyoCallHangUp}
	{parent: VidyoCall}
	{description: Hangs up an in-progress VidyoCall. }
	{prototype: void VidyoCallHangUp(VidyoCall* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
}
*/
void VidyoCallHangUp(VidyoCall* c);

/**
 {function:
	{name: VidyoCallRegisterSubjectEventListener}
	{parent: VidyoCall}
	{description: Registers to get notified about subject events.}
	{prototype: LmiBool VidyoCallRegisterSubjectEventListener(VidyoCall* c, VidyoCallOnSetSubject onSetSubject)}
	{parameter:
		{name: c}
		{description: The VidyoCall object.}
	}
	{parameter:
		{name: onSetSubject}
		{description: Callback that is triggered when the subject has been changed.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoCallRegisterSubjectEventListener(VidyoCall* c, VidyoCallOnSetSubject onSetSubject);

/**
{function:
	{name: VidyoCallSetSubject}
	{parent: VidyoCall}
	{description: Sets a new subject on the VidyoCall. }
	{prototype: LmiBool VidyoCallSetSubject(VidyoCall* c, const char* subject)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: subject}
		{description: New subject of the VidyoCall. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoCallSetSubject(VidyoCall* c, const char* subject);

/**
{function:
	{name: VidyoCallGetSubject}
	{parent: VidyoCall}
	{description: Gets the current subject of the VidyoCall. }
	{prototype: const char* VidyoCallGetSubject(VidyoCall* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{return: ≈subject of the VidyoCall.}
}
*/
const char* VidyoCallGetSubject(VidyoCall* c);

/**
 {function:
	{name: VidyoCallRegisterMessageEventListener}
	{parent: VidyoCall}
	{description: Registers to get notified about message events.}
	{prototype: LmiBool VidyoCallRegisterMessageEventListener(VidyoCall* c, VidyoCallOnMessageReceived onMessageReceived, VidyoCallOnMessageAcknowledged onMessageAcknowledged, VidyoCallOnMessageRead onMessageRead, VidyoCallOnMessageTypingIndication onMessageTypingIndication)}
	{parameter:
		{name: c}
		{description: The VidyoCall object.}
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
LmiBool VidyoCallRegisterMessageEventListener(VidyoCall* c, VidyoCallOnMessageReceived onMessageReceived, VidyoCallOnMessageAcknowledged onMessageAcknowledged, VidyoCallOnMessageRead onMessageRead, VidyoCallOnMessageTypingIndication onMessageTypingIndication);

/**
{function:
	{name: VidyoCallSendMessage}
	{parent: VidyoCall}
	{description: Sends a message to the remote user in the VidyoCall. }
	{prototype: LmiBool VidyoCallSendMessage(VidyoCall* c, const char* message)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: message}
		{description: Message to be sent. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoCallSendMessage(VidyoCall* c, const char* message);

/**
{function:
	{name: VidyoCallGetRemoteRenderers}
	{parent: VidyoCall}
	{description: Gets the LmiVector of VidyoRemoteRenderer objects in the VidyoCall. }
	{prototype: LmiBool VidyoCallGetRemoteRenderers(VidyoCall* c, LmiVector(VidyoRemoteRenderer) *renderers)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: renderers}
		{description: Pointer to the LmiVector of VidyoRemoteRenderer objects. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: Only in progress VidyoCall will have a non-empty vector. }
	{note: Currently there is maximum of one entry in this vector. }
}
*/
LmiBool VidyoCallGetRemoteRenderers(VidyoCall *c, LmiVector(VidyoRemoteRenderer) *renderers);

/**
{function:
	{name: VidyoCallGetRemoteSpeakers}
	{parent: VidyoCall}
	{description: Gets the LmiVector of VidyoRemoteSpeaker objects in the VidyoCall. }
	{prototype: LmiBool VidyoCallGetRemoteSpeakers(VidyoCall* c, LmiVector(VidyoRemoteSpeaker) *speakers)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: speakers}
		{description: Pointer to the LmiVector of VidyoRemoteSpeaker objects. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: Only in progress VidyoCall will have a non-empty vector. }
	{note: Currently there is maximum of one entry in this vector. }
}
*/
LmiBool VidyoCallGetRemoteSpeakers(VidyoCall *c, LmiVector(VidyoRemoteSpeaker) *speakers);

/**
{function:
	{name: VidyoCallGetParticipants}
	{parent: VidyoCall}
	{description: Gets the LmiVector of VidyoParticipant objects in the VidyoCall. }
	{prototype: LmiBool VidyoCallGetParticipants(VidyoCall* c, LmiVector(VidyoParticipant) *participants)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCall object.}
	}
	{parameter:
		{name: participants}
		{description: Pointer to the LmiVector of VidyoParticipant objects. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: VidyoParticipant is the remote party in the call. }
	{note: Currently there is maximum of one entry in this vector. }
}
*/
LmiBool VidyoCallGetParticipants(VidyoCall *c, LmiVector(VidyoParticipant) *participants);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoCallInline.h"
#endif

#endif /* VIDYO_CALL_H_ */

