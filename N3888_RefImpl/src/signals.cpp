#include "signals.h"
//#include <memory>
#include <string>
#include "drawing.h"
#include <cairo.h>
#include <iostream>
#include "xcairoenumhelpers.h"
#include "xdrawinghelpers.h"

using namespace std;
using namespace std::experimental::drawing;

not_proposed::timer& get_timer() {
    static not_proposed::timer t;
    return t;
}

static bool lg_writeToPNG = false;
static string lg_filename;

G_MODULE_EXPORT void on_window_destroy(GtkWidget* object, gpointer user_data) {
    gtk_main_quit();
}

G_MODULE_EXPORT gboolean on_drawingarea_draw(GtkWidget* object, cairo_t* cr, gpointer user_data) {
    auto ctxt = context(cairo_reference(cr));
    sample_draw sampleDraw;
    auto& timer = get_timer();
    timer.update();
    sampleDraw(ctxt, timer.get_elapsed_time());
    if (lg_writeToPNG) {
	// Check to see if the context is in a bad way.
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_status(cr)));
	// Get the surface so we can flush it; reference it while we're doing stuff with it.
	auto sfce = cairo_surface_reference(cairo_get_target(cr));
	try {
	    cairo_surface_flush(sfce);
	    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_write_to_png(sfce, lg_filename.c_str())));
	}
	catch(...) {
	    cairo_surface_destroy(sfce);
	    throw;
	}
	lg_writeToPNG = false;
	lg_filename = "";
    }
    return TRUE;
}

G_MODULE_EXPORT void on_about_ok_button_clicked(GtkButton* button, gpointer user_data) {
    gtk_dialog_response(GTK_DIALOG(g_about_dialog), GTK_RESPONSE_OK);
}
    
G_MODULE_EXPORT void on_help_about_menuitem_activate(GtkMenuItem* menuitem, gpointer user_data) {
    g_about_dialog = GTK_WIDGET(gtk_builder_get_object(g_builder, "about_dialog"));
    gtk_builder_connect_signals(g_builder, NULL);
    
    gtk_widget_show_all(GTK_WIDGET(g_about_dialog));
    auto response = gtk_dialog_run(GTK_DIALOG(g_about_dialog));
    switch (response) {
    case GTK_RESPONSE_OK:
	gtk_widget_hide(GTK_WIDGET(g_about_dialog));
	break;
    case GTK_RESPONSE_DELETE_EVENT:
	g_about_dialog = nullptr;
	break;
    }
}

G_MODULE_EXPORT void on_edit_screencapture_menuitem_activate(GtkMenuItem* menuitem, gpointer user_data) {
    GtkWidget* dialog = GTK_WIDGET(
	gtk_file_chooser_dialog_new("Screenshot Capture", GTK_WINDOW(g_main_window),
				    GTK_FILE_CHOOSER_ACTION_SAVE,
				    "_Cancel", GTK_RESPONSE_CANCEL,
				    "_Save", GTK_RESPONSE_ACCEPT, nullptr)
	);

    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter, "*.png");
    gtk_file_filter_add_mime_type(filter, "image/png");
    gtk_file_filter_set_name(filter, "*.png");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
	char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	lg_filename = std::string(filename);
	lg_writeToPNG = true;
	g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

G_MODULE_EXPORT void on_file_exit_menuitem_activate(GtkMenuItem* menuitem, gpointer user_data) {
    gtk_window_close(GTK_WINDOW(g_main_window));
}
