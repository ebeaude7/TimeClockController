
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

#ifndef UNIT_TEST // disable program main loop while unit testing in progress

#include <Arduino.h>
#include <SPI.h>

#include "ssd1305.h"
#include "rtcManager.h"
#include "timeClockControllerCalc.h"
#include "defaultConfiguration.h"

#define VERSION "1.0.1"
#define ENTER_TIME_MSG "Entrer l'heure actuelle (yyyy-mm-dd hh:mm:ss) : "

// relay config
#define RELAY_PIN_TONE_1 4
#define RELAY_PIN_TONE_2 5

// Display configuration
#define WIDTH     128
#define HEIGHT     32
#define PAGES       4

#define OLED_RST    9 
#define OLED_DC     8
#define OLED_CS    10
#define SPI_MOSI   11    /* connect to the DIN pin of OLED */
#define SPI_SCK    13     /* connect to the CLK pin of OLED */

const unsigned int MAX_SERIAL_INPUT_LENGTH = 21; // yyyy-mm-dd hh:mm:ss

uint8_t oled_buf[WIDTH * HEIGHT / 8];

#define countof(a) (sizeof(a) / sizeof(a[0]))

volatile uint16_t interuptCount = 0;
volatile bool interuptFlag = false;

RtcDateTime now;

int32_t nextAlarm = -1;
int32_t alarmRunningCountdown = -1;

uint8_t alarmDuration = ALARM_DURATION_IN_SEC;
scheduledAlarm_t sAlarm[] = FACTORY_ALARM;
//scheduledAlarm_t sAlarm[] = TEST_ALARM;

const uint16_t stringAddr = 64; // stored on page boundary

void runAlarmMonitor(const RtcDateTime& now);
void printDateTime(const RtcDateTime& dt);
void printRtcError(uint8_t rtcErrorCode);
void displayTime (const RtcDateTime& now);
void printConfig (void);
int32_t selectNextAlarm(const RtcDateTime& now);
void printVersion(void);

void ISR_ATTR InteruptServiceRoutine()
{
    // since this interupted any other running code,
    // don't do anything that takes long and especially avoid
    // any communications calls within this routine
    interuptCount++;
    interuptFlag = true;
}

void setup() {

    // initialize digital pin as an output.
    pinMode(RELAY_PIN_TONE_1, OUTPUT);
    pinMode(RELAY_PIN_TONE_2, OUTPUT);

    // set the interupt pin to input mode
    pinMode(RtcSquareWavePin, INPUT);

    // setup external interupt 
    attachInterrupt(RtcSquareWaveInterrupt, InteruptServiceRoutine, FALLING);       

    // Setup Serial connection
    Serial.begin(115200);

    // setup rtc and Atchip
    init_rtcManager();

    // init settings
    //alarmDuration = getAlarmDuration();
    //getSavedAlarm(sAlarm, MAX_ALARM);
    // printConfig();

    // update Serial
    //updateSerial();

    // restore time from rtc
    now = getCurrentDateTime();
    printRtcError(validRtcTime());
    
    // Display init
    SSD1305_begin();

    printVersion();

    //digitalWrite(RELAY_PIN_TONE_1, HIGH);
    //digitalWrite(RELAY_PIN_TONE_2, HIGH);

}

void readNewTimeFromSerial () {
    // read serial buffer for clock update    
    while (Serial.available() > 0) {
        //Create a place to hold the incoming message
        static char message[MAX_SERIAL_INPUT_LENGTH];
        static unsigned int message_pos = 0;

        //Read the next available byte in the serial receive buffer
        char inByte = Serial.read();

        //Message coming in (check not terminating character) and guard for over message size
        if ( inByte != '\n') {
            //Add the incoming byte to our message
            message[message_pos] = inByte;
            message_pos++;
            Serial.print(inByte);
        } else if (message_pos == MAX_SERIAL_INPUT_LENGTH -1 && inByte == '\n') {
            //Full message received...             
            //Add null character to string
            message[message_pos] = '\0';

            //Print the message (or do other things)
            Serial.println(message);

            // Update rtc    
            RtcDateTime newTime = getDateTimeFromString(message);                    
            setTimeFromRtcDateTime(newTime);                        
                        
            // update clock
            now = newTime;

            printDateTime(now);
                
            Serial.print("Nouvelle heure : ");
            Serial.println(message);
            Serial.println();
            Serial.print(ENTER_TIME_MSG);            
            
            //Reset for the next message
            message_pos = 0;

            nextAlarm = selectNextAlarm(now);
        } else {
            
            Serial.println("Format de date invalide!");
            Serial.print(ENTER_TIME_MSG);
            message_pos = 0;
        }                       
    }
}

void loop() {
        
    if (interuptFlag) {      
        interuptFlag = false;
        
        now = now + 1;

        runAlarmMonitor(now);
        displayTime(now);  
    }    

    readNewTimeFromSerial();    
}

void runAlarmMonitor (const RtcDateTime& now) {
    
    nextAlarm--; 
    if (alarmRunningCountdown < 0 && nextAlarm == 0) {        
        alarmRunningCountdown = ALARM_DURATION_IN_SEC;
    } else if (nextAlarm > 0 || alarmRunningCountdown > 0) {
       // do nothing but keep next alarm at 0
       if (alarmRunningCountdown > 0) {
          nextAlarm = 0;
       }
    } else {        
        nextAlarm = selectNextAlarm(now);  
    }

    // run the alarm 
    if (alarmRunningCountdown > 0) {
        digitalWrite(RELAY_PIN_TONE_1, HIGH);
        alarmRunningCountdown--;
    } else {
        digitalWrite(RELAY_PIN_TONE_1, LOW);
        alarmRunningCountdown--;
    }
}

