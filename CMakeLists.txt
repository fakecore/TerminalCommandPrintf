cmake_minimum_required(VERSION 3.20)
project(TerminalCommandPrintf)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)


add_library(TerminalCommandPrintf SHARED
        src/command_printf.cpp
        src/limited_queue.cpp
        )

add_subdirectory(demo)