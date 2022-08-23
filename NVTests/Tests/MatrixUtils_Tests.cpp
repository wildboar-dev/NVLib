//--------------------------------------------------
// Unit Tests for MatrixUtils
//
// @author: Wild Boar
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/MatrixUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * ConvertMatrix to vector works
 */
TEST(MatrixUtils_Test, Matrix2Vector)
{
	// Setup
	Mat data = (Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);

	// Execute
	auto actual = vector<double>(); MatrixUtils::Matrix2Vector(data, actual);

	// Confirm
	for (auto i = 0; i < 9; i++) ASSERT_EQ(i + 1, actual[i]);
}

/**
 * Prove that the vector to matrix stuff works
 */
TEST(MatrixUtils_Test, Vector2Matrix)
{
	// Setup
	auto data = vector<double>(); for (auto i = 0; i < 9; i++) data.push_back((i + 1) * 2);

	// Execute
	auto actual = MatrixUtils::Vector2Matrix(3, 3, data);

	// Confirm
	for (auto row = 0; row < 3; row++) 
	{
		for (auto column = 0; column < 3; column++) 
		{
			auto index = column + row * 3;
			auto expected = (index + 1) * 2;
			auto actualValue = actual.at<double>(row, column);
			ASSERT_EQ(expected, actualValue);
		}
	}
}

/**
 * Size mismatch error handled
 */
TEST(MatrixUtils_Test, Vector2MatrixSizeMismatch)
{
	auto expected = string("Matrix size does not match the vector");
	auto data = vector<double>{ 1, 2, 3, 4 };

	try 
	{
		Mat output = MatrixUtils::Vector2Matrix(4, 5, data);
		FAIL() << "Expected exception: " << expected;
	}
	catch (runtime_error exception) 
	{
		ASSERT_EQ(expected, exception.what());
	}
	catch (...) 
	{
		FAIL() << "Expected exception: " << expected;
	}
}