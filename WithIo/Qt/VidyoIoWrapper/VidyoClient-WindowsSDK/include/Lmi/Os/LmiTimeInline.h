/** {file:
      {name: LmiTimeInline.h}
      {description: Inline functions for time handling.}
      {copyright:
      	(c) 2006-2014 Vidyo, Inc.,
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

#include <Lmi/Utils/LmiAssert.h>
#include <Lmi/Utils/LmiStdCLib.h>
#include <Lmi/Utils/LmiMisc.h>

/** {implementation: {name: LmiTimeSecs}} */
LMI_INLINE LmiTime LmiTimeSecs(LmiInt64 secs)
{
  return secs * LMI_NSECS_PER_SEC;
}


/** {implementation: {name: LmiTimeMsecs}} */
LMI_INLINE LmiTime LmiTimeMsecs(LmiInt64 msecs)
{
  return msecs * LMI_NSECS_PER_MSEC;
}


/** {implementation: {name: LmiTimeUsecs}} */
LMI_INLINE LmiTime LmiTimeUsecs(LmiInt64 usecs)
{
  return usecs * LMI_NSECS_PER_USEC;
}


/** {implementation: {name: LmiTimeConstructFromNtp}} */
LMI_INLINE LmiTime* LmiTimeConstructFromNtp(LmiTime* t, LmiUint64 ntp)
{
	LmiUint64 secs, frac;

	secs = ntp >> 32;
	frac = ntp & LMI_UINT64_C(0xffffffff);

	*t = (frac * LMI_NSECS_PER_SEC) >> 32;

	*t += LmiTimeSecs(secs - LMI_TIME_NTP_EPOCH_OFFSET_);

	return t;
}

/** {implementation: {name: LmiTimeGetNtp}} */
LMI_INLINE LmiUint64 LmiTimeGetNtp(LmiTime t)
{
  LmiTime secs, frac;
  LmiUint64 ntp;

  secs = t / LMI_NSECS_PER_SEC;
  frac = t % LMI_NSECS_PER_SEC;

  ntp = ((LmiUint64)frac << 32) / LMI_NSECS_PER_SEC;

  ntp += ((LmiUint64)(secs + LMI_TIME_NTP_EPOCH_OFFSET_)) << 32;

  return ntp;
}


#if LMI_TIME_USE_POSIX_WALL_TIME_


/** {implementation: {name: LmiTimeGetCurrentWallTime}} */
LMI_INLINE LmiTime LmiTimeGetCurrentWallTime(void)
{
  struct timeval tv;
  int ret;

  ret = gettimeofday(&tv, NULL);
  LmiAssert(ret == 0);

  return ((LmiTime)tv.tv_sec * LMI_NSECS_PER_SEC) +
    ((LmiTime)tv.tv_usec * LMI_NSECS_PER_USEC);
}


/** {implementation: {name: LmiGregorianTimeConstruct}} */
LMI_INLINE LmiGregorianTime *
LmiGregorianTimeConstruct(LmiGregorianTime * gt, LmiTime systemTime)
{
  time_t secs;
  if (sizeof(time_t) == 4 &&
	  (systemTime < LMI_INT64_C(-2147483648000000000) ||
		  systemTime > LMI_INT64_C(2147483647000000000)))
	  return NULL;
  secs = (time_t)(systemTime / LMI_NSECS_PER_SEC);

  if (localtime_r(&secs, &gt->tm) == NULL) {
    return NULL;
  }

  gt->nanosecs = (long)(systemTime % LMI_NSECS_PER_SEC);

  return gt;
}


/** {implementation: {name: LmiGregorianTimeConstructUTC}} */
LMI_INLINE LmiGregorianTime *
LmiGregorianTimeConstructUTC(LmiGregorianTime * gt, LmiTime systemTime)
{
  time_t secs;
  if (sizeof(time_t) == 4 &&
	  (systemTime < LMI_INT64_C(-2147483648000000000) ||
		  systemTime > LMI_INT64_C(2147483647000000000)))
	  return NULL;
  secs = (time_t)(systemTime / LMI_NSECS_PER_SEC);

  if (gmtime_r(&secs, &gt->tm) == NULL) {
    return NULL;
  }

  gt->nanosecs = (long)(systemTime % LMI_NSECS_PER_SEC);

  return gt;
}


