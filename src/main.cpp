
/*********************************************************************
*                   (c) 2021 Eric Beaudet                            *
**********************************************************************

File    : main.cpp
Purpose : Time clock controller application

This application maintains a list of alarm saved in a AT24C32 module.
Alarm activate a relay. 
Time is kept in a DS3231 IC.

Time and next alarm are displayed on a 2.23" Waveshare OLED hat 
(https://www.waveshare.com/wiki/2.23inch_OLED_HAT)

Configuration is done with an external software using serial communication.

*/

#include <Arduino.h>
#include <SPI.h>

#include "ssd1305.h"
#include "Device/rtcManager.h"
#include "defaultConfiguration.h"

// Display configuration
#define WIDTH     128
#define HEIGHT     32
#define PAGES       4

#define OLED_RST    9 
#define OLED_DC     8
#define OLED_CS    10
#define SPI_MOSI   11    /* connect to the DIN pin of OLED */
#define SPI_SCK    13     /* connect to the CLK pin of OLED */


uint8_t oled_buf[WIDTH * HEIGHT / 8];

#define countof(a) (sizeof(a) / sizeof(a[0]))


volatile uint16_t interuptCount = 0;
volatile bool interuptFlag = false;



const char data[] = "What time is it in Greenwich?";
const uint16_t stringAddr = 64; // stored on page boundary

void printDateTime(const RtcDateTime& dt);
void printRtcError(uint8_t rtcErrorCode);
void displayTime ();

void ISR_ATTR InteruptServiceRoutine()
{
    // since this interupted any other running code,
    // don't do anything that takes long and especially avoid
    // any communications calls within this routine
    interuptCount++;
    interuptFlag = true;
}

void setup() {
  
    // set the interupt pin to input mode
    pinMode(RtcSquareWavePin, INPUT);

    // setup external interupt 
    attachInterrupt(RtcSquareWaveInterrupt, InteruptServiceRoutine, FALLING);       

    // Setup Serial connection
    Serial.begin(115200);

    // setup rtc and Atchip
    init_rtcManager();

    // Serial.print("compiled: ");
    // Serial.print(__DATE__);
    // Serial.println(__TIME__);

    // Display init
    /* display an image of bitmap matrix */
    SSD1305_begin();
}

void loop() {

    printRtcError(validRtcTime());
    
    if (interuptFlag) {
        interuptFlag = false;
        displayTime();  
    }    
}

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}

void printRtcError(uint8_t rtcErrorCode) {

    switch (rtcErrorCode = validRtcTime()) {
        case 1 ... 98:
          Serial.print("RTC communications error = ");
          Serial.println(rtcErrorCode);  
          break; 

        case 99:
          Serial.println("RTC lost confidence in the DateTime!");
          break;

        default:
          break;
    }  
}

void displayTime () {
        Serial.print("Interrupt count : ");  
        Serial.println(interuptCount);      

        RtcDateTime now = getCurrentDateTime();

        printDateTime(now);
        Serial.println();

        char datestring[9];

        snprintf_P(datestring, 
              countof(datestring),
              PSTR("%02u:%02u:%02u"),
              now.Hour(),
              now.Minute(),
              now.Second() );    

        SSD1305_clear(oled_buf);

        SSD1305_bitmap(10, 4, Alarm88, 8, 8, oled_buf); 
        SSD1305_string(20, 2, "(3)", 12, 1, oled_buf);
        SSD1305_string(25, 16, datestring, 16, 1, oled_buf);

        SSD1305_display(oled_buf);  
}