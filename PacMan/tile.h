#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include "constants.h"

class Tile {
public:
	const static int TILE_WIDTH = 8;
	const static int TILE_HEIGHT = 8;
	
	const static int TOTAL_VERTICAL_TILES = SCREEN_HEIGHT / TILE_HEIGHT;
	const static int TOTAL_HORIZONTAL_TILES = SCREEN_WIDTH / TILE_WIDTH;
	
	const static int TOTAL_TILES = 1008;
	const static int NUM_HORIZ_TILES = 28;
	const static int NUM_VERT_TILES = 36;
	const static int NON_COLL_TILES_TOP = NUM_HORIZ_TILES * 3;
	const static int NON_COLL_TILES_BOT = NUM_HORIZ_TILES * 2;
	
	const static int TILES_PER_ROW = 16;
	const static int NUM_TILE_ROWS = 3;
	const static int TOTAL_TILE_SPRITES = 36;
	
	const static int TILE_EMPTY = 32;
	const static int TILE_FOOD = 34;
	const static int TILE_POWER = 35;
	
	// Initializes position and type
	Tile(int x, int y, int tileType);
	
	// Shows the tile
	void render();
	
	// Get the tile type
	int getType();
	
	void setType(int typeVal);
	
	// Get the collision box
	SDL_Rect getBox();
	
protected:
	const static int T_ANIM_POW_FRAMES = 2;
	
	// The attributes of the tile
	SDL_Rect mBox;
	
	// The tile type
	int mType;
};

#endif
