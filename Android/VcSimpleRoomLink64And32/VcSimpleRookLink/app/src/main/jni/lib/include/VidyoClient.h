/*! @file VidyoClient.h
	@brief Main Vidyo Client API Library header.
	@copyright
	(c) 2006-2014 Vidyo, Inc.
	433 Hackensack Avenue, 7th Floor,
	Hackensack, NJ  07601.
	All rights reserved.
	The information contained herein is proprietary to Vidyo, Inc.
	and shall not be reproduced, copied (in whole or in part), adapted,
	modified, disseminated, transmitted, transcribed, stored in a retrieval
	system, or translated into any language in any form by any means
	without the express written consent of Vidyo, Inc.
*/

#ifndef VIDYO_CLIENT_H
#define VIDYO_CLIENT_H


/*!
 * @defgroup VidyoClientModule Vidyo Client API Library
 * @brief Vidyo Client APIs
 */

/*!
 * @defgroup VidyoClientCallbackModule Callbacks
 * @brief Callbacks
 * @ingroup  VidyoClientModule
 */

/*!
 * @defgroup VidyoClientApiModule Functions
 * @brief Application interface functions
 * @ingroup  VidyoClientModule
 */

/*!
 * @defgroup VidyoClientLogModule Logging
 * @brief Integrated logging functions
 * @ingroup  VidyoClientApiModule
 */

/* This group of headers must be included in a specific order,
	 non-alphabetical
*/
#include "VidyoTypes.h"
#include "VidyoClientConstants.h"
#include "VidyoClientMessages.h"
#include "VidyoClientParameters.h"

#undef  PRODUCT_NAME

#ifndef DOXYGEN_SHOULD_IGNORE_THIS

#ifndef VIDYO_CLIENT_LOG_ENABLED
	#ifndef VIDYO_CLIENT_LOG_DISABLED
		#define VIDYO_CLIENT_LOG_ENABLED
	#endif
#endif
#ifndef VIDYO_CLIENT_CONSOLE_LOG_ENABLED
	#ifndef VIDYO_CLIENT_CONSOLE_LOG_DISABLED
		#define VIDYO_CLIENT_CONSOLE_LOG_ENABLED
	#endif
#endif

#endif /* DOXYGEN_SHOULD_IGNORE_THIS */

/**
* @addtogroup VidyoClientLogModule
* @{
*/

/*!
@brief Console logging configuration enumeration type.

@details
This structure is passed in call to VidyoClientConsoleLogConfigure()
*/
typedef enum VidyoClientConsoleLogConfiguration_
{
	VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_NONE,			/*!< no console logging (default) */
	VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_DIRECT,			/*!< only logs that are specified to be printed in console */
	VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_ALL,				/*!< all logs go to console */
	VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_OUT_EVENT_ONLY,	/*!< all logs go as an VIDYO_CLIENT_OUT_EVENT_LOG only (no console logging, no disk logging) */
	VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_RESERVED,		/*!< reserved range for private use */
} VidyoClientConsoleLogConfiguration;

/*!
@brief Confidentiality level in log file enumeration type.

@details
This information is used in call to #VidyoClientGetLogConfidentialityLevel() and #VidyoClientSetLogConfidentialityLevel()
*/
typedef enum VidyoClientLogConfidentialityLevel_
{
	VIDYO_CLIENT_LOG_CONFIDENTIALITY_LEVEL_NONE,    /*!< No confidentiality (default) */
	VIDYO_CLIENT_LOG_CONFIDENTIALITY_LEVEL_EXCLUDE_PERSONALLY_IDENTIFIABLE_INFO,  /*!< Exclude personally identifiable information from logs */
} VidyoClientLogConfidentialityLevel;

/** @} */
/*! Logging configuration structure type.

	Logging configuration structure type, pointer to which is passed in call to #VidyoClientStart() and #VidyoClientInitialize()
*/
typedef struct VidyoClientLogParams_
{
	const char *logLevelsAndCategories;   /*!< levels and categories to log */
	VidyoUint logSize;                    /*!< maximum size of each log file */
	const char *pathToLogDir;             /*!< path to write log files */
	const char *logBaseFileName;          /*!< base file name used for log files */
	const char *pathToDumpDir;            /*!< path to write dump files (unused) */
	const char *pathToConfigDir;          /*!< path to config.xml file (used by Android */
} VidyoClientLogParams;

/*!
@brief String table management structure type.

@details
String table management structure type, pointer to which is passed in call to #VidyoClientStart()
*/
typedef struct VidyoClientAppStringsInfo_
{
	VidyoVoidPtr *stringTable;        /*!< AppStringTable array */
	VidyoUint numStringTableEntries;  /*!< Count of AppStringTable array elements */
	VidyoUint8 **stringFileName;      /*!< Array of language file names to retrieve language strings from */
	VidyoUint numLanguages;           /*!< Count of language file names array elements */
	const char *appStringsDir;        /*!< path to language files */
	VidyoUint initLanguage;           /*!< bitcoded initialized language */
} VidyoClientAppStringsInfo;

