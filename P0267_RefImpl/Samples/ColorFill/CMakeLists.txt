cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(color_fill main.cpp)

target_link_libraries(color_fill io2d)

install(TARGETS color_fill
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
