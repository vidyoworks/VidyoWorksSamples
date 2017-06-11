#include <jni.h>
#include "VidyoClient.h"
#include "VidyoClientPrivate.h"
#include "ClientEventsNotifications.hpp"
#include "ClientEventDispatch.hpp"
#include "ContactManager.hpp"
#include "LoginLogic.hpp"
#include "AndroidDebug.h"
#include "AppDeviceJni.h"
#include "TimerDispatch.hpp"
#include "VidyoJni.h"
#include "VidyoClientJni.h"
#include "VidyoMobileJni.h"
#include "VidyoJniCommon.h"

#define MAX_ARRAY_SIZE 30 //maximum size of array passed to java

char NULLSTRING[257] = {0};
AppDeviceSetup appDeviceSetup;

jobject client_applicationJniObj = 0;
jobject portalEntityObj = 0;
jobject attendeeEntityObj = 0;
jobject webProxyEntityObj = 0;
jobject configInfoObj = 0;
jobject videoCapsObj = 0;

const char *Client_ApplicationJniClassPath = "com/vidyo/VidyoClientLib/ApplicationJni";
const char *PortalEntityClassPath = "com/vidyo/VidyoClientLib/entities/PortalEntity";
const char *AttendeeEntityClassPath = "com/vidyo/VidyoClientLib/entities/AttendeeEntity";
const char *WebProxyEntityClassPath = "com/vidyo/VidyoClientLib/webproxy/WebProxyEntity";
const char *ConfigInfoClassPath = "com/vidyo/VidyoClientLib/entities/ConfigInfo";
const char *VideoCapabilitiesClassPath = "com/vidyo/VidyoClientLib/entities/VideoCapabilities";

static VidyoBool convertVidyoClientPrivateSoapAccountData2ContactObject(JNIEnv *env, jobject *contact, const VidyoClientPrivateSoapAccountData* accountData);
static VidyoBool convertVidyoClientPrivateSoapParticipantData2ContactObject(JNIEnv *env, jobject *contact, const VidyoClientPrivateSoapConferenceParticipantData* participantData);

static VidyoBool VidyoMobileGuiOnOutEvent(VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data);
static void registerForMobileEvents();

#define LOCK 	LmiAndroidJniLock();
#define UNLOCK	LmiAndroidJniUnlock();

// these are parsed in VidyoConferenceActivity and should be identical to the constants there
//TODO: Get the value from the Java values
const int EVENT_SHARE_ADDED = 0;
const int EVENT_SHARE_REMOVED = 1;
void eventGotFrameReceived(VidyoClientInEventVideoFrame *frame, const char *participantURI);
void eventGotAddOrRemoveShare(const int eventType, const char *shareURI);

static VidyoBool initialized = VIDYO_FALSE;

JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_LmiVidyoMobileJniInitialize(JNIEnv *env, jobject jobj)
{
	if (!initialized)
	{
		client_applicationJniObj = initCacheClassReference(env, Client_ApplicationJniClassPath);
		portalEntityObj = initCacheClassReference(env, PortalEntityClassPath);
		attendeeEntityObj = initCacheClassReference(env, AttendeeEntityClassPath);
		webProxyEntityObj = initCacheClassReference(env, WebProxyEntityClassPath);
		configInfoObj = initCacheClassReference(env, ConfigInfoClassPath);
		videoCapsObj = initCacheClassReference(env, VideoCapabilitiesClassPath);
		
		LOGE("ApplicationJni_Construct set default Device Info. calling VidyoClientStart() \n");
		AppDeviceSetEncoderConfiguration(&appDeviceSetup, VIDYO_FALSE, 0, 0);
		//LOGI("Width=%d, Height=%d, Cores=%d", appDeviceSetup.captureWidth, appDeviceSetup.captureHeight, LmiProcessorGetNumLogicalCores());

		registerForMobileEvents();
			 
		LmiAndroidJniRegisterEventHdlr((VidyoClientOutEventCallback)VidyoMobileGuiOnOutEvent);

		initialized = VIDYO_TRUE;
	}
	return (jboolean)initialized;
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_LmiVidyoMobileJniUninitialize(JNIEnv *env, jobject jobj)
{
	if (initialized)
	{
		LmiAndroidJniUnregisterEventHdlr();
		
		if (client_applicationJniObj != NULL) (*env)->DeleteGlobalRef(env, client_applicationJniObj);
		if (portalEntityObj != NULL) (*env)->DeleteGlobalRef(env, portalEntityObj);
		if (attendeeEntityObj != NULL) (*env)->DeleteGlobalRef(env, attendeeEntityObj);
		if (webProxyEntityObj != NULL) (*env)->DeleteGlobalRef(env, webProxyEntityObj);
		if (configInfoObj != NULL) (*env)->DeleteGlobalRef(env, configInfoObj);
		if (videoCapsObj != NULL) (*env)->DeleteGlobalRef(env, videoCapsObj);
		
		client_applicationJniObj = 0;
		portalEntityObj = 0;
		attendeeEntityObj = 0;
		webProxyEntityObj = 0;
		configInfoObj = 0;
		videoCapsObj = 0;
	}
	initialized = VIDYO_FALSE;
}

// Callback for out-events from VidyoClient
//extern "C"
static VidyoBool VidyoMobileGuiOnOutEvent(VidyoClientOutEvent event,
										   VidyoVoidPtr param,
										   VidyoUint paramSize,
										   VidyoVoidPtr data)
{
	VidyoBool retVal = VIDYO_FALSE;
	
	LOGI("VidyoMobileGuiOnOutEvent enter Event = %d\n",(int) event);
	LOCK
	
	if (MASSAGE_HANDLED_BY_CONTACT_MANAGER == contactManagerMessageHandler(event, param,  paramSize, data)) //try contact manager handler
	{
		retVal = VIDYO_TRUE;
	} else {
		if ((VidyoClientPrivateOutEvent)event==VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED)
		{
			retVal = VIDYO_TRUE;

			VidyoClientOutEventVideoFrameReceived* frame = (VidyoClientOutEventVideoFrameReceived*) param;

			eventGotFrameReceived(&frame->frame, (char *) frame->participantURI);
		}
/*		else if ((VidyoClientPrivateOutEvent)event==VIDYO_CLIENT_OUT_EVENT_ADD_SHARE)
		{
			retVal = VIDYO_TRUE;
		     VidyoClientRequestWindowShares shareRequest;

		     // LOGI("received: VIDYO_CLIENT_OUT_EVENT_ADD_SHARE\n");
		     VidyoClientOutEventAddShare *share = (VidyoClientOutEventAddShare*)param;
		     eventGotAddOrRemoveShare( EVENT_SHARE_ADDED,  (char *) share->URI);
		}
		else if ((VidyoClientPrivateOutEvent)event==VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE)
		{
			retVal = VIDYO_TRUE;
		     // LOGI("received: VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE\n");
		     VidyoClientOutEventAddShare *share = (VidyoClientOutEventAddShare*)param;
		     eventGotAddOrRemoveShare( EVENT_SHARE_REMOVED,  (char *) share->URI);
		}
*/
	}
	
	LOGI("VidyoMobileGuiOnOutEvent() exit\n");
	UNLOCK
	return(retVal);
}


// VIDYO_CLIENT_PRIVATE_OUT_EVENT_WEBPROXY_UPDATE_NEEDED
void WebProxyUpdateEventCallbackToJava_(const char *url)
{
	VidyoBool isAttached;
	JNIEnv *env;
	jmethodID mid;
	jstring js = NULL;
	
	LOCK
	LOGE("WebProxyUpdateEventCallbackToJava_ Begin");
	env = getJniEnv(&isAttached);
	if (env == NULL)
		goto FAIL0;
	
	mid = getApplicationJniMethodId(env, client_applicationJniObj, "updateWebProxyEvent", "(Ljava/lang/String;)V");
	if (mid == NULL)
		goto FAIL1;
	
	if(url)
		js = (*env)->NewStringUTF(env, url);
	(*env)->CallVoidMethod(env, client_applicationJniObj, mid, js);
	
	releaseJniEnv(env, isAttached);
	UNLOCK
	LOGE("WebProxyUpdateEventCallbackToJava_ End");
	return;
FAIL1:
	releaseJniEnv(env, isAttached);
FAIL0:
	UNLOCK
	LOGE("WebProxyUpdateEventCallbackToJava_ FAILED");
	return;
}


void WebProxyAuthenticationFailedEventCallbackToJava_()
{
	VidyoBool isAttached;
	JNIEnv *env;
	jmethodID mid;
	jstring js = NULL;
	
	LOCK
	LOGE("WebProxyAuthenticationFailedEventCallbackToJava_ Begin");
	env = getJniEnv(&isAttached);
	if (env == NULL)
		goto FAIL0;
	
	mid = getApplicationJniMethodId(env, client_applicationJniObj, "failedWebProxyAuthenticationEvent", "()V");
	if (mid == NULL)
		goto FAIL1;
	
	(*env)->CallVoidMethod(env, client_applicationJniObj, mid);
	
	releaseJniEnv(env, isAttached);
	UNLOCK
	LOGE("WebProxyAuthenticationFailedEventCallbackToJava_ End");
	return;
FAIL1:
	releaseJniEnv(env, isAttached);
FAIL0:
	UNLOCK
	LOGE("WebProxyAuthenticationFailedEventCallbackToJava_ FAILED");
	return;
}

// Called when we receive VIDYO_CLIENT_PRIVATE_OUT_EVENT_WEBPROXY_UPDATE_NEEDED event
static void VidyoJNIWebProxyUpdateEventHandler(const char *eventName, const void* param)
{
	VidyoClientPrivateOutEventWebProxyUpdateNeeded *event = (VidyoClientPrivateOutEventWebProxyUpdateNeeded *)param;
	LOGI("VidyoJNIWebProxyUpdateEventHandler called with message URL %s", event->webProxyURL);
	WebProxyUpdateEventCallbackToJava_(event->webProxyURL);
}

// VIDYO_CLIENT_OUT_EVENT_LOGIN with error
// VIDYO_CLIENT_PRIVATE_ERROR_HTTP_407_PROXY_AUTHENTICATION_REQUIRED
static void VidyoJNIWebProxyAuthenticationFailedEventHandler(const char *eventName, const void* param)
{
	VidyoClientOutEventLogIn *event = (VidyoClientOutEventLogIn *)param;
	LOGI("VidyoJNIWebProxyAuthenticationFailedEventHandler called with portalURI %s", event->portalUri);
	WebProxyAuthenticationFailedEventCallbackToJava_();
}

//todo: create macro structures to define java objects
static VidyoBool createPortalEntity(JNIEnv *env, jobject *peObject,
								  const char* id, const char* ext,
								  const char* displayName, const char* email,
								  const char* tenant, const char* typeStr,
								  const char* owner)
{
	jclass peClass;
	jmethodID realConstructor;
	jmethodID mId;
	
	//	FUNCTION_ENTRY
	*peObject = NULL;
	peClass = (*env)->GetObjectClass(env, portalEntityObj);
	if (peClass == NULL) {
		LOGE("createPortalEntity: PortalEntity not found");
		(*env)->ExceptionDescribe(env);
		goto END;
	}
	
	if ((realConstructor = (*env)->GetMethodID(env, peClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) == NULL) {
		LOGE("createPortalEntity: NULL real constructor for PortalEntity");
		(*env)->ExceptionDescribe(env);
		goto END;
	}
	
	*peObject = (jobject)(*env)->NewObject(env, peClass, realConstructor,
										   (*env)->NewStringUTF(env, id), (*env)->NewStringUTF(env, typeStr),
										   (*env)->NewStringUTF(env, ext), (*env)->NewStringUTF(env, displayName),
										   (*env)->NewStringUTF(env, tenant), (*env)->NewStringUTF(env, email),
										   (*env)->NewStringUTF(env, owner));
	
	if (*peObject == NULL) {
		LOGE("createPortalEntity: NULL PE object");
		(*env)->ExceptionDescribe(env);
		goto END;
	}
	
	
END:
	if (ExceptionDidOccure(env,__FUNCTION__)) {
		
		*peObject = NULL;
		FUNCTION_EXIT
		return VIDYO_FALSE;
	}
	
	//	FUNCTION_EXIT
	return VIDYO_TRUE;
}

//todo: create macro structures to define java objects
static VidyoBool createPortalEntityFromEntityInfo(JNIEnv *env, jobject *peObject, VidyoClientPrivateRequestEntityInfo* entityInfo)
{
	jclass peClass;
	const char* id = &(entityInfo->entityID[0]);
	const char* ext = &NULLSTRING[0];
	const char* displayName = &(entityInfo->displayName[0]);
	const char* email = &NULLSTRING[0];
	const char* tenant = &NULLSTRING[0];
	const char* typeStr = &NULLSTRING[0];
	const char* owner = &NULLSTRING[0];
	VidyoBool retValue;
	
	FUNCTION_ENTRY
	retValue =  createPortalEntity( env, peObject, id, ext, displayName, email, tenant, typeStr, owner);
	FUNCTION_EXIT
	return retValue;
}


//TODO: docuemnt
static VidyoBool callUpdateMyEntity_(JNIEnv *env, jobject *portalEntityObj)
{
	
	jmethodID mid;
	
	FUNCTION_ENTRY
	
	mid = getApplicationJniMethodId(env, client_applicationJniObj, "updateMyEntity", "(Lcom/vidyo/VidyoClientLib/entities/PortalEntity;)V");
	if (mid != NULL)
	{
		
		(*env)->CallVoidMethod(env, client_applicationJniObj, mid, *portalEntityObj);
		FUNCTION_EXIT
		return VIDYO_TRUE;
	}
	
	
	FUNCTION_EXIT
	return VIDYO_FALSE;
}

//TODO: docuemnt
static VidyoBool callUpdateEntity_(JNIEnv *env, jobject *portalEntityObj)
{
	
	jmethodID mid;
	
	FUNCTION_ENTRY
	
	mid = getApplicationJniMethodId(env, client_applicationJniObj, "updateEntity", "(Lcom/vidyo/VidyoClientLib/entities/PortalEntity;)V");
	if (mid != NULL)
	{
		(*env)->CallVoidMethod(env, client_applicationJniObj, mid, *portalEntityObj);
		FUNCTION_EXIT
		return VIDYO_TRUE;
	}
	
	FUNCTION_EXIT
	return VIDYO_FALSE;
}


//TODO: document
static void VidyoJNIMyEntityInfoUpdated(const char *eventName, const void* param)
{
	VidyoBool isAttached;
	jobject portalEntity;
	JNIEnv *env;
	
	FUNCTION_ENTRY
	if (env = getJniEnv(&isAttached))
	{
		//convert param to right type
		VidyoClientPrivateRequestEntityInfo* entityInfo= (VidyoClientPrivateRequestEntityInfo*)param;
		//create and feel PortalEntity
		if (createPortalEntityFromEntityInfo(env, &portalEntity, entityInfo))
		{
			//call java public void updateMyEntity(PortalEntity entity)
			callUpdateMyEntity_(env, &portalEntity);
		}
		
		releaseJniEnv(env, isAttached);
		
	}
	FUNCTION_EXIT
}


static void VidyoJNISetSchedRoomCapable(VidyoBool capable)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    int arg1;
	
    LOCK
    env = getJniEnv(&isAttached);
    if (env != NULL)
    {
        mid = getApplicationJniMethodId(env, client_applicationJniObj, "setSchedRoomCapableCallback", "(I)V");
        if (mid != NULL)
        {
        	arg1 = capable;
            (*env)->CallVoidMethod(env, client_applicationJniObj, mid, arg1);
        }
        releaseJniEnv(env, isAttached);
    }
    UNLOCK
}

static void VidyoJNISetControlMeetingCapable(VidyoBool capable)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    int arg1;
	
    LOCK
    env = getJniEnv(&isAttached);
    if (env != NULL)
    {
        mid = getApplicationJniMethodId(env, client_applicationJniObj, "setControlMeetingCapableCallback", "(I)V");
        if (mid != NULL)
        {
        	arg1 = capable;
            (*env)->CallVoidMethod(env, client_applicationJniObj, mid, arg1);
        }
        releaseJniEnv(env, isAttached);
    }
    UNLOCK
}


