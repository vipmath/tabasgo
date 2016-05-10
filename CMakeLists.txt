cmake_minimum_required(VERSION 3.5)
project(tabasgo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

## MinGW static linking
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -s")
    set(BOOST_INCLUDEDIR "C:/mingw64/x86_64-w64-mingw32/include/boost-1_60")
    set(BOOST_LIBRARYDIR "C:/mingw64/x86_64-w64-mingw32/lib")
endif()

## Boost
find_package( Boost 1.58 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

set(SOURCE_FILES main.cpp gtp.h gtp.cpp board.cpp board.h)
add_executable(tabasgo ${SOURCE_FILES})
target_link_libraries( tabasgo ${Boost_LIBRARIES} )