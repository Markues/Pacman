#include "ghost.h"
#include "globals.h"
#include "functions.h"
#include <math.h>

void Ghost::init(GHOST_TYPE type) {
	switch (type) {
		case BLINKY:
			animState = G_ANIM_LEFT;
			currentDirection = NONE;
			break;
		case INKY:
			animState = G_ANIM_UP;
			currentDirection = NONE;
			break;
		case PINKY:
			animState = G_ANIM_DOWN;
			currentDirection = NONE;
			break;
		case CLYDE:
			animState = G_ANIM_UP;
			currentDirection = NONE;
			break;
	}
	directionToTurn = NONE;
	
	animation.setFrameRate(G_ANIM_FRAMERATE);
	animation.maxFrames = 2;
	animation.oscillate = false;
	
	// Move anims
	for(int i = 0; i < G_SPRITES_PER_COL; i++) {
		for(int j = 0; j < G_SPRITES_PER_ROW; j++) {
			int currentTile = (i * G_SPRITES_PER_ROW) + j;
			renderBoxes[currentTile].x = j * SPRITE_WIDTH;
			renderBoxes[currentTile].y = G_SPRITE_START_Y + (type * SPRITE_HEIGHT) + (i * SPRITE_HEIGHT);
			renderBoxes[currentTile].w = SPRITE_WIDTH;
			renderBoxes[currentTile].h = SPRITE_HEIGHT;
		}
	}
	
	// Runaway and death anim
	for(int i = 0; i < G_SPRITES_PER_COL; i++) {
		for(int j = 0; j < G_SPRITES_PER_ROW; j++) {
			int currentTile = (i * G_SPRITES_PER_ROW) + j + 8;
			renderBoxes[currentTile].x = j * SPRITE_WIDTH;
			renderBoxes[currentTile].y = G_DEATH_ANIM_START_Y + (i * SPRITE_HEIGHT);
			renderBoxes[currentTile].w = SPRITE_WIDTH;
			renderBoxes[currentTile].h = SPRITE_HEIGHT;
		}
	}
}

void Ghost::update(Tile* tiles[], float timeStep) {
	// Move left or right
	mPosX += mVelX * timeStep;
	mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	// Move up or down
	mPosY += mVelY * timeStep;
	mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
	
	// Base case
	if(currentDirection == NONE && directionToTurn == NONE) {
		move(RIGHT);
	}
	
	if(touchesWall(mBox, tiles)) {
		switch (currentDirection) {
			case LEFT:
				// move back
				mPosX -= mVelX * timeStep;
				mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
				// Stop moving
				mVelX = 0;
				animState = G_ANIM_LEFT;
				break;
			case RIGHT:
				// move back
				mPosX -= mVelX * timeStep;
				mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
				// Stop moving
				mVelX = 0;
				animState = G_ANIM_RIGHT;
				break;
			case UP:
				// move back
				mPosY -= mVelY * timeStep;
				mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
				// Stop moving
				mVelY = 0;
				animState = G_ANIM_UP;
				break;
			case DOWN:
				// move back
				mPosY -= mVelY * timeStep;
				mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
				// Stop moving
				mVelY = 0;
				animState = G_ANIM_DOWN;
				break;
			case NONE:
				mVelX = 0;
				mVelY = 0;
				animState = G_ANIM_RUNAWAY;
				printf("ERROR: Somehow currentDirection is NONE");
				break;
		}
	}
	
	// Tunnel checks
	if(mPosX < -ENTITY_WIDTH) {
		mPosX = LEVEL_WIDTH;
		mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	}
	else if(mPosX > LEVEL_WIDTH) {
		mPosX = -ENTITY_WIDTH;
		mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	}
	
	surroundingTiles[LEFT] = getTileToLeft(tiles, mBox.x, mBox.y);
	surroundingTiles[RIGHT] = getTileToRight(tiles, mBox.x, mBox.y);
	surroundingTiles[UP] = getTileAbove(tiles, mBox.x, mBox.y);
	surroundingTiles[DOWN] = getTileBelow(tiles, mBox.x, mBox.y);
	
	// @TODO Convert to AI Check function
	//checkInput(tiles);
	
	if(directionToTurn != NONE) {
		turn();
	}
}