void printConfig(void) {
    // print config serial
    //Serial.print("EPROMM config serial : ");
    //Serial.print(getConfigSerial());
    //Serial.print(" Config Serial : ");
    //Serial.println(CONFIG_SERIAL);

    // print alarm duration
    Serial.print("Alarm duration : ");
    Serial.println(getAlarmDuration());

    Serial.println("Print configured alarm list to serial port:");
    for (int i=0; i < MAX_ALARM; i++) {
        Serial.print(sAlarm[i].enable);
        Serial.print(" ");
        Serial.print(sAlarm[i].dayOfWeek);
        Serial.print(" ");
        Serial.print(sAlarm[i].hour);
        Serial.print(" ");
        Serial.println(sAlarm[i].minute);
    }
}

void printVersion() {

    SSD1305_clear(oled_buf);
    SSD1305_string(30, 2, VERSION, 12, 1, oled_buf);    
    SSD1305_display(oled_buf);  

    Serial.println();
    Serial.println("-----------------------------------------");
    Serial.print("Time clock Controller v");
    Serial.println(VERSION);
    Serial.println("-----------------------------------------");
}

void printDateTime(const RtcDateTime& dt) {
    char datestring[23];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u %02u/%02u/%04u %02u:%02u:%02u"),
            dt.DayOfWeek(),
            dt.Day(),
            dt.Month(),           
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );

    Serial.println(datestring);
}

void printRtcError(uint8_t rtcErrorCode) {

    switch (rtcErrorCode = validRtcTime()) {
        case 1 ... 98:
            Serial.println();
            Serial.print("RTC communications error = ");
            Serial.println(rtcErrorCode);  
            Serial.print(ENTER_TIME_MSG);
            break; 

        case 99:
            Serial.println();
            Serial.println("RTC lost confidence in the DateTime!");
            Serial.print(ENTER_TIME_MSG);
            break;

        default:
            break;
    }  
}

void displayTime (const RtcDateTime& now) {
    
    char datestring[9];
    char remainingSecString[12];
    char alarmOffSecString[3];

    snprintf_P(datestring, 
          countof(datestring),
          PSTR("%02u:%02u:%02u"),          
          now.Hour(),
          now.Minute(),
          now.Second() );  

    snprintf_P(remainingSecString, 
          countof(remainingSecString),
          PSTR("%06u sec."),
          nextAlarm);           

    snprintf_P(alarmOffSecString, 
          countof(alarmOffSecString),
          PSTR("%02u"),
          alarmRunningCountdown+1);             

    // clear the screen
    SSD1305_clear(oled_buf);

    // display remaining seconds before next alarm
    SSD1305_bitmap(10, 4, Alarm88, 8, 8, oled_buf); 
    if (nextAlarm < 0 && alarmRunningCountdown < 0) {
        SSD1305_string(30, 2, "Aucune alarme", 12, 1, oled_buf);
    } else {
        SSD1305_string(30, 2, remainingSecString, 12, 1, oled_buf);       
    }

    // display remaining seconds before alarm go off
    if (alarmRunningCountdown >= 0) {
        SSD1305_string(100, 2, alarmOffSecString, 12, 1, oled_buf); 
        SSD1305_bitmap(100, 16, Signal816, 16, 8, oled_buf); 
    } 
    
    // Display day of the week
    switch (now.DayOfWeek()) {
        case 0 :
          SSD1305_string(10, 16, "Dim", 12, 1, oled_buf);
          break;
        case 1 :
          SSD1305_string(10, 16, "Lun", 12, 1, oled_buf);
          break;
        case 2 :
          SSD1305_string(10, 16, "Mar", 12, 1, oled_buf);
          break;
        case 3 :
          SSD1305_string(10, 16, "Mer", 12, 1, oled_buf);
          break;
        case 4 :
          SSD1305_string(10, 16, "Jeu", 12, 1, oled_buf);
          break;
        case 5 :
          SSD1305_string(10, 16, "Ven", 12, 1, oled_buf);
          break;
        case 6 :
          SSD1305_string(10, 16, "Sam", 12, 1, oled_buf);
          break;                                                            
    }
    
    // Display time
    SSD1305_string(30, 16, datestring, 16, 1, oled_buf);

    // refresh the screen
    SSD1305_display(oled_buf);  
}


// return remaining seconds before next alarm
// return -1 if no alarm
int32_t selectNextAlarm(const RtcDateTime& now) {

    uint32_t remainingSecondBeforeNextAlarm = -1;
    uint32_t secondFromNow;

    scheduledAlarm_t* selectedAlarm;

    for (int i=0; i < MAX_ALARM; i++) {
        if (sAlarm[i].enable == 1) {
            secondFromNow = getSecondstoAlarm(sAlarm[i], now.DayOfWeek(), now.Hour(), now.Minute(), now.Second());

            if (remainingSecondBeforeNextAlarm == 0 || remainingSecondBeforeNextAlarm > secondFromNow) {
                remainingSecondBeforeNextAlarm = secondFromNow;               
                selectedAlarm = &sAlarm[i];
            } 
        }
    } 

    Serial.println();
    Serial.print("Prochaine alarme dans : ");
    Serial.print(remainingSecondBeforeNextAlarm);
    Serial.print(" sec. = {");
    Serial.print(selectedAlarm->dayOfWeek);
    Serial.print(",");
    Serial.print(selectedAlarm->hour);
    Serial.print(",");
    Serial.print(selectedAlarm->minute);      
    Serial.println("}");
    Serial.println();
    
    Serial.print(ENTER_TIME_MSG);

    return remainingSecondBeforeNextAlarm;    
}

#endif