cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(sprites)
add_executable(sprites main.cpp)
target_link_libraries(sprites io2d)

add_custom_command( TARGET sprites POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/cat.jpg" "$<TARGET_FILE_DIR:sprites>/cat.jpg"
)

if(MSVC)
	set_target_properties(sprites PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()
