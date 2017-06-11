/*
 *   appDelegate.hpp
 *  
 *
 *  Created by raz.galili on 3/22/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */
#ifndef __appDelegate_hpp__
#define __appDelegate_hpp__

#include "VidyoClient.h"
#include "VidyoJniCommon.h"
#include "VidyoClientPrivate.h"
#include "ClientEventsNotifications.hpp"



typedef enum  AppDelegateHandlerResults_
{
	MASSAGE_NOT_HANDLED_BY_APPDELEGATE = 0,
	MASSAGE_HANDLED_BY_APPDELEGATE = 2,
}AppDelegateHandlerResults;


LMI_BEGIN_EXTERN_C

//handle mssage on orientation change
DECLSPEC void doClientSetOrientation(VidyoClientOrientation newOrientation);

//handle setting of language
DECLSPEC void doSetLanguage(const char*);

//handle massage to render client
DECLSPEC void doRender(void);

DECLSPEC void doSceneReset(void);

DECLSPEC void doResize(VidyoUint width, VidyoUint height);

DECLSPEC void doCallOnHold(VidyoBool onHold);

DECLSPEC void doTouchEvent(VidyoInt id, VidyoInt type,VidyoInt x,VidyoInt y);

DECLSPEC void doStartConferenceMedia();

DECLSPEC void doSetHasCamera(VidyoBool hasFrontCamera, VidyoBool hasBackCamera);

void doMuteMicrophone(VidyoBool microphoneMuted);
VidyoBool doGetMicrophoneMutedByServer();
VidyoBool doGetMicrophoneLocalMuted();
void doSetAutoStartMicrophone(VidyoBool value);
VidyoBool doGetAutoStartMicrophone();

void doMuteCamera(VidyoBool cameraMuted);
void doSetAutoStartCamera(VidyoBool value);
VidyoBool doGetAutoStartCamera();
VidyoBool doGetCameraMuted();

void doMuteSpeaker(VidyoBool speakerMuted);
void doSetAutoStartSpeaker(VidyoBool value);
VidyoBool doGetAutoStartSpeaker();

void doSetEchoCancellation(VidyoBool value);
VidyoBool doGetEchoCancellation();

void doSetAutomaticGainControl(VidyoBool value);
VidyoBool doGetAutomaticGainControl();

void doSetGuestTag(const char *tag);

void doSetEulaAgreed(VidyoBool value);
VidyoBool doGetEulaAgreed();

void doEnableMenuBar(VidyoBool menuBarEnabled);

void setForceVidyoProxy(VidyoBool forceVidyoProxy);

void doSetPreviewModeOFF();
void doSetPreviewModeON(VidyoBool pip);

void doRearrangeSceneLayout();

void doSetBackground(VidyoBool willBackground);

void doDisableAllVideo();
void doEnableAllVideo();

const char* AppGuiGetString(VidyoUint displayStringIndex);

void doSetLogLevelsAndCategories(const char* newLogging);

VidyoBool AndroidVidyoClientStart(VidyoClientOutEventCallback eventCb,const char* certificateFileName, const char *androidConfigDirName,
    const char *androidLogDirName, const char* machineID, const char *installedDirName, const char *androidAppVersion);

const char* AndroidClientGetMachineID();
DECLSPEC void AndroidClientSetMachineID(const char* id);

void doPlayWav(VidyoVoidPtr wav, int buffSize);

void setFeccEndpoint(VidyoBool enable);
void setFeccController(VidyoBool enable);

void setVideoPreference(VidyoClientVideoPreferences newVideoPreference);

DECLSPEC void doSwitchVisibleStats();
DECLSPEC void doSetStatsVisibility(VidyoBool visibility);
DECLSPEC void doSetLabelsVisibility(VidyoBool visibility);
DECLSPEC void doSetPixelDensity(double density);
void doToggleVideoDock();
VidyoInt doGetVideoDockCount();
VidyoBool doGetVideoDockVisibility();
void doToggleApplicationDock();
VidyoInt doGetApplicationDockCount();
VidyoBool doGetApplicationDockVisibility();

AppDelegateHandlerResults appDelegateMessageHandler( VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data);

VidyoBool isConnectedSecurly();

//todo: add AppDelegateConstruct
void AppDelegateDestruct();
void AppDelegateConstruct();

LMI_END_EXTERN_C


#endif //__appDelegate_hpp__
