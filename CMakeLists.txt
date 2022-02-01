cmake_minimum_required(VERSION 3.20)
project(TerminalCommandPrintf)

set(CMAKE_CXX_STANDARD 14)

set(CXX_FLAGS
        -Wreturn-type
        -Wreturn-local-addr
        -Wuninitialized
        -Wformat
        -Wsign-compare
        -Wall
        -g
        -rdynamic
        -pthread
        )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
message("current build type:${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG  "$ENV{CXXFLAGS} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(src)

add_library(terminalcommand SHARED
        src/command_printf.cpp
        src/limited_queue.cpp
        )


add_subdirectory(demo)
add_subdirectory(test)