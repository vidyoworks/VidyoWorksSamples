TOP_LOCAL_PATH := $(call my-dir)
include $(call all-subdir-makefiles)
LOCAL_PATH := $(TOP_LOCAL_PATH)
 
include $(CLEAR_VARS)
 
# Here we give our module name and source file(s)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/ $(LOCAL_PATH)/lib/include
LOCAL_SRC_FILES := ndkVidyoSample.c
LOCAL_SHARED_LIBRARIES := VidyoClientApp
LOCAL_LDLIBS = -llog 
LOCAL_MODULE    := ndkVidyoSample
 
include $(BUILD_SHARED_LIBRARY)