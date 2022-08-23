//--------------------------------------------------
// Unit Tests for class Parameters
//
// @author: Wild Boar
//
// @date: 2022-02-19
//--------------------------------------------------

#include <fstream>
#include <iostream>
using namespace std;

#include <gtest/gtest.h>

#include <NVLib/FileUtils.h>
#include <NVLib/Parameters/Parameters.h>
#include <NVLib/Parameters/ParameterLoader.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm the loading of parameters
 */
TEST(Parameters_Test, parameter_confirmation)
{
	// Setup
	if (NVLib::FileUtils::Exists("test_config.xml")) NVLib::FileUtils::Remove("test_config.xml");	
	auto writer = ofstream("test_config.xml");
	writer << "<?xml version=\"1.0.\"?>" << endl;
	writer << "<opencv_storage>" << endl;
	writer << "\t<entry_1>First</entry_1>" << endl;
	writer << "\t<entry_2>Second</entry_2>" << endl;
	writer << "\t<entry_3>Third</entry_3>" << endl;
	writer << "\t<entry_4>Fourth</entry_4>" << endl;
	writer << "\t<entry_5>Fifth</entry_5>" << endl;
	writer << "</opencv_storage>" << endl;
	writer.close();

	// Execute
	auto parameters = ParameterLoader::Load("test_config.xml");

	// Confirm
	ASSERT_EQ(parameters->Count(), 5);
	ASSERT_EQ(parameters->Get("entry_1"), "First");
	ASSERT_EQ(parameters->Get("entry_2"), "Second");
	ASSERT_EQ(parameters->Get("entry_3"), "Third");
	ASSERT_EQ(parameters->Get("entry_4"), "Fourth");
	ASSERT_EQ(parameters->Get("entry_5"), "Fifth");
	ASSERT_TRUE(parameters->Contains("entry_1"));
	ASSERT_FALSE(parameters->Contains("something"));

	// Teardown
	delete parameters;
}
