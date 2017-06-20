/**
{file:
	{name: VidyoMeeting.h}
	{description: User Entity Library. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/

#ifndef VIDYO_MEETING_H_ 
#define VIDYO_MEETING_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiMap.h>
#include <Lmi/Utils/LmiUnordered.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiUri.h>
#include <Lmi/Os/LmiSharedPtr.h>
#include <Lmi/Os/LmiLog.h>
#include "VidyoMeetingAttendee.h"
#include "VidyoForwardDecl.h"

LMI_BEGIN_EXTERN_C

struct VidyoMeetingFeedbackImpl_;
typedef struct VidyoMeetingFeedbackImpl_ VidyoMeetingFeedbackImpl;
Declare_LmiSharedPtr(VidyoMeetingFeedbackImpl)
Declare_LmiSharedPtrWrapper(VidyoMeetingFeedback, VidyoMeetingFeedbackImpl)
Declare_LmiWeakPtrWrapper(VidyoMeetingFeedbackHandle, VidyoMeetingFeedback, VidyoMeetingFeedbackImpl)
Declare_LmiList(VidyoMeetingFeedbackHandle)

struct VidyoMeetingImpl_;
typedef struct VidyoMeetingImpl_ VidyoMeetingImpl;
Declare_LmiSharedPtr(VidyoMeetingImpl)
Declare_LmiSharedPtrWrapper(VidyoMeeting, VidyoMeetingImpl)
Declare_LmiWeakPtrWrapper(VidyoMeetingHandle, VidyoMeeting, VidyoMeetingImpl)
Declare_LmiList(VidyoMeetingHandle)
Declare_LmiList(VidyoMeeting)
Declare_LmiVector(VidyoMeeting)

/* =================================*/
/* ========== PACKAGES ============ */
/* =================================*/


/**
{package:
	{name: Meeting}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoMeeting.h}
	{description: Represents a meeting or appointment.  The meeting may have information in it to identify it as 
				a Vidyo specific meeting.
	}
}
*/

/* =================================*/
/* ======== OBJECT TYPES ========== */
/* =================================*/

/**
{type visibility="public":
	{name: VidyoMeetingType}
	{parent: Meeting}	
	{description: Type of meeting.}
	{value:
		{name: VIDYO_MEETINGTYPE_Vidyo}
		{description: A meeting containing Vidyo specific invite information.}
	}
	{value:
		{name: VIDYO_MEETINGTYPE_Standard}
		{description: Standard meeting - not Vidyo specific.}
	}
}
*/
typedef enum
{
	VIDYO_MEETINGTYPE_Vidyo,
	VIDYO_MEETINGTYPE_Standard,
} VidyoMeetingType;

/**
{type visibility="public":
	{name: VidyoMeetingActionResult}
	{parent: Meeting}
	{description: This type indicates the result of an attempt to create a meeting.}
	{value:
		{name: VIDYO_MEETINGACTIONRESULT_OK}
		{description: The meeting was created successfully.}
	}
	{value:
		{name: VIDYO_MEETINGACTIONRESULT_NoResponse}
		{description: The calendar resource did not respond in a reasonable amount of time for the intended action.}
	}
	{value:
		{name: VIDYO_MEETINGACTIONRESULT_Unauthorized}
		{description: The user is not allowed to create a meeting.}
	}
	{value:
		{name: VIDYO_MEETINGACTIONRESULT_RemovedByLocalUser}
		{description: Meeting was removedby the local user.}
	}
	{value:
		{name: VIDYO_MEETINGACTIONRESULT_RemovedByRemoteUser}
		{description: Meeting was removed by the remote user..}
	}
	{value:
		{name: VIDYO_MEETINGACTIONRESULT_MiscLocalError}
		{description: The server is rejecting the request to perform an action on the meeting due to some miscellaneous problem with the request.}
	}
	{value:
		{name: VIDYO_MEETINGACTIONRESULT_MiscRemoteError}
		{description: The server is rejecting the request to perform an action on the meeting due to some miscellaneous problem of its own.}
	}
}
*/
typedef enum
{
	VIDYO_MEETINGACTIONRESULT_OK,
	VIDYO_MEETINGACTIONRESULT_NoResponse,
	VIDYO_MEETINGACTIONRESULT_Unauthorized,
	VIDYO_MEETINGACTIONRESULT_RemovedByLocalUser,
	VIDYO_MEETINGACTIONRESULT_RemovedByRemoteUser,
	VIDYO_MEETINGACTIONRESULT_MiscLocalError,
	VIDYO_MEETINGACTIONRESULT_MiscRemoteError
} VidyoMeetingActionResult;




