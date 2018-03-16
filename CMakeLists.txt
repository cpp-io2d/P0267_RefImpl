cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)



if( ${IO2D_BACKEND} STREQUAL "COREGRAPHICS_MAC" )
	add_subdirectory(P0267_RefImpl/P0267_RefImpl/coregraphics/mac)
elseif( ${IO2D_BACKEND} STREQUAL "CAIRO_XLIB" )
	add_subdirectory(P0267_RefImpl/P0267_RefImpl/cairo/xlib)
elseif( ${IO2D_BACKEND} STREQUAL "CAIRO_WIN32" )
	add_subdirectory(P0267_RefImpl/P0267_RefImpl/cairo/win32)
else()
	message( FATAL_ERROR "Please specify a backend via IO2D_BACKEND. Possible values are CAIRO_WIN32, CAIRO_XLIB, COREGRAPHICS_MAC" )
endif()



if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
	add_subdirectory(P0267_RefImpl/Samples)
endif()


if( NOT DEFINED IO2D_WITHOUT_TESTS )
	enable_testing()
	add_subdirectory(P0267_RefImpl/Tests)
endif()
