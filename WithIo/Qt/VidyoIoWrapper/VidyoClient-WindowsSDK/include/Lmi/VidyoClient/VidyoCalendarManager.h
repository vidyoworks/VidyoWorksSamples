/**
{file:
{name: VidyoCalendarManager.h}
{description: Calendar Service Entity Library. }
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

#ifndef VIDYO_CALENDAR_SERVICE_MANAGER_H_ 
#define VIDYO_CALENDAR_SERVICE_MANAGER_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiMap.h>
#include <Lmi/Utils/LmiUnordered.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiUri.h>
#include <Lmi/Os/LmiSharedPtr.h>
#include "VidyoCalendar.h"

LMI_BEGIN_EXTERN_C

struct VidyoCalendarManagerFeedbackImpl_;
typedef struct VidyoCalendarManagerFeedbackImpl_ VidyoCalendarManagerFeedbackImpl;
Declare_LmiSharedPtr(VidyoCalendarManagerFeedbackImpl)
Declare_LmiSharedPtrWrapper(VidyoCalendarManagerFeedback, VidyoCalendarManagerFeedbackImpl)
Declare_LmiWeakPtrWrapper(VidyoCalendarManagerFeedbackHandle, VidyoCalendarManagerFeedback, VidyoCalendarManagerFeedbackImpl)
Declare_LmiList(VidyoCalendarManagerFeedbackHandle)

struct VidyoCalendarManagerImpl_;
typedef struct VidyoCalendarManagerImpl_ VidyoCalendarManagerImpl;
Declare_LmiSharedPtr(VidyoCalendarManagerImpl)
Declare_LmiSharedPtrWrapper(VidyoCalendarManager, VidyoCalendarManagerImpl)
Declare_LmiWeakPtrWrapper(VidyoCalendarManagerHandle, VidyoCalendarManager, VidyoCalendarManagerImpl)

/* =================================*/
/* ========== PACKAGES ============ */
/* =================================*/


/**
{package:
	{name: CalendarManager}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoCalendarManager.h}
	{description: The CalendarServices package encapsulates all APIs related to calendar specific actions and items (i.e. a meeting, attendees, etc).}
}
*/


/* =================================*/
/* ======== OBJECT TYPES ========== */
/* =================================*/

/**
{type visibility="public":
	{name: VidyoCalendarCreateResult}
	{parent: CalendarManager}
	{description: Indicates the result code for the creation of the calendar instance .}
	{value:
		{name: VIDYO_CALENDARCREATERESULT_Ok}
		{description: Service was created successfully.}
	}	
	{value:
		{name: VIDYO_CALENDARCREATERESULT_InvalidConnParams}
		{description: Set of connection parameters passed in were either missing or contained invalid values.}
	}
	{value:
		{name: VIDYO_CALENDARCREATERESULT_InvalidType}
		{description: Invalid or unsupported calendar type was indicated.  (Auto discovery will indicate whether the service is available on the platform)}
	}
}
*/
typedef enum
{
	VIDYO_CALENDARCREATERESULT_Ok,
	VIDYO_CALENDARCREATERESULT_InvalidConnParams,
	VIDYO_CALENDARCREATERESULT_InvalidType
} VidyoCalendarCreateResult;


/**
{type visibility="public":
	{name: VidyoCalendarServiceStatus}
	{parent: CalendarManager}
	{description: Indicates the result code for the creation of the calendar instance .}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_Init}
		{description: The initial state of the library for a service - ready to be located and loaded.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_Loaded}
		{description: Library was loaded and the API function required for registering the interface was found.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_LoadError}
		{description: Error occurred while trying to load the library.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_Available}
		{description: A connection attempt for the service was successful.  API calls are ready for use.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_DllNotFound}
		{description: Vidyo DLL or static library for specified calendar service could not be found in the installation directory.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_ApiProcError}
		{description: Unable to retrieve the API function from the Vidyo DLL or static library for specified calendar service.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_PluginSvcNotInstalled}
		{description: Calendar service was loaded, but the 3rd party service it was referencing was not started or was not installed.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_PluginSvcNotActive}
		{description: Calendar service was loaded, and the local 3rd party service is available but not connected to it's resources for event notifications.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_PluginSvcAuthRequired}
		{description: Calendar service was loaded, and the local 3rd party service is available but user is not logged in.}
	}
	{value:
		{name: VIDYO_CALENDARSERVICESTATUS_Unloaded}
		{description: Calendar service has been uninitialized with all internal resources freed.}
	}
}
*/
typedef enum
{	
	VIDYO_CALENDARSERVICESTATUS_Init,	
	VIDYO_CALENDARSERVICESTATUS_Loaded,
	VIDYO_CALENDARSERVICESTATUS_LoadError,
	VIDYO_CALENDARSERVICESTATUS_Available,
	VIDYO_CALENDARSERVICESTATUS_DllNotFound,	
	VIDYO_CALENDARSERVICESTATUS_ApiProcError,
	VIDYO_CALENDARSERVICESTATUS_PluginSvcNotInstalled,
	VIDYO_CALENDARSERVICESTATUS_PluginSvcNotActive,
	VIDYO_CALENDARSERVICESTATUS_PluginSvcAuthRequired,
	VIDYO_CALENDARSERVICESTATUS_Unloaded

} VidyoCalendarServiceStatus;


