cmake_minimum_required(VERSION 3.5)
project(tabasgo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

set(SOURCE_FILES main.cpp gtp.h gtp.cpp)
add_executable(tabasgo ${SOURCE_FILES})