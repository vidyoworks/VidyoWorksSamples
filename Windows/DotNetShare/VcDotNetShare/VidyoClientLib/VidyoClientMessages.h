/*! @file VidyoClientMessages.h
	@brief Messages for Vidyo Client API Library.
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

#ifndef VIDYO_CLIENT_MESSAGES_H
#define VIDYO_CLIENT_MESSAGES_H

/*******************************************************************************
 Events from application to the Vidyo Client Library
*******************************************************************************/


/**
 * @defgroup VidyoClientEventModule Events and Requests
 * @ingroup  VidyoClientModule
 * @brief Input and output events
 *
 * Following events are used to communicate with Vidyo Client API Library:
 * - #VidyoClientInEvent
 *  + Asynchronous events that are sent from Application to Video Client API Library using #VidyoClientSendEvent
 * - #VidyoClientOutEvent
 *  + Asynchronous events that are sent from Video Client API Library to Application via #VidyoClientOutEventCallback callback
 * - #VidyoClientRequest
 *  + Synchronous events (requests) that are sent to and from Application to Video Client API Library using #VidyoClientSendRequest
 */

/**
 * @defgroup VidyoClientInEventModule Input Events
 * @ingroup  VidyoClientEventModule
 * @brief Input events
 * @see VidyoClientSendEvent
 *
 * Input events for VidyoClient API Library. Called asynchronously.
 */

/**
 * @defgroup VidyoClientOutEventModule Output Events
 * @ingroup  VidyoClientEventModule
 * @brief Output events
 * @see VidyoClientOutEventCallback
 *
 * Output events for VidyoClient API Library.
 * Will be called in #VidyoClientOutEventCallback
 *
 */

/**
 * @defgroup VidyoClientRequestModule Requests
 * @ingroup  VidyoClientEventModule
 * @brief Synchronous requests
 * @see VidyoClientSendRequest
 */

/**
* @addtogroup VidyoClientInEventModule
* @{
*/
/*! @brief Vidyo Client In Events.

	Enumeration of events that application can send to Vidyo Client API Library.
*/

