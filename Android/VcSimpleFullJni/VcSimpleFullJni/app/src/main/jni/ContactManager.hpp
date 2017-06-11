/*
 *  ContactManager.h
 *  Android
 *
 *  Created by raz.galili on 5/3/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */
#ifndef __ContactManager_h__
#define __ContactManager_h__

#include "VidyoClientPrivate.h"
#include "VidyoJniCommon.h"
#include "VidyoClientMessages.h"



typedef enum  ContactManagerHandlerResults_
{
	MASSAGE_NOT_HANDLED_BY_CONTACT_MANAGER = 0,
	MASSAGE_HANDLED_BY_CONTACT_MANAGER = 2,
}ContactManagerHandlerResults;


LMI_BEGIN_EXTERN_C

void doStartPortalUpdates(void);
void doStopPortalUpdates(void);
void doStartSearch(const char* hint);
void doStopSearch(void);
VidyoBool doShiftSearch(int shift);

void doStartRoomParticipantsUpdates(VidyoClientPrivateSoapAccountData *accountData);
void doStopRoomParticipantsUpdates();

void doStartMemberRoomsUpdates(VidyoClientPrivateSoapAccountData* entity);
void doStopMemberRoomsUpdates();

void doStartMyRoomsUpdates();
void doStopMyRoomsUpdates();

void doStartEntityUpdates(VidyoClientPrivateSoapAccountData* entity);
void doStopEntityUpdates();
int doIsAContact(VidyoClientPrivateSoapAccountData* entity);


void doClearRoomPin(VidyoClientPrivateSoapAccountData* accountData);
void doSetRoomPin(VidyoClientPrivateSoapAccountData* accountData);
VidyoBool doAddContact(VidyoClientPrivateSoapAccountData* accountData);
void doRemoveContact(VidyoClientPrivateSoapAccountData* accountData);
void doDestroyRoom(VidyoClientPrivateSoapAccountData* accountData);
void doCreateRoom(char name[], char extension[]);
void doCreateScheduledRoom(VidyoBool usePin);
void doGetInviteContent(char roomID[]);
void doUnlockLockRoom(VidyoClientPrivateSoapAccountData* accountData);
void doLockRoom(VidyoClientPrivateSoapAccountData* accountData);

void doDropParticipant(VidyoClientPrivateSoapAccountData* accountData);

void doSetParticipantAudioMute(VidyoClientPrivateSoapAccountData* accountData);
void doSetParticipantAudioUnmute(VidyoClientPrivateSoapAccountData* accountData);


ContactManagerHandlerResults contactManagerMessageHandler( VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data);

LMI_END_EXTERN_C


#endif //__ContactManager_h__
