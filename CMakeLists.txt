cmake_minimum_required(VERSION 3.10)
project(FoodCollectorGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Find raylib package
find_package(raylib REQUIRED)

# Include directories
include_directories(include)

# Gather all source files
file(GLOB_RECURSE MAIN_SRC src/*)

# Create executable
add_executable(food-collector-game
    ${MAIN_SRC}
)

# Link raylib
target_link_libraries(food-collector-game raylib)
