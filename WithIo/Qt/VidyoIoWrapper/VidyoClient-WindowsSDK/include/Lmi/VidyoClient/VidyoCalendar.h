/**
{file:
	{name: VidyoCalendar.h}
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

#ifndef VIDYO_CALENDAR_SERVICE_H_ 
#define VIDYO_CALENDAR_SERVICE_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiMap.h>
#include <Lmi/Utils/LmiUnordered.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiUri.h>
#include <Lmi/Os/LmiSharedPtr.h>
#include <Lmi/Os/LmiLog.h>
#include "VidyoMeeting.h"
#include "VidyoFormField.h"
#include "VidyoCalendarLibraryDefs.h"

LMI_BEGIN_EXTERN_C
struct VidyoCalendarFeedbackImpl_;
typedef struct VidyoCalendarFeedbackImpl_ VidyoCalendarFeedbackImpl;
Declare_LmiSharedPtr(VidyoCalendarFeedbackImpl)
Declare_LmiSharedPtrWrapper(VidyoCalendarFeedback, VidyoCalendarFeedbackImpl)
Declare_LmiWeakPtrWrapper(VidyoCalendarFeedbackHandle, VidyoCalendarFeedback, VidyoCalendarFeedbackImpl)
Declare_LmiList(VidyoCalendarFeedbackHandle)

struct VidyoCalendarImpl_;
typedef struct VidyoCalendarImpl_ VidyoCalendarImpl;
Declare_LmiSharedPtr(VidyoCalendarImpl)
Declare_LmiSharedPtrWrapper(VidyoCalendar, VidyoCalendarImpl)
Declare_LmiWeakPtrWrapper(VidyoCalendarHandle, VidyoCalendar, VidyoCalendarImpl)
Declare_LmiList(VidyoCalendar)

/* =================================*/
/* ========== PACKAGES ============ */
/* =================================*/


/**
{package:
	{name: CalendarSchedule}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoCalendar.h}
	{description: Contains a schedule of meetings that the client wishes to operate against. Note that there is a separate, 
	              but different calendar package defined in under the Lmi related objects called Calendar.	
	}
}
*/

/* =================================*/
/* ======== OBJECT TYPES ========== */
/* =================================*/


/**
{type visibility="public":
	{name: VidyoCalendarManagerDefaultServices}
	{parent: CalendarSchedule}
	{description: Calendar service ID's.}
	{value:
		{name: VIDYO_CALENDARMANAGERDEFAULTSERVICES_External}
		{description: ID used to indicate an externally supplied calendar implementation.}
	}
	{value:
		{name: VIDYO_CALENDARMANAGERDEFAULTSERVICES_Default}
		{description: Vidyo based service (Future).}
	}
	{value:
		{name: VIDYO_CALENDARMANAGERDEFAULTSERVICES_Outlook2010}
		{description: Outlook 2010 client.}
	}
	{value:
		{name: VIDYO_CALENDARMANAGERDEFAULTSERVICES_Outlook2013}
		{description: Outlook 2013 client .}
	}
	{value:
		{name: VIDYO_CALENDARMANAGERDEFAULTSERVICES_Google}
		{description: Google calendar .}
	}
}
*/
typedef enum
{
	VIDYO_CALENDARMANAGERDEFAULTSERVICES_External,
	VIDYO_CALENDARMANAGERDEFAULTSERVICES_Default,
	VIDYO_CALENDARMANAGERDEFAULTSERVICES_Outlook2010,
	VIDYO_CALENDARMANAGERDEFAULTSERVICES_Outlook2013,
	VIDYO_CALENDARMANAGERDEFAULTSERVICES_Google
} VidyoCalendarManagerDefaultServices;


VidyoCalendarManagerDefaultServices* VidyoCalendarManagerDefaultServicesConstructCopy(VidyoCalendarManagerDefaultServices* x, const VidyoCalendarManagerDefaultServices* y);
void VidyoCalendarManagerDefaultServicesDestruct(VidyoCalendarManagerDefaultServices* x);
VidyoCalendarManagerDefaultServices* VidyoCalendarManagerDefaultServicesAssign(VidyoCalendarManagerDefaultServices* x, const VidyoCalendarManagerDefaultServices* y);

Declare_LmiVector(VidyoCalendarManagerDefaultServices)



