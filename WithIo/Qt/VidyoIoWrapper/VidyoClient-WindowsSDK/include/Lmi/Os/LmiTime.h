/** {file:
      {name: LmiTime.h}
      {description: Time handling.}
      {copyright:
      	(c) 2005-2015 Vidyo, Inc.,
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
#ifndef LMI_TIME_H_
#define LMI_TIME_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>

#if LMI_HAVE_TIME_H
#include <time.h>
#endif

#if LMI_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#if LMI_HAVE_MACH_MACH_H
#include <mach/mach.h>
#endif

#if LMI_HAVE_MACH_MACH_TIME_H
#include <mach/mach_time.h>
#endif

#if LMI_HAVE_WINSOCK2_H
#include <winsock2.h>
#elif LMI_HAVE_WINDOWS_H
/* Cygwin needs <windows.h> for QueryPerformanceCounter, but <winsock2.h> isn't
 * compatible with <sys/types.h> etc.  Under Visual C++, however, we need to
 * include <winsock2.h> rather than <windows.h>, or we get the old winsock 1.1
 * functions. */
/* (Note that on Cygwin, <windows.h> only includes <winsock.h> if
 * __USE_W32_SOCKETS is defined, so this is safe.) */
#include <windows.h>
#endif

/* Determine the system implementation of wall-clock time to use. */
#if LMI_HAVE_GETTIMEOFDAY && LMI_HAVE_LOCALTIME_R && LMI_HAVE_GMTIME_R && LMI_HAVE_MKTIME

#define LMI_TIME_USE_POSIX_WALL_TIME_ 1

#elif LMI_HAVE_GETSYSTEMTIMEASFILETIME && \
  LMI_HAVE_FILETIMETOSYSTEMTIME && \
  LMI_HAVE_SYSTEMTIMETOFILETIME && \
  LMI_HAVE_SYSTEMTIMETOTZSPECIFICLOCALTIME && \
  LMI_HAVE_TZSPECIFICLOCALTIMETOSYSTEMTIME

#define LMI_TIME_USE_WIN32_WALL_TIME_ 1

#else
#error "Unknown implementation of wall-clock time."

#endif

/* Determine the system implementation of monotonic time to use. */
#if LMI_HAVE_QUERYPERFORMANCECOUNTER && LMI_HAVE_QUERYPERFORMANCEFREQUENCY

/* Win32 monotonic time. */

#define LMI_TIME_USE_WIN32_MONOTONIC_TIME_ 1

#elif LMI_HAVE_MACH_ABSOLUTE_TIME && LMI_HAVE_MACH_TIMEBASE_INFO

/* Mach (MacOS X) monotonic time */

#define LMI_TIME_USE_MACH_MONOTONIC_TIME_ 1

#elif LMI_HAVE_CLOCK_GETTIME

/* Posix monotonic time */

#define LMI_TIME_USE_POSIX_MONOTONIC_TIME_ 1

#else
#error "Unknown implementation of monotonic time."

#endif

/**
   {type:
     {name: LmiTime}
     {parent: Os}
     {include: Lmi/Os/LmiTime.h}
     {description: A representation of time, counted as a nanoseconds.}
     {constant:
       {name: LMI_TIME_INFINITE}
       {type: LmiTime}
       {description: A time value representing a time greater than any other
         time.  This value can be used to represent infinite waiting times.}}
     {constant:
       {name: LMI_NSECS_PER_SEC}
       {type: LmiTime}
       {description: The number of nanoseconds in a second, i.e. one billion,
         as a manifest constant.}}
     {constant:
       {name: LMI_NSECS_PER_MSEC}
       {type: LmiTime}
       {description: The number of nanoseconds in a millisecond, i.e.
         one million, as a manifest constant.}}
     {constant:
       {name: LMI_NSECS_PER_USEC}
       {type: LmiTime}
       {description: The number of nanoseconds in a microsecond, i.e.
         one thousand, as a manifest constant.}}
      {constant:
       {name: LMI_NSECS_PER_MIN}
       {type: LmiTime}
       {description: The number of nanoseconds in a minute, i.e. 60 * LMI_NSECS_PER_SEC,
         as a manifest constant.  Note that this disregards leap seconds.}}
      {constant:
       {name: LMI_NSECS_PER_HOUR}
       {type: LmiTime}
       {description: The number of nanoseconds in an hour, i.e. 60 * LMI_NSECS_PER_MIN,
         as a manifest constant.}}
      {constant:
       {name: LMI_NSECS_PER_DAY}
       {type: LmiTime}
       {description: The number of nanoseconds in a day, i.e. 24 * LMI_NSECS_PER_HOUR,
         as a manifest constant.  Note that this disregards daylight-savings time changes.}}
      {constant:
       {name: LMI_NSECS_PER_WEEK}
       {type: LmiTime}
       {description: The number of nanoseconds in a week, i.e. 7 * LMI_NSECS_PER_DAY,
         as a manifest constant.}}
     {constant:
       {name: LMI_USECS_PER_SEC}
       {type: LmiTime}
       {description: The number of microseconds in a second, i.e.
         one million, as a manifest constant.}}
     {constant:
       {name: LMI_USECS_PER_MSEC}
       {type: LmiTime}
       {description: The number of microseconds in a millisecond, i.e.
         one thousand, as a manifest constant.}}
     {constant:
       {name: LMI_MSECS_PER_SEC}
       {type: LmiTime}
       {description: The number of milliseconds in a second, i.e.
         one thousand, as a manifest constant.}}
     {note:
       {p: There are three types of time values defined for LmiTime:
         {h\:dl xmlns\:h="http\://www.w3.org/1999/xhtml":
           {h\:dt: Wall clock}
            {h\:dd: A representation of the system\'s best approximation to the
              current time of day.  These values may change unexpectedly as the
              system clock is adjusted.}
           {h\:dt: Monotonic}
             {h\:dd: A monotonic clock whose values consistently (to the best
               of the system\'s ability) measure time regardless of adjustments
               to the system\'s clock.}
           {h\:dt: Interval}
             {h\:dd: A period of time, representing the difference between two
               monotonic or wall-clock times.}
          }
        }
        {p: For both the wall-clock and monotonic times, the time base (the
          moment represented by LmiTime 0) is implementation-defined and any
          particular value should not be assumed in user code.  The time base
          for monotonic time and wall-clock time may be (and will usually be)
          different.}
        {p: LmiTime is a signed arithmetic type with at least 64 bits; it is
          safe to do general arithmetic on it.}
    }
  }
*/
typedef LmiInt64 LmiTime;

