cmake_minimum_required(VERSION 3.10)
project(Quadrocopter_Central_test)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(lib/googletest)
add_subdirectory(src)


set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB TEST_SOURCES
     "stubs/*.cpp"
     "*.h"
     "*.hpp"
     "*.cpp"
)

set(SOURCES ${TEST_SOURCES})
include_directories(stubs)
add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)