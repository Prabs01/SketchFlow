
cmake_minimum_required(VERSION 3.10)
project(SketchFlow)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Manually specify SDL2 and SDL2_image paths (Modify these if needed)
set(SDL2_INCLUDE_DIR "/opt/homebrew/include/SDL2")
set(SDL2_LIB_DIR "/opt/homebrew/lib")

set(SDL2_IMAGE_INCLUDE_DIR "/opt/homebrew/include/SDL2")
set(SDL2_IMAGE_LIB_DIR "/opt/homebrew/lib")

# Define the source directory
set(SOURCE_DIR src)

# Collect source files
file(GLOB MAIN_SOURCES "${SOURCE_DIR}/*.cpp")
add_executable(SketchFlow ${MAIN_SOURCES})

# Include SDL2 and SDL2_image directories
target_include_directories(SketchFlow PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# Link SDL2 and SDL2_image dynamically
target_link_libraries(SketchFlow PRIVATE
    ${SDL2_LIB_DIR}/libSDL2.dylib
    ${SDL2_IMAGE_LIB_DIR}/libSDL2_image.dylib
)