#define LMI_NSECS_PER_WEEK (7 * LMI_NSECS_PER_DAY)

#define LMI_NSECS_PER_DAY (24 * LMI_NSECS_PER_HOUR)

#define LMI_NSECS_PER_HOUR (60 * LMI_NSECS_PER_MIN)

#define LMI_NSECS_PER_MIN (60 * LMI_NSECS_PER_SEC)

#define LMI_NSECS_PER_SEC ((LmiTime)(1000000000L))

#define LMI_NSECS_PER_MSEC ((LmiTime)(1000000L))

#define LMI_NSECS_PER_USEC ((LmiTime)(1000L))

#define LMI_USECS_PER_SEC ((LmiTime)(1000000L))

#define LMI_USECS_PER_MSEC ((LmiTime)(1000L))

#define LMI_MSECS_PER_SEC ((LmiTime)(1000L))

#define LMI_TIME_INFINITE ((LmiTime)(LMI_INT64_C(0x7fffffffffffffff)))

LMI_BEGIN_EXTERN_C

/**
   {function:
     {name: LmiTimeSecs}
     {parent: LmiTime}
     {description: Given a number of seconds, return the corresponding
       LmiTime interval value.}
     {prototype: LmiTime LmiTimeSecs(LmiInt64 secs)}
     {parameter:
       {name: secs}
       {description: The number of seconds.}}
     {return: The number of nanoseconds, i.e. the argument times one billion.}
     {note: Undefined if the resulting number of nanoseconds would exceed
       2^63 - 1.}
   }
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeSecs(LmiInt64 secs);


/**
   {function:
     {name: LmiTimeMsecs}
     {parent: LmiTime}
     {description: Given a number of milliseconds, return the corresponding
       LmiTime interval value.}
     {prototype: LmiTime LmiTimeMsecs(LmiInt64 msecs)}
     {parameter:
       {name: msecs}
       {description: The number of milliseconds.}}
     {return: The number of nanoseconds, i.e. the argument times one million.}
     {note: Undefined if the resulting number of nanoseconds would exceed
       2^63 - 1.}
   }
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeMsecs(LmiInt64 msecs);


/**
   {function:
     {name: LmiTimeUsecs}
     {parent: LmiTime}
     {description: Given a number of microseconds, return the corresponding
       LmiTime interval value.}
     {prototype: LmiTime LmiTimeUsecs(LmiInt64 usecs)}
     {parameter:
       {name: usecs}
       {description: The number of microseconds.}}
     {return: The number of nanoseconds, i.e. the argument times one thousand.}
     {note: Undefined if the resulting number of nanoseconds would exceed
       2^63 - 1.}
   }
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeUsecs(LmiInt64 usecs);



/**
   {function:
     {name: LmiTimeGetCurrentWallTime}
     {parent: LmiTime}
     {description: Get an LmiTime value corresponding to the current
       wall-clock time.}
     {prototype: LmiTime LmiTimeGetCurrentWallTime(void)}
	 {return: The current wall-clock time.}
   }
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeGetCurrentWallTime(void);


/**
   {function:
     {name: LmiTimeGetCurrentMonotonicTime}
     {parent: LmiTime}
     {description: Get an LmiTime value corresponding to the current
       system monotonic time.}
     {prototype: LmiTime LmiTimeGetCurrentMonotonicTime(void)}
	 {return: The current system monotonic time.}
   }
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeGetCurrentMonotonicTime(void);

/**
   {function replaced-by="LmiTimeGetElapsedMsecRelativeTo":
     {name: LmiTimeGetElapsedMsec}
     {parent: LmiTime}
     {description: Get the number of milliseconds elapsed since the specified time.}
     {prototype: LmiUint LmiTimeGetElapsedMsec(LmiTime t)}
	 {parameter:
	   {name: t}
	   {description: The timestamp.}}
	 {return: Elapsed time interval in msec.}
   }
*/
LMI_INLINE_DECLARATION LMI_DEPRECATED("Replaced by LmiTimeGetElapsedMsecRelativeTo") LmiUint LmiTimeGetElapsedMsec(LmiTime t);

/**
   {function replaced-by="LmiTimeGetElapsedRelativeTo":
     {name: LmiTimeGetElapsed}
     {parent: LmiTime}
     {description: Get the time interval elapsed since the specified time.}
     {prototype: LmiTime LmiTimeGetElapsed(LmiTime t)}
	 {parameter:
	   {name: t}
	   {description: The timestamp.}}
	 {return: Elapsed time interval in nanosecs.}
   }
*/
LMI_INLINE_DECLARATION LMI_DEPRECATED("Replaced by LmiTimeGetElapsedRelativeTo") LmiTime LmiTimeGetElapsed(LmiTime t);

