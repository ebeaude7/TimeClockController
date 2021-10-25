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

    // handle wrap around
    if (daysDiff > DAYS_IN_A_WEEK) {
        daysDiff = DAYS_IN_A_WEEK - (daysDiff -DAYS_IN_A_WEEK);
    }

    return daysDiff;
}


uint8_t getDaysFromNow(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute) {
    uint8_t daysFromNow;
    
    // uint8_t dayOfWeek = now.DayOfWeek();    
    // uint8_t hour = now.Hour();
    // uint8_t minute = now.Minute();   

    //Serial.println("--------------------------------");
      
    if (alarm.dayOfWeek == 255 || (alarm.dayOfWeek == dayOfWeek && alarm.hour > hour && alarm.minute > minute)) {
        daysFromNow = 0;
        //Serial.print("case 1 ");
    } else if (alarm.hour < hour || alarm.minute < minute) {
        daysFromNow = substractOneDay(getDaysDiff(alarm.dayOfWeek, dayOfWeek));
       // Serial.print("case 2 ");
    } else if (alarm.dayOfWeek == dayOfWeek && (alarm.hour < hour || alarm.minute < minute)) {
        daysFromNow = DAYS_IN_A_WEEK;
        //Serial.print("case 3 ");
    } else {
        daysFromNow = getDaysDiff(alarm.dayOfWeek, dayOfWeek);
        //Serial.print("case 4 ");
    }  
    
    // Serial.print("Alarm day of week: ");  
    // Serial.print(alarm.dayOfWeek);
    // Serial.print(" | Current day of week: ");  
    // Serial.print(dayOfWeek);
    // Serial.print(" | Days from now ");
    // Serial.println(daysFromNow);  

    return daysFromNow;     
}

uint8_t getHoursFromNow(const scheduledAlarm_t& alarm, uint8_t hour, uint8_t minute) {
    uint8_t hoursFromNow = 0;

    // uint8_t hour = now.Hour();
    // uint8_t minute = now.Minute();  

    if (alarm.hour == 255 || (alarm.hour == hour && alarm.minute > minute)) {
        hoursFromNow = 0;
        //Serial.print("case 1 ");
    }  else if (addOneHour(hour) && alarm.minute < minute) {
        hoursFromNow = 0;
        //Serial.print("case 2 ");      
    } else if (alarm.hour == hour && alarm.minute < minute) {
        hoursFromNow = HOURS_IN_A_DAY;
        //Serial.print("case 3 ");      
    } else if (alarm.hour < hour) {
        hoursFromNow = HOURS_IN_A_DAY - alarm.dayOfWeek + hour;
        //Serial.print("case 4 ");
    } else {
        hoursFromNow = alarm.hour - hour;
        //Serial.print("case 5 ");
    }

    // Serial.println("Alarm hour: ");  
    // Serial.print(alarm.hour);
    // Serial.print(" | Current hour: ");  
    // Serial.print(hour);
    // Serial.print(" | Hours from now ");
    // Serial.println(hoursFromNow);  

    return hoursFromNow;
}

long getSecondsfromNow(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second) {
    long remainingSec = 0;

    // uint8_t dayOfWeek = now.DayOfWeek();
    // uint8_t hour = now.Hour();
    // uint8_t minute = now.Minute();
    // uint8_t second = now.Second();

    uint8_t daysFromNow = getDaysFromNow(alarm, dayOfWeek, hour, minute);
    uint8_t hoursFromNow = getHoursFromNow(alarm, hour, minute);

    if (alarm.minute != 255 && alarm.minute > minute) {
        remainingSec = (A_MINUTE_IN_SEC - second + (alarm.minute - minute) * A_MINUTE_IN_SEC) - A_MINUTE_IN_SEC;
    } else {
        if (alarm.minute == 255) {
            // patch second

        } else {
            // substract remaining minutes from next hour  
            if (hour == 0) {
               hour = 23;
               if (dayOfWeek == 0) {
                 dayOfWeek = 6;
               } else {
                 dayOfWeek = dayOfWeek -1;
               }
            } else {
               hour = hour - 1;
            }
        }
    }

    remainingSec = remainingSec + (daysFromNow * A_DAY_IN_SEC) + (hoursFromNow * An_HOUR_IN_SEC);
        
    if (remainingSec == 0) return -1;    
    return remainingSec;
}