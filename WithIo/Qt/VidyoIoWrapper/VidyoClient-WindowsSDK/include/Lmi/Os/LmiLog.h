/** {file:
	  {name: LmiLog.h}
	  {description: Logging interface.}
	  {copyright:
	  	(c) 2005-2015 Vidyo, Inc.,
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
#ifndef LMI_LOG_H_
#define LMI_LOG_H_

/*#define LMI_NO_LOGGING*/

#ifdef LMI_NO_LOGGING

#define LMI_LOG_NO_FATAL
#define LMI_LOG_NO_ERROR
#define LMI_LOG_NO_WARNING
#define LMI_LOG_NO_DEBUG
#define LMI_LOG_NO_INFO
#define LMI_LOG_NO_SENT
#define LMI_LOG_NO_RECEIVED

#undef LMI_LOG_WANT_ENTER
#undef LMI_LOG_WANT_LEAVE
#endif



#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiRestrictedBitset.h>
#include <Lmi/Utils/LmiBitset.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Os/LmiTime.h>
#include <Lmi/Os/LmiThread.h>

LMI_BEGIN_EXTERN_C

/**
   {package:
	 {name: Log}
	 {parent: Os}
	 {include: Lmi/Os/LmiLog.h}
	 {description: Log system events.}
   }
*/

/**
   {function:
	 {name: LmiLogInitialize}
	 {parent: Log}
	 {description: Initialize the LmiLog package.}
	 {prototype: LmiBool LmiLogInitialize(void)}
	 {return: LMI_TRUE on success, LMI_FALSE on initialization failure.}
   }
*/
LmiBool LmiLogInitialize(void);


/**
   {function:
	 {name: LmiLogUninitialize}
	 {parent: Log}
	 {description: Uninitialize the LmiLog package.}
	 {prototype: void LmiLogUninitialize(void)}
   }
*/
void LmiLogUninitialize(void);

/**
   {type:
	 {name: LmiLogLevel}
	 {parent: Log}
	 {description: An identifier for the level, or type, of a logged
	   event.  This indicates the degree of significance of the event.}
	 {value:
	   {name: LMI_LOGLEVEL_FATAL}
	   {description: The event being logged describes a fatal error.  In
		 all likelihood system execution will not be able to continue.}}
	 {value:
	   {name: LMI_LOGLEVEL_ERROR}
	   {description: The event being logged describes a continuable error.
		 The system should be able to continue, but human intervention or
		 diagnosis may be necessary.}}
	 {value:
	   {name: LMI_LOGLEVEL_WARNING}
	   {description: The event being logged describes a warning.  Something
		 has occurred which may require attention or action, but which is not
		 actually erroneous.}}
	 {value:
	   {name: LMI_LOGLEVEL_INFO}
	   {description: The event being logged describes information which may
		 be useful or informative to a user of the system.	No problems are
		 being reported.}}
	 {value:
	   {name: LMI_LOGLEVEL_DEBUG}
	   {description: The event being logged describes information which may
		 be useful to a developer to understand the code.  The information is
		 not expected to be useful to users of the system.}}
	 {value:
	   {name: LMI_LOGLEVEL_SENT}
	   {description: The event being logged describes data that has been
		 transmitted by the system.}}
	 {value:
	   {name: LMI_LOGLEVEL_RECEIVED}
	   {description: The event being logged describes data that has been
		 received by the system.}}
	 {value:
	   {name: LMI_LOGLEVEL_ENTER}
	   {description: The event being logged describes the system entering
		 a function.}}
	 {value:
	   {name: LMI_LOGLEVEL_LEAVE}
	   {description: The event being logged describes the system leaving
		 from a function.}}
	 {value:
	   {name: LMI_LOGLEVEL_INVALID}
	   {description: A value that does not represent a valid log level.  This
	     value is returned by LmiLogGetLevelByName and LmiLogGetLevelByIndex
		 on invalid input.}}
	 {value replaced-by="LMI_LOGLEVEL_FATAL":
	   {name: LMI_LOG_FATAL}
	   {description: Deprecated name for LMI_LOGLEVEL_FATAL.}}
	 {value replaced-by="LMI_LOGLEVEL_ERROR":
	   {name: LMI_LOG_ERROR}
	   {description: Deprecated name for LMI_LOGLEVEL_ERROR.}}
	 {value replaced-by="LMI_LOGLEVEL_WARNING":
	   {name: LMI_LOG_WARNING}
	   {description: Deprecated name for LMI_LOGLEVEL_WARNING.}}
	 {value replaced-by="LMI_LOGLEVEL_INFO":
	   {name: LMI_LOG_INFO}
	   {description: Deprecated name for LMI_LOGLEVEL_INFO.}}
	 {value replaced-by="LMI_LOGLEVEL_DEBUG":
	   {name: LMI_LOG_DEBUG}
	   {description: Deprecated name for LMI_LOGLEVEL_DEBUG.}}
	 {value replaced-by="LMI_LOGLEVEL_SENT":
	   {name: LMI_LOG_SENT}
	   {description: Deprecated name for LMI_LOGLEVEL_SENT.}}
	 {value replaced-by="LMI_LOGLEVEL_RECEIVED":
	   {name: LMI_LOG_RECEIVED}
	   {description: Deprecated name for LMI_LOGLEVEL_RECEIVED.}}
	 {value replaced-by="LMI_LOGLEVEL_ENTER":
	   {name: LMI_LOG_ENTER}
	   {description: Deprecated name for LMI_LOGLEVEL_ENTER.}}
	 {value replaced-by="LMI_LOGLEVEL_LEAVE":
	   {name: LMI_LOG_LEAVE}
	   {description: Deprecated name for LMI_LOGLEVEL_LEAVE.}}
	 {value replaced-by="LMI_LOGLEVEL_INVALID":
	   {name: LMI_LOG_LEVEL_INVALID}
	   {description: Deprecated name for LMI_LOGLEVEL_INVALID.}}
  }
*/
typedef enum {
  LMI_LOGLEVEL_FATAL,
  LMI_LOGLEVEL_ERROR,
  LMI_LOGLEVEL_WARNING,
  LMI_LOGLEVEL_INFO,
  LMI_LOGLEVEL_DEBUG,
  LMI_LOGLEVEL_SENT,
  LMI_LOGLEVEL_RECEIVED,
  LMI_LOGLEVEL_ENTER,
  LMI_LOGLEVEL_LEAVE,

  LMI_LOGLEVEL_INVALID,
  LMI_LOG_NUM_LEVELS = LMI_LOGLEVEL_INVALID,

  LMI_LOG_FATAL = LMI_LOGLEVEL_FATAL,
  LMI_LOG_ERROR = LMI_LOGLEVEL_ERROR,
  LMI_LOG_WARNING = LMI_LOGLEVEL_WARNING,
  LMI_LOG_INFO = LMI_LOGLEVEL_INFO,
  LMI_LOG_DEBUG = LMI_LOGLEVEL_DEBUG,
  LMI_LOG_SENT = LMI_LOGLEVEL_SENT,
  LMI_LOG_RECEIVED = LMI_LOGLEVEL_RECEIVED,
  LMI_LOG_ENTER = LMI_LOGLEVEL_ENTER,
  LMI_LOG_LEAVE = LMI_LOGLEVEL_LEAVE,

  LMI_LOG_LEVEL_INVALID = LMI_LOGLEVEL_INVALID
} LmiLogLevel;

/* Mask of all the "normal" levels */
#define LMI_LOG_ALL_LEVELS_ (LmiRestrictedBitsetValueGet(LMI_LOG_NUM_LEVELS) - 1)

/**
   {function:
	 {name: LmiLogLevelGetName}
	 {parent: LmiLogLevel}
	 {description: Get a textual name of a log level, suitable for use
	   in log output.}
	 {prototype: const char* LmiLogLevelGetName(LmiLogLevel level)}
	 {parameter:
	   {name: level}
	   {description: The identifier value for the level whose name to get.}}
	 {return: The name of the level.  If the passed-in level is invalid,
	   returns NULL.}
	 {note: The names of the levels are currently written in all capital
	   letters.}
  }
*/
const char* LmiLogLevelGetName(LmiLogLevel level);


/**
   {function replaced-by="LmiLogGetNumberOfLevels":
	 {name: LmiLogLevelGetCount}
	 {parent: LmiLogLevel}
	 {description: Get the number of log levels.}
	 {prototype: LmiSizeT LmiLogLevelGetCount(void)}
	 {return: The number of log levels.}
   }
*/
LMI_INLINE_DECLARATION LMI_DEPRECATED("Deprecated, replaced by LmiLogGetNumberOfLevels") LmiSizeT LmiLogLevelGetCount(void);

/**
   {function:
	 {name: LmiLogGetNumberOfLevels}
	 {parent: Log}
	 {description: Get the number of log levels.}
	 {prototype: LmiSizeT LmiLogGetNumberOfLevels(void)}
	 {return: The number of log levels.}
   }
*/
LMI_INLINE_DECLARATION LmiSizeT LmiLogGetNumberOfLevels(void);

/**
   {function replaced-by="LmiLogGetLevelByName":
	 {name: LmiLogLevelGetByName}
	 {parent: LmiLogLevel}
	 {description: Get an identifier for an LmiLogLevel based on its
	   name.}
	 {prototype: LmiLogLevel LmiLogLevelGetByName(const char* name)}
	 {parameter:
	   {name: name}
	   {description: The name of an LmiLogLevel whose identifier to
		 retrieve.}}
	 {return: The identifier the level,
	   or LMI_LOGLEVEL_INVALID if no such level is defined.}
	 {note: Level names are compared case-insensitively.}
	 {note: This function is linear in the number of levels.}
   }
*/
LMI_INLINE_DECLARATION LMI_DEPRECATED("Deprecated, replaced by LmiLogGetLevelByName") LmiLogLevel LmiLogLevelGetByName(const char* name);

