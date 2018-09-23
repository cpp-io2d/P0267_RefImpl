cmake_minimum_required(VERSION 3.5.0)

project(io2d CXX)
set(CMAKE_CXX_STANDARD 17)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
#find_package(catch2 REQUIRED)

add_executable(tests
	main.cpp
	background_paint.cpp
   	rectangle_stroke.cpp
	stroke_width.cpp
	stroke_dashes.cpp
	linear_gradient.cpp
	radial_gradient.cpp
    surface_brush.cpp
    mask.cpp
    color.cpp
    blending.cpp
	comparison.h
   	comparison.cpp
    image_io.cpp
    image_format.cpp
    frontend_semantics.cpp
)

target_link_libraries(tests io2d Catch)

if(MSVC)
	find_path(PNG_INCLUDE_DIR libpng16/png.h)
	target_include_directories(tests PUBLIC ${PNG_INCLUDE_DIR})
	find_library(PNG_LIB_DEBUG libpng16d)
	find_library(PNG_LIB_RELEASE libpng16)
	target_link_libraries(tests debug ${PNG_LIB_DEBUG} optimized ${PNG_LIB_RELEASE})
elseif(APPLE)
	find_path(PNG_INCLUDE_DIR libpng16/png.h)
	target_include_directories(tests PUBLIC ${PNG_INCLUDE_DIR})
	find_library(PNG_LIB png16)
	target_link_libraries(tests ${PNG_LIB})	
else() # LINUX
	find_path(PNG_INCLUDE_DIR libpng/png.h)
	target_include_directories(tests PUBLIC ${PNG_INCLUDE_DIR})
	find_library(PNG_LIB png)
	target_link_libraries(tests ${PNG_LIB})	

endif()


set(RSC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Reference)
set(RSC_TARGET $<TARGET_FILE_DIR:tests>)

add_custom_command( TARGET tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${RSC_SOURCE}" "${RSC_TARGET}")

if(MSVC)
	set_target_properties(tests PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()

add_test(
    NAME Tests
    COMMAND tests
    WORKING_DIRECTORY ${RSC_TARGET}
)
