/** 
{file:
	{name: VidyoParticipant.h}
	{description: Participant Entity Library. }
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
#ifndef VIDYO_PARTICIPANT_H_ 
#define VIDYO_PARTICIPANT_H_ 

#include <Lmi/Os/LmiLog.h>
#include <Lmi/Os/LmiSharedPtr.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiUnordered.h>

LMI_BEGIN_EXTERN_C

struct VidyoParticipantImpl_;
typedef struct VidyoParticipantImpl_ VidyoParticipantImpl;
Declare_LmiSharedPtr(VidyoParticipantImpl)
Declare_LmiSharedPtrWrapper(VidyoParticipant, VidyoParticipantImpl)
Declare_LmiWeakPtrWrapper(VidyoParticipantHandle, VidyoParticipant, VidyoParticipantImpl)
Declare_LmiUnorderedMap(LmiString, VidyoParticipant)
Declare_LmiVector(VidyoParticipant)
Declare_LmiVectorEqual(VidyoParticipant)
Declare_LmiList(VidyoParticipant)

LMI_END_EXTERN_C

#include "VidyoCall.h"
#include "VidyoRoom.h"
#include "VidyoContact.h"
#include "VidyoRemoteMicrophone.h"
#include "VidyoRemoteCamera.h"
#include "VidyoRemoteWindowShare.h"

LMI_BEGIN_EXTERN_C

/**
{package:
	{name: Participant}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoParticipant.h}
	{description: The VidyoParticipant package.}
}
*/

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoParticipant}
	{parent: Endpoint}
	{include: Lmi/VidyoClient/VidyoParticipant.h}
	{description: This object represents a participant in the room or call. }
	{member:
		{name: name}
		{type: LmiString}
		{description: Display name of the participant. }
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: ID that is unique to the room or call only. }
	}
	{member:
		{name: userId}
		{type: LmiString}
		{description: ID that is globally unique such as user@domain. }
	}
}
*/

/**
{type apigroup="connector simple" visibility="private":
	{name: VidyoParticipantHandle}
	{parent: VidyoParticipant}
	{description: }
}
*/

/**
{function visibility="private":
	{name: VidyoParticipantInitialize}
	{parent: VidyoParticipant}
	{description: }
	{prototype: LmiBool VidyoParticipantInitialize(void)}
	{return: }
}
*/
LmiBool VidyoParticipantInitialize(void);


/**
{function visibility="private":
	{name: VidyoParticipantUninitialize}
	{parent: VidyoParticipant}
	{description: }
	{prototype: void VidyoParticipantUninitialize(void)}
}
*/
void VidyoParticipantUninitialize(void);

/**
{function apigroup="connector simple":
	{name: VidyoParticipantConstructCopy}
	{parent: VidyoParticipant}
	{description: Constructs an VidyoParticipant object as a copy of another.}
	{prototype: VidyoParticipant *VidyoParticipantConstructCopy(VidyoParticipant *obj, const VidyoParticipant *other)}
	{parameter: {name: obj} {description: The VidyoParticipant object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoParticipantDestruct}
	{parent: VidyoParticipant}
	{description: Destructs an VidyoParticipant object.}
	{prototype: void VidyoParticipantDestruct(VidyoParticipant *obj)}
	{parameter: {name: obj} {description: The VidyoParticipant object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantAssign}
	{parent: VidyoParticipant}
	{description: Assigns one VidyoParticipant object the value of another. }
	{prototype: VidyoParticipant *VidyoParticipantAssign(VidyoParticipant *obj, const VidyoParticipant *other)}
	{parameter: {name: obj} {description: The VidyoParticipant object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantGetHandle}
	{parent: VidyoParticipant}
	{description: }
	{prototype: VidyoParticipantHandle* VidyoParticipantGetHandle(VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: }
}
*/
VidyoParticipantHandle* VidyoParticipantGetHandle(VidyoParticipant* p);

/**
{function apigroup="connector simple":
	{name: VidyoParticipantGetName}
	{parent: VidyoParticipant}
	{description: Gets the display name of the participant.}
	{prototype: const LmiString* VidyoParticipantGetName(const VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: Display name of the participant. }
}
*/
const LmiString* VidyoParticipantGetName(const VidyoParticipant* p);

/**
{function apigroup="connector simple":
	{name: VidyoParticipantGetId}
	{parent: VidyoParticipant}
	{description: Gets the ID that is unique to the room or call only.}
	{prototype: const LmiString* VidyoParticipantGetId(const VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: ID that is unique to the room or call only.}
}
*/
const LmiString* VidyoParticipantGetId(const VidyoParticipant* p);

/**
{function apigroup="connector simple":
	{name: VidyoParticipantGetUserId}
	{parent: VidyoParticipant}
	{description: Gets the ID that is globally unique such as user@domain. }
	{prototype: const LmiString* VidyoParticipantGetUserId(const VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: ID that is globally unique such as user@domain.}
}
*/
const LmiString* VidyoParticipantGetUserId(const VidyoParticipant* p);

