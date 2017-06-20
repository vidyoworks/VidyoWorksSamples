/** 
{file:
	{name: VidyoLogger.h}
	{description: High level client library. }
	{copyright:
		(c) 2013-2015 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_LOGGER_H
#define VIDYO_LOGGER_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Os/LmiConsoleLogListener.h>
#include <Lmi/Os/LmiCachedLogListener.h>
#include <Lmi/Os/LmiFileLogListener.h>
#include <Lmi/VidyoClient/VidyoTransport.h>

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: VidyoLoggerCategory}
	{parent: VidyoLogger}
	{description: }
}
*/
typedef struct
{
	const char *name;
	const char *description;
	LmiVector(LmiString) levels;
} VidyoLoggerCategory;

/**
{function visibility="private":
	{name: VidyoLoggerCategoryConstruct}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: VidyoLoggerCategory* VidyoLoggerCategoryConstruct(VidyoLoggerCategory* loggerCategory, const char* name, const char* description, LmiVector(LmiString)* levels, LmiAllocator* alloc)}
	{parameter:
		{name: loggerCategory}
		{description: }
	}
	{parameter:
		{name: name}
		{description: }
	}
	{parameter:
		{name: description}
		{description: }
	}
	{parameter:
		{name: levels}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLoggerCategory* VidyoLoggerCategoryConstruct(VidyoLoggerCategory* loggerCategory, const char* name, const char* description, LmiVector(LmiString)* levels, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryConstructCopy}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: VidyoLoggerCategory* VidyoLoggerCategoryConstructCopy(VidyoLoggerCategory* d, const VidyoLoggerCategory* s)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
VidyoLoggerCategory* VidyoLoggerCategoryConstructCopy(VidyoLoggerCategory* d, const VidyoLoggerCategory* s);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryAssign}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: VidyoLoggerCategory* VidyoLoggerCategoryAssign(VidyoLoggerCategory* d, const VidyoLoggerCategory* s)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
VidyoLoggerCategory* VidyoLoggerCategoryAssign(VidyoLoggerCategory* d, const VidyoLoggerCategory* s);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryDestruct}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: void VidyoLoggerCategoryDestruct(VidyoLoggerCategory* loggerCategory)}
	{parameter:
		{name: loggerCategory}
		{description: }
	}
}
*/
void VidyoLoggerCategoryDestruct(VidyoLoggerCategory* loggerCategory);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryEqual}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: LmiBool VidyoLoggerCategoryEqual(const VidyoLoggerCategory* d, const VidyoLoggerCategory* s)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLoggerCategoryEqual(const VidyoLoggerCategory* d, const VidyoLoggerCategory* s);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryLess}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: LmiBool VidyoLoggerCategoryLess(const VidyoLoggerCategory* d, const VidyoLoggerCategory* s)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: s}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLoggerCategoryLess(const VidyoLoggerCategory* d, const VidyoLoggerCategory* s);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryGetName}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: const char* VidyoLoggerCategoryGetName(VidyoLoggerCategory* loggerCategory)}
	{parameter:
		{name: loggerCategory}
		{description: }
	}
	{return: }
}
*/
const char* VidyoLoggerCategoryGetName(VidyoLoggerCategory* loggerCategory);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryGetDescription}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: const char* VidyoLoggerCategoryGetDescription(VidyoLoggerCategory* loggerCategory)}
	{parameter:
		{name: loggerCategory}
		{description: }
	}
	{return: }
}
*/
const char* VidyoLoggerCategoryGetDescription(VidyoLoggerCategory* loggerCategory);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryGetNumberOfLevels}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: LmiSizeT VidyoLoggerCategoryGetNumberOfLevels(VidyoLoggerCategory* loggerCategory)}
	{parameter:
		{name: loggerCategory}
		{description: }
	}
	{return: }
}
*/
LmiSizeT VidyoLoggerCategoryGetNumberOfLevels(VidyoLoggerCategory* loggerCategory);

/**
{function visibility="private":
	{name: VidyoLoggerCategoryGetLevelName}
	{parent: VidyoLoggerCategory}
	{description: }
	{prototype: const char* VidyoLoggerCategoryGetLevelName(VidyoLoggerCategory* loggerCategory, LmiSizeT index)}
	{parameter:
		{name: loggerCategory}
		{description: }
	}
	{parameter:
		{name: index}
		{description: }
	}
	{return: }
}
*/
const char* VidyoLoggerCategoryGetLevelName(VidyoLoggerCategory* loggerCategory, LmiSizeT index);


