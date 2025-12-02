cmake_minimum_required(VERSION 3.10)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

project(dungeon-smith LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add raylib source (point to the repo root that contains its CMakeLists.txt)
add_subdirectory(external/raylib)

# Collect all your source files
file(GLOB SOURCES "src/*.cpp")

# Create your executable
add_executable(dungeon-smith ${SOURCES})

# Link raylib
target_link_libraries(dungeon-smith raylib)

# Add raylib include directory
target_include_directories(dungeon-smith PRIVATE external/raylib/src)

# On Windows, also link system libraries
if (WIN32)
    target_link_libraries(dungeon-smith winmm)
endif()
