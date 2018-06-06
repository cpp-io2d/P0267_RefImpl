cmake_minimum_required(VERSION 3.0.0)
#set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/CompilerOptions.cmake")
#message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
#message(STATUS "CXX compiler: ${CMAKE_CXX_COMPILER}")

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

add_subdirectory(P0267_RefImpl/P0267_RefImpl)


if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
	add_subdirectory(P0267_RefImpl/Samples)
endif()


if( NOT DEFINED IO2D_WITHOUT_TESTS )
	enable_testing()
	add_subdirectory(P0267_RefImpl/Tests)
endif()
