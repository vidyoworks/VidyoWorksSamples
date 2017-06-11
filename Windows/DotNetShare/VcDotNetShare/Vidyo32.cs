

using System;
using System.Runtime.InteropServices;
using System.Text;
//using version TAG_VC_3_4_5_0010
namespace VGUClientLogic
{
    public class Vidyo32
    {
        static public string UnicodeStringFromUtf8Array(byte[] bytUTF8)
        {
            byte[] bytUnicode = Encoding.Convert(Encoding.UTF8, Encoding.Unicode, bytUTF8);
            int cntUnicode = Encoding.Unicode.GetCharCount(bytUnicode);
            char[] charUnicode = Encoding.Unicode.GetChars(bytUnicode);
            int j = 0;
            for (; j < cntUnicode; j++)
            {
                if (charUnicode[j] == 0)
                    break;
            }
            string strUnicode = Encoding.Unicode.GetString(bytUnicode, 0, j * 2);
            return strUnicode;
        }

        #region Vidyo Client Dll - Data Type definitions

        public const int MAX_PRIVATE_EVENT_DATA_SIZE = 35 * 1024;//16384
        public const int MAX_USER_MESSAGE_STRING_SIZE = (256 + 1);
        public const int NUM_USER_MESSAGE_CODES = 3;
        public const int FIELD_SIZE = 63 + 1;

        const int USERID_SIZE = 128;
        const int PASSWORD_SIZE = (256 + 1);
        const int SERVERPORT_SIZE = 5 + 1;
        const uint MACADDRESS_SIZE = 17 + 1;
        const int ROOMKEY_SIZE = 128;
        const int PIN_SIZE = 17;
        const int VIDYO_CLIENT_REFERENCE_NUMBER_LEN = 64;
        const uint MAX_DEVICE_NUMBER = 30;
        const int URI_LEN = (256 + 1);
        const int MAX_PARTICIPANTS_NUM = 24;
        const int MAX_URI_LEN = URI_LEN;
        public const int MAX_NUM_APP_WINDOWS = 128;
        public const int MAX_REMOTE_SHARE_APP = 40;
        public const int MAX_SHARE_DISPLAY_DEVICE = 16;
        const int DISPLAY_CONFERENCE_SIZE = (127 * 3 + 1);
        const int PARTICIPANTS_LIMIT_AUTO = 32;
        const int MAX_EID_SIZE = (128 + 1);	// endpoint ID string size
        const int MAX_PID_SIZE = (128 + 1); // participant ID string size
        const int MAX_PORTAL_ADDRESS = (int)(URI_LEN + USERID_SIZE);
        const int DEVICE_NAME_SIZE = (127 + 1);
        const int DEVICE_ID_SIZE = (256 + 1);
        const int MAX_PORTAL_HISTORY_NUMBER = 5;
        const uint MAX_PORTAL_HISTORY_SIZE = (SIGNIN_SERVERADDRESS_SIZE + SIGNIN_USERNAME_SIZE + 10);
        const int VIDYO_MANAGER_ID_SIZE = 64;
        const int ENDPOINT_LOCATION_TAG_SIZE = 40;
        const uint MAX_LABEL_STRING_SIZE = (32 + 1);
        const int MAX_ENTITY_ID = 257;
        const uint MAX_GET_PARTICIPANT_NAME = 128;
        const uint MAX_GET_PARTICIPANT_STATISTICS = 128;
        const uint MAX_VISCA_COMMAND = 128;
        const uint MAX_LOG_STRING_SIZE = 200 + 1;
        const uint MAX_INSTALLER_URI_SIZE = 936;
        const uint MAX_CHAT_MESSAGE_LEN = 1024 + 1;
        const int VIDYO_CLIENT_VERSION_SIZE = 32;
        const int MAX_PASSPHRASE_SIZE = 1024;
        const int MAX_EXTERNAL_ACCESS_TOKEN_SIZE = 1024;
        const uint MAX_FONT_PATH_SIZE = (255 + 1);
        /* Constants related to sign-in */
        const int SIGNIN_VIDYO_PROXY_NUMBER = 8;
        const int SIGNIN_VIDYO_PROXY_ADDRESS_SIZE = 128;
        const int SIGNIN_VIDYO_PROXY_PORT_SIZE = 8;

        const int SIGNIN_SERVERADDRESS_SIZE = 192;
        const int SIGNIN_SERVERPORT_SIZE = 8;
        const int SIGNIN_USERNAME_SIZE = ((63 * 3) + 1);
        const int SIGNIN_PORTAL_ACCESS_KEY_SIZE = (256 + 1);
        const int SIGNIN_PORTALADDRESS_SIZE = 128;
        const int SIGNIN_PORTALVERSION_SIZE = 256;
        const int SIGNIN_MAX_COOKIE_SIZE = 512;
        const int VIDYO_CLIENT_SCREEN_ID_SIZE = 128;

        const uint SERVER_ADDRESS_SIZE = (127 + 1);
        const uint SERVER_PORT_SIZE = (7 + 1);

        //* constants profile configuration
        const string DEF_PROGFILES_DIR = "\\Vidyo\\Vidyo Desktop\\";
        const string DEF_CONFIG_KEY_PATH = "SOFTWARE\\Vidyo\\Vidyo Desktop\\";
        const string DEF_PRODUCT_NAME = "VidyoDesktop";
        const string DEF_MYDOCS_DIR = "\\Vidyo Desktop\\";
        const string DEF_VIDYO_DIR = "\\Vidyo";
        public int DEF_HELP_PORT = 63457;
        const string DEF_LOG_BASE_FILENAME = "VidyoDesktop_";
        const int MAX_IPADDRESS_LEN = 48;

        // uint VidyoSizeT;

        public enum VidyoBool
        {
            VIDYO_FALSE = 0,
            VIDYO_TRUE = 1
        }

        /********************************************************************/
        /* Events from GUI to Vidyo Client Library                          */
        /********************************************************************/

        public enum VidyoClientInEvent
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

                @see VidyoClientInEventSendAudioFrame
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
                Maximum value for the enumeration.

                Disregard all events with value above this.
            */
            VIDYO_CLIENT_IN_EVENT_MAX = 99999
        }

        /********************************************************************/
        /* Events from Vidyo Client Library to GUI                          */
        /********************************************************************/

        public enum VidyoClientOutEvent
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
                One or more of alarms raised earlier have been cleared

                Does not have a parameter.
             */
            VIDYO_CLIENT_OUT_EVENT_ALARMS_CLEARED = 2701,

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
                Maximum value for the enumeration.

