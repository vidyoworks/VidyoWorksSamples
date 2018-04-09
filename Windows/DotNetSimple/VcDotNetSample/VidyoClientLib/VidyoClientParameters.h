/*! @file VidyoClientParameters.h
	@brief Message parameters for Vidyo Client API Library.
	@copyright (c) 2006-2014 Vidyo, Inc.
	433 Hackensack Avenue, 7th Floor,
	Hackensack, NJ  07601.
	All rights reserved.
	The information contained herein is proprietary to Vidyo, Inc.
	and shall not be reproduced, copied (in whole or in part), adapted,
	modified, disseminated, transmitted, transcribed, stored in a retrieval
	system, or translated into any language in any form by any means
	without the express written consent of Vidyo, Inc.
*/


#ifndef VIDYO_CLIENT_PARAMETERS_H
#define VIDYO_CLIENT_PARAMETERS_H

/*******************************************************************************
 Parameter enumerations for messages between Vidyo Client Library and GUI
*******************************************************************************/

/*! Modes for self-view region in video layout.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PREVIEW
		+ #VIDYO_CLIENT_OUT_EVENT_PREVIEW

	- Passed in field previewMode of following structures:
		+ #VidyoClientInEventPreview
		+ #VidyoClientOutEventPreview

	@warning Mobile version is limited
*/

typedef enum VidyoClientPreviewMode_
{
	/*! Disable preview */
	VIDYO_CLIENT_PREVIEW_MODE_NONE = 0,
	/*! Picture-in-picture mode */
	VIDYO_CLIENT_PREVIEW_MODE_PIP,
	/*! Docking mode */
	VIDYO_CLIENT_PREVIEW_MODE_DOCK,
	/*! Only supported on Room systems */
	VIDYO_CLIENT_PREVIEW_MODE_OTHER = 4
} VidyoClientPreviewMode;

/*! Types of messages that could be shown to a user.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_USER_MESSAGE
	- Passed in field messageType of following structures:
		+ #VidyoClientOutEventUserMessage
*/
typedef enum VidyoClientUserMessageType_
{
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CHANGES_TO_AUDIO_VIDEO_DEVICES,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CANNOT_DETERMINE_LOG_PATH,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CANNOT_DETERMINE_INSTALLED_PATH,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CANNOT_WRITE_LOG_FILE,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VIDYO_SDK_BASE,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_FRAMEWORK_LOG,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VIDYO_DESKTOP_LOG,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VIDYOPROXY_LOG,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_SDK_CLIENT,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_CONSTRUCTION_VD_LOGIC,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_START_VD_LOGIC,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VD_HELPER_CONSTRUCT,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VD_HELPER_START,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_CONSTRUCTION_STRING_TRANSLATION_TABLE,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_SSE2_CHECK_FAILED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_TASKBAR_ICON_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CONF_STATUS_HOTKEY,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_AUDIO_DEBUG_HOTKEY,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_LOG_SETTINGS_HOTKEY,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_APP_SERVER_COMM_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_PROTOCOL_VERSION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INVALIDUSER_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INVALIDMAC_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_USERINCONF_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INVALIDCONF_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MAXPORTS_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_LOCKEDCONF_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NOROUTER_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CONFMAXUSERS_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MAXDESKTOPS_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_OFFLINECALLER_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_OFFLINECALLEE_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_START_VIDEO_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_START_AUDIO_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CONTACT_USER_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_USER_NO_ANSWER,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_ROUTER_REJECT_JOIN_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_OTHER_PARTY_HANGUP,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NO_CAMERA,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NO_MICROPHONE,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_JOIN_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NO_SPEAKERS,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_COMPLETE_CALL_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_JOIN_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CALLER_CANCELLED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CALLEE_DECLINED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_LOGGED_IN_ELSEWHERE_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NOT_LOGGED_IN_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_IN_CALL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_IN_CALL_OR_CONFERENCE_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_UNEXPECTED_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CALL_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_SIGNIN_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_ACCEPT_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_IGNORE_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_RESTART_VIDEO_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_LOCK_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_F_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_L_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_LS_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_RANGE_LS_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_CH_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_RANGE_CH_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_CW_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_RANGE_CW_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_LP_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_RANGE_LP_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_MD_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_RANGE_MD_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_P_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_S_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_MISSING_VALUE_U_OPTION_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_DIRECT_X_DISABLED_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NO_DIRECT_X_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NO_MAC_ADDR_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_DISCONNECTED_FROM_CONFERENCE ,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CONNECTION_TO_SERVER_LOST,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_HEARTBEAT_FAILED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_DISCONNECTED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_HTTP_RESPONSE_CODE,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_HTTP_RESPONSE_407,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INVITATION_TIMED_OUT,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_PROXY_CONNECT_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_COULDNT_RESOLVE_PROXY,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_QUEUE_INTERNAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_INACTIVE_EID,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_LOGGED_OUT_BY_SERVER,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NETWORK_CONNECTIVITY,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CALL_TIMED_OUT,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_WEB_PROXY_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_REGISTER_LICENSE_COM_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_REGISTER_LICENSE_OTHER,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_CHECK_UPDATES_NORMAL_MSG,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_SELECTED_DEVICE_LOST_MSG,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_DEVICE_SELECTION_CHANGED_MSG,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_AUDIO_ECHO_COUPLING_WARNING,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_DIAGNOSTICS_REPORT_GENERATED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_TOO_FREQUENT_START_VIDEO_IGNORED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_TOO_FREQUENT_STOP_VIDEO_IGNORED,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_BAD_STUN_SERVER,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NO_NW_INTERFACES,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_FAILED_OPEN_MEDIA_CONNECTION,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_QUEUE_FATAL_ERROR,
	VIDYO_CLIENT_USER_MESSAGE_TYPE_NO_MESSAGE, /* Always leave last.
												  Represents an unset message field */
} VidyoClientUserMessageType;

/*! Types of media devices.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_DEVICES_CHANGED
	- Passed in field deviceType of following structures:
		+ #VidyoClientOutEventDevicesChanged
*/
typedef enum VidyoClientDeviceType_
{
	/*! Audio playback */
	VIDYO_CLIENT_DEVICE_TYPE_AUDIO_OUT = 1,
	/*! Audio capturing */
	VIDYO_CLIENT_DEVICE_TYPE_AUDIO_IN,
	/*! Video */
	VIDYO_CLIENT_DEVICE_TYPE_VIDEO,
	/*! Ring tone */
	VIDYO_CLIENT_DEVICE_TYPE_RING_TONE,
} VidyoClientDeviceType;

/*! Status of endpoint registration and user binding.  Indicate state of client connection to
	servers.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_SUBSCRIBING
	- Used in field  of following structures:
		+ #VidyoClientRequestGetEndpointStatus
*/
typedef enum VidyoClientEndpointStatus_
{
	VIDYO_CLIENT_ENDPOINT_STATUS_INACTIVE,  /*!< Client not registered to
											   server */
	VIDYO_CLIENT_ENDPOINT_STATUS_REGISTERED,/*!< Registered to server, but not
											   bound to a user */
	VIDYO_CLIENT_ENDPOINT_STATUS_ACTIVE,    /*!< Client is registered and bound
											   to a user - ready for use */
} VidyoClientEndpointStatus;

/*! Status of user sign-in.  Indicate state of how user is signed in.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_SIGN_IN
	- Passed in field signinType of following structures:
		+ #VidyoClientOutEventSignIn
*/
typedef enum VidyoClientSignInEnum_
{
	SIGNIN_INTERNAL = 1,    /*!< The source of the sign-in event
							   is the VidyoClient library */
	SIGNIN_EXTERNAL,        /*!< The source of the sign-in event
							   is external e.g. browser */
	SIGNIN_APPLICATION,     /*!< The source of the sign-in event
							   is the application using VidyoClient */
} VidyoClientSignInEnum;

/*! Commands that control media streams.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL
	- Passed in field mediaCommand of following structures:
		+ #VidyoClientOutEventMediaControl
*/
typedef enum VidyoClientMediaControlCommand_
{
	VIDYO_CLIENT_MEDIA_CONTROL_COMMAND_MUTE,    /*!< Mute */
	VIDYO_CLIENT_MEDIA_CONTROL_COMMAND_UNMUTE,  /*!< Unmute */
	VIDYO_CLIENT_MEDIA_CONTROL_COMMAND_SILENCE, /*!< Silence */
} VidyoClientMediaControlCommand;

/*! Types of media streams that can be controlled.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL
	- Passed in field mediaType of following structures:
		+ #VidyoClientOutEventMediaControl
*/
typedef enum VidyoClientMediaControlType_
{
	VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO,          /*!< Video stream */
	VIDYO_CLIENT_MEDIA_CONTROL_TYPE_APPLICATION,    /*!< Application (sharing) stream */
	VIDYO_CLIENT_MEDIA_CONTROL_TYPE_AUDIO,          /*!< Audio stream */
	VIDYO_CLIENT_MEDIA_CONTROL_TYPE_SPEAKER,		/*!< Speaker */
	VIDYO_CLIENT_MEDIA_CONTROL_TYPE_UNKNOWN,        /*!< Stream type is unknown */
} VidyoClientMediaControlType;

/*! Locality of media streams that can be controlled.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL
	- Passed in field mediaSource of following structures:
		+ #VidyoClientOutEventMediaControl
*/
typedef enum VidyoClientMediaControlSource_
{
	VIDYO_CLIENT_MEDIA_CONTROL_SOURCE_LOCAL,    /*!< Local stream */
	VIDYO_CLIENT_MEDIA_CONTROL_SOURCE_REMOTE,   /*!< Remote stream */
	VIDYO_CLIENT_MEDIA_CONTROL_SOURCE_UNKNOWN,  /*!< Unknown stream */
} VidyoClientMediaControlSource;

/*! Configuration of video layout resolution and frame rate.
	- Used for the following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CONFIGURATION
	VIDYO_CLIENT_REQUEST_SET_CONFIGURATION
	- Passed in field videoPreferences of following structures:
		+ #VidyoClientRequestConfiguration
*/
typedef enum VidyoClientVideoPreferences_
{
	VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_QUALITY,
	/*!< Default. All resolutions above SVGA are filtered out. For VGA
	   resolutions and above (incl. SVGA) -- frame-rate is limited to 15
	   FPS. 
	   @note For Android finds closest resolution at or below 640x480 */
	VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_FRAMERATE,
	/*!< All resolutions above 720p are filtered out. Minimal frame-rate is
	   30 FPS. 
	   @note for Android finds the closest resolution at or below 320x240 */
	VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_RESOLUTION,
	/*!< All resolutions above 720p are filtered out. Maximal frame-rate is
	   15 FPS.
	   @note For Android finds closest resolution at or below 960x720 */
	VIDYO_CLIENT_VIDEO_PREFERENCES_LIMITED_BANDWIDTH,
	/*!< Limit the maximum encoding resolution to CIF. No limit on the
	   frame-rate -- would initially be 30 FPS. Set the initial ABA
	   available receive bandwidth for video to 500Kbp/s.
	   @note for Android finds the closest resolution at or below 320x240 */
	VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_360p30,
	/*!< Limit resolution to 360p using CPU score. Though the name has 
	   ADVANCED, this is not an advanced mode.
	   @note for Android finds the closest resolution at or below 320x240 */

	   VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_450p30 = 10,
	/*!< Limit resolution to 450p. Ignore CPU score.
	   @note For Android finds closest resolution at or below 640x480 */
	VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_720p15 = 11,
	/*!< Limit resolution to 720p. Limit frame-rate to 15 FPS. Ignore CPU
	   score.
	   @note For Android finds closest resolution at or below 960x720 */
	VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_720p30 = 12,
	/*!< Limit resolution to 720p. Ignore CPU score.
	   @note For Android finds closest resolution at or below 960x720 */

	VIDYO_CLIENT_VIDEO_PREFERENCES_1080p30 = 20,
	/*!< Limit resolution to 1080p using CPU score.
	   @note For Android finds closest resolution at or below 960x720 */

	VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_360p15 = 22,
	/*!< Limit resolution to 360p using CPU score.
	   @note for Android finds the closest resolution at or below 320x240 */

	/* Configurations that apply to room systems only */
	VIDYO_CLIENT_VIDEO_PREFERENCES_VIDYOROOM_SVGA = 50, /*!< Do not use */
	VIDYO_CLIENT_VIDEO_PREFERENCES_VIDYOROOM_VGA = 51, /*!< Do not use */
	VIDYO_CLIENT_VIDEO_PREFERENCES_VIDYOROOM_SUB_HD = 52, /*!< Do not use */
	VIDYO_CLIENT_VIDEO_PREFERENCES_VIDYOROOM_HD = 53, /*!< Do not use */
	VIDYO_CLIENT_VIDEO_PREFERENCES_VIDYOROOM_HD1080 = 54, /*!< Do not use */
} VidyoClientVideoPreferences;

/*! Methods for resizing of video layout.
	- Used for the following requests:
		+ #VIDYO_CLIENT_REQUEST_SNAP_RESIZE
	- Passed in field sizingmethod of following structures:
		+ #VidyoClientRequestSnapResize
*/
typedef enum VidyoClientResizingMethod_
{
	VIDYO_CLIENT_RESIZING_METHOD_HORIZONTAL,    /*!< Horizontal snapping */
	VIDYO_CLIENT_RESIZING_METHOD_VERTICAL,      /*!< Vertical snapping */
	VIDYO_CLIENT_RESIZING_METHOD_DIAGONAL,      /*!< Diagonal (both horizontal and vertical) snapping */
} VidyoClientResizingMethod;

/*! Call state indicates the client's state and whether it is engaged in a call.
	- Used for the following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CALL_STATE
		+ #VIDYO_CLIENT_OUT_EVENT_CALL_STATE
	- Passed in field sizingmethod of following structures:
		+ #VidyoClientRequestCallState
		+ #VidyoClientOutEventCallState
*/
typedef enum VidyoClientCallState_
{
	VIDYO_CLIENT_CALL_STATE_IDLE,           /*!< The client is not engaged in a call. */
	VIDYO_CLIENT_CALL_STATE_RINGING,        /*!< Incoming call. Client is ringing. */
	VIDYO_CLIENT_CALL_STATE_CALLING,        /*!< Client is dialing out. */
	VIDYO_CLIENT_CALL_STATE_JOINING,        /*!< Client is in the process of joining a
											   conference or a call. */
	VIDYO_CLIENT_CALL_STATE_IN_CONFERENCE,  /*!< Client is engaged in a conference or a
											   call. */
	VIDYO_CLIENT_CALL_STATE_DISCONNECTING,  /*!< Client is in the process of disconnecting
											   from a conference or a call. */
} VidyoClientCallState;
/*! Session display context identifiers.  Indicate how the current session was set up for
	displaying field SessionDisplayText of structure VidyoClientRequestSessionDisplayInfo properly.
	- Used for the following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CURRENT_SESSION_DISPLAY_INFO
	- Passed in field SessionDisplayContext of following structures:
		+ #VidyoClientRequestSessionDisplayInfo
*/
typedef enum VidyoClientSessionDisplayContext_
{
	VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_CONF,      /*!< Session created as a conference
													   - userID shows \<conference\> */
	VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_OUT_CALL,  /*!< Session created as outbound
													   - userID shows \<to\> */
	VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_IN_CALL,   /*!< Session created as inbound
													   - userID shows \<from\> */
	VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_IDLE       /*!< No current session */
} VidyoClientSessionDisplayContext;

/*! Display language codes.
	- Used for the following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_LANGUAGE
	- Passed in field _Languagecode_ of following structures:
		+ #VidyoClientRequestGetLanguage
*/
typedef enum VidyoClientLanguageCode_
{
	VIDYO_CLIENT_LANGUAGE_CODE_EN = 0,    /*!< U.S. English */
	VIDYO_CLIENT_LANGUAGE_CODE_FR,        /*!< French */
	VIDYO_CLIENT_LANGUAGE_CODE_JA,        /*!< Japanese */
	VIDYO_CLIENT_LANGUAGE_CODE_ZH_CN,     /*!< Chinese (simplified) */
	VIDYO_CLIENT_LANGUAGE_CODE_ES,        /*!< Spanish */
	VIDYO_CLIENT_LANGUAGE_CODE_IT,        /*!< Italian */
	VIDYO_CLIENT_LANGUAGE_CODE_DE,        /*!< German */
	VIDYO_CLIENT_LANGUAGE_CODE_KO,        /*!< Korean */
	VIDYO_CLIENT_LANGUAGE_CODE_PT,        /*!< Portuguese */
	VIDYO_CLIENT_LANGUAGE_CODE_PL,        /*!< Polish */
	VIDYO_CLIENT_LANGUAGE_CODE_FI,        /*!< Finish */
	VIDYO_CLIENT_LANGUAGE_CODE_ZH_TW,     /*!< Chinese (traditional) */
	VIDYO_CLIENT_LANGUAGE_CODE_TH,        /*!< Thai */
	VIDYO_CLIENT_LANGUAGE_CODE_RU,        /*!< Russian */
	VIDYO_CLIENT_LANGUAGE_CODE_TR,        /*!< Turkish */
	VIDYO_CLIENT_LANGUAGE_CODE_NO,        /*!< Norwegian */
	VIDYO_CLIENT_LANGUAGE_CODE_SV,        /*!< Swedish */
	VIDYO_CLIENT_LANGUAGE_CODE_NL,        /*!< Dutch */
	VIDYO_CLIENT_LANGUAGE_CODE_UNKNOWN,   /*!< KEEP THIS AS ENDING ENUM
											 - other codes are dependent on this value */
} VidyoClientLanguageCode;

/*! Commands that control camera.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_CONTROL_CAMERA
		+ #VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA
	- Passed in field cameraCommand of following structures:
		+ #VidyoClientOutEventControlCamera
	VidyoClientInEventControlCamera
*/
typedef enum VidyoClientCameraControlCommand_
{
	VIDYO_CLIENT_CAMERA_CONTROL_PANRIGHT,       /*!< Pan to the right */
	VIDYO_CLIENT_CAMERA_CONTROL_PANLEFT,        /*!< Pan to the left */
	VIDYO_CLIENT_CAMERA_CONTROL_TILTUP,         /*!< Tilt up */
	VIDYO_CLIENT_CAMERA_CONTROL_TILTDOWN,       /*!< Tilt down */
	VIDYO_CLIENT_CAMERA_CONTROL_ZOOMIN,         /*!< Zoom in */
	VIDYO_CLIENT_CAMERA_CONTROL_ZOOMOUT,        /*!< Zoom out */
	VIDYO_CLIENT_CAMERA_CONTROL_POSITION,       /*!< Set position */
	VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND,   /*!< Custom VISCA command */
	VIDYO_CLIENT_CAMERA_CONTROL_VISCARESPONSE,  /*!< Response to VISCA command */
} VidyoClientCameraControlCommand;

/*! Video display modes for video source.
	- Used for the following requests:
		+ #VIDYO_CLIENT_IN_EVENT_SET_PARTICIPANT_VIDEO_MODE
	- Passed in field videoMode of following structures:
		+ #VidyoClientInEventSetParticipantVideoMode
*/
typedef enum VidyoClientParticipantVideoMode_
{
	VIDYO_CLIENT_VIDEO_MODE_DOCK = 1,   /*!< Default video mode */
	VIDYO_CLIENT_VIDEO_MODE_PINHIGH,    /*!< Preferred video mode */
	VIDYO_CLIENT_VIDEO_MODE_PINLOW,     /*!< Continuous, subordinate to Docked */
} VidyoClientParticipantVideoMode;

/*! Conference information update event identifier.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_CONFERENCE_INFO_UPDATE
*/
typedef enum VidyoClientConferenceInfoUpdateEventID_
{
	VIDYO_CLIENT_CONFERENCE_INFO_UPDATE_WEBCASTING, /*!< Webcasting state change for the conference */
	VIDYO_CLIENT_CONFERENCE_INFO_UPDATE_RECORDING,  /*!< Recording state change for the conference */
} VidyoClientConferenceInfoUpdateEventID;

/*! Types of label or text.
	- Used for the following events:
		+ #VIDYO_CLIENT_REQUEST_SET_LABEL
*/
typedef enum VidyoClientLabelType_
{
	VIDYO_CLIENT_LABEL_SELF_VIEW,   /*!< Self-view label type */
	VIDYO_CLIENT_LABEL_MAX,         /*!< Maximum value for enum */
} VidyoClientLabelType;

/*! Values of requestType on windows share.
	- Used for the following events:
		+ #VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES
		+ #VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES
	- Passed in field requestType of following structures:
		+ #VidyoClientRequestWindowShares
*/
typedef enum VidyoClientWindowShareRequestType_
{
	LIST_SHARING_WINDOWS,           /*!< Get the list of shared application windows available for display. */
	CHANGE_SHARING_WINDOW,          /*!< Change the shared application window currently being displayed.
										 This request type with value of newApp set to 0 will stop showing
										 a remote shared app on layout window. newApp set to a valid value can
										 be used to start viewing a remote shared app on layout.*/
	TOGGLE_SHARING_WINDOW,          /*!< Change the shared application window currently being displayed to next item in list. */
	STOP_SHARING_WINDOW,            /*!< Stop display of shared application window specified by eventUri (if being displayed now).
										 If currently viewed remote shared APP view is stopped next remote APP in list will be used
										 as viewable remote sharing window. */
	UPDATE_DISPLAY_SHARING_WINDOW,  /*!< For future use. */
	ADD_SHARING_WINDOW,             /*!< For usage in mobile devices, where renderer has GUI to show/choose app share
										 @note Important to use this event when button bar is used*/
} VidyoClientWindowShareRequestType;

/*! Indicate the reason why a sign-out event is generated.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT
	- Passed in field cause of following structures:
		+ #VidyoClientOutEventSignedOut
*/
typedef enum VidyoClientSignedOutCause_
{
	VIDYO_CLIENT_USER_SIGNED_IN,    /*!< Signout generated in response to user initiated sign-in */
	VIDYO_CLIENT_USER_SIGNED_OUT,   /*!< Signout generated in response to user initiated sign-out */
	VIDYO_CLIENT_SERVER_SIGNED_OUT, /*!< Signout command from server */
	VIDYO_CLIENT_BIND_USER_TIMEOUT, /*!< Timeout happened while waiting for bind user to endpoint from server */
	VIDYO_CLIENT_AUTHENTICATION_FAILED, /*!< Authentication failed after successful sign-in. User might have disabled, deleted and might has to manually sign-in again */
	VIDYO_CLIENT_EMCP_RETRIES_EXCEEDED, /*Emcp*/
} VidyoClientSignedOutCause;

/*! Indicate the reason why #VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECTION_CHANGED is generated.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECTION_CHANGED
	- Passed in field cause of following structures:
		+ #VidyoClientOutEventDeviceSelectionChanged
*/
typedef enum VidyoClientDeviceChangeType_
{
	VIDYO_CLIENT_USER_MESSAGE_DEVICE_LOST,                  /*!< The specified device being used in conference is lost
																and no alternate selection is made. */
	VIDYO_CLIENT_USER_MESSAGE_DEVICE_SELECTION_CHANGED,     /*!< The specified device being used in conference is lost
																and another device of same type is being used now. */
} VidyoClientDeviceChangeType;

/*! Indicates particular orientation to set.
	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_ORIENTATION
	- Passed in field orientation of following structures:
		+ #VidyoClientInEventSetOrientation
*/
typedef enum VidyoClientOrientation_
{
	/* These values must be kept in sync with corresponding enum LmiOrientation */
	VIDYO_CLIENT_ORIENTATION_UP = 0,    /*!< Up */
	VIDYO_CLIENT_ORIENTATION_DOWN,      /*!< Down */
	VIDYO_CLIENT_ORIENTATION_LEFT,      /*!< Left */
	VIDYO_CLIENT_ORIENTATION_RIGHT,     /*!< Right */
} VidyoClientOrientation;

/*! Indicates which aspects of conference (own video, video layout, both) to set orientation for.
	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_ORIENTATION
	- Passed in field orientation of following structures:
		+ #VidyoClientInEventSetOrientation
*/
typedef enum VidyoClientOrientationControl_
{
	VIDYO_CLIENT_ORIENTATION_CONTROL_BOTH = 0,  /*!< Self-view and remote participants */
	VIDYO_CLIENT_ORIENTATION_CONTROL_CAPTURE,   /*!< Self-view only */
	VIDYO_CLIENT_ORIENTATION_CONTROL_RENDER,    /*!< Remote participants only */
} VidyoClientOrientationControl;

/*! Indicates which kind of touch event has been generated.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_TOUCH
	- Passed in field state of following structures:
		+ #VidyoClientInEventSetOrientation
*/
typedef enum VidyoClientTouchState_
{
	VIDYO_CLIENT_TOUCH_STATE_START = 0, /*!< Touch started */
	VIDYO_CLIENT_TOUCH_STATE_MOVE,      /*!< Moved during touch */
	VIDYO_CLIENT_TOUCH_STATE_STOP,      /*!< Touch stopped */
	VIDYO_CLIENT_TOUCH_STATE_UNKNOWN,   /*!< Touch state is not recognized */
} VidyoClientTouchState;

/*! Icons shown by the renderer.
	- Used for following events:
		+ #VIDYO_CLIENT_IN_EVENT_RENDERER_SHOW_ICON
	- Passed in field rendererIcon of following structures:
		+ #VidyoClientInEventRendererShowIcon
*/
typedef enum VidyoClientRendererIcon_
{
	/*! Webcasting indication icon */
	VIDYO_CLIENT_RENDERER_ICON_WEBCASTING, 
	/*! Recording indication icon */
	VIDYO_CLIENT_RENDERER_ICON_RECORDING,  
} VidyoClientRendererIcon;

/*! Buttons shown by in-call participants for Mobile Device .
	- Used for following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PARTICIPANT_BUTTON_CLICK
	- Passed in field rendererIcon of following structures:
		+ #VidyoClientOutEventParticipantButtonClick
	@note Mobile only
*/
typedef enum VidyoClientParticipantButtonType_
{
	VIDYO_CLIENT_PARTICIPANT_BUTTON_FECC = 0,   /*!< Far End Camera Control button */
	VIDYO_CLIENT_PARTICIPANT_BUTTON_PREFERRED,  /*!< Preferred participant button */
	VIDYO_CLIENT_PARTICIPANT_BUTTON_HIDE,       /*!< Hide button */
} VidyoClientParticipantButtonType;
/*! The state of a button, associated with a button event.
	- Used for following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PARTICIPANT_BUTTON_CLICK
	- Passed in field rendererIcon of following structures:
		+ #VidyoClientOutEventParticipantButtonClick
*/
typedef enum VidyoClientParticipantButtonState_
{
	/*! State is on */
	VIDYO_CLIENT_BUTTON_STATE_ON,
	/*! State is off */
	VIDYO_CLIENT_BUTTON_STATE_OFF,
} VidyoClientParticipantButtonState;
/*! Fault code of SOAP operation
	- Used for following events:
		+ #VIDYO_CLIENT_OUT_EVENT_LICENSE
*/
typedef enum VidyoClientSoapFault_
{
	VIDYO_CLIENT_SOAP_FAULT_NONE,   /*!< None */
	VIDYO_CLIENT_SOAP_FAULT_INVALID_ARGUMENT,   /*!< Invalid argument */
	VIDYO_CLIENT_SOAP_FAULT_NOT_LICENSED,   /*!< Not licensed */
	VIDYO_CLIENT_SOAP_FAULT_GENERAL,    /*!< General fault */
	VIDYO_CLIENT_SOAP_FAULT_CONFERENCE_LOCKED,  /*!< Conference in locked */
	VIDYO_CLIENT_SOAP_FAULT_LICENSE_EXPIRED,    /*!< License expired */
	VIDYO_CLIENT_SOAP_FAULT_WRONG_PIN,  /*!< Wrong conference PIN */
	VIDYO_CLIENT_SOAP_FAULT_RESOURCES_NOT_AVAILABLE,  /*!< Resources not available */
	VIDYO_CLIENT_SOAP_FAULT_ACCESS_RESTRICTED,  /*!< Resources not available */
	VIDYO_CLIENT_SOAP_FAULT_USER_NOT_BOUND,  /*!< User not found */
	VIDYO_CLIENT_SOAP_FAULT_ROOM_IS_FULL,  /*!< Room is full */
	VIDYO_CLIENT_SOAP_FAULT_PORTAL_PREFIX_NOT_CONFIGURED,  /*!< Portal prefix is not configured */
	VIDYO_CLIENT_SOAP_FAULT_CONTROL_MEETING_FAILED,  /*!< Control meeting failed */
} VidyoClientSoapFault;

