cmake_minimum_required(VERSION 3.8)

project(io2d CXX)

add_library(io2d_coregraphics_mac
	io2d.h
	io2d_coregraphics_mac.h
	xio2d_cg_output_surfaces.h
	xio2d_cg_output_surfaces.mm
)

target_include_directories(io2d_coregraphics_mac PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(io2d_coregraphics_mac PUBLIC cxx_std_17)

target_link_libraries(io2d_coregraphics_mac PUBLIC io2d_coregraphics)

target_link_libraries(io2d_coregraphics_mac PUBLIC "-framework Cocoa")
target_link_libraries(io2d_coregraphics_mac PUBLIC "-framework AppKit")
target_link_libraries(io2d_coregraphics_mac PUBLIC "-framework CoreServices")

install(
	TARGETS io2d_coregraphics_mac EXPORT io2d_targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

file(
	GLOB IO2D_COREGRAPHICS_MAC_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

install(
	FILES ${IO2D_COREGRAPHICS_MAC_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
