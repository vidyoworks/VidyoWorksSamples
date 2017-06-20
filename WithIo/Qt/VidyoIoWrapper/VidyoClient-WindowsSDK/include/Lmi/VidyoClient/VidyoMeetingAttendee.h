/**
{file:
	{name: VidyoMeetingAttendee.h}
	{description: MeetingAttendee Entity Library. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
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
#ifndef VIDYO_MEETING_ATTENDEE_H_ 
#define VIDYO_MEETING_ATTENDEE_H_ 

#include <Lmi/Os/LmiLog.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>
#include "VidyoCalendarLibraryDefs.h"

LMI_BEGIN_EXTERN_C


/**
{type visibility="public":
	{name: VidyoAttendeeParticipationRole}
	{parent: VidyoMeetingAttendee}	
	{description: 
		{p: This indicates the role of the local user in a meeting. }
		{p: Maps directly to participation roles defined in IETF RFC 5545. }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONROLE_Chair}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONROLE_Required}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONROLE_Optional}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONROLE_Informational}
		{description:  Maps to NON-PARTICIPANT role in RFC type}
	}
}
*/
typedef enum
{
	VIDYO_ATTENDEEPARTICIPATIONROLE_Chair,
	VIDYO_ATTENDEEPARTICIPATIONROLE_Required,
	VIDYO_ATTENDEEPARTICIPATIONROLE_Optional,
	VIDYO_ATTENDEEPARTICIPATIONROLE_Informational
} VidyoAttendeeParticipationRole;


/**
{type visibility="public":
	{name: VidyoAttendeeParticipationStatus}
	{parent: VidyoMeetingAttendee}
	{description:
		{p: This indicates the role of the local user in a meeting. }
		{p: Maps directly to participation statuses defined in IETF RFC 5545. }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_NeedsAction}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_Organized}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_Accepted}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_Declined}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_Tentative}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_Delegated}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_None}
		{description: Response not required }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_Completed}
		{description: }
	}
	{value:
		{name: VIDYO_ATTENDEEPARTICIPATIONSTATUS_InProcess}
		{description: }
	}
}
*/
typedef enum
{	
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_NeedsAction,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_Organized,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_Accepted,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_Declined,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_Tentative,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_Delegated,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_None,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_Completed,
	VIDYO_ATTENDEEPARTICIPATIONSTATUS_InProcess
} VidyoAttendeeParticipationStatus;


/**
{type visibility="public":
	{name: VidyoMeetingAttendee}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoMeetingAttendee.h}
	{description: Stores information for a meeting attendee.}
	{member:
		{name: name}
		{type: LmiString}
		{description: Attendee name as held by the underlying calendar service}
	}
	{member:
		{name: email}
		{type: LmiString}
		{description: Email for attendee.}
	}
	{member:
		{name: role}
		{type: VidyoAttendeeParticipationRole}
		{description: Role for the attendee as defined by the roleparam specified in RFC 5545}
	}
	{member:
		{name: status}
		{type: VidyoAttendeeParticipationStatus}
		{description: Participation status of the attendee for the meeting as specified by the STATUS property name specified in RFC 5545 }
	}

}
*/
typedef struct 
{
	LmiVoidPtr userData;
	LmiAllocator *alloc;
	LmiString name;
	LmiString email;
	VidyoAttendeeParticipationRole role;
	VidyoAttendeeParticipationStatus status;
}VidyoMeetingAttendee;




/**** -----------------------****/
/**** ---- CONSTRUCTORS -----****/
/**** -----------------------****/

/*****
{function visibility="private":
	{name: VidyoMeetingAttendeeConstructFromPluginAttendee}
	{parent: VidyoMeetingAttendee}
	{description:
		{p: Private constructor for Vidyo meeting attendee}
		{p: Will be called through: }
		{p: - VidyoMeetingConstructDeserialize }
		{p: - Inbound event from meeting data search, fed through the callback }
	}
	{prototype:
		VidyoMeetingAttendee *VidyoMeetingAttendeeConstructFromPluginAttendee(VidyoMeetingAttendee *m, const MeetingAttendee *attendeeIn, LmiAllocator *alloc)
	}
	{parameter:
		{name: m}
		{description: Meeting instance being constructed}
	}
	{parameter:
		{name: attendeeIn}
		{description: attendee data used to construct the MeetingAttendee class from }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*****/
