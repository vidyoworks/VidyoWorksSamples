//
//  ClientContacts.cpp
//
//  Copyright 2011 Vidyo Inc. All rights reserved.
//

#include <jni.h>
#include "ClientEventsNotifications.hpp"
#include "ClientEventDispatch.hpp"
#include "ClientContacts.hpp"
#include "LoginLogic.hpp"
#include <string>
#include <sstream>
#include "VidyoClientPrivate.h" 
#include "TimerDispatch.hpp"
#include "VidyoJniPrivateDefs.h"

using std::string;
using std::stringstream;


// Constants
#define kDefaultRefreshSearchTimeInterval 5.0
#define REFRESH_SEARCH_TIMER_ID "ClientContacts::refreshSearch"

#include "AndroidDebug.h"


//cast any type to a string
template <typename T>
string string_cast(T value)
{
	std::string returnValue("");
	try{
		stringstream ss (stringstream::in | stringstream::out);
		ss << value;
		ss >> returnValue;
	} catch(...)
	{
		LOGE("exception while calling %s",__FUNCTION__);
	}
	
	//function (should) never fail
	return returnValue; 
}

// Helper for (asynchronous) logouts
void ClientContacts::onStateLoggedOut()
{
	FUNCTION_ENTRY
	
	// fail-safe, in case underlying portal data cache was cleared by a forced logout from system/user
	LOGI("Will clear number of entries, id = %u", (unsigned)cacheId);
	numEntries = 0;
	numPortalEntries = 0;
        numCacheEntries = 0;
        maxCacheRecs = 0;
        startCacheRec = 0;
        endCacheRec = 0;
	startedFirstSearch = inSearch = refreshEnabled = refreshPending = VIDYO_FALSE;
	FUNCTION_EXIT
}


// Notification handler for login state change from ClientStateManager
 void ClientContacts::onLoginStateChange(TNotification eventName, void* param)
{
	FUNCTION_ENTRY
	
	GuiClientLoginState clientLoginState =  (GuiClientLoginState)(int)param;
	
	startedFirstSearch = inSearch = refreshEnabled = refreshPending = VIDYO_FALSE;
	
	setRefreshEnabled(false);

	switch (clientLoginState)
	{

		case GUI_CLIENT_LOGIN_STATE_LOGGED_OUT:
			//changes in login state invalidate all previous searches
			startedFirstSearch = inSearch = refreshEnabled = refreshPending = VIDYO_FALSE;
			this->onStateLoggedOut();
			break;
	}
 
	
	FUNCTION_EXIT
}

// Helper for private out-event for response to request to start search of contacts from VidyoClient
 VidyoBool ClientContacts::onPortalDataCacheStart(VidyoClientPrivateOutEventPortalDataCacheStart *event)
{
	FUNCTION_ENTRY
	// check if event has correct cache id
	if (event->cacheId != cacheId)
	{
		FUNCTION_EXIT
		return VIDYO_TRUE;
	}

	// error handling
	if (event->result != VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_RESULT_SUCCESS)
	{
		LOGE("Search contacts request failed, id = %u result = %u",
										 (unsigned)cacheId, event->result);

		// mark not in search, notify listeners
		inSearch = VIDYO_FALSE;
		
		// notify listeners
		::dispatchEvent(completedNotification,this);
		FUNCTION_EXIT
		return VIDYO_FALSE;
	}

	LOGI("No error in response event, %u portal entries", event->portalTotal);

        numEntries = event->numEntries;

        // set total number of entries in the Portal (different than what is cached in the client)
        numPortalEntries = event->portalTotal;
        numCacheEntries = event->numEntries;
        maxCacheRecs = event->maxCacheEntries;
        startCacheRec = event->dataRange.startIndex;
        endCacheRec = event->dataRange.endIndex;


	// notify listeners
	::dispatchEvent(startedNotification,this);
FUNCTION_EXIT
	return VIDYO_TRUE;
}