/**
   {function:
	 {name: LmiLogGetLevelByName}
	 {parent: Log}
	 {description: Get an identifier for an LmiLogLevel based on its
	   name.}
	 {prototype: LmiLogLevel LmiLogGetLevelByName(const char* name)}
	 {parameter:
	   {name: name}
	   {description: The name of an LmiLogLevel whose identifier to
		 retrieve.}}
	 {return: An identifier for the level,
	   or LMI_LOGLEVEL_INVALID if no such level is defined.}
	 {note: Level names are compared case-insensitively.}
	 {note: This function is linear in the number of levels.}
   }
*/
LmiLogLevel LmiLogGetLevelByName(const char* name);


/**
   {function:
	 {name: LmiLogGetLevelByIndex}
	 {parent: Log}
	 {description: Get an identifier for an LmiLogLevel based on its index.}
	 {prototype: LmiLogLevel LmiLogGetLevelByIndex(LmiSizeT levelIndex)}
	 {parameter:
	   {name: levelIndex}
	   {description: The index of an LmiLogLevel whose identifier to
		 retrieve.  This must be less than the value returned by
		 LmiLogGetNumberOfLevels.}}
	 {return: An identifier for the level,
	   or LMI_LOGLEVEL_INVALID if no such level is defined.}
   }
*/
LmiLogLevel LmiLogGetLevelByIndex(LmiSizeT levelIndex);


/**
   {type:
	 {name: LmiLogLevelSet}
	 {parent: Log}
	 {description: A collection of log level identifier values.}
   }
*/
typedef LmiRestrictedBitset LmiLogLevelSet;

/**
   {function:
     {name: LmiLogLevelSetConstruct}
     {parent: LmiLogLevelSet}
     {description: Construct a log level set (with no levels).}
     {prototype: LmiLogLevelSet* LmiLogLevelSetConstruct(LmiLogLevelSet* s)}
     {parameter:
       {name: s}
       {description: The log level set to construct.}}
     {return: s on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiLogLevelSet* LmiLogLevelSetConstruct(LmiLogLevelSet* s);


/**
   {function:
     {name: LmiLogLevelSetConstructWithLevel}
     {parent: LmiLogLevelSet}
     {description: Construct a log level set with one level included.}
     {prototype: LmiLogLevelSet* LmiLogLevelSetConstructWithLevel(LmiLogLevelSet* s, LmiLogLevel level)}
     {parameter:
       {name: s}
       {description: The log level set to construct.}}
     {parameter:
       {name: level}
       {description: The initial log level to include.}}
     {return: s on success, NULL on failure.}
   }
*/
LMI_INLINE_DECLARATION LmiLogLevelSet* LmiLogLevelSetConstructWithLevel(LmiLogLevelSet* s, LmiLogLevel level);


/**
   {function:
     {name: LmiLogLevelSetDestruct}
     {parent: LmiLogLevelSet}
     {description: Destruct a log level set.}
     {prototype: void LmiLogLevelSetDestruct(LmiLogLevelSet* s)}
     {parameter:
       {name: s}
       {description: The level set to destruct.}}
   }
*/
LMI_INLINE_DECLARATION void LmiLogLevelSetDestruct(LmiLogLevelSet * s);


/**
   {function:
     {name: LmiLogLevelSetAddLevel}
     {parent: LmiLogLevelSet}
     {description: Add a log level to a log level set.}
     {prototype: LmiBool LmiLogLevelSetAddLevel(LmiLogLevelSet* s, LmiLogLevel l)}
     {parameter:
       {name: s}
       {description: The log level set to which to add a level.}}
     {parameter:
       {name: l}
       {description: The level to add to the set.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogLevelSetAddLevel(LmiLogLevelSet* s, LmiLogLevel l);


/**
   {function:
     {name: LmiLogLevelSetAddAllLevels}
     {parent: LmiLogLevelSet}
     {description: Add all levels to an LmiLogLevelSet.}
     {prototype: void LmiLogLevelSetAddAllLevels(LmiLogLevelSet* s)}
     {parameter:
       {name: s}
       {description: The log level set to which add all log levels.}}
   }
*/
LMI_INLINE_DECLARATION void LmiLogLevelSetAddAllLevels(LmiLogLevelSet* s);


/**
   {function:
     {name: LmiLogLevelSetRemoveLevel}
     {parent: LmiLogLevelSet}
     {description: Remove a log level from a log level set.}
     {prototype: LmiBool LmiLogLevelSetRemoveLevel(LmiLogLevelSet* s, LmiLogLevel l)}
     {parameter:
       {name: s}
       {description: The log level set from which to remove a level.}}
     {parameter:
       {name: l}
       {description: The log level to remove.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogLevelSetRemoveLevel(LmiLogLevelSet* s, LmiLogLevel l);

/**
   {function:
     {name: LmiLogLevelSetRemoveAllLevels}
     {parent: LmiLogLevelSet}
     {description: Remove all levels from an LmiLogLevelSet.}
     {prototype: void LmiLogLevelSetRemoveAllLevels(LmiLogLevelSet* s)}
     {parameter:
       {name: s}
       {description: The log level set from which to remove all the levels.}}
   }
*/
LMI_INLINE_DECLARATION void LmiLogLevelSetRemoveAllLevels(LmiLogLevelSet* l);


/**
   {function:
     {name: LmiLogLevelSetHasLevel}
     {parent: LmiLogLevelSet}
     {description: Check whether a log level set contains a given log level.}
     {prototype: LmiBool LmiLogLevelSetHasLevel(const LmiLogLevelSet* s, LmiLogLevel l)}
     {parameter:
       {name: s}
       {description: The log level set in which to check for a level.}}
     {parameter:
       {name: l}
       {description: The level to check for.}}
     {return: LMI_TRUE if the log level set contains the given log level,
       LMI_FALSE if not.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogLevelSetHasLevel(const LmiLogLevelSet* s, LmiLogLevel l);


/**
   {function:
     {name: LmiLogLevelSetIsEmpty}
     {parent: LmiLogLevelSet}
     {description: Check whether a log level set is entirely empty.}
     {prototype: LmiBool LmiLogLevelSetIsEmpty(const LmiLogLevelSet* s)}
     {parameter:
       {name: s}
       {description: The log level set in which to check for any levels.}}
     {return: LMI_TRUE if the level set contains no levels,
       LMI_FALSE otherwise.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogLevelSetIsEmpty(const LmiLogLevelSet* s);



/**
   {type:
	 {name: LmiLogCategory}
	 {parent: Log}
	 {description: An identifier of a category within which a logged event
	   occurred.}
	 {constant:
	   {name: LMI_LOGCATEGORY_INVALID}
	   {type: LmiLogCategory}
	   {description: A value representing an invalid or unregistered category.}}
	 {constant replaced-by="LMI_LOGCATEGORY_INVALID":
	   {name: LMI_LOG_CATEGORY_INVALID}
	   {type: LmiLogCategory}
	   {description: Deprecated name for LMI_LOGCATEGORY_INVALID.}}
   }
*/
typedef LmiSizeT LmiLogCategory;

#define LMI_LOGCATEGORY_INVALID ((LmiLogCategory)LMI_SIZE_T_MAX)
#define LMI_LOG_CATEGORY_INVALID LMI_LOGCATEGORY_INVALID

/**
   {function replaced-by="LmiLogRegisterCategory":
	 {name: LmiLogCategoryRegister}
	 {parent: LmiLogCategory}
	 {description: Register the name of an LmiLogCategory}
	 {prototype: LmiLogCategory LmiLogCategoryRegister(const char* name)}
	 {parameter:
	   {name: name}
	   {description: The name of a category to use.}}
	 {return: A category number, or LMI_LOGCATEGORY_INVALID on too many
	   categories.}
	 {note: This function must be called before any function which calls a
	   logging function using this category.  Typically category registration
	   should be done early in a category\'s Initialize function.}
	 {note: There is a limit, currently 512, on the number of categories that
	   may be registered with the logging system.}
	 {note: There is no way to unregister a category.}
	 {note: Categories registered using this (deprecated) API will have
	   descriptions consisting of the empty string.}
  }
*/
LMI_INLINE_DECLARATION LMI_DEPRECATED("Deprecated, replaced by LmiLogRegisterCategory") LmiLogCategory LmiLogCategoryRegister(const char* name);

/**
   {function:
	 {name: LmiLogRegisterCategory}
	 {parent: Log}
	 {description: Create and register a log category.}
	 {prototype: LmiLogCategory LmiLogRegisterCategory(const char* name, const char* description)}
	 {parameter:
	   {name: name}
	   {description: The name of a log category to create and register.}}
	 {parameter:
	   {name: description}
	   {description: A description of the log category being registered.}}
	 {return: An identifier for the category, or LMI_LOGCATEGORY_INVALID if
	   too many categories have been registered.}
	 {note: This function must be called before any function which calls a
	   logging function using this category.  Typically category registration
	   should be done early in a library\'s Initialize function, early in its
	   categories\' execution.}
	 {note: There is a limit, currently 512, on the number of categories that
	   may be registered with the logging system.}
	 {note: There is no way to unregister a category.}
  }
*/
LmiLogCategory LmiLogRegisterCategory(const char* name, const char* description);


/**
   {function:
	 {name: LmiLogCategoryGetName}
	 {parent: LmiLogCategory}
	 {description: Get the name of a registered LmiLogCategory.}
	 {prototype: const char* LmiLogCategoryGetName(LmiLogCategory p)}
	 {parameter:
	   {name: p}
	   {description: The LmiLogCategory identifier whose name to get.}}
	 {return: The name of the category, as passed to LmiLogRegisterCategory,
	   or NULL if no such category has been registered.}
   }
*/
const char* LmiLogCategoryGetName(LmiLogCategory p);


