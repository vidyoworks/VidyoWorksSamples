/*
 *  LoginLogic.hpp
 *  
 *
 *  Created by raz.galili on 3/2/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */
 
#ifndef __GuiLoginLogic_hpp__
#define __GuiLoginLogic_hpp__

#include "VidyoClient.h"
//#include "MessageLookup.h"


#include "VidyoJniCommon.h"
//#include <Lmi/Utils/LmiTypes.h>
//todo: add Construct
//todo: add Destruct



// Types
typedef enum GuiClientStartState_
{
	GUI_CLIENT_START_STATE_STOPPED = 0,
	GUI_CLIENT_START_STATE_STARTED,
} GuiClientStartState;

typedef enum GuiClientLoginState_
{
	GUI_CLIENT_LOGIN_STATE_INITIAL = 0,
	GUI_CLIENT_LOGIN_STATE_LOGGING_IN,
	GUI_CLIENT_LOGIN_STATE_CANCELLING,
	GUI_CLIENT_LOGIN_STATE_CANCELLED,
	GUI_CLIENT_LOGIN_STATE_FAILED,
	GUI_CLIENT_LOGIN_STATE_SIGNED_IN,
	GUI_CLIENT_LOGIN_STATE_LOGGED_IN,		// this state happens after we receive positive Portal Communication Status
	GUI_CLIENT_LOGIN_STATE_LOGGING_OUT,
	GUI_CLIENT_LOGIN_STATE_LOGGED_OUT,
	GUI_CLIENT_LOGIN_STATE_GUEST_LOGIN,
} GuiClientLoginState;

typedef enum GuiClientConnectState_
{
	GUI_CLIENT_CONNECT_STATE_INACTIVE = 0,
	GUI_CLIENT_CONNECT_STATE_ACTIVE,
} GuiClientConnectState;

LMI_BEGIN_EXTERN_C
//all strings are assumed to be null terminated UTF8

typedef enum  LoginHandlerResults
{
	MASSAGE_NOT_HANDLED_YET = 0,
	MESSAGE_HANDLED_BY_LOGIN_MESSAGE_HANDLER = 1,
}LoginHandlerResults;

//handler for all login messages
LoginHandlerResults loginMessageHandler(VidyoClientOutEvent event, VidyoVoidPtr param, 
							  VidyoUint paramSize, VidyoVoidPtr data);

//start portal login
void doLoginToPortal(const char *portal, const char *username, const  char *password);
//cacnel an ongoing login
void doLoginCancel(void); 
//start portal logout
void doLogoutFromPortal(void);
void doLoginFromWeb(VidyoClientInEventSignIn signInParams);
void doGetLoginType(const char *portal);

GuiClientLoginState GetCurrentClientLoginState();

void doHandleGuestLink( const char *hostC,  VidyoUint port, const char* keyC, const char*  userNameC, const char*  pinC, VidyoBool useHTTP);
void doHandleJoinWithRoomkey(const char *hostC,  VidyoUint port, const char* keyC, const char*  pinC);
void doGetPortalFeatures();
void doGetControlMeetingURL(const char *roomID);
VidyoBool doGetLoggedInWithToken();


LMI_END_EXTERN_C


#endif //__GuiLoginLogic_hpp__