/**
   {function:
     {name: LmiTimeGetElapsedMsecRelativeTo}
     {parent: LmiTime}
     {description: Get the number of milliseconds elapsed since the specified time, passing the current time explicitly.}
     {prototype: LmiUint LmiTimeGetElapsedMsecRelativeTo(LmiTime curTime, LmiTime t)}
	 {parameter:
	   {name: curTime}
	   {description: The current time.}}
	 {parameter:
	   {name: t}
	   {description: The timestamp.}}
	 {return: Elapsed time interval in msec.}
   }
*/
LMI_INLINE_DECLARATION LmiUint LmiTimeGetElapsedMsecRelativeTo(LmiTime curTime, LmiTime t);

/**
   {function:
     {name: LmiTimeGetElapsedRelativeTo}
     {parent: LmiTime}
     {description: Get the time interval elapsed since the specified time.}
     {prototype: LmiTime LmiTimeGetElapsedRelativeTo(LmiTime curTime, LmiTime t)}
	 {parameter:
	   {name: curTime}
	   {description: The current time.}}
	 {parameter:
	   {name: t}
	   {description: The timestamp.}}
	 {return: Elapsed time interval in nanosecs.}
   }
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeGetElapsedRelativeTo(LmiTime curTime, LmiTime t);


/**
   {function visibility="private":
     {name: LmiTimeGetNtp}
	 {parent: LmiTime}
	 {description: Get an NTP time value -- a value of 2^-32 seconds since
	   January 1, 1900 00:00:00 GMT.}
	 {prototype: LmiUint64 LmiTimeGetNtp(LmiTime t)}
	 {parameter:
	   {name: t}
	   {description: The wall-clock time value to convert to an NTP time.}}
	 {return: An NTP time value.}
   }
*/
LMI_INLINE_DECLARATION LmiUint64 LmiTimeGetNtp(LmiTime t);

/**
	{function:
		{name: LmiTimeConstructFromNtp}
		{parent: LmiTime}
		{description: Construct an LmiTime object with a wall-clock time corresponding to a given NTP time.}
		{prototype: LmiTime* LmiTimeConstructFromNtp(LmiTime* t, LmiUint64 ntp)}
		{parameter:
			{name: t}
			{description: A pointer to the LmiTime object to initialize.}}
		{parameter:
			{name: ntp}
			{description: The NTP time value with which to construct the NTP
				time.}}
		{return: A pointer to the constructed LmiTime object on success,
        	otherwise NULL.}
	}
*/
LMI_INLINE_DECLARATION LmiTime* LmiTimeConstructFromNtp(LmiTime* t, LmiUint64 ntp);

#if LMI_HAVE_STRUCT_TIMEVAL
/**
   {function visibility="private":
     {name: LmiTimeGetRelativeTimevalFromMonotonicTime}
	 {parent: LmiTime}
	 {description: Given a timeout expressed as a monotonic LmiTime, return
	   a struct timeval * corresponding to the relative time until that
	   timeval.}
	 {prototype: struct timeval* LmiTimeGetRelativeTimevalFromMonotonicTime(LmiTime timeout, struct timeval* tv)}
	 {parameter:
	   {name: timeout}
	   {description: An absolute monotonic LmiTime.  As special cases, this
	     can be 0, representing no waiting; or it can be LMI_TIME_INFINITE,
		 representing an indefinite wait.}}
	 {parameter:
	   {name: tv}
	   {description: A pointer to a struct timeval.  If the function does not
	     return NULL, the return value will be a pointer to this structure.}}
	 {return: A struct timeval * representing the relative time until the
	   timeout.  If the timeout indicates a time in the past, this will be
	   a struct timeval with value 0.0s; if the timeout indicates a time
	   further in the future than the maximum value representable in a struct
	   timeval, this will return NULL.  (The values 0 and LMI_TIME_INFINITE are
	   special cases of the former and the latter cases respectively.)}
	 {note: The value returned from this function is an appropriate argument
	   for passing to the POSIX or Windows select() function.}
	 {note: If the thread calling this function is pre-empted between this
	   function\'s internal call to LmiTimeGetMonotonicTime and the use
	   of the returned struct timeval in select(), the select() will end up
	   waiting too long, since the relative timeout starts "late".  This is
	   an unavoidable result of select\'s use of relative timeouts.}
	 {note: This function is only declared and defined if the system has
	   a struct timeval type.}
   }
*/
LMI_INLINE_DECLARATION struct timeval*
LmiTimeGetRelativeTimevalFromMonotonicTime(LmiTime timeout,
										   struct timeval* tv);
#endif

#define LMI_TIME_COMPACTPRINTBUFFERLENGTH 16

/**
{function:
	{name: LmiTimePrintCompact}
	{parent: LmiTime}
	{description: Print a time value as a short, easily readable string. The time will be printed
		with low precision, using units appropriate for its magnitude.}
	{prototype: const char *LmiTimePrintCompact(LmiTime t, char *buf, LmiSizeT len)}
	{parameter: {name: t} {description: A pointer to the LmiTime object to initialize.}}
	{parameter: {name: buf} {description: A buffer that will hold the string.}}
	{parameter: {name: len} {description: The length of the buffer in bytes. Use a buffer of
		at least LMI_TIME_COMPACTPRINTBUFFERLENGTH bytes, otherwise the string may be truncated.}}
	{return: The buffer (buf) that was passed in.}
}
*/
const char *LmiTimePrintCompact(LmiTime t, char *buf, LmiSizeT len);

/**
   {type:
     {name: LmiGregorianTime}
     {parent: LmiTime}
     {description: A time value in the Gregorian calendar, with split out
       date fields.}
     {note: An LmiGregorianTime may represent either UTC or local time,
       depending how it was constructed.}
     {note: LmiGregorianTime is currently a read-only structure.  Modifiers
       may be created for it in the future as needed.}
   }
*/
#if LMI_TIME_USE_POSIX_WALL_TIME_