/**
   {function:
	 {name: LmiLogCategoryGetDescription}
	 {parent: LmiLogCategory}
	 {description: Get the description of a registered LmiLogCategory.}
	 {prototype: const char* LmiLogCategoryGetDescription(LmiLogCategory p)}
	 {parameter:
	   {name: p}
	   {description: The LmiLogCategory identifier whose description to get.}}
	 {return: The description of the category, as passed to LmiLogRegisterCategory,
	   or NULL if no such category has been registered.}
	 {note: Categories registered using the deprecated LmiLogCategoryRegister
	   API will have descriptions consisting of the empty string.}
   }
*/
const char* LmiLogCategoryGetDescription(LmiLogCategory p);


/**
   {function replaced-by="LmiLogGetNumberOfCategories":
	 {name: LmiLogCategoryGetCount}
	 {parent: LmiLogCategory}
	 {description: Get the number of registered log categories.}
	 {prototype: LmiSizeT LmiLogCategoryGetCount(void)}
	 {return: The number of registered log categories.}
   }
*/
LMI_INLINE_DECLARATION LMI_DEPRECATED("Deprecated, replaced by LmiLogGetNumberOfCategories") LmiSizeT LmiLogCategoryGetCount(void);


/**
   {function:
	 {name: LmiLogGetNumberOfCategories}
	 {parent: Log}
	 {description: Get the number of registered log categories.}
	 {prototype: LmiSizeT LmiLogGetNumberOfCategories(void)}
	 {return: The number of registered log categories.}
   }
*/
LmiSizeT LmiLogGetNumberOfCategories(void);


/**
   {function replaced-by="LmiLogGetCategoryByName":
	 {name: LmiLogCategoryGetByName}
	 {parent: LmiLogCategory}
	 {description: Get the identifier for a registered log category based on its
	   name.}
	 {prototype: LmiLogCategory LmiLogCategoryGetByName(const char* name)}
	 {parameter:
	   {name: name}
	   {description: The name of an LmiLogCategory whose identifier to
		 retrieve.}}
	 {return: The identifier for the category, as returned by LmiLogRegisterCategory,
	   or LMI_LOGCATEGORY_INVALID if no such category has been
	   registered.}
	 {note: This function is linear in the number of registered categories.}
   }
*/
LMI_INLINE_DECLARATION LMI_DEPRECATED("Deprecated, replaced by LmiLogGetCategoryByName") LmiLogCategory LmiLogCategoryGetByName(const char* name);


/**
   {function:
	 {name: LmiLogGetCategoryByName}
	 {parent: Log}
	 {description: Get the identifier for a registered log category based on its
	   name.}
	 {prototype: LmiLogCategory LmiLogGetCategoryByName(const char* name)}
	 {parameter:
	   {name: name}
	   {description: The name of an LmiLogCategory whose identifier to
		 retrieve.}}
	 {return: The identifier for the category, as returned by LmiLogRegisterCategory,
	   or LMI_LOGCATEGORY_INVALID if no such category has been
	   registered.}
	 {note: This function is linear in the number of registered categories.}
   }
*/
LmiLogCategory LmiLogGetCategoryByName(const char* name);


/**
   {function:
	 {name: LmiLogGetCategoryByIndex}
	 {parent: Log}
	 {description: Get the identifier for a registered log category based on its
	   index.}
	 {prototype: LmiLogCategory LmiLogGetCategoryByIndex(LmiSizeT categoryIndex)}
	 {parameter:
	   {name: categoryIndex}
	   {description: The index of an LmiLogCategory whose identifier to
		 retrieve.  This must be less than the value returned by
		 LmiLogGetNumberOfCategories.}}
	 {return: The identifier for the category, as returned by LmiLogRegisterCategory,
	   or LMI_LOGCATEGORY_INVALID if no such category has been
	   registered.}
   }
*/
LmiLogCategory LmiLogGetCategoryByIndex(LmiSizeT categoryIndex);


/**
	{function:
		{name: LmiLogGetAllCategories}
		{parent: Log}
		{description: Get the names of all registered log categories.}
		{prototype: void LmiLogGetAllCategories(LmiVector(LmiString) *categories)}
		{parameter:
			{name: categories}
			{description: The names of all the log categories will be appended to this vector.}
		}
	}
*/
void LmiLogGetAllCategories(LmiVector(LmiString) *categories);


/**
   {type:
	 {name: LmiLogCategorySet}
	 {parent: Log}
	 {description: A collection of LmiLogCategory values.}
   }
*/
typedef LmiBitset LmiLogCategorySet;


/**
   {function:
     {name: LmiLogCategorySetConstruct}
     {parent: LmiLogCategorySet}
     {description: Construct a log category set (with no categories).}
     {prototype: LmiLogCategorySet* LmiLogCategorySetConstruct(LmiLogCategorySet* s, LmiAllocator* a)}
     {parameter:
       {name: s}
       {description: The log category set to construct.}}
	 {parameter:
	   {name: a}
	   {description: Allocator to use for dynamically-allocated memory for the log category.}}
     {return: s on success, NULL on failure.}
   }
*/
LmiLogCategorySet* LmiLogCategorySetConstruct(LmiLogCategorySet* s, LmiAllocator* a);


/**
   {function:
     {name: LmiLogCategorySetConstructWithCategory}
     {parent: LmiLogCategorySet}
     {description: Construct a log category set with one category included).}
     {prototype: LmiLogCategorySet* LmiLogCategorySetConstructWithCategory(LmiLogCategorySet* s, LmiLogCategory category, LmiAllocator* a)}
     {parameter:
       {name: s}
       {description: The log category set to construct.}}
     {parameter:
       {name: category}
       {description: The initial log category to include.}}
	 {parameter:
	   {name: a}
	   {description: Allocator to use for dynamically-allocated memory for the log category.}}
     {return: s on success, NULL on failure.}
   }
*/
LmiLogCategorySet* LmiLogCategorySetConstructWithCategory(LmiLogCategorySet* s, LmiLogCategory category, LmiAllocator* a);


/**
   {function:
     {name: LmiLogCategorySetDestruct}
     {parent: LmiLogCategorySet}
     {description: Destruct a log category set.}
     {prototype: void LmiLogCategorySetDestruct(LmiLogCategorySet* s)}
     {parameter:
       {name: s}
       {description: The category set to destruct.}}
   }
*/
LMI_INLINE_DECLARATION void LmiLogCategorySetDestruct(LmiLogCategorySet * s);


/**
   {function:
     {name: LmiLogCategorySetAddCategory}
     {parent: LmiLogCategorySet}
     {description: Add a log category to a log category set.}
     {prototype: LmiBool LmiLogCategorySetAddCategory(LmiLogCategorySet* s, LmiLogCategory l)}
     {parameter:
       {name: s}
       {description: The log category set to which to add a category.}}
     {parameter:
       {name: l}
       {description: The category to add to the set.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogCategorySetAddCategory(LmiLogCategorySet* s, LmiLogCategory l);


/**
   {function:
     {name: LmiLogCategorySetAddAllCategories}
     {parent: LmiLogCategorySet}
     {description: Add all categories to an LmiLogCategorySet.}
     {prototype: LmiBool LmiLogCategorySetAddAllCategories(LmiLogCategorySet* s)}
     {parameter:
       {name: s}
       {description: The log category set to which add all log categories.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LmiBool LmiLogCategorySetAddAllCategories(LmiLogCategorySet* s);


/**
   {function:
     {name: LmiLogCategorySetRemoveCategory}
     {parent: LmiLogCategorySet}
     {description: Remove a log category from a log category set.}
     {prototype: LmiBool LmiLogCategorySetRemoveCategory(LmiLogCategorySet* s, LmiLogCategory l)}
     {parameter:
       {name: s}
       {description: The log category set from which to remove a category.}}
     {parameter:
       {name: l}
       {description: The log category to remove.}}
     {return: LMI_TRUE on success, else LMI_FALSE.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogCategorySetRemoveCategory(LmiLogCategorySet* s, LmiLogCategory l);

/**
   {function:
     {name: LmiLogCategorySetRemoveAllCategories}
     {parent: LmiLogCategorySet}
     {description: Remove all categories from an LmiLogCategorySet.}
     {prototype: void LmiLogCategorySetRemoveAllCategories(LmiLogCategorySet* s)}
     {parameter:
       {name: s}
       {description: The log category set from which to remove all the categories.}}
   }
*/
LMI_INLINE_DECLARATION void LmiLogCategorySetRemoveAllCategories(LmiLogCategorySet* l);


/**
   {function:
     {name: LmiLogCategorySetHasCategory}
     {parent: LmiLogCategorySet}
     {description: Check whether a log category set contains a given log category.}
     {prototype: LmiBool LmiLogCategorySetHasCategory(const LmiLogCategorySet* s, LmiLogCategory l)}
     {parameter:
       {name: s}
       {description: The log category set in which to check for a category.}}
     {parameter:
       {name: l}
       {description: The category to check for.}}
     {return: LMI_TRUE if the log category set contains the given log category,
       LMI_FALSE if not.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogCategorySetHasCategory(const LmiLogCategorySet* s, LmiLogCategory l);


/**
   {function:
     {name: LmiLogCategorySetIsEmpty}
     {parent: LmiLogCategorySet}
     {description: Check whether a log category set is entirely empty.}
     {prototype: LmiBool LmiLogCategorySetIsEmpty(const LmiLogCategorySet* s)}
     {parameter:
       {name: s}
       {description: The log category set in which to check for any categories.}}
     {return: LMI_TRUE if the category set contains no categories,
       LMI_FALSE otherwise.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogCategorySetIsEmpty(const LmiLogCategorySet* s);


/**
   {function:
     {name: LmiLogHasListener}
	 {parent: Log}
	 {description: Test whether any listener is listening to the given log
	   level and category.}
	 {prototype: LmiBool LmiLogHasListener(LmiLogLevel level, LmiLogCategory category)}
	 {parameter:
	   {name: level}
	   {description: The log level to test.}}
	 {parameter:
	   {name: category}
	   {description: The log category to test.}}
	 {return: LMI_TRUE if any log listener would listen to a log event with the
	   given log level and category; LMI_FALSE otherwise.}
	 {note: This function can be used before expensive logging tests are done,
	   for example if strings need to be formatted for the output.}
	 {note: This function is currently linear in the number of log listeners,
	   so it should only be used if the processing necessary for logging is
	   fairly expensive.}
   }
*/
LMI_INLINE_DECLARATION LmiBool LmiLogHasListener(LmiLogLevel level, LmiLogCategory category);

