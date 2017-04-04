#include "classes.h"
#include "globals.h"
#include "functions.h"

void Pacman::init() {
	animState = P_STATIC_NEUTRAL;
	prospectiveAnimState = P_STATIC_NEUTRAL;
	lastKeyPressed = 'n';
	
	// Move anims
	for(int i = 0; i < P_SPRITES_PER_ROW; i++) {
		for(int j = 0; j < P_SPRITES_PER_COL; j++) {
			int currentTile = (i * P_SPRITES_PER_COL) + j;
			renderBoxes[currentTile].x = i * SPRITE_WIDTH;
			renderBoxes[currentTile].y = SPRITE_START_Y + (j * SPRITE_HEIGHT);
			renderBoxes[currentTile].w = SPRITE_WIDTH;
			renderBoxes[currentTile].h = SPRITE_HEIGHT;
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
		}
	}
}

void Pacman::handleEvent(SDL_Event& e) {
	if(e.type == SDL_KEYDOWN) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP:
				mVelY = -ENTITY_VEL;
				prospectiveAnimState = P_ANIM_UP;
				lastKeyPressed = 'u';
				break;
			case SDLK_DOWN:
				mVelY = ENTITY_VEL;
				prospectiveAnimState = P_ANIM_DOWN;
				lastKeyPressed = 'd';
				break;
			case SDLK_LEFT:
				mVelX = -ENTITY_VEL;
				prospectiveAnimState = P_ANIM_LEFT;
				lastKeyPressed = 'l';
				break;
			case SDLK_RIGHT:
				mVelX = ENTITY_VEL;
				prospectiveAnimState = P_ANIM_RIGHT;
				lastKeyPressed = 'r';
				break;
		}
	}
}

void Pacman::move(Tile *tiles[], float timeStep) {
	// Move left or right
	mPosX += mVelX * timeStep;
	mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	// Move up or down
	mPosY += mVelY * timeStep;
	mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
	
	if(touchesWall(mBox, tiles)) {
		// move back
		mPosX -= mVelX * timeStep;
		mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
		mPosY -= mVelY * timeStep;
		mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
		
		switch (lastKeyPressed) {
			case 'r':
			case 'l':
				mVelX = 0;
				// If Pacman is still moving on the Y-axis, dont change the animation
				if(mVelY != 0) {
					prospectiveAnimState = animState;
				}
				break;
			case 'u':
			case 'd':
				mVelY = 0;
				// If Pacman is still moving on the X-axis, dont change the animation
				if(mVelX != 0) {
					prospectiveAnimState = animState;
				}
				break;
		}
	}
	// If Pacman went too far up or down
	else if(mBox.x < 0 || mBox.x + ENTITY_WIDTH / 2 > LEVEL_WIDTH) {
		// move back
		mPosY -= mVelY * timeStep;
		mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
		mVelY = 0;
	}
	else {
		animState = prospectiveAnimState;
	}
	
	// If Pacman isnt moving
	if(mVelX == 0 && mVelY == 0) {
		switch (lastKeyPressed) {
			case 'r':
				animState = P_STATIC_RIGHT;
				break;
			case 'l':
				animState = P_STATIC_LEFT;
				break;
			case 'u':
				animState = P_STATIC_UP;
				break;
			case 'd':
				animState = P_STATIC_DOWN;
				break;
		}
	}
}

void Pacman::render(int frame) {
	switch (animState) {
		case P_STATIC_NEUTRAL:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[0]);
			break;
		case P_ANIM_RIGHT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[frame / 3]);
			break;
		case P_STATIC_RIGHT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[1]);
			break;
		case P_ANIM_LEFT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[(frame / 3) + 3]);
			break;
		case P_STATIC_LEFT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[4]);
			break;
		case P_ANIM_UP:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[(frame / 3) + 6]);
			break;
		case P_STATIC_UP:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[7]);
			break;
		case P_ANIM_DOWN:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[(frame / 3) + 9]);
			break;
		case P_STATIC_DOWN:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[10]);
			break;
		case P_ANIM_DEATH:
			break;
	}
}