Declare_LmiVector(VidyoLoggerCategory)

/**
{type:
	{name: VidyoLogger}
	{parent: Endpoint}
	{include: Lmi/VidyoClient/VidyoLogger.h}
	{description: }
}
*/
typedef struct
{
	LmiAllocator *alloc;
	LmiLogListener *listener;
} VidyoLogger;

/**
{function visibility="private":
	{name: VidyoLoggerConstruct}
	{parent: VidyoLogger}
	{description: }
	{prototype: VidyoLogger* VidyoLoggerConstruct(VidyoLogger* logger, LmiLogListener* listener, const char* dialogTitle, LmiAllocator* alloc)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: listener}
		{description: }
	}
	{parameter:
		{name: dialogTitle}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLogger* VidyoLoggerConstruct(VidyoLogger* logger, LmiLogListener* listener, const char* dialogTitle, LmiAllocator* alloc);


/**
{function visibility="private":
	{name: VidyoLoggerDestruct}
	{parent: VidyoLogger}
	{description: }
	{prototype: void VidyoLoggerDestruct(VidyoLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
}
*/
void VidyoLoggerDestruct(VidyoLogger* logger);

/**
{function visibility="private":
	{name: VidyoLoggerSetFilter}
	{parent: VidyoLogger}
	{description: }
	{prototype: LmiBool VidyoLoggerSetFilter(VidyoLogger* logger, const char* filter)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: filter}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLoggerSetFilter(VidyoLogger* logger, const char* filter);

/**
{function visibility="private":
	{name: VidyoLoggerSetLevelAndCategory}
	{parent: VidyoLogger}
	{description: }
	{prototype: LmiBool VidyoLoggerSetLevelAndCategory(VidyoLogger* logger, const char* levelName, const char* categoryName, LmiBool on)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: levelName}
		{description: }
	}
	{parameter:
		{name: categoryName}
		{description: }
	}
	{parameter:
		{name: on}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLoggerSetLevelAndCategory(VidyoLogger* logger, const char* levelName, const char* categoryName, LmiBool on);

/**
{function visibility="private":
	{name: VidyoLoggerGetCategoryList}
	{parent: VidyoLogger}
	{description: }
	{prototype: LmiBool VidyoLoggerGetCategoryList(VidyoLogger* logger, LmiVector(VidyoLoggerCategory)* categories)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: categories}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLoggerGetCategoryList(VidyoLogger* logger, LmiVector(VidyoLoggerCategory)* categories);

/**
{function visibility="private":
	{name: VidyoLoggerSetVerbose}
	{parent: VidyoLogger}
	{description: }
	{prototype: void VidyoLoggerSetVerbose(VidyoLogger* logger, LmiBool verbose)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: verbose}
		{description: }
	}
}
*/
void VidyoLoggerSetVerbose(VidyoLogger* logger, LmiBool verbose);

/**
{type:
	{name: VidyoConsoleLogger}
	{parent: VidyoLogger}
	{description: }
}
*/
typedef struct
{
	LmiConsoleLogListener consoleLogger;
	VidyoLogger base;
} VidyoConsoleLogger;

/**
{function visibility="private":
	{name: VidyoConsoleLoggerConstruct}
	{parent: VidyoConsoleLogger}
	{description: }
	{prototype: VidyoConsoleLogger* VidyoConsoleLoggerConstruct(VidyoConsoleLogger* logger, LmiAllocator* alloc)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoConsoleLogger* VidyoConsoleLoggerConstruct(VidyoConsoleLogger* logger, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoConsoleLoggerDestruct}
	{parent: VidyoConsoleLogger}
	{description: }
	{prototype: void VidyoConsoleLoggerDestruct(VidyoConsoleLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
}
*/
void VidyoConsoleLoggerDestruct(VidyoConsoleLogger* logger);