VidyoMeetingAttendee *VidyoMeetingAttendeeConstructFromPluginAttendee(VidyoMeetingAttendee *m, const MeetingAttendee *attendeeIn, LmiAllocator *alloc);


/*****
{function :
	{name: VidyoMeetingAttendeeConstruct}
	{parent: VidyoMeetingAttendee}
	{description: Constructs a VidyoMeetingAttendee object.}
	{prototype: VidyoMeetingAttendee *VidyoMeetingAttendeeConstruct(VidyoMeetingAttendee *m, const LmiString *name, const LmiString *email, VidyoAttendeeParticipationRole role, VidyoAttendeeParticipationStatus status, LmiAllocator *alloc)}
	{parameter: 
		{name: m} 
		{description: The VidyoMeetingAttendee object to construct.}
	}
	{parameter: 
		{name: name}		
		{description:}
	}
	{parameter: 
		{name: email}		
		{description:}
	}
	{parameter: 
		{name: role}		
		{description:}
	}
	{parameter: 
		{name: status}		
		{description:}
	}
	{parameter: 
		{name: alloc} 
		{description: An allocator to use for miscellaneous items.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoMeetingAttendee *VidyoMeetingAttendeeConstruct(VidyoMeetingAttendee *m, const LmiString *name, const LmiString *email, VidyoAttendeeParticipationRole role, VidyoAttendeeParticipationStatus status, LmiAllocator *alloc);


/**
{function visibility="private":
	{name: VidyoMeetingAttendeeConstructCopy}
	{parent: VidyoMeetingAttendee}
	{description: Constructs an VidyoMeetingAttendee object as a copy of another.}
	{prototype: VidyoMeetingAttendee *VidyoMeetingAttendeeConstructCopy(VidyoMeetingAttendee *obj, const VidyoMeetingAttendee *other)}
	{parameter: 
		{name: obj} 
		{description: The VidyoMeetingAttendee object to construct.}
	}
	{parameter: 
		{name: other} 
		{description: The call object to make a copy of.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoMeetingAttendee *VidyoMeetingAttendeeConstructCopy(VidyoMeetingAttendee *obj, const VidyoMeetingAttendee *other);

/**
{function visibility="private":
	{name: VidyoMeetingAttendeeDestruct}
	{parent: VidyoMeetingAttendee}
	{description: Destructs an VidyoMeetingAttendee object.}
	{prototype: void VidyoMeetingAttendeeDestruct(VidyoMeetingAttendee *obj)}
	{parameter: 
		{name: obj} 
		{description: The VidyoMeetingAttendee object to destruct.}
	}
}
*/
void VidyoMeetingAttendeeDestruct(VidyoMeetingAttendee *mtgAttendee);


/**
{function visibility="private":
	{name: VidyoMeetingAttendeeAssign}
	{parent: VidyoMeetingAttendee}
	{description: Assigns one VidyoMeetingAttendee object the value of another. }
	{prototype: VidyoMeetingAttendee *VidyoMeetingAttendeeAssign(VidyoMeetingAttendee *obj, const VidyoMeetingAttendee *other)}
	{parameter: 
		{name: obj} 
		{description: The VidyoMeetingAttendee object.}
	}
	{parameter: 
		{name: other} 
		{description: The call object to make a copy of.}
	}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/
VidyoMeetingAttendee *VidyoMeetingAttendeeAssign(VidyoMeetingAttendee *obj, const VidyoMeetingAttendee *other);


/**
{function visibility="private":
	{name: VidyoMeetingAttendeeEqual}
	{parent: VidyoMeetingAttendee}
	{description: Check the equality of VidyoMeetingAttendee object.}
	{prototype: LmiBool VidyoMeetingAttendeeEqual(const VidyoMeetingAttendee *a, const VidyoMeetingAttendee *b)}
	{parameter: {name: a} {description: The VidyoMeetingAttendee object to compare.}}
	{parameter: {name: b} {description: The VidyoMeetingAttendee object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoMeetingAttendeeEqual(const VidyoMeetingAttendee *a, const VidyoMeetingAttendee *b);


Declare_LmiVector(VidyoMeetingAttendee)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoMeetingAttendeeInline.h"
#endif

#endif /* VIDYO_MEETING_ATTENDEE_H_ */

