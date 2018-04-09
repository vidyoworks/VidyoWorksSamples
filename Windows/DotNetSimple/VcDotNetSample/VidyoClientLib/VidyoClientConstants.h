/*! @file VidyoClientConstants.h
	@brief Constants for Vidyo Client API Library.
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

/*!
 * @defgroup VidyoClientErrorCodeModule Error codes
 * @brief Error codes
 * @ingroup  VidyoClientModule
 * @details Error return codes for Requests from GUI to Vidyo Client Library
 */

/*!
 * @defgroup VidyoClientConstantModule Constants
 * @brief Vidyo Client Library Constants
 * @ingroup  VidyoClientModule
 */

#ifndef VIDYO_CLIENT_CONSTANTS_H
#define VIDYO_CLIENT_CONSTANTS_H

/**
* @addtogroup VidyoClientErrorCodeModule
* @{
*/

/** @name General
 * #VIDYO_CLIENT_REQUEST_SET_CONFIGURATION related error codes.
 */
//@{
/*! No error  */
#define VIDYO_CLIENT_ERROR_OK 0
/*! Library is not started  */
#define VIDYO_CLIENT_ERROR_NO_ENGINE (1<<0)
/*! Wrong parameter size  */
#define VIDYO_CLIENT_ERROR_WRONG_SIZE (1<<1)
/*! Request enumerator is out of bound */
#define VIDYO_CLIENT_ERROR_WRONG_REQUEST (1<<2)
//@}
/** @name Configuration
 * #VIDYO_CLIENT_REQUEST_SET_CONFIGURATION related error codes.
 */
//@{
/*! Microphone index is invalid  */
#define VIDYO_CLIENT_ERROR_WRONG_MIC_NUM  (1<<3)
/*! Failed to set microphone device  */
#define VIDYO_CLIENT_ERROR_SET_MIC  (1<<4)
/*! Speaker index is invalid     */
#define VIDYO_CLIENT_ERROR_WRONG_SPEAKER_NUM  (1<<5)
/*! Failed to set speaker device     */
#define VIDYO_CLIENT_ERROR_SET_SPEAKER (1<<6)
/*! Camera index is invalid  */
#define VIDYO_CLIENT_ERROR_WRONG_CAMERA_NUM  (1<<7)
/*! Failed to set camera device  */
#define VIDYO_CLIENT_ERROR_SET_CAMERA (1<<8)
/*! Failed to set user id    */
#define VIDYO_CLIENT_ERROR_SET_USERID (1<<9)
/*! Failed to set password   */
#define VIDYO_CLIENT_ERROR_SET_PASSWORD (1<<10)
/*! Failed to set server address     */
#define VIDYO_CLIENT_ERROR_SET_SERVER_ADDRESS (1<<11)
/*! Failed to set server port    */
#define VIDYO_CLIENT_ERROR_SET_SERVER_PORT (1<<12)
/*! Failed to set lowest media port  */
#define VIDYO_CLIENT_ERROR_SET_MEDIA_LOW_PORT (1<<13)
/*! Failed to set highest media port     */
#define VIDYO_CLIENT_ERROR_SET_MEDIA_HIGH_PORT (1<<14)
/*! Failed to enable/disable logs    */
#define VIDYO_CLIENT_ERROR_SET_ENABLE_LOGGING (1<<15)
/*! Failed to set auto answer    */
#define VIDYO_CLIENT_ERROR_SET_AUTOANSWER (1<<16)
/*! Failed to set proxy  */
#define VIDYO_CLIENT_ERROR_SET_PROXY (1<<17)
/*! Failed to set logging window     */
#define VIDYO_CLIENT_ERROR_SET_LOGGING_WINDOW (1<<18)
/*! Failed to set entry tone     */
#define VIDYO_CLIENT_ERROR_SET_ENTRYTONE (1<<19)
/*! Failed to set video preference   */
#define VIDYO_CLIENT_ERROR_INVALID_VIDEO_PREFERENCE (1<<20)
/*! Failed to set self view loopback policy; Invalid parameter */
#define VIDYO_CLIENT_ERROR_SET_SELFVIEW_LOOPBACK_POLICY (1<<21)
/*! Set/Get is not supported for this device type */
#define VIDYO_CLIENT_ERROR_DEVICE_NOT_SUPPORTED (1<<22)
/*! Set mic volume is not allowed when AGC in ON */
#define VIDYO_CLIENT_ERROR_AGC_ON (1<<23)
/*! Disable AEC is not allowed for the selected Mic */
#define VIDYO_CLIENT_ERROR_INVALID_AEC_VALUE (1<<24)
/*! Disable AGC is not allowed for the selected Mic */
#define VIDYO_CLIENT_ERROR_INVALID_AGC_VALUE (1<<25)
/*! Called unsupportet function */
#define VIDYO_CLIENT_ERROR_UNSUPPORTED_FUNCTION (1<<26)
//@}

