## Process this file with automake to produce Makefile.in

## sample_app

bin_PROGRAMS = 		sample_app

sample_app_SOURCES =	entrypoint.cpp \
			sample_draw.cpp \
			path_examples.cpp

sample_app_CPPFLAGS =	@CPPFLAGS@
sample_app_CPPFLAGS +=	-I../P0267_RefImpl

sample_app_CXXFLAGS =	@CXXFLAGS@
sample_app_CXXFLAGS +=	-I../P0267_RefImpl
sample_app_CXXFLAGS +=	@CAIRO_CFLAGS@
sample_app_CXXFLAGS +=	@GRAPHMAG_CFLAGS@
sample_app_CXXFLAGS +=	@GRAPHMAG_CPPFLAGS@
sample_app_CXXFLAGS +=	@X11_CFLAGS@ -DUSE_XLIB

sample_app_LDFLAGS =	-static
sample_app_LDFLAGS +=	@GRAPHMAG_LDFLAGS@
sample_app_LDADD =	../P0267_RefImpl/libio2d.la
sample_app_LDADD +=	@LIBS@
sample_app_LDADD +=	@GRAPHMAG_LIBS@
sample_app_LDADD +=	@CAIRO_LIBS@
if USE_XCB
sample_app_LDADD +=	@xcb_LIBS@
endif
if USE_XLIB
sample_app_LDADD +=	@X11_LIBS@
endif

