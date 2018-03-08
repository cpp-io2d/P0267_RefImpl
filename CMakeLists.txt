cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

if(MSVC)
	set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
	)
	foreach(CompilerFlag ${CompilerFlags})
		string(REPLACE "/MD" "/MT" ${CompilerFlag}
			"${${CompilerFlag}}")
	endforeach()
endif()


if( ${IO2D_BACKEND} STREQUAL "COREGRAPHICS_MAC" )
	add_subdirectory(P0267_RefImpl/P0267_RefImpl/coregraphics/mac)
elseif( ${IO2D_BACKEND} STREQUAL "CAIRO_WIN32" )
	add_subdirectory(P0267_RefImpl/P0267_RefImpl/cairo)
endif()

add_subdirectory(P0267_RefImpl/Samples)

enable_testing()
add_subdirectory(P0267_RefImpl/Tests)
