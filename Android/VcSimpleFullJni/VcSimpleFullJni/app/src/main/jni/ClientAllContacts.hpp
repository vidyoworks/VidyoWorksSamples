//
//  ClientAllContacts.hpp

//  Copyright 2010 Vidyo Inc. All rights reserved.
//
#ifndef __ClientAllContacts_hpp__
#define __ClientAllContacts_hpp__

#include "ClientEventsNotifications.hpp"
#include "ClientContacts.hpp"
#include "VidyoClientPrivate.h"

// Names for notifications from this object
#define kClientAllContactsSearchStarted NOTIFICATION("All Contacts Search Started")
#define kClientAllContactsSearchComplete NOTIFICATION("All Contacts Search Complete")

class  ClientAllContacts : public ClientContacts
{

public:

static ClientAllContacts * clientAllContacts();

private:
	ClientAllContacts();
	virtual ~ClientAllContacts();
	
};

#endif // __ClientAllContacts_hpp__
