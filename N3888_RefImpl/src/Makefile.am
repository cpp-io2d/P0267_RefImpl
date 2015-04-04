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

N3888_RefImpl_SOURCES =	brush.cpp \
				device.cpp \
				display_surface-common.cpp \
				display_surface-xlib.cpp \
				entrypoint.cpp \
				font_extents.cpp \
				font_face.cpp \
				font_options.cpp \
				image_surface.cpp \
				io2d_error_category.cpp \
				linear_brush_factory.cpp \
				matrix_2d.cpp \
				mesh_brush_factory.cpp \
				path.cpp \
				path_data.cpp \
				path_factory.cpp \
				radial_brush_factory.cpp \
				rectangle.cpp \
				rgba_color.cpp \
				sample_draw.cpp \
				simple_font_face.cpp \
				solid_color_brush_factory.cpp \
				standalone_functions.cpp \
				surface.cpp \
				surface_brush_factory.cpp \
				text_extents.cpp \
				vector_2d.cpp
##				refimpl-resources.c \
##				RefImplApp.c \
##				RefImplWindow.c \
##				RefImplDraw.cpp
##				signals.cpp \

N3888_RefImpl_LDADD = 		@GTKCAIRO_LIBS@

N3888_RefImpl_CPPFLAGS =	@GTKCAIRO_CFLAGS@ ## -fpermissive

##if ! [ [ test "$CXX" = "g++" ] || [ test "$CXX" = "gcc" ] ]]
##then
##	N3888_RefImpl_LDADD += -fpermissive
##fi
