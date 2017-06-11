#!/usr/bin/env bash
ndk-build NDK_PROJECT_PATH=. NDK_LIBS_OUT=./app/src/main/jniLibs NDK_APPLICATION_MK=app/src/main/jni/Application.mk APP_BUILD_SCRIPT=app/src/main/jni/Android.mk clean
