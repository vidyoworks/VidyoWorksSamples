echo "pullvc for Android"
VC_LOCATION=
if [ -z "$1" ]
then
    echo "VC location not specified."
    echo "usage ./pullvc.sh /pathtovc"
    exit
else
    VC_LOCATION=$1
    echo "VC location  = $VC_LOCATION"
	
	pushd ApiSample
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd RoomLink
	./pullvc.sh $VC_LOCATION
	popd
fi



