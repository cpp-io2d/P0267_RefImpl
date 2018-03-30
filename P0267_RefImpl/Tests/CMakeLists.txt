cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)
set(CMAKE_CXX_STANDARD 17)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})


add_executable(tests
	main.cpp
	background_paint.cpp
   	rectangle_stroke.cpp
	stroke_width.cpp
	stroke_dashes.cpp
	linear_gradient.cpp
	radial_gradient.cpp
    surface_brush.cpp
	comparison.h
   	comparison.cpp
)

target_link_libraries(tests io2d Catch)

if(MSVC)
	find_path(PNG_INCLUDE_DIR libpng16/png.h)
	target_include_directories(tests PUBLIC ${PNG_INCLUDE_DIR})
	find_library(PNG_LIB_DEBUG libpng16d)
	find_library(PNG_LIB_RELEASE libpng16)
	target_link_libraries(tests debug ${PNG_LIB_DEBUG} optimized ${PNG_LIB_RELEASE})
else()
	find_path(PNG_INCLUDE_DIR libpng16/png.h)
	target_include_directories(tests PUBLIC ${PNG_INCLUDE_DIR})
	find_library(PNG_LIB png16)
	target_link_libraries(tests ${PNG_LIB})	
endif()


set(RSC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Reference)
set(RSC_TARGET $<TARGET_FILE_DIR:tests>)

function(COPY_REF_RSC)
	foreach(arg IN LISTS ARGN)
		add_custom_command( TARGET tests POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/${arg}" "${RSC_TARGET}/${arg}"
		)
	endforeach()
endfunction()

COPY_REF_RSC(
    red_background_300x200.png
    stroked_rectangle_300x200.png
    stroke_widths_300x200.png
    dash_pattern_two_one_300x200.png
    linear_gradient_aquamarine_dark_magenta_lime_300x200.png
    linear_gradient_wrapping_modes_300x200.png
    linear_gradient_non_convex_300x200.png
    linear_gradient_curve_stroke_300x200.png
    radial_gradient_aquamarine_dark_magenta_lime_300x200.png
    radial_gradient_aquamarine_dark_magenta_lime_reflect_300x200.png
    radial_gradient_wrapping_modes_300x200.png
    radial_gradient_non_convex_300x200.png
    radial_gradient_curve_stroke_300x200.png
    surface_brush_no_wrapping_20x20.png
    surface_brush_repeat_no_transform_20x20.png
    surface_brush_repeat_2x_scale_20x20.png
    surface_brush_repeat_non_uniform_scale_20x20.png
    surface_brush_repeat_x_shear_20x20.png
)


if(MSVC)
	set_target_properties(tests PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()

add_test(
    NAME Tests
    COMMAND tests
    WORKING_DIRECTORY ${RSC_TARGET}
)
