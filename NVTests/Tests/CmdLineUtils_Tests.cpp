//--------------------------------------------------
// Unit Tests for class CmdLineUtils
//
// @author: Wild Boar
//
// @date: 2021-08-31
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/CmdLineUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test: Confirm that the call gives the desired result
 */
TEST(CmdLineUtils_Test, verify_call)
{
	// Execute
	auto result = CmdLineUtils::Execute("echo hello world");

	// Confirm
	ASSERT_EQ(result, "hello world\n");
}
