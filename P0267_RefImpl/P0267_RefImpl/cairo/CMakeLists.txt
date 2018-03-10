cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

set(IO2D_LIB_SRC 
	cairo_renderer_win32.cpp
	cairo_renderer-graphicsmagickinit.cpp
	../rgba_color.cpp
)

add_library(io2d ${IO2D_LIB_SRC})

target_include_directories(io2d PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)
 
if(MSVC)
	target_compile_definitions(io2d PUBLIC -DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)

	find_path(CAIRO_INCLUDE_DIR cairo.h)
	find_path(GRAPHICSMAGICK_INCLUDE_DIR magick/api.h)
	find_library(CAIRO_LIB cairo)
	find_library(GRAPHICSMAGICK_LIB graphicsmagick)
	find_library(PIXMAN_LIB pixman-1)
	find_library(FREETYPE_LIB freetype)
	find_library(FONTCONFIG_LIB fontconfig)
	find_library(BZ_LIB bz2)
	find_library(ZLIB_LIB zlib)
	find_library(JPEG_LIB jpeg)
	find_library(PNG_LIB libpng16)
	find_library(TIFF_LIB tiff)
	find_library(EXPAT_LIB expat)
	find_library(LZMA_LIB lzma)
	find_library(ICONV_LIB libiconv)
	find_library(CHARSET_LIB libcharset)
endif()
 

target_include_directories(io2d PUBLIC ${CAIRO_INCLUDE_DIR} ${GRAPHICSMAGICK_INCLUDE_DIR})
target_link_libraries(io2d ${CAIRO_LIB} ${GRAPHICSMAGICK_LIB} ${PIXMAN_LIB} ${FREETYPE_LIB} ${FONTCONFIG_LIB} ${BZ_LIB} ${ZLIB_LIB} ${JPEG_LIB} ${PNG_LIB} ${TIFF_LIB} ${EXPAT_LIB} ${LZMA_LIB} ${ICONV_LIB} ${CHARSET_LIB})

install(TARGETS io2d
	ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
)
