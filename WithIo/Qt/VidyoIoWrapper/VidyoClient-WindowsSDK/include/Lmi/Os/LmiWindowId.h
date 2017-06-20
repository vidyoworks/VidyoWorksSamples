/**
{file:
	{name: LmiWindowId.h}
	{description: Describes an Operating System specific window identifier. }
	{copyright:
		(c) 2012-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.

		All rights reserved.

		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.
		                  ***** CONFIDENTIAL *****
	}
}
*/
#ifndef LMI_WINDOWID_H
#define LMI_WINDOWID_H

#include <Lmi/Utils/LmiTypes.h>

/**
{type:
	{name: LmiWindowId}
	{parent: Os}
	{include: Lmi/Os/LmiWindowId.h}
	{description: Operating system specific window identifier.}
}
*/

#if defined(LMI_HAVE_CREATEWINDOWEXA)
#	if defined(LMI_HAVE_WINSOCK2_H)
#		include <winsock2.h>
#	elif defined(LMI_HAVE_WINDOWS_H)
#		include <windows.h>
#	endif
	typedef HWND LmiWindowId;
#elif defined(LMI_HAVE_COCOA_COCOA_H)
#	include <ApplicationServices/ApplicationServices.h>
	typedef CGWindowID LmiWindowId;
#elif defined(LMI_HAVE_X11_XLIB_H)
#	include <X11/Xlib.h>
	typedef Window LmiWindowId;
#elif defined(LMI_HAVE_SCREEN_SCREEN_H)
#	include <screen/screen.h>
	typedef screen_window_t LmiWindowId;
#else
	typedef void *LmiWindowId;
#endif

LMI_BEGIN_EXTERN_C

LMI_INLINE_DECLARATION LmiWindowId *LmiWindowIdConstructInvalid(LmiWindowId *x);
LMI_INLINE_DECLARATION LmiWindowId *LmiWindowIdConstructCopy(LmiWindowId *a, const LmiWindowId *b);
LMI_INLINE_DECLARATION void LmiWindowIdDestruct(LmiWindowId *x);
LMI_INLINE_DECLARATION LmiWindowId *LmiWindowIdAssign(LmiWindowId *a, const LmiWindowId *b);
LMI_INLINE_DECLARATION LmiBool LmiWindowIdEqual(const LmiWindowId *a, const LmiWindowId *b);
LMI_INLINE_DECLARATION LmiBool LmiWindowIdLess(const LmiWindowId *a, const LmiWindowId *b);
LMI_INLINE_DECLARATION LmiBool LmiWindowIdIsValid(const LmiWindowId *x);


/**
 {type:
	{name: LmiViewId}
	{parent: Os}
	{include: Lmi/Os/LmiWindowId.h}
	{description: Operating system specific window view identifier.}
 }
 */
#if defined(LMI_HAVE_CREATEWINDOWEXA)
#	if defined(LMI_HAVE_WINSOCK2_H)
#		include <winsock2.h>
#	elif defined(LMI_HAVE_WINDOWS_H)
#		include <windows.h>
#	endif
typedef HWND LmiViewId;
#elif defined(LMI_HAVE_COCOA_COCOA_H)
#	include <ApplicationServices/ApplicationServices.h>
typedef void *LmiViewId;
#elif defined(LMI_HAVE_X11_XLIB_H)
#	include <X11/Xlib.h>
typedef Window LmiViewId;
#elif defined(LMI_HAVE_SCREEN_SCREEN_H)
#	include <screen/screen.h>
typedef screen_window_t LmiViewId;
#elif defined(ANDROID)
#   include <jni.h>
typedef jobject LmiViewId; /* Must be of type android.view.View */
#else
typedef void *LmiViewId;
#endif

LMI_INLINE_DECLARATION LmiViewId *LmiViewIdConstructInvalid(LmiViewId *x);
LMI_INLINE_DECLARATION LmiViewId *LmiViewIdConstructCopy(LmiViewId *a, const LmiViewId *b);
LMI_INLINE_DECLARATION void LmiViewIdDestruct(LmiViewId *x);
LMI_INLINE_DECLARATION LmiViewId *LmiViewIdAssign(LmiViewId *a, const LmiViewId *b);
LMI_INLINE_DECLARATION LmiBool LmiViewIdEqual(const LmiViewId *a, const LmiViewId *b);
LMI_INLINE_DECLARATION LmiBool LmiViewIdLess(const LmiViewId *a, const LmiViewId *b);
LMI_INLINE_DECLARATION LmiBool LmiViewIdIsValid(const LmiViewId *x);


LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiWindowIdInline.h>
#endif

#endif

