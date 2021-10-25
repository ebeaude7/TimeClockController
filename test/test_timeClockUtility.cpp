/*
 * File: test_main.cpp
 * Project: test
 * Created Date: Monday, October 25th 2021, 12:21:39 am
 * Author: Eric Beaudet (ebeaudet@noovelia.com)
 * 
 * Copyright (c) 2021 EJS
 */

#include <unity.h>
#include "timeClockControllerUtility.h"


//#ifdef UNIT_TEST

//  void setUp(void) {
//     // set stuff up here
//  }

// void tearDown(void) {
//     // clean stuff up here
// }


void testAddOneDay(void) {
    uint8_t alarmDay = 6;    
    uint8_t expected = 0;

    uint8_t result = addOneDay(alarmDay);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysDiff_dim_lun(void) {
    uint8_t alarmDay = 1;
    uint8_t today = 0;
    uint8_t expected = 1;

    uint8_t result = getDaysDiff(alarmDay, today);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
        RUN_TEST(testAddOneDay);
        RUN_TEST(testGetDaysDiff_dim_lun);
    UNITY_END();
}

//#endif