/** @name Participant
 * #VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS related error codes.
 */
//@{
/*! Failed to construct remote participant   */
#define VIDYO_CLIENT_ERROR_CONSTRUCT_REMOTE (1<<3)
//@}

/** @name Window share
 * #VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES related error codes.
 */
//@{
/*! Wrong window share URI   */
#define VIDYO_CLIENT_ERROR_WRONG_URI (1<<3)
//@}

/** @name Media info
 * #VIDYO_CLIENT_REQUEST_GET_MEDIA_INFO related error codes.
 */
//@{
/*! Failed to get capturer statistics    */
#define VIDYO_CLIENT_ERROR_CAPTURER_STAT (1<<3)
/*! Failed to get local source statistics    */
#define VIDYO_CLIENT_ERROR_LOCAL_SOURCE (1<<4)
//@}

/** @name EID
 * #VIDYO_CLIENT_REQUEST_GET_EID related error codes.
 */
//@{
/*! Failed to get Endpoint ID    */
#define VIDYO_CLIENT_ERROR_GET_EID (1<<20)
/*! Failed to set Endpoint ID    */
#define VIDYO_CLIENT_ERROR_SET_EID (1<<21)
/*! Client is not licensed   */
#define VIDYO_CLIENT_ERROR_NOT_LICENSED (1<<22)
//@}

/** @name Layout rectangle
 * #VIDYO_CLIENT_REQUEST_SET_LAYOUT_RECT related error codes.
 */
//@{
/*! Failed to set layout rectangle */
#define VIDYO_CLIENT_ERROR_SET_LAYOUT_RECT (1<<23)
//@}

/** @name Get list of open application windows and list of available system desktops
 * #VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS related error codes.
 */
//@{
/*! Error getting list of open application windows */
#define VIDYO_CLIENT_ERROR_GET_WINDOWS (1<<3)
/*! Error getting list of available system desktops */
#define VIDYO_CLIENT_ERROR_GET_DESKTOPS (1<<4)
//@}

/** @} */

/**
* @addtogroup VidyoClientConstantModule
* @{
*/
/** @name Sign in
 *  @brief Constants related to sign-in.
 *  @see VidyoClientInEventSignIn
 */
//@{
#define SIGNIN_SERVERADDRESS_SIZE 192
#define SIGNIN_SERVERPORT_SIZE (8)
#define SIGNIN_USERNAME_SIZE ((63*3)+1)
#define SIGNIN_PORTAL_ACCESS_KEY_SIZE (256 + 1)
#define SIGNIN_PORTALADDRESS_SIZE 128
#define SIGNIN_PORTALVERSION_SIZE 256
#define SIGNIN_VIDYO_PROXY_ADDRESS_SIZE 128
#define SIGNIN_VIDYO_PROXY_PORT_SIZE 8
#define SIGNIN_VIDYO_PROXY_NUMBER 8
#define SERVER_ADDRESS_SIZE (127+1)
#define SERVER_PORT_SIZE (7+1)
#define SIGNIN_MAX_COOKIE_SIZE 512
#define TOKEN_VALIDITY_INTERVAL	0
//Redefine if we want token to revalidate after let us say 8hrs
//#define TOKEN_VALIDITY_INTERVAL	28800
//@}

