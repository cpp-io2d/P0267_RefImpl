cmake_minimum_required(VERSION 2.8.12)

project(cairo C)

include(CheckIncludeFiles)
include(CheckTypeSize)

check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(sys/int_types.h HAVE_SYS_INT_TYPES_H)
check_include_files(pthread.h CAIRO_HAS_PTHREAD)
check_include_files(xcb/xcb.h CAIRO_HAS_XCB_SURFACE)

set(CAIRO_SRC
    src/cairo-analysis-surface.c                src/cairo-arc.c
    src/cairo-array.c                           src/cairo-atomic.c
    src/cairo-base64-stream.c                   src/cairo-base85-stream.c
    src/cairo-bentley-ottmann.c                 src/cairo-bentley-ottmann-rectangular.c
    src/cairo-bentley-ottmann-rectilinear.c     src/cairo-botor-scan-converter.c
    src/cairo-boxes.c                           src/cairo-boxes-intersect.c
    src/cairo.c                                 src/cairo-cache.c
    src/cairo-clip.c                            src/cairo-clip-boxes.c
    src/cairo-clip-polygon.c                    src/cairo-clip-region.c
    src/cairo-clip-surface.c                    src/cairo-color.c
    src/cairo-composite-rectangles.c            src/cairo-compositor.c
    src/cairo-contour.c                         src/cairo-damage.c
    src/cairo-debug.c                           src/cairo-default-context.c
    src/cairo-device.c                          src/cairo-error.c
    src/cairo-fallback-compositor.c             src/cairo-fixed.c
    src/cairo-font-face.c                       src/cairo-font-face-twin.c
    src/cairo-font-face-twin-data.c             src/cairo-font-options.c
    src/cairo-freelist.c                        src/cairo-freed-pool.c
    src/cairo-gstate.c                          src/cairo-hash.c
    src/cairo-hull.c                            src/cairo-image-compositor.c
    src/cairo-image-info.c                      src/cairo-image-source.c
    src/cairo-image-surface.c                   src/cairo-lzw.c
    src/cairo-matrix.c                          src/cairo-mask-compositor.c
    src/cairo-mesh-pattern-rasterizer.c         src/cairo-mempool.c
    src/cairo-misc.c                            src/cairo-mono-scan-converter.c
    src/cairo-mutex.c                           src/cairo-no-compositor.c
    src/cairo-observer.c                        src/cairo-output-stream.c
    src/cairo-paginated-surface.c               src/cairo-path-bounds.c
    src/cairo-path.c                            src/cairo-path-fill.c
    src/cairo-path-fixed.c                      src/cairo-path-in-fill.c
    src/cairo-path-stroke.c                     src/cairo-path-stroke-boxes.c
    src/cairo-path-stroke-polygon.c             src/cairo-path-stroke-traps.c
    src/cairo-path-stroke-tristrip.c            src/cairo-pattern.c
    src/cairo-pen.c                             src/cairo-polygon.c
    src/cairo-polygon-intersect.c               src/cairo-polygon-reduce.c
    src/cairo-raster-source-pattern.c           src/cairo-recording-surface.c
    src/cairo-rectangle.c                       src/cairo-rectangular-scan-converter.c
    src/cairo-region.c                          src/cairo-rtree.c
    src/cairo-scaled-font.c                     src/cairo-shape-mask-compositor.c
    src/cairo-slope.c                           src/cairo-spans.c
    src/cairo-spans-compositor.c                src/cairo-spline.c
    src/cairo-stroke-dash.c                     src/cairo-stroke-style.c
    src/cairo-surface.c                         src/cairo-surface-clipper.c
    src/cairo-surface-fallback.c                src/cairo-surface-observer.c
    src/cairo-surface-offset.c                  src/cairo-surface-snapshot.c
    src/cairo-surface-subsurface.c              src/cairo-surface-wrapper.c
    src/cairo-time.c                            src/cairo-tor-scan-converter.c
    src/cairo-tor22-scan-converter.c            src/cairo-clip-tor-scan-converter.c
    src/cairo-toy-font-face.c                   src/cairo-traps.c
    src/cairo-tristrip.c                        src/cairo-traps-compositor.c
    src/cairo-unicode.c                         src/cairo-user-font.c
    src/cairo-version.c                         src/cairo-wideint.c

    src/cairo-script-surface.c

    src/cairo-cff-subset.c                      src/cairo-scaled-font-subsets.c
    src/cairo-truetype-subset.c                 src/cairo-type1-fallback.c
    src/cairo-type1-glyph-names.c               src/cairo-type1-subset.c
)

if (WIN32)
    set(CAIRO_HAS_WIN32_SURFACE 1)
    set(CAIRO_HAS_WIN32_FONT 1)

    set(CAIRO_SRC_WIN32
        src/win32/cairo-win32-debug.c               src/win32/cairo-win32-device.c
        src/win32/cairo-win32-gdi-compositor.c      src/win32/cairo-win32-system.c
        src/win32/cairo-win32-surface.c             src/win32/cairo-win32-display-surface.c
        src/win32/cairo-win32-printing-surface.c    src/win32/cairo-win32-font.c
    )
    list(APPEND CAIRO_SRC ${CAIRO_SRC_WIN32})    
    set(CAIRO_EXTRA_LIBRARIES msimg32)
endif()

if (CAIRO_HAS_XCB_SURFACE)
    set(HAVE_INTEL_ATOMIC_PRIMITIVES 1)
    set(CAIRO_SRC_XCB
        src/cairo-xcb-connection.c              src/cairo-xcb-connection-core.c
        src/cairo-xcb-connection-render.c       src/cairo-xcb-connection-shm.c
        src/cairo-xcb-screen.c                  src/cairo-xcb-shm.c
        src/cairo-xcb-surface.c                 src/cairo-xcb-surface-core.c
        src/cairo-xcb-surface-render.c
    )
    list(APPEND CAIRO_SRC ${CAIRO_SRC_XCB})
    set(CAIRO_EXTRA_LIBRARIES -lxcb -lxcb-render -lpthread)
endif()

add_library(cairo ${CAIRO_SRC})
target_link_libraries(cairo
    ${CAIRO_EXTRA_LIBRARIES}
    ${PIXMAN_LIBRARY}
)

target_compile_definitions(cairo PRIVATE HAVE_CONFIG_H)
target_compile_definitions(cairo INTERFACE CAIRO_HAS_XCB_SURFACE)

target_include_directories(cairo PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PIXMAN_INCLUDE_DIR}
)

target_include_directories(cairo INTERFACE
    ${CMAKE_CURRENT_BINARY_DIR}
)

check_type_size("uint64_t" SIZEOF_UINT64_T)
if(SIZEOF_UINT64_T)
    set(HAVE_UINT64_T 1)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/config.h)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cairo-features.h.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/cairo-features.h)
