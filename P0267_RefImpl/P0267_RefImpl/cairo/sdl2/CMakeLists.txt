cmake_minimum_required(VERSION 3.8)
project(io2d CXX)

# Find dependencies
find_package(SDL2 REQUIRED)

# HACK: on Apple, find + link-to dependencies of GraphicsMagick,
#  lest we get linker errors when building certain demo-apps
if (APPLE)
	find_package(LibXml2 REQUIRED)
	find_package(PNG REQUIRED)
	find_package(JPEG REQUIRED)
	find_package(ZLIB REQUIRED)
	find_package(X11 REQUIRED)
	find_package(TIFF REQUIRED)
	find_package(Freetype REQUIRED)
	find_package(BZip2 REQUIRED)

	# Use find_library(...), rather than find_package(...), for
	# stuff that doesn't have CMake find_package(...) modules.
	find_library(LCMS2_LIBRARIES lcms2)
	if (NOT LCMS2_LIBRARIES)
		message(FATAL_ERROR "Unable to find library: lcms2")
	endif()

	find_library(WEBP_LIBRARIES webp)
	if (NOT WEBP_LIBRARIES)
		message(FATAL_ERROR "Unable to find library: webp")
	endif()

	find_library(WEBPMUX_LIBRARIES webpmux)
	if (NOT WEBPMUX_LIBRARIES)
		message(FATAL_ERROR "Unable to find library: webpmux")
	endif()
endif()

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
target_link_libraries(io2d_cairo_sdl2
	PUBLIC
		io2d_cairo
		${SDL2_LIBRARIES}
)

if (APPLE)
	# Follow-up with above hack, regarding linking of GraphicsMagick's
	#  dependencies (lest we may get linker errors).
	target_link_libraries(io2d_cairo_sdl2
		PUBLIC
			# LibXml2::LibXml2		# dludwig@pobox.com: this causes errors for me when building with Homebrew installed, on macOS 10.14
			${LIBXML2_LIBRARIES}
			PNG::PNG
			JPEG::JPEG
			${LCMS2_LIBRARIES}
			${X11_LIBRARIES}
			${WEBP_LIBRARIES}
			${WEBPMUX_LIBRARIES}
			TIFF::TIFF
			Freetype::Freetype
			BZip2::BZip2
	)
endif()

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