/**
{type visibility="public":
	{name: VidyoCalendarState}
	{parent: CalendarSchedule}
	{description: Types of services available to reference for calendar specific data and events.}
	{value:
		{name: VIDYO_CALENDARSTATE_Unavailable}
		{description: Indicates that the service is not available in the environmemt due to either an unreachable server, or by lack of an installed product.}
	}
	{value:
		{name: VIDYO_CALENDARSTATE_Initialized}
		{description: Verified that the service is available to attempt a connection against.}
	}
	{value:
		{name: VIDYO_CALENDARSTATE_Connecting}
		{description: }
	}
	{value:
		{name: VIDYO_CALENDARSTATE_Connected}
		{description: }
	}
	{value:
		{name: VIDYO_CALENDARSTATE_Disconnecting}
		{description: }
	}
	{value:
		{name: VIDYO_CALENDARSTATE_Disconnected}
		{description: }
	}
}
*/
typedef enum
{
	VIDYO_CALENDARSTATE_Unavailable,	// Possible next state(s): <none>
	VIDYO_CALENDARSTATE_Initialized,	// Possible next state(s): VIDYO_CALENDARSTATE_Connecting
	VIDYO_CALENDARSTATE_Connecting,	// Possible next state(s): VIDYO_CALENDARSTATE_Connected, VIDYO_CALENDARSTATE_Disconnected
	VIDYO_CALENDARSTATE_Connected,		// Possible next state(s): VIDYO_CALENDARSTATE_Disconnected, VIDYO_CALENDARSTATE_Disconnecting
	VIDYO_CALENDARSTATE_Disconnecting,	// Possible next state(s): VIDYO_CALENDARSTATE_Disconnected
	VIDYO_CALENDARSTATE_Disconnected,	// Possible next state(s): VIDYO_CALENDARSTATE_Connecting
} VidyoCalendarState;



/**
{type visibility="public":
{name: VidyoCalendarServiceCode}
{parent: CalendarSchedule}
{description: This type indicates the result of an attempt to log in to some service.}
	{value: 
		{name: VIDYO_CALENDARSERVICECODE_Ok}
		{description: The user logged in successfully.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICECODE_NoService}
		{description: }
	}
	{value: 
		{name: VIDYO_CALENDARSERVICECODE_ConnectionFailed}
		{description: The destination could not be reached.}
	}
	{value: 
		{name: VIDYO_CALENDARSERVICECODE_ConnectionLost}
		{description: The transport connection was lost prior to completing the login procedure.}
	}
	{value: 
		{name: VIDYO_CALENDARSERVICECODE_ConnectionTimeout}
		{description: The signaling connection timed out prior to completing the login procedure.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICECODE_InvalidCredentials}
		{description: The credentials (combination of both userID and password) are not known to the service.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICECODE_InvalidCalendarId}
		{description: Could not find the calendar instance for the given name.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICECODE_GeneralError}
		{description: The login failed for some other miscellaneous error.}
	}
}
*/
typedef enum
{
	VIDYO_CALENDARSERVICECODE_Ok,
	VIDYO_CALENDARSERVICECODE_NoService,
	VIDYO_CALENDARSERVICECODE_ConnectionFailed,
	VIDYO_CALENDARSERVICECODE_ConnectionLost,
	VIDYO_CALENDARSERVICECODE_ConnectionTimeout,
	VIDYO_CALENDARSERVICECODE_InvalidCredentials,
	VIDYO_CALENDARSERVICECODE_InvalidCalendarId,
	VIDYO_CALENDARSERVICECODE_GeneralError,
} VidyoCalendarServiceCode;


/**
{type visibility="public":
	{name: VidyoMeetingSearchResult}
	{parent: CalendarSchedule}
	{description: This type indicates the result of a search for a meeting(s).}
	{value: 
		{name: VIDYO_MEETINGSEARCHRESULT_OK} 
		{description: The search operation was successful.}
	}
	{value: 
		{name: VIDYO_MEETINGSEARCHRESULT_NoRecords} 
		{description: No records found for the search.}
	}
	{value: 
		{name: VIDYO_MEETINGSEARCHRESULT_NoResponse} 
		{description: The search result failed due to request timeout.}
	}
	{value: 
		{name: VIDYO_MEETINGSEARCHRESULT_MiscLocalError}
		{description: The search result failed due to some miscellaneous local problem.}
	}
	{value: 
		{name: VIDYO_MEETINGSEARCHRESULT_MiscRemoteError} 
		{description: The search result failed due to some miscellaneous remote problem.}
	}
}
*/
typedef enum
{
	VIDYO_MEETINGSEARCHRESULT_OK,
	VIDYO_MEETINGSEARCHRESULT_NoRecords,
	VIDYO_MEETINGSEARCHRESULT_NoResponse,
	VIDYO_MEETINGSEARCHRESULT_MiscLocalError,
	VIDYO_MEETINGSEARCHRESULT_MiscRemoteError
} VidyoMeetingSearchResult;



/**
{type reference-counted="yes":
	{name: VidyoCalendar}
	{parent: CalendarSchedule}	
	{description: 
		{p: Represents an instance of a calendar service. }
		{p: }
		{p: General concepts: }
		{p: 	- Each instance is identifiable through the combination of the service type and the id }
		{p: }
		{p: Lifecycle of an calendar service instance: }
		{p: 	- Create/construct an instance of the service through the VidyoCalendarManager based on a VidyoCalendarManagerDefaultServices }
		{p: 		- Constructor will take a vector of connection parameters, the content of which will also be dictated by the VidyoCalendarManagerDefaultServices }
		{p: 	- Recieve the constructed instance back through the VidyoCalendarManager callback method VidyoCalendarManagerFeedbackCreateServiceResult. }
		{p: 	- Connect the service to it's resource using the VidyoCalendarConnect method }
		{p: 	- Receive the connect result through the calendar service callback for that service through VidyoCalendarFeedbackConnectResult }
		{p: 	- Upon successful connection result, the user will be able to create, update, read and delete meetings from the service }
		{p: 		as well as receive reminder events }
	}
	{member:
		{name: serviceType} 
		{type: LmiString}
		{description: Types of calendar services supported through this interface.}
	}	
	{member:
		{name: serviceState}
		{type: VidyoCalendarState}
		{description: Enumeration for the states that a calendar service can transition through.}
	}
	{member:
		{name: id}
		{type: LmiString}
		{description: Uniquely identifies the calendar service instance.}
	}
	{example:
		TODO -

		VidyoCalendar myVidyoCalendar;
		VidyoCalendarFeedback myVidyoCalendarFeedback;
		LmiAllocator* alloc;

	}
}
*/


