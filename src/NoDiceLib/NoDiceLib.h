#include "config.h"
#include "exec.h"

#ifndef _NODICELIB_H
#define _NODICELIB_H

char *stristr(const char *String, const char *Pattern);

// File extensions off of "filebase" and other filesystem defines
#define EXT_ROM ".nes"      // Produced ROM file
#define EXT_SYMBOLS ".fns"  // "fns" symbol listing file
#define EXT_ASM ".asm"      // Game assembly source
#define SUBDIR_PRG "PRG"
#define SUBDIR_LEVELS SUBDIR_PRG "/levels"
#define SUBDIR_OBJECTS SUBDIR_PRG "/objects"
#define SUBDIR_ICONS "icons"
#define SUBDIR_ICON_LEVELS SUBDIR_ICONS "/levels"
#define SUBDIR_ICON_TILES SUBDIR_ICONS "/tiles"
#define SUBDIR_MAPS SUBDIR_PRG "/maps/"

// Screen size assumptions (FIXME: this isn't checked to sync with source)
#define TILEMEM_BASE 0x6000                                // Base of tile memory
#define TILEMEM_END 0x794F                                 // Absolute last address of tile memory
#define SCREEN_BYTESIZE 0x1B0                              // Screen size in bytes, non-vertical level
#define SCREEN_BYTESIZE_V 0xF0                             // Screen size in bytes, vertical level
#define SCREEN_WIDTH 16                                    // Vertical or non-vertical, a "screen" is 16 tiles wide
#define SCREEN_VHEIGHT (SCREEN_BYTESIZE_V / SCREEN_WIDTH)  // Vertical screen height
#define SCREEN_COUNT 15                                    // Number of screens when not vertical
#define SCREEN_VCOUNT 16                                   // Number of screens when vertical
#define TILESIZE 16                                        // Pixels wide and tall of a single tile
#define SCREEN_BYTESIZE_M 0x90                             // Screen size in bytes, world map (9 x 16)
#define SCREEN_MCOUNT 4                                    // Number of screens when world map
#define SCREEN_MAP_ROW_OFFSET \
    ((SCREEN_BYTESIZE - SCREEN_BYTESIZE_M) / SCREEN_WIDTH - 1)  // Offset to beginning of map tiles

// Object assumptions (FIXME: this isn't checked to sync with source)
#define OBJ_BANK 6
#define OBJS_MAX 48            // Maximum number of objects total possible in a level
#define MOBJS_MAX 9            // Maximum number of (pre-defined) objects total possible on a map
#define MAP_OBJECT_BASE_ROW 2  // Map objects are two rows in, otherwise not useful
#define MAX_MAP_LINKS 256  // Ideal value is 16x9x4 = 576, but this saves a bit which helps pack a value in gui_popups.c
#define MAX_SPECIAL_TILES 64  // Ideal value is 256 of course, but this helps pack a value in gui_popups.c

#define LEVEL_JCT_STARTS 16

// Types of generators (in level editor only, no bearing on the level format)
enum {
    GENTYPE_JCTSTART,  // Junction start generator
    GENTYPE_VARIABLE,  // Variable-size generator
    GENTYPE_FIXED      // Fixed-size generator
};