/** {implementation: {name: LmiGregorianTimeConstructFields}} */
LMI_INLINE LmiGregorianTime* LmiGregorianTimeConstructFields(LmiGregorianTime* gt,
	LmiInt year, LmiInt month, LmiInt monthDay, LmiInt hour, LmiInt minute, LmiInt second, LmiTime nanosecond)
{
	if (!LmiGregorianTimeValidateFields_(year, month, monthDay, hour, minute, second, nanosecond))
		return NULL;

	LmiMemSet(&gt->tm, 0, sizeof(gt->tm));

	gt->tm.tm_year = year - 1900;
	gt->tm.tm_mon = month - 1;
	gt->tm.tm_mday = monthDay;
	gt->tm.tm_hour = hour;
	gt->tm.tm_min = minute;
	gt->tm.tm_sec = second;
	gt->nanosecs = (LmiInt)nanosecond;

	return gt;
}


/** {implementation: {name: LmiGregorianTimeGetYear}} */
LMI_INLINE LmiInt LmiGregorianTimeGetYear(const LmiGregorianTime * gt)
{
  return gt->tm.tm_year + 1900;
}


/** {implementation: {name: LmiGregorianTimeGetMonth}} */
LMI_INLINE LmiInt LmiGregorianTimeGetMonth(const LmiGregorianTime * gt)
{
  return gt->tm.tm_mon + 1;
}


/** {implementation: {name: LmiGregorianTimeGetMonthDay}} */
LMI_INLINE LmiInt LmiGregorianTimeGetMonthDay(const LmiGregorianTime * gt)
{
  return gt->tm.tm_mday;
}


/** {implementation: {name: LmiGregorianTimeGetHour}} */
LMI_INLINE LmiInt LmiGregorianTimeGetHour(const LmiGregorianTime * gt)
{
  return gt->tm.tm_hour;
}


/** {implementation: {name: LmiGregorianTimeGetMinute}} */
LMI_INLINE LmiInt LmiGregorianTimeGetMinute(const LmiGregorianTime * gt)
{
  return gt->tm.tm_min;
}


/** {implementation: {name: LmiGregorianTimeGetSecond}} */
LMI_INLINE LmiInt LmiGregorianTimeGetSecond(const LmiGregorianTime * gt)
{
  return gt->tm.tm_sec;
}


/** {implementation: {name: LmiGregorianTimeGetNanosecond}} */
LMI_INLINE LmiTime LmiGregorianTimeGetNanosecond(const LmiGregorianTime * gt)
{
  return gt->nanosecs;
}

/** {implementation: {name: LmiGregorianTimeGetLocalTime}} */
LMI_INLINE LmiTime LmiGregorianTimeGetLocalTime(const LmiGregorianTime* gt)
{
	/* mktime normalizes fields. */
	struct tm tmp_tm = gt->tm;
	time_t val;

	tmp_tm.tm_isdst = -1; /* Let mktime figure out DST. */
	val = mktime(&tmp_tm);
	if (val == -1) {
		/* mktime cannot represent 1969-12-31 23:59:59 UTC... */
		return LMI_TIME_INFINITE;
	}
	return (LmiTime)val * LMI_NSECS_PER_SEC +
		(LmiTime)gt->nanosecs;
}

