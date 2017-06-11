echo "pullvc for Android VcHandleOrientation"
VC_LOCATION=
if [ -z "$1" ]
then
    echo "VC location not specified."
    echo "usage ./pullvc.sh /pathtovc"
    exit
else
    VC_LOCATION=$1
    echo "VC location  = $VC_LOCATION"
	pushd VcHandleOrientation
	./pullvc.sh $VC_LOCATION
	popd
fi



