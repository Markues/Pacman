#include "globals.h"

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Scene textures
GameTexture gSpriteSheetTexture;
SDL_Rect gTileClips[Tile::TOTAL_TILE_SPRITES];
SDL_Rect gLetterClips[Word::TOTAL_LETTER_SPRITES];

Mix_Music *gIntro = NULL;
Mix_Chunk *gEatA = NULL;
Mix_Chunk *gEatB = NULL;

int activeFood = 0;

bool playFoodSoundA = true;

GAMESTATE gamestate = LEVELSTART;
