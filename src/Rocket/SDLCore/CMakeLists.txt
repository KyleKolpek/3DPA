

add_library(SDLCore
            SDLRenderInterface.cpp
            SDLSystemInterface.cpp)
target_link_libraries(SDLCore SOIL2 RocketCore ShaderManager)