/**
{type reference-counted="yes":
	{name: VidyoCalendarManager}
	{parent: CalendarManager}	
	{description: 
		{p: This type will be used to retrieve and manage the creation of the various calendar service types. }	
		{p: }
		{p: General concepts: }
		{p: - Presents a set of API's that allow for the creation of a calendar service. }
		{p: - The types of calendar services offered will depend on the implementations that are built and packaged against these API's as plugins }
		{p: - The type of calendar service types defined may change as new implementations are added. }
		{p: - The service type will dicate how an application will construct the servce through this calendar service manager API }
		{p:		=> A set of connection properties will be passed into the create service methods based on the service type. }
		{p: - The service manager will pass back a constructed calendar service type, which can then be used to connect to the service with and manage meeting setups and receive events for that service. }
		{p: }	
	    {p: Note that the availability of a service may come and go based on local applications or network events. }
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
	{name: VidyoCalendarManagerHandle}
	{parent: VidyoCalendarManager}
	{description: Weak reference to the VidyoCalendarManager object.}
}
*/

/**
{type reference-counted="yes":
	{name: VidyoCalendarManagerFeedback}
	{parent: CalendarManager}
	{description: Interface for registering callbacks that notify an application about events on the VidyoCalendarManager object. Multiple feedbacks can be registered on the same VidyoCalendarManager.}
}
*/

/**
{type visibility="private":
	{name: VidyoCalendarManagerFeedbackHandle}
	{parent: VidyoCalendarManagerFeedback}
	{description: Weak reference to the VidyoCalendarManagerFeedback interface.}
}
*/



/* =================================*/
/* =========== METHODS ============ */
/* =================================*/

/**
{function:
	{name: VidyoCalendarManagerConstruct}
	{parent: VidyoCalendarManager}
	{description:
		Constructor for Vidyo Calendar Service Manager
	}
	{prototype: VidyoCalendarManager* VidyoCalendarManagerConstruct(VidyoCalendarManager *calendarMgr,
																	VidyoCalendarManagerFeedback* feedback,
																	LmiAllocator* alloc)
	}
	{parameter:
		{name: calendarMgr}
		{description: }
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
*/	
VidyoCalendarManager* VidyoCalendarManagerConstruct(VidyoCalendarManager *calendarMgr, VidyoCalendarManagerFeedback* feedback, LmiAllocator* alloc);


/**
{function:
	{name: VidyoCalendarManagerDestruct}
	{parent: VidyoCalendarManager}
	{description:
		Destructor for Vidyo Calendar Service Manager
	}
	{prototype: 
		void VidyoCalendarManagerDestruct(VidyoCalendarManager *calendarMgr)
	}
	{parameter:
		{name: calendarMgr}
		{description: }
	}	
}
*/ 


/**
{function visibility="private":
	{name: VidyoCalendarManagerGetHandle}
	{parent: VidyoCalendarManager}
	{description: }
	{prototype: const VidyoCalendarManagerHandle* VidyoCalendarManagerGetHandle(const VidyoCalendarManager* cm)}
	{parameter:
		{name: cm}
		{description: }
	}
	{return: }
}
*/
const VidyoCalendarManagerHandle* VidyoCalendarManagerGetHandle(const VidyoCalendarManager* cm);


