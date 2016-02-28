cmake_minimum_required(VERSION 2.8.12)

add_subdirectory(pixman)
set(PIXMAN_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/pixman/pixman 
    ${CMAKE_CURRENT_BINARY_DIR}/pixman)
set(PIXMAN_LIBRARY pixman)

add_subdirectory(cairo)
