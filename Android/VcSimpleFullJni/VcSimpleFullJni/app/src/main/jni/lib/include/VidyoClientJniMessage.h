/*
 *  VidyoClientJniMessage.h
 *  Android
 *
 *  Func
 *  Created by Paul.Cushman
 *  Copyright 2014 Vidyo. All rights reserved.
 */


#ifndef __VidyoClientJniMessage_h__
#define __VidyoClientJniMessage_h__

LMI_BEGIN_EXTERN_C

VidyoBool LmiVidyoJniMessageInitialize(JNIEnv *env);
void LmiVidyoJniMessageUnInitialize(JNIEnv *env);

// Message callbacks
void VidyoClientJniMessage_MessageOutMsg(AppGuiMessageType displayMessageType, char *displayMessage);
void VidyoClientJniMessage_MessageOutMsgId(AppGuiMessageType displayMessageType, int id);

LMI_END_EXTERN_C

#endif //__VidyoClientJniMessage_h__
