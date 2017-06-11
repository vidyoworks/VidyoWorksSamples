//
//  ClientEventDispatch.hpp
//  Android client
//
//  Created by Raz Galili 
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#ifndef   __ClientEventDispatch_hpp__
#define  __ClientEventDispatch_hpp__

#include "VidyoClient.h"
#include "VidyoJni.h"

VIDYOJNI_BEGIN_EXTERN_C

void GuiOnOutEvent(VidyoClientOutEvent event,
							  VidyoVoidPtr param, VidyoUint paramSize,
							  VidyoVoidPtr data);

//a very simple, thread unsafe event dispathcer 
typedef void (*EventHandlerFunc)(TNotification eventName, void* param);

void dispatchEvent(TNotification eventName, void* param);
void registerForEvent(TNotification eventName,EventHandlerFunc handler);
void unregisterEventHandlerForEvent(TNotification eventName,EventHandlerFunc handler);
void unregisterEventHandler(EventHandlerFunc handler);

double getCurrentWallTimeSeconds();

VIDYOJNI_END_EXTERN_C

#if defined(__cplusplus)

class EventHandlerInterface
{
public:
	virtual void eventHandler(TNotification eventName, void* param) = 0;
};


template <class OwnerClass>
class EventHandlerRedirector : public EventHandlerInterface
{
public:
	typedef void (OwnerClass::*OwnerEventHandlerType)(TNotification eventName, void* param) ;


	EventHandlerRedirector(OwnerClass *owner, OwnerEventHandlerType eventHandler) :
	m_owner(*owner), m_eventHandler(eventHandler) {};
	virtual ~EventHandlerRedirector() {}
	virtual void eventHandler(TNotification eventName, void* param)
	{
		((m_owner).*(m_eventHandler))(eventName, param);
	}


private:
	OwnerClass &m_owner;
	OwnerEventHandlerType m_eventHandler;
	
};

typedef EventHandlerInterface* PEventHandlerInterface;

void registerForEvent(TNotification eventName,PEventHandlerInterface handler);
void unregisterEventHandler(TNotification eventName,PEventHandlerInterface handler);
void unregisterEventHandler(PEventHandlerInterface handler); //unregister from all events

#endif

#endif //__ClientEventDispatch_hpp__

