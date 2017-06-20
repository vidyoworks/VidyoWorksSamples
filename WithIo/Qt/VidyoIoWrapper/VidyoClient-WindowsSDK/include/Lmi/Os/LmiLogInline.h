/** {file:
      {name: LmiLogInline.h}
      {description: Inline functions for the logging interface.}
      {copyright:
      	(c) 2005-2010 Vidyo, Inc.,
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

#include <Lmi/Utils/LmiAssert.h>

/** {implementation: {name: LmiLogGetNumberOfLevels}} */
LMI_INLINE LmiSizeT LmiLogGetNumberOfLevels(void)
{
	return LMI_LOG_NUM_LEVELS;
}


/** {implementation: {name: LmiLogLevelGetCount}} */
LMI_INLINE LmiSizeT LmiLogLevelGetCount(void)
{
	return LmiLogGetNumberOfLevels();
}


/** {implementation: {name: LmiLogLevelGetByName}} */
LMI_INLINE LmiLogLevel LmiLogLevelGetByName(const char* name)
{
	return LmiLogGetLevelByName(name);
}


/** {implementation: {name: LmiLogLevelSetConstruct}} */
LMI_INLINE LmiLogLevelSet* LmiLogLevelSetConstruct(LmiLogLevelSet* s)
{
	return LmiRestrictedBitsetConstruct(s);
}


/** {implementation: {name: LmiLogLevelSetConstructWithLevel}} */
LMI_INLINE LmiLogLevelSet* LmiLogLevelSetConstructWithLevel(LmiLogLevelSet* s, LmiLogLevel level)
{
	return LmiRestrictedBitsetConstructWithOneValue(s, LmiRestrictedBitsetValueGet(level));
}


/** {implementation: {name: LmiLogLevelSetDestruct}} */
LMI_INLINE void LmiLogLevelSetDestruct(LmiLogLevelSet * s)
{
	LmiRestrictedBitsetDestruct(s);
}


/** {implementation: {name: LmiLogLevelSetAddLevel}} */
LMI_INLINE LmiBool LmiLogLevelSetAddLevel(LmiLogLevelSet* s, LmiLogLevel l)
{
	return LmiRestrictedBitsetSet(s, LmiRestrictedBitsetValueGet(l));
}


/** {implementation: {name: LmiLogLevelSetAddAllLevels}} */
LMI_INLINE void LmiLogLevelSetAddAllLevels(LmiLogLevelSet* s)
{
	LmiRestrictedBitsetSetAll(s);
}


/** {implementation: {name: LmiLogLevelSetRemoveLevel}} */
LMI_INLINE LmiBool LmiLogLevelSetRemoveLevel(LmiLogLevelSet* s, LmiLogLevel l)
{
	return LmiRestrictedBitsetClear(s, LmiRestrictedBitsetValueGet(l));
}


/** {implementation: {name: LmiLogLevelSetRemoveAllLevels}} */
LMI_INLINE void LmiLogLevelSetRemoveAllLevels(LmiLogLevelSet* s)
{
	LmiRestrictedBitsetClearAll(s);
}

/** {implementation: {name: LmiLogLevelSetHasLevel}} */
LMI_INLINE LmiBool LmiLogLevelSetHasLevel(const LmiLogLevelSet* s, LmiLogLevel l)
{
	return LmiRestrictedBitsetIsSet(s, LmiRestrictedBitsetValueGet(l));
}


/** {implementation: {name: LmiLogLevelSetIsEmpty}} */
LMI_INLINE LmiBool LmiLogLevelSetIsEmpty(const LmiLogLevelSet* s)
{
	return LmiRestrictedBitsetIsEmpty(s);
}


/** {implementation: {name: LmiLogCategoryRegister}} */
LMI_INLINE LmiLogCategory LmiLogCategoryRegister(const char* name)
{
	return LmiLogRegisterCategory(name, "");
}


/** {implementation: {name: LmiLogCategoryGetCount}} */
LMI_INLINE LmiSizeT LmiLogCategoryGetCount(void)
{
	return LmiLogGetNumberOfCategories();
}


/** {implementation: {name: LmiLogCategoryGetByName}} */
LMI_INLINE LmiLogCategory LmiLogCategoryGetByName(const char* name)
{
	return LmiLogGetCategoryByName(name);
}


/** {implementation: {name: LmiLogCategorySetDestruct}} */
LMI_INLINE void LmiLogCategorySetDestruct(LmiLogCategorySet * s)
{
	LmiBitsetDestruct(s);
}


/** {implementation: {name: LmiLogCategorySetAddCategory}} */
LMI_INLINE LmiBool LmiLogCategorySetAddCategory(LmiLogCategorySet* s, LmiLogCategory l)
{
	return LmiBitsetSet(s, l);
}


/** {implementation: {name: LmiLogCategorySetRemoveCategory}} */
LMI_INLINE LmiBool LmiLogCategorySetRemoveCategory(LmiLogCategorySet* s, LmiLogCategory l)
{
	return LmiBitsetClear(s, l);
}


