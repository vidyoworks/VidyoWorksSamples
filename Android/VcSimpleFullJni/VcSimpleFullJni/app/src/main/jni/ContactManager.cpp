/*
 *  getContactManager()->cpp
 *  Android
 *
 *  Created by raz.galili on 5/3/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */

#include <jni.h>
#include "ContactManager.hpp"
#include "VidyoClientPrivate.h"
#include "TimerDispatch.hpp"
#include "ClientEventsNotifications.hpp"
#include "ClientEventDispatch.hpp"
#include "ClientMyContacts.hpp"
#include "ClientAllContacts.hpp"
#include "ClientRooms.hpp"
#include "RoomParticipants.hpp"
#include "AndroidDebug.h"
#include "VidyoMobileJni.h"
#include "VidyoJniPrivateDefs.h"

#include <tr1/memory>

using std::tr1::shared_ptr;

#include <string>


using std::string;
static void clientManagerMyContactSearchStarted(TNotification eventName, void* param);
static void clientManagerMyContactSearchComplete(TNotification eventName, void* param);
static void clientManagerRoomsSearchComplete(TNotification eventName, void* param);
static void clientManagerAllContactsSearchStarted(TNotification eventName, void* param);
static void clientManagerAllContactsSearchComplete(TNotification eventName, void* param);
static void clientManagerSearchByEntityIDResponseHandler(TNotification eventName, void* param);
static void clientManagerGetPArticipantsResponseHandler(TNotification eventName, void* param);

#define ENTITY_INFO_REFRESH_RATE 60.0
#define ENTITY_INFO_TIMER_ID "ENTITY_INFO_TIMER_ID"
class ContactManager
{
public:
	ContactManager():m_updatingmyEntity(false),m_myContacts(NULL),m_updatingEntity(false){}
	virtual ~ContactManager(){}
	
	//start updates of client entity info and client contacts info
	void doStartPortalUpdates(void)
	{
		startUpdatingMyEntity();
		startUpdatingMyContacts();
		doStartMyRoomsUpdates();
	}
	
	void doStopPortalUpdates(void)
	{
		stopUpdatingMyEntity();
		stopUpdatingMyContacts();
		doStopMyRoomsUpdates();
	}
	
	void doStartMyRoomsUpdates()
	{
		FUNCTION_ENTRY
	
		registerForEvent(kClientRoomsSearchComplete,clientManagerRoomsSearchComplete);
		
		if (ClientRooms::clientRooms()->RefreshEnabled())
			doStopMyRoomsUpdates();

		ClientRooms::clientRooms()->searchWithQueryString("");
			
		//start a timer update that updates the contact info
		ClientRooms::clientRooms()->setRefreshEnabled(VIDYO_TRUE);

		FUNCTION_EXIT
		
	}
	void doStopMyRoomsUpdates()
	{
		FUNCTION_ENTRY
		ClientRooms::clientRooms()->setRefreshEnabled(VIDYO_FALSE);
		FUNCTION_EXIT	
	}
	
	void doStartSearch(const char* hint)
	{		
		FUNCTION_ENTRY
		
		bool currentllySearching = ClientAllContacts::clientAllContacts()->RefreshEnabled();
		
		if (currentllySearching)
		{
			if (ClientAllContacts::clientAllContacts()->getQueryString() == hint)
				return; //search is already running
			
			//new search, stop previous search
			doStopSearch();
		}	
		else
		{
			//no search running - register for search results
		        registerForEvent(kClientAllContactsSearchStarted,clientManagerAllContactsSearchStarted);
			registerForEvent(kClientAllContactsSearchComplete,clientManagerAllContactsSearchComplete);
		}

		//set search string
		ClientAllContacts::clientAllContacts()->searchWithQueryString(hint);
		
		//start a timer update that updates the contact info
		ClientAllContacts::clientAllContacts()->setRefreshEnabled(VIDYO_TRUE);

		FUNCTION_EXIT
	}
	
	void doStopSearch(void)
	{
		FUNCTION_ENTRY
		ClientAllContacts::clientAllContacts()->setRefreshEnabled(VIDYO_FALSE);
		FUNCTION_EXIT	
	}
	
        VidyoBool doShiftSearch(int shift)
        {
                VidyoBool ret;
                FUNCTION_ENTRY
                ret = ClientAllContacts::clientAllContacts()->doShift(shift);
                FUNCTION_EXIT
                return ret;
        }