/*! Profile structure type, pointer to which is passed in call to #VidyoClientStart()
*/
typedef struct VidyoClientProfileParams_
{
	const char *PROGFILES_DIR;      /*!< path of system application directory */
	const char *CONFIG_KEY_PATH;    /*!<
										path of configuration registry hive
										@note Windows only
									*/
	const char *PRODUCT_NAME;       /*!< name of product */
	const char *PRODUCT_VERSION;    /*!< Product version tag or identification string - No more than 16 bytes long */
	const char *MYDOCS_DIR;         /*!< path of user my documents directory */
	const char *VIDYO_DIR;          /*!< path of user application directory */
	const char *CERT_FILE_DIR;      /*!< path of certificate file directory */
	const char *INSTALLED_APP_DIR;  /*!< path of installed application directory */
	int portNumber;                 /*!< port to listen for browser connections */
	char **argvList;                /*!< command line argv list, NULL to ignore */
} VidyoClientProfileParams;

typedef struct VidyoClientFeatureControl_
{
	VidyoBool disableLectureMode;			/*!< VIDYO_TRUE to disable optional lecture mode feature. VIDYO_FALSE to enable lecture mode feature */
	VidyoBool disableLocalMicrophone;       /*!< VIDYO_TRUE to disable using all microphones connected to machine for capturing audio. VIDYO_FALSE to enable using local microphone */
	VidyoBool disableLocalSpeaker;          /*!< VIDYO_TRUE to disable using all speakers connected to machine for playing back audio. VIDYO_FALSE to enable using local speaker */
	VidyoBool disableLocalCamera;           /*!< VIDYO_TRUE to disable using all cameras connected to machine for capturing video. VIDYO_FALSE to enable using local camera */
	VidyoBool disableAutoLoginAtClientStart;/*!< VIDYO_TRUE to disable automatic login to VidyoPortal as previously logged-in user if available at VidyoClient start. VIDYO_FALSE to enable automatic login */
	VidyoBool disableVidyoPortalInterface;  /*!< VIDYO_TRUE to disable SOAP interface with VidyoPortal. Clients working by disabling VidyoPortal interface should be using a SOAP client for user login, licensing, search, contact or roster and conference management. VIDYO_FALSE to enable VidyoPortal Interface. */
	VidyoBool enableVirtualCameraInterface;	/*!< VIDYO_TRUE to enable virtual camera Interface where frames to render will be written to a shared memory created by VidyoClient. */
	VidyoBool enableOpusAudioCodec;			/*!< VIDYO_TRUE to enable OPUS audio codec (if supported by portal/router). VIDYO_FLASE to disable OPUS audio codec (Default) */
	VidyoBool disableUiPinning;             /*!< VIDYO_TRUE to disable the pinning using the user interface. Tiles Renderer Only. VIDYO_FALSE to enable (default) */
    VidyoBool androidForceResolution;             /*!< VIDYO_TRUE to respect the resolution set for advanced resolutions. VIDYO_FALSE implies that bandwidth / cpu adjustments might still change it (default) */
    VidyoBool androidForgetCamera;             /*!< VIDYO_TRUE to join with automatically selected camera*/
} VidyoClientFeatureControl;

