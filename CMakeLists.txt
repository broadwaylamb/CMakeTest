cmake_minimum_required(VERSION 2.8)

project(CMakeTest)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set (COVERAGE_LINK_FLAGS "--coverage")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILE_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINK_FLAGS}")

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

include_directories ("${PROJECT_SOURCE_DIR}/libsodium")
set (EXTRA_LIBS ${EXTRA_LIBS} libsodium)
add_library(libsodium STATIC IMPORTED)
set_property(TARGET libsodium PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libsodium/libsodium.a")

# add the executable
add_executable(CMakeTest Source/main.cpp)
target_link_libraries (CMakeTest ${EXTRA_LIBS})

# add the install targets
install (TARGETS CMakeTest DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/CMakeTestConfig.h"
         DESTINATION include)


include (CTest)

# does the application run
add_test (CMakeTestRuns CMakeTest)

# does it sqrt of 25
add_test (CMakeTestComp25 CMakeTest)
set_tests_properties (CMakeTestComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# does libsodium work?
add_test (CMakeTestLibsodium CMakeTest)
set_tests_properties (CMakeTestLibsodium PROPERTIES PASS_REGULAR_EXPRESSION "Sodium")
