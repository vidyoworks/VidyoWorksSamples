APP_PROJECT_PATH := $(call my-dir)/..
APP_BUILD_SCRIPT := $(APP_PROJECT_PATH)/jni/Android.mk
#APP_OPTIM := debug
APP_OPTIM := release
APP_ABI := $(VIDYO_TYPE_OF_PROCESSOR)
APP_STL := gnustl_static