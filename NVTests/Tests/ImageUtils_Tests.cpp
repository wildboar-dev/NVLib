//--------------------------------------------------
// Unit Tests: ImageUtils
//
// @author: Wild Boar
//
// @date: 2021-08-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/DrawUtils.h>
#include <NVLib/ImageUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that mask inversion is working correctly
 */
TEST(ImageUtils_Test, invert_mask) 
{
    // Setup
    Mat mask = Mat_<uchar>::zeros(500, 500);
    DrawUtils::DrawFilledRect(mask, Rect(100, 100, 300, 300), Scalar(255));

    // Execute
    auto beforeCount = ImageUtils::GetPixelCount(mask, Scalar(255));
    Mat inverted = ImageUtils::InvertMask(mask);
    auto afterCount = ImageUtils::GetPixelCount(inverted, Scalar(255));

    // Confirm
    ASSERT_EQ(beforeCount, 90000);
    ASSERT_EQ(afterCount, 160000);
}

/**
 * @brief Confirm the calculation of an inner and outer histogram given a mask
 */
TEST(ImageUtils_Test, in_out_histogram) 
{
    // Setup
    Mat image = Mat_<uchar>::zeros(500, 500); Mat mask = Mat_<uchar>::zeros(500, 500);
    DrawUtils::DrawFilledRect(image, Rect(100, 100, 300, 300), Scalar(128));
    DrawUtils::DrawFilledRect(mask, Rect(200, 200, 200, 200), Scalar(255));

    Mat inner, outer; 

    // Execute
    ImageUtils::GetInOutHistograms(image, mask, inner, outer);
    auto innerData = (int *) inner.data; auto outerData = (int *) outer.data;

    // Confirm
    ASSERT_EQ(innerData[0], 0);
    ASSERT_EQ(innerData[128], 40000);
    ASSERT_EQ(innerData[255], 0);

    ASSERT_EQ(outerData[0], 160000);
    ASSERT_EQ(outerData[128], 50000);
    ASSERT_EQ(outerData[255], 0);
}

/**
 * @brief Confirm that the determination of a pixel count from a histogram is correct
 */
TEST(ImageUtils_Test, pixel_count_histogram) 
{
    // Setup
    Mat image = Mat_<uchar>::zeros(500, 500); Mat mask = Mat_<uchar>::zeros(500, 500);
    DrawUtils::DrawFilledRect(image, Rect(100, 100, 300, 300), Scalar(128));
    DrawUtils::DrawFilledRect(mask, Rect(200, 200, 200, 200), Scalar(255));

    Mat inner, outer; ImageUtils::GetInOutHistograms(image, mask, inner, outer);

    // Execute
    auto innerCount = ImageUtils::GetPixelCount(inner);
    auto outercount = ImageUtils::GetPixelCount(outer);

    // Confirm
    ASSERT_EQ(innerCount, 40000);
    ASSERT_EQ(outercount, 210000);
}

/**
 * @brief Confirm the conversion of a histogram to a probability distribution
 */
TEST(ImageUtils_Test, probabity_distribution_conversion) 
{
    // Setup
    Mat image = Mat_<uchar>::zeros(500, 500); Mat mask = Mat_<uchar>::zeros(500, 500);
    DrawUtils::DrawFilledRect(image, Rect(100, 100, 300, 300), Scalar(128));
    DrawUtils::DrawFilledRect(mask, Rect(200, 200, 200, 200), Scalar(255));

    Mat inner, outer; ImageUtils::GetInOutHistograms(image, mask, inner, outer);
    
    Mat innerPD, outerPD;
    
    // Execute
    auto innerCount = ImageUtils::Hist2PD(inner, innerPD);
    auto outerCount = ImageUtils::Hist2PD(outer, outerPD);
    auto innerData = (double *) innerPD.data; auto outerData = (double *) outerPD.data;

    // Confirm
    ASSERT_EQ(innerCount, 40000);
    ASSERT_EQ(innerData[0], 0);
    ASSERT_EQ(innerData[128], 1);
    ASSERT_EQ(innerData[255], 0);

    ASSERT_EQ(outerCount, 210000);
    ASSERT_NEAR(outerData[0], 0.761905, 1e-4);
    ASSERT_NEAR(outerData[128], 0.238095, 1e-4);
    ASSERT_EQ(outerData[255], 0);
}


/**
 * @brief Check that pixel count is correct on a color image
 */
TEST(ImageUtils_Test, pixel_count_color_image) 
{
    // Setup
    Mat image = Mat_<Vec3b>::zeros(500, 500);
    DrawUtils::DrawFilledRect(image, Rect(100, 100, 300, 300), Scalar(0, 255, 0));

    // Execute
    auto count = ImageUtils::GetPixelCount(image, Scalar(0, 255, 0));

    // Confirm
    ASSERT_EQ(count, 90000);
}
