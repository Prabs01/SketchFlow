cmake_minimum_required(VERSION 3.10)
project(SketchFlow)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2 and SDL2_image paths
set(SDL2_INCLUDE_DIR "C:/Users/Satyam/Desktop/SDL2/include")
set(SDL2_LIB_DIR "C:/Users/Satyam/Desktop/SDL2/lib/x64")
set(SDL2_IMAGE_INCLUDE_DIR "C:/Users/Satyam/Desktop/SDL2_image-2.8.4/include")
set(SDL2_IMAGE_LIB_DIR "C:/Users/Satyam/Desktop/SDL2_image-2.8.4/lib/x64")

# Source files
set(SOURCE_DIR src)
file(GLOB MAIN_SOURCES "${SOURCE_DIR}/*.cpp")
add_executable(SketchFlow ${MAIN_SOURCES})

# Include directories
target_include_directories(SketchFlow PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# Link libraries
target_link_libraries(SketchFlow 
    ${SDL2_LIB_DIR}/SDL2main.lib 
    ${SDL2_LIB_DIR}/SDL2.lib 
    ${SDL2_IMAGE_LIB_DIR}/SDL2_image.lib
)