/** {implementation: {name: LmiGregorianTimeGetUTCTime}} */
LMI_INLINE LmiTime LmiGregorianTimeGetUTCTime(const LmiGregorianTime* gt)
{
#if LMI_HAVE_TIMEGM
	/* timegm normalizes fields. */
	struct tm tmp_tm = gt->tm;
	time_t val;

	val = timegm(&tmp_tm);
	if (val == -1) {
		/* timegm cannot represent 1969-12-31 23:59:59 UTC */
		return LMI_TIME_INFINITE;
	}
#else
	/* Don't have timegm.  Use formula in the Posix spec: XBD 4.14 Seconds Since The Epoch -- modified to divide down. */
#define LMI_GREGORIANTIME_DIVDOWN_(a, b) ((a) / (b) + ((a) % (b) < 0 ? -1 : 0))
	int yday;
	time_t val;
	if (gt->tm.tm_yday != 0 || (gt->tm.tm_mon == 0 && gt->tm.tm_mday == 1)) {
		yday = gt->tm.tm_yday;
	}
	else {
		/* gt->tm.tm_yday not set.  gt was probably constructed by LmiGregorianCalendarConstructFields
		   or LmiGregorianCalendarConstructFromString. */
		const int monthdays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
		LmiAssert(gt->tm.tm_mon >= 0 && gt->tm.tm_mon < 12);
		yday = monthdays[gt->tm.tm_mon] + gt->tm.tm_mday - 1;
		if (gt->tm.tm_mon >= 2 && gt->tm.tm_year % 4 == 0 &&
			(gt->tm.tm_year % 100 != 0 || (gt->tm.tm_year + 300) % 400 == 0))
			yday++;
	}
	val = gt->tm.tm_sec + gt->tm.tm_min*60 + gt->tm.tm_hour*3600 + yday*86400 +
		(gt->tm.tm_year-70)*(time_t)31536000 +
		LMI_GREGORIANTIME_DIVDOWN_((gt->tm.tm_year-69),4)*86400 -
		LMI_GREGORIANTIME_DIVDOWN_((gt->tm.tm_year-1),100)*86400 +
		LMI_GREGORIANTIME_DIVDOWN_((gt->tm.tm_year+299),400)*86400;
#endif
	return (LmiTime)val * LMI_NSECS_PER_SEC +
		(LmiTime)gt->nanosecs;
}


#elif LMI_TIME_USE_WIN32_WALL_TIME_

LMI_INLINE LmiTime LmiTimeGetFromWin32FileTime_(LmiTimeWin32FileTimeUnion_ ft)
{
  return (LmiTime)(ft.li.QuadPart - LMI_TIME_WIN32_FILE_TIME_OFFSET_) * 100;
}

LMI_INLINE LmiTimeWin32FileTimeUnion_ LmiTimeGetWin32FileTime_(LmiTime t)
{
  LmiTimeWin32FileTimeUnion_ ret;
  ret.li.QuadPart = (t / 100) + LMI_TIME_WIN32_FILE_TIME_OFFSET_;

  return ret;
}

/** {implementation: {name: LmiTimeGetCurrentWallTime}} */
LMI_INLINE LmiTime LmiTimeGetCurrentWallTime(void)
{
  LmiTimeWin32FileTimeUnion_ system_time;

  GetSystemTimeAsFileTime(&system_time.ft);

  return LmiTimeGetFromWin32FileTime_(system_time);
}


/** {implementation: {name: LmiGregorianTimeConstruct}} */
LMI_INLINE LmiGregorianTime *
LmiGregorianTimeConstruct(LmiGregorianTime * gt, LmiTime t)
{
  LmiTimeWin32FileTimeUnion_ ft;
  SYSTEMTIME utc;

  ft = LmiTimeGetWin32FileTime_(t);

  if (!FileTimeToSystemTime(&ft.ft, &utc)) {
    return NULL;
  }
  
  if (!SystemTimeToTzSpecificLocalTime(NULL, &utc, &gt->st)) {
    return NULL;
  }
  gt->nanosecs_in_ms = t % LMI_NSECS_PER_MSEC;
  return gt;
}


/** {implementation: {name: LmiGregorianTimeConstructUTC}} */
LMI_INLINE LmiGregorianTime *
LmiGregorianTimeConstructUTC(LmiGregorianTime * gt, LmiTime t)
{
  LmiTimeWin32FileTimeUnion_ ft;

  ft = LmiTimeGetWin32FileTime_(t);

  if (!FileTimeToSystemTime(&ft.ft, &gt->st)) {
    return NULL;
  }
  gt->nanosecs_in_ms = t % LMI_NSECS_PER_MSEC;
  return gt;
}


