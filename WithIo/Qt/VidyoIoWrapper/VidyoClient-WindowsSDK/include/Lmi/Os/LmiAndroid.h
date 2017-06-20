/**
{file:
	{name: LmiAndroid.h}
	{description: Registers global Android objects.}
	{copyright:
		(c) 2011-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.

		All rights reserved.

		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.
				  ***** CONFIDENTIAL *****
	}
}
*/
#ifndef LMI_LMIANDROID_H
#define LMI_LMIANDROID_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiMutex.h>

LMI_BEGIN_EXTERN_C

LmiBool LmiAndroidInitialize(void);
void LmiAndroidUninitialize(void);

#if ANDROID
#include <jni.h>
#else /* ANDROID */
typedef LmiInt JavaVM;
typedef LmiInt JNIEnv;
typedef LmiVoidPtr jobject;
typedef LmiInt jclass;
typedef LmiVoidPtr jmethodID;
typedef LmiVoidPtr jfieldID;
#endif /* ANDROID */

/*
{function:
	{name: LmiAndroidRegisterDefaultVM}
	{parent: LmiAndroid}
	{description: Registers the default Android Virtual Machine pointer that will be used for JNI calls.}
	{prototype: void LmiAndroidRegisterDefaultVM(JavaVM *vm)}
	{parameter: {name: vm} {description: A pointer to the Java Virtual Machine.}}
	{note: This function must be called on Android platforms before any SDK functions.}
}
*/
void LmiAndroidRegisterDefaultVM(JavaVM *vm);

/*
{function:
	{name: LmiAndroidUnregisterDefaultVM}
	{parent: LmiAndroid}
	{description: Unregisters the default Android Virtual Machine pointer.}
	{prototype: void LmiAndroidRegisterDefaultVM()}
	{note: This function must be called on Android platforms before resources are released.}
}
*/
void LmiAndroidUnregisterDefaultVM();

/*
{function:
	{name: LmiAndroidGetDefaultVM}
	{parent: LmiAndroid}
	{description: Gets the default Android Virtual Machine pointer.}
	{prototype: JavaVM *LmiAndroidGetDefaultVM()}
	{return: A pointer to the default Android Virtual Machine on success, or NULL on failure.}
}
*/
JavaVM *LmiAndroidGetDefaultVM();

/*
{function:
	{name: LmiAndroidRegisterDefaultApp}
	{parent: LmiAndroid}
	{description: Registers the current Context object that will be used to construct Cameras and Windows.}
	{prototype: void LmiAndroidRegisterDefaultApp(JNIEnv* env, jobject context)}
	{parameter: {name: env} {description: Current JNI environment.}}
	{parameter: {name: context} {description: An android.content.Context Java object.}}
	{note: In most circumstances, the Context will be the application's Activity or Application. Some functions (notably, LmiWindowConstruct, though not LmiWindowConstructChildOfExternal) will require an actual Activity class.}
	{note: This function must be called on Android platforms before
		any SDK DeviceManager or Ui functions.  It may be called again at any time to change the default Context.}
}
*/
void LmiAndroidRegisterDefaultApp(JNIEnv* env, jobject activity);

/*
{function:
	{name: LmiAndroidUnregisterDefaultApp}
	{parent: LmiAndroid}
	{description: Unregisters the current Context object that will be used to construct Cameras and Windows.}
	{prototype: void LmiAndroidUnregisterDefaultApp(JNIEnv* env)}
	{parameter: {name: env} {description: Current JNI environment.}}
	{note: This function must be called on Android platforms for resources to be released.}
}
*/
void LmiAndroidUnregisterDefaultApp(JNIEnv* env);

/*
{function:
	{name: LmiAndroidGetDefaultApp}
	{parent: LmiAndroid}
	{description: Gets the current Context object.}
	{prototype: jobject LmiAndroidGetDefaultApp(jobject context)}
	{return: The default Context object on success, or NULL on failure.}
}
*/
jobject LmiAndroidGetDefaultApp();


/**
{type:
	{name: LmiAndroid}
	{parent: Os}
	{include: Lmi/Os/LmiAndroid.h}
	{description: Stores global state of android applications.}
}
*/

typedef struct LmiAndroid_ {
	JavaVM *vm;
	JNIEnv *env;
	jobject classLoader;
	jmethodID classLoaderLoadClass;
	jmethodID stringReplace;
	LmiBool isAttached;
	LmiMutex lock;
} LmiAndroid;

/**
{function:
	{name: LmiAndroidConstruct}
	{parent: LmiAndroid}
	{description: Constructs a LmiAndroid object that keeps global Android data.}
	{prototype: LmiAndroid *LmiAndroidConstruct(LmiAndroid *a)}
	{parameter: {name: a} {description: The LmiAndroid object.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
	{note: On Android platform, some objects need to be stored globally so that
		they can be accessed by various Android specific SDK components. }
}
*/
LmiAndroid *LmiAndroidConstruct(LmiAndroid *a);

/**
{function:
	{name: LmiAndroidDestruct}
	{parent: LmiAndroid}
	{description: Destructs an LmiAndroid object.}
	{prototype: void LmiAndroidDestruct(LmiAndroid *a)}
	{parameter: {name: a} {description: The LmiAndroid object.}}
}
*/
void LmiAndroidDestruct(LmiAndroid *a);

/*
{function:
	{name: LmiAndroidGetEnv}
	{parent: LmiAndroid}
	{description: Gets a thread local JNIEnv pointer from LmiAndroid object.}
	{prototype: JNIEnv *LmiAndroidGetEnv(LmiAndroid *a)}
	{parameter: {name: a} {description: The LmiAndroid object.}}
	{return: A thread local JNIEnv pointer on success, or NULL on failure.}
	{note: This function call must be followed by a call to LmiAndroidReleaseEnv() and
		the thread calling LmiAndroidGetEnv() should not wait on another thread
		before calling LmiAndroidReleaseEnv(). }
}
*/
JNIEnv *LmiAndroidGetEnv(LmiAndroid *a);

/*
{function:
	{name: LmiAndroidReleaseEnv}
	{parent: LmiAndroid}
	{description: Releases a thread local JNIEnv pointer from LmiAndroid object.}
	{prototype: void LmiAndroidReleaseEnv(LmiAndroid *a)}
	{parameter: {name: a} {description: The LmiAndroid object.}}
	{note: Follow the note on LmiAndroidGetEnv(). }
}
*/
void LmiAndroidReleaseEnv(LmiAndroid *a);
jclass *LmiAndroidGetCacheClassReference(LmiAndroid *a, const char *classPath);
void LmiAndroidReleaseCacheClassReference(LmiAndroid *a, jclass jClass);
jmethodID LmiAndroidGetMethodId(LmiAndroid *a, jclass jClass, const char* methodName, const char* methodSignature);
jmethodID LmiAndroidGetStaticMethodId(LmiAndroid *a, jclass jClass, const char* methodName, const char* methodSignature);
jfieldID LmiAndroidGetFieldId(LmiAndroid *a, jclass jClass, const char* fieldName, const char* fieldSignature);
jfieldID LmiAndroidGetStaticFieldId(LmiAndroid *a, jclass jClass, const char* fieldName, const char* fieldSignature);

LMI_END_EXTERN_C
#endif /* LMI_LMIANDROID_H */
