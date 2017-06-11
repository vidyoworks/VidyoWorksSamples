/*
 *  VidyoJni.h
 *  Android
 *
 *  Func
 *  Created by Paul.Cushman
 *  Copyright 2014 Vidyo. All rights reserved.
 */


#ifndef __VidyoJni_h__
#define __VidyoJni_h__

#if defined(__cplusplus)
#define VIDYOJNI_BEGIN_EXTERN_C extern "C" {
#define VIDYOJNI_END_EXTERN_C }
#else
#define VIDYOJNI_BEGIN_EXTERN_C
#define VIDYOJNI_END_EXTERN_C
#endif

VIDYOJNI_BEGIN_EXTERN_C

VidyoBool  ExceptionDidOccure(JNIEnv *env, const char* FunctionName);
jmethodID getApplicationJniMethodId(JNIEnv *env, jobject obj, const char* methodName, const char* methodSignature);
JNIEnv *getJniEnv(VidyoBool  *isAttached);
void releaseJniEnv(JNIEnv *env, VidyoBool  isAttached);
jobject * initCacheClassReference(JNIEnv *env, const char *classPath);

VidyoBool  getClassStringIndexed(JNIEnv *env, jobject contact, jclass peClass, char methodName[], char buffer[] ,unsigned bufSize, unsigned index);

VidyoBool  getClassString(JNIEnv *env, jobject contact, jclass peClass, char methodName[], char buffer[] ,unsigned bufSize);
VidyoBool  setClassString(JNIEnv *env, jclass peClass,jobject *peObject, const char* methodName, const char *newValue);

VidyoBool  getClassBool(JNIEnv *env, jobject peObject, jclass peClass, const char* methodName);
VidyoBool  setClassBool(JNIEnv *env, jclass peClass,jobject *peObject, const char* methodName, VidyoBool newValue);

VidyoBool  javaString2Buffer(JNIEnv *env, jstring jString, char buffer[], unsigned bufSize);

VidyoBool  getStaticFieldInt(JNIEnv *env, jclass peClass, const char* fieldName, VidyoInt *fieldValue);

extern JavaVM *global_vm;

#define MAX_CALLBACK_CLASS_NAME_SIZE	128
#define MAX_CALLBACK_NAME_SIZE	128

/*
 * This structure is used to contain information about each of the callbacks.
 */
typedef struct VidyoJniCallbackInfo_
{
	char	*classDef;
	char	name[MAX_CALLBACK_NAME_SIZE];
	VidyoBool 	initialized;
} VidyoJniCallbackInfo;

VIDYOJNI_END_EXTERN_C

#endif //__VidyoJni_h__
