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
	
	pushd VcGallery
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd VcRawFrame
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd VcSimpleRoomLink
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd VcSimpleSample
	./pullvc.sh $VC_LOCATION
	popd

    pushd VcGetCertificates
    ./pullvc.sh $VC_LOCATION
    popd

    pushd VcSimpleRoomLink64Or32
    ./pullvc.sh $VC_LOCATION
    popd
fi