/* Internal version of the above. */
LmiBool LmiLogHasListener_(LmiLogLevel level, LmiLogCategory category);


/**
   {type:
	 {name: LmiLogRecord}
	 {parent: Log}
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
		{name: function}
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
  LmiLogLevel level;
  LmiLogCategory category;
  const char * file;
  LmiInt line;
  const char * function;
  const char * message;
  const char * threadName;
  LmiThreadId  threadId;
  LmiTime eventTime;
} LmiLogRecord;


/**
   {function:
	 {name: LmiLogRecordGetLevel}
	 {parent: LmiLogRecord}
	 {description: Get the level associated with a logged event.}
	 {prototype: LmiLogLevel LmiLogRecordGetLevel(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the level.}}
	 {return: The level of the message described by this log record.}
	 {note: This will always be a single level.}
	}
*/
LMI_INLINE_DECLARATION LmiLogLevel LmiLogRecordGetLevel(const LmiLogRecord* r);


/**
   {function:
	 {name: LmiLogRecordGetCategory}
	 {parent: LmiLogRecord}
	 {description: Get the category associated with a logged event.}
	 {prototype: LmiLogCategory LmiLogRecordGetCategory(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the category.}}
	 {return: The category associated with the message described by this
	   log record.}
	 {note: This will always be a single category.}
	}
*/
LMI_INLINE_DECLARATION LmiLogCategory LmiLogRecordGetCategory(const LmiLogRecord* r);


/**
   {function:
	 {name: LmiLogRecordGetFile}
	 {parent: LmiLogRecord}
	 {description: Get the filename associated with a logged event.}
	 {prototype: const char* LmiLogRecordGetFile(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a file name.}}
	 {return: The name of the C source file which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the empty string "".}
	}
*/
LMI_INLINE_DECLARATION const char* LmiLogRecordGetFile(const LmiLogRecord* r);


/**
   {function:
	 {name: LmiLogRecordGetLine}
	 {parent: LmiLogRecord}
	 {description: Get the line number associated with a logged event.}
	 {prototype: LmiInt LmiLogRecordGetLine(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a line number.}}
	 {return: The line number of the C source which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the value 0.}
	}
*/
LMI_INLINE_DECLARATION LmiInt LmiLogRecordGetLine(const LmiLogRecord* r);


/**
   {function:
	 {name: LmiLogRecordGetFunction}
	 {parent: LmiLogRecord}
	 {description: Get the name of the function associated with a logged
	   event.}
	 {prototype: const char* LmiLogRecordGetFunction(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain a function name.}}
	 {return: The name of the C source function which logged the message
	   described by this log record.  If this is not available or not
	   meaningful, this will be the value "".}
	}
*/
LMI_INLINE_DECLARATION const char* LmiLogRecordGetFunction(const LmiLogRecord* r);


/**
   {function:
	 {name: LmiLogRecordGetMessage}
	 {parent: LmiLogRecord}
	 {description: Get the message associated with a logged event.}
	 {prototype: const char* LmiLogRecordGetMessage(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the message.}}
	 {return: The message described by this log record.	 If this is not
	   available or not meaningful, this will be the value "".}
	}
*/
LMI_INLINE_DECLARATION const char* LmiLogRecordGetMessage(const LmiLogRecord* r);


/**
   {function:
	 {name: LmiLogRecordGetThreadName}
	 {parent: LmiLogRecord}
	 {description: Get the name of the thread associated with a logged event.}
	 {prototype: const char* LmiLogRecordGetThreadName(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the thread name.}}
	 {return: The name of the thread which logged the event described by
	   this log record. If this is not available, this will be the string "[System thread]".}
	}
*/
LMI_INLINE_DECLARATION const char* LmiLogRecordGetThreadName(const LmiLogRecord* r);

/**
   {function:
	 {name: LmiLogRecordGetThreadId}
	 {parent: LmiLogRecord}
	 {description: Get the thread id of the thread associated with a logged event.}
	 {prototype: LmiThreadId LmiLogRecordGetThreadId(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the thread name.}}
	 {return: The thread id of the thread which logged the event described by
	   this log record.}
	}
*/
LMI_INLINE_DECLARATION LmiThreadId LmiLogRecordGetThreadId(const LmiLogRecord* r);


/**
   {function:
	 {name: LmiLogRecordGetTime}
	 {parent: LmiLogRecord}
	 {description: Get the wall-clock time at which a logged event occurred.}
	 {prototype: LmiTime LmiLogRecordGetTime(const LmiLogRecord* r)}
	 {parameter:
	   {name: r}
	   {description: The log record from which to obtain the wall-clock time.}}
	 {return: The wall-clock time at which the event described by
	   this log record occurred. If this is not available, this will be the value LMI_TIME_INFINITE.}
	}
*/
LMI_INLINE_DECLARATION LmiTime LmiLogRecordGetTime(const LmiLogRecord* r);


typedef void (*LmiWriteFunction_)(void *data, char *format, ...);

void LmiLogRecordWrite_(const LmiLogRecord *rec, LmiBool verbose, LmiBool columns, LmiWriteFunction_ write, void *data);


/**
   {callback:
	 {name: LmiLogListenerHandleRecordCallback}
	 {parent: LmiLogListener}
	 {description: A callback invoked for an LmiLogListener to handle
	   a single LmiLogRecord.}
	 {prototype: void (*LmiLogListenerHandleRecordCallback)(LmiLogListener* l, const LmiLogRecord* r)}
	 {parameter:
	   {name: l}
	   {description: The log listener handling the record.}}
	 {parameter:
	   {name: r}
	   {description: The record being processed.}}
   }
*/

typedef struct LmiLogListener_ LmiLogListener;

typedef void (*LmiLogListenerHandleRecordCallback)(LmiLogListener *,
												   const LmiLogRecord *);

/**
   {type:
	 {name: LmiLogListener}
	 {parent: Log}
	 {description: An object which receives and processes log messages.}
   } */
struct LmiLogListener_ {
	LmiLogListenerHandleRecordCallback handle_cb;
	LmiLogCategorySet categories[LMI_LOG_NUM_LEVELS];

	LmiLogLevelSet compatLevels;
	LmiLogCategorySet compatCategories;
	LmiBool verbose;
	LmiVoidPtr user_data;
};


/**
   {function:
	 {name: LmiLogListenerConstruct}
	 {parent: LmiLogListener}
	 {description: Construct an LmiLogListener.}
	 {prototype: LmiLogListener* LmiLogListenerConstruct(LmiLogListener* l, LmiLogListenerHandleRecordCallback cb, LmiVoidPtr userData, LmiAllocator* a)}
	 {parameter:
	   {name: l}
	   {description: A pointer to the LmiLogListener to construct.}}
	 {parameter:
	   {name: cb}
	   {description: The callback that is called whenever a log record is
		 posted to the listener.}}
	 {parameter:
	   {name: userData}
	   {description: Local data specific to the log listener.}}
	 {parameter:
	   {name: a}
	   {description: Allocator to use for dynamically-allocated memory for the listener.}}
	 {return: l on success, NULL on failure.}
	 {note: The newly-constructed listener will not receive
		notifications for any log levels or categories.  For the listener
		to be useful, the various LmiLogListenerSet* functions must be
		called.}
   }
*/
LmiLogListener* LmiLogListenerConstruct(LmiLogListener* l,
										 LmiLogListenerHandleRecordCallback cb,
										 LmiVoidPtr userData,
										 LmiAllocator* a);

/**
   {function:
	 {name: LmiLogListenerDestruct}
	 {parent: LmiLogListener}
	 {description: Destruct an LmiLogListener.}
	 {prototype: void LmiLogListenerDestruct(LmiLogListener* l)}
	 {parameter:
	   {name: l}
	   {description: A pointer to the LmiLogListener to destruct.}}
	 {note: This does not do deallocate any memory associated with the
			listener\'s user data field.  As such, this function should
			generally be considered "protected", i.e. it should only be
			called by specific listeners\' destruct functions.}
   }
*/
void LmiLogListenerDestruct(LmiLogListener* l);

/**
 {function:
 {name: LmiLogListenerIsVerbose}
 {parent: LmiLogListener}
 {description: Determine whether verbose logging is enabled on the log listener.}
 {prototype: LmiBool LmiLogListenerIsVerbose(const LmiLogListener* l)}
 {parameter:
 {name: l}
 {description: The LmiLogListener whose verbosity is to be determined.}}
 {return: LMI_TRUE if verbose logging is enabled or LMI_FALSE if it is not.}
 }
 */
LMI_INLINE_DECLARATION LmiBool LmiLogListenerIsVerbose(const LmiLogListener* l);

/**
   {function:
	 {name: LmiLogListenerGetLevels}
	 {parent: LmiLogListener}
	 {description: Obtain the set of log levels on which a log listener is
	   receiving at least one category.}
	 {prototype: LmiLogLevelSet LmiLogListenerGetLevels(const LmiLogListener* l)}
	 {parameter:
	   {name: l}
	   {description: The LmiLogListener whose levels to obtain.}}
	 {return: A set of LmiLogLevels on which the listener is receiving at
	   least one category.}
   }
*/
LmiLogLevelSet LmiLogListenerGetLevels(const LmiLogListener* l);