#if defined(__cplusplus)
extern "C" {
#endif

/**
* @addtogroup VidyoClientCallbackModule
* @{
*/

/*!
	@brief Output event callback.

	Receives an event from Vidyo Client library. Should return promptly, and
	copy any retained parameter data before returning.

	@param[out] event                  Enumeration of event received
	@param[out] param                  Pointer to parameter structure, if any
	@param[out] paramSize              Size, in bytes, of parameter structure
	@param[out] data                   Pointer to data, registered with #VidyoClientStart
	@return

	@see VidyoClientOutEvent
	@see VidyoClientStart
	@see VidyoClientInitialize
*/
typedef void (WINAPI *VidyoClientOutEventCallback)( VidyoClientOutEvent event,
													VidyoVoidPtr param,
													VidyoUint paramSize,
													VidyoVoidPtr data);
/**
* @}
*/

/*******************************************************************************
 Functions of Vidyo Client Library
*******************************************************************************/
/*!
	@brief Default constructor for optional features supported by VidyoClient.

	This can be used to get default values of features that can be controlled by application.

	@param[in] featureControlParam    Pointer to VidyoClientFeatureControl which will be filled by VidyoClient
	@return (Nothing - this API should never fail)
*/
DECLSPEC void VidyoClientFeatureControlConstructDefault(VidyoClientFeatureControl *featureControlParam);

/**
 * * @addtogroup VidyoClientApiModule
 * * @{
 * */

/*!
	@brief Set or configure VidyoClient with optional features.

	@warning Application should call VidyoClientFeatureControlConstructDefault to get the default values and modify
	any features that application has to change and then call this API. This API has to be called after
	VidyoClientInitialize and before VidyoClientStart.

	@param[in] featureControlParam    Pointer to VidyoClientFeatureControlt
	@return *VIDYO_TRUE* on success, *VIDYO_FALSE* on failure, defined as
			an inability to accept the requested feature control.
*/
DECLSPEC VidyoBool VidyoClientSetOptionalFeatures(VidyoClientFeatureControl *featureControlParam);
/** @} */

/*!
	@brief Set or configure VidyoClient instance identity. This is required only if multiple instances of vidyoclient are
	required to be created on the same machine.

	@warning This API has to be called after VidyoClientInitialize and before VidyoClientStart.

	@param[in] epInstanceId id string - should not longer than VIDYO_CLIENT_MAX_INSTANCE_ID_SIZE
	@return *VIDYO_TRUE* on success, *VIDYO_FALSE* on failure.
*/
DECLSPEC VidyoBool VidyoClientSetEndpointInstanceId(const char* epInstanceId);

/**
* @addtogroup VidyoClientLogModule
* @{
*/

/*!
	@brief Configure console logging.

	This function can be called before all others, to configure console logging
	performed by the library. Should not be called after VidyoClientStart().
	If not called, console logging will be disabled entirely.

	@param[in] config             Console logging configuration
	@return (Nothing)

	@see VidyoClientLogModule() for log functions
*/
DECLSPEC void
	VidyoClientConsoleLogConfigure(VidyoClientConsoleLogConfiguration config);
/** @} */

/**
* @addtogroup VidyoClientApiModule
* @{
*/

/*!
	@brief Initializes Vidyo Client API Library.

	This function must be called before others to initialize the
	library. If set logging parameters given to this function will take precedence over
	the logging parameters given to VidyoClientStart().

	@param[in] eventCb                  Callback for events from library to GUI
	@param[in] data                     Pointer to data associated with callback
	@param[in] logParams                Parameters required for configuring logging or NULL

	@return *VIDYO_TRUE* on success, *VIDYO_FALSE* on failure, defined as
			an inability to initialize one of the components of the
			library

	@note   Returns successfully if called again after successful return,
			without intervening call to VidyoClientUninitialize(). This API
			has to be called from main thread.
	@warning This function or VidyoClientStart() must be called before others
	@see VidyoClientUninitialize()
*/
DECLSPEC VidyoBool VidyoClientInitialize(VidyoClientOutEventCallback eventCb,
										 VidyoVoidPtr data,
										 VidyoClientLogParams *logParams);


/*!
	@brief Starts Vidyo Client API Library.

	This function start video conferencing runtime.

	@param[in] eventCb                  Callback for events from library to GUI.
	@param[in] data                     Pointer to data associated with callback.
	@param[in] logParams                Parameters required for configuring logging.
	@param[in] parentWindow             Parent window for video layout, operating system dependent.
										Use NULL to create windows automatically.
	@param[in] videoRect                Region of parent window for video layout.
	@param[in] profileParams            Parameters required for setting application profile.
	@param[in] appStringsInfo           Parameters required for initializing AppStrings.
	@param[in] reserved2                Must be set to NULL.
	@return *VIDYO_TRUE* on success, *VIDYO_FALSE* on failure, defined as
			an inability to initialize one of the components of the
			library.

	@note   Returns successfully if called again after successful return,
			without intervening call to VidyoClientStop()
	@warning This function must be called before others except VidyoClientInitialize()
	@see VidyoClientStop()
	@see VidyoClientOutEventCallback()
*/
DECLSPEC VidyoBool VidyoClientStart(VidyoClientOutEventCallback eventCb,
									VidyoVoidPtr data,
									VidyoClientLogParams *logParams,
									VidyoWindowId parentWindow,
									VidyoRect *videoRect,
									VidyoClientAppStringsInfo *appStringsInfo,
									VidyoClientProfileParams *profileParams,
									VidyoBool reserved2);


/*!
	@brief Stops Vidyo Client API Library.

	This function stops video conferencing runtime.

	@return *VIDYO_TRUE* on success, *VIDYO_FALSE* on failure, defined as
			an inability to stop now because the client may be in the
			middle of a conference, or in the process of leaving or
			joining a conference

	@note   Does nothing if called again after successful return,
			without intervening call to VidyoClientStart()
	@warning This function must be called before #VidyoClientUninitialize
	@see VidyoClientStart()
*/
DECLSPEC VidyoBool VidyoClientStop(void);

/*!
	@brief Uninitializes Vidyo Client API Library.

	This function uninitializes Vidyo Client API Library resources.
	Application usually calls this function before exiting.
	Not calling this function will result in the memory leaks.

	@note This function must be called last.  This API
	has to be called from main thread.
	@see VidyoClientStop()
*/
DECLSPEC void VidyoClientUninitialize(void);


/*!
	@brief Sends an event.

	Sends a non-blocking event to Vidyo Client API Library.

	@param[in] event                  enumeration of event to send
	@param[in] param                  pointer to parameter structure, if any
	@param[in] paramSize              size, in bytes, of parameter structure
	@return *VIDYO_TRUE* on success, *VIDYO_FALSE* on failure
	@warning Do not call before #VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED was received

	@see VidyoClientInEvent
	@see VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED
*/
DECLSPEC VidyoBool VidyoClientSendEvent(VidyoClientInEvent event,
										VidyoVoidPtr param,
										VidyoSizeT paramSize);

/*!
	@brief Sends an request.

	Sends a blocking request to Vidyo Client API Library.

	@param[in]     request                enumeration of request to send
	@param[in,out] param                  pointer to parameter structure, if any
	@param[in]     paramSize              size, in bytes, of parameter structure
	@return VidyoUint with error code defined in VidyoClientConstants.h
	@warning Do not call before #VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED was received

	@see VidyoClientRequest
	@see VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED
	@see VidyoClientErrorCodeModule
*/
DECLSPEC VidyoUint VidyoClientSendRequest(VidyoClientRequest request,
										  VidyoVoidPtr param,
										  VidyoSizeT paramSize);

/*!
	@brief Retrieves start/stop status of Vidyo Client API Library.
	@return *VIDYO_TRUE* for started, *VIDYO_FALSE* otherwise

	@see VidyoClientStart()
*/
DECLSPEC VidyoBool VidyoClientIsStarted(void);

    /*!
     @brief To start synchronize the Vidyo Client Library activities using internal mutex.
     @return *VIDYO_TRUE* for syncronize is success, *VIDYO_FALSE* failure due to uninitialized library
     
     @see VidyoClientInitialize()
     */
DECLSPEC VidyoBool VidyoClientSynchronizeStart(void);
    
    /*!
     @brief To end synchronize the Vidyo Client Library activities using internal mutex.
     @return *VIDYO_TRUE* for syncronize is success, *VIDYO_FALSE* failure due to uninitialized library
     
     @see VidyoClientInitialize()
     */
    DECLSPEC VidyoBool VidyoClientSynchronizeEnd(void);
 
/*!
	@brief Gets the version of VidyoClient.

	Returns the system version of Vidyo Client API Library.

	@param[in, out] output            Output buffer where the VidyoClient version is written.
	@param[in]      size              Size of output in bytes. Size should be #VIDYO_CLIENT_VERSION_SIZE or more.
	@warning Do not call before #VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED was received

*/
DECLSPEC void VidyoClientGetVersion(char *output, VidyoSizeT size);

/*!
	@brief Get the name of product for which VidyoClient is used.

	Returns the product name set by application
	@param[in, out] output            Output buffer where the product name should be written and returned.
	@param[in]      size              Size of output in bytes. Size should be #VIDYO_CLIENT_APPLICATION_NAME_LEN or more.
	@warning Do not call before #VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED was received

*/
DECLSPEC void VidyoClientGetProductName(char *output, VidyoSizeT size);

/*!
	@brief Get the tag or vertion of product set to VidyoClient by application

	Returns the product tag/version as set by application
	@param[in, out] output            Output buffer where the product tag/version should be written and returned.
	@param[in]      size              Size of output in bytes. Size should be #VIDYO_CLIENT_VERSION_SIZE or more.
	@warning Do not call before #VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED was received

*/
DECLSPEC void VidyoClientGetProductTag(char *output, VidyoSizeT size);

/*!
	@brief Get the confidentiality level set for the log

	Returns the log confidentiality level as set on the application
	@warning Do not call before #VidyoClientInitialize is successful or after #VidyoClientUninitialize is executed.

*/
DECLSPEC VidyoClientLogConfidentialityLevel VidyoClientGetLogConfidentialityLevel(void);

/*!
	@brief Set the confidentiality level for the log

	Returns VIDYO_TRUE on success and VIDYO_FALSE on failure.
	@param[in]      confidentialityLevel    Confidentiality level to be set.
	@warning Do not call before #VidyoClientInitialize is successful or after #VidyoClientUninitialize is executed.

*/
DECLSPEC VidyoBool VidyoClientSetLogConfidentialityLevel(VidyoClientLogConfidentialityLevel confidentialityLevel);

#if defined(ANDROID)
/*!
	@brief Retrieves configuration path on Android.

	This function returns the directory path name associated with the
	Configuration files. This is for Android so that the configuration
	files will be placed on the same location in internal memory.
	Application cannot use a hard-coded value to rely on phone specific
	directory layouts.

	@param[in]    configDir     value to set the directory to. Can be NULL
															which will just return the value already set.
	@return The string value of the directory where config files should
			be placed on the android device.

	@note Android specific
*/
DECLSPEC char *VidyoAndroidConfigDir(const char *configDir);
#endif

/** @} */

/**
* @addtogroup VidyoClientLogModule
* @{
*/

/*!
	@brief Log a raw message to the console.

	Can be called before VidyoClientStart().
	If called with no prior call to VidyoClientConsoleLogConfigure(), or if the
	configuration passed was #VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_DIRECT,
	the log will not be emitted. Whether the preprocessor macro
	#VIDYO_CLIENT_CONSOLE_LOG_ENABLED is defined has no effect on this function.
	The console used is specified via the standard output process file
	descriptor.

	@param[in]    message     raw message to log to console
	@return (Nothing)
*/
DECLSPEC void VidyoClientConsoleLog(const char *message);

/*!
	@brief Log a formatted message to the console.

	Can be called before
	VidyoClientStart(). If called with no prior call to
	VidyoClientConsoleLogConfigure(), or if the configuration passed was
	#VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_DIRECT, the log will not be emitted.
	Whether the preprocessor macro #VIDYO_CLIENT_CONSOLE_LOG_ENABLED is defined
	has no effect on this function.

	The console used is specified via the standard output process file
	descriptor.

	@param[in]    format    Format string to use, in the style of `printf()`
	@param[in]    ...       One parameter for each specifier in format string
	@return (Nothing)
*/
DECLSPEC void VidyoClientConsoleLogFormatted(const char *format, ...);

/*!
	@brief Log a raw message to logging subsystem.

	Must be called after VidyoClientStart(). Whether the preprocessor macro #VIDYO_CLIENT_LOG_ENABLED
	is defined has no effect on this function.

	@param[in]    level     Logging level to use
	@param[in]    file      Source file name (usually filled in by macro)
	@param[in]    line      Source line number (usually filled in by macro)
	@param[in]    function  Source function name (usually filled in by macro)
	@param[in]    message   Raw message to log to logging subsystem
	@return (Nothing)
*/
DECLSPEC void VidyoClientLog(VidyoLogLevel level,
							 const char *file,
							 VidyoInt line,
							 const char *function,
							 const char *message);


/*!
	@brief Log a formatted message to logging subsystem.

	Must be called after  VidyoClientStart(). Whether the preprocessor macro #VIDYO_CLIENT_LOG_ENABLED
	is defined has no effect on this function.

	@param[in]    level     Logging level to use
	@param[in]    file      Source file name (usually filled in by macro)
	@param[in]    line      Source line number (usually filled in by macro)
	@param[in]    function  Source function name (usually filled in by macro)
	@param[in]    format    Format string to use, in the style of `printf()`
	@param[in]    ...       One parameter for each specifier in format string
	@return (Nothing)
*/
DECLSPEC void VidyoClientLogFormatted(VidyoLogLevel level,
									  const char *file,
									  VidyoInt line,
									  const char *function,
									  const char *format, ...);

/*!
	@brief Log a raw message to nowhere.

	Can be called before VidyoClientStart().
	Used in conjunction with logging macros.

	@param[in]    message    Raw message
	@return (Nothing)
*/
DECLSPEC void VidyoClientNoLog(const char *message);

    /*!
     @brief Setup license keychain name instead of default.
     
     Must be called before VidyoClientStart().
     
     @param[in]    keyChain    Set license keychain. Keychain must start with "."
     @return (Nothing)
     */
DECLSPEC void VidyoClientSetKeyChain(char *keyChain);
    
    /*!
     @brief Return license keychain name.
     
     @param[in]    (Nothing)
     
     @return license keychain name. If license keychain is not change, return default keychain.
     */
DECLSPEC const char* VidyoClientGetKeyChain(void);

/*!
	@brief Log a formatted message to nowhere.

	Can be called before VidyoClientStart().
	Used in conjunction with logging macros.

	@param[in]    format    Format string to use, in the style of `printf()`
	@param[in]    ...       One parameter for each specifier in format string
	@return (Nothing)
*/
DECLSPEC void VidyoClientNoLogFormatted(const char *format, ...);

/** @} */
#if defined(__cplusplus)
}
#endif

