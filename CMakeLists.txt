cmake_minimum_required(VERSION 3.10)
project(SketchFlow)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Check if SDL2 is available
find_package(SDL2 REQUIRED)

# Add the source files
add_executable(SketchFlow src/main.cpp)

# Link SDL2
target_link_libraries(SketchFlow SDL2::SDL2)
