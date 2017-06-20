/** {file:
      {name: LmiConsoleLogListener.h}
      {description: Log listener to log messages to the console.}
      {copyright:
      	(c) 2009-2012 Vidyo, Inc.,
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
#ifndef LMI_CONSOLE_LOG_LISTENER_H_
#define LMI_CONSOLE_LOG_LISTENER_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiLog.h>

LMI_BEGIN_EXTERN_C
/**
   {type:
     {name: LmiConsoleLogListener}
     {parent: Os}
     {derivation-of: LmiLogListener}
     {include: Lmi/Os/LmiConsoleLogListener.h}
     {description: A log listener for logging messages to the console.}
   }
*/
typedef struct
{
	LmiLogListener logListener;
	LmiBool columns;
	LmiBool coloring;
	LmiBool ansiColoring;
} LmiConsoleLogListener;

/**
   {function:
     {name: LmiConsoleLogListenerConstruct}
     {parent: LmiConsoleLogListener}
     {description: Construct an LmiConsoleLogListener.}
     {prototype: LmiConsoleLogListener* LmiConsoleLogListenerConstruct(LmiConsoleLogListener* l, LmiAllocator* a)}
     {parameter:
       {name: l}
       {description: The console log listener object to construct.}}
	 {parameter:
	   {name: a}
	   {description: Allocator to use for dynamically-allocated memory for the listener.}}
     {return: l on success, NULL on failure.}
     {note: The newly-constructed listener will not receive
        notifications for any log levels or packages.  For the listener
        to be useful, the various LmiLogListenerSet* functions must be
        called.}
   }
*/
LmiConsoleLogListener* LmiConsoleLogListenerConstruct(LmiConsoleLogListener* l, LmiAllocator* a);

/**
   {function:
     {name: LmiConsoleLogListenerDestruct}
     {parent: LmiConsoleLogListener}
     {description: Destruct an LmiConsoleLogListener.}
     {prototype: void LmiConsoleLogListenerDestruct(LmiConsoleLogListener* l)}
     {parameter:
       {name: l}
       {description: A pointer to the LmiLogListener to destruct.}}
   }
*/
void LmiConsoleLogListenerDestruct(LmiConsoleLogListener* l);

/**
	{function replaced-by="LmiLogListenerSetVerbose":
		{name: LmiConsoleLogListenerSetMessageOnly}
		{parent: LmiConsoleLogListener}
		{description: Set whether the listener should print only messages, or all fields of the log record.}
		{prototype: LmiBool LmiConsoleLogListenerSetMessageOnly(LmiConsoleLogListener* l, LmiBool messageOnly)}
		{parameter:
			{name: l}
			{description: The log listener in which to set or clear the message-only state.}}
		{parameter:
			{name: messageOnly}
			{description: LMI_TRUE if the log listener should only print messages; LMI_FALSE if it should print all fields of the log record.}}
		{return: LMI_TRUE on success, else LMI_FALSE.}
	}
*/
LMI_DEPRECATED("Deprecated, replaced by LmiLogListenerSetVerbose") LmiBool LmiConsoleLogListenerSetMessageOnly(LmiConsoleLogListener* l, LmiBool messageOnly);

/**
	{function replaced-by="LmiLogListenerIsVerbose":
		{name: LmiConsoleLogListenerGetMessageOnly}
		{parent: LmiConsoleLogListener}
		{description: Get whether the listener is printing only messages, or all fields of the log record.}
		{prototype: LmiBool LmiConsoleLogListenerGetMessageOnly(const LmiConsoleLogListener* l)}
		{parameter:
			{name: l}
			{description: The log listener in which to get the message-only state.}}
		{return: LMI_TRUE if the log listener is only printing messages; LMI_FALSE if it is printing all fields of the log record.}
	}
*/
LMI_DEPRECATED("Deprecated, replaced by LmiLogListenerIsVerbose") LmiBool LmiConsoleLogListenerGetMessageOnly(const LmiConsoleLogListener* l);

/**
{function:
	{name: LmiConsoleLogListenerEnableColumns}
	{parent: LmiConsoleLogListener}
	{description: Enables or disables columnar output for a console log's verbose mode. Columnar mode may
		be slightly less verbose but should be easier to read.}
	{prototype: void LmiConsoleLogListenerEnableColumns(LmiConsoleLogListener *listener, LmiBool enable)}
	{parameter: {name: listener} {description: The console log listener object.}}
	{parameter: {name: enable} {description: LMI_TRUE to enable columnar output, LMI_FALSE to disable it.}}
}
*/
void LmiConsoleLogListenerEnableColumns(LmiConsoleLogListener *listener, LmiBool enable);

/**
{function:
	{name: LmiConsoleLogListenerEnableColoring}
	{parent: LmiConsoleLogListener}
	{description: Enables or disables the coloring of log messages based on severity. Colors are changed by
		directly setting the console text color, where this is supported. Currently, this is supported only
		for the Windows Console.}
	{prototype: void LmiConsoleLogListenerEnableColoring(LmiConsoleLogListener *listener, LmiBool enable)}
	{parameter: {name: listener} {description: The console log listener object.}}
	{parameter: {name: enable} {description: LMI_TRUE to enable coloring, LMI_FALSE to disable it.}}
}
*/
void LmiConsoleLogListenerEnableColoring(LmiConsoleLogListener *listener, LmiBool enable);

/**
{function:
	{name: LmiConsoleLogListenerEnableAnsiColoring}
	{parent: LmiConsoleLogListener}
	{description: Enables or disables the coloring of log messages based on severity. Colors are changed by
		inserting ANSI escape codes.}
	{prototype: void LmiConsoleLogListenerEnableAnsiColoring(LmiConsoleLogListener *listener, LmiBool enable)}
	{parameter: {name: listener} {description: The console log listener object.}}
	{parameter: {name: enable} {description: LMI_TRUE to enable ansi coloring, LMI_FALSE to disable it.}}
	{note: Direct console coloring (controlled via LmiConsoleLogListenerEnableColoring) must be off for this setting to have an effect.}
	{note: If the console terminal in use does not recognize ANSI codes, then the log messages will not be displayed properly.}
}
*/
void LmiConsoleLogListenerEnableAnsiColoring(LmiConsoleLogListener *listener, LmiBool enable);

/**
{function:
	{name: LmiConsoleLogListenerGetListener}
	{parent: LmiConsoleLogListener}
	{description: Gets the log listener base class from a file log listener object. The base class
		can be used to call LmiLogListener API functions for the file logger.}
	{prototype: LmiLogListener* LmiConsoleLogListenerGetListener(LmiConsoleLogListener* listener)}
	{parameter:	{name: listener} {description: The file log listener object.}}
	{return: A pointer to the log listener object.}
}
*/
LmiLogListener *LmiConsoleLogListenerGetListener(LmiConsoleLogListener *listener);

LMI_END_EXTERN_C

#endif /* LMI_CONSOLE_LOG_LISTENER_H_ */
