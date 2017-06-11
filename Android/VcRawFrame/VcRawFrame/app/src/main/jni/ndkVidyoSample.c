#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "VidyoClient.h"
#include "include/AndroidDebug.h"
#include <pthread.h>
#include <unistd.h>

jobject applicationJniObj = 0;
JavaVM* global_vm = 0;
static VidyoBool joinStatus = 0;
int xCoordinate;
int yCoordinate;
static VidyoBool allVideoDisabled = 0;

void SampleSwitchCamera(const char *name);
void SampleStartConference();
void SampleEndConference();
void SampleLoginSuccessful();
void LibraryStarted();
void MuteRender(VidyoBool doWeMute);
void ResetWatchedSources();
int FindIndexInWatched(const char* uri);
void FrameReceived(int participantId, int width, int height, const char *rawImageBytes, int size);

#define MAX_WATCH_CAPACITY	4
char watchedList[4][MAX_URI_LEN];

#define LmiFourCC(_a, _b, _c, _d) ( ((unsigned int)(_d)<<24) | ((unsigned int)(_c) << 16) | ((unsigned int)(_b) << 8) | ((unsigned int)(_a)) )
#define LMI_MEDIAFORMAT_I420 LmiFourCC('I', '4', '2', '0')
#define LMI_MEDIAFORMAT_YU12 LmiFourCC('Y', 'U', '1', '2')
#define LMI_MEDIAFORMAT_ARGB LmiFourCC('A', 'R', 'G', 'B')
#define LMI_MEDIAFORMAT_BGRA LmiFourCC('B', 'G', 'R', 'A')

#define FRAME_WIDTH			320
#define FRAME_HEIGHT		180


void SetCoordinates(int x, int y)
{
	LOGI("***** **** ***** set coordinates  width=%d height=%d\n", x, y);
	xCoordinate = x;
	yCoordinate = y;
}

#define NUMBER_OF_CYCLES_WAIT_FOR_RESIZE_RESTORE		5
void * _TryResizeLater(void *val) {
	int i = 0;
	for(i = 0; i < NUMBER_OF_CYCLES_WAIT_FOR_RESIZE_RESTORE; ++i)
	{
		LOGI("***** **** ***** sleeping");
		sleep(1);
	}
	LOGI("***** **** ***** In another thread active Resize width=%d height=%d\n", xCoordinate, yCoordinate);
	doResize(xCoordinate,yCoordinate);
	return NULL;
}


void TryResizeLater()
{
	pthread_t t;

	LOGI("***** **** ***** creating thread");

	//Launch a thread
	pthread_create(&t, NULL, _TryResizeLater, NULL);
}

