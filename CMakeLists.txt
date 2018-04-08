cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)


add_subdirectory(P0267_RefImpl/P0267_RefImpl)


if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
	add_subdirectory(P0267_RefImpl/Samples)
endif()


if( NOT DEFINED IO2D_WITHOUT_TESTS )
	enable_testing()
	add_subdirectory(P0267_RefImpl/Tests)
endif()
