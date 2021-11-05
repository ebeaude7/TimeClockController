/**
 * File: defaultConfiguration.h
 * Project: Time clock controller
 * Created Date: Wednesday, October 20th 2021, 19:36:14 pm
 * 
 * Copyright (c) 2021 Eric Beaudet
 * 
 * Define alarm and configuration structure
 * 
 * Define a default configuration.
 * Application will load this configuration if AT24C32 module is empty
 * or serial is greater than the one in memory and write it to the module.
 * 
 */

#ifndef _DEFAULT_CONFIGURATION_H_
#define _DEFAULT_CONFIGURATION_H_

#define SERIAL_ADDRESS 0
#define ALARM_DURATION_ADDRESS 1
#define ALARM_START_ADDRESS 2

#include "scheduledAlarm.h"

/**
 * Wiring reference for the siren :
 *
 * How Do I Connect Red, Yellow, & White Wires To a Siren?
 * The following is instructions to connect wires from a hardwired siren.
 *
 * The white wire is 12V negative (GND).
 * The yellow positive wire is for normal steady alarm tone.
 * The red wire is alternate positive and is used to produce the warble tone associated with fire alarms. 
 */

// -----------------------------------------------------------------
// CONFIG START HERE ()
// -----------------------------------------------------------------
// fix maximum number of alarm the system can have
// note : AT24C32 have 256 pages of 32 bytes of memory.
// serial will be written at page 0
// alarm duration will be written at page 1
// first alarm start at page 2
// each alarm will use 1 page of memory


// MUST BE INCREMENTED TO +1 FOR CONFIG TO BE WRITTEN
#define CONFIG_SERIAL 15
#define MAX_ALARM 25
#define ALARM_DURATION_IN_SEC 3

// Set to 1 to ajust clock when uploading code. 
#define AJUST_CLOCK 0

// Clock is set from compiled time. It should be a little bit behind real time.
// Ajust the difference, and upload code again.
#define CLOCK_OFFSET_IN_SEC 7

// Array of alarms.
// Format is 255 for all
// for days, sunday = 0, monday 1...
// 
// enable values are :
//      0   disabled
//      1   tone 1  (steady sound yellow wire)
//
//      enable dayOfWeek     hour    minute  
// --------------------------------------------------
// ex:   1       255        255         0      --> every hour at 0 minute. 
// ex:   1       255        9           15     --> 9h15 every day     
// ex:   1       1          12          0      --> 12h00 on monday only    
// ex:   0       255        255         255    --> alarm disabled

#define FACTORY_ALARM  {  \
                        {1,255,9,0},  \
                        {1,255,9,10}, \
                        {1,255,9,15}, \
                        {1,255,12,0}, \
                        {1,255,12,40},\
                        {1,255,12,45},\
                        {1,255,14,0}, \
                        {1,255,14,10},\
                        {1,255,14,15},\
                        {1,255,16,0}, \
                        {1,255,18,0}, \
                        {1,255,18,10},\
                        {1,255,18,15},\
                        {1,255,20,0}, \
                        {1,255,20,40},\
                        {1,255,20,45},\
                        {1,255,23,0}, \
                        {1,255,23,40},\
                        {1,255,23,45},\
                        {0,255,9,15}, \
                        {0,255,9,15}, \
                        {0,255,9,15}, \
                        {0,255,9,15}, \
                        {0,255,9,15}, \
                        {0,255,9,15}  \
                        }
                       
// -----------------------------------------------------------------
// END OF CONGIF
// -----------------------------------------------------------------                        

#endif