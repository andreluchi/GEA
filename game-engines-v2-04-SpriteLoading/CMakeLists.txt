cmake_minimum_required(VERSION 3.22)

project(GAME VERSION 1.0)

# Enable C++20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Set the paths for SDL2_image manually
set(SDL2_IMAGE_INCLUDE_DIRS "/usr/include/SDL2")
set(SDL2_IMAGE_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2_image.so")

# Check if the SDL2_image paths are valid
if(NOT EXISTS ${SDL2_IMAGE_INCLUDE_DIRS}/SDL_image.h OR NOT EXISTS ${SDL2_IMAGE_LIBRARIES})
    message(FATAL_ERROR "SDL2_image not found")
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SOURCES}
)

# Set include directories for the executable
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Link SDL2 and SDL2_image libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
)