typedef struct {
  struct tm tm;
  long nanosecs;
} LmiGregorianTime;

/* The offset, in nanoseconds, from the LmiTime epoch to the POSIX epoch. */
#define LMI_TIME_POSIX_EPOCH_OFFSET_ LMI_INT64_C(0)

/* The offset, in seconds, from the NTP epoch (01-01-1900) to the
 * Wall Clock Time epoch (01-01-1970). */
#define LMI_TIME_NTP_EPOCH_OFFSET_ LMI_INT64_C(2208988800)

#elif LMI_TIME_USE_WIN32_WALL_TIME_

typedef struct {
	SYSTEMTIME st;
	long nanosecs_in_ms;
} LmiGregorianTime;

/* FILETIME and LARGE_INTEGER.u have the same representation.  Expressing
   them as a union makes it easier to cast between them, and use the
   LARGE_INTEGER.QuadPart 64-bit field. */
typedef union {
  FILETIME ft;
  LARGE_INTEGER li;
} LmiTimeWin32FileTimeUnion_;

/* Windows's FILETIME structure is a 64-bit count of 100 ns intervals
   since 1601-01-01 00:00:00.000 UTC.
   This is sufficient for describing times up to 30828-09-14 02:48:05.477 UTC.

   However, since LmiTime is a count of ns, not 100 ns intervals, this
   base cannot work for us -- 2^63 ns from 1601-01-01 00:00:00.000 is
   1893-04-11 23:47:16.854.

   As such, we define an offset to the value returned by FILE_TIME, so
   that the resulting epoch is useful.  Specifically, we choose the Unix
   epoch, 1970-01-01 00:00:00 UTC.

   With this epoch value, LmiTime can represent all times from
   1677-09-21 00:12:43.145 UTC to 2262-04-11 23:47:16.854 UTC.
*/
#define LMI_TIME_WIN32_FILE_TIME_OFFSET_ LMI_INT64_C(116444736000000000)

/* The offset, in nanoseconds, from the LmiTime epoch to the POSIX epoch. */
#define LMI_TIME_POSIX_EPOCH_OFFSET_ LMI_INT64_C(0)

#define LMI_TIME_NTP_EPOCH_OFFSET_ LMI_INT64_C(2208988800)

LMI_INLINE_DECLARATION LmiTime LmiTimeGetFromWin32FileTime_(LmiTimeWin32FileTimeUnion_ ft);
LMI_INLINE_DECLARATION LmiTimeWin32FileTimeUnion_ LmiTimeGetWin32FileTime_(LmiTime t);

#endif

#if LMI_TIME_USE_WIN32_MONOTONIC_TIME_

extern double LmiTimeWin32MonotonicTimeClockInterval_;

#elif LMI_TIME_USE_MACH_MONOTONIC_TIME_

extern double LmiTimeMachMonotonicTimeClockInterval_;

#elif LMI_TIME_USE_POSIX_MONOTONIC_TIME_

extern clockid_t LmiTimeMonotonicClockId_;

#endif


/**
   {function:
     {name: LmiGregorianTimeConstruct}
     {parent: LmiGregorianTime}
     {description: Construct an LmiGregorianTime value, representing
       the time in the system timezone, corresponding to a given wall clock
       time value.}
     {prototype: LmiGregorianTime* LmiGregorianTimeConstruct(LmiGregorianTime* gt, LmiTime systemTime)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object to construct.}}
     {parameter:
       {name: systemTime}
       {description: The system time value for which to construct a
         corresponding gregorian time.}}
     {return: gt on success, else NULL.}
   }
*/
LMI_INLINE_DECLARATION LmiGregorianTime* LmiGregorianTimeConstruct(LmiGregorianTime* gt,
                                             LmiTime systemTime);

/**
	{function:
		{name: LmiGregorianTimeConstructCopy}
		{parent: LmiGregorianTime}
		{description: Construct a new LmiGregorianTime object as a copy of an
			existing one.}
		{prototype: LmiGregorianTime* LmiGregorianTimeConstructCopy(LmiGregorianTime* dst, const LmiGregorianTime* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiGregorianTime object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiGregorianTime object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiGregorianTime construction will not fail.}
	}
*/
LMI_INLINE_DECLARATION LmiGregorianTime* LmiGregorianTimeConstructCopy(LmiGregorianTime* dst, const LmiGregorianTime* src);


/**
   {function:
     {name: LmiGregorianTimeConstructUTC}
     {parent: LmiGregorianTime}
     {description: Construct an LmiGregorianTime value, representing
       the time in Coordinated Universal Time, corresponding to a given
       wall clock time value.}
     {prototype: LmiGregorianTime* LmiGregorianTimeConstructUTC(LmiGregorianTime* gt, LmiTime systemTime)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object to construct.}}
     {parameter:
       {name: systemTime}
       {description: The system time value for which to construct a
         corresponding gregorian time.}}
     {return: gt on success, else NULL.}
   }
*/
LMI_INLINE_DECLARATION LmiGregorianTime* LmiGregorianTimeConstructUTC(LmiGregorianTime* gt,
                                                LmiTime systemTime);


