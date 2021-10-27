/*
 * File: timeClockControllerCalc.h
 * Project: utility
 * Created Date: Tuesday, October 26th 2021, 8:17:29 pm
 * 
 * Copyright (c) 2021 Eric Beaudet
 * 
 * Utility to calculate seconds to sunday 0h00:00 
 */
#ifndef _TIME_CLOCK_CONTROLLER_CALC_H_
#define _TIME_CLOCK_CONTROLLER_CALC_H_

#include <stdint.h>
#include "scheduledAlarm.h"

#define M_IN_SEC 60
#define H_IN_SEC 3600 
#define D_IN_SEC 86400
#define W_IN_SEC 604800

#define D_IN_WEEK 7
#define H_IN_DAY 24
#define M_IN_HOUR 60
#define S_IN_MINUTE 60



int32_t getNumberOfSeconds(const scheduledAlarm_t& alarm, int32_t second);

/**
 * return the number of seconds to alarm 
 */
int32_t getSecondstoAlarm (const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second);

#endif