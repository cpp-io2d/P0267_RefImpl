cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX C)

set(CMAKE_CXX_STANDARD 17)

if(EMSCRIPTEN)
	# Build library, "pixman".  This is a dependency for Cairo
	set(PIXMAN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/pixman/pixman")
	add_library(pixman STATIC
		"${PIXMAN_SOURCE_DIR}/pixman-access.c"
		"${PIXMAN_SOURCE_DIR}/pixman-access-accessors.c"
		"${PIXMAN_SOURCE_DIR}/pixman-arm.c"
		"${PIXMAN_SOURCE_DIR}/pixman-bits-image.c"
		"${PIXMAN_SOURCE_DIR}/pixman-combine-float.c"
		"${PIXMAN_SOURCE_DIR}/pixman-combine32.c"
		"${PIXMAN_SOURCE_DIR}/pixman-conical-gradient.c"
		"${PIXMAN_SOURCE_DIR}/pixman-edge.c"
		"${PIXMAN_SOURCE_DIR}/pixman-edge-accessors.c"
		"${PIXMAN_SOURCE_DIR}/pixman-fast-path.c"
		"${PIXMAN_SOURCE_DIR}/pixman-general.c"
		"${PIXMAN_SOURCE_DIR}/pixman-gradient-walker.c"
		"${PIXMAN_SOURCE_DIR}/pixman-image.c"
		"${PIXMAN_SOURCE_DIR}/pixman-implementation.c"
		"${PIXMAN_SOURCE_DIR}/pixman-linear-gradient.c"
		"${PIXMAN_SOURCE_DIR}/pixman-matrix.c"
		"${PIXMAN_SOURCE_DIR}/pixman-mips.c"
		"${PIXMAN_SOURCE_DIR}/pixman-noop.c"
		"${PIXMAN_SOURCE_DIR}/pixman-ppc.c"
		"${PIXMAN_SOURCE_DIR}/pixman-radial-gradient.c"
		"${PIXMAN_SOURCE_DIR}/pixman-region32.c"
		"${PIXMAN_SOURCE_DIR}/pixman-solid-fill.c"
		"${PIXMAN_SOURCE_DIR}/pixman-trap.c"
		"${PIXMAN_SOURCE_DIR}/pixman-utils.c"
		"${PIXMAN_SOURCE_DIR}/pixman-x86.c"
		"${PIXMAN_SOURCE_DIR}/pixman.c"
	)
	target_include_directories(pixman PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external")
	set_target_properties(pixman PROPERTIES
		COMPILE_FLAGS "-DPACKAGE -DPIXMAN_NO_TLS -Wno-shift-negative-value -Wno-tautological-constant-out-of-range-compare"
	)

	# Build library, "cairo".  This handles a large bulk of rendering.
	set(CAIRO_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/cairo/src")
	add_library(cairo STATIC
		"${CAIRO_SOURCE_DIR}/cairo-analysis-surface.c"
		"${CAIRO_SOURCE_DIR}/cairo-arc.c"
		"${CAIRO_SOURCE_DIR}/cairo-array.c"
		"${CAIRO_SOURCE_DIR}/cairo-atomic.c"
		"${CAIRO_SOURCE_DIR}/cairo-bentley-ottmann-rectangular.c"
		"${CAIRO_SOURCE_DIR}/cairo-bentley-ottmann-rectilinear.c"
		"${CAIRO_SOURCE_DIR}/cairo-bentley-ottmann.c"
		"${CAIRO_SOURCE_DIR}/cairo-boxes-intersect.c"
		"${CAIRO_SOURCE_DIR}/cairo-boxes.c"
		"${CAIRO_SOURCE_DIR}/cairo-cache.c"
		"${CAIRO_SOURCE_DIR}/cairo-clip-boxes.c"
		"${CAIRO_SOURCE_DIR}/cairo-clip-polygon.c"
		"${CAIRO_SOURCE_DIR}/cairo-clip-region.c"
		"${CAIRO_SOURCE_DIR}/cairo-clip-surface.c"
		"${CAIRO_SOURCE_DIR}/cairo-clip.c"
		"${CAIRO_SOURCE_DIR}/cairo-color.c"
		"${CAIRO_SOURCE_DIR}/cairo-composite-rectangles.c"
		"${CAIRO_SOURCE_DIR}/cairo-compositor.c"
		"${CAIRO_SOURCE_DIR}/cairo-contour.c"
		"${CAIRO_SOURCE_DIR}/cairo-damage.c"
		"${CAIRO_SOURCE_DIR}/cairo-default-context.c"
		"${CAIRO_SOURCE_DIR}/cairo-device.c"
		"${CAIRO_SOURCE_DIR}/cairo-error.c"
		"${CAIRO_SOURCE_DIR}/cairo-font-face-twin-data.c"
		"${CAIRO_SOURCE_DIR}/cairo-font-face-twin.c"
		"${CAIRO_SOURCE_DIR}/cairo-font-face.c"
		"${CAIRO_SOURCE_DIR}/cairo-font-options.c"
		"${CAIRO_SOURCE_DIR}/cairo-freelist.c"
		"${CAIRO_SOURCE_DIR}/cairo-ft-font.c"
		"${CAIRO_SOURCE_DIR}/cairo-gstate.c"
		"${CAIRO_SOURCE_DIR}/cairo-hash.c"
		"${CAIRO_SOURCE_DIR}/cairo-image-compositor.c"
		"${CAIRO_SOURCE_DIR}/cairo-image-source.c"
		"${CAIRO_SOURCE_DIR}/cairo-image-surface.c"
		"${CAIRO_SOURCE_DIR}/cairo-line.c"
		"${CAIRO_SOURCE_DIR}/cairo-matrix.c"
		"${CAIRO_SOURCE_DIR}/cairo-mesh-pattern-rasterizer.c"
		"${CAIRO_SOURCE_DIR}/cairo-misc.c"
		"${CAIRO_SOURCE_DIR}/cairo-mono-scan-converter.c"
		"${CAIRO_SOURCE_DIR}/cairo-no-compositor.c"
		"${CAIRO_SOURCE_DIR}/cairo-observer.c"
		"${CAIRO_SOURCE_DIR}/cairo-output-stream.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-bounds.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-fill.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-fixed.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-in-fill.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-stroke-boxes.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-stroke-polygon.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-stroke-traps.c"
		"${CAIRO_SOURCE_DIR}/cairo-path-stroke.c"
		"${CAIRO_SOURCE_DIR}/cairo-path.c"
		"${CAIRO_SOURCE_DIR}/cairo-pattern.c"
		"${CAIRO_SOURCE_DIR}/cairo-pen.c"
		"${CAIRO_SOURCE_DIR}/cairo-png.c"
		"${CAIRO_SOURCE_DIR}/cairo-polygon-intersect.c"
		"${CAIRO_SOURCE_DIR}/cairo-polygon-intersect.c"
		"${CAIRO_SOURCE_DIR}/cairo-polygon-reduce.c"
		"${CAIRO_SOURCE_DIR}/cairo-polygon.c"
		"${CAIRO_SOURCE_DIR}/cairo-raster-source-pattern.c"
		"${CAIRO_SOURCE_DIR}/cairo-recording-surface.c"
		"${CAIRO_SOURCE_DIR}/cairo-rectangle.c"
		"${CAIRO_SOURCE_DIR}/cairo-rectangular-scan-converter.c"
		"${CAIRO_SOURCE_DIR}/cairo-region.c"
		"${CAIRO_SOURCE_DIR}/cairo-scaled-font.c"
		"${CAIRO_SOURCE_DIR}/cairo-shape-mask-compositor.c"
		"${CAIRO_SOURCE_DIR}/cairo-slope.c"
		"${CAIRO_SOURCE_DIR}/cairo-spans-compositor.c"
		"${CAIRO_SOURCE_DIR}/cairo-spans.c"
		"${CAIRO_SOURCE_DIR}/cairo-spline.c"
		"${CAIRO_SOURCE_DIR}/cairo-stroke-dash.c"
		"${CAIRO_SOURCE_DIR}/cairo-stroke-style.c"
		"${CAIRO_SOURCE_DIR}/cairo-surface-offset.c"
		"${CAIRO_SOURCE_DIR}/cairo-surface-snapshot.c"
		"${CAIRO_SOURCE_DIR}/cairo-surface-wrapper.c"
		"${CAIRO_SOURCE_DIR}/cairo-surface.c"
		"${CAIRO_SOURCE_DIR}/cairo-tor-scan-converter.c"
		"${CAIRO_SOURCE_DIR}/cairo-tor22-scan-converter.c"
		"${CAIRO_SOURCE_DIR}/cairo-toy-font-face.c"
		"${CAIRO_SOURCE_DIR}/cairo-traps-compositor.c"
		"${CAIRO_SOURCE_DIR}/cairo-traps.c"
		"${CAIRO_SOURCE_DIR}/cairo-unicode.c"
		"${CAIRO_SOURCE_DIR}/cairo-user-font.c"
		"${CAIRO_SOURCE_DIR}/cairo-wideint.c"
		"${CAIRO_SOURCE_DIR}/cairo.c"
	)
	target_include_directories(cairo PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/external"
		"${CMAKE_CURRENT_SOURCE_DIR}/external/pixman/pixman"
	)
	set_target_properties(cairo PROPERTIES
		COMPILE_FLAGS "-s USE_FREETYPE=1 -s USE_LIBPNG=1 -DCAIRO_FEATURES_H -Wno-enum-conversion -Wno-parentheses-equality -Wno-incompatible-pointer-types"
	)
endif()

add_library(io2d_cairo_sdl2
   	io2d.h
    io2d_cairo_sdl2.h
	cairo_renderer_sdl2.cpp
    xio2d_cairo_sdl2_main.h
	xio2d_cairo_sdl2_output_surfaces.h
	xio2d_cairo_sdl2_unmanaged_output_surfaces.h
	xio2d_cairo_sdl2_surfaces.h
   	xio2d_cairo_sdl2_surfaces_impl.h
	../xio2d_cairo_main.h
	../xcairo.h
	../xcairo_brushes_impl.h
	../xcairo_helpers.h
	../xcairo_paths_impl.h
	../xcairo_surface_state_props_impl.h
	../xcairo_surfaces_image_impl.h
	../xcairo_surfaces_impl.h
	../cairo_renderer-graphicsmagickinit.cpp
    ../../xpath.h
    ../../xpath_impl.h
    ../../xpathbuilder_impl.h
)

target_include_directories(io2d_cairo_sdl2 PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/../..
)

if(EMSCRIPTEN)
	target_include_directories(io2d_cairo_sdl2 SYSTEM PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/external"
		"${CMAKE_CURRENT_SOURCE_DIR}/external/cairo/src"
		"${CMAKE_CURRENT_SOURCE_DIR}/external/pixman/pixman"
	)
	target_link_libraries(io2d_cairo_sdl2
		"-s USE_SDL=2"
		"-s USE_FREETYPE=1"
		cairo
		pixman
	)
	target_compile_options(io2d_cairo_sdl2
		PRIVATE -s USE_SDL=2
	)
else()
	find_path(CAIRO_INCLUDE_DIR cairo-xlib.h PATH_SUFFIXES cairo)
	find_path(GRAPHICSMAGICK_INCLUDE_DIR magick/api.h PATH_SUFFIXES GraphicsMagick)
	find_library(CAIRO_LIB cairo)
	find_library(GRAPHICSMAGICK_LIB GraphicsMagick)
	find_library(PIXMAN_LIB pixman-1)
	find_library(FREETYPE_LIB freetype)
	find_library(FONTCONFIG_LIB fontconfig)
	find_library(BZ_LIB bz2)
	find_library(ZLIB_LIB z)
	find_library(JPEG_LIB jpeg)
	find_library(PNG_LIB png)
	find_library(TIFF_LIB tiff)
	find_library(EXPAT_LIB expat)
	find_library(LZMA_LIB lzma)
	find_library(X11_LIB X11)

	if(USE_DEVELOPMENT_SDL2)
		set(SDL2_INCLUDE_DIRS "${USE_DEVELOPMENT_SDL2}/include/SDL2")
		set(SDL2_LIBRARIES "-L ${USE_DEVELOPMENT_SDL2}/lib -lSDL2")
	else()
		# list(INSERT CMAKE_MODULE_PATH 0 "${USE_DEVELOPMENT_SDL2}/lib/cmake/SDL2")
		# message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
		# find_package(SDL2 REQUIRED)
		find_package(SDL2 REQUIRED)
	endif()

	target_include_directories(io2d_cairo_sdl2 SYSTEM PUBLIC ${CAIRO_INCLUDE_DIR} ${GRAPHICSMAGICK_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
	target_link_libraries(io2d_cairo_sdl2 ${CAIRO_LIB} ${GRAPHICSMAGICK_LIB} ${PIXMAN_LIB} ${FREETYPE_LIB} ${FONTCONFIG_LIB} ${BZ_LIB} ${ZLIB_LIB} ${JPEG_LIB} ${PNG_LIB} ${TIFF_LIB} ${EXPAT_LIB} ${LZMA_LIB} ${ICONV_LIB} ${CHARSET_LIB} ${X11_LIB} ${SDL2_LIBRARIES})

endif()

set(ICONV_LIB "")
set(CHARSET_LIB "")

#install(TARGETS io2d
#    ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
#)
