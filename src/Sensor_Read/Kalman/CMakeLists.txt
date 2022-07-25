set(COMPONENT_NAME Kalman)
add_library(${COMPONENT_NAME})

target_sources(
    ${COMPONENT_NAME}
    PRIVATE
        Kalman.cpp
)
target_include_directories(
    ${COMPONENT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)