cmake_minimum_required(VERSION 3.8)

project(io2d CXX)

add_library(io2d_coregraphics
	xio2d_cg_brushes.cpp
	xio2d_cg_brushes.h
	xio2d_cg_colors.cpp
	xio2d_cg_colors.h
	xio2d_cg_display.cpp
	xio2d_cg_display.h
	xio2d_cg_fps_counter.cpp
	xio2d_cg_fps_counter.h
	xio2d_cg_gradient.cpp
	xio2d_cg_gradient.h
	xio2d_cg_interop.h
	xio2d_cg_main.h
	xio2d_cg_paths.cpp
	xio2d_cg_paths.h
	xio2d_cg_paths_figures.cpp
	xio2d_cg_paths_figures.h
	xio2d_cg_surfaces.cpp
	xio2d_cg_surfaces.h
	xio2d_cg_surface_state_props.h
	xio2d_cg_texture.cpp
	xio2d_cg_texture.h
	xio2d_cg_tmplayer.cpp
	xio2d_cg_tmplayer.h
)

target_include_directories(io2d_coregraphics PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(io2d_coregraphics PUBLIC cxx_std_17)

target_link_libraries(io2d_coregraphics PUBLIC io2d_core)

target_link_libraries(io2d_coregraphics PUBLIC "-framework CoreFoundation")
target_link_libraries(io2d_coregraphics PUBLIC "-framework ImageIO")
target_link_libraries(io2d_coregraphics PUBLIC "-framework CoreGraphics")

install(
	TARGETS io2d_coregraphics EXPORT io2d_targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

file(
	GLOB IO2D_COREGRAPHICS_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

install(
	FILES ${IO2D_COREGRAPHICS_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
