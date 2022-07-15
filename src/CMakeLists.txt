set(BINARY ${CMAKE_PROJECT_NAME})
#include_directories(../adapters)


#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true 
#    *.h *.cpp
#    ../adapters/*.h ../adapters/*.cpp)
    
add_subdirectory(Sensor_Read)

#set(SOURCES ${SOURCES})

add_executable(${BINARY}_run main.cpp)
target_link_libraries(
    ${BINARY}_run wiringPi
    i2c_adapter
    gy86
)
add_definitions(-std=c++0x -lwiringPi -lpthread)