	void doStartEntityUpdates(VidyoClientPrivateSoapAccountData& entity)
	{	
		FUNCTION_ENTRY_EXIT
                if(!m_updatingEntity) {
                        m_updatingEntity = true;
                }

		if (entityInfoSearch.RefreshEnabled())
			doStopEntityUpdates();
		
		entityInfoSearch.searchWithQueryString(entity);
		
		//search once;
//		entityInfoSearch.doRefresh();
		entityInfoSearch.setRefreshEnabled(VIDYO_TRUE);
	}

	void doStopEntityUpdates()
	{
		FUNCTION_ENTRY_EXIT
		m_updatingEntity = false;
		entityInfoSearch.setRefreshEnabled(VIDYO_FALSE);

	}
	
	void doStartRoomParticipantsUpdates(VidyoClientPrivateSoapAccountData& accountData)	
	{	FUNCTION_ENTRY
		
		::registerForEvent(KVidyoClientPrivateSoapGetParticipantsResponse,clientManagerGetPArticipantsResponseHandler);
		
		if (RoomParticipants::roomParticipants()->RefreshEnabled())
			doStopRoomParticipantsUpdates();
		
		RoomParticipants::roomParticipants()->searchWithQueryString(accountData);
		
		//start a timer update that updates the contact info
		RoomParticipants::roomParticipants()->setRefreshEnabled(VIDYO_TRUE);
		
		FUNCTION_EXIT
	}
	
	void doStopRoomParticipantsUpdates()
	{
		FUNCTION_ENTRY
		RoomParticipants::roomParticipants()->setRefreshEnabled(VIDYO_FALSE);
		FUNCTION_EXIT
	}

	
	ContactManagerHandlerResults onPrivateOutEventVcsoap(VidyoVoidPtr event)
	{
				
		VidyoUint requestType = *((VidyoUint *)event);
		VidyoBool ret = VIDYO_TRUE;
		switch (requestType)
		{
			case VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_ENTITY_ID:
			{
				VidyoClientPrivateSoapOutEventSearch *response =  (VidyoClientPrivateSoapOutEventSearch*)event;
				if (response->requestId == ENTITY_INFO_SEARCH_ID ) {
                                        ::dispatchEvent( kVidyoClientContactManagerEntityInfoUpdated, reinterpret_cast<void*>(event));
                                        return MASSAGE_HANDLED_BY_CONTACT_MANAGER;
				}
				else if (response->requestId == MEMBER_ROOMS_SEARCH_ID) {
                                        ::dispatchEvent( KVidyoClientPrivateSoapSearchByEntityIDResponse, reinterpret_cast<void*>(event));
                                        return MASSAGE_HANDLED_BY_CONTACT_MANAGER;
				}
				break;
			}
			case VIDYO_CLIENT_PRIVATE_SOAP_GET_PARTICIPANTS:
				::dispatchEvent( KVidyoClientPrivateSoapGetParticipantsResponse, reinterpret_cast<void*>(event));
				return MASSAGE_HANDLED_BY_CONTACT_MANAGER;
                        case VIDYO_CLIENT_PRIVATE_SOAP_LOCK_ROOM:
                        {
                                VidyoClientPrivateSoapOutEventLockRoom *lockMsg = (VidyoClientPrivateSoapOutEventLockRoom *)(event);
                                LOGI("VIDYO_CLIENT_PRIVATE_SOAP_LOCK_ROOM returned with result =%d, error = %d httpCode = %d", lockMsg->result, lockMsg->error, lockMsg->httpStatusCode);
				return MASSAGE_HANDLED_BY_CONTACT_MANAGER;
                        }
            case VIDYO_CLIENT_PRIVATE_SOAP_CREATE_SCHEDULED_ROOM:
				::dispatchEvent( KVidyoClientPrivateSoapCreateSchedRoomResponse, reinterpret_cast<void*>(event));
				return MASSAGE_HANDLED_BY_CONTACT_MANAGER;
                break;
            case VIDYO_CLIENT_PRIVATE_SOAP_GET_INVITE_CONTENT:
				::dispatchEvent( KVidyoClientPrivateSoapGetInviteContentResponse, reinterpret_cast<void*>(event));
				return MASSAGE_HANDLED_BY_CONTACT_MANAGER;
                
            case VIDYO_CLIENT_PRIVATE_SOAP_ADD_TO_MY_CONTACTS:
				::dispatchEvent( KVidyoClientPrivateSoapAddContactResponse, reinterpret_cast<void*>(event));
				return MASSAGE_HANDLED_BY_CONTACT_MANAGER;
            case VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_FROM_MY_CONTACTS:
				::dispatchEvent( KVidyoClientPrivateSoapRemoveContactResponse, reinterpret_cast<void*>(event));
				return MASSAGE_HANDLED_BY_CONTACT_MANAGER;

			default: 
				LOGI("soap event %d not handled", requestType);
				return MASSAGE_NOT_HANDLED_BY_CONTACT_MANAGER;
		}
		return MASSAGE_NOT_HANDLED_BY_CONTACT_MANAGER;
	}

