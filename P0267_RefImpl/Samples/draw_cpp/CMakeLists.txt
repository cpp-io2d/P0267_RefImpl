cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

if(EMSCRIPTEN)
	message("Skipping the draw_cpp example due to lack of Emscripten support")
	return()
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(draw_cpp main.cpp)

target_link_libraries(draw_cpp io2d)

install(TARGETS draw_cpp
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