/**
{type visibility="private":
	{name: VidyoCalendarHandle}
	{parent: VidyoCalendar}
	{description: Weak reference to the VidyoCalendar object.}
}
*/

/**
{type reference-counted="yes":
	{name: VidyoCalendarFeedback}
	{parent: CalendarSchedule}	
	{description: Interface for registering callbacks that notify an application about events on the VidyoCalendar object. Multiple feedbacks can be registerd on the same VidyoCalendar. }
}
*/

/**
{type visibility="private":
	{name: VidyoCalendarFeedbackHandle}
	{parent: VidyoCalendarFeedback}
	{description: Weak reference to the VidyoCalendarFeedback object.}
}
*/



/**** -----------------------****/
/**** ---- CONSTRUCTORS -----****/
/**** -----------------------****/

/******
{function visibility="private":
	{name: VidyoCalendarConstruct}
	{parent: VidyoCalendar}
	{description:
		Constructor for Vidyo Calendar.  Will be identifiable through the service type and id.
	}
	{prototype:
			VidyoCalendar* VidyoCalendarConstruct(VidyoCalendar* service,
													VidyoCalendarManagerDefaultServices svcType,
													VidyoCalendarManager calMgr,
													LmiString id,
													VidyoCalendarFeedback* feedback,
													LmiAllocator* alloc)
	}
	{parameter:
		{name: service}
		{description: }
	}
	{parameter:
		{name: svcType}
		{description: Corresponds to either a built in service (retrieved using VidyoCalendarManagerGetCalendarSvcString), or a string specified by a custom plugin implementation }
	}
	{parameter:
		{name: id}
		{description: Uniquely identifies the calendar service instance.  Construction with a previously used id that has not been destructed, will result in a failure. }
	}
	{parameter:
		{name: feedback}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
***/
//VidyoCalendar* VidyoCalendarConstruct(VidyoCalendar* service, VidyoCalendarManagerDefaultServices type, VidyoCalendarManager calMgr, LmiString id, VidyoCalendarFeedback* feedback, LmiAllocator* alloc);

/* =================================*/
/* =========== METHODS ============ */
/* =================================*/

/**
{function:
	{name: VidyoCalendarConstructCopy}
	{parent: VidyoCalendar}
	{description: Constructs an VidyoCalendar object as a copy of another.}
	{prototype: VidyoCalendar *VidyoCalendarConstructCopy(VidyoCalendar *obj, const VidyoCalendar *other)}
	{parameter: {name: obj} {description: The VidyoCalendar object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoCalendarDestruct}
	{parent: VidyoCalendar}
	{description: Destructs an VidyoCalendar object.}
	{prototype: void VidyoCalendarDestruct(VidyoCalendar *obj)}
	{parameter: 
		{name: obj} 
		{description: The VidyoCalendar object to destruct.}
	}
}
*/

/**
{function visibility="private":
	{name: VidyoCalendarAssign}
	{parent: VidyoCalendar}
	{description: Assigns one VidyoCalendar object the value of another. }
	{prototype: VidyoCalendar *VidyoCalendarAssign(VidyoCalendar *obj, const VidyoCalendar *other)}
	{parameter: {name: obj} {description: The VidyoCalendar object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoCalendarGetHandle}
	{parent: VidyoCalendar}
	{description: }
	{prototype: const VidyoCalendarHandle* VidyoCalendarGetHandle(const VidyoCalendar* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
const VidyoCalendarHandle* VidyoCalendarGetHandle(const VidyoCalendar* c);


/**
{function visibility="private":
	{name: VidyoCalendarSetUserData}
	{parent: VidyoCalendar}
	{description: Sets a user data pointer that can be retreived later.}
	{prototype: void VidyoCalendarSetUserData(VidyoCalendar* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar object.}
	}
	{parameter:
		{name: userData}
		{description: Void pointer that holds opaque application data.}
	}
}
*/
void VidyoCalendarSetUserData(VidyoCalendar* c, LmiVoidPtr userData);



/**
{function visibility="private":
	{name: VidyoCalendarGetUserData}
	{parent: VidyoCalendar}
	{description: Retreives the user data pointer that was previousely set by Calendaring VidyoCalendarSetUserData.}
	{prototype: LmiVoidPtr VidyoCalendarGetUserData(const VidyoCalendar* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar object.}
	}
	{return: Void pointer that holds opaque application data.}
}
*/
LmiVoidPtr VidyoCalendarGetUserData(const VidyoCalendar* c);


