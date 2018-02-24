cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

set(IO2D_LIB_SRC 
	io2d_cg_brushes.h
	io2d_cg_brushes.cpp
	io2d_cg_interop.h
	io2d_cg_output_surfaces.h
	io2d_cg_output_surfaces.mm
	io2d_cg_paths.h
	io2d_cg_paths.cpp
	io2d_cg_surface_state_props.h
	io2d_cg_paths_figures.h
	io2d_cg_paths_figures.cpp
	io2d_cg_surfaces.h
	io2d_cg_surfaces.cpp
	../../rgba_color.cpp
)

add_library(io2dlib ${IO2D_LIB_SRC})

target_include_directories(io2dlib INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(io2dlib "-framework Cocoa")
target_link_libraries(io2dlib "-framework AppKit")
target_link_libraries(io2dlib "-framework CoreServices")
target_link_libraries(io2dlib "-framework CoreFoundation")
target_link_libraries(io2dlib "-framework ImageIO")
target_link_libraries(io2dlib "-framework CoreGraphics")
