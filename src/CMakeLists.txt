set(BINARY ${CMAKE_PROJECT_NAME})
    
add_subdirectory(Sensor_Read)
add_subdirectory(Remote_Controll)

add_executable(${BINARY}_run main.cpp)
target_link_libraries(
    ${BINARY}_run wiringPi
    i2c_adapter
    gy86
    sensor_master
    Kalman
    remote_controll
)
add_definitions(-std=c++0x -lwiringPi -lpthread)