/**
* @addtogroup VidyoClientLogModule
* @{
*/
/*! @name Logging macros
 *
 *  Macros of Vidyo Client Library, which support integrated logging
 *  @note Macros that end in _FORMATTED (with the exception of
 *        VIDYO_CLIENT_CONSOLE_LOG_FORMATTED) cannot be used with a format string
 *        and no additional parameters
 */
/*!  */
 //@{
#ifdef DOXYGEN_SHOULD_IGNORE_THIS
/*! When defined, enables console logging */
#define VIDYO_CLIENT_CONSOLE_LOG_ENABLED 1

/*! When defined, enables logging */
#define VIDYO_CLIENT_LOG_ENABLED 1
#endif
/*! @def VIDYO_CLIENT_CONSOLE_LOG_FORMATTED()
*
*  Maps to VidyoClientConsoleLogFormatted()
*/
/*! @def VIDYO_CLIENT_LOG()
*
*  Maps to VidyoClientLog()
*/

/*! @def VIDYO_CLIENT_LOG_FORMATTED()
*
*  Maps to VidyoClientLogFormatted()
*/

/*! @def VIDYO_CLIENT_LOG_FATAL()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_FATAL_FORMATTED()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_ERROR()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_ERROR_FORMATTED()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_WARNING()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_WARNING_FORMATTED()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_INFO()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_INFO_FORMATTED()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_DEBUG()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_DEBUG_FORMATTED()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_SENT()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_SENT_FORMATTED()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_RECEIVED()
 *  Specific log level macro
 */
