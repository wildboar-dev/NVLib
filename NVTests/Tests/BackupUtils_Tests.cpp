//--------------------------------------------------
// Unit Tests for class BackupUtils
//
// @author: Wild Boar
//
// @date: 2021-09-05
//--------------------------------------------------

#include <fstream>
#include <iostream>
using namespace std;

#include <gtest/gtest.h>

#include <UnitTestLib/SnippetTester.h>

#include <NVLib/FileUtils.h>
#include <NVLib/BackupUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test: When the folder does not exist, it is created
 */
TEST(BackupUtils_Test, folder_generation)
{
	// Remove the backup folder if it exists
	if (NVLib::FileUtils::Exists("Backup")) NVLib::FileUtils::RemoveAll("Backup");

	// Create a file to backup
	auto writer = ofstream("test.txt", ios::trunc);
	writer << "this is the first line" << endl;
	writer << "this is the second line" << endl;
	writer.close();

	// Execute
	auto folderExists_1 = NVLib::FileUtils::Exists("Backup");
	BackupUtils::Backup("Backup", "test.txt");
	auto folderExists_2 = NVLib::FileUtils::Exists("Backup");

	// Confirm
	ASSERT_FALSE(folderExists_1);
	ASSERT_TRUE(folderExists_2);	
}

/**
 * @brief Test: Save only one file to this folder
 */
TEST(BackupUtils_Test, single_save)
{
	// Remove the backup folder if it exists
	if (NVLib::FileUtils::Exists("Backup")) NVLib::FileUtils::RemoveAll("Backup");
	if (NVLib::FileUtils::Exists("test.txt")) NVLib::FileUtils::Remove("test.txt");

	// Create a file to backup
	auto writer = stringstream();
	writer << "this is the first line" << endl;
	writer << "this is the second line" << endl;
	FileUtils::WriteFile("test.txt", writer.str());

	// Execute
	BackupUtils::Backup("Backup", "test.txt");

	// Confirm
	NVL_TestTools::SnippetTester::Compare("Backup/test.txt", writer.str());
}

/**
 * @brief Test: Save two files to this folder
 */
TEST(BackupUtils_Test, multiple_save)
{
	// Remove the backup folder if it exists
	if (NVLib::FileUtils::Exists("Backup")) NVLib::FileUtils::RemoveAll("Backup");
	if (NVLib::FileUtils::Exists("test_1.txt")) NVLib::FileUtils::Remove("test_1.txt");
	if (NVLib::FileUtils::Exists("test_2.txt")) NVLib::FileUtils::Remove("test_2.txt");

	// Create a file to backup
	FileUtils::WriteFile("test_1.txt", "some text");
	FileUtils::WriteFile("test_2.txt", "some text");

	// Execute
	BackupUtils::Backup("Backup", "test_1.txt");
	BackupUtils::Backup("Backup", "test_2.txt");
	auto count = FileUtils::GetFileCount("Backup");

	// Confirm
	ASSERT_EQ(count, 2);
}

/**
 * @brief Test: Overwrite a file in the folder
 */
TEST(BackupUtils_Test, file_overwrite)
{
	// Remove the backup folder if it exists
	if (NVLib::FileUtils::Exists("Backup")) NVLib::FileUtils::RemoveAll("Backup");
	if (NVLib::FileUtils::Exists("test.txt")) NVLib::FileUtils::Remove("test.txt");

	// Execute
	FileUtils::WriteFile("test.txt", "first version of the file");
	BackupUtils::Backup("Backup", "test.txt");
	if (NVLib::FileUtils::Exists("test.txt")) NVLib::FileUtils::Remove("test.txt");

	auto content_1 = FileUtils::ReadFile("Backup/test.txt");

	FileUtils::WriteFile("test.txt", "second version of the file");
	BackupUtils::Backup("Backup", "test.txt");

	auto content_2 = FileUtils::ReadFile("Backup/test.txt");

	// Confirm
	ASSERT_EQ(content_1, "first version of the file");
	ASSERT_EQ(content_2, "second version of the file");
}

/**
 * @brief Test: Attempting to backup a non-existent file leads to error
 */
TEST(BackupUtils_Test, missing_file_exception)
{
	// Setup
	auto expected = string("File not found: unknown");

	// Execute
	try
	{
		BackupUtils::Backup("Backup", "unknown");
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
