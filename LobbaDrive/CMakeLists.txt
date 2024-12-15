# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name and the version
project(LobbaDrive VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories (modify paths as necessary)
include_directories(
    ${CMAKE_SOURCE_DIR}/include  # The folder where your header files are located
)

# Add source files
set(SOURCES
    src/Main.cpp
    src/CPU.cpp
    src/VDP.cpp
    src/Audio.cpp
    src/InputHandler.cpp
)

# Find SDL2 package (make sure you have it installed in your system)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Specify the executable to create
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2, SDL2_image, and SDL2_mixer with the project
target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

# Set the path for SDL2 libraries if necessary (modify paths as needed)
link_directories(
    ${CMAKE_SOURCE_DIR}/libs
)

# Optionally, add custom flags for compiling (e.g., optimization or debugging)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")  # Set MSVC warning level to 4
endif()

# Optionally set the output directory for your binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# If you are using additional libraries (like an external lib), you can link them here
# target_link_libraries(${PROJECT_NAME} <your_lib_name>)

