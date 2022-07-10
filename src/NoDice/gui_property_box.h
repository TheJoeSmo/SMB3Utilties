#include <gtk/gtk.h>

#ifndef GUI_PROPERTY_BOX_H
#define GUI_PROPERTY_BOX_H

void gui_generate_option_controls(GList **context, GtkWidget *vbox, unsigned short header_byte, unsigned char header_val, const struct NoDice_headers *header, GCallback list_change, GCallback toggle_change, GCallback spin_change);
void gui_update_option_controls(GList *context);

#endif
