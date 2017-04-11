#ifndef CONSTANTS_H
#define CONSTANTS_H

// Screen dimension constants
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

// The dimensions of the level
const int LEVEL_WIDTH = 224;
const int LEVEL_HEIGHT = 288;

const int TILE_WIDTH = 8;
const int TILE_HEIGHT = 8;
const int TOTAL_VERTICAL_TILES = SCREEN_HEIGHT / TILE_HEIGHT;
const int TOTAL_HORIZONTAL_TILES = SCREEN_WIDTH / TILE_WIDTH;

const int SPRITE_WIDTH = 16;
const int SPRITE_HEIGHT = 16;
const int SPRITE_HITBOX_WIDTH = 8;
const int SPRITE_HITBOX_HEIGHT = 8;

const int TOTAL_TILES = 1008;
const int TILES_PER_ROW = 16;
const int NUM_TILE_ROWS = 3;
const int TOTAL_TILE_SPRITES = 36;

const int P_TOTAL_SPRITES = 24;
const int P_SPRITES_PER_ROW = 4;
const int P_SPRITES_PER_COL = 3;
const int P_SPRITES_PER_DIR = 3;
const int P_NUM_DEATH_SPRITES = 12;

const int P_ANIM_MOVE_FRAMES = 3;
const int P_ANIM_DEATH_FRAMES = 12;
const int T_ANIM_POW_FRAMES = 2;

// Moveable tiles
const int TILE_EMPTY = 32;
const int TILE_FOOD = 34;
const int TILE_POWER = 35;

enum PACMAN_ANIM_STATE {
	P_STATIC_NEUTRAL = 0,
	P_ANIM_RIGHT = 1,
	P_STATIC_RIGHT = 2,
	P_ANIM_LEFT = 3,
	P_STATIC_LEFT = 4,
	P_ANIM_UP = 5,
	P_STATIC_UP = 6,
	P_ANIM_DOWN = 7,
	P_STATIC_DOWN = 8,
	P_ANIM_DEATH = 9
};

enum GHOST_ANIM_STATE {
	G_ANIM_RIGHT = 0,
	G_ANIM_LEFT = 1,
	G_ANIM_UP = 2,
	G_ANIM_DOWN = 3,
	G_ANIM_RUNAWAY = 4,
	G_ANIM_RUNAWAY_END = 5,
	G_ANIM_RESPAWN = 6
};

enum DIRECTION {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	NONE = 4
};

#endif