/*! Result code of SOAP operation
	- Used for following events:
		+ #VIDYO_CLIENT_OUT_EVENT_LICENSE
*/
typedef enum VidyoClientSoapResultCode_
{
	VIDYO_CLIENT_SOAP_RESULT_FAILURE,               /*!< Result is some unknown general failure */
	VIDYO_CLIENT_SOAP_RESULT_SUCCESS,               /*!< Result is success */
	VIDYO_CLIENT_SOAP_RESULT_NOT_LICENSED,          /*!< Not licensed */
	VIDYO_CLIENT_SOAP_RESULT_SEAT_LICENSE_EXPIRED,  /*!< Seat license expired */
	VIDYO_CLIENT_SOAP_RESULT_WRONG_PIN,             /*!< Wrong PIN */
	VIDYO_CLIENT_SOAP_RESULT_CONFERENCE_LOCKED,     /*!< Conference locked */
	VIDYO_CLIENT_SOAP_RESULT_ROOM_DISABLED,         /*!< Room disabled */
	VIDYO_CLIENT_SOAP_RESULT_GENERAL_FAULT,         /*!< General Fault */
	VIDYO_CLIENT_SOAP_RESULT_INVALID_ARGUMENT_FAULT,/*!< Invalid argument fault */
	VIDYO_CLIENT_SOAP_RESULT_MEMBER_NOT_ONLINE,     /*!< Status of member is not online */
	VIDYO_CLIENT_SOAP_RESULT_NOT_OWNER_OF_ROOM,     /*!< Not owner of room */
	VIDYO_CLIENT_SOAP_RESULT_USER_NOT_FOUND,        /*!< Specified user is not found */
	VIDYO_CLIENT_SOAP_RESULT_UNEXPECTED_SUBELEMENT_IN_MESSAGE,  /*!< Unexpected sub element in SOAP message */
	VIDYO_CLIENT_SOAP_RESULT_END_POINT_NOT_FOUND,   /*!< Endpoint not found */
	VIDYO_CLIENT_SOAP_RESULT_FAILED_PLACE_DIRECT_CALL, /*!< Failed to place a direct call */
	VIDYO_CLIENT_SOAP_RESULT_IPC_JOIN_FAILURE,      /*!< Failure to join room on other portal */
	VIDYO_CLIENT_SOAP_RESULT_ALL_LINES_IN_USE,      /*!< All lines are in use */
} VidyoClientSoapResultCode;

/*! Indicates which kind of touch event has been generated.
	- Used for following events:
		+ #VIDYO_CLIENT_OUT_EVENT_FECC_STATUS_UPDATE
	- Passed in field state of following structures:
		+ #VidyoClientOutEventFeccStatusUpdate
*/
typedef enum VidyoClientFeccStatusCode_
{
	/*! The remote participant under FECC is disconnected from call */
	VIDYO_CLIENT_FECC_STATUS_CODE_USER_LOST = 0,
	/*! The remote participant under FECC set camera to privacy */
	VIDYO_CLIENT_FECC_STATUS_CODE_USER_IN_PRIVACY,
} VidyoClientFeccStatusCode;

/*! Indicates the type of Proxy available to the client.
	- Used for following events:
		+ #VIDYO_CLIENT_IN_EVENT_SIGN_IN
	- Passed in field state of following structures:
		+ #VidyoClientInEventSignIn
*/
typedef enum VidyoClientProxyType_
{
	/*! No proxy */
	VIDYO_CLIENT_PROXY_NONE = 0,
	/*! Proxy type is Vidyo Proxy */
	VIDYO_CLIENT_VIDYO_PROXY,
	/*! The proxy type is reverse proxy */
	VIDYO_CLIENT_REVERSE_PROXY,
} VidyoClientProxyType;

/*! Indicates the type of Proxy available to the client.
	- Used for following events:
		+ #VIDYO_CLIENT_IN_EVENT_SIGN_IN
	- Passed in field state of following structs:
		+ #VidyoClientInEventSignIn
*/
typedef enum VidyoClientActionType_
{
	/*! Action Type is FECC - Far End Camera Control */
	VIDYO_CLIENT_ACTION_TYPE_FECC = 0,
	/*! Action Type is pinning a remote participant */
	VIDYO_CLIENT_ACTION_TYPE_PIN = 100,
} VidyoClientActionType;

/*! Indicates the type of device selection methods available to the client.
	- Used for following events:
		+ #VIDYO_CLIENT_REQUEST_GET_CONFIGURATION & VIDYO_CLIENT_REQUEST_SET_CONFIGURATION
	- Passed in field state of following structs:
		+ #VidyoClientRequestConfiguration
*/
typedef enum VidyoClientDeviceSelectionMethod_
{
	/*! Device selection method to be used is 'history based device selection' based on previous user selection */
	HISTORY_BASED_SELECTION,
	/*! Device selection method to be used is fixed - do not use any other device */
	KIOSK_DEVICE_SELECTION,
	/*! Device selection method should follow OS/Machine default for audio devices. For camera 'history based device selection' is used */
	OS_DEFAULT_AUDIO_DEVICE_SELECTION,  
	/*! Device selection method should follow OS/Machine default for audio devices, but user can override and select a different device. For camera 'history based device selection' is used */
	OVERRIDE_OS_DEFAULT_AUDIO_DEVICE_SELECTION,
} VidyoClientDeviceSelectionMethod;

/*! Indicates the type of Echo cancellation and Automatic gain control methods available to the client.
	- Used for following events:
		+ #VIDYO_CLIENT_REQUEST_GET_CONFIGURATION & VIDYO_CLIENT_REQUEST_SET_CONFIGURATION
	- Passed in field state of following structs:
		+ #VidyoClientRequestConfiguration
*/
typedef enum VidyoClientAecAgcMethod_
{
	/*! AEC and AGC used is Vidyo Internal */
	VIDYO_INTERNAL_AEC_AGC,
	/*! AEC and AGC used is OS provided if supported in OS. If not supported use nothing */
	OS_INTERNAL_AEC_AGC,
	/*! Use both OS provided if supported in OS and Vidyo internal AEC and AGC */
	VIDYO_AND_OS_AEC_AGC,
	/*! AEC and AGC used is OS provided if supported in OS. If not supported use Vidyo internal */
	OS_INTERNAL_OR_VIDYO_AEC_AGC,
} VidyoClientAecAgcMethod;

/*! Types of client types
	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_CLIENT_VERSION_ON_SERVER
		+ #VIDYO_CLIENT_IN_EVENT_LOGIN
	- Passed in field messageType of following structures:
		+ #VidyoClientInEventClientVersionOnServer
		+ #VidyoClientInEventLogIn
*/
typedef enum VidyoClientClientType_
{
	/*! Mac client */
	VIDYO_CLIENT_CLIENTTYPE_M,
	/*! VidyoRoom HD 200 (Windows Platform) */
	VIDYO_CLIENT_CLIENTTYPE_V,
	/*! Windows client */
	VIDYO_CLIENT_CLIENTTYPE_W, 
	/*! VidyoRoom HD 100 / HD 50 (Windows Platform) */
	VIDYO_CLIENT_CLIENTTYPE_R, 
	/*! Linux client */
	VIDYO_CLIENT_CLIENTTYPE_L, 
	/*! SLS Platform */
	VIDYO_CLIENT_CLIENTTYPE_S, 
	/*! 32 bit ubuntu or SLS */
	VIDYO_CLIENT_CLIENTTYPE_U, 
	/*! SL5 64 */
	VIDYO_CLIENT_CLIENTTYPE_T, 
	/*! Ubuntu 64 */
	VIDYO_CLIENT_CLIENTTYPE_X, 
	/*! Android */
	VIDYO_CLIENT_CLIENTTYPE_A, 
	/*! iOS */
	VIDYO_CLIENT_CLIENTTYPE_I, 
	/*! UNKNOWN - Should not be used and should be kept at the end */
	VIDYO_CLIENT_CLIENTTYPE_UNKNOWN, 
} VidyoClientClientType;

/*! CPU usage status.

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_CPU_USAGE_ACTIONS

	- Passed in field previewMode of following structures:
		+ #VidyoClientOutEventCpuUsageActions
*/

typedef enum VidyoClientCpuUsageStatus_
{
	/*! CPU usage is normal or below high CPU usage threshold */
	VIDYO_CLIENT_NORMAL_CPU_USAGE = 1,
	/*! CPU usage is above high CPU usage threshold */
	VIDYO_CLIENT_HIGH_CPU_USAGE,
} VidyoClientCpuUsageStatus;


/*! Optional portal feature identification.

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_FEATURES

	- Passed in field portal of following structures:
		+ #VidyoClientEventPortalFeatures
*/
typedef enum VidyoClientPortalFeatureNames_
{
	/*! Scheduled room */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_SCHEDULED_ROOM=1,
	/*! Guest */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_GUEST,
	/*! IPC outbound */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_IPC_OUTBOUND,	
	/*! IPC inbound */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_IPC_INBOUND,	
	/*! Moderator URL */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_MEDERATOR_URL,	
	/*!  TLS Tunneling */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_TLS_TUNNELING,	
	/*! Login Banner*/
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_LOGIN_BANNER,	
	/*! Welcome banner */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_WELCOME_BANNER,
	/*! Support for Private Chat*/
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_PRIVATE_CHAT,
	/*! Support for Public or group chat */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_GROUP_CHAT,
	/*! Support for CDR version 2.1*/
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_CDR_VERSION_2_1,
	/*! Support for reporting endpoint details and features supported by endpoint */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_ENDPOINT_DETAILS,
	/*! Support for 16 tiles */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_16_TILES,
	/*! Support for HTML change password */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_HTML_CHANGE_PASSWORD,
	/*! Support for Router participant information */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_ROUTER_PARTICIPANT_INFORMATION,
	/*! Support for Moderated Conference information */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_MODERATED_CONFERENCE,
    /*! Support for Opus Audio */
    VIDYO_CLIENT_PORTAL_FEATURE_NAME_OPUS_AUDIO,
    /*! None - invalid and should be kept at the end */
	VIDYO_CLIENT_PORTAL_FEATURE_NAME_MAX
} VidyoClientPortalFeatureNames;

/*! Identification of setting on conference room.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS
		+ #VIDYO_CLIENT_OUT_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS

	- Passed in field portal of following structures:
		+ #VidyoClientInEventControlConferenceRoomSettings
		+ #VidyoClientOutEventControlConferenceRoomSettings
*/
typedef enum VidyoClientConferenceRoomSettingId_
{
	/*! Lock a conference room, so that no one else can enter/join the conference room */
	VIDYO_CLIENT_LOCK_CONFERENCE_ROOM=1,
	/*! Unlock a conference room, so that any participant can enter/join the conference room */
	VIDYO_CLIENT_UNLOCK_CONFERENCE_ROOM,
} VidyoClientConferenceRoomSettingId;

/*! Type or identification of room.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS
		+ #VIDYO_CLIENT_OUT_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS

	- Passed in field portal of following structures:
		+ #VidyoClientInEventControlConferenceRoomSettings
		+ #VidyoClientOutEventControlConferenceRoomSettings
*/
typedef enum VidyoClientConferenceRoomType_
{
	/*! Users default conference room */
	VIDYO_CLIENT_DEFAULT_CONFERENCE_ROOM=1,
	/*! Conference room on which user has joined now for the conference */
	VIDYO_CLIENT_CURRENT_ACTIVE_CONFERENCE_ROOM,
} VidyoClientConferenceRoomType;

/*! Pre-call device test action identifier.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_CAMERA
		+ #VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_MICROPHONE
		+ #VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE

	- Passed in field portal of following structures:
		+ #VidyoClientInEventPrecallTestCamera
		+ #VidyoClientInEventPrecallTestMicrophone
		+ #VidyoClientOutEventPrecallTestDevice

*/
typedef enum VidyoClientPrecallDeviceTestAction_
{
	/*! Start testing the device */
	VIDYO_CLIENT_DEVICE_TEST_START=1,
	/*! Stop testing the device */
	VIDYO_CLIENT_DEVICE_TEST_STOP,
} VidyoClientPrecallDeviceTestAction;

/*! Result of Pre-call device test.

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE

	- Passed in field result of following structures:
		+ #VidyoClientOutEventPrecallTestDevice
*/
typedef enum VidyoClientPrecallDeviceTestResult_
{
	/*! Requested action is completed successfully */
	VIDYO_CLIENT_DEVICE_TEST_SUCCESS=1,
	/*! Requested action is failed */
	VIDYO_CLIENT_DEVICE_TEST_FAILED,
} VidyoClientPrecallDeviceTestResult;

/*! The conference control action.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS

	- Passed in field action of following structures:
		+ #VidyoClientInEventConferenceControlAllParticipants
*/
typedef enum VidyoClientConferenceControlCommand_
{
	/*! Requested action is drop all participants from the conference */
	VIDYO_CLIENT_DROP_ALL=1,
	/*! Requested action is mute audio of all participants in the conference. This is a server or admin mute and user will not be able to unmute */
	VIDYO_CLIENT_AUDIO_MUTE_SERVER_ALL,
	/*! Requested action is unmute audio of all participants in the conference. This is a server or admin unmute */
	VIDYO_CLIENT_AUDIO_UNMUTE_SERVER_ALL,
	/*! Requested action is mute audio of all participants in the conference. This is a client or user mute and user will be able to unmute */
	VIDYO_CLIENT_AUDIO_MUTE_CLIENT_ALL,
	/*! Requested action is trun on privacy for all participants in the conference. This is a server or admin privacy and user will not be able to trun it off */
	VIDYO_CLIENT_PRIVACY_ON_SERVER_ALL,
	/*! Requested action is trun off privacy of all participants in the conference. This is a server or admin privacy off */
	VIDYO_CLIENT_PRIVACY_OFF_SERVER_ALL,
	/*! Requested action is turn privacy of all participants in the conference. This is a client or user privacy and user will be able to turn it off */
	VIDYO_CLIENT_PRIVACY_ON_CLIENT_ALL,
	/*! Requested action is mute speaker of all participants in the conference. This is a server or admin mute and user will not be able to unmute */
	VIDYO_CLIENT_SPEAKER_MUTE_SERVER_ALL,
	/*! Requested action is unmute speaker of all participants in the conference. This is a server or admin unmute */
	VIDYO_CLIENT_SPEAKER_UNMUTE_SERVER_ALL,
} VidyoClientConferenceControlCommand;

/*! The conference control action.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_PARTICIPANT

	- Passed in field action of following structures:
		+ #VidyoClientInEventConferenceControlParticipant
*/
typedef enum VidyoClientConferenceControlCommandParticipant_
{
	/*! Requested action is drop participant from the conference */
	VIDYO_CLIENT_DROP=1,
	/*! Requested action is mute audio of participant in the conference. This is a server or admin mute and user will not be able to unmute */
	VIDYO_CLIENT_AUDIO_MUTE_SERVER,
	/*! Requested action is unmute audio of participant in the conference. This is a server or admin unmute */
	VIDYO_CLIENT_AUDIO_UNMUTE_SERVER,
	/*! Requested action is mute audio of participant in the conference. This is a client or user mute and user will be able to unmute */
	VIDYO_CLIENT_AUDIO_MUTE_CLIENT,
	/*! Requested action is trun on privacy for participant in the conference. This is a server or admin privacy and user will not be able to trun it off */
	VIDYO_CLIENT_PRIVACY_ON_SERVER,
	/*! Requested action is trun off privacy of participant in the conference. This is a server or admin privacy off */
	VIDYO_CLIENT_PRIVACY_OFF_SERVER,
	/*! Requested action is turn privacy of participant in the conference. This is a client or user privacy and user will be able to turn it off */
	VIDYO_CLIENT_PRIVACY_ON_CLIENT,
	/*! Requested action is mute speaker of participant in the conference. This is a server or admin mute and user will not be able to unmute */
	VIDYO_CLIENT_SPEAKER_MUTE_SERVER,
	/*! Requested action is unmute speaker of participant in the conference. This is a server or admin unmute */
	VIDYO_CLIENT_SPEAKER_UNMUTE_SERVER,
} VidyoClientConferenceControlCommandParticipant;

/*! The type of contents share requested.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_SHARE

	- Passed in field action of following structures:
		+ #VidyoClientInEventShare
*/
typedef enum VidyoClientContentsShareType_
{
	/*! Requested contents share is an application window. */
	VIDYO_CLIENT_CONTENTS_SHARE_TYPE_APPLICATION_WINDOW=1,
	/*! Requested contents share is a desktop/monitor/screen. */
	VIDYO_CLIENT_CONTENTS_SHARE_TYPE_DESKTOP_WINDOW,
} VidyoClientContentsShareType;

/*! Types of source that can be in conference.
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_ADDED
		+ #VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_REMOVED
	- Passed in field sourceType of following structures:
		+ #VidyoClientOutEventRemoteSourceChanged
*/
typedef enum VidyoClientSourceType_
{
	VIDYO_CLIENT_SOURCE_TYPE_VIDEO,          /*!< Video source */
	VIDYO_CLIENT_SOURCE_TYPE_APPLICATION,    /*!< Application (sharing) */
	VIDYO_CLIENT_SOURCE_TYPE_AUDIO,          /*!< Audio source */
	VIDYO_CLIENT_SOURCE_TYPE_UNKNOWN,        /*!< source type is unknown */
} VidyoClientSourceType;


/*! Combined error codes from Curl(TCP), Curl(HTTP), SOAP server returned faults/results and internal SOAP module errors
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_ROOM_LINK
		+ #VIDYO_CLIENT_OUT_EVENT_CLIENT_VERSION_ON_SERVER
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_PREFIX
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE
*/
typedef enum VidyoClientSoapError_
{
	VIDYO_CLIENT_ERROR_NONE = 0, 

	/*!< curl/TCP errors 1-88 */
	VIDYO_CLIENT_ERROR_TCP_UNSUPPORTED_PROTOCOL		=  1,	/*!< CURLE_UNSUPPORTED_PROTOCOL,    */
	VIDYO_CLIENT_ERROR_TCP_FAILED_INIT				=  2,	/*!< CURLE_FAILED_INIT,             */
	VIDYO_CLIENT_ERROR_TCP_URL_MALFORMAT			=  3,	/*!< CURLE_URL_MALFORMAT,           */
	VIDYO_CLIENT_ERROR_TCP_NOT_BUILT_IN				=  4,	/*!< CURLE_NOT_BUILT_IN,  [was obsoleted in August 2007 for 7.17.0, reused in April 2011 for 7.21.5] */
	VIDYO_CLIENT_ERROR_TCP_COULD_NOT_RESOLVE_PROXY	=  5,	/*!< CURLE_COULDNT_RESOLVE_PROXY,    */
	VIDYO_CLIENT_ERROR_TCP_COULD_NOT_RESOLVE_HOST	=  6,	/*!< CURLE_COULDNT_RESOLVE_HOST,     */
	VIDYO_CLIENT_ERROR_TCP_COULD_NOT_CONNECT		=  7,	/*!< CURLE_COULDNT_CONNECT,         */
	VIDYO_CLIENT_ERROR_TCP_FTP_WEIRD_SERVER_REPLY	=  8,	/*!< CURLE_FTP_WEIRD_SERVER_REPLY,   */
	VIDYO_CLIENT_ERROR_TCP_REMOTE_ACCESS_DENIED		=  9,	/*!< CURLE_REMOTE_ACCESS_DENIED, a service was denied by the server due to lack of access - when login fails this is not returned. */
	VIDYO_CLIENT_ERROR_TCP_PARTIAL_FILE				= 18,	/*!< CURLE_PARTIAL_FILE,             */
	VIDYO_CLIENT_ERROR_TCP_HTTP_RETURNED_ERROR		= 22,	/*!< CURLE_HTTP_RETURNED_ERROR,     */
	VIDYO_CLIENT_ERROR_TCP_OUT_OF_MEMORY			= 27,	/*!< CURLE_OUT_OF_MEMORY,            */
	VIDYO_CLIENT_ERROR_TCP_OPERATION_TIMED_OUT		= 28,	/*!< CURLE_OPERATION_TIMEDOUT,       - the timeout time was reached */
	VIDYO_CLIENT_ERROR_TCP_HTTP_POST_ERROR			= 34,	/*!< CURLE_HTTP_POST_ERROR,          */
	VIDYO_CLIENT_ERROR_TCP_SSL_CONNECT_ERROR		= 35,	/*!< CURLE_SSL_CONNECT_ERROR,       - wrong when connecting with SSL */
	VIDYO_CLIENT_ERROR_TCP_FUNCTION_NOT_FOUND		= 41,	/*!< CURLE_FUNCTION_NOT_FOUND,      */
	VIDYO_CLIENT_ERROR_TCP_ABORTED_BY_CALLBACK		= 42,	/*!< CURLE_ABORTED_BY_CALLBACK,     */
	VIDYO_CLIENT_ERROR_TCP_BAD_FUNCTION_ARGUMENT	= 43,	/*!< CURLE_BAD_FUNCTION_ARGUMENT,    */
	VIDYO_CLIENT_ERROR_TCP_INTERFACE_FAILED			= 45,	/*!< CURLE_INTERFACE_FAILED,        45 - CURLOPT_INTERFACE failed */
	VIDYO_CLIENT_ERROR_TCP_TOO_MANY_REDIRECTS		= 47,	/*!< CURLE_TOO_MANY_REDIRECTS ,    - catch endless re-direct loops */
	VIDYO_CLIENT_ERROR_TCP_UNKNOWN_OPTION			= 48,	/*!< CURLE_UNKNOWN_OPTION,          - User specified an unknown option */
	VIDYO_CLIENT_ERROR_TCP_PEER_FAILED_VERIFICATION	= 51,	/*!< CURLE_PEER_FAILED_VERIFICATION,  - peer's certificate or fingerprint wasn't verified fine */
	VIDYO_CLIENT_ERROR_TCP_GOT_NOTHING				= 52,	/*!< CURLE_GOT_NOTHING,              - when this is a specific error */
	VIDYO_CLIENT_ERROR_TCP_SSL_ENGINE_NOT_FOUND		= 53,	/*!< CURLE_SSL_ENGINE_NOTFOUND,    - SSL crypto engine not found */
	VIDYO_CLIENT_ERROR_TCP_SSL_ENGINE_SET_FAILED	= 54,	/*!< CURLE_SSL_ENGINE_SETFAILED,   - can not set SSL crypto engine as default */
	VIDYO_CLIENT_ERROR_TCP_SEND_ERROR				= 55,	/*!< CURLE_SEND_ERROR,              - failed sending network data */
	VIDYO_CLIENT_ERROR_TCP_RECV_ERROR				= 56,	/*!< CURLE_RECV_ERROR,             - failure in receiving network data */
	VIDYO_CLIENT_ERROR_TCP_SSL_CERT_PROBLEM			= 58,	/*!< CURLE_SSL_CERTPROBLEM,       - problem with the local certificate */
	VIDYO_CLIENT_ERROR_TCP_SSL_CIPHER				= 59,	/*!< CURLE_SSL_CIPHER,             - couldn't use specified cipher */
	VIDYO_CLIENT_ERROR_TCP_SSL_CACERT				= 60,	/*!< CURLE_SSL_CACERT,            - problem with the CA cert (path?) */
	VIDYO_CLIENT_ERROR_TCP_BAD_CONTENT_ENCODING		= 61,	/*!< CURLE_BAD_CONTENT_ENCODING,    - Unrecognized/bad encoding */
	VIDYO_CLIENT_ERROR_TCP_FILE_SIZE_EXCEEDED		= 63,	/*!< CURLE_FILESIZE_EXCEEDED,     - Maximum file size exceeded */
	VIDYO_CLIENT_ERROR_TCP_SEND_FAIL_REWIND			= 65,	/*!< CURLE_SEND_FAIL_REWIND,      - Sending the data requires a rewind that failed */
	VIDYO_CLIENT_ERROR_TCP_SSL_ENGINE_INIT_FAILED	= 66,	/*!< CURLE_SSL_ENGINE_INITFAILED,  - failed to initialise ENGINE */
	VIDYO_CLIENT_ERROR_TCP_SSL_SHUTDOWN_FAILED		= 80,	/*!< CURLE_SSL_SHUTDOWN_FAILED,    - Failed to shut down the SSL connection */
	VIDYO_CLIENT_ERROR_TCP_AGAIN					= 81,	/*!< CURLE_AGAIN,                 - socket is not ready for send/recv, wait till it's ready and try again (Added in 7.18.2) */
	VIDYO_CLIENT_ERROR_TCP_SSL_ISSUER_ERROR			= 83,	/*!< CURLE_SSL_ISSUER_ERROR,       - Issuer check failed.  (Added in 7.19.0) */
	VIDYO_CLIENT_ERROR_TCP_CHUNK_FAILED				= 88,	/*!< CURLE_CHUNK_FAILED,            - chunk callback reported error */

	/*!< http errors */
	VIDYO_CLIENT_ERROR_HTTP_200_OK 					= 200,
	VIDYO_CLIENT_ERROR_HTTP_301_REDIRECT 			= 301,
	VIDYO_CLIENT_ERROR_HTTP_302_REDIRECT 			= 302,
	VIDYO_CLIENT_ERROR_HTTP_401_UNAUTHORIZED 		= 401,
	VIDYO_CLIENT_ERROR_HTTP_404_NOT_IMPLEMENTED 	= 404,
	VIDYO_CLIENT_ERROR_HTTP_407_PROXY_AUTHENTICATION_REQUIRED = 407,
	VIDYO_CLIENT_ERROR_HTTP_408_TIMED_OUT			= 408,
	VIDYO_CLIENT_ERROR_HTTP_500_SERVER_ERROR		= 500,
	VIDYO_CLIENT_ERROR_HTTP_501_NOT_IMPLEMENTED 	= 501,
	
	/*!< SOAP faults/results */
	VIDYO_CLIENT_ERROR_SOAP_SUCCESS 				= 1000,		/*!< Result is success */
	VIDYO_CLIENT_ERROR_SOAP_FAILURE,							/*!< Result is some unknown general failure */
	VIDYO_CLIENT_ERROR_SOAP_NOT_LICENSED,						/*!< Not licensed */
	VIDYO_CLIENT_ERROR_SOAP_SEAT_LICENSE_EXPIRED,				/*!< Seat license expired */
	VIDYO_CLIENT_ERROR_SOAP_WRONG_PIN,							/*!< Wrong PIN */
	VIDYO_CLIENT_ERROR_SOAP_CONFERENCE_LOCKED,					/*!< Conference locked */
	VIDYO_CLIENT_ERROR_SOAP_ROOM_DISABLED,						/*!< Room disabled */
	VIDYO_CLIENT_ERROR_SOAP_GENERAL_FAULT,						/*!< General Fault */
	VIDYO_CLIENT_ERROR_SOAP_INVALID_ARGUMENT_FAULT,				/*!< Invalid argument fault */
	VIDYO_CLIENT_ERROR_SOAP_MEMBER_NOT_ONLINE,					/*!< Status of member is not online */
	VIDYO_CLIENT_ERROR_SOAP_NOT_OWNER_OF_ROOM,					/*!< Not owner of room */
	VIDYO_CLIENT_ERROR_SOAP_USER_NOT_FOUND,						/*!< Specified user is not found */
	VIDYO_CLIENT_ERROR_SOAP_UNEXPECTED_SUBELEMENT_IN_MESSAGE,	/*!< Unexpected subelement in SOAP message */
	VIDYO_CLIENT_ERROR_SOAP_END_POINT_NOT_FOUND,				/*!< Endpoint not found */
	VIDYO_CLIENT_ERROR_SOAP_FAILED_PLACE_DIRECT_CALL,			/*!< Fialed to place call */
	VIDYO_CLIENT_ERROR_SOAP_IPC_JOIN_FAILURE,					/*!< Failure to join room on other portal */
	VIDYO_CLIENT_ERROR_SOAP_ALL_LINES_IN_USE,					/*!< All lines are in use */
	VIDYO_CLIENT_ERROR_SOAP_RESOURCE_NOT_AVAILABLE,				/*!< Resource Not available */
	VIDYO_CLIENT_ERROR_SOAP_RESULT_ACCESS_RESTRICTED,			/*!< Access restricted */
	VIDYO_CLIENT_ERROR_SOAP_RESULT_USER_NOT_BOUND,				/*!< User is not bond to endpoint */
	VIDYO_CLIENT_ERROR_SOAP_CANNOT_JOIN_GUEST,					/*!< Failed to join as guest */
	VIDYO_CLIENT_ERROR_SOAP_ROOM_IS_FULL,						/*!< Room trying to join is already full */
	VIDYO_CLIENT_ERROR_SOAP_PORTAL_PREFIX_NOT_CONFIGURED,		/*!< Portal prefix is not configured */
	VIDYO_CLIENT_ERROR_SOAP_CONTROL_MEETING_FAILED,				/*!< Control meeting failed */	
	VIDYO_CLIENT_ERROR_INVALID_EXTENSION,						/*!< Invalid extension */	
	VIDYO_CLIENT_ERROR_INVALID_PARAMETERS,						/*!< Invalid Paramaters */
	VIDYO_CLIENT_ERROR_INVALID_ROOM,							/*!< Invalid room */

	/*!< internal errors */
	VIDYO_CLIENT_ERROR_INTERNAL_REQUEST 			= 2000,
	VIDYO_CLIENT_ERROR_INTERNAL_RESPONSE,
	VIDYO_CLIENT_ERROR_INTERNAL_COULD_NOT_LINK,
	VIDYO_CLIENT_ERROR_INTERNAL_LOGIN_CANCELED,
	VIDYO_CLIENT_ERROR_INTERNAL_LOGIN_OLD_SERVER,
	VIDYO_CLIENT_ERROR_INTERNAL_CURL_INIT,
	VIDYO_CLIENT_ERROR_INTERNAL_NO_PORTAL_ADDRESS, 
	VIDYO_CLIENT_ERROR_INTERNAL_WRONG_STATE, 
	
	/*!< USER_MESSAGES will be here	 */
	
	VIDYO_CLIENT_ERROR_UNKNOWN = 0xFFFF,
} VidyoClientError;
/*******************************************************************************
 Parameter structures for events from GUI to Vidyo Client Library
*******************************************************************************/