// Callback for out-events from VidyoClient
#define PRINT_EVENT(X) if(event==X) LOGI("GuiOnOutEvent recieved %s", #X);
void SampleGuiOnOutEvent(VidyoClientOutEvent event,
				   VidyoVoidPtr param,
				   VidyoUint paramSize,
				   VidyoVoidPtr data)
{
	LOGI("GuiOnOutEvent enter Event = %d\n",(int) event);
	if(event == VIDYO_CLIENT_OUT_EVENT_LICENSE)
	{
		VidyoClientOutEventLicense *eventLicense;
		eventLicense = (VidyoClientOutEventLicense *) param;

		VidyoUint error = eventLicense->error;
		VidyoUint vmConnectionPath = eventLicense->vmConnectionPath;
		VidyoBool OutOfLicenses = eventLicense->OutOfLicenses;

		LOGI("License Error: errorid=%d vmConnectionPath=%d OutOfLicense=%d\n", error, vmConnectionPath, OutOfLicenses);
	}
	else if(event == VIDYO_CLIENT_OUT_EVENT_SIGN_IN)
	{
		VidyoClientOutEventSignIn *eventSignIn;
		eventSignIn = (VidyoClientOutEventSignIn *) param;

		VidyoUint activeEid = eventSignIn->activeEid;
		VidyoBool signinSecured = eventSignIn->signinSecured;

		LOGI("activeEid=%d signinSecured=%d\n", activeEid, signinSecured);

		/*
		 * If the EID is not setup, it will return activeEid = 0
		 * in this case, we invoke the license request using below event
		 */
		if(!activeEid)
			(void)VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LICENSE, NULL, 0);
	    VidyoClientRequestCurrentUser user_id;
	    VidyoUint ret = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CURRENT_USER, &user_id, sizeof(user_id));
	    LOGE("SG: logged in with %d. user_id.CurrentUserID: %s, user_id.CurrentUserDisplay: %s .", ret, user_id.currentUserID, user_id.currentUserDisplay);
	}
    else if(event == VIDYO_CLIENT_OUT_EVENT_SIGNED_IN)
	{
        // Send message to Client/application
		SampleLoginSuccessful();
    }
	else if(event == VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE)
	{
		LOGI("Join Conference Event - received VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE\n");
        SampleStartConference();
		joinStatus = 1;
		LOGI("***** **** ***** active Resize width=%d height=%d\n", xCoordinate, yCoordinate);
		doResize(xCoordinate,yCoordinate);
		TryResizeLater(NULL);
	}
	else if(event == VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED)
	{
		LOGI("Left Conference Event\n");
		SampleEndConference();
		joinStatus = 0;
	}
	else if(event == VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL)
	{
		LOGW("VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL\n");
		VidyoBool ret = VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ANSWER, NULL, 0);
		LOGW("SG: VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL %d.", ret);
	}
    /*else if(event == VIDYO_CLIENT_OUT_EVENT_ADD_SHARE)
    {
        VidyoClientRequestWindowShares shareRequest;
        VidyoUint result;

        LOGI("VIDYO_CLIENT_OUT_EVENT_ADD_SHARE\n");
        memset(&shareRequest, 0, sizeof(shareRequest));
        shareRequest.requestType = LIST_SHARING_WINDOWS;
         VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES,
                                              &shareRequest,
                                              sizeof(shareRequest));
        if (result != VIDYO_CLIENT_ERROR_OK)
        {
            LOGE("VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES failed");
        }
        else
        {
            LOGI("VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES success:%d, %d", shareRequest.shareList.numApp, shareRequest.shareList.currApp);

            shareRequest.shareList.newApp = shareRequest.shareList.currApp = 1;
            shareRequest.requestType = ADD_SHARING_WINDOW;
    
            result = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES,
                                              &shareRequest,
                                              sizeof(shareRequest));

            if (result != VIDYO_CLIENT_ERROR_OK)
            {
                LOGE("VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES failed\n");

            }
            else
            {
                LOGI("VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES success\n");
            }
        }
	}*/
	else if (event == VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECTION_CHANGED)
	{
		VidyoClientOutEventDeviceSelectionChanged *eventOutDeviceSelectionChg = (VidyoClientOutEventDeviceSelectionChanged *)param;

		if (eventOutDeviceSelectionChg->changeType == VIDYO_CLIENT_USER_MESSAGE_DEVICE_SELECTION_CHANGED)
		{
			if (eventOutDeviceSelectionChg->deviceType == VIDYO_CLIENT_DEVICE_TYPE_VIDEO) 
			{
				SampleSwitchCamera((char *)eventOutDeviceSelectionChg->newDeviceName);
			}
		}
	}
	else if (event == VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED)
	{
		LOGI("Library Started Event\n");
		LibraryStarted();
	}
	else if (event == VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED)
	{
		VidyoClientOutEventVideoFrameReceived *event = (VidyoClientOutEventVideoFrameReceived*)param;

		int width = event->frame.width;
		int height = event->frame.height;

		char str[MAX_URI_LEN];
		sprintf(str, "%s", event->participantURI);

		int hashParticipantId = FindIndexInWatched(str);
		if(hashParticipantId < 0) {
			LOGI("----------- Participant uri : %s not found", str);
			return;
		}
		LOGI("----------- Participant ID: %d", hashParticipantId);

		VidyoClientMediaControlType format = event->mediaType;
		if (format == VIDYO_CLIENT_MEDIA_CONTROL_TYPE_APPLICATION)
		{
			LOGI("-----------  Share frame received.");
		}
		else if (format == VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO)
		{
			LOGE("-----------  Video frame received.");
			FrameReceived(hashParticipantId, width, height, event->frame.data, event->frame.size);
		}
		else
			LOGE("-----------  strange path");

	}
}

static JNIEnv *getJniEnv(jboolean *isAttached)
{
	int status;
	JNIEnv *env;
	*isAttached = 0;

	status = (*global_vm)->GetEnv(global_vm, (void **) &env, JNI_VERSION_1_4);
	if (status < 0) 
	{
		//LOGE("getJavaEnv: Failed to get Java VM");
		status = (*global_vm)->AttachCurrentThread(global_vm, &env, NULL);
		if(status < 0) 
		{
			LOGE("getJavaEnv: Failed to get Attach Java VM");
			return NULL;
		}
		//LOGE("getJavaEnv: Attaching to Java VM");
		*isAttached = 1;
	}

	return env;
}

