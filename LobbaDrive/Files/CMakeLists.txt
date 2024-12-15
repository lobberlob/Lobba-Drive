# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(LobbaEmulator)

# Enable C++17 (or higher if needed)
set(CMAKE_CXX_STANDARD 17)

# Set the executable name
set(EXECUTABLE_NAME "LobbaEmulator")

# Add source files
set(SOURCE_FILES
    Main.cpp
    CPU.cpp
    VDP.cpp
    Audio.cpp
    InputHandler.cpp
)

# Include directories (add paths to your header files)
include_directories(
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/SDL2/include
    ${CMAKE_SOURCE_DIR}/SDL2_image/include
)

# Link directories (add paths to your library files)
link_directories(
    ${CMAKE_SOURCE_DIR}/SDL2/lib
    ${CMAKE_SOURCE_DIR}/SDL2_image/lib
)

# Find SDL2 and SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add executable
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Link SDL2, SDL2_image, and other necessary libraries
target_link_libraries(${EXECUTABLE_NAME}
    SDL2::SDL2
    SDL2_image::SDL2_image
)

# Set up for building and using SDL2_image (if needed)
if(WIN32)
    # Include additional libraries for Windows
    target_link_libraries(${EXECUTABLE_NAME} "${CMAKE_SOURCE_DIR}/SDL2/lib/SDL2.lib")
    target_link_libraries(${EXECUTABLE_NAME} "${CMAKE_SOURCE_DIR}/SDL2_image/lib/SDL2_image.lib")
endif()