/**
{function:
	{name: VidyoCalendarManagerInitialize}
	{parent: VidyoCalendarManager}
	{description: 
			Prepares the environment for accessing the underlying calendar services 
	}
	{prototype: 
			LmiBool VidyoCalendarManagerInitialize(VidyoCalendarManager *calendarMgr)
	}
	{parameter:
		{name: calendarMgr}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoCalendarManagerInitialize(VidyoCalendarManager *calendarMgr);


/**
{function:
	{name: VidyoCalendarManagerUninitialize}
	{parent: VidyoCalendarManager}
	{description:
		Cleans up all resources related to calendar processing.  MUST be performed before destructing the VidyoCalendarManager
	}
	{prototype:
		LmiBool VidyoCalendarManagerUninitialize(VidyoCalendarManager *calendarMgr)
	}
	{parameter:
	{name: calendarMgr}
	{description: }
	}
	{return: }
}
*/
LmiBool VidyoCalendarManagerUninitialize(VidyoCalendarManager *calendarMgr);

/**
{function :
	{name: VidyoCalendarManagerCreateCalendarInstance}
	{parent: VidyoCalendarManager}
	{description:
		Creates a VidyoCalendar which is returned through VidyoCalendarManagerFeedbackCalendarCreated.  Will be identifiable through the service ID and calendarName.
	}
	{prototype:
	LmiBool VidyoCalendarManagerCreateCalendarInstance(VidyoCalendarManager* calMgr,
															VidyoCalendarFeedback * feedback,
															LmiString * svcId,
															LmiString * calendarName,															
															LmiString * createToken)
	}
	{parameter:
		{name: calMgr}
		{description: }
	}
	{parameter:
		{name: feedback}
		{description: Calendar feeback handle}
	}
	{parameter:
		{name: svcId}
		{description: The service Id to create the calendar against. Use VidyoCalendarManagerGetCalendarSvcString to retrieve the string for the ID}
	}
	{parameter:
		{name: calendarName}
		{description: Name of the calendar or calendar folder that will be used to operate against for the service.  An empty string indicates that the default calendar should be used. }
	}
	{parameter:
		{name: createToken}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoCalendarManagerCreateCalendarInstance(VidyoCalendarManager* calMgr, VidyoCalendarFeedback* feedback, LmiString * svcId, LmiString * calendarName, LmiString * createToken);

/**
{function :
	{name: VidyoCalendarManagerDeleteCalendarInstance}
	{parent: VidyoCalendarManager}
	{description:
		Destructs the for VidyoCalendar calendar instance passed in. 
	}
	{prototype:
		void VidyoCalendarManagerDeleteCalendarInstance(VidyoCalendarManager* calMgr, VidyoCalendar * cal)
	}
	{parameter:
		{name: calMgr}
		{description: }
	}
	{parameter:
		{name: cal}
		{description: Calendar handle}
	}
}
*/
void VidyoCalendarManagerDeleteCalendarInstance(VidyoCalendarManager* calMgr, VidyoCalendar * cal);



/**
{function:
	{name: VidyoCalendarManagerGetCalendarSvcString}
	{parent: VidyoCalendarManager}
	{description:
		Retrieves the list of calendar types that the given calendar manager is configured to operate against.
	}
	{prototype:
		LmiString* VidyoCalendarManagerGetCalendarSvcString(VidyoCalendarManagerDefaultServices calendarId)
	}
	{parameter:
		{name: calendarId}
		{description: Enumerated calendar ID to retrieve the string value for.}
	}
	{return: String identifying the calendar service}
}
*/
LmiString * VidyoCalendarManagerGetCalendarSvcString(VidyoCalendarManagerDefaultServices calendarId);



/**
{function:
	{name: VidyoCalendarManagerGetCalendarTypes}
	{parent: VidyoCalendarManager}
	{description:
		Retrieves the list of calendar types that the given calendar manager is configured to operate against.
	}
	{prototype:
		LmiBool VidyoCalendarManagerGetCalendarTypes(VidyoCalendarManager *calendarMgr, LmiVector(VidyoCalendarManagerDefaultServices) * serviceTypes)
	}
	{parameter:
		{name: calendarMgr}
		{description: Calendar manager object to retrieve the supported calendar types from.}
	}
	{parameter:
		{name: serviceTypes}
		{description: Calendar manager object to retrieve the supported calendar types from.}
	}

	{return: }
}
*/
LmiBool VidyoCalendarManagerGetCalendarTypes(VidyoCalendarManager *calendarMgr, LmiVector(VidyoCalendarManagerDefaultServices) * serviceTypes);

