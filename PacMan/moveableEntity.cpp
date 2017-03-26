#include "classes.h"
#include "globals.h"
#include "functions.h"

MoveableEntity::MoveableEntity(int startX, int startY) {
	// Initialize the collision box
	mBox.x = startX + COLL_BOX_OFFSET;
	mBox.y = startY + COLL_BOX_OFFSET;
	mBox.w = ENTITY_WIDTH / 2;
	mBox.h = ENTITY_HEIGHT / 2;
	
	mPosX = startX;
	mPosY = startY;
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

void MoveableEntity::move(Tile *tiles[], float timeStep) {
	// Move the MoveableEntity left or right
	mPosX += mVelX * timeStep;
	mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	
	// If the MoveableEntity went too far to the left or right or touched a wall
	if(touchesWall(mBox, tiles)) {
		// move back
		mPosX -= mVelX * timeStep;
		mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	}
	
	if(mBox.x < 0 - ENTITY_WIDTH) {
		mPosX = LEVEL_WIDTH;
		mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	}
	
	if(mBox.x > LEVEL_WIDTH + COLL_BOX_OFFSET) {
		mPosX = 0 - ENTITY_WIDTH + COLL_BOX_OFFSET;
		mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	}
	
	
	// Move the MoveableEntity up or down
	mPosY += mVelY * timeStep;
	mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
	
	// If the MoveableEntity went too far up or down or touched a wall
	if(mBox.x < 0 || mBox.x + ENTITY_WIDTH / 2 > LEVEL_WIDTH || touchesWall(mBox, tiles)) {
		//move back
		mPosY -= mVelY * timeStep;
		mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
	}
}

void MoveableEntity::render() {
	// Show the MoveableEntity
	gDotTexture.render((int)mPosX, (int)mPosY);
}

