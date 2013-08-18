
# Compile ShaderManager
add_library(ShaderManager
            ShaderManager.cpp
            ShaderLoader.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} ShaderManager)

# Compile Drawable
add_library(Drawable
            Drawable.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Drawable)

# Compile Cube
add_library(Cube
            Cube.cpp)
target_link_libraries(Cube ShaderManager Drawable)
set(INTERNAL_LIBS ${INTERNAL_LIBS} Cube)

# Compile SOIL
add_subdirectory(SOIL)
set(INTERNAL_LIBS ${INTERNAL_LIBS} SOIL)

# Add the executable
add_executable(../3DPA main.cpp)
target_link_libraries(../3DPA ${LIBS} ${INTERNAL_LIBS})
