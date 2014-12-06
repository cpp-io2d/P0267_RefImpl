#include "RefImplApp.h"
#include "RefImplWindow.h"

struct RefImplAppPrivate_t {
    guint unused;
};

G_DEFINE_TYPE_WITH_PRIVATE(RefImplApp, refimpl_app, GTK_TYPE_APPLICATION);

GtkWindow* refimpl_app_peek_first_window(RefImplApp* app) {
    GList* windowListItem;

    g_return_val_if_fail(REFIMPL_IS_APP(app), NULL);

    for (windowListItem = gtk_application_get_windows(GTK_APPLICATION(app)); windowListItem != NULL; windowListItem = g_list_next(windowListItem)) {
	if (REFIMPL_IS_WINDOW(windowListItem->data)) {
	    return GTK_WINDOW(windowListItem->data);
	}
    }

    refimpl_app_new_window(app);

    return refimpl_app_peek_first_window(app);
}

void refimpl_app_new_window(RefImplApp* self) {
    g_return_if_fail(REFIMPL_IS_APP(self));
    g_action_group_activate_action(G_ACTION_GROUP(self), "new-window", NULL);
}

void refimpl_app_quit(RefImplApp* self) {
    g_return_if_fail(REFIMPL_IS_APP(self));
    g_action_group_activate_action(G_ACTION_GROUP(self), "quit", NULL);
}

void refimpl_app_raise(RefImplApp* self) {
    g_return_if_fail(REFIMPL_IS_APP(self));
    g_action_group_activate_action(G_ACTION_GROUP(self), "raise", NULL);
}

gboolean refimpl_app_has_app_menu(RefImplApp* app) {
    g_return_val_if_fail(REFIMPL_IS_APP(app), FALSE);
    return gtk_application_prefers_app_menu(GTK_APPLICATION(app));
}

static void new_window_action(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    RefImplApp* app = REFIMPL_APP(user_data);
    GtkWidget* window;

    window = refimpl_window_new(app);
    gtk_application_add_window(GTK_APPLICATION(app), GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

static void about_window_action(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    RefImplApp* app = REFIMPL_APP(user_data);

    const gchar* authors[] = {
	"Michael B. McLaughlin <mikebmcl@gmail.com>",
	NULL
    };

    const gchar** documenters = NULL;
    GtkWindow* parent;
    parent = refimpl_app_peek_first_window(app);

    gtk_show_about_dialog(parent,
			  "name", "N3888_RefImpl",
			  "version", RefImplVersion,
			  "comments", "Reference implementation of the latest successor to N3888.",
			  "authors", authors,
			  "documenters", documenters,
			  "translator-credits", NULL,
			  "website", "https://github.com/mikebmcl/N3888_RefImpl/",
			  "website-label", "https://github.com/mikebmcl/N3888_RefImpl/",
//			  "logo-icon-name", PACKAGE_TARNAME,
			  NULL);
}

static void raise_action(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    RefImplApp* app = REFIMPL_APP(user_data);
    GtkWindow* window;

    window = refimpl_app_peek_first_window(app);
    gtk_window_present(window);
}

static void quit_action(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    RefImplApp* app = REFIMPL_APP(user_data);
    GList* windowListItem;

    while((windowListItem = gtk_application_get_windows(GTK_APPLICATION(app)))) {
	gtk_application_remove_window(GTK_APPLICATION(app), GTK_WINDOW(windowListItem->data));
    }
}

static GActionEntry app_entries[] = {
    { "new-window", new_window_action, NULL, NULL, NULL },
    { "about", about_window_action, NULL, NULL, NULL },
    { "quit", quit_action, NULL, NULL, NULL },
    { "raise", raise_action, NULL, NULL, NULL }
};

static void refimpl_app_startup(GApplication* application) {
    RefImplApp* app = REFIMPL_APP(application);

    G_APPLICATION_CLASS(refimpl_app_parent_class)->startup(application);

    g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), app);

    if (refimpl_app_has_app_menu(app)) {
	GtkBuilder* builder;
	GError* error = NULL;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_resource(builder,
					   "/com/bobtacoindustries/N3888_RefImpl/refimpl_menu.ui",
					   &error)) {
	    g_warning("Loading menu builder file failed. Message: %s", error->message);
	    g_error_free(error);
	}
	else {
	    GMenuModel* appMenu;
	    appMenu = G_MENU_MODEL(gtk_builder_get_object(builder, "app_menu"));
	    gtk_application_set_app_menu(GTK_APPLICATION(application), appMenu);
	}

	g_object_unref(builder);
    }

    //setup_accelerators(app);
}

RefImplApp* refimpl_app_new(void) {
    return g_object_new(REFIMPL_TYPE_APP,
			"application-id", "com.bobtacoindustries.N3888_RefImpl",
			"flags", G_APPLICATION_FLAGS_NONE,
			"register-session", TRUE,
			NULL);
}

static void refimpl_app_init(RefImplApp* app) {
    g_set_application_name("N3888_RefImpl");
    //gtk_window_set_default_icon_name("N3888RefImpl");
}

static void refimpl_app_dispose(GObject* obj) {
    //RefImplApp* app = REFIMPL_APP(obj);
    G_OBJECT_CLASS(refimpl_app_parent_class)->dispose(obj);
}

static void refimpl_app_class_init(RefImplAppClass* cls) {
    GObjectClass* objectClass = G_OBJECT_CLASS(cls);
    GApplicationClass* applicationClass = G_APPLICATION_CLASS(cls);

    applicationClass->startup = refimpl_app_startup;

    objectClass->dispose = refimpl_app_dispose;
}
