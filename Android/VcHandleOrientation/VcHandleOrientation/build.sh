#!/usr/bin/env bash
# ndk r11 is used
# reference $NDK_ROOT/build/core/build-local.mk
rm -rf app/src/main/jniLibs/armeabi-v7a/lib*
rm -rf obj
ndk-build NDK_PROJECT_PATH=. NDK_LIBS_OUT=./app/src/main/jniLibs NDK_APPLICATION_MK=app/src/main/jni/Application.mk APP_BUILD_SCRIPT=app/src/main/jni/Android.mk
