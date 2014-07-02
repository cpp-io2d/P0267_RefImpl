bin_PROGRAMS = 			N3888_RefImpl
N3888_RefImpl_SOURCES =		entrypoint-gtk.cpp signals.cpp device.cpp drawing_exception.cpp font_face.cpp font_options_builder.cpp font_options.cpp image_surface.cpp linear_pattern_builder.cpp matrix.cpp mesh_pattern_builder.cpp path_builder.cpp path.cpp pattern.cpp point.cpp radial_pattern_builder.cpp raster_source_pattern_builder.cpp rgba_color.cpp sample_draw.cpp scaled_font.cpp solid_color_pattern_builder.cpp standalone_functions.cpp surface.cpp toy_font_face.cpp
N3888_RefImpl_LDADD = 		@GTKCAIRO_LIBS@
N3888_RefImpl_CPPFLAGS =	@GTKCAIRO_CFLAGS@ # -fpermissive

#if ! [ [ test "$CXX" = "g++" ] || [ test "$CXX" = "gcc" ] ]]
#then
#	N3888_RefImpl_LDADD += -fpermissive
#fi
