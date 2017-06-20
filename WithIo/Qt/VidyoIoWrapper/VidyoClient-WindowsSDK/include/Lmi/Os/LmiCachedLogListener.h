/** {file:
      {name: LmiCachedLogListener.h}
      {description: Log listener to log messages to a file.}
      {copyright:
      	(c) 2009-2015 Vidyo, Inc.,
      	433 Hackensack Avenue,
      	Hackensack, NJ  07601.
      
      	All rights reserved.
      
      	The information contained herein is proprietary to Vidyo, Inc.
      	and shall not be reproduced, copied (in whole or in part), adapted,
      	modified, disseminated, transmitted, transcribed, stored in a retrieval
      	system, or translated into any language in any form by any means
      	without the express written consent of Vidyo, Inc.
      	                  ***** CONFIDENTIAL *****
      }
    }
*/
#ifndef LMI_CACHED_LOG_LISTENER_H_
#define LMI_CACHED_LOG_LISTENER_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiLog.h>
#include <Lmi/Os/LmiFile.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct LmiCachedLogRecordImpl_;
typedef struct LmiCachedLogRecordImpl_ LmiCachedLogRecordImpl;
Declare_LmiSharedPtr(LmiCachedLogRecordImpl)
Declare_LmiSharedPtrWrapper(LmiCachedLogRecord, LmiCachedLogRecordImpl)
Declare_LmiVector(LmiCachedLogRecord)

/**
   {type:
	 {name: LmiCachedLogRecord}
	 {parent: Log}
	 {include: Lmi/Os/LmiCachedLogListener.h}
	 {description: A record of one logged event.}
	 {member:
		{name: level}
		{type: LmiLogLevel}
		{description:}
	 }
	 {member:
		{name: category}
		{type: LmiLogCategory}
		{description:}
	 }
	 {member:
		{name: categoryName}
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


/**
{function visibility="private":
	{name: LmiCachedLogRecordConstruct}
	{parent: LmiCachedLogRecord}
	{description: Constructs an LmiCachedLogRecord object.}
	{prototype: LmiCachedLogRecord *LmiCachedLogRecordConstruct(LmiCachedLogRecord *r, LmiUint64 index, LmiLogLevel level, LmiSizeT category, const char *categoryName,
		const char *file, LmiInt line, const char *functionName, const char *message, const char *threadName, LmiThreadId threadId, LmiTime eventTime, LmiAllocator *alloc)}
	{parameter: {name: r} {description: The LmiCachedLogRecord object to construct.}}
	{parameter: {name: index} {description: The index of the log record.}}
	{parameter: {name: level} {description: The level of the log record.}}
	{parameter: {name: category} {description: The category id of the log.}}
	{parameter: {name: categoryName} {description: The category name of the log.}}
	{parameter: {name: file} {description: The file name of the log.}}
	{parameter: {name: line} {description: The line of the code.}}
	{parameter: {name: functionName} {description: The functionName that called the log.}}
	{parameter: {name: message} {description: The message.}}
	{parameter: {name: threadName} {description: The threadName that called the log.}}
	{parameter: {name: threadId} {description: The threadId that called the log.}}
	{parameter: {name: eventTime} {description: The timestamp of the log record.}}
	{parameter: {name: alloc} {description: The allocator to use.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCachedLogRecord *LmiCachedLogRecordConstruct(LmiCachedLogRecord *r, LmiUint64 index, LmiLogLevel level, LmiLogCategory category, const char* categoryName, const char *file, LmiInt line, const char *functionName, const char *message, const char *threadName, LmiThreadId threadId, LmiTime eventTime, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: LmiCachedLogRecordConstructCopy}
	{parent: LmiCachedLogRecord}
	{description: Constructs an LmiCachedLogRecord object as a copy of another.}
	{prototype: LmiCachedLogRecord *LmiCachedLogRecordConstructCopy(LmiCachedLogRecord *obj, const LmiCachedLogRecord *other)}
	{parameter: {name: obj} {description: The LmiCachedLogRecord object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: LmiCachedLogRecordDestruct}
	{parent: LmiCachedLogRecord}
	{description: Destructs an LmiCachedLogRecord object.}
	{prototype: void LmiCachedLogRecordDestruct(LmiCachedLogRecord *obj)}
	{parameter: {name: obj} {description: The LmiCachedLogRecord object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: LmiCachedLogRecordAssign}
	{parent: LmiCachedLogRecord}
	{description: Assigns one LmiCachedLogRecord object the value of another. }
	{prototype: LmiCachedLogRecord *LmiCachedLogRecordAssign(LmiCachedLogRecord *obj, const LmiCachedLogRecord *other)}
	{parameter: {name: obj} {description: The LmiCachedLogRecord object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/


/**
   {function:
	 {name: LmiCachedLogRecordGetIndex}
	 {parent: LmiCachedLogRecord}
	 {description: Get the index associated with a logged event.}
	 {prototype: LmiUint64 LmiCachedLogRecordGetIndex(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the level.}}
	 {return: The index of the message described by this log record.}
	}
*/
LmiUint64 LmiCachedLogRecordGetIndex(const LmiCachedLogRecord* r);

