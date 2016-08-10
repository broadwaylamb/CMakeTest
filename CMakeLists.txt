cmake_minimum_required(VERSION 2.8)

project(CMakeTest)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions (-coverage)
# set (CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " -coverage")

# The version number.
set (CMakeTest_VERSION_MAJOR 1)
set (CMakeTest_VERSION_MINOR 0)
set (CMakeTest_VERSION_PATCH 0)

configure_file (
"${PROJECT_SOURCE_DIR}/CMakeTestConfig.h.in"
"${PROJECT_BINARY_DIR}/CMakeTestConfig.h"
)

include_directories("${PROJECT_BINARY_DIR}")

# should we use our own math functions?
option (USE_MYMATH  "Use provided math implementation" ON)

# add the MathFunctions library?
if (USE_MYMATH)
    include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
    add_subdirectory (MathFunctions)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# add the executable
add_executable(CMakeTest Source/main.cpp)
target_link_libraries (CMakeTest ${EXTRA_LIBS})

# add the install targets
install (TARGETS CMakeTest DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/CMakeTestConfig.h"
         DESTINATION include)

include(CTest)


# does the application run
add_test (CMakeTestRuns CMakeTest 25)

# does it sqrt of 25
add_test (CMakeTestComp25 CMakeTest 25)
set_tests_properties (CMakeTestComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# does it handle small numbers
add_test (CMakeTestSmall CMakeTest 0.0001)
set_tests_properties (CMakeTestSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

# does the usage message work?
add_test (CMakeTestUsage CMakeTest)
set_tests_properties (CMakeTestUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")