/**
   {function:
	 {name: LmiLogListenerGetCategories}
	 {parent: LmiLogListener}
	 {description: Obtain the set of log categories on which a log listener is receiving at least one level.}
	 {prototype: LmiBool LmiLogListenerGetCategories(const LmiLogListener* l, LmiLogCategorySet* categories)}
	 {parameter:
	   {name: l}
	   {description: The log listeners whose categories to obtain.}}
	 {parameter:
	   {name: categories}
	   {description: A constructed category set.  On successful return, the set of log categories the listener wishes to receive.}}
	 {return: LMI_TRUE on success, else LMI_FALSE}
   }
*/
LmiBool LmiLogListenerGetCategories(const LmiLogListener* l, LmiLogCategorySet* categories);


/**
	{function:
		{name: LmiLogListenerHasLevelAndCategory}
		{parent: LmiLogListener}
		{description: Query whether a log listener is receiving log messages for a given log level and category.}
		{prototype: LmiBool LmiLogListenerHasLevelAndCategory(const LmiLogListener* l, LmiLogLevel level, LmiLogCategory category)}
		{parameter:
			{name: l}
			{description: The log listener to query.}}
		{parameter:
			{name: level}
			{description: The log level to query.}}
		{parameter:
			{name: category}
			{description: The log category to query.}}
		{return: LMI_TRUE if the log listener is receiving the level and category; LMI_FALSE otherwise.}
	}
*/
LmiBool LmiLogListenerHasLevelAndCategory(const LmiLogListener* l, LmiLogLevel level, LmiLogCategory category);


/**
	{function:
		{name: LmiLogListenerGetCategoriesForLevel}
		{parent: LmiLogListener}
		{description: Get the set of log categories for which a log listener is receiving log messages on a given log level.}
		{prototype: LmiBool LmiLogListenerGetCategoriesForLevel(const LmiLogListener* l, LmiLogLevel level, LmiLogCategorySet* categories)}
		{parameter:
			{name: l}
			{description: The log listener to query.}}
		{parameter:
			{name: level}
			{description: The log level to query.}}
		{parameter:
			{name: categories}
			{description: A constructed category set.  On successful return, the set of log categories being received on the given log level.}}
		{return: LMI_TRUE on success, else LMI_FALSE.}
	}
*/
LmiBool LmiLogListenerGetCategoriesForLevel(const LmiLogListener* l, LmiLogLevel level, LmiLogCategorySet* categories);


/**
	{function:
		{name: LmiLogListenerGetLevelsForCategory}
		{parent: LmiLogListener}
		{description: Get the set of log levels on which a log listener is receiving log messages for a given log category.}
		{prototype: LmiLogLevelSet LmiLogListenerGetLevelsForCategory(const LmiLogListener* l, LmiLogCategory category)}
		{parameter:
			{name: l}
			{description: The log listener to query.}}
		{parameter:
			{name: category}
			{description: The log category to query.}}
		{return: The set of levels being received for the given log category.}
	}
*/
LmiLogLevelSet LmiLogListenerGetLevelsForCategory(const LmiLogListener* l, LmiLogCategory category);

/**
 {function:
 {name: LmiLogListenerSetVerbose}
 {parent: LmiLogListener}
 {description: Set the verbosity of the log messages reported by the log listener.}
 {prototype: void LmiLogListenerSetVerbose(LmiLogListener* l, LmiBool verbose)}
 {parameter:
 {name: l}
 {description: The LmiLogListener whose verbosity is to be set.}}
 {parameter:
 {name: verbose}
 {description: LMI_TRUE to enable verbose logging or LMI_FALSE to disable verbose logging.}}
 }
 */
LMI_INLINE_DECLARATION void LmiLogListenerSetVerbose(LmiLogListener* l, LmiBool verbose);

/**
 {function replaced-by="LmiLogListenerSetVerbose":
 {name: LmiLogListenerVerbose}
 {parent: LmiLogListener}
 {description: Set the verbosity of the log messages reported by the log listener.}
 {prototype: void LmiLogListenerVerbose(LmiLogListener* l, LmiBool verbose)}
 {parameter:
 {name: l}
 {description: The LmiLogListener whose verbosity is to be set.}}
 {parameter:
 {name: verbose}
 {description: LMI_TRUE to enable verbose logging or LMI_FALSE to disable verbose logging.}}
 }
 */
LMI_DEPRECATED("Deprecated, replaced by LmiLogListenerSetVerbose") LMI_INLINE_DECLARATION void LmiLogListenerVerbose(LmiLogListener* l, LmiBool verbose);

/**
	{function:
		{name: LmiLogListenerSetLevelAndCategory}
		{parent: LmiLogListener}
		{description: Set whether log messages should be received for the given log listener for the given level and category.}
		{prototype: LmiBool LmiLogListenerSetLevelAndCategory(LmiLogListener* l, LmiLogLevel level, LmiLogCategory category, LmiBool on)}
		{parameter:
			{name: l}
			{description: The log listener to set.}}
		{parameter:
			{name: level}
			{description: The log level to set.}}
		{parameter:
			{name: category}
			{description: The log category to set.}}
		{parameter:
			{name: on}
			{description: Whether messages should be received for the level and category.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerSetLevelAndCategory(LmiLogListener* l, LmiLogLevel level, LmiLogCategory category, LmiBool on);


/**
	{function:
		{name: LmiLogListenerSetCategoriesForLevel}
		{parent: LmiLogListener}
		{description: Set which log categories should be received for a given log level on a log listener.}
		{prototype: LmiBool LmiLogListenerSetCategoriesForLevel(LmiLogListener* l, const LmiLogCategorySet* categories, LmiLogLevel level)}
		{parameter:
			{name: l}
			{description: The log listener to set.}}
		{parameter:
			{name: categories}
			{description: The (exact) set of log categories desired for the given level.}}
		{parameter:
			{name: level}
			{description: The log level for which to set categories}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerSetCategoriesForLevel(LmiLogListener* l, const LmiLogCategorySet* categories, LmiLogLevel level);


/**
	{function:
		{name: LmiLogListenerAddCategoriesForLevel}
		{parent: LmiLogListener}
		{description: Add some log categories for a given log level.}
		{prototype: LmiBool LmiLogListenerAddCategoriesForLevel(LmiLogListener* l, const LmiLogCategorySet* categories, LmiLogLevel level)}
		{parameter:
			{name: l}
			{description: The log listener for which to add categories.}}
		{parameter:
			{name: categories}
			{description: The categories to add on the given level.}}
		{parameter:
			{name: level}
			{description: The log level to which to add categories.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerAddCategoriesForLevel(LmiLogListener* l, const LmiLogCategorySet* categories, LmiLogLevel level);


/**
	{function:
		{name: LmiLogListenerClearCategoriesForLevel}
		{parent: LmiLogListener}
		{description: Remove some log categories for a given log level.}
		{prototype: LmiBool LmiLogListenerClearCategoriesForLevel(LmiLogListener* l, const LmiLogCategorySet* categories, LmiLogLevel level)}
		{parameter:
			{name: l}
			{description: The log listener for which to remove categories.}}
		{parameter:
			{name: categories}
			{description: The categories to remove for the given level.}}
		{parameter:
			{name: level}
			{description: The level for which to remove categories.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerClearCategoriesForLevel(LmiLogListener* l, const LmiLogCategorySet* categories, LmiLogLevel level);


/**
	{function:
		{name: LmiLogListenerSetLevelsForCategory}
		{parent: LmiLogListener}
		{description: Set which log levels should be received for a given log category on a log listener.}
		{prototype: LmiBool LmiLogListenerSetLevelsForCategory(LmiLogListener* l, LmiLogLevelSet levels, LmiLogCategory category)}
		{parameter:
			{name: l}
			{description: The log listener to set.}}
		{parameter:
			{name: levels}
			{description: The (exact) set of log levels desired for the given category.}}
		{parameter:
			{name: category}
			{description: The log category for which to set levels.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerSetLevelsForCategory(LmiLogListener* l, LmiLogLevelSet levels, LmiLogCategory category);


/**
	{function:
		{name: LmiLogListenerAddLevelsForCategory}
		{parent: LmiLogListener}
		{description: Add some log levels to a given log category.}
		{prototype: LmiBool LmiLogListenerAddLevelsForCategory(LmiLogListener* l, LmiLogLevelSet levels, LmiLogCategory category)}
		{parameter:
			{name: l}
			{description: The log listener to which to add levels.}}
		{parameter:
			{name: levels}
			{description: The levels to add for the given category.}}
		{parameter:
			{name: category}
			{description: The log category for which to add levels.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerAddLevelsForCategory(LmiLogListener* l, LmiLogLevelSet levels, LmiLogCategory category);


/**
	{function:
		{name: LmiLogListenerClearLevelsForCategory}
		{parent: LmiLogListener}
		{description: Remove some log levels from a given log category.}
		{prototype: LmiBool LmiLogListenerClearLevelsForCategory(LmiLogListener* l, LmiLogLevelSet levels, LmiLogCategory category)}
		{parameter:
			{name: l}
			{description: The log listener from which to remove levels.}}
		{parameter:
			{name: levels}
			{description: The levels to remove from the given category.}}
		{parameter:
			{name: category}
			{description: The category from which to remove levels.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerClearLevelsForCategory(LmiLogListener* l, LmiLogLevelSet levels, LmiLogCategory category);


/**
	{function:
		{name: LmiLogListenerClearAllLevelsAndCategories}
		{parent: LmiLogListener}
		{description: Remove all levels and categories for a log listener.}
		{prototype: LmiBool LmiLogListenerClearAllLevelsAndCategories(LmiLogListener* l)}
		{parameter:
			{name: l}
			{description: The log listener for which to remove all levels and categories.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiLogListenerClearAllLevelsAndCategories(LmiLogListener* l);




/**
   {function:
     {name: LmiLogListenerSetLevelsAndCategoriesFromString}
	 {parent: LmiLogListener}
	 {description: Set a log listener\'s levels and categories based on
	   a string describing the levels and categories.}
	 {prototype: LmiBool LmiLogListenerSetLevelsAndCategoriesFromString(LmiLogListener* l, const char* logParam, LmiBool add)}
	 {parameter:
	   {name: l}
	   {description: The log listener whose levels and categories to set.}}
	 {parameter:
	   {name: logParam}
	   {description:
	   {p: A space-separated (or comma-separated)
		 sequence of names of log levels, each optionally followed by a
		 category.  Categories are
		 separated from levels by the character \'@\'.}
	   {p: Either a level or category may be specified as \'all\' or \'*\'
	     (interchangeably), meaning all levels or categories.  A level specified
		 without a category is equivalent to a level@*.}
	   {p: The levels are: \'fatal\', \'error\', \'warning\', \'info\', \'debug\', 
		 \'sent\', \'received\', \'enter\', and '\leave\'.}
	   {p: The level may be prefixed by \'-\' or \'!\' (interchangeably), meaning to remove
		 the given level (or levels, see below) from the given category.
		 The string \'none\' is equivalent to \'-all\'.}
	   {p: The first level in the list may be prefixed by \'+\'.
	     If the first level begins with a \'+\' or \'-\'/\'!\', the string
		 is used to modify the listener\'s existing levels and categories.
		 Otherwise, unless the {code: add} parameter is true, the levels and categories 
 		 specified in the string replace all existing levels and categories for the listener.  
 		 The leading character \'+\' may be present before other levels, but is ignored.}
	   {p: Unless they are preceded by \'=\', level names imply other levels
		 as well.  In particular, each of the levels \'fatal\', \'error\', \'warning\',
		 \'info\', and \'debug\' implies the levels higher than it, when specified
		 positively; \'sent\' and \'received\' always imply each other; and \'enter\' and
		 \'leave\' always imply each other.}
	   {p: See {code:LmiLogGetCategoryByIndex} for determining the names and descriptions of registered categories.}
	   {p: Level names are case-insensitive; category names are case-sensitive.}
	   {p: Example: "all" - all levels, all categories.}
	   {p: Example: "all -enter" - all categories, all levels but enter and leave.}
	   {p: Example: "*@LmiMutex" - all levels for the LmiMutex category.}
	   {p: Example: "-*@LmiMutex" - remove all levels from the LmiMutex category.}
	   {p: Example: "debug" - all categories, fatal, error, warning, info, and debug levels.}
	   {p: Example: "=debug" - all categories, debug level only.}
	   {p: Example: "all -=enter" - all categories, all levels but enter (leave is still included).}
	   {p: Example: "error@LmiMutex" - fatal and error only for the LmiMutex category.}
	   {p: Example: "warning debug@LmiMutex" - fatal, error, and warning for all categories; additionally, info and debug for the LmiMutex category.}
	 }}
	{parameter:
	   {name: add}
	   {description: Whether the levels and categories specified should
	     replace the existing state of the log listener (LMI_FALSE), or
		 modify it (LMI_TRUE).  Typically this is useful if a log category
		 description is pre-tokenized before being passed to the log listener;
		 add can be false for the first token and true for the rest.  As
		 stated above, if the log string begins with \'+\' or \'-\', it
		 always modifies the listener\'s existing settings, regardless of
		 the value of this flag.}}
	{return: LMI_FALSE on failure parsing the string or setting the levels and
	  categories, otherwise LMI_TRUE.}
  }
*/
LmiBool LmiLogListenerSetLevelsAndCategoriesFromString(LmiLogListener* l,
	const char* logParam, LmiBool add);

