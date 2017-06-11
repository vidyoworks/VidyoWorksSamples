echo "pullvc for Qt"
VC_LOCATION=
if [ -z "$1" ]
then
    echo "VC location not specified."
    echo "usage ./pullvc.sh /pathtovc"
    exit
else
    VC_LOCATION=$1
    echo "VC location  = $VC_LOCATION"
	
	pushd QtGalleryView
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd QtRawFrame
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd QtRawFrame2
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd QtRawFrameSingleView
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd QtSendAudioRawFrame
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd QtSendRawFrame
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd QtVidyoSample
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd QtDisplayFont
	./pullvc.sh $VC_LOCATION
	popd
fi



