cmake_minimum_required(VERSION 4.0)
project(cowStrings)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cowStrings
        cow_string.cpp
        cow_string.h
        generic_string.cpp
        generic_string.h
        main.cpp)