typedef enum VidyoClientInEvent_
{
	/*!
		Minimum value for the enumeration.

		Disregard all event with value below this.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_MIN = 99,

	/*!
		Perform manual endpoint registration

		Used for customizing login parameters to Vidyo Portal.
		Use #VIDYO_CLIENT_IN_EVENT_LOGIN for simple login.

		@see Corresponding parameter structure #VidyoClientInEventSignIn

		@see VIDYO_CLIENT_IN_EVENT_LOGIN
	*/
	VIDYO_CLIENT_IN_EVENT_SIGN_IN = 100,

	/*!
		Cancel entering a conference.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_CANCEL = 200,
	/*!
		Leave a conference, already entered.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_LEAVE = 201,
	/*!
		Answer an incoming call.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_ANSWER = 300,
	/*!
		Decline an incoming call.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_DECLINE = 301,
	/*!
		Change how own video shown in video layout.

		@see Corresponding parameter structure #VidyoClientInEventPreview
		@see VIDYO_CLIENT_OUT_EVENT_PREVIEW

		@note Limited on mobile
	*/
	VIDYO_CLIENT_IN_EVENT_PREVIEW = 400,
	/*!
		Change mute state of audio input (capture / microphone) device.

		@see Corresponding parameter structure #VidyoClientInEventMute
	*/
	VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN = 500,
	/*!
		Change mute state of audio output (playback/speaker) device.

		@see Corresponding parameter structure #VidyoClientInEventMute
	*/
	VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_OUT = 501,
	/*!
		Change privacy state of video (capture/camera) device.

		@see Corresponding parameter structure #VidyoClientInEventMute
	*/
	VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO = 502,
	/*!
		Change default rendering state.
		Used to reduce the extra rendering when enpoint is receiving raw frames

		@see Corresponding parameter structure #VidyoClientInEventMute
	*/
	VIDYO_CLIENT_IN_EVENT_MUTE_DEFAULT_RENDERING = 503,
    /*!
     Disable or enable sending selfview frames while joining.
     Is using only if default rendering in tiles library is muted
     
     @see Corresponding parameter structure #VidyoClientInEventShowSelfViewWhileJoining
     */
    VIDYO_CLIENT_IN_EVENT_SHOW_SELFVIEW_WHILE_JOINING = 510,
	/*!
		Share local application window in conference.

		@see Corresponding parameter structure #VidyoClientInEventShare
	*/
	VIDYO_CLIENT_IN_EVENT_SHARE = 600,
	/*!
		Stop sharing local application window in conference.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_UNSHARE = 601,
	/*!
		Send a share frame for an application share started with #VIDYO_CLIENT_IN_EVENT_SHARE.

		@see Corresponding parameter structure is #VidyoClientInEventVideoFrame.
		@see #VIDYO_CLIENT_IN_EVENT_SHARE

		@note Replaces the less generic and platform specific #VIDYO_CLIENT_IN_EVENT_RAW_FRAME.
	*/
	VIDYO_CLIENT_IN_EVENT_SEND_FRAME = 602,
	/*!
		Invoke system dialog for configuration of currently selected video
		device on Windows.

		Does not use parameter structure. Use *NULL*.

		@note Windows only
	*/
	VIDYO_CLIENT_IN_EVENT_SETUP_CAMERA = 700,
	/*!
		Resize video layout.

		@see Corresponding parameter structure #VidyoClientInEventResize
	*/
	VIDYO_CLIENT_IN_EVENT_RESIZE = 800,
	/*!
		Set maximum number of viewable remote participants in video layout to specified value.

		@see Corresponding parameter structure #VidyoClientInEventParticipantsLimit

		@note Not available on mobile platforms
	*/
	VIDYO_CLIENT_IN_EVENT_PARTICIPANTS_LIMIT = 900,
	/*!
		Change number of participants to be shown in a larger size region within video layout.

		@see Corresponding parameter structure #VidyoClientInEventLayout

		@note Not available on mobile platforms
	*/
	VIDYO_CLIENT_IN_EVENT_LAYOUT = 901,
	/*!
		Change the background color of the renderer.

		@see Corresponding parameter structure #VidyoClientInEventColor

		@note Only functional for tiles renderer
	*/
	VIDYO_CLIENT_IN_EVENT_SET_BACKGROUND_COLOR = 902,
    /*!
         Set minimum number of viewable remote participants in video layout to specified value.
     
         @see Corresponding parameter structure #VidyoClientInEventParticipantsLimit
     */
    VIDYO_CLIENT_IN_EVENT_SET_MIN_PARTICIPANTS_LIMIT = 903,
	/*!
		Play audio from specified data buffer, using system default audio playback
		device for wave data, which is useful for ringtones.
		Useful for playing sound one time when in call
		
		@see Corresponding parameter structure #VidyoClientInEventPlaySound

		@note Must use encoding of 1-channel, 16 bits per sample and 16000 samples per second.

	*/
	VIDYO_CLIENT_IN_EVENT_PLAY_SOUND = 1000,
	/*!
		Play audio from specified data buffer

		Play audio from specified data buffer, using system default audio playback
		device for wave data, which is useful for ringtones.
		Ringtone is used when receiving an incoming call
		It will play the data buffer in a loop till the ringing condition changes.

		@see Corresponding parameter structure #VidyoClientInEventPlaySound
		@see VIDYO_CLIENT_OUT_EVENT_PLAY_SOUND_DONE

		@note Must use encoding of 1-channel, 16 bits per sample and 16000 samples per second.
	*/
	VIDYO_CLIENT_IN_EVENT_PLAY_RINGTONE = 1001,
	/*!
		Play audio from specified data buffer

		Play audio from specified data buffer, using system default audio playback
		device for wave data, which is useful for playing calling or call process tone 
		for out bond call and waiting for called party to answer the call.
		Calling is used when making a direct call
		It will play the data buffer in a loop till the calling condition changes.

		@see Corresponding parameter structure #VidyoClientInEventPlaySound

		@note Must use encoding of 1-channel, 16 bits per sample and 16000 samples per second.
	*/
	VIDYO_CLIENT_IN_EVENT_PLAY_CALLING_TONE = 1002,
	/*!
		Change state of acoustic echo detection.

		@see Corresponding parameter structure #VidyoClientInEventSetFlag
	*/
	VIDYO_CLIENT_IN_EVENT_SET_ECHO_DETECT = 1100,
	/*!
		Change state of acoustic echo cancellation.

		@see Corresponding parameter structure #VidyoClientInEventSetFlag
	*/
	VIDYO_CLIENT_IN_EVENT_SET_ECHO_CANCEL = 1101,
	/*!
		Change state of audio AGC (Automatic Gain Control.)

		@see Corresponding parameter structure #VidyoClientInEventSetFlag
	*/
	VIDYO_CLIENT_IN_EVENT_SET_AUDIO_AGC = 1200,
	/*!
		Play a DTMF tone for the specified duration into audio capture and playback paths.

		@see Corresponding parameter structure #VidyoClientInEventPlayDialTone
	*/
	VIDYO_CLIENT_IN_EVENT_PLAY_DIAL_TONE = 1300,
	/*!
		Start playing a DTMF tone into audio capture and playback paths.
		Use event #VIDYO_CLIENT_IN_EVENT_STOP_PLAYING_CONTINUOUS_DIAL_TONE to stop it.

		@see Corresponding parameter structure #VidyoClientInEventPlayContinuousDialTone
	*/
	VIDYO_CLIENT_IN_EVENT_START_PLAYING_CONTINUOUS_DIAL_TONE = 1301,
	/*!
		Stop playing a DTMF tone into audio capture and playback paths.
		Use event #VIDYO_CLIENT_IN_EVENT_START_PLAYING_CONTINUOUS_DIAL_TONE to start it in
		first place.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_STOP_PLAYING_CONTINUOUS_DIAL_TONE = 1302,
	/*!
		Send a camera control request over FECC (Far End Camera Control), for participant
		with specified URI.

		@see Corresponding parameter structure #VidyoClientInEventControlCamera
	*/
	VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA = 1400,
	/*!
		Set display mode of video source, for participant with specified URI.

		@see Corresponding parameter structure #VidyoClientInEventSetParticipantVideoMode
	*/
	VIDYO_CLIENT_IN_EVENT_SET_PARTICIPANT_VIDEO_MODE = 1401,
	/*!
		Start AppFramework library.

		Does not use parameter structure. Use *NULL*.

		@warning For internal use only
	*/
	VIDYO_CLIENT_IN_EVENT_START_FRAMEWORK = 1500,
	/*!
		Enter full screen mode.

		Control number and order of monitors.

		@see Corresponding parameter structure #VidyoClientInEventSetMonitors

		@warning For internal use only
	*/
	VIDYO_CLIENT_IN_EVENT_SET_MONITORS = 1501,
	/*!
		Sets send bandwidth limit.

		@see Corresponding parameter structure #VidyoClientInEventSetSendBandwidth
	*/
	VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH = 1502,
	/*!
		Send a raw RGB frame over the app share.

		@see Corresponding parameter structure #VidyoClientInEventRawFrame
		@warning For internal use only
	*/
	VIDYO_CLIENT_IN_EVENT_RAW_FRAME = 1503,
	/*!
		Sets the default network interface.
		VidyoClient ignores every other network interface in any media negotiation

		@see Corresponding parameter structure #VidyoClientInEventSetNetworkInterface
	*/
	VIDYO_CLIENT_IN_EVENT_SET_NETWORK_INTERFACE = 1504,
	/*!
		Called by application to login to user to Portal

		@see Corresponding parameter structure #VidyoClientInEventLogIn
	*/
	VIDYO_CLIENT_IN_EVENT_LOGIN = 1600,
	/*!
		Called by application to cancel login process.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_LOGIN_CANCEL = 1601,
	/*!
		Called by application to activate licensing procedure on Portal.

		Does not use parameter structure. Use *NULL*.

		@see <a href="index.html">Main page</a> for sample.
	*/
	VIDYO_CLIENT_IN_EVENT_LICENSE = 1602,
	/*!
		Called by application to sign off VidyoManager.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_SIGNOFF = 1603,
	/*!
		Called by GUI to join to Conference via Room Link
	
		@see corresponding parameter structure #VidyoClientInEventRoomLink
	*/
	VIDYO_CLIENT_IN_EVENT_ROOM_LINK = 1604,
	/*!
		Gets the preferred client version on the server
	
		@see corresponding parameter structure #VidyoClientInEventClientVersionOnServer
	*/
	VIDYO_CLIENT_IN_EVENT_CLIENT_VERSION_ON_SERVER = 1605,
	/*!
		Called by GUI to join to Conference via Room Link with location tag as an extra parameter
	
		@see corresponding parameter structure #VidyoClientInEventRoomLinkEx
	*/
	VIDYO_CLIENT_IN_EVENT_ROOM_LINK_EX = 1606,
	/*!
		Used to control connection with conference manager

		@see Corresponding parameter structure #VidyoClientInEventSetOffline
	*/
	VIDYO_CLIENT_IN_EVENT_SET_OFFLINE = 1700,
	/*!
		Used to freeze/unfreeze the image from the video capturer

		@see Corresponding parameter structure #VidyoClientInEventSetFlag
	*/
	VIDYO_CLIENT_IN_EVENT_SET_FREEZE_IMAGE = 1701,
	/*!
		Used to set orientation of own video and/or video layout.

		@see Corresponding parameter structure #VidyoClientInEventSetOrientation

		@note Mobile platforms only
	*/
	VIDYO_CLIENT_IN_EVENT_SET_ORIENTATION = 1702,
	/*!
		Reports that conference is interrupted by incoming call

		@see VidyoClientInEventTelephoneCall

		@note iOS only

	*/
	VIDYO_CLIENT_IN_EVENT_TELEPHONE_CALL = 1704,
	/*!
     Identify the location of the font file to use
     
     @see VidyoClientInEventSetFontFile
     */
	VIDYO_CLIENT_IN_EVENT_SET_FONT_FILE = 1705,
	/*!
		Change enable state of status bar widget on video layout.

		This in event needs to be sent before joining a conference,
		in order to take affect for the next conference.
		The status bar defaults to being disabled if this in
		event is never sent.
		Sending this in event will result in the corresponding #VIDYO_CLIENT_OUT_EVENT_ENABLED_STATUS_BAR event to
		confirm the setting.

		@note Mobile platforms only

		@see Corresponding parameter structure #VidyoClientInEventEnable
		@see VIDYO_CLIENT_IN_EVENT_ENABLE_STATUS_BAR
	*/
	VIDYO_CLIENT_IN_EVENT_ENABLE_STATUS_BAR = 1800,
	/*!
		Change enable state of button bar widget on video layout.

		This event needs to be sent before joining a conference,
		in order to take affect for the next conference.
		The button bar defaults to being enabled if this
		event is never sent. Sending this in event will result in the corresponding #VIDYO_CLIENT_OUT_EVENT_ENABLED_BUTTON_BAR to
		confirm the setting.

		@note Mobile platforms only

		@see VidyoClientInEventEnable
		@see VIDYO_CLIENT_IN_EVENT_ENABLE_STATUS_BAR
	*/
	VIDYO_CLIENT_IN_EVENT_ENABLE_BUTTON_BAR = 1801,
	/*!
		Cycle the visibility of the video/participant dock on the video layout.
		This in event only works if there are participants in the dock, otherwise
		it has no effect.
		There is no corresponding out event.

		@note Mobile only
	*/
	VIDYO_CLIENT_IN_EVENT_TOGGLE_VIDEO_DOCK = 1802,
	/*!
		Cycle the visibility of the application/share dock on the video layout.

		This in event only works if there are application/shares in the dock, otherwise
		it has no effect.
		There is no corresponding out event.

		@note Mobile only
	*/
	VIDYO_CLIENT_IN_EVENT_TOGGLE_APPLICATION_DOCK = 1803,

	/*!
		Toggle capturing cameras through FRONT-BACK-OFF.

		@note Mobile only
	*/
	VIDYO_CLIENT_IN_EVENT_TOGGLE_CAMERA = 1804,

	/*!
     Called to start media during the startup of a conference.
     
     @note Android Client only
     */
	VIDYO_CLIENT_IN_EVENT_CONFERENCE_MEDIA_START = 1805,

	/*!
		Identify which icon for the renderer to show.  The list of possible
		icons is identified by the #VidyoClientRendererIcon enumerated type.

		@see VidyoClientInEventRendererShowIcon
	*/
	VIDYO_CLIENT_IN_EVENT_RENDERER_SHOW_ICON = 1901,

	/*!
		Used to send a group chat text to all remote participants.

		@see VidyoClientInEventGroupChat
	*/
	VIDYO_CLIENT_IN_EVENT_GROUP_CHAT = 2000,

	/*!
		Used to send a private chat text to a specified remote participant.

		@see VidyoClientInEventPrivateChat
	*/
	VIDYO_CLIENT_IN_EVENT_PRIVATE_CHAT = 2001,

	/*!
		Used to set the display name of the specified remote participant.

		@see VidyoClientInEventSetDisplayName
	*/
	VIDYO_CLIENT_IN_EVENT_SET_DISPLAY_NAME = 3000,

	/*!
		Used to reset the display name of the remote participant to default name.

		@see VidyoClientInEventResetDisplayName
	*/
	VIDYO_CLIENT_IN_EVENT_RESET_DISPLAY_NAME = 3100,

	/*!
		Used to request raise hand or clear hand in lecture mode

		@see VidyoClientInEventLectureClearRaiseHand
	*/
	VIDYO_CLIENT_IN_EVENT_LECTURE_CLEAR_RAISE_HAND = 3200,
	/*!
		Used to start watching/viewing a specified video source

		@see VidyoClientInEventStartWatchVideoSource
	*/
	VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE = 3210,
	/*!
		Used to stop watching/viewing a specified video source

		@see VidyoClientInEventStopWatchVideoSource
	*/
	VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE = 3211,
	/*!
		Used to start or stop watching dynamic video souce of loudest speakers

		@see VidyoClientInEventSetDynamicWatchVideoSource
	*/
	VIDYO_CLIENT_IN_EVENT_SET_DYNAMIC_WATCH_VIDEO_SOURCE = 3212,
	/*!
		Used to start watching/viewing self view (preview)
	*/
	VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW = 3213,
	/*!
		Used to stop watching/viewing self view (preview)
	*/
	VIDYO_CLIENT_IN_EVENT_STOP_WATCH_SELF_VIEW = 3214,
	/*!
		Used to start or stop video sources in local renderer

		@see VidyoClientInEventSetRendererVisible
	*/
	VIDYO_CLIENT_IN_EVENT_SET_RENDERER_VISIBLE = 3215,
	/*!
		Used to start or update watching/viewing a specified video source
		Available only in tiles version of renderer.

		@see VidyoClientInEventStartWatchVideoSource
	*/
	VIDYO_CLIENT_IN_EVENT_RESTART_WATCH_VIDEO_SOURCE = 3216,
	/*!
		Used to start acquire audio source/frame from the specified number of sources.

		@see VidyoClientInEventStartAcquireAudio
	*/
	VIDYO_CLIENT_IN_EVENT_START_ACQUIRE_AUDIO = 3220,
	/*!
		Used to stop acquire audio source/frame.
	*/
	VIDYO_CLIENT_IN_EVENT_STOP_ACQUIRE_AUDIO = 3221,
	/*!
		Used to start sending a video frames.

		@see VidyoClientInEventStartVideoSend
	*/
	VIDYO_CLIENT_IN_EVENT_START_VIDEO_SEND = 3225,
	/*!
		Used to stop sending a video frames.
	*/
	VIDYO_CLIENT_IN_EVENT_STOP_VIDEO_SEND = 3226,
	/*!
		Used to send a video frame.

		@see VidyoClientInEventVideoFrame
	*/
	VIDYO_CLIENT_IN_EVENT_SEND_VIDEO_FRAME = 3227,
	/*!
		Used to start sending a audio frames.

		@see VidyoClientInEventStartAudioSend
	*/
	VIDYO_CLIENT_IN_EVENT_START_AUDIO_SEND = 3230,
	/*!
		Used to stop sending a audio frames.
	*/
	VIDYO_CLIENT_IN_EVENT_STOP_AUDIO_SEND = 3231,
	/*!
		Used to send a audio frame.

		@see VidyoClientAudioFrame
	*/
	VIDYO_CLIENT_IN_EVENT_SEND_AUDIO_FRAME = 3232,
	/*!
		Used to control conference room settings.

		@see VidyoClientInEventControlConferenceRoomSettings
	*/
	VIDYO_CLIENT_IN_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS = 3240,
	/*!
		Used to test self-view using selected camera when not joined in a call or conference (pre-call self-view).
		This is used to start or stop self-view.

		@see VidyoClientInEventPrecallTestCamera
	*/
	VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_CAMERA = 3245,
	/*!
		Used to control selected microphone when not joined in a call or conference (pre-call microphone test).
		This is used to start or stop microphone.

		@see VidyoClientInEventPrecallTestMicrophone
	*/
	VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_MICROPHONE = 3246,
	/*!
		Used to start testing selected speaker when not joined in a call or conference (pre-call speaker test).
		The sound data given in VidyoClientInEventStartPrecallTestSpeaker will be played until requested to
		stop using interface VIDYO_CLIENT_IN_EVENT_STOP_PRECALL_TEST_SPEAKER.

		@see VidyoClientInEventStartPrecallTestSpeaker
	*/
	VIDYO_CLIENT_IN_EVENT_START_PRECALL_TEST_SPEAKER = 3247,
	/*!
		Used to stop testing selected speaker when not joined in a call or conference (pre-call speaker test).

	*/
	VIDYO_CLIENT_IN_EVENT_STOP_PRECALL_TEST_SPEAKER = 3248,
	/*!
		Used to send a command to control meeting. This can be used to control that affect all participants of a conference.
		Some examples are drop all participants, mute audio of all participants, set all participants to privacy.
		The conference on which this event will work is the conference on which the user is connected to.

		@see VidyoClientInEventConferenceControlAllParticipants
	*/
	VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS = 3260,
	/*!
		Used to send a command to control meeting. This can be used to control that affect given participant of a conference.
		Some examples are drop participant, mute audio of participant, set participant to privacy.
		The conference on which this event will work is the conference on which the user is connected to.

		@see VidyoClientInEventConferenceControlParticipant
	*/
	VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_PARTICIPANT = 3270,
	/*!
		A generic command used to send a request to portal.

		@see VidyoClientInEventPortalService
	*/
	VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE = 4000,
	/*!
		Disable all share events

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_DISABLE_SHARE_EVENTS = 4010,
	/*!
		Enable all share events

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_IN_EVENT_ENABLE_SHARE_EVENTS = 4011,
	/*!
		Event used to select speaker *Deprecated*.

		@see VidyoClientInEventSelectSpeaker.
        @warning This API is deprecated. Please use MpVolumeView from Apple instead of this. Details are
        available at https://developer.apple.com/library/ios/documentation/MediaPlayer/Reference/MPVolumeView_Class/index.html

	*/
	VIDYO_CLIENT_IN_EVENT_SELECT_SPEAKER = 4020,
	/*!
		Event used to send group command to all remote participants.

		@see VidyoClientInEventGroupCommand
	*/
	VIDYO_CLIENT_IN_EVENT_GROUP_COMMAND = 5000,
	/*!
		Event used to send private command to a specified remote participants.

		@see VidyoClientInEventPrivateCommand
	*/
	VIDYO_CLIENT_IN_EVENT_PRIVATE_COMMAND = 5010,
    /*!
     Event used to check viability of portal
     
     @see VidyoClientInEventIsPortalAvailable.
     */
    VIDYO_CLIENT_IN_EVENT_IS_PORTAL_AVAILABLE = 5020,
	/*!
		Maximum value for the enumeration.

		Disregard all events with value above this.
	*/
	VIDYO_CLIENT_IN_EVENT_MAX = 99999
} VidyoClientInEvent;

