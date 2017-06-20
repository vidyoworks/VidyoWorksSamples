/** {file:
    {name: LmiProperty.h}
    {description: Represents a Property}
    {copyright:
    	(c) 2008-2011 Vidyo, Inc.,
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

#ifndef LMI_PROPERTY_H_
#define LMI_PROPERTY_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiVector.h>

LMI_BEGIN_EXTERN_C

/**
   {type:
     {name: LmiProperty}
     {parent: Utils}
     {include: Lmi/Utils/LmiProperty.h}
     {description: This class implements a Property.}
   }
*/

typedef struct {
	LmiString name;
	LmiString value;
} LmiProperty;

/**
{function visibility="private":
	{name: LmiPropertyConstructDefault}
	{parent: LmiProperty}
	{description: Default constructor.}
	{prototype: LmiProperty* LmiPropertyConstructDefault(LmiProperty* p, LmiAllocator* a)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object to be constructed.}
	}
	{parameter: 
		{name: a}
		{description: The allocator object.}
	}
	{return: p if the construct operation was successful; NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiProperty* LmiPropertyConstructDefault(LmiProperty* p, LmiAllocator* a);

/**
{function visibility="public":
	{name: LmiPropertyConstruct}
	{parent: LmiProperty}
	{description: Constructor with initial values.}
	{prototype: LmiProperty* LmiPropertyConstruct(LmiProperty* p, const LmiString* name, const LmiString* value)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object to be constructed.}
	}
	{parameter: 
		{name: name}
		{description: The name of the property.}
	}
	{parameter: 
		{name: value}
		{description: The value of the property.}
	}
	{return: p if the construct operation was successful; NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiProperty* LmiPropertyConstruct(LmiProperty* p, const LmiString* name, const LmiString* value);

/**
{function visibility="public":
	{name: LmiPropertyConstructCStr}
	{parent: LmiProperty}
	{description: Constructor with initial values (in CStr format).}
	{prototype: LmiProperty* LmiPropertyConstructCStr(LmiProperty* p, const char* name, const char* value, LmiAllocator* a)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object to be constructed.}
	}
	{parameter: 
		{name: name}
		{description: The name of the property.}
	}
	{parameter: 
		{name: value}
		{description: The value of the property.}
	}
	{parameter: 
		{name: a}
		{description: The allocator to be used.}
	}
	{return: p if the construct operation was successful; NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiProperty* LmiPropertyConstructCStr(LmiProperty* p, const char* name, const char* value, LmiAllocator* a);

/**
{function visibility="public":
	{name: LmiPropertyDestruct}
	{parent: LmiProperty}
	{description: Destructor.}
	{prototype: void LmiPropertyDestruct(LmiProperty* p)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object to be destructed.}
	}
}
*/
void LmiPropertyDestruct(LmiProperty* p);

/**
{function visibility="public":
	{name: LmiPropertyConstructCopy}
	{parent: LmiProperty}
	{description: Copy constructor.}
	{prototype: LmiProperty* LmiPropertyConstructCopy(LmiProperty* p, const LmiProperty* o)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object to be copy-constructed.}
	}
	{parameter: 
		{name: o}
		{description: The LmiProperty object to be constructed from.}
	}
	{return: p if the construct operation was successful; NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiProperty* LmiPropertyConstructCopy(LmiProperty* p, const LmiProperty* o);

/**
{function visibility="public":
	{name: LmiPropertyAssign}
	{parent: LmiProperty}
	{description: Assignment operator.}
	{prototype: LmiProperty* LmiPropertyAssign(LmiProperty* p, const LmiProperty* o)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object to be assigned to.}
	}
	{parameter: 
		{name: o}
		{description: The LmiProperty object to be assigned from.}
	}
	{return: p if the assignment operation was successful; NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiProperty* LmiPropertyAssign(LmiProperty* p, const LmiProperty* o);

LMI_INLINE_DECLARATION LmiBool LmiPropertyEqual(const LmiProperty* p, const LmiProperty* o);
LMI_INLINE_DECLARATION LmiBool LmiPropertyLess(const LmiProperty* p, const LmiProperty* o);

/**
{function visibility="public":
	{name: LmiPropertyGetName}
	{parent: LmiProperty}
	{description: To get the name of an LmiProperty object.}
	{prototype: const LmiString* LmiPropertyGetName(const LmiProperty* p)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{return: The name of the object.}
}
*/
LMI_INLINE_DECLARATION const LmiString* LmiPropertyGetName(const LmiProperty* p);

