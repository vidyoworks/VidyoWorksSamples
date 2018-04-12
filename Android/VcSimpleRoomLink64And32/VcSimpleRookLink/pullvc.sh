VC_LOCATION=
if [ -z "$1" ]
then
    echo "VC location not specified."
    echo "usage ./pullvc.sh /pathtovc"
    exit
else
    VC_LOCATION=$1
    echo "VC location  = $VC_LOCATION"
fi

####remove all copies of so files and old headers
source ./cleanjni.sh
rm -f app/src/main/jni/lib/include/*.h

##overwrite new headers
mkdir -p app/src/main/jni/lib
mkdir -p app/src/main/jni/lib/include
#cp -Rp $VC_LOCATION/Release/Android/armeabi-v7a/libVidyoClientApp.so app/src/main/jni/lib/libVidyoClientApp.so
cp -Rp $VC_LOCATION/Release/Android/libVidyoClientApp.so app/src/main/jni/lib/libVidyoClientApp.so
cp -Rp $VC_LOCATION/Interfaces/*.h app/src/main/jni/lib/include/.

##overwrite new device manager
rm -f app/src/main/java/com/vidyo/LmiDeviceManager/*.java
cp -Rp $VC_LOCATION/Release/Android/com/vidyo/LmiDeviceManager/*.java app/src/main/java/com/vidyo/LmiDeviceManager/.


