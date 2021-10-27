/*
 * File: test_main.cpp
 * Project: test
 * Created Date: Monday, October 25th 2021, 19:21:39 am 
 * 
 * Copyright (c) 2021 Eric Beaudet
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
// Test addOneHour (uint8_t hour)
// ------------------------------------------
void testAddOneHour_wrap(void) {
    uint8_t alarmHour = 23;    
    uint8_t expected = 0;

    uint8_t result = addOneHour(alarmHour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testAddOneHour_normal(void) {
    uint8_t alarmHour = 1;    
    uint8_t expected = 2;

    uint8_t result = addOneHour(alarmHour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test substractOneHour (uint8_t hour) 
// ------------------------------------------
void testSubstractOneHour_wrap(void) {
    uint8_t alarmHour = 0;    
    uint8_t expected = 23;

    uint8_t result = substractOneHour(alarmHour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testSubstractOneHour_normal(void) {
    uint8_t alarmHour = 4;    
    uint8_t expected = 3;

    uint8_t result = substractOneHour(alarmHour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test substractOneMinute (uint8_t minute) 
// ------------------------------------------
void testSubstractOneMinute_wrap(void) {
    uint8_t alarmMinute = 0;    
    uint8_t expected = 59;

    uint8_t result = substractOneMinute(alarmMinute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testSubstractOneMinute_normal(void) {
    uint8_t alarmMinute = 4;    
    uint8_t expected = 3;

    uint8_t result = substractOneMinute(alarmMinute);

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
// Test getHoursDiff(uint8_t alarmHour, uint8_t hour)
// ------------------------------------------
void testGetHoursDiff_beginDay(void) {
    uint8_t alarmHour = 1;
    uint8_t hour = 0;
    uint8_t expected = 1;

    uint8_t result = getHoursDiff(alarmHour, hour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetHoursDiff_endDay(void) {
    uint8_t alarmHour = 0;
    uint8_t hour = 1;
    uint8_t expected = 23;

    uint8_t result = getHoursDiff(alarmHour, hour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetHoursDiff_normalUp(void) {
    uint8_t alarmHour = 5;
    uint8_t hour = 3;
    uint8_t expected = 2;

    uint8_t result = getHoursDiff(alarmHour, hour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetHoursDiff_normalDn(void) {
    uint8_t alarmHour = 3;
    uint8_t hour = 5;
    uint8_t expected = 22;

    uint8_t result = getHoursDiff(alarmHour, hour);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test getMinutesDiff(uint8_t alarmMinute, uint8_t minute) 
// ------------------------------------------
void testGetMinutesDiff_beginHour(void) {
    uint8_t alarmMinute = 1;
    uint8_t minute = 0;
    uint8_t expected = 1;

    uint8_t result = getMinutesOrSecondDiff(alarmMinute, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetMinutesDiff_endHour(void) {
    uint8_t alarmMinute = 0;
    uint8_t minute = 1;
    uint8_t expected = 59;

    uint8_t result = getMinutesOrSecondDiff(alarmMinute, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetMinutesDiff_normalUp(void) {
    uint8_t alarmMinute = 5;
    uint8_t minute = 3;
    uint8_t expected = 2;

    uint8_t result = getMinutesOrSecondDiff(alarmMinute, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetMinutesDiff_normalDn(void) {
    uint8_t alarmMinute = 3;
    uint8_t minute = 5;
    uint8_t expected = 58;

    uint8_t result = getMinutesOrSecondDiff(alarmMinute, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetMinutesDiff_middle(void) {
    uint8_t alarmMinute = 0;
    uint8_t minute = 30;
    uint8_t expected = 30;

    uint8_t result = getMinutesOrSecondDiff(alarmMinute, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test getDaysFromNow(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute)
// ------------------------------------------
void testGetDaysFromNow_AlarmAtLaterHourThanNowUp(void) {
    scheduledAlarm_t alarm = {1,5,12,0};
    
    uint8_t today = 3;
    uint8_t hour = 11;
    uint8_t minute = 0;

    uint8_t expected = 2;

    uint8_t result = getDaysFromNow(alarm, today, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysFromNow_AlarmAtLaterHourThanNowDn(void) {
    scheduledAlarm_t alarm = {1,3,12,0};
    
    uint8_t today = 5;
    uint8_t hour = 11;
    uint8_t minute = 0;

    uint8_t expected = 5;

    uint8_t result = getDaysFromNow(alarm, today, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysFromNow_AlarmAtEarlierHourThanNowUp(void) {
    scheduledAlarm_t alarm = {1,5,12,0};
    
    uint8_t today = 3;
    uint8_t hour = 16;
    uint8_t minute = 0;

    uint8_t expected = 1;

    uint8_t result = getDaysFromNow(alarm, today, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysFromNow_AlarmAtEarlierHourThanNowDn(void) {
    scheduledAlarm_t alarm = {1,3,12,0};
    
    uint8_t today = 5;
    uint8_t hour = 16;
    uint8_t minute = 0;

    uint8_t expected = 4;

    uint8_t result = getDaysFromNow(alarm, today, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysFromNow_AlarmAtEarlierMinuteThanNowUp(void) {
    scheduledAlarm_t alarm = {1,5,12,0};
    
    uint8_t today = 3;
    uint8_t hour = 12;
    uint8_t minute = 10;

    uint8_t expected = 1;

    uint8_t result = getDaysFromNow(alarm, today, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetDaysFromNow_AlarmAtEarlierMinuteThanNowDn(void) {
    scheduledAlarm_t alarm = {1,3,12,0};
    
    uint8_t today = 5;
    uint8_t hour = 12;
    uint8_t minute = 10;

    uint8_t expected = 4;

    uint8_t result = getDaysFromNow(alarm, today, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test getHoursFromNow(const scheduledAlarm_t& alarm, uint8_t hour, uint8_t minute)
// ------------------------------------------
void testGetHoursFromNow_AlarmAtLaterMinuteThanNowUp(void) {
    scheduledAlarm_t alarm = {1,5,12,10};
    
    uint8_t hour = 10;
    uint8_t minute = 0;

    uint8_t expected = 2;

    uint8_t result = getHoursFromNow(alarm, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetHoursFromNow_AlarmAtLaterMinuteThanNowDn(void) {
    scheduledAlarm_t alarm = {1,3,12,10};
    
    uint8_t hour = 13;
    uint8_t minute = 0;

    uint8_t expected = 23;

    uint8_t result = getHoursFromNow(alarm, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetHoursFromNow_AlarmAtEarlierMinuteThanNowUp(void) {
    scheduledAlarm_t alarm = {1,5,12,0};
    
    uint8_t hour = 10;
    uint8_t minute = 10;

    uint8_t expected = 1;

    uint8_t result = getHoursFromNow(alarm, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetHoursFromNow_AlarmAtEarlierHourThanNowDn(void) {
    scheduledAlarm_t alarm = {1,3,12,0};
    
    uint8_t hour = 13;
    uint8_t minute = 10;

    uint8_t expected = 22;

    uint8_t result = getHoursFromNow(alarm, hour, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test getMinutesFromNow(const scheduledAlarm_t& alarm, uint8_t minute)
// ------------------------------------------
void testGetMinutesFromNow_AlarmAtSameMinuteThanNow(void) {
    scheduledAlarm_t alarm = {1,5,12,12};
        
    uint8_t minute = 12;
    uint8_t expected = 60;

    uint8_t result = getMinutesFromNow(alarm, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetMinutesFromNow_AlarmAtLaterMinuteThanNowUp(void) {
    scheduledAlarm_t alarm = {1,5,12,12};
        
    uint8_t minute = 10;
    uint8_t expected = 2;

    uint8_t result = getMinutesFromNow(alarm, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetMinutesFromNow_AlarmAtEarlierHourThanNowDn(void) {
    scheduledAlarm_t alarm = {1,3,12,12};
        
    uint8_t minute = 14;
    uint8_t expected = 57;

    uint8_t result = getMinutesFromNow(alarm, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test getSecondsfromNow(uint8_t second)
// ------------------------------------------
void testGetSecondsfromNow_AlarmAtSameSecondThanNow(void) {       
    uint8_t second = 0;
    uint8_t expected = 0;

    uint8_t result = getSecondsfromNow(second);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetSecondsfromNow_AlarmAtLaterSecondThanNowUp(void) {
    uint8_t second = 10;
    uint8_t expected = 50;

    uint8_t result = getSecondsfromNow(second);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetSecondsfromNow_AlarmAtEarlierSecondThanNowDn(void) {
    uint8_t second = 58;
    uint8_t expected = 2;

    uint8_t result = getSecondsfromNow(second);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

// ------------------------------------------
// Test getSecondsfromAlarm(const scheduledAlarm_t& alarm, uint8_t dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second)
// ------------------------------------------
void testGetSecondsfromAlarm_in_10_min(void) {
    scheduledAlarm_t alarm = {1,255,255,10};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 0;
    uint8_t second = 0;

    int32_t expected = 600;

    int32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsfromAlarm_in_10_minBefore0(void) {
    scheduledAlarm_t alarm = {1,255,255,0};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 50;
    uint8_t second = 0;

    int32_t expected = 600;

    int32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsfromAlarm_in_10(void) {
    scheduledAlarm_t alarm = {1,255,255,0};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 49;
    uint8_t second = 30;

    int32_t expected = 630;

    int32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetMinutesFromNow(void) {
    scheduledAlarm_t alarm = {1,255,255,10};

    uint8_t minute = 0;
    uint8_t expected = 10;

    uint8_t result = getMinutesFromNow(alarm, minute);

    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void testGetSecondsfromAlarm_in_24h(void) {
    scheduledAlarm_t alarm = {1,255,17,00};

    uint8_t dayOfWeek = 5;
    uint8_t hour = 17;    
    uint8_t minute = 0;
    uint8_t second = 0;

    uint32_t expected = 86400;

    uint32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsfromAlarm_0(void) {
    scheduledAlarm_t alarm = {1,255,9,00};

    uint8_t dayOfWeek = 1;
    uint8_t hour = 21;    
    uint8_t minute = 44;
    uint8_t second = 50;

    uint32_t expected = 40510;

    uint32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsfromAlarm_max(void) {
    scheduledAlarm_t alarm = {1,0,9,0};

    uint8_t dayOfWeek = 0;
    uint8_t hour = 9;    
    uint8_t minute = 0;
    uint8_t second = 10;

    uint32_t expected = 604799;

    uint32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsfromAlarm_1h(void) {
    scheduledAlarm_t alarm = {1,255,0,0};

    uint8_t dayOfWeek = 0;
    uint8_t hour = 23;    
    uint8_t minute = 0;
    uint8_t second = 0;

    uint32_t expected = 3600;

    uint32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);
}

void testGetSecondsfromAlarm_1h_beforeNoon(void) {
    scheduledAlarm_t alarm = {1,255,12,0};

    uint8_t dayOfWeek = 0;
    uint8_t hour = 11;    
    uint8_t minute = 0;
    uint8_t second = 0;

    uint32_t expected = 3600;

    uint32_t result = getSecondsFromAlarm(alarm, dayOfWeek, hour, minute, second);

    TEST_ASSERT_EQUAL_INT32(expected, result);    
}

// ------------------------------------------
// Test Runner
// ------------------------------------------
int main( int argc, char **argv) {
    UNITY_BEGIN();
        
        // RUN_TEST(testAddOneDay_wrap);
        // RUN_TEST(testAddOneDay_normal);

        // RUN_TEST(testSubstractOneDay_wrap);
        // RUN_TEST(testSubstractOneDay_normal);

        // RUN_TEST(testAddOneHour_wrap);
        // RUN_TEST(testAddOneHour_normal);     

        // RUN_TEST(testSubstractOneHour_wrap);
        // RUN_TEST(testSubstractOneHour_normal);

        // RUN_TEST(testSubstractOneMinute_wrap);
        // RUN_TEST(testSubstractOneMinute_normal);        

        // RUN_TEST(testGetDaysDiff_dim_lun);
        // RUN_TEST(testGetDaysDiff_lun_dim);
        // RUN_TEST(testGetDaysDiff_normalUp);
        // RUN_TEST(testGetDaysDiff_normalDn);

        // RUN_TEST(testGetHoursDiff_beginDay);
        // RUN_TEST(testGetHoursDiff_endDay);
        // RUN_TEST(testGetHoursDiff_normalUp);
        // RUN_TEST(testGetHoursDiff_normalDn);    

        // RUN_TEST(testGetMinutesDiff_beginHour);
        // RUN_TEST(testGetMinutesDiff_endHour);
        // RUN_TEST(testGetMinutesDiff_normalUp);
        // RUN_TEST(testGetMinutesDiff_normalDn);            
        // RUN_TEST(testGetMinutesDiff_middle);   

        // RUN_TEST(testGetDaysFromNow_AlarmAtLaterHourThanNowUp);        
        // RUN_TEST(testGetDaysFromNow_AlarmAtLaterHourThanNowDn);
        // RUN_TEST(testGetDaysFromNow_AlarmAtEarlierHourThanNowUp);        
        // RUN_TEST(testGetDaysFromNow_AlarmAtEarlierHourThanNowDn);        
        // RUN_TEST(testGetDaysFromNow_AlarmAtEarlierMinuteThanNowUp);        
        // RUN_TEST(testGetDaysFromNow_AlarmAtEarlierMinuteThanNowDn); 

        // RUN_TEST(testGetHoursFromNow_AlarmAtLaterMinuteThanNowUp);        
        // RUN_TEST(testGetHoursFromNow_AlarmAtLaterMinuteThanNowDn);
        // RUN_TEST(testGetHoursFromNow_AlarmAtEarlierMinuteThanNowUp);        
        // RUN_TEST(testGetHoursFromNow_AlarmAtEarlierHourThanNowDn);       

        // RUN_TEST(testGetMinutesFromNow_AlarmAtSameMinuteThanNow);        
        // RUN_TEST(testGetMinutesFromNow_AlarmAtLaterMinuteThanNowUp);
        // RUN_TEST(testGetMinutesFromNow_AlarmAtEarlierHourThanNowDn);       

        // RUN_TEST(testGetSecondsfromNow_AlarmAtSameSecondThanNow);        
        // RUN_TEST(testGetSecondsfromNow_AlarmAtLaterSecondThanNowUp);
        // RUN_TEST(testGetSecondsfromNow_AlarmAtEarlierSecondThanNowDn);            

        // RUN_TEST(testGetSecondsfromAlarm_in_10_min);
        // RUN_TEST(testGetSecondsfromAlarm_in_10_minBefore0);
        // RUN_TEST(testGetSecondsfromAlarm_in_10);
        // RUN_TEST(testGetMinutesFromNow);
        // RUN_TEST(testGetSecondsfromAlarm_0);
        // RUN_TEST(testGetSecondsfromAlarm_max);
        // RUN_TEST(testGetSecondsfromAlarm_1h);
        // RUN_TEST(testGetSecondsfromAlarm_1h_beforeNoon);                             
    UNITY_END();
}

//#endif