cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

set(IO2D_LIB_SRC 
	io2d.h
	io2d_coregraphics_ios.h
	../io2d_cg_main.h
	../io2d_cg_brushes.h
	../io2d_cg_brushes.cpp
	../io2d_cg_interop.h
	io2d_cg_output_surfaces.h
	io2d_cg_output_surfaces.mm
	../io2d_cg_paths.h
	../io2d_cg_paths.cpp
	../io2d_cg_surface_state_props.h
	../io2d_cg_paths_figures.h
	../io2d_cg_paths_figures.cpp
	../io2d_cg_surfaces.h
	../io2d_cg_surfaces.cpp
   	../io2d_cg_gradient.cpp
    	../io2d_cg_gradient.h
	../io2d_cg_colors.cpp
	../io2d_cg_colors.h
	../io2d_cg_texture.cpp
	../io2d_cg_texture.h
)
set(IO2D_LIB_HEADERS 
	io2d.h
	io2d_cg.h
	io2d_cg_frontend.h
	io2d_cg_brushes.h
	io2d_cg_interop.h
	io2d_cg_output_surfaces.h
	io2d_cg_paths.h
	io2d_cg_surface_state_props.h
	io2d_cg_paths_figures.h
	io2d_cg_surfaces.h
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

#install(TARGETS io2d
#	ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
#)
#install(FILES ${IO2D_LIB_HEADERS}
#        DESTINATION ${CMAKE_BINARY_DIR}/include
#)
