#include "signals.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include "N3888_RefImpl.ui.h"
#include <assert.h>
#include <stdexcept>

GtkBuilder* g_builder;
GtkWidget* g_main_window;
GtkWidget* g_drawingarea;
GtkWidget* g_about_dialog;
GtkWidget* g_screenshotcapture_filechooserdialog;

gboolean redraw_callback(gpointer user_data) {
    gtk_widget_queue_draw(GTK_WIDGET(g_drawingarea));
    return G_SOURCE_CONTINUE;
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    g_builder = gtk_builder_new();

    auto result = gtk_builder_add_from_string(g_builder, g_n3888_ui_as_string, -1, nullptr);
    if (result == 0) {
      throw ::std::runtime_error("Failed call to gtk_builder_add_from_string.");
    }

    g_main_window = GTK_WIDGET(gtk_builder_get_object(g_builder, "window"));
    assert(g_main_window != nullptr);
    g_drawingarea = GTK_WIDGET(gtk_builder_get_object(g_builder, "drawingarea"));
    assert(g_drawingarea != nullptr);
    gtk_builder_connect_signals(g_builder, NULL);
    g_timeout_add(1000/50, &redraw_callback, nullptr);
    gtk_widget_show(g_main_window);
    gtk_main();
    
    g_object_unref(G_OBJECT(g_builder));

    return 0;
}
