//--------------------------------------------------
// Unit Test: DrawUtils RandomGray
//
// @author: Wild Boar
//
// @date: 2021-08-27
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/ImageUtils.h>
#include <NVLib/DrawUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
* @brief Confirm the size of the image
*/
TEST(RandomGray_Test, ConfirmSize) 
{
    // Execute
    Mat image = DrawUtils::GetRandomGray(Size(500, 500));

    // Confirm
    ASSERT_FALSE(image.empty());
    ASSERT_EQ(image.rows, 500);
    ASSERT_EQ(image.cols, 500);
    ASSERT_EQ(image.channels(), 1);
}

/**
 * @brief Confirm that we have more than 100 different colors
 */
TEST(RandomGray_Test, ConfirmDistribution) 
{
    // Setup
    Mat image = DrawUtils::GetRandomGray(Size(500, 500));
    Mat H = ImageUtils::GetHistogram(image);

    auto differentColors = 0; auto hData = (int *)H.data;
    for (auto i = 0; i < 256; i++) 
    {
        if (hData[i] > 0) differentColors++;
    }

    // Confirm
    ASSERT_GT(differentColors, 100);
}