/*! @def VIDYO_CLIENT_LOG_RECEIVED_FORMATTED()
 *  Specific log level macro
 */

/*
 Macros of Vidyo Client Library, which support integrated logging as follows:
 VIDYO_CLIENT_CONSOLE_LOG_ENABLED     When defined, enables console logging
																			macros
 VIDYO_CLIENT_CONSOLE_LOG()           Maps to VidyoClientConsoleLog()
 VIDYO_CLIENT_CONSOLE_LOG_FORMATTED() Maps to VidyoClientConsoleLogFormatted()
 VIDYO_CLIENT_LOG_ENABLED             When defined, enables general logging
																			macros
 VIDYO_CLIENT_LOG()                   Maps to VidyoClientLog()
 VIDYO_CLIENT_LOG_FORMATTED()         Maps to VidyoClientLogFormatted()
 VIDYO_CLIENT_LOG_FATAL()             VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_FATAL, ...)
 VIDYO_CLIENT_LOG_FATAL_FORMATTED()   VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_FATAL, ...)
 VIDYO_CLIENT_LOG_ERROR()             VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_ERROR, ...)
 VIDYO_CLIENT_LOG_ERROR_FORMATTED()   VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_ERROR, ...)
 VIDYO_CLIENT_LOG_WARNING()           VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_WARNING, ...)
 VIDYO_CLIENT_LOG_WARNING_FORMATTED() VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_WARNING, ...)
 VIDYO_CLIENT_LOG_INFO()              VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_INFO, ...)
 VIDYO_CLIENT_LOG_INFO_FORMATTED()    VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_INFO, ...)
 VIDYO_CLIENT_LOG_DEBUG()             VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_DEBUG, ...)
 VIDYO_CLIENT_LOG_DEBUG_FORMATTED()   VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_DEBUG, ...)
 VIDYO_CLIENT_LOG_SENT()              VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_SENT, ...)
 VIDYO_CLIENT_LOG_SENT_FORMATTED()    VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_SENT, ...)
 VIDYO_CLIENT_LOG_RECEIVED()          VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_RECEIVED, ...)
 VIDYO_CLIENT_LOG_RECEIVED_FORMATTED()VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_RECEIVED, ...)
 Note:  Macros that end in _FORMATTED (with the exception of
		VIDYO_CLIENT_CONSOLE_LOG_FORMATTED) cannot be used with a format string
		and no additional parameters
****************************************************************************** */
#ifdef VIDYO_CLIENT_CONSOLE_LOG_ENABLED
#define VIDYO_CLIENT_CONSOLE_LOG VidyoClientConsoleLog
#define VIDYO_CLIENT_CONSOLE_LOG_FORMATTED VidyoClientConsoleLogFormatted
#else /* VIDYO_CONSOLE_LOG_ENABLED */
#define VIDYO_CLIENT_CONSOLE_LOG VidyoClientNoLog
#define VIDYO_CLIENT_CONSOLE_LOG_FORMATTED VidyoClientNoLogFormatted
#endif /* VIDYO_CONSOLE_LOG_ENABLED */

