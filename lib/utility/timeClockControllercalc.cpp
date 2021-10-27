/*
 * File: timeClockControllercalc.cpp
 * Project: utility
 * Created Date: Tuesday, October 26th 2021, 8:17:45 pm
 * Author: Eric Beaudet (ebeaudet@noovelia.com)
 * 
 * Copyright (c) 2021 EJS
 */

#include "timeClockControllerCalc.h"


int32_t getNumberOfSeconds(const scheduledAlarm_t& alarm, int32_t second) {
    int32_t numbersOfSeconds = 0;

    // add day in second
    numbersOfSeconds = (int32_t) alarm.dayOfWeek * D_IN_SEC;
    
    // add hour in second
    numbersOfSeconds = numbersOfSeconds + (int32_t) alarm.hour * H_IN_SEC;

    // add minute in second
    numbersOfSeconds = numbersOfSeconds + (int32_t) alarm.minute * M_IN_SEC;

    // add second
    numbersOfSeconds = numbersOfSeconds + second;

    //return numbersOfSeconds;
    return numbersOfSeconds;
}

int32_t getSecondstoAlarm (const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second) {
    
    int32_t secondsToAlarm = 0; 
    int32_t alarmInSeconds = 0;
    int32_t nowInSeconds = 0;
    
    scheduledAlarm_t now = {1,dayOfWeek,hour,minute};    
    scheduledAlarm_t sAlarm = {1, alarm.dayOfWeek, alarm.hour, alarm.minute};

    if (sAlarm.dayOfWeek == 255) {
        sAlarm.dayOfWeek = dayOfWeek;
    }

    if (sAlarm.hour == 255) {
        sAlarm.hour = hour;
    }

    if (sAlarm.minute == 255) {
        sAlarm.minute = minute;
    }

    bool alarmAheadInTheWeek = false;

    if (sAlarm.dayOfWeek > dayOfWeek) {
        alarmAheadInTheWeek = true;
    } else if (sAlarm.dayOfWeek == dayOfWeek) {
        // -------------- day
        if (sAlarm.hour > hour) {
            alarmAheadInTheWeek = true;
        } else if (sAlarm.hour == hour) {
            // -------------- hour
            if (sAlarm.minute > minute) {
                alarmAheadInTheWeek = true;
            }  else if (sAlarm.minute == minute && alarm.minute == 255) {
                // -------------- min
                // alarm sec always 0
                            
                // alarm is not this minute, ajust sAlarm
                if (minute == 59) {
                    sAlarm.minute = 0;
                } else {
                    sAlarm.minute = minute + 1;                                                    
                }    

                alarmAheadInTheWeek = true;
            } 

            // alarm is not this hour, ajust sAlarm
            if (!alarmAheadInTheWeek && alarm.hour == 255) {
                if (hour == 23) {
                    sAlarm.hour = 0;
                } else {
                    sAlarm.hour = hour + 1;                
                }    

                alarmAheadInTheWeek = true;
            }
        } 

        // alarm is not today, ajust sAlarm for tomorrow
        if (!alarmAheadInTheWeek && alarm.dayOfWeek == 255) {
            if (dayOfWeek == 6) {
                sAlarm.dayOfWeek = 0;
            } else {
                sAlarm.dayOfWeek = dayOfWeek + 1;            
            }

            alarmAheadInTheWeek = true;
        }            
    } 

    alarmInSeconds = getNumberOfSeconds(sAlarm, 0);
    nowInSeconds = getNumberOfSeconds(now, second);

    if (alarmAheadInTheWeek) {    
        secondsToAlarm = alarmInSeconds - nowInSeconds;        
    } else {
        secondsToAlarm = (W_IN_SEC - nowInSeconds) + alarmInSeconds;        
    }
    
    return secondsToAlarm;        
}
