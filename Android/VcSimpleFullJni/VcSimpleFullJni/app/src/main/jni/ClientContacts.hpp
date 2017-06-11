//
//  ClientContacts.hpp
//  VidyoMobile
//
//  Created by Gary Hildebrand on 02/03/11.
//	Android version by Raz Galili
//  Copyright 2011 Vidyo Inc. All rights reserved.
//

#ifndef __ClientContacts_hpp__
#define __ClientContacts_hpp__


#include "ClientEventsNotifications.hpp"
#include "ClientEventDispatch.hpp"
#include "VidyoClientPrivate.h"

#include <string>

class ClientContacts 
{
private:
	
	VidyoClientPrivatePortalDataCacheId cacheId;
	TNotification startedNotification;
	TNotification completedNotification;
	double refreshInterval; //in seconds
	int numEntries;
	int numPortalEntries;   //number of entries that are in the Portal
	int numCacheEntries;
	int maxCacheRecs;
	int startCacheRec;
	int endCacheRec;

	std::string currentQuery;
	std::string objectID;	//an ID used to identify the object against timers
	
	VidyoBool startedFirstSearch;
	VidyoBool inSearch;
	VidyoBool refreshEnabled;	
	VidyoBool refreshPending;
	
	int numSearches;
	

	
	void initWithCacheId(VidyoClientPrivatePortalDataCacheId aCacheId,
						 TNotification aStartedNotification,
						 TNotification aCompletedNotification);
	void onStateLoggedOut();

	void onLoginStateChange(TNotification eventName, void* param);
	void onPortalDataCacheEvent(TNotification eventName, void* param);

	VidyoBool onPortalDataCacheStart(VidyoClientPrivateOutEventPortalDataCacheStart *event);
	VidyoBool onPortalDataCacheCompleted(VidyoClientPrivateOutEventPortalDataCacheCompleted *event);
	VidyoBool onPortalDataCacheRefreshed(VidyoClientPrivateOutEventPortalDataCacheRefresh *event);
	VidyoBool onPortalDataCacheShift(VidyoClientPrivateOutEventPortalDataCacheShift *event);


	void doRefresh();
	void refreshSearch();

	EventHandlerRedirector<ClientContacts> onLoginStateChangeAdapter; //todo: rewrite this, redirectors are ugly
	EventHandlerRedirector<ClientContacts> onPortalDataCacheEventAdapter;



public:
	ClientContacts();
	virtual ~ClientContacts();
	ClientContacts(VidyoClientPrivatePortalDataCacheId aCacheId,
				   TNotification aStartedNotification,
				   TNotification aCompletedNotification);
	
	void searchWithQueryString(const std::string &query);
	VidyoBool copyEntryAtIndex(int index, VidyoClientPrivateSoapAccountData &buffer);
	VidyoBool RefreshEnabled();
	void setRefreshEnabled(VidyoBool enabled);
	VidyoBool doShift(int shift);

	int getNumEntries() const { return numEntries; }
        int getNumPortalEntries() const { return numPortalEntries; }
        int getNumCacheEntries() const { return numCacheEntries; }
        int getMaxCacheRecs() const { return maxCacheRecs; }
        int getStartCacheRecNum() const { return startCacheRec; }
        int getEndCacheRecNum() const { return endCacheRec; }

	const std::string& getQueryString() const { return currentQuery; }

};	


#endif //#ifndef __ClientContacts_hpp__
