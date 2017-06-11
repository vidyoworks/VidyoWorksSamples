/*
 *  VidyoClientSample.h
 *
 *  Created by Chetan Gandhi on 08/19/11.
 *  Copyright 2011 Vidyo Inc. All rights reserved.
 *
 */

#ifndef VIDYOCLIENTSAMPLE_H
#define VIDYOCLIENTSAMPLE_H

#include "VidyoClient.h"

BOOL inCall;

// Receive out event from VidyoClient
void vidyoClientSampleOnVidyoClientEvent(VidyoClientOutEvent actionType,
										 VidyoVoidPtr param, 
										 VidyoUint paramSize,
										 VidyoVoidPtr data);

#endif // VIDYOCLIENTSAMPLE_H
