bin_PROGRAMS = 			N3888_RefImpl
N3888_RefImpl_SOURCES =		entrypoint-gtk.cpp signals.cpp context.cpp device.cpp drawing_exception.cpp font_face.cpp font_options.cpp gradient_pattern.cpp image_surface.cpp linear_pattern.cpp matrix.cpp mesh_pattern.cpp pattern.cpp radial_pattern.cpp raster_source_pattern.cpp region.cpp sample_draw.cpp scaled_font.cpp solid_color_pattern.cpp standalone_functions.cpp surface.cpp toy_font_face.cpp user_data_key.cpp
N3888_RefImpl_LDADD = 		@GTKCAIRO_LIBS@
N3888_RefImpl_CPPFLAGS =	@GTKCAIRO_CFLAGS@ # -fpermissive

#if ! [ [ test "$CXX" = "g++" ] || [ test "$CXX" = "gcc" ] ]]
#then
#	N3888_RefImpl_LDADD += -fpermissive
#fi
