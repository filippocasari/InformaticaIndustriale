cmake_minimum_required(VERSION 3.7)
project(Data-Parallelism-template)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
add_compile_options("-Wall")
add_executable( data SommeParzialiThread.c)