// Helper for private out-event for signaling completion of start search of contacts from VidyoClient
 VidyoBool ClientContacts::onPortalDataCacheCompleted(VidyoClientPrivateOutEventPortalDataCacheCompleted *event)
{
	FUNCTION_ENTRY
	// check if event has correct cache id
	if (event->cacheId != cacheId)
	{
		FUNCTION_EXIT
		return VIDYO_TRUE;
	}

	// error handling
	if (event->result != VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_RESULT_SUCCESS)
	{
		LOGE("Search contacts request failed, id = %u result = %u",
										 (unsigned)cacheId, event->result);
		// mark not in search, notify listeners
		inSearch = VIDYO_FALSE;
		
		// notify listeners
		::dispatchEvent(completedNotification, this);
		FUNCTION_EXIT
		return VIDYO_FALSE;
	}

	LOGI("No error in response event, %u entries", event->cacheTotal);

	// set total number of entries
	numEntries = event->cacheTotal;

        // set total number of entries in the Portal (different than what is cached in the client)
        numPortalEntries = event->portalTotal;
        numCacheEntries = event->cacheTotal;
        maxCacheRecs = event->maxCacheEntries;
        startCacheRec = event->dataRange.startIndex;
        endCacheRec = event->dataRange.endIndex;

        LOGI("CacheCompleted: startIndex=%u, endIndex=%u", event->dataRange.startIndex, event->dataRange.endIndex);


	// mark search complete, notify listeners
	inSearch = VIDYO_FALSE;
	
	// notify listeners
	::dispatchEvent(completedNotification, this);
	FUNCTION_EXIT
	return VIDYO_TRUE;
}

// Helper for private out-event for signaling completion of refresh search of contacts from VidyoClient
 VidyoBool ClientContacts::onPortalDataCacheRefreshed(VidyoClientPrivateOutEventPortalDataCacheRefresh *event)
{
//	FUNCTION_ENTRY
	// check if event has correct cache id
	if (event->cacheId != cacheId)
	{
		//FUNCTION_EXIT
		return VIDYO_TRUE;
	}

	// error handling
	if (event->result != VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_RESULT_SUCCESS)
	{
		// TODO: alert user
		LOGE(" ClientContacts::onPortalDataCacheRefreshed - Search contacts request failed, id = %u result = %u",
										 (unsigned)cacheId, event->result);
		// mark not in search, notify listeners
		inSearch = VIDYO_FALSE;

		// notify listeners
		::dispatchEvent(completedNotification, this);
//FUNCTION_EXIT
		return VIDYO_FALSE;
	}

	LOGI("No error in response event, %u entries", event->cacheTotal);

	// set total number of entries
	numEntries = event->cacheTotal;
	startCacheRec = event->dataRange.startIndex;
	endCacheRec = event->dataRange.endIndex;
	numPortalEntries = event->portalTotal;
	maxCacheRecs = event->maxCacheEntries;

	// mark search complete, notify listeners

	inSearch = VIDYO_FALSE;
	
	// notify listeners
	::dispatchEvent(completedNotification, this);
	
	return VIDYO_TRUE;
}

 // Helper for private out-event for signaling completion of shift request of contacts from VidyoClient
  VidyoBool ClientContacts::onPortalDataCacheShift(VidyoClientPrivateOutEventPortalDataCacheShift *event)
 {
 //      FUNCTION_ENTRY
    LOGE("in onPortalDataCacheShift");
         // check if event has correct cache id
         if (event->cacheId != cacheId)
         {
                 //FUNCTION_EXIT
                 return VIDYO_TRUE;
         }

         // error handling
         if (event->result != VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_RESULT_SUCCESS)
         {
                 // TODO: alert user
                 LOGE(" ClientContacts::onPortalDataCacheShifted - Search contacts request failed, id = %u result = %u",
                                                                                  (unsigned)cacheId, event->result);
                 // mark not in search, notify listeners
                 inSearch = VIDYO_FALSE;

                 // notify listeners
                 ::dispatchEvent(completedNotification, this);
 //FUNCTION_EXIT
                 return VIDYO_FALSE;
         }

         LOGI("No error in response event, %u entries", event->cacheTotal);


         // set total number of entries
         numEntries = event->cacheTotal;
         startCacheRec = event->dataRange.startIndex;
         endCacheRec = event->dataRange.endIndex;
         numPortalEntries = event->portalTotal;
         maxCacheRecs = event->maxCacheEntries;

LOGE("in onPortalDataCacheShift: numEntries=%u, start=%u, end=%u", numEntries, startCacheRec, endCacheRec);
         // mark search complete, notify listeners

         inSearch = VIDYO_FALSE;

         // notify listeners
         ::dispatchEvent(completedNotification, this);

         return VIDYO_TRUE;
 }



