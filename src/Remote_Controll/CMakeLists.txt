set(COMPONENT_NAME remote_controll)
add_library(${COMPONENT_NAME})

target_link_libraries(
    ${COMPONENT_NAME}
    PRIVATE
        
)

target_sources(
    ${COMPONENT_NAME}
    PRIVATE
        UART_read.cpp
        controll_master.cpp
)
target_include_directories(
    ${COMPONENT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)