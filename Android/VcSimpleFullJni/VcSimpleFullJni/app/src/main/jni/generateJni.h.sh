cd ./bin/classes
javah -jni com.vidyo.VidyoClient.ApplicationJni
javap -s -p com.vidyo.VidyoClient.PortalEntity > PortalEntity.javap.txt

cd ../../Common/bin/classes
javah -jni com.vidyo.VidyoClient.WebProxyEntity
javap -s -p com.vidyo.VidyoClient.WebProxyEntity > WebProxyEntity.javap.txt
