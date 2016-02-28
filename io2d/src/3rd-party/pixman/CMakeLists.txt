cmake_minimum_required(VERSION 2.8.12)

project(pixman C)
               
set(PIXMAN_SRC
    pixman/pixman.c                     pixman/pixman-access.c
    pixman/pixman-access-accessors.c    pixman/pixman-bits-image.c
    pixman/pixman-combine32.c           pixman/pixman-combine-float.c
    pixman/pixman-conical-gradient.c    pixman/pixman-filter.c
    pixman/pixman-x86.c                 pixman/pixman-mips.c
    pixman/pixman-arm.c                 pixman/pixman-ppc.c
    pixman/pixman-edge.c                pixman/pixman-edge-accessors.c
    pixman/pixman-fast-path.c           pixman/pixman-glyph.c
    pixman/pixman-general.c             pixman/pixman-gradient-walker.c
    pixman/pixman-image.c               pixman/pixman-implementation.c
    pixman/pixman-linear-gradient.c     pixman/pixman-matrix.c
    pixman/pixman-noop.c                pixman/pixman-radial-gradient.c
    pixman/pixman-region16.c            pixman/pixman-region32.c
    pixman/pixman-solid-fill.c          pixman/pixman-timer.c
    pixman/pixman-trap.c                pixman/pixman-utils.c
)

add_library(pixman ${PIXMAN_SRC})

target_include_directories(pixman PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/pixman
    ${CMAKE_CURRENT_BINARY_DIR}
)

option(USE_SSE2 "use SSE2 compiler intrinsics" ON)
if (USE_SSE2 AND CMAKE_COMPILER_IS_GNU_C)
    list(APPEND PIXMAN_SRC pixman/pixman-sse2.c)
    target_compile_definitions(pixman PRIVATE USE_SSE2)
endif()

include(CheckIncludeFiles)
target_compile_definitions(pixman PRIVATE HAVE_CONFIG_H)
check_include_files(pthread.h HAVE_PTHREAD_H)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set(PIXMAN_VERSION_MAJOR 0)
set(PIXMAN_VERSION_MINOR 33)
set(PIXMAN_VERSION_MICRO 1)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pixman/pixman-version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/pixman-version.h)
