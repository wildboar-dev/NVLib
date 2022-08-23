//--------------------------------------------------
// Unit Tests: LoadUtils
//
// @author: Wild Boar
//
// @date: 2021-08-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/FileUtils.h>
#include <NVLib/DrawUtils.h>
#include <NVLib/LoadUtils.h>
using namespace NVLib;

#include <UnitTestLib/ImageTester.h>

//--------------------------------------------------
// Load Gray Image
//--------------------------------------------------

/**
 * @brief Confirm that I am able to load a gray image
 */
TEST(LoadUtils_Test, load_gray_image_success) 
{
    // Setup
    Mat actual = Mat_<uchar>::zeros(500, 500); NVLib::DrawUtils::DrawFilledRect(actual, Rect(100, 100, 300, 300), Scalar(100));

    if (FileUtils::Exists("gray.png")) FileUtils::Remove("gray.png");
    imwrite("gray.png", actual);

    // Execute
    Mat expected = NVLib::LoadUtils::LoadGray("gray.png");

    // Confirm
    NVL_TestTools::ImageTester::ExactMatch(actual, expected);

    // Teardown
    if (FileUtils::Exists("gray.png")) FileUtils::Remove("gray.png");
}

/**
 * @brief Confirm that failure to load a gray image is done gracefully
 */
TEST(LoadUtils_Test, Load_gray_image_fail) 
{
    // Setup
    if (FileUtils::Exists("gray.png")) FileUtils::Remove("gray.png");
    auto expected = string("Unable to load image: gray.png");

	// Execute
	try
	{
        NVLib::LoadUtils::LoadGray("gray.png");
		FAIL() << "Expected exception: " << expected;
	}
	catch(runtime_error exception)
	{
		ASSERT_EQ(exception.what(), expected);
	}
	catch(...)
	{
		FAIL() << "Expected exception: " << expected;
	}
}