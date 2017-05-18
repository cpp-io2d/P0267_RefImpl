## Process this file with automake to produce Makefile.in

## P0267_RefImpl

P0267_RefImpl_SOURCES =	entrypoint.cpp \
						sample_draw.cpp
P0267_RefImpl_CPPFLAGS =	@CPPFLAGS@
P0267_RefImpl_CXXFLAGS =	@CXXFLAGS@
P0267_RefImpl_LDFLAGS =	-static
P0267_RefImpl_LDADD	=	libio2d.la
P0267_RefImpl_LDADD +=	@LIBS@
P0267_RefImpl_LDADD +=	@CAIRO_LIBS@
if USE_XCB
P0267_RefImpl_LDADD +=	@xcb_LIBS@
endif
