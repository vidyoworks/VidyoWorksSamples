#!/usr/bin/env bash
# ndk r11 is used
# reference $NDK_ROOT/build/core/build-local.mk
#stage 1 - armeabi-v7a
export VIDYO_TYPE_OF_PROCESSOR=armeabi-v7a
echo "step 1 VIDYO_TYPE_OF_PROCESSOR  = $VIDYO_TYPE_OF_PROCESSOR"
#remove all older so files other than from where it is supposed to be in
find obj -iname "*.so" -exec rm -R {} \;
find app/src/main/jniLibs -iname "*.so" -exec rm -R {} \;
rm -rf obj
rm -rf build
rm -rf app/build
ndk-build NDK_PROJECT_PATH=. NDK_LIBS_OUT=./app/src/main/jniLibs NDK_APPLICATION_MK=app/src/main/jni/Application.mk APP_BUILD_SCRIPT=app/src/main/jni/Android.mk

export VIDYO_TYPE_OF_PROCESSOR=arm64-v8a
echo "step 2 VIDYO_TYPE_OF_PROCESSOR  = $VIDYO_TYPE_OF_PROCESSOR"
#remove all older so files other than from where it is supposed to be in
rm -rf obj
rm -rf build
rm -rf app/build
ndk-build NDK_PROJECT_PATH=. NDK_LIBS_OUT=./app/src/main/jniLibs NDK_APPLICATION_MK=app/src/main/jni/Application.mk APP_BUILD_SCRIPT=app/src/main/jni/Android.mk
