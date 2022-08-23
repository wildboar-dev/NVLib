//--------------------------------------------------
// Unit Tests: StringUtils
//
// @author: Wild Boar
//
// @date: 2021-08-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <UnitTestLib/SnippetTester.h>

#include <NVLib/StringUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test Trim
//--------------------------------------------------

/**
 * @brief A fix for the trim same string bug
 */
TEST(StringUtils_Test, trim_same_string_bug) 
{
    // Setup
    auto myString = string("    \tTest String ");

    // Execute
    StringUtils::Trim(myString, myString);

    // Confirm
    ASSERT_EQ(myString, "Test String");
}

//--------------------------------------------------
// Test GetBracketText
//--------------------------------------------------

/**
 * @brief TEST: The case in which no brackets are found
 */
TEST(StringUtils_Test, bracket_not_found) 
{
    // Setup
    auto value = string("this is some text");

    // Execute
    auto output = StringUtils::GetBracketText(value, '(', ')');

    // Confirm
    ASSERT_EQ(output, string());
}

/**
 * @brief TEST: The case in which there is only an open bracket
 */
TEST(StringUtils_Test, bracket_only_open) 
{
    // Setup
    auto value = string("void myfunc(int test, ...");

    // Execute
    auto output = StringUtils::GetBracketText(value, '(', ')');

    // Confirm
    ASSERT_EQ(output, "int test, ...");
}

/**
 * @brief TEST: The case in which there is only a close bracket
 */
TEST(StringUtils_Test, bracket_only_close) 
{
    // Setup
    auto value = string("int test, const string& value)");

    // Execute
    auto output = StringUtils::GetBracketText(value, '(', ')');

    // Confirm
    ASSERT_EQ(output, string());
}

/**
 * @brief TEST: The case which is normal - basic set of brackets with some normal text between
 */
TEST(StringUtils_Test, bracket_normal_extraction) 
{
    // Setup
    auto value = string("string GetBracketText(const string& value, char startTag, char endTag)");

    // Execute
    auto output = StringUtils::GetBracketText(value, '(', ')');

    // Confirm
    ASSERT_EQ(output, "const string& value, char startTag, char endTag");
}

/**
 * @brief TEST: The case in which there are a bunch of different brackets
 */
TEST(StringUtils_Test, bracket_multiple_brackets) 
{
    // Setup
    auto value = string("this is ((some) (text)");

    // Execute
    auto output = StringUtils::GetBracketText(value, '(', ')');

    // Confirm
    ASSERT_EQ(output, "(some");
}

//--------------------------------------------------
// Test Stream2Text
//--------------------------------------------------

/**
 * @brief Test the conversion of a stream into text
 */
TEST(StringUtils_Test, stream_to_text) 
{
    // Setup
    auto input = stringstream();
    input << "This is my first line" << endl;
    input << "This is my second ling" << endl;
    input << "this is my third line" << endl;

    auto expected = stringstream(input.str());

    // Executed
    auto actualString = StringUtils::Stream2Text(input);
    auto actual = stringstream(actualString);

    // Confirm
    NVL_TestTools::SnippetTester::Compare(expected, actual);
}

//--------------------------------------------------
// Test Line Assemble
//--------------------------------------------------

/**
 * @brief Test the assembly of a set of lines
 */
TEST(StringUtils_Test, assmeble_lines) 
{
    // Setup
    auto lines = vector<string> { "line one", "line two", "line three", "line four" };

    auto expected = stringstream();
    expected << "line one" << endl;
    expected << "line two" << endl;
    expected << "line three" << endl;
    expected << "line four" << endl;

    // Execute
    auto actual = stringstream(StringUtils::AssembleLines(lines));

    // Confirm
    NVL_TestTools::SnippetTester::Compare(expected, actual);
}

//--------------------------------------------------
// Test Conversion Failures
//--------------------------------------------------

/**
 * @brief Confirm that an integer conversion behaves as expected
 */
TEST(StringUtils_Test, integer_conversion_failure) 
{
	auto expected = "Integer conversion failed: not an integer";

	try
	{
        auto value = StringUtils::String2Int("not an integer");
		FAIL() << "Expected exception: " << expected;
	}
	catch (runtime_error error)
	{
		ASSERT_EQ(error.what(), string(expected));
	}
	catch (...)
	{
		FAIL() << "Expected exception: " << expected;
	}
}

/**
 * @brief Confirm that a bool conversion behaves as expected
 */
TEST(StringUtils_Test, bool_conversion_failure) 
{
	auto expected = "Integer conversion failed: not a boolean";

	try
	{
        auto value = StringUtils::String2Int("not a boolean");
		FAIL() << "Expected exception: " << expected;
	}
	catch (runtime_error error)
	{
		ASSERT_EQ(error.what(), string(expected));
	}
	catch (...)
	{
		FAIL() << "Expected exception: " << expected;
	}
}

//--------------------------------------------------
// Split Error Check
//--------------------------------------------------

/**
 * @brief Verify new line split
 */
TEST(StringUtils_Test, split_new_line) 
{
    // Setup
    auto input = stringstream();
    input << "line 1" << endl;
    input << "line 2" << endl;
    input << "line 3" << endl;

    auto lines = vector<string>();

    // Execute
    StringUtils::Split(input.str(), '\n', lines);

    // Confirm
    ASSERT_EQ(lines.size(), 3);
    ASSERT_EQ(lines[0], "line 1");
    ASSERT_EQ(lines[1], "line 2");
    ASSERT_EQ(lines[2], "line 3");
}

/**
 * @brief Verify new line split without key characte
r */
TEST(StringUtils_Test, split_new_line_one_line) 
{
    // Setup
    auto input = string("my line");

    auto lines = vector<string>();

    // Execute
    StringUtils::Split(input, '\n', lines);

    // Confirm
    ASSERT_EQ(lines.size(), 1);
    ASSERT_EQ(lines[0], "my line");
}

//--------------------------------------------------
// Ends With Check
//--------------------------------------------------

/**
 * @brief Confirms that EndsWith operates as expected
 */
TEST(StringUtils_Test, ends_with_check) 
{
    // Execute
    auto test_1 = StringUtils::EndsWith("test string", "string");
    auto test_2 = StringUtils::EndsWith("image.jpg", ".jpg");
    auto test_3 = StringUtils::EndsWith("image.jpg", ".png");
    auto test_4 = StringUtils::EndsWith("string", "my very large token!");
    auto test_5 = StringUtils::EndsWith(string(), "match");
    auto test_6 = StringUtils::EndsWith("string", string());

    // Confirm
    ASSERT_TRUE(test_1);
    ASSERT_TRUE(test_2);
    ASSERT_FALSE(test_3);
    ASSERT_FALSE(test_4);
    ASSERT_FALSE(test_5);
    ASSERT_FALSE(test_6);
}

//--------------------------------------------------
// Buffer String
//--------------------------------------------------

/**
 * @brief Test the buffer string functionality
 */
TEST(StringUtils_Test, buffer_string) 
{
    // Execute
    auto test_1 = StringUtils::BufferString("test", 10);
    auto test_2 = StringUtils::BufferString("test", 3);

    // Confirm
    ASSERT_EQ(test_1, "test      ");
    ASSERT_EQ(test_2, "tes");
}
