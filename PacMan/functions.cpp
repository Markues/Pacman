#include <SDL2_image/SDL_image.h>
#include "functions.h"
#include "globals.h"
#include "letter.h"
#include "tile.h"
#include <fstream>

using namespace std;

bool init() {
	// Initialization flag
	bool success = true;
	
	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
			printf("Warning: Nearest pixel sampling not enabled!");
		}
		
		// Create window
		gWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// Set the device independent resolution for rendering 
				SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				
				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				
				// Initialize SDL_mixer
				if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}
	
	return success;
}

bool loadMedia(Tile* tiles[], Food* foodTiles[]) {
	// Loading success flag
	bool success = true;
	
	// Load tile texture
	if(!gSpriteSheetTexture.loadFromFile("spritesheet.png")) {
		printf("Failed to load spritesheet texture!\n");
		success = false;
	}
	
	// Load tile map
	if(!setTilesAndLetters(tiles, foodTiles)) {
		printf("Failed to load tiles and letters!\n");
		success = false;
	}
	
	// Load sound effects
	gIntro = Mix_LoadMUS("pacman_sfx/intro.wav");
	if(gIntro == NULL) {
		printf("Failed to load intro sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gEatA = Mix_LoadWAV("pacman_sfx/munch A.wav");
	if(gEatA == NULL) {
		printf("Failed to load eatA sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gEatB = Mix_LoadWAV("pacman_sfx/munch B.wav");
	if(gEatB == NULL) {
		printf("Failed to load eatB sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	return success;
}

void close(Tile* tiles[], Food* food[]) {
	// Deallocate tiles
	for(int i = 0; i < Tile::TOTAL_TILES; ++i) {
		if(tiles[i] != NULL) {
			delete tiles[i];
			tiles[i] = NULL;
		}
	}
	
	// Deallocate food
	for(int i = 0; i < Food::TOTAL_FOOD; ++i) {
		if(food[i] != NULL) {
			delete food[i];
			food[i] = NULL;
		}
	}
	
	Mix_FreeMusic(gIntro);
	Mix_FreeChunk(gEatA);
	Mix_FreeChunk(gEatB);
	gIntro = NULL;
	gEatA = NULL;
	gEatB = NULL;
	
	// Free loaded images
	gSpriteSheetTexture.free();
	
	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	// Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	
	// Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	
	// Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	
	// If any of the sides from A are outside of B
	if(bottomA <= topB) {
		return false;
	}
	
	if(topA >= bottomB) {
		return false;
	}
	
	if(rightA <= leftB) {
		return false;
	}
	
	if(leftA >= rightB) {
		return false;
	}
	
	// If none of the sides from A are outside B
	return true;
}

bool setTilesAndLetters(Tile* tiles[], Food* foodTiles[]) {
	// Success flag
	bool tilesLoaded = true;
	
	// The tile offsets
	int x = 0, y = 0;
	
	// Open the map
	ifstream map("Level1.map");
	
	// If the map couldn't be loaded
	if(!map.is_open()) {
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else {
		// Initialize the tiles
		for(int i = 0; i < Tile::TOTAL_TILES; ++i) {
			// Determines what kind of tile will be made
			int tileType = -1;
			
			// Read tile from map file
			map >> tileType;
			
			// If the was a problem in reading the map
			if(map.fail()) {
				// Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}
			
			// If the number is a valid tile number
			if((tileType >= 0) && (tileType < Tile::TOTAL_TILE_SPRITES)) {
				if(tileType == Tile::TILE_FOOD || tileType == Tile::TILE_POWER) {
					foodTiles[activeFood] = new Food(x, y, tileType);
					activeFood += 1;
					tiles[i] = new Tile(x, y, Tile::TILE_EMPTY);
				}
				else {
					tiles[i] = new Tile(x, y, tileType);
				}
			}
			// If we don't recognize the tile type
			else {
				// Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}
			
			// Move to next tile spot
			x += Tile::TILE_WIDTH;
			
			// If we've gone too far
			if(x >= LEVEL_WIDTH) {
				// Move back
				x = 0;
				
				// Move to the next row
				y += Tile::TILE_HEIGHT;
			}
		}
		
		// Clip the sprite sheet (tiles and letters)
		if(tilesLoaded) {
			for(int i = 0; i < Tile::NUM_TILE_ROWS + Letter::NUM_LETTER_ROWS; i++) {
				for(int j = 0; j < Tile::TILES_PER_ROW; j++) {
					int currentSprite = (i * Tile::TILES_PER_ROW) + j;
					if(currentSprite >= Tile::TOTAL_TILE_SPRITES + Letter::TOTAL_LETTER_SPRITES) {
						break;
					}
					else if(currentSprite >= Tile::TOTAL_TILE_SPRITES) {
						gLetterClips[currentSprite - Tile::TOTAL_TILE_SPRITES].x = j * Letter::LETTER_WIDTH;
						gLetterClips[currentSprite - Tile::TOTAL_TILE_SPRITES].y = i * Letter::LETTER_HEIGHT;
						gLetterClips[currentSprite - Tile::TOTAL_TILE_SPRITES].w = Letter::LETTER_WIDTH;
						gLetterClips[currentSprite - Tile::TOTAL_TILE_SPRITES].h = Letter::LETTER_HEIGHT;
					}
					else {
						gTileClips[currentSprite].x = j * Tile::TILE_WIDTH;
						gTileClips[currentSprite].y = i * Tile::TILE_HEIGHT;
						gTileClips[currentSprite].w = Tile::TILE_WIDTH;
						gTileClips[currentSprite].h = Tile::TILE_HEIGHT;
					}
				}
			}
		}
	}
	
	// Close the file
	map.close();
	
	// If the map was loaded fine
	return tilesLoaded;
}

bool touchesWall(SDL_Rect box, Tile *tiles[]) {
	// Go through the tiles
	for(int i = Tile::NON_COLL_TILES_TOP; i < Tile::TOTAL_TILES - Tile::NON_COLL_TILES_BOT; ++i) {
		// If the tile is a wall type tile
		if(tiles[i]->getType() != Tile::TILE_EMPTY) {
			// If the collision box touches the wall tile
			if(checkCollision(box, tiles[i]->getBox())) {
				return true;
			}
		}
	}
	
	// If no wall tiles were touched
	return false;
}

int getCurrentTileIndex(int xPos, int yPos) {
	return (((yPos + (SPRITE_HITBOX_HEIGHT / 2)) / Tile::TILE_HEIGHT) * Tile::TOTAL_HORIZONTAL_TILES) + ((xPos + (SPRITE_HITBOX_WIDTH / 2)) / Tile::TILE_WIDTH);
}

Tile* getTileToLeft(Tile *tiles[], int xPos, int yPos) {
	int currentTileIndex = getCurrentTileIndex(xPos, yPos);
	
	return tiles[currentTileIndex - 1];
}

Tile* getTileToRight(Tile *tiles[], int xPos, int yPos) {
	int currentTileIndex = getCurrentTileIndex(xPos, yPos);
	
	return tiles[currentTileIndex + 1];
}

Tile* getTileAbove(Tile *tiles[], int xPos, int yPos) {
	int currentTileIndex = getCurrentTileIndex(xPos, yPos);

	return tiles[currentTileIndex - Tile::TOTAL_HORIZONTAL_TILES];
}

Tile* getTileBelow(Tile *tiles[], int xPos, int yPos) {
	int currentTileIndex = getCurrentTileIndex(xPos, yPos);
	
	return tiles[currentTileIndex + Tile::TOTAL_HORIZONTAL_TILES];
	
}

bool fuzzyEquals(int firstNum, int secondNum, int threshold) {
	return abs(firstNum - secondNum) <= threshold;
}

bool areOpposites(DIRECTION dirOne, DIRECTION dirTwo) {
	switch (dirOne) {
		case LEFT:
			if(dirTwo == RIGHT) {
				return true;
			}
			break;
		case RIGHT:
			if(dirTwo == LEFT) {
				return true;
			}
			break;
		case UP:
			if(dirTwo == DOWN) {
				return true;
			}
			break;
		case DOWN:
			if(dirTwo == UP) {
				return true;
			}
			break;
		default:
			break;
	}
	
	return false;
}
