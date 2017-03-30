#include <SDL2_image/SDL_image.h>
#include "constants.h"
#include "globals.h"
#include "functions.h"
#include <fstream>

using namespace std;

bool init() {
	// Initialization flag
	bool success = true;
	
	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
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
			}
		}
	}
	
	return success;
}

bool loadMedia(Tile* tiles[]) {
	// Loading success flag
	bool success = true;
	
	// Load tile texture
	if(!gSpriteSheetTexture.loadFromFile("spritesheet.png")) {
		printf("Failed to load spritesheet texture!\n");
		success = false;
	}
	
	// Load tile map
	if(!setTiles(tiles)) {
		printf("Failed to load tile set!\n");
		success = false;
	}
	
	return success;
}

void close(Tile* tiles[]) {
	// Deallocate tiles
	for(int i = 0; i < TOTAL_TILES; ++i) {
		if(tiles[i] == NULL) {
			delete tiles[ i ];
			tiles[i] = NULL;
		}
	}
	
	// Free loaded images
	gSpriteSheetTexture.free();
	
	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	// Quit SDL subsystems
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

bool setTiles(Tile* tiles[]) {
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
		for(int i = 0; i < TOTAL_TILES; ++i) {
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
			if((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
				tiles[i] = new Tile(x, y, tileType);
			}
			// If we don't recognize the tile type
			else {
				// Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}
			
			// Move to next tile spot
			x += TILE_WIDTH;
			
			// If we've gone too far
			if(x >= LEVEL_WIDTH) {
				// Move back
				x = 0;
				
				// Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
		// Clip the sprite sheet
		if(tilesLoaded) {
			for(int i = 0; i < NUM_TILE_ROWS; i++) {
				for(int j = 0; j < TILES_PER_ROW; j++) {
					int currentTile = (i * TILES_PER_ROW) + j;
					gTileClips[currentTile].x = j * TILE_WIDTH;
					gTileClips[currentTile].y = i * TILE_HEIGHT;
					gTileClips[currentTile].w = TILE_WIDTH;
					gTileClips[currentTile].h = TILE_HEIGHT;
					if(currentTile >= TOTAL_TILES) {
						break;
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

bool touchesWall(SDL_Rect box, Tile* tiles[]) {
	// Go through the tiles
	for(int i = 0; i < TOTAL_TILES; ++i) {
		// If the tile is a wall type tile
		if((tiles[i]->getType() != TILE_EMPTY) && (tiles[i]->getType() != TILE_FOOD) && (tiles[i]->getType() != TILE_POWER)) {
			// If the collision box touches the wall tile
			if(checkCollision(box, tiles[i]->getBox())) {
				return true;
			}
		}
	}
	
	// If no wall tiles were touched
	return false;
}
