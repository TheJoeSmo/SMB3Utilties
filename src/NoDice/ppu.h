
#ifndef PPU_H
#define PPU_H

// PPU stuff
#define PPU_PORTAL_X 272
#define PPU_PORTAL_Y 44

// extern BITMAP *PPU_portal;
void ppu_init();
void ppu_set_BG_bank(unsigned char bank, unsigned char to0800);
void ppu_configure_for_level();
void ppu_draw_tile(int x, int y, unsigned char tile, unsigned char pal);
void ppu_draw(int x, int y, int w, int h);
int ppu_sprite_draw(unsigned char id, int x, int y);
void ppu_sprite_get_offset(unsigned char id, int *offset_x, int *offset_y, int *width, int *height);
void ppu_shutdown();

#endif
