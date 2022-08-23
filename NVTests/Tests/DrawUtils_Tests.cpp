//--------------------------------------------------
// Unit Tests: DrawUtils
//
// @author: Wild Boar
//
// @date: 2021-08-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/ImageUtils.h>
#include <NVLib/DrawUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that we can render the outline
 */
TEST(DrawUtils_Test, draw_outline)
{
	// Setup
    auto points = vector<Point> { Point(100, 100), Point(399, 100), Point(399, 399), Point(100, 399)};

	Mat image = Mat_<Vec3b>::zeros(500, 500);
    DrawUtils::DrawPolyOutline(image, Scalar(0, 255, 0), points);

	// Execute
	auto pixelCount = NVLib::ImageUtils::GetPixelCount(image, Scalar(0,255, 0));

	// Confirm
	ASSERT_EQ(pixelCount, 1196);
}

/**
 * @brief Confirm that we can render the card as a mask
 */
TEST(DrawUtils_Test, draw_mask)
{
	// Setup
    auto points = vector<Point> { Point(100, 100), Point(399, 100), Point(399, 399), Point(100, 399)};
	Mat mask = DrawUtils::GetPolyMask(Size(500, 500), points);

	// Execute
	auto pixelCount = NVLib::ImageUtils::GetPixelCount(mask, Scalar(0));

	// Confirm
	ASSERT_EQ(pixelCount, 160000);
}

/**
 * @brief Confirm the ability to render a rectangular mask
 */
TEST(DrawUtils_Test, draw_rectangle_mask) 
{
	// Setup
	Mat mask = NVLib::DrawUtils::GetRectangleMask(Size(500, 500), Rect(100, 100, 300, 300));

	// Execute
	auto pixelCount = NVLib::ImageUtils::GetPixelCount(mask, Scalar(0));

	// Confirm
	ASSERT_EQ(mask.rows, 500);
	ASSERT_EQ(mask.cols, 500);
	ASSERT_EQ(pixelCount, 160000);
}