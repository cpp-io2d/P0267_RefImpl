## Process this file with automake to produce Makefile.in

## rocks_in_space

bin_PROGRAMS = 		rocks_in_space

rocks_in_space_SOURCES =	Asteroid.cpp \
				Game.cpp \
				Input.cpp \
				Maths.cpp \
				Physics.cpp \
				Ship.cpp \
				XlibWin.cpp

rocks_in_space_CPPFLAGS =	@CPPFLAGS@
rocks_in_space_CPPFLAGS +=	-I../P0267_RefImpl
rocks_in_space_CPPFLAGS +=	@CAIRO_CFLAGS@
rocks_in_space_CXXFLAGS =	@CXXFLAGS@
rocks_in_space_CXXFLAGS +=	@X11_CFLAGS@ -DUSE_XLIB
rocks_in_space_LDFLAGS =	-static
rocks_in_space_LDADD =	../P0267_RefImpl/libio2d.la
rocks_in_space_LDADD +=	@LIBS@
rocks_in_space_LDADD +=	@CAIRO_LIBS@
if USE_XCB
rocks_in_space_LDADD +=	@xcb_LIBS@
endif
if USE_XLIB
rocks_in_space_LDADD +=	@X11_LIBS@
endif

