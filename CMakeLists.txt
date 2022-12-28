cmake_minimum_required(VERSION 3.10)
project(Quadrocopter_Central)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)


set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(BINARY ${CMAKE_PROJECT_NAME})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${BINARY}_run src/main.cpp)
target_link_libraries(
    ${BINARY}_run 
    ${CONAN_LIBS}
    i2c_adapter
    gy86
    sensor_master
    Kalman
    remote_controll
)
add_definitions(-std=c++0x -lwiringPi -lpthread)