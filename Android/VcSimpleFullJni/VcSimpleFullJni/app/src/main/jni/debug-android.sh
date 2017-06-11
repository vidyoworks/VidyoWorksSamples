#!/bin/bash
WORKDIR="$( cd "$( dirname "$0" )/.." && pwd )"
export MAIN_DIR=$(cd "$WORKDIR/../../../.." && pwd)
cd "$WORKDIR"
export SAMPLES_DIR=$MAIN_DIR/Samples
export SDK_DIR=$MAIN_DIR/SDK
export FRAMEWORKS_DIR=$MAIN_DIR/Frameworks

set -e

if test -z "`type -t ndk-gdb`"
then
	echo "Executable 'ndk-gdb' not found in PATH" 1>&2
	exit 1
fi

GNUMAKE="make NDK_APPLICATION_MK=jni/Application.mk" ndk-gdb "$@"
