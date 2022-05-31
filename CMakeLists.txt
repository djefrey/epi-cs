cmake_minimum_required(VERSION 3.12)

project(ecs CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include("${CMAKE_SOURCE_DIR}/cmake/Findraylib.cmake")
find_package(raylib REQUIRED)

add_executable(ecs
    "src/main.cpp"
    "src/ecs/World.cpp"
)

target_link_libraries(ecs raylib)
target_include_directories(ecs
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${raylib_SOURCE_DIR}/"
)
set_target_properties(ecs
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/"
)
