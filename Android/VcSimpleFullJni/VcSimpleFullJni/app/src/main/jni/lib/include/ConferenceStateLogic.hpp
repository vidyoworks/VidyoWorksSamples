/*
 *  ConferenceStateLogic.hpp
 *  
 *
 *  Created by raz.galili on 3/2/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */
 
#ifndef __GuiConferenceStateLogic_hpp__
#define __GuiConferenceStateLogic_hpp__

#include "VidyoClient.h"
#include "MessageLookup.h"
//#include "../../AppStringsEnum.h"
#include "../../../ClientLib/VidyoClientPrivate.h"

#include "VidyoJniCommon.h"

#include "LoginLogic.hpp"

LMI_BEGIN_EXTERN_C


//todo: add Construct
//todo: add Destruct

//all strings are assumed to be null terminated UTF8
typedef enum  ConferenceStateHandlerResults_
{
	MASSAGE_NOT_HANDLED_BY_CONFERENCESTATE = 0,
	MASSAGE_HANDLED_BY_CONFERENCESTATE = 2,
}ConferenceStateHandlerResults;

//handler for all login messages
ConferenceStateHandlerResults conferenceStateMessageHandler(VidyoClientOutEvent event,
							  VidyoVoidPtr param, 
							  VidyoUint paramSize,
							  VidyoVoidPtr data);

void doLeave(void);
void doInviteEntity(VidyoClientPrivateSoapAccountData *accountData);
void doJoinByName(const char *displayName, const char *pin);
void doJoin(VidyoClientPrivateSoapAccountData *accountData);
void doJoinIPC(VidyoClientPrivateSoapAccountData *accountData);
void doJoinSchedRoomExtension(const char *extension, const char *pin);
void doCallByNameDirect(const char *displayName);
void doCallDirect(VidyoClientPrivateSoapAccountData *accountData);
void doAcceptCall(void);
void doCancelCall(void);
void doRejectCall(void);
void doStartAttendeeUpdates(void);
void doStopAttendeeUpdates(void);
int doGetParticiapntsNumber(void);
VidyoBool doFeccSendControlCommand(VidyoInt command);


LMI_END_EXTERN_C



// Types

typedef enum GuiClientConferenceState_
{
	GUI_CLIENT_CONFERENCE_STATE_IDLE = 0,
	GUI_CLIENT_CONFERENCE_STATE_JOINING,
	GUI_CLIENT_CONFERENCE_STATE_JOINED,
	GUI_CLIENT_CONFERENCE_STATE_LEAVING,
} GuiClientConferenceState;

//ConferenceState change event info
typedef struct ConferenceStateEventInfo_
{
	GuiClientConferenceState	state;
	int				error;
} ConferenceStateEventInfo;

// Conference operation state information
// WARNING: These values need to be coordinated with application code
#define CONFERENCE_RECORDING_STATUS		1
#define CONFERENCE_WEBCASTING_STATUS	2


#endif //__GuiConferenceStateLogic_hpp__
