#include "classes.h"
#include "globals.h"
#include "functions.h"
#include <math.h>

void Pacman::init() {
	animState = P_STATIC_NEUTRAL;
	//prospectiveAnimState = P_STATIC_NEUTRAL;
	//lastKeyPressed = 'n';
	
	currentDirection = NONE;
	directionToTurn = NONE;
	
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

void Pacman::update(Tile* tiles[], float timeStep) {
	if(touchesWall(mBox, tiles)) {
		switch (currentDirection) {
			case LEFT:
				// move back
				mPosX -= mVelX * timeStep;
				mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
				// Stop moving
				mVelX = 0;
				animState = P_STATIC_LEFT;
				break;
			case RIGHT:
				// move back
				mPosX -= mVelX * timeStep;
				mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
				// Stop moving
				mVelX = 0;
				animState = P_STATIC_RIGHT;
				break;
			case UP:
				// move back
				mPosY -= mVelY * timeStep;
				mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
				// Stop moving
				mVelY = 0;
				animState = P_STATIC_UP;
				break;
			case DOWN:
				// move back
				mPosY -= mVelY * timeStep;
				mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
				// Stop moving
				mVelY = 0;
				animState = P_STATIC_DOWN;
				break;
			case NONE:
				mVelX = 0;
				mVelY = 0;
				animState = P_STATIC_NEUTRAL;
				printf("ERROR: Somehow currentDirection is NONE");
				break;
		}
	}
	// If Pacman went too far up or down (tunnel)
	else if(mBox.x < 0 || mBox.x + ENTITY_WIDTH / 2 > LEVEL_WIDTH) {
		// move back
		mPosY -= mVelY * timeStep;
		mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
		mVelY = 0;
		if(currentDirection == UP) {
			animState = P_STATIC_UP;
		}
		else if(currentDirection == DOWN) {
			animState = P_STATIC_DOWN;
		}
		
	}
	
	surroundingTiles[LEFT] = getTileToLeft(tiles, mBox.x, mBox.y);
	surroundingTiles[RIGHT] = getTileToRight(tiles, mBox.x, mBox.y);
	surroundingTiles[UP] = getTileAbove(tiles, mBox.x, mBox.y);
	surroundingTiles[DOWN] = getTileBelow(tiles, mBox.x, mBox.y);
	
	checkInput(tiles, timeStep);
	
	if(directionToTurn != NONE) {
		turn(tiles, timeStep);
	}
}

void Pacman::checkInput(Tile* tiles[], float timeStep) {
	const Uint8 *currentKeyState = SDL_GetKeyboardState(NULL);
	
	if(currentKeyState[SDL_SCANCODE_LEFT]) {
		checkDirection(LEFT, tiles, timeStep);
	}
	else if(currentKeyState[SDL_SCANCODE_RIGHT]) {
		checkDirection(RIGHT, tiles, timeStep);
	}
	else if(currentKeyState[SDL_SCANCODE_UP]) {
		checkDirection(UP, tiles, timeStep);
	}
	else if(currentKeyState[SDL_SCANCODE_DOWN]) {
		checkDirection(DOWN, tiles, timeStep);
	}
	else {
		// Forces user to hold key to turn
		directionToTurn = NONE;
	}
}

void Pacman::checkDirection(DIRECTION inputDirToTurn, Tile *tiles[], float timeStep) {
	if(directionToTurn == inputDirToTurn || surroundingTiles[inputDirToTurn]->getType() != TILE_EMPTY || surroundingTiles[inputDirToTurn]->getType() != TILE_FOOD || surroundingTiles[inputDirToTurn]->getType() != TILE_POWER) {
		return;
	}
	
	if(areOpposites(currentDirection, inputDirToTurn)) {
		move(inputDirToTurn, tiles, timeStep);
	}
	else {
		directionToTurn = inputDirToTurn;
		turningPoint.x = tiles[getCurrentTileIndex(mBox.x, mBox.y)]->getBox().x;
		turningPoint.y = tiles[getCurrentTileIndex(mBox.x, mBox.y)]->getBox().y;
	}
}

void Pacman::turn(Tile* tiles[], float timeStep) {
	if(!(fuzzyEquals(mBox.x, turningPoint.x, 1) || !(fuzzyEquals(mBox.y, turningPoint.y, 1)))) {
		return;
	}
	
	mPosX = turningPoint.x;
	mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	mPosY = turningPoint.y;
	mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
	
	move(directionToTurn, tiles, timeStep);
	
	directionToTurn = NONE;
}

void Pacman::move(DIRECTION dirToMove, Tile *tiles[], float timeStep) {
	switch (dirToMove) {
		case LEFT:
			mVelX = -ENTITY_VEL;
			animState = P_ANIM_LEFT;
			break;
		case RIGHT:
			mVelX = ENTITY_VEL;
			animState = P_ANIM_RIGHT;
			break;
		case UP:
			mVelY = -ENTITY_VEL;
			animState = P_ANIM_UP;
			break;
		case DOWN:
			mVelY = ENTITY_VEL;
			animState = P_ANIM_DOWN;
			break;
		case NONE:
			mVelX = 0;
			mVelY = 0;
			animState = P_STATIC_NEUTRAL;
			printf("ERROR: Somehow dirToMove is NONE");
			break;
	}
	
	// Move left or right
	mPosX += mVelX * timeStep;
	mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	// Move up or down
	mPosY += mVelY * timeStep;
	mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
	
	// Update the currentDirection
	currentDirection = dirToMove;
}

/*
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
*/
 
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
