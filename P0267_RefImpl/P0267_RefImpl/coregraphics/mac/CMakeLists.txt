cmake_minimum_required(VERSION 3.0.0)

project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

set(IO2D_LIB_SRC 
	io2d.h
	io2d_cg.h
	io2d_cg_frontend.h
	io2d_cg_brushes.h
	io2d_cg_brushes.cpp
	io2d_cg_interop.h
	io2d_cg_output_surfaces.h
	io2d_cg_output_surfaces.mm
	io2d_cg_paths.h
	io2d_cg_paths.cpp
	io2d_cg_surface_state_props.h
	io2d_cg_paths_figures.h
	io2d_cg_paths_figures.cpp
	io2d_cg_surfaces.h
	io2d_cg_surfaces.cpp
    io2d_cg_linear_gradient.cpp
    io2d_cg_linear_gradient.h
	../../rgba_color.cpp
)
set(IO2D_LIB_HEADERS 
	io2d.h
	io2d_cg.h
	io2d_cg_frontend.h
	io2d_cg_brushes.h
	io2d_cg_interop.h
	io2d_cg_output_surfaces.h
	io2d_cg_paths.h
	io2d_cg_surface_state_props.h
	io2d_cg_paths_figures.h
	io2d_cg_surfaces.h
	../../xio2d.h
	../../xbrushes.h
	../../xcolor.h
	../../xdiagnostics.h
	../../xgraphicsmath.h
	../../xgraphicsmathfloat.h
	../../xinput.h
	../../xio2d.h
	../../xpath.h
	../../xsurfaces_enums.h
	../../xsurfaces.h
	../../xtext.h
	../../xbrushes_impl.h
	../../xgraphicsmath_impl.h
	../../xgraphicsmathfloat_impl.h
	../../xio2d_impl.h
	../../xpath_impl.h
	../../xpathbuilder_impl.h
	../../xsurfaces_impl.h
	../../xsurfacesprops_impl.h
) 

add_library(io2d ${IO2D_LIB_SRC})

target_include_directories(io2d PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(io2d "-framework Cocoa")
target_link_libraries(io2d "-framework AppKit")
target_link_libraries(io2d "-framework CoreServices")
target_link_libraries(io2d "-framework CoreFoundation")
target_link_libraries(io2d "-framework ImageIO")
target_link_libraries(io2d "-framework CoreGraphics")

install(TARGETS io2d
	ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
)
install(FILES ${IO2D_LIB_HEADERS}
        DESTINATION ${CMAKE_BINARY_DIR}/include
)
