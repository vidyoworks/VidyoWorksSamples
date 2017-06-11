/*
 *  VidyoClientJniConference.h
 *  Android
 *
 *  Func
 *  Created by Paul.Cushman
 *  Copyright 2014 Vidyo. All rights reserved.
 */


#ifndef __VidyoClientJniConference_h__
#define __VidyoClientJniConference_h__

LMI_BEGIN_EXTERN_C

VidyoBool LmiVidyoJniConferenceInitialize(JNIEnv *env);
void LmiVidyoJniConferenceUnInitialize(JNIEnv *env);

// Conference Status callbacks
void VidyoClientJniConference_JoinProgress();
void VidyoClientJniConference_JoinComplete();
void VidyoClientJniConference_JoiningFailed(int ErrType);
void VidyoClientJniConference_ErrorJoiningGuestRoom(int ErrType);
void VidyoClientJniConference_AnswerCall(const char* callerName);
void VidyoClientJniConference_EndCalling();
void VidyoClientJniConference_CancelIncomingCall();

// Conference Event Callbacks
void VidyoClientJniConference_RecordingStatusEvent(VidyoBool enabled);
void VidyoClientJniConference_WebcastingStatusEvent(VidyoBool enabled);
void VidyoClientJniConference_ServerVideoMuteChangedEvent(VidyoBool muted);
void VidyoClientJniConference_CameraEnabledEvent(VidyoBool enabled);
void VidyoClientJniConference_MicEnabledEvent(VidyoBool enabled);
void VidyoClientJniConference_SpeakerEnabledEvent(VidyoBool enabled);
void VidyoClientJniConference_GUIChangedEvent();
void VidyoClientJniConference_FECCButtonClickedEvent(VidyoBool on);
void VidyoClientJniConference_PreferredButtonClickedEvent(VidyoBool on);
void VidyoClientJniConference_HideButtonClickedEvent(VidyoBool on);

// Conference Share Event callbacks
void VidyoClientJniConference_ShareEventCallback(const VidyoBool addShare, const char *shareURI);

// Conference FECC Command callbacks
void VidyoClientJniConference_FECCCommand(const char *commandId, const int cameraCommand);

// Conference Switch Camera callbacks
void VidyoClientJniConference_SwitchCamera(const char *cameraName);

// Conference Participants Changed callback
void VidyoClientJniConference_ParticipantsChanged(int numOfParticipants);

// Lecture Mode Callbacks
void VidyoClientJniConference_LectureModeState(const int lectureModeState);
void VidyoClientJniConference_LectureHandCleared();
void VidyoClientJniConference_LecturePresenterChanged(const char *presenterURI);

extern VidyoInt JNI_CONFERENCE_FAIL_NONE;
extern VidyoInt JNI_CONFERENCE_FAIL_INVALID_ARGUMENT;
extern VidyoInt JNI_CONFERENCE_FAIL_NOT_LICENSED;
extern VidyoInt JNI_CONFERENCE_FAIL_GENERAL;
extern VidyoInt JNI_CONFERENCE_FAIL_CONFERENCE_LOCKED;
extern VidyoInt JNI_CONFERENCE_FAIL_LICENSE_EXPIRED;
extern VidyoInt JNI_CONFERENCE_FAIL_WRONG_PIN;
extern VidyoInt JNI_CONFERENCE_FAIL_USER_NOT_FOUND;
extern VidyoInt JNI_CONFERENCE_FAIL_END_POINT_NOT_FOUND;
extern VidyoInt JNI_CONFERENCE_FAIL_MEMBER_NOT_ONLINE;
extern VidyoInt JNI_CONFERENCE_FAIL_FAILED_PLACE_DIRECT_CALL;
extern VidyoInt JNI_CONFERENCE_FAIL_SEAT_LICENSE_EXPIRED;
extern VidyoInt JNI_CONFERENCE_FAIL_ROOM_DISABLED;
extern VidyoInt JNI_CONFERENCE_FAIL_NOT_OWNER_OF_ROOM;
extern VidyoInt JNI_CONFERENCE_FAIL_UNEXPECTED_SUBELEMENT_IN_MESSAGE;
extern VidyoInt JNI_CONFERENCE_FAIL_IPC_JOIN_FAILURE;
extern VidyoInt JNI_CONFERENCE_FAIL_ALL_LINES_IN_USE;

LMI_END_EXTERN_C

#endif //__VidyoClientJniConference_h__
