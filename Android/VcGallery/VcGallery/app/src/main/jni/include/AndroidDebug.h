/*
 *  AndroidDebug.h
 *  Android
 *
 *  Created by raz.galili on 6/2/11.
 *  Copyright 2011 Vidyo. All rights reserved.
 *
 */

#ifndef __AndroidDebug_h__
#define __AndroidDebug_h__
#include <jni.h>
#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "VidyoMobile "__FILE__
#endif 

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)

#define FUNCTION_ENTRY	LOGI("%s ENTRY\n",__PRETTY_FUNCTION__);
#define FUNCTION_EXIT	LOGI("%s EXIT\n" ,__PRETTY_FUNCTION__);
#define IMPLEMENT_ME	LOGI("%s CALLED, please implement me\n" ,__PRETTY_FUNCTION__);
#define BEEN_HERE LOGI("reached %s %d",__FILE__, __LINE__);

#define entry_exit_LOG(funcName,line,printAtTntry,PrintAtExit) struct funcName##line{funcName##line(){ LOGI printAtTntry;} ~funcName##line(){ LOGI PrintAtExit;}} funcName##line##_inst;
#define FUNCTION_ENTRY_EXIT entry_exit_LOG(__FUNCTION__,__LINE__, ("%s ENTRY\n",__PRETTY_FUNCTION__), ("%s EXIT\n" ,__PRETTY_FUNCTION__));


#endif //__AndroidDebug_h__
