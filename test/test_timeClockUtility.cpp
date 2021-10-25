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

// ------------------------------------------
// Test addOneDay (uint8_t day)
// ------------------------------------------
void testAddOneDay_wrap(void) {
    uint8_t alarmDay = 6;    
    uint8_t expected = 0;

    uint8_t result = addOneDay(alarmDay);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testAddOneDay_normal(void) {
    uint8_t alarmDay = 1;    
    uint8_t expected = 2;

    uint8_t result = addOneDay(alarmDay);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test substractOneDay (uint8_t day) 
// ------------------------------------------
void testSubstractOneDay_wrap(void) {
    uint8_t alarmDay = 0;    
    uint8_t expected = 6;

    uint8_t result = substractOneDay(alarmDay);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testSubstractOneDay_normal(void) {
    uint8_t alarmDay = 4;    
    uint8_t expected = 3;

    uint8_t result = substractOneDay(alarmDay);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test getDaysDiff(uint8_t alarmDay, uint8_t today)
// ------------------------------------------
void testGetDaysDiff_dim_lun(void) {
    uint8_t alarmDay = 1;
    uint8_t today = 0;
    uint8_t expected = 1;

    uint8_t result = getDaysDiff(alarmDay, today);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysDiff_lun_dim(void) {
    uint8_t alarmDay = 0;
    uint8_t today = 1;
    uint8_t expected = 6;

    uint8_t result = getDaysDiff(alarmDay, today);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysDiff_normalUp(void) {
    uint8_t alarmDay = 5;
    uint8_t today = 3;
    uint8_t expected = 2;

    uint8_t result = getDaysDiff(alarmDay, today);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysDiff_normalDn(void) {
    uint8_t alarmDay = 3;
    uint8_t today = 5;
    uint8_t expected = 5;

    uint8_t result = getDaysDiff(alarmDay, today);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test 
// ------------------------------------------

// ------------------------------------------
// Test Runner
// ------------------------------------------
int main( int argc, char **argv) {
    UNITY_BEGIN();
        RUN_TEST(testAddOneDay_wrap);
        RUN_TEST(testAddOneDay_normal);

        RUN_TEST(testSubstractOneDay_wrap);
        RUN_TEST(testSubstractOneDay_normal);

        RUN_TEST(testGetDaysDiff_dim_lun);
        RUN_TEST(testGetDaysDiff_lun_dim);
        RUN_TEST(testGetDaysDiff_normalUp);
        RUN_TEST(testGetDaysDiff_normalDn);
    UNITY_END();
}

//#endif