#pragma once
#if !defined(_SIGNALS_H)
#define _SIGNALS_H

#include <cairo.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "sample_draw.h"

extern GtkBuilder* g_builder;
extern GtkWidget* g_main_window;
extern GtkWidget* g_about_dialog;
extern GtkWidget* g_screenshotcapture_filechooserdialog;

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



#if defined(__cplusplus)
extern "C" {
#endif

    G_MODULE_EXPORT void on_window_destroy(GtkWidget* object, gpointer user_data);
    
    G_MODULE_EXPORT gboolean on_drawingarea_draw(GtkWidget* object, cairo_t* ctxt, gpointer user_data);
    
    G_MODULE_EXPORT void on_about_ok_button_clicked(GtkButton* button, gpointer user_data);
    
    G_MODULE_EXPORT void on_help_about_menuitem_activate(GtkMenuItem* menuitem, gpointer user_data);

    G_MODULE_EXPORT void on_edit_screencapture_menuitem_activate(GtkMenuItem* menuitem, gpointer user_data);

    G_MODULE_EXPORT void on_file_exit_menuitem_activate(GtkMenuItem* menuitem, gpointer user_data);
#if defined(__cplusplus)
}
#endif

#endif
