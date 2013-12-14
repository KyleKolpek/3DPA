set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(Luatable
            Key.cpp
            Value.cpp)
target_link_libraries(Luatable lua)

add_subdirectory(lua)

