#include "RefImplWindow.h"
#include <assert.h>
#include <glib/gprintf.h>

struct RefImplWindowPrivate_t {
    GtkMenuButton* gearMenuButton;
    GMenuModel* gearAppMenu;
    GtkDrawingArea* drawingArea;
    gulong drawingArea_draw;
    guint redrawTimeoutEventSourceId;
    gboolean gearMenuIsOpen;
    gchar* saveFileName;
    gboolean saveScreenshot;
};

static void close_window_action(GSimpleAction* action, GVariant* parameter, gpointer user_data);
static void screen_capture_action(GSimpleAction* action, GVariant* parameter, gpointer user_data);
static void gear_menu_action(GSimpleAction* action, GVariant* parameter, gpointer user_data);
gboolean refimpl_window_redraw_g_source_func(gpointer user_data);
static void refimpl_window_dispose(GObject* obj);
static void refimpl_window_class_init(RefImplWindowClass* windowClass);
static void refimpl_window_init(RefImplWindow* window);

G_DEFINE_TYPE_WITH_PRIVATE(RefImplWindow, refimpl_window, GTK_TYPE_APPLICATION_WINDOW);

static void close_window_action(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    RefImplWindow* window = REFIMPL_WINDOW(user_data);
    gtk_widget_destroy(GTK_WIDGET(window));
}

static void screen_capture_action(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    RefImplWindow* window = REFIMPL_WINDOW(user_data);
    GtkWidget* dialog = GTK_WIDGET(
	gtk_file_chooser_dialog_new("Screenshot Capture", GTK_WINDOW(window),
				    GTK_FILE_CHOOSER_ACTION_SAVE,
				    "_Cancel", GTK_RESPONSE_CANCEL,
				    "_Save", GTK_RESPONSE_ACCEPT, NULL)
	);

    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter, "*.png");
    gtk_file_filter_add_mime_type(filter, "image/png");
    gtk_file_filter_set_name(filter, "*.png");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
    if (window->priv->saveFileName != NULL) {
	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(dialog), window->priv->saveFileName);
    }

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
	if (window->priv->saveFileName != NULL) {
	    g_free(window->priv->saveFileName);
	    window->priv->saveFileName = NULL;
	}
	window->priv->saveFileName = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	window->priv->saveScreenshot = TRUE;
    }

    gtk_widget_destroy(dialog);
}

static void gear_menu_action(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    GVariant* state = NULL;
    assert(action != NULL);
    state = g_action_get_state(G_ACTION(action));
    assert(state != NULL);
    gboolean currentState = g_variant_get_boolean(state);
//    g_printf("Gear menu state was %s and is now %s.\n", currentState ? "true" : "false", currentState ? "false" : "true");
    g_action_change_state(G_ACTION(action), g_variant_new_boolean(!currentState));
    REFIMPL_WINDOW(user_data)->priv->gearMenuIsOpen = !currentState;
    g_variant_unref(state);
}

static GActionEntry win_action_entries[] = {
    { "close", close_window_action, NULL, NULL, NULL },
    { "screen-capture", screen_capture_action, NULL, NULL, NULL },
    { "gear-menu", gear_menu_action, NULL, "false", NULL }
};

gboolean refimpl_window_redraw_g_source_func(gpointer user_data) {
    gtk_widget_queue_draw(GTK_WIDGET(REFIMPL_WINDOW(user_data)->priv->drawingArea));
    return G_SOURCE_CONTINUE;
}

static void refimpl_window_dispose(GObject* obj) {
    RefImplWindow* window = REFIMPL_WINDOW(obj);

    if (window->priv->saveFileName != NULL) {
	g_free(window->priv->saveFileName);
	window->priv->saveFileName = NULL;
    }
    g_signal_handler_disconnect(window->priv->drawingArea, window->priv->drawingArea_draw);
    assert(window->priv->redrawTimeoutEventSourceId != 0);
    g_source_remove(window->priv->redrawTimeoutEventSourceId);
    G_OBJECT_CLASS(refimpl_window_parent_class)->dispose(obj);
}

static void refimpl_window_class_init(RefImplWindowClass* windowClass) {
    GObjectClass* objectClass = G_OBJECT_CLASS(windowClass);
    GtkWidgetClass* widgetClass = GTK_WIDGET_CLASS(windowClass);

    objectClass->dispose = refimpl_window_dispose;

    gtk_widget_class_set_template_from_resource(widgetClass, "/com/bobtacoindustries/N3888_RefImpl/refimpl_window.ui");
    gtk_widget_class_bind_template_child_private(widgetClass, RefImplWindow, gearMenuButton);
    gtk_widget_class_bind_template_child_private(widgetClass, RefImplWindow, drawingArea);
}

static void refimpl_window_init(RefImplWindow* window) {
    gtk_widget_init_template(GTK_WIDGET(window));
    window->priv = refimpl_window_get_instance_private(window);
    assert(window->priv != NULL);
    assert(window->priv->drawingArea != NULL);
    window->priv->gearMenuIsOpen = FALSE;
    window->priv->saveFileName = NULL;
    window->priv->saveScreenshot = FALSE;
    window->priv->drawingArea_draw = g_signal_connect(window->priv->drawingArea, "draw", G_CALLBACK(drawing_area_draw), window);
    assert(window->priv->drawingArea_draw != 0);
    window->priv->redrawTimeoutEventSourceId = g_timeout_add(1000/50, &refimpl_window_redraw_g_source_func, window);
    assert(window->priv->redrawTimeoutEventSourceId != 0);

    g_action_map_add_action_entries(G_ACTION_MAP(window), win_action_entries, G_N_ELEMENTS(win_action_entries), window);

    if (!refimpl_app_has_app_menu(REFIMPL_APP(g_application_get_default()))) {
	GtkBuilder* builder;
	GError* error = NULL;
	builder = gtk_builder_new();
	gtk_builder_add_from_resource(builder, "/com/bobtacoindustries/N3888_RefImpl/refimpl_menu.ui", &error);

	if (error != NULL) {
	    g_critical("Unable to load app menu: %s\n", error->message);
	    g_error_free(error);
	    error = NULL;
	}
	else {
	    window->priv->gearAppMenu = G_MENU_MODEL(gtk_builder_get_object(builder, "app_menu"));
	    gtk_menu_button_set_menu_model(window->priv->gearMenuButton, window->priv->gearAppMenu);
	}
	g_object_unref(builder);
	builder = NULL;
    }
}

GtkWidget* refimpl_window_new(RefImplApp* application) {
    RefImplWindow* window;

    window = g_object_new(REFIMPL_TYPE_WINDOW, "application", application, NULL);
    window->priv = refimpl_window_get_instance_private(window);

    return GTK_WIDGET(window);
}

gboolean refimpl_window_is_gear_menu_open(RefImplWindow* window) {
    return window->priv->gearMenuIsOpen;
}

gboolean refimpl_window_get_save_screenshot(RefImplWindow* window, gchar** filename) {
    assert(filename != NULL);
    if (window->priv->saveScreenshot == FALSE) {
	*filename = NULL;
	return FALSE;
    }
    *filename = g_strdup(window->priv->saveFileName);
    return TRUE;
}

void refimpl_window_set_screenshot_saved(RefImplWindow* window) {
    window->priv->saveScreenshot = FALSE;
}