// Notification handler for VIDYO_CLIENT_PRIVATE_OUT_EVENT_PORTAL_DATA_CACHE events
void ClientContacts::onPortalDataCacheEvent(TNotification eventName,  void* param)
{
//	FUNCTION_ENTRY
	// based on request type of VIDYO_CLIENT_PRIVATE_OUT_EVENT_PORTAL_DATA_CACHE event, dispatch to appropriate helper function
	VidyoClientPrivateOutEventPortalDataCacheStart *parameter = (VidyoClientPrivateOutEventPortalDataCacheStart *)param;
	VidyoClientPrivatePortalDataCacheRequestType requestType = parameter->typeRequest;
	VidyoBool ret = VIDYO_TRUE;
	switch (requestType)
	{
		case VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_START:
			ret = this->onPortalDataCacheStart((VidyoClientPrivateOutEventPortalDataCacheStart *)param);
			break;
		case VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_COMPLETED:
			ret = this->onPortalDataCacheCompleted((VidyoClientPrivateOutEventPortalDataCacheCompleted *)param);
			break;
		case VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_RETRIEVE:
			break;
		case VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_REFRESH:
			ret = this->onPortalDataCacheRefreshed((VidyoClientPrivateOutEventPortalDataCacheRefresh *)param);
			break;
                case VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_SHIFT:
                        ret = this->onPortalDataCacheShift((VidyoClientPrivateOutEventPortalDataCacheShift *)param);
                        break;
		case VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_CLEAR:
		case VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_STOP:
			break;
		default:
			LOGE("ClientContacts::onPortalDataCacheEvent - Unrecognized Private Portal Data Cache Event = %u",
											   requestType);
			//FUNCTION_EXIT
			return;
	}
	if (!ret)
	{
		LOGE("ClientContacts::onPortalDataCacheEvent - Something went wrong with processing of event!");
	}
//	FUNCTION_EXIT
}



// This function send out a request to shift to the next or previous records
VidyoBool ClientContacts::doShift(int shift)
{
        FUNCTION_ENTRY
        VidyoBool ret = VIDYO_FALSE;

        // based on state, send request to refresh search contacts
        GuiClientLoginState clientLoginState =  ::GetCurrentClientLoginState();
        //double currentTime = getCurrentWallTimeSeconds();

        if ((clientLoginState == GUI_CLIENT_LOGIN_STATE_LOGGED_IN)
           && startedFirstSearch && !inSearch
                /*&& (currentTime - dateLastSearchCompleted  <= -(refreshInterval) )*/)
        {
                numSearches++;
                LOGI("shift, %d searches so far, id = %u", numSearches, (unsigned)cacheId);
                VidyoClientPrivateInEventPortalDataCacheShift shiftEvent/* = {0}*/;
                shiftEvent.typeRequest = VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_SHIFT;
                shiftEvent.cacheId = cacheId;
                if (shift > 0) {
                    shiftEvent.shiftType = VIDYO_CLIENT_PRIVATE_PORTAL_CACHE_SHIFT_FORWARD;   // Shift cache data forward
                    shiftEvent.numEntries = shift;
                } else {
                    shiftEvent.shiftType = VIDYO_CLIENT_PRIVATE_PORTAL_CACHE_SHIFT_BACKWARD;   // Shift cache data backward
                    shiftEvent.numEntries = shift * -1;
                }

                LOGI("sending DATA_CACHE_SHIFT, shift=%d",shift);

                inSearch = VIDYO_TRUE;
                (void)GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_PORTAL_DATA_CACHE, &shiftEvent,
                                                                  sizeof(VidyoClientPrivateInEventPortalDataCacheShift));
                ret = VIDYO_TRUE;
        }else {
                LOGI("clientLoginState =  %d startedFirstSearch = %d inSearch %d", (int) clientLoginState, (int)startedFirstSearch, (int) inSearch);
        }

        FUNCTION_EXIT
        return ret;
}





