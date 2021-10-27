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

uint8_t substractOneHour (uint8_t hour) {
    if (hour == 0) return 23;
    return hour - 1;
}

uint8_t substractOneMinute (uint8_t minute) {
    if (minute == 0) return 59;
    return minute - 1;
}

uint8_t getDaysDiff(uint8_t alarmDay, uint8_t today) {
    uint8_t daysDiff;

    if (alarmDay < today) {
        daysDiff = DAYS_IN_A_WEEK - alarmDay + today;
    } else {
        daysDiff = alarmDay - today;
    }

    // handle wrap around
    if (daysDiff > DAYS_IN_A_WEEK) {
        daysDiff = DAYS_IN_A_WEEK - (daysDiff -DAYS_IN_A_WEEK);
    }

    return daysDiff;
}

uint8_t getHoursDiff(uint8_t alarmHour, uint8_t hour) {
    uint8_t hoursDiff;

    if (alarmHour < hour) {
        hoursDiff = HOURS_IN_A_DAY - alarmHour + hour;
    } else {
        hoursDiff = alarmHour - hour;
    }

    // handle wrap around
    if (hoursDiff > HOURS_IN_A_DAY) {
        hoursDiff = HOURS_IN_A_DAY - (hoursDiff -HOURS_IN_A_DAY);
    }

    return hoursDiff;
}

uint8_t getMinutesOrSecondDiff(uint8_t alarmMinute, uint8_t minute) {
    uint8_t minutesDiff;

    if (alarmMinute < minute) {
        minutesDiff = MINUTE_IN_SEC - alarmMinute + minute;
    } else {
        minutesDiff = alarmMinute - minute;
    }

    // handle wrap around
    if (minutesDiff > MINUTE_IN_SEC) {
        minutesDiff = MINUTE_IN_SEC - (minutesDiff -MINUTE_IN_SEC);
    }

    return minutesDiff;
}

uint8_t getDaysFromNow(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute) {
    uint8_t daysFromNow;
    
    if (alarm.dayOfWeek == 255 || (alarm.dayOfWeek == dayOfWeek && alarm.hour > hour && alarm.minute > minute)) {
        daysFromNow = 0;
    } else if (alarm.hour < hour || alarm.minute < minute) {
        daysFromNow = substractOneDay(getDaysDiff(alarm.dayOfWeek, dayOfWeek));       
    } else if (alarm.dayOfWeek == dayOfWeek && (alarm.hour < hour || alarm.minute < minute)) {
        daysFromNow = DAYS_IN_A_WEEK;        
    } else {
        daysFromNow = getDaysDiff(alarm.dayOfWeek, dayOfWeek);    
    }  
    
    return daysFromNow;     
}

uint8_t getHoursFromNow(const scheduledAlarm_t& alarm, uint8_t hour, uint8_t minute) {
    uint8_t hoursFromNow = 0;

    if (alarm.hour == 255 || (alarm.hour == hour && alarm.minute > minute)) {
        hoursFromNow = 0;
    }  else if (alarm.minute < minute) {
        hoursFromNow = substractOneHour(getHoursDiff(alarm.hour, hour));  
    } else if (alarm.hour == hour && alarm.minute < minute) {
        hoursFromNow = HOURS_IN_A_DAY;
    } else {
        hoursFromNow = getHoursDiff(alarm.hour, hour);
    }

    return hoursFromNow;
}

uint8_t getMinutesFromNow(const scheduledAlarm_t& alarm, uint8_t minute) {
    uint8_t minutesFromNow = 0;

    if (alarm.minute == 255) {
        minutesFromNow = 0;
    }  else if (alarm.minute < minute) {
        minutesFromNow = substractOneMinute(getMinutesOrSecondDiff(alarm.minute, minute));  
    } else if (alarm.minute == minute) {
        // second is always 00 so always <
        minutesFromNow = MINUTE_IN_SEC;
    } else {
        minutesFromNow = getMinutesOrSecondDiff(alarm.minute, minute);
    }

    return minutesFromNow;
}

uint8_t getSecondsfromNow(uint8_t second) {
    uint8_t secondsFromNow = 0;

    if (second == 0) {
        secondsFromNow = second;  
    } else {
        secondsFromNow = getMinutesOrSecondDiff(0, second);
    }

    return secondsFromNow;
}

int32_t getSecondsFromAlarm(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second) {   
    int32_t secondsFromAlarm = 0;

    uint8_t dayDiff = getDaysDiff(alarm.dayOfWeek, dayOfWeek);
    uint8_t hourDiff = getHoursDiff(alarm.hour, hour);
    uint8_t minuteDiff = getMinutesOrSecondDiff(alarm.minute, minute);
    uint8_t secondDiff = getMinutesOrSecondDiff(0, second);

    uint8_t dayInSec = getDaysFromNow(alarm, dayOfWeek, hour, minute);
    uint8_t hourInsec = getHoursFromNow(alarm, hour, minute);
    uint8_t minuteInSec = getMinutesFromNow(alarm, minute);
    uint8_t secondInSec = getSecondsfromNow(second);

    // if (dayInSec > 0 && getDaysDiff(alarm.dayOfWeek, dayOfWeek) < dayInSec) {
    //     secondsFromAlarm = (dayInSec - 1) * (int32_t) DAY_IN_SEC;     
    // } else {
    //     secondsFromAlarm = dayInSec * (int32_t) DAY_IN_SEC;     
    // }

    // if (hourInsec > 0 && getHoursDiff(alarm.hour, hour) == hourInsec) {
    //     secondsFromAlarm = secondsFromAlarm + (hour -1) * (int32_t) HOUR_IN_SEC;
    // } else {    
    //     secondsFromAlarm = secondsFromAlarm + hour * (int32_t) HOUR_IN_SEC;
    // }

    // if (minuteInSec > 0 && getMinutesOrSecondDiff(alarm.minute, minute) == minuteInSec) {

    //       secondsFromAlarm = secondsFromAlarm + (minuteInSec -1) * (int32_t) MINUTE_IN_SEC; 
    // } else {            
    secondsFromAlarm = secondsFromAlarm + minuteInSec; // * (int32_t) MINUTE_IN_SEC;         
    //}    
    
    //if (secondInSec > 0) secondsFromAlarm = secondsFromAlarm + secondInSec; 
    // secondsFromAlarm = secondsFromAlarm + secondInSec; 

    return secondsFromAlarm;          
}