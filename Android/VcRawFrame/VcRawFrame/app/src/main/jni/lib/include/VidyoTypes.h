/*! @file VidyoTypes.h
	@brief Fundamental types of Vidyo Client API Library.
	@copyright (c) 2006-2014 Vidyo, Inc.
	433 Hackensack Avenue, 7th Floor,
	Hackensack, NJ  07601.
	All rights reserved.
	The information contained herein is proprietary to Vidyo, Inc.
	and shall not be reproduced, copied (in whole or in part), adapted,
	modified, disseminated, transmitted, transcribed, stored in a retrieval
	system, or translated into any language in any form by any means
	without the express written consent of Vidyo, Inc.

	Vidyo Client Library platform identification macros:
	- VIDYO_WIN32 (Windows 32-bit and 64-bit platforms)
	- VIDYO_MACOS (Mac OS X, starting with Leopard)
	- VIDYO_LINUX (All Linux distros)
	- VIDYO_ANDROID (Android)
	If one of these macros is not defined by build environment, one will be
	picked by inspection of compiler-defined macros
*/


/*! @typedef VidyoInt
	@brief Signed integer
*/
/*! @typedef VidyoUint
	@brief Unsigned integer
*/
/*! @typedef VidyoUint8
	@brief Unsigned 8bit integer
*/
/*! @typedef VidyoUint32
	@brief Unsigned 32bit integer
*/
/*! @typedef VidyoFourCC
	@brief Four bytes
*/
/*! @typedef VidyoBool
	@brief Boolean
*/
/*! @typedef VidyoSizeT
	@brief Size type
*/
/*! @typedef VidyoVoidPtr
	@brief Generic pointer
*/
/*! @typedef VidyoWindowId
	@brief System dependent windows handle
*/
/*! @typedef VidyoWindowCapturerWindowId
	@brief System dependent capture window handle
*/


#ifndef VIDYO_TYPES_H
#define VIDYO_TYPES_H

#ifdef DOXYGEN_SHOULD_IGNORE_THIS

/*! Should be defined if compiled for Android */
#define VIDYO_ANDROID
/*! Should be defined if compiled for Windows */
#define VIDYO_WIN32
/*! Should be defined if compiled for MacOS or iOS */
#define VIDYO_MACOS
/*! Should be defined if compiled for Linux */
#define VIDYO_LINUX
#else
#if defined(_MSC_VER)
	#if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) &&!defined(VIDYO_ANDROID)
		#define VIDYO_WIN32
	#endif /* #if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) */
#elif defined(__APPLE_CC__)
	#if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) &&!defined(VIDYO_ANDROID)
		#define VIDYO_MACOS
	#endif /* #if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) */
#elif defined(ANDROID)
	#if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) && !defined(VIDYO_ANDROID)
		#define VIDYO_ANDROID
	#endif /* #if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) */
#elif defined(linux)
	#if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) && !defined(VIDYO_ANDROID)
		#define VIDYO_LINUX
	#endif /* #if !defined(VIDYO_WIN32) && !defined(VIDYO_MACOS) && !defined(VIDYO_LINUX) */
#endif /* #if defined(_MSC_VER) */

/* Include certain system headers */
#if defined(VIDYO_LINUX) || defined (VIDYO_ANDROID)
#include <sys/types.h> /* for size_t */
#endif /* #if defined(VIDYO_LINUX) || defined (VIDYO_ANDROID) */
#if defined(VIDYO_WIN32) && !defined(BUILD_VIDYO_DESKTOP_QMAKE)
#include <windows.h> /* for WINAPI, HWND, etc. */
#endif /* #if defined(VIDYO_WIN32) && !defined(BUILD_VIDYO_DESKTOP_QMAKE) */

/* Establish values for certain platform-specific reserved identifiers */
#if defined(VIDYO_WIN32) && !defined(BUILD_VIDYO_DESKTOP_QMAKE)
	#ifndef DECLSPEC
		#if defined(BUILD_VIDYO_CLIENT_DLL)
			#define DECLSPEC __declspec(dllexport)
		#elif defined(VIDYO_CLIENT_STATIC_LIB)
			#define DECLSPEC
		#else
			#define DECLSPEC __declspec(dllimport)
		#endif /* #if defined(BUILD_VIDYO_CLIENT_DLL) */
	#endif /* #ifndef DECLSPEC */
	#define VIDYO_MAX_PATH _MAX_PATH
