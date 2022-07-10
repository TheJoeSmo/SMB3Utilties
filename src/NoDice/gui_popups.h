#include "../NoDiceLib/NoDiceLib.h"

#ifndef NODICE_GUI_POPUPS_H
#define NODICE_GUI_POPUPS_H

// Popups
enum OPEN_LEVEL_POPUP {
    OLP_FORBROWSE = 1,             // Browsing for level, not intending to load
    OLP_NIBBLE_TILESETS_ONLY = 2,  // Only list levels that fit in a tileset 4-bits wide
};

void gui_display_6502_error(enum RUN6502_STOP_REASON reason);
void gui_display_message(int is_error, const char *err_str);
int gui_ask_question(const char *prompt);
int gui_open_level_popup(
    enum OPEN_LEVEL_POPUP popup_options, unsigned char *tileset, const struct NoDice_the_levels **level);
void gui_level_properties(struct NoDice_the_level_generator *selected_gen);
int gui_special_obj_properties(struct NoDice_the_level_object *object);
int gui_map_obj_properties(struct NoDice_the_level_object *object);
int gui_map_link_properties(struct NoDice_map_link *link);
int gui_new_level_popup();

#endif