	void doStartMemberRoomsUpdates(VidyoClientPrivateSoapAccountData& entity)
	{
		//no search runing - register for search results
		::registerForEvent(KVidyoClientPrivateSoapSearchByEntityIDResponse,clientManagerSearchByEntityIDResponseHandler);
		
		
		if (memberRooms.RefreshEnabled())
		        doStopMemberRoomsUpdates();
		
		memberRooms.searchWithQueryString(entity);
		
		//start a timer update that updates the contact info
		memberRooms.setRefreshEnabled(VIDYO_TRUE);
		
	}

	VidyoBool isMemberRoomsUpdatesActive()
	{
		return memberRooms.RefreshEnabled();
	}

	
	void doStopMemberRoomsUpdates()
	{
		memberRooms.setRefreshEnabled(VIDYO_FALSE);
	}

	void doClearRoomPin(VidyoClientPrivateSoapAccountData& accountData) 
	{
		VidyoClientPrivateSoapInEventRemoveRoomPin removeRoomPinReq;
		removeRoomPinReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_ROOM_PIN;
		strcpy(removeRoomPinReq.roomID, accountData.entityID);;
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &removeRoomPinReq, sizeof(VidyoClientPrivateSoapInEventRemoveRoomPin));
	}
	
	void doSetRoomPin(VidyoClientPrivateSoapAccountData& accountData) 
	{
		VidyoClientPrivateSoapInEventCreateRoomPin createRoomPinReq;
		createRoomPinReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_CREATE_ROOM_PIN;
		strcpy(createRoomPinReq.roomID, accountData.entityID);;
		strcpy(createRoomPinReq.roomPIN, accountData.roomMode.roomPIN);;
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &createRoomPinReq, sizeof(VidyoClientPrivateSoapInEventCreateRoomPin));
		
	}
	
	VidyoBool doAddContact(VidyoClientPrivateSoapAccountData& accountData) 
	{
		VidyoClientPrivateSoapInEventAddToMyContacts addToMyContactsReq;
		addToMyContactsReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_ADD_TO_MY_CONTACTS;
		strcpy(addToMyContactsReq.entityID, accountData.entityID);
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &addToMyContactsReq, sizeof(VidyoClientPrivateSoapInEventAddToMyContacts));
		return VIDYO_TRUE;
	}
	
	void doRemoveContact(VidyoClientPrivateSoapAccountData& accountData) 
	{
		VidyoClientPrivateSoapInEventRemoveFromMyContacts removeFromMyContactsReq;
		removeFromMyContactsReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_FROM_MY_CONTACTS;
		strcpy(removeFromMyContactsReq.entityID, accountData.entityID);
		GuiSendPrivateEvent( VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &removeFromMyContactsReq, sizeof(VidyoClientPrivateSoapInEventRemoveFromMyContacts));
	}
	
	void doDestroyRoom(VidyoClientPrivateSoapAccountData& accountData) 
	{
		VidyoClientPrivateSoapInEventDeleteRoom deleteRoomReq;
		deleteRoomReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_DELETE_ROOM;
		strcpy(deleteRoomReq.roomID, accountData.entityID);;
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &deleteRoomReq, sizeof(VidyoClientPrivateSoapInEventDeleteRoom));
	}
	
	void doCreateRoom(char name[], char extension[]) 
	{	
		VidyoClientPrivateSoapInEventCreateRoom createRoomReq;
		createRoomReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_CREATE_ROOM;
		strcpy(createRoomReq.name, name);
		strcpy(createRoomReq.extension, extension);
		GuiSendPrivateEvent( VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &createRoomReq, sizeof(VidyoClientPrivateSoapInEventCreateRoom));
	}
	
	void doCreateScheduledRoom(VidyoBool usePin) 
	{
		VidyoClientPrivateSoapInEventCreateScheduledRoom createSchedRoomReq;
		createSchedRoomReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_CREATE_SCHEDULED_ROOM;
		createSchedRoomReq.setPIN = usePin;
		GuiSendPrivateEvent( VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &createSchedRoomReq, sizeof(VidyoClientPrivateSoapInEventCreateScheduledRoom));
	}
	
	void doGetInviteContent(char roomID[])
	{
		VidyoClientPrivateSoapInEventGetInviteContent getInviteContent;
		getInviteContent.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_GET_INVITE_CONTENT;
		strcpy(getInviteContent.roomID, roomID);
		GuiSendPrivateEvent( VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &getInviteContent, sizeof(VidyoClientPrivateSoapInEventGetInviteContent));
	}
	
	void doUnlockLockRoom(VidyoClientPrivateSoapAccountData& accountData) 
	{
		VidyoClientPrivateSoapInEventUnlockRoom unlockReq = { 0 };
		unlockReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_UNLOCK_ROOM;
		strcpy(unlockReq.roomID, accountData.entityID);;
        LOGI("Unlock Room %s",unlockReq.roomID);

		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &unlockReq, sizeof(VidyoClientPrivateSoapInEventUnlockRoom));		
	}
	
	void doLockRoom(VidyoClientPrivateSoapAccountData& accountData) 
	{	
		VidyoClientPrivateSoapInEventLockRoom lockRoomReq = { 0 };
		lockRoomReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_LOCK_ROOM;
		strcpy(lockRoomReq.roomID, accountData.entityID);;
        LOGI("Lock Room %s",lockRoomReq.roomID);
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &lockRoomReq, sizeof(VidyoClientPrivateSoapInEventLockRoom));
	}

	void doDropParticipant(VidyoClientPrivateSoapAccountData& accountData) 
	{	
		VidyoClientPrivateSoapInEventDropParticipant dropParticipantReq;

		std::string entityID = RoomParticipants::roomParticipants()->getConferenceID();
		char * ptr = (char *)(&entityID[0]);

		dropParticipantReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_DROP_PARTICIPANT;
		strcpy(dropParticipantReq.conferenceID, ptr);
		strcpy(dropParticipantReq.participantID, accountData.entityID);
		LOGI("Drop Participant %s, id %s", accountData.displayName, dropParticipantReq.participantID);
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &dropParticipantReq, sizeof(VidyoClientPrivateSoapInEventDropParticipant));
	}
	
	void doSetParticipantAudioMute(VidyoClientPrivateSoapAccountData& accountData)
	{
		VidyoClientPrivateSoapInEventMuteAudio muteParticipantReq;

		muteParticipantReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_MUTE_AUDIO;
		strcpy(muteParticipantReq.conferenceID, RoomParticipants::roomParticipants()->getConferenceID().c_str());
		strcpy(muteParticipantReq.participantID, accountData.participantID);
		LOGI("Mute Participant %s, id %s", accountData.displayName, muteParticipantReq.participantID);
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &muteParticipantReq, sizeof(VidyoClientPrivateSoapInEventMuteAudio));
	}

	void doSetParticipantAudioUnmute(VidyoClientPrivateSoapAccountData& accountData)
	{
		VidyoClientPrivateSoapInEventUnmuteAudio unmuteParticipantReq;

		unmuteParticipantReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_MUTE_AUDIO;
		strcpy(unmuteParticipantReq.conferenceID, RoomParticipants::roomParticipants()->getConferenceID().c_str());
		strcpy(unmuteParticipantReq.participantID, accountData.participantID);
		LOGI("Unmute Participant %s, id %s", accountData.displayName, unmuteParticipantReq.participantID);
		GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &unmuteParticipantReq, sizeof(VidyoClientPrivateSoapInEventUnmuteAudio));
	}

	
	
	