#elif defined(VIDYO_MACOS)
	#ifndef DECLSPEC
		#define DECLSPEC
	#endif /* #ifndef DECLSPEC */
	#ifndef WINAPI
		#define WINAPI
	#endif /* #ifndef WINAPI */
	#define VIDYO_MAX_PATH PATH_MAX
#elif defined(VIDYO_ANDROID)
	#ifndef WINAPI
		#define WINAPI
	#endif /* #ifndef WINAPI */
	#define DECLSPEC __attribute__((visibility("default")))
	#define VIDYO_MAX_PATH PATH_MAX
#else // Linux
	#ifndef DECLSPEC
		#define DECLSPEC
	#endif /* #ifndef DECLSPEC */
	#ifndef WINAPI
		#define WINAPI
	#endif /* #ifndef WINAPI */
	#define VIDYO_MAX_PATH PATH_MAX
#endif /* #if defined(VIDYO_WIN32) */

// Ronen's changes: TODO: Merge into above block.
#if defined(VIDYO_WIN32) && defined(BUILD_VIDYO_DESKTOP_QMAKE)
	#define VIDYO_MAX_PATH _MAX_PATH
#endif

/* AppStrings defines to control the string type for format/encoding */
#if defined(VIDYO_WIN32) && !defined(BUILD_VIDYO_DESKTOP_QMAKE)
	#define ASCHAR const wchar_t
	#define ASTEXT(a) L##a
#elif defined(VIDYO_MACOS) && !defined(BUILD_VIDYO_DESKTOP_QMAKE)
	#define ASCHAR NSString
	#define ASTEXT(a) @a
#else // Linux, Android
	#define ASCHAR const char
	#define ASTEXT(a) a
#endif // #if defined(VIDYO_WIN32)

#endif /* DOXYGEN_SHOULD_IGNORE_THIS */
/* Basic types defined by Vidyo Client Library */
typedef signed int VidyoInt;
typedef unsigned int VidyoUint;
typedef unsigned char VidyoUint8;

#if defined(VIDYO_WIN32) || defined(VIDYO_LINUX) || defined(VIDYO_MACOS) || defined(VIDYO_ANDROID)
typedef unsigned int VidyoUint32;
#endif

typedef VidyoUint32 VidyoFourCC;
typedef VidyoUint32 VidyoImageFormat;

typedef char VidyoBool;
/*! @brief Boolean definitions */
enum
{
	VIDYO_FALSE = 0, /*!< False */
	VIDYO_TRUE = 1   /*!< True */
};
typedef size_t VidyoSizeT;
typedef void *VidyoVoidPtr;

/*! @brief Rectangle structure */
typedef struct
{
	VidyoInt xPos;      /*!< x position */
	VidyoInt yPos;      /*!< y position */
	VidyoUint width;    /*!< width */
	VidyoUint height;   /*!< height */
} VidyoRect;

#if defined(VIDYO_WIN32) && !defined(BUILD_VIDYO_DESKTOP_QMAKE)
typedef HWND VidyoWindowId;
typedef HWND VidyoWindowCapturerWindowId;
#elif defined(VIDYO_MACOS)
typedef void *VidyoWindowId;
typedef unsigned int VidyoWindowCapturerWindowId;
#else // Linux
typedef void *VidyoWindowId;
typedef unsigned int VidyoWindowCapturerWindowId;
#endif // #if defined(VIDYO_WIN32)

/* Enumeration type to support logging */
/**
* @addtogroup VidyoClientLogModule
* @{
*/
/*! @brief Log levels */
typedef enum
{
	VIDYO_LOG_LEVEL_FATAL,     /*!< Fatal */
	VIDYO_LOG_LEVEL_ERROR,     /*!< Error */
	VIDYO_LOG_LEVEL_WARNING,   /*!< Warning */
	VIDYO_LOG_LEVEL_INFO,      /*!< Information */
	VIDYO_LOG_LEVEL_DEBUG,     /*!< Debug */
	VIDYO_LOG_LEVEL_SENT,      /*!< Sent */
	VIDYO_LOG_LEVEL_RECEIVED,  /*!< Received */
} VidyoLogLevel;
/** @} */
#endif /* VIDYO_TYPES_H */