/** @} */


/**
 * @addtogroup VidyoClientOutEventModule
 * @{
 */

/*! @brief Vidyo Client Out Events.

	Enumeration of events that Vidyo Client API Library sends to application.
	Called in #VidyoClientOutEventCallback
*/
typedef enum  VidyoClientOutEvent_
{
	/*!
		Minimum value for the enumeration.

		Disregard all event with value below this.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_MIN = 99,
	/*!
		Application may display a notification message. Informational only.

		@see Corresponding parameter structure #VidyoClientOutEventUserMessage
	*/
	VIDYO_CLIENT_OUT_EVENT_USER_MESSAGE = 100,
	/*!
		Signal completion of VidyoClient startup.

		Does not have a parameter.

		@warning No other IN or OUT event or request may be issues before this event.
	*/
	VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED = 200,
	/*!
		Signal that sign-in to server has been initiated.

		Reports if the endpoint ID is activated or not.
		@see Corresponding parameter structure #VidyoClientOutEventSignIn

		@see <a href="index.html">Main page</a> for example
	*/
	VIDYO_CLIENT_OUT_EVENT_SIGN_IN = 300,
	/*!
		Signal that sign-out from server has been completed.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_SIGN_OUT = 301,
	/*!
		Signal status of connectivity with server.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_SUBSCRIBING = 400,
	/*!
		Application should exit as soon as possible.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_APP_EXIT = 500,
	/*!
		Change in list of attached devices for specified kind of device.
		This event is sent out whenever the attached devices for specified kind
		is changed and the device selection is required to be done by the user.
		This means VidyoClient could not select a device from the current list based
		on the current logic and user has to select one.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECT = 600,
	/*!
		This out event is send whenever a device is plugged in to or plugged out of the system.
		This event signals a change in the list of devices operating system has.

		@details @see Corresponding parameter structure #VidyoClientOutEventDevicesChanged

		@note Use request #VIDYO_CLIENT_REQUEST_GET_CONFIGURATION to get list of devices
		and currently selected device.  Use request #VIDYO_CLIENT_REQUEST_SET_CONFIGURATION
		to change currently selected device.
	*/
	VIDYO_CLIENT_OUT_EVENT_DEVICES_CHANGED = 601,
	/*!
		This event is send out when the device used in the active conference is no longer available.
		Will happen only while in a conference.

		This event signals a newly selected device which is selected automatically 
		by the library. The value of VidyoClientOutEventDeviceSelectionChanged::changeType can be #VIDYO_CLIENT_USER_MESSAGE_DEVICE_LOST
		when there is no appropriate device exists in the system. Then VidyoClientOutEventDeviceSelectionChanged::newDeviceName will not be valid.

		@see Corresponding parameter structure #VidyoClientOutEventDeviceSelectionChanged
	*/
	VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECTION_CHANGED = 602,
	/*!
		This out event is send whenever the OS default device used for audio in or audio out is changed.

		@details @see Corresponding parameter structure #VidyoClientOutEventSelectedDeviceOnOsChanged

		@note Use request #VIDYO_CLIENT_REQUEST_GET_CONFIGURATION to get current list of devices
		and currently selected device.
	*/
	VIDYO_CLIENT_OUT_EVENT_SELECTED_DEVICE_ON_OS_CHANGED = 603,
	/*!
		Display dialog box with progress bar for pending ring operation.

		@see Corresponding parameter structure #VidyoClientOutEventStartProgress
	*/
	VIDYO_CLIENT_OUT_EVENT_RINGING = 700,
	/*!
		Advance progress bar for pending ring operation.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_RING_PROGRESS = 701,
	/*!
		Dismiss dialog box with progress bar for pending ring operation.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_END_RINGING = 702,
	/*!
		Display dialog box with progress bar for pending call operation.

		@see Corresponding parameter structure #VidyoClientOutEventStartProgress
	*/
	VIDYO_CLIENT_OUT_EVENT_CALLING = 800,
	/*!
		Advance progress bar for pending call operation.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_CALL_PROGRESS = 801,
	/*!
		Dismiss dialog box with progress bar for pending call operation.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_END_CALLING = 802,
	/*!
		Display dialog box with progress bar for pending join operation.

		@see Corresponding parameter structure #VidyoClientOutEventStartProgress
	*/
	VIDYO_CLIENT_OUT_EVENT_JOINING = 900,
	/*!
		Advance progress bar for pending join operation.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_JOIN_PROGRESS = 901,
	/*!
		Display dialog box with progress bar for pending retry operation.

		@see Corresponding parameter structure #VidyoClientOutEventStartProgress
	*/
	VIDYO_CLIENT_OUT_EVENT_RETRYING = 1000,
	/*!
		Advance progress bar for pending retry operation.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_RETRY_PROGRESS = 1001,
	/*!
		Indicate completion or cancellation of certain operations relating to state of
		entering and leaving conferences.  Also used to dismiss dialog box with progress
		bar for certain pending operations.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_END_PROCESSING = 1100,
	/*!
		Inform the user that a sound buffer finished playing.

		@see VIDYO_CLIENT_IN_EVENT_PLAY_SOUND
		@see Corresponding parameter structure #VidyoClientInEventPlaySound
	*/
	VIDYO_CLIENT_OUT_EVENT_PLAY_SOUND_DONE = 1105,
	/*!
		Signal that operation to join a conference is complete.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE = 1200,
	/*!
		Signal that operation to leave a conference is complete.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED = 1201,
	/*!
		Signal that number of participants in conference have
		changed.

		@see Corresponding parameter structure #VidyoClientOutEventParticipantsChanged
	*/
	VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED = 1202,
	/*!
		Signal that operation to clear a conference is complete.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CLEARED = 1203,
	/*!
		Signal that operation to join a conference is complete after retries.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE_AFTER_RETRY = 1204,
	/*!
		Signal that a remote source is added in the conference.

		@see Corresponding parameter structure #VidyoClientOutEventRemoteSourceChanged
	*/
	VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_ADDED = 1210,
	/*!
		Signal that a remote source is removed in the conference.

		@see Corresponding parameter structure #VidyoClientOutEventRemoteSourceChanged
	*/
	VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_REMOVED = 1211,
	/*!
		Display dialog box for an incoming call, allowing user to accept or decline the call.

		@see Corresponding parameter structure #VidyoClientOutEventIncomingCall
	*/
	VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL = 1300,
	/*!
		Dismiss dialog box for an incoming call, as call has timed out or has been canceled.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_END_INCOMING_CALL = 1301,
	/*!
		Acknowledge change of how own video shown in video layout.

		@see Corresponding parameter structure #VidyoClientOutEventPreview

		@see VIDYO_CLIENT_IN_EVENT_PREVIEW
		@see VidyoClientOutEventPreview
	*/
	VIDYO_CLIENT_OUT_EVENT_PREVIEW = 1400,
	/*!
		Acknowledge change of mute state of audio input (capture/microphone) device.

		@see Corresponding parameter structure #VidyoClientOutEventMuted
	*/
	VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN = 1500,
	/*!
		Acknowledge change of mute state of audio output (playback/speaker) device.

		@see Corresponding parameter structure #VidyoClientOutEventMuted
	*/
	VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_OUT = 1501,
	/*!
		Acknowledge change of privacy state of video (capture/camera) device.

		@see Corresponding parameter structure #VidyoClientOutEventMuted
	*/
	VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO = 1502,
	/*!
		Indicate change of mute state of audio input (capture/microphone) device, due to server.

		@see Corresponding parameter structure #VidyoClientOutEventMuted
	*/
	VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_AUDIO_IN = 1503,
	/*!
		Indicate change of privacy state of video (capture/camera) device, due to server.

		@see Corresponding parameter structure #VidyoClientOutEventMuted
	*/
	VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_VIDEO = 1504,
	/*!
		Indicates that remote application window share added.

		@see Corresponding parameter structure #VidyoClientOutEventAddShare
	*/
	VIDYO_CLIENT_OUT_EVENT_ADD_SHARE = 1600,
	/*!
		Indicates that remote application window share removed.

		@see Corresponding parameter structure #VidyoClientOutEventRemoveShare
	*/
	VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE = 1601,
	/*!
		Signal the closing of a detached remote application share.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_SHARE_CLOSED = 1602,
	/*!
		Resize of video layout.

		@see Corresponding parameter structure #VidyoClientOutEventResize
	*/
	VIDYO_CLIENT_OUT_EVENT_RESIZE = 1700,
	/*!
		Limit imposed on number of remote participants which can be rendered.

		@see Corresponding parameter structure #VidyoClientOutEventParticipantsLimit
	*/
	VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT = 1800,
	/*!
		Echo in the audio path has been detected.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_ECHO_DETECTED = 1900,
	/*!
		Rendering window captured a keyboard key-down event.

		@see Corresponding parameter structure #VidyoClientOutEventKeyboard
	*/
	VIDYO_CLIENT_OUT_EVENT_KEYDOWN = 2000,
	/*!
		Rendering window captured a keyboard key-up event.

		@see Corresponding parameter structure #VidyoClientOutEventKeyboard
	*/
	VIDYO_CLIENT_OUT_EVENT_KEYUP = 2001,
	/*!
		Rendering window captured a mouse down event.

		@see Corresponding parameter structure #VidyoClientOutEventMouse
	*/
	VIDYO_CLIENT_OUT_EVENT_MOUSE_DOWN = 2002,
	/*!
		Rendering window captured a mouse up event.

		@see Corresponding parameter structure #VidyoClientOutEventMouse
	*/
	VIDYO_CLIENT_OUT_EVENT_MOUSE_UP = 2003,
	/*!
		Rendering window captured a mouse move event.

		@see Corresponding parameter structure #VidyoClientOutEventMouse
	*/
	VIDYO_CLIENT_OUT_EVENT_MOUSE_MOVE = 2004,
	/*!
		Rendering window captured a mouse scroll event.

		@see Corresponding parameter structure #VidyoClientOutEventMouse
	*/
	VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL = 2005,
	/*!
		Rendering window captured a touch event.

		@see Corresponding parameter structure #VidyoClientOutEventTouch

		@note Mobile only
	*/
	VIDYO_CLIENT_OUT_EVENT_TOUCH = 2006,
	/*!
		Floating share window created or destroyed event.

		@see Corresponding parameter structure #VidyoClientOutEventFloatingWindow
	*/
	VIDYO_CLIENT_OUT_EVENT_FLOATING_WINDOW = 2007,
	/*!
		Indicate an updated list of participants in the conference that have a controllable camera.

		@see Corresponding parameter structure #VidyoClientOutEventFeccListUpdated
	*/
	VIDYO_CLIENT_OUT_EVENT_FECC_LIST_UPDATED = 2100,
	/*!
		Received a camera control request over FECC.

		@see Corresponding parameter structure #VidyoClientOutEventControlCamera
	*/
	VIDYO_CLIENT_OUT_EVENT_CONTROL_CAMERA = 2101,
	/*!
		Acknowledge setting of display mode of participant's video source.

		@see Corresponding parameter structure #VidyoClientOutEventSetParticipantVideoModeDone
	*/
	VIDYO_CLIENT_OUT_EVENT_SET_PARTICIPANT_VIDEO_MODE_DONE = 2102,
	/*!
		Report conference information update event.

		@see Corresponding parameter structure #VidyoClientOutEventConferenceInfoUpdate
	*/
	VIDYO_CLIENT_OUT_EVENT_CONFERENCE_INFO_UPDATE = 2103,
	/*!
		Report status of remote participants whose camera is being controlled.

		@see Corresponding parameter structure #VidyoClientOutEventFeccStatusUpdate
	*/
	VIDYO_CLIENT_OUT_EVENT_FECC_STATUS_UPDATE = 2104,
	/*!
		Indicates that the user has clicked an incall button associated with a specific participant.
		@see Corresponding parameter structure #VidyoClientOutEventParticipantButtonClick

		@note Mobile only
	*/
	VIDYO_CLIENT_OUT_EVENT_PARTICIPANT_BUTTON_CLICK = 2105,
	/*!
		Server-based media control command details against a media device type.

		@see Corresponding parameter structure #VidyoClientOutEventMediaControl
	*/
	VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL = 2200,
	/*!
		Report login to Portal succes/error

		@see Corresponding parameter structure #VidyoClientOutEventLogIn
	*/
	VIDYO_CLIENT_OUT_EVENT_LOGIN = 2300,
	/*!
		Report licensing on Portal succes/error

		@see Corresponding parameter structure #VidyoClientOutEventLicense
	*/
	VIDYO_CLIENT_OUT_EVENT_LICENSE = 2301,
	/*!
		Report linking end-point succes/error

		@see Corresponding parameter structure #VidyoClientOutEventLinked
	*/
	VIDYO_CLIENT_OUT_EVENT_LINKED = 2302,
	/*!
		Report signed-in success

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_SIGNED_IN = 2303,
	/*!
		Report signed-out success or signed-in failure with an error
		Report server requested sign-out.

		@see Corresponding parameter structure #VidyoClientOutEventSignedOut
	*/
	VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT = 2304,
	/*!
		Report state of Guest logged & joined-conference; possible with an error

		@see Corresponding parameter structure #VidyoClientOutEventRoomLink
	*/
	VIDYO_CLIENT_OUT_EVENT_ROOM_LINK = 2305,
	/*!
		Returns the preferred client version on the portal

		@see Corresponding parameter structure #VidyoClientOutEventClientVersionOnServer
	*/
	VIDYO_CLIENT_OUT_EVENT_CLIENT_VERSION_ON_SERVER = 2306,
	/*!
        Report signed-in success and complete
        It is now safe to contact portal for search, control meeting etc

        Does not have a parameter.
    */
    VIDYO_CLIENT_OUT_EVENT_SIGN_IN_COMPLETE = 2307,
	/*!
		Acknowledge change of enable state of status bar widget on video layout.

		Sending the corresponding #VIDYO_CLIENT_OUT_EVENT_ENABLED_STATUS_BAR event will result in this out event to
		be sent.

		@see Corresponding parameter structure #VidyoClientOutEventEnabled

		@note Mobile platforms only
	*/
	VIDYO_CLIENT_OUT_EVENT_ENABLED_STATUS_BAR = 2400,
	/*!
		Acknowledge change of enable state of button bar widget on video layout.

		@see Corresponding parameter structure #VidyoClientOutEventEnabled
		@note Mobile platforms only
	*/
	VIDYO_CLIENT_OUT_EVENT_ENABLED_BUTTON_BAR = 2401,
	/*!
		Event to indicate selected remote participants for viewing is changed

		@see Corresponding parameter structure #VidyoClientRequestParticipants
	*/
	VIDYO_CLIENT_OUT_EVENT_SELECTED_PARTICIPANTS_CHANGED = 2450,
	/*!
		An update of the current call state.

		@see Corresponding parameter structure #VidyoClientOutEventCallState
		@see VidyoClientCallState
	*/
	VIDYO_CLIENT_OUT_EVENT_CALL_STATE = 2500,
	/*!
		The text message received as part of a group chat from a remote participant.

		@see Corresponding parameter structure #VidyoClientOutEventGroupChat
	*/
	VIDYO_CLIENT_OUT_EVENT_GROUP_CHAT = 2600,
	/*!
		The text message received as part of a private chat from a remote participant.

		@see Corresponding parameter structure #VidyoClientOutEventPrivateChat
	*/
	VIDYO_CLIENT_OUT_EVENT_PRIVATE_CHAT = 2601,
	/*!
		The out event received if not able to send group chat / private chat to remote participants
		Review log file

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_CHAT_SEND_ERROR = 2610,
	/*!
		One or more of alarms are set at this time

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_ALARMS_RAISED = 2700,
	/*!
		All alarms have been cleared

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_ALARMS_CLEARED = 2701,
    /*!
     One or more of alarms raised earlier have been cleared
     
     Does not have a parameter.
     */
    VIDYO_CLIENT_OUT_EVENT_ALARMS_UPDATED = 2702,
	/*!
		To report the retrieved portal prefix

		@see Corresponding parameter structure #VidyoClientOutEventPortalPrefix
	*/
	VIDYO_CLIENT_OUT_EVENT_PORTAL_PREFIX = 2710,
	/*!
		To report the retrieved portal features. Different optional portal features and their enabled/disabled status

		@see Corresponding parameter structure #VidyoClientEventPortalFeatures
	 */
	VIDYO_CLIENT_OUT_EVENT_PORTAL_FEATURES = 2715,
	/*!
		To report the actions taken due to CPU usage

		@see Corresponding parameter structure #VidyoClientOutEventCpuUsageActions
	 */
	VIDYO_CLIENT_OUT_EVENT_CPU_USAGE_ACTIONS = 2720,
	/*!
		To report that lecture mode has started or stopped or changed

		@see Corresponding parameter structure #VidyoClientOutEventLectureModeStage
	 */
	VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_STAGE = 2800,
	/*!
		To report that lecture mode presenter has changed

		@see Corresponding parameter structure #VidyoClientOutEventLectureModePresenter
	 */
	VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_PRESENTER_CHANGED = 2802,
	/*!
		To report that the raise hand status was cleared

		Does not have a parameter.
	 */
	VIDYO_CLIENT_OUT_EVENT_LECTURE_HAND_CLEARED = 2803,
	/*!
		Used to report received audio frames.

		@see VidyoClientOutEventAudioFrameReceived
	*/
	VIDYO_CLIENT_OUT_EVENT_AUDIO_FRAME_RECEIVED = 2810,
	/*!
		Used to report received video frames from remote conference participants.

		@see VidyoClientOutEventVideoFrameReceived
	*/
	VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED = 2811,
	/*!
		Used to report received video frame of self view (preview).

		@see VidyoClientOutEventVideoFrameReceived
	*/
	VIDYO_CLIENT_OUT_EVENT_SELF_VIEW_VIDEO_FRAME_RECEIVED = 2812,
	/*!
		Used to send response to control conference room settings event.

		@see VidyoClientOutEventControlConferenceRoomSettings
	*/
	VIDYO_CLIENT_OUT_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS = 2820,	
	/*!
		Used to report the status of test device test using selected device when not joined in a call or conference.

		@see VidyoClientOutEventPrecallTestDevice
	*/
	VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE = 2830,
	/*!
		When a shared application window is closed the sharing will stop automatically and this out event is send.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_SHARED_WINDOW_CLOSED = 2850,
	/*!
		When a shared screen or display is disconnected the sharing will stop automatically and this out event is send.

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_SHARED_SCREEN_DISCONNECTED = 2851,
	/*!
		Used to send a response to control meeting command VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS.

		@see VidyoClientOutEventConferenceControlAllParticipants
		@see VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS
	*/
	VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS = 2855,
	/*!
		Used to send a response to control meeting command VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_PARTICIPANT.

		@see VidyoClientOutEventConferenceControlParticipant
		@see VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_PARTICIPANT
	*/
	VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CONTROL_PARTICIPANT = 2856,
	/*!
		Used to send changes in network interface.

		@see VidyoClientOutEventNetworkInterfaceChanged
	*/
	VIDYO_CLIENT_OUT_EVENT_NETWORK_INTERFACE_CHANGED = 2860,
	/*!
		Used to send a response to portal service command VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE.

		@see VidyoClientOutEventPortalService
		@see VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE
	*/
	VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE = 3000,
	/*!
		Used to send logs

		@see VidyoClientOutEventLog
		@see VidyoClientConsoleLogConfiguration
	*/
	VIDYO_CLIENT_OUT_EVENT_LOG = 3100,
	/*!
		The command received as part of a group command from a remote participant.

		@see Corresponding parameter structure #VidyoClientOutEventGroupCommand
	*/
	VIDYO_CLIENT_OUT_EVENT_GROUP_COMMAND = 4000,
	/*!
		The command received as part of a private command from a remote participant.

		@see Corresponding parameter structure #VidyoClientOutEventPrivateCommand
	*/
	VIDYO_CLIENT_OUT_EVENT_PRIVATE_COMMAND = 4001,
	/*!
		The out event received if not able to send group/private command to remote participants
		Review log file

		Does not have a parameter.
	*/
	VIDYO_CLIENT_OUT_EVENT_COMMAND_SEND_ERROR = 4010,
    /*!
     Used to send a response about viability of portal
     
     @see Corresponding parameter structure #VidyoClientOutEventIsPortalAvailable
     */
    VIDYO_CLIENT_OUT_EVENT_IS_PORTAL_AVAILABLE = 4020,
    /*!
     Used to notify application that frames received
     
     Does not have a parameter.
     */
    VIDYO_CLIENT_OUT_EVENT_INITIAL_VIDEO_FRAME_SENT = 4030,
	/*!
		Maximum value for the enumeration.

		Disregard all events with value above this.
	*/
	VIDYO_CLIENT_OUT_EVENT_MAX = 99999,
} VidyoClientOutEvent;