private:
	void startUpdatingMyEntity()
	{
		FUNCTION_ENTRY
		if(!m_updatingmyEntity)
		{
			m_updatingmyEntity = true;
			refreshMyEntityInfo();
		}
		FUNCTION_EXIT
	}

	void startUpdatingMyContacts()
	{
		
		FUNCTION_ENTRY
		
                registerForEvent(kClientMyContactsSearchStarted,clientManagerMyContactSearchStarted);

		registerForEvent(kClientMyContactsSearchComplete,clientManagerMyContactSearchComplete);

		if (!ClientMyContacts::clientMyContacts()->RefreshEnabled())
		{
			ClientMyContacts::clientMyContacts()->searchWithQueryString("");

			//start a timer update that updates the contact info
			ClientMyContacts::clientMyContacts()->setRefreshEnabled(VIDYO_TRUE);
		}
		FUNCTION_EXIT
	}
	
	void stopUpdatingMyEntity()
	{
		FUNCTION_ENTRY
		m_updatingmyEntity = false;
		cancelTimer(ENTITY_INFO_TIMER_ID);
		FUNCTION_EXIT
	}
	void stopUpdatingMyContacts()
	{
		FUNCTION_ENTRY
		ClientMyContacts::clientMyContacts()->setRefreshEnabled(VIDYO_FALSE);
		FUNCTION_EXIT
	}
	
	void refreshMyEntityInfo()
	{
		FUNCTION_ENTRY
		if(m_updatingmyEntity)
		{
			VidyoClientPrivateRequestEntityInfo req;
			//use VIDYO_CLIENT_PRIVATE_REQUEST_GET_ENTITY_INFO
			GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_ENTITY_INFO,
								  (VidyoVoidPtr)&req,
								  sizeof(VidyoClientPrivateRequestEntityInfo),
								  0);
			
			//update entity info in jni
			::dispatchEvent(kVidyoClientContactManagerMyEntityInfoUpdated,&req);
			
			//reset timer - info update once a minute
			TD<ContactManager,void,void>::executeAfterDelay(*this, &ContactManager::refreshMyEntityInfo, (double)ENTITY_INFO_REFRESH_RATE, ENTITY_INFO_TIMER_ID); 

		}
		FUNCTION_EXIT
	}



        bool m_updatingmyEntity;
	ClientMyContacts *m_myContacts;
	MemberRooms memberRooms;

	EntityInfoSearch entityInfoSearch;
        bool m_updatingEntity;

};