// Automatically populated when NoDice_load_level is called
extern struct NoDice_level {
    struct NoDice_level_header {
        unsigned short alt_level_layout,  // Alternate level layout address
            alt_level_objects;            // Alternate level object set address

        // Alternate tileset
        unsigned char alt_level_tileset;

        // The header option bytes
        unsigned char option[LEVEL_HEADER_COUNT];

        // Flag for whether level is vertical
        unsigned char is_vert;

        // Keep total screens
        unsigned char total_screens;

        // Capture vertical position; mostly used for creating thumbnail at this point
        unsigned short vert_scroll;

    } header;

    const struct NoDice_tileset *tileset;   // Tileset of this level
    const struct NoDice_the_levels *level;  // Definition of the level

    unsigned char bg_page_1,            // First MMC3 BG page
        bg_page_2;                      // Second MMC3 BG page
    unsigned char tile_layout[256][4];  // UL, LL, UR, LR; 8x8 patterns making up the 16x16 tile
    unsigned char bg_pal[16];           // NES color values making up the 4 BG palettes
    unsigned char spr_pal[16];          // NES color values making up the 4 SPR palettes
    unsigned char *tiles;               // Pointer to beginning of tile RAM

    // This defines a grid of tiles (stride depending on whether vertical or not)
    // where the index of the generator that produced the tile is stored, thus
    // the topmost generator of a particular tile has its index there.  This helps
    // to identify which tiles belong to what generator to simplify determining if
    // the mouse is actually on the generator and not an overlapped one or a gap.
    unsigned short tile_id_grid[TILEMEM_END - TILEMEM_BASE];

    struct NoDice_the_level_generator {
        unsigned short index;  // Internal index count for tile_id_grid
        unsigned char type;    // Type of generator

        unsigned char id;                 // ID of generator
        unsigned short addr_start;        // Tile RAM address generator starts at
        unsigned short addr_min;          // Minimum tile RAM address used
        unsigned short addr_max;          // Maximum tile RAM address used
        unsigned short xs, ys;            // Pixel X/Y start
        unsigned short xe, ye;            // Pixel X/Y end
        unsigned char p[GEN_MAX_PARAMS];  // Parameters depending on generator; see #define GEN_MAX_PARAMS
        unsigned char size;               // Size of generator

        struct NoDice_the_level_generator *prev;  // Previous generator in level
        struct NoDice_the_level_generator *next;  // Next generator in level
    } * generators;                               // All generators

    unsigned char Level_JctXLHStart[LEVEL_JCT_STARTS], Level_JctYLHStart[LEVEL_JCT_STARTS];

    unsigned short addr_start, addr_end;

    unsigned char object_unknown;
    struct NoDice_the_level_object {
        unsigned char row;
        unsigned char col;
        unsigned char id;  // 0xFF is a terminator
    } objects[OBJS_MAX];
    int object_count;

    // World Map stuff only
    struct NoDice_map_link {
        unsigned char row_tileset;   // upper 4 bits is row, lower 4 bits is tileset
        unsigned char col_hi;        // upper 4 bits is column, lower 4 bits is screen
        unsigned short object_addr;  // Object address (except Spade/Toad panels)
        unsigned short layout_addr;  // Layout address
    } map_links[MAX_MAP_LINKS];      // Enough storage to link every tile on every screen
    int map_link_count;

    // Special storage for map object items only
    unsigned char map_object_items[MOBJS_MAX];

} NoDice_the_level;

enum MUSICTRACK {
    MUSICTRACK_SQUARE2,
    MUSICTRACK_SQUARE1,
    MUSICTRACK_TRIANGLE,
    MUSICTRACK_NOISE,
    MUSICTRACK_DMC,

    MUSICTRACK_TOTAL
};

struct NoDice_music_context {
    // Holds pointers and initialization info to all segments
    struct NoDice_music_segment {
        const unsigned char *segment_data;             // Data belonging to segment
        unsigned char track_starts[MUSICTRACK_TOTAL];  // Start offsets for all tracks
    } music_segments[256];  // 256 should be more than enough since the segment counter is only 8-bit
    unsigned char music_segment_count;

    unsigned char rest_table_base;    // Base index value into rest_table
    const unsigned char *rest_table;  // Rest lookup table

    // Tally data, probably not useful?
    unsigned char index_start;
    unsigned char index_end;
    unsigned char index_loop;
};

int NoDice_Init();
const char *NoDice_Error();
void NoDice_Shutdown();

enum RUN6502_STOP_REASON {
    RUN6502_STOP_NOTSTOPPED,      // 6502 still running!
    RUN6502_STOP_END,             // Ended
    RUN6502_INIT_ERROR,           // Initialization error occurred!
    RUN6502_LEVEL_OORW_LOW,       // Level load out-of-range write low (beyond RAM A, below TILEMEM_BASE)
    RUN6502_LEVEL_OORW_HIGH,      // Level load out-of-range write high (greater than TILEMEM_END)
    RUN6502_GENERATOR_TOO_LARGE,  // A generator was loaded that has more parameters than GEN_MAX_PARAMS

    // Signals not set by the 6502 core, externally influenced
    RUN6502_TIMEOUT,               // Timeout hit (external source must make this happen)
    RUN6502_GENGENCOUNT_MISMATCH,  // Generator count unexpectedly changed
};
extern volatile enum RUN6502_STOP_REASON NoDice_Run6502_Stop;  // Set stop reason to halt execution

int NoDice_PRG_refresh();
const unsigned char *NoDice_get_raw_CHR_bank(unsigned char bank);
const unsigned char *NoDice_pack_level(int *size, int need_header);
void NoDice_load_level(unsigned char tileset, const char *level_layout, const char *object_layout);
void NoDice_load_level_raw_data(const unsigned char *data, int size, int has_header);
unsigned short NoDice_get_addr_for_label(const char *label);
int NoDice_get_tilebank_free_space(unsigned char tileset);
const unsigned char *NoDice_get_rest_table();
int NoDice_get_music_context(
    struct NoDice_music_context *context,
    const char *header_index_name,
    const char *SEL_name,
    unsigned char music_index);
void NoDice_tile_test();

const char *NoDice_DoBuild();

#endif  // _NODICELIB_H
