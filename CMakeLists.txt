cmake_minimum_required(VERSION 3.8)

project(challenge)

include (CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_subdirectory(c++)