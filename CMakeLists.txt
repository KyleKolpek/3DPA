cmake_minimum_required(VERSION 2.6)
project(3DPA)


# Set version number
set(TDPA_VERSION_MAJOR 0)
set(TDPA_VERSION_MINOR 1)

# Set platform {_NIX, WIN32, MACOSX}
#IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#   set(PLATFORM MACOSX)
#ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
   set(PLATFORM _NIX)
#ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Define the shader location
set(SHADER_DIR "\"${PROJECT_SOURCE_DIR}/assets/shaders/\"")

# Set up a config file
configure_file(
    "${PROJECT_SOURCE_DIR}/src/Config.h.in"
    "${PROJECT_BINARY_DIR}/Config.h"
)
include_directories(${PROJECT_BINARY_DIR})

# Include the include direcetory
include_directories("${PROJECT_SOURCE_DIR}/include/")

# Add a library directory
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${PROJECT_SOURCE_DIR}/lib)

# Add custom module path
set(
    CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${PROJECT_SOURCE_DIR}/depend/cmake_modules/"
)

# Include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Include SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Include GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

# Set library directory
link_directories(${PROJECT_BINARY_DIR})

# Collect libraries for target_link_libraries
set(LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${GLEW_LIBRARY})

# Set g++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(src)
