#pragma once
#ifndef REFIMPLWINDOW_H
#define REFIMPLWINDOW_H

#include <gtk/gtk.h>
#include "RefImplApp.h"
#include "RefImplDraw.h"

G_BEGIN_DECLS

#define REFIMPL_TYPE_WINDOW         (refimpl_window_get_type())
#define REFIMPL_WINDOW(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), REFIMPL_TYPE_WINDOW, RefImplWindow))
#define REFIMPL_IS_WINDOW(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), REFIMPL_TYPE_WINDOW))
#define REFIMPL_WINDOW_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), REFIMPL_TYPE_WINDOW, RefImplWindowClass))
#define REFIMPL_IS_WINDOW_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), REFIMPL_TYPE_WINDOW))
#define REFIMPL_WINDOW_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), REFIMPL_TYPE_WINDOW, RefImplWindowClass))

typedef struct RefImplWindow_t        RefImplWindow;
typedef struct RefImplWindowClass_t   RefImplWindowClass;
typedef struct RefImplWindowPrivate_t RefImplWindowPrivate;

struct RefImplWindow_t {
    GtkApplicationWindow parent_instance;
    RefImplWindowPrivate* priv;
};

struct RefImplWindowClass_t {
    GtkApplicationWindowClass parent_class;
};

GType refimpl_window_get_type(void);
GtkWidget* refimpl_window_new(RefImplApp* application);

gboolean refimpl_window_is_gear_menu_open(RefImplWindow* window);

// Notes:
// 'filename' is an out parameter. It must not be null.
// If a string value is returned via 'filename', it will be in "file name encoding". See: https://developer.gnome.org/glib/stable/glib-Character-Set-Conversion.html .
// The function will return true if the user has requested a screenshot, false if not.
// If the return value is true, caller is responsible for freeing *filename with g_free. Caller must also call 'refimpl_window_set_screenshot_saved()' to reset the screenshot request state to FALSE.
// If the return value is false, *filename will be set to NULL.
gboolean refimpl_window_get_save_screenshot(RefImplWindow* window, gchar** filename);

void refimpl_window_set_screenshot_saved(RefImplWindow* window);

G_END_DECLS

#endif