// TODO: Add callback code for Get Portal Feature Response handling
// response VIDYO_CLIENT_PRIVATE_SOAP_GET_PORTALFEATURES
static void VidyoJNIGetPortalFeatureResponse(const char *eventName, const void* param)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    int error;
    int i;
    VidyoBool schedRoomSeen = VIDYO_FALSE;
    VidyoBool controlMeetingSeen = VIDYO_FALSE;
    
    FUNCTION_ENTRY
    VidyoClientPrivateSoapOutEventGetPortalFeatures *response =  (VidyoClientPrivateSoapOutEventGetPortalFeatures *)param;
    if (!response)
    {
        LOGE("VidyoJNIGetPortalFeatureResponse paramter is NULL");
    }
    else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_GET_PORTALFEATURES)
    {
        LOGE("VidyoJNIGetPortalFeatureResponse response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_GET_PORTALFEATURES");
    }
    else if (response->error != 0)
    {
        LOGE("VidyoJNIGetPortalFeatureResponse response->error != 0");
        VidyoJNISetSchedRoomCapable(VIDYO_FALSE);
        VidyoJNISetControlMeetingCapable(VIDYO_FALSE);
    }
    else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
    {
        LOGE("VidyoJNIGetPortalFeatureResponse response->response != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS");
        VidyoJNISetSchedRoomCapable(VIDYO_FALSE);
        VidyoJNISetControlMeetingCapable(VIDYO_FALSE);
    }
    else
    {
        for (i=0; i<response->featureCount; i++)
        {
        	if (response->features[i].featureName == VIDYO_CLIENT_PRIVATE_SOAP_PORTAL_FEATURE_NAME_SCHEDULED_ROOM)
            {
                LOGE("VidyoJNIGetPortalFeatureResponse SchedRooom is %s", response->features[i].isEnabled ? "Enabled" : "Disabled");
                VidyoJNISetSchedRoomCapable(response->features[i].isEnabled);
				schedRoomSeen = VIDYO_TRUE;
            }
            else if (response->features[i].featureName == VIDYO_CLIENT_PRIVATE_SOAP_PORTAL_FEATURE_NAME_MEDERATOR_URL)
            {
                LOGE("VidyoJNIGetPortalFeatureResponse ControlMeeting is %s", response->features[i].isEnabled ? "Enabled" : "Disabled");
                VidyoJNISetControlMeetingCapable(response->features[i].isEnabled);
				controlMeetingSeen = VIDYO_TRUE;
            }
			
        }
        if (!schedRoomSeen)
        {
            LOGE("VidyoJNIGetPortalFeatureResponse forcing SchedRooom to Disabled");
            VidyoJNISetSchedRoomCapable(VIDYO_FALSE);
        }
        if (!controlMeetingSeen)
        {
            LOGE("VidyoJNIGetPortalFeatureResponse forcing ControlMeeting to Disabled");
            VidyoJNISetControlMeetingCapable(VIDYO_FALSE);
        }
		
    }
	
	FUNCTION_EXIT
}

static void VidyoJNISetControlMeetingURL(const char *url, const VidyoBool hasPIN)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
	jstring jsURL;
	
    LOCK
    env = getJniEnv(&isAttached);
    if (env != NULL)
    {
        mid = getApplicationJniMethodId(env, client_applicationJniObj, "getControlMeetingURLCallback", "(Ljava/lang/String;)V");
        if (mid != NULL)
        {
			jsURL = (*env)->NewStringUTF(env, url);
			
            (*env)->CallVoidMethod(env, client_applicationJniObj, mid, jsURL);
        }
        releaseJniEnv(env, isAttached);
    }
    UNLOCK
}

// Called in response to VIDYO_CLIENT_PRIVATE_SOAP_GET_MODERATOR_URL
static void VidyoJNIGetControlMeetingURLResponse(const char *eventName, const void* param)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    int error;
    int i;
    
    FUNCTION_ENTRY
    VidyoClientPrivateSoapOutEventGetModeratorURL *response =  (VidyoClientPrivateSoapOutEventGetModeratorURL *)param;
    if (!response)
    {
        LOGE("VidyoJNIGetControlMeetingURLResponse parameter is NULL");
    }
    else if (response->result != VIDYO_CLIENT_ERROR_NONE && response->result != VIDYO_CLIENT_ERROR_SOAP_SUCCESS)
    {
        LOGE("VidyoJNIGetControlMeetingURLResponse response->result(%d) != VIDYO_CLIENT_ERROR_NONE", response->result);
    }
    else
    {
		VidyoJNISetControlMeetingURL(response->moderatorURL, response->hasPin);
    }
	
	FUNCTION_EXIT
}

// Called in response to VIDYO_CLIENT_PRIVATE_SOAP_CREATE_SCHEDULED_ROOM
static void VidyoJNISchedRoomRsp(const char *eventName, const void* param)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    jstring jsRoomExtn;
    jstring jsRoomPin;
    jstring jsInvite;
    jstring jsRoomURL;
	jstring jsSubject;
    int error;
    
    FUNCTION_ENTRY
    VidyoClientPrivateSoapOutEventCreateScheduledRoom *response =  (VidyoClientPrivateSoapOutEventCreateScheduledRoom*)param;
    if (!response)
    {
        LOGE("VidyoJNISchedRoomRsp paramter is NULL");
    }
    else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_CREATE_SCHEDULED_ROOM )
    {
        LOGE("VidyoJNISchedRoomRsp response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_CREATE_SCHEDULED_ROOM");
    }
    else if (response->error != 0)
    {
        LOGE("VidyoJNISchedRoomRsp response->error == %d", response->error );
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "createScheduledRoomFailedCallback", "(I)V");
            if (mid != NULL)
            {
                error = response->error;
                (*env)->CallVoidMethod(env, client_applicationJniObj, mid, (jint)error);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
    }
    else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
    {
        LOGE("VidyoJNISchedRoomRsp response->result != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS (%d)",response->result);
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "createScheduledRoomFailedCallback", "(I)V");
            if (mid != NULL)
            {
                error = response->result;
                (*env)->CallVoidMethod(env, client_applicationJniObj, mid, (jint)error);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
		
    }
    else
    {
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "createScheduledRoomCallback",
					"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
            if (mid != NULL)
            {
                jsRoomExtn = (*env)->NewStringUTF(env, response->roomExtn);
                jsRoomPin = (*env)->NewStringUTF(env, response->roomPin);
                jsInvite = (*env)->NewStringUTF(env, response->invite);
                jsRoomURL = (*env)->NewStringUTF(env, response->roomURL);
				jsSubject = (*env)->NewStringUTF(env, response->subject);

                (*env)->CallVoidMethod(env, client_applicationJniObj, mid, jsRoomExtn, jsRoomPin, jsInvite, jsRoomURL, jsSubject);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
    }
	FUNCTION_EXIT
}

// Called in reponse to VIDYO_CLIENT_PRIVATE_SOAP_GET_INVITE_CONTENT
static void VidyoJNIInviteContentRsp(const char *eventName, const void* param)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    jstring js;
    jstring jsSubject;
    
    FUNCTION_ENTRY
    VidyoClientPrivateSoapOutEventGetInviteContent *response =  (VidyoClientPrivateSoapOutEventGetInviteContent*)param;
    if (!response)
    {
        LOGE("VidyoJNIInviteContentRsp paramter is NULL");
    }
    else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_GET_INVITE_CONTENT )
    {
        LOGE("VidyoJNIInviteContentRsp response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_CREATE_SCHEDULED_ROOM");
    }
    else if (response->error != 0)
    {
        LOGE("VidyoJNIInviteContentRsp response->error == %d", response->error );
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "getInviteContentsFailedCallback", "()V");
            if (mid != NULL)
            {
                (*env)->CallVoidMethod(env, client_applicationJniObj, mid);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
    }
    else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
    {
        LOGE("VidyoJNIInviteContentRsp response->result != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS (%d)",response->result);
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "getInviteContentsFailedCallback", "()V");
            if (mid != NULL)
            {
                (*env)->CallVoidMethod(env, client_applicationJniObj, mid);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
    }
    else
    {
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "getInviteContentsCallback", "(Ljava/lang/String;Ljava/lang/String;)V");
            if (mid != NULL)
            {
                js = (*env)->NewStringUTF(env, response->invite);
                jsSubject = (*env)->NewStringUTF(env, response->subject);
                (*env)->CallVoidMethod(env, client_applicationJniObj, mid, js, jsSubject);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
    }
	FUNCTION_EXIT
}

// Called in response to VIDYO_CLIENT_PRIVATE_SOAP_ADD_TO_MY_CONTACTS
static void VidyoJNIAddContactRsp(const char *eventName, const void* param)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    jint result;
    
    FUNCTION_ENTRY
    VidyoClientPrivateSoapOutEventAddToMyContacts *response =  (VidyoClientPrivateSoapOutEventAddToMyContacts *)param;
    if (!response)
    {
        LOGE("VidyoJNIAddContactRsp paramter is NULL");
    }
    else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_ADD_TO_MY_CONTACTS)
    {
        LOGE("VidyoJNIAddContactRsp response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_ADD_TO_MY_CONTACTS");
    }
    else if (response->error != 0)
    {
        LOGE("VidyoJNIAddContactRsp response->error == %d", response->error );
    }
    else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
    {
        LOGE("VidyoJNIAddContactRsp response->result != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS (%d)",response->result);
    }
    else
    {
        result = 0;
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "addContactCallback", "(I)V");
            if (mid != NULL)
            {
                (*env)->CallVoidMethod(env, client_applicationJniObj, mid, result);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
    }
	FUNCTION_EXIT
}

// Called in response to VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_FROM_MY_CONTACTS
static void VidyoJNIRemoveContactRsp(const char *eventName, const void* param)
{
    VidyoBool isAttached;
    JNIEnv *env;
    jmethodID mid;
    jint result;
    
    FUNCTION_ENTRY
    VidyoClientPrivateSoapOutEventRemoveFromMyContacts *response =  (VidyoClientPrivateSoapOutEventRemoveFromMyContacts *)param;
    if (!response)
    {
        LOGE("VidyoJNIRemoveContactRsp paramter is NULL");
    }
    else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_FROM_MY_CONTACTS)
    {
        LOGE("VidyoJNIRemoveContactRsp response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_FROM_MY_CONTACTS");
    }
    else if (response->error != 0)
    {
        LOGE("VidyoJNIRemoveContactRsp response->error == %d", response->error );
    }
    else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
    {
        LOGE("VidyoJNIRemoveContactRsp response->result != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS (%d)",response->result);
    }
    else
    {
        result = 0;
        LOCK
        env = getJniEnv(&isAttached);
        if (env != NULL)
        {
            mid = getApplicationJniMethodId(env, client_applicationJniObj, "removeContactCallback", "(I)V");
            if (mid != NULL)
            {
                (*env)->CallVoidMethod(env, client_applicationJniObj, mid, result);
            }
            releaseJniEnv(env, isAttached);
        }
        UNLOCK
    }
	FUNCTION_EXIT
}

// Called in response to VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_ENTITY_ID
static void VidyoJNIEntityInfoUpdated(const char *eventName, const void* param)
{
    FUNCTION_ENTRY
    VidyoClientPrivateSoapOutEventSearch *response =  (VidyoClientPrivateSoapOutEventSearch*)param;
    if (!response)
    {
        LOGE("VidyoJNIEntityInfoUpdated paramter is NULL");
    }
    else if (response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_ENTITY_ID )
    {
        LOGE("VidyoJNIEntityInfoUpdated response->typeRequest != VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_BY_ENTITY_ID");
    }
    else if (response->error != 0)
    {
        LOGE("VidyoJNIEntityInfoUpdated response->error == %d", response->error );
    }
    else if (VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS != response->result)
    {
        LOGE("VidyoJNIEntityInfoUpdated response->result != VIDYO_CLIENT_PRIVATE_SOAP_RESULT_SUCCESS (%d)",response->result);
    }
    else
    {
		if(!response->error)
		{
			int i;
			/*   LOGI("typeRequest=%d requestId=%d error=%d httpStatusCode=%d total=%d start=%d numEntries=%d result=%d",
			 response->typeRequest,
			 response->requestId,
			 response->error,
			 response->httpStatusCode,
			 response->total,
			 response->start,
			 response->numEntries,
			 response->result);   */
			
			for(i=0; i<response->numEntries;i++)
			{
				VidyoClientPrivateSoapAccountData d = response->accountData[i];
				if(     !d.roomMode.hasPIN)
					d.roomMode.roomPIN[0]=0;
				
				VidyoBool isAttached;
				jobject portalEntity;
				JNIEnv *env;
				
				if (env = getJniEnv(&isAttached))
				{
					//convert param to right type
					VidyoClientPrivateSoapAccountData* entityInfo= (VidyoClientPrivateSoapAccountData*)&d;
					
					//create and feel PortalEntity
					if (convertVidyoClientPrivateSoapAccountData2ContactObject(env, &portalEntity, entityInfo))
					{
						//call java public void updateMyEntity(PortalEntity entity)
						callUpdateEntity_(env, &portalEntity);
					}
					
					releaseJniEnv(env, isAttached);
					
				}
			}
		}
    }
	
    FUNCTION_EXIT
}


