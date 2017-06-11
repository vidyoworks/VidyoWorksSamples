if [[ -e "$2" ]]
then
TAG=$1
BUILDNUMBER=`echo $TAG | sed 's/^.*_//;s/.*/.&/'`
VERSION=`echo $TAG | sed 's/_[0-9]*$//;s/^[A-Za-z_]*//;s/_/./g'`
echo VERSION STRING = $VERSION$BUILDNUMBER
INT_TAG_FROM_DATE=$(date "+%y%m%d%H%M") 
rm 1.txt 2.txt
sed "s/^.*versionCode.*$/android:versionCode=\"$INT_TAG_FROM_DATE\"/" "$2" > 1.txt
sed "s/^.*versionName.*$/android:versionName=\"$VERSION$BUILDNUMBER\"/" 1.txt > 2.txt
sed "s/^.*android:debuggable.*$/android:debuggable=\"false\"/" 2.txt > "$2"
cvs commit -m"Manifast automatic stamp for tag $TAG" "$2"
cvs tag -F $TAG "$2"
fi
