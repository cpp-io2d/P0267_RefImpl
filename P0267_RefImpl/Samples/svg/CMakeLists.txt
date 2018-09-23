cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

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

add_executable(${PROJECT_ID}
	main.cpp
	svg.h
	svg.cpp
	window.h
	window.cpp
)

if(MSVC)
	target_compile_options(${PROJECT_ID} PUBLIC /bigobj /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING /wd4459 /wd4702)
endif()

target_link_libraries(${PROJECT_ID} io2d)
target_include_directories(${PROJECT_ID}
  PRIVATE external/svgpp/include
  PRIVATE external
)
target_include_directories(${PROJECT_ID} SYSTEM
  PRIVATE ${Boost_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT_ID}
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
install(FILES example.svg
        DESTINATION ${CMAKE_BINARY_DIR}/samples
)