static void VidyoJNIGetLoginTypeResponse(const char *eventName, const void* param)
{
	VidyoBool isAttached;
	JNIEnv *env;
	jmethodID mid;
	int arg1;

	FUNCTION_ENTRY

	VidyoClientPrivateSoapOutEventGetLoginType *response =  (VidyoClientPrivateSoapOutEventGetLoginType *)param;
	LOGE("GotVidyoClientPrivateSoapOutEventGetLoginType loginType = %d, error =%d", response->loginType, response->error);
	if(response->error == 0)
		arg1 = response->loginType;
	else
		arg1 = -1;

	env = getJniEnv(&isAttached);
	if (env != NULL)
	{
		mid = getApplicationJniMethodId(env, client_applicationJniObj, "getLoginTypeCallback", "(I)V");
		if (mid != NULL)
		{
			(*env)->CallVoidMethod(env, client_applicationJniObj, mid, arg1);
		}
		releaseJniEnv(env, isAttached);
	}
	FUNCTION_EXIT
}


//todo: move this function to login controler
//register to recieve login events
static void registerForMobileEvents()
{
	registerForEvent(kVidyoClientContactManagerMyEntityInfoUpdated,(EventHandlerFunc)VidyoJNIMyEntityInfoUpdated);
	registerForEvent(kVidyoClientContactManagerEntityInfoUpdated,(EventHandlerFunc)VidyoJNIEntityInfoUpdated);
	/*
	 * This isn't actually Login event, but it is related to logging in or connecting to a server
	 */
	registerForEvent(kClientOutEventWebProxyUpdateRequested, (EventHandlerFunc)VidyoJNIWebProxyUpdateEventHandler);
	registerForEvent(kVidyoClientOutEventWebProxyAuthenticationFailed, (EventHandlerFunc)VidyoJNIWebProxyAuthenticationFailedEventHandler);
	
    registerForEvent(KVidyoClientPrivateSoapGetPortalFeatureResponse, (EventHandlerFunc)VidyoJNIGetPortalFeatureResponse);
    registerForEvent(KVidyoClientPrivateSoapGetControlMeetingURLResponse, (EventHandlerFunc)VidyoJNIGetControlMeetingURLResponse);
    
    registerForEvent(KVidyoClientPrivateSoapCreateSchedRoomResponse, (EventHandlerFunc)VidyoJNISchedRoomRsp);
    registerForEvent(KVidyoClientPrivateSoapGetInviteContentResponse, (EventHandlerFunc)VidyoJNIInviteContentRsp);
	
    registerForEvent(KVidyoClientPrivateSoapAddContactResponse, (EventHandlerFunc)VidyoJNIAddContactRsp);
    registerForEvent(KVidyoClientPrivateSoapRemoveContactResponse, (EventHandlerFunc)VidyoJNIRemoveContactRsp);

	registerForEvent(KVidyoClientPrivateSoapGetLoginTypeResponse, (EventHandlerFunc)VidyoJNIGetLoginTypeResponse);
}

JNIEXPORT jint JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetLoginState(JNIEnv *env, jobject jobj)
{
	GuiClientLoginState clientLoginState =  GetCurrentClientLoginState();
	jint retStatus;
	
	retStatus = (jint)clientLoginState;
	return retStatus;
}

// Set as a result of a VIDYO_CLIENT_PRIVATE_OUT_EVENT_PORTAL_COMMUNICATION_STATUS event
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetLoggedInWithToken(JNIEnv *env, jobject jObj2){
    //FUNCTION_ENTRY
    return (jboolean)(doGetLoggedInWithToken());
    //FUNCTION_EXIT
}




// Uses VIDYO_CLIENT_PRIVATE_REQUEST_SET_CURRENT_LANGUAGE
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetLanguage(JNIEnv *env, jobject jobj, jstring languageName)
{
	FUNCTION_ENTRY
	const char *ln = (*env)->GetStringUTFChars(env, languageName, NULL);
	
	doSetLanguage( ln );
	
	(*env)->ReleaseStringUTFChars(env, languageName, ln);
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_REQUEST_MOBILE_CALL_ON_HOLD
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_CallOnHold(JNIEnv *env, jobject jobj, jboolean onHold)
{
	doCallOnHold(onHold);
}

// TEMPORARY until SDK supports Front and back cameras
// Uses VIDYO_CLIENT_PRIVATE_REQUEST_ANDROID_SET_HAS_CAMERA
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetHasCamera(JNIEnv *env, jobject jobj,jboolean hasFrontCamera, jboolean hasBackCamera)
{
	//FUNCTION_ENTRY
	doSetHasCamera((VidyoBool)hasFrontCamera, (VidyoBool)hasBackCamera);
	//FUNCTION_EXIT
}

int JniStrcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
    return 0;
}



static VidyoClientPortalServiceEntityType Str2EntityType(char str[])
{
    if (JniStrcicmp(str, "legacy") == 0)
		return VIDYO_CLIENT_ENTITY_TYPE_LEGACY;
	else if (JniStrcicmp(str, "room") == 0)
		return VIDYO_CLIENT_ENTITY_TYPE_ROOM;
		return VIDYO_CLIENT_ENTITY_TYPE_MEMBER;
}

//
// converts java contact object to VidyoClientPrivateSoapAccountData
// returns true for success, false for failure
//
static VidyoBool convertContactObject2AccountDataStruct(JNIEnv *env, VidyoClientPrivateSoapAccountData* accountData, jobject contact, jstring j_pin)
{
#define MAX_PORTAL_ENTITY_TYPE_SIZE	20
	
	VidyoBool success;
	jclass peClass;
	char entityType[MAX_PORTAL_ENTITY_TYPE_SIZE];
	//	char status[MAX_STATUS_SIZE];
	
	FUNCTION_ENTRY
	if (j_pin != NULL)
	{
		if (!javaString2Buffer(env, j_pin, accountData->roomMode.roomPIN,VIDYO_CLIENT_PRIVATE_SOAP_PIN_SIZE))
			return VIDYO_FALSE;
		accountData->roomMode.hasPIN = VIDYO_TRUE;
	}
	else
		accountData->roomMode.hasPIN = VIDYO_FALSE;
	
	peClass = (*env)->GetObjectClass(env, portalEntityObj);
	if (peClass == NULL) {
		LOGE("ConstructFromJavaObject: No class PortalEntity");
		return VIDYO_FALSE;
	}
	
	if (!getClassString(env, contact, peClass, "getId", accountData->entityID, VIDYO_CLIENT_PRIVATE_SOAP_EID_SIZE))
	{
		LOGE("ConstructFromJavaObject: getId failed");
		return VIDYO_FALSE;
	}
	
	if (!getClassString(env, contact, peClass, "getParticipantId", accountData->participantID, VIDYO_CLIENT_PRIVATE_SOAP_EID_SIZE))
	{
		LOGE("ConstructFromJavaObject: getParticipantId failed");
		return VIDYO_FALSE;
	}
	
	if (!getClassString(env, contact, peClass, "getDisplayName", accountData->displayName, VIDYO_CLIENT_PRIVATE_SOAP_USERNAME_SIZE))
	{
		LOGE("ConstructFromJavaObject: getDisplayName failed");
		return VIDYO_FALSE;
	}
	
	
	if (!getClassString(env, contact, peClass, "getExtension", accountData->extension, VIDYO_CLIENT_PRIVATE_SOAP_EXTENSION_SIZE))
	{
		LOGE("ConstructFromJavaObject: getExtension failed");
		return VIDYO_FALSE;
	}
	
	
	if (!getClassString(env, contact, peClass, "getTypeString", entityType, MAX_PORTAL_ENTITY_TYPE_SIZE))
	{
		LOGE("ConstructFromJavaObject: getTypeString failed");
		return VIDYO_FALSE;
	}
	
	
	accountData->entityType = Str2EntityType(entityType);
	
	//we do not need the rest of the data
	FUNCTION_EXIT
	return VIDYO_TRUE;
}


//TODO: document
const char *memberStatus2String(VidyoClientPrivateSoapMemberStatus status)
{ //TODO: translate to multiple languages
	switch(status)
	{
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_ONLINE: return "Online";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_OFFLINE: return "Offline";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_BUSY: return "Busy";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_BUSY_IN_OWN_ROOM: return "BusyInOwnRoom";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RINGING: return "Ringing";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RING_ACCEPTED: return "RingAccepted";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RING_REJECTED: return "RingRejected";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_RING_NO_ANSWER: return "RingNoAnswer";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_ALERTING: return "Alerting";
		case VIDYO_CLIENT_PRIVATE_SOAP_MEMBER_STATUS_ALERT_CANCELLED: return "AlertCancelled";
	}
	return NULLSTRING;
}

//TODO: document
const char *roomStatus2String(VidyoClientPrivateSoapRoomStatus status)
{
	//TODO: translate to multiple languages
	switch(status)
	{
		case VIDYO_CLIENT_PRIVATE_SOAP_ROOM_EMPTY: return "Empty";
		case VIDYO_CLIENT_PRIVATE_SOAP_ROOM_FULL: return "Full";
		case VIDYO_CLIENT_PRIVATE_SOAP_ROOM_OCCUPIED: return "Occupied";
	}
	return NULLSTRING;
}


//TODO: document
static VidyoBool convertVidyoClientPrivateSoapAccountData2ContactObject(JNIEnv *env, jobject *contact, const VidyoClientPrivateSoapAccountData* accountData)
{
	
	char* typeStr = "member";
	jclass peClass = NULL;
	VidyoBool success = VIDYO_FALSE;
	
	//	FUNCTION_ENTRY
	
	//get class object
	if( (peClass = (*env)->GetObjectClass(env, portalEntityObj)) == NULL)
	{
		LOGE("convertVidyoClientPrivateSoapAccountData2ContactObject: PortalEntity not found");
		(*env)->ExceptionDescribe(env);
		//FUNCTION_EXIT
		return VIDYO_FALSE;
	}
	
	//define type string
	if(accountData->entityType == VIDYO_CLIENT_ENTITY_TYPE_ROOM)
		typeStr = "room";
	else if(accountData->entityType == VIDYO_CLIENT_ENTITY_TYPE_LEGACY)
		typeStr = "legacy";
	
	//create Portal entity object
	success = createPortalEntity(env, contact,
								 accountData->entityID, accountData->extension,
								 accountData->displayName, accountData->emailAddress,
								 accountData->tenant, typeStr, accountData->ownerID);
	if (success)
	{
		if( setClassString(env, peClass, contact, "setParticipantId", accountData->participantID) )
		{
			setClassBool(env, peClass, contact, "setIsContact", accountData->isInMyContacts); //PWC

			if (accountData->entityType == VIDYO_CLIENT_ENTITY_TYPE_MEMBER)
			{
				if( setClassString(env, peClass, contact, "setMemberStatus", memberStatus2String(accountData->memberStatus)))
				{
					//if( setClassString(env, peClass, contact, "setMemberMode", ""))) //NA
					if( setClassBool(env, peClass, contact, "setCanCallDirect", accountData->canCallDirect) )
					{
						if( setClassBool(env, peClass, contact, "setCanJoinMeeting", accountData->canJoinMeeting) )
						{
							// Added to support member's room
							setClassBool(env, peClass, contact, "setLocked", accountData->roomMode.isRoomLocked);
							setClassBool(env, peClass, contact, "setHasPin", accountData->roomMode.hasPIN);
							setClassString(env, peClass, contact, "setRoomStatus", roomStatus2String(accountData->roomStatus));
							setClassString(env, peClass, contact, "setRoomUrl", accountData->roomMode.roomURL);
							
							if (accountData->roomMode.hasPIN == VIDYO_TRUE) {
								setClassString(env, peClass, contact, "setRoomPin", accountData->roomMode.roomPIN);
							}
							
							//FUNCTION_EXIT
							return VIDYO_TRUE;
						}
					}
				}
			}
			else if (accountData->entityType == VIDYO_CLIENT_ENTITY_TYPE_ROOM ||
					 accountData->entityType == VIDYO_CLIENT_ENTITY_TYPE_LEGACY)
			{
			
				LOGI("Participant=%s, RoomStatus=%s\n", accountData->participantID, roomStatus2String(accountData->roomStatus));
				
				
				if( setClassString(env, peClass, contact, "setRoomStatus", roomStatus2String(accountData->roomStatus)))
				{
					if( setClassString(env, peClass, contact, "setRoomUrl", accountData->roomMode.roomURL))
					{
						if( setClassBool(env, peClass, contact, "setLocked", accountData->roomMode.isRoomLocked) )
						{
							if( setClassBool(env, peClass, contact, "setHasPin", accountData->roomMode.hasPIN) )
							{
								setClassBool(env, peClass, contact, "setCanJoinMeeting", accountData->canJoinMeeting);
								
								if (accountData->roomMode.hasPIN == VIDYO_TRUE) {
									setClassString(env, peClass, contact, "setRoomPin", accountData->roomMode.roomPIN);
								}
								//FUNCTION_EXIT
								return VIDYO_TRUE;
							}
						}
					}
				}
			}
		}
	}
	
	//FUNCTION_EXIT
	return VIDYO_FALSE;
}


//TODO: document
static VidyoBool convertVidyoClientPrivateSoapParticipantData2ContactObject(JNIEnv *env, jobject *contact, const VidyoClientPrivateSoapConferenceParticipantData* participantData)
{
	LOGE("convertVidyoClientPrivateSoapParticipantData2ContactObject === lpeng, TBD");
	return VIDYO_FALSE;
}

