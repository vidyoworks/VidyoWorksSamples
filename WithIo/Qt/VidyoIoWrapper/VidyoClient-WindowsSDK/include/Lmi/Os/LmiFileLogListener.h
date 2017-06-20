/** {file:
      {name: LmiFileLogListener.h}
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
#ifndef LMI_FILE_LOG_LISTENER_H_
#define LMI_FILE_LOG_LISTENER_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiLog.h>
#include <Lmi/Os/LmiFile.h>

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: LmiFileLogListener}
	{parent: Os}
	{derivation-of: LmiLogListener}
	{include: Lmi/Os/LmiFileLogListener.h}
	{description: A log listener for logging messages to a text file.}
}
*/
typedef struct
{
	LmiAllocator *alloc;
	LmiLogListener logListener;
	LmiFile fp;
	LmiBool fpConstructed;
	LmiInt64 cutoff;
	LmiUint64 filesize;
	LmiBool recursing;
	LmiString name;
	LmiTime wrapTime; /* out of a 24hr day, when to roll over the file */
	LmiTime wrapPeriod; /* how often to roll over the file */
	LmiTime wrapPeriodNum; /* current number of wraps */
	LmiSizeT wrapCount; /* how many files to keep */
} LmiFileLogListener;


/**
{function:
	{name: LmiFileLogListenerConstructEx}
	{parent: LmiFileLogListener}
	{description: Constructs a file log listener object.}
	{prototype: LmiFileLogListener* LmiFileLogListenerConstructEx(LmiFileLogListener* listener, const char* filename, LmiInt64 size, LmiTime wrapPeriod, LmiSizeT wrapCount, LmiAllocator* a)}
	{parameter:	{name: listener} {description: The file log listener object to construct.}}
	{parameter:	{name: filename} {description: The name of the file to log to.}}
	{parameter:	{name: size} {description: The number of bytes of logged messages to save. When the length of
		logged messages exceeds this value, older messages will be overwritten.
		If this value is negative, the size of the log is unbounded.}}
	{parameter:
		{name: wrapPeriod}
		{description: How often to initiate the wrap. If this value is LMI_TIME_INFINITE, the log file will not be wrapped based on time.}}
	{parameter:
		{name: wrapCount}
		{description: The maximum number of files to keep.}}
	 {parameter:
	   {name: a}
	   {description: Allocator to use for dynamically-allocated memory for the listener.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
	{note: If the wrapCount value is 0, the log file will wrap to the beginning when it reaches size or wrapPeriod.  If this value is 1 the file will be cleared every wrap. If the number is greater then 1, the files will be re-named in the order of creation such as filename.1, filename.2 and the log will be written to the new 'filename' file.}
}
*/
LmiFileLogListener *LmiFileLogListenerConstructEx(LmiFileLogListener *fll, const char *filename, LmiInt64 size, LmiTime wrapPeriod, LmiSizeT wrapCount, LmiAllocator *alloc);

/**
{function:
	{name: LmiFileLogListenerConstruct}
	{parent: LmiFileLogListener}
	{description: Constructs a file log listener object.}
	{prototype: LmiFileLogListener* LmiFileLogListenerConstruct(LmiFileLogListener* listener, const char* filename, LmiInt64 size, LmiAllocator* a)}
	{parameter:	{name: listener} {description: The file log listener object to construct.}}
	{parameter:	{name: filename} {description: The name of the file to log to.}}
	{parameter:	{name: size} {description: The number of bytes of logged messages to save. When the length of
		logged messages exceeds this value, older messages will be overwritten.
		If this value is negative, the size of the log is unbounded.}}
	 {parameter:
	   {name: a}
	   {description: Allocator to use for dynamically-allocated memory for the listener.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiFileLogListener *LmiFileLogListenerConstruct(LmiFileLogListener *listener, const char *filename, LmiInt64 size, LmiAllocator* a);

/**
{function:
	{name: LmiFileLogListenerDestruct}
	{parent: LmiFileLogListener}
	{description: Destructs a file log listener object.}
	{prototype: void LmiFileLogListenerDestruct(LmiFileLogListener* listener)}
	{parameter:	{name: listener} {description: The file log listener object.}}
}
*/
void LmiFileLogListenerDestruct(LmiFileLogListener *listener);