/** {implementation: {name: LmiLogCategorySetRemoveAllCategories}} */
LMI_INLINE void LmiLogCategorySetRemoveAllCategories(LmiLogCategorySet* s)
{
	LmiBitsetClearAll(s);
}

/** {implementation: {name: LmiLogCategorySetHasCategory}} */
LMI_INLINE LmiBool LmiLogCategorySetHasCategory(const LmiLogCategorySet* s, LmiLogCategory l)
{
	return LmiBitsetIsSet(s, l);
}


/** {implementation: {name: LmiLogCategorySetIsEmpty}} */
LMI_INLINE LmiBool LmiLogCategorySetIsEmpty(const LmiLogCategorySet* s)
{
	return LmiBitsetIsEmpty(s);
}


/** {implementation: {name: LmiLogHasListener}} */
LMI_INLINE LmiBool
LmiLogHasListener(LmiLogLevel level, LmiLogCategory category)
{
	switch (level) {
#if defined(LMI_LOG_NO_FATAL)
	case LMI_LOGLEVEL_FATAL:
#endif
#if defined(LMI_LOG_NO_ERROR)
	case LMI_LOGLEVEL_ERROR:
#endif
#if defined(LMI_LOG_NO_WARNING)
	case LMI_LOGLEVEL_WARNING:
#endif
#if defined(LMI_LOG_NO_INFO)
	case LMI_LOGLEVEL_INFO:
#endif
#if defined(LMI_LOG_NO_DEBUG)
	case LMI_LOGLEVEL_DEBUG:
#endif
#if defined(LMI_LOG_NO_SENT)
	case LMI_LOGLEVEL_SENT:
#endif
#if defined(LMI_LOG_NO_RECEIVED)
	case LMI_LOGLEVEL_RECEIVED:
#endif
#if !defined(LMI_LOG_WANT_ENTER)
	case LMI_LOGLEVEL_ENTER:
#endif
#if !defined(LMI_LOG_WANT_LEAVE)
	case LMI_LOGLEVEL_LEAVE:
#endif
	case LMI_LOGLEVEL_INVALID:
		return LMI_FALSE;

	default:
		return LmiLogHasListener_(level, category);
	}
}

/** {implementation: {name: LmiLogRecordGetFile}} */
LMI_INLINE const char * LmiLogRecordGetFile(const LmiLogRecord * r)
{
  return r->file;
}

/** {implementation: {name: LmiLogRecordGetLine}} */
LMI_INLINE LmiInt LmiLogRecordGetLine(const LmiLogRecord * r)
{
  return r->line;
}

/** {implementation: {name: LmiLogRecordGetFunction}} */
LMI_INLINE const char * LmiLogRecordGetFunction(const LmiLogRecord * r)
{
  return r->function;
}


/** {implementation: {name: LmiLogRecordGetMessage}} */
LMI_INLINE const char * LmiLogRecordGetMessage(const LmiLogRecord * r)
{
  return r->message;
}


/** {implementation: {name: LmiLogRecordGetThreadName}} */
LMI_INLINE const char * LmiLogRecordGetThreadName(const LmiLogRecord * r)
{
  return r->threadName;
}

/** {implementation: {name: LmiLogRecordGetThreadId}} */
LMI_INLINE LmiThreadId LmiLogRecordGetThreadId(const LmiLogRecord * r)
{
  return r->threadId;
}

/** {implementation: {name: LmiLogRecordGetTime}} */
LMI_INLINE LmiTime LmiLogRecordGetTime(const LmiLogRecord * r)
{
  return r->eventTime;
}

/** {implementation: {name: LmiLogRecordGetLevel}} */
LMI_INLINE LmiLogLevel LmiLogRecordGetLevel(const LmiLogRecord * r)
{
  return r->level;
}

/** {implementation: {name: LmiLogRecordGetCategory}} */
LMI_INLINE LmiLogCategory LmiLogRecordGetCategory(const LmiLogRecord * r)
{
  return r->category;
}

/** {implementation: {name: LmiLogListenerIsVerbose}} */
LMI_INLINE LmiBool LmiLogListenerIsVerbose(const LmiLogListener* l)
{
	return l->verbose;
}

/** {implementation: {name: LmiLogListenerGetUserData}} */
LMI_INLINE LmiVoidPtr LmiLogListenerGetUserData(LmiLogListener * l)
{
  return l->user_data;
}

/** {implementation: {name: LmiLogListenerSetVerbose}} */
LMI_INLINE void LmiLogListenerSetVerbose(LmiLogListener* l, LmiBool verbose)
{
	l->verbose = verbose;	
}

/** {implementation: {name: LmiLogListenerVerbose}} */
LMI_INLINE void LmiLogListenerVerbose(LmiLogListener* l, LmiBool verbose)
{
	LmiLogListenerSetVerbose(l, verbose);
}

/** {implementation: {name: LmiLogDummyFormatted_}} */
LMI_INLINE void LmiLogDummyFormatted_(LmiLogCategory category, const char * format, ...)
{
	LmiAssert(LMI_FALSE);
}