/**
{function :
	{name: VidyoCalendarGetId}
	{parent: VidyoCalendar}
	{description: Retreives the unique string Id that identifies the instance of the calendar.}
	{prototype: const LmiString* VidyoCalendarGetId(const VidyoCalendar* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar object.}
	}
	{return: LmiString that holds the Id for the calendar.}
}
*/
const LmiString* VidyoCalendarGetId(const VidyoCalendar* c);

/**
{function:
	{name: VidyoCalendarGetServiceState}
	{parent: VidyoCalendar}
	{description: Retreives the user data pointer that was previousely set by Calendaring VidyoCalendarSetUserData.}
	{prototype: const VidyoCalendarState * VidyoCalendarGetServiceState(const VidyoCalendar* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar object.}
	}
	{return: LmiString that holds the state of the calendar.}
}
*/
const VidyoCalendarState * VidyoCalendarGetServiceState(const VidyoCalendar* c);


/**
{function:
	{name: VidyoCalendarGetServiceType}
	{parent: VidyoCalendar}
	{description: Retreives the service type for the calendar.}
	{prototype: const LmiString * VidyoCalendarGetServiceType(const VidyoCalendar* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar object.}
	}
	{return: Value for the service type .}
}
*/
const LmiString * VidyoCalendarGetServiceType(const VidyoCalendar* c);


/**
{function :
	{name: VidyoCalendarSetRoomIdMatchString}
	{parent: VidyoCalendar}
	{description: Sets the regular expression string that will be used to identify Vidyo room URLs or key information, during a meeting search or retrieval.}
	{prototype: LmiBool VidyoCalendarSetRoomIdMatchString(const VidyoCalendar* c, LmiString * regexp)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar object.}
	}
	{parameter:
		{name: regexp}
		{description: A string that contains a regular expression which will be used in searches, to identify whether a meeting contains a
					  reference to a Vidyo room URL or key.  If the search finds the string, then it will accessible through the 
					  meeting attributes }
	}
	{return: True for a successful set, false if there was an issue setting the value.}
}
*/
LmiBool VidyoCalendarSetRoomIdMatchString(const VidyoCalendar* c, LmiString * regexp);


/**
{function:
	{name: VidyoCalendarFeedbackConstructCopy}
	{parent: VidyoCalendarFeedback}
	{description: 
		Constructs a VidyoCalendarFeedback object as a copy of another.
	}	
	{prototype: 
		VidyoCalendarFeedback *VidyoCalendarFeedbackConstructCopy(VidyoCalendarFeedback *obj, const VidyoCalendarFeedback *other)
	}
	{parameter:
		{name: obj}
		{description: The VidyoCalendarFeedback object to construct.}
	}
	{parameter:
		{name: other}
		{description: The feedback object to make a copy of.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoCalendarFeedbackDestruct}
	{parent: VidyoCalendarFeedback}
	{description: Destructs an VidyoCalendarFeedback object.}
	{prototype: void VidyoCalendarFeedbackDestruct(VidyoCalendarFeedback *obj)}
	{parameter:
		{name: obj}
		{description: The VidyoCalendarFeedback object to destruct.}
	}
}
*/

/**
{function visibility="private":
	{name: VidyoCalendarFeedbackAssign}
	{parent: VidyoCalendarFeedback}
	{description: Assigns one VidyoCalendarFeedback object the value of another. }
	{prototype: VidyoCalendarFeedback *VidyoCalendarFeedbackAssign(VidyoCalendarFeedback *obj, const VidyoCalendarFeedback *other)}
	{parameter:
		{name: obj}
		{description: The VidyoCalendarFeedback object.}
	}
	{parameter:
		{name: other}
		{description: The callers VidyoCalendarFeedback object to make a copy of.}
	}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/


/**
{function:
	{name: VidyoCalendarGetConnectFields}
	{parent: VidyoCalendar}
	{description:
		Retrieves the connection fields needed to connect to a service, based on the service type.
	}
	{prototype:
		LmiVector(VidyoFormField) VidyoCalendarGetConnectFields(VidyoCalendarManagerDefaultServices serviceType )
	}
	{parameter:
		{name: serviceType}
		{description: Type of service to retrieve the connection param types for}
	}
	{return: }
}
*/
LmiVector(VidyoFormField) VidyoCalendarGetConnectFields(VidyoCalendarManagerDefaultServices serviceType);



/**
{function:
	{name: VidyoCalendarConnect}
	{parent: VidyoCalendar}
	{description: 
		{p: Initiates a connection of the calendar service to its resource for data.  This can include both a local resource or a server based one. }
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackConnectResult  }
	}
	{prototype: LmiBool VidyoCalendarConnect(VidyoCalendar* c,																						
											LmiVector(VidyoFormField)* connProperties)
	}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: connProperties}
		{description: Property values  }
	}
	{return: }
}
*/
LmiBool VidyoCalendarConnect(VidyoCalendar* c, LmiVector(VidyoFormField)*  connProperties);



