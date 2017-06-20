#ifndef VIDYO_CONNECTOR_WRAPPERH_
#define VIDYO_CONNECTOR_WRAPPERH_
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

typedef signed int VidyoInt;
typedef unsigned int VidyoUint;
typedef unsigned char VidyoUint8;

typedef struct
{
	VidyoInt xPos;      /*!< x position */
	VidyoInt yPos;      /*!< y position */
	VidyoUint width;    /*!< width */
	VidyoUint height;   /*!< height */
} VidyoRect;

typedef enum
{
	VIDYO_IO_WRAPPER_FAILREASON_ConnectionFailed,
	VIDYO_IO_WRAPPER_FAILREASON_ConnectionLost,
	VIDYO_IO_WRAPPER_FAILREASON_ConnectionTimeout,
	VIDYO_IO_WRAPPER_FAILREASON_NoResponse,
	VIDYO_IO_WRAPPER_FAILREASON_Terminated,
	VIDYO_IO_WRAPPER_FAILREASON_InvalidToken,
	VIDYO_IO_WRAPPER_FAILREASON_UnableToCreateResource,
	VIDYO_IO_WRAPPER_FAILREASON_NoResponseFromResource,
	VIDYO_IO_WRAPPER_FAILREASON_InvalidResourceId,
	VIDYO_IO_WRAPPER_FAILREASON_ResourceFull,
	VIDYO_IO_WRAPPER_FAILREASON_NotMember,
	VIDYO_IO_WRAPPER_FAILREASON_Banned,
	VIDYO_IO_WRAPPER_FAILREASON_MediaNotEnabled,
	VIDYO_IO_WRAPPER_FAILREASON_MediaFailed,
	VIDYO_IO_WRAPPER_FAILREASON_MiscLocalError,
	VIDYO_IO_WRAPPER_FAILREASON_MiscRemoteError,
	VIDYO_IO_WRAPPER_FAILREASON_MiscError
} VidyoIoWrapperFailReason;

typedef enum
{
	VIDYO_IO_WRAPPER_DISCONNECTREASON_Disconnected,
	VIDYO_IO_WRAPPER_DISCONNECTREASON_ConnectionLost,
	VIDYO_IO_WRAPPER_DISCONNECTREASON_ConnectionTimeout,
	VIDYO_IO_WRAPPER_DISCONNECTREASON_NoResponse,
	VIDYO_IO_WRAPPER_DISCONNECTREASON_Terminated,
	VIDYO_IO_WRAPPER_DISCONNECTREASON_MiscLocalError,
	VIDYO_IO_WRAPPER_DISCONNECTREASON_MiscRemoteError,
	VIDYO_IO_WRAPPER_DISCONNECTREASON_MiscError
} VidyoIoWrapperDisconnectReason;

#if defined(VIDYO_WIN32)
typedef void(__stdcall *VidyoIoWrapperOnSuccess)();
typedef void(__stdcall *VidyoIoWrapperOnFailure)(VidyoIoWrapperFailReason reason);
typedef void(__stdcall *VidyoIoWrapperOnDisconnected)(VidyoIoWrapperDisconnectReason reason);
#else
typedef void(*VidyoIoWrapperOnSuccess)();
typedef void(*VidyoIoWrapperOnFailure)(VidyoIoWrapperFailReason reason);
typedef void(*VidyoIoWrapperOnDisconnected)(VidyoIoWrapperDisconnectReason reason);
#endif





DECLSPEC bool VIoWrapperInitialize(VidyoWindowId parentWindow, VidyoRect* videoRect);
DECLSPEC bool VIoWrapperUninitialize();
DECLSPEC bool VIoWrapperConnect(const char *host, const char * token, const char *displayName, const char* resourceId, 
	VidyoIoWrapperOnSuccess onSuccess, VidyoIoWrapperOnFailure onFailure, VidyoIoWrapperOnDisconnected onDisconnected);



#endif