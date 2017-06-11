#!/bin/bash
if [ -z "$1" ]
then
    echo "paramter unspeified"
    echo "usage ./deploy.sh Bundlename"
    exit
fi

VC_LIB_PATH=VidyoClient/lib/mac
VD_APP_PATH=./$1.app
pushd $VC_LIB_PATH
install_name_tool -id @rpath/Frameworks/VidyoClientDll.dylib VidyoClientDll.dylib
popd
mkdir -p $VD_APP_PATH/Contents/Frameworks
cp -v $VC_LIB_PATH/VidyoClientDll.dylib $VD_APP_PATH/Contents/Frameworks
pushd $VD_APP_PATH/Contents/MacOS
install_name_tool -change /usr/local/lib/VidyoClientDll.dylib @rpath/Frameworks/VidyoClientDll.dylib $1
install_name_tool -add_rpath @loader_path/.. $1
popd
echo "Deployed Shared lib"
