//--------------------------------------------------
// Unit Tests for class ZipUtils
//
// @author: Wild Boar
//
// @date: 2022-01-06
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/ZipUtils.h>
using namespace NVLib;

#include <UnitTestLib/SnippetTester.h>

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm lossless zip and unzip test
 */
TEST(ZipUtils_Test, zip_and_unzip)
{
	// Setup: Make sure that the directories exists
	if (NVLib::FileUtils::Exists("input_folder")) NVLib::FileUtils::RemoveAll("input_folder");
	if (NVLib::FileUtils::Exists("output_folder")) NVLib::FileUtils::RemoveAll("output_folder");
	NVLib::FileUtils::AddFolder("input_folder"); NVLib::FileUtils::AddFolder("output_folder");

	// Setup: Populate the input folder with given files
	for (auto i=0; i < 5; i++) 
	{
		auto path = stringstream(); path << "input_folder/test_" << setw(4) << setfill('0') << i << ".txt";
		auto content = stringstream(); content << "This is file content: " << (i + 1) << endl;
		NVLib::FileUtils::WriteFile(path.str(), content.str());
	}

	// Execute
	ZipUtils::Zip("input_folder/test.zip", "input_folder");
	ASSERT_TRUE(NVLib::FileUtils::Exists("input_folder/test.zip"));
	ZipUtils::UnZip("input_folder/test.zip", "output_folder");

	// Confirm
	ASSERT_EQ(NVLib::FileUtils::GetFileCount("output_folder"), 5);

	for (auto i = 0; i < 5; i++) 
	{
		auto path = stringstream(); path << "output_folder/test_" << setw(4) << setfill('0') << i << ".txt";
		auto content = stringstream(); content << "This is file content: " << (i + 1) << endl;
		NVL_TestTools::SnippetTester::Compare(path.str(), content.str());
	}
}

