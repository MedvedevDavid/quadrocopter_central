set(COMPONENT_NAME gy86)
add_library(${COMPONENT_NAME})

target_link_libraries(
    ${COMPONENT_NAME}
    PRIVATE
        i2c_adapter
)

target_sources(
    ${COMPONENT_NAME}
    PRIVATE
        gy86_driver.cpp
        mpu_6050.cpp
        hmc_5883l.cpp
)
target_include_directories(
    ${COMPONENT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)