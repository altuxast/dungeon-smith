cmake_minimum_required(VERSION 3.10)

project(dungeon-smith LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Raylib
add_subdirectory(external/raylib)

# Source files
set(SOURCES
    src/main.cpp
    src/generator/BSPGenerator.cpp
    src/generator/TileMap.cpp
    src/renderer/RaylibRenderer.cpp
    utils/JsonIO.cpp
)

add_executable(dungeon-smith ${SOURCES})

# Link libraries
target_link_libraries(dungeon-smith PRIVATE
    raylib
    winmm
)

# Include directories
target_include_directories(dungeon-smith PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/external/json
    ${CMAKE_SOURCE_DIR}/external/raylib/src
    ${CMAKE_SOURCE_DIR}/external/raygui
)
