include(set_common_options)

add_library(prch STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/TypeOne.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/TypeTwo.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/TypeThree.cpp
)

target_include_directories(prch
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(prch
    PRIVATE
        global
        common
)

set_common_options(prch)