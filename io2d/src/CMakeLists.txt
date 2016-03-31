cmake_minimum_required(VERSION 2.8.12)

project(io2d CXX)

add_subdirectory(3rd-party)
set(CAIRO_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/cairo/src 
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/cairo/
    ${CMAKE_CURRENT_BINARY_DIR}/3rd-party/cairo)
set(CAIRO_LIBRARY cairo)

set(IO2D_SRC
    brush.cpp
    device.cpp
    display_surface-common.cpp
    font_extents.cpp
    font_resource.cpp 
    font_resource_factory.cpp 
    font_options.cpp
    glyph_run.cpp 
    image_surface.cpp
    io2d_error_category.cpp
    linear_brush_factory.cpp
    mapped_surface.cpp
    matrix_2d.cpp
    mesh_brush_factory.cpp
    path.cpp
    path_data.cpp
    path_data_item.cpp
    path_factory.cpp
    radial_brush_factory.cpp
    rectangle.cpp
    rgba_color.cpp
    solid_color_brush_factory.cpp
    standalone_functions.cpp
    surface.cpp
    surface_brush_factory.cpp
    text_extents.cpp
    vector_2d.cpp
)

if (WIN32)
    list(APPEND IO2D_SRC display_surface-win32.cpp)
else()
    list(APPEND IO2D_SRC display_surface-xlib.cpp)
endif()

add_library(io2d ${IO2D_SRC})
target_link_libraries(io2d ${CAIRO_LIBRARY})
target_include_directories(io2d PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CAIRO_INCLUDE_DIR}
)

if (WIN32)
    target_compile_definitions(io2d PRIVATE
        _WIN32_WINNT=0x0600 CAIRO_WIN32_STATIC_BUILD UNICODE)
endif()
