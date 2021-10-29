/*
 * File: rtcManager.c
 * Project: Device
 * Created Date: Thursday, October 21st 2021, 20:39:49 pm
 * 
 * Copyright (c) 2021 Eric BEaudet
 */
#ifndef UNIT_TEST // disable program main loop while unit testing in progress

#include <Arduino.h>
#include "rtcManager.h"


RtcDS3231<TwoWire> Rtc(Wire);
EepromAt24c32<TwoWire> RtcEeprom(Wire);

void updateClockFirstRun(void);
void restoreFactorySchedule(void);

uint8_t init_rtcManager(void) {

    uint8_t errorCode = 0;
  
    // start Memory chip 
    RtcEeprom.Begin();

    // start Rtc chip 
    Rtc.Begin();    
    
    // errorCode = validRtcTime();

    if (!Rtc.GetIsRunning()) {
        // Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    updateClockFirstRun();

     // Set interrupt to trigger every seconde
     Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1Hz);

    // never assume the Rtc was last configured by you, so
    // just clear them to your needed state
    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeClock, false); 

    restoreFactorySchedule();

    return errorCode;
}

RtcDateTime getCurrentDateTime(void) {
    return Rtc.GetDateTime();
}

uint8_t validRtcTime(void) {
    uint8_t errorCode = 0;

    if (!Rtc.IsDateTimeValid()) 
    {
        if (Rtc.LastError() != 0)
        {
            // we have a communications error
            // see https://www.arduino.cc/en/Reference/WireEndTransmission for 
            // what the number means
            // Serial.print("RTC communications error = ");
            // Serial.println(Rtc.LastError());
            errorCode = Rtc.LastError();
        }
        else
        {
            // Serial.println("RTC lost confidence in the DateTime!");
            // Rtc.SetDateTime(compiled);
            errorCode = 99;
        }
    }    

    // TODO build error code enum....
    return errorCode;
}

void updateClockFirstRun(void) {

    if (CONFIG_SERIAL > getConfigSerial() && AJUST_CLOCK) {
        RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);            
        Rtc.SetDateTime(compiled + CLOCK_OFFSET_IN_SEC);        
    }  
}

uint8_t getAlarmDuration(void) {
    return RtcEeprom.GetMemory(ALARM_DURATION_ADDRESS);
}

uint8_t getConfigSerial(void) {
    return RtcEeprom.GetMemory(SERIAL_ADDRESS);
}

void getSavedAlarm(scheduledAlarm_t* scheduledAlarm, int alarmNumber) {

    uint8_t buff[4];
    for (int i=ALARM_START_ADDRESS; i < alarmNumber + ALARM_START_ADDRESS; i++ ){
        buff[4] = RtcEeprom.GetMemory(i, buff, 4);
        scheduledAlarm[i-ALARM_START_ADDRESS].enable = buff[0];
        scheduledAlarm[i-ALARM_START_ADDRESS].dayOfWeek = buff[1];
        scheduledAlarm[i-ALARM_START_ADDRESS].hour = buff[2];
        scheduledAlarm[i-ALARM_START_ADDRESS].minute = buff[3];
    }
}

void restoreFactorySchedule(void) {

    if (CONFIG_SERIAL > getConfigSerial()) {

        scheduledAlarm_t myAlarm[] = FACTORY_ALARM;            
        RtcEeprom.SetMemory(ALARM_DURATION_ADDRESS, ALARM_DURATION_IN_SEC); // store the 

        uint8_t buff[4];
        for (int i=ALARM_START_ADDRESS; i < MAX_ALARM+ALARM_START_ADDRESS; i++) {
            buff[0] = myAlarm[i-ALARM_START_ADDRESS].enable;
            buff[1] = myAlarm[i-ALARM_START_ADDRESS].dayOfWeek;
            buff[2] = myAlarm[i-ALARM_START_ADDRESS].hour;
            buff[3] = myAlarm[i-ALARM_START_ADDRESS].minute;

            RtcEeprom.SetMemory(i, (const uint8_t*)buff, 4); // store the 
        }
    }   
}

void updateSerial (void) {
    if (CONFIG_SERIAL > getConfigSerial()) {
        RtcEeprom.SetMemory(SERIAL_ADDRESS, CONFIG_SERIAL); 
    }    
}

#endif