// Helper, which with the right conditions, refreshes the search with the current query string
void ClientContacts::doRefresh()
{
	FUNCTION_ENTRY
	// based on state, send request to refresh search contacts
	GuiClientLoginState clientLoginState =  ::GetCurrentClientLoginState();
	//double currentTime = getCurrentWallTimeSeconds();
	
	if ((clientLoginState == GUI_CLIENT_LOGIN_STATE_LOGGED_IN)
	   && startedFirstSearch && !inSearch
		/*&& (currentTime - dateLastSearchCompleted  <= -(refreshInterval) )*/)
	{
		numSearches++;
		LOGI("refresh, %d searches so far, id = %u", numSearches, (unsigned)cacheId);
		VidyoClientPrivateInEventPortalDataCacheRefresh refreshEvent/* = {0}*/;
		refreshEvent.typeRequest = VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_REFRESH;
		refreshEvent.cacheId = cacheId;
		inSearch = VIDYO_TRUE;
		(void)GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_PORTAL_DATA_CACHE, &refreshEvent,
								  sizeof(VidyoClientPrivateInEventPortalDataCacheRefresh));
	}else {
		LOGI("clientLoginState =  %d startedFirstSearch = %d inSearch %d", (int) clientLoginState, (int)startedFirstSearch, (int) inSearch);
	}

	FUNCTION_EXIT
}

// Helper, which periodically runs to refresh the search with the current query string
// Note: when searches take any measurable time, actual refresh interval approximately twice value in refreshInterval
void ClientContacts::refreshSearch()
{
	FUNCTION_ENTRY
	if (!refreshEnabled)
	{
		LOGI("refresh disabled, will not run itself again");
		refreshPending = VIDYO_FALSE;
		FUNCTION_EXIT
		return;
	}

	this->doRefresh();

	LOGI("refresh enabled, will run itself again");
	refreshPending = VIDYO_TRUE;
	TD<ClientContacts,void,void>::executeAfterDelay(*this, &ClientContacts::refreshSearch, refreshInterval, objectID.c_str());
	FUNCTION_EXIT
}

// Default initializer
ClientContacts::ClientContacts()
:onLoginStateChangeAdapter(this,&ClientContacts::onLoginStateChange), 
onPortalDataCacheEventAdapter(this,&ClientContacts::onPortalDataCacheEvent)
{
	FUNCTION_ENTRY
	initWithCacheId(VIDYO_CLIENT_PRIVATE_CACHE_MY_CONTACTS, NOTIFICATION(""), NOTIFICATION(""));
	FUNCTION_EXIT
}

ClientContacts::ClientContacts(VidyoClientPrivatePortalDataCacheId aCacheId,
			   TNotification aStartedNotification,
			   TNotification aCompletedNotification)
:onLoginStateChangeAdapter(this,&ClientContacts::onLoginStateChange), 
onPortalDataCacheEventAdapter(this,&ClientContacts::onPortalDataCacheEvent)			   
{
	FUNCTION_ENTRY
	initWithCacheId(aCacheId, aStartedNotification, aCompletedNotification);
	FUNCTION_EXIT
}

// Designated initializer 
void ClientContacts::initWithCacheId(VidyoClientPrivatePortalDataCacheId aCacheId,
	TNotification aStartedNotification,
	TNotification aCompletedNotification)
{
	FUNCTION_ENTRY
		this->cacheId = aCacheId;
		this->startedNotification = aStartedNotification;
		this->completedNotification = aCompletedNotification;
		refreshInterval = kDefaultRefreshSearchTimeInterval;
		numEntries = 0;
		numPortalEntries = 0;
		numCacheEntries = 0;
		maxCacheRecs = 0;
		startCacheRec = 0;
		endCacheRec = 0;

		currentQuery = "";
		startedFirstSearch = inSearch = refreshEnabled = refreshPending = VIDYO_FALSE;
		numSearches = 0;
	
	//create a string from the address of this pointer
	//to use as a unique id for current object
	objectID = string_cast<long int>((long int)this); 
				
	LOGI("objectID %s",objectID.c_str());
	
		// register for notifications
	//todo: redefine this with a better interface
	registerForEvent(kClientStateManagerLoginStateChange, &onLoginStateChangeAdapter);
	registerForEvent(kVidyoClientPrivateOutEventPortalDataCache, &onPortalDataCacheEventAdapter); 
	FUNCTION_EXIT
}

ClientContacts::~ClientContacts()
{
	FUNCTION_ENTRY
	//[[NSNotificationCenter defaultCenter] removeObserver:self]; //TODO: remove notifications	
	::unregisterEventHandler(&onLoginStateChangeAdapter);
	::unregisterEventHandler(&onPortalDataCacheEventAdapter);
	
	cancelTimer(objectID.c_str());
	startedFirstSearch = inSearch = refreshEnabled = refreshPending = VIDYO_FALSE;
	numEntries = 0;
	numPortalEntries = 0;
        numCacheEntries = 0;
        maxCacheRecs = 0;
        startCacheRec = 0;
        endCacheRec = 0;
	FUNCTION_EXIT

}

