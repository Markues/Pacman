#include "classes.h"
#include "globals.h"
#include "functions.h"

void Pacman::init() {
	animState = P_STATIC_NEUTRAL;
	
	// Move anims
	for(int i = 0; i < P_SPRITES_PER_ROW; i++) {
		for(int j = 0; j < P_SPRITES_PER_COL; j++) {
			int currentTile = (i * P_SPRITES_PER_COL) + j;
			renderBoxes[currentTile].x = i * SPRITE_WIDTH;
			renderBoxes[currentTile].y = SPRITE_START_Y + (j * SPRITE_HEIGHT);
			renderBoxes[currentTile].w = SPRITE_WIDTH;
			renderBoxes[currentTile].h = SPRITE_HEIGHT;
			printf("%d %d %d\n", currentTile, renderBoxes[currentTile].x, renderBoxes[currentTile].y);
		}
	}
	
	// Death anim
	for(int i = 0; i < P_SPRITES_PER_COL; i++) {
		for(int j = 0; j < P_SPRITES_PER_ROW; j++) {
			int currentTile = (i * P_SPRITES_PER_ROW) + j + 12;
			renderBoxes[currentTile].x = DEATH_ANIM_START_X + (j * SPRITE_WIDTH);
			renderBoxes[currentTile].y = SPRITE_START_Y + (i * SPRITE_HEIGHT);
			renderBoxes[currentTile].w = SPRITE_WIDTH;
			renderBoxes[currentTile].h = SPRITE_HEIGHT;
			printf("%d %d %d\n", currentTile, renderBoxes[currentTile].x, renderBoxes[currentTile].y);
		}
	}
}

void Pacman::handleEvent(SDL_Event& e) {
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP:
				mVelY = -ENTITY_VEL;
				break;
			case SDLK_DOWN:
				mVelY = ENTITY_VEL;
				break;
			case SDLK_LEFT:
				mVelX = -ENTITY_VEL;
				break;
			case SDLK_RIGHT:
				mVelX = ENTITY_VEL;
				break;
		}
	}
}

void Pacman::move(Tile *tiles[], float timeStep) {
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	
	// Move the MoveableEntity left or right
	mPosX += mVelX * timeStep;
	mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	
	// If the MoveableEntity went too far to the left or right or touched a wall
	if(touchesWall(mBox, tiles)) {
		// move back
		mPosX -= mVelX * timeStep;
		mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
		if (!(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT])){
			mVelX = 0;
		}
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
		if (!(keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN])){
			mVelY = 0;
		}
	}
}

void Pacman::render() {
	switch (animState) {
		case P_STATIC_NEUTRAL:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[0]);
			break;
		case P_ANIM_RIGHT:
			break;
		case P_STATIC_RIGHT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[1]);
			break;
		case P_ANIM_LEFT:
			break;
		case P_STATIC_LEFT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[4]);
			break;
		case P_ANIM_UP:
			break;
		case P_STATIC_UP:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[7]);
			break;
		case P_ANIM_DOWN:
			break;
		case P_STATIC_DOWN:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[10]);
			break;
		case P_ANIM_DEATH:
			break;
	}
}