/**
{type reference-counted="yes":
	{name: VidyoMeeting}
	{parent: Meeting}	
	{description: Represents a meeting and all the related attributes.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique id that identifies a conference meeting at the service which the meeting is created through.}
	}
	{member:
		{name: type}
		{type: VidyoMeetingType}
		{description: Type of meeting.  See definition of VidyoMeetingType for possible values}
	}
	{member:
		{name: startDateTime}
		{type: LmiString}
		{description: Date and time that the meeting is scheduled for }
	}
	{member:
		{name: endDateTime}
		{type: LmiString}
		{description: Date and time that the meeting is scheduled for }
	}
	{member:
		{name: subject}
		{type: LmiString}
		{description: Subject for the meeting. }
	}
	{member:
		{name: location}
		{type: LmiString}
		{description: Subject for the meeting. }
	}
	{member:
		{name: ownerName}
		{type: LmiString}
		{description: Owner name for the meeting. }
	}
	{member:
		{name: ownerEmail}
		{type: LmiString}
		{description: Email for owner the meeting. }
	}
	{member:
		{name: vidyoMeetingRoomId}
		{type: LmiString}
		{description: Contains key information (URL, Room JID, etc) for the Vidyo room that the meeting is being held in if the meeting type is VIDYO_MEETINGTYPE_Vidyo.
						Otherwise it contains an empty string.
		}
	}
	{member:
		{name: body}
		{type: LmiString}
		{description: Body contents for the meeting. }
	}
}
*/

/**
{type visibility="private":
	{name: VidyoMeetingHandle}
	{parent: VidyoMeeting}
	{description: Weak reference to VidyoMeeting object.}
}
*/

/**
{type reference-counted="yes":
	{name: VidyoMeetingFeedback}
	{parent: VidyoMeeting}
	{description: Interface for registering callbacks that notify an application about events on the VidyoMeeting object. Multiple feedbacks can be registered on the same VidyoMeeting.}
}
*/

/**
{type visibility="private":
	{name: VidyoMeetingFeedbackHandle}
	{parent: VidyoMeeting}
	{description: Weak reference to the VidyoMeetingFeedback interface.}
}
*/


/**** -----------------------****/
/**** ---- CONSTRUCTORS -----****/
/**** -----------------------****/



