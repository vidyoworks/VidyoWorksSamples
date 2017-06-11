VC_LOCATION=
if [ -z "$1" ]
then
    echo "first paramter unspecified"
    echo "usage <vc version> <sample version>"
	echo "example"
	echo "usage ./compress.sh 3_4_5_0010 3"
    exit
fi

if [ -z "$2" ]
then
    echo "second paramter unspecified"
     echo "usage <vc version> <sample version>"
	echo "example"
	echo "usage ./publish.sh 3_4_5_0010 3"
    exit
fi
VCVERSION=$1
SAMPLE_VERSION=$2


if [[ "$OSTYPE" == "cygwin" ]]; then
	echo "OS detected Cygwin"
    ZIP_PROGRAM="7z.exe"
else
        echo "OS not detected"
		exit
fi

UNDESCORE="_"
EXTENSION=".zip"
rm -p *.zip
SUFFIX=$UNDESCORE$VCVERSION$UNDESCORE$SAMPLE_VERSION$EXTENSION
$ZIP_PROGRAM  a -r DotNet$SUFFIX  -w DotNet -mem=AES256
$ZIP_PROGRAM  a -r DotNetSimple$SUFFIX  -w DotNetSimple -mem=AES256
$ZIP_PROGRAM  a -r ReferenceSample$SUFFIX  -w ReferenceSample -mem=AES256
$ZIP_PROGRAM  a -r SimpleRawFrame$SUFFIX  -w SimpleRawFrame -mem=AES256

