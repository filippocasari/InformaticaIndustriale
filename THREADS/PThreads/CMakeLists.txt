cmake_minimum_required(VERSION 3.17)
project(PThreads)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
add_executable(PThreads main.c main.c)