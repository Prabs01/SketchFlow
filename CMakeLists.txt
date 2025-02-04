

cmake_minimum_required(VERSION 3.10)
project(SketchFlow)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Manually specify SDL2_image paths (modify these to your actual paths)
set(SDL2_IMAGE_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2_image/2.8.4/include")
set(SDL2_IMAGE_LIB_DIR "/opt/homebrew/Cellar/sdl2_image/2.8.4/lib")

# Find required SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Define the main source directory
#set(TEST_DIR test)
set(SOURCE_DIR src)


# Add the main executable
file(GLOB MAIN_SOURCES "${SOURCE_DIR}/*.cpp")
add_executable(SketchFlow ${MAIN_SOURCES})

# Add the test executable (for testing purposes)
file(GLOB TEST_SOURCES "${TEST_DIR}/*.cpp")
#add_executable(SketchFlowTest ${TEST_SOURCES})

# Add the SDL2_image include directory to both the main and test executables
#target_include_directories(SketchFlowTest PRIVATE ${SDL2_IMAGE_INCLUDE_DIR})
target_include_directories(SketchFlow PRIVATE ${SDL2_IMAGE_INCLUDE_DIR})


# Link SDL2 and SDL2_image libraries to the main and test applications
#target_link_libraries(SketchFlowTest SDL2::SDL2 ${SDL2_IMAGE_LIB_DIR}/libSDL2_image.dylib)
target_link_libraries(SketchFlow SDL2::SDL2 ${SDL2_IMAGE_LIB_DIR}/libSDL2_image.dylib)