static jmethodID getApplicationJniMethodId(JNIEnv *env, jobject obj, const char* methodName, const char* methodSignature)
{
	jmethodID mid;
	jclass appClass;

	appClass = (*env)->GetObjectClass(env, obj);
	if (!appClass) 
	{
		LOGE("getApplicationJniMethodId - getApplicationJniMethodId: Failed to get applicationJni obj class");
		return NULL;
	}
	
	mid = (*env)->GetMethodID(env, appClass, methodName, methodSignature);
	if (mid == NULL)
	{
		LOGE("getApplicationJniMethodId - getApplicationJniMethodId: Failed to get %s method", methodName);
		return NULL;
	}
	
	return mid;
}

void LibraryStarted()
{
	jboolean isAttached;
	JNIEnv *env;
	jmethodID mid;
	jstring js;
	LOGE("LibraryStarted Begin");
	env = getJniEnv(&isAttached);
	if (env == NULL)
		goto FAIL0;

	mid = getApplicationJniMethodId(env, applicationJniObj, "libraryStartedCallback", "()V");
	if (mid == NULL)
		goto FAIL1;

	(*env)->CallVoidMethod(env, applicationJniObj, mid);

	if (isAttached)
	{
		(*global_vm)->DetachCurrentThread(global_vm);
	}
	LOGE("LibraryStarted End");
	return;
	FAIL1:
	if (isAttached)
	{
		(*global_vm)->DetachCurrentThread(global_vm);
	}
	FAIL0:
	LOGE("LibraryStarted FAILED");
	return;
}

void SampleStartConference()
{
    jboolean isAttached;
    JNIEnv *env;
    jmethodID mid;
    jstring js;
    LOGE("SampleStartConference Begin");
    env = getJniEnv(&isAttached);
    if (env == NULL)
        goto FAIL0;
    
    mid = getApplicationJniMethodId(env, applicationJniObj, "callStartedCallback", "()V");
    if (mid == NULL)
        goto FAIL1;
    
    (*env)->CallVoidMethod(env, applicationJniObj, mid);
	
    if (isAttached)
    {
        (*global_vm)->DetachCurrentThread(global_vm);
    }
    LOGE("SampleStartConference End");
    return;
FAIL1:
    if (isAttached)
    {
        (*global_vm)->DetachCurrentThread(global_vm);
    }
FAIL0:
    LOGE("SampleStartConference FAILED");
    return;
}

void SampleLoginSuccessful()
{
    jboolean isAttached;
    JNIEnv *env;
    jmethodID mid;
    jstring js;
    LOGE("SampleLoginSuccessful Begin");
    env = getJniEnv(&isAttached);
    if (env == NULL)
        goto FAIL0;
    
    mid = getApplicationJniMethodId(env, applicationJniObj, "loginSuccessfulCallback", "()V");
    if (mid == NULL)
        goto FAIL1;
    
    (*env)->CallVoidMethod(env, applicationJniObj, mid);
	
    if (isAttached)
    {
        (*global_vm)->DetachCurrentThread(global_vm);
    }
    LOGE("SampleLoginSuccessful End");
    return;
FAIL1:
    if (isAttached)
    {
        (*global_vm)->DetachCurrentThread(global_vm);
    }
FAIL0:
    LOGE("SampleLoginSuccessful FAILED");
    return;
}

void SampleEndConference()
{
        jboolean isAttached;
        JNIEnv *env;
        jmethodID mid;
        jstring js;
        LOGE("SampleEndConference Begin");
        env = getJniEnv(&isAttached);
        if (env == NULL)
                goto FAIL0;

        mid = getApplicationJniMethodId(env, applicationJniObj, "callEndedCallback", "()V");
        if (mid == NULL)
                goto FAIL1;

        (*env)->CallVoidMethod(env, applicationJniObj, mid);
	
		if (isAttached)
		{
			(*global_vm)->DetachCurrentThread(global_vm);
		}
        LOGE("SampleEndConference End");
        return;
FAIL1:
		if (isAttached)
		{
			(*global_vm)->DetachCurrentThread(global_vm);
		}
FAIL0:
        LOGE("SampleEndConference FAILED");
        return;
}

