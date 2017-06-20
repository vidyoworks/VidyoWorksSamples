/** 
{file:
	{name: VidyoLogRecord.h}
	{description: Vidyo Contact. }
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_LOGRECORD_H_
#define VIDYO_LOGRECORD_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiTime.h>
#include <Lmi/Os/LmiLog.h>
LMI_BEGIN_EXTERN_C

/**
{type:
	{name: VidyoLogLevel}
	{parent: VidyoLogRecord}
	{include: Lmi/VidyoClient/VidyoLogRecord.h}
	{description: An identifier for the level, or type, of a logged
	event.  This indicates the degree of significance of the event.}
	{value:{name: VIDYO_LOGLEVEL_FATAL}
		{description: The event being logged describes a fatal error.  In
		all likelihood system execution will not be able to continue.}}
	{value:{name: VIDYO_LOGLEVEL_ERROR}
		{description: The event being logged describes a continuable error.
		The system should be able to continue, but human intervention or
		diagnosis may be necessary.}}
	{value:{name: VIDYO_LOGLEVEL_WARNING}
		{description: The event being logged describes a warning.  Something
		has occurred which may require attention or action, but which is not
		actually erroneous.}}
	{value:{name: VIDYO_LOGLEVEL_INFO}
		{description: The event being logged describes information which may
		be useful or informative to a user of the system.	No problems are
		being reported.}}
	{value:{name: VIDYO_LOGLEVEL_DEBUG}
		{description: The event being logged describes information which may
		be useful to a developer to understand the code.  The information is
		not expected to be useful to users of the system.}}
	{value:{name: VIDYO_LOGLEVEL_SENT}
		{description: The event being logged describes data that has been
		transmitted by the system.}}
	{value:{name: VIDYO_LOGLEVEL_RECEIVED}
		{description: The event being logged describes data that has been
		received by the system.}}
	{value:{name: VIDYO_LOGLEVEL_ENTER}
		{description: The event being logged describes the system entering
		a function.}}
	{value:{name: VIDYO_LOGLEVEL_LEAVE}
		{description: The event being logged describes the system leaving
		from a function.}}
	{value:{name: VIDYO_LOGLEVEL_INVALID}
		{description: A value that does not represent a valid log level.  This
		value is returned by LmiLogGetLevelByName and LmiLogGetLevelByIndex
		on invalid input.}}
}
*/
typedef enum {
	VIDYO_LOGLEVEL_FATAL,
	VIDYO_LOGLEVEL_ERROR,
	VIDYO_LOGLEVEL_WARNING,
	VIDYO_LOGLEVEL_INFO,
	VIDYO_LOGLEVEL_DEBUG,
	VIDYO_LOGLEVEL_SENT,
	VIDYO_LOGLEVEL_RECEIVED,
	VIDYO_LOGLEVEL_ENTER,
	VIDYO_LOGLEVEL_LEAVE,
	VIDYO_LOGLEVEL_INVALID
} VidyoLogLevel;

/**
   {type:
	 {name: VidyoLogRecord}
	 {parent: Endpoint}
	 {include: Lmi/VidyoClient/VidyoLogRecord.h}
	 {description: A record of one logged event.}
	 {member:
		{name: level}
		{type: VidyoLogLevel}
		{description:}
	 }
	 {member:
		{name: categoryName}
		{type: LmiSizeT}
		{description:}
	 }
	 {member:
		{name: name}
		{type: const char*}
		{description:}
	 }
	 {member:
		{name: file}
		{type: const char *}
		{description:}
	 }
	 {member:
		{name: line}
		{type: LmiInt}
		{description:}
	 }
	 {member:
		{name: functionName}
		{type: const char * }
		{description:}
	 }
	 {member:
		{name: message}
		{type: const char * }
		{description:}
	 }
	 {member:
		{name: threadName}
		{type: const char * }
		{description:}
	 }
	 {member:
		{name: eventTime}
		{type: LmiTime}
		{description:}
	 }
   }
*/
typedef struct {
  VidyoLogLevel level;
  LmiSizeT categoryName;
  const char* name;
  const char *file;
  LmiInt line;
  const char *functionName;
  const char *message;
  const char *threadName;
  LmiThreadId threadId;
  LmiTime eventTime;
} VidyoLogRecord;

