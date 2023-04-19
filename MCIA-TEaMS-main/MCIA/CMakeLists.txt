# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("MCIA")
enable_testing()

set(CMAKE_CXX_STANDARD 14)
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
# set(COVERAGE_FLAGS " -coverage -fprofile-arcs -ftest-coverage")
# SET(LCOV_COVERAGE_LINK_FLAGS " -lgcov --coverage")

# string(APPEND CMAKE_C_FLAGS "${COVERAGE_FLAGS}")
# string(APPEND CMAKE_CXX_FLAGS "${COVERAGE_FLAGS}")
# SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LCOV_COVERAGE_LINK_FLAGS}")

# Include sub-projects.
add_subdirectory (Validator)
add_subdirectory ("MCIA")
# add_subdirectory (QT)
add_subdirectory ("UnitTests")
