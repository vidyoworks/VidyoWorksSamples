#ifndef VIDYO_CONNECTOR_WRAPPERH_
#define VIDYO_CONNECTOR_WRAPPERH_

#include "IVidyoClient.h"
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








#if defined(VIDYO_WIN32)

#else

#endif


DECLSPEC VidyoClientPtr VcwGetClient(VidyoClientSwitchDefs::ClientType clientType);

#endif