void SampleSwitchCamera(const char *name)
{
        jboolean isAttached;
        JNIEnv *env;
        jmethodID mid;
        jstring js;
        LOGE("SampleSwitchCamera Begin");
        env = getJniEnv(&isAttached);
        if (env == NULL)
                goto FAIL0;

        mid = getApplicationJniMethodId(env, applicationJniObj, "cameraSwitchCallback", "(Ljava/lang/String;)V");
        if (mid == NULL)
                goto FAIL1;

        js = (*env)->NewStringUTF(env, name);
        (*env)->CallVoidMethod(env, applicationJniObj, mid, js);
	
		if (isAttached)
		{
			(*global_vm)->DetachCurrentThread(global_vm);
		}
        LOGE("SampleSwitchCamera End");
        return;
FAIL1:
		if (isAttached)
		{
			(*global_vm)->DetachCurrentThread(global_vm);
		}
FAIL0:
        LOGE("SampleSwitchCamera FAILED");
        return;
}

static jobject * SampleInitCacheClassReference(JNIEnv *env, const char *classPath) 
{
	jclass appClass = (*env)->FindClass(env, classPath);
	if (!appClass) 
	{
		LOGE("cacheClassReference: Failed to find class %s", classPath);
		return ((jobject*)0);
	}
	
	jmethodID mid = (*env)->GetMethodID(env, appClass, "<init>", "()V");
	if (!mid) 
	{
		LOGE("cacheClassReference: Failed to construct %s", classPath);
		return ((jobject*)0);
	}
	jobject obj = (*env)->NewObject(env, appClass, mid);
	if (!obj) 
	{
		LOGE("cacheClassReference: Failed to create object %s", classPath);
		return ((jobject*)0);
	}
	return (*env)->NewGlobalRef(env, obj);
}


void doSetLogLevelsAndCategories(char* newLogging)
{
    if (newLogging != NULL)
    {
        if (strlen(newLogging) > 199)
        {
            LOGE("New logging string too long!");
        }
        else
        {
           
            LOGE("Log String set to %s\n", newLogging);
            
            
            VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_LOG_LEVELS_AND_CATEGORIES, newLogging, sizeof(newLogging));
        }
    }
  
}

JNIEXPORT jboolean Java_com_vidyo_vidyosample_VidyoSampleApplication_Construct(JNIEnv* env, jobject javaThis,
                jstring caFilename, jstring logDir, jstring pathDir, jstring uniqueId, jobject defaultActivity) {

	FUNCTION_ENTRY;
    
    
    VidyoClientAndroidRegisterDefaultVM(global_vm);
    VidyoClientAndroidRegisterDefaultApp(env, defaultActivity);
    
    const char *pathDirC = (*env)->GetStringUTFChars(env, pathDir, NULL);
    const char *logDirC = (*env)->GetStringUTFChars(env, logDir, NULL);
	const char *certificatesFileNameC = (*env)->GetStringUTFChars(env, caFilename, NULL);
	const char *uniqueIdC = (*env)->GetStringUTFChars(env, uniqueId, NULL);
	VidyoBool returnValue = VIDYO_FALSE;
	

 	//const char *logBaseFileName = "VidyoClientSample_";
 	//const char *installedDirPath = NULL;
 	//static const VidyoUint DEFAULT_LOG_SIZE = 1000000;
	//const char *logLevelsAndCategories = "fatal error warning debug@App info@AppEmcpClient debug@LmiApp debug@AppGui info@AppGui";
	VidyoRect videoRect = {(VidyoInt)(0), (VidyoInt)(0), (VidyoUint)(100), (VidyoUint)(100)};
    //VidyoUint logSize = DEFAULT_LOG_SIZE;

	applicationJniObj = SampleInitCacheClassReference(env, "com/vidyo/vidyosample/VidyoSampleApplication");
	// This will start logging to LogCat
    // Use mainly for debugging purposes
	VidyoClientConsoleLogConfigure(VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_ALL);

	// Start the VidyoClient Library
    
    /* VidyoBool returnValue = VidyoClientStart(SampleGuiOnOutEvent,
     NULL,
     "/data/data/com.vidyo.vidyosample/cache/",
     logBaseFileName,
     "/data/data/com.vidyo.vidyosample/files/",
     logLevelsAndCategories,
     logSize,
     (VidyoWindowId)(0),
     &videoRect,
     NULL,
     &profileParam,NULL);
     if (returnValue)
*/
    VidyoClientLogParams logParam = {0};
    logParam.logLevelsAndCategories = "fatal error warning debug@App info@AppEmcpClient debug@LmiApp debug@AppGui info@AppGui";
    logParam.logSize = 5000000;
//    logParam.pathToLogDir = "/data/data/com.vidyo.vidyosample/cache/";
    logParam.pathToLogDir = logDirC;
    logParam.logBaseFileName = "VidyoClientSample_";
//    logParam.pathToDumpDir = "/data/data/com.vidyo.vidyosample/files/";
    logParam.pathToDumpDir = logDirC;
    logParam.pathToConfigDir = pathDirC;
    
    VidyoClientInitialize(SampleGuiOnOutEvent, NULL, &logParam);

	void AndroidClientSetMachineID(const char* id);
	AndroidClientSetMachineID(uniqueIdC);

	LOGE("ApplicationJni_Construct: certifcateFileName=%s, configDir=%s, logDir=%s!\n", certificatesFileNameC, pathDirC, logDirC);


	returnValue = VidyoClientStart(SampleGuiOnOutEvent,
                                             NULL,
                                             &logParam,
											 (VidyoWindowId)(0),
											 &videoRect,
											 NULL,
											 NULL,
                                             VIDYO_FALSE);
	if (returnValue)
	{
		LOGI("VidyoClientStart() was a SUCCESS\n");
	}
	else
	{
		//start failed
		LOGE("ApplicationJni_Construct VidyoClientStart() returned error!\n");
	}

	AppCertificateStoreInitialize(logDirC,certificatesFileNameC,NULL);
    char test[]="fatal error warning debug@App info@AppEmcpClient debug@LmiApp debug@AppGui info@AppGui debug@LmiUi";
    doSetLogLevelsAndCategories(test);
	ResetWatchedSources();
	FUNCTION_EXIT;
	return (jboolean)returnValue;
}

JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_Login(JNIEnv* env, jobject javaThis,
		jstring vidyoportalName, jstring userName, jstring passwordName) {

	FUNCTION_ENTRY;
	LOGI("Java_com_vidyo_vidyosample_VidyoSampleApplication_Login() enter\n");

	const char *portalC = (*env)->GetStringUTFChars(env, vidyoportalName, NULL);
	const char *usernameC = (*env)->GetStringUTFChars(env, userName, NULL);
	const char *passwordC = (*env)->GetStringUTFChars(env, passwordName, NULL);

	LOGI("Starting Login Process\n");
	VidyoClientInEventLogIn event = {0};

	strlcpy(event.portalUri, portalC, sizeof(event.portalUri));
	strlcpy(event.userName, usernameC, sizeof(event.userName));
	strlcpy(event.userPass, passwordC, sizeof(event.userPass));

	LOGI("logging in with portalUri %s user %s ", event.portalUri, event.userName);
    
	VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LOGIN, &event, sizeof(VidyoClientInEventLogIn));
 	FUNCTION_EXIT;
}


JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_JoinRoomLink(JNIEnv* env, jobject javaThis,
                                                                       jstring vidyoportalName, jstring key, jstring displayName, jstring pin) {
    
    FUNCTION_ENTRY;
    LOGI("Java_com_vidyo_vidyosample_VidyoSampleApplication_JoinRoomLink() enter\n");
    
    //since this is a raw frame sample
    //we will mute default rendering
    MuteRender(VIDYO_TRUE);
    
    const char *portalC = (*env)->GetStringUTFChars(env, vidyoportalName, NULL);
    const char *keyC = (*env)->GetStringUTFChars(env, key, NULL);
    const char *displayNameC = (*env)->GetStringUTFChars(env, displayName, NULL);
    const char *pinC = (*env)->GetStringUTFChars(env, pin, NULL);
    
    LOGI("Starting JoinRoomLink Process\n");
    
    VidyoClientInEventRoomLink event = {0};
    
    strlcpy(event.portalUri, portalC, sizeof(event.portalUri));
    strlcpy(event.roomKey, keyC, sizeof(event.roomKey));
    strlcpy(event.displayName, displayNameC, sizeof(event.displayName));
    strlcpy(event.pin, pinC, sizeof(event.pin));
    
    LOGI("joiningRoomlink with portalUri %s key %s ", event.portalUri, event.roomKey);
    
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ROOM_LINK, &event, sizeof(VidyoClientInEventRoomLink));
    FUNCTION_EXIT;
}


JNIEXPORT void Java_com_vidyo_vidyosample_VidyoSampleApplication_ConferenceEnd(JNIEnv* env, jobject javaThis) {
    
    FUNCTION_ENTRY;
    LOGI("Java_com_vidyo_vidyosample_VidyoSampleApplication_ConferenceEnd() enter\n");
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LEAVE,NULL, 0);
    FUNCTION_EXIT;
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_Dispose(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY;
	if (VidyoClientStop())
		LOGI("VidyoClientStop() SUCCESS!!\n");
        
	else
		LOGE("VidyoClientStop() FAILURE!!\n");

	FUNCTION_EXIT;
}


