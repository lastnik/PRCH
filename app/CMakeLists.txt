include(set_common_options)

add_subdirectory(common)
add_subdirectory(prch)

add_library(application STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/StartApp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sceduler.cpp
)

target_include_directories(application
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(application
    PRIVATE
        global
        common
        prch
        nlohmann_json::nlohmann_json -static
)

set_common_options(application)