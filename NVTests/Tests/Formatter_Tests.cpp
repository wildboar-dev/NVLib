//--------------------------------------------------
// Unit Tests: Formatter
//
// @author: Wild Boar
//
// @date: 2021-08-26
//--------------------------------------------------


#include <iostream>
using namespace std;

#include <gtest/gtest.h>

#include <NVLib/Formatter.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test:
 */
TEST(Formatter_Test, basic_string_generation) 
{
    // Setup
    auto name = "Trevor"; auto age = 18;
    auto expected = string("My name is Trevor and I am 18 years old");

    // Execute
    try
    {
        throw runtime_error(NVLib::Formatter() << "My name is " << name << " and I am " << age << " years old");
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