#ifdef VIDYO_CLIENT_LOG_ENABLED
#define VIDYO_CLIENT_LOG(level, message) \
	VidyoClientLog(level, __FILE__, __LINE__, "", message)
#define VIDYO_CLIENT_LOG_FORMATTED(level, format, ...) \
	VidyoClientLogFormatted(level, __FILE__, __LINE__, "", format, __VA_ARGS__)
#else /* VIDYO_CLIENT_LOG_ENABLED */
#define VIDYO_CLIENT_LOG(level, message) VidyoClientNoLog(message)
#define VIDYO_CLIENT_LOG_FORMATTED(level, format, ...) \
	VidyoClientNoLogFormatted(format, __VA_ARGS__)
#endif /* VIDYO_CLIENT_LOG_ENABLED */
#define VIDYO_CLIENT_LOG_FATAL(message) \
	VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_FATAL, message)
#define VIDYO_CLIENT_LOG_FATAL_FORMATTED(format, ...) \
	VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_FATAL, format, __VA_ARGS__)
#define VIDYO_CLIENT_LOG_ERROR(message) \
	VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_ERROR, message)
#define VIDYO_CLIENT_LOG_ERROR_FORMATTED(format, ...) \
	VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_ERROR, format, __VA_ARGS__)
#define VIDYO_CLIENT_LOG_WARNING(message) \
	VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_WARNING, message)