/**
{function visibility="public":
	{name: LmiPropertyGetNameCStr}
	{parent: LmiProperty}
	{description: To get the name of an LmiProperty object in CStr format.}
	{prototype: const char* LmiPropertyGetNameCStr(const LmiProperty* p)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{return: The name of the object.}
}
*/
LMI_INLINE_DECLARATION const char* LmiPropertyGetNameCStr(const LmiProperty* p);

/**
{function visibility="public":
	{name: LmiPropertyGetValue}
	{parent: LmiProperty}
	{description: To get the value of an LmiProperty object.}
	{prototype: const LmiString* LmiPropertyGetValue(const LmiProperty* p)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{return: The value of the object.}
}
*/
LMI_INLINE_DECLARATION const LmiString* LmiPropertyGetValue(const LmiProperty* p);

/**
{function visibility="public":
	{name: LmiPropertyGetValueCStr}
	{parent: LmiProperty}
	{description: To get the value of an LmiProperty object in CStr format.}
	{prototype: const char* LmiPropertyGetValueCStr(const LmiProperty* p)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{return: The value of the object.}
}
*/
LMI_INLINE_DECLARATION const char* LmiPropertyGetValueCStr(const LmiProperty* p);

/**
{function visibility="public":
	{name: LmiPropertySetValue}
	{parent: LmiProperty}
	{description: To change the value of an LmiProperty object.}
	{prototype: LmiBool LmiPropertySetValue(LmiProperty* p, const LmiString* value)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{parameter: 
		{name: value}
		{description: The new value.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiPropertySetValue(LmiProperty* p, const LmiString* value);

/**
{function visibility="public":
	{name: LmiPropertySetValueCStr}
	{parent: LmiProperty}
	{description: To change the value of an LmiProperty object.}
	{prototype: LmiBool LmiPropertySetValueCStr(LmiProperty* p, const char* value)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{parameter: 
		{name: value}
		{description: The new value.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiPropertySetValueCStr(LmiProperty* p, const char* value);

/**
{function visibility="public":
	{name: LmiPropertyIsEqual}
	{parent: LmiProperty}
	{description: To check whether the name of the LmiProperty object matches the given string.}
	{prototype: LmiBool LmiPropertyIsEqual(const LmiProperty* p, const LmiString* name)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{parameter: 
		{name: name}
		{description: The name string to be matched against.}
	}
	{return: LMI_TRUE if the name of the property matches with the given name; LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiPropertyIsEqual(const LmiProperty* p, const LmiString* name);

/**
{function visibility="public":
	{name: LmiPropertyIsEqualCStr}
	{parent: LmiProperty}
	{description: To check whether the name of the LmiProperty object matches the given string (in CStr format).}
	{prototype: LmiBool LmiPropertyIsEqualCStr(const LmiProperty* p, const char* name)}
	{parameter: 
		{name: p}
		{description: The LmiProperty object.}
	}
	{parameter: 
		{name: name}
		{description: The name string to be matched against.}
	}
	{return: LMI_TRUE if the name of the property matches with the given name; LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiPropertyIsEqualCStr(const LmiProperty* p, const char* name);

Declare_LmiVector(LmiProperty)

typedef LmiVector(LmiProperty) LmiPropertyList;

LMI_INLINE_DECLARATION LmiPropertyList* LmiPropertyListConstructDefault(LmiPropertyList* l, LmiAllocator* a);
LMI_INLINE_DECLARATION void LmiPropertyListDestruct(LmiPropertyList* l);
LMI_INLINE_DECLARATION LmiBool LmiPropertyListAdd(LmiPropertyList* l, const LmiProperty* o);
LMI_INLINE_DECLARATION void LmiPropertyListClear(LmiPropertyList* l);
LMI_INLINE_DECLARATION LmiProperty* LmiPropertyListAt(LmiPropertyList* l, LmiSizeT n);
LMI_INLINE_DECLARATION const LmiProperty* LmiPropertyListAtConst(const LmiPropertyList* l, LmiSizeT n);
LMI_INLINE_DECLARATION LmiSizeT LmiPropertyListSize(const LmiPropertyList* l);

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiPropertyInline.h>
#endif

LMI_END_EXTERN_C

#endif /* LMI_PROPERTY_H_ */
