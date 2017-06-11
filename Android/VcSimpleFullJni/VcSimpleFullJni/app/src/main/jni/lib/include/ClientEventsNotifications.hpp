/*
 *  ClientEventsNorifications.hpp
 *  
 *
 *  Created by raz.galili on 3/21/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */
 
#ifndef __ClientEventsNorifications_hpp__
#define __ClientEventsNorifications_hpp__

typedef const char* TNotification;
 
#ifdef VIDYO_ANDROID
#define NOTIFICATION(X) ((TNotification)X)
#endif
//TODO: add defnitions for Mac, Windows

// Notification names for public out events from VidyoClient
#define kVidyoClientOutEventUserMessage NOTIFICATION("User Message")
#define kVidyoClientOutEventLogicStarted NOTIFICATION("Logic Started")
#define kVidyoClientOutEventSignIn NOTIFICATION("Sign In")
#define kVidyoClientOutEventSignOut NOTIFICATION("Sign Out")
#define kVidyoClientOutEventSubscribing NOTIFICATION("Subscribing")
#define kVidyoClientOutEventAppExit NOTIFICATION("App Exit")
#define kVidyoClientOutEventDeviceSelect NOTIFICATION("Device Select")
#define kVidyoClientOutEventDevicesChanged NOTIFICATION("Devices Changed")
#define kVidyoClientOutEventRinging NOTIFICATION("Ringing")
#define kVidyoClientOutEventRingProgress NOTIFICATION("Ring Progress")
#define kVidyoClientOutEventEndRinging NOTIFICATION("End Ringing")
#define kVidyoClientOutEventCalling NOTIFICATION("Calling")
#define kVidyoClientOutEventCallProgress NOTIFICATION("Call Progress")
#define kVidyoClientOutEventEndCalling NOTIFICATION("End Calling")
#define kVidyoClientOutEventJoining NOTIFICATION("Joining")
#define kVidyoClientOutEventJoinProgress NOTIFICATION("Join Progress")
#define kVidyoClientOutEventRetrying NOTIFICATION("Retrying")
#define kVidyoClientOutEventRetryProgress NOTIFICATION("Retry Progress")
#define kVidyoClientOutEventEndProcessing NOTIFICATION("End Processing")
#define kVidyoClientOutEventConferenceActive NOTIFICATION("Conference Active")
#define kVidyoClientOutEventConferenceEnded NOTIFICATION("Conference Ended")
#define kVidyoClientOutEventIncomingCall NOTIFICATION("Incoming Call")
#define kVidyoClientOutEventEndIncomingCall NOTIFICATION("End Incoming Call")
#define kVidyoClientOutEventPreview NOTIFICATION("Preview")
#define kVidyoClientOutEventAudioInDeviceMuted NOTIFICATION("Audio In Device Muted")
#define kVidyoClientOutEventAudioOutDeviceMuted NOTIFICATION("Audio Out Device Muted")
#define kVidyoClientOutEventVideoDeviceMuted NOTIFICATION("Video Device Muted")
#define kVidyoClientOutEventAudioInDeviceMutedByServer NOTIFICATION("Audio In Device Muted By Server")
#define kVidyoClientOutEventVideoDeviceMutedByServer NOTIFICATION("Video Device Muted By Server")
#define kVidyoClientOutEventAddShare NOTIFICATION("Add Share")
#define kVidyoClientOutEventRemoveShare NOTIFICATION("Remove Share")
#define kVidyoClientOutEventResize NOTIFICATION("Resize")
#define kVidyoClientOutEventParticipantsLimit NOTIFICATION("Participants Limit")
#define kVidyoClientOutEventEchoDetected NOTIFICATION("Echo Detected")
#define kVidyoClientOutEventKeyDown NOTIFICATION("Key Down")
#define kVidyoClientOutEventKeyUp NOTIFICATION("Key Up")
#define kVidyoClientOutEventMouseDown NOTIFICATION("Mouse Down")
#define kVidyoClientOutEventMouseUp NOTIFICATION("Mouse Up")
#define kVidyoClientOutEventMouseMove NOTIFICATION("Mouse Move")
#define kVidyoClientOutEventMouseScroll NOTIFICATION("Mouse Scroll")
#define kVidyoClientOutEventFeccListUpdated NOTIFICATION("Fecc List Updated")
#define kVidyoClientOutEventControlCamera NOTIFICATION("Control Camera")
#define kVidyoClientOutEventSetParticipantVideoModeDone NOTIFICATION("Set Participant Video Mode Done")
#define kVidyoClientOutEventConferenceInfoUpdate NOTIFICATION("Conference Info Update")
#define kVidyoClientOutEventMediaControl NOTIFICATION("Media Control")


