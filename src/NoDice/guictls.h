#include <cairo.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "gui_combobox_simple.h"
#include "gui_overlay.h"
#include "gui_popups.h"
#include "gui_property_box.h"

#ifndef GUICTLS_H_INCLUDED
#define GUICTLS_H_INCLUDED

// Pseudo-listbox
GtkWidget *gui_listbox_new(GCallback sel_change_callback, gpointer user_data);
void gui_listbox_additem(GtkListStore *list_store, int index, const char *item);
GtkListStore *gui_listbox_get_disconnected_list(GtkWidget *listbox);
void gui_listbox_reconnect_list(GtkWidget *listbox, GtkListStore *model);
int gui_listbox_get_index_by_view(GtkTreeView *view);
int gui_listbox_get_index(GtkWidget *listbox);
void gui_listbox_set_index(GtkWidget *listbox, int index);
void gui_listbox_set_first(GtkWidget *listbox);

#endif  // GUICTLS_H_INCLUDED
