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
//EepromAt24c32<TwoWire> RtcEeprom(Wire);

void updateClockFirstRun(void);
//void restoreFactorySchedule(void);

uint8_t init_rtcManager(void) {

    uint8_t errorCode = 0;
  
    // start Memory chip 
    //RtcEeprom.Begin();

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

    //restoreFactorySchedule();

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
             Serial.print("RTC communications error = ");
             Serial.println(Rtc.LastError());
            errorCode = Rtc.LastError();
        }
        else
        {
            Serial.println("RTC lost confidence in the DateTime!");            
            errorCode = 99;
        }
    }    

    // TODO build error code enum....
    return errorCode;
}

void updateClockFirstRun(void) {

    //if (CONFIG_SERIAL > getConfigSerial() && AJUST_CLOCK) {
    if (AJUST_CLOCK == 1) {        
        RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);            
        Rtc.SetDateTime(compiled + CLOCK_OFFSET_IN_SEC);        
    }  
}

uint8_t getAlarmDuration(void) {
    //return RtcEeprom.GetMemory(ALARM_DURATION_ADDRESS);
    return (uint8_t) ALARM_DURATION_IN_SEC;
}

/**
 * Expect a string of "yyyy-mm-jj hh:mm:ss"
*/
RtcDateTime getDateTimeFromString(const char* datetime) {

    // sample input: date = "Dec 06 2009", time = "12:34:56"
    char time[9];
    char date[12];
    
    time[0] = datetime[11];
    time[1] = datetime[12];
    time[2] = datetime[13];
    time[3] = datetime[14];
    time[4] = datetime[15];
    time[5] = datetime[16];
    time[6] = datetime[17];
    time[7] = datetime[18];
    time[8] = '\0';

    date[3] = ' ';
    if (datetime[8] == '0') {
        date[4] = ' ';
    } else {
        date[4] = datetime[8];
    }
    
    date[5] = datetime[9];
    date[6] = ' ';
    date[7] = datetime[0];
    date[8] = datetime[1];
    date[9] = datetime[2];
    date[10] = datetime[3];
    date[11] = '\0';


    switch (datetime[5]) {
        case '0' :
            switch (datetime[6]) {
                case '1' : 
                    date[0] = 'J';
                    date[1] = 'a';
                    date[2] = 'n';
                    break;

                case '2' : 
                    date[0] = 'F';
                    date[1] = 'e';
                    date[2] = 'b';
                    break;

                case '3' : 
                    date[0] = 'M';
                    date[1] = 'a';
                    date[2] = 'r';
                    break;

                case '4' : 
                    date[0] = 'A';
                    date[1] = 'p';
                    date[2] = 'r';
                    break;

                case '5' : 
                    date[0] = 'M';
                    date[1] = 'a';
                    date[2] = 'y';
                    break;

                case '6' : 
                    date[0] = 'J';
                    date[1] = 'u';
                    date[2] = 'n';
                    break;

                case '7' : 
                    date[0] = 'J';
                    date[1] = 'u';
                    date[2] = 'l';
                    break;

                case '8' : 
                    date[0] = 'A';
                    date[1] = 'u';
                    date[2] = 'g';
                    break;

                case '9' : 
                    date[0] = 'S';
                    date[1] = 'e';
                    date[2] = 'p';
                    break;                                        
            }
        break;

        case '1' :
            switch (datetime[6]) {
                case '0' : 
                    date[0] = 'O';
                    date[1] = 'c';
                    date[2] = 't';
                    break;

                case '1' : 
                    date[0] = 'N';
                    date[1] = 'o';
                    date[2] = 'v';
                    break;

                case '2' : 
                    date[0] = 'D';
                    date[1] = 'e';
                    date[2] = 'c';
                    break;                                        
            }        
        break;
    }

    return RtcDateTime(date, time);
}

/**
 * Expect a string of "yyyy-mm-jj hh:mm:ss"
*/
void setTimeFromRtcDateTime(const RtcDateTime& dt) {   
    delay (2);
    Rtc.SetDateTime(dt);  
}

#endif