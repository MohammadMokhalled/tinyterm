cmake_minimum_required(VERSION 3.0)

project(example)

# source files
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/example_linux.c
    ${CMAKE_CURRENT_SOURCE_DIR}/example_commands.c
    )

find_package(Threads REQUIRED)

# exacutable
add_executable(example_linux ${SOURCES})

# libraries
target_link_libraries(example_linux TinyTerm_LIBRARY )
target_link_libraries(example_linux ncurses)
target_link_libraries(example_linux Threads::Threads)

