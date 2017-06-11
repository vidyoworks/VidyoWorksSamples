echo "pullvc for .Net"
VC_LOCATION=
if [ -z "$1" ]
then
    echo "VC location not specified."
    echo "usage ./pullvc.sh /pathtovc"
    exit
else
    VC_LOCATION=$1
    echo "VC location  = $VC_LOCATION"
	
	pushd DotNet
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd DotNetSimple
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd ReferenceSample
	./pullvc.sh $VC_LOCATION
	popd
	
	pushd SimpleRawFrame
	./pullvc.sh $VC_LOCATION
	popd
fi