/**
{function:
	{name: VidyoConsoleLoggerGetBase}
	{parent: VidyoConsoleLogger}
	{description: }
	{prototype: VidyoLogger* VidyoConsoleLoggerGetBase(VidyoConsoleLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
	{return: }
}
*/
VidyoLogger* VidyoConsoleLoggerGetBase(VidyoConsoleLogger* logger);

/**
{type:
	{name: VidyoFeedbackLogger}
	{parent: VidyoLogger}
	{description: }
}
*/
typedef struct
{
	LmiLogListener feedbackLogger;
	VidyoLogger base;
} VidyoFeedbackLogger;

/**
{callback visibility="private":
	{name: VidyoFeedbackLoggerCallback}
	{parent: VidyoFeedbackLogger}
	{description: }
	{prototype: void (*VidyoFeedbackLoggerCallback)(LmiLogListener* logger, const LmiLogRecord* logRecord)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: logRecord}
		{description: }
	}
}
*/
typedef void (*VidyoFeedbackLoggerCallback)(LmiLogListener* logger, const LmiLogRecord* logRecord);

/**
{function visibility="private":
	{name: VidyoFeedbackLoggerConstruct}
	{parent: VidyoFeedbackLogger}
	{description: }
	{prototype: VidyoFeedbackLogger* VidyoFeedbackLoggerConstruct(VidyoFeedbackLogger* logger, VidyoFeedbackLoggerCallback callback, LmiVoidPtr userData, LmiAllocator* alloc)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: callback}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoFeedbackLogger* VidyoFeedbackLoggerConstruct(VidyoFeedbackLogger* logger, VidyoFeedbackLoggerCallback callback, LmiVoidPtr userData, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoFeedbackLoggerDestruct}
	{parent: VidyoFeedbackLogger}
	{description: }
	{prototype: void VidyoFeedbackLoggerDestruct(VidyoFeedbackLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
}
*/
void VidyoFeedbackLoggerDestruct(VidyoFeedbackLogger* logger);


/**
{function visibility="private":
	{name: VidyoFeedbackLoggerGetBase}
	{parent: VidyoFeedbackLogger}
	{description: }
	{prototype: VidyoLogger* VidyoFeedbackLoggerGetBase(VidyoFeedbackLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
	{return: }
}
*/
VidyoLogger* VidyoFeedbackLoggerGetBase(VidyoFeedbackLogger* logger);

/**
{type:
	{name: VidyoFileLogger}
	{parent: VidyoLogger}
	{description: }
}
*/
typedef struct
{
	LmiFileLogListener fileLogger;
	VidyoLogger base;
} VidyoFileLogger;

/**
{function visibility="private":
	{name: VidyoFileLoggerConstruct}
	{parent: VidyoFileLogger}
	{description: }
	{prototype: VidyoFileLogger* VidyoFileLoggerConstruct(VidyoFileLogger* logger, const char* fileName, LmiAllocator* alloc)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: fileName}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoFileLogger* VidyoFileLoggerConstruct(VidyoFileLogger* logger, const char* fileName, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoFileLoggerDestruct}
	{parent: VidyoFileLogger}
	{description: }
	{prototype: void VidyoFileLoggerDestruct(VidyoFileLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
}
*/
void VidyoFileLoggerDestruct(VidyoFileLogger* logger);


/**
{function visibility="private":
	{name: VidyoFileLoggerGetBase}
	{parent: VidyoFileLogger}
	{description: }
	{prototype: VidyoLogger* VidyoFileLoggerGetBase(VidyoFileLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
	{return: }
}
*/
VidyoLogger* VidyoFileLoggerGetBase(VidyoFileLogger* logger);

/**
{function visibility="private":
	{name: VidyoFileLoggerCompress}
	{parent: VidyoFileLogger}
	{description: }
	{prototype: LmiBool VidyoFileLoggerCompress(VidyoFileLogger *logger, LmiString *compressedFileName)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: compressedFileName}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoFileLoggerCompress(VidyoFileLogger *logger, LmiString *compressedFileName);

/**
{type:
	{name: VidyoCachedLogger}
	{parent: VidyoLogger}
	{description: }
}
*/

typedef struct
{
	LmiCachedLogListener cachedLogger;
	VidyoLogger base;
} VidyoCachedLogger;

