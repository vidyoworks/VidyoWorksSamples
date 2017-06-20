/**
   {file:
     {name: LmiStringInline.h}
     {description: Inline functions for LmiString.}
     {copyright:
     	(c) 2005-2011 Vidyo, Inc.,
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

/** {implementation: {name: LmiStringLess}} */
LMI_INLINE LmiBool LmiStringLess(const LmiString* x, const LmiString *y)
{
  return LmiStringCompare(x, y) < 0;
}


/** {implementation: {name: LmiStringLength}} */
LMI_INLINE LmiSizeT LmiStringLength(const LmiString *x)
{
  return x->size;
}


/** {implementation: {name: LmiStringSize}} */
LMI_INLINE LmiSizeT LmiStringSize(const LmiString *x)
{
  return x->size;
}


/** {implementation: {name: LmiStringMaxSize}} */
LMI_INLINE LmiSizeT LmiStringMaxSize(const LmiString *x)
{
  return LmiAllocatorGetMaxSize(x->allocator);
}

/** {implementation: {name: LmiStringGetAllocator}} */
LMI_INLINE LmiAllocator* LmiStringGetAllocator(const LmiString *x)
{
	return x->allocator;
}


/** {implementation: {name: LmiStringCapacity}} */
LMI_INLINE LmiSizeT LmiStringCapacity(const LmiString *x)
{
  return x->capacity;
}


/** {implementation: {name: LmiStringData}} */
LMI_INLINE const char* LmiStringData(const LmiString *x)
{
  return (x->buf != NULL ? x->buf : lmiStringEmptyStr_);
}


/** {implementation: {name: LmiStringCStr}
    {note: Our implementation always keeps a terminating NUL on strings.}} */
LMI_INLINE const char* LmiStringCStr(const LmiString *x)
{
  return (x->buf != NULL ? x->buf : lmiStringEmptyStr_);
}


/** {implementation: {name: LmiStringGetBuffer}} */
LMI_INLINE char* LmiStringGetBuffer(LmiString *x)
{
  return (char*)LmiStringData(x) + x->size;
}


/** {implementation: {name: LmiStringAt}} */
LMI_INLINE char * LmiStringAt(LmiString * x, LmiSizeT n)
{
  if (n > x->size)
    return NULL;

  return (char*)LmiStringData(x) + n;
}

/** {implementation: {name: LmiStringAtConst}} */
LMI_INLINE const char * LmiStringAtConst(const LmiString * x, LmiSizeT n)
{
  if (n > x->size)
    return NULL;

  return LmiStringData(x) + n;
}


/** {implementation: {name: LmiStringEmpty}} */
LMI_INLINE LmiBool LmiStringEmpty(const LmiString * x)
{
  return x->size == 0;
}


/** {implementation: {name: LmiStringClear}} */
LMI_INLINE void LmiStringClear(LmiString * x)
{
  x->size = 0;
  if (x->buf != NULL && x->buf != lmiStringEmptyStr_) {
    x->buf[0] = '\0';
  }
}


/** {implementation: {name: LmiStringBegin}} */
LMI_INLINE LmiStringIterator LmiStringBegin(LmiString * x)
{
  return (LmiStringIterator)LmiStringData(x);
}


/** {implementation: {name: LmiStringBeginConst}} */
LMI_INLINE LmiStringConstIterator LmiStringBeginConst(const LmiString * x)
{
  return (LmiStringConstIterator)LmiStringData(x);
}


/** {implementation: {name: LmiStringEnd}} */
LMI_INLINE LmiStringIterator LmiStringEnd(LmiString * x)
{
  return (LmiStringIterator)LmiStringData(x) + x->size;
}


/** {implementation: {name: LmiStringEndConst}} */
LMI_INLINE LmiStringConstIterator LmiStringEndConst(const LmiString * x)
{
  return (LmiStringConstIterator)LmiStringData(x) + x->size;
}


/** {implementation: {name: LmiStringRBegin}} */
LMI_INLINE LmiStringReverseIterator LmiStringRBegin(LmiString * x)
{
  return (LmiStringReverseIterator)LmiStringEnd(x);
}


/** {implementation: {name: LmiStringRBeginConst}} */
LMI_INLINE LmiStringConstReverseIterator LmiStringRBeginConst(const LmiString * x)
{
  return (LmiStringConstReverseIterator)LmiStringEndConst(x);
}


/** {implementation: {name: LmiStringREnd}} */
LMI_INLINE LmiStringReverseIterator LmiStringREnd(LmiString * x)
{
  return (LmiStringReverseIterator)LmiStringBegin(x);
}


/** {implementation: {name: LmiStringREndConst}} */
LMI_INLINE LmiStringConstReverseIterator LmiStringREndConst(const LmiString * x)
{
  return (LmiStringConstReverseIterator)LmiStringBeginConst(x);
}


/** {implementation: {name: LmiStringFront}} */
LMI_INLINE char * LmiStringFront(LmiString * x)
{
  return (char *)LmiStringData(x);
}


/** {implementation: {name: LmiStringFrontConst}} */
LMI_INLINE const char * LmiStringFrontConst(const LmiString * x)
{
  return LmiStringData(x);
}


/** {implementation: {name: LmiStringBack}} */
LMI_INLINE char * LmiStringBack(LmiString * x)
{
  return (char *)LmiStringData(x) + x->size - 1;
}


/** {implementation: {name: LmiStringBackConst}} */
LMI_INLINE const char * LmiStringBackConst(const LmiString * x)
{
  return LmiStringData(x) + x->size - 1;
}


/** {implementation: {name: LmiStringPushBack}} */
LMI_INLINE LmiBool LmiStringPushBack(LmiString* x, const char *c)
{
  return LmiStringAppendChar(x, *c) != NULL;
}


/** {implementation: {name: LmiStringPopBack}} */
LMI_INLINE void LmiStringPopBack(LmiString* x)
{
  LmiStringErase(x, LmiStringEnd(x) - 1);
}



DefineInline_LmiRandomAccessIterator(LmiIterator(LmiString),
                                     char, const char, LMI_INLINE)

DefineInline_LmiRandomAccessIterator(LmiConstIterator(LmiString),
                                     const char, const char, LMI_INLINE)

DefineInline_LmiReverseRandomAccessIterator(LmiReverseIterator(LmiString),
                                            LmiIterator(LmiString),
                                            char, const char, LMI_INLINE)

DefineInline_LmiReverseRandomAccessIterator(LmiConstReverseIterator(LmiString),
                                            LmiConstIterator(LmiString),
                                            const char, const char, LMI_INLINE)