/**
{function:
	{name: VidyoCalendarCreateMeeting}
	{parent: VidyoCalendar}
	{description: 
		{p: Creates a calendar meeting }
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackMeetingCreated  }
	}
	{prototype: LmiBool VidyoCalendarCreateMeeting( VidyoCalendar* c, 
													VidyoCalendarFeedback *feedback,
													VidyoMeeting *meeting, 
													LmiString *createToken)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: feedback}
		{description: }
	}
	{parameter:
		{name: meeting}
		{description: }
	}
	{parameter:
		{name: createToken}
		{description: A unique string token to match this method call with the resulting asynchronous callback}
	}
	{return: r}
}
*/
LmiBool VidyoCalendarCreateMeeting(VidyoCalendar* c, VidyoCalendarFeedback *feedback, VidyoMeeting *meeting, LmiString *createToken);


/**
{function:
	{name: VidyoCalendarUpdateMeeting}
	{parent: VidyoCalendar}
	{description: 
		{p: Updates a calendar meeting }
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackMeetingUpdated  }
	}
	{prototype: LmiBool VidyoCalendarUpdateMeeting(VidyoCalendar* c, VidyoCalendarFeedback *feedback, VidyoMeeting *meeting, LmiString *createToken)}
	{parameter:
		{name: c}
		{description: Calendar service to update the meeting against}
	}
	{parameter:
		{name: feedback}
		{description: Instance belonging to this calendar service}
	}
	{parameter:
		{name: meeting}
		{description: Meeting object to update}
	}
	{parameter:
		{name: createToken}
		{description: A unique string token to match this method call with the resulting asynchronous callback}
	}
	{return: r}
}
*/
LmiBool VidyoCalendarUpdateMeeting(VidyoCalendar* c, VidyoCalendarFeedback *feedback, VidyoMeeting *meeting, LmiString *createToken);


/**
{function:
	{name: VidyoCalendarRemoveMeeting}
	{parent: VidyoCalendar}
	{description: 
		{p: Removes a meeting from the calendar}
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackMeetingRemoved  }
	}
	{prototype: LmiBool VidyoCalendarRemoveMeeting(VidyoCalendar* c, VidyoCalendarFeedback *feedback, VidyoMeeting *meeting, LmiString *createToken)}
	{parameter:
		{name: c}
		{description: Calendar service to update the meeting against}
	}
	{parameter:
		{name: feedback}
		{description: Instance belonging to this calendar service}
	}
	{parameter:
		{name: meeting}
		{description: Meeting object to update}
	}
	{parameter:
		{name: createToken}
		{description: A unique string token to match this method call with the resulting asynchronous callback}
	}
	{return: r}
}
*/
LmiBool VidyoCalendarRemoveMeeting(VidyoCalendar* c, VidyoCalendarFeedback *feedback, VidyoMeeting *meeting, LmiString *createToken);


/**
{function:
{name: VidyoCalendarSearchMeetings}
	{parent: VidyoCalendar}
	{description: 
		{p: Search a calendar for meetings based on a search string and a begin - end date.}
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackGetMeetingsResult  }
		{p: }
		{p: NOTE - TODO:  Should we also limit search range for dates?  }
	}
	{prototype: LmiBool VidyoCalendarSearchMeetings(VidyoCalendar* c, LmiString * searchText, LmiString * beginDate, LmiString * endDate, LmiUint index, LmiUint pageSize)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: searchText}
		{description: }
	}
	{parameter:
		{name: beginDate}
		{description: }
	}
	{parameter:
		{name: endDate}
		{description: }
	}
	{parameter:
		{name: index}
		{description: }
	}
	{parameter:
		{name: pageSize}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoCalendarSearchMeetings(VidyoCalendar* c, LmiString * searchText, LmiString * beginDate, LmiString * endDate, LmiUint index, LmiUint pageSize);



/**
{function:
	{name: VidyoCalendarGetMeetingsByMonth}
	{parent: VidyoCalendar}
	{description: 			
		{p: Get a list of meetings by month. }
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackGetMeetingsResult  }
	}
	{prototype: LmiBool VidyoCalendarGetMeetingsByMonth(VidyoCalendar* c, LmiUint year, LmiUint month, LmiString *createToken)}
	{parameter:
		{name: c}
		{description: Vidyo calendar service object.}
	}
	{parameter:
		{name: year}
		{description: 4 digit year to search for the meetings within - (yyyy).}
	}
	{parameter:
		{name: month}
		{description: 1-2 digit month to search for the meetings within - (<m>m - no zero padding required).}
	}
	{parameter:
		{name: createToken}
		{description: A unique string token to match this method call with the resulting asynchronous callback}
	}
	{return: }
}
*/
LmiBool VidyoCalendarGetMeetingsByMonth(VidyoCalendar *c, LmiUint y, LmiUint m, LmiString *createToken);

/**
{function:
	{name: VidyoCalendarGetMeetingsByWeek}
	{parent: VidyoCalendar}
	{description: 			
		{p: Get a list of meetings by week. }
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackGetMeetingsResult  }
	}
	{prototype: LmiBool VidyoCalendarGetMeetingsByWeek(VidyoCalendar* c, LmiUint year, LmiUint month, LmiUint day, LmiString *createToken)}
	{parameter:
		{name: c}
		{description: Vidyo calendar service object.}
	}
	{parameter:
		{name: year}
		{description: 4 digit year to search for the meetings within - (yyyy).}
	}
	{parameter:
		{name: month}
		{description: 1-2 digit month to search for the meetings within - (mm - no zero padding required).}
	}
	{parameter:
		{name: day}
		{description: 1-2 digit day that falls within the week which we will search for the meetings within - (dd - no zero padding required).
					  Week used to retrieve meetings will begin on a Sunday and end on a Saturday, based on the weekday passed in from the parameters. 
		}
	}
	{parameter:
		{name: createToken}
		{description: A unique string token to match this method call with the resulting asynchronous callback}
	}
	{return: }
}
*/
LmiBool VidyoCalendarGetMeetingsByWeek(VidyoCalendar *c, LmiUint year, LmiUint month, LmiUint day, LmiString *createToken);

