@echo off
REM  1 - armeabi-v7a
set VIDYO_TYPE_OF_PROCESSOR=armeabi-v7a
echo "step 1 VIDYO_TYPE_OF_PROCESSOR  = %VIDYO_TYPE_OF_PROCESSOR%"
REM remove all older so files other than from where it is supposed to be in
del /S obj\*.so
del /S  app\src\main\jniLibs\*.so
rm -rf obj
rm -rf build
rm -rf app\build
copy/Y app\src\main\jni\lib\%VIDYO_TYPE_OF_PROCESSOR%\libVidyoClientApp.so app\src\main\jni\lib\libVidyoClientApp.so
ndk-build NDK_PROJECT_PATH=. NDK_LIBS_OUT=.\app\src\main\jniLibs NDK_APPLICATION_MK=app\src\main\jni\Application.mk APP_BUILD_SCRIPT=app\src\main\jni\Android.mk

set VIDYO_TYPE_OF_PROCESSOR=arm64-v8a
echo "step 2 VIDYO_TYPE_OF_PROCESSOR  = %VIDYO_TYPE_OF_PROCESSOR%"
#remove all older so files other than from where it is supposed to be in
rm -rf obj
rm -rf build
rm -rf app/build
copy/Y app\src\main\jni\lib\%VIDYO_TYPE_OF_PROCESSOR%\libVidyoClientApp.so app\src\main\jni\lib\libVidyoClientApp.so
ndk-build NDK_PROJECT_PATH=. NDK_LIBS_OUT=./app/src/main/jniLibs NDK_APPLICATION_MK=app/src/main/jni/Application.mk APP_BUILD_SCRIPT=app/src/main/jni/Android.mk

set VIDYO_TYPE_OF_PROCESSOR=

