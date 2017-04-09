#include "classes.h"
#include "globals.h"
#include "functions.h"
#include <math.h>

void Pacman::init() {
	animState = P_STATIC_NEUTRAL;
	
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
	// Move left or right
	mPosX += mVelX * timeStep;
	mBox.x = ((int)mPosX) + COLL_BOX_OFFSET;
	// Move up or down
	mPosY += mVelY * timeStep;
	mBox.y = ((int)mPosY) + COLL_BOX_OFFSET;
	
	// Base case
	if(currentDirection == NONE && directionToTurn == NONE) {
		move(RIGHT);
		printf("---------\n");
	}
	
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
	
	checkInput(tiles);
	
	if(directionToTurn != NONE) {
		printf("Update call turn, dir:%d\n", directionToTurn);
		turn();
	}
}

void Pacman::checkInput(Tile* tiles[]) {
	const Uint8 *currentKeyState = SDL_GetKeyboardState(NULL);
	
	if(currentKeyState[SDL_SCANCODE_LEFT]) {
		checkDirection(LEFT, tiles);
	}
	else if(currentKeyState[SDL_SCANCODE_RIGHT]) {
		checkDirection(RIGHT, tiles);
	}
	else if(currentKeyState[SDL_SCANCODE_UP]) {
		checkDirection(UP, tiles);
	}
	else if(currentKeyState[SDL_SCANCODE_DOWN]) {
		checkDirection(DOWN, tiles);
	}
	else {
		// Forces user to hold key to turn
		directionToTurn = NONE;
	}
}

void Pacman::checkDirection(DIRECTION inputDirToTurn, Tile *tiles[]) {
	printf("SurrBoxPos:%d,%d Dirs:%d,%d\n", surroundingTiles[inputDirToTurn]->getBox().x, surroundingTiles[inputDirToTurn]->getBox().y, directionToTurn, currentDirection);
	if(directionToTurn == inputDirToTurn || !(surroundingTiles[inputDirToTurn]->getType() == TILE_EMPTY || surroundingTiles[inputDirToTurn]->getType() == TILE_FOOD || surroundingTiles[inputDirToTurn]->getType() == TILE_POWER)) {
		printf("BAIL\n");
		return;
	}
	
	if(areOpposites(currentDirection, inputDirToTurn)) {
		printf("OPPS");
		move(inputDirToTurn);
	}
	else {
		directionToTurn = inputDirToTurn;
		turningPoint.x = tiles[getCurrentTileIndex(mBox.x, mBox.y)]->getBox().x;
		turningPoint.y = tiles[getCurrentTileIndex(mBox.x, mBox.y)]->getBox().y;
		printf("CD Dir:%d Curr:%d,%d Turn:%d,%d\n", directionToTurn, mBox.x, mBox.y, turningPoint.x, turningPoint.y);
	}
}

void Pacman::turn() {
	if(!(fuzzyEquals(mBox.x, turningPoint.x, 0) || !(fuzzyEquals(mBox.y, turningPoint.y, 0)))) {
		return;
	}
	
	mBox.x = turningPoint.x;
	mPosX = ((int)mBox.x) - COLL_BOX_OFFSET;
	mBox.y = turningPoint.y;
	mPosY = ((int)mBox.y) - COLL_BOX_OFFSET;
	
	printf("Turn Call Move\n");
	move(directionToTurn);
	
	//directionToTurn = NONE;
	printf("TURN Pos:%d,%d\n", mBox.x, mBox.y);
}

void Pacman::move(DIRECTION dirToMove) {
	printf("Please move:%d\n", dirToMove);
	switch (dirToMove) {
		case LEFT:
			mVelX = -ENTITY_VEL;
			mVelY = 0;
			animState = P_ANIM_LEFT;
			break;
		case RIGHT:
			mVelX = ENTITY_VEL;
			mVelY = 0;
			animState = P_ANIM_RIGHT;
			break;
		case UP:
			mVelY = -ENTITY_VEL;
			mVelX = 0;
			animState = P_ANIM_UP;
			break;
		case DOWN:
			mVelY = ENTITY_VEL;
			mVelX = 0;
			animState = P_ANIM_DOWN;
			break;
		case NONE:
			mVelX = 0;
			mVelY = 0;
			animState = P_STATIC_NEUTRAL;
			printf("ERROR: Somehow dirToMove is NONE");
			break;
	}
	
	// Update the currentDirection
	currentDirection = dirToMove;
	
	printf("Move Vel:%f,%f Dir:%d\n", mVelX, mVelY, currentDirection);
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

void Pacman::renderSurrs() {
	 SDL_Rect temp;
	 SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	 temp.x = surroundingTiles[LEFT]->getBox().x;
	 temp.y = surroundingTiles[LEFT]->getBox().y;
	 temp.w = surroundingTiles[LEFT]->getBox().w;
	 temp.h = surroundingTiles[LEFT]->getBox().h;
	 SDL_RenderDrawRect(gRenderer, &temp);
	 temp.x = surroundingTiles[RIGHT]->getBox().x;
	 temp.y = surroundingTiles[RIGHT]->getBox().y;
	 temp.w = surroundingTiles[RIGHT]->getBox().w;
	 temp.h = surroundingTiles[RIGHT]->getBox().h;
	 SDL_RenderDrawRect(gRenderer, &temp);
	 temp.x = surroundingTiles[UP]->getBox().x;
	 temp.y = surroundingTiles[UP]->getBox().y;
	 temp.w = surroundingTiles[UP]->getBox().w;
	 temp.h = surroundingTiles[UP]->getBox().h;
	 SDL_RenderDrawRect(gRenderer, &temp);
	 temp.x = surroundingTiles[DOWN]->getBox().x;
	 temp.y = surroundingTiles[DOWN]->getBox().y;
	 temp.w = surroundingTiles[DOWN]->getBox().w;
	 temp.h = surroundingTiles[DOWN]->getBox().h;
	 SDL_RenderDrawRect(gRenderer, &temp);
}
