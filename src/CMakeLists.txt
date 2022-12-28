add_subdirectory(Sensor_Read)
add_subdirectory(Remote_Controll)

# set(CMAKE_THREAD_LIBS_INIT "-lpthread")
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
# set(CMAKE_HAVE_THREADS_LIBRARY 1)
# set(CMAKE_USE_WIN32_THREADS_INIT 0)
# set(CMAKE_USE_PTHREADS_INIT 1)
# set(THREADS_PREFER_PTHREAD_FLAG ON)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

# add_executable(${BINARY}_run main.cpp)
# target_link_libraries(
#     ${CONAN_LIBS}
#     ${BINARY}_run 
#     #wiringPi
#     i2c_adapter
#     gy86
#     sensor_master
#     Kalman
#     remote_controll
# )
# #add_definitions(-std=c++0x -lwiringPi -lpthread)
# add_definitions(-std=c++0x -lwiringPi -lpthread)


