/*
 * File: test_timeClockControllerCalc.cpp
 * Project: test
 * Created Date: Tuesday, October 26th 2021, 8:25:14 pm
 * 
 * Copyright (c) 2021 Eric Beaudet
 */

#include <unity.h>
#include "timeClockControllerCalc.h"

// ------------------------------------------
// Test getSecondstoAlarm
// ------------------------------------------
void testGetSecondsToAlarm_in_10_min(void) {
    scheduledAlarm_t alarm = {1,255,255,10};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 0;
    uint8_t second = 0;

    int32_t expected = 600;

    int32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_in_10_min255Up(void) {
    scheduledAlarm_t alarm = {1,255,17,10};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 0;
    uint8_t second = 0;

    int32_t expected = 600;

    int32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_in_10_min255Dn(void) {
    scheduledAlarm_t alarm = {1,255,17,0};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 10;
    uint8_t second = 0;

    int32_t expected = 85800;

    int32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_in_10_minBefore0(void) {
    scheduledAlarm_t alarm = {1,255,255,0};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 50;
    uint8_t second = 0;

    int32_t expected = 600;

    int32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_in_10(void) {
    scheduledAlarm_t alarm = {1,255,255,0};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 49;
    uint8_t second = 30;

    int32_t expected = 630;

    int32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_in_24h(void) {
    scheduledAlarm_t alarm = {1,255,17,00};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 0;
    uint8_t second = 0;

    uint32_t expected = 86400;

    uint32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_0(void) {
    scheduledAlarm_t alarm = {1,255,9,00};

    uint8_t dayOfWeek = 1;
    uint8_t hour = 21;    
    uint8_t minute = 44;
    uint8_t second = 50;

    uint32_t expected = 40510;

    uint32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_max(void) {
    scheduledAlarm_t alarm = {1,0,9,0};

    uint8_t dayOfWeek = 0;
    uint8_t hour = 9;    
    uint8_t minute = 0;
    uint8_t second = 1;

    uint32_t expected = 604799;

    uint32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_1h(void) {
    scheduledAlarm_t alarm = {1,255,0,0};

    uint8_t dayOfWeek = 0;
    uint8_t hour = 23;    
    uint8_t minute = 0;
    uint8_t second = 0;

    uint32_t expected = 3600;

    uint32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsToAlarm_1h_beforeNoon(void) {
    scheduledAlarm_t alarm = {1,255,12,0};

    uint8_t dayOfWeek = 0;
    uint8_t hour = 11;    
    uint8_t minute = 0;
    uint8_t second = 0;

    uint32_t expected = 3600;

    uint32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);    
}

void testGetSecondsToAlarm_23h45(void) {
    scheduledAlarm_t alarm = {1,255,23,45};

    uint8_t dayOfWeek = 4;
    uint8_t hour = 16;    
    uint8_t minute = 20;
    uint8_t second = 10;

    uint32_t expected = 26690;

    uint32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);    
}

void testGetSecondsToAlarm_1week(void) {
    scheduledAlarm_t alarm = {1,6,23,59};

    uint8_t dayOfWeek = 0;
    uint8_t hour = 0;    
    uint8_t minute = 0;
    uint8_t second = 0;

    uint32_t expected = 604740;

    uint32_t result = getSecondstoAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);    
}

// ------------------------------------------
// Test getNumberOfSeconds
// ------------------------------------------
void testGetNumberOfSeconds_23h(void) {
    scheduledAlarm_t alarm = {1,0,23,0};

    // uint8_t dayOfWeek = 0;
    // uint8_t hour = 23;    
    // uint8_t minute = 0;
    uint8_t second = 0;
    uint32_t expected = 82800;

    uint32_t result = getNumberOfSeconds(alarm, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetNumberOfSeconds_0h(void) {
    scheduledAlarm_t alarm = {1,1,0,0};

    // uint8_t dayOfWeek = 0;
    // uint8_t hour = 23;    
    // uint8_t minute = 0;
    uint8_t second = 0;
    uint32_t expected = 86400;

    uint32_t result = getNumberOfSeconds(alarm, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

// ------------------------------------------
// Test Runner
// ------------------------------------------
int main( int argc, char **argv) {
    UNITY_BEGIN();    
        // ------------------------------------------
        // Test getSecondstoAlarm 
        // ------------------------------------------
        RUN_TEST(testGetSecondsToAlarm_in_10_min);
        RUN_TEST(testGetSecondsToAlarm_in_10_min255Up);
        RUN_TEST(testGetSecondsToAlarm_in_10_min255Dn);

        RUN_TEST(testGetSecondsToAlarm_in_10_minBefore0);
        RUN_TEST(testGetSecondsToAlarm_in_10);
        RUN_TEST(testGetSecondsToAlarm_0);
        RUN_TEST(testGetSecondsToAlarm_max);
        RUN_TEST(testGetSecondsToAlarm_1h);
        RUN_TEST(testGetSecondsToAlarm_1h_beforeNoon);
        RUN_TEST(testGetSecondsToAlarm_23h45);
        RUN_TEST(testGetSecondsToAlarm_1week);

        RUN_TEST(testGetNumberOfSeconds_23h);
        RUN_TEST(testGetNumberOfSeconds_0h);

    UNITY_END();
}    
