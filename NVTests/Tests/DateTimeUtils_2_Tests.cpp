//--------------------------------------------------
// Unit Tests for DateTimeUtils
//
// @author: Wild Boar
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/DateTimeUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm the creation of a time_t with valid values
 */
TEST(DateTimeUtils_Test, CreateDateTimeBeforeSavings)
{
	// Setup
	auto dateTime = DateTimeUtils::GetDateTime(15, 03, 1977, 16, 20, 1);

	// Execute
	auto day = DateTimeUtils::ExtractDay(dateTime);
	auto month = DateTimeUtils::ExtractMonth(dateTime);
	auto year = DateTimeUtils::ExtractYear(dateTime);
	auto seconds = DateTimeUtils::ExtractSeconds(dateTime);
	auto minutes = DateTimeUtils::ExtractMinutes(dateTime);
	auto hours = DateTimeUtils::ExtractHours(dateTime);

	// Confirm
	ASSERT_EQ(15, day);
	ASSERT_EQ(03, month);
	ASSERT_EQ(1977, year);
	ASSERT_EQ(1, seconds);
	ASSERT_EQ(20, minutes);
	ASSERT_EQ(16, hours);
}

/**
 * @brief Confirm the creation of a time_t with valid values
 */
TEST(DateTimeUtils_Test, CreateDateTimeAfterSavings)
{
	// Setup
	auto dateTime = DateTimeUtils::GetDateTime(15, 06, 1977, 16, 20, 1);

	// Execute
	auto day = DateTimeUtils::ExtractDay(dateTime);
	auto month = DateTimeUtils::ExtractMonth(dateTime);
	auto year = DateTimeUtils::ExtractYear(dateTime);
	auto seconds = DateTimeUtils::ExtractSeconds(dateTime);
	auto minutes = DateTimeUtils::ExtractMinutes(dateTime);
	auto hours = DateTimeUtils::ExtractHours(dateTime);

	// Confirm
	ASSERT_EQ(15, day);
	ASSERT_EQ(06, month);
	ASSERT_EQ(1977, year);
	ASSERT_EQ(1, seconds);
	ASSERT_EQ(20, minutes);
	ASSERT_EQ(16, hours);
}

/**
 * @brief Confirm the creation of a time_t with valid values
 */
TEST(DateTimeUtils_Test, CreateDate)
{
	// Setup
	auto dateTime = DateTimeUtils::GetDate(15, 03, 2021);

	// Execute
	auto day = DateTimeUtils::ExtractDay(dateTime);
	auto month = DateTimeUtils::ExtractMonth(dateTime);
	auto year = DateTimeUtils::ExtractYear(dateTime);

	// Confirm
	ASSERT_EQ(15, day);
	ASSERT_EQ(03, month);
	ASSERT_EQ(2021, year);
}

/**
 * @brief Confirm the creation of a time_t with valid values
 */
TEST(DateTimeUtils_Test, CreateTime)
{
	// Setup
	auto dateTime = DateTimeUtils::GetTime(7, 30, 35);

	// Execute
	auto seconds = DateTimeUtils::ExtractSeconds(dateTime);
	auto minutes = DateTimeUtils::ExtractMinutes(dateTime);
	auto hours = DateTimeUtils::ExtractHours(dateTime);

	// Confirm
	ASSERT_EQ(35, seconds);
	ASSERT_EQ(30, minutes);
	ASSERT_EQ(7, hours);
}

/**
 * @brief Test the conversion of a time_t to a string with a given format
 */
TEST(DateTimeUtils_Test, ConvertDateTime2String) 
{
	// Setup
	auto time = DateTimeUtils::GetDateTime(15, 03, 1977, 12, 30, 45);

	// Execute
	auto timeString = DateTimeUtils::DateTime2String(time, "%Y-%m-%d %H:%M:%S");

	// Confirm
	ASSERT_EQ(timeString, "1977-03-15 12:30:45");
}

/**
 * @brief Test the conversion of a string to a time_t with the string conforming to the given format
 */
TEST(DateTimeUtils_Test, ConvertString2DateTime) 
{
	// Setup
	auto timeString = "1977-03-15 12:30:45";

	// Execute
	auto time = DateTimeUtils::String2DateTime(timeString, "%Y-%m-%d %H:%M:%S");
	auto day = DateTimeUtils::ExtractDay(time);
	auto month = DateTimeUtils::ExtractMonth(time);
	auto year = DateTimeUtils::ExtractYear(time);
	auto seconds = DateTimeUtils::ExtractSeconds(time);
	auto minutes = DateTimeUtils::ExtractMinutes(time);
	auto hours = DateTimeUtils::ExtractHours(time);

	// Confirm
	ASSERT_EQ(15, day);
	ASSERT_EQ(03, month);
	ASSERT_EQ(1977, year);
	ASSERT_EQ(45, seconds);
	ASSERT_EQ(30, minutes);
	ASSERT_EQ(12, hours);
}

/**
 * @brief Confirm the logic to subtract a day from the time
 */
TEST(DateTimeUtils_Test, subtract_day_from_time) 
{
	// Setup
	auto my_date = DateTimeUtils::GetDate(5, 1, 2022);

	// Perform the subtraction
	auto new_date = DateTimeUtils::AddDays(my_date, -10);
	auto timeString = DateTimeUtils::Date2String(new_date);

	// Confirm
	ASSERT_EQ(timeString, "2021-12-26");
}