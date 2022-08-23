//--------------------------------------------------
// Unit Tests for class ConvertUtils
//
// @author: Wild Boar
//
// @date: 2022-05-23
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/PoseUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that we can convert a quaternion to a rotation matrix and back
 */
TEST(PoseUtils_Test, convert_quaternions_2_rotation_matrix)
{
	// Setup
    auto baseQ = Vec4d(1, 2, 3, 4);
	auto expected = PoseUtils::NormalizeQuaternion(baseQ);

	// Execute
    Mat rotation = PoseUtils::Quaternion2Matrix(expected);
    auto action = PoseUtils::Matrix2Quaternion(rotation);
    cout << rotation << endl;

	// Confirm
	ASSERT_NEAR(action[0], expected[0], 1E-8);
	ASSERT_NEAR(action[1], expected[1], 1E-8);
	ASSERT_NEAR(action[2], expected[2], 1E-8);
	ASSERT_NEAR(action[3], expected[3], 1E-8);
}

/**
 * @brief Test the operation of Euler angle conversions
 */
TEST(PoseUtils_Test, euler_angle_conversion) 
{
	// Setup
	auto degrees = Vec3d(40, -20, 10);

	// Convert to matrix
	Mat rotation = PoseUtils::Euler2Matrix(degrees);
	auto estimated = PoseUtils::Matrix2Euler(rotation);

	// Confirm the operation
	ASSERT_NEAR(degrees[0], estimated[0], 1E-4);
	ASSERT_NEAR(degrees[1], estimated[1], 1E-4);
	ASSERT_NEAR(degrees[2], estimated[2], 1E-4);
}