shared_ptr<ContactManager> contactmanager = shared_ptr<ContactManager>((ContactManager*)NULL);

/*
 * TODO:
 * There does NOT seem to be a way to destroy the Contact Manager
 * The application is never shut down completely
 */



shared_ptr<ContactManager> getContactManager()
{
	if (!contactmanager.get())
		contactmanager = shared_ptr<ContactManager>(new ContactManager());
	
	return contactmanager;
}

static void clientManagerMyContactSearchStarted(TNotification eventName, void* param)
{
  FUNCTION_ENTRY
  ClientContacts* clientContacts = (ClientContacts*) param;

  size_t numOFEntries = clientContacts->getNumEntries();
  FUNCTION_EXIT
}


static void clientManagerMyContactSearchComplete(TNotification eventName, void* param)
{
	FUNCTION_ENTRY
	bool allIsOK = true;
	ClientContacts* clientContacts = (ClientContacts*) param;
	VidyoClientPrivateSoapAccountData *accountDataArray= NULL;; //todo: replace with a safe ptr

	size_t numOFEntries = clientContacts->getNumEntries();
	
	if(numOFEntries && (accountDataArray = new VidyoClientPrivateSoapAccountData[numOFEntries]) )
	{
		for(int i=0; i<numOFEntries; i++)
		{
			if(!clientContacts->copyEntryAtIndex(i, accountDataArray[i]))
			{
				allIsOK = false;
				break;
			}
		}
	}

	if(numOFEntries && !accountDataArray)
		allIsOK = false;

	if (allIsOK)
		JavaGuiUpdateMyContacts(accountDataArray, numOFEntries);

	if (accountDataArray)
		delete [] accountDataArray;
	FUNCTION_EXIT
}

static void clientManagerRoomsSearchComplete(TNotification eventName, void* param)
{
	FUNCTION_ENTRY
	bool allIsOK = true;
	//ClientRooms* clientRooms = (ClientRooms*) param;
	ClientRooms* clientRooms = ClientRooms::clientRooms();
	
	VidyoClientPrivateSoapAccountData *accountDataArray= NULL;; //todo: replace with a safe ptr
	
	size_t numOFEntries = clientRooms->getNumEntries();
	
	if(numOFEntries && (accountDataArray = new VidyoClientPrivateSoapAccountData[numOFEntries]) )
	{
		for(int i=0; i<numOFEntries; i++)
		{
			if(!clientRooms->copyEntryAtIndex(i, accountDataArray[i]))
			{
				allIsOK = false;
				break;
			}
		}
	}
	
	if(numOFEntries && !accountDataArray)
		allIsOK = false;
	
	if (allIsOK)
		JavaGuiUpdateMyRooms(accountDataArray, numOFEntries);
	
	LOGI( "clientManagerRoomsSearchComplete called, with %d rooms:" , numOFEntries);
/* Commented out so User Name(s) are not present in the log file
	for(int ii= 0; ii<numOFEntries; ii++)
	{
		LOGI( "clientManagerRoomsSearchComplete:  %d) %s,%s" , ii, accountDataArray[ii].displayName,accountDataArray[ii].entityID);
	}
*/
	
	
	if (accountDataArray)
		delete [] accountDataArray;
	FUNCTION_EXIT
}


