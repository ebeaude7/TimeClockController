/*
 * File: rtcManager.h
 * Project: Device
 * Created Date: Thursday, October 21st 2021, 19:26:55 pm
 * 
 * Copyright (c) 2021 Eric Beaudet
 */

#ifndef _RTC_MANAGER_H_
#define _RTC_MANAGER_H_

#include <Wire.h>
#include <RtcDS3231.h>
#include <EepromAT24C32.h>
#include "defaultConfiguration.h"

// Interrupt Pin Lookup Table
// (copied from Arduino Docs)
//
// CAUTION:  The interrupts are Arduino numbers NOT Atmel numbers
//   and may not match (example, Mega2560 int.4 is actually Atmel Int2)
//   this is only an issue if you plan to use the lower level interupt features
//
// Board           int.0    int.1   int.2   int.3   int.4   int.5
// ---------------------------------------------------------------
// Uno, Ethernet    2       3
// Mega2560         2       3       21      20     [19]      18 
// Leonardo         3       2       0       1       7
#define RtcSquareWavePin 2
#define RtcSquareWaveInterrupt 0 // Uno


// rtc function
// -----------------------------------------------------
uint8_t init_rtcManager(void);
uint8_t validRtcTime(void);

uint8_t getAlarmDuration(void);
RtcDateTime getCurrentDateTime(void);

// void getSavedAlarm(scheduledAlarm_t* scheduledAlarm, int alarmNumber);
//uint8_t getConfigSerial(void);
// void updateSerial (void);

#endif