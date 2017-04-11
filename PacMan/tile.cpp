#include "classes.h"
#include "globals.h"
#include "functions.h"

Tile::Tile(int x, int y, int tileType) {
	// Get the offsets
	mBox.x = x;
	mBox.y = y;
	
	// Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;
	
	// Get the tile type
	mType = tileType;
}

void Tile::render() {
	int checkedType = mType == TILE_POWER_BLINK ? TILE_EMPTY : mType;
	
	// Show the tile
	gSpriteSheetTexture.render(mBox.x, mBox.y, &gTileClips[checkedType]);
}

int Tile::getType() {
	return mType;
}

void Tile::setType(int typeVal) {
	mType = typeVal;
}

SDL_Rect Tile::getBox() {
	return mBox;
}
