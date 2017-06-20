/** 
{file:
	{name: VidyoContactInfo.h}
	{description: Vidyo Contact. }
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_CONTACTINFO_H_
#define VIDYO_CONTACTINFO_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Utils/LmiSet.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C

/**
{type apigroup="simple" visibility="public":
	{name: VidyoContactInfoProperty}
	{parent: VidyoContactInfo}
	{description: Contact Property that has value and metadata for fields.}
	{member:
		{name: value}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: types}
		{type: LmiVector(LmiString)}
		{description:}
	}
}
*/
typedef struct {
	LmiString value;
	LmiVector(LmiString) types;
} VidyoContactInfoProperty;

/**
{function visibility="private":
	{name: VidyoContactInfoPropertyConstruct}
	{parent: VidyoContactInfoProperty}
	{description: Constructs an VidyoContactInfoProperty object.}
	{prototype: VidyoContactInfoProperty *VidyoContactInfoPropertyConstruct(VidyoContactInfoProperty *p, const LmiString* value, const LmiVector(LmiString)* types, LmiAllocator *alloc)}
	{parameter: {name: p} {description: The VidyoContactInfoProperty object to construct.}}
	{parameter: {name: value} {description: The value of the property.}}
	{parameter: {name: types} {description: The vector of type metadata associated with the property.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContactInfoProperty *VidyoContactInfoPropertyConstruct(VidyoContactInfoProperty *p, const LmiString* value, const LmiVector(LmiString)* types, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoContactInfoPropertyConstructCopy}
	{parent: VidyoContactInfoProperty}
	{description: Constructs an VidyoContactInfoProperty object as a copy of an existing object.}
	{prototype: VidyoContactInfoProperty *VidyoContactInfoPropertyConstructCopy(VidyoContactInfoProperty *d, const VidyoContactInfoProperty *s)}
	{parameter: {name: d} {description: The VidyoContactInfoProperty object to construct.}}
	{parameter: {name: s} {description: The existing VidyoContactInfoProperty object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContactInfoProperty *VidyoContactInfoPropertyConstructCopy(VidyoContactInfoProperty *d, const VidyoContactInfoProperty *s);

/**
{function visibility="private":
	{name: VidyoContactInfoPropertyDestruct}
	{parent: VidyoContactInfoProperty}
	{description: Destructs an VidyoContactInfoProperty object.}
	{prototype: void VidyoContactInfoPropertyDestruct(VidyoContactInfoProperty *p)}
	{parameter: {name: p} {description: The VidyoContactInfoProperty object to destruct.}}
}
*/
void VidyoContactInfoPropertyDestruct(VidyoContactInfoProperty *p);

/**
{function visibility="private":
	{name: VidyoContactInfoPropertyAssign}
	{parent: VidyoContactInfoProperty}
	{description: Assign the contents of one VidyoContactInfoProperty to another.}
	{prototype: VidyoContactInfoProperty *VidyoContactInfoPropertyAssign(VidyoContactInfoProperty *d, const VidyoContactInfoProperty *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoContactInfoProperty *VidyoContactInfoPropertyAssign(VidyoContactInfoProperty *d, const VidyoContactInfoProperty *s);

/**
{function visibility="private":
	{name: VidyoContactInfoPropertyEqual}
	{parent: VidyoContactInfoProperty}
	{description: Check the equality of VidyoContactInfoProperty object.}
	{prototype: LmiBool VidyoContactInfoPropertyEqual(const VidyoContactInfoProperty *a, const VidyoContactInfoProperty *b)}
	{parameter: {name: a} {description: The VidyoContactInfoProperty object to compare.}}
	{parameter: {name: b} {description: The VidyoContactInfoProperty object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoContactInfoPropertyEqual(const VidyoContactInfoProperty *a, const VidyoContactInfoProperty *b);

Declare_LmiVector(VidyoContactInfoProperty)

/**
{type apigroup="simple" visibility="public":
	{name: VidyoContactInfo}
	{parent: Endpoint}
	{include: Lmi/VidyoClient/VidyoContactInfo.h}
	{description: Stores contact information returned from search.}
	{member:
		{name: id}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: name}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: handle}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: nickname}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: emails}
		{type: LmiVector(VidyoContactInfoProperty)}
		{description:}
	}
	{member:
		{name: telephones}
		{type: LmiVector(VidyoContactInfoProperty)}
		{description:}
	}
	{member:
		{name: groups}
		{type: LmiVector(LmiString)}
		{description:}
	}
	{member:
		{name: photo}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: timestamp}
		{type: LmiTime}
		{description:}
	}
}
*/
typedef struct
{
	LmiString id;
	LmiString name;
	LmiString handle; /* user's name for contact */
	LmiString nickname; /* contact's name for contact */
	LmiVector(VidyoContactInfoProperty) emails;
	LmiVector(VidyoContactInfoProperty) telephones;
	LmiVector(LmiString) groups;
	LmiString photo;
	LmiTime timestamp;
} VidyoContactInfo;

