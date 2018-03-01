cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)

add_executable(svg
	main.cpp
	svg.h
	svg.cpp
	window.h
	window.cpp
)

target_link_libraries(svg io2d)
target_include_directories(svg
  PRIVATE external/svgpp/include
  PRIVATE external
)

target_include_directories(svg SYSTEM
  PRIVATE ${Boost_INCLUDE_DIRS}
)

install(TARGETS svg
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