/******
{function visibility="private":
	{name: VidyoMeetingConstruct}
	{parent: VidyoMeeting}
	{description:
		{p: Private constructor for Vidyo meeting }
		{p: Will be called through: }
		{p: - VidyoCalendarCreateMeeting }
		{p: - Inbound event from remote user fed through the callback }
	}
	{prototype:
		VidyoMeeting* VidyoMeetingConstruct(VidyoMeeting* meeting,
											VidyoMeetingFeedback* feedback,
											LmiVector(VidyoMeetingAttendee) attendees,
											LmiString startDateTime,
											LmiString endDateTime,
											LmiString owner,
											LmiString subject,
											LmiString location,
											LmiString body,
											VidyoMeetingType vidyoMeetingType,
											LmiString roomResourceId,
											LmiAllocator* alloc)
	}
	{parameter:
		{name: meeting}
		{description: Meeting instance being constructed}
	}
	{parameter:
		{name: feedback}
		{description: Feedback container to register against the meeting }
	}
	{parameter:
		{name: attendees}
		{description: A vector of VidyoMeetingAttendees which includes the roles for the meeting}
	}
	{parameter:
		{name: startDateTime}
		{description: Start date-time for the meeting.}
	}
	{parameter:
		{name: endDateTime}
		{description: End date-time for the meeting.}
	}
	{parameter:
		{name: owner}
		{description: Creator of the meeting.}
	}
	{parameter:
		{name: subject}
		{description: Text for the subject of the meeting.}
	}
	{parameter:
		{name: location}
		{description: Location information text for the meeting.}
	}
	{parameter:
		{name: body}
		{description: Body text for the meeting.}
	}
	{parameter:
		{name: vidyoMeetingType}
		{description: Value of VIDYO_MEETINGTYPE_Vidyo means the meeting contains Vidyo meeting specific information,
						i.e. a room URL or key, else if VIDYO_MEETINGTYPE_Standard then no Vidyo data found in the contents of the meeting.}
	}
	{parameter:	
		{name: roomResourceId}
		{description: Holds either a Vidyo room URL or room key data if it exists based on the value of the vidyoMeeting flag.}
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoMeeting* VidyoMeetingConstruct(VidyoMeeting* meeting,
	VidyoMeetingFeedback* feedback,
	LmiVector(VidyoMeetingAttendee) attendees,
	LmiString startDateTime,
	LmiString endDateTime,
	LmiString owner,
	LmiString subject,
	LmiString location,
	LmiString body,
	VidyoMeetingType vidyoMeetingType,
	LmiString roomResourceId,
	LmiAllocator* alloc);



/**
{function:
	{name: VidyoMeetingConstructCopy}
	{parent: VidyoMeeting}
	{description: Constructs an VidyoMeeting object as a copy of another.}
	{prototype: VidyoMeeting *VidyoMeetingConstructCopy(VidyoMeeting *obj, const VidyoMeeting *other)}
	{parameter: {name: obj} {description: The VidyoMeeting object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoMeetingDestruct}
	{parent: VidyoMeeting}
	{description: Destructs an VidyoMeeting object.}
	{prototype: void VidyoMeetingDestruct(VidyoMeeting *obj)}
	{parameter: {name: obj} {description: The VidyoRoom object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoMeetingAssign}
	{parent: VidyoMeeting}
	{description: Assigns one VidyoMeeting object the value of another. }
	{prototype: VidyoMeeting *VidyoMeetingAssign(VidyoMeeting *obj, const VidyoMeeting *other)}
	{parameter: {name: obj} {description: The VidyoMeeting object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoMeetingGetHandle}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const VidyoMeetingHandle*VidyoMeetingGetHandle(const VidyoMeeting* r)}
	{parameter:
		{name: r}
		{description: }
	}
	{return: }
}
*/
const VidyoMeetingHandle* VidyoMeetingGetHandle(const VidyoMeeting* r);


/*****
{function visibility="private":
	{name: VidyoMeetingConstructFromPluginMeeting}
	{parent: VidyoMeeting}
	{description:
		{p: Private constructor for Vidyo meeting }
		{p: Will be called through: }
		{p: - VidyoCalendarCreateMeeting }
		{p: - Inbound event from remote user fed through the callback }
	}
	{prototype:
		VidyoMeeting *VidyoMeetingConstructFromPluginMeeting(VidyoMeeting *m
														, const CalendarMeeting* meetingIn
														, LmiAllocator *alloc)
	}
	{parameter:
		{name: m}
		{description: Meeting instance being constructed}
	}
	{parameter:
		{name: jsonIn}
		{description: meeting data used to construct the Meeting class from }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
******/
VidyoMeeting *VidyoMeetingConstructFromPluginMeeting(VidyoMeeting *m, const CalendarMeeting* meetingIn, LmiAllocator *alloc);


/* =================================*/
/* =========== METHODS ============ */
/* =================================*/

/**
{function:
	{name: VidyoMeetingAddAttendee}
	{parent: VidyoMeeting}
	{description:
		{p: Adds an attendee to the meeting }
		{p: }
		{p: Triggers callback(s):  VidyoMeetingFeedbackAttendeeAdded  }
	}
	{prototype: LmiBool VidyoMeetingAddAttendee(VidyoMeeting* m, VidyoMeetingAttendee *a)}
	{parameter:
		{name: m}
		{description: Meeting to add the attendee to}
	}
	{parameter:
		{name: a}
		{description: Attendee to add }
	}
	{return: }
}
*/
LmiBool VidyoMeetingAddAttendee(VidyoMeeting* m, VidyoMeetingAttendee *a);


