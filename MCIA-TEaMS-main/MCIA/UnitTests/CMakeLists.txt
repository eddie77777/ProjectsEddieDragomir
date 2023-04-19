cmake_minimum_required (VERSION 3.8)

message(STATUS "COMPILER ID: ${CMAKE_CXX_COMPILER_ID}")

find_package(SqliteOrm REQUIRED)
# linking based on compiler used:
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	find_package(GTest REQUIRED)
	include(GoogleTest)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	include(FetchContent)

	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        release-1.12.0
	)
	FetchContent_MakeAvailable(googletest)
	add_library(GTest::GTest INTERFACE IMPORTED)
	target_link_libraries(GTest::GTest INTERFACE gtest_main)
else()
	find_package(GTest REQUIRED)
	include(GoogleTest)
endif()

add_executable(
  testing
  tests/CodedExceptionTests.cpp
  tests/ConsoleInputControllerTests.cpp
  tests/DBPageTests.cpp
  tests/DBValidationTests.cpp
  tests/GenreTests.cpp
  tests/MovieGenreTests.cpp
  tests/MovieInformationDisplayerTests.cpp
  tests/MovieIntermediaryTests.cpp
  tests/MovieTests.cpp
  tests/OperationStatusTests.cpp
  tests/OperationStatusToMessageTests.cpp
  tests/UserTests.cpp
  tests/WatchedMovieDisplayerTests.cpp
  tests/WatchedMovieTests.cpp
  tests/WishlistedMovieDisplayerTests.cpp
  tests/WishlistedMovieTests.cpp
  Source.cpp)

 target_link_libraries(testing 
	PRIVATE GTest::gtest
	PRIVATE sqlite_orm::sqlite_orm
	PUBLIC MCIALib
		 )

add_test(testing_t testing)
# gtest_discover_tests(testing)