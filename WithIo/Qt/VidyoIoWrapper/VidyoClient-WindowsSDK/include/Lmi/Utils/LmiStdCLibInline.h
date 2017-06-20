/**
   {file:
     {name: LmiStdCLibInline.h}
     {description: Inline functions for LmiStdCLib.}
     {copyright:
     	(c) 2005-2014 Vidyo, Inc.,
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

#if LMI_HAVE_STRING_H
#include <string.h>
#endif

#include <ctype.h>

#if LMI_HAVE_STRCMP
/** {implementation: {name: LmiStrCmp}} */
LMI_INLINE LmiInt LmiStrCmp(const char *a, const char *b)
{
  return strcmp(a, b);
}
#endif /* LMI_HAVE_STRCMP */


#if LMI_HAVE_STRNCMP
/** {implementation: {name: LmiStrNCmp}} */
LMI_INLINE LmiInt LmiStrNCmp(const char *a, const char *b, LmiSizeT len)
{
  return strncmp(a, b, len);
}
#endif /* LMI_HAVE_STRNCMP */


#if LMI_HAVE_STRLEN
/** {implementation: {name: LmiStrLen}} */
LMI_INLINE LmiSizeT LmiStrLen(const char *a)
{
  return strlen(a);
}
#endif /* LMI_HAVE_STRLEN */

#if LMI_HAVE_STRCHR
/** {implementation: {name: LmiStrChr}} */
LMI_INLINE const char* LmiStrChr(const char* s, char c)
{
  return strchr(s, c);
}
#endif /* LMI_HAVE_STRCHR */

#if LMI_HAVE_STRRCHR
/** {implementation: {name: LmiStrRChr}} */
LMI_INLINE const char* LmiStrRChr(const char* s, char c)
{
  return strrchr(s, c);
}
#endif /* LMI_HAVE_STRCHR */

#if LMI_HAVE_STRSTR
/** {implementation: {name: LmiStrStr}} */
LMI_INLINE const char* LmiStrStr(const char* s1, const char* s2)
{
  return strstr(s1, s2);
}
#endif /* LMI_HAVE_STRSTR */

#if LMI_HAVE_STRTOL
LMI_INLINE LmiInt32 LmiStrToInt32(const char* start, char** end, LmiInt base)
{
  return (LmiInt32)strtol(start, end, base);
}
#endif /* LMI_HAVE_STRTOL */


#if LMI_HAVE_STRTOUL
LMI_INLINE LmiUint32 LmiStrToUint32(const char* start, char** end, LmiInt base)
{
  return (LmiUint32)strtoul(start, end, base);
}
#endif /* LMI_HAVE_STRTOL */


#if LMI_HAVE_STRTOL && LMI_SIZEOF_LONG == LMI_SIZEOF_LONG_LONG
LMI_INLINE LmiInt64 LmiStrToInt64(const char* start, char** end, LmiInt base)
{
  return (LmiInt64)strtol(start, end, base);
}

#elif LMI_HAVE_STRTOLL
LMI_INLINE LmiInt64 LmiStrToInt64(const char* start, char** end, LmiInt base)
{
  return (LmiInt64)strtoll(start, end, base);
}

#elif LMI_HAVE__STRTOI64
LMI_INLINE LmiInt64 LmiStrToInt64(const char* start, char** end, LmiInt base)
{
  return (LmiInt64)_strtoi64(start, end, base);
}
#endif /* LMI_HAVE__STRTOI64 */


#if LMI_HAVE_STRTOUL && LMI_SIZEOF_UNSIGNED_LONG == LMI_SIZEOF_UNSIGNED_LONG_LONG
LMI_INLINE LmiUint64 LmiStrToUint64(const char* start, char** end, LmiInt base)
{
  return (LmiUint64)strtoul(start, end, base);
}

#elif LMI_HAVE_STRTOULL
LMI_INLINE LmiUint64 LmiStrToUint64(const char* start, char** end, LmiInt base)
{
  return (LmiUint64)strtoull(start, end, base);
}

#elif LMI_HAVE__STRTOUI64
LMI_INLINE LmiUint64 LmiStrToUint64(const char* start, char** end, LmiInt base)
{
  return (LmiUint64)_strtoui64(start, end, base);
}
#endif /* LMI_HAVE__STRTOUI64 */

#if LMI_HAVE_STRCASECMP
/** {implementation: {name: LmiStrCaseCmp}} */
LMI_INLINE LmiInt LmiStrCaseCmp(const char *a, const char *b)
{

  return strcasecmp(a, b);
}
#endif /* LMI_HAVE_STRCASECMP */