/**
{function:
	{name: VidyoCalendarManagerSetCalendarTypes}
	{parent: VidyoCalendarManager}
	{description:
		Specifies a specific list of calendar types that the given calendar manager will be allowed to operate against.
	}
	{prototype:
		LmiBool VidyoCalendarManagerSetCalendarTypes(VidyoCalendarManager *calendarMgr, LmiVector(VidyoCalendarManagerDefaultServices) * serviceTypes)
	}
	{parameter:
		{name: calendarMgr}
		{description: Calendar manager object to retrieve the supported calendar types from.}
	}
	{parameter:
		{name: serviceTypes}
		{description: The set of calendar service types that the implementer wants to let the user of the library use.}
	}
	{return: LmiBool }
}
*/
LmiBool VidyoCalendarManagerSetCalendarTypes(VidyoCalendarManager *calendarMgr, LmiVector(VidyoCalendarManagerDefaultServices) * serviceTypes);

/**
{function visibility="private":
	{name: VidyoCalendarManagerSetUserData}
	{parent: VidyoCalendarManager}
	{description: Sets a user data pointer that can be retreived later.}
	{prototype: void VidyoCalendarManagerSetUserData(VidyoCalendarManager* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendarManager object.}
	}
	{parameter:
		{name: userData}
		{description: Void pointer that holds opaque application data.}
	}
}
*/
void VidyoCalendarManagerSetUserData(VidyoCalendarManager* c, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoCalendarManagerGetUserData}
	{parent: VidyoCalendarManager}
	{description: Retreives the user data pointer that was previousely set by Calendaring VidyoCalendarManagerSetUserData.}
	{prototype: LmiVoidPtr VidyoCalendarManagerGetUserData(const VidyoCalendarManager* c)}
	{parameter:
		{name: c}
		{description: Pointer to the VidyoCalendarManager object.}
	}
	{return: Void pointer that holds opaque application data.}
}
*/
LmiVoidPtr VidyoCalendarManagerGetUserData(const VidyoCalendarManager* c);



/* =================================*/
/* ========= CALLBACKS ============ */
/* =================================*/

/**
{callback:
	{name: VidyoCalendarManagerFeedbackServiceDiscovery}
	{parent: VidyoCalendarManagerFeedback}
	{description:	
		{p: Triggered through the construction of calendar manager.  Returns the results from discovering the avialability for the supported calendar services. }
		{p: }
		{p: Triggered through method(s):  VidyoCalendarManagerConstruct  }	
	}
	{prototype: 
		void (*VidyoCalendarManagerFeedbackServiceDiscovery)(VidyoCalendarManagerFeedback *f, VidyoCalendarManager * cm, LmiString *t, VidyoCalendarServiceStatus s)
	}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarManagerFeedback object. }
	}
	{parameter:
		{name: cm}
		{description: Pointer to the VidyoCalendarManager object. }
	}
	{parameter:
		{name: t}
		{description: Calendar service type. }
	}
	{parameter:
		{name: s}
		{description: Status of the service after the discovery attempt. }
	}
}
*/
typedef void(*VidyoCalendarManagerFeedbackServiceDiscovery)(VidyoCalendarManagerFeedback *f, VidyoCalendarManager * cm, LmiString *t, VidyoCalendarServiceStatus s);

/**
{callback:
	{name: VidyoCalendarManagerFeedbackUninitialized}
	{parent: VidyoCalendarManagerFeedback}
	{description:
		{p: Triggered through the construction of calendar manager.  Returns the results from discovering the avialability for the supported calendar services. }
		{p: }
		{p: Triggered through method(s):  VidyoCalendarManagerConstruct  }
	}
	{prototype:
		void (*VidyoCalendarManagerFeedbackUninitialized)(VidyoCalendarManagerFeedback *f, VidyoCalendarManager * cm)
	}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarManagerFeedback object. }
	}
	{parameter:
		{name: cm}
		{description: Pointer to the VidyoCalendarManager object. }
	}
}
*/
typedef void(*VidyoCalendarManagerFeedbackUninitialized)(VidyoCalendarManagerFeedback *f, VidyoCalendarManager * cm);


