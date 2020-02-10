#!/usr/bin/env bash
# ndk r11 is used
# reference $NDK_ROOT/build/core/build-local.mk

ndk-build NDK_PROJECT_PATH=. NDK_LIBS_OUT=./app/src/main/jniLibs NDK_APPLICATION_MK=app/src/main/jni/Application.mk APP_BUILD_SCRIPT=app/src/main/jni/Android.mk