#include "classes.h"
#include "globals.h"

void Pacman::handleEvent(SDL_Event& e) {
	// If a key was pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP: mVelY -= ENTITY_VEL; break;
			case SDLK_DOWN: mVelY += ENTITY_VEL; break;
			case SDLK_LEFT: mVelX -= ENTITY_VEL; break;
			case SDLK_RIGHT: mVelX += ENTITY_VEL; break;
		}
	}
	// If a key was released
	else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP: mVelY += ENTITY_VEL; break;
			case SDLK_DOWN: mVelY -= ENTITY_VEL; break;
			case SDLK_LEFT: mVelX += ENTITY_VEL; break;
			case SDLK_RIGHT: mVelX -= ENTITY_VEL; break;
		}
	}
}

void Pacman::render() {
	switch (animState) {
		case P_ANIM_RIGHT:
			break;
		case P_ANIM_LEFT:
			break;
		case P_ANIM_UP:
			break;
		case P_ANIM_DOWN:
			break;
		case P_ANIM_DEATH:
			break;
	}

	gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[0]);
}