/**
	{function:
		{name: LmiLogListenerGetLevelsAndCategoriesAsCStr}
		{parent: LmiLogListener}
		{description: Get a C string describing a log listener's levels and
			categories.}
		{prototype: LmiSizeT LmiLogListenerGetLevelsAndCategoriesAsCStr(const LmiLogListener* l, char* logString, LmiSizeT logStringSize)}
		{parameter:
			{name: l}
			{description: The log listener.}}
		{parameter:
			{name: logString}
			{description: A buffer into which to write the log description.}}
		{parameter:
			{name: logStringSize}
			{description: The size of the buffer.}}
		{return: The total size of the string that would be written to the buffer, if unbounded.}
		{note: If it is not truncated (i.e. the return value is less than logStringSize), the resulting string is suitable for passing to LmiLogListenerSetLevelsAndCategoriesFromString.}
	}
*/
LmiSizeT LmiLogListenerGetLevelsAndCategoriesAsCStr(const LmiLogListener* l, char* logString, LmiSizeT logStringSize);

/**
	{function:
		{name: LmiLogListenerAppendLevelsAndCategoriesToString}
		{parent: LmiLogListener}
		{description: Append a description of log listener's levels and
			categories to a string.}
		{prototype: LmiBool LmiLogListenerAppendLevelsAndCategoriesToString(const LmiLogListener* l, LmiString* logString)}
		{parameter:
			{name: l}
			{description: The log listener.}}
		{parameter:
			{name: logString}
			{description: A buffer into which to write the log description.}}
		{return: LMI_TRUE on success, LMI_FALSE otherwise.}
		{note: The resulting string is suitable for passing to LmiLogListenerSetLevelsAndCategoriesFromString.}
	}
*/
LmiBool LmiLogListenerAppendLevelsAndCategoriesToString(const LmiLogListener* l, LmiString* logString);

/**
   {function:
	 {name: LmiLogListenerGetUserData}
	 {parent: LmiLogListener}
	 {description: Get the user data pointer associated with a log listener.}
	 {prototype: LmiVoidPtr LmiLogListenerGetUserData(LmiLogListener* l)}
	 {parameter:
	   {name: l}
	   {description: The LmiLogListener whose user data to retrieve.}}
	 {return: The userData pointer passed in when the listener was
	   constructed.}
   }
*/
LMI_INLINE_DECLARATION LmiVoidPtr LmiLogListenerGetUserData(LmiLogListener* l);


/**
   {function:
	 {name: LmiLogRegisterListener}
	 {parent: Log}
	 {description: Register an LmiLogListener to receive log messages.}
	 {prototype: LmiBool LmiLogRegisterListener(LmiLogListener* l)}
	 {parameter:
	   {name: l}
	   {description: The LmiLogListener to register.}}
	 {return: LMI_TRUE on success, LMI_FALSE on failure.}
	 {note: The caller maintains ownership of the log listener.	 The
	   listener object must remain valid for the lifetime of the program,
	   or until it is unregistered.}
	 {note: The number of distinct listeners
	   that may be registered is limited only by available memory.}
   }
*/
LmiBool LmiLogRegisterListener(LmiLogListener* l);


/**
   {function:
	 {name: LmiLogUnregisterListener}
	 {parent: Log}
	 {description: Unregister an LmiLogListener from receiving log messages.}
	 {prototype: LmiBool LmiLogUnregisterListener(LmiLogListener* l)}
	 {parameter:
	   {name: l}
	   {description: The LmiLogListener to unregister.}}
	 {return: LMI_TRUE on success, LMI_FALSE if the listener was not
	   registered.}
	 {note: To be removed, the pointer argument must compare equal to a
	   previously registered listener.	No semantic equality operation is
	   defined for log listeners.}
	 {note: This function is linear in the number of registered listeners.}
   }
*/
LmiBool LmiLogUnregisterListener(LmiLogListener* l);


/**
   {type:
	 {name: LmiLogConfidentialityLevel}
	 {parent: Log}
	 {description: The confidentiality level the logging system should adhere to.  For example, exclude personally identifiable information.}
 	 {value:
	   {name: LMI_LOGCONFIDENTIALITYLEVEL_None}
	   {description: No information is excluded from logs.}}
 	 {value:
	   {name: LMI_LOGCONFIDENTIALITYLEVEL_ExcludePersonallyIdentifiableInformation}
	   {description: Exclude personally identifiable information from logs.}}
   }
*/
typedef enum {
	LMI_LOGCONFIDENTIALITYLEVEL_None,	/*  */
	LMI_LOGCONFIDENTIALITYLEVEL_ExcludePersonallyIdentifiableInformation	/* Exclude display text/names */
} LmiLogConfidentialityLevel;

/**
   {function:
	 {name: LmiLogGetConfidentialityLevel}
	 {parent: Log}
	 {description: Gets the current, global confidentiality level.}
	 {prototype: LmiLogConfidentialityLevel LmiLogGetConfidentialityLevel()}
	 {return: Returns the current confidentiality level.}
   }
*/
LmiLogConfidentialityLevel LmiLogGetConfidentialityLevel();

/**
   {function:
	 {name: LmiLogSetConfidentialityLevel}
	 {parent: Log}
	 {description: Sets the current, global confidentiality level.}
	 {prototype: void LmiLogSetConfidentialityLevel(LmiLogConfidentialityLevel confidentialityLevel)}
 	 {parameter:
	   {name: confidentialityLevel}
	   {description: The confidentiality level.}}
   }
*/
void LmiLogSetConfidentialityLevel(LmiLogConfidentialityLevel confidentialityLevel);

/**
   {function:
	 {name: LmiLogObfuscate}
	 {parent: Log}
     {description: Obfuscate (or not) a string based on the current log confidentiality level.  
        If the confidentiality level in high enough (for example LMI_LOGCONFIDENTIALITYLEVEL_ExcludePersonallyIdentifiableInformation),
        the obfuscated string will contain a one-way hash of the clear text. If the confidentiality level in low enough (LMI_LOGCONFIDENTIALITYLEVEL_None),
 		the clear text is simply copied to the obfuscated string.}
	 {prototype: const LmiString* LmiLogObfuscate(const LmiString* clear, LmiString* obfuscated)}
 	 {parameter:
	   {name: clear}
	   {description: The clear text to obfuscate.}}
  	 {parameter:
	   {name: obfuscated}
	   {description: The obfuscated text.}}
	 {return: Returns a point to the obfuscated text.}
   }
*/
const LmiString* LmiLogObfuscate(const LmiString* clear, LmiString* obfuscated);