/**
{function:
	{name: VidyoMeetingRemoveAttendee}
	{parent: VidyoMeeting}
	{description:
		{p: Removes an attendee from the meeting }
		{p: }
		{p: Triggers callback(s):  VidyoMeetingFeedbackAttendeeRemoved  }
	}
	{prototype: LmiBool VidyoMeetingRemoveAttendee(VidyoMeeting* m, VidyoMeetingAttendee *a)}
	{parameter:
		{name: m}
		{description: Meeting to remove the attendee from }
	}
	{parameter:
		{name: a}
		{description: Attendee to remove }
	}
	{return: }
}
*/
LmiBool VidyoMeetingRemoveAttendee(VidyoMeeting* m, VidyoMeetingAttendee *a);


/**
{function:
	{name: VidyoMeetingRespondToInvite}
	{parent: VidyoMeeting}
	{description:
		{p: Respond to a meeting invite}
	}
	{prototype: LmiBool VidyoMeetingRespondToInvite(VidyoMeeting* m, VidyoMeetingAttendee *a, VidyoAttendeeParticipationStatus s )}
	{parameter:
		{name: m}
		{description: Meeting to send an invite response for}
	}
	{parameter:
		{name: a}
		{description: Attendee that the response is associated with }
	}
	{parameter:
		{name: s}
		{description: The participation status for the meeting - typically accepted-declined-tentative. }
	}
	{return: r}
}
*/
LmiBool VidyoMeetingRespondToInvite(VidyoMeeting* m, VidyoMeetingAttendee *a, VidyoAttendeeParticipationStatus s);


/**
{function:
	{name: VidyoMeetingGetAttendees}
	{parent: VidyoMeeting}
	{description:
		{p: Retrieve all attendees for the meeting}
	}
	{prototype: LmiBool VidyoMeetingGetAttendees(VidyoMeeting* m, LmiVector(VidyoMeetingAttendee) *a )}
	{parameter:
		{name: m}
		{description: Meeting to retrieve attendees from}
	}
	{parameter:
		{name: a}
		{description: List of attendees for the meeting as per the role argument }
	}
	{return: }
}
*/
LmiBool VidyoMeetingGetAttendees(VidyoMeeting* m, LmiVector(VidyoMeetingAttendee) *a );

/**
{function:
	{name: VidyoMeetingGetAttendeesByRole}
	{parent: VidyoMeeting}
	{description:
		{p: Retrieve all attendees for the meeting}
	}
	{prototype: LmiBool VidyoMeetingGetAttendeesByRole(VidyoMeeting* m, LmiVector(VidyoMeetingAttendee) *a, VidyoAttendeeParticipationRole r )}
	{parameter:
		{name: m}
		{description: Meeting to retrieve attendees from}
	}
	{parameter:
		{name: a}
		{description: List of attendees for the meeting as per the role argument }
	}
	{parameter:
		{name: r}
		{description: The participation role to filter the attendee list by. }
	}
	{return: }
}
*/
LmiBool VidyoMeetingGetAttendeesByRole(VidyoMeeting* m, LmiVector(VidyoMeetingAttendee) *a, VidyoAttendeeParticipationRole r);


/*****
{function visibility="private":
	{name: VidyoMeetingConstructDeserialize}
	{parent: VidyoMeeting}
	{description: Constructs an VidyoMeeting object from a serialized Json string.}
	{prototype: VidyoMeeting* VidyoMeetingConstructDeserialize(VidyoMeeting* vidyoMeetingVar, const VidyoLmiJson* jsonIn, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoMeetingVar}
		{description: The VidyoMeetingFeedback object to construct.}
	}
	{parameter:
		{name: jsonIn}
		{description: The json object to deserialize meeting data from.}
	}
	{parameter:
		{name: alloc}
		{description: Allocator.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
******/
VidyoMeeting* VidyoMeetingConstructDeserialize(VidyoMeeting* vidyoMeetingVar, const VidyoLmiJson* jsonIn, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoMeetingSetUserData}
	{parent: VidyoMeeting}
	{description: Sets a user data pointer that can be retreived later.}
	{prototype: void VidyoMeetingSetUserData(VidyoMeeting* m, LmiVoidPtr userData)}
	{parameter:
		{name: m}
		{description: Pointer to the VidyoMeeting object.}
	}
	{parameter:
		{name: userData}
		{description: Void pointer that holds opaque application data.}
	}
}
*/
void VidyoMeetingSetUserData(VidyoMeeting* m, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoMeetingGetUserData}
	{parent: VidyoMeeting}
	{description: Retreives the user data pointer that was previousely set by Meetinging VidyoMeetingSetUserData.}
	{prototype: LmiVoidPtr VidyoMeetingGetUserData(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: Pointer to the VidyoMeeting object.}
	}
	{return: Void pointer that holds opaque application data.}
}
*/
LmiVoidPtr VidyoMeetingGetUserData(const VidyoMeeting* m);


