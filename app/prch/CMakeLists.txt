include(set_common_options)

add_library(prch STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Generator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KindOne.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KindTwo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KindThree.cpp
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