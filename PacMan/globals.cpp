#include "classes.h"
#include "constants.h"

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Scene textures
LTexture gDotTexture;
LTexture gSpriteSheetTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