/* Function which does non-variadic logging. */
void LmiLogDo_(LmiLogLevel level, LmiLogCategory category,
			   const char* file, LmiInt line, const char* function,
			   const char* message);

/* Wrapper which does a log message at a given level. */
#define LmiLogAtLevel_(level, category, message)			   \
  LmiLogDo_(level, category, __FILE__, __LINE__, LMI_FUNCTION, \
			message)

#if LMI_HAVE_VARIADIC_MACROS || LMI_HAVE_GCC_VARIADIC_MACROS
/* Function which does variadic logging. */
void LmiLogDoFormatted_(LmiLogLevel level, LmiLogCategory category,
						const char* file, LmiInt line, const char* function,
						const char* format, ...)
  LmiFunctionPrintfLike(6, 7);

/* Dummy function which should never be called, so we still do format
   checking and evaluate side effects. */
LMI_INLINE_DECLARATION void LmiLogDummyFormatted_(LmiLogCategory category, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);
#endif

/* Wrapper which does a variadic log message at a given level. */
#if LMI_HAVE_VARIADIC_MACROS

#define LmiLogAtLevelFormatted_(level, category, format, ...) \
  LmiLogDoFormatted_(level, category, __FILE__, __LINE__, LMI_FUNCTION, \
					 format, __VA_ARGS__)

#define LmiLogIgnoreFormatted_(category, format, ...)					\
	do { if (0) { LmiLogDummyFormatted_(category, format, __VA_ARGS__); } } while (0)
	

#elif LMI_HAVE_GCC_VARIADIC_MACROS

#define LmiLogAtLevelFormatted_(level, category, format, args...) \
  LmiLogDoFormatted_(level, category, __FILE__, __LINE__, LMI_FUNCTION, \
					 format, args)

#define LmiLogIgnoreFormatted_(category, format, ...)					\
	do { if (0) { LmiLogDummyFormatted_(category, format, args); } } while (0)

#endif


/* LMI_LOG_NO_* can suppress, at compile-time, log messages at
   any given level. */


/**
   {function:
	 {name: LmiLogFatal}
	 {parent: Log}
	 {description: Log a fatal error.  In all likelihood, system execution
	   will not be able to continue.}
	 {prototype: void LmiLogFatal(LmiLogCategory category, const char* message)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: message}
	   {description: A human-readable message describing the event being
		 logged.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_FATAL is set at compile time,
	   this function will do nothing, and its argument will be omitted from
	   the library\'s object files.}
   }
*/
/**
   {function:
	 {name: LmiLogFatalFormatted}
	 {parent: Log}
	 {description: Log a fatal error, with arguments formatted from a
	   printf-style string.  In all likelihood, system execution will not be
	   able to continue.}
	 {prototype: void LmiLogFatalFormatted(LmiLogCategory category, const char* format, ...)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: format}
	   {description: A printf-style string formatting a human-readable message
	     describing the event being logged.  The arguments to the format follow
		 the format string.}}
	 {parameter:
	   {name: ...}
	   {description: Variadic arguments corresponding to the formatting string.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_FATAL is set at compile time,
	   this function will do nothing, and its arguments will be omitted from
	   the library\'s object files.}
	 {note: There must be at least one argument to the format.  For formats
	   without arguments, LmiLogFatal should be used instead.}
	 {note: If the compiler does not support variadic macros, the resulting
	   log record will not have source context set.}
   }
*/
#if defined(LMI_LOG_NO_FATAL)
#define LmiLogFatal(category, message) do {} while (0)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogFatalFormatted(category, format, ...) LmiLogIgnoreFormatted_(category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogFatalFormatted(category, format, args...) LmiLogIgnoreFormatted_(category, format, args)

#else
/* This will produce compiler warnings, but usually not errors. */
#define LmiLogFatalFormatted(category, format, args) do {} while (0)

#endif

