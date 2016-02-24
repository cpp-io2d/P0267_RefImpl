#include "RefImplDraw.h"
#include "RefImplWindow.h"
#include <string>
#include "io2d.h"
#include <cairo.h>
#include <iostream>
#include "xcairoenumhelpers.h"
#include "xio2dhelpers.h"
#include "sample_draw.h"
#include <glib.h>

using namespace std;
using namespace std::experimental::io2d;

namespace not_proposed {
    class timer {
	GTimer* m_gTimer;
	double m_elapsedTime;
	double m_totalTime;
	
    public:
	timer()
	    : m_gTimer(::g_timer_new()) 
	    , m_elapsedTime()
	    , m_totalTime() {
	    reset();
	}

	~timer() {
	    if (m_gTimer != nullptr) {
		::g_timer_destroy(m_gTimer);
		m_gTimer = nullptr;
	    }
	}

	timer(const timer&) = delete;
	timer& operator=(const timer&) = delete;

	void reset() {
	    m_totalTime = 0.0;
	    m_elapsedTime = 0.0;
	    ::g_timer_start(m_gTimer);
	}
	
	// Returns elapsed time since last call to Update or Reset.
	void update() {
	    const gdouble millisecondsPerSecond = 1000.0;
	    auto currentTotalTime = static_cast<double>(::g_timer_elapsed(m_gTimer, nullptr) * millisecondsPerSecond);
	    m_elapsedTime = currentTotalTime - m_totalTime;
	    m_totalTime = currentTotalTime;
	}
	
	double get_elapsed_time() {
	    return m_elapsedTime;
	}
	
	double get_total_time() {
	    return m_totalTime;
	}
    };
};

not_proposed::timer& get_timer() {
    static not_proposed::timer t;
    return t;
}

gboolean drawing_area_draw(GtkWidget* widget, cairo_t* cr, gpointer data) {
    double x, y, width, height;
    double elapsedTime = 0.0;
    auto& timer = get_timer();
    timer.update();
    if (refimpl_window_is_gear_menu_open(REFIMPL_WINDOW(data)) == FALSE) {
	elapsedTime = timer.get_elapsed_time();
    }

    cairo_clip_extents(cr, &x, &y, &width, &height);
    width = width - x;
    height = height - y;
    auto gtkSurface = make_surface({ cairo_surface_create_similar_image(cairo_get_target(cr), CAIRO_FORMAT_ARGB32, width, height), nullptr });//{cairo_surface_reference(cairo_get_target(cr)), nullptr});
    sample_draw sampleDraw;
    sampleDraw(gtkSurface, elapsedTime);
    cairo_set_source_surface(cr, gtkSurface.native_handle().csfce, x, y);
    cairo_paint(cr);

    gchar* saveFileName = NULL;
    if (refimpl_window_get_save_screenshot(REFIMPL_WINDOW(data), &saveFileName) != FALSE) {
	cairo_surface_flush(gtkSurface.native_handle().csfce);
	gsize bytesRead;
	gsize bytesWritten;
	GError* error = NULL;
	gchar* utf8SaveFileName = g_filename_to_utf8(saveFileName, -1, &bytesRead, &bytesWritten, &error);
	if (utf8SaveFileName != nullptr) {
	    cairo_surface_write_to_png(gtkSurface.native_handle().csfce, utf8SaveFileName);
	    g_free(utf8SaveFileName);
	    utf8SaveFileName = nullptr;
	}
	else {
	    GtkWidget* dialog =
		gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT,
				       GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
				       "Error converting filename: %s", error->message);
	    gtk_dialog_run(GTK_DIALOG(dialog));
	    gtk_widget_destroy(dialog);
	    g_error_free(error);
	    error = NULL;
	}
	refimpl_window_set_screenshot_saved(REFIMPL_WINDOW(data));
	g_free(saveFileName);
	saveFileName = NULL;
    }
    return TRUE;
}
