#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "tile.h"
#include "food.h"

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia(Tile* tiles[], Food* foodTiles[]);

// Frees media and shuts down SDL
void close(Tile* tiles[], Food* food[]);

// Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

// Checks collision box against set of tiles
bool touchesWall(SDL_Rect box, Tile* tiles[]);

// Sets tiles from tile map
bool setTilesAndLetters(Tile* tiles[], Food* foodTiles[]);

int getCurrentTileIndex(int xPos, int yPos);
Tile* getTileToLeft(Tile* tiles[], int xPos, int yPos);
Tile* getTileToRight(Tile* tiles[], int xPos, int yPos);
Tile* getTileAbove(Tile* tiles[], int xPos, int yPos);
Tile* getTileBelow(Tile* tiles[], int xPos, int yPos);

bool fuzzyEquals(int firstNum, int secondNum, int threshold);
bool areOpposites(DIRECTION dirOne, DIRECTION dirTwo);

#endif
