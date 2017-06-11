//
//  ClientAllContacts.mm
//  VidyoMobile
//
//  Created by Gary Hildebrand on 12/29/10.
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#include <jni.h>
#include "ClientEventsNotifications.hpp"
#include "ClientAllContacts.hpp"

// Constants
#define kRefreshSearchTimeInterval 5.0 

// Globals
static ClientAllContacts *_clientAllContacts = NULL; //todo: replace with safe pointer



ClientAllContacts::ClientAllContacts():
	ClientContacts(VIDYO_CLIENT_PRIVATE_CACHE_ALL_CONTACTS, 
	kClientAllContactsSearchStarted, 
	kClientAllContactsSearchComplete)
{
}

ClientAllContacts::~ClientAllContacts()
{
	_clientAllContacts = NULL;
}

ClientAllContacts *ClientAllContacts::clientAllContacts()
{
	if (_clientAllContacts == NULL)
	{
		_clientAllContacts = new ClientAllContacts();
	}
	return _clientAllContacts;
}


