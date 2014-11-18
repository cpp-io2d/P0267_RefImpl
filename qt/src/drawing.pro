TEMPLATE = lib
TARGET = drawing
INCLUDEPATH += . ../include
CONFIG += C++11 plugin

DESTDIR = $$PWD/../lib/$$PLATFORM/$$BUILD
OBJECTS_DIR = $$OUT_PWD/obj/$$PLATFORM/$$BUILD

# Input
HEADERS += ../include/drawing.h xdrawing.h xdrawinghelpers.h
SOURCES += device.cpp \
           drawing_exception.cpp \
           font_face.cpp \
           font_options.cpp \
           font_options_builder.cpp \
           image_surface.cpp \
           linear_pattern_builder.cpp \
           matrix.cpp \
           path.cpp \
           path_builder.cpp \
           pattern.cpp \
           point.cpp \
           radial_pattern_builder.cpp \
           rgba_color.cpp \
           scaled_font.cpp \
           solid_color_pattern_builder.cpp \
           surface.cpp \
           surface_pattern_builder.cpp \
           toy_font_face.cpp
