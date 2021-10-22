/*
 * File: rtcManager.c
 * Project: Device
 * Created Date: Thursday, October 21st 2021, 10:39:49 pm
 * 
 * Copyright (c) 2021 Eric BEaudet
 */

#include <Arduino.h>
#include "rtcManager.h"

RtcDS3231<TwoWire> Rtc(Wire);
EepromAt24c32<TwoWire> RtcEeprom(Wire);

void updateClockFirstRun(void);

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

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    RtcDateTime now = Rtc.GetDateTime();

    if (now < compiled) {
        //Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }    
}

void restoreFactorySchedule(void) {
/* comment out on a second run to see that the info is stored long term */
    // // Store something in memory on the Eeprom

    // // store starting address of string
    // RtcEeprom.SetMemory(0, stringAddr); 
    // // store the string, nothing longer than 32 bytes due to paging
    // uint8_t written = RtcEeprom.SetMemory(stringAddr, (const uint8_t*)data, sizeof(data) - 1); // remove the null terminator strings add
    // // store the length of the string
    // RtcEeprom.SetMemory(1, written); // store the 
/* end of comment out section */    

/*
      // get the offset we stored our data from address zero
      uint8_t address = RtcEeprom.GetMemory(0);
      if (address != stringAddr)
      {
          Serial.print("address didn't match ");
          Serial.println(address);
      }
      
      {
          // get the size of the data from address 1
          uint8_t count = RtcEeprom.GetMemory(1);
          uint8_t buff[64];

          // get our data from the address with the given size
          uint8_t gotten = RtcEeprom.GetMemory(address, buff, count);

          if (gotten != count ||
              count != sizeof(data) - 1) // remove the extra null terminator strings add
          {
              Serial.print("something didn't match, count = ");
              Serial.print(count, DEC);
              Serial.print(", gotten = ");
              Serial.print(gotten, DEC);
              Serial.println();
          }
          Serial.print("data read (");
          Serial.print(gotten);
          Serial.print(") = \"");
          for (uint8_t ch = 0; ch < gotten; ch++)
          {
              Serial.print((char)buff[ch]);
          }
          Serial.println("\"");
      }
*/
}





