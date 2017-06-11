//
//  VidyoJniPrivateDefs.hpp
//  Android client
//
//  Created by Paul Cushman
//  Copyright 2014 Vidyo Inc. All rights reserved.
//

#ifndef   __VidyoJniPrivateDefs_hpp__
#define  __VidyoJniPrivateDefs_hpp__

#include "VidyoClientPrivate.h"
#include "VidyoClient.h"
#include "VidyoJniCommon.h"

LMI_BEGIN_EXTERN_C

// Helper to send private events to VidyoClient
VidyoBool GuiSendPrivateEvent( VidyoClientPrivateInEvent event, void *param, size_t paramSize);

// Helper to send private requests to VidyoClient
VidyoUint GuiSendPrivateRequest( VidyoClientPrivateRequest request, void *param1, size_t param1Size, size_t param2);

void GuiOnOutEvent(VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data);

LMI_END_EXTERN_C

#endif //__VidyoJniPrivateDefs_hpp__

