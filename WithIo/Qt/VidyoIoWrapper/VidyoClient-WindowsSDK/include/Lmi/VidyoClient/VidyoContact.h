/** 
{file:
	{name: VidyoContact.h}
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
#ifndef VIDYO_CONTACT_H_ 
#define VIDYO_CONTACT_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Utils/LmiSet.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C

/**
{type apigroup="simple" visibility="public":
	{name: VidyoContactPresenceState}
	{parent: VidyoContact}
	{description: Presence status codes.}
	{value: {name: VIDYO_CONTACTPRESENCESTATE_Unavailable}      {description: Unavailable}}
	{value: {name: VIDYO_CONTACTPRESENCESTATE_DoNotDisturb}     {description: Do not disturb}}
	{value: {name: VIDYO_CONTACTPRESENCESTATE_ExtendedAway}     {description: Extended away}}
	{value: {name: VIDYO_CONTACTPRESENCESTATE_Away}             {description: Away}}
	{value: {name: VIDYO_CONTACTPRESENCESTATE_Available}        {description: Available}}
	{value: {name: VIDYO_CONTACTPRESENCESTATE_InterestedInChat} {description: Interested in chat}}
}
*/
/* Please keep these enums sorted by increasing gregariousness. */
typedef enum
{
	VIDYO_CONTACTPRESENCESTATE_Unavailable,
	VIDYO_CONTACTPRESENCESTATE_DoNotDisturb,
	VIDYO_CONTACTPRESENCESTATE_ExtendedAway,
	VIDYO_CONTACTPRESENCESTATE_Away,
	VIDYO_CONTACTPRESENCESTATE_Available,
	VIDYO_CONTACTPRESENCESTATE_InterestedInChat,
} VidyoContactPresenceState;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoContactSubscriptionState}
	{parent: VidyoContact}
	{description: Describes the relationship between a contact publishing its contact information and
		a contact subscribing to that information.}
	{value: {name: VIDYO_CONTACTSUBSCRIPTIONSTATE_Unavailable} {description: The subscriber's state is unknown.}}
	{value: {name: VIDYO_CONTACTSUBSCRIPTIONSTATE_NotSubscribed} {description: The subscriber is not
		currently subscribed to the publisher's information. No action is pending on the subscription state.}}
	{value: {name: VIDYO_CONTACTSUBSCRIPTIONSTATE_Preapproved} {description: The subscriber has not
		subscribed to the publisher's information, however, the publisher has already granted permission
		to the subscriber.}}
	{value: {name: VIDYO_CONTACTSUBSCRIPTIONSTATE_AwaitingApproval} {description: The subscriber has
		subscribed to the publisher's information and is waiting for the publisher to grant permission
		for the subscription.}}
	{value: {name: VIDYO_CONTACTSUBSCRIPTIONSTATE_Subscribed} {description: The subscriber is currently
		subscribed to the publisher's information.}}
}
*/
typedef enum
{
	VIDYO_CONTACTSUBSCRIPTIONSTATE_Unavailable,
	VIDYO_CONTACTSUBSCRIPTIONSTATE_NotSubscribed,
	VIDYO_CONTACTSUBSCRIPTIONSTATE_Preapproved,
	VIDYO_CONTACTSUBSCRIPTIONSTATE_AwaitingApproval,
	VIDYO_CONTACTSUBSCRIPTIONSTATE_Subscribed,
} VidyoContactSubscriptionState;

/**
{type apigroup="simple" visibility="public":
	{name: VidyoContactProperty}
	{parent: VidyoContact}
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
} VidyoContactProperty;

/**
{function visibility="private":
	{name: VidyoContactPropertyConstruct}
	{parent: VidyoContactProperty}
	{description: Constructs an VidyoContactProperty object.}
	{prototype: VidyoContactProperty *VidyoContactPropertyConstruct(VidyoContactProperty *p, const LmiString* value, const LmiVector(LmiString)* types, LmiAllocator *alloc)}
	{parameter: {name: p} {description: The VidyoContactProperty object to construct.}}
	{parameter: {name: value} {description: The value of the property.}}
	{parameter: {name: types} {description: The vector of type metadata associated with the property.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContactProperty *VidyoContactPropertyConstruct(VidyoContactProperty *p, const LmiString* value, const LmiVector(LmiString)* types, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoContactPropertyConstructCopy}
	{parent: VidyoContactProperty}
	{description: Constructs an VidyoContactProperty object as a copy of an existing object.}
	{prototype: VidyoContactProperty *VidyoContactPropertyConstructCopy(VidyoContactProperty *d, const VidyoContactProperty *s)}
	{parameter: {name: d} {description: The VidyoContactProperty object to construct.}}
	{parameter: {name: s} {description: The existing VidyoContactProperty object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContactProperty *VidyoContactPropertyConstructCopy(VidyoContactProperty *d, const VidyoContactProperty *s);

/**
{function visibility="private":
	{name: VidyoContactPropertyDestruct}
	{parent: VidyoContactProperty}
	{description: Destructs an VidyoContactProperty object.}
	{prototype: void VidyoContactPropertyDestruct(VidyoContactProperty *p)}
	{parameter: {name: p} {description: The VidyoContactProperty object to destruct.}}
}
*/
void VidyoContactPropertyDestruct(VidyoContactProperty *p);

/**
{function visibility="private":
	{name: VidyoContactPropertyAssign}
	{parent: VidyoContactProperty}
	{description: Assign the contents of one VidyoContactProperty to another.}
	{prototype: VidyoContactProperty *VidyoContactPropertyAssign(VidyoContactProperty *d, const VidyoContactProperty *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoContactProperty *VidyoContactPropertyAssign(VidyoContactProperty *d, const VidyoContactProperty *s);

/**
{function visibility="private":
	{name: VidyoContactPropertyEqual}
	{parent: VidyoContactProperty}
	{description: Check the equality of VidyoContactProperty object.}
	{prototype: LmiBool VidyoContactPropertyEqual(const VidyoContactProperty *a, const VidyoContactProperty *b)}
	{parameter: {name: a} {description: The VidyoContactProperty object to compare.}}
	{parameter: {name: b} {description: The VidyoContactProperty object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoContactPropertyEqual(const VidyoContactProperty *a, const VidyoContactProperty *b);

Declare_LmiVector(VidyoContactProperty)

/**
{type apigroup="simple" visibility="public":
	{name: VidyoContact}
	{parent: Endpoint}
	{include: Lmi/VidyoClient/VidyoContact.h}
	{description: Stores contact information and presence status.}
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
		{type: LmiVector(VidyoContactProperty)}
		{description:}
	}
	{member:
		{name: telephones}
		{type: LmiVector(VidyoContactProperty)}
		{description:}
	}
	{member:
		{name: groups}
		{type: LmiVector(LmiString)}
		{description:}
	}
	{member:
		{name: presenceState}
		{type: VidyoContactPresenceState}
		{description:}
	}
	{member:
		{name: presenceStatus}
		{type: LmiString}
		{description:}
	}
	{member:
		{name: publicationState}
		{type: VidyoContactSubscriptionState}
		{description:}
	}
	{member:
		{name: subscriptionState}
		{type: VidyoContactSubscriptionState}
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
	LmiVector(VidyoContactProperty) emails;
	LmiVector(VidyoContactProperty) telephones;
	LmiVector(LmiString) groups;
	VidyoContactPresenceState presenceState;
	LmiString presenceStatus;
	VidyoContactSubscriptionState publicationState;
	VidyoContactSubscriptionState subscriptionState;
	LmiString photo;
	LmiTime timestamp;
} VidyoContact;

/**
{function visibility="private":
	{name: VidyoContactConstruct}
	{parent: VidyoContact}
	{description: Constructs an VidyoContact object.}
	{prototype: VidyoContact *VidyoContactConstruct(VidyoContact *c, const LmiString *id, LmiAllocator *alloc)}
	{parameter: {name: c} {description: The VidyoContact object to construct.}}
	{parameter: {name: id} {description: The contact's user ID.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous items.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContact *VidyoContactConstruct(VidyoContact *c, const LmiString *id, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoContactConstructCopy}
	{parent: VidyoContact}
	{description: Constructs an VidyoContact object as a copy of an existing object.}
	{prototype: VidyoContact *VidyoContactConstructCopy(VidyoContact *d, const VidyoContact *s)}
	{parameter: {name: d} {description: The VidyoContact object to construct.}}
	{parameter: {name: s} {description: The existing VidyoContact object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoContact *VidyoContactConstructCopy(VidyoContact *d, const VidyoContact *s);

/**
{function visibility="private":
	{name: VidyoContactDestruct}
	{parent: VidyoContact}
	{description: Destructs an VidyoContact object.}
	{prototype: void VidyoContactDestruct(VidyoContact *c)}
	{parameter: {name: c} {description: The VidyoContact object to destruct.}}
}
*/
void VidyoContactDestruct(VidyoContact *c);

/**
{function visibility="private":
	{name: VidyoContactAssign}
	{parent: VidyoContact}
	{description: Assign the contents of one VidyoContact to another.}
	{prototype: VidyoContact *VidyoContactAssign(VidyoContact *d, const VidyoContact *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoContact *VidyoContactAssign(VidyoContact *d, const VidyoContact *s);

/**
{function visibility="private":
	{name: VidyoContactEqual}
	{parent: VidyoContact}
	{description: Check the equality of VidyoContact object.}
	{prototype: LmiBool VidyoContactEqual(const VidyoContact *a, const VidyoContact *b)}
	{parameter: {name: a} {description: The VidyoContact object to compare.}}
	{parameter: {name: b} {description: The VidyoContact object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoContactEqual(const VidyoContact *a, const VidyoContact *b);

LmiBool VidyoContactLess(const VidyoContact* a, const VidyoContact* b);

Declare_LmiSet(VidyoContact)

Declare_LmiVector(VidyoContact)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoContactInline.h"
#endif

#endif /* VIDYO_CONTACT_H_ */