/**
{function:
	{name: VidyoParticipantGetContact}
	{parent: VidyoParticipant}
	{description: }
	{prototype: VidyoContact* VidyoParticipantGetContact(const VidyoParticipant* p, VidyoContact* contact)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{parameter:
		{name: contact}
		{description: }
	}
	{return: }
}
*/
VidyoContact* VidyoParticipantGetContact(const VidyoParticipant* p, VidyoContact* contact);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantSetUserData}
	{parent: VidyoParticipant}
	{description: }
	{prototype: void VidyoParticipantSetUserData(VidyoParticipant* p, LmiVoidPtr userData)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoParticipantSetUserData(VidyoParticipant* p, LmiVoidPtr userData);

/**
{function:
	{name: VidyoParticipantIsLocal}
	{parent: VidyoParticipant}
	{description: }
	{prototype: LmiBool VidyoParticipantIsLocal(VidyoParticipant *p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: }
}
*/
LmiBool VidyoParticipantIsLocal(VidyoParticipant *p);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantGetUserData}
	{parent: VidyoParticipant}
	{description: }
	{prototype: LmiVoidPtr VidyoParticipantGetUserData(const VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: }
}
*/
LmiVoidPtr VidyoParticipantGetUserData(const VidyoParticipant* p);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantGetRemoteCameras}
	{parent: VidyoParticipant}
	{description: }
	{prototype: LmiBool VidyoParticipantGetRemoteCameras(VidyoParticipant *p, LmiVector(VidyoRemoteCamera) *cameras)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{parameter:
		{name: cameras}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoParticipantGetRemoteCameras(VidyoParticipant *p, LmiVector(VidyoRemoteCamera) *cameras);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantHasRemoteCameras}
	{parent: VidyoParticipant}
	{description: }
	{prototype: LmiBool VidyoParticipantHasRemoteCameras(VidyoParticipant *p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: }
}
*/
LmiBool VidyoParticipantHasRemoteCameras(VidyoParticipant *p);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantGetRemoteMicrophones}
	{parent: VidyoParticipant}
	{description: }
	{prototype: LmiBool VidyoParticipantGetRemoteMicrophones(VidyoParticipant *p, LmiVector(VidyoRemoteMicrophone) *microphones)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{parameter:
		{name: microphones}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoParticipantGetRemoteMicrophones(VidyoParticipant *p, LmiVector(VidyoRemoteMicrophone) *microphones);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoParticipantGetRemoteWindowShares}
	{parent: VidyoParticipant}
	{description: }
	{prototype: LmiBool VidyoParticipantGetRemoteWindowShares(VidyoParticipant *p, LmiVector(VidyoRemoteWindowShare) *windowShares)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{parameter:
		{name: windowShares}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoParticipantGetRemoteWindowShares(VidyoParticipant *p, LmiVector(VidyoRemoteWindowShare) *windowShares);

/**
{function visibility="private":
	{name: VidyoParticipantGetCall}
	{parent: VidyoParticipant}
	{description: }
	{prototype: VidyoCall *VidyoParticipantGetCall(VidyoParticipant *p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: }
}
*/
VidyoCall *VidyoParticipantGetCall(VidyoParticipant *p);

/**
{function visibility="private":
	{name: VidyoParticipantGetRoomHandle}
	{parent: VidyoParticipant}
	{description: }
	{prototype: VidyoRoomHandle *VidyoParticipantGetRoomHandle(VidyoParticipant *p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: }
}
*/
VidyoRoomHandle *VidyoParticipantGetRoomHandle(VidyoParticipant *p);

/**
{function visibility="private":
	{name: VidyoParticipantGetStats}
	{parent: VidyoParticipant}
	{description: Fill in data in VidyoParticipantGetStats from a participant.}
	{prototype: LmiBool VidyoParticipantGetStats(VidyoParticipant *p, VidyoParticipantStats *stats)}
	{parameter: {name: p} {description: The participant object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoParticipantGetStats(VidyoParticipant *p, VidyoParticipantStats *stats);

/**
{function apigroup="connector simple":
	{name: VidyoParticipantIsRecording}
	{parent: VidyoParticipant}
	{description: Gets the recording state of the participant.}
	{prototype: LmiBool VidyoParticipantIsRecording(const VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: LMI_TRUE if the participant is recording, LMI_FALSE otherwise. }
}
*/
LmiBool VidyoParticipantIsRecording(const VidyoParticipant* p);

/**
{function apigroup="connector simple":
	{name: VidyoParticipantIsHidden}
	{parent: VidyoParticipant}
	{description: Gets the hidden state of the participant.}
	{prototype: LmiBool VidyoParticipantIsHidden(const VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: LMI_TRUE if the participant is hidden, LMI_FALSE otherwise. }
}
*/
LmiBool VidyoParticipantIsHidden(const VidyoParticipant* p);

/**
{function apigroup="connector simple":
	{name: VidyoParticipantIsSelectable}
	{parent: VidyoParticipant}
	{description: Gets the selectable state of the participant.}
	{prototype: LmiBool VidyoParticipantIsSelectable(const VidyoParticipant* p)}
	{parameter:
		{name: p}
		{description: The VidyoParticipant object.}
	}
	{return: LMI_TRUE if the participant is selectable, LMI_FALSE otherwise. }
}
*/
LmiBool VidyoParticipantIsSelectable(const VidyoParticipant* p);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoParticipantInline.h"
#endif

#endif /* VIDYO_PARTICIPANT_H_ */