/** @name Licensing
 * Constants related to licensing.
 */
//@{
#define LAC_KEY_SIZE (128+1)
//@}

/** @name VidyoProxy
 * Constants related to VidyoProxy.
 */
//@{
#define PROXY_VIDYO_AUTO (1<<1)                     /*!< Automatic use of VidyoProxy */
#define PROXY_VIDYO_MANUAL (1<<2)                   /*!< Manual use of VidyoProxy */
#define PROXY_VIDYO_FORCE (1)                       /*!< Force use of VidyoProxy towards VidyoManager and VidyoRouter */
#define PROXY_WEB_ENABLE (1<<3)                     /*!< Enable web proxy */
#define PROXY_WEB_IE (1<<4)                         /*!< Means get and follow Internet Explorer LAN Settings */
#define PROXY_WEB_LOCAL (1<<5)                      /*!< Means web proxy details are configured directly on Client Application */
#define PROXY_WEB_IE_AUTO_DETECT (1<<6)             /*!< IE LAN setting is "Automatically Detect".
														 This means use WPAD to detect web proxy */
#define PROXY_WEB_IE_AUTO_CONFIG_SCRIPT (1<<7)      /*!< IE LAN setting is "Use Automatic Configuration Script".
														 This means download given PAC script using WPAD and find web proxy */
#define PROXY_WEB_IE_MANUAL (1<<8)                  /*!< IE LAN setting is "Use configured proxy server" */
#define PROXY_WEB_LOCAL_AUTO_DETECT (1<<9)          /*!< Client Application setting is "Automatically Detect".
													 Client Application is configured to use WPAD to detect web proxy */
#define PROXY_WEB_LOCAL_AUTO_CONFIG_SCRIPT (1<<10)  /*!< Client Application setting is "Use Automatic Configuration Script".
														This means download given PAC script using WPAD and find web proxy */
#define PROXY_WEB_LOCAL_MANUAL (1<<11)              /*!< Client Application setting is "Use configured proxy server" */
#define PROXY_VIDYO_FORCE_TO_VM (1<<12)             /*!< Force use of VidyoProxy towards VidyoManager only */
#define PROXY_VIDYO_DO_NOT_USE_TO_VR (1<<13)        /*!< Do not retry by using VidyoProxy for connection to VidyoRouter when direct connection is failed */
//@}

/**
* @addtogroup VidyoClientRequestModule
* @{
*/
/*! Base for request enumeration */
#define VIDYO_CLIENT_REQUEST_BASE 100000
/** @} */

/** @name Various
 * Various other definitions.
 */
