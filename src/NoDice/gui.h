#include "../NoDiceLib/NoDiceLib.h"

#ifndef NODICE_GUI_H
#define NODICE_GUI_H

// GUI controls
enum EDIT_NOTEBOOK_PAGES {
    ENPAGE_GENS,    // Regular level generators
    ENPAGE_OBJS,    // Regular level objects
    ENPAGE_STARTS,  // Regular level start positions
    ENPAGE_TILES,   // World map tiles
    ENPAGE_MOBJS,   // World map objects
    ENPAGE_LINKS,   // World map links
    ENPAGE_TOTAL
};

// Not going to expose Cairo surface, but reserved in case we need a "real" type
typedef void gui_surface_t;

// Publicizes info about the current drawing surface to the virtual PPU
extern struct _gui_draw_info {
    double tilehint_alpha;
    double zoom;
    void *context;  // Holds pointer to context for Cairo; typeless so it can be exposed
} gui_draw_info;

extern struct _gui_tilehints {
    gui_surface_t *hint;  // Tile hint graphic
    int is_global;        // TRUE means this is from the global <tilehints /> collection, so no need to free/reload
} gui_tilehints[256];

void gui_boot(int argc, char *argv[]);
int gui_init();
void gui_loop();
gui_surface_t *gui_surface_create(int width, int height);
gui_surface_t *gui_surface_from_file(const char *file);
unsigned char *gui_surface_capture_data(gui_surface_t *surface, int *out_stride);
void gui_surface_release_data(gui_surface_t *surface);
void gui_surface_blit(gui_surface_t *draw, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void gui_surface_overlay(gui_surface_t *draw, int dest_x, int dest_y);
void gui_surface_destroy(gui_surface_t *surface);
void gui_update_for_generators();
void gui_refesh_for_level();
void gui_6502_timeout_start();
void gui_6052_timeout_end();
void gui_overlay_select_index(int index);
const char *gui_make_image_path(const struct NoDice_tileset *tileset, const struct NoDice_the_levels *level);
void gui_set_subtitle(const char *subtitle);
void gui_set_modepage(enum EDIT_NOTEBOOK_PAGES page);
void gui_disable_empty_objs(int is_empty);
void gui_reboot();

#endif
