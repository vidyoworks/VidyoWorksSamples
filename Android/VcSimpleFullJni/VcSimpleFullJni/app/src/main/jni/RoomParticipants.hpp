//
//  RoomParticipants.hpp
//
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#ifndef __RoomParticipants_hpp__
#define __RoomParticipants_hpp__

#include "ClientEventsNotifications.hpp"
#include "ClientContacts.hpp"
#include <string>
#include "VidyoClientPrivate.h"


// Names for notifications from this object
#define kRoomParticipantsSearchStarted NOTIFICATION("RoomsParticipantsStarted")
#define kRoomParticipantsSearchComplete NOTIFICATION("oomsParticipantsComplete")

class RoomParticipants 
{
public:
	static RoomParticipants *roomParticipants();
	
	void searchWithQueryString(const VidyoClientPrivateSoapAccountData &query);
	VidyoBool RefreshEnabled();
	void setRefreshEnabled(VidyoBool enabled);
	const std::string& getConferenceID() const { return entityID; }
	
private:
	RoomParticipants();
	virtual ~RoomParticipants();
	void refreshSearch();
	void doRefresh();
	
	double  refreshInterval; //in seconds
	std::string entityID; //entity id of user

	VidyoBool refreshEnabled;
	std::string objectID;	//an ID used to identify the object against timers
};


#endif // __RoomParticipants_hpp__