/**
   {function:
     {name: LmiGregorianTimeConstructFields}
     {parent: LmiGregorianTime}
     {description: Construct an LmiGregorianTime value with explicitly-set field values.}
     {prototype: LmiGregorianTime* LmiGregorianTimeConstructFields(LmiGregorianTime* gt, LmiInt year, LmiInt month, LmiInt monthDay, LmiInt hour, LmiInt minute, LmiInt second, LmiTime nanosecond)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object to construct.}}
	 {parameter: {name: year} {description: The year value to set for the Gregorian time.}}
	 {parameter: {name: month} {description: The month value to set for the Gregorian time. This must be in the range 1 - 12.}}
	 {parameter: {name: monthDay} {description: The day-of-the-month value to set for the Gregorian time. This must be in the range 1 - 31, and must be a valid month day for the month specified.}}
	 {parameter: {name: hour} {description: The hour value to set for the Gregorian time. This must be in the range 0 - 23.}}
	 {parameter: {name: minute} {description: The minute value to set for the Gregorian time. This must be in the range 0 - 59.}}
	 {parameter: {name: second} {description: The second value to set for the Gregorian time. This must be in the range 0 - 60 (allowing for leap seconds.)}}
	 {parameter: {name: nanosecond} {description: The nanosecond value to set for the Gregorian time. This must be in the range 0 - 999 999 999.)}}
     {return: gt on success, else NULL.}
	 {note: The constructor does not validate whether a leap second value represents an actual leap second.  It also does not validate whether the time specified actually exists (as opposed to, say, taking place during the spring-forward interval of the local time zone).}
   }
*/
LMI_INLINE_DECLARATION LmiGregorianTime* LmiGregorianTimeConstructFields(LmiGregorianTime* gt,
	LmiInt year, LmiInt month, LmiInt monthDay, LmiInt hour, LmiInt minute, LmiInt second, LmiTime nanosecond);

/**
   {function:
     {name: LmiGregorianTimeConstructCStr}
     {parent: LmiGregorianTime}
     {description: Construct an LmiGregorianTime value from a NUL-terminated C string representation.}
	 {prototype: LmiGregorianTime* LmiGregorianTimeConstructCStr(LmiGregorianTime* gt, const char* str)}
	 {parameter: {name: gt} {description: The LmiGregorianTime object to construct.}}
	 {parameter: {name: str}
	   {description: A NUL-terminated C string representation of a Gregorian time, in ISO 8601 format, i.e. the format
	   output by LmiGregorianTimeGetAsString, with some variation.}}
	 {return: gt on success, NULL on failure.}
	 {note: This function accepts the subset of ISO 8601 syntax defined by RFC 3339.  The separator between the date and
	   time may be either the capital letter T or a space.}
	 {note: If the string contains a numeric timezone offset, the resulting constructed gregorian time will be adjusted
	   to UTC by the amount of the offset.}
  }
*/
LmiGregorianTime* LmiGregorianTimeConstructCStr(LmiGregorianTime* gt, const char* str);


/**
   {function:
     {name: LmiGregorianTimeDestruct}
     {parent: LmiGregorianTime}
     {description: Destruct an LmiGregorianTime object.}
     {prototype: void LmiGregorianTimeDestruct(LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object to destruct.}}
   }
*/
LMI_INLINE_DECLARATION void LmiGregorianTimeDestruct(LmiGregorianTime* gt);

/**
	{function:
		{name: LmiGregorianTimeAssign}
		{parent: LmiGregorianTime}
		{description: Assign the value of one LmiGregorianTime object to another one.}
		{prototype: LmiGregorianTime* LmiGregorianTimeAssign(LmiGregorianTime* dst, const LmiGregorianTime* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiGregorianTime object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiGregorianTime object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiGregorianTime assignment will not fail.}
	}
*/
LMI_INLINE_DECLARATION LmiGregorianTime* LmiGregorianTimeAssign(LmiGregorianTime* dst, const LmiGregorianTime* src);


/**   
	{function:
		{name: LmiGregorianTimeEqual}
		{parent: LmiGregorianTime}
		{description: Compare the values of two LmiGregorianTime objects for
			equality.}
		{prototype: LmiBool LmiGregorianTimeEqual(const LmiGregorianTime* a, const LmiGregorianTime* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiGregorianTime object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiGregorianTime object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
*/
LmiBool LmiGregorianTimeEqual(const LmiGregorianTime* a, const LmiGregorianTime* b);


/**   
	{function:
		{name: LmiGregorianTimeLess}
		{parent: LmiGregorianTime}
		{description: Compare the values of two LmiGregorianTime objects for
			ordering.}
		{prototype: LmiBool LmiGregorianTimeLess(const LmiGregorianTime* a, const LmiGregorianTime* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiGregorianTime object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiGregorianTime object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}
*/
LmiBool LmiGregorianTimeLess(const LmiGregorianTime* a, const LmiGregorianTime* b);

