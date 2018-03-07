cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)
enable_testing()
set(CMAKE_CXX_STANDARD 17)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

find_path(PNG_INCLUDE_DIR libpng16/png.h)
find_library(PNG_LIB png16)

add_executable(tests
	main.cpp
	background_paint.cpp
    comparison.h
    comparison.cpp
)

target_include_directories(tests PUBLIC ${PNG_INCLUDE_DIR})
target_link_libraries(tests io2d Catch ${PNG_LIB})

set(RSC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Reference)
set(RSC_TARGET $<TARGET_FILE_DIR:tests>)

add_custom_command( TARGET tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}/red_background_300x200.png" "${RSC_TARGET}/red_background_300x200.png"
)

if(MSVC)
	set_target_properties(tests PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()

add_test(NAME Tests COMMAND tests)

