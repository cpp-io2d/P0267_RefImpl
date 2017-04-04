## Process this file with automake to produce Makefile.in

bin_PROGRAMS = 			N3888_RefImpl

N3888_RefImpl_SOURCES =		brush.cpp \
				color_stop.cpp \
				device.cpp \
				display_surface-common.cpp \
				entrypoint.cpp \
				image_surface.cpp \
				io2d_error_category.cpp \
				mapped_surface.cpp \
				matrix_2d.cpp \
				rgba_color.cpp \
				sample_draw.cpp \
				standalone_functions.cpp \
				surface.cpp \
				test_renderer_fill.cpp \
				vector_2d.cpp

if USE_XCB
N3888_RefImpl_SOURCES +=	display_surface-xcb.cpp
endif
if USE_XLIB
N3888_RefImpl_SOURCES +=	display_surface-xlib.cpp
endif

N3888_RefImpl_LDADD = 		@GTKCAIRO_LIBS@
if USE_XCB
N3888_RefImpl_LDADD += @xcb_LIBS@
endif

N3888_RefImpl_CPPFLAGS =	@GTKCAIRO_CFLAGS@
if USE_XCB
N3888_RefImpl_CPPFLAGS += @xcb_CFLAGS@ -DUSE_XCB
endif
if USE_XLIB
N3888_RefImpl_CPPFLAGS += -DUSE_XLIB
endif
##if ! [ [ test "$CXX" = "g++" ] || [ test "$CXX" = "gcc" ] ]]
##then
##	N3888_RefImpl_LDADD += -fpermissive
##fi
N3888_RefImpl_LDADD += -lturbojpeg
