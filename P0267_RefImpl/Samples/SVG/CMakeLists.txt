cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost QUIET)
if( NOT Boost_FOUND )
	message( "Skipping the SVG example since Boost was not found" )
	return()
endif()

if( MSVC )
	if( CMAKE_CXX_COMPILER MATCHES ".*/Hostx86/x86/cl.exe" OR 
            CMAKE_CXX_COMPILER MATCHES ".*/Hostx86/x64/cl.exe")
		message( "Skipping the SVG example since 32-bit cl.exe cannot be used to compile it" )
		return()		
	endif()
endif()

add_executable(svg
	main.cpp
	svg.h
	svg.cpp
	window.h
	window.cpp
)

if(MSVC)
	target_compile_options(svg PUBLIC /bigobj /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING /wd4459 /wd4702)
endif()

target_link_libraries(svg io2d)
target_include_directories(svg
  PRIVATE external/svgpp/include
  PRIVATE external
)
target_include_directories(svg SYSTEM
  PRIVATE ${Boost_INCLUDE_DIRS}
)

install(TARGETS svg
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
install(FILES example.svg
        DESTINATION ${CMAKE_BINARY_DIR}/samples
)