/**   
	{function:
		{name: LmiGregorianTimeSwap}
		{parent: LmiGregorianTime}
		{description: Swap the contents of two LmiGregorianTime objects.}
		{prototype: LmiBool LmiGregorianTimeSwap(LmiGregorianTime* a, LmiGregorianTime* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiGregorianTime object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiGregorianTime object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiGregorianTime swapping will not fail.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiGregorianTimeSwap(LmiGregorianTime* a, LmiGregorianTime* b);

/**
   {function:
     {name: LmiGregorianTimeGetYear}
     {parent: LmiGregorianTime}
     {description: Get the year value from an LmiGregorianTime.}
     {prototype: LmiInt LmiGregorianTimeGetYear(const LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object from which to obtain the year.}}
     {return: The LmiGregorianTime object\'s year field.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiGregorianTimeGetYear(const LmiGregorianTime* gt);


/**
   {function:
     {name: LmiGregorianTimeGetMonth}
     {parent: LmiGregorianTime}
     {description: Get the month value from an LmiGregorianTime.}
     {prototype: LmiInt LmiGregorianTimeGetMonth(const LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object from which to obtain the month.}}
     {return: The LmiGregorianTime object\'s month field, a number in the
       range 1 - 12.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiGregorianTimeGetMonth(const LmiGregorianTime* gt);


/**
   {function:
     {name: LmiGregorianTimeGetMonthDay}
     {parent: LmiGregorianTime}
     {description: Get the day-of-the-month value from an LmiGregorianTime.}
     {prototype: LmiInt LmiGregorianTimeGetMonthDay(const LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object from which to obtain the year.}}
     {return: The LmiGregorianTime object\'s day-of-the-month field, a number
       in the range 1 - 31.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiGregorianTimeGetMonthDay(const LmiGregorianTime* gt);


/**
   {function:
     {name: LmiGregorianTimeGetHour}
     {parent: LmiGregorianTime}
     {description: Get the hour value from an LmiGregorianTime.}
     {prototype: LmiInt LmiGregorianTimeGetHour(const LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object from which to obtain the hour.}}
     {return: The LmiGregorianTime object\'s hour field, a number in the
       range 0 - 23.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiGregorianTimeGetHour(const LmiGregorianTime* gt);


/**
   {function:
     {name: LmiGregorianTimeGetMinute}
     {parent: LmiGregorianTime}
     {description: Get the minute value from an LmiGregorianTime.}
     {prototype: LmiInt LmiGregorianTimeGetMinute(const LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object from which to obtain the minute.}}
     {return: The LmiGregorianTime object\'s minute field, a number in the
       range 0 - 59.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiGregorianTimeGetMinute(const LmiGregorianTime* gt);


/**
   {function:
     {name: LmiGregorianTimeGetSecond}
     {parent: LmiGregorianTime}
     {description: Get the second value from an LmiGregorianTime.}
     {prototype: LmiInt LmiGregorianTimeGetSecond(const LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object from which to obtain the second.}}
     {return: The LmiGregorianTime object\'s second field, a number in the
       range 0 - 60 (allowing for leap seconds).}
     {note: Whether the LmiGregorianTime object actually supports leap seconds
       is system-dependent.}
   }
*/
LMI_INLINE_DECLARATION LmiInt LmiGregorianTimeGetSecond(const LmiGregorianTime* gt);


/**
   {function:
     {name: LmiGregorianTimeGetNanosecond}
     {parent: LmiGregorianTime}
     {description: Get the nanosecond value from an LmiGregorianTime.}
     {prototype: LmiTime LmiGregorianTimeGetNanosecond(const LmiGregorianTime* gt)}
     {parameter:
       {name: gt}
       {description: The LmiGregorianTime object from which to obtain the nanoseconds.}}
     {return: The LmiGregorianTime object\'s nanosecond field, a number in the
       range 0 - 999 999 999.}
   }
*/
LMI_INLINE_DECLARATION LmiTime LmiGregorianTimeGetNanosecond(const LmiGregorianTime* gt);


/**
   {function:
     {name: LmiGregorianTimeGetAsString}
     {parent: LmiGregorianTime}
     {description: Get a string representation of a given gregorian time.}
     {prototype: char* LmiGregorianTimeGetAsString(const LmiGregorianTime* t, char* buf, LmiSizeT buflen)}
     {parameter:
       {name: t}
       {description: The time to represent.}}
     {parameter:
       {name: buf}
       {description: The buffer into which to print the time.}}
     {parameter:
       {name: buflen}
       {description: The length of the buffer pointed to by buflen.  This
         should be at least 24 bytes (see below).}}
     {return:  A pointer to the buffer buf, or NULL if the buffer was
       too small.}
     {note: The outputted time will be formatted as "YYYY-MM-DD HH:MM:SS.sss",
       i.e. ISO 8601 date format with millisecond precision.  As such, the
       length of the passed-in buffer should be at least 24, counting room
       for the terminating NUL byte.  (If the year is outside the range
       0001 - 9999 CE, further bytes will be necessary.)}
   }
*/
char* LmiGregorianTimeGetAsString(const LmiGregorianTime* t,
                                   char* buf, LmiSizeT buflen);


/**
  {function:
    {name: LmiGregorianTimeGetLocalTime}
	{parent: LmiGregorianTime}
	{description: Get the wall-clock time corresponding to a gregorian time, interpreted as being in the
	  system local timezone.}
	{prototype: LmiTime LmiGregorianTimeGetLocalTime(const LmiGregorianTime* gt)}
	{parameter: {name: gt} {description: The gregorian time to get as local time.}}
	{return: The wall-clock time corresponding to the gregorian time value, interpreted as a local time, or LMI_TIME_INFINITE on failure.}
	{note: This function may fail if the time represented by the gregorian time is out of the range supported by the underlying system time APIs.}
	{note: If the time represented by the gregorian time does not occur (i.e. would occur during the local time zone's spring-forward interval) the result is unspecified -- the function may fail, or may return a nearby time (e.g. adjusted for the zone change).  If the time represented by the gregorian time occurs more than once (i.e. would occur during the local time zone's fall-back interval) the result will be one of the instances the time corresponds to the requested gregorian time, but it is unspecified which one.}
}
*/
LMI_INLINE_DECLARATION LmiTime LmiGregorianTimeGetLocalTime(const LmiGregorianTime* gt);


/**
  {function:
    {name: LmiGregorianTimeGetUTCTime}
	{parent: LmiGregorianTime}
	{description: Get the wall-clock time corresponding to a gregorian time, interpreted as being in Universal Coordinated Time (UTC).}
	{prototype: LmiTime LmiGregorianTimeGetUTCTime(const LmiGregorianTime* gt)}
	{parameter: {name: gt} {description: The gregorian time to get as UTC time.}}
	{return: The wall-clock time corresponding to the gregorian time value, interpreted as a UTC time, or LMI_TIME_INFINITE on failure.}
	{note: This function may fail if the time represented by the gregorian time is out of the range supported by the underlying system time APIs.}
}
*/
LMI_INLINE_DECLARATION LmiTime LmiGregorianTimeGetUTCTime(const LmiGregorianTime* gt);


