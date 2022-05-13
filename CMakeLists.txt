cmake_minimum_required(VERSION 3.12)

project(ecs CXX)

add_executable(ecs
    "src/main.cpp"
    "src/ecs/World.cpp"
)

target_include_directories(ecs PRIVATE "${CMAKE_SOURCE_DIR}/include")
set_target_properties(ecs
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/"
)