// Names for notifications from LoginLogic object
#define kClientStateManagerStartStateChange NOTIFICATION("Start State Change")
#define kClientStateManagerLoginStateChange NOTIFICATION("Login State Change")
#define kClientStateManagerConnectStateChange NOTIFICATION("Connect State Change")
#define kVidyoClientOutEventLogin NOTIFICATION("Login")
#define kVidyoClientOutEventLicense NOTIFICATION("License")
#define kVidyoClientOutEventLinked NOTIFICATION("Linked")
#define kVidyoClientOutEventSignedIn NOTIFICATION("SignedIn")
#define kVidyoClientOutEventSignedOut NOTIFICATION("SignedOut")
#define kVidyoClientOutEventWebProxyAuthenticationFailed NOTIFICATION("WebProxy Authentication Failed")

#define kClientStateManagerLogutRequested NOTIFICATION("Logout Requested")

#define kClientStateManagerConferenceStateChange NOTIFICATION("Conference State Change")

#define kVidyoClientPrivateOutEventPortalDataCache NOTIFICATION("Portal Data Cache")

#define kVidyoClientContactManagerMyEntityInfoUpdated NOTIFICATION("MyEntityInfoUpdated") //VidyoClientPrivateRequestEntityInfo* is passed as a parameter 
#define KVidyoClientPrivateSoapGetParticipantsResponse NOTIFICATION("ParticipantsResponse")  //VidyoClientPrivateSoapOutEventGetParticipants* is passed as a parameter
#define KVidyoClientPrivateSoapSearchByEntityIDResponse NOTIFICATION("SearchByEntityIDResponse")  //VidyoClientPrivateSoapOutEventSearch* is passed as a parameter
#define kVidyoClientContactManagerEntityInfoUpdated NOTIFICATION("EntityInfoUpdated") //VidyoClientPrivateRequestEntityInfo* is passed as a parameter 
#define kVidyoClientLogoutWithMessage NOTIFICATION("logoutwithmessage") //ACHAR* is passed as a parameter 

#define kClientOutEventWebProxyUpdateRequested NOTIFICATION("Web Proxy Update Event")

#define KVidyoClientPrivateSoapGetPortalFeatureResponse NOTIFICATION("GetPortalFeatureResponse")  //KVidyoClientPrivateSoapGetPortalFeatureResponse* is passed as a parameter
#define KVidyoClientPrivateSoapGetControlMeetingURLResponse NOTIFICATION("GetControlMeetingURLResponse")  //KVidyoClientPrivateSoapGetControlMeetingURLResponse* is passed as a parameter
#define KVidyoClientOutEventPortalPrefix NOTIFICATION("OutEventPortalPrefix")  //VidyoClientOutEventPortalPrefix* is passed as a parameter

#define KVidyoClientPrivateSoapCreateSchedRoomResponse NOTIFICATION("CreateSchedRoomResponse")  //VidyoClientPrivateSoapOutEventCreateScheduledRoom* is passed as a parameter
#define KVidyoClientPrivateSoapGetInviteContentResponse NOTIFICATION("GetInviteContentResponse")  //VidyoClientPrivateSoapOutEventGetInviteContent* is passed as a parameter

#define KVidyoClientPrivateSoapAddContactResponse NOTIFICATION("AddContactResponse")
#define KVidyoClientPrivateSoapRemoveContactResponse NOTIFICATION("RemoveContactResponse")

#define KVidyoClientPrivateSoapGetLoginTypeResponse NOTIFICATION("GetLoginTypeResponse")  //KVidyoClientPrivateSoapGetLoginTypeResponse* is passed as a parameter

#endif // __ClientEventsNorifications_hpp__

