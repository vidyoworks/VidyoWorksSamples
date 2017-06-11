/*
 *  VidyoClientJni.h
 *  Android
 *
 *  Func
 *  Created by Paul.Cushman
 *  Copyright 2014 Vidyo. All rights reserved.
 */


#ifndef __VidyoClientJni_h__
#define __VidyoClientJni_h__

LMI_BEGIN_EXTERN_C

typedef VidyoBool (WINAPI *AndroidVidyoClientOutEventCallback)(VidyoClientOutEvent event,
                                                                                                                           VidyoVoidPtr param,
                                                                                                                           VidyoUint paramSize,
                                                                                                                           VidyoVoidPtr data);

LMI_END_EXTERN_C

#endif //__VidyoClientJni_h__
