//
//  ClientMyContacts.mm
//  VidyoMobile
//
//  Created by Gary Hildebrand on 12/29/10.
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#include <jni.h>
#include "ClientMyContacts.hpp"
#include "ClientEventsNotifications.hpp"

#include "AndroidDebug.h"

// Constants
#define kRefreshSearchTimeInterval 5.0

// Globals
static ClientMyContacts *_clientMyContacts = NULL; 

ClientMyContacts::ClientMyContacts() :
ClientContacts(VIDYO_CLIENT_PRIVATE_CACHE_MY_CONTACTS,
			   kClientMyContactsSearchStarted,
			   kClientMyContactsSearchComplete)
{
	FUNCTION_ENTRY
}

ClientMyContacts::~ClientMyContacts()
{
	FUNCTION_ENTRY
	_clientMyContacts = NULL;
	FUNCTION_EXIT
}

ClientMyContacts *ClientMyContacts::clientMyContacts()
{
	if (_clientMyContacts == NULL)
	{
		_clientMyContacts = new ClientMyContacts();
	}
	return _clientMyContacts;
}