/**
{function:
	{name: VidyoMeetingGetType}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const VidyoMeetingType  * VidyoMeetingGetType(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const VidyoMeetingType  * VidyoMeetingGetType(const VidyoMeeting* m);


/**
{function:
	{name: VidyoMeetingGetSubject}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetSubject(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetSubject(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetEndDateTime}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetEndDateTime(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetEndDateTime(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetStartDateTime}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetStartDateTime(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetStartDateTime(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetId}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetId(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetId(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetOwnerName}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetOwnerName(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetOwnerName(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetOwnerEmail}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetOwnerEmail(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetOwnerEmail(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetLocation}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetLocation(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetLocation(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetVidyoMeetingRoomId}
	{parent: VidyoMeeting}
	{description: }
	{prototype: const LmiString * VidyoMeetingGetVidyoMeetingRoomId(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetVidyoMeetingRoomId(const VidyoMeeting* m);


/**
{function :
	{name: VidyoMeetingGetBody}
	{parent: VidyoMeeting}
	{description: Retrieve up to 2K bytes of body data from a Vidyo meeting }
	{prototype: const LmiString * VidyoMeetingGetBody(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingGetBody(const VidyoMeeting* m);



/**
{function :
	{name: VidyoMeetingRetrieveBody}
	{parent: VidyoMeeting}
	{description: To retrieve entire body from a Vidyo meeting }
	{prototype: const LmiString * VidyoMeetingRetrieveBody(const VidyoMeeting* m)}
	{parameter:
		{name: m}
		{description: }
	}
	{return: }
}
*/
const LmiString * VidyoMeetingRetrieveBody(const VidyoMeeting* m);


/* ===================================*/
/* =========== CALLBACKS ============ */
/* ===================================*/


/**
{callback:
	{name: VidyoMeetingFeedbackMeetingAttendeeAdded}
	{parent: VidyoMeetingFeedback}
	{description:
		{p: Indicates that an attendee was added to the meeting.   }
		{p: }
		{p: Triggered by:  VidyoMeetingAddAttendee or from addition by a remote user}
	}
	{prototype: void (*VidyoMeetingFeedbackMeetingAttendeeAdded)(VidyoMeetingFeedback* f, VidyoMeeting* meeting, VidyoMeetingAttendee* attendee)}
	{parameter:
		{name: f}
		{description: }
	}
	{parameter:
		{name: meeting}
		{description: }
	}
	{parameter:
		{name: attendee}
		{description: }
	}
}
*/
typedef void(*VidyoMeetingFeedbackMeetingAttendeeAdded)(VidyoMeetingFeedback* f, VidyoMeeting* meeting, VidyoMeetingAttendee* attendee);
 
/**
{callback:
	{name: VidyoMeetingFeedbackMeetingAttendeeRemoved}
	{parent: VidyoMeetingFeedback}
	{description: 
		{p: Indicates that an attendee was removed from the meeting.   }
		{p: }
		{p: Triggered by:  VidyoMeetingRemoveAttendee or from addition by a remote user}	
	}
	{prototype: void (*VidyoMeetingFeedbackMeetingAttendeeRemoved)(VidyoMeetingFeedback* f, VidyoMeeting* meeting, VidyoMeetingAttendee* attendee)}
	{parameter:
		{name: f}
		{description: }
	}
	{parameter:
		{name: meeting}
		{description: }
	}
	{parameter:
		{name: attendee}
		{description: }
	}
}
*/
typedef void(*VidyoMeetingFeedbackMeetingAttendeeRemoved)(VidyoMeetingFeedback* f, VidyoMeeting* meeting, VidyoMeetingAttendee* attendee);

