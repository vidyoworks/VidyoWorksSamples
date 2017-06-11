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
rm -f VidyoClient/include/*.h
cp -Rp $VC_LOCATION/Interfaces/*.h  VidyoClient/include/.

mkdir -p VidyoClient/lib
mkdir -p VidyoClient/lib/linux
rm -f VidyoClient/lib/linux/*.*
cp -Rp $VC_LOCATION/Release/linux/64Bit/NoQt/*.*  VidyoClient/lib/linux/.

mkdir -p VidyoClient/lib/mac
rm -f VidyoClient/lib/mac/*.*
cp -Rp $VC_LOCATION/Release/MacOS/Release/Tiles/*.dylib  VidyoClient/lib/mac/.

mkdir -p VidyoClient/lib/win32
rm -f VidyoClient/win32/*.*
cp -Rp $VC_LOCATION/Release/Win32/Tiles/*.dll  VidyoClient/lib/win32/.
cp -Rp $VC_LOCATION/Release/Win32/Tiles/VidyoClientDll.lib  VidyoClient/lib/win32/.
 