//create an empty array of ContactObject s
static VidyoBool createContactObjectJavaArray(JNIEnv *env, jobjectArray* contactObjectArray, size_t listSize)
{
	//FUNCTION_ENTRY
	jclass peClass = NULL;
	//	jmethodID defaultConstructor = NULL;
	//	jobject dummyObj = NULL;
	
	if(peClass = (*env)->GetObjectClass(env, portalEntityObj))
	/*if ((defaultConstructor = (*env)->GetMethodID(env, peClass, "<init>", "()V")))
	 if ((dummyObj = (jobject)(*env)->NewObject(env, peClass, defaultConstructor)) )*/
		if (*contactObjectArray = (jobjectArray)(*env)->NewObjectArray(env, (int)listSize, peClass, NULL)) //TODO: this is probably the wrong way to do it
		{
			//FUNCTION_EXIT
			return VIDYO_TRUE;
		}
	
	
	ExceptionDidOccure(env, __FUNCTION__);
	
	*contactObjectArray = NULL;
	
	LOGE("createContactObjectJavaArray failed");
	//FUNCTION_EXIT
	return VIDYO_FALSE;
	
}

// Convert AccountData Array to ContactObject Java Array
static VidyoBool convertAccountDataArray2ContactObjectArray(JNIEnv *env, jobjectArray* contactObjectArray, const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	int i;
	//	FUNCTION_ENTRY
	for(i = 0; i<arraySize; i++)
	{
		jobject peObject;
		
		//		LOGI("calling convertVidyoClientPrivateSoapAccountData2ContactObject for element %d",i);
		
		if(!convertVidyoClientPrivateSoapAccountData2ContactObject(env, &peObject , &(accountDataArray[i]) ))
		{
			LOGE("convertAccountDataArray2ContactObjectArray failed for element %d",i);
			//FUNCTION_EXIT
			return VIDYO_FALSE;
		}
		//LOGI("calling SetObjectArrayElement  for element %d",i);
		
		(*env)->SetObjectArrayElement(env, *contactObjectArray, i, peObject);
		//LOGI("after calling SetObjectArrayElement  for element %d",i);
		
	}
	
	//	FUNCTION_EXIT
	return VIDYO_TRUE;
}

// Convert ParticipantData Array to ContactObject Java Array
static VidyoBool convertParticipantDataArray2ContactObjectArray(JNIEnv *env, jobjectArray* contactObjectArray, const VidyoClientPrivateSoapConferenceParticipantData* participantDataArray, size_t arraySize)
{
	int i;
	//	FUNCTION_ENTRY
	for(i = 0; i<arraySize; i++)
	{
		jobject peObject;

		//LOGI("calling convertVidyoClientPrivateSoapParticipantData2ContactObject for element %d",i);

		if(!convertVidyoClientPrivateSoapParticipantData2ContactObject(env, &peObject , &(participantDataArray[i]) ))
		{
			LOGE("convertParticipantDataArray2ContactObjectArray failed for element %d",i);
			//FUNCTION_EXIT
			return VIDYO_FALSE;
		}
		//LOGI("calling SetObjectArrayElement  for element %d",i);

		(*env)->SetObjectArrayElement(env, *contactObjectArray, i, peObject);
		//LOGI("after calling SetObjectArrayElement  for element %d",i);
		
	}

	//	FUNCTION_EXIT
	return VIDYO_TRUE;
}

//TODO: document
static VidyoUint createContactObjectJavaArrayFromAccountDataArray(JNIEnv *env, jobjectArray* contactObjectArray, const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	//limit array size to avoid overflow of the JNI refere3nce table
	if (arraySize > MAX_ARRAY_SIZE) //30
		arraySize = MAX_ARRAY_SIZE;
	if (createContactObjectJavaArray(env, contactObjectArray,arraySize))
		if ( ! convertAccountDataArray2ContactObjectArray(env, contactObjectArray,accountDataArray,arraySize))
		    return 0;

	return arraySize;
}

static VidyoUint createContactObjectJavaArrayFromParticipantDataArray(JNIEnv *env, jobjectArray* contactObjectArray, const VidyoClientPrivateSoapConferenceParticipantData* participantDataArray, size_t arraySize)
{	
	//limit array size to avoid overflow of the JNI refere3nce table
	if (arraySize > MAX_ARRAY_SIZE) //30
		arraySize = MAX_ARRAY_SIZE;
	if (createContactObjectJavaArray(env, contactObjectArray,arraySize))
		if ( ! convertParticipantDataArray2ContactObjectArray(env, contactObjectArray,participantDataArray,arraySize))
		    return 0;
	
	return arraySize;
}


static void InvokeContactsUpdate(const char *methodId, const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	VidyoBool isAttached;
	VidyoBool success = VIDYO_FALSE;
	JNIEnv *env;
	jmethodID mid;
	jobjectArray peArray;
	jboolean lastrec = VIDYO_FALSE;
	VidyoUint numrecs;
	VidyoUint totalrecs;
	VidyoUint nextrec = 0;
	
	FUNCTION_ENTRY
	LOGE("InvokeContactsUpdate #contacts %d", arraySize);
	
	// Need to handle the case of 0 records so that GUI can do appropriate thing
	if (arraySize == 0) {
		if (env = getJniEnv(&isAttached))
		{
			if (mid = getApplicationJniMethodId(env, client_applicationJniObj, methodId, "([Lcom/vidyo/VidyoClientLib/entities/PortalEntity;Z)V"))
			{
				createContactObjectJavaArrayFromAccountDataArray(env, &peArray, accountDataArray, arraySize);
				(*env)->CallVoidMethod(env, client_applicationJniObj, mid, peArray, VIDYO_TRUE);
				success = VIDYO_TRUE;
			}
			releaseJniEnv(env, isAttached);
		}
	} else {
		// iterate through the records
		totalrecs = arraySize;
		while (totalrecs != 0)
		{
			if (env = getJniEnv(&isAttached))
			{
				if (mid = getApplicationJniMethodId(env, client_applicationJniObj, methodId, "([Lcom/vidyo/VidyoClientLib/entities/PortalEntity;Z)V"))
				{
					LOGE("InvokeContactsUpdate doing contacts %d to %d", nextrec, arraySize-nextrec);
					numrecs = createContactObjectJavaArrayFromAccountDataArray(env, &peArray, &accountDataArray[nextrec],arraySize-nextrec);
					if (numrecs == 0) {
						releaseJniEnv(env, isAttached);
						break;
					}
					nextrec += numrecs;
					
					if (numrecs > totalrecs)
						numrecs = totalrecs;
					
					totalrecs -= numrecs;
					if (totalrecs == 0)
						lastrec = VIDYO_TRUE;
					
					(*env)->CallVoidMethod(env, client_applicationJniObj, mid, peArray, lastrec);  //PWC
					success = VIDYO_TRUE;
				} else {
					releaseJniEnv(env, isAttached);
					break;
				}
			} else {
				break;
			}
			releaseJniEnv(env, isAttached);
		}
	}
	
	
	if(!success)
	{
		LOGE("InvokeContactsUpdate FAILED");
	}
	FUNCTION_EXIT
}

//TODO: document
void JavaGuiUpdateMyContacts(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	//FUNCTION_ENTRY
	InvokeContactsUpdate( "updateContacts", accountDataArray, arraySize);
	//FUNCTION_EXIT
}

//TODO: document
void JavaGuiUpdateAllContacts(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	//FUNCTION_ENTRY
	InvokeContactsUpdate( "updateSearch", accountDataArray, arraySize);
	//FUNCTION_EXIT
}