static void clientManagerAllContactsSearchStarted(TNotification eventName, void* param)
{
        FUNCTION_ENTRY

        /*
        ClientAllContacts* clientAllContacts = (ClientAllContacts*) param;

        size_t numOFEntries = clientAllContacts->getNumPortalEntries();

        // Let the Java code know the records counts
        JavaGuiRecCountUpdateAllContacts(clientAllContacts->getNumPortalEntries(),
            clientAllContacts->getNumCacheEntries(),
            clientAllContacts->getMaxCacheRecs(),
            clientAllContacts->getStartCacheRecNum(),
            clientAllContacts->getEndCacheRecNum());
*/
        clientManagerAllContactsSearchComplete(eventName, param);

        FUNCTION_EXIT
}

static void clientManagerAllContactsSearchComplete(TNotification eventName, void* param)
{
	FUNCTION_ENTRY
	bool allIsOK = true;
	ClientAllContacts* clientAllContacts = (ClientAllContacts*) param;
	VidyoClientPrivateSoapAccountData *accountDataArray= NULL;; //todo: replace with a safe ptr
	
	bool currentllySearching = ClientAllContacts::clientAllContacts()->RefreshEnabled();
	if (currentllySearching) {
		size_t numOFEntries = clientAllContacts->getNumEntries();
		size_t actualNumEntries = 0;
	
		if(numOFEntries && (accountDataArray = new VidyoClientPrivateSoapAccountData[numOFEntries]) )
		{
			for(int i=0; i<numOFEntries; i++)
			{
				if(!clientAllContacts->copyEntryAtIndex(i, accountDataArray[i]))
				{
					allIsOK = false;
					LOGI( "clientManagerAllContactsSearchComplete failed: at %d, numOfEntries = %d, endCacheRecNum=%d, numCacheEnries=%d" , i, numOFEntries,
							clientAllContacts->getEndCacheRecNum(), clientAllContacts->getNumCacheEntries());
				} else {
					actualNumEntries++;
				}
			}
			if (actualNumEntries > 0)
				JavaGuiUpdateAllContacts(accountDataArray, numOFEntries);
		}
		else if (numOFEntries == 0)
		{
			// Don't like this but lets allocate a 0 length array
			if(accountDataArray = new VidyoClientPrivateSoapAccountData[0]) {
				JavaGuiUpdateAllContacts(accountDataArray, 0);
			}
		}
	
		if (accountDataArray) {
			delete [] accountDataArray;

			// Let the Java code know the records counts
			JavaGuiRecCountUpdateAllContacts(clientAllContacts->getNumPortalEntries(),
					clientAllContacts->getNumCacheEntries(),
					clientAllContacts->getMaxCacheRecs(),
					clientAllContacts->getStartCacheRecNum(),
					actualNumEntries - 1);
//	            clientAllContacts->getEndCacheRecNum());
		}
	}
	
	FUNCTION_EXIT
}
static const char* VidyoBool2str(VidyoBool b)
{
	return b?"yes":"no";
}

static const char* VidyoClientPrivateSoapEntityType2str(VidyoClientPortalServiceEntityType t)
{
	switch(t)
	{
		case VIDYO_CLIENT_ENTITY_TYPE_MEMBER: return "Member";
		case VIDYO_CLIENT_ENTITY_TYPE_ROOM: return "Room";
		case VIDYO_CLIENT_ENTITY_TYPE_LEGACY: return "Legacy";
		case VIDYO_CLIENT_ENTITY_TYPE_ANY: return "Any";
		default: return "???";
	}
}
static const char* VidyoClientPrivateSoapMemberStatus2str(VidyoClientPrivateSoapMemberStatus s)
{
	switch (s)
	{
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_ONLINE: return "Online";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_OFFLINE: return "Offline";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_BUSY: return "Busy";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_BUSY_IN_OWN_ROOM: return "Busy in own room";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RINGING: return "Ringing";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RING_ACCEPTED: return "Ring accepted";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RING_REJECTED: return "Ring rejected";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RING_NO_ANSWER: return "Ring no answer";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_ALERTING: return "Alerting";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_ALERT_CANCELLED: return "Alert Cancelled";
		
	}
	return "???";
}

static const char* VidyoClientPrivateSoapMemberMode2str(VidyoClientPrivateSoapMemberMode m)
{
	switch (m)
	{
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_MODE_AVAILABLE: return "Available";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_MODE_AWAY: return "Away";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_MODE_DONOTDISTURB: return "Do not disturb";
	}
	return "???";
	
}

