#pragma once
#ifndef REFIMPLDRAW_H
#define REFIMPLDRAW_H

#include <cairo.h>
#include <gtk/gtk.h>
#include <glib.h>
G_BEGIN_DECLS

gboolean drawing_area_draw(GtkWidget* widget, cairo_t* cr, gpointer data);

G_END_DECLS
#endif
