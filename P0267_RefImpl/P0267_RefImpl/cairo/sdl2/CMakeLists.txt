cmake_minimum_required(VERSION 3.8)
project(io2d CXX)

# Find dependencies
find_package(SDL2 REQUIRED)

# Create and configure library
add_library(io2d_cairo_sdl2
	cairo_renderer_sdl2.cpp
	io2d.h
	io2d_cairo_sdl2.h
	xio2d_cairo_sdl2_main.h
	xio2d_cairo_sdl2_output_surfaces.h
	xio2d_cairo_sdl2_surfaces.h
	xio2d_cairo_sdl2_surfaces_impl.h
	xio2d_cairo_sdl2_unmanaged_output_surfaces.h
)
target_compile_features(io2d_cairo_sdl2 PUBLIC cxx_std_17)
target_include_directories(io2d_cairo_sdl2 PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	${SDL2_INCLUDE_DIRS}
)
target_link_libraries(io2d_cairo_sdl2 PUBLIC io2d_cairo ${SDL2_LIBRARIES})

# Install library artifact(s)
install(
	TARGETS io2d_cairo_sdl2 EXPORT io2d_targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
file(
	GLOB IO2D_CAIRO_SDL2_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
install(
	FILES ${IO2D_CAIRO_SDL2_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
