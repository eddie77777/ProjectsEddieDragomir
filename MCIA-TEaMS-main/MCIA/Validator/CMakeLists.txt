cmake_minimum_required (VERSION 3.8)

project(VALIDATOR_DLL)
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library (Validator SHARED src/Validator.cpp)
target_include_directories(Validator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)