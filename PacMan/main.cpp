#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include "constants.h"
#include "functions.h"
#include "food.h"
#include "gameTimer.h"
#include "ghost.h"
#include "globals.h"
#include "pacman.h"
#include "tile.h"

using namespace std;

// make a music finished function
void musicFinished()
{
	gamestate = PLAYING;
}

int main(int argc, char* args[]) {
	// Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// The level tiles
		Tile* tileSet[Tile::TOTAL_TILES];
		// The food tiles
		Food* foodSet[Food::TOTAL_FOOD];
		
		// Load media
		if(!loadMedia(tileSet, foodSet)) {
			printf( "Failed to load media!\n" );
		}
		else {
			// Main loop flag
			bool quit = false;
			
			// Event handler
			SDL_Event e;
			
			Pacman pacman(104, 204);
			Ghost blinky(104, 108, Ghost::BLINKY);
			Ghost inky(88, 132, Ghost::INKY);
			Ghost pinky(104, 132, Ghost::PINKY);
			Ghost clyde(120, 132, Ghost::CLYDE);
			
			GameTimer stepTimer;
			
			Mix_PlayMusic(gIntro, 1);
			
			// Don't being play until the music stops
			Mix_HookMusicFinished(musicFinished);
			
			// While application is running
			while(!quit) {
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					// User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
						switch(e.key.keysym.sym) {
							case SDLK_ESCAPE:
								gamestate = gamestate == PAUSED ? PLAYING : PAUSED;
								break;
						}
					}
				}
				
				if(gamestate == LEVELSTART) {
					float startTimeStep = 0.0f;
					
					// Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderClear(gRenderer);
					
					// Render level
					for(int i = 0; i < Tile::TOTAL_TILES; ++i) {
						tileSet[i]->render();
					}
					// Render the food
					for(int i = 0; i < Food::TOTAL_FOOD; ++i) {
						foodSet[i]->render(startTimeStep);
					}
					
					// Render Pacman
					pacman.render(startTimeStep);
					
					blinky.render(startTimeStep);
					inky.render(startTimeStep);
					pinky.render(startTimeStep);
					clyde.render(startTimeStep);
					
					// Update screen
					SDL_RenderPresent(gRenderer);
				}
				else if(gamestate == PLAYING) {
					stepTimer.unpause();
					
					// Calculate time step
					int timeStepMilli = stepTimer.getTicks();
					float timeStepSec = timeStepMilli / 1000.f;
					
					// Move pacman
					pacman.update(tileSet, timeStepSec);
					
					// Check to see if Pacman ate any food
					for(int i = 0; i < Food::TOTAL_FOOD; ++i) {
						foodSet[i]->update(&pacman);
					}
					
					// Restart step timer
					stepTimer.start();
					
					// Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderClear(gRenderer);
					
					// Render level
					for(int i = 0; i < Tile::TOTAL_TILES; ++i) {
						tileSet[i]->render();
					}
					// Render the food
					for(int i = 0; i < Food::TOTAL_FOOD; ++i) {
						foodSet[i]->render(timeStepMilli);
					}
					
					// Render Pacman
					pacman.render(timeStepMilli);
					
					blinky.render(timeStepMilli);
					inky.render(timeStepMilli);
					pinky.render(timeStepMilli);
					clyde.render(timeStepMilli);
					
					// Update screen
					SDL_RenderPresent(gRenderer);
				}
				else if(gamestate == PAUSED) {
					stepTimer.pause();
					SDL_Delay(1000.0f / 30); // 30FPS while paused
				}
			}
		}
		
		// Free resources and close SDL
		close(tileSet, foodSet);
	}
	
	return 0;
}
