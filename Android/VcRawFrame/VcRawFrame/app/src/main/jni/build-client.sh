#!/bin/bash
set -e

if test -z "`type -t android`"
then
	echo "Executable 'android' not found in PATH" 1>&2
	exit 1
fi

if test -z "`type -t ndk-build`"
then
	echo "Executable 'ndk-build' not found in PATH" 1>&2
	exit 1
fi

if test -z "`type -t ant`"
then
	echo "Executable 'ant' not found in PATH" 1>&2
	exit 1
fi

ANDROID_TARGET=android-17

android update project --target $ANDROID_TARGET --path .

#read -p "Press any key…"
if test $# -gt 0 -a "$1" = "clean"
then
	ndk-build NDK_APPLICATION_MK=./jni/Application.mk clean
	ant clean
else
	if test $# -gt 0 -a "$1" = "release"
	then
		mkdir -p libs/armeabi-v7a
		ndk-build NDK_APPLICATION_MK=./jni/Application.mk NDE_DEBUG=0 -j8
		ant release
	else
		mkdir -p libs/armeabi-v7a
		ndk-build NDK_APPLICATION_MK=./jni/Application.mk NDE_DEBUG=1 -j8
		ant debug
	fi
fi
