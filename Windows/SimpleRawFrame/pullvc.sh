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
rm -f lib/*.*
rm -f include/*.*
cp -Rp $VC_LOCATION/Interfaces/*.h  include/.
cp -Rp $VC_LOCATION/Release/Win32/Tiles/*.dll  lib/.
cp -Rp $VC_LOCATION/Release/Win32/Tiles/VidyoClientDll.lib  lib/.
 