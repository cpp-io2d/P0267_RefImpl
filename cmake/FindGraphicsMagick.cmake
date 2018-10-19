#
# FindGraphicsMagick.cmake
# 
# When done, if GraphicsMagick is found, the following will be defined:
#
#  Library Targets:
#   - GraphicsMagick::GraphicsMagick
#
#  Global Variables:
#   - GRAPHICSMAGICK_FOUND
#

# Use pkg-config, if available, to help find the library
find_package(PkgConfig)
pkg_check_modules(PC_GRAPHICSMAGICK GraphicsMagick)

# Find the header(s)
find_path(GRAPHICSMAGICK_INCLUDE_DIRS
    NAMES magick/api.h
    HINTS ${PC_GRAPHICSMAGICK_INCLUDE_DIRS}
)

# Find the pre-compiled binary.  For Windows + MSVC, this will be its .lib file.
find_library(GRAPHICSMAGICK_LIBRARIES
    GraphicsMagick
    HINTS ${PC_GRAPHICSMAGICK_LIBRARY_DIRS}
)

# Search for base path of installation
if (GRAPHICSMAGICK_INCLUDE_DIRS)
    set(_TMP_PATH ${GRAPHICSMAGICK_INCLUDE_DIRS})
    while(TRUE)
        get_filename_component(_TMP_PATH_PART ${_TMP_PATH} NAME)
        string(TOLOWER ${_TMP_PATH_PART} _TMP_PATH_PART)
        if (${_TMP_PATH_PART} STREQUAL "graphicsmagick" OR ${_TMP_PATH_PART} STREQUAL "include")
            get_filename_component(_TMP_PATH ${_TMP_PATH} DIRECTORY)
            continue()
        endif()
        if (NOT (${_TMP_PATH} STREQUAL ""))
            set(GRAPHICSMAGICK_PATH ${_TMP_PATH})
        endif()
        break()
    endwhile()
endif()

# Look for a pre-compiled .dll file
find_path(GRAPHICSMAGICK_DLL
    NAMES graphicsmagick.dll
    HINTS ${GRAPHICSMAGICK_PATH}
    PATH_SUFFIXES bin
)

# Perform CMake Find-module stuff
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GraphicsMagick
    REQUIRED_VARS GRAPHICSMAGICK_INCLUDE_DIRS GRAPHICSMAGICK_LIBRARIES
)

# Create a library target
if (GRAPHICSMAGICK_FOUND AND NOT TARGET GraphicsMagick::GraphicsMagick)
    if (GRAPHICSMAGICK_DLL)
        # Not using 'SHARED' when Cairo is available through a .dll can
        # cause build issues with MSVC, at least when trying to link against
        # a vcpkg-provided copy of "cairod".
        add_library(GraphicsMagick::GraphicsMagick SHARED IMPORTED)
    else()
        add_library(GraphicsMagick::GraphicsMagick UNKNOWN IMPORTED)
    endif()

    set_target_properties(GraphicsMagick::GraphicsMagick PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        INTERFACE_INCLUDE_DIRECTORIES ${GRAPHICSMAGICK_INCLUDE_DIRS}
    )

    if (GRAPHICSMAGICK_DLL)
        # When using a .dll, the location of *both* the .dll file, and its
        # .lib, needs to be specified to CMake.  The path to the .dll goes
        # into IMPORTED_LOCATION(_*), whereas the path to the .lib goes
        # into IMPORTED_IMPLIB(_*).
        set_target_properties(GraphicsMagick::GraphicsMagick PROPERTIES
            IMPORTED_LOCATION ${GRAPHICSMAGICK_DLL}
            IMPORTED_IMPLIB ${GRAPHICSMAGICK_LIBRARIES}
        )
    else()
        set_target_properties(GraphicsMagick::GraphicsMagick PROPERTIES
            IMPORTED_LOCATION ${GRAPHICSMAGICK_LIBRARIES}
        )
    endif()
endif()