JNIEXPORT jint JNICALL JNI_OnLoad( JavaVM *vm, void *pvt )
{
	FUNCTION_ENTRY;
	LOGI("JNI_OnLoad called\n");
	global_vm = vm;
	FUNCTION_EXIT;
	return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_OnUnload( JavaVM *vm, void *pvt )
{
	FUNCTION_ENTRY
	LOGE("JNI_OnUnload called\n");
	FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_Render(JNIEnv *env, jobject jObj2)
{
//	FUNCTION_ENTRY;
	doRender();
//	FUNCTION_EXIT;
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_RenderRelease(JNIEnv *env, jobject jObj2)
{
	FUNCTION_ENTRY;
	doSceneReset();
	FUNCTION_EXIT;
}

 void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_Resize(JNIEnv *env, jobject jobj, jint width, jint height)
{
	FUNCTION_ENTRY;
	LOGI("***** **** ***** JNI Resize width=%d height=%d\n", width, height);
	SetCoordinates(width, height);
	doResize( (VidyoUint)width, (VidyoUint)height);
	FUNCTION_EXIT;
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_TouchEvent(JNIEnv *env, jobject jobj, jint id, jint type, jint x, jint y)
{
	FUNCTION_ENTRY;
	doTouchEvent((VidyoInt)id, (VidyoInt)type, (VidyoInt)x, (VidyoInt)y);
	FUNCTION_EXIT;
}


JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetOrientation(JNIEnv *env, jobject jobj,  jint orientation)
{
FUNCTION_ENTRY;

        VidyoClientOrientation newOrientation = VIDYO_CLIENT_ORIENTATION_UP;

        //translate LMI orienation to client orientation
        switch(orientation) {
                case 0: newOrientation = VIDYO_CLIENT_ORIENTATION_UP;
                                LOGI("VIDYO_CLIENT_ORIENTATION_UP");
                                break;
                case 1: newOrientation = VIDYO_CLIENT_ORIENTATION_DOWN;
                        LOGI("VIDYO_CLIENT_ORIENTATION_DOWN");
                        break;
                case 2: newOrientation = VIDYO_CLIENT_ORIENTATION_LEFT;
                        LOGI("VIDYO_CLIENT_ORIENTATION_LEFT");
                        break;
                case 3: newOrientation = VIDYO_CLIENT_ORIENTATION_RIGHT;
                        LOGI("VIDYO_CLIENT_ORIENTATION_RIGHT");
                        break;
        }

        doClientSetOrientation(newOrientation);

FUNCTION_EXIT;
return;
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetCameraDevice(JNIEnv *env, jobject jobj, jint camera)
{
	// FUNCTION_ENTRY
	VidyoClientRequestConfiguration requestConfig;
	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &requestConfig, sizeof(VidyoClientRequestConfiguration));

	/*
	 * Value of 0 is (currently) used to signify the front camera
	 */
	if (camera == 0)
	{
		requestConfig.currentCamera = 0;
	}
	/*
	 * Value of 1 is (currently) used to signify the back camera
	 */
	else if (camera == 1)
	{
		requestConfig.currentCamera = 1;
	}
	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &requestConfig, sizeof(VidyoClientRequestConfiguration));

        //FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_DisableAutoLogin(JNIEnv *env, jobject jobj)
{
	//FUNCTION_ENTRY
	VidyoClientRequestConfiguration requestConfig;
	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &requestConfig, sizeof(VidyoClientRequestConfiguration));
	requestConfig.enableAutoLogIn = 0;
	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &requestConfig, sizeof(VidyoClientRequestConfiguration));
	//FUNCTION_EXIT
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetPreviewModeON(JNIEnv *env, jobject jobj, jboolean pip)
{
	VidyoClientInEventPreview event;
	if (pip)
		event.previewMode = VIDYO_CLIENT_PREVIEW_MODE_DOCK;
	else
		event.previewMode = VIDYO_CLIENT_PREVIEW_MODE_NONE;
	VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PREVIEW, &event, sizeof(VidyoClientInEventPreview));
}

void _init()
{
	FUNCTION_ENTRY;
	LOGE("_init called\n");
	FUNCTION_EXIT;
}

void _fini()
{
	FUNCTION_ENTRY;
	LOGE("_fini called\n");
	FUNCTION_EXIT;
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_DisableAllVideoStreams(JNIEnv *env, jobject jobj)
{
    if (!allVideoDisabled)
    {
        //this would have the effect of stopping all video streams but self preview
        
        VidyoClientRequestSetBackground reqBackground = {0};
        reqBackground.willBackground = VIDYO_TRUE;
        (void)VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_BACKGROUND,
                                     &reqBackground, sizeof(reqBackground));
        
        allVideoDisabled = VIDYO_TRUE;
    }
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_EnableAllVideoStreams(JNIEnv *env, jobject jobj)
{
	{
		if (allVideoDisabled)
		{
            VidyoClientRequestSetBackground reqBackground = {0};
			reqBackground.willBackground = VIDYO_FALSE;
            (void)VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_BACKGROUND,
                                         &reqBackground, sizeof(reqBackground));
            
			//this would have the effect of enabling all video streams 
			allVideoDisabled = VIDYO_FALSE;
//			rearrangeSceneLayout();
		}	
	}
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_MuteCamera(JNIEnv *env, jobject jobj, jboolean MuteCamera)
{
	VidyoClientInEventMute event;
	event.willMute = MuteCamera;
	VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO, &event, sizeof(VidyoClientInEventMute));
}

void MuteRender(VidyoBool doWeMute)
{
    VidyoClientInEventMute event;
    LOGI("MuteRender enter\n");
    event.willMute = doWeMute;
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_DEFAULT_RENDERING, &event, sizeof(VidyoClientInEventMute));
    LOGI("MuteRender exit\n");
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_StartConferenceMedia(JNIEnv *env, jobject jobj)
{
    doStartConferenceMedia();
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_HideToolBar(JNIEnv* env, jobject jobj, jboolean disablebar)
{
	LOGI("Java_com_vidyo_vidyosample_VidyoSampleApplication_HideToolBar() enter\n");
    VidyoClientInEventEnable event;
    event.willEnable = VIDYO_TRUE;
    VidyoBool ret = VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ENABLE_BUTTON_BAR, &event,sizeof(VidyoClientInEventEnable));
    if (!ret)
        LOGW("Java_com_vidyo_vidyosample_VidyoSampleApplication_HideToolBar() failed!\n");
}

// this function will enable echo cancellation
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetEchoCancellation(JNIEnv *env, jobject jobj, jboolean aecenable)
{
	// get persistent configuration values
	  VidyoClientRequestConfiguration requestConfiguration;

	  VidyoUint ret = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &requestConfiguration,
	                                                                             sizeof(requestConfiguration));
	  if (ret != VIDYO_CLIENT_ERROR_OK) {
	          LOGE("VIDYO_CLIENT_REQUEST_GET_CONFIGURATION returned error!");
	          return;
	  }

	  // modify persistent configuration values, based on current values of on-screen controls
	  if (aecenable) {
	          requestConfiguration.enableEchoCancellation = 1;
	  } else {
	          requestConfiguration.enableEchoCancellation = 0;
	  }

	  // set persistent configuration values
	  ret = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &requestConfiguration,
	                                                           sizeof(requestConfiguration));
	  if (ret != VIDYO_CLIENT_ERROR_OK) {
	          LOGE("VIDYO_CLIENT_REQUEST_SET_CONFIGURATION returned error!");
	  }
	}
JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_SetSpeakerVolume(JNIEnv *env, jobject jobj, jint volume)
{
	//FUNCTION ENTRY
	VidyoClientRequestVolume volumeRequest;
	volumeRequest.volume = volume;
	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_OUT, &volumeRequest,
		                                                           sizeof(volumeRequest));
	//FUNCTION EXIT
	return;
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_DisableShareEvents(JNIEnv *env, jobject javaThisj)
{
	FUNCTION_ENTRY
	VidyoClientSendEvent (VIDYO_CLIENT_IN_EVENT_DISABLE_SHARE_EVENTS, 0, 0);
	LOGI("Disable Shares Called - Vimal");
	FUNCTION_EXIT;
}

void ResetWatchedSources()
{
	memset(&watchedList, 0, sizeof(watchedList));
}

int FindIndexInWatched(const char* uri)
{
	int result = -1;
	int index;
	if (strlen(uri) == 0)
		return result;
	for(index = 0; index < MAX_WATCH_CAPACITY; ++index)
	{
		if (strlen(watchedList[index]) == 0)
			continue;
		if(strcmp(uri, watchedList[index]) == 0)
			return index;
	}
	return result;

}

void ClearWatchedSources()
{
	int index = 0;
	LOGI("Entering ClearWatchedSources");
	VidyoClientInEventStopWatchVideoSource stopWatch;
	
	for( index = 0; index < MAX_WATCH_CAPACITY; ++index)
	{
		 if (strlen(watchedList[index]) == 0)
			 continue;
		strcpy(stopWatch.source.participantURI, watchedList[index]);
		stopWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
		LOGI("Removing from watch = %s", stopWatch.source.participantURI);
		VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE, &stopWatch, sizeof(stopWatch));		
	}
	
	ResetWatchedSources();
	LOGI("Entering complete");
}

