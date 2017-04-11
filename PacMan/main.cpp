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
		
		// Load media
		if(!loadMedia(tileSet)) {
			printf( "Failed to load media!\n" );
		}
		else {
			// Main loop flag
			bool quit = false;
			
			// Event handler
			SDL_Event e;
			
			// The dot that will be moving around on the screen
			Pacman pacman(104, 204);
			
			//Keeps track of time between steps
			GameTimer stepTimer;
			
			int p_frame = 0;
			int pow_frame = 0;
			
			// While application is running
			while(!quit) {
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					// User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
				}
				
				// Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;
				
				// Move pacman
				pacman.update(tileSet, timeStep);
				
				// Restart step timer
				stepTimer.start();
				
				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);
				
				// TODO - This should not be hardcoded, instead loaded from data
				// To come later :)
				if(pow_frame / 12 == 0) {
					tileSet[169]->setType(TILE_POWER);
					tileSet[194]->setType(TILE_POWER);
					tileSet[729]->setType(TILE_POWER);
					tileSet[754]->setType(TILE_POWER);
				}
				else {
					tileSet[169]->setType(TILE_EMPTY);
					tileSet[194]->setType(TILE_EMPTY);
					tileSet[729]->setType(TILE_EMPTY);
					tileSet[754]->setType(TILE_EMPTY);
				}
				// Render level
				for(int i = 0; i < TOTAL_TILES; ++i) {
					tileSet[i]->render();
				}
				
				// Render dot
				pacman.render(p_frame);
				//pacman.renderSurrs();
				
				// Update screen
				SDL_RenderPresent(gRenderer);
				
				++p_frame;
				++pow_frame;
				
				// TODO - Make animation class
				if(p_frame / 3 >= P_ANIM_MOVE_FRAMES) {
					p_frame = 0;
				}
				if(pow_frame / 12 >= T_ANIM_POW_FRAMES) {
					pow_frame = 0;
				}
			}
		}
		
		// Free resources and close SDL
		close(tileSet);
	}
	
	return 0;
}
