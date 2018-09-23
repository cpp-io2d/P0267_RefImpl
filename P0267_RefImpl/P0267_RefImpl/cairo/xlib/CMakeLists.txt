cmake_minimum_required(VERSION 3.8)

project(io2d CXX)

add_library(io2d_cairo_xlib
	cairo_renderer_xlib.cpp
	io2d.h
	io2d_cairo_xlib.h
	xio2d_cairo_xlib_main.h
	xio2d_cairo_xlib_output_surfaces.h
	xio2d_cairo_xlib_surfaces.h
	xio2d_cairo_xlib_surfaces_impl.h
	xio2d_cairo_xlib_unmanaged_output_surfaces.h
)

target_include_directories(io2d_cairo_xlib PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(io2d_cairo_xlib PUBLIC cxx_std_17)

target_link_libraries(io2d_cairo_xlib PUBLIC io2d_cairo)

if(MSVC)
# TODO?
elseif(APPLE)
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

target_link_libraries(io2d_cairo_xlib PUBLIC ${PIXMAN_LIB} ${FREETYPE_LIB} ${FONTCONFIG_LIB} ${BZ_LIB} ${ZLIB_LIB} ${JPEG_LIB} ${PNG_LIB} ${TIFF_LIB} ${EXPAT_LIB} ${LZMA_LIB} ${ICONV_LIB} ${CHARSET_LIB} ${X11_LIB})

install(
	TARGETS io2d_cairo_xlib EXPORT io2d_targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

file(
	GLOB IO2D_CAIRO_XLIB_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

install(
	FILES ${IO2D_CAIRO_XLIB_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
