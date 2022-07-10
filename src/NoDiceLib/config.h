#include <limits.h>

// Force a path max in case limits doesn't work
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef NODICE_CONFIG_H
#define NODICE_CONFIG_H

// GEN_MAX_PARAMS: Maximum number of "parameters" a generator may have;
// Should definitely be >= 2.  GENTYPE_JCTSTART requires 2.  GENTYPE_VARIABLE
// may need 1 to 2.  For GENTYPE_VARIABLE, the first is always LL_ShapeDef's
// lower 4 bits, second is an additional byte that MAY be used by some of the
// variable generators that need a greater parameter range.
// This also determines the maximum <param /> blocks you can have in game.xml
#define GEN_MAX_PARAMS	2

// There are 5 level header bytes besides the pointers to next level/object
#define LEVEL_HEADER_COUNT	5

// Types of build errors
enum BUILDERR
{
	BUILDERR_RETURNCODE,	// Check if assembler returns non-zero code
	BUILDERR_TEXTERROR,		// Check if assembler output includes word "error"
	BUILDERR_TOTAL
};

// Automatically loaded from XML when initialized
extern struct NoDice_configuration
{
	char original_dir[PATH_MAX];	// Maintain original CWD in case of configuration reload
	const char *game_dir;

	struct
	{
		char *_build_str;		// Pointer to split build string, just required for freeing later
		char **build_argv;		// Build executable (index 0) and additional parameters
		enum BUILDERR builderr;	// Error check style
	} buildinfo;

	const char *filebase;
	int core6502_timeout;
	unsigned short level_range_check_high;

	// Built from the game.xml
	struct NoDice_game
	{
		struct NoDice_options
		{
			const char *title;				// Game title
			const char *warpzone;			// Warp Zone layout label definition
			const char *object_set_bank;	// The bank ASM file which specifies 
		} options;

		struct NoDice_tilehint
		{
			unsigned char id;		// ID of the tile
			const char *overlay;	// Overlay graphic file
		} *tilehints;				// Tileset-agnostic (common) hints
		int tilehint_count;

		struct NoDice_tileset
		{
			int id;			// ID of tileset
			const char *name;		// Name of tileset
			const char *path;		// Relative file path component to access tileset
			const char *rootfile;	// Name of ASM file which defines the layout includes for this tileset; if null, use "path"
			const char *desc;		// Description of tileset

			struct NoDice_generator
			{
				unsigned char type;	// Type of generator
				unsigned char id;	// ID of generator
				const char *name;	// Name of generator
				const char *desc;	// Description of generator

				// This just provides descriptive labels for the parameters
				// of the generator and parameter ranges
				struct NoDice_generator_parameter
				{
					const char *name;	// Name of the parameter
					unsigned char min;	// Minimum value
					unsigned char max;	// Maximum value
				} parameters[GEN_MAX_PARAMS];

			}	*generators;		// Variable and Fixed-size block generators
			int 	gen_count;		// Count of generators

			struct NoDice_tilehint *tilehints;	// Tileset specific hints
			int tilehint_count;

			struct NoDice_the_levels
			{
				const char *name;		// Name of level
				const char *layoutfile;	// Assembly file for level layout
				const char *layoutlabel;	// Assembly label for level layout
				const char *objectfile;	// Assembly file for object layout
				const char *objectlabel;	// Assembly label for object layout
				const char *desc;		// Description of level
			}
				*levels;
			int levels_count;		// Count of levels


		} *tilesets;	// Tilesets in this game

		int tileset_count;	// Count of tilesets

		struct NoDice_headers
		{
			// Each header byte can be broken into one or more <options />
			struct NoDice_header_options
			{
				const char *id;		// Optional id value for referencing
				unsigned char mask;		// Mask of options list
				unsigned char shift;	// Shift value
				const char *display;	// Display value

				// Each <option /> block
				struct NoDice_option
				{
					const char *label;		// Assembler label for this option item
					const char *display;	// Display value for this option item
					unsigned char value;	// Value for this option
				} *options;
				int options_count;

				// Form: "id:val"
				const char *showif_id;		// Id to check
				unsigned char showif_val;	// Value to match
			} *options_list;
			int options_list_count;

		} 	headers[LEVEL_HEADER_COUNT];

		// Junction has some options
		struct NoDice_headers jct_options;

		struct NoDice_objects
		{
			const char *label;		// Label
			const char *name;		// Name of object
			const char *desc;		// Description

			struct NoDice_object_sprites
			{
				int x;
				int y;
				unsigned char bank;
				unsigned char pattern;
				unsigned char palette;
				unsigned char flips;	// bit 0: Hflip, 1: Vflip
			} *sprites;
			int total_sprites;

			struct NoDice_headers special_options;

		}	*objects,
			regular_objects[256], 	// Level objects
			map_objects[256];		// World Map objects

		struct NoDice_map_object_item
		{
			unsigned char id;	// ID of item
			const char *name;	// Name of item
		} *map_object_items;
		int total_map_object_items;

		struct NoDice_map_special_tile
		{
			unsigned char id;			// ID of tile to map
			unsigned char tileset;		// If "tilelayout" is specified, this provides the tileset to be used (otherwise ignored)

			// Spade and Toad houses can use one or the other layout values for something else
			struct NoDice_map_special_tile_override
			{
				struct NoDice_headers low;	// Low byte options
				struct NoDice_headers high;	// High byte options
			} override_tile, override_object;
		} *map_special_tiles;
		int total_map_special_tiles;
	} game;
} NoDice_config;

int _config_init();
void _config_shutdown();

const char *NoDice_config_game_add_level_entry(unsigned char tileset, const char *name, const char *layoutfile, const char *layoutlabel, const char *objectfile, const char *objectlabel, const char *desc);

#endif