//todo: create macro structures to define java objects
static VidyoBool createAttendeeEntity(JNIEnv *env, jobject *aeObject, const char* uri, const char* displayName)
{
	jclass aeClass;
	jmethodID realConstructor;
	jmethodID mId;
	
	//	FUNCTION_ENTRY
	*aeObject = NULL;
	aeClass = (*env)->GetObjectClass(env, attendeeEntityObj);
	if (aeClass == NULL) {
		LOGE("createAttendeeEntity: AttendeeEntity not found");
		(*env)->ExceptionDescribe(env);
		goto END;
	}
	
	if ((realConstructor = (*env)->GetMethodID(env, aeClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V")) == NULL) {
		LOGE("createAttendeentity: NULL real constructor for AttendeeEntity");
		(*env)->ExceptionDescribe(env);
		goto END;
	}
	
	*aeObject = (jobject)(*env)->NewObject(env, aeClass, realConstructor, (*env)->NewStringUTF(env, uri), (*env)->NewStringUTF(env, displayName));
	
	if (*aeObject == NULL) {
		LOGE("createAttendeeEntity: NULL AE object");
		(*env)->ExceptionDescribe(env);
		goto END;
	}
	
	
END:
	if (ExceptionDidOccure(env,__FUNCTION__)) {
		*aeObject = NULL;
		FUNCTION_EXIT
		return VIDYO_FALSE;
	}
	
	//	FUNCTION_EXIT
	return VIDYO_TRUE;
}

//TODO: document
static VidyoBool convertAttendeeData2AttendeeObject(JNIEnv *env, jobject *attendee, const AttendeeData* attendeeData)
{
	jclass aeClass = NULL;
	VidyoBool success = VIDYO_FALSE;
	
	//	FUNCTION_ENTRY
	
	//get class object
	if( (aeClass = (*env)->GetObjectClass(env, attendeeEntityObj)) == NULL)
	{
		LOGE("convertAttendeeData2AttendeeObject: attendeeEntityObj not found");
		(*env)->ExceptionDescribe(env);
		//FUNCTION_EXIT
		return VIDYO_FALSE;
	}
	
	//create Portal entity object
	success = createAttendeeEntity(env, attendee, attendeeData->uri, attendeeData->displayName);
	if (success)
		return VIDYO_TRUE;
	
	//FUNCTION_EXIT
	return VIDYO_FALSE;
}

// Convert AttendeeData Array to AttendeeObject Java Array
static VidyoBool convertAttendeeDataArray2AttendeeObjectArray(JNIEnv *env, jobjectArray* attendeeObjectArray, const AttendeeData* attendeeDataArray, size_t arraySize)
{
	int i;
	//	FUNCTION_ENTRY
	for(i = 0; i<arraySize; i++)
	{
		jobject aeObject;
		
		if (!convertAttendeeData2AttendeeObject(env, &aeObject , &(attendeeDataArray[i]) ))
		{
			LOGE("convertAttendeeDataArray2AttendeeObjectArray failed for element %d",i);
			//FUNCTION_EXIT
			return VIDYO_FALSE;
		}
		
		(*env)->SetObjectArrayElement(env, *attendeeObjectArray, i, aeObject);
	}
	
	//	FUNCTION_EXIT
	return VIDYO_TRUE;
}

//create an empty array of AttendeeObject s
static VidyoBool createAttendeeObjectJavaArray(JNIEnv *env, jobjectArray* attendeeObjectArray, size_t listSize)
{
	//FUNCTION_ENTRY
	jclass aeClass = NULL;
	
	if (aeClass = (*env)->GetObjectClass(env, attendeeEntityObj))
	{
		if (*attendeeObjectArray = (jobjectArray)(*env)->NewObjectArray(env, (int)listSize, aeClass, NULL)) //TODO: this is probably the wrong way to do it
		{
			//FUNCTION_EXIT
			return VIDYO_TRUE;
		}
	}
	
	ExceptionDidOccure(env, __FUNCTION__);
	*attendeeObjectArray = NULL;
	
	LOGE("createAttendeeObjectJavaArray failed");
	//FUNCTION_EXIT
	return VIDYO_FALSE;
}

//TODO: document
static VidyoUint createAttendeeObjectJavaArrayFromAttendeeDataArray(JNIEnv *env, jobjectArray* attendeeObjectArray, const AttendeeData* attendeeDataArray, size_t arraySize)
{
	//limit array size to avoid overflow of the JNI refere3nce table
	if (arraySize > MAX_ARRAY_SIZE) //30
		arraySize = MAX_ARRAY_SIZE;
	if (createAttendeeObjectJavaArray(env, attendeeObjectArray, arraySize))
		if ( ! convertAttendeeDataArray2AttendeeObjectArray(env, attendeeObjectArray, attendeeDataArray, arraySize))
		    return 0;
	
	return arraySize;
}

static void InvokeContactsRecCountUpdate(const char *methodId, int numPortalRecs, int numCacheRecs, int maxCacheRecs, int startCacheRec, int endCacheRec)
{
	VidyoBool isAttached;
	VidyoBool success = VIDYO_FALSE;
	JNIEnv *env;
	jmethodID mid;
	
	//FUNCTION_ENTRY
	
	// Need to handle the case of 0 records so that GUI can do appropriate thing
	if (env = getJniEnv(&isAttached))
	{
		if (mid = getApplicationJniMethodId(env, client_applicationJniObj, methodId, "(IIIII)V"))
		{
			(*env)->CallVoidMethod(env, client_applicationJniObj, mid, (jint)numPortalRecs, (jint)numCacheRecs, (jint)maxCacheRecs, (jint)startCacheRec, (jint)endCacheRec );
			success = VIDYO_TRUE;
		}
		releaseJniEnv(env, isAttached);
	}
	
	if(!success)
	{
		LOGE("InvokeContactsUpdate FAILED");
	}
	//FUNCTION_EXIT
}

//TODO: document
void JavaGuiRecCountUpdateAllContacts(int numPortalRecs, int numCacheRecs, int maxCacheRecs, int startCacheRec, int endCacheRec)
{
	//FUNCTION_ENTRY
	InvokeContactsRecCountUpdate( "setSearchCounts", numPortalRecs, numCacheRecs, maxCacheRecs, startCacheRec, endCacheRec);
	//FUNCTION_EXIT
}


static void InvokeRoomUpdate(const char *methodId, const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	VidyoBool isAttached;
	VidyoBool success = VIDYO_FALSE;
	JNIEnv *env;
	jmethodID mid;
	jobjectArray peArray;
	jboolean lastrec = VIDYO_FALSE;
	VidyoUint numrecs;
	VidyoUint totalrecs;
	VidyoUint nextrec = 0;
	
	//FUNCTION_ENTRY
	
	//LOGI("InvokeRoomUpdate(%s) #recs=%d", methodId, arraySize);
	
	// Need to handle the case of 0 records so that GUI can do appropriate thing
	if (arraySize == 0) {
		if (env = getJniEnv(&isAttached))
		{
			if (mid = getApplicationJniMethodId(env, client_applicationJniObj, methodId, "(Lcom/vidyo/VidyoClientLib/entities/PortalEntity;[Lcom/vidyo/VidyoClientLib/entities/PortalEntity;Z)V"))
			{
				createContactObjectJavaArrayFromAccountDataArray(env, &peArray, accountDataArray, arraySize);
				(*env)->CallVoidMethod(env, client_applicationJniObj, mid, NULL, peArray, VIDYO_TRUE);
				success = VIDYO_TRUE;
			}
			releaseJniEnv(env, isAttached);
		}
	} else {
		// iterate through the records
		totalrecs = arraySize;
		while (totalrecs != 0)
		{
			if (env = getJniEnv(&isAttached))
			{
				if (mid = getApplicationJniMethodId(env, client_applicationJniObj, methodId, "(Lcom/vidyo/VidyoClientLib/entities/PortalEntity;[Lcom/vidyo/VidyoClientLib/entities/PortalEntity;Z)V"))
				{
					LOGE("InvokeRoomUpdate(%s) nextrec=%d, recsleft=%d", methodId, nextrec, arraySize-nextrec);
					
					numrecs = createContactObjectJavaArrayFromAccountDataArray(env, &peArray, &accountDataArray[nextrec],arraySize-nextrec);
					if (numrecs == 0) {
						releaseJniEnv(env, isAttached);
						break;
					}
					nextrec += numrecs;
					
					if (numrecs > totalrecs)
						numrecs = totalrecs;
					
					totalrecs -= numrecs;
					if (totalrecs == 0)
						lastrec = VIDYO_TRUE;
					
					(*env)->CallVoidMethod(env, client_applicationJniObj, mid, NULL, peArray, lastrec);
					success = VIDYO_TRUE;
				} else {
					releaseJniEnv(env, isAttached);
					break;
				}
			} else {
				break;
			}
			releaseJniEnv(env, isAttached);
		}
	}
	
	
	
	if(!success)
	{
		LOGE("InvokeRoomUpdate FAILED");
	}
	//FUNCTION_EXIT
}

static void InvokeRoomUpdate2(const char *methodId, const VidyoClientPrivateSoapConferenceParticipantData* participantDataArray, size_t arraySize)
{
	VidyoBool isAttached;
	VidyoBool success = VIDYO_FALSE;
	JNIEnv *env;
	jmethodID mid;
	jobjectArray peArray;
	jboolean lastrec = VIDYO_FALSE;
	VidyoUint numrecs;
	VidyoUint totalrecs;
	VidyoUint nextrec = 0;

	//FUNCTION_ENTRY

	//LOGI("InvokeRoomUpdate(%s) #recs=%d", methodId, arraySize);
	// Need to handle the case of 0 records so that GUI can do appropriate thing
	if (arraySize == 0) {
		if (env = getJniEnv(&isAttached))
		{
			if (mid = getApplicationJniMethodId(env, client_applicationJniObj, methodId, "(Lcom/vidyo/VidyoClientLib/entities/PortalEntity;[Lcom/vidyo/VidyoClientLib/entities/PortalEntity;Z)V"))
			{
				createContactObjectJavaArrayFromParticipantDataArray(env, &peArray, participantDataArray, arraySize);
				(*env)->CallVoidMethod(env, client_applicationJniObj, mid, NULL, peArray, VIDYO_TRUE);
				success = VIDYO_TRUE;
			}
			releaseJniEnv(env, isAttached);
		}
	} else {
		// iterate through the records
		totalrecs = arraySize;
		while (totalrecs != 0)
		{
			if (env = getJniEnv(&isAttached))
			{
				if (mid = getApplicationJniMethodId(env, client_applicationJniObj, methodId, "(Lcom/vidyo/VidyoClientLib/entities/PortalEntity;[Lcom/vidyo/VidyoClientLib/entities/PortalEntity;Z)V"))
				{
					LOGE("InvokeRoomUpdate(%s) nextrec=%d, recsleft=%d", methodId, nextrec, arraySize-nextrec);

					numrecs = createContactObjectJavaArrayFromParticipantDataArray(env, &peArray, &participantDataArray[nextrec],arraySize-nextrec);
					if (numrecs == 0) {
						releaseJniEnv(env, isAttached);
						break;
					}
					nextrec += numrecs;

					if (numrecs > totalrecs)
						numrecs = totalrecs;

					totalrecs -= numrecs;
					if (totalrecs == 0)
						lastrec = VIDYO_TRUE;

					(*env)->CallVoidMethod(env, client_applicationJniObj, mid, NULL, peArray, lastrec);
					success = VIDYO_TRUE;
				} else {
					releaseJniEnv(env, isAttached);
					break;
				}
			} else {
				break;
			}
			releaseJniEnv(env, isAttached);
		}
	}

	if(!success)
	{
		LOGE("InvokeRoomUpdate FAILED");
	}
	//FUNCTION_EXIT
}

//TODO: document
void JavaGuiUpdateMyRooms(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	//FUNCTION_ENTRY
	
	//rooms list is of current user
	InvokeRoomUpdate( "updateRooms",  accountDataArray, arraySize);
	//FUNCTION_EXIT
}


void JavaGuiUpdateMemberRooms(const VidyoClientPrivateSoapAccountData* accountDataArray, size_t arraySize)
{
	//FUNCTION_ENTRY
	InvokeRoomUpdate("updateMemberRooms",  accountDataArray, arraySize);
	//FUNCTION_EXIT
}


void JavaGuiUpdateRoomParticipants(const VidyoClientPrivateSoapConferenceParticipantData* participantDataArray, size_t arraySize)
{
	//FUNCTION_ENTRY
	InvokeRoomUpdate2( "updateRoomParticipants", participantDataArray, arraySize);
	//FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_GET_PORTALFEATURES
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetPortalFeatures(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doGetPortalFeatures();
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_GET_MODERATOR_URL
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetControlMeetingURL(JNIEnv *env, jobject jObj2, jstring roomID)
{
	FUNCTION_ENTRY
	const char *roomIDC = (*env)->GetStringUTFChars(env, roomID, NULL);
	
	LOGI("Java_com_vidyo_vidyosample_VidyoSampleApplication_GetControlMeetingURL( roomID %s) \n", roomIDC);
	doGetControlMeetingURL(roomIDC);
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_INVITE_TO_CONFERENCE
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_InviteEntity(JNIEnv *env, jobject jObj2, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		doInviteEntity(&accountData);
	}
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_DIRECT_CALL or VIDYO_CLIENT_PRIVATE_SOAP_JOIN_CONFERENCE
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_Join(JNIEnv *env, jobject jObj2,jobject contact, jboolean callDirect, jstring j_pin)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, j_pin))
	{
		if(callDirect)
		{
			doCallDirect(&accountData);
			
		}
		else
		{
			doJoin(&accountData);
		}
		return (jboolean)1;
	}
	
	FUNCTION_EXIT
	return (jboolean)0;
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_JOIN_CONFERENCE_BY_NAME
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_JoinByName(JNIEnv *env, jobject jObj2, jstring displayName, jstring j_pin)
{
	FUNCTION_ENTRY
	
	const char *dn = (*env)->GetStringUTFChars(env, displayName, NULL);
	const char *pin = (*env)->GetStringUTFChars(env, j_pin, NULL);
	doJoinByName(dn, pin);
	
	FUNCTION_EXIT
	return (jboolean)1;
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_JOIN_IPC_CONFERENCE
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_JoinIPC(JNIEnv *env, jobject jObj2,jobject contact, jstring j_pin)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, j_pin))
	{
		doJoinIPC(&accountData);
		return (jboolean)1;
	}
	
	FUNCTION_EXIT
	return (jboolean)0;
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_JOIN_CONFERENCE
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_JoinSchedRoomExtension(JNIEnv *env, jobject jObj2,jstring extension, jstring j_pin)
{
	FUNCTION_ENTRY
	
	const char *ext = (*env)->GetStringUTFChars(env, extension, NULL);
	const char *pin = (*env)->GetStringUTFChars(env, j_pin, NULL);
	doJoinSchedRoomExtension(ext, pin);
	
	FUNCTION_EXIT
	return (jboolean)0;
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_DIRECT_CALL_BY_NAME
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_CallByNameDirect(JNIEnv *env, jobject jObj2, jstring displayName)
{
	FUNCTION_ENTRY
	
	const char *dn = (*env)->GetStringUTFChars(env, displayName, NULL);
	doCallByNameDirect(dn);
	
	FUNCTION_EXIT
	return (jboolean)1;
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StopPortalUpdates(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStopPortalUpdates();
	FUNCTION_EXIT
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StartPortalUpdates(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStartPortalUpdates();
	FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StartSearch(JNIEnv *env, jobject jobj, jstring hint)
{
	char* hintStr;
	FUNCTION_ENTRY
	hintStr = (char *)(*env)->GetStringUTFChars(env, hint, NULL);
	doStartSearch(hintStr);
	(*env)->ReleaseStringUTFChars(env, hint, hintStr);
	FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StopSearch(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStopSearch();
	FUNCTION_EXIT
}

JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_ShiftSearch(JNIEnv *env, jobject jobj, jint shift)
{
	jboolean ret;
	FUNCTION_ENTRY
	ret = doShiftSearch(shift);
	FUNCTION_EXIT
	return ret;
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StartRoomParticipantsUpdates(JNIEnv *env, jobject jobj, jobject jRoom)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, jRoom, NULL))
	{
		doStartRoomParticipantsUpdates(&accountData);
	}
	
	FUNCTION_EXIT
}
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StopRoomParticipantsUpdates(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStopRoomParticipantsUpdates();
	FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StopAttendeeUpdates(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStopAttendeeUpdates();
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_REQUEST_GET_NUM_PARTICIPANTS and VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT
static jboolean doGetAttendee(JNIEnv *env, jint index, jobject *ptr2AttendeeEntry)
{
	jclass aeClass = NULL;
	size_t numParticipants;
	
	//determine the number of participants
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_NUM_PARTICIPANTS, &numParticipants, 0, 0);
	
	//If the number of participants is less than the desired index then return False
	if (numParticipants <= index)
		return VIDYO_FALSE;
	
	
	//get class object
	if( (aeClass = (*env)->GetObjectClass(env, attendeeEntityObj)) == NULL)
	{
		LOGE("GetSelfAttendee: AttendeeEntity not found");
		(*env)->ExceptionDescribe(env);
		//FUNCTION_EXIT
		return VIDYO_FALSE;
	}

	VidyoClientPrivateRequestParticipantDetails pDetails;
	if (GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_PARTICIPANT_DETAILS_AT,
							  &pDetails,
							  sizeof(VidyoClientPrivateRequestParticipantDetails),
							  index) == VIDYO_CLIENT_ERROR_OK)
	{
		const char* uri = pDetails.uri;
		const char* displayName = pDetails.name;
		
		setClassString(env, aeClass, ptr2AttendeeEntry, "setDisplayName", displayName);
		setClassString(env, aeClass, ptr2AttendeeEntry, "setUri", uri);
		setClassBool(env, aeClass, ptr2AttendeeEntry, "setIsGuest",
					 (pDetails.participantType == VidyoClientPrivateParticipantTypeGuest));
	}
	return VIDYO_TRUE;
}

// Uses VIDYO_CLIENT_PRIVATE_REQUEST_GET_NUM_PARTICIPANTS and VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetAttendee(JNIEnv *env, jobject jObj2, jint index, jobject aeObject)
{
	return doGetAttendee(env, index, &aeObject);
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StartAttendeeUpdates(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStartAttendeeUpdates();
	FUNCTION_EXIT
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StartMemberRoomsUpdates(JNIEnv *env, jobject jobj, jobject jEntity)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, jEntity, NULL))
	{
		doStartMemberRoomsUpdates(&accountData);
	}
	
	FUNCTION_EXIT
	
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StopMemberRoomsUpdates(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStopMemberRoomsUpdates();
	FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StartEntityUpdates(JNIEnv *env, jobject jobj, jobject jContact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, jContact, NULL))
	{
		doStartEntityUpdates(&accountData);
	}
	
	FUNCTION_EXIT
	
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StopEntityUpdates(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doStopEntityUpdates();
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_LOCK_ROOM
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_LockRoom(JNIEnv *env, jobject jobj, jobject Contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, Contact, NULL))
	{
		doLockRoom(&accountData);
	}
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_UNLOCK_ROOM
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_UnlockRoom(JNIEnv *env, jobject jobj, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		doUnlockLockRoom(&accountData);
	}
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_CREATE_SCHEDULED_ROOM
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_CreateScheduledRoom(JNIEnv *env, jobject jobj, jboolean usePin)
{
	FUNCTION_ENTRY
    
    doCreateScheduledRoom((VidyoBool)usePin);
    
    FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_GET_INVITE_CONTENT
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetRoomEmailInviteContent(JNIEnv *env, jobject jobj, jstring javastringRoomID)
{
    char roomID[VIDYO_CLIENT_PRIVATE_SOAP_EID_SIZE+1];
	
	FUNCTION_ENTRY
	
    //send the request to get the invitation
	if (javaString2Buffer(env, javastringRoomID, roomID, VIDYO_CLIENT_PRIVATE_SOAP_EID_SIZE))
		doGetInviteContent(roomID);
    
    FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_DROP_PARTICIPANT
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_DropParticipant(JNIEnv *env, jobject jobj, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		doDropParticipant(&accountData);
	}
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_MUTE_AUDIO
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetParticipantAudioMute(JNIEnv *env, jobject jobj, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		doSetParticipantAudioMute(&accountData);
	}
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_MUTE_AUDIO
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetParticipantAudioUnmute(JNIEnv *env, jobject jobj, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		doSetParticipantAudioUnmute(&accountData);
	}
	
	FUNCTION_EXIT
}

static void RoomCreatedCallbackToJava_( const char *name, VidyoBool result)
{
	VidyoBool isAttached;
	JNIEnv *env;
	jmethodID mid;
	jstring js;
	
	LOCK
	FUNCTION_ENTRY
	
	env = getJniEnv(&isAttached);
	if (env == NULL)
		goto FAIL0;
	
	mid = getApplicationJniMethodId(env, client_applicationJniObj, "roomCreated", "(Ljava/lang/String;Z)V");
	if (mid == NULL)
		goto FAIL1;
	
	js = (*env)->NewStringUTF(env, name);
	(*env)->CallVoidMethod(env, client_applicationJniObj, mid, js, (jboolean)result);
	
	releaseJniEnv(env, isAttached);
	FUNCTION_EXIT
	UNLOCK
	
	return;
FAIL1:
	releaseJniEnv(env, isAttached);
FAIL0:
	FUNCTION_EXIT
	UNLOCK
	return;
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_CREATE_ROOM
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_CreateRoom(JNIEnv *env, jobject jobj, jstring javastringName, jstring javastringExtension)
{
	char name[VIDYO_CLIENT_PRIVATE_SOAP_USERNAME_SIZE];
	char extension[VIDYO_CLIENT_PRIVATE_SOAP_EXTENSION_SIZE];
	
	FUNCTION_ENTRY
	if (javaString2Buffer(env, javastringName, name, VIDYO_CLIENT_PRIVATE_SOAP_USERNAME_SIZE))
		if (javaString2Buffer(env, javastringExtension, extension, VIDYO_CLIENT_PRIVATE_SOAP_EXTENSION_SIZE))
		{
			doCreateRoom(name,extension);
			RoomCreatedCallbackToJava_(name,VIDYO_TRUE);
		}
		else
		{
			RoomCreatedCallbackToJava_(name,VIDYO_FALSE);
		}
	
	FUNCTION_EXIT
}

static void RoomDestroyedCallbackToJava_(const char *name, VidyoBool result)
{
	VidyoBool isAttached;
	JNIEnv *env;
	jmethodID mid;
	jstring js;
	
	
	FUNCTION_ENTRY
	LOCK
	env = getJniEnv(&isAttached);
	if (env == NULL)
		goto FAIL0;
	
	mid = getApplicationJniMethodId(env, client_applicationJniObj, "roomDestroyed", "(Ljava/lang/String;Z)V");
	if (mid == NULL)
		goto FAIL1;
	
	js = (*env)->NewStringUTF(env, name);
	(*env)->CallVoidMethod(env, client_applicationJniObj, mid, js, (jboolean)result);
	
	releaseJniEnv(env, isAttached);
	LOGE("AppGuiRoomDestroyed End");
	UNLOCK
	FUNCTION_EXIT
	return;
FAIL1:
	releaseJniEnv(env, isAttached);
FAIL0:
	FUNCTION_EXIT
	UNLOCK
	return;
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_DELETE_ROOM
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_DestroyRoom(JNIEnv *env, jobject jobj, jobject room)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, room, NULL))
	{
		doDestroyRoom(&accountData);
		RoomDestroyedCallbackToJava_(accountData.displayName,VIDYO_TRUE);
	}
	else {
		RoomDestroyedCallbackToJava_(accountData.displayName,VIDYO_FALSE);
		
	}
	
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_FROM_MY_CONTACTS
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_RemoveContact(JNIEnv *env, jobject jobj, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		doRemoveContact(&accountData);
	}
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_ADD_TO_MY_CONTACTS
JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_AddContact(JNIEnv *env, jobject jobj, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	jboolean retVal = VIDYO_FALSE;
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		retVal = doAddContact(&accountData);
	}
	
	FUNCTION_EXIT
	return retVal;
}


//return true if application jni construct construct was called successfully
static VidyoBool alreadyConstructed()
{
	// TODO: Needs to be changed to handle case where certain objects are now defined or available
	if (client_applicationJniObj != 0 && portalEntityObj != 0 && attendeeEntityObj != 0 && webProxyEntityObj !=0)
		return VIDYO_TRUE;
	return 	VIDYO_FALSE;
}

static void doGetSelfAccountData(JNIEnv *env, jobject *ptr2SelfAccountEntry)
{
	jobject newSelfEntry;
	jclass peClass = NULL;
	
	if(!alreadyConstructed())
		return;
	//get class object
	if( (peClass = (*env)->GetObjectClass(env, portalEntityObj)) == NULL)
	{
		LOGE("GetSelfAccountData: PortalEntity not found");
		(*env)->ExceptionDescribe(env);
		//FUNCTION_EXIT
		return;
	}
	
	VidyoClientPrivateRequestSelfAccountData requestConfig;
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_SELF_ACCOUNT_DATA, &requestConfig, sizeof(VidyoClientPrivateRequestSelfAccountData), 0);
	
	if (requestConfig.dataValid)
	{
		const char* entityID = &(requestConfig.data.entityID[0]);
		const char* displayName = &(requestConfig.data.displayName[0]);
		const char* extension = &(requestConfig.data.extension[0]);
		const char* tenant = &(requestConfig.data.tenant[0]);
		const char* email = &(requestConfig.data.emailAddress[0]);
		const char* roomURL;
		const char* roomPIN;
		
		setClassString(env, peClass, ptr2SelfAccountEntry, "setDisplayName", displayName);
		setClassString(env, peClass, ptr2SelfAccountEntry, "setExtension", extension);
		setClassString(env, peClass, ptr2SelfAccountEntry, "setTenant", tenant);
		setClassString(env, peClass, ptr2SelfAccountEntry, "setEmail", email);
		setClassString(env, peClass, ptr2SelfAccountEntry, "setId", entityID);
		
		// Get room information for my entity
		if( setClassString(env, peClass, ptr2SelfAccountEntry, "setRoomUrl", requestConfig.data.roomMode.roomURL))
		{
			if( setClassBool(env, peClass, ptr2SelfAccountEntry, "setHasPin", requestConfig.data.roomMode.hasPIN) )
			{
				if (requestConfig.data.roomMode.hasPIN == VIDYO_TRUE) {
					setClassString(env, peClass, ptr2SelfAccountEntry, "setRoomPin", requestConfig.data.roomMode.roomPIN);
				}
			}
		}
	}
	//	FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetSelfAccountData(JNIEnv *env, jobject jobj, jobject peObject)
{
	doGetSelfAccountData(env, &peObject);
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_CREATE_ROOM_PIN
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetRoomPin(JNIEnv *env, jobject jobj, jobject contact, jstring pin)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, pin))
	{
		doSetRoomPin(&accountData);
	}
	
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_REMOVE_ROOM_PIN
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_ClearRoomPin(JNIEnv *env, jobject jobj, jobject contact)
{
	VidyoClientPrivateSoapAccountData accountData={0};
	FUNCTION_ENTRY
	
	if (convertContactObject2AccountDataStruct(env, &accountData, contact, NULL))
	{
		doClearRoomPin(&accountData);
	}
	
	FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_DisableShareEvents(JNIEnv *env, jobject jobj)
{
	FUNCTION_ENTRY
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_ANDROID_DISABLE_SHARE_EVENTS, NULL, 0, 0);
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_EnableShareEvents(JNIEnv *env, jobject jobj)
{
	FUNCTION_ENTRY
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_ANDROID_ENABLE_SHARE_EVENTS, NULL, 0, 0);
}

// Uses VIDYO_CLIENT_PRIVATE_REQUEST_MOBILE_CYCLE_RENDERER_STATS
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_switchVisibleStats(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY
	doSwitchVisibleStats();
	FUNCTION_EXIT
}

// Uses VIDYO_CLIENT_PRIVATE_REQUEST_MOBILE_SET_LABELS_VISIBILITY
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_setLabelsVisibility(JNIEnv *env, jobject jobj, jboolean visibility)
{
	doSetLabelsVisibility(visibility);
}

// Uses VIDYO_CLIENT_PRIVATE_REQUEST_SET_PIXEL_DENSITY
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_setPixelDensity(JNIEnv *env, jobject jobj, jdouble density)
{
	doSetPixelDensity(density);
}

// Uses VIDYO_CLIENT_PRIVATE_REQUEST_MOBILE_SET_STATS_VISIBILITY
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_setStatsVisibility(JNIEnv *env, jobject jobj, jboolean visibility)
{
	doSetStatsVisibility(visibility);
}

// Uses VIDYO_CLIENT_PRIVATE_SOAP_JOIN_WITH_ROOMKEY
JNIEXPORT jint JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_handleJoinWithRoomKey(JNIEnv *env, jobject jobj,
																					   jstring host, jint port, jstring key, jstring pin)
{
	FUNCTION_ENTRY
	{
		const char *hostC = (*env)->GetStringUTFChars(env, host, NULL);
		const char *keyC = (*env)->GetStringUTFChars(env, key, NULL);
		const char *pinC = (*env)->GetStringUTFChars(env, pin, NULL);
		
		
		
		LOGI("Java_com_vidyo_vidyosample_VidyoSampleApplication_handleJoinWithRoomKey( host %s, port %d, key %s, pint %s) \n", hostC, (int)port, keyC,  pinC);
		doHandleJoinWithRoomkey( hostC,  (int) port,  keyC,   pinC);
		
		
		(*env)->ReleaseStringUTFChars(env,host , hostC);
		(*env)->ReleaseStringUTFChars(env, key, keyC);
		(*env)->ReleaseStringUTFChars(env, pin, pinC);
		
	}
	FUNCTION_EXIT
}


JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_ProcessorHasNeon(JNIEnv * env, jobject thiz)
{
	return AppDeviceProcessorHasNeon(&appDeviceSetup);
}

JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetNumProcessorCores(JNIEnv * env, jobject thiz)
{
	return AppDeviceGetNumLogicalCores(&appDeviceSetup);
}

JNIEXPORT jint JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetEncodedWidth(JNIEnv *env, jobject jobj)
{
	FUNCTION_ENTRY
	int width = AppDeviceGetEncodedWidth(&appDeviceSetup);
	FUNCTION_EXIT
	return width;
}

JNIEXPORT jint JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetEncodedHeight(JNIEnv *env, jobject jobj)
{
	FUNCTION_ENTRY
	int height = AppDeviceGetEncodedHeight(&appDeviceSetup);
	FUNCTION_EXIT
	return height;
}

JNIEXPORT jint JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetEncodedFrameRate(JNIEnv *env, jobject jobj)
{
	FUNCTION_ENTRY
	int frameRate = AppDeviceGetEncodedFrameRate(&appDeviceSetup);
	FUNCTION_EXIT
	return frameRate;
}

JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetEncoderConfiguration(JNIEnv * env, jobject tobj, jboolean direct, jint temporalSpatialTradeoff, jint forcePerf)
{
	return AppDeviceSetEncoderConfiguration(&appDeviceSetup, direct, temporalSpatialTradeoff, forcePerf);
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_EnableStatistics(JNIEnv *env, jobject jobj)
{
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_STATISTICS_ENABLE, NULL,  0, 0);
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_DisableStatistics(JNIEnv *env, jobject jobj)
{
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_STATISTICS_DISABLE, NULL, 0, 0);
}

JNIEXPORT jboolean JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetBandwidthInfo(JNIEnv *env, jobject jobj, jintArray bwArray)
{
	// Get the Bandwidth statistics
	VidyoClientPrivateRequestGetBandwidthInfo bandwidthInfo = {0};
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_BANDWIDTH_INFO, &bandwidthInfo, sizeof(VidyoClientPrivateRequestGetBandwidthInfo), 0);
	
	// Pass these statistics to the Java code
	// initializations, declarations, etc
	jint *c_array;
	jint i = 0;
	
	// get a pointer to the array
	c_array = (*env)->GetIntArrayElements(env, bwArray, NULL);
	
	if (c_array == NULL)
	{
		return 0;
	}
	
	c_array[0] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_TOTAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_AVAIL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_SEND];
	c_array[1] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_VIDEO][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_SEND];
	c_array[2] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_AUDIO][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_SEND];
	c_array[3] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_APP][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_SEND];
	c_array[4] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_TOTAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_SEND];
	
	c_array[5] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_TOTAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_AVAIL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_RECV];
	c_array[6] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_VIDEO][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_RECV];
	c_array[7] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_AUDIO][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_RECV];
	c_array[8] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_APP][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_RECV];
	c_array[9] = bandwidthInfo.rate[VIDYO_CLIENT_PRIVATE_BANDWIDTH_SOURCE_TOTAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_TYPE_ACTUAL][VIDYO_CLIENT_PRIVATE_BANDWIDTH_DIR_RECV];
	
	VidyoRect encodeResolution = {0};
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_VIDEO_ENCODE_RESOLUTION,  &encodeResolution, sizeof(VidyoRect), 0);
   
    c_array[10] = VidyoRectangleGetWidth(&encodeResolution);
    c_array[11] = VidyoRectangleGetHeight(&encodeResolution);
	
	VidyoClientPrivateRequestGetVideoFrameRateInfo videoFrameRateInfo = {0};
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_VIDEO_FRAME_RATE_INFO, &videoFrameRateInfo, sizeof(VidyoClientPrivateRequestGetVideoFrameRateInfo), 0);
	c_array[12] = videoFrameRateInfo.captureFrameRate;
	c_array[13] = videoFrameRateInfo.encodeFrameRate;
	c_array[14] = videoFrameRateInfo.sendFrameRate;
	
	VidyoClientPrivateRequestGetVideoEncoderLayers videoEncoderLayers;
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_VIDEO_ENCODER_LAYERS, &videoEncoderLayers, sizeof(VidyoClientPrivateRequestGetVideoEncoderLayers), 0);
	c_array[15] = videoEncoderLayers.numSLayers;
	c_array[16] = videoEncoderLayers.numTLayers;
	
	unsigned numIFrames = 0;
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_NUM_IFRAMES, &numIFrames, sizeof(unsigned), 0);
	c_array[17] = numIFrames;
	
	unsigned numFirs = 0;
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_NUM_FIRS, &numFirs, sizeof(unsigned), 0);
	c_array[18] = numFirs;
	
	unsigned numNacks = 0;
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_NUM_NACKS, &numNacks, sizeof(unsigned), 0);
	c_array[19] = numNacks;
	
	unsigned mediaRTT = 0;
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_MEDIA_RTT, &mediaRTT, sizeof(unsigned), 0);
	c_array[20] = mediaRTT;
	
	// get and display CPU utilization
	unsigned currentCpuUtil = 0;
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_CURRENT_CPU_UTIL, &currentCpuUtil, sizeof(currentCpuUtil), 0);
	c_array[21] = currentCpuUtil;
	c_array[22] = 1;	// number of CPUs/cores
	c_array[23] = 0;	// CPU1
	c_array[24] = 0;	// CPU2
	c_array[25] = 0;	// CPU3
	c_array[26] = 0;	// CPU4
	
	
	
	(*env)->ReleaseIntArrayElements(env, bwArray, c_array, 0);
	
	return 1;
}

