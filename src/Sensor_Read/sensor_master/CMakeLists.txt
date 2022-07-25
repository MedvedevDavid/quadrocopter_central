set(COMPONENT_NAME sensor_master)
add_library(${COMPONENT_NAME})

target_link_libraries(
    ${COMPONENT_NAME}
    PRIVATE
        gy86
        i2c_adapter
        Kalman
)

target_sources(
    ${COMPONENT_NAME}
    PRIVATE
        sensor_master.cpp
)
target_include_directories(
    ${COMPONENT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)