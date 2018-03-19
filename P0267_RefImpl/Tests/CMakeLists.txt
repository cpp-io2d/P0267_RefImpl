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

add_custom_command( TARGET tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/red_background_300x200.png" "${RSC_TARGET}/red_background_300x200.png"
    COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/stroked_rectangle_300x200.png" "${RSC_TARGET}/stroked_rectangle_300x200.png"
    COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/stroke_widths_300x200.png" "${RSC_TARGET}/stroke_widths_300x200.png"
    COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/dash_pattern_two_one_300x200.png" "${RSC_TARGET}/dash_pattern_two_one_300x200.png"
    COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/linear_gradient_aquamarine_dark_magenta_lime_300x200.png" "${RSC_TARGET}/linear_gradient_aquamarine_dark_magenta_lime_300x200.png"
    COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/linear_gradient_wrapping_modes_300x200.png" "${RSC_TARGET}/linear_gradient_wrapping_modes_300x200.png"
)

if(MSVC)
	set_target_properties(tests PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()

add_test(
    NAME Tests
    COMMAND tests
    WORKING_DIRECTORY ${RSC_TARGET}
)