#if 0
VidyoClientPrivateRequestGetRateShaperInfo rateShaperInfo = {0};
VidyoClientPrivateRequestGetAudioStats audioStats;

SendPrivateRequest(gui, VIDYO_CLIENT_PRIVATE_REQUEST_GET_SEND_MAX_KBPS, &sendMaxKbps,  0, 0);
SendPrivateRequest(gui, VIDYO_CLIENT_PRIVATE_REQUEST_GET_RECV_MAX_KBPS, &recvMaxKbps, 0, 0);

SendPrivateRequest(gui, VIDYO_CLIENT_PRIVATE_REQUEST_STATISTICS_DISABLE, NULL,
				   
				   SendPrivateRequest(gui, VIDYO_CLIENT_PRIVATE_REQUEST_STATISTICS_ENABLE, NULL,  0, 0);
				   
				   
				   SendPrivateRequest(gui, VIDYO_CLIENT_PRIVATE_REQUEST_GET_RATE_SHAPER_INFO, &rateShaperInfo, 0, 0);
				   SendPrivateRequest(gui, VIDYO_CLIENT_PRIVATE_REQUEST_GET_AUDIO_STATS, &audioStats, 0, 0);
				   
				   
				   // get and display CPU utilization
				   SendPrivateRequest(gui, VIDYO_CLIENT_PRIVATE_REQUEST_GET_CURRENT_CPU_UTIL, &currentCpuUtil, 0, 0);
				   if (currentCpuUtil >= 0)
{
	(void)_snprintf(cpuString, sizeof(cpuString), "%d%c", currentCpuUtil, '%');
	SetDlgItemTextA(hDlg, IDC_CPU_PERCENT, cpuString);//UNICODE
	// TODO: make color change of progress bar work, which requires disabling
	// use of visual styles
	if (currentCpuUtil > CPU_USAGE_THRESHOLD)
		SendMessage(GetDlgItem(hDlg, IDC_CPU_USAGE), PBM_SETBARCOLOR, 0,
					RGB(255, 0, 0));
	else
		SendMessage(GetDlgItem(hDlg, IDC_CPU_USAGE), PBM_SETBARCOLOR, 0,
					RGB(0, 255, 0));
	SendMessage(GetDlgItem(hDlg, IDC_CPU_USAGE), PBM_SETPOS, currentCpuUtil, 0);
}
#endif
				   
				   
jobjectArray createDeviceArrayFromVidyoClientRequestDevices(JNIEnv *env, VidyoClientRequestDevices* req)
{
	jobjectArray ret = NULL;
	int i;
	int listsize = req->numberDevices;
	
	
	if (listsize > 0 && listsize <= MAX_DEVICE_NUMBER)
	{
		LOGI("createDeviceArrayFromVidyoClientRequestDevices size %d first element %s",listsize, req->deviceInfo[0].name);
		
		ret= (jobjectArray)(*env)->NewObjectArray(env, listsize,
												  (*env)->FindClass(env,"java/lang/String"),
												  (*env)->NewStringUTF(env, ""));
        if (ret != NULL)
        	for(i= 0; i<listsize; i++)
        		(*env)->SetObjectArrayElement(env, ret,i,(*env)->NewStringUTF(env, req->deviceInfo[i].name));
	}else
		LOGI("createDeviceArrayFromVidyoClientRequestDevices: bad list size: %d",listsize);
	
	return ret;
}
				   
jintArray createCameraLocationArrayFromVidyoClientRequestDevices(JNIEnv *env, VidyoClientRequestDevices* req)
{
	jintArray ret = NULL;
	int i;
	int listsize = req->numberDevices;
	
	if (listsize > 0 && listsize <= MAX_DEVICE_NUMBER)
	{
		
		ret= (jobjectArray)(*env)->NewIntArray(env, listsize);
        if (ret != NULL){
       		jint fill[256];
        	for(i= 0; i<listsize; i++)
        		fill[i]=(jint)req->deviceInfo[i].location;
			
        	(*env)->SetIntArrayRegion(env, ret, 0, listsize, fill);
        }
	}else
		LOGI("createCameraLocationArrayFromVidyoClientRequestDevices: bad list size: %d",listsize);
	
	return ret;
}

jobject CreateConfigInfoObjectFromRequestDevices(JNIEnv *env,VidyoClientRequestDevices *microphones, VidyoClientRequestDevices* cameras, VidyoClientRequestDevices* speakers)
{
	jclass ciClass = NULL;
	jmethodID realConstructor=NULL;
	jmethodID mSetAllFields = NULL;
	jobject configInfo = NULL;
	jobjectArray mics = NULL;
	jobjectArray cams = NULL;
	jobjectArray spks = NULL;
	jintArray CamsLocs = NULL;
	FUNCTION_ENTRY
	
	//create new ConfigInfo
	ciClass = (*env)->GetObjectClass(env, configInfoObj);
	if (ciClass == NULL) {
		LOGE("CreateConfigInfoObjectFromConfigurationRequest: ConfigInfo not found");
		(*env)->ExceptionDescribe(env);
		goto ciBadExit;
	}
	
	if ((realConstructor = (*env)->GetMethodID(env, ciClass, "<init>", "()V")) == NULL) {
		LOGE("CreateConfigInfoObjectFromConfigurationRequest: NULL real constructor for ConfigInfo");
		(*env)->ExceptionDescribe(env);
		goto ciBadExit;
	}
	
	configInfo = (jobject)(*env)->NewObject(env, ciClass, realConstructor);
	if (!configInfo) {
		LOGE("CreateConfigInfoObjectFromConfigurationRequest: NULL ConfigInfo object");
		(*env)->ExceptionDescribe(env);
		goto ciBadExit;
	}
	
	mSetAllFields = (*env)->GetMethodID(env, ciClass, "setAllFields", "([Ljava/lang/String;I[Ljava/lang/String;I[Ljava/lang/String;I[I)V");
	if(mSetAllFields == NULL){
		LOGE("CreateConfigInfoObjectFromConfigurationRequest: setAllFields not found");
		(*env)->ExceptionDescribe(env);
		goto ciBadExit;
	}
	
	mics = createDeviceArrayFromVidyoClientRequestDevices(env, microphones);
	cams = createDeviceArrayFromVidyoClientRequestDevices(env, cameras);
	CamsLocs = createCameraLocationArrayFromVidyoClientRequestDevices(env, cameras);
	spks = createDeviceArrayFromVidyoClientRequestDevices(env, speakers);
	
	//set microphones
	//set current mic
	//set cameras
	//set current cam
	//set speakers
	//set current speaker
	
	//	(*env)->CallVoidMethod(env, configInfo, mSetAllFields, mics, req->currentMicrophone, spks, req->currentSpeaker, cams, req->currentSpeaker);
	(*env)->CallVoidMethod(env, configInfo, mSetAllFields, mics, microphones->currentDevice, spks, speakers->currentDevice, cams, cameras->currentDevice, CamsLocs);
	
	//return config
	FUNCTION_EXIT
	return configInfo;
ciBadExit:
	ExceptionDidOccure(env,__FUNCTION__); //clear exception
	FUNCTION_EXIT
	return NULL;
}
				   
JNIEXPORT jobject JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetConfigInfo(JNIEnv *env, jobject jobj)
{
	FUNCTION_ENTRY
	int i;
	VidyoClientRequestConfiguration requestConfig;
	
	VidyoClientRequestDevices cams;
	VidyoClientRequestDevices mics;
	VidyoClientRequestDevices spks;
	
	cams.deviceType = VIDYO_CLIENT_DEVICE_TYPE_VIDEO;
	mics.deviceType = VIDYO_CLIENT_DEVICE_TYPE_AUDIO_IN;
	spks.deviceType = VIDYO_CLIENT_DEVICE_TYPE_AUDIO_OUT;
	
	
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_MOBILE_GET_DEVICES_FROM_MANAGER, &cams, sizeof(cams), 0);
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_MOBILE_GET_DEVICES_FROM_MANAGER, &mics, sizeof(mics), 0);
	GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_MOBILE_GET_DEVICES_FROM_MANAGER, &spks, sizeof(spks), 0);
	
	LOGI("Jni_GetConfigInfo: numberMicrophones %d, numberSpeakers %d, numberCameras %d ", mics.numberDevices, spks.numberDevices, cams.numberDevices);
	for(i=0; i<cams.numberDevices; i++)
		LOGI("Jni_GetConfigInfo: cam[%d]=%s location=%s ", i, cams.deviceInfo[i].name, (cams.deviceInfo[i].location == 0)?"front":"back");
	
	
	// 	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &requestConfig, sizeof(VidyoClientRequestConfiguration));
	//
	// 	LOGI("Jni_GetConfigInfo: numberMicrophones %d, numberSpeakers %d, numberCameras %d", requestConfig.numberMicrophones, requestConfig.numberSpeakers, requestConfig.numberCameras);
	FUNCTION_EXIT
	return CreateConfigInfoObjectFromRequestDevices(env, &mics, &cams, &spks);
	//	return CreateConfigInfoObjectFromConfigurationRequest(env, &requestConfig);
}
				   
