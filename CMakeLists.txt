#cmake file for SimpleGF top-level dir

cmake_minimum_required(VERSION 3.13)
project(SimpleGF)

set(CMAKE_CXX_STANDARD 14)

option(DEBUG "build debug symbols" ON)
option(BUILD_TESTS "build tests" ON)

if(DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(${SimpleGF_SOURCE_DIR}/include)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

