cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)
set(CMAKE_CXX_STANDARD 17)

if( NOT DEFINED IO2D_DEFAULT )
	message( FATAL_ERROR "Please specify the default backend via IO2D_DEFAULT. Possible values are CAIRO_WIN32, CAIRO_XLIB, COREGRAPHICS_MAC" )
endif()

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
)

target_include_directories(io2d PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)


function(GET_BACKEND_INFO backend_name)
	if( ${backend_name} STREQUAL "COREGRAPHICS_MAC" )
		set(BACKEND_PATH coregraphics/mac PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_coregraphics_mac PARENT_SCOPE)
	elseif( ${backend_name} STREQUAL "CAIRO_XLIB" )
		set(BACKEND_PATH cairo/xlib PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_cairo_xlib PARENT_SCOPE)
	elseif( ${backend_name} STREQUAL "CAIRO_WIN32" )
		set(BACKEND_PATH cairo/win32 PARENT_SCOPE)
		set(BACKEND_LIBRARY io2d_cairo_win32 PARENT_SCOPE)
	else()
		message( FATAL_ERROR "GET_BACKEND_INFO: unknown backend name" )
	endif()
endfunction(GET_BACKEND_INFO)


#GET_BACKEND_INFO(COREGRAPHICS_MAC)

GET_BACKEND_INFO(${IO2D_DEFAULT})



# add a search path depending on a default backend setting
target_include_directories(io2d PUBLIC
#  ${CMAKE_CURRENT_SOURCE_DIR}/coregraphics/mac
  ${CMAKE_CURRENT_SOURCE_DIR}/${BACKEND_PATH}
)


# add backends themselves


foreach(backend ${IO2D_ENABLED})
	GET_BACKEND_INFO(${backend})
	add_subdirectory(${BACKEND_PATH})
	target_link_libraries(io2d ${BACKEND_LIBRARY})
endforeach(backend)

#BACKEND_LIBRARY

#add_subdirectory(${BACKEND_PATH})
#target_link_libraries(io2d ${BACKEND_LIBRARY})

	
#add_subdirectory(coregraphics/mac)
#target_link_libraries(io2d io2d_coregraphics_mac)

