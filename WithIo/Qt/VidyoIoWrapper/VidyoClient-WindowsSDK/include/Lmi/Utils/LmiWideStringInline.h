/**
   {file:
     {name: LmiWideStringInline.h}
     {description: Inline functions for LmiWideString.}
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

/** {implementation: {name: LmiWideStringLess}} */
LMI_INLINE LmiBool LmiWideStringLess(const LmiWideString* x, const LmiWideString *y)
{
	return LmiWideStringCompare(x, y) < 0;
}


/** {implementation: {name: LmiWideStringLength}} */
LMI_INLINE LmiSizeT LmiWideStringLength(const LmiWideString *x)
{
	return x->size;
}


/** {implementation: {name: LmiWideStringSize}} */
LMI_INLINE LmiSizeT LmiWideStringSize(const LmiWideString *x)
{
	return x->size;
}


/** {implementation: {name: LmiWideStringMaxSize}} */
LMI_INLINE LmiSizeT LmiWideStringMaxSize(const LmiWideString *x)
{
	return LmiAllocatorGetMaxSize(x->allocator);
}

/** {implementation: {name: LmiWideStringGetAllocator}} */
LMI_INLINE LmiAllocator* LmiWideStringGetAllocator(const LmiWideString *x)
{
	return x->allocator;
}


/** {implementation: {name: LmiWideStringCapacity}} */
LMI_INLINE LmiSizeT LmiWideStringCapacity(const LmiWideString *x)
{
	return x->capacity;
}


/** {implementation: {name: LmiWideStringData}} */
LMI_INLINE const LmiWideChar* LmiWideStringData(const LmiWideString *x)
{
	return (x->buf != NULL ? x->buf : lmiWideStringEmptyStr_);
}


/** {implementation: {name: LmiWideStringCStr}
    {note: Our implementation always keeps a terminating NUL on strings.}} */
LMI_INLINE const LmiWideChar* LmiWideStringCStr(const LmiWideString *x)
{
	return (x->buf != NULL ? x->buf : lmiWideStringEmptyStr_);
}


/** {implementation: {name: LmiWideStringGetBuffer}} */
LMI_INLINE LmiWideChar* LmiWideStringGetBuffer(LmiWideString *x)
{
	return (LmiWideChar*)LmiWideStringData(x) + x->size;
}


/** {implementation: {name: LmiWideStringAt}} */
LMI_INLINE LmiWideChar* LmiWideStringAt(LmiWideString * x, LmiSizeT n)
{
	if (n > x->size)
		return NULL;

	return (LmiWideChar*)LmiWideStringData(x) + n;
}

/** {implementation: {name: LmiWideStringAtConst}} */
LMI_INLINE const LmiWideChar* LmiWideStringAtConst(const LmiWideString * x, LmiSizeT n)
{
	if (n > x->size)
		return NULL;

	return LmiWideStringData(x) + n;
}


/** {implementation: {name: LmiWideStringEmpty}} */
LMI_INLINE LmiBool LmiWideStringEmpty(const LmiWideString * x)
{
	return x->size == 0;
}


/** {implementation: {name: LmiWideStringClear}} */
LMI_INLINE void LmiWideStringClear(LmiWideString * x)
{
	x->size = 0;
	if (x->buf != NULL && x->buf != lmiWideStringEmptyStr_) {
		x->buf[0] = '\0';
	}
}


/** {implementation: {name: LmiWideStringBegin}} */
LMI_INLINE LmiWideStringIterator LmiWideStringBegin(LmiWideString * x)
{
	return (LmiWideStringIterator)LmiWideStringData(x);
}


/** {implementation: {name: LmiWideStringBeginConst}} */
LMI_INLINE LmiWideStringConstIterator LmiWideStringBeginConst(const LmiWideString * x)
{
	return (LmiWideStringConstIterator)LmiWideStringData(x);
}


/** {implementation: {name: LmiWideStringEnd}} */
LMI_INLINE LmiWideStringIterator LmiWideStringEnd(LmiWideString * x)
{
	return (LmiWideStringIterator)LmiWideStringData(x) + x->size;
}


/** {implementation: {name: LmiWideStringEndConst}} */
LMI_INLINE LmiWideStringConstIterator LmiWideStringEndConst(const LmiWideString * x)
{
	return (LmiWideStringConstIterator)LmiWideStringData(x) + x->size;
}


/** {implementation: {name: LmiWideStringRBegin}} */
LMI_INLINE LmiWideStringReverseIterator LmiWideStringRBegin(LmiWideString * x)
{
	return (LmiWideStringReverseIterator)LmiWideStringEnd(x);
}


/** {implementation: {name: LmiWideStringRBeginConst}} */
LMI_INLINE LmiWideStringConstReverseIterator LmiWideStringRBeginConst(const LmiWideString * x)
{
	return (LmiWideStringConstReverseIterator)LmiWideStringEndConst(x);
}


/** {implementation: {name: LmiWideStringREnd}} */
LMI_INLINE LmiWideStringReverseIterator LmiWideStringREnd(LmiWideString * x)
{
	return (LmiWideStringReverseIterator)LmiWideStringBegin(x);
}


/** {implementation: {name: LmiWideStringREndConst}} */
LMI_INLINE LmiWideStringConstReverseIterator LmiWideStringREndConst(const LmiWideString * x)
{
	return (LmiWideStringConstReverseIterator)LmiWideStringBeginConst(x);
}


/** {implementation: {name: LmiWideStringFront}} */
LMI_INLINE LmiWideChar* LmiWideStringFront(LmiWideString * x)
{
	return (LmiWideChar*)LmiWideStringData(x);
}


/** {implementation: {name: LmiWideStringFrontConst}} */
LMI_INLINE const LmiWideChar* LmiWideStringFrontConst(const LmiWideString * x)
{
	return LmiWideStringData(x);
}


/** {implementation: {name: LmiWideStringBack}} */
LMI_INLINE LmiWideChar* LmiWideStringBack(LmiWideString * x)
{
	return (LmiWideChar*)LmiWideStringData(x) + x->size - 1;
}


/** {implementation: {name: LmiWideStringBackConst}} */
LMI_INLINE const LmiWideChar* LmiWideStringBackConst(const LmiWideString * x)
{
	return LmiWideStringData(x) + x->size - 1;
}


/** {implementation: {name: LmiWideStringPushBack}} */
LMI_INLINE LmiBool LmiWideStringPushBack(LmiWideString* x, const LmiWideChar* c)
{
	return LmiWideStringAppendChar(x, *c) != NULL;
}


/** {implementation: {name: LmiWideStringPopBack}} */
LMI_INLINE void LmiWideStringPopBack(LmiWideString* x)
{
	LmiWideStringErase(x, LmiWideStringEnd(x) - 1);
}



DefineInline_LmiRandomAccessIterator(LmiIterator(LmiWideString),
	LmiWideChar, const LmiWideChar, LMI_INLINE)

DefineInline_LmiRandomAccessIterator(LmiConstIterator(LmiWideString),
	const LmiWideChar, const LmiWideChar, LMI_INLINE)

DefineInline_LmiReverseRandomAccessIterator(LmiReverseIterator(LmiWideString),
	LmiIterator(LmiWideString),
	LmiWideChar, const LmiWideChar, LMI_INLINE)

DefineInline_LmiReverseRandomAccessIterator(LmiConstReverseIterator(LmiWideString),
	LmiConstIterator(LmiWideString),
	const LmiWideChar, const LmiWideChar, LMI_INLINE)
