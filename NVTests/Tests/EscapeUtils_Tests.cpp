//--------------------------------------------------
// Unit Tests for class EscapeUtils
//
// @author: Wild Boar
//
// @date: 2021-10-14
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/EscapeUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test: make sure that we are escaping quotes
 */
TEST(EscapeUtils_Test, escape_quotes)
{
	// Setup
	auto input = string("Hello 'Trevor', how are \"you\"?");

	// Execute
	auto transformed = NVLib::EscapeUtils::MySqlEscape(input);	

	// Confirm
	ASSERT_EQ(transformed, "Hello \\'Trevor\\', how are \\\"you\\\"?");
}
