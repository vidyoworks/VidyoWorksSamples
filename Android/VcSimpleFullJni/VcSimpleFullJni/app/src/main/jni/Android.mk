TOP_LOCAL_PATH := $(call my-dir)
include $(call all-subdir-makefiles)
_LOCAL_PATH := $(TOP_LOCAL_PATH)
 
include $(CLEAR_VARS)


_HEAD_PATH:=$(MAIN_DIR)

#
# Current path is (likely) Endpoints/VidyoMobile/Android
#

PRODUCTS_DIR := $(_HEAD_PATH)/Products

LOCAL_PATH := $(_LOCAL_PATH)


CLIENT_DIR:= $(PRODUCTS_DIR)/Client
CLIENTLIB_DIR:=$(CLIENT_DIR)/ClientLib


# To include OpenSSL libraries
OPENSSL_DIR := $(FRAMEWORKS)/Linux/OpenSSL/openssl-1.0.1u-fips-2.0.13/release/arm-android
OPENSSL_INCLUDE_DIR := $(FRAMEWORKS)/Linux/OpenSSL/openssl-1.0.1u-fips-2.0.13/release/arm-android/include
OPENSSL_LIB_DIR := $(FRAMEWORKS)/Linux/OpenSSL/openssl-1.0.1u-fips-2.0.13/release/arm-android/lib


CURL_INCLUDE_DIR := $(FRAMEWORKS)/Android/Curl/curl-7.41.0/include
CURL_LIB_DIR := $(_LOCAL_PATH)

# 
#VIDYO_CLIENT_CFLAGS := -DWITH_CS_TLS_PLUGIN -DVIDYO_ANDROID
# to include OPENSSL FIPS
VIDYO_CLIENT_CFLAGS := -DWITH_CS_TLS_PLUGIN -DVIDYO_ANDROID -DOPENSSL_FIPS -DFIPSMODE


_CURL_LIBFILES := -lcurl -lz

_CLIENT_LDLIBS :=  -L$(TARGET_OUT)

#MY_TLS_LDLIBS := -L$(OPENSSL_LIB_DIR) -lssl -lcrypto -ldl -L$(CURL_LIB_DIR)
MY_TLS_LDLIBS := -L$(OPENSSL_LIB_DIR) -ldl -L$(CURL_LIB_DIR)


# Make Vidyo Client Library
LOCAL_C_INCLUDES :=  $(LOCAL_PATH)/lib/include $(CLIENTLIB_DIR) $(CLIENT_DIR) $(OPENSSL_INCLUDE_DIR) $(CURL_INCLUDE_DIR)

include $(CLEAR_VARS)

LOCAL_MODULE := VidyoMobileApp
LOCAL_PATH := $(_LOCAL_PATH)

# FIPS Modules
#FIPS_SRC_FILES	:= fips_workaround.c
FIPS_SRC_FILES	:= 

VIDYOCLIENT_FILES := TimerDispatch.cpp \
					ndkVidyoSample.c VidyoJni.c VidyoClientJni.c vidyo_consts.cpp LoginLogic.cpp \
					ClientEventDispatch.cpp appDelegate.cpp AppIcons.c \
					ConferenceStateLogic.cpp $(FIPS_SRC_FILES)
LOCAL_SRC_FILES := ContactManager.cpp ClientMyContacts.cpp ClientAllContacts.cpp \
			ClientRooms.cpp ClientContacts.cpp \
			VidyoMobileJni.c RoomParticipants.cpp

LOCAL_C_INCLUDES :=  $(LOCAL_PATH)/lib/include $(CLIENTLIB_DIR) $(CLIENT_DIR) $(OPENSSL_INCLUDE_DIR) $(CURL_INCLUDE_DIR)
LOCAL_CFLAGS := -DLMI_HAVE_LMI_CONFIG_AUTOCONF_H=1 -fno-stack-protector -g $(VIDYO_CLIENT_CFLAGS)
LOCAL_CPPFLAGS := $(LOCAL_CFLAGS)
ifeq ($(TARGET_CLIENTLIB),1)
  LOCAL_LDFLAGS := -Wl,-Map,vidyomobile.map -Wl,--gc-sections -Wl
else
  LOCAL_LDFLAGS := -Wl,-Map,vidyomobile.map -Wl,--gc-sections -Wl,--exclude-libs=ALL
endif
$(warning Value of LOCAL_LDFLAGS is '$(LOCAL_LDFLAGS)')
$(warning Value of LOCAL_C_INCLUDES is '$(LOCAL_C_INCLUDES)')
LOCAL_CPP_FEATURES += exceptions


LOCAL_LDLIBS :=  $(_CLIENT_LDLIBS) \
	$(MY_TLS_LDLIBS) -llog
#earlier line
#$(MY_TLS_LDLIBS) -llog  -lGLESv2

		
LOCAL_SHARED_LIBRARIES := VidyoClientApp
include $(BUILD_SHARED_LIBRARY)

# Android changed the variable defining SYSROOT in NDK r8e
ifdef SYSROOT
ANDROID_SYSROOT := $(SYSROOT)
else ifdef SYSROOT_INC
ANDROID_SYSROOT := $(SYSROOT_INC)
endif


$(LOCAL_BUILT_MODULE) : $(MY_LOCAL_STATIC_LIBRARIES)