JNIEXPORT jint JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetVideoCapabilitiesCount(JNIEnv *env, jobject jobj)
{
	FUNCTION_ENTRY
	int i;
	int j;
	int retCount = 0;
	
	VidyoClientPrivateRequestGetVideoCaptureCapabilities videoCaps;
	
	for (i=0; i<2; i++) {
		videoCaps.device = i;
		if (GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_VIDEO_CAPTURE_CAPABILITIES, &videoCaps, sizeof(videoCaps), 0) == VIDYO_CLIENT_ERROR_OK)
		{
			if (videoCaps.capsCount > retCount)
				retCount = videoCaps.capsCount;
			
			for (j=0; j<videoCaps.capsCount; j++) {
				LOGI("Jni_GetVideoCaps[%d]: cap[%d] %dw x %dh minFrameRate=%d", i,
					 videoCaps.caps[j].preference,
					 videoCaps.caps[j].width,
					 videoCaps.caps[j].height,
					 videoCaps.caps[j].minFrameRate);
			}
		}
	}
	FUNCTION_EXIT
	return retCount;
}









jobject CreateVideoCapsObject(JNIEnv *env, VidyoClientPrivateRequestGetVideoCaptureCapabilities *inVideoCaps)
{
	jclass vcClass = NULL;
	jmethodID realConstructor=NULL;
	jmethodID mSetNumCaps = NULL;
	jmethodID mSetCaps = NULL;
	jmethodID mSetFrontCamera = NULL;
	jobject outVideoCaps = NULL;
	int i;
	FUNCTION_ENTRY

	//create new VideoCapability
	vcClass = (*env)->GetObjectClass(env, videoCapsObj);
	if (vcClass == NULL) {
		LOGE("CreateVideoCapsObject: videoCapsObj not found");
		(*env)->ExceptionDescribe(env);
		goto vcBadExit;
	}

	if ((realConstructor = (*env)->GetMethodID(env, vcClass, "<init>", "(III)V")) == NULL) {
		LOGE("CreateVideoCapsObject: NULL real constructor for VideoCapabilities");
		(*env)->ExceptionDescribe(env);
		goto vcBadExit;
	}

	outVideoCaps = (jobject)(*env)->NewObject(env, vcClass, realConstructor,
						  VIDYO_CLIENT_VIDEO_PREFERENCES_LIMITED_BANDWIDTH,
						  VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_450p30,
						  VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_RESOLUTION);
	if (!outVideoCaps) {
		LOGE("CreateVideoCapsObject: NULL VideoCapabilities object");
		(*env)->ExceptionDescribe(env);
		goto vcBadExit;
	}

	mSetFrontCamera = (*env)->GetMethodID(env, vcClass, "setFrontCamera", "(Z)V");
	if(mSetFrontCamera == NULL){
		LOGE("CreateVideoCapsObject: setFrontCamera not found");
		(*env)->ExceptionDescribe(env);
		goto vcBadExit;
	}
	(*env)->CallVoidMethod(env, outVideoCaps, mSetFrontCamera, (jboolean)(inVideoCaps->isFrontCamera));

	mSetNumCaps = (*env)->GetMethodID(env, vcClass, "setNumberCapabilities", "(I)V");
	if(mSetNumCaps == NULL){
		LOGE("CreateVideoCapsObject: setAllFields not found");
		(*env)->ExceptionDescribe(env);
		goto vcBadExit;
	}
	(*env)->CallVoidMethod(env, outVideoCaps, mSetNumCaps, inVideoCaps->capsCount);

	mSetCaps = (*env)->GetMethodID(env, vcClass, "setCapability", "(IIIII)V");
	if(mSetCaps == NULL){
		LOGE("CreateVideoCapsObject: setCapability not found");
		(*env)->ExceptionDescribe(env);
		goto vcBadExit;
	}

	for (i=0; i<inVideoCaps->capsCount; i++)
	{
		LOGI("CreateVideoCapsObject: cap[%d] %dw x %dh minFrameRate=%d, pref=%d", i,
				inVideoCaps->caps[i].width,
				inVideoCaps->caps[i].height,
				inVideoCaps->caps[i].minFrameRate,
				inVideoCaps->caps[i].preference);

		(*env)->CallVoidMethod(env, outVideoCaps, mSetCaps, i, inVideoCaps->caps[i].width, inVideoCaps->caps[i].height,
						inVideoCaps->caps[i].minFrameRate, (int)inVideoCaps->caps[i].preference);
	}

	//return videoCaps
	FUNCTION_EXIT
	return outVideoCaps;
vcBadExit:
	ExceptionDidOccure(env,__FUNCTION__); //clear exception
	FUNCTION_EXIT
	return NULL;
}


JNIEXPORT jobject JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_GetVideoCapabilities(JNIEnv *env, jobject jobj, jint deviceNumber)
{
	FUNCTION_ENTRY
	int i;
	int j;
	int retCount = 0;
	jobject retObject;

	VidyoClientPrivateRequestGetVideoCaptureCapabilities videoCaps;

	videoCaps.device = deviceNumber;
	if (GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_GET_VIDEO_CAPTURE_CAPABILITIES, &videoCaps, sizeof(videoCaps), 0) == VIDYO_CLIENT_ERROR_OK)
	{
		LOGI("GetVideoCapabilities: got capability for deviceNumber=%d", deviceNumber);

		retObject = CreateVideoCapsObject(env, &videoCaps);
	} else {
		retObject = NULL;
	}
	FUNCTION_EXIT

	return retObject;
}

				   
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_vidyoLog(JNIEnv *env, jobject jobj, jstring tag, jstring message)
{
	FUNCTION_ENTRY
	{
		const char *tagC = (*env)->GetStringUTFChars(env, tag, NULL);
		const char *messageC = (*env)->GetStringUTFChars(env, message, NULL);
		
		LOGI("%s: %s", tagC, messageC);
		
		(*env)->ReleaseStringUTFChars(env, tag, tagC);
		(*env)->ReleaseStringUTFChars(env, message, messageC);
	}
	FUNCTION_EXIT
}


