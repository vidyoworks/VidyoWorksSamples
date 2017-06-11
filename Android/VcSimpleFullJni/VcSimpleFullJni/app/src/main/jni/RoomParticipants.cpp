//
//  RoomParticipants.cpp
//  VidyoMobile
//
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#include <jni.h>
#include "RoomParticipants.hpp"
#include "ClientEventsNotifications.hpp"
#include <string>
#include <sstream>
#include "TimerDispatch.hpp"
#include "VidyoJniPrivateDefs.h"

#include "AndroidDebug.h"

using std::string;
using std::stringstream;

// Constants
#define kRefreshSearchTimeInterval 15.0
#define ROOM_PARTICIPANTS_TIMER_ID "ROOM_PARTICIPANTS_TIMER_ID"

// Globals

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


static RoomParticipants *_roomParticipants = NULL; 

RoomParticipants *RoomParticipants::roomParticipants()
{ 
	FUNCTION_ENTRY_EXIT
	if (_roomParticipants == NULL)
	{
		_roomParticipants = new RoomParticipants();
	}
	return _roomParticipants;
}

RoomParticipants::RoomParticipants() : refreshEnabled(VIDYO_FALSE) , refreshInterval(kRefreshSearchTimeInterval)
{ 
	FUNCTION_ENTRY_EXIT

}

RoomParticipants::~RoomParticipants()
{ 
	FUNCTION_ENTRY_EXIT
	cancelTimer(ROOM_PARTICIPANTS_TIMER_ID);
	refreshEnabled =  VIDYO_FALSE;
}

void RoomParticipants::searchWithQueryString(const VidyoClientPrivateSoapAccountData &query)
{ 
	FUNCTION_ENTRY_EXIT
	setRefreshEnabled(VIDYO_FALSE);
	entityID = query.entityID;
}

VidyoBool RoomParticipants::RefreshEnabled(){ return refreshEnabled;}

void RoomParticipants::setRefreshEnabled(VidyoBool enabled)
{
	FUNCTION_ENTRY_EXIT
	if (refreshEnabled = enabled)
	{
		LOGI("refresh enabled, will try to refresh now");
		refreshSearch();
	}	
}

void RoomParticipants::refreshSearch()
{
	FUNCTION_ENTRY_EXIT
	if (!refreshEnabled)
	{
		LOGI("refresh disabled, will not run itself again");
		return;
	}
	
	this->doRefresh();
	
	LOGI("refresh enabled, will run itself again");
	TD<RoomParticipants,void,void>::executeAfterDelay(*this, &RoomParticipants::refreshSearch, refreshInterval, ROOM_PARTICIPANTS_TIMER_ID);
}

void RoomParticipants::doRefresh()
{
	FUNCTION_ENTRY_EXIT
	VidyoClientPrivateSoapInEventGetParticipants getParticipantsReq = {0};
	getParticipantsReq.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_GET_PARTICIPANTS;
	strcpy(getParticipantsReq.conferenceID, entityID.c_str());
	getParticipantsReq.start = 0;
	getParticipantsReq.limit = 100;
	getParticipantsReq.searchBy = VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_DISPLAY_NAME;
//	getParticipantsReq.searchBy = VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_EXTENSION_NUM;
	getParticipantsReq.sortOrder = VIDYO_CLIENT_PRIVATE_SOAP_SORT_ORDER_ASCENDING;
	strcpy(getParticipantsReq.searchString, "");
	LOGI("VIDYO_CLIENT_PRIVATE_SOAP_GET_PARTICIPANTS with conferenceid of %s",getParticipantsReq.conferenceID);
	GuiSendPrivateEvent(VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, &getParticipantsReq, sizeof(VidyoClientPrivateSoapInEventGetParticipants));
	
}