/**
{function:
	{name: VidyoCalendarGetMeetingsByDay}
	{parent: VidyoCalendar}
	{description: 
		{p: Get a list of meetings by day. }
		{p: }
		{p: Triggers callback(s):  VidyoCalendarFeedbackGetMeetingsResult  }	
	}
	{prototype: LmiBool VidyoCalendarGetMeetingsByDay(VidyoCalendar* c, LmiUint year, LmiUint month, LmiUint day, LmiString *createToken)}
	{parameter:
		{name: c}
		{description: Vidyo calendar service object.}
	}
	{parameter:
		{name: year}
		{description: 4 digit year to search for the meetings within - (yyyy).}
	}
	{parameter:
		{name: month}
		{description: 1-2 digit month to search for the meetings within - ((mm) - no zero padding required).}
	}
	{parameter:
		{name: day}
		{description: 1-2 digit day to search for meetings within - ((dd) - no zero padding required).}
		
	}
	{parameter:
		{name: createToken}
		{description: A unique string token to match this method call with the resulting asynchronous callback}
	}
	{return: }
}
*/
LmiBool VidyoCalendarGetMeetingsByDay(VidyoCalendar *c, LmiUint year, LmiUint month, LmiUint day, LmiString *createToken);


/**
{function visibility="private":
	{name: VidyoCalendarGetMeetings}
	{parent: VidyoCalendar}
	{description: }
	{prototype: LmiBool VidyoCalendarGetMeetings(VidyoCalendar *c, LmiVector(VidyoMeeting) *mtgs)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: mtgs}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoCalendarGetMeetings(VidyoCalendar *c, LmiVector(VidyoMeeting) *mtgs);


/* =================================*/
/* ========= CALLBACKS ============ */
/* =================================*/

/**
{callback:
	{name: VidyoCalendarFeedbackConnectResult}
	{parent: VidyoCalendarFeedback}
	{description: 		
		{p: Triggered when service is connected. }
		{p: }
		{p: Triggered through method(s):  VidyoCalendarConnect  }
	}
	{prototype: void (*VidyoCalendarFeedbackConnectResult)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoCalendarServiceCode result)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: result}
		{description: Indication on whether the connection attempt was successful or not. }
	}
}
*/
typedef void(*VidyoCalendarFeedbackConnectResult)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoCalendarServiceCode result);


/**
{callback:
	{name: VidyoCalendarFeedbackDisconnected}
	{parent: VidyoCalendarFeedback}
	{description: Callback that is triggered when service is disconnected. 
		{p: Triggered when service is connected. }
		{p: }
		{p: Triggered through event(s):  user will be notified through this method when the connection to the calendar service becomes unavailable.   }
	}
	{prototype: void (*VidyoCalendarFeedbackDisconnected)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoCalendarServiceCode result)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: result}
		{description: Reason for the disconnect. }
	}
}
*/
typedef void(*VidyoCalendarFeedbackDisconnected)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoCalendarServiceCode result);

/**
{callback:
	{name: VidyoCalendarFeedbackMeetingEventNotification}
	{parent: VidyoCalendarFeedback}
	{description: 
		{p: Triggered when a meeting event occurs. }
		{p: }
		{p: Triggered through event(s):  user will be notified through this method when the start time for a scheduled meeting occurs.   }
	}
	{prototype: void (*VidyoCalendarFeedbackMeetingEventNotification)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: m}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
}
*/
typedef void(*VidyoCalendarFeedbackMeetingEventNotification)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m);


/**
{callback:
	{name: VidyoCalendarFeedbackGetMeetingsResult}
	{parent: VidyoCalendarFeedback}
	{description: 
		{p: Triggered from a meeting search request. }
		{p: }
		{p: Triggered through method(s): }		
		{p:		- VidyoCalendarGetMeetingsByMonth }
		{p:		- VidyoCalendarGetMeetingsByWeek }
		{p:		- VidyoCalendarGetMeetingsByDay }
		{p:		- VidyoCalendarSearchMeetings }		
	}
	{prototype: void (*VidyoCalendarFeedbackGetMeetingsResult)(VidyoCalendarFeedback *f, 
																	  VidyoCalendar* c, 
																	  VidyoMeetingSearchResult searchResult, 
																	  const LmiVector(VidyoMeeting) *meetings)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that the callback was triggered against. }
	}
	{parameter:
		{name: searchResult}
		{description: Indicates the reason code for the results. }
	}
	{parameter:
		{name: meetings}
		{description: A vector of meeting objects based on the results of the triggering method. }
	}
}
*/
typedef void(*VidyoCalendarFeedbackGetMeetingsResult)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeetingSearchResult searchResult, const LmiVector(VidyoMeeting) *meetings);