//@{
#define MAX_PRIVATE_EVENT_DATA_SIZE 35*1024 //16384
#define NUM_USER_MESSAGE_CODES 3
#define MAX_USER_MESSAGE_STRING_SIZE (256+1)
#define FIELD_SIZE (63+1)
#define USERID_SIZE 128
#define PASSWORD_SIZE (256 + 1)
#define DEVICE_NAME_SIZE (127+1)
#define DEVICE_ID_SIZE (256+1)
#define SERVERPORT_SIZE (5+1)
#define MACADDRESS_SIZE (17+1)
#define ROOMKEY_SIZE 128
#define PIN_SIZE 17
#define MAX_DEVICE_NUMBER 30
#define MAX_PARTICIPANTS_NUM 24
#define URI_LEN (256+1)
#define DISPLAY_CONFERENCE_SIZE (127*3+1)//Bug#:2162
#define MAX_URI_LEN URI_LEN
#define MAX_NUM_APP_WINDOWS 128 // Maximum number of open application windows
#define MAX_NUM_SHARABLE_WINDOWS_WHITE_LIST 64 // Maximum number of sharable windows in white list 
#define MAX_SHARE_DISPLAY_DEVICE 16 // Maximum allowed sharable display devices
#define MAX_REMOTE_SHARE_APP 40 // Maximum number of remotely shared applications
#define PARTICIPANTS_LIMIT_AUTO 32
#define MAX_EID_SIZE (128+1) // endpoint ID string size
#define MAX_PID_SIZE (128+1) // participant ID string size
#define MAX_PORTAL_ADDRESS (URI_LEN+USERID_SIZE)
#define MAX_PORTAL_HISTORY_NUMBER 5
#define MAX_PORTAL_HISTORY_SIZE  (SIGNIN_SERVERADDRESS_SIZE + SIGNIN_USERNAME_SIZE + 10)
#define VIDYO_MANAGER_ID_SIZE 64
#define ENDPOINT_LOCATION_TAG_SIZE 40
#define MAX_LABEL_STRING_SIZE (32+1)
#define MAX_ENTITY_ID 257
#define MAX_GET_PARTICIPANT_NAME 128  // Maximum number of conference participant name can be retrieved in one message
#define MAX_GET_PARTICIPANT_STATISTICS 128 // Maximum number of conference participant's statistics information can be retrieved in one message
#define MAX_VISCA_COMMAND 128
#define MAX_LOG_STRING_SIZE (200+1)
#define MAX_INSTALLER_URI_SIZE 936
#define MAX_CHAT_MESSAGE_LEN    1024+1 // Maximum length of text message (contents)
#define VIDYO_CLIENT_VERSION_SIZE 32 // Maximum size of VidyoClient version
#define MAX_PASSPHRASE_SIZE 1024
#define MAX_EXTERNAL_ACCESS_TOKEN_SIZE 1024
#define MAX_FONT_PATH_SIZE (255+1)
#define MAX_PORTAL_PREFIX_SIZE (16+1)
#define MAX_COMMAND_LEN 4096 // Maximum length of command text
#define MAX_INTERFACE_LENGTH (256+1)


#define MAX_APPROVED_DOMAIN_NAMES 50

#define DEF_PROGFILES_DIR "\\Vidyo\\Vidyo Desktop\\"
#define DEF_CONFIG_KEY_PATH "SOFTWARE\\Vidyo\\Vidyo Desktop\\"
#define DEF_PRODUCT_NAME "VidyoDesktop"
#define DEF_MOBILEPRODUCT_NAME "VidyoMobile"
#define DEF_MYDOCS_DIR "\\Vidyo Desktop\\"
#define DEF_VIDYO_DIR "\\Vidyo"
#define DEF_HELP_PORT 63457
#define DEF_LOG_BASE_FILENAME "VidyoDesktop_"
#define MAX_IPADDRESS_LEN 48  // Max size of IPV6 in string is 39 characters
#define VIDYO_CLIENT_REFERENCE_NUMBER_LEN 64  // Max size of reference number or string
#define VIDYO_CLIENT_APPLICATION_NAME_LEN 24  // Max size of application name
#define VIDYO_CLIENT_MAX_DYNAMIC_VIEWS 16  // Maximum number of participants that can be watched dynamically
#define VIDYO_CLIENT_MAX_INSTANCE_ID_SIZE 12 // Maximum vidyoclient instance identity
#define VIDYO_MAX_EMAIL_ADDRESS_SIZE 128
#define VIDYO_MAX_EXTENSION_SIZE	64
#define VIDYO_CLIENT_SCREEN_ID_SIZE 128
#define VIDYO_CLIENT_MAX_LOG_LEN 2048

//@}
#endif /* VIDYO_CLIENT_CONSTANTS_H */
//@}
