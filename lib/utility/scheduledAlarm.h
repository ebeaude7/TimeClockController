/*
 * File: scheduledAlarm.h
 * Project: utility
 * Created Date: Monday, October 25th 2021, 12:34:46 pm
 * Author: Eric Beaudet (ebeaudet@noovelia.com)
 * 
 * Copyright (c) 2021 EJS
 */
#ifndef _SCHEDULED_ALARM_H_
#define _SCHEDULED_ALARM_H_


/**
 * Alarm structure.
 */
typedef struct scheduledAlarm {
    uint8_t enable;
    uint8_t dayOfWeek;
    uint8_t hour;
    uint8_t minute;
} scheduledAlarm_t;

#endif