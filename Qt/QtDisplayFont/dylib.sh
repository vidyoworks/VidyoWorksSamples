if [ -z "$1" ]
then
	echo "This script updates the bundle with a shared lib"
    echo "It needs source location where dylib is and where app bundle is"
	echo "usage ./dylib.sh <pathtodylib> <pathtoappBundle> <BUNDLENAME>"
    echo "usage ./dylib.sh /pathtodylib /pathtoappBundle NAME"
	echo "./dylib.sh ~/src/TAGS/ApiSamples/3x/Qt/QtDisplayFont/VidyoClient/lib/mac ~/src/TAGS/ApiSamples/3x/Qt/build-QtDisplayFont-Qt48-Debug/QtDisplayFont.app QtDisplayFont"
    exit
fi

if [ -z "$2" ]
then
	echo "This script updates the bundle with a shared lib"
    echo "It needs source location where dylib is and where app bundle is"
	echo "usage ./dylib.sh <pathtodylib> <pathtoappBundle> <BUNDLENAME>"
    echo "usage ./dylib.sh /pathtodylib /pathtoappBundle NAME"
	echo "./dylib.sh ~/src/TAGS/ApiSamples/3x/Qt/QtDisplayFont/VidyoClient/lib/mac ~/src/TAGS/ApiSamples/3x/Qt/build-QtDisplayFont-Qt48-Debug/QtDisplayFont.app QtDisplayFont"
    exit
fi

if [ -z "$3" ]
then
	echo "This script updates the bundle with a shared lib"
    echo "It needs source location where dylib is and where app bundle is"
	echo "usage ./dylib.sh <pathtodylib> <pathtoappBundle> <BUNDLENAME>"
    echo "usage ./dylib.sh /pathtodylib /pathtoappBundle NAME"
	echo "./dylib.sh ~/src/TAGS/ApiSamples/3x/Qt/QtDisplayFont/VidyoClient/lib/mac ~/src/TAGS/ApiSamples/3x/Qt/build-QtDisplayFont-Qt48-Debug/QtDisplayFont.app QtDisplayFont"
    exit
fi

DYLIB_LOC=$1
BUNDLE_LOC=$2
BUNDLE_NAME=$3

install_name_tool -change /usr/local/lib/VidyoClientDll.dylib  "@executable_path/../Frameworks/libVidyoClientDll.dylib" $BUNDLE_LOC/Contents/MacOS/$BUNDLE_NAME

mkdir $BUNDLE_LOC/Contents/Frameworks

cp $DYLIB_LOC/VidyoClientDll.dylib $DYLIB_LOC/libVidyoClientDll.dylib

cp $DYLIB_LOC/libVidyoClientDll.dylib $BUNDLE_LOC/Contents/Frameworks/
 