#define VIDYO_CLIENT_LOG_WARNING_FORMATTED(format, ...) \
	VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_WARNING, format, __VA_ARGS__)
#define VIDYO_CLIENT_LOG_INFO(message) \
	VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_INFO, message)
#define VIDYO_CLIENT_LOG_INFO_FORMATTED(format, ...) \
	VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_INFO, format, __VA_ARGS__)
#define VIDYO_CLIENT_LOG_DEBUG(message) \
	VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_DEBUG, message)
#define VIDYO_CLIENT_LOG_DEBUG_FORMATTED(format, ...) \
	VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_DEBUG, format, __VA_ARGS__)
#define VIDYO_CLIENT_LOG_SENT(message) \
	VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_SENT, message)
#define VIDYO_CLIENT_LOG_SENT_FORMATTED(format, ...) \
	VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_SENT, format, __VA_ARGS__)
#define VIDYO_CLIENT_LOG_RECEIVED(message) \
	VIDYO_CLIENT_LOG(VIDYO_LOG_LEVEL_RECEIVED, message)
#define VIDYO_CLIENT_LOG_RECEIVED_FORMATTED(format, ...) \
	VIDYO_CLIENT_LOG_FORMATTED(VIDYO_LOG_LEVEL_RECEIVED, format, __VA_ARGS__)
//@}
/** @} */

#endif /* VIDYO_CLIENT_H */