/**
{function visibility="private":
	{name: VidyoLogRecordConstruct}
	{parent: VidyoLogRecord}
	{description: Constructs an VidyoLogRecord object.}
	{prototype: VidyoLogRecord *VidyoLogRecordConstruct(VidyoLogRecord *r, VidyoLogLevel level, LmiSizeT category, const char* name, const char *file, LmiInt line, const char *functionName, const char *message, const char *threadName, LmiThreadId threadId, LmiTime eventTime)}
	{parameter: {name: r} {description: The VidyoLogRecord object to construct.}}
	{parameter: {name: level} {description: The level of the log record.}}
	{parameter: {name: category} {description: The category id of the log.}}
	{parameter: {name: name} {description: The category name of the log.}}
	{parameter: {name: file} {description: The file name of the log.}}
	{parameter: {name: line} {description: The line of the code.}}
	{parameter: {name: functionName} {description: The functionName that called the log.}}
	{parameter: {name: message} {description: The message.}}
	{parameter: {name: threadName} {description: The threadName that called the log.}}
	{parameter: {name: threadId} {description: The threadId that called the log.}}
	{parameter: {name: eventTime} {description: The timestamp of the log record.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoLogRecord *VidyoLogRecordConstruct(VidyoLogRecord *r, VidyoLogLevel level, LmiSizeT category, const char* name, const char *file, LmiInt line, const char *functionName, const char *message, const char *threadName, LmiThreadId threadId, LmiTime eventTime);

/**
{function visibility="private":
	{name: VidyoLogRecordDestruct}
	{parent: VidyoLogRecord}
	{description: Destructs an VidyoLogRecord object.}
	{prototype: void VidyoLogRecordDestruct(VidyoLogRecord *r)}
	{parameter: {name: r} {description: The VidyoLogRecord object to destruct.}}
}
*/
void VidyoLogRecordDestruct(VidyoLogRecord *r);

/**
   {function visibility="private":
	 {name: VidyoLogRecordGetLevel}
	 {parent: VidyoLogRecord}
	 {description: Get the level associated with a logged event.}
	 {prototype: VidyoLogLevel VidyoLogRecordGetLevel(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the level.}}
	 {return: The level of the message described by this log record.}
	 {note: This will always be a single level.}
	}
*/
LMI_INLINE_DECLARATION VidyoLogLevel VidyoLogRecordGetLevel(const VidyoLogRecord* r);

/**
   {function visibility="private":
	 {name: VidyoLogRecordGetCategoryName}
	 {parent: VidyoLogRecord}
	 {description: Get the category associated with a logged event.}
	 {prototype: LmiSizeT VidyoLogRecordGetCategoryName(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the category.}}
	 {return: The category associated with the message described by this
	   log record.}
	 {note: This will always be a single category.}
	}
*/
LMI_INLINE_DECLARATION LmiSizeT VidyoLogRecordGetCategoryName(const VidyoLogRecord* r);


/**
   {function visibility="private":
	 {name: VidyoLogRecordGetFile}
	 {parent: VidyoLogRecord}
	 {description: Get the filename associated with a logged event.}
	 {prototype: const char* VidyoLogRecordGetFile(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a file name.}}
	 {return: The name of the C source file which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the empty string "".}
	}
*/
LMI_INLINE_DECLARATION const char* VidyoLogRecordGetFile(const VidyoLogRecord* r);


/**
   {function visibility="private":
	 {name: VidyoLogRecordGetLine}
	 {parent: VidyoLogRecord}
	 {description: Get the line number associated with a logged event.}
	 {prototype: LmiInt VidyoLogRecordGetLine(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a line number.}}
	 {return: The line number of the C source which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the value 0.}
	}
*/
LMI_INLINE_DECLARATION LmiInt VidyoLogRecordGetLine(const VidyoLogRecord* r);


/**
   {function visibility="private":
	 {name: VidyoLogRecordGetFunctionName}
	 {parent: VidyoLogRecord}
	 {description: Get the name of the functionName associated with a logged
	   event.}
	 {prototype: const char* VidyoLogRecordGetFunctionName(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a function name.}}
	 {return: The name of the C source function which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the value "".}
	}
*/
LMI_INLINE_DECLARATION const char* VidyoLogRecordGetFunctionName(const VidyoLogRecord* r);


/**
   {function visibility="private":
	 {name: VidyoLogRecordGetMessage}
	 {parent: VidyoLogRecord}
	 {description: Get the message associated with a logged event.}
	 {prototype: const char* VidyoLogRecordGetMessage(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the message.}}
	 {return: The message described by this log record.	 If this is not
	   available or not meaningful, this will be the value "".}
	}
*/
LMI_INLINE_DECLARATION const char* VidyoLogRecordGetMessage(const VidyoLogRecord* r);


/**
   {function visibility="private":
	 {name: VidyoLogRecordGetThreadName}
	 {parent: VidyoLogRecord}
	 {description: Get the name of the thread associated with a logged event.}
	 {prototype: const char* VidyoLogRecordGetThreadName(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the thread name.}}
	 {return: The name of the thread which logged the event described by
	   this log record. If this is not available, this will be the string "[System thread]".}
	}
*/
LMI_INLINE_DECLARATION const char* VidyoLogRecordGetThreadName(const VidyoLogRecord* r);


/**
   {function visibility="private":
	 {name: VidyoLogRecordGetTime}
	 {parent: VidyoLogRecord}
	 {description: Get the wall-clock time at which a logged event occurred.}
	 {prototype: LmiTime VidyoLogRecordGetTime(const VidyoLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the wall-clock time.}}
	 {return: The wall-clock time at which the event described by
	   this log record occurred. If this is not available, this will be the value LMI_TIME_INFINITE.}
	}
*/
LMI_INLINE_DECLARATION LmiTime VidyoLogRecordGetTime(const VidyoLogRecord* r);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoLogRecordInline.h"
#endif

#endif /* VIDYO_LOGRECORD_H_ */
