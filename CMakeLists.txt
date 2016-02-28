cmake_minimum_required(VERSION 2.8.12)

project(io2d CXX)

add_subdirectory(io2d/src)
set(IO2D_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/io2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/io2d/src/3rd-party/cairo/src)
set(IO2D_LIBRARY io2d)

add_subdirectory(examples/hello-world)
