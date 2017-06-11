//
//  ClientRooms.hpp
//
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#ifndef __ClientRooms_hpp__
#define __ClientRooms_hpp__

#include "ClientEventsNotifications.hpp"
#include "ClientContacts.hpp"
#include <string>
#include "VidyoClientPrivate.h"
#include "ClientEventDispatch.hpp"


// Names for notifications from this object
#define kClientRoomsSearchStarted NOTIFICATION("Rooms Search Started")
#define kClientRoomsSearchComplete NOTIFICATION("Rooms Search Complete")

class ClientRooms : public ClientContacts
{
public:
	static ClientRooms *clientRooms();

private:
	ClientRooms();
	virtual ~ClientRooms();

};

//compare to request type on VidyoClientPrivateSoapOutEventSearch //TODO: rename requestID to requestType 
#define MEMBER_ROOMS_SEARCH_ID 12
#define ENTITY_INFO_SEARCH_ID 15

class SearchByEntityID
{
public:
	
	void searchWithQueryString(const VidyoClientPrivateSoapAccountData &query);
	VidyoBool RefreshEnabled();
	void setRefreshEnabled(VidyoBool enabled);
	const std::string& getEntityID() const { return entityID; }

	unsigned getRequestID() const { return requestId; }//TODO: rename requestID to requestType 
	
	void onLoginStateChange(TNotification eventName, void* param);

	SearchByEntityID(unsigned aRequestID); //TODO: rename requestID to requestType 
	virtual ~SearchByEntityID();
	void doRefresh();

private:
	void refreshSearch();
	
	double  refreshInterval; //in seconds
	std::string entityID; //entity id of user

	VidyoBool refreshEnabled;
	std::string objectID;	//an ID used to identify the object against timers
	unsigned requestId; //TODO: rename requestID to requestType 
	EventHandlerRedirector<SearchByEntityID> onLoginStateChangeAdapter; //todo: rewrite this, redirectors are ugly

};



class MemberRooms :public SearchByEntityID
{
public:
	MemberRooms():SearchByEntityID(MEMBER_ROOMS_SEARCH_ID){}
	virtual ~MemberRooms(){}
};


class EntityInfoSearch :public SearchByEntityID
{
public:
	EntityInfoSearch():SearchByEntityID(ENTITY_INFO_SEARCH_ID){}
	virtual~ EntityInfoSearch(){}
};

#endif // __ClientRooms_hpp__