/*! @mainpage Introduction
## About ##
VidyoClient library definitions are divided into the following header
 files:
 - VidyoClient.h:
     + Main header file
     + Includes all other headers
     + Provides function definitions.
 - VidyoTypes.h:
     + Fundamental types, such as scalars
 - VidyoClientConstants.h:
     + Error return codes
     + Non-enumeration constants for certain kinds of message parameters and
         configuration info
 - VidyoClientMessages.h:
     Enumerations for messages of every kind:
     + Events sent to VidyoClient library (VIDYO_CLIENT_IN_EVENT_*). See #VidyoClientInEvent.
     + Events received from VidyoClient library (VIDYO_CLIENT_OUT_EVENT_*). See #VidyoClientOutEvent.
     + Requests dispatched to VidyoClient library (VIDYO_CLIENT_REQUEST_*) See #VidyoClientRequest.
 - VidyoClientParameters.h:
     + Enumerations and structures for parameters passed in messages

The user of VidyoClient library only has to include VidyoClient.h header, to
automatically include the headers listed above.

## Basic library usage ##

### Initialization ###

Initialization process is used to allocate memory and do other pre-start tasks. Should be used only once per lifetime of the application.

@code{.c}

VidyoClientLogParams logParams = {0};

logParams.logBaseFileName = "vidyo_";
logParams.pathToLogDir = "/path_to_log";
logParams.logLevelsAndCategories = "debug@App debug@AppEvents warning";
logParams.logSize = 10*1024*1024; // 10M

if (VidyoClientInitialize(VidyoClientOutEventCallback, applicationData, &logParams) == VIDYO_FALSE)
{
    // Failure handling code
}
@endcode

### Starting library ###

Starts library logic.

@code{.c}

VidyoClientLogParams logParams = {0};

logParams.logBaseFileName = "vidyo_";
logParams.pathToLogDir = "/path_to_log";
logParams.logLevelsAndCategories = "debug@App debug@AppEvents warning";
logParams.logSize = 10*1024*1024; // 10M

VidyoClientProfileParams profileParams = {0};
profileParams.PROGFILES_DIR   = "\\CompanyName\\Product Name\\";
profileParams.CONFIG_KEY_PATH = "SOFTWARE\\CompanyName\\Product Name\\";
profileParams.PRODUCT_NAME    = "ProductName";
profileParams.MYDOCS_DIR      = "\\Product Name\\";
profileParams.VIDYO_DIR       = "\\CompanyName";
profileParams.portNumber      = 63457;

if (VidyoClientStart(   VidyoClientOutEventCallback,
                        applicationData,
                        &logParams,
                        (VidyoWindowId) osWindow,
                        &osVideoRect,
                        &profileParams,
                        NULL,
                        VIDYO_FALSE) != VIDYO_TRUE)
{
    // Failure handling code
}
@endcode

### Sending an event ###

@code{.c}

// Login to the portal
VidyoClientInEventLogIn event = {0};

strlcpy(event.portalUri, "https://demo.vidyo.com", sizeof(event.portalUri));
strlcpy(event.userName, "vidyo_user", sizeof(event.userName));
strlcpy(event.userPass, "vidyo_user_password", sizeof(event.userPass));

if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LOGIN, &event, sizeof(VidyoClientInEventLogIn)) != VIDYO_TRUE)
{
    // Failure handling code
}
@endcode

### Sending a request ###

@code{.c}
// Setting input devices
VidyoClientRequestConfiguration config = {0};

// Getting current system configuration
VidyoUint error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION,
                                         &config,
                                         sizeof(VidyoClientRequestConfiguration));
if (error != VIDYO_CLIENT_ERROR_OK)
{
    // Failure handling code
}

// Application should let user to decide what device to use

config.currentMicrophone  = userSelectedMicrophone;
config.currentCamera      = userSelectedCamera;
config.currentSpeaker     = userSelectedSpeaker;

// Enable lables in the conference window
config.enableShowConfParticipantName = 1;

// Updating system configuration
error = VidyoClientSendRequest( VIDYO_CLIENT_REQUEST_SET_CONFIGURATION,
                                &config,
                                sizeof(VidyoClientRequestConfiguration));
if (error != VIDYO_CLIENT_ERROR_OK)
{
    // Failure handling code
}
@endcode

### Receiving an event ###

@code{.c}
// Callback for output events from Vidyo Client API Library
// Registered with VidyoClientStart
void VidyoClientOutEventCallback(VidyoClientOutEvent event,
                                 VidyoVoidPtr param,
                                 VidyoUint paramSize,
                                 VidyoVoidPtr data)
{
    printf("Received event=%d \n", event);

    if (event >= VIDYO_CLIENT_OUT_EVENT_MIN
        && event <= VIDYO_CLIENT_OUT_EVENT_MAX)
    {
        // dispatch to handler for public out events
        if(event == VIDYO_CLIENT_OUT_EVENT_LICENSE)
        {
            //
            // If there are any issues with Licenses, this event will be sent
            // by the VidyoClient library
            //
            VidyoClientOutEventLicense *eventLicense;
            eventLicense = (VidyoClientOutEventLicense *) param;

            VidyoUint error = eventLicense->error;
            VidyoUint vmConnectionPath = eventLicense->vmConnectionPath;
            VidyoBool OutOfLicenses = eventLicense->OutOfLicenses;

            printf("License Error: errorid=%d vmConnectionPath=%d OutOfLicense=%d\n", error, vmConnectionPath, OutOfLicenses);
        }
        else if(event == VIDYO_CLIENT_OUT_EVENT_SIGN_IN)
        {
            VidyoClientOutEventSignIn *eventSignIn;
            eventSignIn = (VidyoClientOutEventSignIn *) param;

            VidyoUint activeEid = eventSignIn->activeEid;
            VidyoBool signinSecured = eventSignIn->signinSecured;

            printf("activeEid=%d signinSecured=%d\n", activeEid, signinSecured);

            //
            // If the EID is not setup, it will return activeEid = 0
            // in this case, we invoke the license request using below event
            //

            if(!activeEid)
                (void)VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LICENSE, NULL, 0);
        }
        else if (event == VIDYO_CLIENT_OUT_EVENT_SIGNED_IN)
        {
            // Signed in logic
        }
        else if (event == VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT)
        {
            // Signed out logic
        }
    }
    else
    {
        // log unknown event
    }
}
@endcode

### Stop ###

Stops library logic.

@code{.c}
if (VidyoClientStop() != VIDYO_TRUE)
{
    // Probably still processing. May need to wait a little.
    // handle error
}
@endcode

### Deinitialization ###

Deinitialization process is used to deallocate memory. Should be used only once per lifetime of the application.

@code{.c}
VidyoClientUninitialize();
@endcode

*/
