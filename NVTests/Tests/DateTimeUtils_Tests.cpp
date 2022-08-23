//--------------------------------------------------
// Unit Tests: StringUtils
//
// @author: Wild Boar
//
// @date: 2021-08-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/DateTimeUtils.h>
#include <NVLib/StringUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Conversion Bugs
//--------------------------------------------------

/**
 * @brief Fix a conversion bug
 */
TEST(DateTimeUtils_Test, conversion_bug) 
{
    // Setup
    auto value = NVLib::DateTimeUtils::GetDateTime(12, 7, 2021, 15, 3, 1);

    // Execute
    auto timeString = NVLib::DateTimeUtils::DateTime2String(value, "%Y-%m-%d %H:%M:%S");

    // Test
    ASSERT_EQ(timeString, "2021-07-12 15:03:01");
}

/**
 * @brief Confirm that a bool conversion failure behaves as expected
 */
TEST(DateTimeUtils_Test, bool_conversion_from_string_expected_fail) 
{
	auto expected = "Date conversion failed: not a date";

	try
	{
        auto value = DateTimeUtils::String2DateTime("not a date", "%Y-%m-%d %H:%M:%S");
		FAIL() << "Expected exception: " << expected;
	}
	catch (runtime_error error)
	{
		ASSERT_EQ(error.what(), string(expected));
	}
	catch (...)
	{
		FAIL() << "Expected exception: " << expected;
	}
}