/**
{file:
	{name: VidyoCalendarLibraryDefs.h}
	{description: Definitions and interface for VidyoCalendar plug-in Library. }
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
#ifndef VIDYO_CALENDAR_LIBRARY_DEFS_H_ 
#define VIDYO_CALENDAR_LIBRARY_DEFS_H_ 

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define VERSION_NUM 1

#define MEETING_ATTENDEE_EMAIL_SIZE 256
#define MEETING_ATTENDEE_NAME_SIZE 256

#define MEETING_SUBJECT_SIZE 256
#define MEETING_LOCATION_SIZE 256
#define MEETING_ID_SIZE 256
#define MEETING_TIME_SIZE 64


// Return codes for connection status of the CalendarImpl
typedef enum
{
	CALCONNECTCODE_OK = 0,
	CALCONNECTCODE_NoService = 1,
	CALCONNECTCODE_ConnectionFailed = 2,
	CALCONNECTCODE_ConnectionLost = 3,
	CALCONNECTCODE_ConnectionTimeout = 4,
	CALCONNECTCODE_InvalidCredentials = 5,
	CALCONNECTCODE_InvalidCalendarId = 6,
	CALCONNECTCODE_GeneralError = 7
} CalendarConnectCode;


typedef enum
{
	MEETINGSEARCHRESULT_OK = 0,
	MEETINGSEARCHRESULT_NoRecords = 1,
	MEETINGSEARCHRESULT_NoResponse = 2,
	MEETINGSEARCHRESULT_MiscLocalError = 3,
	MEETINGSEARCHRESULT_MiscRemoteError = 4
} MeetingSearchResult;


typedef enum
{
	MEETING_ATTENDEE_ROLE_CHAIR = 0,
	MEETING_ATTENDEE_ROLE_REQUIRED = 1,
	MEETING_ATTENDEE_ROLE_OPTIONAL = 2,
	MEETING_ATTENDEE_ROLE_INFORMATIONAL = 3
} MeetingAttendeeRole;


typedef enum
{	
	MEETING_ATTENDEE_STATUS_NEEDSACTION = 0,
	MEETING_ATTENDEE_STATUS_ORGANIZED = 1,
	MEETING_ATTENDEE_STATUS_ACCEPTED = 2,
	MEETING_ATTENDEE_STATUS_DECLINED = 3,
	MEETING_ATTENDEE_STATUS_TENTATIVE = 4,
	MEETING_ATTENDEE_STATUS_DELEGATED = 5,
	MEETING_ATTENDEE_STATUS_NONE = 6,
	MEETING_ATTENDEE_STATUS_COMPLETED = 7,
	MEETING_ATTENDEE_STATUS_INPROCESS = 8
} MeetingAttendeeStatus;


typedef enum
{
	MEETING_TYPE_VIDYO = 0,
	MEETING_TYPE_STANDARD = 1
} MeetingType;

typedef struct _MeetingAttendee
{
	char name[MEETING_ATTENDEE_NAME_SIZE];
	char email[MEETING_ATTENDEE_EMAIL_SIZE];
	MeetingAttendeeRole role;
	MeetingAttendeeStatus status;
} MeetingAttendee;

typedef struct _CalendarMeeting
{
	char id[MEETING_ID_SIZE];
	char startTime[MEETING_TIME_SIZE];
	char endTime[MEETING_TIME_SIZE];
	char ownerName[MEETING_ATTENDEE_NAME_SIZE];
	char ownerEmail[MEETING_ATTENDEE_EMAIL_SIZE];
	char subject[MEETING_SUBJECT_SIZE];
	char location[MEETING_LOCATION_SIZE];
	char vidyoMeetingRoomId[MEETING_ID_SIZE];
	MeetingType type;
	size_t bodyLength;
	char *body;
	size_t attendeeCount;
	MeetingAttendee *attendees;
} CalendarMeeting;

typedef struct _CalendarMeetingList
{
	size_t meetingCount;
	CalendarMeeting *meetings;
} CalendarMeetingList;

typedef struct _CalendarImpl CalendarImpl;
typedef struct _CalendarPluginInterface CalendarPluginInterface;

/***/
// Service registration API method names
// (Will be used to by VidyoClient calendar modules to identify exported registration methods using GetProcAddress)
//
#define VCM_GET_VERSION_FUNC_NAME	"CalendarPluginGetVersion"
#define VCM_INITIALIZE_FUNC_NAME	"CalendarPluginInitialize"
#define VCM_UNINITIALIZE_FUNC_NAME	"CalendarPluginUninitialize"

// Export for function used to retrieve the library version
DLL_API bool CalendarPluginGetVersion(int version);

// Export for function used to register the API with...
DLL_API bool CalendarPluginInitialize(CalendarPluginInterface * serviceCalls, const char * serviceName);

// Signature for Deinitialize callback
typedef void(*UninitializeLibrary)(void* appData);

//*************************************************************************************************
// Export for function used by the VidyoClient calendar module to shut down the calendar library.  The
// plugin implementation of this method should perform the following logic:
//	- Perform any shutdown / logout for the plugin application object
//	- Remove any references to internal plugin application objects
//	- Once internal plugin application shutdown is complete, initiate DeinitializeLibrary to VidyoClient layer
//	- DeinitializeLibrary callback must be initiated over an independent thread.
//
DLL_API bool CalendarPluginUninitialize(UninitializeLibrary uninitCallback, void *appData);


