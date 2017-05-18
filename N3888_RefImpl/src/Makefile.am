## Process this file with automake to produce Makefile.in

## libio2d

lib_LTLIBRARIES =		libio2d.la

libio2d_la_SOURCES =		brush.cpp \
				color_stop.cpp \
				device.cpp \
				display_surface-common.cpp \
				image_surface.cpp \
				io2d_error_category.cpp \
				mapped_surface.cpp \
				matrix_2d.cpp \
				rgba_color.cpp \
				standalone_functions.cpp \
				surface.cpp \
				vector_2d.cpp \
				throw_helpers.h \
				xcairoenumhelpers.h \
				xdiagnostics.h

if USE_XCB
libio2d_la_SOURCES +=	display_surface-xcb.cpp
endif
if USE_XLIB
libio2d_la_SOURCES +=	display_surface-xlib.cpp
endif

include_HEADERS =	io2d.h xio2d.h

libio2d_la_CPPFLAGS =	@CPPFLAGS@
libio2d_la_CXXFLAGS =	@CXXFLAGS@
libio2d_la_CXXFLAGS +=	@CAIRO_CFLAGS@
if USE_XCB
libio2d_la_CXXFLAGS +=	-DUSE_XCB
libio2d_la_CXXFLAGS +=	@xcb_CFLAGS@
endif
if USE_XLIB
libio2d_la_CXXFLAGS +=	-DUSE_XLIB
libio2d_la_CXXFLAGS +=	@X11_CFLAGS@
endif

libio2d_la_LDFLAGS =	@LIBS@
libio2d_la_LDFLAGS +=	-lturbojpeg
libio2d_la_LDFLAGS +=	@CAIRO_LIBS@
if USE_XCB
libio2d_la_LDFLAGS +=	@xcb_LIBS@
endif
if USE_XLIB
libio2d_la_LDFLAGS +=	@X11_LIBS@
endif

