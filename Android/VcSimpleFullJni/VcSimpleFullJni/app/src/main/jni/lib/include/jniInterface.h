/*
 *  jniInterface.h
 *  Android
 *
 *  Func
 *  Created by raz.galili on 6/15/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */


#ifndef __jniInterface_h__
#define __jniInterface_h__

#include "MessageLookup.h"
#include "VidyoClientPrivate.h"		//VidyoClientPrivateSoapAccountData
#include "VidyoJniCommon.h"

LMI_BEGIN_EXTERN_C

void JavaGuiNotifyServerVideoMuteChanged(VidyoBool muted);
void JavaGuiNotifyConferenceEvent(int event, VidyoBool enabled);

void JavaGuiDisplayMessageBox(AppGuiMessageType displayMessageType, const char *displayMessage, ...);
void JavaGuiDisplayMessageBoxId(AppGuiMessageType displayMessageType, int, ...);

void JavaGuiChatMsgReceived(const VidyoBool groupChat, const char* uri, const char* name, const char* message);


void LoginFailedSSLCACERTCallbackToJava(const void* param);

void JavaGuiGuestLoginConferenceEnded();
void JavaGuiLogoutAfterGuestSession();



LMI_END_EXTERN_C

#endif //__jniInterface_h__
