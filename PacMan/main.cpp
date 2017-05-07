#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

using namespace std;

int main(int argc, char* args[]) {
	// Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// The level tiles
		Tile* tileSet[TOTAL_TILES];
		// The food tiles
		Food* foodSet[TOTAL_FOOD];
		
		// Load media
		if(!loadMedia(tileSet, foodSet)) {
			printf( "Failed to load media!\n" );
		}
		else {
			// Main loop flag
			bool quit = false;
			
			GAMESTATE gamestate = PLAYING;
			
			// Event handler
			SDL_Event e;
			
			Pacman pacman(104, 204);
			
			//Keeps track of time between steps
			GameTimer stepTimer;
			
			// While application is running
			while(!quit) {
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					// User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
						if(e.key.keysym.sym == SDLK_ESCAPE) {
							if(gamestate == PAUSED) {
								gamestate = PLAYING; // Unpause
							}
							else {
								gamestate = PAUSED;
							}
						}
					}
				}
				
				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
		
		// Free resources and close SDL
		close(tileSet);
	}
	
	return 0;
}
