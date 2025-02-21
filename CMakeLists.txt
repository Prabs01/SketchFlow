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

# Resource file
set(RESOURCE_FILE "resource.rc")

# Add executable with WIN32 option for GUI app
add_executable(SketchFlow WIN32 ${MAIN_SOURCES} ${RESOURCE_FILE})

# Include directories
target_include_directories(SketchFlow PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# Link libraries
target_link_libraries(SketchFlow 
    ${SDL2_LIB_DIR}/SDL2main.lib 
    ${SDL2_LIB_DIR}/SDL2.lib 
    ${SDL2_IMAGE_LIB_DIR}/SDL2_image.lib
)

# Add the resource file if on Windows
if(WIN32)
    # Set the path to the resource file and icon
    set(RESOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/resource.rc")
    set(ICON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/icon.ico")

    # Add the resource to the executable
    add_custom_command(TARGET SketchFlow POST_BUILD
        COMMAND ${CMAKE_RC_COMPILER} ${RESOURCE_FILE} -o ${CMAKE_CURRENT_BINARY_DIR}/resource.res
    )
    target_sources(SketchFlow PRIVATE ${RESOURCE_FILE})
endif()