//*************************************************************************************************
// Callback typedefs for reporting calendar related events back to the VidyoClient calendar library
//	NOTES: 
//			- All feedbacks must be intiated over an independent thread
//			- All argument values must be persisted until the application returns from the callback
//			- The appData arguments must hold the pointer value set by CalendarPluginInterface->CalendarSetUserData method
//-------------------------------------------------------------------------------------------------

//	CalendarFeedbackDeleted: Calendar specified by calendarId has been deleted
typedef void(*CalendarFeedbackDeleted)(CalendarImpl * calData, const char * calendarId, void * appData);

//-------------------------------------------------------------------------------------------------
//	CalendarFeedbackConnectResult: Result of connection attempt to the plugin calendar resource identified by calendarId
//		- Result contains a CalendarConnectCode defined value (see above)
typedef void(*CalendarFeedbackConnectResult)(CalendarImpl * calData, const char * calendarId, CalendarConnectCode result, void * appData);

//-------------------------------------------------------------------------------------------------
//	CalendarFeedbackConnectResult: Result of connection attempt to the plugin calendar resource identified by calendarId
//		- Result contains a CalendarConnectCode defined value (see above)
typedef void(*CalendarFeedbackDisconnected)(CalendarImpl * calData, const char * calendarId, CalendarConnectCode result, void * appData);

//-------------------------------------------------------------------------------------------------
//	CalendarFeedbackMeetingEvent: Meeting reminder (contained in meetingData argument) belonging to the calendar resource identified by calendarId
typedef void(*CalendarFeedbackMeetingEvent)(CalendarImpl * calData, const char * calendarId, const char * meetingId, const CalendarMeeting * meetingData, void * appData);

//-------------------------------------------------------------------------------------------------
//	CalendarFeedbackGetMeetingsResult: Meeting search results will be contained in meetingData argumment, for the calendar resource identified by calendarId 
//		- searchResult argument contains a MeetingSearchResult defined value (see above)
typedef void(*CalendarFeedbackGetMeetingsResult)(CalendarImpl * calData, const char * calendarId, MeetingSearchResult searchResult, const CalendarMeetingList * meetingData, int numRecords, void * appData);

//-------------------------------------------------------------------------------------------------
//	CalendarFeedbackMeetingCreated: Created meeting will be contained in meetingData argumment
//		- createdToken holds an application specific string tying this callback to the request that triggered the event
typedef void(*CalendarFeedbackMeetingCreated)(CalendarImpl * calData, const char * calendarId, const CalendarMeeting * meetingData, const char * createdToken, void * appData);

//-------------------------------------------------------------------------------------------------
//	CalendarFeedbackMeetingUpdated: Updated meeting will be contained in meetingData argumment
//		- createdToken holds an application specific string tying this callback to the request that triggered the event
typedef void(*CalendarFeedbackMeetingUpdated)(CalendarImpl * calData, const char * calendarId, const CalendarMeeting * meetingData, const char * updatedToken, void * appData);

//-------------------------------------------------------------------------------------------------
//	CalendarFeedbackMeetingEvent: Meeting search results will be contained in meetingData argumment, for the calendar resource identified by calendarId 
typedef void(*CalendarFeedbackMeetingRemoved)(CalendarImpl * calData, const char * calendarId, const CalendarMeeting * meetingData, const char * removedToken, void * appData);


// Struct for callback interface that the calendar service will use to issue events back to the VidyoCalendar instance
typedef struct CalendarClientPluginFeedbackImpl CalendarClientPluginFeedback;

struct CalendarClientPluginFeedbackImpl
{
	CalendarFeedbackDeleted				calendarDeleted;
	CalendarFeedbackConnectResult		connectResult;
	CalendarFeedbackDisconnected		disconnected;
	CalendarFeedbackMeetingEvent		meetingEvent;
	CalendarFeedbackGetMeetingsResult	getMeetingResults;
	CalendarFeedbackMeetingCreated		meetingCreated;
	CalendarFeedbackMeetingUpdated		meetingUpdated;
	CalendarFeedbackMeetingRemoved		meetingRemoved;
};


typedef struct _CalendarDateTime CalendarDateTime;
struct _CalendarDateTime
{
	short int	dtYear;
	short int	dtMonth;
	short int	dtDay;
	short int	dtHour;
	short int	dtMinutes;	
};


/****/
// Signatures for interface methods
typedef bool(*CalendarCreateInstance)(CalendarImpl ** calData, const char * svcName, const char* user, const char* password, const char* mailbox, const char* webServiceUrl);
typedef const char*(*CalendarGetType)(CalendarImpl * calData);
typedef bool(*CalendarDeleteInstance)(CalendarImpl * calData);
typedef bool(*CalendarSetUserData)(CalendarImpl * calData, void * userData);
typedef void*(*CalendarGetUserData)(CalendarImpl * calData);
typedef bool(*CalendarConnect)(CalendarImpl * calData);
typedef bool(*CalendarSetFeedback)(CalendarImpl * calData, CalendarClientPluginFeedback * feedbacks);
typedef bool(*CalendarSearchMeetings)(CalendarImpl * calData, const char * searchString, CalendarDateTime beginDateTime, CalendarDateTime endDateTime, int index, int pageSize);


// Struct for vendor specific calendar interface methods and callbacks
struct _CalendarPluginInterface
{
	int version;

	// Interface Methods
	CalendarCreateInstance		createInstance;
	CalendarGetType				getType;
	CalendarSetUserData			setUserData;
	CalendarGetUserData			getUserData;
	CalendarConnect				connect;
	CalendarSetFeedback			setFeedback;
	CalendarSearchMeetings		searchMeetings;		
};


#if defined(__cplusplus)
}
#endif

#endif /* VIDYO_CALENDAR_LIBRARY_DEFS_H_ */
