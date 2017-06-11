/*
 *  VidyoClientJniChat.h
 *  Android
 *
 *  Func
 *  Created by Paul.Cushman
 *  Copyright 2014 Vidyo. All rights reserved.
 */


#ifndef __VidyoClientJniChat_h__
#define __VidyoClientJniChat_h__

LMI_BEGIN_EXTERN_C

VidyoBool LmiVidyoJniChatInitialize(JNIEnv *env);
void LmiVidyoJniChatUnInitialize(JNIEnv *env);

// Chat callbacks
void VidyoClientJniChat_ChatMsgRcv(const VidyoBool groupChat, const char* uri, const char* name, const char* message);

LMI_END_EXTERN_C

#endif //__VidyoClientJniConference_h__
