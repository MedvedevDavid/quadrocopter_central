cmake_minimum_required(VERSION 3.10)
project(Quadrocopter_Central)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)

add_definitions(-std=c++0x -lwiringPi -lwiringPi )