/**
   {function:
	 {name: LmiCachedLogRecordGetLevel}
	 {parent: LmiCachedLogRecord}
	 {description: Get the level associated with a logged event.}
	 {prototype: LmiLogLevel LmiCachedLogRecordGetLevel(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the level.}}
	 {return: The level of the message described by this log record.}
	 {note: This will always be a single level.}
	}
*/
LmiLogLevel LmiCachedLogRecordGetLevel(const LmiCachedLogRecord* r);


/**
   {function:
	 {name: LmiCachedLogRecordGetCategory}
	 {parent: LmiCachedLogRecord}
	 {description: Get the category associated with a logged event.}
	 {prototype: LmiLogCategory LmiCachedLogRecordGetCategory(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the category.}}
	 {return: The category associated with the message described by this
	   log record.}
	 {note: This will always be a single category.}
	}
*/
LmiLogCategory LmiCachedLogRecordGetCategory(const LmiCachedLogRecord* r);


/**
   {function:
	 {name: LmiCachedLogRecordGetCategoryName}
	 {parent: LmiCachedLogRecord}
	 {description: Get the category name associated with a logged event.}
	 {prototype: const LmiString *LmiCachedLogRecordGetCategoryName(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the category name.}}
	 {return: The category name associated with the message described by this
	   log record.}
	 {note: This will always be a single category.}
	}
*/
const LmiString *LmiCachedLogRecordGetCategoryName(const LmiCachedLogRecord* r);

/**
   {function:
	 {name: LmiCachedLogRecordGetFile}
	 {parent: LmiCachedLogRecord}
	 {description: Get the filename associated with a logged event.}
	 {prototype: const LmiString* LmiCachedLogRecordGetFile(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a file name.}}
	 {return: The name of the C source file which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the empty string "".}
	}
*/
const LmiString* LmiCachedLogRecordGetFile(const LmiCachedLogRecord* r);


/**
   {function:
	 {name: LmiCachedLogRecordGetLine}
	 {parent: LmiCachedLogRecord}
	 {description: Get the line number associated with a logged event.}
	 {prototype: LmiInt LmiCachedLogRecordGetLine(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a line number.}}
	 {return: The line number of the C source which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the value 0.}
	}
*/
LmiInt LmiCachedLogRecordGetLine(const LmiCachedLogRecord* r);


/**
   {function:
	 {name: LmiCachedLogRecordGetFunctionName}
	 {parent: LmiCachedLogRecord}
	 {description: Get the name of the function associated with a logged
	   event.}
	 {prototype: const LmiString* LmiCachedLogRecordGetFunctionName(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a function name.}}
	 {return: The name of the C source function which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the value "".}
	}
*/
const LmiString* LmiCachedLogRecordGetFunctionName(const LmiCachedLogRecord* r);


/**
   {function:
	 {name: LmiCachedLogRecordGetMessage}
	 {parent: LmiCachedLogRecord}
	 {description: Get the message associated with a logged event.}
	 {prototype: const LmiString* LmiCachedLogRecordGetMessage(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the message.}}
	 {return: The message described by this log record.	 If this is not
	   available or not meaningful, this will be the value "".}
	}
*/
const LmiString* LmiCachedLogRecordGetMessage(const LmiCachedLogRecord* r);


/**
   {function:
	 {name: LmiCachedLogRecordGetThreadName}
	 {parent: LmiCachedLogRecord}
	 {description: Get the name of the thread associated with a logged event.}
	 {prototype: const LmiString* LmiCachedLogRecordGetThreadName(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the thread name.}}
	 {return: The name of the thread which logged the event described by
	   this log record. If this is not available, this will be the string "[System thread]".}
	}
*/
const LmiString* LmiCachedLogRecordGetThreadName(const LmiCachedLogRecord* r);

/**
   {function:
	 {name: LmiCachedLogRecordGetThreadId}
	 {parent: LmiCachedLogRecord}
	 {description: Get the thread id of the thread associated with a logged event.}
	 {prototype: LmiThreadId LmiCachedLogRecordGetThreadId(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the thread name.}}
	 {return: The thread id of the thread which logged the event described by
	   this log record.}
	}
*/
LmiThreadId LmiCachedLogRecordGetThreadId(const LmiCachedLogRecord* r);


/**
   {function:
	 {name: LmiCachedLogRecordGetTime}
	 {parent: LmiCachedLogRecord}
	 {description: Get the wall-clock time at which a logged event occurred.}
	 {prototype: LmiTime LmiCachedLogRecordGetTime(const LmiCachedLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the wall-clock time.}}
	 {return: The wall-clock time at which the event described by
	   this log record occurred. If this is not available, this will be the value LMI_TIME_INFINITE.}
	}
*/
LmiTime LmiCachedLogRecordGetTime(const LmiCachedLogRecord* r);

