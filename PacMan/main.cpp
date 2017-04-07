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
			
			int frame = 0;
			
			// While application is running
			while(!quit) {
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					// User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					
					// Handle input for the dot
					//pacman.handleEvent(e);
				}
				
				//Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;
				
				// Move the dot
				//pacman.move(tileSet, timeStep);
				pacman.update(tileSet, timeStep);
				pacman.actuallyMove(timeStep);
				
				//Restart step timer
				stepTimer.start();
				
				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);
				
				// Render level
				for(int i = 0; i < TOTAL_TILES; ++i) {
					tileSet[i]->render();
				}
				
				// Render dot
				pacman.render(frame);
				
				// Update screen
				SDL_RenderPresent(gRenderer);
				
				++frame;
				
				if(frame / 3 >= P_ANIM_MOVE_FRAMES) {
					frame = 0;
				}
			}
		}
		
		// Free resources and close SDL
		close(tileSet);
	}
	
	return 0;
}
