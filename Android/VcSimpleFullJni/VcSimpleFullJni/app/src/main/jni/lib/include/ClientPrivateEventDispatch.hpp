//
//  ClientPrivateEventDispatch.hpp
//  Android client
//
//  Created by Raz Galili 
//  Copyright 2010 Vidyo Inc. All rights reserved.
//

#ifndef   __ClientPrivateEventDispatch_hpp__
#define  __ClientPrivateEventDispatch_hpp__

#include "VidyoClientPrivate.h"
#include "VidyoClient.h"
#include "VidyoJniCommon.h"

#include "ClientEventsNotifications.hpp"

LMI_BEGIN_EXTERN_C


// Helper to send private events to VidyoClient
VidyoBool GuiSendPrivateEvent( VidyoClientPrivateInEvent event, //todo: rename this, these are not gui functions
								void *param, size_t paramSize);

// Helper to send private requests to VidyoClient
VidyoUint GuiSendPrivateRequest( VidyoClientPrivateRequest request,
								 void *param1, size_t param1Size, size_t param2);

void GuiOnOutEvent(VidyoClientOutEvent event,
							  VidyoVoidPtr param, VidyoUint paramSize,
							  VidyoVoidPtr data);

LMI_END_EXTERN_C

#endif //__ClientPrivateEventDispatch_hpp__

