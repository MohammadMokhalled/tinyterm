cmake_minimum_required(VERSION 3.5)

project(TinyTerm_LIBRARY)

set(CMAKE_BUILD_TYPE Debug)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(${PROJECT_NAME} STATIC 
        ${PROJECT_SOURCE_DIR}/src/tinyterm.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        
)

add_subdirectory(${PROJECT_SOURCE_DIR}/example)