/* Internal - platform-independent field validation for LmiGregorianTimeConstructFromFields */
LmiBool LmiGregorianTimeValidateFields_(LmiInt year, LmiInt month, LmiInt monthDay, LmiInt hour, LmiInt minute, LmiInt second, LmiTime nanosecond);


/**
	{function:
		{name: LmiTimeConstruct}
		{parent: LmiTime}
		{description: Construct a default instance of an LmiTime object.}
		{prototype: LmiTime* LmiTimeConstruct(LmiTime* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiTime object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiTime object is initialized with the value 0.
			LmiTime construction will not fail.}
	}

	{function:
		{name: LmiTimeConstructCopy}
		{parent: LmiTime}
		{description: Construct a new LmiTime object as a copy of an
			existing one.}
		{prototype: LmiTime* LmiTimeConstructCopy(LmiTime* dst, const LmiTime* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiTime object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiTime object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiTime construction will not fail.}
	}

	{function:
		{name: LmiTimeDestruct}
		{parent: LmiTime}
		{description: Destruct an LmiTime object.}
		{prototype: void LmiTimeDestruct(LmiTime* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiTime object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiTimeAssign}
		{parent: LmiTime}
		{description: Assign the value of one LmiTime object to another one.}
		{prototype: LmiTime* LmiTimeAssign(LmiTime* dst, const LmiTime* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiTime object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiTime object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiTime assignment will not fail.}
	}
   
	{function:
		{name: LmiTimeEqual}
		{parent: LmiTime}
		{description: Compare the values of two LmiTime objects for
			equality.}
		{prototype: LmiBool LmiTimeEqual(const LmiTime* a, const LmiTime* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiTime object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiTime object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiTimeLess}
		{parent: LmiTime}
		{description: Compare the values of two LmiTime objects for
			ordering.}
		{prototype: LmiBool LmiTimeLess(const LmiTime* a, const LmiTime* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiTime object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiTime object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiTimeSwap}
		{parent: LmiTime}
		{description: Swap the contents of two LmiTime objects.}
		{prototype: LmiBool LmiTimeSwap(LmiTime* a, LmiTime* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiTime object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiTime object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiTime swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiTime)

/**
	{type:
		{name: LmiTimeRange}
		{parent: Os}
		{include: Lmi/Os/LmiTime.h}
		{description:
			A time range class used to represent a range of time intervals.}
 		{member: 
 			{name: begin}
			{type: LmiTime}
 			{description: The first time interval of the range.}}
 		{member: 
 			{name: end}
			{type: LmiTime}
 			{description: The last time interval of the range.}}
	}
*/
typedef struct
{
	LmiTime begin;
	LmiTime end;
} LmiTimeRange;

/**
	{function:
		{name: LmiTimeRangeConstruct}
		{parent: LmiTimeRange}
		{description: Constructs an LmiTimeRange object.}
		{prototype: LmiTimeRange* LmiTimeRangeConstruct(LmiTimeRange *x, LmiTime begin, LmiTime end)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object to construct.}}
		{parameter:
			{name: begin}
			{description: The first interval of the time range.}}
		{parameter:
			{name: end}
			{description: The last interval of the time range.}}
		{return: Returns a pointer to the constructed object or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiTimeRange* LmiTimeRangeConstruct(LmiTimeRange *x, LmiTime begin, LmiTime end);

/**
	{function:
		{name: LmiTimeRangeDestruct}
		{parent: LmiTimeRange}
		{description: Destructs an LmiTimeRange object.}
		{prototype: void LmiTimeRangeDestruct(LmiTimeRange *x)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object to destruct.}}
	}
*/
LMI_INLINE_DECLARATION void LmiTimeRangeDestruct(LmiTimeRange *x);

/**
	{function:
		{name: LmiTimeRangeConstructCopy}
		{parent: LmiTimeRange}
		{description: Constructs an LmiTimeRange object as a copy of another object.}
		{prototype: LmiTimeRange* LmiTimeRangeConstructCopy(LmiTimeRange *x, const LmiTimeRange *y)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object to construct.}}
		{parameter:
			{name: y}
			{description: The LmiTimeRange object from which the object need to be constructed.}}
		{return: Returns a pointer to the constructed object or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiTimeRange* LmiTimeRangeConstructCopy(LmiTimeRange *x, const LmiTimeRange *y);

/**
	{function:
		{name: LmiTimeRangeAssign}
		{parent: LmiTimeRange}
		{description: Assigns an LmiTimeRange object from another object.}
		{prototype: LmiTimeRange* LmiTimeRangeAssign(LmiTimeRange *x, const LmiTimeRange *y)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object to assign.}}
		{parameter:
			{name: y}
			{description: The LmiTimeRange object from which the object need to be assigned.}}
		{return: Returns a pointer to the assigned object or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiTimeRange* LmiTimeRangeAssign(LmiTimeRange *x, const LmiTimeRange *y);

/**
	{function:
		{name: LmiTimeRangeSwap}
		{parent: LmiTimeRange}
		{description: Swaps an LmiTimeRange object with another LmiTimeRange object.}
		{prototype: void LmiTimeRangeSwap(LmiTimeRange *x, LmiTimeRange *y)}
		{parameter:
			{name: x}
			{description: A LmiTimeRange object to swap.}}
		{parameter:
			{name: y}
			{description: A LmiTimeRange object to swap.}}
}
*/
LMI_INLINE_DECLARATION void LmiTimeRangeSwap(LmiTimeRange *x, LmiTimeRange *y);

