cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

set(IO2D_LIB_SRC 
	io2d.h
	io2d_coregraphics_ios.h
    xio2d_cg_output_surfaces.h
    xio2d_cg_output_surfaces.mm
	../xio2d_cg_main.h
	../xio2d_cg_brushes.h
	../xio2d_cg_brushes.cpp
	../xio2d_cg_interop.h
	../xio2d_cg_paths.h
	../xio2d_cg_paths.cpp
	../xio2d_cg_surface_state_props.h
	../xio2d_cg_paths_figures.h
	../xio2d_cg_paths_figures.cpp
	../xio2d_cg_surfaces.h
	../xio2d_cg_surfaces.cpp
   	../xio2d_cg_gradient.cpp
    ../xio2d_cg_gradient.h
	../xio2d_cg_colors.cpp
	../xio2d_cg_colors.h
	../xio2d_cg_texture.cpp
	../xio2d_cg_texture.h
)

add_library(io2d_coregraphics_ios ${IO2D_LIB_SRC})

target_include_directories(io2d_coregraphics_ios PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(io2d_coregraphics_ios "-framework UIKit")
target_link_libraries(io2d_coregraphics_ios "-framework Foundation")
target_link_libraries(io2d_coregraphics_ios "-framework CoreFoundation")
target_link_libraries(io2d_coregraphics_ios "-framework ImageIO")
target_link_libraries(io2d_coregraphics_ios "-framework CoreGraphics")
target_link_libraries(io2d_coregraphics_ios "-framework QuartzCore")