/**
	{function replaced-by="LmiLogListenerSetVerbose":
		{name: LmiFileLogListenerSetMessageOnly}
		{parent: LmiFileLogListener}
		{description: Set whether the listener should print only messages, or all fields of the log record.}
		{prototype: LmiBool LmiFileLogListenerSetMessageOnly(LmiFileLogListener* l, LmiBool messageOnly)}
		{parameter:
			{name: l}
			{description: The log listener in which to set or clear the message-only state.}}
		{parameter:
			{name: messageOnly}
			{description: LMI_TRUE if the log listener should only print messages; LMI_FALSE if it should print all fields of the log record.}}
		{return: LMI_TRUE on success, else LMI_FALSE.}
	}
*/
LMI_DEPRECATED("Deprecated, replaced by LmiLogListenerSetVerbose") LmiBool LmiFileLogListenerSetMessageOnly(LmiFileLogListener* l, LmiBool messageOnly);

/**
	{function replaced-by="LmiLogListenerIsVerbose":
		{name: LmiFileLogListenerGetMessageOnly}
		{parent: LmiFileLogListener}
		{description: Get whether the listener is printing only messages, or all fields of the log record.}
		{prototype: LmiBool LmiFileLogListenerGetMessageOnly(const LmiFileLogListener* l)}
		{parameter:
			{name: l}
			{description: The log listener in which to get the message-only state.}}
		{return: LMI_TRUE if the log listener is only printing messages; LMI_FALSE if it is printing all fields of the log record.}
	}
*/
LMI_DEPRECATED("Deprecated, replaced by LmiLogListenerIsVerbose") LmiBool LmiFileLogListenerGetMessageOnly(const LmiFileLogListener* l);

/**
	{function:
		{name: LmiFileLogListenerSetMaxSize}
		{parent: LmiFileLogListener}
		{description: Set the maximum size of the log file produced by a file log listener.}
		{prototype: LmiBool LmiFileLogListenerSetMaxSize(LmiFileLogListener* l, LmiInt64 maxSize)}
		{parameter:
			{name: l}
			{description: The log listener in which to set the maximum file size.}}
		{parameter:
			{name: maxSize}
			{description: The maximum size of a log file.  If this value is negative, the log file is unbounded.}}
		{return: LMI_TRUE on success, else LMI_FALSE.}
	}
*/
LmiBool LmiFileLogListenerSetMaxSize(LmiFileLogListener* l, LmiInt64 maxSize);

/**
	{function:
		{name: LmiFileLogListenerGetMaxSize}
		{parent: LmiFileLogListener}
		{description: Get the maximum size of the log file produced by a file log listener.}
		{prototype: LmiInt64 LmiFileLogListenerGetMaxSize(const LmiFileLogListener* l)}
		{parameter:
			{name: l}
			{description: The log listener in which to get the maximum log file size.}}
		{return: The current maximum size of a log file.  If this value is negative, the log file is unbounded.}
	}
*/
LmiInt64 LmiFileLogListenerGetMaxSize(const LmiFileLogListener* l);

/**
	{function:
		{name: LmiFileLogListenerSetWrapPeriod}
		{parent: LmiFileLogListener}
		{description: Set the wrap period of the log file produced by a file log listener.}
		{prototype: LmiBool LmiFileLogListenerSetWrapPeriod(LmiFileLogListener* l, LmiTime wrapPeriod)}
		{parameter:
			{name: l}
			{description: The log listener.}}
		{parameter:
			{name: wrapPeriod}
			{description: How often to initiate the wrap. If this value is LMI_TIME_INFINITE, the log file will not be wrapped based on time.}}
		{return: LMI_TRUE on success, else LMI_FALSE.}
	}
*/
LmiBool LmiFileLogListenerSetWrapPeriod(LmiFileLogListener* l, LmiTime wrapPeriod);