/*! Sign in event.

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_SIGN_IN
*/
typedef struct VidyoClientInEventSignIn_
{
	char serverAddress[SIGNIN_SERVERADDRESS_SIZE];
	/*!< Hostname or IP address of VidyoManager to be used */
	char serverPort[SIGNIN_SERVERPORT_SIZE];
	/*!< Port of VidyoManager to be used. */
	char userName[SIGNIN_USERNAME_SIZE];
	/*!< Username to sign in with, as known to VidyoPortal.  Encoded as UTF-8. */
	char portalAccessKey[SIGNIN_PORTAL_ACCESS_KEY_SIZE];
	/*!< Key allocated by VidyoPortal to be used in place of password.  This value should be acquired through login procedure with VidyoPortal. */
	char portalAddress[SIGNIN_PORTALADDRESS_SIZE];
	/*!< Base URL for accessing SOAP services on the VidyoPortal
		 (e.g. http://example.vidyo.com/services). */
	char portalVersion[SIGNIN_PORTALVERSION_SIZE];
	/*!< Portal version */
	char vmIdentity[VIDYO_MANAGER_ID_SIZE];
	/*!<
		Identity of Vidyo Manager to which end point is assigned. This value should be
		acquired through login procedure with VidyoPortal. This is required for vidyo
		router cascading feature.
	*/
	char locationTag[ENDPOINT_LOCATION_TAG_SIZE];
	/*!<
		Location tag of end point. This is configured on portal to indicate the location of
		an endpoint. It is used to assign end point nearest and lowest loaded vidyo router
		when joining a call. This value should be acquired through login procedure with VidyoPortal.
	*/
	char clientExternalIPAddress[MAX_IPADDRESS_LEN];
	/*!< External IP address of machine on which client is running as seen by web server. */
	VidyoClientProxyType proxyType;
	/*!<
		The type of Proxy available to the client.
		If value is #VIDYO_CLIENT_VIDYO_PROXY #vidyoProxyAddress should have valid proxy address
		and #vidyoProxyPort should have valid proxy port. Instead if value is #VIDYO_CLIENT_REVERSE_PROXY
		#reverseProxyAddress should have valid proxy address and #reverseProxyPort should have valid proxy port.
		In both cases #numberProxies will provide the number of proxies available to client.
	*/
	char vidyoProxyAddress[SIGNIN_VIDYO_PROXY_NUMBER][SIGNIN_VIDYO_PROXY_ADDRESS_SIZE];
	/*!<
		Array of VidyoProxy hostnames or IP addresses.  Only 0 or 1 VidyoProxy addresses
		are currently supported.
	*/
	char vidyoProxyPort[SIGNIN_VIDYO_PROXY_NUMBER][SIGNIN_VIDYO_PROXY_PORT_SIZE];
	/*!<
		Array of VidyoProxy ports.  Only 0 or 1 VidyoProxy addresses are currently supported.
		Each port is used with corresponding value found in the same index of preceding
		parameter vidyoProxyAddress.
	*/
	char reverseProxyAddress[SIGNIN_VIDYO_PROXY_NUMBER][SIGNIN_VIDYO_PROXY_ADDRESS_SIZE];
	/*!<
		Array of ReverseProxy hostnames or IP addresses.  Only 0 or 1 ReverseProxy addresses
		are currently supported.
	*/
	char reverseProxyPort[SIGNIN_VIDYO_PROXY_NUMBER][SIGNIN_VIDYO_PROXY_PORT_SIZE];
	/*!<
		Array of ReverseProxy ports.  Only 0 or 1 ReverseProxy addresses are currently supported.
		Each port is used with corresponding value found in the same index of preceding
		parameter reverseProxyAddress.
	*/
	char passphrase[MAX_PASSPHRASE_SIZE]; 	
	/*!< Passphrase for the user - this can have an expiration */

	char externalAccessToken[MAX_EXTERNAL_ACCESS_TOKEN_SIZE]; 	
	/*!< Token used for communicating with external servers */

	VidyoUint numberProxies;
	/*!<
		Number of entries in parameters vidyoProxyAddress and vidyoProxyPort. This value
		should currently be set to only 0 or 1.
	*/
	VidyoUint emcpSecured;
	/*!<
		VIDYO_TRUE if connection to VidyoManager should be secured using TLS,
		VIDYO_FALSE if connection to VidyoManager should not be secure.
	*/
	VidyoBool guestLogin;
	/*!<
		VIDYO_TRUE if username given in preceding parameter userName is ephemeral
		value allocated for guest login, VIDYO_FALSE for permanent users.
	*/
	VidyoBool showDialpad;
	/*!<
		Reserved for use by standard Vidyo clients.  Should be set to VIDYO_FALSE.
	*/
	VidyoBool showStartmeeting;
	/*!<
		Reserved for use by standard Vidyo clients.  Should be set to VIDYO_FALSE.
	*/
	VidyoUint guestId;
	/*!<
		if guestLogin is true - this value has the guest Id

	*/
	VidyoClientClientType clientType;
	/*! Type of the client */
	char cookie[SIGNIN_MAX_COOKIE_SIZE];
	/*!<
		Used by some endpoints to facilitate external login. Ensure clientType set when using this
	*/
} VidyoClientInEventSignIn;


/*! Represents input event structure for preview mode
	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PREVIEW
		+ #VIDYO_CLIENT_REQUEST_GET_PREVIEW_MODE
@see #VidyoClientPreviewMode

*/
typedef struct VidyoClientInEventPreview_
{
	/*! How video will be shown in video layout */
	VidyoClientPreviewMode previewMode;
	VidyoBool primaryDisplay; /*!< For internal use */
} VidyoClientInEventPreview;

/*! Mute structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN
		+ #VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_OUT
		+ #VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO
*/
typedef struct VidyoClientInEventMute_
{
	/*! VIDYO_TRUE to mute local media device for specified in event, VIDYO_FALSE to un-mute.
		Use #VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN to (un-)mute the microphone device,
		#VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_OUT to (un-)mute the speaker device,
		and #VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO to (un-)mute the camera device.
	*/
	VidyoBool willMute;
} VidyoClientInEventMute;

/*! VidyoClientInEventShowSelfViewWhileJoining structure
 
 - Used by VIDYO_CLIENT_IN_EVENT_SHOW_SELFVIEW_WHILE_JOINING
 */
typedef struct VidyoClientInEventShowSelfViewWhileJoining_
{
    /*! VIDYO_TRUE to show selfview while joining, VIDYO_FALSE to dont show selfview while joining.
     */
    VidyoBool showSelfViewWhileJoining;
} VidyoClientInEventShowSelfViewWhileJoining;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SHARE
*/
typedef struct VidyoClientInEventShare_
{
	/*!
		Indicates what is requested as contents share (application window or screen?).
	*/
	VidyoClientContentsShareType shareType;
	/*!
		OS-specific window ID of local application window to share with remote participants in
		a conference.  See VidyoTypes.h for definition of VidyoWindowCapturerWindowId for
		particular platform.
     
        window should not be set to 0 when requesting to share. If desktop share is requested
        and there is no valid value for window please set this to 1.
	*/
	VidyoWindowCapturerWindowId window;
    /*!
     If the value of shareType is VIDYO_CLIENT_CONTENTS_SHARE_TYPE_DESKTOP_WINDOW the requested
     desktop id should be provided in the field desktopId. This value should be one of the value in field sysDesktopId in
     #VidyoClientRequestGetWindowsAndDesktops. No other values are accepted.
     */
    char desktopId[VIDYO_CLIENT_SCREEN_ID_SIZE];
	VidyoRect windowSize;  /*!< Geometry of subregion of window to share.  @note not yet supported. */
} VidyoClientInEventShare;


/*! Color structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_BACKGROUND_COLOR
*/
typedef struct VidyoClientInEventColor_
{
	/*!
		Color parameter
	*/
	VidyoColor color;
} VidyoClientInEventColor;



/*! Event structure

	- Used by the following in events:
		 + #VIDYO_CLIENT_IN_EVENT_SEND_FRAME to send a share frame

	@note Replaces the less generic VidyoClientInEventRawFrame. May be used for out events as well.
*/
typedef struct VidyoClientInEventVideoFrame_
{
	/*!
		Width of shared frame
	*/
	VidyoUint width;
	/*!
		Height of shared frame
	*/
	VidyoUint height;
	/*!
		The fourcc code of the frame format. Default value is ARGB. Other values supported are I420 & YUV12.
		e.g. To encode ARGB, the 1st 8 bits should be 'A', 2nd 8 bits should be 'R', 3rd 8 bits should be 'G'
		and the last (most significant) 8 bits should be 'B'.
	*/
	VidyoUint format;
	/*!
		The size of the data buffer holding the frame
	*/
	VidyoUint size;
	/*!
		Frame data start. Frame data must be contiguous in memory so that it can be passed to VidyoClientSendEvent
		@note Do not add structure members below
		@note When calling VidyoClientSendEvent set event data size to sizeof(VidyoClientInEventVideoFrame)+VidyoClientInEventVideoFrame.size
	*/
	VidyoUint8 data[1];
} VidyoClientInEventVideoFrame;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_RESIZE
*/
typedef struct VidyoClientInEventResize_
{
	VidyoUint x;                /*!< Horizontal offset of the topmost left corner of video layout region on
									 all platforms except MacOS X. It is lowermost left corner on Mac OS X. */
	VidyoUint y;                /*!< Vertical offset of the topmost left corner of video layout region.
									 all platforms except MacOS X. It is lowermost left corner on Mac OS X. */
	VidyoUint width;            /*!< Width of video layout region.  Range of allowed values 0~UINT_MAX. */
	VidyoUint height;           /*!< Height of video layout region.  Range of allowed values 0~UINT_MAX.*/
} VidyoClientInEventResize;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PARTICIPANTS_LIMIT
*/
typedef struct VidyoClientInEventParticipantsLimit_
{
	/*!
		Maximum number of viewable remote participants in video layout.  A value of 0
		causes no remote participants (not even a loopback of own video via server) to
		be shown.  A value of 1 causes only one remote participant (including loopback
		of own video, if applicable) to be shown.  A value of 2~8 causes a maximum of
		the specified number of remote participants (including loopback of own video,
		if applicable) to be shown.  A value of 16 causes the system to automatically
		regulate the maximum number of remote participants that can be shown.  Range of
		allowed values 0~8 and 16.

		@note Mobile devices may be limited
	*/
	VidyoUint maxNumParticipants;
} VidyoClientInEventParticipantsLimit;

/*! Event structure
 
 - Used by following in events:
 + #VIDYO_CLIENT_IN_EVENT_SET_MIN_PARTICIPANTS_LIMIT
 */
typedef struct VidyoClientInEventSetMinParticipantsLimit_
{
    VidyoUint minNumParticipants;
} VidyoClientInEventSetMinParticipantsLimit;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_LAYOUT
*/
typedef struct VidyoClientInEventLayout_
{
	/*!
		Number of remote participants to be shown in a larger size region within video
		layout.  A value of 0 causes all remote participants to be shown in equal size
		regions.  A value of 1 causes one remote participant (selected by virtue of having
		been last loudest speaker), the so-called "preferred" participant, to be shown in
		a larger size region than any other participants within video layout.  Range of
		allowed values 0~1.
	*/
	VidyoUint numPreferred;
} VidyoClientInEventLayout;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PLAY_SOUND
		+ #VIDYO_CLIENT_IN_EVENT_PLAY_RINGTONE
		+ #VIDYO_CLIENT_IN_EVENT_PLAY_CALLING_TONE
*/
typedef struct VidyoClientInEventPlaySound_
{
	/*!
		Pointer to a buffer of sound data.  Required encoding of sound data 1-channel,
		16 bits per sample and 16000 samples per second.
	*/
	VidyoUint8 *soundData;
} VidyoClientInEventPlaySound;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_ECHO_DETECT
		+ #VIDYO_CLIENT_IN_EVENT_SET_ECHO_CANCEL
		+ #VIDYO_CLIENT_IN_EVENT_SET_AUDIO_AGC
		+ #VIDYO_CLIENT_IN_EVENT_SET_FREEZE_IMAGE
*/
typedef struct VidyoClientInEventSetFlag_
{
	/*!
		VIDYO_TRUE to set flag corresponding to specified event, VIDYO_FALSE to clear flag.
		Use VIDYO_CLIENT_IN_EVENT_SET_ECHO_DETECT to enable/disable acoustic echo detection,
		VIDYO_CLIENT_IN_EVENT_SET_ECHO_CANCEL to enable/disable acoustic echo cancellation,
		VIDYO_CLIENT_IN_EVENT_SET_AUDIO_AGC to enable/disable automatic gain control,
		and VIDYO_CLIENT_IN_EVENT_SET_FREEZE_IMAGE to enable/disable freezing of video image.
	*/
	VidyoBool willEnable;
} VidyoClientInEventSetFlag;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_ORIENTATION
*/
typedef struct VidyoClientInEventSetOrientation_
{
	/*!
		Orientation of own video and/or video layout to set.
		Typically, this value tracks where the camera is located on the device relative to
		the normal orientation of the device. Devices that have the camera located at the
		top will 'usually' have an orientation of VIDYO_CLIENT_ORIENTATION_UP.  Not all
		devices adhere to this scheme and will require some experimentation to get the
		correct value for this parameter.
	*/
	VidyoClientOrientation orientation;
	/*! Which aspects of conference (own video, video layout, both) to set orientation for. */
	VidyoClientOrientationControl control;
} VidyoClientInEventSetOrientation;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PLAY_DIAL_TONE
*/
typedef struct VidyoClientInEventPlayDialTone_
{
	/*! Dial tone to play.  Range of allowed values 0~9, *, #, A, B, C, D. */
	char tone;
	/*! Duration of dial tone, in milliseconds.  Range of allowed values 0~INT_MAX. */
	VidyoInt duration;
} VidyoClientInEventPlayDialTone;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_START_PLAYING_CONTINUOUS_DIAL_TONE
*/
typedef struct VidyoClientInEventPlayContinuousDialTone_
{
	/*! Dial tone to play.  Range of allowed values 0~9, *, #, A, B, C, D. */
	char tone;
} VidyoClientInEventPlayContinuousDialTone;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA
*/
typedef struct VidyoClientInEventControlCamera_
{
	/*! Vidyo URI of remote participant to control camera of. */
	char uri[URI_LEN];
	/*! Type of camera control operation.  See definition of VidyoClientCameraControlCommand. */
	VidyoClientCameraControlCommand cameraCommand;
	/*! ID for VISCA pass-through command */
	char commandId[MAX_VISCA_COMMAND];
	/*! Data for VISCA pass-through command in hex, e.g. "81 09 06 12 ff". */
	char commandData[MAX_VISCA_COMMAND];
	/*! Preset parameter. */
	unsigned char preset;
} VidyoClientInEventControlCamera;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_PARTICIPANT_VIDEO_MODE
*/
typedef struct VidyoClientInEventSetParticipantVideoMode_
{
	/*! The action type/purpose for which remote participant's video mode is changed. */
	VidyoClientActionType actionType;

	/*! Vidyo URI of remote participant to set video mode for. */
	char uri[URI_LEN];
	/*! Video mode of remote participant.  See definition of VidyoClientParticipantVideoMode. */
	VidyoClientParticipantVideoMode videoMode;
} VidyoClientInEventSetParticipantVideoMode;

/*!  Structure for internal use

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_MONITORS
*/
typedef struct VidyoClientInEventSetMonitors_
{
	VidyoUint numMonitors;  /*!< Number of displays to use, 1 or 2 */
	VidyoUint seqMon[2];    /*!< 
								If 2 displays set order:
								- 0 for the primary monitor
								- 1 for the secondary monitor 
								*/
} VidyoClientInEventSetMonitors;

/*!  Structure for internal use

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH
*/
typedef struct VidyoClientInEventSetSendBandwidth_
{
	VidyoInt sendBandwidth;  /*!< Maximum send bandwidth:
								7 - 768Kbps,  1 - 1Mbps, 2 - 2Mbps, 3 - 3Mbps,
								4 - 4Mbps, 6 - 6Mbps */
	VidyoUint sLayers;       /* 1 - 3 */
} VidyoClientInEventSetSendBandwidth;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_LOGIN
*/
typedef struct VidyoClientInEventLogIn_
{
	/*! Portal URI, i.e. "https://example.vidyo.com" */
	char portalUri[URI_LEN];
	/*! Name of the registered user on portal */
	char userName[USERID_SIZE];
	/*! Password of the user */
	char userPass[PASSWORD_SIZE];
	/*! Type of the client */
	VidyoClientClientType clientType;
} VidyoClientInEventLogIn;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_ROOM_LINK
 */
typedef struct VidyoClientInEventRoomLink_
{
	/*! Portal URI, i.e. https://example.vidyo.com */
	char portalUri[URI_LEN];
	/*! Room Key -- value of parameter "key=" of Room Link */
	char roomKey[ROOMKEY_SIZE];
	/*! Display Name for Guest only */
	char displayName[USERID_SIZE];
	/*! Conference PIN if needed */
	char pin[PIN_SIZE];
	/*! Type of the client */
	VidyoClientClientType clientType;
	/*! Reference number - optional */
	char referenceNumber[VIDYO_CLIENT_REFERENCE_NUMBER_LEN];
	/*! Join the conference with camera muted */
	VidyoBool muteCamera;
	/*! Join the conference with microphone muted */
	VidyoBool muteMicrophone;
	/*! Join the conference with speaker muted */
	VidyoBool muteSpeaker;
} VidyoClientInEventRoomLink;


/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_ROOM_LINK_EX
 */
typedef struct VidyoClientInEventRoomLinkEx_
{
	/*! Portal URI, i.e. https://example.vidyo.com */
	char portalUri[URI_LEN];
	/*! Room Key -- value of parameter "key=" of Room Link */
	char roomKey[ROOMKEY_SIZE];
	/*! Display Name for Guest only */
	char displayName[USERID_SIZE];
	/*! Conference PIN if needed */
	char pin[PIN_SIZE];
	/*! Type of the client */
	VidyoClientClientType clientType;
	/*! Reference number - optional */
	char referenceNumber[VIDYO_CLIENT_REFERENCE_NUMBER_LEN];
	/*! Join the conference with camera muted */
	VidyoBool muteCamera;
	/*! Join the conference with microphone muted */
	VidyoBool muteMicrophone;
	/*! Join the conference with speaker muted */
	VidyoBool muteSpeaker;
	/*!
		Location tag that the endpoint wants. This is configured on portal to indicate the
		location of an endpoint and is used to assign a VidyoRouter group to the endpoint
		when joining a call.
	*/
	char locationTag[ENDPOINT_LOCATION_TAG_SIZE];
} VidyoClientInEventRoomLinkEx;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_CLIENT_VERSION_ON_SERVER
 */
typedef struct VidyoClientInEventClientVersionOnServer_
{
	/*! Portal URI, i.e. https://example.vidyo.com */
	char portalUri[URI_LEN];
	/*! Type of the client */
	VidyoClientClientType clientType;
	/*! Request initiated by user */
	VidyoBool userInitiated;
} VidyoClientInEventClientVersionOnServer;


/*! Event structure
	
	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_OFFLINE
*/
typedef struct VidyoClientInEventSetOffline_
{
	/*!
		VIDYO_TRUE to disconnect communication with conference manager and go offline,
		ending any active conference.
		VIDYO_FALSE to establish communication with conference manager and go online.
	*/
	VidyoBool offline;
} VidyoClientInEventSetOffline;

/*! States of Telephone call
	- sent with event
		+ #VIDYO_CLIENT_IN_EVENT_TELEPHONE_CALL
*/
typedef enum VidyoClientTelephoneCallState_
{
	VIDYO_CLIENT_TELEPHONE_CALL_NONE = 0,       /*!< Initial state */
	VIDYO_CLIENT_TELEPHONE_CALL_DIALING,        /*!< Dialing */
	VIDYO_CLIENT_TELEPHONE_CALL_INCOMING,       /*!< Incoming call */
	VIDYO_CLIENT_TELEPHONE_CALL_CONNECTED,      /*!< Call connected */
	VIDYO_CLIENT_TELEPHONE_CALL_DISCONNECTED,   /*!< Call disconnected */
} VidyoClientTelephoneCallState;

/*! Event structure
	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_TELEPHONE_CALL
*/
typedef struct VidyoClientInEventTelephoneCall_
{
	VidyoClientTelephoneCallState state;
} VidyoClientInEventTelephoneCall;

/*! Event structure
    - Used by following in events:
        + #VIDYO_CLIENT_IN_EVENT_SET_FONT_FILE
 */
typedef struct VidyoClientInEventSetFontFile_
{
	/*! path name for the systm font file in UTF8. */
    char fontFileName[MAX_FONT_PATH_SIZE];
} VidyoClientInEventSetFontFile;

/*! Event structure
	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_RAW_FRAME

	@note Use #VidyoClientInEventVideoFrame with #VIDYO_CLIENT_IN_EVENT_SEND_FRAME instead
*/
typedef struct VidyoClientInEventRawFrame_
{
	/*! Width of video frame.  Range of allowed values 0~INT_MAX. */
	VidyoInt width;
	/*! Height of video frame.  Range of allowed values 0~INT_MAX. */
	VidyoInt height;
	/*! Buffer containing a raw RGB frame. */
	VidyoUint8 samples[1];
} VidyoClientInEventRawFrame;

/*! Event structure
	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_NETWORK_INTERFACE
*/
typedef struct VidyoClientInEventSetNetworkInterface_
{
	/*! Name of the network interface */
	char name[MAX_INTERFACE_LENGTH];
} VidyoClientInEventSetNetworkInterface;

/*! Event structure
	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_ENABLE_STATUS_BAR
		+ #VIDYO_CLIENT_IN_EVENT_ENABLE_BUTTON_BAR
*/
typedef struct VidyoClientInEventEnable_
{
	/*!
		- VIDYO_TRUE to enable setting for specified in event,
		- VIDYO_FALSE to disable.
	*/
	VidyoBool willEnable;
} VidyoClientInEventEnable;

/*! Event structure
	- Used by following in event:
		+ #VIDYO_CLIENT_IN_EVENT_RENDERER_SHOW_ICON
*/
typedef struct VidyoClientInEventRendererShowIcon_
{
	/*!
		- #VIDYO_CLIENT_RENDERER_ICON_WEBCASTING to specify the Webcasting icon.
		- #VIDYO_CLIENT_RENDERER_ICON_RECORDING to specify as the Recording icon.
	*/
	VidyoClientRendererIcon rendererIcon;
	/*!
		- VIDYO_TRUE to enable showing this icon by the renderer
		- VIDYO_FALSE to disable.
	*/
	VidyoBool setVisible;
} VidyoClientInEventRendererShowIcon;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_GROUP_CHAT
*/
typedef struct VidyoClientInEventGroupChat_
{
	/*! Message (contents) to be sent to all remote participants */
	char message[MAX_CHAT_MESSAGE_LEN];
} VidyoClientInEventGroupChat;


/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PRIVATE_CHAT
*/
typedef struct VidyoClientInEventPrivateChat_
{
	/*! Vidyo URI of remote participant to whom this text message to be sent. */
	char uri[URI_LEN];
	/*! Message (contents) to be sent. */
	char message[MAX_CHAT_MESSAGE_LEN];
} VidyoClientInEventPrivateChat;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_DISPLAY_NAME
*/
typedef struct VidyoClientInEventSetDisplayName_
{
	/*! Vidyo URI of remote participant whose display name has to be changed. */
	char uri[MAX_URI_LEN];
	/*! Display name in UTF8 encoded string which will be set to the participant. */
	char displayName[USERID_SIZE];
} VidyoClientInEventSetDisplayName;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_RESET_DISPLAY_NAME
*/
typedef struct VidyoClientInEventResetDisplayName_
{
	/*! Vidyo URI of remote participant whose display name has to be reverted to the default participant name. */
	char uri[MAX_URI_LEN];
} VidyoClientInEventResetDisplayName;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_LECTURE_CLEAR_RAISE_HAND
*/
typedef struct VidyoClientInEventLectureClearRaiseHand_
{
	/*! whether current participant wants to raise or clear raised hand */
	VidyoBool raise;
} VidyoClientInEventLectureClearRaiseHand;

/*! Event structure

	- Used by following in events to identify the source to start/stop watching:
		+ #VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE
		+ #VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE
*/
typedef struct VidyoClientMediaSource_
{
	/*! URI of participant to watch. */
	char participantURI[MAX_URI_LEN]; 
	/*! Uideo or application share of participant. */
	VidyoClientMediaControlType mediaType;
	/*! Used if more than one media source of a given type (typically 0). When source ID is 0, the first stream of the given media type is selected. */
	VidyoUint sourceId;
} VidyoClientMediaSource;

/*! Event structure used to start receving source frames.
   The video frames from participants being watched are send to application 
   using VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE
*/
typedef struct VidyoClientInEventStartWatchVideoSource_
{
	/*! Identify the source to start watching */
    VidyoClientMediaSource source;
	/*! Width of resolution desired when receiving video or application share */
	VidyoUint width; 
	/*! Height of resolution desired when receiving video or application share */
	VidyoUint height;
	/*! Frame-rate desired when receiving video or application share */
	VidyoUint frameRate; 
	/*! Limit on rate of frames to be delivered to application - minimal interval in ms */
	VidyoUint minFrameInterval;
	/*! Application data to be reflected in out event for frames received  */
	void* watchData; 
} VidyoClientInEventStartWatchVideoSource;


/*! Event structure used to stop receving source frames

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE
*/
typedef struct VidyoClientInEventStopWatchVideoSource_
{
	/*! Identify the source to start watching */
    VidyoClientMediaSource source;
} VidyoClientInEventStopWatchVideoSource;


/*! Event structure

	- Used by following in events to identify the number of source/s to watch dynamically:
		+ #VIDYO_CLIENT_IN_EVENT_SET_DYNAMIC_WATCH_VIDEO_SOURCE
*/
typedef struct VidyoClientDynamicWatchView_
{
	/*! Width of window on which this participant is viewed. */
	VidyoUint width;
	/*! Height of window on which this participant is viewed. */
	VidyoUint height;
 	/*! Max Frame rate expected for this participant. This is provided as an upper
	bound and the library will not deliver frames at a rate exceeding the provided frame-rate (in FPS)*/
	VidyoUint maxFrameRate;
} VidyoClientDynamicWatchView;

/*! Event structure used to get desired resolution and frame rate of the particiant being viewed dynamically.
	In dynamic switching the application provides a list of remote participants/source the VidyoClient library 
	assigns with dynamic selected participants based on loudest speaker. The non-zero height and width is
	mandatory for each dynamically watched participants. To stop dynamic watch set the numParticipants to zero.
	The video frames from participants being watched are send to application using #VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_DYNAMIC_WATCH_VIDEO_SOURCE
*/

