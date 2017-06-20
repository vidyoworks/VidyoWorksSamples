/** {file:
      {name: VidyoLogRecordInline.h}
      {description: Inline functions for the logging interface.}
      {copyright:
      	(c) 2014-2015 Vidyo, Inc.,
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

/** {implementation: {name: VidyoLogRecordGetLevel}} */
LMI_INLINE VidyoLogLevel VidyoLogRecordGetLevel(const VidyoLogRecord* r)
{
	return r->level;
}

/** {implementation: {name: VidyoLogRecordGetCategoryName}} */
LMI_INLINE LmiSizeT VidyoLogRecordGetCategoryName(const VidyoLogRecord* r)
{
	return r->categoryName;
}

/** {implementation: {name: VidyoLogRecordGetFile}} */
LMI_INLINE const char * VidyoLogRecordGetFile(const VidyoLogRecord * r)
{
  return r->file;
}

/** {implementation: {name: VidyoLogRecordGetLine}} */
LMI_INLINE LmiInt VidyoLogRecordGetLine(const VidyoLogRecord * r)
{
  return r->line;
}

/** {implementation: {name: VidyoLogRecordGetFunctionName}} */
LMI_INLINE const char * VidyoLogRecordGetFunctionName(const VidyoLogRecord * r)
{
  return r->functionName;
}


/** {implementation: {name: VidyoLogRecordGetMessage}} */
LMI_INLINE const char * VidyoLogRecordGetMessage(const VidyoLogRecord * r)
{
  return r->message;
}


/** {implementation: {name: VidyoLogRecordGetThreadName}} */
LMI_INLINE const char * VidyoLogRecordGetThreadName(const VidyoLogRecord * r)
{
  return r->threadName;
}


/** {implementation: {name: VidyoLogRecordGetTime}} */
LMI_INLINE LmiTime VidyoLogRecordGetTime(const VidyoLogRecord * r)
{
  return r->eventTime;
}

