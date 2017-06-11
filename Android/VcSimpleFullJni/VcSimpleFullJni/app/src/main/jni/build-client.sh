#!/bin/bash
WORKDIR="$( cd "$( dirname "$0" )/.." && pwd )"
export MAIN_DIR=$(cd "$WORKDIR/../../.." && pwd)
cd "$WORKDIR"
export SAMPLES_DIR=$MAIN_DIR/Samples
export SDK_DIR=$MAIN_DIR/SDK
export FRAMEWORKS_DIR=$MAIN_DIR/Frameworks

set -e

echo "WORKDIR=$WORKDIR"
echo "MAIN_DIR=$MAIN_DIR"

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

ANDROID_TARGET=android-19


#
# Handle some SDK tool issues between SDK tool versions
#
if [[ ! -e "ant.properties" ]]
then
    cp build.properties ant.properties
fi
if [[ ! -e "project.properties" ]]
then
    cp default.properties project.properties
fi

android update project --target $ANDROID_TARGET --path .

#read -p "Press any key…"
if test $# -gt 0 -a "$1" = "clean"
then
	ndk-build NDK_APPLICATION_MK=./jni/Application.mk clean
	ant clean
else
	if test $# -gt 0 -a "$1" = "release"
	then
		# HACK: work around missing dependency in ndk makefiles, breaks -j8
		mkdir -p libs/armeabi-v7a
		ndk-build NDK_APPLICATION_MK=./jni/Application.mk NDE_DEBUG=0 -j8
#		ant release
	else
		# HACK: work around missing dependency in ndk makefiles, breaks -j8
		mkdir -p libs/armeabi-v7a
		ndk-build NDK_APPLICATION_MK=./jni/Application.mk NDE_DEBUG=1 -j8
#		ant debug
	fi
fi
