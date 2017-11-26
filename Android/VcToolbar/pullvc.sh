echo "pullvc for Android VcGallery"
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
fi



