#!/bin/bash
#   copyright (c) 2011-2018 Vidyo, Inc. All rights reserved.


# check for valid tag
if [ -z "$1" ]; then
	echo "log file not provided"
	LOG_FILE=./vcapiusage.log
else
	LOG_FILE=$1
fi

if [ -z "$2" ]; then
	echo "target folder not provided"
	TARGET_FOLDER=.
else
	TARGET_FOLDER=$2
fi

echo "*********************************"
echo "Running Apiusage analysis"
echo "logfile=$LOG_FILE"
echo "folder=$TARGET_FOLDER"
echo "*********************************"
echo "Do you wish to run? Enter 1 for Yes and 2 for no"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done
echo "Starting"

NOWBEGIN=$(date +"%T")
echo "Starting at $NOWBEGIN" > $LOG_FILE >&1
echo "Analysing all events" >> $LOG_FILE >&1
echo "Unique Occurrences" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_IN_EVENT_\w*" $TARGET_FOLDER  | sort  | uniq  | wc -l >> $LOG_FILE >&1
echo "Spread across in number of files:" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c' --include='*.m'  --include='*.mm' -le "\w*VIDYO_CLIENT_IN_EVENT_\w*" $TARGET_FOLDER  | sort  | uniq | wc -l >> $LOG_FILE >&1
echo "*******All events ******" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_IN_EVENT_\w*" $TARGET_FOLDER >> $LOG_FILE >&1
echo "*******All events done ******" >> $LOG_FILE >&1

echo "***********************Analysing all requests***********************" >> $LOG_FILE >&1
echo "Unique Occurrences" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_REQUEST_\w*" $TARGET_FOLDER  | sort  | uniq  | wc -l >> $LOG_FILE >&1
echo "Spread across in number of files:" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c' --include='*.m'  --include='*.mm' -le "\w*VIDYO_CLIENT_REQUEST_\w*" $TARGET_FOLDER  | sort  | uniq | wc -l >> $LOG_FILE >&1
echo "*******All requests ******" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_REQUEST_\w*" $TARGET_FOLDER >> $LOG_FILE >&1
echo "*******All requests done ******" >> $LOG_FILE >&1

echo "***********************Analysing all notifications***********************" >> $LOG_FILE >&1
echo "Unique Occurrences" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_OUT_EVENT_\w*" $TARGET_FOLDER  | sort  | uniq  | wc -l >> $LOG_FILE >&1
echo "Spread across in number of files:" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c' --include='*.m'  --include='*.mm' -le "\w*VIDYO_CLIENT_OUT_EVENT_\w*" $TARGET_FOLDER  | sort  | uniq | wc -l >> $LOG_FILE >&1
echo "*******All notifications ******" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_OUT_EVENT_\w*" $TARGET_FOLDER >> $LOG_FILE >&1
echo "*******All notifications done ******" >> $LOG_FILE >&1


echo "***********************Analysing all undocumented***********************" >> $LOG_FILE >&1
echo "Unique Occurrences" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_PRIVATE_\w*" $TARGET_FOLDER  | sort  | uniq  | wc -l >> $LOG_FILE >&1
echo "Spread across in number of files:" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c' --include='*.m' --include='*.mm' -le "\w*VIDYO_CLIENT_PRIVATE_\w*" $TARGET_FOLDER  | sort  | uniq | wc -l >> $LOG_FILE >&1
echo "*******All undocumented ******" >> $LOG_FILE >&1
grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*VIDYO_CLIENT_PRIVATE_\w*" $TARGET_FOLDER >> $LOG_FILE >&1
echo "*******All undocumented done ******" >> $LOG_FILE >&1
NOWBEGIN=$(date +"%T")
echo "Completed at $NOWBEGIN" >> $LOG_FILE >&1
echo "*********************************"
echo " Apiusage complete"
echo "*********************************"
echo "*********************************"