/** {implementation: {name: LmiStrNCaseCmp}} */
LMI_INLINE LmiInt LmiStrNCaseCmp(const char *a, const char *b, LmiSizeT length)
{
#ifdef _MSC_VER
  return _strnicmp(a, b, length);
#else
  return strncasecmp(a, b, length);
#endif
}

#if LMI_HAVE_MEMCPY
/** {implementation: {name: LmiMemCpy}} */
LMI_INLINE void * LmiMemCpy(void * s1, const void * s2, LmiSizeT n)
{
  return memcpy(s1, s2, n);
}
#endif /* LMI_HAVE_MEMCPY */


#if LMI_HAVE_MEMMOVE
/** {implementation: {name: LmiMemMove}} */
LMI_INLINE void * LmiMemMove(void * s1, const void * s2, LmiSizeT n)
{
  return memmove(s1, s2, n);
}
#endif /* LMI_HAVE_MEMMOVE */


#if LMI_HAVE_MEMCMP
/** {implementation: {name: LmiMemCmp}} */
LMI_INLINE LmiInt LmiMemCmp(const void * s1, const void * s2, LmiSizeT n)
{
  return memcmp(s1, s2, n);
}
#endif /* LMI_HAVE_MEMCMP */


#if LMI_HAVE_MEMSET
/** {implementation: {name: LmiMemSet}} */
LMI_INLINE void* LmiMemSet(void * s, LmiInt c, LmiSizeT n)
{
  return memset(s, c, n);
}
#endif /* LMI_HAVE_MEMSET */


#if LMI_HAVE_MEMCHR
/** {implementation: {name: LmiMemChr}} */
LMI_INLINE const void* LmiMemChr(const void * s, LmiInt c, LmiSizeT n)
{
  return memchr(s, c, n);
}
#endif /* LMI_HAVE_MEMCHR */

#if LMI_HAVE_MEMMEM
/** {implementation: {name: LmiMemMem}} */
LMI_INLINE const void* LmiMemMem(const void* s1, LmiSizeT len1, const void* s2, LmiSizeT len2)
{
	return memmem(s1, len1, s2, len2);
}
#endif /* LMI_HAVE_MEMMEM */

LMI_INLINE LmiBool LmiIsAlnum(LmiInt c)
{
	return isalnum(c) != 0;
}

#if LMI_HAVE_GETENV
LMI_INLINE const char* LmiGetEnv(const char* name)
{
#if defined(_MSC_VER) /* Visual C++ complains that getenv is potentially insecure. */
#pragma warning(push)
#pragma warning(disable:4996)
#endif
	return getenv(name);
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
}
#endif /* LMI_HAVE_GETENV */

#if LMI_HAVE_SETENV
LMI_INLINE LmiBool LmiSetEnv(const char* name, const char* value, LmiBool overwrite)
{
	return setenv(name, value, overwrite) == 0;
}
#elif LMI_HAVE__PUTENV_S
LMI_INLINE LmiBool LmiSetEnv(const char* name, const char* value, LmiBool overwrite)
{
	if (!overwrite) {
#if defined(_MSC_VER) /* Visual C++ complains that getenv is potentially insecure. */
#pragma warning(push)
#pragma warning(disable:4996)
#endif
		if (getenv(name) != NULL)
			return LMI_TRUE;
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
	}
	return _putenv_s(name, value) == 0;
}
#endif /* LMI_HAVE_SETENV || LMI_HAVE__PUTENV_S */

#if LMI_HAVE_UNSETENV
LMI_INLINE LmiBool LmiUnsetEnv(const char* name)
{
#if defined(__DARWIN_UNIX03) && !__DARWIN_UNIX03
	/* Mac OS X, in backward-compatibility mode including OS X 10.4,
	   has an old definition of unsetenv that returns void. */
	unsetenv(name);
	return LMI_TRUE;
#else
	return unsetenv(name) == 0;
#endif
}
#elif LMI_HAVE__PUTENV_S
LMI_INLINE LmiBool LmiUnsetEnv(const char* name)
{

	return _putenv_s(name, "") == 0;
}
#endif /* LMI_HAVE_UNSETENV || LMI_HAVE__PUTENV_S */

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)

LMI_INLINE int LmiPrintfWrapWP8_(const char* fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = LmiVPrintfWrapWP8_(fmt, ap);
	va_end(ap);

	return ret;
}

LMI_INLINE int LmiFPrintfWrapWP8_(FILE* file, const char* fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = LmiVFPrintfWrapWP8_(file, fmt, ap);
	va_end(ap);

	return ret;

}


#endif
