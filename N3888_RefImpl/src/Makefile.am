## Process this file with automake to produce Makefile.in

##resource_Files = @DOLLAR_SIGN@(shell glib-compile-resources --sourcedir=$(srcdir) --generate-dependencies $(srcdir)/refimpl.gresource.xml)
##refimpl-resources.c: refimpl.gresource.xml $(resource_Files)
##	glib-compile-resources --target=$@ --sourcedir=$(srcdir) --generate-source --c-name refimpl $(srcdir)/refimpl.gresource.xml
##refimpl-resources.h: refimpl.gresource.xml $(resource_Files)
##	glib-compile-resources --target=$@ --sourcedir=$(srcdir) --generate-header --c-name refimpl $(srcdir)/refimpl.gresource.xml

##BUILT_SOURCES =			refimpl-resources.c \
##				refimpl-resources.h \
##				$(NULL)

bin_PROGRAMS = 			N3888_RefImpl

N3888_RefImpl_SOURCES =		brush.cpp \
				color_stop.cpp \
				device.cpp \
				display_surface-common.cpp \
				entrypoint.cpp \
				font_extents.cpp \
				font_options.cpp \
				font_resource.cpp \
				font_resource_factory.cpp \
				glyph_run.cpp \
				image_surface.cpp \
				io2d_error_category.cpp \
				linear_brush_factory.cpp \
				mapped_surface.cpp \
				matrix_2d.cpp \
				path.cpp \
				path_data.cpp \
				radial_brush_factory.cpp \
				rectangle.cpp \
				rgba_color.cpp \
				sample_draw.cpp \
				solid_color_brush_factory.cpp \
				standalone_functions.cpp \
				surface.cpp \
				surface_brush_factory.cpp \
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
