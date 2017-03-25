#include "classes.h"
#include "globals.h"
#include "functions.h"

Tile::Tile( int x, int y, int tileType )
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;
	
	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;
	
	//Get the tile type
	mType = tileType;
}

void Tile::render()
{
	//Show the tile
	gTileTexture.render(mBox.x, mBox.y, &gTileClips[mType]);
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}
