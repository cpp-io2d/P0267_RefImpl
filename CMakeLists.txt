cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(io2d CXX)
if( MSVC )
	if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
		string (REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
	endif()
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string (REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
	add_compile_options(/permissive-)
#else()
#	message(STATUS "Not MSVC")
endif()


# Setup default installation subpaths, if they were not defined outside
if(NOT DEFINED CMAKE_INSTALL_BINDIR)
    set(CMAKE_INSTALL_BINDIR bin)
endif()
if(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include/io2d)
endif()
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib)
endif()


add_subdirectory(P0267_RefImpl/P0267_RefImpl)


if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
	add_subdirectory(P0267_RefImpl/Samples)
endif()


if( NOT DEFINED IO2D_WITHOUT_TESTS )
	enable_testing()
	add_subdirectory(P0267_RefImpl/Tests)
endif()