static const char* VidyoClientPrivateSoapRoomStatus2str(VidyoClientPrivateSoapRoomStatus s)
{
	switch(s)
	{
		case VIDYO_CLIENT_PRIVATE_SOAP_ROOM_EMPTY: return "Room is empty";
		case VIDYO_CLIENT_PRIVATE_SOAP_ROOM_FULL: return "Room is full";
		case VIDYO_CLIENT_PRIVATE_SOAP_ROOM_OCCUPIED: return "Room is occupied";
	}
	return "???";
}


static void clientManagerSearchByEntityIDResponseHandler(TNotification eventName, void* param)
{
	FUNCTION_ENTRY
	
	if (!getContactManager()->isMemberRoomsUpdatesActive())
		return;

	VidyoClientPrivateSoapOutEventSearch *response =  (VidyoClientPrivateSoapOutEventSearch*)param;
	if (!response)
	{
		LOGE("clientManagerSearchByEntityIDResponseHandler paramter is NULL");
	}
	else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_ENTITY_ID )
	{
		LOGE("clientManagerSearchByEntityIDResponseHandler response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_ENTITY_ID");
	}
	else if (response->error != 0)
	{
		LOGE("clientManagerSearchByEntityIDResponseHandler response->error == %d", response->error );
	}else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
	{
		LOGE("clientManagerSearchByEntityIDResponseHandler response->result != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS (%d)",response->result);
	}
	else
	{
		LOGI("clientManagerSearchByEntityIDResponseHandler response->numEntries= %d", response->numEntries);
		LOGI( "typeRequest = %d\n"
			 "requestId = %d\n"			
			 "error = %d\n"
			 "total = %d\n"				
			 "start = %d\n"				
			 "numEntries = %d\n"			
			 "result = %d\n",
			 (int)response->typeRequest,
			 (int)response->requestId,			
			 (int)response->error,
			 (int)response->total,				
			 (int)response->start,				
			 (int)response->numEntries,			
			 (int)response->result);
		
		if(!response->error)
		{
			for(int i=0; i<response->numEntries;i++)
			{
				VidyoClientPrivateSoapAccountData d = response->accountData[i];
				if(	!d.roomMode.hasPIN)
					d.roomMode.roomPIN[0]=0;

				LOGI( "entityID: %s |"
					 "participantID: %s |"			
					 "entityType: %s |"
					 "displayName: %s |"
					 "extension	: %s |"
					 "tenant: %s |"
					 "emailAddress: %s |"
					 "tenant: %s | "
					 "memberStatus: %s |"
					 "memberMode: %s |"
					 "canCallDirect: %s |"
					 "canJoinMeeting: %s |"
					 "roomStatus: %s |"
					 "roomURL: %s |"
					 "isRoomLocked: %s |"
					 "hasPIN: %s |"
					 "roomPIN: %s |"
					 "canControl: %s |",
					 d.entityID,
					 d.participantID,			
					 VidyoClientPrivateSoapEntityType2str(d.entityType),
					 d.displayName,
					 d.extension	,
					 d.tenant,
					 d.emailAddress,
					 d.tenant,
					 VidyoClientPrivateSoapMemberStatus2str(d.memberStatus),
					 VidyoClientPrivateSoapMemberMode2str(d.memberMode),
					 VidyoBool2str(d.canCallDirect),
					 VidyoBool2str(d.canJoinMeeting),
					 VidyoClientPrivateSoapRoomStatus2str(d.roomStatus),
					 d.roomMode.roomURL,
					 VidyoBool2str(d.roomMode.isRoomLocked),
					 VidyoBool2str(d.roomMode.hasPIN),
					 d.roomMode.roomPIN,
					 VidyoBool2str(d.canControl));
				
			}
			
		}
	
		JavaGuiUpdateMemberRooms(response->accountData, response->numEntries);
	}
	
	FUNCTION_EXIT
}

