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