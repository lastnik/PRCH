cmake_minimum_required(VERSION 3.15.3)

project(diplomPRCH LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_FIND_ROOT_PATH $ENV{_5GSDR_SDK_DIR})
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

include(set_common_options)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_subdirectory(global)
add_subdirectory(app)

add_executable(diplomPRCH
    ${CMAKE_CURRENT_SOURCE_DIR}/main-x86.cpp
)

target_link_libraries(diplomPRCH
    PRIVATE
        global
        application
)

set_common_options(diplomPRCH)