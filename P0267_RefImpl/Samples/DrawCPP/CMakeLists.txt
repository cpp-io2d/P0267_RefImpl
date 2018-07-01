cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(draw_cpp main.cpp)

target_link_libraries(draw_cpp io2d)

set(RSC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/texture.jpg)
set(RSC_TARGET $<TARGET_FILE_DIR:draw_cpp>/texture.jpg)

add_custom_command( TARGET draw_cpp POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}" "${RSC_TARGET}")

if(MSVC)
    set_target_properties(draw_cpp PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()