typedef struct VidyoClientInEventSetDynamicWatchVideoSource_
{
	/*! Number of participants to be viewed. */
	VidyoUint numParticipants;
	VidyoClientDynamicWatchView dynamicViews[VIDYO_CLIENT_MAX_DYNAMIC_VIEWS];
} VidyoClientInEventSetDynamicWatchVideoSource;

/*! Event structure used to make the rendering visible or hidden.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SET_RENDERER_VISIBLE
*/

typedef struct VidyoClientInEventSetRendererVisible_
{
	/*! VIDYO_TRUE to make rendering windows visible and VIDYO_FALSE to hide. */
	VidyoBool visible;
} VidyoClientInEventSetRendererVisible;


/*! Event structure used to start start audio acquisition in application.
    The audio frames from participants being watched/aquired are send to 
	application using #VIDYO_CLIENT_OUT_EVENT_AUDIO_FRAME_RECEIVED.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_START_ACQUIRE_AUDIO
*/
typedef struct VidyoClientInEventStartAcquireAudio_
{
	/*! Number of selected participant audio to receive. */
    VidyoUint maxAudioStreams;
} VidyoClientInEventStartAcquireAudio;


/*! Event structure used to open a channel for sending video.
    Once channel is open video frames can be sent by using VIDYO_CLIENT_IN_EVENT_SEND_VIDEO_FRAME

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_START_VIDEO_SEND
*/
typedef struct VidyoClientInEventStartVideoSend_
{
	/*! Expected frame width */
    VidyoUint width;
	/*! Expected frame height */
    VidyoUint height;
	/*! Expected frame-rate */
    VidyoUint frameRate;
} VidyoClientInEventStartVideoSend;

/*! Event structure used to open a channel for sending audio.
    Once channel is open audio frames can be sent by using VIDYO_CLIENT_IN_EVENT_SEND_AUDIO_FRAME

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_START_AUDIO_SEND
*/
typedef struct VidyoClientInEventStartAudioSend_
{
	/*! bit-per-sample for audio frames (typically 16) */
    VidyoUint bps;
	/*! audio sampling-rate */
    VidyoUint samplingRate;
 	/*! frame duration in ms (e.g. 20 or 40 ms) */
   VidyoUint frameDuration;	
} VidyoClientInEventStartAudioSend;

/*! Event structure used to send an audio frame once channel to send audio frames is open.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_SEND_AUDIO_FRAME
*/
typedef struct VidyoClientAudioFrame_
{
 	/*! For received audio frames - calculated energy in Db (-96..-1) */
    VidyoInt energy;		
 	/*! bits per sample (typically 16) */
    VidyoUint bps;          
	/*! audio sampling-rate */
	VidyoUint samplingRate; 
	/*! currently 1 */
	VidyoUint channels;     
	/*! number of samples (at 32Khz would be set to 640 for 20 ms) */
	VidyoUint samples;      
	/*! size of data is depth*nSamples*channels/8 */
	VidyoUint8 data[1];   
} VidyoClientAudioFrame;

/*! Event structure used to control conference room settings.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS
*/
typedef struct VidyoClientInEventControlConferenceRoomSettings_
{
	/*! Request identification. This identification will be send back in response. */
    VidyoUint requestId;
	/*! Type of room or room identification on which the room setting has to be applied */
    VidyoClientConferenceRoomType roomType;
	/*! The setting change identification to be applied */
    VidyoClientConferenceRoomSettingId roomSettingId;
	/*! Conference Moderator PIN if needed */
	char moderatorPin[PIN_SIZE];
} VidyoClientInEventControlConferenceRoomSettings;

/*! Event structure used to start or stop self-view in pre-call or test selected camera in pre-call.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_CAMERA
*/
typedef struct VidyoClientInEventPrecallTestCamera_
{
	/*! The device test action requested. */
    VidyoClientPrecallDeviceTestAction action;
} VidyoClientInEventPrecallTestCamera;

/*! Event structure used to start or stop microphone in pre-call or test selected microphone in pre-call.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_MICROPHONE
*/
typedef struct VidyoClientInEventPrecallTestMicrophone_
{
	/*! The device test action requested. */
    VidyoClientPrecallDeviceTestAction action;
} VidyoClientInEventPrecallTestMicrophone;

/*! Event structure used to start speaker test in pre-call.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_START_PRECALL_TEST_SPEAKER
*/
typedef struct VidyoClientInEventStartPrecallTestSpeaker_
{
	/*!
		Pointer to a buffer of sound data.  Required encoding of sound data 1-channel,
		16 bits per sample and 16000 samples per second.
	*/
	VidyoUint8 *soundData;
} VidyoClientInEventStartPrecallTestSpeaker;

/*! Event structure used to control conference that affect all participants of a conference.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS
*/
typedef struct VidyoClientInEventConferenceControlAllParticipants_
{
	/*! Request identification. This identification provided by application in VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS will be returned in corresponding response */
    VidyoUint requestId;
	/*! The conference control command requested. */
    VidyoClientConferenceControlCommand controlCommand;
	/*! Conference Moderator PIN if needed. This is needed only if the user do not have privillege to do control meeting on this conference room.
	    If moderatorPin is not provided, it has to be a null string. */
	char moderatorPin[PIN_SIZE];
	/*! Conference ID, it has to be a null terminated string. This is optional. 
	   To make it optional provide null string and VidyoClient will use the conference ID of the
	   conference where the user is connected. */
	char conferenceId[MAX_EID_SIZE];
} VidyoClientInEventConferenceControlAllParticipants;

/*! Event structure used to control conference that affect given participant of a conference.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_PARTICIPANT
*/
typedef struct VidyoClientInEventConferenceControlParticipant_
{
	/*! Request identification. This identification provided by application in VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_PARTICIPANT will be returned in corresponding response */
    VidyoUint requestId;
	/*! The conference control command requested. */
    VidyoClientConferenceControlCommandParticipant controlCommand;
	/*! Conference Moderator PIN if needed. This is needed only if the user do not have privillege to do control meeting on this conference room.
	    If moderatorPin is not provided, it has to be a null string. */
	char moderatorPin[PIN_SIZE];
	/*! Conference ID, it has to be a null terminated string. This is optional. 
	   To make it optional provide null string and VidyoClient will use the conference ID of the
	   conference where the user is connected. */
	char conferenceId[MAX_EID_SIZE];
	/*! Participant ID, to send the control command */
	char participantId[MAX_EID_SIZE];
} VidyoClientInEventConferenceControlParticipant;

/*! SubRequests for Portal service

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE

	- Passed in field previewMode of following structures:
		+ #VidyoClientInEventPortalService
*/

typedef enum VidyoClientPortalServiceTypeRequest_
{
	/*! Direct call */
	VIDYO_CLIENT_SERVICE_TYPE_DIRECT_CALL = 0,
	/*! Search */
	VIDYO_CLIENT_SERVICE_SEARCH = 1,
	/*! Invite to conference */
	VIDYO_CLIENT_SERVICE_INVITE_TO_CONFERENCE = 2,
	/*! Drop participant */
	VIDYO_CLIENT_SERVICE_DROP_PARTICIPANT = 3,
	/*! Join conference */
	VIDYO_CLIENT_SERVICE_JOIN_CONFERENCE = 4,
	/*! Get current conference ID */
	VIDYO_CLIENT_SERVICE_GET_CONFERENCE_ID = 5,
	/*! Invalid */
	VIDYO_CLIENT_SERVICE_TYPE_INVALID = 16000,
} VidyoClientPortalServiceTypeRequest;


/*! EntityType

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE

	- Passed in field previewMode of following structures:
		+ #VidyoClientInEventPortalService
*/

typedef enum VidyoClientPortalServiceEntityType_
{
	/*! Member */
	VIDYO_CLIENT_ENTITY_TYPE_MEMBER=1,
	/*! Room */
	VIDYO_CLIENT_ENTITY_TYPE_ROOM,
	/*! Legacy */
	VIDYO_CLIENT_ENTITY_TYPE_LEGACY,
	/*! InterPortal */
	VIDYO_CLIENT_ENTITY_TYPE_IPC_ROOM,
	/*! Scheduled Room - not supported  at moment of 04/2014 */
	VIDYO_CLIENT_ENTITY_TYPE_SCHEDULED,
	/*! Any */
	VIDYO_CLIENT_ENTITY_TYPE_ANY,
} VidyoClientPortalServiceEntityType;

/*! SearchBy

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE

	- Passed in field searchBy field of search of following structures:
		+ #VidyoClientInEventPortalService
*/

typedef enum VidyoClientPortalServiceSearchBy_
{
	/*! Search by display name */
	VIDYO_CLIENT_SEARCH_BY_DISPLAY_NAME,
	/*! Search by extension number */
	VIDYO_CLIENT_SEARCH_BY_EXTENSION_NUM,
} VidyoClientPortalServiceSearchBy;

/*! Sorting order

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE

	- Passed in field sortOrder field of search of following structures:
		+ #VidyoClientInEventPortalService
*/

typedef enum VidyoClientPortalServiceSortOrder_
{
	/*! Sort in ascending order */
	VIDYO_CLIENT_SORT_ORDER_ASCENDING,
	/*! Sort in descending order */
	VIDYO_CLIENT_SORT_ORDER_DESCENDING,
} VidyoClientPortalServiceSortOrder;


/*! Member status

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_SEARCH

	- Passed in field memberStatus of the field search of the following structures:
		+ #VidyoClientOutEventPortalServiceSearch
*/

typedef enum VidyoClientMemberStatus_
{
	/*! Online */
	VIDYO_CLIENT_MEMBER_STATUS_ONLINE=1,
	/*! Offline */
	VIDYO_CLIENT_MEMBER_STATUS_OFFLINE,
	/*! Busy */
	VIDYO_CLIENT_MEMBER_STATUS_BUSY,
	/*! Busy in own room */
	VIDYO_CLIENT_MEMBER_STATUS_BUSY_IN_OWN_ROOM,
	/*! Ringing */
	VIDYO_CLIENT_MEMBER_STATUS_RINGING,
	/*! Ring accepted */
	VIDYO_CLIENT_MEMBER_STATUS_RING_ACCEPTED,
	/*! Ring rejected */
	VIDYO_CLIENT_MEMBER_STATUS_RING_REJECTED,
	/*! Ring no answer */
	VIDYO_CLIENT_MEMBER_STATUS_RING_NO_ANSWER,
	/*! Alerting */
	VIDYO_CLIENT_MEMBER_STATUS_ALERTING,
	/*! Alert Cancelled */
	VIDYO_CLIENT_MEMBER_STATUS_ALERT_CANCELLED,
} VidyoClientMemberStatus;

/*! Member mode
	
	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_SEARCH

	- Passed in field memberMode of the field search of the following structures:
		+ #VidyoClientOutEventPortalServiceSearch
*/
typedef enum VidyoClientMemberMode_
{
	/*! Available */
	VIDYO_CLIENT_MEMBER_MODE_AVAILABLE=1,
	/*! Away */
	VIDYO_CLIENT_MEMBER_MODE_AWAY,
	/*! Do not disturb */
	VIDYO_CLIENT_MEMBER_MODE_DONOTDISTURB,
} VidyoClientMemberMode;

/*! Room status

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_SEARCH

	- Passed in field roomStatus of the field search of the following structures:
		+ #VidyoClientOutEventPortalServiceSearch
*/
typedef enum VidyoClientRoomStatus_
{
	/*!  Room is empty */
	VIDYO_CLIENT_ROOM_EMPTY=1,
	/*! Room is full */
	VIDYO_CLIENT_ROOM_FULL,
	/*! Room is occupied */
	VIDYO_CLIENT_ROOM_OCCUPIED,
} VidyoClientRoomStatus;

/*! Event structure that is mandatory for event Service call

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE

	- Passed in field previewMode of following structures:
		+ #VidyoClientInEventPortalService
*/

#define VIDYO_CLIENT_USERNAME_SIZE				USERID_SIZE