/** @} */

/**
* @addtogroup VidyoClientRequestModule
* @{
*/
/*! Vidyo Client Requests
	Enumeration of requests that application issues to Vidyo Client API Library.

	@see VidyoClientSendRequest
*/
typedef enum VidyoClientRequest_
{
	/*!
		Minimum value for the enumeration.

		Disregard all event with value below this.

		Does not use parameter structure. Use NULL.
	*/
	VIDYO_CLIENT_REQUEST_MIN = VIDYO_CLIENT_REQUEST_BASE + 100,
	/*!
		Get all configuration data.

		@see Corresponding parameter structure #VidyoClientRequestConfiguration
	*/
	VIDYO_CLIENT_REQUEST_GET_CONFIGURATION = VIDYO_CLIENT_REQUEST_BASE + 100,
	/*!
		Set writable configuration data.

		@see Corresponding parameter structure #VidyoClientRequestConfiguration
	*/
	VIDYO_CLIENT_REQUEST_SET_CONFIGURATION = VIDYO_CLIENT_REQUEST_BASE + 101,
	/*!
		Inquire endpoint ID.

		@see Corresponding parameter structure #VidyoClientRequestGetEid
	*/
	VIDYO_CLIENT_REQUEST_GET_EID = VIDYO_CLIENT_REQUEST_BASE + 200,
	/*!
		Inquire endpoint License ID.

		@see Corresponding parameter structure #VidyoClientRequestGetLid
	*/
	VIDYO_CLIENT_REQUEST_GET_LID = VIDYO_CLIENT_REQUEST_BASE + 201,
	/*!
		Inquire endpoint PID.

		@see Corresponding parameter structure #VidyoClientRequestGetPid
	*/
	VIDYO_CLIENT_REQUEST_GET_PID = VIDYO_CLIENT_REQUEST_BASE + 202,
	/*!
		Perform endpoint registration.

		@see Corresponding parameter structure #VidyoClientRequestActivateEid
	*/
	VIDYO_CLIENT_REQUEST_ACTIVATE_EID = VIDYO_CLIENT_REQUEST_BASE + 203,
	/*!
		Returns the currently used sign-in information and parameters

		@see Corresponding parameter structure #VidyoClientRequestConnectivityInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_CONNECTIVITY_INFO = VIDYO_CLIENT_REQUEST_BASE + 204,
	/*!
		Inquire level of audio input (capture/microphone) device.

		@see Corresponding parameter structure #VidyoClientRequestVolume
	*/
	VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_IN = VIDYO_CLIENT_REQUEST_BASE + 300,
	/*!
		Change level of audio input (capture/microphone) device.

		@see Corresponding parameter structure #VidyoClientRequestVolume
	*/
	VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_IN = VIDYO_CLIENT_REQUEST_BASE + 301,
	/*!
		Inquire volume of audio output (playback/speaker) device.

		@see Corresponding parameter structure #VidyoClientRequestVolume
	*/
	VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT = VIDYO_CLIENT_REQUEST_BASE + 302,
	/*!
		Change volume of audio output (playback/speaker) device.

		@see Corresponding parameter structure #VidyoClientRequestVolume
	*/
	VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_OUT = VIDYO_CLIENT_REQUEST_BASE + 303,
	/*!
		Inquire maximum aggregate bandwidth of all types of media to send.

		@see Corresponding parameter structure Pointer to VidyoInt where the send bandwidth in Kbps is returned.
	*/
	VIDYO_CLIENT_REQUEST_GET_SEND_MAX_KBPS = VIDYO_CLIENT_REQUEST_BASE + 400,
	/*!
		Change maximum aggregate bandwidth of all types of media to send.

		@see Corresponding parameter structure Pointer to VidyoInt which has the value of send bandwidth in Kbps to be set.
	*/
	VIDYO_CLIENT_REQUEST_SET_SEND_MAX_KBPS = VIDYO_CLIENT_REQUEST_BASE + 401,
	/*!
		Inquire maximum aggregate bandwidth of all types of media to receive.

		@see Corresponding parameter structure Pointer to VidyoInt where the receive bandwidth in Kbps is returned.
	*/
	VIDYO_CLIENT_REQUEST_GET_RECV_MAX_KBPS = VIDYO_CLIENT_REQUEST_BASE + 402,
	/*!
		Change maximum aggregate bandwidth of all types of media to receive.

		@see Corresponding parameter structure Pointer to VidyoInt which has the value of receive bandwidth in Kbps to be set.
	*/
	VIDYO_CLIENT_REQUEST_SET_RECV_MAX_KBPS = VIDYO_CLIENT_REQUEST_BASE + 403,
	/*!
		Get list of remote shared windows available for display in a fixed array.

		@see Corresponding parameter structure #VidyoClientRequestWindowShares
	*/
	VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES = VIDYO_CLIENT_REQUEST_BASE + 500,
	/*!
		Start/stop display of remote shared window & toggle window being displayed to next window in list.

		@see Corresponding parameter structure #VidyoClientRequestWindowShares
	*/
	VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES = VIDYO_CLIENT_REQUEST_BASE + 501,
	/*!
		Enable/Disable the application share. (Disabled on Windows 8 and above by default)
		Only supported on Windows 8 and above. for all other os application share is always enabled.

		@see Corresponding parameter structure #VidyoClientRequestEnableAppShare
	*/
	VIDYO_CLIENT_REQUEST_ENABLE_APP_SHARE = VIDYO_CLIENT_REQUEST_BASE + 502,
	/*!
		Set appearance of text labels on video layout, according to language setting.

		@see Corresponding parameter structure #VidyoClientRequestSetLabel
	*/
	VIDYO_CLIENT_REQUEST_SET_LABEL = VIDYO_CLIENT_REQUEST_BASE + 600,
	/*!
		Show / Hide the participant border. (Available only on Tiles version of VidyoClient)

		@see Corresponding parameter structure #VidyoClientRequestSetBorder
	*/
	VIDYO_CLIENT_REQUEST_SET_PARTICIPANT_BORDER = VIDYO_CLIENT_REQUEST_BASE + 605,
	/*!
		Inquire history of VidyoPortals successfully logged into.

		@see Corresponding parameter structure #VidyoClientRequestPortalHistory
	*/
	VIDYO_CLIENT_REQUEST_GET_PORTAL_HISTORY = VIDYO_CLIENT_REQUEST_BASE + 700,
	/*!
		Change history of VidyoPortals successfully logged into.

		@see Corresponding parameter structure #VidyoClientRequestPortalHistory
	*/
	VIDYO_CLIENT_REQUEST_SET_PORTAL_HISTORY = VIDYO_CLIENT_REQUEST_BASE + 701,
	/*!
		Request suggested size (width and height) for video layout.

		@see Corresponding parameter structure #VidyoClientRequestSnapResize
	*/
	VIDYO_CLIENT_REQUEST_SNAP_RESIZE = VIDYO_CLIENT_REQUEST_BASE + 800,
	/*!
		Invoke system dialog for configuration of currently selected video
		device.

		Does not use parameter structure. Use *NULL*.

		@note Windows only
	*/
	VIDYO_CLIENT_REQUEST_SETUP_CAMERA = VIDYO_CLIENT_REQUEST_BASE + 801,
	/*!
		Inquire how own video shown in video layout.

		@see Corresponding parameter structure #VidyoClientInEventPreview
	*/
	VIDYO_CLIENT_REQUEST_GET_PREVIEW_MODE = VIDYO_CLIENT_REQUEST_BASE + 900,
	/*!
		Inquire mute state of audio input (capture/microphone) device.

		@see Corresponding parameter structure #VidyoClientRequestGetMuted
	*/
	VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_IN = VIDYO_CLIENT_REQUEST_BASE + 1000,
	/*!
		Inquire mute state of audio output (playback/speaker) device.

		@see Corresponding parameter structure #VidyoClientRequestGetMuted
	*/
	VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_OUT = VIDYO_CLIENT_REQUEST_BASE + 1001,
	/*!
		Inquire privacy state of video (capture/camera) device.

		@see Corresponding parameter structure #VidyoClientRequestGetMuted
	*/
	VIDYO_CLIENT_REQUEST_GET_MUTED_VIDEO = VIDYO_CLIENT_REQUEST_BASE + 1002,
	/*!
		Inquire mute state of audio input (capture/microphone) device, as controlled by server.

		@see Corresponding parameter structure #VidyoClientRequestGetMuted
	*/
	VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_AUDIO_IN = VIDYO_CLIENT_REQUEST_BASE + 1003,
	/*!
		Inquire mute state of video (capture/camera) device, as controlled by server.

		@see Corresponding parameter structure #VidyoClientRequestGetMuted
	*/
	VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_VIDEO = VIDYO_CLIENT_REQUEST_BASE + 1004,
	/*!
		Inquire current language setting.

		@see Corresponding parameter structure #VidyoClientRequestGetLanguage
	*/
	VIDYO_CLIENT_REQUEST_GET_LANGUAGE = VIDYO_CLIENT_REQUEST_BASE + 1100,
	/*!
		Inquire secureConnectionState and verifyCertPortalAcct

		@see Corresponding parameter structure #VidyoClientRequestSecureConnection
	*/
	VIDYO_CLIENT_REQUEST_GET_SECURE_CONNECTION = VIDYO_CLIENT_REQUEST_BASE + 1200,
	/*!
		Check whether both audio devices (mic and speaker) are on same device
		and the device is recommended audio device. If both audio devices are
		one single recommended device, echo cancellation is recommended to be
		kept disabled.

		@see Corresponding parameter structure #VidyoClientRequestEchoRecommendation
	*/
	VIDYO_CLIENT_REQUEST_GET_ECHO_RECOMMENDATION = VIDYO_CLIENT_REQUEST_BASE + 1300,
	/*!
		Check whether given audio devices (mic and speaker) is a recommended device.

		@see Corresponding parameter structure #VidyoClientRequestCheckRecommended
	*/
	VIDYO_CLIENT_REQUEST_CHECK_RECOMMENDED = VIDYO_CLIENT_REQUEST_BASE + 1301,
	/*!
		Check validity of web proxy configurations

		@see Corresponding parameter structure #VidyoClientRequestWebProxySettingValid
	*/
	VIDYO_CLIENT_REQUEST_GET_WEB_PROXY_SETTING_VALID = VIDYO_CLIENT_REQUEST_BASE + 1400,
	/*!
		Return if web proxy settings are ignored.

		@see Corresponding parameter structure Pointer to VidyoUint.

		@warning Currently not implemented. Do not use.
	*/
	VIDYO_CLIENT_REQUEST_IS_WEBPROXY_SKIPPED = VIDYO_CLIENT_REQUEST_BASE + 1401,
	/*!
		Sets the User Name and Password associated with the Web Proxy.

		@see Corresponding parameter structure #VidyoClientRequestWebProxySetUsernamePassword
	*/
	VIDYO_CLIENT_REQUEST_SET_WEBPROXY_USERNAME_PASSWORD = VIDYO_CLIENT_REQUEST_BASE + 1402,
	/*!
		Return current user ID.

		@see Corresponding parameter structure #VidyoClientRequestCurrentUser

		@warning For future use. Currently not supported.
	*/
	VIDYO_CLIENT_REQUEST_GET_CURRENT_USER = VIDYO_CLIENT_REQUEST_BASE + 1500,
	/*!
		Return current conference display details.

		@see Corresponding parameter structure #VidyoClientRequestSessionDisplayInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_CURRENT_SESSION_DISPLAY_INFO = VIDYO_CLIENT_REQUEST_BASE + 1501,
	/*!
		Return current limits for rendering of remote participants.

		@see Corresponding parameter structure #VidyoClientRequestParticipantsLimit
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS_LIMIT = VIDYO_CLIENT_REQUEST_BASE + 1502,
	/*!
		Return basic info for all participants.

		@see Corresponding parameter structure #VidyoClientRequestParticipants
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS = VIDYO_CLIENT_REQUEST_BASE + 1503,
	/*!
		Return ID of user placing incoming call.

		@see Corresponding parameter structure #VidyoClientRequestInvitingUser
	*/
	VIDYO_CLIENT_REQUEST_GET_INVITING_USER = VIDYO_CLIENT_REQUEST_BASE + 1504,
	/*!
		Inquire VidyoRouter used by client for the current conference.

		@see Corresponding parameter structure #VidyoClientRequestSessionVidyoRouter
	*/
	VIDYO_CLIENT_REQUEST_GET_CURRENT_SESSION_VIDYO_ROUTER = VIDYO_CLIENT_REQUEST_BASE + 1505,
	/*!
		Get the list of controllable far end cameras available in conference call.

		@see Corresponding parameter structure #VidyoClientRequestFeccList
	*/
	VIDYO_CLIENT_REQUEST_GET_FECC_LIST = VIDYO_CLIENT_REQUEST_BASE + 1506,
	/*!
		Get the list of general conference information reported by VidyoRouter in conference call.

		@see Corresponding parameter structure #VidyoClientRequestConferenceInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_CONFERENCE_INFO = VIDYO_CLIENT_REQUEST_BASE + 1507,
	/*!
		Get the current call state (see documentation for VidyoClientCallState)

		@see Corresponding parameter structure #VidyoClientRequestCallState
	 */
	VIDYO_CLIENT_REQUEST_GET_CALL_STATE = VIDYO_CLIENT_REQUEST_BASE + 1508,
	/*!
		Return basic info for all selected participants for viewing or rendering.

		@see Corresponding parameter structure #VidyoClientRequestParticipants
	*/
	VIDYO_CLIENT_REQUEST_GET_SELECTED_PARTICIPANTS = VIDYO_CLIENT_REQUEST_BASE + 1509,
	/*!
		Enable gathering of conference statistics.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_REQUEST_STATISTICS_ENABLE = VIDYO_CLIENT_REQUEST_BASE + 1600,
	/*!
		Disable gathering of conference statistics.

		Does not use parameter structure. Use *NULL*.
	*/
	VIDYO_CLIENT_REQUEST_STATISTICS_DISABLE = VIDYO_CLIENT_REQUEST_BASE + 1601,
	/*!
		Inquire current conference bandwidth statistics.

		@see Corresponding parameter structure #VidyoClientRequestBandwidthInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_BANDWIDTH_INFO = VIDYO_CLIENT_REQUEST_BASE + 1602,
	/*!
		Inquire current conference video resolution that is encoded.

		@see Corresponding parameter structure Pointer to VidyoRect where the encode resolution is returned.
	*/
	VIDYO_CLIENT_REQUEST_GET_VIDEO_ENCODE_RESOLUTION = VIDYO_CLIENT_REQUEST_BASE + 1603,
	/*!
		Inquire current conference video frame rate that is captured, encoded, and sent.

		@see Corresponding parameter structure #VidyoClientRequestFrameRateInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_VIDEO_FRAME_RATE_INFO = VIDYO_CLIENT_REQUEST_BASE + 1604,
	/*!
		Inquire current conference number of IFrames, FIRs, NACKs, and mediaRTT relating
		to media sent to network.

		@see Corresponding parameter structure #VidyoClientRequestMediaInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_MEDIA_INFO = VIDYO_CLIENT_REQUEST_BASE + 1605,
	/*!
		Inquire current conference statistics relating to rate shaper.

		@see Corresponding parameter structure #VidyoClientRequestRateShaperInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_RATE_SHAPER_INFO = VIDYO_CLIENT_REQUEST_BASE + 1606,
	/*!
		Inquire current CPU utilization.

		@see Corresponding parameter structure Pointer to VidyoUint where the CPU utilization is returned.
	*/
	VIDYO_CLIENT_REQUEST_GET_CURRENT_CPU_UTIL = VIDYO_CLIENT_REQUEST_BASE + 1607,
	/*!
		Inquire current conference statistics for all remote participants.

		@see Corresponding parameter structure #VidyoClientRequestParticipantInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_INFO = VIDYO_CLIENT_REQUEST_BASE + 1608,
	/*!
		Inquire total number of conference participants.

		@see Corresponding parameter structure #VidyoClientRequestGetNumParticipants
	*/
	VIDYO_CLIENT_REQUEST_GET_NUM_PARTICIPANTS = VIDYO_CLIENT_REQUEST_BASE + 1609,
	/*!
		Retrieve the conference participant's name at a given index in the
		list of participants.

		@see Corresponding parameter structure #VidyoClientRequestGetParticipantNameAt
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_NAME_AT = VIDYO_CLIENT_REQUEST_BASE + 1610,
	/*!
		Retrieve the conference participant's statistics at a given
		index in the list of participants.

		@see Corresponding parameter structure #VidyoClientRequestParticipantStatisticsAt
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT = VIDYO_CLIENT_REQUEST_BASE + 1611,
	/*!
		Retrieve a list of conference participant.

		The list start from the given index.
		@see Corresponding parameter structure #VidyoClientRequestGetParticipantNameList
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_NAME_LIST = VIDYO_CLIENT_REQUEST_BASE + 1612,
	/*!
		Retrieve conference participant statistics.

		Retrieve conference participant statistics for a list
		of participants. The starting index of list shall be provided.
		@see Corresponding parameter structure #VidyoClientRequestParticipantStatisticsList
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST = VIDYO_CLIENT_REQUEST_BASE + 1613,
	/*!
		Retrieve conference participant details.

		Retrieve conference participant details
		Participant index to be provided
		@see Corresponding parameter structure #VidyoClientRequestParticipantDetailsAt
	*/
	VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_DETAILS_AT = VIDYO_CLIENT_REQUEST_BASE + 1614,
	/*!
		Used to retrieve current active users

		@see Corresponding parameter structure #VidyoClientRequestAudioActiveUsers
	*/
	VIDYO_CLIENT_REQUEST_GET_AUDIO_ACTIVE_USERS = VIDYO_CLIENT_REQUEST_BASE + 1615,
	/*!
		Used to retrieve Audio energy

		@see Corresponding parameter structure #VidyoClientRequestAudioEnergyInfo
	*/
	VIDYO_CLIENT_REQUEST_GET_AUDIO_ENERGY_INFO = VIDYO_CLIENT_REQUEST_BASE + 1616,
	/*!
		Inquire specified display string for current language.

		@see Corresponding parameter structure #VidyoClientRequestGetDisplayString
	*/
	VIDYO_CLIENT_REQUEST_GET_DISPLAY_STRING = VIDYO_CLIENT_REQUEST_BASE + 1700,
	/*!
		Get status of endpoint.

		@see Corresponding parameter structure #VidyoClientRequestGetEndpointStatus
	*/
	VIDYO_CLIENT_REQUEST_GET_ENDPOINT_STATUS = VIDYO_CLIENT_REQUEST_BASE + 1800,
	/*!
		Set region rectangle for video layout.

		@see Corresponding parameter structure #VidyoClientRequestSetLayoutRect
		@note Not available on mobile platforms.
	 */
	VIDYO_CLIENT_REQUEST_SET_LAYOUT_RECT = VIDYO_CLIENT_REQUEST_BASE + 1900,
	/*!
		Set the parent of the rendering window. 
		NULL implies that endpoint is not specifying the parent for rendering window. Rendering window will still be created
		Can not be set during a call.

		@see Corresponding parameter structure #VidyoWindowId
	 */
	VIDYO_CLIENT_REQUEST_SET_GUI_WINDOW = VIDYO_CLIENT_REQUEST_BASE + 1901,
	/*!
		Set log levels and categories.

		@see Corresponding parameter structure #VidyoClientRequestSetLogLevelsAndCategories
	 */
	VIDYO_CLIENT_REQUEST_SET_LOG_LEVELS_AND_CATEGORIES = VIDYO_CLIENT_REQUEST_BASE + 2000,
	/*!
		Get the number of entries in the application share dock and the participant
		video dock.  This request should be made before calling the
		#VIDYO_CLIENT_IN_EVENT_TOGGLE_VIDEO_DOCK or #VIDYO_CLIENT_IN_EVENT_TOGGLE_APPLICATION_DOCK
		events.

		@see Corresponding parameter structure #VidyoClientRequestGetDockCounts

		@note Mobile only
	*/
	VIDYO_CLIENT_REQUEST_GET_DOCK_COUNTS = VIDYO_CLIENT_REQUEST_BASE + 2100,
	/*!
		Get list of open application windows and list of available system desktops.

		@see Corresponding parameter structure #VidyoClientRequestGetWindowsAndDesktops

		@note Windows and MacOs only
	 */
	VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS = VIDYO_CLIENT_REQUEST_BASE + 2200,
	/*!
		Get the list of application windows that are in white list of sharable window.

		@see Corresponding parameter structure #VidyoClientSharableWindowWhiteList

		@note Windows only
	 */
	VIDYO_CLIENT_REQUEST_GET_SHARABLE_WINDOW_WHITE_LIST = VIDYO_CLIENT_REQUEST_BASE + 2210,
	/*!
		Set the list of application windows that are in white list of sharable window.
		If an open application window whose name contain one of the white listed window name,
		that windows property (e.g. is visible, is transparent toolbar window etc) will not
		be verified and it will be included in the list if sharable window list when using API
		#VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS

		@see Corresponding parameter structure #VidyoClientSharableWindowWhiteList

		@note Windows only
	 */
	VIDYO_CLIENT_REQUEST_SET_SHARABLE_WINDOW_WHITE_LIST = VIDYO_CLIENT_REQUEST_BASE + 2211,
	/*!
     Change backgrounded state during a conference
     
     @see VidyoClientRequestSetBackground
     */
	VIDYO_CLIENT_REQUEST_SET_BACKGROUND = VIDYO_CLIENT_REQUEST_BASE + 2300,
    /*!
     Set the rendering mode to be used
     
     @see Corresponding parameter structure #VidyoClientRequestSetRenderingMode
     @note VidyoWeb MacOSX clients only
	 */
    VIDYO_CLIENT_REQUEST_SET_RENDERING_MODE = VIDYO_CLIENT_REQUEST_BASE + 2400,
    /*!
     Called when rendering is to occur
     
     @note VidyoWeb MacOSX clients only
	 */
    VIDYO_CLIENT_REQUEST_DO_RENDER = VIDYO_CLIENT_REQUEST_BASE + 2401,
	 /*!
     Get all the current alarms
     
     @see Corresponding parameter structure #VidyoClientRequestGetAlarms
	 */
    VIDYO_CLIENT_REQUEST_GET_ALARMS = VIDYO_CLIENT_REQUEST_BASE + 2500,
    /*!
     Find out whether VidyoClient has installation license or not
     
     @see Corresponding parameter structure #VidyoClientRequestGetLicensedStatus
	 */
    VIDYO_CLIENT_REQUEST_GET_LICENSED_STATUS = VIDYO_CLIENT_REQUEST_BASE + 2505,
	/*!
     Get all the list of optional portal features supported and their status
     
     @see Corresponding parameter structure #VidyoClientEventPortalFeatures
	 */
	VIDYO_CLIENT_REQUEST_GET_PORTAL_FEATURES = VIDYO_CLIENT_REQUEST_BASE + 2510,
	/*!
     Get the layout paramaters 
     
     @see Corresponding parameter structure #VidyoClientRequestEventLayout
	 */
	VIDYO_CLIENT_REQUEST_GET_LAYOUT = VIDYO_CLIENT_REQUEST_BASE + 2515,
	/*!
     Get the media format used when sending  VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED
	 for participant being watched. Default value is ARGB. Other formats supported are
	 I420 and YU12.
     
     @see Corresponding parameter structure #VidyoClientRequestEventGetWatchVideoFormat
	 */
	VIDYO_CLIENT_REQUEST_GET_WATCH_VIDEO_FRAME_FORMAT = VIDYO_CLIENT_REQUEST_BASE + 2520,
	/*!
     Set/Change the media format used when sending  VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED
	 for participant being watched. Default value is ARGB. Other formats supported are
	 I420 and YU12.
     
     @see Corresponding parameter structure #VidyoClientRequestEventSetWatchVideoFormat
	 */
	VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT = VIDYO_CLIENT_REQUEST_BASE + 2521,
	/*!
     Get the communication status of VidyoClient with VidyoManager and VidyoRouter.
     
     @see Corresponding parameter structure #VidyoClientRequestCommunicationStatus
	 */
	VIDYO_CLIENT_REQUEST_GET_COMMUNICATION_STATUS = VIDYO_CLIENT_REQUEST_BASE + 2525,
	/*!
     Show inbuilt statistics window for Desktops.
     
     Does not have a parameter.
	 */
    VIDYO_CLIENT_REQUEST_SHOW_STATISTICS = VIDYO_CLIENT_REQUEST_BASE + 2526,
    /*!
     Set the portal address to configuration file.
     
     @see Corresponding parameter structure #VidyoClientRequestSetPortalAddress
     */
    VIDYO_CLIENT_REQUEST_SET_PORTAL_ADDRESS = VIDYO_CLIENT_REQUEST_BASE + 2600,
    /*!
     Set the bandwidth adjustment period for tiles renderer.
     
     @see Corresponding parameter structure #VidyoClientRequestSetBandwidthAdjustmentPeriod
     */
    VIDYO_CLIENT_REQUEST_SET_BANDWIDTH_ADJUSTMENT_PERIOD = VIDYO_CLIENT_REQUEST_BASE + 2610,
    /*!
     Get general CPU usage of system.
     
     @see Corresponding parameter structure #VidyoClientRequestGetCPUUsage
     */
    VIDYO_CLIENT_REQUEST_GET_CPU_USAGE = VIDYO_CLIENT_REQUEST_BASE + 2620,

#ifndef DOXYGEN_SHOULD_IGNORE_THIS
	/*!
		Reserved for private requests only used by standard Vidyo clients.

		@see Corresponding parameter structure #VidyoClientRequestPrivate
	*/
	VIDYO_CLIENT_REQUEST_PRIVATE = VIDYO_CLIENT_REQUEST_BASE + 99999,
#endif
	/*!
		Maximum value for the enumeration.

		Disregard all requests with value above this.
	*/
	VIDYO_CLIENT_REQUEST_MAX = VIDYO_CLIENT_REQUEST_BASE + 99999
} VidyoClientRequest;
/** @} */

#endif /* VIDYO_CLIENT_MESSAGES_H */