#else
#define LmiLogFatal(category, message) \
  LmiLogAtLevel_(LMI_LOGLEVEL_FATAL, category, message)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogFatalFormatted(category, format, ...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_FATAL, category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogFatalFormatted(category, format, args...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_FATAL, category, format, args)

#else
/* If we don't have variadic macros, we don't get context information here. */
void LmiLogFatalFormatted(LmiLogCategory category, const char * format, ...)
  LmiFunctionPrintfLike(2, 3);

#endif
#endif

/**
   {function:
	 {name: LmiLogError}
	 {parent: Log}
	 {description: Log a continuable error.	 The system should be able to
	   continue, but human intervention or diagnosis may be necessary.}
	 {prototype: void LmiLogError(LmiLogCategory category, const char* message)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: message}
	   {description: A human-readable message describing the event being
		 logged.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_ERROR is set at compile time,
	   this function will do nothing, and its argument will be omitted from
	   the library\'s object files.}
   }
*/

/**
   {function:
	 {name: LmiLogErrorFormatted}
	 {parent: Log}
	 {description: Log a continuable error, with arguments formatted from a
	   printf-style string.  The system should be able to
	   continue, but human intervention or diagnosis may be necessary.}
	 {prototype: void LmiLogErrorFormatted(LmiLogCategory category, const char* format, ...)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: format}
	   {description: A printf-style string formatting a human-readable message
	     describing the event being logged.  The arguments to the format follow
		 the format string.}}
	 {parameter:
	   {name: ...}
	   {description: Variadic arguments corresponding to the formatting string.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_ERROR is set at compile time,
	   this function will do nothing, and its arguments will be omitted from
	   the library\'s object files.}
	 {note: There must be at least one argument to the format.  For formats
	   without arguments, LmiLogError should be used instead.}
	 {note: If the compiler does not support variadic macros, the resulting
	   log record will not have source context set.}
   }
*/
#if defined(LMI_LOG_NO_ERROR)
#define LmiLogError(category, message) do {} while (0)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogErrorFormatted(category, format, ...) LmiLogIgnoreFormatted_(category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogErrorFormatted(category, format, args...) LmiLogIgnoreFormatted_(category, format, args)

#else
/* This will produce compiler warnings, but usually not errors. */
#define LmiLogErrorFormatted(category, format, args) do {} while (0)

#endif

#else
#define LmiLogError(category, message) \
  LmiLogAtLevel_(LMI_LOGLEVEL_ERROR, category, message)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogErrorFormatted(category, format, ...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_ERROR, category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogErrorFormatted(category, format, args...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_ERROR, category, format, args)

#else
/* If we don't have variadic macros, we don't get context information here. */
void LmiLogErrorFormatted(LmiLogCategory category, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);

#endif
#endif

/**
   {function:
	 {name: LmiLogWarning}
	 {parent: Log}
	 {description: Log a warning.  Something has occurred which may require
	   attention or action, but which is not actually erroneous.}
	 {prototype: void LmiLogWarning(LmiLogCategory category, const char* message)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: message}
	   {description: A human-readable message describing the event being
		 logged.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_WARNING is set at compile
	   time, this function will do nothing, and its argument will be omitted
	   from the library\'s object files.}
   }
*/

/**
   {function:
	 {name: LmiLogWarningFormatted}
	 {parent: Log}
	 {description: Log a warning, with arguments formatted from a
	   printf-style string.  Something has occurred which may require
	   attention or action, but which is not actually erroneous.}
	 {prototype: void LmiLogWarningFormatted(LmiLogCategory category, const char* format, ...)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: format}
	   {description: A printf-style string formatting a human-readable message
	     describing the event being logged.  The arguments to the format follow
		 the format string.}}
	 {parameter:
	   {name: ...}
	   {description: Variadic arguments corresponding to the formatting string.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_WARNING is set at compile time,
	   this function will do nothing, and its arguments will be omitted from
	   the library\'s object files.}
	 {note: There must be at least one argument to the format.  For formats
	   without arguments, LmiLogWarning should be used instead.}
	 {note: If the compiler does not support variadic macros, the resulting
	   log record will not have source context set.}
   }
*/
#if defined(LMI_LOG_NO_WARNING)
#define LmiLogWarning(category, message) do {} while (0)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogWarningFormatted(category, format, ...) LmiLogIgnoreFormatted_(category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogWarningFormatted(category, format, args...) LmiLogIgnoreFormatted_(category, format, args)

#else
/* This will produce compiler warnings, but usually not errors. */
#define LmiLogWarningFormatted(category, format, args) do {} while (0)

#endif

#else
#define LmiLogWarning(category, message) \
  LmiLogAtLevel_(LMI_LOGLEVEL_WARNING, category, message)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogWarningFormatted(category, format, ...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_WARNING, category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogWarningFormatted(category, format, args...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_WARNING, category, format, args)

#else
/* If we don't have variadic macros, we don't get context information here. */
void LmiLogWarningFormatted(LmiLogCategory category, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);

#endif
#endif

/**
   {function:
	 {name: LmiLogInfo}
	 {parent: Log}
	 {description: Log an informational message.  The event being logged
	   describes information which may be useful or informative to a user of
	   the system.	No problems are being reported.}
	 {prototype: void LmiLogInfo(LmiLogCategory category, const char* message)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: message}
	   {description: A human-readable message describing the event being
		 logged.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_INFO is set at compile time,
	   this function will do nothing, and its argument will be omitted from
	   the library\'s object files.}
   }
*/

/**
   {function:
	 {name: LmiLogInfoFormatted}
	 {parent: Log}
	 {description: Log an informational message, with arguments formatted from a
	   printf-style string.  The event being logged
	   describes information which may be useful or informative to a user of
	   the system.	No problems are being reported.}
	 {prototype: void LmiLogInfoFormatted(LmiLogCategory category, const char* format, ...)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: format}
	   {description: A printf-style string formatting a human-readable message
	     describing the event being logged.  The arguments to the format follow
		 the format string.}}
	 {parameter:
	   {name: ...}
	   {description: Variadic arguments corresponding to the formatting string.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_INFO is set at compile time,
	   this function will do nothing, and its arguments will be omitted from
	   the library\'s object files.}
	 {note: There must be at least one argument to the format.  For formats
	   without arguments, LmiLogInfo should be used instead.}
	 {note: If the compiler does not support variadic macros, the resulting
	   log record will not have source context set.}
   }
*/

#if defined(LMI_LOG_NO_INFO)
#define LmiLogInfo(category, message) do {} while (0)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogInfoFormatted(category, format, ...) LmiLogIgnoreFormatted_(category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogInfoFormatted(category, format, args...) LmiLogIgnoreFormatted_(category, format, args)

#else
/* This will produce compiler warnings, but usually not errors. */
#define LmiLogInfoFormatted(category, format, args) do {} while (0)

#endif

#else
#define LmiLogInfo(category, message) \
  LmiLogAtLevel_(LMI_LOGLEVEL_INFO, category, message)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogInfoFormatted(category, format, ...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_INFO, category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogInfoFormatted(category, format, args...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_INFO, category, format, args)

#else
/* If we don't have variadic macros, we don't get context information here. */
void LmiLogInfoFormatted(LmiLogCategory category, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);

#endif
#endif

/**
   {function:
	 {name: LmiLogDebug}
	 {parent: Log}
	 {description: Log a debug message.	 The event being logged describes
	   information which may be useful to a developer to understand the
	   code.  The information is not expected to be useful to users of the
	   system.}
	 {prototype: void LmiLogDebug(LmiLogCategory category, const char* message)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: message}
	   {description: A human-readable message describing the event being
		 logged.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_DEBUG is set at compile time,
	   this function will do nothing, and its argument will be omitted from
	   the library\'s object files.}
   }
*/


/**
   {function:
	 {name: LmiLogDebugFormatted}
	 {parent: Log}
	 {description: Log a debug message, with arguments formatted from a
	   printf-style string.	 The event being logged describes
	   information which may be useful to a developer to understand the
	   code.  The information is not expected to be useful to users of the
	   system.}
	 {prototype: void LmiLogDebugFormatted(LmiLogCategory category, const char* format, ...)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: format}
	   {description: A printf-style string formatting a human-readable message
	     describing the event being logged.  The arguments to the format follow
		 the format string.}}
	 {parameter:
	   {name: ...}
	   {description: Variadic arguments corresponding to the formatting string.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_DEBUG is set at compile time,
	   this function will do nothing, and its arguments will be omitted from
	   the library\'s object files.}
	 {note: There must be at least one argument to the format.  For formats
	   without arguments, LmiLogDebug should be used instead.}
	 {note: If the compiler does not support variadic macros, the resulting
	   log record will not have source context set.}
   }
*/

#if defined(LMI_LOG_NO_DEBUG)
#define LmiLogDebug(category, message) do {} while (0)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogDebugFormatted(category, format, ...) LmiLogIgnoreFormatted_(category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogDebugFormatted(category, format, args...) LmiLogIgnoreFormatted_(category, format, args)

#else
/* This will produce compiler warnings, but usually not errors. */
#define LmiLogDebugFormatted(category, format, args) do {} while (0)

#endif

#else
#define LmiLogDebug(category, message) \
  LmiLogAtLevel_(LMI_LOGLEVEL_DEBUG, category, message)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogDebugFormatted(category, format, ...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_DEBUG, category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogDebugFormatted(category, format, args...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_DEBUG, category, format, args)

#else
/* If we don't have variadic macros, we don't get context information here. */
void LmiLogDebugFormatted(LmiLogCategory category, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);

#endif
#endif

/**
   {function:
	 {name: LmiLogSent}
	 {parent: Log}
	 {description: Log sent data.  The event being logged describes
	   data that has been transmitted by the system.}
	 {prototype: void LmiLogSent(LmiLogCategory category, const char* message)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: message}
	   {description: The data that was sent.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_SENT is set at compile time,
	   this function will do nothing, and its argument will be omitted from
	   the library\'s object files.}
   }
*/

/**
   {function:
	 {name: LmiLogSentFormatted}
	 {parent: Log}
	 {description: Log sent data, with arguments formatted from a
	   printf-style string.	 The event being logged describes
	   data that has been transmitted by the system.}
	 {prototype: void LmiLogSentFormatted(LmiLogCategory category, const char* format, ...)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: format}
	   {description: A printf-style string formatting a human-readable message
	     describing the event being logged.  The arguments to the format follow
		 the format string.}}
	 {parameter:
	   {name: ...}
	   {description: Variadic arguments corresponding to the formatting string.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_SENT is set at compile time,
	   this function will do nothing, and its arguments will be omitted from
	   the library\'s object files.}
	 {note: There must be at least one argument to the format.  For formats
	   without arguments, LmiLogSent should be used instead.}
	 {note: If the compiler does not support variadic macros, the resulting
	   log record will not have source context set.}
   }
*/


#if defined(LMI_LOG_NO_SENT)
#define LmiLogSent(category, message) do {} while (0)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogSentFormatted(category, format, ...) LmiLogIgnoreFormatted_(category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogSentFormatted(category, format, args...) LmiLogIgnoreFormatted_(category, format, args)

#else
/* This will produce compiler warnings, but usually not errors. */
#define LmiLogSentFormatted(category, format, args) do {} while (0)

#endif

#else
#define LmiLogSent(category, message) \
  LmiLogAtLevel_(LMI_LOGLEVEL_SENT, category, message)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogSentFormatted(category, format, ...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_SENT, category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogSentFormatted(category, format, args...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_SENT, category, format, args)

#else
/* If we don't have variadic macros, we don't get context information here. */
void LmiLogSentFormatted(LmiLogCategory category, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);

#endif
#endif

/**
   {function:
	 {name: LmiLogReceived}
	 {parent: Log}
	 {description: Log received data.  The event being logged describes
	   data that has been received by the system.}
	 {prototype: void LmiLogReceived(LmiLogCategory category, const char* message)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: message}
	   {description: The data that was received.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_RECEIVED is set at compile
	   time, this function will do nothing, and its argument will be omitted
	   from the library\'s object files.}
   }
*/

/**
   {function:
	 {name: LmiLogReceivedFormatted}
	 {parent: Log}
	 {description: Log received data, with arguments formatted from a
	   printf-style string.	 The event being logged describes
	   data that has been received by the system.}
	 {prototype: void LmiLogReceivedFormatted(LmiLogCategory category, const char* format, ...)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {parameter:
	   {name: format}
	   {description: A printf-style string formatting a human-readable message
	     describing the event being logged.  The arguments to the format follow
		 the format string.}}
	 {parameter:
	   {name: ...}
	   {description: Variadic arguments corresponding to the formatting string.}}
	 {note: If the preprocessor symbol LMI_LOG_NO_RECEIVED is set at compile time,
	   this function will do nothing, and its arguments will be omitted from
	   the library\'s object files.}
	 {note: There must be at least one argument to the format.  For formats
	   without arguments, LmiLogReceived should be used instead.}
	 {note: If the compiler does not support variadic macros, the resulting
	   log record will not have source context set.}
   }
*/

#if defined(LMI_LOG_NO_RECEIVED)
#define LmiLogReceived(category, message) do {} while (0)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogReceivedFormatted(category, format, ...) LmiLogIgnoreFormatted_(category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogReceivedFormatted(category, format, args...) LmiLogIgnoreFormatted_(category, format, args)

#else
/* This will produce compiler warnings, but usually not errors. */
#define LmiLogReceivedFormatted(category, format, args) do {} while (0)

#endif

#else
#define LmiLogReceived(category, message) \
  LmiLogAtLevel_(LMI_LOGLEVEL_RECEIVED, category, message)

#if LMI_HAVE_VARIADIC_MACROS
#define LmiLogReceivedFormatted(category, format, ...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_RECEIVED, category, format, __VA_ARGS__)

#elif LMI_HAVE_GCC_VARIADIC_MACROS
#define LmiLogReceivedFormatted(category, format, args...) \
  LmiLogAtLevelFormatted_(LMI_LOGLEVEL_RECEIVED, category, format, args)

#else
/* If we don't have variadic macros, we don't get context information here. */
void LmiLogReceivedFormatted(LmiLogCategory category, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);

#endif
#endif

/**
   {function:
	 {name: LmiLogEnter}
	 {parent: Log}
	 {description: Log entry into a function or block.}
	 {prototype: void LmiLogEnter(LmiLogCategory category)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {note: Unless the preprocessor symbol LMI_LOG_WANT_ENTER is set at compile
	   time, this function will do nothing.}
   }
*/
#if !defined(LMI_LOG_WANT_ENTER)
#define LmiLogEnter(category) do {} while (0)
#else
#define LmiLogEnter(category) LmiLogAtLevel_(LMI_LOGLEVEL_ENTER, category, "")
#endif


/**
   {function:
	 {name: LmiLogLeave}
	 {parent: Log}
	 {description: Log exit from a function or block.}
	 {prototype: void LmiLogLeave(LmiLogCategory category)}
	 {parameter:
	   {name: category}
	   {description: The category of the event being logged.}}
	 {note: Unless the preprocessor symbol LMI_LOG_WANT_LEAVE is set at compile
	   time, this function will do nothing.}
   }
*/
#if !defined(LMI_LOG_WANT_LEAVE)
#define LmiLogLeave(category) do {} while (0)
#else
#define LmiLogLeave(category) LmiLogAtLevel_(LMI_LOGLEVEL_LEAVE, category, "")
#endif


LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiLogInline.h>
#endif

#endif /* LMI_LOG_H_ */
