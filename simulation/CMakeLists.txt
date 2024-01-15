cmake_minimum_required(VERSION 3.10)

project(SquareRootTests)

# Locate GTest
find_package(GTest REQUIRED)

# Include headers and source files
include_directories(${GTEST_INCLUDE_DIRS})

# Create a library with the implementation file
add_library(traffic_managment_lib traffic.cpp)

# Create an executable for your tests
add_executable(smart_traffic_mng_tests unit-test.cpp)

# Link the executable with GTest and your library
target_link_libraries(smart_traffic_mng_tests ${GTEST_BOTH_LIBRARIES} traffic_managment_lib)

# Add GTest include directories to your project
target_include_directories(smart_traffic_mng_tests PRIVATE ${GTEST_INCLUDE_DIRS})

# Specify the C++ standard
set_target_properties(smart_traffic_mng_tests PROPERTIES
                      CXX_STANDARD 11
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

# Run the tests
enable_testing()
add_test(NAME smart_traffic_mng_tests COMMAND smart_traffic_mng_tests)
