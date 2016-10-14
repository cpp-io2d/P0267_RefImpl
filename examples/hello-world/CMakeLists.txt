cmake_minimum_required(VERSION 2.8.12)

project(hello CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hello hello.cpp)

target_link_libraries(hello ${IO2D_LIBRARY})
target_include_directories(hello PRIVATE ${IO2D_INCLUDE_DIR})
