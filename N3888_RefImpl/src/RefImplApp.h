#pragma once
#ifndef REFIMPLAPP_H
#define REFIMPLAPP_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define REFIMPL_TYPE_APP         (refimpl_app_get_type())
#define REFIMPL_APP(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), REFIMPL_TYPE_APP, RefImplApp))
#define REFIMPL_IS_APP(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), REFIMPL_TYPE_APP))
#define REFIMPL_APP_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), REFIMPL_TYPE_APP, RefImplAppClass))
#define REFIMPL_IS_APP_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), REFIMPL_TYPE_APP))
#define REFIMPL_APP_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), REFIMPL_TYPE_APP, RefImplAppClass))

typedef struct RefImplApp_t RefImplApp;
typedef struct RefImplAppClass_t RefImplAppClass;
typedef struct RefImplAppPrivate_t RefImplAppPrivate;
struct RefImplApp_t {
    GtkApplication parent_instance;
};

struct RefImplAppClass_t {
    GtkApplicationClass parent_class;
};

const static gchar* RefImplVersion = "1.0.4073.1";
const static gchar* RefImplFullVersion = "N3888_RefImpl version 1.0.4073.1";

GType refimpl_app_get_type(void);

RefImplApp* refimpl_app_new(void);
void refimpl_app_new_window(RefImplApp* self);
void refimpl_app_quit(RefImplApp* self);
void refimpl_app_raise(RefImplApp* app);

gboolean refimpl_app_has_app_menu(RefImplApp* app);

G_END_DECLS

#endif
