## Process this file with automake to produce Makefile.in

## libio2d

lib_LTLIBRARIES =		libio2d.la

libio2d_la_SOURCES =	rgba_color.cpp \
			cairo_renderer-graphicsmagickinit.cpp

if USE_XCB
libio2d_la_SOURCES +=	cairo_renderer_xcb.cpp
endif
if USE_XLIB
libio2d_la_SOURCES +=	cairo_renderer_xlib.cpp
endif

include_HEADERS =		io2d.h \
						xbrushes.h \
						xbrushes_impl.h \
						xcolor.h \
						xdiagnostics.h \
						xgraphicsmath.h \
						xgraphicsmath_impl.h \
						xgraphicsmathfloat.h \
						xgraphicsmathfloat_impl.h \
						xinput.h \
						xio2d.h \
						xio2d_impl.h \
						xpath.h \
						xpath_impl.h \
						xpathbuilder_impl.h \
						xsurfaces.h \
						xsurfaces_enums.h \
						xsurfaces_impl.h \
						xsurfacesprops_impl.h \
						xtext.h

include_HEADERS +=		xcairo.h \
						xcairo_helpers.h \
						xcairo_impl.h \
						xsystemheaders.h


libio2d_la_CPPFLAGS =	@CPPFLAGS@
libio2d_la_CXXFLAGS =	@CXXFLAGS@
libio2d_la_CXXFLAGS +=	@CAIRO_CFLAGS@
libio2d_la_CXXFLAGS +=	@GRAPHMAG_CFLAGS@
libio2d_la_CXXFLAGS +=	@GRAPHMAG_CPPFLAGS@
if USE_XCB
libio2d_la_CXXFLAGS +=	-DUSE_XCB
libio2d_la_CXXFLAGS +=	@xcb_CFLAGS@
endif
if USE_XLIB
libio2d_la_CXXFLAGS +=	-DUSE_XLIB
libio2d_la_CXXFLAGS +=	@X11_CFLAGS@
endif

libio2d_la_LDFLAGS =	@LIBS@
libio2d_la_LDFLAGS +=	@GRAPHMAG_LDFLAGS@
libio2d_la_LDFLAGS +=	@GRAPHMAG_LIBS@
libio2d_la_LDFLAGS +=	@CAIRO_LIBS@
if USE_XCB
libio2d_la_LDFLAGS +=	@xcb_LIBS@
endif
if USE_XLIB
libio2d_la_LDFLAGS +=	@X11_LIBS@
endif

