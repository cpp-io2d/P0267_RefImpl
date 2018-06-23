cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

if(EMSCRIPTEN)
	# Enable web-browser step-debugging, when compiling with Emscripten
	set(CMAKE_CXX_FLAGS_DEBUG "-g4 --source-map-base http://127.0.0.1:8080/")

	# TODO(dludwig@pobox.com): Enable tests in io2d's Emscripten port
    set(IO2D_WITHOUT_TESTS 1)
endif()

add_subdirectory(P0267_RefImpl/P0267_RefImpl)

if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
	add_subdirectory(P0267_RefImpl/Samples)
endif()

if( NOT DEFINED IO2D_WITHOUT_TESTS )
	enable_testing()
	add_subdirectory(P0267_RefImpl/Tests)
endif()