/*! Event structure that is mandatory for event Service call

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE

	- Passed in field previewMode of following structures:
		+ #VidyoClientInEventPortalService
*/
typedef struct VidyoClientPortalServiceMandatory_
{
	/*! Type of request */
	VidyoUint typeRequest;
	/*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
	VidyoUint requestId;
} VidyoClientPortalServiceMandatory;

/*! Event structure used to send event for direct call

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
		+ #VidyoClientInEventPortalService
*/
typedef struct VidyoClientPortalServiceDirectCall_
{
	/*! Type of request */
	VidyoUint typeRequest;
	/*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
	VidyoUint requestId;
	/*! Entity Type
			Only valid values are Member or Legacy
			If this value is Member, entityID should be filled
			If this value is Legacy, legacyID should be filled*/
	VidyoClientPortalServiceEntityType entityType;
	/*! Entity ID of the member participant being called */
	char entityID[MAX_EID_SIZE];
	/*! ID of the legacy participant being called.
			This is the value of field extension in AccountData
			when the legacy endpoint's informtion is taken from Search result.*/
	char legacyID[MAX_EID_SIZE];	
	/*! Join the conference with camera muted */
	VidyoBool muteCamera;
	/*! Join the conference with microphone muted */
	VidyoBool muteMicrophone;
	/*! Join the conference with speaker muted */
	VidyoBool muteSpeaker;
} VidyoClientPortalServiceDirectCall;



/*! Event structure used to send searches to portal

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
		+ #VidyoClientInEventPortalService
*/

typedef struct VidyoClientPortalServiceSearchRequest_
{
	/*! Type of request */
	VidyoUint typeRequest;
	/*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
	VidyoUint requestId;
	/*! Starting number for search to start from - To start from beginning set as 0 */
	VidyoUint start;
	/*! Limit in number of response - MAX can be VIDYO_CLIENT_PRIVATE_SOAP_SEARCH_SIZE */
	VidyoUint limit;
	/*! What are we trying to search by - display name or entity id*/
	VidyoClientPortalServiceSearchBy searchBy;
	/*! Ascending or descending*/
	VidyoClientPortalServiceSortOrder sortOrder;
	/*!  Actual Search string*/
	char searchString[VIDYO_CLIENT_USERNAME_SIZE]; // Search string
} VidyoClientPortalServiceSearchRequest;


/*! Event structure used to send invite to conference

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
		+ #VidyoClientInEventPortalService
*/

typedef struct VidyoClientPortalServiceInviteToConferenceRequest_
{
	/*! Type of request */
	VidyoUint typeRequest;
	/*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
	VidyoUint requestId;
	/*! Entity Type
	Only valid values are Member or Legacy
	If this value is Member, entityID should be filled
	If this value is Legacy, legacyID should be filled
	*/
	VidyoClientPortalServiceEntityType entityType;
	/*! Entity ID - Unique in Portal DB
	   Entity ID of the room to where Invite to Conference is being requested*/
	char conferenceID[MAX_EID_SIZE];
	/*! Conference ID, it has to be a null terminated string.
	   Entity ID of the participant who is invited to conference*/
	char entityID[MAX_EID_SIZE];
	/*! ID of the legacy participant who is invited to conference
	  This is the value of field extension in VidyoClientPrivateSoapAccountData
	  when the legacy endpoint's informtion is taken from Search result.*/
	char legacyID[MAX_EID_SIZE];
} VidyoClientPortalServiceInviteToConferenceRequest;

/*! Event structure used to drop participant

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
		+ #VidyoClientInEventPortalService
*/
typedef struct VidyoClientPortalServiceDropParticipantRequest_
{
	/*! Type of request */
	VidyoUint typeRequest;
	/*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
	VidyoUint requestId;
	/*! Entity ID - Unique in Portal DB
	   Entity ID of the current conference*/
	char conferenceID[MAX_EID_SIZE];
	/*! Particpant ID
	   of the participant who is to be dropped*/
	char participantID[URI_LEN];
} VidyoClientPortalServiceDropParticipantRequest;

/*! Event structure used to join conference

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
		+ #VidyoClientInEventPortalService
*/
typedef struct VidyoClientPortalServiceJoinConferenceRequest_
{
	/*! Type of request */
	VidyoUint typeRequest;
	/*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
	VidyoUint requestId;
	/*! EntityId of the room to join
	if joining by ID
	Extension should be empty
	*/
	char entityID[MAX_EID_SIZE];
	/*! Extension of the room to join
	if joining by extension
	EntityId should be empty
	*/
	char extension[VIDYO_MAX_EXTENSION_SIZE];	
	/*!  Room PIN 
	If room has PIN*/
	char roomPIN[PIN_SIZE];
	/*!  Reference number 
	This is optional field*/
	char referenceNumber[VIDYO_CLIENT_REFERENCE_NUMBER_LEN];
	/*! Join the conference with camera muted */
	VidyoBool muteCamera;
	/*! Join the conference with microphone muted */
	VidyoBool muteMicrophone;
	/*! Join the conference with speaker muted */
	VidyoBool muteSpeaker;
} VidyoClientPortalServiceJoinConferenceRequest;

/*! Event structure used to get the current conference id

	- Used for the following events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
		+ #VidyoClientInEventPortalService
*/
typedef struct VidyoClientPortalServiceGetConferenceIdRequest_
{
	/*! Type of request */
	VidyoUint	typeRequest;
	/*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
	VidyoUint	requestId;
} VidyoClientPortalServiceGetConferenceIdRequest;


/*! Event structure used to send generic command to portal.

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
*/
typedef struct VidyoClientInEventPortalService_
{
	/*! The actual portal service structures. */
    union 
	{
		/*! never usedl */
		VidyoClientPortalServiceMandatory mandatory;
		/*! direct call */
		VidyoClientPortalServiceDirectCall directCall;
		/*! search portal */
		VidyoClientPortalServiceSearchRequest search;
		/*! Invite to conference */
		VidyoClientPortalServiceInviteToConferenceRequest inviteToConference;
		/*! Drop participant from conference */
		VidyoClientPortalServiceDropParticipantRequest dropParticipant;
		/*! Join conference */
		VidyoClientPortalServiceJoinConferenceRequest joinConference;
		/*! Get the conference Id */
		VidyoClientPortalServiceGetConferenceIdRequest getConferenceId;
	} requests;
} VidyoClientInEventPortalService;


/*! Event structure used to select speaker. currently only supported in iOS

	- Used by following in events: *Deprecated*.
		+ #VIDYO_CLIENT_IN_EVENT_SELECT_SPEAKER
 
    @warning This API is deprecated. Please use MpVolumeView from Apple instead of this. Details are
    available at https://developer.apple.com/library/ios/documentation/MediaPlayer/Reference/MPVolumeView_Class/index.html
*/
typedef struct VidyoClientInEventSelectSpeaker_
{
	/*! Index of speaker */
	VidyoInt speaker;
} VidyoClientInEventSelectSpeaker;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_GROUP_COMMAND
*/
typedef struct VidyoClientInEventGroupCommand_
{
	/*! Command to be sent to all remote participants */
	char command[MAX_COMMAND_LEN];
} VidyoClientInEventGroupCommand;

/*! Event structure

	- Used by following in events:
		+ #VIDYO_CLIENT_IN_EVENT_PRIVATE_COMMAND
*/
typedef struct VidyoClientInEventPrivateCommand_
{
	/*! Vidyo URI of remote participant to whom this command to be sent */
	char uri[URI_LEN];
	/*! Command to be sent */
	char command[MAX_COMMAND_LEN];
} VidyoClientInEventPrivateCommand;

/*! Event structure
 
	- Used by following in events:
    + #VIDYO_CLIENT_IN_EVENT_IS_PORTAL_AVAILABLE
*/
typedef struct VidyoClientInEventIsPortalAvailable_
{
    /*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
    VidyoUint	requestId;
    char portalUri[URI_LEN];
} VidyoClientInEventIsPortalAvailable;

/*******************************************************************************
 Parameter structures for events from Vidyo Client Library to GUI
*******************************************************************************/

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_USER_MESSAGE

	Has informational meaning only.
*/
typedef struct VidyoClientOutEventUserMessage_
{
	/*! Specific message to convey to user.  See definition of VidyoClientUserMessageType. */
	VidyoClientUserMessageType messageType;
	/*!
		Additional information, currently limited to the first element of this array.

		Passed with (but can be ignored for) following messages:
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VIDYO_SDK_BASE
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_FRAMEWORK_LOG
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VIDYO_DESKTOP_LOG
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VIDYOPROXY_LOG
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_SDK_CLIENT
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_CONSTRUCTION_VD_LOGIC
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_START_VD_LOGIC
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VD_HELPER_CONSTRUCT
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_VD_HELPER_START
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_CONSTRUCTION_STRING_TRANSLATION_TABLE
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INIT_ERROR_SSE2_CHECK_FAILED
	*/
	VidyoUint messageCode[NUM_USER_MESSAGE_CODES];
	/*!
		Additional information, currently limited to the first element of this array.

		Passed with following messages:
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_CALLEE_DECLINED
				Username of recipient of outbound call.
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_CALLER_CANCELLED
				Username of originator of inbound call.
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_INVITATION_TIMED_OUT
				Username of originator of inbound call.
			- VIDYO_CLIENT_USER_MESSAGE_TYPE_CALL_TIMED_OUT
				Username of originator of inbound call.
	*/
	VidyoUint8 messageString[MAX_USER_MESSAGE_STRING_SIZE];
} VidyoClientOutEventUserMessage;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_SIGN_IN
*/
typedef struct VidyoClientOutEventSignIn_
{
	/*!
		Value is non-zero if client is licensed and can function.  If value is zero, action
		must be taken by application to acquire license from VidyoPortal and activate
		license (which produces an EID).
	*/
	VidyoUint activeEid;
	/*!
		VIDYO_TRUE if sign-in is for guest user, VIDYO_FALSE if sign-in is for
		permanent user.
	*/
	VidyoBool guestLogin;
	/*! Reserved for use by standard Vidyo clients.  Value can be ignored. */
	VidyoBool showDialpad;
	/*! Reserved for use by standard Vidyo clients.  Value can be ignored. */
	VidyoBool showStartmeeting;
	/*! Indicates source of sign-in event.  @see VidyoClientSignInEnum. */
	VidyoClientSignInEnum signinType;
	/*!
		VIDYO_TRUE if sign-in is for secure VidyoPortal and VidyoManager, VIDYO_FALSE if
		sign-in is for insecure VidyoPortal and VidyoManager.
	*/
	VidyoBool signinSecured;
} VidyoClientOutEventSignIn;

/*! Structure for device change event

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_DEVICES_CHANGED
*/
typedef struct  VidyoClientOutEventDevicesChanged_
{
	/*!
		Kind of device, for which a device was added or removed.  @see VidyoClientDeviceType.
	*/
	VidyoClientDeviceType deviceType;
} VidyoClientOutEventDevicesChanged;

/*! Structure for device change event

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_SELECTED_DEVICE_ON_OS_CHANGED
*/
typedef struct  VidyoClientOutEventSelectedDeviceOnOsChanged_
{
	/*!
		Kind of device, for which a device was added or removed.  @see VidyoClientDeviceType.
	*/
	VidyoClientDeviceType deviceType;
} VidyoClientOutEventSelectedDeviceOnOsChanged;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_DEVICES_CHANGED
*/
typedef struct VidyoClientOutEventDeviceSelectionChanged_
{
	/*!
		Kind of device, whose selection is changed.  @see VidyoClientDeviceType.
	*/
	VidyoClientDeviceType deviceType;
	/*!
		The type of device change had happened. @see VidyoClientDeviceChangeType.
	*/
	VidyoClientDeviceChangeType changeType;
	/*! Name of the device that is changed. */
	VidyoUint8 prevDeviceName[DEVICE_NAME_SIZE];
	/*!
		Name of the device that is changed to. Valid only when an alternate
		device is selected. i.e. when the value of changeType is 
		VIDYO_CLIENT_USER_MESSAGE_DEVICE_SELECTION_CHANGED
	*/
	VidyoUint8 newDeviceName[DEVICE_NAME_SIZE];	
} VidyoClientOutEventDeviceSelectionChanged;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_RINGING
		+ #VIDYO_CLIENT_OUT_EVENT_CALLING
		+ #VIDYO_CLIENT_OUT_EVENT_JOINING
		+ #VIDYO_CLIENT_OUT_EVENT_RETRYING
*/
typedef struct VidyoClientOutEventStartProgress_
{
	/*! How many maximum steps of progress anticipated.  Range of values 0~UINT_MAX. */
	VidyoUint numProgressSteps;
	/*!
		For #VIDYO_CLIENT_OUT_EVENT_CALLING, the username of the recipient of an outbound
		call.  For #VIDYO_CLIENT_OUT_EVENT_JOINING, the name of the conference to be joined.
		Encoded as UTF-8.
	*/
	char caption[DISPLAY_CONFERENCE_SIZE];
} VidyoClientOutEventStartProgress;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED
*/
typedef struct VidyoClientOutEventParticipantsChanged_
{
	/*! The number of participants in conference now. */
	VidyoUint participantCount;
} VidyoClientOutEventParticipantsChanged;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_ADDED
		+ #VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_REMOVED
*/
typedef struct VidyoClientOutEventRemoteSourceChanged_
{
	/*! The type of source added to conference. */
	VidyoClientSourceType sourceType;
	/*! The URI identifying the participant whose source is added */
	char participantURI[MAX_URI_LEN]; 
	/*! Display name of conference participant. */
	char displayName[USERID_SIZE];
	/*! Name of source added to conference. */
	char sourceName[DEVICE_NAME_SIZE];
} VidyoClientOutEventRemoteSourceChanged;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL
*/
typedef struct VidyoClientOutEventIncomingCall_
{
	/*!
		Username of the originator of an inbound call.  Only valid if this event was generated
		for an inbound call initiated by another endpoint and not VidyoPortal, as determined by
		parameter onCallFlag.  Encoded as UTF-8.
	*/
	char invitingUser[DISPLAY_CONFERENCE_SIZE];
	/*!
		VIDYO_TRUE if this event was generated for an inbound call initiated by another
		endpoint, VIDYO_FALSE if this event was generated for an inbound call initiated by
		VidyoPortal.
	*/
	VidyoBool onCallFlag;
} VidyoClientOutEventIncomingCall;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_CALL_STATE
*/
typedef struct VidyoClientOutEventCallState_
{
	/*! Updated call state of client

		@see VidyoClientCallState
	*/
	VidyoClientCallState callState;
} VidyoClientOutEventCallState;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PREVIEW
*/
typedef struct VidyoClientOutEventPreview_
{
	/*! How video is now shown in video layout.  @see VidyoClientPreviewMode. */
	VidyoClientPreviewMode previewMode;
} VidyoClientOutEventPreview;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN
		+ #VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_OUT
		+ #VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO
		+ #VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_AUDIO_IN
		+ #VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_VIDEO
*/
typedef struct VidyoClientOutEventMuted_
{
	/*!
		VIDYO_TRUE to acknowledge or indicate muting of local media device for specified out
		event, VIDYO_FALSE to acknowledge or indicate un-muting.
		#VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN is sent for local muting of the microphone device,
		#VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_OUT is sent for local muting of the speaker device,
		and #VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO is sent for local muting of the camera device.
		#VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_AUDIO_IN is sent for remote muting of the
		microphone device, and #VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_VIDEO is sent for remote
		muting of the camera device.
	*/
	VidyoBool isMuted;
	/*!
		Possible values, only for acknowledgment events #VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN,
		#VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_OUT, and #VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO,
		from VidyoClientConstants.h:
		- VIDYO_CLIENT_ERROR_OK
			No error.
		- VIDYO_CLIENT_ERROR_NO_ENGINE
			Client is currently not in a conference.

		@note Only applies to acknowledgments, not indications
	*/
	VidyoUint errorCode;
} VidyoClientOutEventMuted;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_ADD_SHARE
*/
typedef struct VidyoClientOutEventAddShare_
{
	/*!
		Vidyo URI of remote participant who has added an application sharing window to
		the current conference.
	*/
	char URI[URI_LEN];
} VidyoClientOutEventAddShare;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE
*/
typedef struct VidyoClientOutEventRemoveShare_
{
	/*!
		Vidyo URI of remote participant who has removed an application sharing window from
		the current conference.
	*/
	char URI[URI_LEN];
} VidyoClientOutEventRemoveShare;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_RESIZE
*/
typedef struct VidyoClientOutEventResize_
{
	VidyoUint width;    /*!< Width of video layout region.  Range of values 0~UINT_MAX. */
	VidyoUint height;   /*!< Height of video layout region.  Range of values 0~UINT_MAX. */
} VidyoClientOutEventResize;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT
*/
typedef struct VidyoClientOutEventParticipantsLimit_
{
	/*!
		Maximum number of viewable remote participants in video layout, due to current network
		bandwidth.  Range of values 0~16.
	*/
	VidyoUint BandwidthLimit;
	/*!
		Maximum number of viewable remote participants in video layout, due to current CPU
		utilization.  Range of values 0~16.
	*/
	VidyoUint CpuLimit;
	/*!
		Maximum number of viewable tiles in video layout as configured by user.
	*/
	VidyoUint UserLimit;
} VidyoClientOutEventParticipantsLimit;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_KEYDOWN
		+ #VIDYO_CLIENT_OUT_EVENT_KEYUP
*/
typedef struct VidyoClientOutEventKeyboard_
{
	/*!
		Keycode of key, which has either been pressed (VIDYO_CLIENT_OUT_EVENT_KEYDOWN) or
		released (VIDYO_CLIENT_OUT_EVENT_KEYUP) while window containing video layout had
		focus.  Actual range of values dependent on underlying platform.
	*/
	VidyoUint key;
	/*! How many times the key was pressed/released in succession.  Range of values 1~UINT_MAX. */
	VidyoUint count;
} VidyoClientOutEventKeyboard;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_MOUSE_DOWN
		+ #VIDYO_CLIENT_OUT_EVENT_MOUSE_UP (not yet supported)
		+ #VIDYO_CLIENT_OUT_EVENT_MOUSE_MOVE
		+ #VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL (not yet supported)
*/
typedef struct VidyoClientOutEventMouse_
{
	/*!
		Index of mouse button, which is involved in triggering event.  A value of 1
		indicates the left button, a value of 2 indicates the right button (for 2-button mice
		and emulation of the 2-button mice), and a value of 3 indicates the middle button (for
		3-button mice and emulation of 3-button mice.)
	*/
	VidyoUint button;
	/*!
		How many times the mouse button was pressed.  A value of 0 is used for
		events #VIDYO_CLIENT_OUT_EVENT_MOUSE_UP, #VIDYO_CLIENT_OUT_EVENT_MOUSE_MOVE, and
		#VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL, a value of 1 is used for event
		#VIDYO_CLIENT_OUT_EVENT_MOUSE_DOWN to indicate a single click, and a value of 2 is used
		for event #VIDYO_CLIENT_OUT_EVENT_MOUSE_DOWN to indicate a double click.

	*/
	VidyoUint count;
	/*!
		Horizontal offset of mouse event.  Actual range of values dependent on underlying
		platform.
	*/
	VidyoInt xPos;
	/*!
		Vertical offset of mouse event.  Actual range of values dependent on underlying
		platform.
	*/
	VidyoInt yPos;
	/*!
		VIDYO_TRUE if shift modifier key was depressed when mouse button was clicked,
		VIDYO_FALSE if shift modifier key was not depressed when mouse button was clicked.
	*/
	VidyoBool shift;
	/*!
		VIDYO_TRUE if ctrl modifier key was depressed when mouse button was clicked,
		VIDYO_FALSE if ctrl modifier key was not depressed when mouse button was clicked.
	*/
	VidyoBool ctrl;
	/*!
		VIDYO_TRUE if alt modifier key was depressed when mouse button was clicked,
		VIDYO_FALSE if alt modifier key was not depressed when mouse button was clicked.
	*/
	VidyoBool alt;
	/*!
		VIDYO_TRUE if command modifier key was depressed when mouse button was clicked,
		VIDYO_FALSE if command modifier key was not depressed when mouse button was clicked.
		@note Only supported on OS X platform.
	*/
	VidyoBool command;
	/*!
		Difference in horizontal offset between last mouse event and this mouse event, for
		event #VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL.  Actual range of values dependent on
		underlying platform.
	*/
	VidyoInt scrollDeltaX;
	/*!
		Difference in vertical offset between last mouse event and this mouse event, for
		event #VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL.  Actual range of values dependent on
		underlying platform.
	*/
	VidyoInt scrollDeltaY;
	/*!
		Difference in z-axis offset between last mouse event and this mouse event, for
		event #VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL.  Actual range of values dependent on
		underlying platform.
	*/
	VidyoInt scrollDeltaZ;
} VidyoClientOutEventMouse;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_TOUCH
*/
typedef struct VidyoClientOutEventTouch_
{
	/*!
		How many times the same kind of touch event was generated.  A value of 1 is used
		to indicate a single tap, a value of 2 is used to indicate a double tap, and so on.
	*/
	VidyoUint count;
	/*!
		Horizontal offset of touch event.  Actual range of values dependent on underlying
		platform.
	*/
	VidyoInt xPos;
	/*!
		Vertical offset of touch event.  Actual range of values dependent on underlying
		platform.
		@note Only supported on OS X platform.
	*/
	VidyoInt yPos;
	/*! Indicates which kind of touch event has been generated. */
	VidyoClientTouchState state;
} VidyoClientOutEventTouch;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_FECC_LIST_UPDATED
*/
typedef struct VidyoClientOutEventFeccListUpdated_
{
	/*! Number of Vidyo URI values in parameter uri.  Range of values 0~UINT_MAX. */
	VidyoUint numberParticipants;
} VidyoClientOutEventFeccListUpdated;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_FECC_STATUS_UPDATE
*/
typedef struct VidyoClientOutEventFeccStatusUpdate_
{
	/*! FECC status code */
	VidyoClientFeccStatusCode statusCode;
	/*! URI of the remote participant */
	char curFeccUri[URI_LEN];
} VidyoClientOutEventFeccStatusUpdate;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PARTICIPANT_BUTTON_CLICK
*/
typedef struct VidyoClientOutEventParticipantButtonClick_
{
	/*! Vidyo URI of participant for the button that was clicked. */
	char srcParticipantID[URI_LEN];
	/*! Identifies which button has been clicked.

		For a buttonType of #VIDYO_CLIENT_PARTICIPANT_BUTTON_FECC the buttonState will be either
		a value of #VIDYO_CLIENT_BUTTON_STATE_ON or #VIDYO_CLIENT_BUTTON_STATE_OFF. */
	VidyoClientParticipantButtonType buttonType;
	/*!
		- #VIDYO_CLIENT_BUTTON_STATE_ON when the button is in an ON (or highlighted) state,
		- #VIDYO_CLIENT_BUTTON_STATE_OFF when button is OFF
	*/
	VidyoClientParticipantButtonState buttonState;
} VidyoClientOutEventParticipantButtonClick;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_CONTROL_CAMERA
*/
typedef struct VidyoClientOutEventControlCamera_
{
	/*! Vidyo URI of remote participant that issued request to control local camera. */
	char srcParticipantID[URI_LEN];
	/*! Type of camera control operation.  See definition of VidyoClientCameraControlCommand. */
	VidyoClientCameraControlCommand cameraCommand;
	/*! ID for VISCA pass-through command. */
	char commandId[MAX_VISCA_COMMAND];
	/*! Data for VISCA pass-through response in hex (e.g. "95 50 00 00 00 00 00 00 00 00 ff") */
	char commandData[MAX_VISCA_COMMAND];
} VidyoClientOutEventControlCamera;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_SET_PARTICIPANT_VIDEO_MODE_DONE
*/
typedef struct VidyoClientOutEventSetParticipantVideoModeDone_
{
	/*! Vidyo URI of remote participant that video mode was set for. */
	char uri[URI_LEN];
	/*! Video mode of remote participant.  See definition of VidyoClientParticipantVideoMode. */
	VidyoClientParticipantVideoMode videoMode;
	/*!
		VIDYO_TRUE if video mode was successfully set, VIDYO_FALSE if video mode was not
		successfully set.
	*/
	VidyoBool isSet;
} VidyoClientOutEventSetParticipantVideoModeDone;

/*! Event structure

	- Used for reporting conference information update events:
		+ #VIDYO_CLIENT_OUT_EVENT_CONFERENCE_INFO_UPDATE
*/
typedef struct VidyoClientOutEventConferenceInfoUpdate_
{
	VidyoClientConferenceInfoUpdateEventID eventID; /*!< Event identity */
	VidyoBool eventStatus;                          /*!< Event status and get value 0 (false) or 1 (true) */
} VidyoClientOutEventConferenceInfoUpdate;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL
*/
typedef struct VidyoClientOutEventMediaControl_
{
	/*! Operation to perform.  @see VidyoClientMediaControlCommand. */
	VidyoClientMediaControlCommand mediaCommand;
	/*! Kind of media on which to perform operation.  @see VidyoClientMediaControlType. */
	VidyoClientMediaControlType mediaType;
	/*! Source of operation.  @see VidyoClientMediaControlSource. */
	VidyoClientMediaControlSource mediaSource;
} VidyoClientOutEventMediaControl;

/*! Event structure

	- Used for reporting conference information update events:
		+ #VIDYO_CLIENT_OUT_EVENT_LOGIN
*/
typedef struct VidyoClientOutEventLogIn_
{
	/*! Error code.  */
	VidyoUint error;
	/*! Portal URI */
	char portalUri[URI_LEN];
	/*! User name */
	char userName[USERID_SIZE];
} VidyoClientOutEventLogIn;

/*!	Status code of Guest Link Room operation
	- Used for event
		+ VIDYO_CLIENT_OUT_EVENT_ROOM_LINK
*/	
typedef enum VidyoClientRoomLinkState_
{
	VIDYO_CLIENT_ROOM_LINK_STATE_INIT = 0,		/*!< Initial state, nothing achived */
	VIDYO_CLIENT_ROOM_LINK_STATE_CONNECTED, 	/*!< Connection to server (maybe HTTP proxy) tried by Getting Portal Version */
	VIDYO_CLIENT_ROOM_LINK_STATE_LOGGED,		/*!< SOAP request Logging to Portal is sent */
	VIDYO_CLIENT_ROOM_LINK_STATE_LINKED,		/*!< Process Linking to VidyoMahager is passed */
	VIDYO_CLIENT_ROOM_LINK_STATE_GOT_ENTITY,	/*!< intermedia state for using Room Link being logged in the same Portal */
	VIDYO_CLIENT_ROOM_LINK_STATE_CANCELLED,		/*!< process cancelled by User */
	VIDYO_CLIENT_ROOM_LINK_STATE_JOINED,		/*!< SOAP request Joining Conference is sent */
} VidyoClientRoomLinkState;

/*! Event structure

	- Used for reporting guest login & join-room state and error via event:
		+ #VIDYO_CLIENT_OUT_EVENT_ROOM_LINK
*/
typedef struct VidyoClientOutEventRoomLink_
{
	/*! Error code.  */
	VidyoClientError error;
	/*! Guest login & join-room state  */
	VidyoClientRoomLinkState state;
	/*! Server URI */
	char serverUri[URI_LEN];
}VidyoClientOutEventRoomLink;

/*! Event structure

	- Used for reporting recommended client version:
		+ #VIDYO_CLIENT_OUT_EVENT_CLIENT_VERSION_ON_SERVER
*/
typedef struct VidyoClientOutEventClientVersionOnServer_
{
	/*! Error code.  */
	VidyoClientError error;
	/*! version of client  */
	char currentTag[VIDYO_CLIENT_VERSION_SIZE];
	/*! Uri for the installer */
	char installerUri[URI_LEN];
}VidyoClientOutEventClientVersionOnServer;

/*! Event structure

	- Used for reporting conference information update events:
		+ #VIDYO_CLIENT_OUT_EVENT_LICENSE
*/
typedef struct VidyoClientOutEventLicense_
{
	/*! Error code. */
	VidyoUint error;
	/*! Connection path */
	VidyoUint vmConnectionPath;
	/*! VIDYO_TRUE when licenses are exhausted on the portal. VIDYO_FALSE otherwise. */
	VidyoBool OutOfLicenses;
	/*! Result from SOAP response */
	VidyoClientSoapResultCode result;
	/*! SOAP fault code */
	VidyoClientSoapFault fault;
} VidyoClientOutEventLicense;

/*! Event structure

	- Used for reporting conference information update events:
		+ #VIDYO_CLIENT_OUT_EVENT_LINKED
*/
typedef struct VidyoClientOutEventLinked_
{
	/*! Error code.  */
	VidyoUint error;
} VidyoClientOutEventLinked;

/*! Event structure

	- Used for reporting failure of sign-in request.
	- Used for responding to signed-out request.
	- Used for reporting sign-out command from portal
		 e.g. user signed-in to another machine.
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT
*/
typedef struct VidyoClientOutEventSignedOut_
{
	/*! Cause to generate this event. */
	VidyoClientSignedOutCause cause;
	/*! Error code. */
	VidyoUint error;
	/*!
	 VIDYO_TRUE if logged (joined to Room Link) as guest,
	 VIDYO_FALSE for permanent users.
	 */
	VidyoBool guestLogin;
} VidyoClientOutEventSignedOut;

/*! Event structure

	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_ENABLED_STATUS_BAR
		+ #VIDYO_CLIENT_OUT_EVENT_ENABLED_BUTTON_BAR
*/
typedef struct VidyoClientOutEventEnabled_
{
	/*!
		VIDYO_TRUE to confirm enabling of setting for specified out event,
		VIDYO_FALSE to confirm disabling.
	*/
	VidyoBool isEnabled;
} VidyoClientOutEventEnabled;

/*! Event structure
	- Used by following in events:
		+ #VIDYO_CLIENT_OUT_EVENT_FLOATING_WINDOW
*/
typedef struct VidyoClientOutEventFloatingWindow_
{
	/*!
		OS-specific window ID of floating window.  0 when the window has been destroyed.
		See VidyoTypes.h for definition of #VidyoWindowId for particular platform.
	*/
	VidyoWindowId window;
} VidyoClientOutEventFloatingWindow;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_GROUP_CHAT
*/
typedef struct VidyoClientOutEventGroupChat_
{
	/*! Vidyo URI of remote participant that sent message. */
	char uri[URI_LEN];
	/*! Display name of conference participant. */
	char displayName[USERID_SIZE];
	/*! Message (contents) to be sent. */
	char message[MAX_CHAT_MESSAGE_LEN];
} VidyoClientOutEventGroupChat;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PRIVATE_CHAT
*/
typedef struct VidyoClientOutEventPrivateChat_
{
	/*! Vidyo URI of remote participant to whom this text message to be sent. */
	char uri[URI_LEN];
	/*! Display name of conference participant to whom this text message to be sent. */
	char displayName[USERID_SIZE];
	/*! Message (contents) to be sent. */
	char message[MAX_CHAT_MESSAGE_LEN];
} VidyoClientOutEventPrivateChat;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_PREFIX
*/
typedef struct VidyoClientOutEventPortalPrefix_
{
	/*! The result of retrieving Portal prefix */
	VidyoClientError result;
	/*! The portal prefix retrieved. This will be valid only when result is VIDYO_CLIENT_ERROR_NONE */
	char portalPrefix[MAX_PORTAL_PREFIX_SIZE];

} VidyoClientOutEventPortalPrefix;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_FEATURES
*/
typedef struct VidyoClientPortalFeatureStatus_
{
	/*! The portal feature name */
	VidyoClientPortalFeatureNames featureName;
	/*! Indicates whether the feature is enabled */
	VidyoBool isEnabled;

} VidyoClientPortalFeatureStatus;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_FEATURES
		+ #VIDYO_CLIENT_REQUEST_GET_PORTAL_FEATURES
*/
typedef struct VidyoClientEventPortalFeatures_
{
	/*! The number of portal features */
	VidyoUint featureCount;
	/*! The portal feature name and it status */
	VidyoClientPortalFeatureStatus featureStatus[VIDYO_CLIENT_PORTAL_FEATURE_NAME_MAX];

} VidyoClientEventPortalFeatures;

/*! @struct VidyoClientCpuUsageActions
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_OUT_EVENT_CPU_USAGE_ACTIONS

	@var VidyoClientCpuUsageActions::reducedToThirtyFps [out]
		Number of decode streams reduced to no more than 30 FPS.
	@var VidyoClientCpuUsageActions::reducedToFifteenFps [out]
		Number of decode streams reduced to no more than 15 FPS.
	@var VidyoClientCpuUsageActions::reducedToSevenFps [out]
		Number of decode streams reduced to no more than 7 FPS.
	@var VidyoClientCpuUsageActions::reducedToThreeFourthResolution [out]
		Number of decode streams reduced to no more than 3/4th resolution.
	@var VidyoClientCpuUsageActions::reducedToHalfResolution [out]
		Number of decode streams reduced to no more than 1/2 resolution.
	@var VidyoClientCpuUsageActions::reducedNumberOfDecodeStreams [out]
		Number of decode streams removed.
	@var VidyoClientCpuUsageActions::reducedToHalfEncodeFps [out]
		Number of encode streams reduced to 1/2 of original FPS.
	@var VidyoClientCpuUsageActions::reducedToThreeFourthEncodeResolution [out]
		Number of encode streams reduced to 3/4th of original resolution.
	@var VidyoClientCpuUsageActions::reducedToHalfEncodeResolution [out]
		Number of encode streams reduced to 1/2 of original resolution.

*/
typedef struct VidyoClientCpuUsageActions_
{
	VidyoUint reducedToThirtyFps;
	VidyoUint reducedToFifteenFps;
	VidyoUint reducedToSevenFps;
	VidyoUint reducedToThreeFourthResolution;
	VidyoUint reducedToHalfResolution;
	VidyoUint reducedNumberOfDecodeStreams;
	VidyoUint reducedToHalfEncodeFps;
	VidyoUint reducedToThreeFourthEncodeResolution;
	VidyoUint reducedToHalfEncodeResolution;
} VidyoClientCpuUsageActions;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_CPU_USAGE_ACTIONS
*/
typedef struct VidyoClientOutEventCpuUsageActions_
{
	/*! The current CPU usage action */
	VidyoClientCpuUsageStatus currentCpuUsageStatus;
	/*! The CPU usage actions taken */
	VidyoClientCpuUsageActions cpuUsageActions;

} VidyoClientOutEventCpuUsageActions;

/*! Lecture mode stages

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_STAGE

	- Passed in field previewMode of following structures:
		+ #VidyoClientOutEventLectureModeStage
*/

typedef enum VidyoClientLectureStage_
{
	/*! Lecture mode in listen mode */
	VIDYO_CLIENT_LECTURE_MODE_LISTEN = 0,
	/*! Lecture mode in presenter mode */
	VIDYO_CLIENT_LECTURE_MODE_PRESENT = 1,
	/*! Lecture mode in allowed to speak mode */
	VIDYO_CLIENT_LECTURE_MODE_ALLOWED_TO_SPEAK = 2,
	/*! Lecture mode has started*/
	VIDYO_CLIENT_LECTURE_MODE_START = 3,
	/*! Lecture mode stop */
	VIDYO_CLIENT_LECTURE_MODE_STOP = 10
} VidyoClientLectureStage;

/*! Event structure
	- Used by following out events:
        + #VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_STAGE
*/
typedef struct VidyoClientOutEventLectureModeStage_
{
	/*! Stage of lecture mode */
	VidyoClientLectureStage	stage;
} VidyoClientOutEventLectureModeStage;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_PRESENTER_CHANGED
*/
typedef struct VidyoClientOutEventLectureModePresenter_
{
	/*! Uri of the participant who is the presenter, empty if no presenter */
	char uriOfPresenter[URI_LEN];
} VidyoClientOutEventLectureModePresenter;

/*! Event structure
	- Used by following out events to send received video frames from remote participants being watched by 
	  VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE or VIDYO_CLIENT_IN_EVENT_SET_DYNAMIC_WATCH_VIDEO_SOURCE
	   Typically, the frame will be formatted as ARGB:

		+ #VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED
*/ 
typedef struct VidyoClientOutEventVideoFrameReceived_
{
	/*! The URI identifying the participant which generated the video frame */
	char participantURI[MAX_URI_LEN]; 
	/*! Identify whether this is a Video or application share */
	VidyoClientMediaControlType mediaType;
	/*! In case of more than one source - provides the identity (typically 0) */
	VidyoUint sourceId; 
 	/*! When used with dynamic switching provides the place in the selected participant list. Loudest speaker will have value 0  */
    VidyoUint viewPriority; 
	/*! Application data provided when participant watch was started */
	void* watchData; 
	/*! Frame information */
	VidyoClientInEventVideoFrame frame;  // MUST BE LAST IN STRUCT. DO NOT ADD BELOW.
} VidyoClientOutEventVideoFrameReceived;

/*! Event structure
	- Used by following out events to send received audio frames from remote participants being aquired by 
	  VIDYO_CLIENT_IN_EVENT_START_ACQUIRE_AUDIO:

		+ #VIDYO_CLIENT_OUT_EVENT_AUDIO_FRAME_RECEIVED
*/ 
typedef struct VidyoClientOutEventAudioFrameReceived_
{
	/*! The URI identifying the participant which generated the audio frame */
	char participantURI[MAX_URI_LEN];
	/*! In case of more than one source - provides the identity (typically 0) */
	VidyoUint sourceId;
	/*! Provides the place in the selected participant list.  Loudest speaker will have value 0 */
    VidyoUint viewPriority;
	/*! Frame data */
    VidyoClientAudioFrame frame;
} VidyoClientOutEventAudioFrameReceived;

/*! Event structure
	- Used by following out events to send response for 
	  VIDYO_CLIENT_IN_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS:

		+ #VIDYO_CLIENT_OUT_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS
*/ 
typedef struct VidyoClientOutEventControlConferenceRoomSettings_
{
	/*! Request identification. This identification is provided by application in VIDYO_CLIENT_IN_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS */
    VidyoUint requestId;
	/*! The setting change identification to be applied - This is same as the value provided by application in VIDYO_CLIENT_IN_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS */
    VidyoClientConferenceRoomSettingId roomSettingId;
	/*! Result of the operation */
	VidyoClientError result;
} VidyoClientOutEventControlConferenceRoomSettings;

/*! Event structure used to report status of start or stop device test in pre-call.

	- Used by following in events:
		+ #VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE
*/
typedef struct VidyoClientOutEventPrecallTestDevice_
{
	/*! The device type. */
	VidyoClientDeviceType deviceType;
	/*! The device test action requested. */
    VidyoClientPrecallDeviceTestAction action;
	/*! The result of device test action requested. */
    VidyoClientPrecallDeviceTestResult result;
} VidyoClientOutEventPrecallTestDevice;

/*! Event structure used to send response for control conference that affect all participants of a conference commands.

	- Used by following in events:
		+ #VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS
*/
typedef struct VidyoClientOutEventConferenceControlAllParticipants_
{
	/*! Request identification. This identification provided by application in VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS */
    VidyoUint requestId;
	/*! The conference control command requested. */
    VidyoClientConferenceControlCommand controlCommand;
	/*! Result of the operation */
	VidyoClientError result;
} VidyoClientOutEventConferenceControlAllParticipants;

/*! Event structure used to send response for control conference that affect given participant of a conference commands.

	- Used by following in events:
		+ #VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CONTROL_PARTICIPANT
*/
typedef struct VidyoClientOutEventConferenceControlParticipant_
{
	/*! Request identification. This identification provided by application in VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_PARTICIPANT */
    VidyoUint requestId;
	/*! The conference control command requested. */
    VidyoClientConferenceControlCommandParticipant controlCommand;
	/*! Result of the operation */
	VidyoClientError result;
} VidyoClientOutEventConferenceControlParticipant;

/*! Event structure used to send changes in network interface.

	- Used by following in events:
		+ #VIDYO_CLIENT_OUT_EVENT_NETWORK_INTERFACE_CHANGED
*/
typedef struct VidyoClientOutEventNetworkInterfaceChanged_
{
	/*! The number of valid interfaces the device has */
    VidyoUint numValidInterfaces;
} VidyoClientOutEventNetworkInterfaceChanged;

/*! Event structure that is mandatory for out event Service response

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE
		+ #VidyoClientOutEventPortalService
*/
typedef struct VidyoClientOutEventPortalServiceMandatoryPart_
{
	/*! Type of request */
	VidyoClientPortalServiceTypeRequest typeRequest;
	/*! Error returned*/
	VidyoClientError error;
	/*! Http error returned by service*/
	VidyoUint httpStatusCode;
	/*! Request identification. This identification provided by application in VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS */
	VidyoUint requestId;
} VidyoClientOutEventPortalServiceMandatoryPart;

/*! Event structure that is notified back to user as part of out event Service for VIDYO_CLIENT_SERVICE_TYPE_DIRECT_CALL

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientOutEventPortalServiceDirectCall_
{
	/*! Type of request */
	VidyoClientPortalServiceTypeRequest typeRequest;
	/*! Error returned*/
	VidyoClientError error;
	/*! Http error returned by service*/
	VidyoUint httpStatusCode;
	/*! Request identification. This identification provided by application in VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS */
	VidyoUint requestId;
} VidyoClientOutEventPortalServiceDirectCall;


#define VIDYO_CLIENT_MAX_TENANT_ADDRESS_SIZE 128
#define VIDYO_CLIENT_LANGUAGE_CODE_SIZE 6
#define VIDYO_CLIENT_PORTAL_SEARCH_SIZE		32

/*! Room mode

	- Used for the following events:
		+ #VIDYO_CLIENT_SERVICE_SEARCH

	- Passed in field previewMode of following structures:
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientRoomMode_
{
	/*!  Room URL */
	char roomURL[MAX_URI_LEN];
	/*!  Is room locked? */
	VidyoBool isRoomLocked;
	/*!  Is a PIN needed to join room? */
	VidyoBool hasPIN;
	/*!  Room PIN */
	char roomPIN[PIN_SIZE];
	/*!  Does it have moderator PIN */
	VidyoBool hasModeratorPIN;
	/*!  Moderator PIN */
	char moderatorPIN[PIN_SIZE];
} VidyoClientRoomMode;


/*! Event structure that is notified back to user as part of out event Service for search request as part of account details

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE  / VIDYO_CLIENT_SERVICE_SEARCH
		+ #VidyoClientOutEventPortalService  in the accountData field
*/
typedef struct VidyoClientAccountData_
{
	/*! Entity ID - Unique in Portal DB */
	char entityID[MAX_EID_SIZE];// Entity ID - Unique in Portal DB
	/*! Participant ID is unique per conference participant , Valid only when user is in conference*/
	char participantID[MAX_EID_SIZE]; // Participant ID is unique per conference participant. 
															// Valid only when user is in conference
	/*! Entity Type */
	VidyoClientPortalServiceEntityType entityType;
	/*! Owner ID */
	char ownerID[MAX_EID_SIZE];
	/*! Display Name */
	char displayName[VIDYO_CLIENT_USERNAME_SIZE];
	/*! Display Name */
	char extension[VIDYO_MAX_EXTENSION_SIZE];
	/*! Display Name */
	char emailAddress[VIDYO_MAX_EMAIL_ADDRESS_SIZE];
	/*! Tenant */
	char tenant[VIDYO_CLIENT_MAX_TENANT_ADDRESS_SIZE];
	/*! Language code */
	char language[VIDYO_CLIENT_LANGUAGE_CODE_SIZE];
	/*! Member status */
	VidyoClientMemberStatus memberStatus;
	/*! Member mode */
	VidyoClientMemberMode memberMode;
	/*!  Can call this person directly? */
	VidyoBool canCallDirect;
	/*! Can this person's room for conference? */
	VidyoBool canJoinMeeting;
	/*! Room status */
	VidyoClientRoomStatus roomStatus;
	/*! Room mode */
	VidyoClientRoomMode roomMode;
	/*! Can control a conference call? */
	VidyoBool canControl;
	/*! Is this entity is in MYContacts? */
	VidyoBool isInMyContacts;
	/*! Audio */
	VidyoBool audio;
	/*! Video */
	VidyoBool video;
	/*! AppShare */
	VidyoBool appShare;
} VidyoClientAccountData;


/*! Event structure that is notified back to user as part of out event Service for search request

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_SEARCH
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientOutEventPortalServiceSearch_
{
	/*! Type of request */
	VidyoClientPortalServiceTypeRequest typeRequest;
	/*! Error returned*/
	VidyoClientError error;
	/*! Http error returned by service*/
	VidyoUint httpStatusCode;
	/*! Request identification.*/
	VidyoUint requestId;
	/*! Total number of users matching the given search criteria */
	VidyoUint total;
	/*! Starting number specified in request */
	VidyoUint start;
	/*! Number of entries in this response */
	VidyoUint numEntries;
	/*! Result of search request */
	VidyoClientError result;
	/*!List of accounts that matched the search*/
    VidyoClientAccountData accountData[VIDYO_CLIENT_PORTAL_SEARCH_SIZE];
} VidyoClientOutEventPortalServiceSearch;


