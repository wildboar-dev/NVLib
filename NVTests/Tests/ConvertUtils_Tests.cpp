//--------------------------------------------------
// Unit Tests for class ConvertUtils
//
// @author: Wild Boar
//
// @date: 2021-08-27
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/ConvertUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test: Verify basic 2d to 2f conversion
 */
TEST(ConvertUtils_Test, convert_2d_to_2f)
{
	// Setup
	auto input = vector<Point2d> { Point2d(1.4, 2.3), Point2d(7.2, 2.2), Point2d(8.22222, 9.4444) };

	// Execute
	auto output = vector<Point2f>(); 
	ConvertUtils::ConvertPoints(input, output);

	// Confirm
	ASSERT_EQ(output.size(), input.size());

	ASSERT_EQ(output[0].x, 1.4f);
	ASSERT_EQ(output[0].y, 2.3f);

	ASSERT_EQ(output[1].x, 7.2f);
	ASSERT_EQ(output[1].y, 2.2f);

	ASSERT_EQ(output[2].x, 8.22222f);
	ASSERT_EQ(output[2].y, 9.4444f);
}

/**
 * @brief Test: Verify basic 2d to int conversion
 */
TEST(ConvertUtils_Test, convert_2d_to_int)
{
	// Setup
	auto input = vector<Point2d> { Point2d(1.4, 2.5), Point2d(7.2, 2.2), Point2d(8.22222, 9.6444) };

	// Execute
	auto output = vector<Point>(); 
	ConvertUtils::ConvertPoints(input, output);

	// Confirm
	ASSERT_EQ(output.size(), input.size());

	ASSERT_EQ(output[0].x, 1);
	ASSERT_EQ(output[0].y, 3);

	ASSERT_EQ(output[1].x, 7);
	ASSERT_EQ(output[1].y, 2);

	ASSERT_EQ(output[2].x, 8);
	ASSERT_EQ(output[2].y, 10);
}