/**
	{function:
		{name: LmiTimeRangeEqual}
		{parent: LmiTimeRange}
		{description: Determines the equality of two LmiTimeRange objects.}
		{prototype: LmiBool LmiTimeRangeEqual(const LmiTimeRange *x, const LmiTimeRange *y)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object.}}
		{parameter:
			{name: y}
			{description: The LmiTimeRange object.}}
		{return: Returns LMI_TRUE if equal or LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiTimeRangeEqual(const LmiTimeRange *x, const LmiTimeRange *y);

/**
	{function:
		{name: LmiTimeRangeLess}
		{parent: LmiTimeRange}
		{description: Determines whether an LmiTimeRange object is less than another LmiTimeRange object.}
		{prototype: LmiBool LmiTimeRangeLess(const LmiTimeRange *x, const LmiTimeRange *y)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object.}}
		{parameter:
			{name: y}
			{description: The LmiTimeRange object.}}
		{return: Returns LMI_TRUE if less or LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiTimeRangeLess(const LmiTimeRange *x, const LmiTimeRange *y);


/**
	{function:
		{name: LmiTimeRangeBegin}
		{parent: LmiTimeRange}
		{description: Gets the first value of the time range.}
		{prototype: LmiTime LmiTimeRangeBegin(const LmiTimeRange *x)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object.}}
		{return: Returns the first value of the time range.}
}
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeRangeBegin(const LmiTimeRange *x);

/**
	{function:
		{name: LmiTimeRangeEnd}
		{parent: LmiTimeRange}
		{description: Gets the last value of the time range.}
		{prototype: LmiTime LmiTimeRangeEnd(const LmiTimeRange *x)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object.}}
		{return: Returns the last value of the time range.}
}
*/
LMI_INLINE_DECLARATION LmiTime LmiTimeRangeEnd(const LmiTimeRange *x);

/**
	{function:
		{name: LmiTimeRangeIsValid}
		{parent: LmiTimeRange}
		{description: Determines whether an LmiTimeRange object is valid.}
		{prototype: LmiBool LmiTimeRangeIsValid(const LmiTimeRange *x)}
		{parameter:
			{name: x}
			{description: The LmiTimeRange object.}}
		{return: Returns LMI_TRUE if the time range represents a valid range or LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiTimeRangeIsValid(const LmiTimeRange *x);

/**
	{function:
		{name: LmiTimeRangeIntersects}
		{parent: LmiTimeRange}
		{description: Determines whether an LmiTimeRange object intersects another LmiTimeRange object.}
		{prototype: LmiBool LmiTimeRangeIntersects(const LmiTimeRange *x, const LmiTimeRange *y)}
		{parameter:
			{name: x}
			{description: A LmiTimeRange object.}}
		{parameter:
			{name: y}
			{description: A LmiTimeRange object.}}
		{return: Returns LMI_TRUE if the time ranges intersect or LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiTimeRangeIntersects(const LmiTimeRange *x, const LmiTimeRange *y);
/**
	{function:
		{name: LmiTimeRangeSubsumes}
		{parent: LmiTimeRange}
		{description: Determines whether an time range {code:x} subsumes (contains) time range {code:y}.}
		{prototype: LmiBool LmiTimeRangeSubsumes(const LmiTimeRange *x, const LmiTimeRange *y)}
		{parameter:
			{name: x}
			{description: A LmiTimeRange object.}}
		{parameter:
			{name: y}
			{description: A LmiTimeRange object.}}
		{return: Return LMI_TRUE if {code:x} subsumes (contains) {code:y} or LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiTimeRangeSubsumes(const LmiTimeRange *x, const LmiTimeRange *y);

/**
	{function:
		{name: LmiTimeRangeIntersection}
		{parent: LmiTimeRange}
		{description: Computes the intersection of two LmiTimeRange objects.}
		{prototype: void LmiTimeRangeIntersection(const LmiTimeRange *x, const LmiTimeRange *y, LmiTimeRange *result)}
		{parameter:
			{name: x}
			{description: A LmiTimeRange object.}}
		{parameter:
			{name: y}
			{description: A LmiTimeRange object.}}
		{parameter:
			{name: result}
			{description: The resulting LmiTimeRange object. If {code: x} and {code: y} do not intersect the {code: result} will be invalid.  Use LmiTimeRangeIsValid to determine this condition.}}
}
*/
LMI_INLINE_DECLARATION void LmiTimeRangeIntersection(const LmiTimeRange *x, const LmiTimeRange *y, LmiTimeRange *result);

/**
	{function:
		{name: LmiTimeRangeUnion}
		{parent: LmiTimeRange}
		{description: Computes the union of two LmiTimeRange objects.}
		{prototype: void LmiTimeRangeUnion(const LmiTimeRange *x, const LmiTimeRange *y, LmiTimeRange *result)}
		{parameter:
			{name: x}
			{description: A LmiTimeRange object.}}
		{parameter:
			{name: y}
			{description: A LmiTimeRange object.}}
		{parameter:
			{name: result}
			{description: The resulting LmiTimeRange object.}}
}
*/
LMI_INLINE_DECLARATION void LmiTimeRangeUnion(const LmiTimeRange *x, const LmiTimeRange *y, LmiTimeRange *result);

Declare_LmiVector(LmiTimeRange)
Declare_LmiVectorEqual(LmiTimeRange)

/* "Static" member functions */
LmiBool LmiTimeInitialize(void);

/* Threshold for warning about things blocking. */
#define LMI_TIME_WARNING_THRESHOLD LmiTimeMsecs(50)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiTimeInline.h>
#endif

#endif /* LMI_TIME_H_ */
