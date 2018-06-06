cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)
set(CMAKE_CXX_STANDARD 17)

# If there's no default backend we try to set it automatically
if( NOT DEFINED IO2D_DEFAULT )
	message( "Default IO2D backend was not specified, choosing automatically..." )
	if( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
		message( "Found Windows, using CAIRO_WIN32." )
		set(IO2D_DEFAULT CAIRO_WIN32)
	elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
		message( "Found macOS, using CAIRO_XLIB." )
		set(IO2D_DEFAULT CAIRO_XLIB)
	elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )	
		message( "Found Linux, using CAIRO_XLIB." )
		set(IO2D_DEFAULT CAIRO_XLIB)
	else()	
		message( FATAL_ERROR "Failed to detect the platform type. Please manually specify the default backend via IO2D_DEFAULT. Possible values include CAIRO_WIN32, CAIRO_XLIB, CAIRO_SDL2, COREGRAPHICS_MAC." )
	endif()
endif()

# In most of the cases, there's only one enabled backend which is IO2D_DEFAULT.
if( NOT DEFINED IO2D_ENABLED )
	set(IO2D_ENABLED ${IO2D_DEFAULT})
endif()

add_library(io2d
	rgba_color.cpp
	xio2d.h
	xbrushes.h
	xcolor.h
	xdiagnostics.h
	xgraphicsmath.h
	xgraphicsmathfloat.h
	xinput.h
	xio2d.h
	xpath.h
	xsurfaces_enums.h
	xsurfaces.h
	xtext.h
	xbrushes_impl.h
	xgraphicsmath_impl.h
	xgraphicsmathfloat_impl.h
	xio2d_impl.h
	xpath_impl.h
	xpathbuilder_impl.h
	xsurfaces_impl.h
	xsurfacesprops_impl.h
    xinterchangebuffer.cpp
    xinterchangebuffer.h
)

target_include_directories(io2d PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)


# function that maps a backend name into it's path and library name
function(GET_BACKEND_INFO backend_name)
	if( ${backend_name} STREQUAL "COREGRAPHICS_MAC" )
		set(BACKEND_PATH coregraphics/mac PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_coregraphics_mac PARENT_SCOPE)
	elseif( ${backend_name} STREQUAL "COREGRAPHICS_IOS" )
		set(BACKEND_PATH coregraphics/ios PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_coregraphics_ios PARENT_SCOPE)
	elseif( ${backend_name} STREQUAL "CAIRO_XLIB" )
		set(BACKEND_PATH cairo/xlib PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_cairo_xlib PARENT_SCOPE)
	elseif( ${backend_name} STREQUAL "CAIRO_WIN32" )
		set(BACKEND_PATH cairo/win32 PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_cairo_win32 PARENT_SCOPE)
	elseif( ${backend_name} STREQUAL "CAIRO_SDL2" )
		set(BACKEND_PATH cairo/sdl2 PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_cairo_sdl2 PARENT_SCOPE)
	else()
		message( FATAL_ERROR "GET_BACKEND_INFO: unknown backend name" )
	endif()
endfunction(GET_BACKEND_INFO)

# fetch info about the default backend
GET_BACKEND_INFO(${IO2D_DEFAULT})

# add a search path depending on a default backend setting
target_include_directories(io2d PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/${BACKEND_PATH}
)

# add backends themselves
foreach(backend ${IO2D_ENABLED})
	GET_BACKEND_INFO(${backend})
	add_subdirectory(${BACKEND_PATH})
	target_link_libraries(io2d ${BACKEND_LIBRARY})
endforeach(backend)