/**
{callback:
	{name: VidyoCalendarFeedbackMeetingCreatedByService}
	{parent: VidyoCalendarFeedback}
	{description:
		{p: Triggered when a meeting is created through the receipt of an invite by a remote user. }
		{p: }
		{p: Triggered by an event for creating a meeting that originated from the calendar service }
	}
	{prototype: void (*VidyoCalendarFeedbackMeetingCreatedByService)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingAttendee * inviteOwner)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: m}
		{description: Pointer to the meeting that was created. }
	}
	{parameter:
		{name: inviteOwner}
		{description: Contact information on the user that created the invite. }
	}
}
*/
typedef void(*VidyoCalendarFeedbackMeetingCreatedByService)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingAttendee *inviteOwner);



/**
{callback:
	{name: VidyoCalendarFeedbackMeetingCreated}
	{parent: VidyoCalendarFeedback}
	{description:
		{p: Triggered when a meeting is created by the local user. }
		{p: }
		{p: Triggered through method(s): VidyoCalendarCreateMeeting }
	}
	{prototype: void (*VidyoCalendarFeedbackMeetingCreated)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingActionResult r, LmiString * createdToken)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: m}
		{description: Pointer to the meeting that was created. }
	}
	{parameter:
		{name: r}
		{description: Result to indicate whether creating the meeting was successful or not . }
	}
	{parameter:
		{name: createdToken}
		{description: A unique string provided by the triggering method.  Used to correlate the method that triggered this callback. }
	}

}
*/
typedef void(*VidyoCalendarFeedbackMeetingCreated)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingActionResult r, LmiString * createdToken);



/**
{callback:
	{name: VidyoCalendarFeedbackMeetingUpdatedByService}
	{parent: VidyoCalendarFeedback}
	{description:		
		{p: Triggered when a meeting is updated. }
		{p: }
		{p: Triggered from an event originating through the calendar service}
	}
	{prototype: void (*VidyoCalendarFeedbackMeetingUpdatedByService)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingActionResult r)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: m}
		{description: Pointer to the meeting that was created. }
	}
	{parameter:
		{name: r}
		{description: Result to indicate whether creating the meeting was successful or not . }
	}
}
*/
typedef void(*VidyoCalendarFeedbackMeetingUpdatedByService)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingActionResult r);


/**
{callback:
	{name: VidyoCalendarFeedbackMeetingUpdated}
	{parent: VidyoCalendarFeedback}
	{description:
		{p: Triggered when a meeting is updated. }
		{p: }
		{p: Triggered from the method VidyoCalendarUpdateMeeting}
	}
	{prototype: void (*VidyoCalendarFeedbackMeetingUpdated)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingActionResult r, LmiString * updatedToken)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: m}
		{description: Pointer to the meeting that was created. }
	}
	{parameter:
		{name: r}
		{description: Result to indicate whether creating the meeting was successful or not . }
	}
	{parameter:
		{name: updatedToken}
		{description: A unique string provided by the triggering method.  Used to correlate the method that triggered this callback. }
	}
}
*/
typedef void(*VidyoCalendarFeedbackMeetingUpdated)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting* m, VidyoMeetingActionResult r, LmiString * updatedToken);


/**
{callback:
	{name: VidyoCalendarFeedbackMeetingRemovedByService}
	{parent: VidyoCalendarFeedback}
	{description:		
		{p: Triggered when a meeting is removed from the calendar schedule. }
		{p: }
		{p: Triggered through method(s): VidyoCalendarRemoveMeeting or remotely from a meeting removal by the originator.  }
		{p: The value of the VidyoMeetingActionResult will indicate how the meeting was removed.  }
	}
	{prototype: void (*VidyoCalendarFeedbackMeetingRemovedByService)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting *m, VidyoMeetingActionResult r)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: m}
		{description: Pointer to the VidyoMeeting object removed for the callback. }
	}
	{parameter:
		{name: r}
		{description: Result to indicate whether the meeting was being removed by an action from the local user or the remote owner. }
	}

}
*/
typedef void(*VidyoCalendarFeedbackMeetingRemovedByService)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting *m, VidyoMeetingActionResult r);


/**
{callback:
	{name: VidyoCalendarFeedbackMeetingRemoved}
	{parent: VidyoCalendarFeedback}
	{description:
	{p: Triggered when a meeting is removed from the calendar schedule. }
	{p: }
	{p: Triggered through method(s): VidyoCalendarRemoveMeeting.  }
	{p: The value of the VidyoMeetingActionResult will indicate if any errors occured trying to remove the meeting.  }
	}
	{prototype: void (*VidyoCalendarFeedbackMeetingRemoved)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting *m, VidyoMeetingActionResult r, LmiString * removedToken)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object. }
	}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendar that triggered the callback. }
	}
	{parameter:
		{name: m}
		{description: Pointer to the VidyoMeeting object removed for the callback. }
	}
	{parameter:
		{name: r}
		{description: Result to indicate whether the meeting was being removed by an action from the local user or the remote owner. }
	}
	{parameter:
		{name: removedToken}
		{description: A unique string provided by the triggering method.  Used to correlate the method that triggered this callback. }
	}
}
*/
typedef void(*VidyoCalendarFeedbackMeetingRemoved)(VidyoCalendarFeedback *f, VidyoCalendar* c, VidyoMeeting *m, VidyoMeetingActionResult r, LmiString * removedToken);



