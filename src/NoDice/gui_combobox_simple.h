#include <gtk/gtk.h>

#ifndef GUI_COMBOBOX_SIMPLE_H
#define GUI_COMBOBOX_SIMPLE_H

// Simple combobox
GtkWidget *gui_combobox_simple_new();
void gui_combobox_simple_add_item(GtkWidget *widget, int index, const char *text);
void gui_combobox_simple_clear_items(GtkWidget *widget);
void gui_combobox_simple_set_selected(GtkWidget *widget, int index);
int gui_combobox_simple_get_index(GtkWidget *widget);

#endif
