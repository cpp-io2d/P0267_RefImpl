cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(draw_cpp main.cpp)

target_link_libraries(draw_cpp io2dlib)
