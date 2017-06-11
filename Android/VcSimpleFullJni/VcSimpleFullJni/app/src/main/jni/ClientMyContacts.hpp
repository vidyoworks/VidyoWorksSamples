//
//  ClientMyContacts.hpp
//
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#ifndef __ClientMyContacts_hpp__
#define __ClientMyContacts_hpp__

#include "ClientEventsNotifications.hpp"
#include "ClientContacts.hpp"

// Names for notifications from this object
#define kClientMyContactsSearchStarted NOTIFICATION("My Contacts Search Started")
#define kClientMyContactsSearchComplete NOTIFICATION("My Contacts Search Complete")

class ClientMyContacts : public ClientContacts
{
public:
	static ClientMyContacts *clientMyContacts();

private:
	ClientMyContacts();
	virtual ~ClientMyContacts();

};

#endif // __ClientMyContacts_hpp__