/*! Event structure that is notified back to user as part of out event Service for invite to conference

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_INVITE_TO_CONFERENCE
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientOutEventPortalServiceInviteToConference_
{
	/*! Type of request */
	VidyoClientPortalServiceTypeRequest typeRequest;
	/*! Error returned*/
	VidyoClientError error;
	/*! Http error returned by service*/
	VidyoUint httpStatusCode;
	/*! Request identification.*/
	VidyoUint requestId;
	/*! Result of invite to conference */
	VidyoClientError result;
} VidyoClientOutEventPortalServiceInviteToConference;


/*! Event structure that is notified back to user as part of out event Service for dropping participant

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_DROP_PARTICIPANT
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientOutEventPortalServiceDropParticipant_
{
	/*! Type of request */
	VidyoClientPortalServiceTypeRequest typeRequest;
	/*! Error returned*/
	VidyoClientError error;
	/*! Http error returned by service*/
	VidyoUint httpStatusCode;
	/*! Request identification.*/
	VidyoUint requestId;
	/*! Result of drop participant */
	VidyoClientError result;
} VidyoClientOutEventPortalServiceDropParticipant;


/*! Event structure that is notified back to user as part of out event Service for search request

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_JOIN_CONFERENCE
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientOutEventPortalServiceJoinConference_
{
	/*! Type of request */
	VidyoClientPortalServiceTypeRequest typeRequest;
	/*! Error returned*/
	VidyoClientError error;
	/*! Http error returned by service*/
	VidyoUint httpStatusCode;
	/*! Request identification.*/
	VidyoUint requestId;
	/*! Result of drop participant */
	VidyoClientError result;
	/*! Soap fault */
	VidyoClientSoapFault fault;
} VidyoClientOutEventPortalServiceJoinConference;

/*! Event structure that is notified back to user as part of out event Service for get conference id

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE / VIDYO_CLIENT_SERVICE_GET_CONFERENCE_ID
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientOutEventPortalServiceGetConferenceId_
{
	/*! Type of request */
	VidyoClientPortalServiceTypeRequest typeRequest;
	/*! Error returned*/
	VidyoClientError error;
	/*! Http error returned by service*/
	VidyoUint httpStatusCode;
	/*! Request identification.*/
	VidyoUint requestId;
	/*! Result of get conference id */
	VidyoClientError result;
	/*! Soap fault */
	VidyoClientSoapFault fault;
	/*! Conference Id */
	char conferenceID[MAX_EID_SIZE];
} VidyoClientOutEventPortalServiceGetConferenceId;

/*! Event structure that is notified back to user as part of out event Service

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE
		+ #VidyoClientOutEventPortalService
*/

typedef struct VidyoClientOutEventPortalService_
{
	union 
	{
		VidyoClientOutEventPortalServiceMandatoryPart mandatory;
		VidyoClientOutEventPortalServiceDirectCall directCall;
		VidyoClientOutEventPortalServiceSearch search;
		VidyoClientOutEventPortalServiceInviteToConference inviteToConference;
		VidyoClientOutEventPortalServiceDropParticipant dropParticipant;
		VidyoClientOutEventPortalServiceJoinConference joinConference;
		VidyoClientOutEventPortalServiceGetConferenceId conferenceId;
	} response;
} VidyoClientOutEventPortalService;


/*! Event structure that is notified back to user for logs

	- Used for the following events:
		+ #VIDYO_CLIENT_OUT_EVENT_LOG 
		+ #VidyoClientOutEventLog
*/
typedef struct VidyoClientOutEventLog_
{
	char message[VIDYO_CLIENT_MAX_LOG_LEN];
} VidyoClientOutEventLog;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_GROUP_COMMAND
*/
typedef struct VidyoClientOutEventGroupCommand_
{
	/*! Vidyo URI of remote participant that sent group command. */
	char uri[URI_LEN];
	/*! Display name of remote participant that sent group command. */
	char displayName[USERID_SIZE];
	/*! Message (contents) to be sent. */
	char command[MAX_COMMAND_LEN];
} VidyoClientOutEventGroupCommand;

/*! Event structure
	- Used by following out events:
		+ #VIDYO_CLIENT_OUT_EVENT_PRIVATE_COMMAND
*/
typedef struct VidyoClientOutEventPrivateCommand_
{
	/*! Vidyo URI of remote participant that sent private command. */
	char uri[URI_LEN];
	/*! Display name of remote participant that sent private command. */
	char displayName[USERID_SIZE];
	/*! Message (contents) to be sent. */
	char command[MAX_COMMAND_LEN];
} VidyoClientOutEventPrivateCommand;

/*! Event structure
 
	- Used by following in events:
    + #VIDYO_CLIENT_OUT_EVENT_IS_PORTAL_AVAILABLE
*/
typedef struct VidyoClientOutEventIsPortalAvailable_
{
    /*! A unique request ID to match the in and its corresponding out event - should be a copy of in event */
    VidyoUint	requestId;
    char portalUri[URI_LEN];
    VidyoBool isPortalAvailable;
} VidyoClientOutEventIsPortalAvailable;



/*******************************************************************************
 Parameter structures for requests from GUI to Vidyo Client Library
*******************************************************************************/

/*! @struct VidyoClientRequestConfiguration
	@brief  Request structure
	@details - Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CONFIGURATION
		+ #VIDYO_CLIENT_REQUEST_SET_CONFIGURATION

	@var VidyoClientRequestConfiguration::microphones [out]
		Array of values for the names of attached audio input (capture/microphone) devices.
	@var VidyoClientRequestConfiguration::microphonePhyDeviceName [out]
		Array of values for the physical device names of attached audio input (capture/microphone) devices.
	@var VidyoClientRequestConfiguration::microphoneVoiceProcessingSupport [out]
		Array of values indicating whether voice processing is supported for audio input (capture/microphone) devices.
	@var VidyoClientRequestConfiguration::numberMicrophones  [out]
		Number of attached audio input (capture/microphone) devices.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestConfiguration::currentMicrophone  [in,out]
		Index of currently selected audio input (capture/microphone) device.  Range of values
		0~UINT_MAX, UINT_MAX designating no current selection.
	@var VidyoClientRequestConfiguration::speakers [out]
		Array of values for the names of attached audio output (playback/speaker) devices.
	@var VidyoClientRequestConfiguration::speakerPhyDeviceName [out]
		Array of values for the physical device names of the attached audio output (playback/speaker) devices.
	@var VidyoClientRequestConfiguration::numberSpeakers [out]
		Number of attached audio output (playback/speaker) devices.
		Range of values 0~UINT_MAX.
	@var VidyoClientRequestConfiguration::currentSpeaker [in,out]
		Index of currently selected audio output (playback/speaker) device.  Range of values
		0~UINT_MAX, UINT_MAX designating no current selection.
	@var VidyoClientRequestConfiguration::cameras [out]
		Array of values for the names of attached video (capture/camera) devices.
     @var VidyoClientRequestConfiguration::labels [out]
         Array of values for the labels(name and id) of attached video (capture/camera) devices.
	@var VidyoClientRequestConfiguration::numberCameras [out]
		Number of attached video (capture/camera) devices.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestConfiguration::currentCamera [in,out]
		Index of currently selected video (capture/camera) device.  Range of values
		0~UINT_MAX, UINT_MAX designating no current selection.
	@var VidyoClientRequestConfiguration::enableFeccEndpoint [in,out]
		Non-zero value if endpoint camera is controllable, Zero value if endpoint camera is not
		controllable.
	@var VidyoClientRequestConfiguration::enableFeccController [in,out]
		Non-zero value if endpoint can send FECC commands, Zero value if endpoint cannot send
		FECC commands.
	@var VidyoClientRequestConfiguration::vidyoProxies [out]
		Array of values for the IP addresses and ports of configured VidyoProxy entities.
		Format of individual values is <b>\<IP address\>:\<port\></b>.
	@var VidyoClientRequestConfiguration::numberVidyoProxies [out]
		Number of configured VidyoProxy entities.
		Range of values 0~UINT_MAX, but currently
		limited to 0 or 1.
	@var VidyoClientRequestConfiguration::currentVidyoProxy [out]
		Index of currently configured VidyoProxy entity.
		Range of values
		0~UINT_MAX, but currently limited to 0.
	@var VidyoClientRequestConfiguration::userID [in,out]
		Username to sign in with, as known to VidyoPortal.  Encoded as UTF-8.
	@var VidyoClientRequestConfiguration::password [in,out]
		Key allocated by VidyoPortal to be used in place of password.  This value should be
		acquired through login procedure with VidyoPortal.
	@var VidyoClientRequestConfiguration::serverAddress [in,out]
		Hostname or IP address of VidyoManager to be used.
	@var VidyoClientRequestConfiguration::serverPort [in,out]
		Port of VidyoManager to be used.
	@var VidyoClientRequestConfiguration::vidyoProxyAddress [in,out]
		VidyoProxy hostname or IP address.  *Deprecated*.
	@var VidyoClientRequestConfiguration::vidyoProxyPort [in,out]
		VidyoProxy port.   *Deprecated*.
	@var VidyoClientRequestConfiguration::webProxyAddress [in,out]
		Web proxy hostname or IP address, used when parameter proxySettings does set bit for
		PROXY_WEB_LOCAL_MANUAL.
	@var VidyoClientRequestConfiguration::webProxyPort [in,out]
		Web proxy port, used when parameter proxySettings does set bit for PROXY_WEB_LOCAL_MANUAL.
	@var VidyoClientRequestConfiguration::webProxyUsername [in,out]
		Web proxy username, used when parameter proxySettings does set bit for PROXY_WEB_ENABLE.
	@var VidyoClientRequestConfiguration::webProxyPassword [in,out]
		Web proxy password, used when parameter proxySettings does set bit for PROXY_WEB_ENABLE.
	@var VidyoClientRequestConfiguration::webProxyIeAddress [out]
		Web proxy hostname or IP address, used when parameter proxySettings does set bit
		for PROXY_WEB_IE_MANUAL.  Cannot be changed via request
		#VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, since value comes from underlying platform.
	@var VidyoClientRequestConfiguration::webProxyIePort [out]
		Web proxy port, used when parameter proxySettings does set bit for PROXY_WEB_IE_MANUAL.
		Cannot be changed via request #VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, since value comes
		from underlying platform.
	@var VidyoClientRequestConfiguration::portalAddress [in,out]
		@details Base URL for accessing SOAP services on the VidyoPortal
		(e.g. http://example.vidyo.com/services).
	@var VidyoClientRequestConfiguration::ringtoneDeviceName [in,out]
		Name of device to play ring tone for inbound calls.  Used in conjunction with
		event #VIDYO_CLIENT_IN_EVENT_PLAY_RINGTONE.
	@var VidyoClientRequestConfiguration::verifyCertPortalAcct [in,out]
		@details Name of the portal account (address and port) for which Certificate authenticity check is
		disabled by user temporarily for that specific username.
	@var VidyoClientRequestConfiguration::webProxyScriptUrl [in,out]
		URL for Web proxy PAC script, used when parameter proxySettings does set bit for #PROXY_WEB_LOCAL_AUTO_CONFIG_SCRIPT.
	@var VidyoClientRequestConfiguration::webProxyIeScriptUrl [out]
		URL for Web proxy PAC script, used when parameter proxySettings does set bit for #PROXY_WEB_IE_AUTO_CONFIG_SCRIPT.
		Cannot be changed via request #VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, since value comes from underlying platform.
	@var VidyoClientRequestConfiguration::mediaLowPort [in,out]
		Lowest value of IP source port to be used for media connections.  Range of allowed
		values 1~65530.
	@var VidyoClientRequestConfiguration::mediaHighPort [in,out]
		Highest value of IP source port to be used for media connections.  Range of allowed
		values 6~65535.
	@var VidyoClientRequestConfiguration::proxySettings [in,out]
		Configuration of use of VidyoProxy and web proxies.  See definition of
		following constants, in VidyoClientConstants.h:
		- #PROXY_VIDYO_AUTO (1<<1)  *Deprecated*.
		- #PROXY_VIDYO_MANUAL (1<<2) *Deprecated*.
		- #PROXY_VIDYO_FORCE (1)
		- #PROXY_WEB_ENABLE (1<<3)
		- #PROXY_WEB_IE (1<<4)
		- #PROXY_WEB_LOCAL (1<<5)
		- #PROXY_WEB_IE_AUTO_DETECT (1<<6)
		- #PROXY_WEB_IE_AUTO_CONFIG_SCRIPT (1<<7)
		- #PROXY_WEB_IE_MANUAL (1<<8)
		- #PROXY_WEB_LOCAL_AUTO_DETECT (1<<9)
		- #PROXY_WEB_LOCAL_AUTO_CONFIG_SCRIPT (1<<10)
		- #PROXY_WEB_LOCAL_MANUAL (1<<11)
 		- #PROXY_VIDYO_FORCE_TO_VM (1<<12)
		- #PROXY_VIDYO_DO_NOT_USE_TO_VR (1<<13) 
	@var VidyoClientRequestConfiguration::videoPreferences [in,out]
		Configuration of own video resolution and frame rate.  See definition of
		VidyoClientVideoPreferences.
	@var VidyoClientRequestConfiguration::enableLogging [in,out]
		Non-zero value for logging enabled, zero value for logging disabled.  Currently not
		supported.
	@var VidyoClientRequestConfiguration::enableAutoAnswer [in,out]
		@details Non-zero value for auto-answer of inbound calls enabled, zero value for auto-answer of
		inbound calls disabled.
	@var VidyoClientRequestConfiguration::enableForceProxy [out]
		@details Non-zero value for forced use of VidyoProxy enabled, zero value for forced use of
		VidyoProxy disabled.
	@var VidyoClientRequestConfiguration::enableLogWindow [in,out]
		Non-zero value for log settings window enabled, zero value for log settings window
		disabled.  Currently not supported.
	@var VidyoClientRequestConfiguration::enableEntryTone [in,out]
		Non-zero value for entry and exit tones enabled, zero value for entry and exit tones
		disabled.  It is still responsibility of GUI to manage logic for when to play entry
		and exit tones, using other events provided by this API.
	@var VidyoClientRequestConfiguration::enableEchoDetection [in,out]
		Non-zero value for echo detection enabled, zero value for echo detection disabled.
	@var VidyoClientRequestConfiguration::enableEchoCancellation [in,out]
		Non-zero value for echo cancellation enabled, zero value for echo cancellation disabled.
	@var VidyoClientRequestConfiguration::enableFullScreenVideo [in,out]
		Non-zero value for full-screen on joining of conference enabled, zero value for
		full-screen on joining of conference disabled.  It is still responsibility of GUI to
		manage logic for actual display of a video layout in full-screen, using other events
		provided by this API.
	@var VidyoClientRequestConfiguration::showToolbarInFullScreenVideo [in,out]
		Non-zero value for showing GUI controls (toolbar) while full-screen enabled, zero value
		for showing GUI controls (toolbar) while full-screen disabled.  It is still
		responsibility of GUI to manage logic for actual display of GUI controls while
		full-screen, using other events provided by this API.
	@var VidyoClientRequestConfiguration::enableAudioAGC [in,out]
		@details Non-zero value for audio AGC (Automatic Gain Control) enabled, zero value for audio AGC
		disabled.
	@var VidyoClientRequestConfiguration::enableAutoStart [in,out]
		@details Non-zero value for auto-start of application on login enabled, zero value for auto-start
		disabled.
	@var VidyoClientRequestConfiguration::enableAutoLogIn [in,out]
		@details Non-zero value for auto-start of application login enabled when application starts, zero 
		value for auto-login disabled. (see specific client for implementation details)
	@var VidyoClientRequestConfiguration::enableShowConfParticipantName [in,out]
		@details Non-zero value for labeling of video layout with participant display names enabled, zero
		value for labeling disabled.
	@var VidyoClientRequestConfiguration::enableMuteMicrophoneOnJoin [in,out]
		@details Non-zero value for muting of microphone device when conference or call entered, zero
		value for no muting.
	@var VidyoClientRequestConfiguration::enableHideCameraOnJoin [in,out]
		@details Non-zero value for hiding of camera device when conference or call entered, zero
		value for no hiding.
	@var VidyoClientRequestConfiguration::enableMuteSpeakerOnJoin [in,out]
		@details Non-zero value for muting of speaker device when conference or call entered, zero
		value for no muting.
	@var VidyoClientRequestConfiguration::enableEulaAgreed [in,out]
		@details Non-zero value for terms of EULA (End User License Agreement) agreed to by user, zero
		value for not yet agreed.
	@var VidyoClientRequestConfiguration::enableRendering [in,out]
		Non-zero value to enable rendering, zero value to disable rendering.
	@var VidyoClientRequestConfiguration::enableBackgrounding [in,out]
		Non-zero value to enable backgrounding for Mobile platforms, zero value to disable backgrounding.
	@var VidyoClientRequestConfiguration::enableFullDisplaySharing [in,out]
		Non-zero value for Full Display Sharing enabled, zero value for Full Display Sharing disabled.
	@var VidyoClientRequestConfiguration::selfViewLoopbackPolicy [in,out]
		@details 0 for participant to see self video, 1 for disabling self video and 2 for enabling self video
		only when there are no other participant in conference.
	@var VidyoClientRequestConfiguration::enableLowBackgroundTimeout [in,out]
        @details 0 means use use default high background timeout so that endpoint remain online and can be
        called while in background. 1 means low timeout value will be used and after timeout the endpoint will
        go offline at VidyoPortal and will not be able added or called to join a conference until the application
        is brought to foreground and it goes online.
	@var VidyoClientRequestConfiguration::allowLetterBoxVideoScaling [in,out]
		Non-zero value for allow scaling of video in letter box (no cropping), zero value for disallow scaling of video in letter box (will crop and might be zoomed).
     @var VidyoClientRequestConfiguration::enableTilesToolbars [in,out]
         Value that indicating whether toolbar and statusbar are enabled in tiles renderer. Only for Tiles renderer.
*/
typedef struct VidyoClientRequestConfiguration_
{
	VidyoUint8 microphones[MAX_DEVICE_NUMBER][DEVICE_NAME_SIZE];
	VidyoUint8 microphonePhyDeviceName[MAX_DEVICE_NUMBER][DEVICE_NAME_SIZE];
	VidyoBool microphoneVoiceProcessingSupport[MAX_DEVICE_NUMBER];
	VidyoUint numberMicrophones;
	VidyoUint currentMicrophone;

	VidyoUint8 speakers[MAX_DEVICE_NUMBER][DEVICE_NAME_SIZE];
	VidyoUint8 speakerPhyDeviceName[MAX_DEVICE_NUMBER][DEVICE_NAME_SIZE];
	VidyoUint numberSpeakers;
	VidyoUint currentSpeaker;

	VidyoUint8 cameras[MAX_DEVICE_NUMBER][DEVICE_NAME_SIZE];
    VidyoUint8 cameraLabels[MAX_DEVICE_NUMBER][DEVICE_NAME_SIZE];
	VidyoUint numberCameras;
	VidyoUint currentCamera;

	VidyoUint enableFeccEndpoint;
	VidyoUint enableFeccController;

	VidyoUint8 vidyoProxies[SIGNIN_VIDYO_PROXY_NUMBER]
		[SIGNIN_VIDYO_PROXY_ADDRESS_SIZE+SIGNIN_VIDYO_PROXY_PORT_SIZE+1];
	VidyoUint numberVidyoProxies;
	VidyoUint currentVidyoProxy;

	VidyoUint8 userID[FIELD_SIZE];
	VidyoUint8 password[FIELD_SIZE];
	VidyoUint8 serverAddress[URI_LEN];
	VidyoUint8 serverPort[SERVERPORT_SIZE];
	VidyoUint8 vidyoProxyAddress[URI_LEN];
	VidyoUint8 vidyoProxyPort[SERVERPORT_SIZE];
	VidyoUint8 webProxyAddress[URI_LEN];
	VidyoUint8 webProxyPort[SERVERPORT_SIZE];
	VidyoUint8 webProxyUsername[FIELD_SIZE];
	VidyoUint8 webProxyPassword[FIELD_SIZE];
	VidyoUint8 webProxyIeAddress[URI_LEN];
	VidyoUint8 webProxyIePort[SERVERPORT_SIZE];
	VidyoUint8 portalAddress[FIELD_SIZE];
	VidyoUint8 ringtoneDeviceName[FIELD_SIZE];
	VidyoUint8 verifyCertPortalAcct[MAX_PORTAL_ADDRESS];
	VidyoUint8 webProxyScriptUrl[URI_LEN];
	VidyoUint8 webProxyIeScriptUrl[URI_LEN];

	VidyoUint mediaLowPort;
	VidyoUint mediaHighPort;
	VidyoUint proxySettings;
	VidyoClientVideoPreferences videoPreferences;

	VidyoUint enableLogging;
	VidyoUint enableAutoAnswer;
	VidyoUint enableForceProxy;
	VidyoUint enableLogWindow;
	VidyoUint enableEntryTone;
	VidyoUint enableEchoDetection;
	VidyoUint enableEchoCancellation;
	VidyoUint enableFullScreenVideo;
	VidyoUint showToolbarInFullScreenVideo;
	VidyoUint enableAudioAGC;
	VidyoUint enableAutoStart;
	VidyoUint enableAutoLogIn;
	VidyoUint enableShowConfParticipantName;
	VidyoUint enableMuteMicrophoneOnJoin;
	VidyoUint enableHideCameraOnJoin;
	VidyoUint enableMuteSpeakerOnJoin;
	VidyoUint enableEulaAgreed;
	VidyoUint enableRendering;
	VidyoUint enableBackgrounding;
	VidyoUint enablePersonalRoomForSchedulingMeeting;
	VidyoUint enableFullDisplaySharing;
	VidyoUint selfViewLoopbackPolicy;
    VidyoUint enableLowBackgroundTimeout;
	VidyoUint allowLetterBoxVideoScaling;
    VidyoBool enableTilesToolbars;
} VidyoClientRequestConfiguration;

/*! Request structure

	- Used by following in events:
		+ #VIDYO_CLIENT_REQUEST_GET_CONNECTIVITY_INFO
*/
typedef struct VidyoClientRequestConnectivityInfo_
{
	/*!
		Hostname or IP address of VidyoManager
	*/
	char serverAddress[SIGNIN_SERVERADDRESS_SIZE];
	/*!
		Port of VidyoManager address
	*/
	char serverPort[SIGNIN_SERVERPORT_SIZE];
	/*!
		VIDYO_TRUE if connection to VidyoManager would be secured using TLS,
		VIDYO_FALSE if connection to VidyoManager would not be secure.
	*/
	VidyoBool serverSecured;
	/*!
		Identity of Vidyo Manager to which end point is assigned. This value was
		acquired through login procedure with VidyoPortal.
	*/
	char vmIdentity[VIDYO_MANAGER_ID_SIZE];
	/*!
		Username to sign in with, as known to VidyoPortal.  Encoded as UTF-8.
	*/
	char userName[SIGNIN_USERNAME_SIZE];
	/*!
		Base URL used for accessing SOAP services on the VidyoPortal
		(e.g. http://example.vidyo.com/services).
	*/
	char portalAddress[SIGNIN_PORTALADDRESS_SIZE];
	/*!
		Array of portal version
	*/
	char portalVersion[SIGNIN_PORTALVERSION_SIZE];
	/*!
		Location tag assigned to the endpoint. This is configured on portal to indicate the
		location of an endpoint and is used to assign a VidyoRouter group to the endpoint
		when joining a call.
	*/
	char locationTag[ENDPOINT_LOCATION_TAG_SIZE];
	/*!
		Array of VidyoProxy hostnames or IP addresses.  Only 0 or 1 VidyoProxy addresses
		are currently supported.
	*/
	char vidyoProxyAddress[SIGNIN_VIDYO_PROXY_ADDRESS_SIZE];
	/*!
		Array of VidyoProxy ports.  Only 0 or 1 VidyoProxy addresses are currently supported.
		Each port is used with corresponding value found in the same index of preceding
		parameter vidyoProxyAddress.
	*/
	char vidyoProxyPort[SIGNIN_VIDYO_PROXY_PORT_SIZE];
	/*!
		VIDYO_TRUE if username given in preceding parameter userName is ephemeral
		value allocated for guest login, VIDYO_FALSE for permanent users.
	*/
	VidyoBool guestLogin;

	/*!< External IP address of machine on which client is running as seen by web server. */
	char clientExternalIPAddress[MAX_IPADDRESS_LEN];
	/*!<
		The type of Proxy available to the client.
		If value is VIDYO_CLIENT_VIDYO_PROXY vidyoProxyAddress should have valid proxy address
		and vidyoProxyPort should have valid proxy port. Instead if value is VIDYO_CLIENT_REVERSE_PROXY
		reverseProxyAddress should have valid proxy address and reverseProxyPort should have valid proxy port.
		In both cases numberProxies will provide the number of proxies available to client.
	*/
	VidyoClientProxyType proxyType;
	/*!<
		ReverseProxy hostnames or IP addresses used to connect to VidyoManager.
	*/
	char reverseProxyAddress[SIGNIN_VIDYO_PROXY_ADDRESS_SIZE];
	/*!<
		ReverseProxy port used to connect to VidyoManager.
	*/
	char reverseProxyPort[SIGNIN_VIDYO_PROXY_PORT_SIZE];
} VidyoClientRequestConnectivityInfo;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_EID
*/
typedef struct VidyoClientRequestGetEid_
{
	/*!
		EID (Endpoint IDentifier) uniquely identifies VidyoClient installation and is
		used as identifier of VidyoClient towards VidyoManager and VidyoPortal.
	*/
	char EID[MAX_EID_SIZE];
} VidyoClientRequestGetEid;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_LID
*/
typedef struct VidyoClientRequestGetLid_
{
	/*!
		LID (Licensing IDentifier) is used as unique identifier of VidyoClient
		installation for licensing purposes. The LID should be used in sent installation
		license request to identify installation to VidyoPortal.
	*/
	char LID[MAX_EID_SIZE];
} VidyoClientRequestGetLid;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PID
*/
typedef struct VidyoClientRequestGetPid_
{
	/*!
		PID (Participant IDentifier) assigned to VidyoClient by VidyoManager.
		The participant identifier is in-conference unique identifier used by
		VidyoClient to identify itself when joining conference on VidyoRouter.
	*/
	char PID[MAX_PID_SIZE];
} VidyoClientRequestGetPid;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_ACTIVATE_EID
*/
typedef struct VidyoClientRequestActivateEid_
{
	/*!
		LAC (License Activation Key) is provided by VidyoPortal when license is requested.
		LAC must be passed to VidyoClient as verification that VidyoPortal has authorized
		activation of installation license.
	*/
	char lacKey[LAC_KEY_SIZE];
} VidyoClientRequestActivateEid;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_IN
		+ #VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_IN
		+ #VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT
		+ #VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_OUT
*/
typedef struct VidyoClientRequestVolume_
{
	/*!
		Volume (requests ending in AUDIO_OUT) or gain level (requests ending in AUDIO_IN) of
		local audio device.  Use requests ending in AUDIO_IN to control gain level of
		microphone device, requests ending in AUDIO_OUT to control volume of speaker device.
		Range of allowed values 0~65535.
	*/
	VidyoUint volume;
} VidyoClientRequestVolume;

/*! @struct VidyoClientWindowShares
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES
		+ #VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES

	@var VidyoClientWindowShares::remoteAppUri [in,out]
		Array of Vidyo URI values for remote participants providing application window shares.
		Output parameter for both #VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES and
		#VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES.  Input parameter for
		#VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, used in conjunction with parameter setApp to
		determine which application window share to show in the video layout.  Recommended
		for GUI to always use #VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES just prior to
		#VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, passing pointer to same copy of struct
		#VidyoClientRequestWindowShares, in order for this parameter to be set correctly.
		Valid application URI are filled from index 1 and 0th index is not used.
	@var VidyoClientWindowShares::remoteAppName [out]
		Array of values for application window share names or captions.  The order of this
		array matches that for the parameter remoteAppUri.
		Valid application name are filled from index 1 and 0th index is not used.
	@var VidyoClientWindowShares::numApp [out]
		Number of entries in the parameters remoteAppUri and remoteAppName.  Range of values
		0~UINT_MAX.
	@var VidyoClientWindowShares::currApp [out]
		Index of entry in parameter remoteAppUri, to use for determining which application
		window share is currently shown in the video layout.  Only valid for
		#VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES.  A value of zero means no application window
		share is currently shown in the video layout.  Range of allowed values -INT_MAX~INT_MAX.
	@var VidyoClientWindowShares::eventUri [in]
		URI of the current application being shared.  Used to stop sharing when remote
		stopped to share.
	@var VidyoClientWindowShares::newApp [in]
		Index of entry in parameter remoteAppUri, to use for determining which application
		window share to show in the video layout.  Only valid for
		#VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES.  A value of zero causes no application window
		share to be shown in the video layout.  Range of allowed values -INT_MAX~INT_MAX.

*/
typedef struct VidyoClientWindowShares_
{
	char remoteAppUri[MAX_REMOTE_SHARE_APP][MAX_URI_LEN];
	char remoteAppName[MAX_REMOTE_SHARE_APP][MAX_URI_LEN];
	VidyoInt numApp;
	VidyoInt currApp;
	char eventUri[MAX_URI_LEN];
	VidyoInt newApp;
} VidyoClientWindowShares;