static void clientManagerGetPArticipantsResponseHandler(TNotification eventName, void* param)
{
	FUNCTION_ENTRY
	VidyoClientPrivateSoapOutEventGetParticipants *response =  (VidyoClientPrivateSoapOutEventGetParticipants*)param;
	if (!response)
	{
		LOGE("clientManagerGetPArticipantsResponseHandler parameter is NULL");
	}
	else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_GET_PARTICIPANTS )
	{
		LOGE("clientManagerGetPArticipantsResponseHandler response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_GET_PARTICIPANTS");
	}
	else if (response->error != 0)
	{
		LOGE("clientManagerGetPArticipantsResponseHandler response->error == %d", response->error );
	}else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
	{
				LOGE("clientManagerGetPArticipantsResponseHandler response->result != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS (%d)",response->result);
	}
	else
	{
		LOGI("clientManagerGetPArticipantsResponseHandler response->numEntries= %d", response->numEntries);
	
	LOGI( "typeRequest = %d\n"
		 "error = %d\n"
		 "total = %d\n"				
		 "start = %d\n"				
		 "numEntries = %d\n"			
		 "result = %d\n",
		 (int)response->typeRequest,
		 (int)response->error,
		 (int)response->total,				
		 (int)response->start,				
		 (int)response->numEntries,			
		 (int)response->result);	
	JavaGuiUpdateRoomParticipants(response->participantData, response->numEntries);
        }
	
	FUNCTION_EXIT
}
void doStartPortalUpdates(void)
{
	getContactManager()->doStartPortalUpdates();
}

void doStopPortalUpdates(void)
{
	getContactManager()->doStopPortalUpdates();
}

void doStartSearch(const char* hint)
{

	getContactManager()->doStartSearch(hint);
}

void doStopSearch(void)
{
	getContactManager()->doStopSearch();
}

VidyoBool doShiftSearch(int shift)
{
        return getContactManager()->doShiftSearch(shift);
}

void doStartRoomParticipantsUpdates(VidyoClientPrivateSoapAccountData *accountData)
{
	getContactManager()->doStartRoomParticipantsUpdates(*accountData);
}

void doStopRoomParticipantsUpdates()
{
	getContactManager()->doStopRoomParticipantsUpdates();
}

void doStartMemberRoomsUpdates(VidyoClientPrivateSoapAccountData* entity)
{
	getContactManager()->doStartMemberRoomsUpdates(*entity);
}

void doStopMemberRoomsUpdates()
{
	getContactManager()->doStopMemberRoomsUpdates();
}

void doStartMyRoomsUpdates()
{
	getContactManager()->doStartMyRoomsUpdates();
}

void doStopMyRoomsUpdates()
{
	getContactManager()->doStopMyRoomsUpdates();
}


void doStartEntityUpdates(VidyoClientPrivateSoapAccountData* entity)
{
	getContactManager()->doStartEntityUpdates(*entity);
}

void doStopEntityUpdates()
{
	getContactManager()->doStopEntityUpdates();
}


void doClearRoomPin(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doClearRoomPin(*accountData);
}

void doSetRoomPin(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doSetRoomPin(*accountData);
}

VidyoBool doAddContact(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doAddContact(*accountData);
}

void doRemoveContact(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doRemoveContact(*accountData);
}

void doDestroyRoom(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doDestroyRoom(*accountData);
}

void doCreateRoom(char name[], char extension[])
{
	getContactManager()->doCreateRoom(name, extension);
}

void doCreateScheduledRoom(VidyoBool usePin)
{
    getContactManager()->doCreateScheduledRoom(usePin);
}

void doGetInviteContent(char roomID[])
{
    getContactManager()->doGetInviteContent(roomID);
}

void doUnlockLockRoom(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doUnlockLockRoom(*accountData);
}

void doLockRoom(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doLockRoom(*accountData);
}

void doDropParticipant(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doDropParticipant(*accountData);
}

void doSetParticipantAudioMute(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doSetParticipantAudioMute(*accountData);
}

void doSetParticipantAudioUnmute(VidyoClientPrivateSoapAccountData* accountData)
{
	getContactManager()->doSetParticipantAudioUnmute(*accountData);
}


ContactManagerHandlerResults contactManagerMessageHandler( VidyoClientOutEvent eventType, 
															VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data)
{
	if ((VidyoClientPrivateOutEvent)eventType==VIDYO_CLIENT_PRIVATE_OUT_EVENT_PORTAL_DATA_CACHE)
	{	
		::dispatchEvent( kVidyoClientPrivateOutEventPortalDataCache, reinterpret_cast<void*>(param));
		return MASSAGE_HANDLED_BY_CONTACT_MANAGER; 
	}else if (VIDYO_CLIENT_PRIVATE_OUT_EVENT_VCSOAP == (VidyoClientPrivateOutEvent)eventType)
	{
		return getContactManager()->onPrivateOutEventVcsoap(param);
	}
	return MASSAGE_NOT_HANDLED_BY_CONTACT_MANAGER; 
}


