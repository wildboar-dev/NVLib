//--------------------------------------------------
// Unit Tests: StringUtils: FindLocations method
//
// @author: Wild Boar
//
// @date: 2021-08-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/StringUtils.h>
using namespace NVLib;

//--------------------------------------------------
// Test 
//--------------------------------------------------

/**
 * @brief Confirm that the algorithm does not fail when no locations are found
 */
TEST(FindLocations_Test, no_locations) 
{
    // Setup
    auto value = string("This is a string");
    auto locations = vector<int>();

    // Execute
    auto count = StringUtils::FindLocations(value, "notfound", locations);

    // Confirm
    ASSERT_EQ(count, 0);
    ASSERT_EQ(locations.size(), 0);
}

/**
 * @brief A basic one location problem
 */
TEST(FindLocations_Test, single_location) 
{
    // Setup
    auto value = stringstream();
    value << "This is a line to ignore" << endl;    // 25
    value << "\t\tprivate: " << endl;               // 12
    value << endl;                                  // 1
    value << "void main() {}" << endl;              // 15

    auto locations = vector<int>();

    // Execute
    auto count = StringUtils::FindLocations(value.str(), "private", locations);

    // Confirm
    ASSERT_EQ(count, 1);
    ASSERT_EQ(locations.size(), 1);
    ASSERT_EQ(locations[0], 27);
}

/**
 * @brief A multiple locations problem
 */
TEST(FindLocations_Test, multiple_locations) 
{
    // Setup
    auto value = stringstream();
    value << "This is a line to ignore" << endl;    // 25
    value << "\t\tprivate: " << endl;               // 12
    value << endl;                                  // 1
    value << "void main() {}" << endl;              // 15    
    value << "private: " << endl;

    auto locations = vector<int>();

    // Execute
    auto count = StringUtils::FindLocations(value.str(), "private", locations);

    // Confirm
    ASSERT_EQ(count, 2);
    ASSERT_EQ(locations.size(), 2);
    ASSERT_EQ(locations[0], 25 + 2);
    ASSERT_EQ(locations[1], 25 + 12 + 1 + 15);
}

/**
 * @brief Confirm that overlapping locations are handled in an expected way
 */
TEST(FindLocations_Test, overlap_locations) 
{
    // Setup
    auto value = string("bababababa");
    auto locations = vector<int>();

    // Execute
    auto count = StringUtils::FindLocations(value, "aba", locations);

    // Confirm
    ASSERT_EQ(count, 4);
    ASSERT_EQ(locations.size(), 4);
    ASSERT_EQ(locations[0], 1);
    ASSERT_EQ(locations[1], 3);
    ASSERT_EQ(locations[2], 5);
    ASSERT_EQ(locations[3], 7);
}