/** {implementation: {name: LmiGregorianTimeConstructUTC}} */
LMI_INLINE LmiGregorianTime* LmiGregorianTimeConstructFields(LmiGregorianTime* gt,
	LmiInt year, LmiInt month, LmiInt monthDay, LmiInt hour, LmiInt minute, LmiInt second, LmiTime nanosecond)
{
	if (!LmiGregorianTimeValidateFields_(year, month, monthDay, hour, minute, second, nanosecond))
		return NULL;

	LmiMemSet(&gt->st, 0, sizeof(gt->st));
	gt->st.wYear = year;
	gt->st.wMonth = month;
	gt->st.wDay = monthDay;
	gt->st.wHour = hour;
	gt->st.wMinute = minute;
	gt->st.wSecond = second;
	gt->st.wMilliseconds = (WORD)(nanosecond / LMI_NSECS_PER_MSEC);
	gt->nanosecs_in_ms = nanosecond % LMI_NSECS_PER_MSEC;

	return gt;
}


/** {implementation: {name: LmiGregorianTimeGetYear}} */
LMI_INLINE LmiInt LmiGregorianTimeGetYear(const LmiGregorianTime * gt)
{
  return gt->st.wYear;
}


/** {implementation: {name: LmiGregorianTimeGetMonth}} */
LMI_INLINE LmiInt LmiGregorianTimeGetMonth(const LmiGregorianTime * gt)
{
  return gt->st.wMonth;
}


/** {implementation: {name: LmiGregorianTimeGetMonthDay}} */
LMI_INLINE LmiInt LmiGregorianTimeGetMonthDay(const LmiGregorianTime * gt)
{
  return gt->st.wDay;
}


/** {implementation: {name: LmiGregorianTimeGetHour}} */
LMI_INLINE LmiInt LmiGregorianTimeGetHour(const LmiGregorianTime * gt)
{
  return gt->st.wHour;
}


/** {implementation: {name: LmiGregorianTimeGetMinute}} */
LMI_INLINE LmiInt LmiGregorianTimeGetMinute(const LmiGregorianTime * gt)
{
  return gt->st.wMinute;
}


/** {implementation: {name: LmiGregorianTimeGetSecond}} */
LMI_INLINE LmiInt LmiGregorianTimeGetSecond(const LmiGregorianTime * gt)
{
  return gt->st.wSecond;
}


/** {implementation: {name: LmiGregorianTimeGetNanoseconds}} */
LMI_INLINE LmiTime LmiGregorianTimeGetNanosecond(const LmiGregorianTime * gt)
{
  return LmiTimeMsecs(gt->st.wMilliseconds) + (LmiTime)gt->nanosecs_in_ms;
}

/** {implementation: {name: LmiGregorianTimeGetLocalTime}} */
LMI_INLINE LmiTime LmiGregorianTimeGetLocalTime(const LmiGregorianTime* gt)
{
	SYSTEMTIME local;
	LmiTimeWin32FileTimeUnion_ ft;
	if (!TzSpecificLocalTimeToSystemTime(NULL, &gt->st, &local))
		return LMI_TIME_INFINITE;
	if (!SystemTimeToFileTime(&local, &ft.ft))
		return LMI_TIME_INFINITE;
	return LmiTimeGetFromWin32FileTime_(ft) + (LmiTime)gt->nanosecs_in_ms;
}

/** {implementation: {name: LmiGregorianTimeGetUTCTime}} */
LMI_INLINE LmiTime LmiGregorianTimeGetUTCTime(const LmiGregorianTime* gt)
{
	LmiTimeWin32FileTimeUnion_ ft;
	if (!SystemTimeToFileTime(&gt->st, &ft.ft))
		return LMI_TIME_INFINITE;
	return LmiTimeGetFromWin32FileTime_(ft) + (LmiTime)gt->nanosecs_in_ms;
}



