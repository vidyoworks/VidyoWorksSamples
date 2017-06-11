/*
 *  VidyoMobileJni.h
 *  Android
 *
 *  Func
 *  Created by Paul.Cushman
 *  Copyright 2014 Vidyo. All rights reserved.
 */

#ifndef __VidyoMobileJni_h__
#define __VidyoMobileJni_h__

LMI_BEGIN_EXTERN_C

void JavaGuiUpdateAllContacts(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize);
void JavaGuiUpdateMyContacts(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize);
void JavaGuiUpdateMyRooms(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize);
void JavaGuiUpdateMemberRooms(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize);
void JavaGuiUpdateRoomParticipants(const VidyoClientPrivateSoapConferenceParticipantData* participantDataArray, size_t arraySize);

void JavaGuiNotifyParticipantsChanged(int numOfParticipants);
void JavaGuiNotifyIncallGuiChanged();
void JavaGuiRecCountUpdateAllContacts(int numPortalRecs, int numCacheRecs, int maxCacheRecs, int startCacheRec, int endCacheRec);

//Attendee Object
typedef struct AttendeeData_
{
        char displayName[VIDYO_CLIENT_PRIVATE_SOAP_USERNAME_SIZE];      // Display Name
        char uri[URI_LEN];
} AttendeeData;


LMI_END_EXTERN_C

#endif //__VidyoMobileJni_h__
