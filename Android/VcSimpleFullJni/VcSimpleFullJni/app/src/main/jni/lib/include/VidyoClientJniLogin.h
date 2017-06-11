/*
 *  VidyoClientJniLogin.h
 *  Android
 *
 *  Func
 *  Created by Paul.Cushman
 *  Copyright 2014 Vidyo. All rights reserved.
 */


#ifndef __VidyoClientJniLogin_h__
#define __VidyoClientJniLogin_h__

LMI_BEGIN_EXTERN_C

VidyoBool LmiVidyoJniLoginInitialize(JNIEnv *env);
void LmiVidyoJniLoginUnInitialize(JNIEnv *env);
void VidyoJNILoginStateEventHandler(const char *eventName, const void* param);
void VidyoJNILogoutWithMessageEventHandler(const char *eventName, const void* param);

LMI_END_EXTERN_C

#endif //__VidyoClientJniLogin_h__
