/** {file:
      {name: LmiBaseCompiler.h}
      {description: Compiler-specific specializations for LMI code.}
      {copyright:
      	(c) 2011-2014 Vidyo, Inc.,
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

#ifndef LMI_BASE_COMPILER_H_
#define LMI_BASE_COMPILER_H_

/* Autoconf-detected compiler configuration */
#if defined(HAVE_CONFIG_H) || defined(LMI_HAVE_LMI_CONFIG_AUTOCONF_H)
#include <LmiConfigAutoconf.h>

#if defined LMI_HAVE_TARGETCONDITIONALS_H
#include <TargetConditionals.h>
#endif

/* Apple Mac OS X / iPhone (Xcode) */
#elif defined(__APPLE_CC__)
#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#if defined(__i386__)
#include <Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeI386.h>
#elif defined(__x86_64__)
#include <Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeX86_64.h>
#elif defined(__arm__)
#include <Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeARM.h>
#elif defined(__arm64__)
#include <Lmi/Utils/SysDep/LmiConfigIPhoneOSXcodeARM64.h>
#else
#error "Unknown iPhone OS/XCode CPU"
#endif

#else /* Mac OS X */

#if defined(__i386__)
#include <Lmi/Utils/SysDep/LmiConfigMacOS10Xcode.h>
#elif defined(__x86_64__)
#include <Lmi/Utils/SysDep/LmiConfigMacOS10XcodeX86_64.h>
#else
#error "Unknown Mac OS/XCode CPU"
#endif

#endif

/* Microsoft Visual Studio */
#elif defined(_MSC_VER) 
#if defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
/* Windows Phone */
#if _M_IX86
#include <Lmi/Utils/SysDep/LmiConfigWindowsPhoneX86_.h>
#elif _M_ARM
#include <Lmi/Utils/SysDep/LmiConfigWindowsPhoneARM_.h>
#else
#error "Unknown Windows Phone/Visual Studio CPU"
#endif

#else

#if _M_IX86
#include <Lmi/Utils/SysDep/LmiConfigWindowsX86_.h>
#elif _M_X64
#include <Lmi/Utils/SysDep/LmiConfigWindowsX64_.h>
#else
#error "Unknown Windows/Visual Studio CPU"
#endif

#endif

#else
#error "Unknown compiler/platform"
#endif

#include <Lmi/Utils/SysDep/LmiInline.h>
#include <Lmi/Utils/SysDep/LmiFunctionName.h>
#include <Lmi/Utils/SysDep/LmiAttributeDefs.h>
#include <Lmi/Utils/SysDep/LmiOptFns.h>

/* If compiling as C++, extern "C" include guards. */
#if defined(__cplusplus)
#define LMI_BEGIN_EXTERN_C extern "C" {
#define LMI_END_EXTERN_C }
#else
#define LMI_BEGIN_EXTERN_C
#define LMI_END_EXTERN_C
#endif

#endif /* LMI_BASE_COMPILER_H_ */