// Search own contacts on server, using specified UTF-8 search query string
 void ClientContacts::searchWithQueryString(const std::string &query)
{
	FUNCTION_ENTRY
	// reset number of entries in contact store
	if (!inSearch)
	{
		numEntries = 0;
		numPortalEntries = 0;
                numCacheEntries = 0;
                maxCacheRecs = 0;
                startCacheRec = 0;
                endCacheRec = 0;
	}

	// based on state, send request to search my contacts
	GuiClientLoginState clientLoginState =  ::GetCurrentClientLoginState();

	if (clientLoginState == GUI_CLIENT_LOGIN_STATE_LOGGED_IN)
	{
		// remember query, for periodic refresh
		this->currentQuery = query;

		// send request
		if (!inSearch)
		{
			numSearches++;
			LOGI("query string is %s, %d searches so far, id = %u",
											query.c_str(), numSearches,
											(unsigned)cacheId);
			startedFirstSearch = VIDYO_TRUE;
			VidyoClientPrivateInEventPortalDataCacheStart startEvent/* = {0}*/;
			startEvent.typeRequest = VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_START;
			startEvent.cacheId = cacheId;
			(void)strlcpy(startEvent.searchString, query.c_str(),
						  sizeof(startEvent.searchString));
			inSearch = VIDYO_TRUE;
			(void)GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_PORTAL_DATA_CACHE, &startEvent,
									  sizeof(VidyoClientPrivateInEventPortalDataCacheStart));
		}
	}
	FUNCTION_EXIT
}

VidyoBool ClientContacts::copyEntryAtIndex(int index, VidyoClientPrivateSoapAccountData &buffer)
{
//	FUNCTION_ENTRY
	// based on state, send request to retrieve contact at specified index
	GuiClientLoginState clientLoginState =  ::GetCurrentClientLoginState(); 
	if (clientLoginState == GUI_CLIENT_LOGIN_STATE_LOGGED_IN)
	{
		VidyoClientPrivateRetrievePortalDataCache retrieveRequest/* = {0}*/;
		retrieveRequest.cacheId = cacheId;
		retrieveRequest.startIndex = (VidyoUint)index;
		retrieveRequest.numEntries = 1;
		retrieveRequest.retrieveFilter.disabledRooms = VIDYO_FALSE;
		retrieveRequest.retrieveFilter.myContacts = VIDYO_FALSE;
		retrieveRequest.retrieveFilter.myRooms = VIDYO_FALSE;
		GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_PORTAL_DATA_CACHE, &retrieveRequest,
									sizeof(VidyoClientPrivateRetrievePortalDataCache), 0);
		if (retrieveRequest.result != VIDYO_CLIENT_PRIVATE_PORTAL_DATA_CACHE_RESULT_SUCCESS)
		{
			LOGE("ClientContacts::copyEntryAtIndex retrieve of record %d failed, result is %u",
											 index, retrieveRequest.result);
			//FUNCTION_EXIT
			return VIDYO_FALSE;
		}
		if (retrieveRequest.userData[0].dataIndex != (VidyoUint)index)
		{
			LOGE("ClientContacts::copyEntryAtIndex retrieve of record %d mismatched, retrieved record has index of %u",
											 index, retrieveRequest.userData[0].dataIndex);
			//FUNCTION_EXIT
			return VIDYO_FALSE;
		}

		// copy retrieved data
		memcpy(&buffer, &(retrieveRequest.userData[0].accountData), sizeof(VidyoClientPrivateSoapAccountData));
		//FUNCTION_EXIT
		return VIDYO_TRUE;
	}

	//FUNCTION_EXIT
	// failure if reached here
	return VIDYO_FALSE;
}

VidyoBool ClientContacts::RefreshEnabled()
{
	FUNCTION_ENTRY FUNCTION_EXIT
	return refreshEnabled;

}

void ClientContacts::setRefreshEnabled(VidyoBool enabled)
{
	FUNCTION_ENTRY
	refreshEnabled = enabled;
	if (enabled)
	{
		LOGI("refresh enabled, will try to refresh now");
		refreshSearch();
		if (!refreshPending)
		{
			LOGI("refresh was not pending, will schedule future refresh");
			refreshPending = true;
		}
	}else{
		refreshPending = inSearch = VIDYO_FALSE;
	}
	
	FUNCTION_EXIT
}