// GET ACTIVE SHARES
JNIEXPORT jstring Java_com_vidyo_vidyosample_VidyoSampleApplication_GetMyPID(JNIEnv* env, jobject javaThis) {
	// FUNCTION_ENTRY;
    	VidyoClientRequestGetPid requestParticipantID;
    	char myPID[MAX_PID_SIZE];

    	// Note:  along the application, a correlation is checked between my (this client) pid and the items in the list returned by
    	// VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES.

    	// shares.shareList.remoteAppUri[i] returns this form:
    	// scip:CsAPI1367950084-14a18-ee9de70b4f89c5fa-e920430f9383fff0;transport=TCP

    	// VIDYO_CLIENT_REQUEST_GET_PID return this form:
    	// CsAPI1367950084-14a18-ee9de70b4f89c5fa-e920430f9383fff0

    	// so we add scip:<pid>;transport=TCP
    	char returnedPID[MAX_PID_SIZE+20];

		if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PID, &requestParticipantID, sizeof(VidyoClientRequestGetPid)) == VIDYO_CLIENT_ERROR_OK)
    	{
    		strcpy(myPID, requestParticipantID.PID);
    		sprintf(returnedPID, "scip:%s;transport=TCP", myPID);
      	}

    	return (*env)->NewStringUTF(env, returnedPID);

    	// FUNCTION_EXIT;
}

// GET ACTIVE SHARES
JNIEXPORT jobjectArray Java_com_vidyo_vidyosample_VidyoSampleApplication_GetActiveShares(JNIEnv* env, jobject javaThis) {
	// FUNCTION_ENTRY;
    VidyoClientRequestWindowShares shares = {LIST_SHARING_WINDOWS};
    VidyoUint status;

    // shares.requestType = LIST_SHARING_WINDOWS;
    // shares.requestType = ADD_SHARING_WINDOW;

    // LOGI("sending: VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES");
    status = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, (void*) &shares, sizeof(VidyoClientRequestWindowShares));

    if (status != VIDYO_CLIENT_ERROR_OK)
	{
	    LOGE("\n sending VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES failed");
	}

	jobjectArray retArray;
	retArray = (jobjectArray) (*env)->NewObjectArray(
			env, shares.shareList.numApp, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));

	int i;

	/*
	LOGI("\n-----------------------  C  CODE  -----------------------------------");
	for(i=1; i<shares.shareList.numApp+1; i++) {
   	    LOGI("\nPIDEBUG remoteAppUri[%d] %s" , i, shares.shareList.remoteAppUri[i]);
    	LOGI("\nPIDEBUG remoteAppName[%d] %s" , i, shares.shareList.remoteAppName[i]);
	}
*/

	for(i=1; i<(shares.shareList.numApp)+1; i++) {

   	    // LOGI("\nPID remoteAppUri[%d] %s" , i, shares.shareList.remoteAppUri[i]);
    	// LOGI("\nPID remoteAppName[%d] %s" , i, shares.shareList.remoteAppName[i]);

        char participantIds[MAX_PID_SIZE*2];  // to store remoteAppUri and remoteAppName[i]
 		sprintf(participantIds, "%s:%s", shares.shareList.remoteAppUri[i], shares.shareList.remoteAppName[i]);
		(*env)->SetObjectArrayElement(env, retArray,i-1,(*env)->NewStringUTF(env, participantIds));
	}

	return retArray;

	// FUNCTION_EXIT;
}

JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_StartShare(JNIEnv* env, jobject javaThis) {
	//FUNCTION_ENTRY;
    // LOGI("\n ----------------------  Start Share ----------------------");
	VidyoClientInEventShare shareInfo;
	memset(&shareInfo, 0, sizeof(shareInfo));
	VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SHARE, &shareInfo, sizeof(shareInfo));
    //FUNCTION_EXIT;
}

JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_StopShare(JNIEnv* env, jobject javaThis) {
	//FUNCTION_ENTRY;
    VidyoClientInEventShare shareInfo;
    memset(&shareInfo, 0, sizeof(shareInfo));
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_UNSHARE, &shareInfo, sizeof(shareInfo));
    //FUNCTION_EXIT;
}

/*
JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_SignInUsingUrlString(
		JNIEnv* env, jobject javaThis, jobject samlEntityObject) {

	//FUNCTION_ENTRY;
	jclass peClass;
	VidyoClientInEventSignIn signInParams = {0};

	peClass = (*env)->GetObjectClass(env, samlEntityObject);
	if (peClass == NULL) {
		LOGE("ConstructFromJavaObject: No class SamlEntity");
		return VIDYO_FALSE;
	}
	if (!getClassString(env, samlEntityObject, peClass, "getVmIdentity", signInParams->vmIdentity, VIDYO_MANAGER_ID_SIZE))
	{
		LOGE("ConstructFromJavaObject: getVmIdentity failed");
		return VIDYO_FALSE;
	}

}
*/

JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_SendShareFrame(
		JNIEnv* env, jobject javaThis, jbyteArray frameByteArray, jint width, jint height) {

	//FUNCTION_ENTRY;
    unsigned char *ARGBdata = NULL;
    ARGBdata = (unsigned char *) (*env)->GetByteArrayElements(env, frameByteArray, NULL);

    unsigned int frameSize = width * height * 4;

    // REPLACE RED WITH BLUE (see more comments in receiving frame function which dows the same
    // before calling the Android Java size
    // this code is duplicated !#$ unify
    /* if we do BGRA then add this back
    int i;
    unsigned char c;
    for(i=0; i<frameSize-4; i=i+4) {
   	 c = (unsigned) ARGBdata[i];
   	ARGBdata[i] = ARGBdata[i+2];
   	ARGBdata[i+2] = c;
    }
    */

    VidyoClientInEventVideoFrame* vidyoFrame = (VidyoClientInEventVideoFrame*) malloc(sizeof(VidyoClientInEventVideoFrame)+frameSize);
    memset(vidyoFrame, 0, sizeof(VidyoClientInEventVideoFrame));
    memcpy(vidyoFrame->data, ARGBdata, frameSize);

//    vidyoFrame->format = 1111970369; // this was taken from ios code... didn't verify yet what it represents, this is BGRA
    vidyoFrame->format = AppDeviceMediaFormat(JNI_MEDIA_FORMAT_RGBA);

    vidyoFrame->width = width;
    vidyoFrame->height = height;
    vidyoFrame->size = frameSize;

    if (vidyoFrame) {
    	GuiSendPrivateEvent(VIDYO_CLIENT_IN_EVENT_SEND_FRAME, vidyoFrame, sizeof(VidyoClientInEventVideoFrame) + vidyoFrame->size);
    	free(vidyoFrame);
    	vidyoFrame = NULL;
    }

    (*env)->ReleaseByteArrayElements(env, frameByteArray, ARGBdata, 0);

    // FUNCTION_EXIT;
}

static VidyoClientMediaSource lastSource =
 	    	              { "", VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO, 0};


JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_StartWatch(JNIEnv* env, jobject javaThis, jstring jparticipantId) {
     // FUNCTION_ENTRY;
     // LOGI("\n ----------------------   Start Watch ------------------------------------");
     // !@# DEBUG  currently we work with one and only share

     VidyoClientRequestWindowShares shares = {LIST_SHARING_WINDOWS};
     VidyoUint error;
     error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, (void*) &shares, sizeof(VidyoClientRequestWindowShares));

 	 // pull the last share added (at index 1)
 	 if (error != VIDYO_CLIENT_ERROR_OK)
 	    {
 	    	LOGE("\nsending VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES failed");
 	    } else {
 	    	const char *participantId = (*env)->GetStringUTFChars(env, jparticipantId, NULL);

 	    	// Watch
 	    	static VidyoClientInEventStartWatchVideoSource watchSource;
 	    	VidyoClientInEventShare shareInfo;

 	    	// strcpy(lastSource.participantURI, shares.shareList.remoteAppUri[1]);
 	    	strcpy(lastSource.participantURI, participantId);


 	    	VidyoClientMediaControlType mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_APPLICATION;
 	    	lastSource.mediaType = mediaType;

 	    	watchSource.source = lastSource;
 	    	watchSource.width = 640;
 	    	watchSource.height = 360;
 	    	// watchSource.frameRate = 15; // orig
 	    	watchSource.frameRate = 2;  // was 3. trying to avoid "out of memory"
 	    	watchSource.minFrameInterval = 160;
 	    	watchSource.watchData = NULL;

 	    	GuiSendPrivateEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &watchSource, sizeof(watchSource));

 	    	//memset(&shareInfo, 0, sizeof(shareInfo));
			//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SHARE, &shareInfo, sizeof(shareInfo));
 	    }

 	 // FUNCTION_EXIT;
}


JNIEXPORT jstring Java_com_vidyo_vidyosample_VidyoSampleApplication_StopWatch(JNIEnv* env, jobject javaThis, jstring jparticipantId) {
     //FUNCTION_ENTRY;
     // LOGI("\n ----------------------   Stop Watch ------------------------------------");
     const char *participantId = (*env)->GetStringUTFChars(env, jparticipantId, NULL);

     strcpy(lastSource.participantURI, participantId);
     GuiSendPrivateEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE, &lastSource, sizeof(lastSource));
     //FUNCTION_EXIT;
}

typedef unsigned long Color32;

inline Color32 Color32Reverse(Color32 x)
{
    return
    // Source is in format: 0xAARRGGBB
        ((x & 0xFF000000) >> 24) | //______AA
        ((x & 0x00FF0000) >>  8) | //____RR__
        ((x & 0x0000FF00) <<  8) | //__GG____
        ((x & 0x000000FF) << 24);  //BB______
    // Return value is in format:  0xBBGGRRAA
}

// FRAME RECEIVED
void eventGotFrameReceived(VidyoClientInEventVideoFrame *frame, const char *participantURI)
{
    int width;
    int height;
    void *data;

     jboolean isAttached;
     JNIEnv *env;
     jmethodID mid;

     width = frame->width;
     height = frame->height;
     data = frame->data;

     //LOGI("FRAME RECEIVED - width: %d  hight %d participant: %s", width, height, participantURI);


     env = getJniEnv(&isAttached);
     if (env == NULL)
	     goto FAIL0;

     // Note: II is used in the signature for simple int width and height (note that I;I;... is used for full Class like Integer
     mid = getApplicationJniMethodId(env, client_applicationJniObj, "frameReveivedCallback", "(IILjava/lang/String;Ljava/lang/Object;)V");

     if (mid == NULL)
             goto FAIL1;

     long size = width * height * 4;

     // It appeared that bitmap in android is generated were RED is switched with BLUE
     // this loop replaces the 1st and 3rd byte in the pixel to put RED and BLUE in place
     // to avoid this processing - an option that server

     unsigned char* dataChar = (unsigned char*) data;
     int i;

     // Convert to RGBA format
     LOGI("VIDYO_CLIENT_PRIVATE_OUT_EVENT_FRAME_RECEIVED format=%x", frame->format);
    if (frame->format == AppDeviceMediaFormat(JNI_MEDIA_FORMAT_RGBA)) {
	     LOGI("VIDYO_CLIENT_PRIVATE_OUT_EVENT_FRAME_RECEIVED format=RGBA");
    } else if (frame->format == AppDeviceMediaFormat(JNI_MEDIA_FORMAT_ARGB)) {
	     LOGI("VIDYO_CLIENT_PRIVATE_OUT_EVENT_FRAME_RECEIVED format=ARGB");
	     //TODO: Fix the performance, Color32Reverse() does not seem to work
/*	     Color32* dataInt = (Color32*) data;
	     for (i=0; i<size/4; i++) {
		     dataInt[i] = Color32Reverse(dataInt[i]);
	     }
*/
	     for(i=0; i<size-4; i=i+4) {
		 unsigned char r, g, b, a;
	    	 a = (unsigned) dataChar[i];
	    	 r = (unsigned) dataChar[i+1];
	    	 g = (unsigned) dataChar[i+2];
	    	 b = (unsigned) dataChar[i+3];
	    	 dataChar[i] = r;
	    	 dataChar[i+1] = g;
	    	 dataChar[i+2] = b;
	    	 dataChar[i+3] = a;
	     }
    } else if (frame->format == AppDeviceMediaFormat(JNI_MEDIA_FORMAT_BGRA)) {
	     LOGI("VIDYO_CLIENT_PRIVATE_OUT_EVENT_FRAME_RECEIVED format=BGRA");
	     for(i=0; i<size-4; i=i+4) {
		 unsigned char c;
	    	 c = (unsigned) dataChar[i];
	    	 dataChar[i] = dataChar[i+3];
	    	 dataChar[i+3] = c;
	    	 c = (unsigned) dataChar[i+1];
	    	 dataChar[i+1] = dataChar[i+2];
	    	 dataChar[i+2] = c;
	     }
     } else {
	     LOGI("VIDYO_CLIENT_PRIVATE_OUT_EVENT_FRAME_RECEIVED format=not sure");
     }


     //fill the buffer
     jbyteArray jBuff = (*env)->NewByteArray(env, size);
     (*env)->SetByteArrayRegion(env, jBuff, 0, size, (jbyte*) dataChar);

     // call JNI method
     jstring returnURI = (*env)->NewStringUTF(env, participantURI);
     (*env)->CallVoidMethod(env, client_applicationJniObj, mid, width, height, returnURI, jBuff);

     releaseJniEnv(env, isAttached);

    // LOGI("localFrameReceived End");

    return;

    FAIL1:
	     releaseJniEnv(env, isAttached);
    FAIL0:
	    LOGE("localFrameReceived FAILED");
    
}

/*
//   EVENT GOT - REMOVE SHARE
void eventGotAddOrRemoveShare(const int eventType, const char *shareURI)
{
    jboolean isAttached;
    JNIEnv *env;
    jmethodID mid;

    env = getJniEnv(&isAttached);
    if (env == NULL)
        goto FAIL0;

    mid = getApplicationJniMethodId(env, client_applicationJniObj, "addOrRemoveShareCallback", "(ILjava/lang/String;)V");
    if (mid == NULL)
        goto FAIL1;

    jstring returnURI = (*env)->NewStringUTF(env, shareURI);
    (*env)->CallVoidMethod(env, client_applicationJniObj, mid, eventType, returnURI);

    releaseJniEnv(env, isAttached);
    return;
FAIL1:
    releaseJniEnv(env, isAttached);
FAIL0:
    LOGE("removeShareCallback FAILED");
    return;
}
*/


