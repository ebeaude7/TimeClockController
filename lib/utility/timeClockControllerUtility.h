/*
 * File: timeClockControllerUtility.h
 * Project: src
 * Created Date: Monday, October 25th 2021, 1:26:14 am
 * Author: Eric Beaudet (ebeaudet@noovelia.com)
 * 
 * Copyright (c) 2021 EJS
 */
#ifndef _TIME_CLOCK_UTILITY_CONTROLLER_H_
#define _TIME_CLOCK_UTILITY_CONTROLLER_H_

#include <stdint.h>
#include "scheduledAlarm.h"

#define DAYS_IN_A_WEEK 7
#define HOURS_IN_A_DAY 24
#define MINUTE_IN_SEC 60
#define HOUR_IN_SEC 3600 
#define DAY_IN_SEC 86400

// alarm selection operation
uint8_t addOneDay (uint8_t day);
uint8_t substractOneDay (uint8_t day);
uint8_t addOneHour (uint8_t hour);
uint8_t substractOneHour (uint8_t hour);
uint8_t substractOneMinute (uint8_t minute);
uint8_t getDaysDiff(uint8_t alarmDay, uint8_t today);
uint8_t getHoursDiff(uint8_t alarmHour, uint8_t hour);
uint8_t getMinutesOrSecondDiff(uint8_t alarmMinute, uint8_t minute);

uint8_t getDaysFromNow(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute);
uint8_t getHoursFromNow(const scheduledAlarm_t& alarm, uint8_t hour, uint8_t minute); 
uint8_t getMinutesFromNow(const scheduledAlarm_t& alarm, uint8_t minute);
uint8_t getSecondsfromNow(uint8_t second);
int32_t getSecondsFromAlarm(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second); 

#endif