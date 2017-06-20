/**
{file:
	{name: VidyoCalendarConnProps.h}
	{description: Vidyo Calendar Connection Properties. }
	{copyright:
		(c) 2014-2016 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.
	}
}
*/
#ifndef VIDYO_CALENDARCONNPROPS_H_ 
#define VIDYO_CALENDARCONNPROPS_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="public":
	{name: VidyoCalendarConnectParamType}
	{parent: VidyoCalendar}
	{include: Lmi/VidyoClient/VidyoCalendarConnProps.h}
	{description: This type indicates the connection parameter types that would be required for connecting to a specific calendar service.}
	{value:
		{name: VIDYO_CALENDARCONNECTPARAMTYPE_Unknown}
		{description: Undefined type.}
	}
	{value:
		{name: VIDYO_CALENDARCONNECTPARAMTYPE_UserId}
		{description: Parameter type that specifies a user ID string.}
	}
	{value:
		{name: VIDYO_CALENDARCONNECTPARAMTYPE_PasswordToken}
		{description: Parameter type that specifies a password or token string.}
	}
	{value:
		{name: VIDYO_CALENDARCONNECTPARAMTYPE_Mailbox}
		{description: Parameter type that specifies a mailbox name string.}
	}
	{value:
		{name: VIDYO_CALENDARCONNECTPARAMTYPE_ServerAddress}
		{description: Parameter type that specifies a server address string.}
	}
}
*/
typedef enum
{
	VIDYO_CALENDARCONNECTPARAMTYPE_Unknown,
	VIDYO_CALENDARCONNECTPARAMTYPE_UserId,
	VIDYO_CALENDARCONNECTPARAMTYPE_PasswordToken,
	VIDYO_CALENDARCONNECTPARAMTYPE_Mailbox,
	VIDYO_CALENDARCONNECTPARAMTYPE_ServerAddress
} VidyoCalendarConnectParamType;

VidyoCalendarConnectParamType* VidyoCalendarConnectParamTypeConstructCopy(VidyoCalendarConnectParamType* x, const VidyoCalendarConnectParamType* y);
void VidyoCalendarConnectParamTypeDestruct(VidyoCalendarConnectParamType* x);
VidyoCalendarConnectParamType* VidyoCalendarConnectParamTypeAssign(VidyoCalendarConnectParamType* x, const VidyoCalendarConnectParamType* y);


Declare_LmiVector(VidyoCalendarConnectParamType)

/**
{type visibility="public":
	{name: VidyoCalendarConnProps}
	{parent: VidyoCalendar}
	{include: Lmi/VidyoClient/VidyoCalendarConnProps.h}
	{description: Properties for connecting to a calendar service.}
	{member:
		{name: connPropType}
		{type: VidyoCalendarConnectParamType}
		{description:}
	}
	{member:
		{name: connPropValue}
		{type: LmiString}
		{description:}
	}
}
*/
typedef struct
{
	VidyoCalendarConnectParamType connPropType;
	LmiString connPropValue;
} VidyoCalendarConnProps;

/**
{function visibility="private":
	{name: VidyoCalendarConnPropsConstructDefault}
	{parent: VidyoCalendarConnProps}
	{description: Constructs an VidyoCalendarConnProps object.}
	{prototype: 
		VidyoCalendarConnProps *VidyoCalendarConnPropsConstructDefault(VidyoCalendarConnProps *p, LmiAllocator *alloc)
	}
	{parameter: 
		{name: p} 
		{description: The VidyoCalendarConnProps object to construct.}
	}
	{parameter: 
		{name: alloc} 
		{description: An allocator to use for miscellaneous items.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoCalendarConnProps *VidyoCalendarConnPropsConstructDefault(VidyoCalendarConnProps *p, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoCalendarConnPropsConstructCopy}
	{parent: VidyoCalendarConnProps}
	{description: Constructs an VidyoCalendarConnProps object as a copy of an existing object.}
	{prototype: 
		VidyoCalendarConnProps *VidyoCalendarConnPropsConstructCopy(VidyoCalendarConnProps *d, const VidyoCalendarConnProps *s)
	}
	{parameter: 
		{name: d} 
		{description: The VidyoCalendarConnProps object to construct.}
	}
	{parameter: 
		{name: s} 
		{description: The existing VidyoCalendarConnProps object to copy.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoCalendarConnProps *VidyoCalendarConnPropsConstructCopy(VidyoCalendarConnProps *d, const VidyoCalendarConnProps *s);

/**
{function visibility="private":
	{name: VidyoCalendarConnPropsDestruct}
	{parent: VidyoCalendarConnProps}
	{description: Destructs an VidyoCalendarConnProps object.}
	{prototype: 
		void VidyoCalendarConnPropsDestruct(VidyoCalendarConnProps *p)
	}
	{parameter: 
		{name: p} 
		{description: The VidyoCalendarConnProps object to destruct.}
	}
}
*/
void VidyoCalendarConnPropsDestruct(VidyoCalendarConnProps *p);

/**
{function visibility="private":
	{name: VidyoCalendarConnPropsAssign}
	{parent: VidyoCalendarConnProps}
	{description: Assign the contents of one VidyoCalendarConnProps to another.}
	{prototype: 
		VidyoCalendarConnProps *VidyoCalendarConnPropsAssign(VidyoCalendarConnProps *d, const VidyoCalendarConnProps *s)
	}
	{parameter: 
		{name: d} 
		{description: The object to assign to.}
	}
	{parameter: 
		{name: s} 
		{description: The object to copy.}
	}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoCalendarConnProps *VidyoCalendarConnPropsAssign(VidyoCalendarConnProps *d, const VidyoCalendarConnProps *s);

/**
{function visibility="private":
	{name: VidyoCalendarConnPropsEqual}
	{parent: VidyoCalendarConnProps}
	{description: Check the equality of VidyoCalendarConnProps object.}
	{prototype: 
		LmiBool VidyoCalendarConnPropsEqual(const VidyoCalendarConnProps *a, const VidyoCalendarConnProps *b)
	}
	{parameter: 
		{name: a} 
		{description: The VidyoCalendarConnProps object to compare.}
	}
	{parameter: 
		{name: b} 
		{description: The VidyoCalendarConnProps object to compare.}
	}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoCalendarConnPropsEqual(const VidyoCalendarConnProps *a, const VidyoCalendarConnProps *b);

Declare_LmiVector(VidyoCalendarConnProps)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoCalendarConnPropsInline.h"
#endif


#endif /* VIDYO_CALENDARCONNPROPS_H_  */
