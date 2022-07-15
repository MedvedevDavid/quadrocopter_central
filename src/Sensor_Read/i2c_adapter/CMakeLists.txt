set(COMPONENT_NAME i2c_adapter)
add_library(${COMPONENT_NAME})

#target_link_libraries(
#    ${COMPONENT_NAME}
#    PRIVATE
#        #gy56
#)

target_sources(
    ${COMPONENT_NAME}
    PRIVATE
        i2c_adapter.cpp
)
target_include_directories(
    ${COMPONENT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)