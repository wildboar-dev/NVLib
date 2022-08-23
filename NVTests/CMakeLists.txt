#--------------------------------------------------------
# CMake for generating NV Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2021-08-24
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Setup base directory
if (WIN32)
    set(LIBRARY_BASE "D:/Work/Infrastructure/LIBS")
else()
    set(LIBRARY_BASE $ENV{HOME}/Libraries)
endif()

# Add include directory
include_directories( "../" )

# Add opencv to the solution
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add the UnitTestLib library to the folder
add_library(UnitTestLib STATIC IMPORTED)
set_target_properties(UnitTestLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/UnitTestLib/build/UnitTestLib/libUnitTestLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/UnitTestLib"
)

# Create the executable
add_executable (NVTests
	Tests/MatrixUtils_Tests.cpp
	Tests/ImageUtils_Tests.cpp
	Tests/LoadUtils_Tests.cpp
	Tests/ConvertUtils_Tests.cpp
	Tests/RandomGray_Tests.cpp
	Tests/DrawUtils_Tests.cpp
	Tests/CmdLineUtils_Tests.cpp
	Tests/StringUtils_Tests.cpp
	Tests/FindLocations_Tests.cpp
	Tests/BackupUtils_Tests.cpp
	Tests/FileUtils_Tests.cpp
	Tests/DateTimeUtils_Tests.cpp
	Tests/DateTimeUtils_2_Tests.cpp
	Tests/Formatter_Tests.cpp
	Tests/EscapeUtils_Tests.cpp
	Tests/ZipUtils_Tests.cpp
	Tests/Graph_Tests.cpp
	Tests/Parameters_Tests.cpp
	Tests/PoseUtils_Tests.cpp
)

# Link associated libraries to the project
target_link_libraries(NVTests ${OpenCV_LIBS} NVLib UnitTestLib GTest::Main zip uuid)

# Find the associated unit tests
gtest_discover_tests(NVTests)