/**
{function visibility="private":
	{name: VidyoCalendarFeedbackSetUserData}
	{parent: VidyoCalendarFeedback}
	{description: Sets a user data pointer that can be retreived later or in VidyoCalendarFeedback callbacks. }
	{prototype: void VidyoCalendarFeedbackSetUserData(VidyoCalendarFeedback* f, LmiVoidPtr userData)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object.}
	}
	{parameter:
		{name: userData}
		{description: Pointer that holds opaque application data. }
	}
}
*/
void VidyoCalendarFeedbackSetUserData(VidyoCalendarFeedback* f, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoCalendarFeedbackGetUserData}
	{parent: VidyoCalendarFeedback}
	{description: Retreives a user data pointer that was previousely set by calling VidyoCalendarFeedbackSetUserData. }
	{prototype: LmiVoidPtr VidyoCalendarFeedbackGetUserData(const VidyoCalendarFeedback* f)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarFeedback object.}
	}
	{return: Pointer that holds opaque application data.}
}
*/
LmiVoidPtr VidyoCalendarFeedbackGetUserData(const VidyoCalendarFeedback* f);



/**
{function:
	{name: VidyoCalendarFeedbackConstruct}
	{parent: VidyoCalendarFeedback}
	{description: Construct the calendar feedback instance. }
	{prototype: VidyoCalendarFeedback* VidyoCalendarFeedbackConstruct(VidyoCalendarFeedback* f,
																					VidyoCalendarFeedbackConnectResult connectState, 
																					VidyoCalendarFeedbackDisconnected disconnected, 
																					VidyoCalendarFeedbackMeetingEventNotification meetingEvent, 
																					VidyoCalendarFeedbackMeetingCreatedByService meetingCreatedByService,
																					VidyoCalendarFeedbackMeetingCreated meetingCreated,																					
																					VidyoCalendarFeedbackMeetingUpdatedByService meetingUpdatedByService,
																					VidyoCalendarFeedbackMeetingUpdated meetingUpdated,
																					VidyoCalendarFeedbackMeetingRemovedByService meetingRemovedByService,
																					VidyoCalendarFeedbackMeetingRemoved meetingRemoved,
																					VidyoCalendarFeedbackGetMeetingsResult getMeetingResults, 
																					LmiAllocator* alloc)
	}
	{parameter:
		{name: f}
		{description: Feedback structure to hold registered member functions}
	}
	{parameter:
		{name: connectState}
		{description: Indicates any state transitions against the connection for the calendar service}
	}
	{parameter:
		{name: disconnected}
		{description: Indicates tha the connection for the calendar service has been disconnected. }
	}
	{parameter:
		{name: meetingEvent}
		{description: Event triggered against the scheduled time for a meeting }
	}
	{parameter:
		{name: meetingCreatedByService}
		{description: Indicates the results for the creation of a meeting that was initiated by the calendar service}
	}
	{parameter:
		{name: meetingCreated}
		{description: Indicates the results for the creation of a meeting by the local user}
	}
	{parameter:
		{name: meetingUpdatedByService}
		{description: Indicates the results for the update of a meeting that was initiated by the calendar service }
	}
	{parameter:
		{name: meetingUpdated}
		{description: Indicates the results on the update of a meeting }
	}
	{parameter:
		{name: meetingRemovedByService}
		{description: Indicates the results for the removal of a meeting that was initiated by the calendar service }
	}
	{parameter:
		{name: meetingRemoved}
		{description: Indicates the results for the removal of a meeting }
	}
	{parameter:
		{name: getMeetingResults}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoCalendarFeedback* VidyoCalendarFeedbackConstruct(VidyoCalendarFeedback* f,
	VidyoCalendarFeedbackConnectResult connectState,
	VidyoCalendarFeedbackDisconnected disconnected,
	VidyoCalendarFeedbackMeetingEventNotification meetingEvent,
	VidyoCalendarFeedbackMeetingCreatedByService meetingCreatedByService,
	VidyoCalendarFeedbackMeetingCreated meetingCreated,	
	VidyoCalendarFeedbackMeetingUpdatedByService meetingUpdatedByService,
	VidyoCalendarFeedbackMeetingUpdated meetingUpdated,	
	VidyoCalendarFeedbackMeetingRemovedByService meetingRemovedByService,
	VidyoCalendarFeedbackMeetingRemoved meetingRemoved,
	VidyoCalendarFeedbackGetMeetingsResult getMeetingResults,
	LmiAllocator* alloc);



typedef LmiBool(*VidyoCalendarClientRegisterInterface)(CalendarPluginInterface * svcInterface);
LmiBool VidyoCalendarSetServiceInterface(VidyoCalendar *c, CalendarPluginInterface *svcInterface);



LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoCalendarInline.h"
#endif

#endif /* VIDYO_CALENDAR_SERVICE_H_ */