#endif /* LMI_TIME_USE_*_WALL_TIME_ */

LMI_INLINE LmiGregorianTime* LmiGregorianTimeConstructCopy(LmiGregorianTime* dst, const LmiGregorianTime* src)
{
	*dst = *src;
	return dst;
}

LMI_INLINE void LmiGregorianTimeDestruct(LmiGregorianTime* gt)
{
}

LMI_INLINE LmiGregorianTime* LmiGregorianTimeAssign(LmiGregorianTime* dst, const LmiGregorianTime* src)
{
	*dst = *src;
	return dst;
}

LMI_INLINE LmiBool LmiGregorianTimeSwap(LmiGregorianTime* a, LmiGregorianTime* b)
{
	LmiGregorianTime tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

	return LMI_TRUE;
}

#if LMI_TIME_USE_POSIX_MONOTONIC_TIME_ 

LMI_INLINE LmiTime LmiTimeGetCurrentMonotonicTime(void)
{
  struct timespec ts;
  int ret;

  ret = clock_gettime(LmiTimeMonotonicClockId_, &ts);
  LmiAssert(ret == 0);

  return ((LmiTime)ts.tv_sec * LMI_NSECS_PER_SEC) +
    (LmiTime)ts.tv_nsec;
}

#elif LMI_TIME_USE_WIN32_MONOTONIC_TIME_

LMI_INLINE LmiTime LmiTimeGetCurrentMonotonicTime(void)
{
  LARGE_INTEGER ctr;
  BOOL ret;

  ret = QueryPerformanceCounter(&ctr);
  LmiAssert(ret);

  return (LmiTime)((double)ctr.QuadPart * 
	  LmiTimeWin32MonotonicTimeClockInterval_);
}

#elif LMI_TIME_USE_MACH_MONOTONIC_TIME_
LMI_INLINE LmiTime LmiTimeGetCurrentMonotonicTime(void)
{
  uint64_t now;

  now = mach_absolute_time();

  return (LmiTime)((double)now *
	  (double)LmiTimeMachMonotonicTimeClockInterval_);
}

#endif /* LMI_TIME_USE_*_MONOTONIC_TIME_ */

/* We save on calling LmiTimeGetCurrentMonotonicTime() by passing its value as an argument */
LMI_INLINE LmiTime LmiTimeGetElapsedRelativeTo(LmiTime curTime, LmiTime t)
{
	LmiTime elTime = curTime - t;

	if (elTime < 0)
		elTime = 0;

	return elTime;
}

LMI_INLINE LmiUint LmiTimeGetElapsedMsecRelativeTo(LmiTime curTime, LmiTime t)
{
	LmiTime elTime = curTime - t;

	if (elTime < 0)
		elTime = 0;

	return (LmiUint)(elTime/LMI_NSECS_PER_MSEC);
}

LMI_INLINE LmiUint LmiTimeGetElapsedMsec(LmiTime t)
{
	LmiTime elTime = LmiTimeGetCurrentMonotonicTime() - t;

	if (elTime < 0)
		elTime = 0;

	return (LmiUint)(elTime/LMI_NSECS_PER_MSEC);
}

LMI_INLINE LmiTime LmiTimeGetElapsed(LmiTime t)
{
	LmiTime elTime = LmiTimeGetCurrentMonotonicTime() - t;

	if (elTime < 0)
		return 0;
	else
		return elTime;
}

