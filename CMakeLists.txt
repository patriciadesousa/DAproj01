cmake_minimum_required(VERSION 3.24)
project(firstDA)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(firstDA
        src/Menu.cpp
        src/Menu.h src/ReadFiles.cpp src/ReadFiles.h src/Station.h src/Station.cpp src/main.cpp)