                Disregard all events with value above this.
            */
            VIDYO_CLIENT_OUT_EVENT_MAX = 99999,
        };

        /********************************************************************/
        /* Requests from GUI to Vidyo Client Library                        */
        /********************************************************************/

        const int VIDYO_CLIENT_REQUEST_BASE = 100000;
        public enum VidyoClientRequest
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
                Reserved for private requests only used by standard Vidyo clients.

                @see Corresponding parameter structure #VidyoClientRequestPrivate
            */
            VIDYO_CLIENT_REQUEST_PRIVATE = VIDYO_CLIENT_REQUEST_BASE + 99999,

            /*!
                Maximum value for the enumeration.

                Disregard all requests with value above this.
            */
            VIDYO_CLIENT_REQUEST_MAX = VIDYO_CLIENT_REQUEST_BASE + 99999
        };



        ////////////////////////////////// REQUESTs
        /*  Change volume and/or mute state of audio input/output device */
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestVolume
        {
            public uint volume;
        }


        public enum VidyoClientDeviceSelectionMethod
        {
            /*! Device selection method to be used is 'history based device selection' based on previous user selection */
            HISTORY_BASED_SELECTION,
            /*! Device selection method to be used is fixed - do not use any other device */
            KIOSK_DEVICE_SELECTION,
            /*! Device selection method should follow OS/Machine default for audio devices. For camera 'history based device selection' is used */
            OS_DEFAULT_AUDIO_DEVICE_SELECTION,
            /*! Device selection method should follow OS/Machine default for audio devices, but user can override and select a different device. For camera 'history based device selection' is used */
            OVERRIDE_OS_DEFAULT_AUDIO_DEVICE_SELECTION,
        };
        public enum VidyoClientAecAgcMethod
        {
            /*! AEC and AGC used is Vidyo Internal */
            VIDYO_INTERNAL_AEC_AGC,
            /*! AEC and AGC used is OS provided if supported in OS. If not supported use nothing */
            OS_INTERNAL_AEC_AGC,
            /*! Use both OS provided if supported in OS and Vidyo internal AEC and AGC */
            VIDYO_AND_OS_AEC_AGC,
            /*! AEC and AGC used is OS provided if supported in OS. If not supported use Vidyo internal */
            OS_INTERNAL_OR_VIDYO_AEC_AGC,
        };

        public enum VidyoClientVideoPreferences
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
        };
        public enum VidyoClientActionType
        {
            /*! Action Type is FECC - Far End Camera Control */
            VIDYO_CLIENT_ACTION_TYPE_FECC = 0,
            /*! Action Type is pinning a remote participant */
            VIDYO_CLIENT_ACTION_TYPE_PIN = 100,
        };

        ///REQUESTS
        /* VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_IN
         * VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_OUT
          VIDYO_CLIENT_REQUEST_GET_MUTED_VIDEO  */

        /*! Level of Alarm
            - Sent as part of VIDYO_CLIENT_REQUEST_GET_ALARMS:
                + #VidyoClientRequestGetAlarms
         */
        public enum VidyoClientAlarmLevel
        {
            VIDYO_CLIENT_ALARM_LEVEL_GREEN = 0,				// No alarm
            VIDYO_CLIENT_ALARM_LEVEL_YELLOW,				// Warning
            VIDYO_CLIENT_ALARM_LEVEL_RED,					// Serious issue
            VIDYO_CLIENT_ALARM_LEVEL_MAX,
        };
        /*! Type of Alarm
    - Sent as part of VIDYO_CLIENT_REQUEST_GET_ALARMS:
        + #VidyoClientRequestGetAlarms
 */
        public enum VidyoClientAlarmType
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
        };


        [StructLayout(LayoutKind.Sequential)]
        public unsafe struct VidyoRect
        {
            public int xPos;    /*!< x position */
            public int yPos;    /*!< y position */
            public UInt32 width;  /*!< width */
            public UInt32 height; /*!< height */
        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct VidyoClientLogParams
        {
            IntPtr logLevelsAndCategories;
            public uint logSize;
            IntPtr pathToLogDir;
            IntPtr logBaseFileName;
            IntPtr PathToDumpDir;
            IntPtr pathToConfigDir;    /*!< path to config.xml file (used by Android */

            public void setLogLevelsAndCategories(string logLevelsAndCategoriesString)
            {
                logLevelsAndCategories = Marshal.StringToCoTaskMemAnsi(logLevelsAndCategoriesString);
            }

            public void setpathToLogDir(string pathToLogDirString)
            {
                pathToLogDir = Marshal.StringToCoTaskMemAnsi(pathToLogDirString);
            }
            public void setlogBaseFileName(string logBaseFileNameString)
            {
                logBaseFileName = Marshal.StringToCoTaskMemAnsi(logBaseFileNameString);
            }
            public void setPathToDumpDir(string PathToDumpDirString)
            {
                PathToDumpDir = Marshal.StringToCoTaskMemAnsi(PathToDumpDirString);
            }

            public void setpathToConfigDir(string pathToConfigDirString)
            {
                pathToConfigDir = Marshal.StringToCoTaskMemAnsi(pathToConfigDirString);
            }



        };
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct VidyoClientProfileParams
        {
            IntPtr PROGFILES_DIR;		/*!< path of system application directory */
            IntPtr CONFIG_KEY_PATH;	    /*!< path of configuration registry hive */
            IntPtr PRODUCT_NAME;		/*!< name of product */
            IntPtr PRODUCT_VERSION;     /*!< Product version tag or identification string - No more than 16 bytes long */
            IntPtr MYDOCS_DIR;			/*!< path of user my documents directory */
            IntPtr VIDYO_DIR;/*!< path of user application directory */
            IntPtr CERT_FILE_DIR; /*!< path of certificate file directory */
            IntPtr INSTALLED_APP_DIR;	/*!< path of installed application directory */
            public int portNumber;		/*!< port to listen for browser connections */
            IntPtr argvList;            /*!< command line argv list, NULL to ignore */
            public void setPROGFILES_DIR(string PROGFILES_DIRString)
            {
                PROGFILES_DIR = Marshal.StringToCoTaskMemAnsi(PROGFILES_DIRString);
            }

            public void setCONFIG_KEY_PATH(string CONFIG_KEY_PATHString)
            {
                CONFIG_KEY_PATH = Marshal.StringToCoTaskMemAnsi(CONFIG_KEY_PATHString);
            }

            public void setPRODUCT_NAME(string PRODUCT_NAMEString)
            {
                PRODUCT_NAME = Marshal.StringToCoTaskMemAnsi(PRODUCT_NAMEString);
            }

            public void setMYDOCS_DIR(string MYDOCS_DIRString)
            {
                MYDOCS_DIR = Marshal.StringToCoTaskMemAnsi(MYDOCS_DIRString);
            }

            public void setVIDYO_DIR(string VIDYO_DIRString)
            {
                VIDYO_DIR = Marshal.StringToCoTaskMemAnsi(VIDYO_DIRString);
            }

            public void setCERT_FILE_DIR(string CERT_FILE_DIRString)
            {
                CERT_FILE_DIR = Marshal.StringToCoTaskMemAnsi(CERT_FILE_DIRString);
            }

            public void setINSTALLED_APP_DIR(string INSTALLED_APP_DIRString)
            {
                INSTALLED_APP_DIR = Marshal.StringToCoTaskMemAnsi(INSTALLED_APP_DIRString);
            }

        };



        [Serializable]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        unsafe public struct VidyoClientInEventSignIn
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = SIGNIN_SERVERADDRESS_SIZE)]
            public string serverAddress;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = SIGNIN_SERVERPORT_SIZE)]
            public string serverPort;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = SIGNIN_USERNAME_SIZE)]
            public string userName;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = SIGNIN_PORTAL_ACCESS_KEY_SIZE)]
            public string portalAccessKey;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = SIGNIN_PORTALADDRESS_SIZE)]
            public string portalAddress;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = SIGNIN_PORTALVERSION_SIZE)]
            public string portalVersion;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VIDYO_MANAGER_ID_SIZE)]
            public string vmIdentity;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = ENDPOINT_LOCATION_TAG_SIZE)]
            public string locationTag;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_IPADDRESS_LEN)]
            public string clientExternalIPAddress;
            public VidyoClientProxyType proxyType;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = ((int)SIGNIN_VIDYO_PROXY_NUMBER * (int)(SIGNIN_VIDYO_PROXY_ADDRESS_SIZE)))] //SizeConst = SIGNIN_VIDYO_PROXY_ADDRESS_SIZE
            public string vidyoProxyAddress;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = ((int)SIGNIN_VIDYO_PROXY_NUMBER * (int)(SIGNIN_VIDYO_PROXY_PORT_SIZE)))] //SizeConst = SIGNIN_VIDYO_PROXY_PORT_SIZE
            public string vidyoProxyPort;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = ((int)SIGNIN_VIDYO_PROXY_NUMBER * (int)(SIGNIN_VIDYO_PROXY_ADDRESS_SIZE)))] //SizeConst = SIGNIN_VIDYO_PROXY_ADDRESS_SIZE
            public string reverseProxyAddress;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = ((int)SIGNIN_VIDYO_PROXY_NUMBER * (int)(SIGNIN_VIDYO_PROXY_PORT_SIZE)))] //SizeConst = SIGNIN_VIDYO_PROXY_PORT_SIZE
            public string reverseProxyPort;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_PASSPHRASE_SIZE)]
            public string passphrase;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_EXTERNAL_ACCESS_TOKEN_SIZE)]
            public string externalAccessToken;
            public uint numberProxies;
            public uint emcpSecured;
            public VidyoBool guestLogin;
            public VidyoBool showDialpad;
            public VidyoBool showStartmeeting;
            public uint guestId;
            public VidyoClientClientType clientType;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = SIGNIN_MAX_COOKIE_SIZE)]
            public string cookie;
        };

        //VidyoClientProxyType
        public enum VidyoClientProxyType
        {
            VIDYO_CLIENT_PROXY_NONE = 0,
            /*! Proxy type is Vidyo Proxy */
            VIDYO_CLIENT_VIDYO_PROXY,
            /*! The proxy type is reverse proxy */
            VIDYO_CLIENT_REVERSE_PROXY,
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestGetMuted
        {
            public VidyoBool isMuted;
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestEchoRecommendation
        {
            public uint speakerIndex;
            public uint micIndex;
            public VidyoBool echoDisabled;
        };


        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventSetFlag
        {
            VidyoBool willEnable;
        };

        /*  VIDYO_CLIENT_REQUEST_GET_CONFIGURATION,
            VIDYO_CLIENT_REQUEST_SET_CONFIGURATION,   ------> need details here
         */
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestConfiguration
        {
            unsafe fixed byte microphones[(int)MAX_DEVICE_NUMBER * DEVICE_NAME_SIZE];//read only
            unsafe fixed byte microphonePhyDeviceName[(int)MAX_DEVICE_NUMBER * DEVICE_NAME_SIZE];//read only
            unsafe fixed byte microphoneVoiceProcessingSupport[(int)MAX_DEVICE_NUMBER];

            public uint numberMicrophones;
            public uint currentMicrophone;

            unsafe fixed byte speakers[(int)MAX_DEVICE_NUMBER * DEVICE_NAME_SIZE];//read only
            unsafe fixed byte speakerPhyDeviceName[(int)MAX_DEVICE_NUMBER * DEVICE_NAME_SIZE];//read only
            public uint numberSpeakers;
            public uint currentSpeaker;


            unsafe fixed byte cameras[(int)MAX_DEVICE_NUMBER * DEVICE_NAME_SIZE];//read only
            public uint numberCameras;
            public uint currentCamera;

            public uint enableFeccEndpoint;
            public uint enableFeccController;

            unsafe fixed byte vidyoProxies[(int)SIGNIN_VIDYO_PROXY_NUMBER * (int)(SIGNIN_VIDYO_PROXY_ADDRESS_SIZE + SIGNIN_VIDYO_PROXY_PORT_SIZE + 1)];
            public uint numberVidyoProxies;
            public uint currentVidyoProxy;

            unsafe fixed byte userID[FIELD_SIZE];
            unsafe fixed byte password[FIELD_SIZE];
            unsafe fixed byte serverAddress[URI_LEN];
            unsafe fixed byte serverPort[SERVERPORT_SIZE];

            unsafe fixed byte vidyoProxyAddress[URI_LEN];
            unsafe fixed byte vidyoProxyPort[SERVERPORT_SIZE];
            unsafe fixed byte webProxyAddress[URI_LEN];
            unsafe fixed byte webProxyPort[SERVERPORT_SIZE];
            unsafe fixed byte webProxyUsername[FIELD_SIZE];
            unsafe fixed byte webProxyPassword[FIELD_SIZE];
            unsafe fixed byte webProxyIeAddress[URI_LEN];
            unsafe fixed byte webProxyIePort[SERVERPORT_SIZE];
            unsafe fixed byte portalAddress[FIELD_SIZE];
            unsafe fixed byte ringtoneDeviceName[FIELD_SIZE];
            unsafe fixed byte verifyCertPortalAcct[MAX_PORTAL_ADDRESS];
            unsafe fixed byte webProxyScriptUrl[URI_LEN];
            unsafe fixed byte webProxyIeScriptUrl[URI_LEN];

            public uint mediaLowPort;
            public uint mediaHighPort;
            public uint proxySettings;
            VidyoClientVideoPreferences videoPreferences;

            public uint enableLogging;
            public uint enableAutoAnswer;
            public uint enableForceProxy;
            public uint enableLogWindow;
            public uint enableEntryTone;
            public uint enableEchoDetection;
            public uint enableEchoCancellation;
            public uint enableFullScreenVideo;
            public uint showToolbarInFullScreenVideo;
            public uint enableAudioAGC;
            public uint enableAutoStart;
            public uint enableAutoLogIn;
            public uint enableShowConfParticipantName;
            public uint enableMuteMicrophoneOnJoin;
            public uint enableHideCameraOnJoin;
            public uint enableMuteSpeakerOnJoin;
            public uint enableEulaAgreed;
            public uint enableRendering;
            public uint enableBackgrounding;
            public uint enablePersonalRoomForSchedulingMeeting;
            public uint enableFullDisplaySharing;
            public uint selfViewLoopbackPolicy;
            public uint enableLowBackgroundTimeout;
            public uint allowLetterBoxVideoScaling;





            public unsafe string GetUserID()
            {
                byte[] bytUTF8 = new byte[FIELD_SIZE];
                fixed (VidyoClientRequestConfiguration* p = &this)
                    for (int i = 0; i < FIELD_SIZE; i++)
                    {
                        bytUTF8[i] = p->userID[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }

            public unsafe string GetPassword()
            {
                byte[] bytUTF8 = new byte[FIELD_SIZE];
                fixed (VidyoClientRequestConfiguration* p = &this)
                    for (int i = 0; i < FIELD_SIZE; i++)
                    {
                        bytUTF8[i] = p->password[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
            public unsafe string[] GetMicrophones()
            {
                string[] MicrophonesStr = new string[numberMicrophones];
                byte[] bytUTF8 = new byte[DEVICE_NAME_SIZE];
                fixed (VidyoClientRequestConfiguration* p = &this)
                    for (int j = 0; j < numberMicrophones; j++)
                    {
                        for (int i = 0; i < DEVICE_NAME_SIZE; i++)
                        {
                            bytUTF8[i] = p->microphones[i + j * Vidyo32.DEVICE_NAME_SIZE];
                        }
                        MicrophonesStr[j] = UnicodeStringFromUtf8Array(bytUTF8);
                    }
                return MicrophonesStr;
            }

            public unsafe string[] GetCameras()
            {
                string[] Camstr = new string[numberCameras];
                byte[] bytUTF8 = new byte[DEVICE_NAME_SIZE];
                fixed (VidyoClientRequestConfiguration* p = &this)
                    for (int j = 0; j < numberCameras; j++)
                    {
                        for (int i = 0; i < DEVICE_NAME_SIZE; i++)
                        {
                            bytUTF8[i] = p->cameras[i + j * Vidyo32.DEVICE_NAME_SIZE];
                        }
                        Camstr[j] = UnicodeStringFromUtf8Array(bytUTF8);
                    }
                return Camstr;
            }

            public unsafe string[] GetSpeakers()
            {
                string[] SpeakerStr = new string[numberSpeakers];
                byte[] bytUTF8 = new byte[DEVICE_NAME_SIZE];
                fixed (VidyoClientRequestConfiguration* p = &this)
                    for (int j = 0; j < numberSpeakers; j++)
                    {
                        for (int i = 0; i < DEVICE_NAME_SIZE; i++)
                        {
                            bytUTF8[i] = p->speakers[i + j * Vidyo32.DEVICE_NAME_SIZE];
                        }
                        SpeakerStr[j] = UnicodeStringFromUtf8Array(bytUTF8);
                    }
                return SpeakerStr;
            }



        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public class Participant
        {
            public String Name;
            public String URI;
            public Participant()
            {
                Name = ""; URI = "";
            }
            public Participant(String Nm, String Ur)
            {
                Name = Nm;
                URI = Ur;
            }
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public class ParticipantInfo
        {
            public String Name;
            public String URI;
            public uint bytesRcvd;
            public uint numFirsSent;
            public uint numNacksSent;
            public uint numDistinctNacksSent;
            public uint receivedFrameRate;
            public uint decodedFrameRate;
            public uint displayedFrameRate;
            public uint receivedPacketRate;
            public uint receivedBpsVideo;//TBD
            public uint receivedBpsAudio;//TBD
            public uint receivedWidth;
            public uint receivedHeight;
            public uint receivedBytesVideo;
            public uint receivedBytesAudio;
            public ParticipantInfo()
            {
                Name = ""; URI = "";



            }
            public ParticipantInfo(String Nm, String Ur, uint nfs, uint nns,
                uint ndns, uint rfr, uint dfr, uint disfr, uint rpr, uint rbpv, uint rbpa, uint rw, uint rh, uint rbyv, uint rbya)
            {
                Name = Nm;
                URI = Ur;
                numFirsSent = nfs;
                numNacksSent = nns;
                numDistinctNacksSent = ndns;
                receivedFrameRate = rfr;
                decodedFrameRate = dfr;
                displayedFrameRate = disfr;
                receivedPacketRate = rpr;
                receivedBpsVideo = rbpv;
                receivedBpsAudio = rbpa;
                receivedBytesVideo = rbyv;
                receivedBytesAudio = rbya;


            }
        }


        /* VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS
         */
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestParticipants
        {
            unsafe fixed byte Name[(int)MAX_PARTICIPANTS_NUM * FIELD_SIZE];
            unsafe fixed byte URI[(int)MAX_PARTICIPANTS_NUM * URI_LEN];

            uint numberParticipants;
            public Participant[] GetParticipants()
            {
                Participant[] ParticipantArr = new Participant[numberParticipants];
                byte[] bytUTF8 = new byte[Math.Max(FIELD_SIZE, URI_LEN)];
                fixed (VidyoClientRequestParticipants* p = &this)
                    for (int j = 0; j < numberParticipants; j++)
                    {
                        ParticipantArr[j] = new Participant();
                        for (int i = 0; i < FIELD_SIZE; i++)
                        {
                            bytUTF8[i] = p->Name[i + j * Vidyo32.FIELD_SIZE];
                        }
                        ParticipantArr[j].Name = UnicodeStringFromUtf8Array(bytUTF8);
                        for (int i = 0; i < URI_LEN; i++)
                        {
                            bytUTF8[i] = p->URI[i + j * Vidyo32.URI_LEN];
                        }
                        ParticipantArr[j].URI = UnicodeStringFromUtf8Array(bytUTF8);
                    }
                return ParticipantArr;
            }
        }

        /*  VIDYO_CLIENT_REQUEST_GET_CURRENT_USER
         */
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestCurrentUser
        {
            unsafe fixed byte CurrentUser[USERID_SIZE];
            unsafe fixed byte CurrentUserDisplay[USERID_SIZE];
            public unsafe string GetCurrentUser()
            {
                byte[] bytUTF8 = new byte[FIELD_SIZE];
                fixed (VidyoClientRequestCurrentUser* p = &this)
                    for (int i = 0; i < FIELD_SIZE; i++)
                    {
                        bytUTF8[i] = p->CurrentUser[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
        }

        /* VIDYO_CLIENT_REQUEST_GET_ALARMS
         */

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestGetAlarms
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)VidyoClientAlarmType.VIDYO_CLIENT_ALARM_TYPE_MAX)]
            public byte[] alarmTable;                      //whether each type of the alarm is set or not, VIDYO_TRUE if set

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)VidyoClientAlarmType.VIDYO_CLIENT_ALARM_TYPE_MAX)]
            public Int32[] alarmLevel; //level of each alarm if set  else VIDYO_CLIENT_ALARM_LEVEL_GREEN
        }





        public enum VidyoClientSessionDisplayContext
        {
            VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_CONF,      /* Session created as a conference
        													   - userID shows <conference> */
            VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_OUT_CALL,  /* Session created as outbound
        													   - userID shows <to> */
            VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_IN_CALL,   /* Session created as inbound
        													   - userID shows <from> */
            VIDYO_CLIENT_SESSION_DISPLAY_CONTEXT_IDLE		/* No current session */
        };

        /*  VIDYO_CLIENT_REQUEST_GET_CURRENT_SESSION_DISPLAY_INFO
         */
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestSessionDisplayInfo //VidyoClientRequestCurrentConference
        {
            VidyoClientSessionDisplayContext SessionDisplayContext;
            unsafe fixed byte SessionDisplayText[DISPLAY_CONFERENCE_SIZE];
            //TODO: implement GetSessionDisplayText
            /*
                        unsafe fixed byte CurrentConference[DISPLAY_CONFERENCE_SIZE];
                        public unsafe string GetCurrentConference()
                        {
                            byte[] bytUTF8 = new byte[DISPLAY_CONFERENCE_SIZE];
                            fixed (VidyoClientRequestCurrentConference* p = &this)
                            for (int i = 0; i < DISPLAY_CONFERENCE_SIZE; i++)
                            {
                                bytUTF8[i] = p->CurrentConference[i];
                            }
                            string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                            return strUnicode;
                        }
             */
        }

        /*VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS_LIMIT
         0 means "no limitation" */
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct VidyoClientRequestParticipantsLimit
        {
            public uint BandwidthLimit;
            public uint CpuLimit;
            public uint ManualLimit;
        };

        /*  VIDYO_CLIENT_REQUEST_GET_BANDWIDTH_INFO
         */
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct VidyoClientRequestBandwidthInfo
        {
            public uint AvailSendBwVideo;
            public uint AvailSendBwAudio;
            public uint AvailSendBwApplication;
            public uint AvailSendBwMax;
            public uint ActualSendBwVideo;
            public uint ActualSendBwAudio;
            public uint ActualSendBwApplication;
            public uint ActualSendBwMax;
            public uint AvailRecvBwVideo;
            public uint AvailRecvBwAudio;
            public uint AvailRecvBwApplication;
            public uint AvailRecvBwMax;
            public uint ActualRecvBwVideo;
            public uint ActualRecvBwAudio;
            public uint ActualRecvBwApplication;
            public uint ActualRecvBwMax;
        };

        /*VIDYO_CLIENT_REQUEST_GET_VIDEO_FRAME_RATE_INFO*/
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestFrameRateInfo
        {
            public uint captureFrameRate;
            public uint encodeFrameRate;
            public uint sendFrameRate;
        };

        /*VIDYO_CLIENT_REQUEST_GET_RATE_SHAPER_INFO*/
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestRateShaperInfo
        {
            public uint delayVideoPriorytyNormal;
            public uint numPacketsVideoPriorytyNormal;
            public uint numFramesVideoPriorytyNormal;
            public uint numDroppedVideoPriorytyNormal;
            public uint delayVideoPriorutyRetransmit;
            public uint numPacketsVideoPriorutyRetransmit;
            public uint numFramesVideoPriorutyRetransmit;
            public uint numDroppedVideoPriorutyRetransmit;
            public uint delayAppPriorityNormal;
            public uint numPacketsAppPriorityNormal;
            public uint numFramesAppPriorityNormal;
            public uint numDroppedAppPriorityNormal;
            public uint delayAppPriorityRetransmit;
            public uint numPacketsAppPriorityRetransmit;
            public uint numFramesAppPriorityRetransmit;
            public uint numDroppedAppPriorityRetransmit;
        };

        /*VIDYO_CLIENT_REQUEST_GET_INVITING_USER*/
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestInvitingUser
        {
            unsafe fixed byte InvitingUser[FIELD_SIZE];
            public unsafe string GetInvitingUser()
            {
                byte[] bytUTF8 = new byte[FIELD_SIZE];
                fixed (VidyoClientRequestInvitingUser* p = &this)
                    for (int i = 0; i < FIELD_SIZE; i++)
                    {
                        bytUTF8[i] = p->InvitingUser[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
        }

        public enum VidyoClientWindowShareRequestType
        {
            LIST_SHARING_WINDOWS = 0,
            CHANGE_SHARING_WINDOW,
            TOGGLE_SHARING_WINDOW,
            STOP_SHARING_WINDOW,
            UPDATE_DISPLAY_SHARING_WINDOW,
            ADD_SHARING_WINDOW,
        };
        /*  VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES
            VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARE*/



        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientWindowShares
        {
            unsafe fixed byte remoteAppUri[MAX_REMOTE_SHARE_APP * MAX_URI_LEN];
            unsafe fixed byte remoteAppName[MAX_REMOTE_SHARE_APP * MAX_URI_LEN];
            public uint numApp;
            public int currApp;
            public unsafe fixed byte eventUri[MAX_URI_LEN];
            public int newApp;


            public string[] GetShareUriList()
            {
                string[] ShareUriList = new string[numApp];
                byte[] bytUTF8 = new byte[MAX_URI_LEN];
                string empty = "";
                fixed (VidyoClientWindowShares* p = &this)
                    for (int j = 0; j < numApp; j++)
                    {
                        for (int i = 0; i < MAX_URI_LEN; i++)
                        {
                            bytUTF8[i] = p->remoteAppName[i + (j + 1) * Vidyo32.MAX_URI_LEN];
                        }
                        if (bytUTF8[0] != 0)
                            ShareUriList[j] = UnicodeStringFromUtf8Array(bytUTF8);
                        else
                            ShareUriList[j] = empty;
                    }


                return ShareUriList;
            }
        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestWindowShares
        {
            public VidyoClientWindowShareRequestType shareReqType;
            public VidyoClientWindowShares shareList;

        };

        [StructLayout(LayoutKind.Sequential)]
        unsafe public struct VidyoClientScreenInfo
        {
            public uint xDpi;
            public uint yDpi;
            public VidyoBool isPrimary;
        };




        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        unsafe public struct VidyoClientRequestGetWindowsAndDesktops
        {
            public uint numApplicationWindows;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_NUM_APP_WINDOWS)]
            public UriStringSize[] appWindowName;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_NUM_APP_WINDOWS)]
            public UriStringSize[] appWindowAppName;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_NUM_APP_WINDOWS)]
            public IntPtr[] appWindowId;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_NUM_APP_WINDOWS)]
            public VidyoRect[] appWindowRect;


            public uint numSystemDesktops;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_SHARE_DISPLAY_DEVICE)]
            public UriStringSize[] sysDesktopName;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_SHARE_DISPLAY_DEVICE)]
            public ShareId[] sysDesktopId;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_SHARE_DISPLAY_DEVICE)]
            public VidyoRect[] sysDesktopRect;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_SHARE_DISPLAY_DEVICE)]
            public VidyoRect[] sysDesktopWorkArea;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_SHARE_DISPLAY_DEVICE)]
            public VidyoClientScreenInfo[] sysDesktopInfo;

            public VidyoBool appSharesDisabled;

            /*************            
             * 
             *  This struct will allow marshalling to identify the size for each string in the array
             *  
             *************/
            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
            public struct UriStringSize
            {
                [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_URI_LEN)]
                public string _theStr;

                public static implicit operator string(UriStringSize aInStr)
                {
                    return aInStr._theStr;
                }

                public static implicit operator UriStringSize(string aInStr)
                {
                    // Note that longer strings would be silently truncated
                    //  if we didn't explicitly check this.
                    if (aInStr.Length >= MAX_URI_LEN)
                        throw new Exception("UriStringSize: <copy operator> - String too large for field: " + aInStr);

                    return new UriStringSize { _theStr = aInStr };
                }
            }

            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
            public struct ShareId
            {
                [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VIDYO_CLIENT_SCREEN_ID_SIZE)]
                public string _theStr;

                public static implicit operator string(ShareId aInStr)
                {
                    return aInStr._theStr;
                }

                public static implicit operator ShareId(string aInStr)
                {
                    // Note that longer strings would be silently truncated
                    //  if we didn't explicitly check this.
                    if (aInStr.Length >= VIDYO_CLIENT_SCREEN_ID_SIZE)
                        throw new Exception("ShareId: <copy operator> - String too large for field: " + aInStr);

                    return new ShareId { _theStr = aInStr };
                }
            }

            public void Init()
            {
                this.appWindowName = new UriStringSize[MAX_NUM_APP_WINDOWS];
                this.appWindowAppName = new UriStringSize[MAX_NUM_APP_WINDOWS];
                this.appWindowId = new IntPtr[MAX_NUM_APP_WINDOWS];
                this.appWindowRect = new VidyoRect[MAX_NUM_APP_WINDOWS];
                this.sysDesktopName = new UriStringSize[MAX_SHARE_DISPLAY_DEVICE];
                this.sysDesktopId = new ShareId[MAX_SHARE_DISPLAY_DEVICE];
                this.sysDesktopRect = new VidyoRect[MAX_SHARE_DISPLAY_DEVICE];
                this.sysDesktopWorkArea = new VidyoRect[MAX_SHARE_DISPLAY_DEVICE];
                this.sysDesktopInfo = new VidyoClientScreenInfo[MAX_SHARE_DISPLAY_DEVICE];

            }
        };
        // VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_INFO

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestParticipantInfo
        {
            unsafe fixed byte Name[(int)MAX_PARTICIPANTS_NUM * FIELD_SIZE];
            unsafe fixed byte URI[(int)MAX_PARTICIPANTS_NUM * URI_LEN];
            public unsafe fixed uint bytesRcvd[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint numFirsSent[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint numNacksSent[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint numDistinctNacksSent[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint receivedFrameRate[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint decodedFrameRate[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint displayedFrameRate[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint receivedPacketRate[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint receivedBpsVideo[MAX_PARTICIPANTS_NUM];//TBD
            public unsafe fixed uint receivedBpsAudio[MAX_PARTICIPANTS_NUM];//TBD
            public unsafe fixed uint receivedWidth[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint receivedHeight[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint receivedBytesVideo[MAX_PARTICIPANTS_NUM];
            public unsafe fixed uint receivedBytesAudio[MAX_PARTICIPANTS_NUM];

            public uint numberParticipants;
            public Participant[] GetParticipantInfo()
            {
                Participant[] ParticipantArr = new Participant[numberParticipants];
                byte[] bytUTF8 = new byte[Math.Max(FIELD_SIZE, URI_LEN)];
                fixed (VidyoClientRequestParticipantInfo* p = &this)
                    for (int j = 0; j < numberParticipants; j++)
                    {
                        ParticipantArr[j] = new Participant();
                        for (int i = 0; i < FIELD_SIZE; i++)
                        {
                            bytUTF8[i] = p->Name[i + j * Vidyo32.FIELD_SIZE];
                        }
                        ParticipantArr[j].Name = UnicodeStringFromUtf8Array(bytUTF8);
                        for (int i = 0; i < URI_LEN; i++)
                        {
                            bytUTF8[i] = p->URI[i + j * Vidyo32.URI_LEN];
                        }
                        ParticipantArr[j].URI = UnicodeStringFromUtf8Array(bytUTF8);
                    }
                return ParticipantArr;
            }

        };
        //Marina July 17

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientParticipantStatistics
        {
            unsafe fixed byte uri[MAX_URI_LEN];
            unsafe fixed byte name[USERID_SIZE];
            public VidyoRect videoResolution;
            public uint videoKBitsPerSecRecv;
            public uint audioKBitsPerSecRecv;
            public uint firs;
            public uint nacks;
            public uint videoFrameRate;
            public uint videoDecodedFrameRate;
            public uint videoDisplayedFrameRate;
            public unsafe string Geturi()
            {
                byte[] bytUTF8 = new byte[MAX_URI_LEN];
                fixed (VidyoClientParticipantStatistics* p = &this)
                    for (int i = 0; i < MAX_URI_LEN; i++)
                    {
                        bytUTF8[i] = p->uri[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }

            public unsafe string Getname()
            {
                byte[] bytUTF8 = new byte[USERID_SIZE];
                fixed (VidyoClientParticipantStatistics* p = &this)
                    for (int i = 0; i < USERID_SIZE; i++)
                    {
                        bytUTF8[i] = p->name[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
        };

        /* 
      VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT
      Used for retrieving statistics of conference participant */

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientRequestParticipantStatisticsAt
        {
            public int index;
            public VidyoBool result;
            public VidyoClientParticipantStatistics statistics;
        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct VidyoClientRequestGetParticipantStatisticsList
        {
            public int startIndex;
            public int numParticipants;
            public VidyoClientParticipantStatistics statstics;
        }

        // VIDYO_CLIENT_REQUEST_GET_EID
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestGetEID
        {
            unsafe fixed byte EID[MAX_EID_SIZE];
            public unsafe string GetEID()
            {
                byte[] bytUTF8 = new byte[FIELD_SIZE];
                fixed (VidyoClientRequestGetEID* p = &this)
                    for (int i = 0; i < FIELD_SIZE; i++)
                    {
                        bytUTF8[i] = p->EID[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
        };

        // VIDYO_CLIENT_REQUEST_GET_MEDIA_INFO
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestMediaInfo
        {
            public uint numIFrames;
            public uint numFirs;
            public uint numNacks;
            public uint mediaRTT;
        };

        // VIDYO_CLIENT_REQUEST_SNAP_RESIZE
        public enum VidyoClientResizingMethod
        {
            VIDYO_CLIENT_RESIZING_METHOD_HORIZONTAL,
            VIDYO_CLIENT_RESIZING_METHOD_VERTICAL,
            VIDYO_CLIENT_RESIZING_METHOD_DIAGONAL,
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestSnapResize
        {
            public uint width;
            public uint height;
            public uint curWidth;
            public uint curHeight;
            public uint minWidth;
            public uint minHeight;
            public uint maxWidth;
            public uint maxHeight;
            public VidyoClientResizingMethod sizingmethod;
        };

        // VidyoClientPreviewMode
        public enum VidyoClientPreviewMode
        {
            VIDYO_CLIENT_PREVIEW_MODE_NONE = 0,
            VIDYO_CLIENT_PREVIEW_MODE_PIP,
            VIDYO_CLIENT_PREVIEW_MODE_DOCK,
            VIDYO_CLIENT_PREVIEW_MODE_OTHER = 4 // room systems only
        };

        public enum VidyoClientParticipantVideoMode
        {
            VIDYO_CLIENT_VIDEO_MODE_DOCK = 0,
            VIDYO_CLIENT_VIDEO_MODE_PINHIGH,
            VIDYO_CLIENT_VIDEO_MODE_PINLOW
        };

        public enum VidyoClientRoomLinkState
        {
            VIDYO_CLIENT_ROOM_LINK_STATE_INIT = 0,
            VIDYO_CLIENT_ROOM_LINK_STATE_CONNECTED,
            VIDYO_CLIENT_ROOM_LINK_STATE_LOGGED,
            VIDYO_CLIENT_ROOM_LINK_STATE_LINKED,
            VIDYO_CLIENT_ROOM_LINK_STATE_GOT_ENTITY,
            VIDYO_CLIENT_ROOM_LINK_STATE_CANCELLED,
            VIDYO_CLIENT_ROOM_LINK_STATE_JOINED,
        };

        public enum VidyoClientSignInEnum
        {
            SIGNIN_INTERNAL = 1,	/*!< The source of the sign-in event 
							       is the VidyoClient library */
            SIGNIN_EXTERNAL,		/*!< The source of the sign-in event
							       is external e.g. browser */
            SIGNIN_APPLICATION		/*!< The source of the sign-in event
							       is the application using VidyoClient */
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientRequestGetEndpointStatus
        {
            public VidyoClientEndpointStatus endPointStatus;
        };


        public enum VidyoClientEndpointStatus
        {
            VIDYO_CLIENT_ENDPOINT_STATUS_INACTIVE,  /*!< Client not registered to server */

            VIDYO_CLIENT_ENDPOINT_STATUS_REGISTERED,/*!< Registered to server, but not bound to a user */

            VIDYO_CLIENT_ENDPOINT_STATUS_ACTIVE    /*!< Client is registered and bound to a user - ready for use */

        };

        public enum VidyoClientClientType
        {
            VIDYO_CLIENT_CLIENTTYPE_M,
            VIDYO_CLIENT_CLIENTTYPE_V,
            VIDYO_CLIENT_CLIENTTYPE_W,
            VIDYO_CLIENT_CLIENTTYPE_R,
            VIDYO_CLIENT_CLIENTTYPE_L,
            VIDYO_CLIENT_CLIENTTYPE_S,
            VIDYO_CLIENT_CLIENTTYPE_U,
            VIDYO_CLIENT_CLIENTTYPE_T,
            VIDYO_CLIENT_CLIENTTYPE_X,
            VIDYO_CLIENT_CLIENTTYPE_A,
            VIDYO_CLIENT_CLIENTTYPE_I,
            VIDYO_CLIENT_CLIENTTYPE_UNKNOWN
        }


        public enum VidyoClientPortalServiceTypeRequest
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
        };
        public enum VidyoClientError
        {

            VIDYO_CLIENT_ERROR_NONE = 0,

            /*!< curl/TCP errors 1-88 */
            VIDYO_CLIENT_ERROR_TCP_UNSUPPORTED_PROTOCOL = 1,	/*!< CURLE_UNSUPPORTED_PROTOCOL,    */
            VIDYO_CLIENT_ERROR_TCP_FAILED_INIT = 2,	/*!< CURLE_FAILED_INIT,             */
            VIDYO_CLIENT_ERROR_TCP_URL_MALFORMAT = 3,	/*!< CURLE_URL_MALFORMAT,           */
            VIDYO_CLIENT_ERROR_TCP_NOT_BUILT_IN = 4,	/*!< CURLE_NOT_BUILT_IN,  [was obsoleted in August 2007 for 7.17.0, reused in April 2011 for 7.21.5] */
            VIDYO_CLIENT_ERROR_TCP_COULD_NOT_RESOLVE_PROXY = 5,	/*!< CURLE_COULDNT_RESOLVE_PROXY,    */
            VIDYO_CLIENT_ERROR_TCP_COULD_NOT_RESOLVE_HOST = 6,	/*!< CURLE_COULDNT_RESOLVE_HOST,     */
            VIDYO_CLIENT_ERROR_TCP_COULD_NOT_CONNECT = 7,	/*!< CURLE_COULDNT_CONNECT,         */
            VIDYO_CLIENT_ERROR_TCP_FTP_WEIRD_SERVER_REPLY = 8,	/*!< CURLE_FTP_WEIRD_SERVER_REPLY,   */
            VIDYO_CLIENT_ERROR_TCP_REMOTE_ACCESS_DENIED = 9,	/*!< CURLE_REMOTE_ACCESS_DENIED, a service was denied by the server due to lack of access - when login fails this is not returned. */
            VIDYO_CLIENT_ERROR_TCP_PARTIAL_FILE = 18,	/*!< CURLE_PARTIAL_FILE,             */
            VIDYO_CLIENT_ERROR_TCP_HTTP_RETURNED_ERROR = 22,	/*!< CURLE_HTTP_RETURNED_ERROR,     */
            VIDYO_CLIENT_ERROR_TCP_OUT_OF_MEMORY = 27,	/*!< CURLE_OUT_OF_MEMORY,            */
            VIDYO_CLIENT_ERROR_TCP_OPERATION_TIMED_OUT = 28,	/*!< CURLE_OPERATION_TIMEDOUT,       - the timeout time was reached */
            VIDYO_CLIENT_ERROR_TCP_HTTP_POST_ERROR = 34,	/*!< CURLE_HTTP_POST_ERROR,          */
            VIDYO_CLIENT_ERROR_TCP_SSL_CONNECT_ERROR = 35,	/*!< CURLE_SSL_CONNECT_ERROR,       - wrong when connecting with SSL */
            VIDYO_CLIENT_ERROR_TCP_FUNCTION_NOT_FOUND = 41,	/*!< CURLE_FUNCTION_NOT_FOUND,      */
            VIDYO_CLIENT_ERROR_TCP_ABORTED_BY_CALLBACK = 42,	/*!< CURLE_ABORTED_BY_CALLBACK,     */
            VIDYO_CLIENT_ERROR_TCP_BAD_FUNCTION_ARGUMENT = 43,	/*!< CURLE_BAD_FUNCTION_ARGUMENT,    */
            VIDYO_CLIENT_ERROR_TCP_INTERFACE_FAILED = 45,	/*!< CURLE_INTERFACE_FAILED,        45 - CURLOPT_INTERFACE failed */
            VIDYO_CLIENT_ERROR_TCP_TOO_MANY_REDIRECTS = 47,	/*!< CURLE_TOO_MANY_REDIRECTS ,    - catch endless re-direct loops */
            VIDYO_CLIENT_ERROR_TCP_UNKNOWN_OPTION = 48,	/*!< CURLE_UNKNOWN_OPTION,          - User specified an unknown option */
            VIDYO_CLIENT_ERROR_TCP_PEER_FAILED_VERIFICATION = 51,	/*!< CURLE_PEER_FAILED_VERIFICATION,  - peer's certificate or fingerprint wasn't verified fine */
            VIDYO_CLIENT_ERROR_TCP_GOT_NOTHING = 52,	/*!< CURLE_GOT_NOTHING,              - when this is a specific error */
            VIDYO_CLIENT_ERROR_TCP_SSL_ENGINE_NOT_FOUND = 53,	/*!< CURLE_SSL_ENGINE_NOTFOUND,    - SSL crypto engine not found */
            VIDYO_CLIENT_ERROR_TCP_SSL_ENGINE_SET_FAILED = 54,	/*!< CURLE_SSL_ENGINE_SETFAILED,   - can not set SSL crypto engine as default */
            VIDYO_CLIENT_ERROR_TCP_SEND_ERROR = 55,	/*!< CURLE_SEND_ERROR,              - failed sending network data */
            VIDYO_CLIENT_ERROR_TCP_RECV_ERROR = 56,	/*!< CURLE_RECV_ERROR,             - failure in receiving network data */
            VIDYO_CLIENT_ERROR_TCP_SSL_CERT_PROBLEM = 58,	/*!< CURLE_SSL_CERTPROBLEM,       - problem with the local certificate */
            VIDYO_CLIENT_ERROR_TCP_SSL_CIPHER = 59,	/*!< CURLE_SSL_CIPHER,             - couldn't use specified cipher */
            VIDYO_CLIENT_ERROR_TCP_SSL_CACERT = 60,	/*!< CURLE_SSL_CACERT,            - problem with the CA cert (path?) */
            VIDYO_CLIENT_ERROR_TCP_BAD_CONTENT_ENCODING = 61,	/*!< CURLE_BAD_CONTENT_ENCODING,    - Unrecognized/bad encoding */
            VIDYO_CLIENT_ERROR_TCP_FILE_SIZE_EXCEEDED = 63,	/*!< CURLE_FILESIZE_EXCEEDED,     - Maximum file size exceeded */
            VIDYO_CLIENT_ERROR_TCP_SEND_FAIL_REWIND = 65,	/*!< CURLE_SEND_FAIL_REWIND,      - Sending the data requires a rewind that failed */
            VIDYO_CLIENT_ERROR_TCP_SSL_ENGINE_INIT_FAILED = 66,	/*!< CURLE_SSL_ENGINE_INITFAILED,  - failed to initialise ENGINE */
            VIDYO_CLIENT_ERROR_TCP_SSL_SHUTDOWN_FAILED = 80,	/*!< CURLE_SSL_SHUTDOWN_FAILED,    - Failed to shut down the SSL connection */
            VIDYO_CLIENT_ERROR_TCP_AGAIN = 81,	/*!< CURLE_AGAIN,                 - socket is not ready for send/recv, wait till it's ready and try again (Added in 7.18.2) */
            VIDYO_CLIENT_ERROR_TCP_SSL_ISSUER_ERROR = 83,	/*!< CURLE_SSL_ISSUER_ERROR,       - Issuer check failed.  (Added in 7.19.0) */
            VIDYO_CLIENT_ERROR_TCP_CHUNK_FAILED = 88,	/*!< CURLE_CHUNK_FAILED,            - chunk callback reported error */

            /*!< http errors */
            VIDYO_CLIENT_ERROR_HTTP_200_OK = 200,
            VIDYO_CLIENT_ERROR_HTTP_301_REDIRECT = 301,
            VIDYO_CLIENT_ERROR_HTTP_302_REDIRECT = 302,
            VIDYO_CLIENT_ERROR_HTTP_401_UNAUTHORIZED = 401,
            VIDYO_CLIENT_ERROR_HTTP_404_NOT_IMPLEMENTED = 404,
            VIDYO_CLIENT_ERROR_HTTP_407_PROXY_AUTHENTICATION_REQUIRED = 407,
            VIDYO_CLIENT_ERROR_HTTP_408_TIMED_OUT = 408,
            VIDYO_CLIENT_ERROR_HTTP_500_SERVER_ERROR = 500,
            VIDYO_CLIENT_ERROR_HTTP_501_NOT_IMPLEMENTED = 501,

            /*!< SOAP faults/results */
            VIDYO_CLIENT_ERROR_SOAP_SUCCESS = 1000,		/*!< Result is success */
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
            VIDYO_CLIENT_ERROR_INTERNAL_REQUEST = 2000,
            VIDYO_CLIENT_ERROR_INTERNAL_RESPONSE,
            VIDYO_CLIENT_ERROR_INTERNAL_COULD_NOT_LINK,
            VIDYO_CLIENT_ERROR_INTERNAL_LOGIN_CANCELED,
            VIDYO_CLIENT_ERROR_INTERNAL_LOGIN_OLD_SERVER,
            VIDYO_CLIENT_ERROR_INTERNAL_CURL_INIT,
            VIDYO_CLIENT_ERROR_INTERNAL_NO_PORTAL_ADDRESS,
            VIDYO_CLIENT_ERROR_INTERNAL_WRONG_STATE,

            /*!< USER_MESSAGES will be here	 */

            VIDYO_CLIENT_ERROR_UNKNOWN = 0xFFFF,
        };


        /////////////////////

        /********************************************************************/
        /* Message types for event VIDYO_CLIENT_OUT_EVENT_USER_MESSAGE from */
        /* Vidyo Client Library to GUI                                      */
        /********************************************************************/
        public enum VidyoClientUserMessageType
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
            VIDYO_CLIENT_USER_MESSAGE_TYPE_DISCONNECTED_FROM_CONFERENCE,
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

        };

        ///////////////////////////// OUT_EVENTs

        // VIDYO_CLIENT_OUT_EVENT_SIGN_IN
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientOutEventSignIn
        {
            public uint activeEid;
            public VidyoBool guestLogin;
            public VidyoBool showDialpad;
            public VidyoBool showStartmeeting;
            VidyoClientSignInEnum signinType;
            VidyoBool signinSecured;
        };

        //VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE

        [Serializable]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        unsafe public struct VidyoClientOutEventPortalService
        {
            public VidyoClientOutEventPortalServiceDirectCall directCall;

        };

        public struct VidyoClientOutEventPortalServiceDirectCall
        {
            public VidyoClientPortalServiceTypeRequest typeRequest;

            public VidyoClientError error;

            public uint httpStatusCode;
            /*! Request identification. This identification provided by application in VIDYO_CLIENT_IN_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS */
            public uint requestId;
        } ;

        // VIDYO_CLIENT_OUT_EVENT_lOGIN_IN
        [Serializable]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct VidyoClientOutEventLogIn
        {

            public uint error;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = URI_LEN)]
            public string portalUri;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = USERID_SIZE)]
            public string userName;
        };
        /*  
        VidyoUint error
        VidyoUint vmConnectionPath
        VidyoBool OutOfLicenses
         * 
         * public VidyoBool isMuted;
                    public uint errorCode;
        */

        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientOutEventLicense
        {
            public uint error;
            public uint vmConnectionPath;
            public VidyoBool OutOfLicenses;
        };

        // VIDYO_CLIENT_OUT_EVENT_USER_MESSAGE
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientOutEventUserMessage
        {
            public VidyoClientUserMessageType messageType;
            public unsafe fixed uint messageCode[NUM_USER_MESSAGE_CODES];
            public unsafe fixed char messageString[MAX_USER_MESSAGE_STRING_SIZE];
        };

        // VIDYO_CLIENT_OUT_EVENT_ADD_SHARE
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct VidyoClientOutEventAddShare
        {
            unsafe fixed byte URI[URI_LEN];
            public unsafe string GetURI()
            {
                byte[] bytUTF8 = new byte[URI_LEN];
                fixed (VidyoClientOutEventAddShare* p = &this)
                    for (int i = 0; i < URI_LEN; i++)
                    {
                        bytUTF8[i] = p->URI[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
        };

        // VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct VidyoClientOutEventRemoveShare
        {
            unsafe fixed byte URI[URI_LEN];
            public unsafe string GetURI()
            {
                byte[] bytUTF8 = new byte[URI_LEN];
                fixed (VidyoClientOutEventRemoveShare* p = &this)
                    for (int i = 0; i < URI_LEN; i++)
                    {
                        bytUTF8[i] = p->URI[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
        };

        // VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientOutEventParticipantsLimit
        {
            public uint BandwidthLimit;
            public uint CpuLimit;
        };

        // VIDYO_CLIENT_OUT_EVENT_ROOM_LINK 
        [Serializable]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct VidyoClientOutEventRoomLink
        {
            public uint error;
            public VidyoClientRoomLinkState state;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = URI_LEN)]
            public string serverUri;
        };

        //  VIDYO_CLIENT_OUT_EVENT_RESIZE
        //    call when number of participant (or shared app) changes  
        //    and logic choses different layout
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientOutEventResize
        {
            public uint width;
            public uint height;
        };
        /* VIDYO_CLIENT_OUT_EVENT_RINGING:
           VIDYO_CLIENT_OUT_EVENT_CALLING:
           VIDYO_CLIENT_OUT_EVENT_JOINING:
           VIDYO_CLIENT_OUT_EVENT_RETRYING:
           Display dialog box with progress bar for pending operation */
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct VidyoClientOutEventStartProgress
        {
            public uint numProgressSteps;
            unsafe fixed byte Caption[DISPLAY_CONFERENCE_SIZE];
            public unsafe string GetCaption()
            {
                byte[] bytUTF8 = new byte[DISPLAY_CONFERENCE_SIZE];
                fixed (VidyoClientOutEventStartProgress* p = &this)
                    for (int i = 0; i < DISPLAY_CONFERENCE_SIZE; i++)
                    {
                        bytUTF8[i] = p->Caption[i];
                    }
                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                return strUnicode;
            }
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientOutEventMuted
        {
            public byte isMuted;
            public uint errorCode;
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientOutEventCallState
        {
            public VidyoClientCallState callState;
        }

        public enum VidyoClientCallState
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
        }

        // VidyoClientOutEventParticipantsChanged 
        // VidyoClientOutEventIncomingCall
        // VidyoClientOutEventPreview
        // VidyoClientOutEventKeyboard
        // VidyoClientOutEventMouse
        // VidyoClientOutEventTouch
        // VidyoClientOutEventFeccListUpdated
        // VidyoClientOutEventControlCamera
        // VidyoClientOutEventSetParticipantVideoModeDone
        // VidyoClientOutEventConferenceInfoUpdate
        // VidyoClientOutEventMediaControl
        // VidyoClientOutEventLicense
        // VidyoClientOutEventLinked
        // VidyoClientOutEventSignedOut
        // VidyoClientOutEventEnabled
        // VidyoClientOutEventGuestLink
        // VidyoClientOutEventGroupChat
        // VidyoClientOutEventPrivateChat

        ////////////////////////////////// IN_EVENTs

        /* VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN:
        VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_OUT:
        VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO:
        Change mute state of audio/video input/output device */


        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventMute
        {
            public VidyoBool isMuted;
        };

        //  VIDYO_CLIENT_IN_EVENT_PREVIEW
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventPreview
        {
            public VidyoClientPreviewMode PreviewMode;
            public VidyoBool primaryDisplay; // Only applies to Room system mode
        };

        // VIDYO_CLIENT_IN_EVENT_SET_PARTICIPANT_VIDEO_MODE
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventSetParticipantVideoMode
        {
            public string URI;
            public VidyoClientParticipantVideoMode videoMode;
        };

        // VIDYO_CLIENT_IN_EVENT_RESIZE
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventResize
        {
            public uint x;
            public uint y;
            public uint width;
            public uint height;
        };

        // VIDYO_CLIENT_IN_EVENT_LOGIN
        [Serializable]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        unsafe public struct VidyoClientInEventLogin
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = URI_LEN)]
            public string portalUri;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = USERID_SIZE)]
            public string userName;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = PASSWORD_SIZE)]
            public string userPass;

            public VidyoClientClientType clientType; // PHIL: added param in 3.3.1.4
        };

        //[StructLayout(LayoutKind.Explicit)]
        //unsafe public struct VidyoClientInEventPortalService
        //{
        //    // The actual portal service structures.
        //    [FieldOffset(0)] VidyoClientPortalServiceMandatory     mandatory;  // never used
        //    [FieldOffset(0)] VidyoClientPortalServiceDirectCall    directCall; // direct call
        //    [FieldOffset(0)] VidyoClientPortalServiceSearchRequest search;     // search portal
        //}

        [Serializable]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        unsafe public struct VidyoClientInEventPortalService
        {
            public VidyoClientPortalServiceDirectCall directCall;
        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        unsafe public struct VidyoClientPortalServiceDirectCall
        {
            public uint typeRequest;
            public uint requestId;
            public VidyoClientPortalServiceEntityType entityType;
            public unsafe fixed byte entityID[MAX_EID_SIZE];
            public unsafe fixed byte legacyID[MAX_EID_SIZE];
            public byte muteCamera;
            public byte muteMicrophone;
            public byte muteSpeaker;


            /* public unsafe string GetEntityID()
             {
                 byte[] bytUTF8 = new byte[MAX_EID_SIZE];
                 fixed (VidyoClientPortalServiceDirectCall* p = &this)
                     for (int i = 0; i < MAX_EID_SIZE; i++)
                     {
                         bytUTF8[i] = p->entityID[i];
                     }
                 string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                 return strUnicode;
             }
             public unsafe string GetLegacyID()
             {
                 byte[] bytUTF8 = new byte[MAX_EID_SIZE];
                 fixed (VidyoClientPortalServiceDirectCall* p = &this)
                     for (int i = 0; i < MAX_EID_SIZE; i++)
                     {
                         bytUTF8[i] = p->legacyID[i];
                     }
                 string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                 return strUnicode;
             } */
        };

        public enum VidyoClientPortalServiceEntityType
        {
            /*! Member */
            VIDYO_CLIENT_ENTITY_TYPE_MEMBER = 1,
            /*! Room */
            VIDYO_CLIENT_ENTITY_TYPE_ROOM,
            /*! Legacy */
            VIDYO_CLIENT_ENTITY_TYPE_LEGACY,
            /*! InterPortal */
            VIDYO_CLIENT_ENTITY_TYPE_IPC_ROOM,
            // Scheduled rooms
            VIDYO_CLIENT_ENTITY_TYPE_SCHEDULED,
            /*! Any */
            VIDYO_CLIENT_ENTITY_TYPE_ANY,
        };

        public enum VidyoClientContentsShareType
        {
            VIDYO_CLIENT_CONTENTS_SHARE_TYPE_APPLICATION_WINDOW = 1,

            VIDYO_CLIENT_CONTENTS_SHARE_TYPE_DESKTOP_WINDOW,
        };

        // VIDYO_CLIENT_IN_EVENT_ROOM_LINK
        [Serializable]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        unsafe public struct VidyoClientInEventRoomLink
        {

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = URI_LEN)]
            public string portalUri;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = ROOMKEY_SIZE)]
            public string roomKey;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = USERID_SIZE)]
            public string displayName;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = PIN_SIZE)]
            public string pin;

            public VidyoClientClientType clientType;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VIDYO_CLIENT_REFERENCE_NUMBER_LEN)]
            public string referenceNumber;

            public VidyoBool muteCamera;

            public VidyoBool muteMicrophone;

            public VidyoBool muteSpeaker;
        };

        // VIDYO_CLIENT_IN_EVENT_SHARE:
        // Share local application window in conference
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventShare
        {
            // public VidyoWindowCapturerWindowId window;
            public VidyoClientContentsShareType shareType;
            public IntPtr window;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VIDYO_CLIENT_SCREEN_ID_SIZE)]
            public string desktopId;
            public VidyoRect windowSize; // c# / NOTE: not yet support
        };
		
		
		public enum VidyoClientPrecallDeviceTestAction
        {
           /*! Start testing the device */
			VIDYO_CLIENT_DEVICE_TEST_START=1,
			/*! Stop testing the device */
			VIDYO_CLIENT_DEVICE_TEST_STOP,
        };
		
		// VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_CAMERA:
        // Used to test self-view using selected camera when not joined in a call or conference (pre-call self-view).
		//This is used to start or stop self-view.
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventPrecallTestCamera
        {
			public VidyoClientPrecallDeviceTestAction action;
        };
		
		// VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_MICROPHONE:
        // Used to control selected microphone when not joined in a call or conference (pre-call microphone test).
		//This is used to start or stop microphone.
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventPrecallTestMicrophone
        {
            public VidyoClientPrecallDeviceTestAction action;
        };
		
		


        // Code for sharing windows locally
        public const int SW_RESTORE = 9;

        [DllImport("user32.dll")]
        public static extern bool IsIconic(IntPtr handle);

        [DllImport("user32.dll")]
        public static extern bool ShowWindow(IntPtr handle, int nCmdShow);

        [DllImport("user32.dll")]
        public static extern int SetForegroundWindow(IntPtr handle);

        // end of sharing feature

        // VIDYO_CLIENT_IN_EVENT_UNSHARE:
        // Share local application window in conference
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventUnShare
        {
            //empty structure
        };

        // VIDYO_CLIENT_IN_EVENT_LAYOUT
        //    Change layout 
        //    0 - equal
        //    1 - one big
        [StructLayout(LayoutKind.Sequential)]
        public struct VidyoClientInEventLayout
        {
            public uint layout_num;
        };
        //Marina 

        /*	
                        [StructLayout(LayoutKind.Sequential)]
                        public struct VidyoClientRequestFeccList 
                        {
                           unsafe fixed byte URI[(int)MAX_PARTICIPANTS_NUM * URI_LEN];
                           public VidyoBool privacyMode [(int)MAX_PARTICIPANTS_NUM];
                           uint numberParticipants; 
          
          
          
        
                              //unsafe fixed byte Name[(int)MAX_PARTICIPANTS_NUM * FIELD_SIZE];
                    
                            //unsafe fixed byte URI[URI_LEN];
                           // public unsafe string GetURI()
                            {
                                byte[] bytUTF8 = new byte[URI_LEN];
                                fixed (VidyoClientOutEventFeccList* p = &this)
                                    for (int i = 0; i < URI_LEN; i++)
                                    {
                                        bytUTF8[i] = p->URI[i];
                                    }
                                string strUnicode = UnicodeStringFromUtf8Array(bytUTF8);
                                return strUnicode;
                            }
                        } ; */



        #endregion

        #region Delegate (Callback) Definition

        public delegate void VidyoClientOutEventCallback(
                                VidyoClientOutEvent actionType,
                                IntPtr param,
                                uint paramSize,
                                IntPtr data);

        #endregion

        #region Import functions from VidyoClientDll.dll

        //[UnmanagedFunctionPointerAttribute(CallingConvention.Cdecl)]
        //[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall)]
        // StdCall is the default calling convention
        [DllImport("VidyoClientDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern byte VidyoClientInitialize(
        VidyoClientOutEventCallback eventCallback,
        IntPtr data,
        IntPtr logParams);

        [DllImport("VidyoClientDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern byte VidyoClientStart(
            VidyoClientOutEventCallback eventCallback,
            IntPtr data,
            IntPtr logParams,
            IntPtr videoWindowHandle,
            IntPtr videoRect,
            IntPtr appStringsInfo,
            IntPtr profileParams,
            bool reserved);

        [DllImport("VidyoClientDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void VidyoClientUninitialize();


        [DllImport("VidyoClientDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern byte VidyoClientStop();

        //  [DllImport("VidyoClientDll.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        //  public void VidyoClientGetVersion(char* output, int size);

        [DllImport("VidyoClientDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern byte VidyoClientSendEvent(
            VidyoClientInEvent e,
            IntPtr param,
            int paramSize);

        [DllImport("VidyoClientDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern uint VidyoClientSendRequest(
            VidyoClientRequest request,
            IntPtr parame,
            int paramSize);
        //       [DllImport("VidyoClientDll.dl", CharSet = CharSet.Ansi)]
        //     public static extern IntPtr VidyoClientLogParam(ref logParams logParams);
        #endregion
    }
}