/**
{callback :
	{name: VidyoCalendarManagerFeedbackCalendarCreated}
	{parent: VidyoCalendarManagerFeedback}
	{description:
		Returns the created VidyoCalendar that was initiated through VidyoCalendarManagerCreateCalendarInstance.
	}
	{prototype:
		void (*VidyoCalendarManagerFeedbackCalendarCreated)(VidyoCalendarManagerFeedback *f, VidyoCalendarManager * cm, VidyoCalendar * calendar, VidyoCalendarServiceCode resultCode, LmiString * createToken)
	}
	{parameter:
		{name: f}
		{description: Calendar Manager feeback handle}
	}
	{parameter:
		{name: cm}
		{description: Calendar Manager object}
	}
	{parameter:
		{name: calendar}
		{description: The created calendar}
	}
	{parameter:
		{name: resultCode}
		{description: Will hold VIDYO_CALENDARSERVICECODE_Ok for a successfully created calendar, otherwise an error occured}
	}
	{parameter:
		{name: createToken}
		{description: Contains the value passed into the original VidyoCalendarManagerCreateCalendarInstance call for matching the request to this response }
	}
}
*/
typedef void(*VidyoCalendarManagerFeedbackCalendarCreated)(VidyoCalendarManagerFeedback* f, VidyoCalendarManager * cm, VidyoCalendar * calendar, VidyoCalendarServiceCode resultCode, LmiString * createToken);


/**
{function:
	{name: VidyoCalendarManagerFeedbackConstruct}
	{parent: VidyoCalendarManagerFeedback}
	{description: }
	{prototype: VidyoCalendarManagerFeedback* VidyoCalendarManagerFeedbackConstruct(VidyoCalendarManagerFeedback* f,
																									VidyoCalendarManagerFeedbackServiceDiscovery serviceStatus,
																									VidyoCalendarManagerFeedbackUninitialized uninitialized,
																									VidyoCalendarManagerFeedbackCalendarCreated calendarCreated,
																									LmiAllocator* alloc)
	}
	{parameter:
		{name: f}
		{description: Feedback structure to hold registered member functions}
	}
	{parameter:
		{name: serviceStatus}
		{description: }
	}
	{parameter:
		{name: uninitialized}
		{description: }
	}
	{parameter:
		{name: calendarCreated}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoCalendarManagerFeedback* VidyoCalendarManagerFeedbackConstruct(VidyoCalendarManagerFeedback* f,
																					VidyoCalendarManagerFeedbackServiceDiscovery serviceStatus,
																					VidyoCalendarManagerFeedbackUninitialized uninitialized,
																					VidyoCalendarManagerFeedbackCalendarCreated calendarCreated,
																					LmiAllocator* alloc);


/**
{function visibility="private":
	{name: VidyoCalendarManagerFeedbackSetUserData}
	{parent: VidyoCalendarManagerFeedback}
	{description: Sets a user data pointer that can be retreived later or in VidyoCalendarManagerFeedback callbacks. }
	{prototype: void VidyoCalendarManagerFeedbackSetUserData(VidyoCalendarManagerFeedback* f, LmiVoidPtr userData)}
		{parameter:
		{name: f}
	{description: Pointer to the VidyoCalendarManagerFeedback object.}
	}
	{parameter:
		{name: userData}
		{description: Pointer that holds opaque application data. }
	}
}
*/
void VidyoCalendarManagerFeedbackSetUserData(VidyoCalendarManagerFeedback* f, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoCalendarManagerFeedbackGetUserData}
	{parent: VidyoCalendarManagerFeedback}
	{description: Retreives a user data pointer that was previousely set by calling VidyoCalendarManagerFeedbackSetUserData. }
	{prototype: LmiVoidPtr VidyoCalendarManagerFeedbackGetUserData(const VidyoCalendarManagerFeedback* f)}
	{parameter:
		{name: f}
		{description: Pointer to the VidyoCalendarManagerFeedback object.}
	}
	{return: Pointer that holds opaque application data.}
}
*/
LmiVoidPtr VidyoCalendarManagerFeedbackGetUserData(const VidyoCalendarManagerFeedback* f);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoCalendarManagerInline.h"
#endif

#endif /* VIDYO_CALENDAR_SERVICE_MANAGER_H_ */