void AddSources(int maxWatch)
{
	VidyoClientRequestParticipants reqParticipants;
	VidyoClientInEventStartWatchVideoSource watchSource;
	int index = 0;

	LOGI("Entering AddSources");
	
	if(maxWatch > MAX_WATCH_CAPACITY)
		maxWatch = MAX_WATCH_CAPACITY;
	
	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants));
	if(maxWatch > reqParticipants.numberParticipants)
		maxWatch = reqParticipants.numberParticipants;
	for( index = 0; index < maxWatch; ++index)
	{
		strcpy(watchSource.source.participantURI, reqParticipants.URI[index]);
		watchSource.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
		watchSource.source.sourceId = 0;
		watchSource.frameRate = 15;
		watchSource.height = FRAME_HEIGHT;
		watchSource.width = FRAME_WIDTH;
		watchSource.minFrameInterval = 0;
		watchSource.watchData = NULL;
		LOGI("******** ****** Adding to watch = %s", watchSource.source.participantURI);
		VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &watchSource, sizeof(watchSource));		
	}

	for( index = 0; index < maxWatch; ++index)
	{
		strcpy(watchedList[index], reqParticipants.URI[index]);
	}
	LOGI("exiting AddSources");
}

void FrameReceived(int participantId, int width, int height, const char *rawImageBytes, int size)
{
	LOGE(".... **** ....FrameReceived Begin");
	LOGI("%d", size);

	jboolean isAttached;
	JNIEnv *env;
	jmethodID mid;
	jint jParticipant;
	jint jWidth;
	jint jHeight;
	jbyteArray jRawImageBytes;

	env = getJniEnv(&isAttached);

	if (env == NULL)
		goto FAIL0;

	mid = getApplicationJniMethodId(env, applicationJniObj, "vidyoConferenceFrameReceivedCallback", "(III[B)V");

	if (mid == NULL)
		goto FAIL1;

	jWidth = width;
	jHeight = height;

	jParticipant = participantId;
	LOGI("jParticipant: %d", jParticipant);

	jRawImageBytes = (*env)->NewByteArray(env, size);
	(*env)->SetByteArrayRegion(env, jRawImageBytes, 0, size, rawImageBytes);

	(*env)->CallVoidMethod(env, applicationJniObj, mid, jParticipant, jWidth, jHeight, jRawImageBytes);

	if (isAttached)
	{
		(*global_vm)->DetachCurrentThread(global_vm);
	}
	LOGE("FrameReceived End");
	return;
	FAIL1:
	if (isAttached)
	{
		(*global_vm)->DetachCurrentThread(global_vm);
	}
	FAIL0:
	LOGE("FrameReceived FAILED");
	return;
}


void SetWatchFormat()
{
	VidyoClientRequestEventSetWatchVideoFormat watch;

	LOGI("Setting watch format");
	watch.format = LMI_MEDIAFORMAT_YU12;
	//If VidyoClient version is 3.4.4.0200 or greater use LMI_MEDIAFORMAT_BGRA
    //unless you use this format, colors wont come correctly
    //however, this format exists only in 3.4.4.0200
    //therefore anything LMI_MEDIAFORMAT_BGRA earlier it will fail.
    watch.format = LMI_MEDIAFORMAT_YU12;
    //watch.format = LMI_MEDIAFORMAT_BGRA;
	VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT, &watch, sizeof(watch));

	LOGI("******** ****** watch format complete");
}

JNIEXPORT void JNICALL Java_com_vidyo_vidyosample_VidyoSampleApplication_RefreshWatchList(JNIEnv *env, jobject javaThis, jint maxWatch)
{
	LOGI("Java_com_vidyo_vidyosample_VidyoSampleApplication_RefreshWatchList() enter\n");
	FUNCTION_ENTRY
	SetWatchFormat();
	ClearWatchedSources();
	AddSources((int)maxWatch);	
	FUNCTION_EXIT;
}