#if LMI_HAVE_STRUCT_TIMEVAL
/** {implementation: {name: LmiTimeGetRelativeTimevalFromMonotonicTime}} */
LMI_INLINE struct timeval*
LmiTimeGetRelativeTimevalFromMonotonicTime(LmiTime timeout, struct timeval* tv)
{
  if (timeout == LMI_TIME_INFINITE) {
	return NULL;
  }
  else if (timeout == 0) {
	tv->tv_sec = 0;
	tv->tv_usec = 0;
	return tv;
  }
  else {
	LmiTime cur = LmiTimeGetCurrentMonotonicTime();

	if (timeout <= cur) {
	  tv->tv_sec = 0;
	  tv->tv_usec = 0;
	  return tv;
	}
	else {
	  LmiTime delta = timeout - cur;

	  /* We want to round up, not down, to the nearest microsecond. */
	  delta += (LMI_NSECS_PER_USEC - 1);

	  /* Assume that timeval.tv_sec is 32-bits.  This is fine for
		 a relative value. */
	  if (delta >= LmiTimeSecs(0x7fffffff)) {
		return NULL;
	  }

	  tv->tv_sec = (long)(delta / LMI_NSECS_PER_SEC);
	  tv->tv_usec = 
#if LMI_HAVE_SUSECONDS_T
        (suseconds_t)
#else
        (long)
#endif
        ((delta % LMI_NSECS_PER_SEC) / LMI_NSECS_PER_USEC);
	  return tv;
	}
  }
}
#endif

/* LmiTimeRange implementation. */

LMI_INLINE LmiTimeRange* LmiTimeRangeConstruct(LmiTimeRange *x, LmiTime begin, LmiTime end)
{
	x->begin = begin;
	x->end = end;
	return x;
}

LMI_INLINE void LmiTimeRangeDestruct(LmiTimeRange *x)
{

}

LMI_INLINE LmiTimeRange* LmiTimeRangeConstructCopy(LmiTimeRange *x, const LmiTimeRange *y)
{
	x->begin = y->begin;
	x->end = y->end;
	return x;
}

LMI_INLINE LmiTimeRange* LmiTimeRangeAssign(LmiTimeRange *x, const LmiTimeRange *y)
{
	x->begin = y->begin;
	x->end = y->end;
	
	return x;
}

LMI_INLINE void LmiTimeRangeSwap(LmiTimeRange *x, LmiTimeRange *y)
{
	LmiTimeRange t;
	LmiTimeRangeConstructCopy(&t, x);
	LmiTimeRangeAssign(x, y);
	LmiTimeRangeAssign(y, &t);
	LmiTimeRangeDestruct(&t);
}

LMI_INLINE LmiBool LmiTimeRangeEqual(const LmiTimeRange *x, const LmiTimeRange *y)
{
	return (x->begin == y->begin && x->end == y->end);
}

LMI_INLINE LmiBool LmiTimeRangeLess(const LmiTimeRange *x, const LmiTimeRange *y)
{
	if(x->end < y->end)
		return LMI_TRUE;
	if(y->end < x->end)
		return LMI_FALSE;
	return x->begin < y->begin;
}

LMI_INLINE LmiTime LmiTimeRangeBegin(const LmiTimeRange *x)
{
	return x->begin;
}

LMI_INLINE LmiTime LmiTimeRangeEnd(const LmiTimeRange *x)
{
	return x->end;
}

LMI_INLINE LmiBool LmiTimeRangeIsValid(const LmiTimeRange *x)
{
	return x->begin >= x->end;
}

LMI_INLINE LmiBool LmiTimeRangeIntersects(const LmiTimeRange *x, const LmiTimeRange *y)
{
	LmiTimeRange result;
	LmiTimeRangeIntersection(x, y, &result);
	return LmiTimeRangeIsValid(&result);
}

LMI_INLINE LmiBool LmiTimeRangeSubsumes(const LmiTimeRange *x, const LmiTimeRange *y)
{
	return ((x->begin >= y->begin) && (x->end <= y->end));
}

LMI_INLINE void LmiTimeRangeIntersection(const LmiTimeRange *x, const LmiTimeRange *y, LmiTimeRange *result)
{
	result->begin = LmiMin(x->begin, y->begin);
	result->end = LmiMax(x->end, y->end);
}


LMI_INLINE void LmiTimeRangeUnion(const LmiTimeRange *x, const LmiTimeRange *y, LmiTimeRange *result)
{
	result->begin = LmiMax(x->begin, y->begin);
	result->end = LmiMin(x->end, y->end);
}

