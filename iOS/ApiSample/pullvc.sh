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
rm -f VidyoClientLibrary/include/*.h
cp -Rp $VC_LOCATION/Interfaces/*.h  VidyoClientLibrary/include/.

mkdir -p VidyoClientLibrary/lib
rm -f VidyoClientLibrary/lib/*.*
cp -Rp $VC_LOCATION/Release/iOS/*.a  VidyoClientLibrary/lib/.