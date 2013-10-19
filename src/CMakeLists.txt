
# Compile ShaderManager
add_library(ShaderManager
            ShaderManager.cpp
            ShaderLoader.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} ShaderManager)

# Compile Drawable
add_library(Drawable
            Drawable.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Drawable)

# Compile Updatable
add_library(Updatable
            Updatable.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Updatable)

# Compile Camera
add_library(Camera
            Camera.cpp)
target_link_libraries(Camera Updatable)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Camera)

# Compule MortonNumber
add_library(MortonNumber
            MortonNumber.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} MortonNumber)

# Compile Cube
add_library(Cube
            Cube.cpp)
target_link_libraries(Cube ShaderManager Drawable)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Cube)

# Compile CubeManager
add_library(CubeManager
            CubeManager.cpp)
target_link_libraries(CubeManager Cube MortonNumber)
set(INTERNAL_LIBS ${INTERNAL_LIBS} CubeManager) 

# Compile SOIL
add_subdirectory(SOIL)
set(INTERNAL_LIBS ${INTERNAL_LIBS} SOIL)

# Compile Viewport
add_library(Viewport
            Viewport.cpp)
target_link_libraries(Viewport Camera)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Viewport)

# Compile Renderer
add_library(Renderer
            Renderer.cpp)
target_link_libraries(Renderer Cube Viewport)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Renderer)

# Compile Input
add_library(Input
            InputContext.cpp
            InputMapper.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Input)

# Add the executable
add_executable(../3DPA main.cpp)
target_link_libraries(../3DPA ${LIBS} ${INTERNAL_LIBS})

# Add test executable
add_executable(../3DPAInput InputTest.cpp)
target_link_libraries(../3DPAInput ${LIBS} ${INTERNAL_LIBS})
