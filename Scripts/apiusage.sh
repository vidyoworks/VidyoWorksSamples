#!/bin/bash
#   copyright (c) 2011-2018 Vidyo, Inc. All rights reserved.

function ParseUsage 
{
 CALLER_TYPE=$1
 FILTER_VAL=$2
 
 echo "***********************Analysing all $CALLER_TYPE***********************" >> $LOG_FILE >&1
 echo "Unique Occurrences" >> $LOG_FILE >&1
 grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*$FILTER_VAL\w*" $TARGET_FOLDER  | sort  | uniq  | wc -l >> $LOG_FILE >&1
 echo "Spread across in number of files:" >> $LOG_FILE >&1
 grep -ohir --include='*.cpp' --include='*.c' --include='*.m'  --include='*.mm' -le "\w*$FILTER_VALV\w*" $TARGET_FOLDER  | sort  | uniq | wc -l >> $LOG_FILE >&1
 echo "*******All events ******" >> $LOG_FILE >&1
 grep -ohir --include='*.cpp' --include='*.c'  --include='*.m'  --include='*.mm' "\w*$FILTER_VAL\w*" $TARGET_FOLDER >> $LOG_FILE >&1
 echo "*******All $CALLER_TYPE done ******" >> $LOG_FILE >&1
}


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
ParseUsage "events" "VIDYO_CLIENT_IN_EVENT_"
ParseUsage "requests" "VIDYO_CLIENT_REQUEST_"
ParseUsage "notifications" "VIDYO_CLIENT_OUT_EVENT_"
ParseUsage "privates" "VIDYO_CLIENT_PRIVATE_"

NOWBEGIN=$(date +"%T")
echo "Completed at $NOWBEGIN" >> $LOG_FILE >&1
echo "*********************************"
echo " Apiusage complete"
echo "*********************************"
echo "*********************************"
