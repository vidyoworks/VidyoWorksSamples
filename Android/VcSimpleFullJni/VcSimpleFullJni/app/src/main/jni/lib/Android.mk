LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := VidyoClientApp
LOCAL_SRC_FILES := libVidyoClientApp.so

include $(PREBUILT_SHARED_LIBRARY)
