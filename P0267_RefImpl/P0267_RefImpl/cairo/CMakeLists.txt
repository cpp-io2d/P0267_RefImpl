cmake_minimum_required(VERSION 3.8)

project(io2d CXX)

find_package(Cairo REQUIRED)
find_package(GraphicsMagick REQUIRED)

add_library(io2d_cairo
	cairo_renderer-graphicsmagickinit.cpp
	xcairo.h
	xcairo_brushes_impl.h
	xcairo_helpers.h
	xcairo_paths_impl.h
	xcairo_surfaces_image_impl.h
	xcairo_surfaces_impl.h
	xcairo_surface_state_props_impl.h
	xio2d_cairo_main.h
)

target_include_directories(io2d_cairo PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(io2d_cairo PUBLIC cxx_std_17)

target_link_libraries(io2d_cairo PUBLIC io2d_core Cairo::Cairo GraphicsMagick::GraphicsMagick)

install(
	TARGETS io2d_cairo EXPORT io2d_targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

file(
	GLOB IO2D_CAIRO_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

install(
	FILES ${IO2D_CAIRO_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