/*! @struct VidyoClientRequestWindowShares
	@brief Request structure
	@details - Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES
		+ #VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES

	@var VidyoClientRequestWindowShares::requestType [in]
			The type of request:
			- list
			- change
			- stop
			- toggle


	@var VidyoClientRequestWindowShares::shareList [in,out]
		The details of sharable windows.

	@note LIST_SHARING_WINDOWS - Shall be used only for #VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES.
	Other values are valid only with #VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES.

*/
typedef struct VidyoClientRequestWindowShares_
{

	VidyoClientWindowShareRequestType requestType;
	VidyoClientWindowShares shareList;
} VidyoClientRequestWindowShares;

/*! Request structure

	- Sent by following requests:
		+ #VIDYO_CLIENT_REQUEST_ENABLE_APP_SHARE
*/
typedef struct VidyoClientRequestEnableAppShare_
{
	/*!
		VIDYO_TRUE to enable the Application share
		VIDYO_FALSE to disable the Application share
		Use VIDYO_CLIENT_REQUEST_ENABLE_APP_SHARE to enable/disable the application share
		device.
	*/
	VidyoBool isEnable;
} VidyoClientRequestEnableAppShare;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_SET_LABEL
*/
typedef struct VidyoClientRequestSetLabel_
{
	/*! Identity of label to be set. */
	VidyoClientLabelType labelID;
	/*! Actual text to be used - UTF8 encoded. */
	char labelText[MAX_LABEL_STRING_SIZE];
} VidyoClientRequestSetLabel;

/*! Request structure

	- Sent by following requests:
		+ #VIDYO_CLIENT_REQUEST_SET_PARTICIPANT_BORDER
*/
typedef struct VidyoClientRequestSetBorder_
{
	/*!
		VIDYO_TRUE to show the Participant border
		VIDYO_FALSE to hide the Participant border
		Use VIDYO_CLIENT_REQUEST_SET_PARTICIPANT_BORDER to show / hide the participant border
		(Available only on Tiles version of VidyoClient)
	*/
	VidyoBool showBorder;
} VidyoClientRequestSetBorder;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PORTAL_HISTORY
		+ #VIDYO_CLIENT_REQUEST_SET_PORTAL_HISTORY

	@note   CurrentPortalHistory always FIRST.
*/
typedef struct VidyoClientRequestPortalHistory_
{
	/*! Combined string from URI and User Name. The format of portalUriName is portal=PortalAddress&un=UserName */
	VidyoUint8 portalUriName[MAX_PORTAL_HISTORY_NUMBER][MAX_PORTAL_HISTORY_SIZE];
	/*! Number of entries in the parameter portalUriName. */
	VidyoUint numberPortalHistory;
} VidyoClientRequestPortalHistory;

/*! @struct VidyoClientRequestSnapResize
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_SNAP_RESIZE

	@var VidyoClientRequestSnapResize::width [in,out]
		Prospective width of video layout region.  Value will be changed to closest
		allowed, that preserves aspect ratio.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::height [in,out]
		Prospective height of video layout region.  Value will be changed to closest
		allowed, that preserves aspect ratio.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::curWidth [in]
		Current width of video layout region.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::curHeight [in]
		Current height of video layout region.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::minWidth [in]
		Minimum acceptable width of video layout region.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::minHeight [in]
		Minimum acceptable height of video layout region.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::maxWidth [in]
		Maximum acceptable width of video layout region.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::maxHeight [in]
		Maximum acceptable height of video layout region.  Range of allowed values 0~UINT_MAX.
	@var VidyoClientRequestSnapResize::sizingmethod [in]
		Constraints on prospective resize operation.  See definition of
		#VidyoClientResizingMethod.
*/
typedef struct VidyoClientRequestSnapResize_
{
	VidyoUint width;
	VidyoUint height;
	VidyoUint curWidth;
	VidyoUint curHeight;
	VidyoUint minWidth;
	VidyoUint minHeight;
	VidyoUint maxWidth;
	VidyoUint maxHeight;
	VidyoClientResizingMethod sizingmethod;
} VidyoClientRequestSnapResize;

/*! Request structure

	- Sent by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_IN
		+ #VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_OUT
		+ #VIDYO_CLIENT_REQUEST_GET_MUTED_VIDEO
		+ #VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_AUDIO_IN
		+ #VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_VIDEO
*/
typedef struct VidyoClientRequestGetMuted_
{
	/*!
		VIDYO_TRUE if local media device for specified request muted, VIDYO_FALSE if local
		media device for specified request not muted.  Use
		#VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_IN to check local muting of microphone device,
		#VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_OUT to check local muting of speaker device,
		and #VIDYO_CLIENT_REQUEST_GET_MUTED_VIDEO to check local muting of camera device.
		Use #VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_AUDIO_IN to check remote muting of microphone
		device.
	*/
	VidyoBool isMuted;
} VidyoClientRequestGetMuted;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_LANGUAGE
*/
typedef struct VidyoClientRequestGetLanguage_
{
	/*! Currently selected display language.  See definition of VidyoClientLanguageCode. */
	VidyoClientLanguageCode Languagecode;
} VidyoClientRequestGetLanguage;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_SECURE_CONNECTION
*/
typedef struct VidyoClientRequestSecureConnection_
{
	/*! Secure connection state */
	VidyoUint secureConnectionState;
	/*! Certificate */
	VidyoUint8 verifyCertPortalAcct[MAX_PORTAL_ADDRESS];
} VidyoClientRequestSecureConnection;

/*! @struct VidyoClientRequestEchoRecommendation
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_ECHO_RECOMMENDATION

	@var VidyoClientRequestEchoRecommendation::speakerIndex [in]
		Selected speaker index.
	@var VidyoClientRequestEchoRecommendation::micIndex [in]
		Selected Mic index.
	@var VidyoClientRequestEchoRecommendation::echoDisabled [out]
		Echo disabled recommendation (VIDYO_TRUE or VIDYO_FALSE.).
*/
typedef struct VidyoClientRequestEchoRecommendation_
{
	VidyoUint speakerIndex;
	VidyoUint micIndex;
	VidyoBool echoDisabled;
} VidyoClientRequestEchoRecommendation;

/*! @struct VidyoClientRequestCheckRecommended
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_CHECK_RECOMMENDED

	@var VidyoClientRequestCheckRecommended::deviceType [in]
		Selected device type - #VIDYO_CLIENT_DEVICE_TYPE_AUDIO_OUT or #VIDYO_CLIENT_DEVICE_TYPE_AUDIO_IN.
	@var VidyoClientRequestCheckRecommended::deviceIndex [in]
		Selected device index.
	@var VidyoClientRequestCheckRecommended::isRecommended [out]
		Device is recommended or NOT (VIDYO_TRUE or VIDYO_FALSE.)
*/
typedef struct VidyoClientRequestCheckRecommended_
{
	VidyoClientDeviceType deviceType;
	VidyoUint deviceIndex;
	VidyoBool isRecommended;
} VidyoClientRequestCheckRecommended;

/*! @struct VidyoClientRequestWebProxySettingValid
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_WEB_PROXY_SETTING_VALID

	@var VidyoClientRequestWebProxySettingValid::isConfigComplete [out]
		VIDYO_TRUE if web proxy configuration is complete, VIDYO_FALSE otherwise.
*/
typedef struct VidyoClientRequestWebProxySettingValid_
{
	VidyoBool isConfigComplete;
} VidyoClientRequestWebProxySettingValid;

/*! @struct VidyoClientRequestWebProxySetUsernamePassword
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_SET_WEBPROXY_USERNAME_PASSWORD

	@var VidyoClientRequestWebProxySetUsernamePassword::isSaved [in]
		@details VIDYO_TRUE if the values are to be saved in Configuration, VIDYO_FALSE if volatile
	@var VidyoClientRequestWebProxySetUsernamePassword::webProxyUsername [in,out]
		Web proxy username, used when parameter proxySettings does set bit for PROXY_WEB_ENABLE.
	@var VidyoClientRequestWebProxySetUsernamePassword::webProxyPassword [in,out]
		Web proxy password, used when parameter proxySettings does set bit for PROXY_WEB_ENABLE.
*/
typedef struct VidyoClientRequestWebProxySetUsernamePassword_
{
	VidyoBool isSaved;
	VidyoUint8 webProxyUsername[FIELD_SIZE];
	VidyoUint8 webProxyPassword[FIELD_SIZE];
} VidyoClientRequestWebProxySetUsernamePassword;

/*! @struct VidyoClientRequestCurrentUser
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CURRENT_USER

	@var VidyoClientRequestCurrentUser::currentUserID [out]
		User ID of currently signed in user.
	@var VidyoClientRequestCurrentUser::currentUserDisplay [out]
		Display name of currently signed in user.
	@var VidyoClientRequestCurrentUser::entityId [out]
		Entity ID of currently signed in user.
	@var VidyoClientRequestCurrentUser::extension [out]
		Extension of currently signed in user.
	@var VidyoClientRequestCurrentUser::emailAddress [out]
		Email address of currently signed in user.
	@var VidyoClientRequestCurrentUser::roomUrl [out]
		Room URL of default room of currently signed in user.
	@var VidyoClientRequestCurrentUser::hasPin [out]
		Presence of PIN for default room of currently signed in user.
	@var VidyoClientRequestCurrentUser::roomPin [out]
		Room PIN of currently signed in user.
	@var VidyoClientRequestCurrentUser::hasModeratorPin [out]
		Presence of moderator PIN for the default room of the currently signed in user.
	@var VidyoClientRequestCurrentUser::moderatorPin [out]
		Moderator PIN of currently signed in user for user's default room.
*/
typedef struct VidyoClientRequestCurrentUser_
{
	char currentUserID[USERID_SIZE];
	char currentUserDisplay[USERID_SIZE];
	char entityId[MAX_EID_SIZE];
	char extension[VIDYO_MAX_EXTENSION_SIZE];
	char emailAddress[VIDYO_MAX_EMAIL_ADDRESS_SIZE];
	char roomUrl[URI_LEN];
	VidyoBool hasPin;
	char roomPin[PIN_SIZE];
	VidyoBool hasModeratorPin;
	char moderatorPin[PIN_SIZE];
} VidyoClientRequestCurrentUser;

/*! @struct VidyoClientRequestCallState
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CALL_STATE

	@var    VidyoClientRequestCallState::callState [out]
			Current call state of client @see #VidyoClientCallState
*/
typedef struct VidyoClientRequestCallState_
{
	VidyoClientCallState callState;
} VidyoClientRequestCallState;
/*! @struct VidyoClientRequestSessionDisplayInfo
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CURRENT_SESSION_DISPLAY_INFO

	@var VidyoClientRequestSessionDisplayInfo::sessionDisplayContext [out]
		Current conference state of client.  See definition of VidyoClientSessionDisplayContext.
	@var VidyoClientRequestSessionDisplayInfo:: sessionDisplayText [out]
		If client is in a conference, current text which could be displayed in a window
		caption, to identify the conference to the user.  Encoded as UTF-8.
*/
typedef struct VidyoClientRequestSessionDisplayInfo_
{
	VidyoClientSessionDisplayContext sessionDisplayContext;
	char sessionDisplayText[DISPLAY_CONFERENCE_SIZE];
} VidyoClientRequestSessionDisplayInfo;

/*! @struct VidyoClientRequestParticipantsLimit
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS_LIMIT

	@var VidyoClientRequestParticipantsLimit::bandwidthLimit [out]
		Maximum number of viewable remote participants in video layout, due to current network
		bandwidth.  Range of values 0~16.
	@var VidyoClientRequestParticipantsLimit::cpuLimit [out]
		Maximum number of viewable remote participants in video layout, due to current CPU
		utilization.  Range of values 0~16.
	@var VidyoClientRequestParticipantsLimit::userLimit [out]
		Maximum number of viewable remote participants in video layout, due to use of
		event #VIDYO_CLIENT_IN_EVENT_PARTICIPANTS_LIMIT.  Range of values 0~8 and 16.
*/
typedef struct VidyoClientRequestParticipantsLimit_
{
	VidyoUint bandwidthLimit;
	VidyoUint cpuLimit;
	VidyoUint userLimit;
} VidyoClientRequestParticipantsLimit;

/*! @struct VidyoClientRequestParticipants
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS
		+ #VIDYO_CLIENT_REQUEST_GET_SELECTED_PARTICIPANTS
		+ #VIDYO_CLIENT_OUT_EVENT_SELECTED_PARTICIPANTS_CHANGED

	@var VidyoClientRequestParticipants::name [out]
		Array of values for display name of remote participants in a conference.  Encoded as
		UTF-8.
	@var VidyoClientRequestParticipants::URI [out]
		Array of values for Vidyo URI of remote participants in a conference.
	@var VidyoClientRequestParticipants::numberParticipants [out]
		Number of remote participants in a conference.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestParticipants::haveDockedContentsShare [out]
		Indication of whether contents share is selected for rendering in a docked window.  
		VIDYO_TRUE - contents share is selected for viewing in a docked window.
	@var VidyoClientRequestParticipants::haveFloatingContentsShare [out]
		Indication of whether contents share is selected for rendering in a floating window.  
		VIDYO_TRUE - contents share is selected for viewing in a floating window.
*/
typedef struct VidyoClientRequestParticipants_
{
	char name[MAX_PARTICIPANTS_NUM][FIELD_SIZE];
	char URI[MAX_PARTICIPANTS_NUM][URI_LEN];
	VidyoUint numberParticipants;
	VidyoBool haveDockedContentsShare;
	VidyoBool haveFloatingContentsShare;
} VidyoClientRequestParticipants;

/*! @struct VidyoClientRequestInvitingUser
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_INVITING_USER

	@var VidyoClientRequestInvitingUser::invitingUser [out]
		Display name of originator of inbound call.  Encoded as UTF-8.
*/
typedef struct VidyoClientRequestInvitingUser_
{
	char invitingUser[FIELD_SIZE];
} VidyoClientRequestInvitingUser;

/*! @struct VidyoClientRequestSessionVidyoRouter
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CURRENT_SESSION_VIDYO_ROUTER

	@var VidyoClientRequestSessionVidyoRouter::routerAddress [out]
		Router address.
*/
typedef struct VidyoClientRequestSessionVidyoRouter_
{
	char routerAddress[SERVER_ADDRESS_SIZE];
} VidyoClientRequestSessionVidyoRouter;

/*! @struct VidyoClientRequestFeccList
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_FECC_LIST

	@var VidyoClientRequestFeccList::uri [out]
		Array of Vidyo URI values, one for each remote participant
		that can have its camera controlled.
	@var VidyoClientRequestFeccList::name [out]
		Array of usernames, one for each remote participant
		that can have its camera controlled.
	@var VidyoClientRequestFeccList::privacyMode [out]
		Array of LMI_TRUE or LMI_FALSE value representing privacy ON(=LMI_TRUE) or OFF(=LMI_FALSE) status,
		one for each remote participant that can have its camera controlled.
	@var VidyoClientRequestFeccList::numberParticipants [out]
		Number of Vidyo URI values in parameter uri. Range from 0 to MAX_PARTICIPANTS_NUM.
	@var VidyoClientRequestFeccList::feccParticipantIndex [out]
		The current participant under FECC. If no participant in being controlled value is MAX_PARTICIPANTS_NUM. Range from 0 to MAX_PARTICIPANTS_NUM.
*/
typedef struct VidyoClientRequestFeccList_
{
	char uri[MAX_PARTICIPANTS_NUM][URI_LEN];
	char name[MAX_PARTICIPANTS_NUM][USERID_SIZE];
	VidyoBool privacyMode[MAX_PARTICIPANTS_NUM];
	VidyoUint numberParticipants;
	VidyoUint feccParticipantIndex;
} VidyoClientRequestFeccList;

/*! @struct VidyoClientRequestConferenceInfo
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_CONFERENCE_INFO

	@var VidyoClientRequestConferenceInfo::recording [out]
		VIDYO_TRUE or VIDYO_FALSE to indicate whether conference is recording or not.
	@var VidyoClientRequestConferenceInfo::webcast [out]
		VIDYO_TRUE or VIDYO_FALSE to indicate whether conference is webcast or not.
*/
typedef struct VidyoClientRequestConferenceInfo_
{
	VidyoBool recording;
	VidyoBool webcast;
} VidyoClientRequestConferenceInfo;

/*! @struct VidyoClientRequestBandwidthInfo
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_BANDWIDTH_INFO

	@var VidyoClientRequestBandwidthInfo::AvailSendBwVideo [out]
		Available bandwidth for sending video data, in units of kilobits per second.  Range of
		values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::AvailSendBwAudio [out]
		Available bandwidth for sending audio data, in units of kilobits per second.  Range of
		values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::AvailSendBwApplication [out]
		Available bandwidth for sending application window sharing data, in units of kilobits
		per second.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::AvailSendBwMax [out]
		Available bandwidth for sending all media data, in units of kilobits per second.  Range
		of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualSendBwVideo [out]
		Actual bandwidth for sending video data, in units of kilobits per second.  Range of
		values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualSendBwAudio [out]
		Actual bandwidth for sending audio data, in units of kilobits per second.  Range of
		values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualSendBwApplication [out]
		Actual bandwidth for sending application window sharing data, in units of kilobits
		per second.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualSendBwMax [out]
		Actual bandwidth for sending all media data, in units of kilobits per second.  Range
		of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::AvailRecvBwVideo [out]
		Available bandwidth for receiving video data, in units of kilobits per second.  Range
		of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::AvailRecvBwAudio [out]
		Available bandwidth for receiving audio data, in units of kilobits per second.  Range
		of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::AvailRecvBwApplication [out]
		Available bandwidth for receiving application window sharing data, in units of kilobits
		per second.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::AvailRecvBwMax [out]
		Available bandwidth for receiving all media data, in units of kilobits per second.
		Range of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualRecvBwVideo [out]
		Actual bandwidth for receiving video data, in units of kilobits per second.  Range
		of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualRecvBwAudio [out]
		Actual bandwidth for receiving audio data, in units of kilobits per second.  Range
		of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualRecvBwApplication [out]
		Actual bandwidth for receiving application window sharing data, in units of kilobits
		per second.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestBandwidthInfo::ActualRecvBwMax [out]
		Actual bandwidth for receiving all media data, in units of kilobits per second.
		Range of values 0~UINT_MAX.
*/
typedef struct VidyoClientRequestBandwidthInfo_
{
	VidyoUint AvailSendBwVideo;
	VidyoUint AvailSendBwAudio;
	VidyoUint AvailSendBwApplication;
	VidyoUint AvailSendBwMax;
	VidyoUint ActualSendBwVideo;
	VidyoUint ActualSendBwAudio;
	VidyoUint ActualSendBwApplication;
	VidyoUint ActualSendBwMax;
	VidyoUint AvailRecvBwVideo;
	VidyoUint AvailRecvBwAudio;
	VidyoUint AvailRecvBwApplication;
	VidyoUint AvailRecvBwMax;
	VidyoUint ActualRecvBwVideo;
	VidyoUint ActualRecvBwAudio;
	VidyoUint ActualRecvBwApplication;
	VidyoUint ActualRecvBwMax;
} VidyoClientRequestBandwidthInfo;

/*! @struct VidyoClientRequestFrameRateInfo
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_VIDEO_FRAME_RATE_INFO

	@var VidyoClientRequestFrameRateInfo::captureFrameRate [out]
		Current frame rate of video as captured from the local device, in frames per second.
		Range of values 0~UINT_MAX.
	@var VidyoClientRequestFrameRateInfo::encodeFrameRate [out]
		Current frame rate of video as encoded, in frames per second.  Range of values
		0~UINT_MAX.
	@var VidyoClientRequestFrameRateInfo::sendFrameRate [out]
		Current frame rate of video as sent over the network, in frames per second.  Range of
		values 0~UINT_MAX.
*/
typedef struct VidyoClientRequestFrameRateInfo_
{
	VidyoUint captureFrameRate;
	VidyoUint encodeFrameRate;
	VidyoUint sendFrameRate;
} VidyoClientRequestFrameRateInfo;

/*! @struct VidyoClientRequestMediaInfo
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_MEDIA_INFO

	@var VidyoClientRequestMediaInfo::numIFrames [out]
		Total number of I-frames sent from the client, since the beginning of the current
		conference.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestMediaInfo::numFirs [out]
		Total number of FIR (Full Intra Request) messages received by the client, since the
		beginning of the current conference.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestMediaInfo::numNacks [out]
		Total number of distinct NACK (No ACKnowledgement) messages received by the client,
		since the beginning of the current conference.  Only NACK messages received for
		sequence numbers that are reasonably close to the most recent packet sent are counted.
		Range of values 0~UINT_MAX.
	@var VidyoClientRequestMediaInfo::mediaRTT [out]
		Current estimate of round-trip time for media packets, based on RTCP interactions,
		in units of milliseconds.  Range of values 0~UINT_MAX.
*/
typedef struct VidyoClientRequestMediaInfo_
{
	VidyoUint numIFrames;
	VidyoUint numFirs;
	VidyoUint numNacks;
	VidyoUint mediaRTT;
} VidyoClientRequestMediaInfo;

/*! @struct VidyoClientRequestRateShaperInfo
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_RATE_SHAPER_INFO

	@var VidyoClientRequestRateShaperInfo::delayVideoPriorytyNormal [out]
		Maximum actual delay of packets flowing through normal priority rate shaper queue,
		for sent video data, in units of milliseconds.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numPacketsVideoPriorytyNormal [out]
		Current number of packets in normal priority rate shaper queue, for sent video data.
		Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numFramesVideoPriorytyNormal [out]
		Reserved for future use.
	@var VidyoClientRequestRateShaperInfo::numDroppedVideoPriorytyNormal [out]
		Total number of packets dropped from normal priority rate shaper queue for current
		conference, for sent video data.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::delayVideoPriorutyRetransmit [out]
		Maximum actual delay of packets flowing through high priority rate shaper queue,
		for sent video data, in units of milliseconds.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numPacketsVideoPriorutyRetransmit [out]
		Current number of packets in high priority rate shaper queue, for sent video data.
		Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numFramesVideoPriorutyRetransmit [out]
		Reserved for future use.
	@var VidyoClientRequestRateShaperInfo::numDroppedVideoPriorutyRetransmit [out]
		Total number of packets dropped from high priority rate shaper queue for current
		conference, for sent video data.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::delayAppPriorityNormal [out]
		Maximum actual delay of packets flowing through normal priority rate shaper queue,
		for sent application window sharing data, in units of milliseconds.  Range of values
		0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numPacketsAppPriorityNormal [out]
		Current number of packets in normal priority rate shaper queue, for sent application
		window sharing data.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numFramesAppPriorityNormal [out]
		Reserved for future use.
	@var VidyoClientRequestRateShaperInfo::numDroppedAppPriorityNormal [out]
		Total number of packets dropped from normal priority rate shaper queue for current
		conference, for sent application window sharing data.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::delayAppPriorityRetransmit [out]
		Maximum actual delay of packets flowing through high priority rate shaper queue,
		for sent application window sharing data, in units of milliseconds.  Range of
		values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numPacketsAppPriorityRetransmit [out]
		Current number of packets in high priority rate shaper queue, for sent application
		window sharing data.  Range of values 0~UINT_MAX.
	@var VidyoClientRequestRateShaperInfo::numFramesAppPriorityRetransmit [out]
		Reserved for future use.
	@var VidyoClientRequestRateShaperInfo::numDroppedAppPriorityRetransmit [out]
		Total number of packets dropped from high priority rate shaper queue for current
		conference, for sent application window sharing data.  Range of values 0~UINT_MAX.
*/
typedef struct VidyoClientRequestRateShaperInfo_
{
	 VidyoUint delayVideoPriorytyNormal;
	 VidyoUint numPacketsVideoPriorytyNormal;
	 VidyoUint numFramesVideoPriorytyNormal;
	 VidyoUint numDroppedVideoPriorytyNormal;
	 VidyoUint delayVideoPriorutyRetransmit;
	 VidyoUint numPacketsVideoPriorutyRetransmit;
	 VidyoUint numFramesVideoPriorutyRetransmit;
	 VidyoUint numDroppedVideoPriorutyRetransmit;
	 VidyoUint delayAppPriorityNormal;
	 VidyoUint numPacketsAppPriorityNormal;
	 VidyoUint numFramesAppPriorityNormal;
	 VidyoUint numDroppedAppPriorityNormal;
	 VidyoUint delayAppPriorityRetransmit;
	 VidyoUint numPacketsAppPriorityRetransmit;
	 VidyoUint numFramesAppPriorityRetransmit;
	 VidyoUint numDroppedAppPriorityRetransmit;
} VidyoClientRequestRateShaperInfo;

/*! @struct VidyoClientRequestParticipantInfo
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_INFO

	@var VidyoClientRequestParticipantInfo::Name [out]
		Array of values for display name of remote participants in a conference.  Encoded as
		UTF-8.
	@var VidyoClientRequestParticipantInfo::URI [out]
		Array of values for Vidyo URI of remote participants in a conference.
	@var VidyoClientRequestParticipantInfo::bytesRcvd [out]
		Reserved for future use.
	@var VidyoClientRequestParticipantInfo::numFirsSent [out]
		Reserved for future use.
	@var VidyoClientRequestParticipantInfo::numNacksSent [out]
		Reserved for future use.
	@var VidyoClientRequestParticipantInfo::numDistinctNacksSent [out]
		Reserved for future use.
	@var VidyoClientRequestParticipantInfo::receivedFrameRate [out]
		Array of values for current received frame rate (units of frames per second) of remote
		participants in a conference.  Range of values 0~SIZE_MAX.
	@var VidyoClientRequestParticipantInfo::decodedFrameRate [out]
		Array of values for current decoded frame rate (units of frames per second) of remote
		participants in a conference.  Range of values 0~SIZE_MAX.
	@var VidyoClientRequestParticipantInfo::displayedFrameRate [out]
		Array of values for current displayed frame rate (units of frames per second) of remote
		participants in a conference.  Range of values 0~SIZE_MAX.
	@var VidyoClientRequestParticipantInfo::receivedPacketRate [out]
		Received rate of packet. *Not currently implemented*.
	@var VidyoClientRequestParticipantInfo::receivedBpsVideo [out]
		Received payload.
	@var VidyoClientRequestParticipantInfo::receivedBpsAudio [out]
		Reserved for future use.
	@var VidyoClientRequestParticipantInfo::receivedWidth [out]
		Array of values for current received width of video stream of remote participants in a
		conference.  Range of values 0~SIZE_MAX.
	@var VidyoClientRequestParticipantInfo::receivedHeight [out]
		Array of values for current received height of video stream of remote participants in a
		conference.  Range of values 0~SIZE_MAX.
	@var VidyoClientRequestParticipantInfo::receivedBytesVideo [out]
		Array of values for total received bytes of video data of remote participants in a
		conference.  Range of values 0~SIZE_MAX.
	@var VidyoClientRequestParticipantInfo::receivedBytesAudio [out]
		Array of values for total received bytes of audio data of remote participants in a
		conference.  Range of values 0~SIZE_MAX.
	@var VidyoClientRequestParticipantInfo::numberParticipants  [out]
		Number of remote participants in a conference.  Range of values 0~UINT_MAX.
*/
typedef struct VidyoClientRequestParticipantInfo_
{
	char Name[MAX_PARTICIPANTS_NUM][FIELD_SIZE];
	char URI[MAX_PARTICIPANTS_NUM][URI_LEN];
	VidyoSizeT bytesRcvd[MAX_PARTICIPANTS_NUM];
	VidyoSizeT numFirsSent[MAX_PARTICIPANTS_NUM];
	VidyoSizeT numNacksSent[MAX_PARTICIPANTS_NUM];
	VidyoSizeT numDistinctNacksSent[MAX_PARTICIPANTS_NUM];
	VidyoSizeT receivedFrameRate[MAX_PARTICIPANTS_NUM];
	VidyoSizeT decodedFrameRate[MAX_PARTICIPANTS_NUM];
	VidyoSizeT displayedFrameRate[MAX_PARTICIPANTS_NUM];
	VidyoSizeT receivedPacketRate[MAX_PARTICIPANTS_NUM];
	VidyoSizeT receivedBpsVideo[MAX_PARTICIPANTS_NUM];  /* receivedPayload */
	VidyoSizeT receivedBpsAudio[MAX_PARTICIPANTS_NUM];
	VidyoSizeT receivedWidth[MAX_PARTICIPANTS_NUM];
	VidyoSizeT receivedHeight[MAX_PARTICIPANTS_NUM];
	VidyoSizeT receivedBytesVideo[MAX_PARTICIPANTS_NUM];
	VidyoSizeT receivedBytesAudio[MAX_PARTICIPANTS_NUM];
	VidyoUint numberParticipants;
} VidyoClientRequestParticipantInfo;