/**
{type:
	{name: LmiCachedLogListener}
	{parent: Os}
	{derivation-of: LmiLogListener}
	{include: Lmi/Os/LmiCachedLogListener.h}
	{description: A log listener for logging messages to a text file.}
}
*/
typedef struct
{
	LmiAllocator *alloc;
	LmiLogListener logListener;
	LmiVector(LmiCachedLogRecord) records;
	LmiUint64 maxNumRecords;
	LmiUint64 lastAddedIndex;
	LmiMutex recordsLock;
} LmiCachedLogListener;

/**
{function:
	{name: LmiCachedLogListenerConstruct}
	{parent: LmiCachedLogListener}
	{description: Constructs a file log listener object.}
	{prototype: LmiCachedLogListener* LmiCachedLogListenerConstruct(LmiCachedLogListener* l, LmiUint64 maxNumRecords, LmiAllocator* a)}
	{parameter:	{name: l} {description: The cached log listener object.}}
	{parameter: {name: maxNumRecords} {description: The maximum number of records to cache.}}
	{parameter: {name: a} {description: Allocator to use for dynamically-allocated memory for the listener.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCachedLogListener *LmiCachedLogListenerConstruct(LmiCachedLogListener *l, LmiUint64 maxNumRecords, LmiAllocator* a);

/**
{function:
	{name: LmiCachedLogListenerDestruct}
	{parent: LmiCachedLogListener}
	{description: Destructs a file log listener object.}
	{prototype: void LmiCachedLogListenerDestruct(LmiCachedLogListener* l)}
	{parameter:	{name: l} {description: The file log listener object.}}
}
*/
void LmiCachedLogListenerDestruct(LmiCachedLogListener *l);

/**
	{function:
		{name: LmiCachedLogListenerSetMaxNumRecords}
		{parent: LmiCachedLogListener}
		{description: Set the maximum number of records to keep in the of the cache.}
		{prototype: LmiBool LmiCachedLogListenerSetMaxNumRecords(LmiCachedLogListener* l, LmiUint64 maxNumRecords)}
		{parameter:
			{name: l}
			{description: The log listener in which to set the maximum file size.}}
		{parameter:
			{name: maxNumRecords}
			{description: The maximum number of records to keep in the cache.}}
		{return: LMI_TRUE on success, else LMI_FALSE.}
	}
*/
LmiBool LmiCachedLogListenerSetMaxNumRecords(LmiCachedLogListener* l, LmiUint64 maxNumRecords);

/**
	{function:
		{name: LmiCachedLogListenerGetMaxNumRecords}
		{parent: LmiCachedLogListener}
		{description: Get the maximum number of records to keep in the of the cache.}
		{prototype: LmiUint64 LmiCachedLogListenerGetMaxNumRecords(const LmiCachedLogListener* l)}
		{parameter:
			{name: l}
			{description: The log listener in which to get the maximum log file size.}}
		{return: The current maximum number of records to keep in the cache.}
	}
*/
LmiUint64 LmiCachedLogListenerGetMaxNumRecords(const LmiCachedLogListener* l);

/**
{function:
	{name: LmiCachedLogListenerGetListener}
	{parent: LmiCachedLogListener}
	{description: Gets the log listener base class from a cached log listener object. The base class
		can be used to call LmiLogListener API functions for the file logger.}
	{prototype: LmiLogListener* LmiCachedLogListenerGetListener(LmiCachedLogListener* l)}
	{parameter:	{name: l} {description: The file log listener object.}}
	{return: A pointer to the log listener object.}
}
*/
LmiLogListener *LmiCachedLogListenerGetListener(LmiCachedLogListener *l);

/**
{function:
	{name: LmiCachedLogListenerGetLogRecords}
	{parent: LmiCachedLogListener}
	{description: Gets the log records from a cached log listener object.}
	{prototype: LmiUint64 LmiCachedLogListenerGetLogRecords(LmiCachedLogListener *l, LmiUint64 lastIndexOfPreviousQuery, LmiUint64 maxRecords, const char *bodyFilter, const char *notInBodyFilter, const char *levelCategoryFilter, LmiVector(LmiCachedLogRecord) *records)}
	{parameter:	{name: l} {description: The cached log listener object.}}
	{parameter:	{name: lastIndexOfPreviousQuery} {description: Index of the last entry from the previous query.}}
	{parameter:	{name: maxRecords} {description: Maximum number of records to return.}}
	{parameter:	{name: bodyFilter} {description: Log record body should match this filter.}}
	{parameter:	{name: notInBodyFilter} {description: Log record body should not match this filter.}}
	{parameter:	{name: levelCategoryFilter} {description: Filter to apply to the level and category. See LmiLogListenerSetLevelsAndCategoriesFromString().}}
	{parameter:	{name: records} {description: The vector where the records will be copied.}}
	{return: The new index from the last log record.}
}
*/
LmiUint64 LmiCachedLogListenerGetLogRecords(LmiCachedLogListener *cll, LmiUint64 lastIndexOfPreviousQuery, LmiUint64 maxRecords, const char *bodyFilter, const char *notInBodyFilter, const char *levelCategoryFilter, LmiVector(LmiCachedLogRecord) *records);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "LmiCachedLogListenerInline.h"
#endif

#endif /* LMI_CACHED_LOG_LISTENER_H_ */

