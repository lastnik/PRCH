include(set_common_options)

add_library(common STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/WorkerPool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/JobQueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BigBinary.cpp
)

target_include_directories(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(common
    PRIVATE
        global
)

set_common_options(common)