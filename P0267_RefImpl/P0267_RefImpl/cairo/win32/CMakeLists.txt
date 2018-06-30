cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

set(IO2D_LIB_SRC 
	io2d.h
	io2d_cairo_win32.h
	xio2d_cairo_win32_main.h
	xio2d_cairo_win32_output_surface.h
	xio2d_cairo_win32_unmanaged_output_surface.h
	xio2d_cairo_win32_surfaces.h
	xio2d_cairo_win32_surfaces_impl.h
	xio2d_cairo_win32_error.h
	cairo_renderer_win32.cpp
	../xcairo.h
	../xcairo_brushes_impl.h
	../xcairo_helpers.h
	../xcairo_paths_impl.h
	../xcairo_surface_state_props_impl.h
	../xcairo_surfaces_image_impl.h
	../xcairo_surfaces_impl.h
	../xio2d_cairo_main.h
	../cairo_renderer-graphicsmagickinit.cpp
)

add_library(io2d_cairo_win32 ${IO2D_LIB_SRC})

target_include_directories(io2d_cairo_win32 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
 
if(MSVC)
	target_compile_definitions(io2d_cairo_win32 PUBLIC -DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)

	find_path(CAIRO_INCLUDE_DIR cairo.h)
	find_path(GRAPHICSMAGICK_INCLUDE_DIR magick/api.h)
	find_library(CAIRO_LIB_DEBUG cairod)
	find_library(CAIRO_LIB_RELEASE cairo)
	find_library(GRAPHICSMAGICK_LIB graphicsmagick)
	find_library(PIXMAN_LIB pixman-1)
	find_library(FREETYPE_LIB freetype)
	find_library(FONTCONFIG_LIB fontconfig)
	find_library(BZ_LIB bz2)
	find_library(ZLIB_LIB_DEBUG zlibd)
	find_library(ZLIB_LIB_RELEASE zlib)
	find_library(JPEG_LIB jpeg)
	find_library(PNG_LIB_DEBUG libpng16d)
	find_library(PNG_LIB_RELEASE libpng16)
	find_library(TIFF_LIB tiff)
	find_library(EXPAT_LIB expat)
	find_library(LZMA_LIB lzma)
	find_library(ICONV_LIB libiconv)
	find_library(CHARSET_LIB libcharset)

	target_include_directories(io2d_cairo_win32 PUBLIC ${CAIRO_INCLUDE_DIR} ${GRAPHICSMAGICK_INCLUDE_DIR})
	target_link_libraries(io2d_cairo_win32 ${GRAPHICSMAGICK_LIB} ${PIXMAN_LIB} ${FREETYPE_LIB} ${FONTCONFIG_LIB} ${BZ_LIB} ${JPEG_LIB} ${TIFF_LIB} ${EXPAT_LIB} ${LZMA_LIB} ${ICONV_LIB} ${CHARSET_LIB})
	target_link_libraries(io2d_cairo_win32 debug ${PNG_LIB_DEBUG} optimized ${PNG_LIB_RELEASE})
	target_link_libraries(io2d_cairo_win32 debug ${ZLIB_LIB_DEBUG} optimized ${ZLIB_LIB_RELEASE})
	target_link_libraries(io2d_cairo_win32 debug ${CAIRO_LIB_DEBUG} optimized ${CAIRO_LIB_RELEASE})
endif()
 
# installation
install(
    TARGETS io2d_cairo_win32
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
file(
    GLOB IO2D_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../*.h"
)
install(
    FILES ${IO2D_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