/*! @struct VidyoClientRequestGetNumParticipants
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_NUM_PARTICIPANTS

	@var VidyoClientRequestGetNumParticipants::numParticipants [out]
		Total number of participants in a conference call.
*/
typedef struct VidyoClientRequestGetNumParticipants_
{
	VidyoUint numParticipants;
} VidyoClientRequestGetNumParticipants;

/*! @struct VidyoClientRequestGetParticipantNameAt
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_NAME_AT

	@var VidyoClientRequestGetParticipantNameAt::index [in]
		Index of conference participant whose name to be retrieved.
	@var VidyoClientRequestGetParticipantNameAt::result [out]
		Success (VIDYO_TRUE) or failure (VIDYO_FALSE).
		Name is valid only when result is VIDYO_TRUE.  If value of
		result is VIDYO_FALSE, it means there is no participant at
		the given location/index.
	@var VidyoClientRequestGetParticipantNameAt::name [out]
		Participant's display name.
*/
typedef struct VidyoClientRequestGetParticipantNameAt_
{
	VidyoUint index;
	VidyoBool result;
	char name[USERID_SIZE];
} VidyoClientRequestGetParticipantNameAt;

/*! @struct VidyoClientParticipantStatistics
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT

	@var VidyoClientParticipantStatistics::uri [out]
		URI of conference participant.
	@var VidyoClientParticipantStatistics::name [out]
		Display name of conference participant.
	@var VidyoClientParticipantStatistics::videoResolution [out]
		Received video resolution, as width by height.
	@var VidyoClientParticipantStatistics::videoKBitsPerSecRecv [out]
		Received video in kBPS.
	@var VidyoClientParticipantStatistics::audioKBitsPerSecRecv [out]
		Received audio in kBPS.
	@var VidyoClientParticipantStatistics::firs [out]
		Number of FIR packets.
	@var VidyoClientParticipantStatistics::nacks [out]
		Number of NACK packets.
	@var VidyoClientParticipantStatistics::videoFrameRate [out]
		Video frame rate.
	@var VidyoClientParticipantStatistics::videoDecodedFrameRate [out]
		Decoded video frame rate.
	@var VidyoClientParticipantStatistics::videoDisplayedFrameRate [out]
		Displayed Video frame rate.
*/
typedef struct VidyoClientParticipantStatistics_
{
	char uri[MAX_URI_LEN];
	char name[USERID_SIZE];
	VidyoRect videoResolution;
	VidyoUint videoKBitsPerSecRecv;
	VidyoUint audioKBitsPerSecRecv;
	VidyoUint firs;
	VidyoUint nacks;
	VidyoUint videoFrameRate;
	VidyoUint videoDecodedFrameRate;
	VidyoUint videoDisplayedFrameRate;
} VidyoClientParticipantStatistics;

/*! @struct VidyoClientRequestParticipantStatisticsAt
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT

	@var VidyoClientRequestParticipantStatisticsAt::index [in]
		Index of conference participant whose statistics
		to be retrieved.
	@var VidyoClientRequestParticipantStatisticsAt::result [out]
		Success (VIDYO_TRUE) or failure (VIDYO_FALSE).
		Contents are valid only when result is VIDYO_TRUE. If
		value of result is VIDYO_FALSE, means there is no
		participant at the given location/index.
	@var VidyoClientRequestParticipantStatisticsAt::statistics [out]
		Statistics parameters.
*/
typedef struct VidyoClientRequestParticipantStatisticsAt_
{
	VidyoUint index;
	VidyoBool result;
	VidyoClientParticipantStatistics statistics;
} VidyoClientRequestParticipantStatisticsAt;

/*! @struct VidyoClientRequestGetParticipantNameList
	Used for retrieving participant's display name.
	A list of maximum MAX_GET_PARTICIPANT_NAME will
	be retried starting from the participant identified
	by an index.
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_NAME_LIST

	@var VidyoClientRequestGetParticipantNameList::startIndex [in]
	Index of conference participant from
	where the list should start.
	@var VidyoClientRequestGetParticipantNameList::numParticipants [out]
	Number of participants names included
	in this message. If the value is 0, there are no participants
	starting from the given startIndex.
	@var VidyoClientRequestGetParticipantNameList::name [out]
	Participant's display name list.
*/
typedef struct VidyoClientRequestGetParticipantNameList_
{
	VidyoUint startIndex;
	VidyoUint numParticipants;
	char name[MAX_GET_PARTICIPANT_NAME][USERID_SIZE];
} VidyoClientRequestGetParticipantNameList;

/*! @struct VidyoClientRequestParticipantStatisticsList
	Used for retrieving statistics of a list of conference participants.
	A maximum of MAX_GET_PARTICIPANT_STATISTICS participant's
	statistics can be retrieved using one message.
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST

	@var VidyoClientRequestParticipantStatisticsList::startIndex [in]
	Starting index of conference participant starting
	from where the statistics to be retrieved.
	@var VidyoClientRequestParticipantStatisticsList::numParticipants [out]
	Number of participant's statistics included
	in this message. If the value is 0, there are no participants
	starting from the given startIndex.
	@var VidyoClientRequestParticipantStatisticsList::statistics [out]
	Statistics parameters of each participants.
*/
typedef struct VidyoClientRequestParticipantStatisticsList_
{
	VidyoUint startIndex;
	VidyoUint numParticipants;
	VidyoClientParticipantStatistics statistics[MAX_GET_PARTICIPANT_STATISTICS];
} VidyoClientRequestParticipantStatisticsList;

/*! Types of participants

	- Used for the following events:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_DETAILS_AT

	- Passed in field previewMode of following structures:
		+ #VidyoClientRequestParticipantDetailsAt
*/

typedef enum
{
	/*! Undefined participant type*/
	VidyoClientParticipantTypeNone,
	/*!Participant is a guest*/
	VidyoClientParticipantTypeGuest,
	/*!Participant is not a real participant but a recorder*/
	VidyoClientParticipantTypeRecorder,
	/*!Participant is a legacy*/
	VidyoClientParticipantTypeLegacy,
	/*!Participant can control*/
	VidyoClientParticipantTypeControl
} VidyoClientParticipantType;


/*! Role of participants

	- Used for the following events:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_DETAILS_AT

	- Passed in field previewMode of following structures:
		+ #VidyoClientRequestParticipantDetailsAt
*/

typedef enum
{
	/*! No special role*/
	VidyoClientParticipantRoleNone,
	/*!Participant is the owner*/
	VidyoClientParticipantRoleOwner,
	/*!Participant is the admin*/
	VidyoClientParticipantRoleAdmin,
	/*!Participant is the moderator*/
	VidyoClientParticipantRoleModerator
} VidyoClientParticipantRole;


/*! @struct VidyoClientRequestParticipantDetails
	Used for retrieving conference participant details for a participant
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_DETAILS_AT

*/
typedef struct VidyoClientRequestParticipantDetails_
{
	char uri[MAX_URI_LEN];
	char name[USERID_SIZE];
    /*! Entity ID of the participant */
	char participantID[MAX_EID_SIZE];
    /*! Entity ID of the participant */
	char entityID[MAX_EID_SIZE];
    /*! Is this user joined as guest, recorder, legacy */
    VidyoClientParticipantType participantType;
    /*! whether normal , owner or special right */
	VidyoClientParticipantRole participantRole;
    VidyoBool isVideoBlocked;
    VidyoBool isAudioBlocked;
    VidyoBool isShareBlocked;
} VidyoClientRequestParticipantDetails;

/*! @struct VidyoClientRequestParticipantDetailsAt
	Used for retrieving conference participant details for a given index
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_DETAILS_AT

	@var VidyoClientRequestParticipantDetailsAt::index [in]
	Index of participant
	from where the details to be retrieved.
	@var VidyoClientRequestParticipantDetailsAt::details[out]
	Details parameters of teh requested participants.
*/
typedef struct VidyoClientRequestParticipantDetailsAt_
{
	VidyoUint index;
	VidyoClientRequestParticipantDetails details;
} VidyoClientRequestParticipantDetailsAt;

#define MAX_ACTIVE_PARTICIPANTS	3

/*! @struct VidyoClientAudioActiveUser
	used by following out events to send active user 
		+ #VIDYO_CLIENT_REQUEST_GET_AUDIO_ACTIVE_USERS

	@var VidyoClientAudioActiveUser::participantURI [out]
	Uri of participant
	@var VidyoClientAudioActiveUser::energy[out]
	Energy generated by the participant
*/

typedef struct VidyoClientAudioActiveUser_
{
	/*! The URI identifying the participant which generated the audio*/
	char participantURI[MAX_URI_LEN];
	/*! Energy generated by the participant */
	VidyoUint energy;
} VidyoClientAudioActiveUser;



/*! @struct VidyoClientRequestAudioActiveUsers
	used by following out events to send active users 
		+ #VIDYO_CLIENT_REQUEST_GET_AUDIO_ACTIVE_USERS

	@var VidyoClientRequestAudioActiveUsers::activeUsers[out]
	Active users.
*/

typedef struct VidyoClientRequestAudioActiveUsers_
{
	/*! The active participants*/
	VidyoClientAudioActiveUser activeUsers[MAX_ACTIVE_PARTICIPANTS];
} VidyoClientRequestAudioActiveUsers;

/*! @struct VidyoClientRequestAudioEnergyInfo
	used by following out events to receive audio energy levels 
		+ #VIDYO_CLIENT_REQUEST_GET_AUDIO_ENERGY_INFO
*/
typedef struct VidyoClientRequestAudioEnergyInfo_
{
	VidyoInt rendererEnergy;
	VidyoInt capturerEnergy;
} VidyoClientRequestAudioEnergyInfo;


/*! @struct VidyoClientRequestGetDisplayString
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_DISPLAY_STRING

	@var VidyoClientRequestGetDisplayString::enumStringID [in]
		Numeric ID (usually based on enumeration type) of display string requested, for
		currently set display language.  Range of allowed values 0 to a maximum, that is
		dependent on number of strings originally registered by GUI, at time of call to
		#VidyoClientStart().
	@var VidyoClientRequestGetDisplayString::StringDisplayText [out]
		Pointer to display string requested, for currently set display language.  No
		modification of the storage accessed by this pointer should be attempted.  Encoding
		of string based on strings originally registered by GUI, at time of call to
		#VidyoClientStart().
*/
typedef struct VidyoClientRequestGetDisplayString_
{
	VidyoUint enumStringID;
	VidyoVoidPtr StringDisplayText;
} VidyoClientRequestGetDisplayString;

#ifndef DOXYGEN_SHOULD_IGNORE_THIS

/*! Camera location enumeration for mobile devices

	- Passed in field _previewMode_ of following structures:
		+ #VidyoClientDeviceInfo
*/
typedef enum
{
	VIDYO_VIDEOCAPTURERLOCATION_Front,
	VIDYO_VIDEOCAPTURERLOCATION_Back
} VidyoVideoCapturerLocation;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_DEVICES_FROM_MANAGER
*/
typedef struct VidyoClientDeviceInfo_
{
	/*! Name of device. */
	VidyoUint8 name[DEVICE_NAME_SIZE];
	/*! Identity of device */
	VidyoUint8 id[DEVICE_ID_SIZE];
	/*! Properties of device */
	VidyoUint  properties;
	/*! Device Location */
	VidyoVideoCapturerLocation location;
} VidyoClientDeviceInfo;

/*! Request structure

	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_DEVICES_FROM_MANAGER
*/
typedef struct VidyoClientRequestDevices_
{
	/*! Device information - Reserved for internal use. */
	VidyoClientDeviceInfo deviceInfo[MAX_DEVICE_NUMBER];
	/*! Reserved for internal use. */
	VidyoUint numberDevices;
	/*! Reserved for internal use. */
	VidyoUint currentDevice;
	/*! Reserved for internal use. */
	VidyoClientDeviceType deviceType;
} VidyoClientRequestDevices;
#endif

/*! @struct VidyoClientRequestGetEndpointStatus
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_ENDPOINT_STATUS

	@var VidyoClientRequestGetEndpointStatus::endPointStatus [out]
		Status of endpoint.
*/
typedef struct VidyoClientRequestGetEndpointStatus_
{
	VidyoClientEndpointStatus endPointStatus;
} VidyoClientRequestGetEndpointStatus;

/*! @struct VidyoClientRequestSetLayoutRect
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_SET_LAYOUT_RECT
*/
typedef struct VidyoClientRequestSetLayoutRect_
{
	/*! Top left X coordinate of layout rectangle */
	VidyoUint xPos;
	/*! Top left Y coordinate of layout rectangle */
	VidyoUint yPos;
	/*! Width of the layout rectangle */
	VidyoUint width;
	/*! Height of the layout rectangle */
	VidyoUint height;
} VidyoClientRequestSetLayoutRect;

/*! Type of Rendering mode to use, automatic or manual
    - Passed in field _previewMode_ of following structs:
        + #VidyoClientRequestSetRenderingMode
 */
typedef enum VidyoClientRenderingMode_
{
	VIDYO_CLIENT_RENDERING_MODE_AUTO,
	VIDYO_CLIENT_RENDERING_MODE_MANUAL,
} VidyoClientRenderingMode;

/*!	@struct VidyoClientRequestSetRenderingMode
    Request structure
        - Used by following requests:
            + #VIDYO_CLIENT_REQUEST_SET_RENDERING_MODE
 */
typedef struct VidyoClientRequestSetRenderingMode_
{
	VidyoClientRenderingMode mode;
} VidyoClientRequestSetRenderingMode;

/*! @struct VidyoClientRequestSetLogLevelsAndCategories
	Request structure for setting log levels and categories
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_SET_LOG_LEVELS_AND_CATEGORIES
	@var VidyoClientRequestSetLogLevelsAndCategories::levelsAndCategories [in]
	New setting for log levels and categories.
*/
typedef struct VidyoClientRequestSetLogLevelsAndCategories_
{
	char levelsAndCategories[MAX_LOG_STRING_SIZE];
} VidyoClientRequestSetLogLevelsAndCategories;

/*! @struct VidyoClientRequestGetDockCounts
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_DOCK_COUNTS
*/
typedef struct VidyoClientRequestGetDockCounts_
{
	/*! The number of application shares currently docked */
	VidyoUint numApplicationsDocked;
	VidyoBool isApplicationDockVisible;
	/*! The number of participant videos currently docked */
	VidyoUint numParticipantsDocked;
	VidyoBool isParticipantDockVisible;
} VidyoClientRequestGetDockCounts;

/*! The desktop/screen information 
    - Passed in field sysDesktopInfo of following structs:
        + #VidyoClientRequestGetWindowsAndDesktops
 */
typedef struct VidyoClientScreenInfo_
{
	/*! The pixel density in horizontal axis */
	VidyoUint xDpi;
	/*! The pixel density in vertical axis */
	VidyoUint yDpi;
	/*! Indicates whether the screen is primary or not primary */
	VidyoBool isPrimary;
} VidyoClientScreenInfo;

/*! @struct VidyoClientRequestGetWindowsAndDesktops
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS
		@note For Windows, MacOs and Linux only
*/
typedef struct VidyoClientRequestGetWindowsAndDesktops_
{
	/*! The number of application windows currently open */
	VidyoUint numApplicationWindows;
	/*! List of open application window names (UTF-8) (Localized) - MacOs only */
	char appWindowName[MAX_NUM_APP_WINDOWS][MAX_URI_LEN];
	/*! List of open application window application names (UTF-8) (Localized) */
	char appWindowAppName[MAX_NUM_APP_WINDOWS][MAX_URI_LEN];
	/*! List of open application window handles */
	VidyoWindowCapturerWindowId appWindowId[MAX_NUM_APP_WINDOWS];
	/*! List of open application window geometries - MacOs only */
	VidyoRect appWindowRect[MAX_NUM_APP_WINDOWS];
	/*! The number of system desktops currently available */
	VidyoUint numSystemDesktops;
	/*! List of available system desktop names (UTF-8) (Not localized) */
	char sysDesktopName[MAX_SHARE_DISPLAY_DEVICE][MAX_URI_LEN];
	/*! List of available system desktop id - This should be provided in #VidyoClientInEventShare when requesting to share. */
	char sysDesktopId[MAX_SHARE_DISPLAY_DEVICE][VIDYO_CLIENT_SCREEN_ID_SIZE];
	/*! List of actual system desktop geometries  */
	VidyoRect sysDesktopRect[MAX_SHARE_DISPLAY_DEVICE];
    /*! List of available system desktop geometries  */
    VidyoRect sysDesktopWorkArea[MAX_SHARE_DISPLAY_DEVICE];
	/*! List of available system desktop geometries - MacOs only */
	VidyoClientScreenInfo sysDesktopInfo[MAX_SHARE_DISPLAY_DEVICE];
	/*! App shares are not returned due to security risk or lack of support. In windows 8 and above, there is a risk when High DPI is on*/
	VidyoBool appSharesDisabled;
} VidyoClientRequestGetWindowsAndDesktops;


/*! @struct VidyoClientSharableWindowWhiteList
	Request structure used to get the current sharable window white list and to modify the current sharable window white list.
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_SHARABLE_WINDOW_WHITE_LIST
		+ #VIDYO_CLIENT_REQUEST_SET_SHARABLE_WINDOW_WHITE_LIST
*/
typedef struct VidyoClientSharableWindowWhiteList_
{
	/*! The number of application windows currently configured in white list */
	VidyoUint numWindows;
	/*! Application window names (UTF-8) marked as white list for sharing. */
	char windowName[MAX_NUM_SHARABLE_WINDOWS_WHITE_LIST][MAX_URI_LEN];
} VidyoClientSharableWindowWhiteList;

/*!	Event structure
	- Used by following in events:
		+ #VIDYO_CLIENT_REQUEST_SET_BACKGROUND
*/
typedef struct VidyoClientRequestSetBackground_
{
	/*!
		VIDYO_TRUE to enable backgrounded state, VIDYO_FALSE otherwise.
		When in backgrounded state during a conference, video and application window
		sharing streams are not requested from the server, and no rendering of
		those media types is performed.  Also, video capture is not performed.
		Audio capture continues, and received audio streams continue to be mixed and
		played back.
	*/
	VidyoBool willBackground;
} VidyoClientRequestSetBackground;


/*! Type of Alarm
    - Sent as part of VIDYO_CLIENT_REQUEST_GET_ALARMS:
        + #VidyoClientRequestGetAlarms
 */
typedef enum VidyoClientAlarmType_
{

	/*! High CPU utilization limits quality of conference */
	VIDYO_CLIENT_ALARM_TYPE_CPU = 0,				
	/*! Insufficient network send bandwidth limits quality of own video */
	// VIDYO_CLIENT_ALARM_TYPE_TX_BANDWIDTH,
	/*! Insufficient network send bandwidth limits resolution of own video */
	VIDYO_CLIENT_ALARM_TYPE_TX_DOWNSAMPLING_RESOLUTION_BW,	
	/*! Insufficient network send bandwidth limits FPS of own video */
	VIDYO_CLIENT_ALARM_TYPE_TX_DOWNSAMPLING_FPS_BW,	
	/*! High CPU utilization limits resolution of own video */
	VIDYO_CLIENT_ALARM_TYPE_TX_DOWNSAMPLING_RESOLUTION_CPU,	
	/*!  High CPU utilization forces reduction of encoded video's frames per second */
	VIDYO_CLIENT_ALARM_TYPE_TX_REDUCED_FPS_CPU,	
	/*! Insufficient network receive bandwidth limits number of viewable participants */
	VIDYO_CLIENT_ALARM_TYPE_RX_SOURCES_REDUCED_BW,	
	/*! CPU of machine is not powerful to view all configured number of participants though there are same or more participants in conference */
	VIDYO_CLIENT_ALARM_TYPE_LOW_POWER_CPU_RX_SOURCES_REDUCED,
	/*!  High CPU utilization forces reduction of frame rate of received video */
	VIDYO_CLIENT_ALARM_TYPE_RX_FPS_REDUCED_CPU,	
	/*!  High CPU utilization forces reduction of resolution of received video */
	VIDYO_CLIENT_ALARM_TYPE_RX_RESOLUTION_REDUCED_CPU,	
	/*!  High CPU utilization forces reduction of number of received video sources */
	VIDYO_CLIENT_ALARM_TYPE_RX_SOURCES_REDUCED_CPU,	
	/*! Transmit or receive slider on status tab of configuration dialog not on auto setting */
	VIDYO_CLIENT_ALARM_TYPE_GUI_SAFE_MODE_ENABLED,	
	/*! System running on battery power. Video performance may not be optimal */
	VIDYO_CLIENT_ALARM_TYPE_ACDC,					
	/*! System power scheme or plan not optimal for video conferencing */
	VIDYO_CLIENT_ALARM_TYPE_POWERSAVER,				
	/*!  VidyoProxy is onand causing indirectly any other alarm */
	VIDYO_CLIENT_ALARM_TYPE_USING_PROXY,	
	/*! Not a valid value - Keep at the end */
	VIDYO_CLIENT_ALARM_TYPE_MAX,
} VidyoClientAlarmType;

/*! Level of Alarm
    - Sent as part of VIDYO_CLIENT_REQUEST_GET_ALARMS:
        + #VidyoClientRequestGetAlarms
 */
typedef enum VidyoClientAlarmLevel_
{
	/*! No alarm */
	VIDYO_CLIENT_ALARM_LEVEL_GREEN = 0,				
	/*! Warning */
	VIDYO_CLIENT_ALARM_LEVEL_YELLOW,				
	/*! Serious issue */
	VIDYO_CLIENT_ALARM_LEVEL_RED,					
	/*! Not a valid value - Keep at the end */
	VIDYO_CLIENT_ALARM_LEVEL_MAX,
} VidyoClientAlarmLevel;

/*! @struct VidyoClientRequestGetAlarms
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_ALARMS
*/
typedef struct VidyoClientRequestGetAlarms_
{
	/*! whether each type of the alarm is set or not, VIDYO_TRUE if set */
	VidyoBool alarmTable[VIDYO_CLIENT_ALARM_TYPE_MAX];				
	/*! level of each alarm if set  else VIDYO_CLIENT_ALARM_LEVEL_GREEN */
	VidyoClientAlarmLevel alarmLevel[VIDYO_CLIENT_ALARM_TYPE_MAX]; 
} VidyoClientRequestGetAlarms;

/*! @struct VidyoClientRequestGetLicensedStatus
 Request structure
 - Used by following requests:
    + #VIDYO_CLIENT_REQUEST_GET_LICENSED_STATUS
 */
typedef struct VidyoClientRequestGetLicensedStatus_
{
    /*! VIDYO_TRUE means vidyoclient is licesed and VIDYO_FALSE means vidyoClient is not licesed */
	VidyoBool isLicensed;
} VidyoClientRequestGetLicensedStatus;

/*! @struct VidyoClientRequestEventLayout
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_LAYOUT
*/
typedef struct VidyoClientRequestEventLayout_
{
	/*! The number of user configured tiles in layout */
	VidyoUint numUserTiles;
	/*! Indicates whether preferred layout is enabled */
	VidyoBool isPreferredLayout;
} VidyoClientRequestEventLayout;

/*! @struct VidyoClientRequestEventGetWatchVideoFormat
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_WATCH_VIDEO_FRAME_FORMAT
*/
typedef struct VidyoClientRequestEventGetWatchVideoFormat_
{
	/*! 
		The fourcc code of the frame format. Default value is ARGB. Other values supported are I420 & YUV12.
		e.g. To encode ARGB, the 1st 8 bits should be 'A', 2nd 8 bits should be 'R', 3rd 8 bits should be 'G'
		and the last (most significant) 8 bits should be 'B'.
	*/
	VidyoImageFormat format;
} VidyoClientRequestEventGetWatchVideoFormat;

/*! @struct VidyoClientRequestEventSetWatchVideoFormat
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT
*/
typedef struct VidyoClientRequestEventSetWatchVideoFormat_
{
	/*! 
		The fourcc code of the frame format. Default value is ARGB. Other values supported are I420 & YUV12.
		e.g. To encode ARGB, the 1st 8 bits should be 'A', 2nd 8 bits should be 'R', 3rd 8 bits should be 'G'
		and the last (most significant) 8 bits should be 'B'.
	*/
	VidyoImageFormat format;
} VidyoClientRequestEventSetWatchVideoFormat;

/*! @struct VidyoClientRequestCommunicationStatus
	Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_GET_COMMUNICATION_STATUS
*/
typedef struct VidyoClientRequestCommunicationStatus_
{
	/*! Communication status with VidyoManager */
	VidyoBool vmCommunicationStatus;
	/*! VidyoManager via. VidyoProxy */
	VidyoBool vmCommunicationViaVidyoProxy;
	/*! VidyoManager via. WebProxy */
	VidyoBool vmCommunicationViaWebProxy;
	/*! Communication status with VidyoRouter */
	VidyoBool vrCommunicationStatus;
	/*! VidyoRouter via. VidyoProxy. If connected via VidyoProxy media (RTP and RTCP) will be using TCP.
	    If connected without VidyoProxy media  (RTP and RTCP) will be using UDP. */
	VidyoBool vrCommunicationViaVidyoProxy;
	/*! VidyoRouter via. WebProxy */
	VidyoBool vrCommunicationViaWebProxy;
} VidyoClientRequestCommunicationStatus;

/*! @struct VidyoClientRequestSetPortalAddress
	Request structure
	- Used by following requests:
 + #VIDYO_CLIENT_REQUEST_SET_PORTAL_ADDRESS
 */
typedef struct VidyoClientRequestSetPortalAddress_
{
    /*! Contains portal address which will be added to configuration file */
    char portalAddress[FIELD_SIZE];
} VidyoClientRequestSetPortalAddress;

/*! @struct VidyoClientRequestSetBandwidthAdjustmentPeriod
 Request structure
 - Used by following requests:
 + #VIDYO_CLIENT_REQUEST_SET_BANDWIDTH_ADJUSTMENT_PERIOD
 */
typedef struct VidyoClientRequestSetBandwidthAdjustmentPeriod_
{
    /*! Contains bandwidth adjustment period which will be set for tiles renderer */
    VidyoUint bandwidthAdjustmentPeriod; //seconds
} VidyoClientRequestSetBandwidthAdjustmentPeriod;

/*! @struct VidyoClientRequestGetCPUUsage
 Request structure
 - Used by following requests:
 + #VIDYO_CLIENT_REQUEST_GET_CPU_USAGE
 */
typedef struct VidyoClientRequestGetCPUUsage_
{
    /*! Contains general CPU usage of system  */
    VidyoUint cpuUsage; //percents
} VidyoClientRequestGetCPUUsage;

#ifndef DOXYGEN_SHOULD_IGNORE_THIS
/*! Request structure
	- Used by following requests:
		+ #VIDYO_CLIENT_REQUEST_PRIVATE
*/
typedef struct VidyoClientRequestPrivate_
{
	/*! (Reserved for private requests only used by standard Vidyo clients) */
	VidyoUint requestType;
	/*! (Reserved for private requests only used by standard Vidyo clients) */
	VidyoVoidPtr requestData;
	/*! (Reserved for private requests only used by standard Vidyo clients) */
	VidyoSizeT requestDataSize;
	/*! (Reserved for private requests only used by standard Vidyo clients) */
	VidyoSizeT reserved;
} VidyoClientRequestPrivate;
#endif

#endif /* VIDYO_CLIENT_PARAMETERS_H */