/**
{function visibility="private":
	{name: VidyoCachedLoggerConstruct}
	{parent: VidyoCachedLogger}
	{description: }
	{prototype: VidyoCachedLogger* VidyoCachedLoggerConstruct(VidyoCachedLogger* logger, LmiInt64 maxRecords, LmiAllocator* alloc)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: maxRecords}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoCachedLogger* VidyoCachedLoggerConstruct(VidyoCachedLogger* logger, LmiInt64 maxRecords, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoCachedLoggerDestruct}
	{parent: VidyoCachedLogger}
	{description: }
	{prototype: void VidyoCachedLoggerDestruct(VidyoCachedLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
}
*/
void VidyoCachedLoggerDestruct(VidyoCachedLogger* logger);


/**
{function visibility="private":
	{name: VidyoCachedLoggerGetBase}
	{parent: VidyoCachedLogger}
	{description: }
	{prototype: VidyoLogger* VidyoCachedLoggerGetBase(VidyoCachedLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
	{return: }
}
*/
VidyoLogger* VidyoCachedLoggerGetBase(VidyoCachedLogger* logger);

/**
{function visibility="private":
	{name: VidyoCachedLoggerGetLogRecords}
	{parent: VidyoCachedLogger}
	{description: Gets the log records from a cached log listener object.}
	{prototype: LmiUint64 VidyoCachedLoggerGetLogRecords(VidyoCachedLogger *logger, LmiUint64 lastIndexOfPreviousQuery, LmiUint64 maxRecords, const char *bodyFilter, const char *notInBodyFilter, const char *levelCategoryFilter, LmiVector(LmiCachedLogRecord) *records)}
	{parameter:	{name: logger} {description: The cached log listener object.}}
	{parameter:	{name: lastIndexOfPreviousQuery} {description: Index of the last entry from the previous query.}}
	{parameter:	{name: maxRecords} {description: Maximum number of records to return.}}
	{parameter:	{name: bodyFilter} {description: Log record body should match this filter.}}
	{parameter:	{name: notInBodyFilter} {description: Log record body should not match this filter.}}
	{parameter:	{name: levelCategoryFilter} {description: Subset of the main filter of the level and category to apply per query.}}
	{parameter:	{name: records} {description: The vector where the records will be copied.}}
	{return: The new index from the last log record.}
}
*/
LmiUint64 VidyoCachedLoggerGetLogRecords(VidyoCachedLogger *logger, LmiUint64 lastIndexOfPreviousQuery, LmiUint64 maxRecords, const char *bodyFilter, const char *notInBodyFilter, const char *levelCategoryFilter, LmiVector(LmiCachedLogRecord) *records);

/**
{type:
	{name: VidyoHttpLogger}
	{parent: VidyoLogger}
	{description: }
}
*/
typedef struct
{
	LmiVoidPtr httpServer;
	VidyoCachedLogger cachedLogger;
	LmiAllocator *alloc;
} VidyoHttpLogger;

/**
{function visibility="private":
	{name: VidyoHttpLoggerConstruct}
	{parent: VidyoHttpLogger}
	{description: }
	{prototype: VidyoHttpLogger* VidyoHttpLoggerConstruct(VidyoHttpLogger* logger, VidyoTransport *transport, LmiUint port, LmiAllocator* alloc)}
	{parameter:
		{name: logger}
		{description: }
	}
	{parameter:
		{name: transport}
		{description: }
	}
	{parameter:
		{name: port}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoHttpLogger* VidyoHttpLoggerConstruct(VidyoHttpLogger* logger, VidyoTransport *transport, LmiUint port, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoHttpLoggerDestruct}
	{parent: VidyoHttpLogger}
	{description: }
	{prototype: void VidyoHttpLoggerDestruct(VidyoHttpLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
}
*/
void VidyoHttpLoggerDestruct(VidyoHttpLogger* logger);


/**
{function visibility="private":
	{name: VidyoHttpLoggerGetBase}
	{parent: VidyoHttpLogger}
	{description: }
	{prototype: VidyoLogger* VidyoHttpLoggerGetBase(VidyoHttpLogger* logger)}
	{parameter:
		{name: logger}
		{description: }
	}
	{return: }
}
*/
VidyoLogger* VidyoHttpLoggerGetBase(VidyoHttpLogger* logger);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoLoggerInline.h"
#endif

#endif /* VIDYO_LOGGER_H */
