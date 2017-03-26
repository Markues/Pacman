#include "classes.h"
#include "globals.h"
#include "functions.h"

MoveableEntity::MoveableEntity(int startX, int startY) {
	// Initialize the collision box
	mBox.x = startX;
	mBox.y = startY;
	mBox.w = ENTITY_WIDTH / 2;
	mBox.h = ENTITY_HEIGHT / 2;
	
	// Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void MoveableEntity::handleEvent(SDL_Event& e) {
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

void MoveableEntity::move(Tile *tiles[]) {
	// Move the MoveableEntity left or right
	mBox.x += mVelX;
	
	// If the MoveableEntity went too far to the left or right or touched a wall
	if(touchesWall(mBox, tiles)) {
		// move back
		mBox.x -= mVelX;
	}
	
	if(mBox.x < 0 - ENTITY_WIDTH) {
		mBox.x = LEVEL_WIDTH;
	}
	
	if(mBox.x > LEVEL_WIDTH) {
		mBox.x = 0 - ENTITY_WIDTH;
	}
	
	// Move the MoveableEntity up or down
	mBox.y += mVelY;
	
	// If the MoveableEntity went too far up or down or touched a wall
	if(mBox.x < 0 || mBox.x + ENTITY_WIDTH / 2 > LEVEL_WIDTH || touchesWall(mBox, tiles)) {
		//move back
		mBox.y -= mVelY;
	}
}

void MoveableEntity::render() {
	// Show the MoveableEntity
	gDotTexture.render(mBox.x - COLL_BOX_OFFSET, mBox.y - COLL_BOX_OFFSET);
}

