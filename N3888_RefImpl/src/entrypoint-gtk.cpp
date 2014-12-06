#include <cairo.h>
#include <gtk/gtk.h>
#include <assert.h>
#include <stdexcept>
#include <clocale>

#include "RefImplApp.h"
#include "RefImplWindow.h"

using namespace std;

static gboolean option_new_window;
static gboolean option_quit;
static gboolean option_version;

static GOptionEntry options[] = {
    { "new-window", 'n', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE, &option_new_window, "Opens a new N3888_RefImpl window", NULL },
    { "version", 'v', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE, &option_version, "Display the version and exit", NULL },
    { "quit", 'q', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE, &option_quit, "Quit any running N3888_RefImpl", NULL },
    { NULL }
};

static void run_action (RefImplApp* application, gboolean isRemote) {
    if (option_new_window) {
	if (isRemote) {
	    refimpl_app_new_window(application);
	}
    }
    else {
	if (option_quit) {
	    refimpl_app_quit(application);
	}
	else {
	    if (isRemote) {
		refimpl_app_raise(application);
	    }
	}
    }
}

static void activate_callback(GtkApplication* application) {
    refimpl_app_new_window(REFIMPL_APP(application));

    run_action(REFIMPL_APP(application), FALSE);
}

int main(int argc, char** argv) {
    RefImplApp* application;
    GError* error = nullptr;
    int retVal;

    setlocale(LC_ALL, "");

    if (!gtk_init_with_args(&argc, &argv, nullptr, options, nullptr, &error)) {
	g_printerr("%s\n", error->message);
	return EXIT_FAILURE;
    }

    if (option_version) {
	g_print("%s\n", RefImplFullVersion);
	return EXIT_SUCCESS;
    }

    application = refimpl_app_new();
    g_signal_connect(application, "activate", G_CALLBACK(activate_callback), nullptr);

    g_application_set_default(G_APPLICATION(application));

    if (!g_application_register (G_APPLICATION (application), nullptr, &error)) {
	g_printerr("Couldn't register N3888_RefImpl instance: '%s'\n", error != nullptr ? error->message : "");
	g_object_unref (application);
	return EXIT_FAILURE;
    }

    if (g_application_get_is_remote (G_APPLICATION (application))) {
	run_action(application, TRUE);
	g_object_unref (application);
	return EXIT_SUCCESS;
    }

    retVal = g_application_run (G_APPLICATION (application), argc, argv);
    g_object_unref (application);

    return retVal;
}
