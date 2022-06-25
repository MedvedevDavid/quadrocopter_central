set(BINARY ${CMAKE_PROJECT_NAME})
include_directories(../adapters)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true 
    *.h *.cpp
    ../adapters/*.h ../adapters/*.cpp)
    
set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})