/**
{function visibility="private":
	{name: VidyoContactInfoConstruct}
	{parent: VidyoContactInfo}
	{description: Constructs an VidyoContactInfo object.}
	{prototype: VidyoContactInfo *VidyoContactInfoConstruct(VidyoContactInfo *c, const LmiString *id, LmiAllocator *alloc)}
	{parameter: {name: c} {description: The VidyoContactInfo object to construct.}}
	{parameter: {name: id} {description: The contact's user ID.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContactInfo *VidyoContactInfoConstruct(VidyoContactInfo *c, const LmiString *id, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoContactInfoConstructCopy}
	{parent: VidyoContactInfo}
	{description: Constructs an VidyoContactInfo object as a copy of an existing object.}
	{prototype: VidyoContactInfo *VidyoContactInfoConstructCopy(VidyoContactInfo *d, const VidyoContactInfo *s)}
	{parameter: {name: d} {description: The VidyoContactInfo object to construct.}}
	{parameter: {name: s} {description: The existing VidyoContactInfo object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContactInfo *VidyoContactInfoConstructCopy(VidyoContactInfo *d, const VidyoContactInfo *s);

/**
{function visibility="private":
	{name: VidyoContactInfoDestruct}
	{parent: VidyoContactInfo}
	{description: Destructs an VidyoContactInfo object.}
	{prototype: void VidyoContactInfoDestruct(VidyoContactInfo *c)}
	{parameter: {name: c} {description: The VidyoContactInfo object to destruct.}}
}
*/
void VidyoContactInfoDestruct(VidyoContactInfo *c);

/**
{function visibility="private":
	{name: VidyoContactInfoAssign}
	{parent: VidyoContactInfo}
	{description: Assign the contents of one VidyoContactInfo to another.}
	{prototype: VidyoContactInfo *VidyoContactInfoAssign(VidyoContactInfo *d, const VidyoContactInfo *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoContactInfo *VidyoContactInfoAssign(VidyoContactInfo *d, const VidyoContactInfo *s);

/**
{function visibility="private":
	{name: VidyoContactInfoEqual}
	{parent: VidyoContactInfo}
	{description: Check the equality of VidyoContactInfo object.}
	{prototype: LmiBool VidyoContactInfoEqual(const VidyoContactInfo *a, const VidyoContactInfo *b)}
	{parameter: {name: a} {description: The VidyoContactInfo object to compare.}}
	{parameter: {name: b} {description: The VidyoContactInfo object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoContactInfoEqual(const VidyoContactInfo *a, const VidyoContactInfo *b);

LmiBool VidyoContactInfoLess(const VidyoContactInfo* a, const VidyoContactInfo* b);

Declare_LmiSet(VidyoContactInfo)
Declare_LmiVector(VidyoContactInfo)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoContactInfoInline.h"
#endif

#endif /* VIDYO_CONTACTINFO_H_ */
