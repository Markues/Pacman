#include "gameTexture.h"
#include "constants.h"
#include "globals.h"

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Scene textures
GameTexture gSpriteSheetTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

int activeFood = 0;
