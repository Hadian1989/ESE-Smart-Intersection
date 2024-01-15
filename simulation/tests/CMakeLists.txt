cmake_minimum_required(VERSION 3.12)

project(YourProjectName)
# Register your tests with CTest



# Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# Add the main executable target
add_executable(your_executable src/main.cpp)
target_include_directories(your_executable PRIVATE src)


# Add the tests executable target
add_executable(your_tests tests/tests.cpp)
target_include_directories(your_tests PRIVATE )
target_link_libraries(your_tests gtest_main)

target_sources(your_executable PRIVATE
    src/intersection.cpp
    src/street.cpp
    src/controller.cpp
    src/car.cpp
)

target_sources(your_tests PRIVATE
    src/intersection.cpp
    src/street.cpp
    src/controller.cpp
    src/car.cpp
)

# Link any libraries or dependencies needed for your_executable

# Set up testing with Google Test
find_package(GTest REQUIRED)
# target_link_libraries(your_tests PRIVATE GTest::GTest GTest::Main)

# Exclude main.cpp from the build when building your_tests
set_target_properties(your_tests PROPERTIES EXCLUDE_FROM_ALL 1)

# Add a custom target to build both your_executable and your_tests
add_custom_target(all_targets)
add_dependencies(all_targets your_executable your_tests)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
if(NOT CMAKE_CROSSCOMPILING)
    gtest_discover_tests(your_tests)
endif()
