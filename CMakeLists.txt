cmake_minimum_required(VERSION 3.10)
project(SketchFlow)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use more portable path handling
set(SDL2_ROOT "C:/Users/anist/Downloads/SDL2/SDL2")
set(SDL2_IMAGE_ROOT "C:/Users/anist/Downloads/SDL2_image-2.8.4/SDL2_image-2.8.4")

# Set paths using standard variables
set(SDL2_INCLUDE_DIR "${SDL2_ROOT}/include")
set(SDL2_LIB_DIR "${SDL2_ROOT}/lib/x64")
set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_ROOT}/include")
set(SDL2_IMAGE_LIB_DIR "${SDL2_IMAGE_ROOT}/lib/x64")

# Better source file management (explicit is better than GLOB)
set(SOURCE_DIR src)
file(GLOB MAIN_SOURCES 
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.h"  # Include headers if needed
)

add_executable(SketchFlow ${MAIN_SOURCES})

# Include directories
target_include_directories(SketchFlow PRIVATE 
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

# Link libraries with proper Windows dependencies
target_link_libraries(SketchFlow 
    "${SDL2_LIB_DIR}/SDL2main.lib"
    "${SDL2_LIB_DIR}/SDL2.lib"
    "${SDL2_IMAGE_LIB_DIR}/SDL2_image.lib"
)

# For Windows, add required system libraries
if(WIN32)
    target_link_libraries(SketchFlow 
        mingw32  # If using MinGW
        imm32
        version
        winmm
        setupapi
        advapi32
        gdi32
        user32
        shell32
    )
endif()

# Copy DLLs to build directory (optional but helpful)
add_custom_command(TARGET SketchFlow POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SDL2_LIB_DIR}/SDL2.dll"
        "${SDL2_IMAGE_LIB_DIR}/SDL2_image.dll"
        $<TARGET_FILE_DIR:SketchFlow>
)