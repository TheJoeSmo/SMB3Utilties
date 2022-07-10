#include <gtk/gtk.h>

#ifndef GUI_OVERLAY_H
#define GUI_OVERLAY_H

G_BEGIN_DECLS

#define GTK_SELECTABLE_OVERLAY(obj) GTK_CHECK_CAST(obj, gtk_selectable_overlay_get_type(), GtkSelectableOverlay)
#define GTK_SELECTABLE_OVERLAY_CLASS(klass) \
    GTK_CHECK_CLASS_CAST(klass, gtk_selectable_overlay_get_type(), GtkSelectableOverlayClass)
#define GTK_IS_SELECTABLE_OVERLAY(obj) GTK_CHECK_TYPE(obj, gtk_selectable_overlay_get_type())

typedef struct _GtkSelectableOverlay GtkSelectableOverlay;
typedef struct _GtkSelectableOverlayClass GtkSelectableOverlayClass;

struct _GtkSelectableOverlay {
    GtkWidget widget;
    void (*select_handler)(const GtkSelectableOverlay *selectable_overlay);

    struct NoDice_the_level_generator *gen;  // The generator this represents (if applicable)
    struct NoDice_the_level_object *obj;     // The object this represents (if applicable)
    struct NoDice_map_link *link;            // The map link this represents (if applicable)

    gboolean selected;  // This item is selected

    struct _translation_data {
        double mouse_origin_x, mouse_origin_y;  // Origin of mouse when dragging began
        int origin_x, origin_y;                 // Origin X/Y
    } translation_data;                         // Data used to translate a generator
};

struct _GtkSelectableOverlayClass {
    GtkWidgetClass parent_class;
};

GtkType gtk_selectable_overlay_get_type(void);
GtkWidget *gtk_selectable_overlay_new();
void gtk_selectable_overlay_select(GtkSelectableOverlay *selectable_overlay);

G_END_DECLS

#endif
