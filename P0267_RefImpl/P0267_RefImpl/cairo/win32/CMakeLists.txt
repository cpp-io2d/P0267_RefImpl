cmake_minimum_required(VERSION 3.8)

project(io2d CXX)

add_library(io2d_cairo_win32 
	io2d.h
	io2d_cairo_win32.h
	xio2d_cairo_win32_main.h
	xio2d_cairo_win32_output_surface.h
	xio2d_cairo_win32_unmanaged_output_surface.h
	xio2d_cairo_win32_surfaces.h
	xio2d_cairo_win32_surfaces_impl.h
	xio2d_cairo_win32_error.h
	cairo_renderer_win32.cpp
)

target_include_directories(io2d_cairo_win32 PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(io2d_cairo_win32 PUBLIC cxx_std_17)

target_link_libraries(io2d_cairo_win32 PUBLIC io2d_cairo)
 
if(MSVC)
	target_compile_definitions(io2d_cairo_win32 PUBLIC -DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)

	find_library(PIXMAN_LIB pixman-1)
	find_library(FREETYPE_LIB freetype)
	find_library(FONTCONFIG_LIB fontconfig)
	find_library(BZ_LIB bz2)
	find_library(JPEG_LIB jpeg)
	find_library(TIFF_LIB tiff)
	find_library(EXPAT_LIB expat)
	find_library(LZMA_LIB lzma)
	find_library(ICONV_LIB libiconv)
	find_library(CHARSET_LIB libcharset)

	target_link_libraries(io2d_cairo_win32 PUBLIC ${PIXMAN_LIB} ${FREETYPE_LIB} ${FONTCONFIG_LIB} ${BZ_LIB} ${JPEG_LIB} ${TIFF_LIB} ${EXPAT_LIB} ${LZMA_LIB} ${ICONV_LIB} ${CHARSET_LIB})
endif()
 
install(
	TARGETS io2d_cairo_win32 EXPORT io2d_targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

file(
	GLOB IO2D_CAIRO_WIN32_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

install(
	FILES ${IO2D_CAIRO_WIN32_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