/**
	{function:
		{name: LmiFileLogListenerGetWrapPeriod}
		{parent: LmiFileLogListener}
		{description: Get the wrap time of the log file produced by a file log listener.}
		{prototype: LmiTime LmiFileLogListenerGetWrapPeriod(const LmiFileLogListener* l)}
		{parameter:
			{name: l}
			{description: The log listener.}}
		{return: How often the wrap will be initiated. If this value is LMI_TIME_INFINITE, the log file will not be wrapped based on time.}
	}
*/
LmiTime LmiFileLogListenerGetWrapPeriod(const LmiFileLogListener* l);

/**
	{function:
		{name: LmiFileLogListenerSetWrapCount}
		{parent: LmiFileLogListener}
		{description: Set the maximum number of log files to keep.}
		{prototype: LmiBool LmiFileLogListenerSetWrapCount(LmiFileLogListener* l, LmiSizeT wrapCount)}
		{parameter:
			{name: l}
			{description: The log listener.}}
		{parameter:
			{name: wrapCount}
			{description: The maximum number of files to keep.}}
		{return: LMI_TRUE on success, else LMI_FALSE.}
		{note:If this value is 0, the log file will wrap to the beginning, If this value is 1 the file will be cleared every wrap. If the number is greater then 1, the files will be re-named in the order of creation such as filename-1.log, filename-2.log and the log will be written to the new filename.log file. }
	}
*/
LmiBool LmiFileLogListenerSetWrapCount(LmiFileLogListener* l, LmiSizeT wrapCount);

/**
	{function:
		{name: LmiFileLogListenerGetWrapCount}
		{parent: LmiFileLogListener}
		{description: Get the maximum number of log files to keep.}
		{prototype: LmiSizeT LmiFileLogListenerGetWrapCount(const LmiFileLogListener* l)}
		{parameter:
			{name: l}
			{description: The log listener.}}
		{return: The maximum number of files to keep.}
		{note:If this value is 0, the log file will wrap to the beginning, If this value is 1 the file will be cleared every wrap. If the number is greater then 1, the files will be re-named in the order of creation such as filename-1.log, filename-2.log and the log will be written to the new filename.log file. }
	}
*/
LmiSizeT LmiFileLogListenerGetWrapCount(const LmiFileLogListener* l);

/**
{function:
	{name: LmiFileLogListenerGetListener}
	{parent: LmiFileLogListener}
	{description: Gets the log listener base class from a file log listener object. The base class
		can be used to call LmiLogListener API functions for the file logger.}
	{prototype: LmiLogListener* LmiFileLogListenerGetListener(LmiFileLogListener* listener)}
	{parameter:	{name: listener} {description: The file log listener object.}}
	{return: A pointer to the log listener object.}
}
*/
LmiLogListener *LmiFileLogListenerGetListener(LmiFileLogListener *listener);

/**
{function:
	{name: LmiFileLogListenerGetFileNames}
	{parent: LmiFileLogListener}
	{description: Fills in the passed in vector with a list of file names used by the FileLogger.}
	{prototype: LmiBool LmiFileLogListenerGetFileNames(LmiFileLogListener* listener,LmiVector(LmiString) *fileNames)}
	{parameter:	{name: listener} {description: The file log listener object.}}
	{parameter:	{name: fileNames} {description: Empty vector of strings to be filled in with file names.}}
	{return: LMI_TRUE on success, else LMI_FALSE.}
}
*/
LmiBool LmiFileLogListenerGetFileNames(LmiFileLogListener *fll, LmiVector(LmiString) *fileNames);

LMI_END_EXTERN_C

#endif /* LMI_FILE_LOG_LISTENER_H_ */