// @TODO Convert to AI Check function
/*void Ghost::checkInput(Tile* tiles[]) {
	const Uint8 *currentKeyState = SDL_GetKeyboardState(NULL);
	
	if(currentKeyState[SDL_SCANCODE_LEFT]) {
		checkDirection(LEFT, tiles);
	}
	else if(currentKeyState[SDL_SCANCODE_RIGHT]) {
		checkDirection(RIGHT, tiles);
	}
	else if(currentKeyState[SDL_SCANCODE_UP]) {
		// Up key only works while not transitioning via tunnel
		if(mBox.x >= 0 && mBox.x + ENTITY_WIDTH / 2 <= LEVEL_WIDTH) {
			checkDirection(UP, tiles);
		}
	}
	else if(currentKeyState[SDL_SCANCODE_DOWN]) {
		// Down key only works while not transitioning via tunnel
		if(mBox.x >= 0 && mBox.x + ENTITY_WIDTH / 2 <= LEVEL_WIDTH) {
			checkDirection(DOWN, tiles);
		}
	}
	else {
		// Forces user to hold key to turn
		directionToTurn = NONE;
	}
}*/

void Ghost::checkDirection(DIRECTION inputDirToTurn, Tile *tiles[]) {
	if(currentDirection == inputDirToTurn || directionToTurn == inputDirToTurn || !(surroundingTiles[inputDirToTurn]->getType() == Tile::TILE_EMPTY || surroundingTiles[inputDirToTurn]->getType() == Tile::TILE_FOOD || surroundingTiles[inputDirToTurn]->getType() == Tile::TILE_POWER)) {
		return;
	}
	
	if(areOpposites(currentDirection, inputDirToTurn)) {
		move(inputDirToTurn);
	}
	else {
		directionToTurn = inputDirToTurn;
		turningPoint.x = tiles[getCurrentTileIndex(mBox.x, mBox.y)]->getBox().x;
		turningPoint.y = tiles[getCurrentTileIndex(mBox.x, mBox.y)]->getBox().y;
	}
}

void Ghost::turn() {
	if(!(fuzzyEquals(mBox.x, turningPoint.x, 0) || !(fuzzyEquals(mBox.y, turningPoint.y, 0)))) {
		return;
	}
	
	mBox.x = turningPoint.x;
	mPosX = ((int)mBox.x) - COLL_BOX_OFFSET;
	mBox.y = turningPoint.y;
	mPosY = ((int)mBox.y) - COLL_BOX_OFFSET;
	
	move(directionToTurn);
	
	directionToTurn = NONE;
}

void Ghost::move(DIRECTION dirToMove) {
	switch (dirToMove) {
		case LEFT:
			mVelX = -ENTITY_VEL;
			mVelY = 0;
			animState = G_ANIM_LEFT;
			break;
		case RIGHT:
			mVelX = ENTITY_VEL;
			mVelY = 0;
			animState = G_ANIM_RIGHT;
			break;
		case UP:
			mVelY = -ENTITY_VEL;
			mVelX = 0;
			animState = G_ANIM_UP;
			break;
		case DOWN:
			mVelY = ENTITY_VEL;
			mVelX = 0;
			animState = G_ANIM_DOWN;
			break;
		case NONE:
			mVelX = 0;
			mVelY = 0;
			animState = G_ANIM_RUNAWAY;
			printf("ERROR: Somehow dirToMove is NONE");
			break;
	}
	
	// Update the currentDirection
	currentDirection = dirToMove;
}

void Ghost::render(int timeStep) {
	if(animState == G_ANIM_RUNAWAY_END) {
		animation.maxFrames = 4;
	}
	else {
		animation.maxFrames = 2;
	}
	
	animation.animate(timeStep);
	int currentFrame = animation.getCurrentFrame();
	
	switch (animState) {
		case G_ANIM_UP:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[currentFrame]);
			break;
		case G_ANIM_DOWN:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[currentFrame + 2]);
			break;
		case G_ANIM_LEFT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[currentFrame + 4]);
			break;
		case G_ANIM_RIGHT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[currentFrame + 6]);
			break;
		case G_ANIM_RUNAWAY:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[currentFrame + 8]);
			break;
		case G_ANIM_RUNAWAY_END:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[currentFrame + 8]);
			break;
		case G_ANIM_DEAD_UP:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[12]);
			break;
		case G_ANIM_DEAD_DOWN:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[13]);
			break;
		case G_ANIM_DEAD_LEFT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[14]);
			break;
		case G_ANIM_DEAD_RIGHT:
			gSpriteSheetTexture.render((int)mPosX, (int)mPosY, &renderBoxes[15]);
			break;
	}
}
