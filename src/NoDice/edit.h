#include "guictls.h"

#ifndef NODICE_EDIT_H
#define NODICE_EDIT_H

const struct NoDice_the_levels *edit_level_find(unsigned char tileset_id, unsigned short layout_addr, unsigned short objects_addr);
int edit_level_save(int save_layout, int save_objects);
void edit_level_save_new_check(const char *tileset_path, const char *layoutfile, int *save_layout, const char *objectfile, int *save_objects);
int edit_level_add_labels(const struct NoDice_the_levels *level, int add_layout, int add_objects);
void edit_level_load(unsigned char tileset, const struct NoDice_the_levels *level);
void edit_gen_remove(struct NoDice_the_level_generator *gen);
void edit_revert();
void edit_gen_translate(struct NoDice_the_level_generator *gen, int diff_row, int diff_col);
void edit_gen_send_backward(struct NoDice_the_level_generator *gen);
void edit_gen_bring_forward(struct NoDice_the_level_generator *gen);
void edit_gen_send_to_back(struct NoDice_the_level_generator *gen);
void edit_gen_bring_to_front(struct NoDice_the_level_generator *gen);
void edit_gen_insert_generator(const struct NoDice_generator *gen, int row, int col, const unsigned char *p);
void edit_gen_set_parameters(struct NoDice_the_level_generator *gen, const unsigned char *parameters);
void edit_header_change(struct NoDice_the_level_generator *selected_gen, const unsigned char *old_header);
void edit_startspot_alt_load();
void edit_startspot_alt_revert();
void edit_obj_translate(struct NoDice_the_level_object *obj, int diff_row, int diff_col);
int edit_obj_insert_object(const struct NoDice_objects *obj, int row, int col);
void edit_obj_remove(struct NoDice_the_level_object *obj);
void edit_map_obj_clear(struct NoDice_the_level_object *obj);
void edit_maptile_set(int row, int col, unsigned char tile);
unsigned char edit_maptile_get(int row, int col);
void edit_link_translate(struct NoDice_map_link *link, int diff_row, int diff_col);
int edit_link_insert_link(int row, int col);
void edit_link_remove(struct NoDice_map_link *link);
void edit_link_adjust(struct NoDice_map_link *updated_link, struct NoDice_map_link *old_link);

#endif
