cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

set(IO2D_LIB_SRC
   	io2d.h
    io2d_cairo_xlib.h
	cairo_renderer_xlib.cpp
    xio2d_cairo_xlib_main.h
	xio2d_cairo_xlib_output_surfaces.h
	xio2d_cairo_xlib_unmanaged_output_surfaces.h
	xio2d_cairo_xlib_surfaces.h
   	xio2d_cairo_xlib_surfaces_impl.h
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

add_library(io2d_cairo_xlib ${IO2D_LIB_SRC})

target_include_directories(io2d_cairo_xlib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

if(MSVC)
# TODO?
elseif(APPLE)
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
	find_library(PNG_LIB png16)
	find_library(TIFF_LIB tiff)
	find_library(EXPAT_LIB expat)
	find_library(LZMA_LIB lzma)
	find_library(ICONV_LIB iconv)
	find_library(CHARSET_LIB charset)
    find_library(X11_LIB X11)
else() # Linux
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
	set(ICONV_LIB "")
	set(CHARSET_LIB "")
endif()

target_include_directories(io2d_cairo_xlib SYSTEM PUBLIC ${CAIRO_INCLUDE_DIR} ${GRAPHICSMAGICK_INCLUDE_DIR})
target_link_libraries(io2d_cairo_xlib ${CAIRO_LIB} ${GRAPHICSMAGICK_LIB} ${PIXMAN_LIB} ${FREETYPE_LIB} ${FONTCONFIG_LIB} ${BZ_LIB} ${ZLIB_LIB} ${JPEG_LIB} ${PNG_LIB} ${TIFF_LIB} ${EXPAT_LIB} ${LZMA_LIB} ${ICONV_LIB} ${CHARSET_LIB} ${X11_LIB})

install(
    TARGETS io2d_cairo_xlib
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