/**
{function:
	{name: VidyoMeetingFeedbackConstruct}
	{parent: VidyoMeetingFeedback}
	{description: }
	{prototype: VidyoMeetingFeedback* VidyoMeetingFeedbackConstruct(VidyoMeetingFeedback* f,
																	VidyoMeetingFeedbackMeetingAttendeeAdded attendeeAdded, 
																	VidyoMeetingFeedbackMeetingAttendeeRemoved attendeeRemoved,
																	LmiAllocator* alloc)}
	{parameter:
		{name: f}
		{description: }
	}
	{parameter:
		{name: attendeeAdded}
		{description: }
	}
	{parameter:
		{name: attendeeRemoved}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoMeetingFeedback* VidyoMeetingFeedbackConstruct(  VidyoMeetingFeedback* f, 
												VidyoMeetingFeedbackMeetingAttendeeAdded attendeeAdded,
												VidyoMeetingFeedbackMeetingAttendeeRemoved attendeeRemoved,
												LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoMeetingFeedbackConstructCopy}
	{parent: VidyoMeetingFeedback}
	{description: Constructs an VidyoMeetingFeedback object as a copy of another.}
	{prototype: VidyoMeetingFeedback *VidyoMeetingFeedbackConstructCopy(VidyoMeetingFeedback *obj, const VidyoMeetingFeedback *other)}
	{parameter: 
		{name: obj} 
		{description: The VidyoMeetingFeedback object to construct.}
	}
	{parameter: 
		{name: other} 
		{description: The Meeting feedback object to make a copy of.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoMeetingFeedbackDestruct}
	{parent: VidyoMeetingFeedback}
	{description: Destructs an VidyoMeetingFeedback object.}
	{prototype: void VidyoMeetingFeedbackDestruct(VidyoMeetingFeedback *obj)}
	{parameter:	
		{name: obj} 
		{description: The VidyoMeetingFeedback object to destruct.}
	}
}
*/

/**
{function visibility="private":
	{name: VidyoMeetingFeedbackAssign}
	{parent: VidyoMeetingFeedback}
	{description: Assigns one VidyoMeetingFeedback object the value of another. }
	{prototype: VidyoMeetingFeedback *VidyoMeetingFeedbackAssign(VidyoMeetingFeedback *obj, const VidyoMeetingFeedback *other)}
	{parameter: 
		{name: obj} 
		{description: The VidyoMeetingFeedback object.}
	}
	{parameter: 
		{name: other} 
		{description: The Meeting feedback object to make a copy of.}
	}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/


/**
{function visibility="private":
	{name: VidyoMeetingFeedbackSetUserData}
	{parent: VidyoMeetingFeedback}
	{description: Sets a user data pointer that can be retreived later.}
	{prototype: void VidyoMeetingFeedbackSetUserData(VidyoMeetingFeedback* c, LmiVoidPtr userData)}
	{parameter:
	{name: c}
	{description: Pointer to the VidyoMeetingFeedback object.}
	}
	{parameter:
	{name: userData}
	{description: Void pointer that holds opaque application data.}
	}
}
*/
void VidyoMeetingFeedbackSetUserData(VidyoMeetingFeedback* c, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoMeetingFeedbackGetUserData}
	{parent: VidyoMeetingFeedback}
	{description: Retreives the user data pointer that was previousely set by meeting VidyoMeetingFeedbackSetUserData.}
	{prototype: LmiVoidPtr VidyoMeetingFeedbackGetUserData(const VidyoMeetingFeedback* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoMeetingFeedback object.}
	}
	{return: Void pointer that holds opaque application data.}
}
*/
LmiVoidPtr VidyoMeetingFeedbackGetUserData(const VidyoMeetingFeedback* c);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoMeetingInline.h"
#endif

#endif /* VIDYO_MEETING_H_ */
