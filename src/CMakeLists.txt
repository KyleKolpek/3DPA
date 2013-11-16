
# Compile ShaderManager
add_library(ShaderManager
            ShaderManager.cpp
            ShaderLoader.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} ShaderManager)

# Compile Drawable
add_library(Drawable
            Drawable.cpp)
target_link_libraries(Drawable ShaderManager)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Drawable)

# Compile Updatable
add_library(Updatable
            Updatable.cpp)
target_link_libraries(Updatable InputMapper)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Updatable)

# Compile Cameras
add_library(Camera
            Camera.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Camera)

add_library(FirstPersonCamera
            FirstPersonCamera.cpp)
target_link_libraries(FirstPersonCamera Updatable)
set(INTERNAL_LIBS ${INTERNAL_LIBS} FirstPersonCamera)

# Compule MortonNumber
add_library(MortonNumber
            MortonNumber.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} MortonNumber)

# Compile Cube
add_library(Cube
            Cube.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Cube)

# Compile CubeGenerator
add_library(CubeGenerator
            CubeGenerator.cpp)
target_link_libraries(CubeGenerator Cube CubeManager InputMapper Drawable Updatable)
set(INTERNAL_LIBS ${INTERNAL_LIBS} CubeGenerator) 

# Compile CubeManager
add_library(CubeManager
            CubeManager.cpp)
target_link_libraries(CubeManager Cube Drawable MortonNumber)
set(INTERNAL_LIBS ${INTERNAL_LIBS} CubeManager) 

# Compile SOIL
add_subdirectory(SOIL)
set(INTERNAL_LIBS ${INTERNAL_LIBS} SOIL)

# Compile Viewport
add_library(Viewport
            Viewport.cpp)
target_link_libraries(Viewport FirstPersonCamera)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Viewport)

# Compile Renderer
add_library(Renderer
            Renderer.cpp)
target_link_libraries(Renderer CubeManager Viewport)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Renderer)

# Compile Input
add_library(RawInputConstants
            RawInputConstants.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} RawInputConstants)

add_library(RangeConverter
            RangeConverter.cpp)
target_link_libraries(RangeConverter RawInputConstants)
set(INTERNAL_LIBS ${INTERNAL_LIBS} RangeConverter)

add_library(InputContext
            InputContext.cpp)
target_link_libraries(InputContext RangeConverter RawInputConstants)
set(INTERNAL_LIBS ${INTERNAL_LIBS} InputContext)

add_library(InputMapper
            InputMapper.cpp)
target_link_libraries(InputMapper InputContext RawInputConstants)
set(INTERNAL_LIBS ${INTERNAL_LIBS} InputMapper)

# Add the executable
add_executable(../3DPA main.cpp)
target_link_libraries(../3DPA ${LIBS} ${INTERNAL_LIBS})
