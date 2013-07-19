
# Compile ShaderManager
add_library(ShaderManager
            ShaderManager.cpp
            ShaderLoader.cpp)
set(INTERNAL_LIBS ${INTERNAL_LIBS} ShaderManager)

# Compile SOIL
add_subdirectory(SOIL)
set(INTERNAL_LIBS ${INTERNAL_LIBS} SOIL)

# Add the executable
add_executable(../3DPA main.cpp)
target_link_libraries(../3DPA ${LIBS} ${INTERNAL_LIBS})
