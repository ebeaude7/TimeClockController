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

#define DAYS_IN_A_WEEK 7
#define HOURS_IN_A_DAY 24
#define A_MINUTE_IN_SEC 60
#define An_HOUR_IN_SEC 60 * A_MINUTE_IN_SEC // 3600
#define A_DAY_IN_SEC 24 * An_HOUR_IN_SEC // 86400

// alarm selection operation
uint8_t addOneDay (uint8_t day);
uint8_t substractOneDay (uint8_t day);
uint8_t addOneHour (uint8_t hour);
uint8_t getDaysDiff(uint8_t alarmDay, uint8_t today);

#endif