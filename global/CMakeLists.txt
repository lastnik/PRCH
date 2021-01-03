include(set_common_options)

add_library(global STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Global.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BinaryBuffer.cpp
)

target_include_directories(global
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# target_link_libraries()

set_common_options(global)