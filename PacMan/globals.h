#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2_mixer/SDL_mixer.h>
#include "gameTexture.h"
#include "tile.h"
#include "word.h"

// The window we'll be rendering to
extern SDL_Window* gWindow;

// The window renderer
extern SDL_Renderer* gRenderer;

// Scene textures
extern GameTexture gSpriteSheetTexture;
extern SDL_Rect gTileClips[Tile::TOTAL_TILE_SPRITES];
extern SDL_Rect gLetterClips[Word::TOTAL_LETTER_SPRITES];

extern Mix_Music *gIntro;
extern Mix_Chunk *gEatA;
extern Mix_Chunk *gEatB;

extern int activeFood;

extern bool playFoodSoundA;

extern GAMESTATE gamestate;

#endif
