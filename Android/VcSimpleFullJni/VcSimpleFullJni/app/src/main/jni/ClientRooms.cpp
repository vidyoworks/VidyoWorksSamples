//
//  ClientRooms.cpp
//  VidyoMobile
//
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#include <jni.h>
#include "ClientRooms.hpp"
#include "ClientEventsNotifications.hpp"
#include <string>
#include <sstream>
#include "TimerDispatch.hpp"
#include "ClientEventDispatch.hpp"
#include "AndroidDebug.h"
#include "VidyoJniPrivateDefs.h"

using std::string;
using std::stringstream;

// Constants
#define kRefreshSearchTimeInterval 15.0


// Globals
static ClientRooms *_clientRooms = NULL; 

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

ClientRooms::ClientRooms() :
ClientContacts(VIDYO_CLIENT_PRIVATE_CACHE_MY_ROOMS,
			   kClientRoomsSearchStarted,
			   kClientRoomsSearchComplete)
{
	FUNCTION_ENTRY
	FUNCTION_EXIT
}

ClientRooms::~ClientRooms()
{
	FUNCTION_ENTRY
	_clientRooms = NULL;
	FUNCTION_EXIT
}

ClientRooms *ClientRooms::clientRooms()
{
	if (_clientRooms == NULL)
	{
		_clientRooms = new ClientRooms();
	}
	return _clientRooms;
}



SearchByEntityID::SearchByEntityID(unsigned aRequestID) : requestId(aRequestID), refreshEnabled(VIDYO_FALSE) , refreshInterval(kRefreshSearchTimeInterval), 
onLoginStateChangeAdapter(this,&SearchByEntityID::onLoginStateChange)
{ 
        //create a string from the address of this pointer
        //to use as a unique id for current object
        objectID = string_cast<long int>((long int)this);
        LOGI("objectID %s",objectID.c_str());

	::registerForEvent(kClientStateManagerLoginStateChange, &onLoginStateChangeAdapter);

}

SearchByEntityID::~SearchByEntityID()
{ 
	cancelTimer(objectID.c_str());
	refreshEnabled =  VIDYO_FALSE;
	::unregisterEventHandler(&onLoginStateChangeAdapter);
}

void SearchByEntityID::searchWithQueryString(const VidyoClientPrivateSoapAccountData &query)
{ 
	FUNCTION_ENTRY
	setRefreshEnabled(VIDYO_FALSE);
	entityID = query.entityID;
LOGI("PWC searchWithQueryString %s", query.entityID);
	FUNCTION_EXIT
}

VidyoBool SearchByEntityID::RefreshEnabled(){ return refreshEnabled;}

void SearchByEntityID::setRefreshEnabled(VidyoBool enabled)
{
	FUNCTION_ENTRY
	if (refreshEnabled = enabled)
	{
		LOGI("refresh enabled, will try to refresh now");
		refreshSearch();
	}	
	FUNCTION_EXIT
}

void SearchByEntityID::refreshSearch()
{
	FUNCTION_ENTRY
	if (!refreshEnabled)
	{
		LOGI("refresh disabled, will not run itself again");
		FUNCTION_EXIT
		return;
	}
	
	this->doRefresh();
	
	LOGI("refresh enabled, will run itself again");
	TD<SearchByEntityID,void,void>::executeAfterDelay(*this, &SearchByEntityID::refreshSearch, refreshInterval, objectID.c_str()); 
	FUNCTION_EXIT
}

void SearchByEntityID::doRefresh()
{
	
	VidyoClientPrivateSoapInEventSearchByEntityId searchByEntityIdReq = {0};
	
		searchByEntityIdReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_ENTITY_ID;
		strcpy(searchByEntityIdReq.entityID, entityID.c_str());
		searchByEntityIdReq.requestId = requestId;
		searchByEntityIdReq.filterValid = VIDYO_TRUE;
		searchByEntityIdReq.start = 0;
		searchByEntityIdReq.limit = VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_SIZE;
		searchByEntityIdReq.searchBy = VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_DISPLAY_NAME;
		searchByEntityIdReq.sortOrder = VIDYO_CLIENT_PRIVATE_SOAP_SORT_ORDER_ASCENDING;
		GuiSendPrivateEvent( VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &searchByEntityIdReq, sizeof(VidyoClientPrivateSoapInEventSearchByEntityId));

}

// Notification handler for login state change from ClientStateManager
void SearchByEntityID::onLoginStateChange(TNotification eventName, void* param)
{
	FUNCTION_ENTRY
	
	refreshEnabled = false;
	
	FUNCTION_EXIT
}

