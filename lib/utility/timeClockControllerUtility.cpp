/*
 * File: timeClockControllerUtility.cpp
 * Project: src
 * Created Date: Monday, October 25th 2021, 1:26:49 am
 * Author: Eric Beaudet (ebeaudet@noovelia.com)
 * 
 * Copyright (c) 2021 EJS
 */

#include "timeClockControllerUtility.h"

uint8_t addOneDay (uint8_t day) {
    if (day == 6) return 0;
    return day + 1;
}

uint8_t substractOneDay (uint8_t day) {
    if (day == 0) return 6;
    return day - 1;
}


uint8_t addOneHour (uint8_t hour) {
    if (hour == 23) return 0;
    return hour + 1;
}

uint8_t getDaysDiff(uint8_t alarmDay, uint8_t today) {
    uint8_t daysDiff;

    if (alarmDay < today) {
        daysDiff = DAYS_IN_A_WEEK - alarmDay + today;
    } else {
        daysDiff = alarmDay - today;
    }

    return daysDiff;
}