//--------------------------------------------------
// Unit Tests: FileUtils
//
// @author: Wild Boar
//
// @date: 2021-09-05
//--------------------------------------------------

#include <fstream>
#include <iostream>
using namespace std;

#include <gtest/gtest.h>

#include <NVLib/FileUtils.h>
using namespace NVLib;

//--------------------------------------------------
// TESTS
//--------------------------------------------------

/**
 * @brief Test the file count of an empty folder
 */
TEST(FileUtils_Test, folder_file_count_0) 
{
    // Setup
    if (FileUtils::Exists("TestFolder")) FileUtils::RemoveAll("TestFolder");
    FileUtils::AddFolder("TestFolder");

    // Execute
    auto count = FileUtils::GetFileCount("TestFolder");

    // Verify
    ASSERT_EQ(count, 0);
}

/**
 * @brief Test the file count if there is one file in the folder
 */
TEST(FileUtils_Test, folder_file_count_1) 
{
    // Setup
    if (FileUtils::Exists("TestFolder")) FileUtils::RemoveAll("TestFolder");
    FileUtils::AddFolder("TestFolder");

    FileUtils::WriteFile("TestFolder/file_1.txt", "this is file 1");

    // Execute
    auto count = FileUtils::GetFileCount("TestFolder");

    // Verify
    ASSERT_EQ(count, 1);
}

/**
 * @brief Test the file count with 5 files
 */
TEST(FileUtils_Test, folder_file_count_4) 
{
    // Setup
    if (FileUtils::Exists("TestFolder")) FileUtils::RemoveAll("TestFolder");
    FileUtils::AddFolder("TestFolder");

    FileUtils::WriteFile("TestFolder/file_1.txt", "this is file 1");
    FileUtils::WriteFile("TestFolder/file_2.txt", "this is file 2");
    FileUtils::WriteFile("TestFolder/file_3.txt", "this is file 3");
    FileUtils::WriteFile("TestFolder/file_4.txt", "this is file 4");
    FileUtils::AddFolders("TestFolder/Test");

    // Execute
    auto count = FileUtils::GetFileCount("TestFolder");

    // Verify
    ASSERT_EQ(count, 4);
}

/**
 * @brief Test the generation of a temp folder and file pair
 */
TEST(FileUtils_Test, temp_folder_and_file) 
{
    // Setup: Create the working folder
    if (FileUtils::Exists("TestFolder")) FileUtils::RemoveAll("TestFolder");
    FileUtils::AddFolders("TestFolder");

    // Execute
    auto tempFolder = FileUtils::MakeTempFolder("TestFolder");
    auto tempFile = FileUtils::MakeTempFile(tempFolder, ".txt");

    // Verify
    ASSERT_GT(tempFolder.length(), string("TestFolder").length());
    ASSERT_GT(tempFile.length(), tempFolder.length());
    ASSERT_TRUE(FileUtils::Exists(tempFolder));
    ASSERT_TRUE(FileUtils::Exists(tempFile));
    ASSERT_TRUE(FileUtils::IsFolder(tempFolder));
    ASSERT_FALSE(FileUtils::IsFolder(tempFile));
}