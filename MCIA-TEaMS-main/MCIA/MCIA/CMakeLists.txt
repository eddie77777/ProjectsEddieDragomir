# CMakeList.txt : CMake project for MCIA, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.

find_package(SqliteOrm REQUIRED)

set(CMAKE_PREFIX_PATH $CONDA_PREFIX)
find_package (PythonLibs REQUIRED)
message(STATUS "Found python libraries: ${PYTHON_LIBRARIES}")
message(STATUS "Found python includeDirs: ${PYTHON_INCLUDE_DIRS}")

set(BACKEND_SOURCES
		include/NamedAsciiChars.h
		src/AuthService.cpp
		src/MovieService.cpp
		src/CodedException.cpp
		src/ConsoleInputController.cpp
		src/DatabaseManagement.cpp
		src/DBPage.cpp
		src/DBValidation.cpp
		src/Genre.cpp
		src/Movie.cpp
		src/MovieInformationDisplayer.cpp
		src/MovieGenre.cpp
		src/MovieIntermediary.cpp
		src/OperationStatus.cpp
		src/OperationStatusToMessage.cpp
		src/PyObjectWrapper.cpp
		src/RecomSystem.cpp
		src/User.cpp
		src/UserRecomService.cpp
		src/WatchedMovie.cpp
		src/WatchedMovieDisplayer.cpp
		src/WishlistedMovie.cpp
		src/ConnectedUser.cpp
		src/WishlistedMovieDisplayer.cpp)

add_executable (MCIA 
	${BACKEND_SOURCES}
	Source.cpp)

add_library(MCIALib STATIC
		${BACKEND_SOURCES} )
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MCIA PROPERTY CXX_STANDARD 20)
endif()


# TODO: Add tests and install targets if needed.
set(wanted_path "${CMAKE_CURRENT_BINARY_DIR}")
cmake_path(GET wanted_path PARENT_PATH PARENT_DIR)
message("Where to look for Validator: ${PARENT_DIR}")

# link libraries
target_link_libraries(MCIA
        PRIVATE sqlite_orm::sqlite_orm
		PUBLIC Validator
		PUBLIC ${PYTHON_LIBRARIES}
        )

target_link_libraries(MCIALib
        PRIVATE sqlite_orm::sqlite_orm
		PUBLIC Validator
		PRIVATE ${PYTHON_LIBRARIES}
        )

target_include_directories(MCIALib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ PRIVATE ${PYTHON_INCLUDE_DIRS})
target_include_directories(MCIA PRIVATE ${PYTHON_INCLUDE_DIRS})
