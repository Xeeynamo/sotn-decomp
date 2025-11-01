/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psprtc.h - Prototypes for the sceRtc library
 *
 * Function returns marked with (?) have not been tested.
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __PSPRTC_H__
#define __PSPRTC_H__

#include <time.h>
#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

enum pspRtcCheckValidErrors {
	PSP_TIME_INVALID_YEAR = -1,
	PSP_TIME_INVALID_MONTH = -2,
	PSP_TIME_INVALID_DAY = -3,
	PSP_TIME_INVALID_HOUR = -4,
	PSP_TIME_INVALID_MINUTES = -5,
	PSP_TIME_INVALID_SECONDS = -6,
	PSP_TIME_INVALID_MICROSECONDS = -7
};

/**
 * Get the resolution of the tick counter
 *
 * @return # of ticks per second
 */
u32 sceRtcGetTickResolution();

/**
 * Get current tick count
 *
 * @param tick - pointer to u64 to receive tick count
 * @return 0 on success, < 0 on error
 */
int sceRtcGetCurrentTick(u64 *tick);

/**
 * Get current tick count, adjusted for local time zone
 *
 * @param time - pointer to ScePspDateTime struct to receive time
 * @param tz - time zone to adjust to (minutes from UTC)
 * @return 0 on success, < 0 on error
 */
int sceRtcGetCurrentClock(ScePspDateTime *time, int tz);

/**
 * Get current local time into a ScePspDateTime struct
 *
 * @param time - pointer to ScePspDateTime struct to receive time
 * @return 0 on success, < 0 on error
 */
int sceRtcGetCurrentClockLocalTime(ScePspDateTime *time);

/**
 * Convert a UTC-based tickcount into a local time tick count
 *
 * @param tickUTC - pointer to u64 tick in UTC time
 * @param tickLocal - pointer to u64 to receive tick in local time
 * @return 0 on success, < 0 on error
 */
int sceRtcConvertUtcToLocalTime(const u64* tickUTC, u64* tickLocal);

/**
 * Convert a local time based tickcount into a UTC-based tick count
 *
 * @param tickLocal - pointer to u64 tick in local time
 * @param tickUTC - pointer to u64 to receive tick in UTC based time
 * @return 0 on success, < 0 on error
 */
int sceRtcConvertLocalTimeToUTC(const u64* tickLocal, u64* tickUTC);

/**
 * Check if a year is a leap year
 *
 * @param year - year to check if is a leap year
 * @return 1 on leapyear, 0 if not
 */
int sceRtcIsLeapYear(int year);

/**
 * Get number of days in a specific month
 *
 * @param year - year in which to check (accounts for leap year)
 * @param month - month to get number of days for
 * @return # of days in month, <0 on error (?)
 */
int sceRtcGetDaysInMonth(int year, int month);

/**
 * Get day of the week for a date
 *
 * @param year - year in which to check (accounts for leap year)
 * @param month - month that day is in
 * @param day - day to get day of week for
 * @return day of week with 0 representing Monday
 */
int sceRtcGetDayOfWeek(int year, int month, int day);

/**
 * Validate pspDate component ranges
 *
 * @param date - pointer to pspDate struct to be checked
 * @return 0 on success, one of ::pspRtcCheckValidErrors on error
 */
int sceRtcCheckValid(const ScePspDateTime* date);

/**
 * Set a ScePspDateTime struct based on ticks
 *
 * @param date - pointer to ScePspDateTime struct to set
 * @param tick - pointer to ticks to convert
 * @return 0 on success, < 0 on error
 */
int sceRtcSetTick(ScePspDateTime* date, const u64* tick);

/**
 * Set ticks based on a ScePspDateTime struct
 *
 * @param date - pointer to ScePspDateTime to convert
 * @param tick - pointer to tick to set
 * @return 0 on success, < 0 on error
 */
int sceRtcGetTick(const ScePspDateTime* date, u64 *tick);

/**
 * Compare two ticks
 *
 * @param tick1 - pointer to first tick
 * @param tick2 - poiinter to second tick
 * @return 0 on equal, <0 when tick1 < tick2, >0 when tick1 > tick2
 */
int sceRtcCompareTick(const u64* tick1, const u64* tick2);

/**
 * Add two ticks
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numTicks - number of ticks to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddTicks(u64* destTick, const u64* srcTick, u64 numTicks);

/**
 * Add an amount of ms to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numMS - number of ms to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddMicroseconds(u64* destTick, const u64* srcTick, u64 numMS);

/**
 * Add an amount of seconds to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numSecs - number of seconds to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddSeconds(u64* destTick, const u64* srcTick, u64 numSecs);

/**
 * Add an amount of minutes to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numMins - number of minutes to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddMinutes(u64* destTick, const u64* srcTick, u64 numMins);

/**
 * Add an amount of hours to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numHours - number of hours to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddHours(u64* destTick, const u64* srcTick, int numHours);

/**
 * Add an amount of days to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numDays - number of days to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddDays(u64* destTick, const u64* srcTick, int numDays);

/**
 * Add an amount of weeks to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numWeeks - number of weeks to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddWeeks(u64* destTick, const u64* srcTick, int numWeeks);


/**
 * Add an amount of months to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numMonths - number of months to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddMonths(u64* destTick, const u64* srcTick, int numMonths);

/**
 * Add an amount of years to a tick
 *
 * @param destTick - pointer to tick to hold result
 * @param srcTick - pointer to source tick
 * @param numYears - number of years to add
 * @return 0 on success, <0 on error
 */
int sceRtcTickAddYears(u64* destTick, const u64* srcTick, int numYears);

int sceRtcSetTime_t(ScePspDateTime* date, const time_t time);
int sceRtcGetTime_t(const ScePspDateTime* date, time_t *time);
int sceRtcSetDosTime(ScePspDateTime* date, u32 dosTime);
int sceRtcGetDosTime(ScePspDateTime* date, u32 dosTime);
int sceRtcSetWin32FileTime(ScePspDateTime* date, u64* win32Time);
int sceRtcGetWin32FileTime(ScePspDateTime* date, u64* win32Time);

int sceRtcParseDateTime(u64 *destTick, const char *dateString);

/**
 * Format Tick-representation UTC time in RFC2822 format
 */
int sceRtcFormatRFC2822(char *pszDateTime, const u64 *pUtc, int iTimeZoneMinutes);

/**
 * Format Tick-representation UTC time in RFC2822 format
 */
int sceRtcFormatRFC2822LocalTime(char *pszDateTime, const u64 *pUtc);

/**
 * Format Tick-representation UTC time in RFC3339(ISO8601) format
 */
int sceRtcFormatRFC3339(char *pszDateTime, const u64 *pUtc, int iTimeZoneMinutes);

/**
 * Format Tick-representation UTC time in RFC3339(ISO8601) format
 */
int sceRtcFormatRFC3339LocalTime(char *pszDateTime, const u64 *pUtc);

/**
 * Parse time information represented in RFC3339 format
 */
int sceRtcParseRFC3339(u64 *pUtc, const char *pszDateTime);

#ifdef __cplusplus
}
#endif

#endif
