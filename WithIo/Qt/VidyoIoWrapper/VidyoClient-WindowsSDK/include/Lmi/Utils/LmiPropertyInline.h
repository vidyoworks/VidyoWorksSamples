/** {file:
    {name: LmiPropertyInline.h}
    {description: Represents a Property}
    {copyright:
    	(c) 2008-2012 Vidyo, Inc.,
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

LMI_INLINE LmiProperty* LmiPropertyConstructDefault(LmiProperty* p, LmiAllocator* a)
{
	if (LmiStringConstructDefault(&p->name, a) == NULL)
		return NULL;
	if (LmiStringConstructDefault(&p->value, a) == NULL) {
		LmiStringDestruct(&p->name);
		return NULL;
	}
	return p;
}

LMI_INLINE LmiProperty* LmiPropertyConstructCStr(LmiProperty* p, const char* name, const char* value, LmiAllocator* a)
{
	LmiAssert(p && name && value);

	if (LmiStringConstructCStr(&p->name, name, a) == NULL) {
		goto FAIL0;
	}
	if (LmiStringConstructCStr(&p->value, value, a) == NULL) {
		goto FAIL1;
	}
	return p;
FAIL1: LmiStringDestruct(&p->name);
FAIL0: return NULL;
}

LMI_INLINE LmiProperty* LmiPropertyConstruct(LmiProperty* p, const LmiString* name, const LmiString* value)
{
	LmiAssert(p && name && value);

	return LmiPropertyConstructCStr(p, LmiStringCStr(name), LmiStringCStr(value), LmiStringGetAllocator(name));
}

LMI_INLINE LmiProperty* LmiPropertyConstructCopy(LmiProperty* p, const LmiProperty* o)
{
	if (LmiStringConstructCopy(&p->name, &o->name) == NULL) {
		goto FAIL0;
	}
	if (LmiStringConstructCopy(&p->value, &o->value) == NULL) {
		goto FAIL1;
	}
	return p;
FAIL1: LmiStringDestruct(&p->name);
FAIL0: return NULL;
}

LMI_INLINE LmiProperty* LmiPropertyAssign(LmiProperty* p, const LmiProperty* o)
{
	if (LmiStringAssign(&p->name, &o->name) == NULL) {
		goto FAIL0;
	}
	if (LmiStringAssign(&p->value, &o->value) == NULL) {
		goto FAIL1;
	}
	return p;
FAIL1: LmiStringDestruct(&p->name);
FAIL0: return NULL;
}

LMI_INLINE LmiBool LmiPropertyEqual(const LmiProperty* a, const LmiProperty* b)
{
	return LmiStringEqual(&a->name, &b->name) && LmiStringEqual(&a->value, &b->value);
}

LMI_INLINE LmiBool LmiPropertyLess(const LmiProperty* a, const LmiProperty* b)
{
	LmiInt c = LmiStringCompare(&a->name, &b->name);
	if(c < 0)
		return LMI_TRUE;
	if(c > 0)
		return LMI_FALSE;
	return LmiStringLess(&a->value, &b->value);
}

LMI_INLINE const LmiString* LmiPropertyGetName(const LmiProperty* p)
{
	return &p->name;
}

LMI_INLINE const char* LmiPropertyGetNameCStr(const LmiProperty* p)
{
	return LmiStringCStr(&p->name);
}

LMI_INLINE const LmiString* LmiPropertyGetValue(const LmiProperty* p)
{
	return &p->value;
}

LMI_INLINE const char* LmiPropertyGetValueCStr(const LmiProperty* p)
{
	return LmiStringCStr(&p->value);
}

LMI_INLINE LmiBool LmiPropertySetValue(LmiProperty* p, const LmiString* value)
{
	return LmiStringAssign(&p->value, value) != NULL;
}

LMI_INLINE LmiBool LmiPropertySetValueCStr(LmiProperty* p, const char* value)
{
	return LmiStringAssignCStr(&p->value, value) != NULL;
}

LMI_INLINE LmiBool LmiPropertyIsEqual(const LmiProperty* p, const LmiString* name)
{
	return LmiStringEqual(&p->name, name);
}

LMI_INLINE LmiBool LmiPropertyIsEqualCStr(const LmiProperty* p, const char* name)
{
	return LmiStringEqualCStr(&p->name, name);
}

LMI_INLINE LmiPropertyList* LmiPropertyListConstructDefault(LmiPropertyList* l, LmiAllocator* a)
{
	return LmiVectorConstructDefault(LmiProperty)(l, a);
}

LMI_INLINE void LmiPropertyListDestruct(LmiPropertyList* l)
{
    LmiVectorDestruct(LmiProperty)(l);
}

LMI_INLINE LmiBool LmiPropertyListAdd(LmiPropertyList* l, const LmiProperty* o)
{
	return LmiVectorPushBack(LmiProperty)(l, o);
}

LMI_INLINE void LmiPropertyListClear(LmiPropertyList* l)
{
	LmiVectorClear(LmiProperty)(l);
}

LMI_INLINE LmiProperty* LmiPropertyListAt(LmiPropertyList* l, LmiSizeT n)
{
	return LmiVectorAt(LmiProperty)(l, n);
}

LMI_INLINE const LmiProperty* LmiPropertyListAtConst(const LmiPropertyList* l, LmiSizeT n)
{
	return LmiVectorAtConst(LmiProperty)(l, n);
}

LMI_INLINE LmiSizeT LmiPropertyListSize(const LmiPropertyList* l)
{
    return LmiVectorSize(LmiProperty)(l);
}
