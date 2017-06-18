#include "food.h"
#include "globals.h"
#include "functions.h"

void Food::init() {
	animation.setFrameRate(F_ANIM_FRAMERATE);
	animation.maxFrames = 2;
	
	isEaten = false;
	
	mPosX = mBox.x;
	mPosY = mBox.y;
	
	mBox.x = mBox.x + FOOD_HITBOX_OFFSET_H;
	mBox.y = mBox.y + FOOD_HITBOX_OFFSET_V;
	mBox.w = FOOD_HITBOX_WIDTH;
	mBox.h = FOOD_HITBOX_HEIGHT;
}

void Food::update(Pacman* pacman) {
	if(checkCollision(mBox, pacman->getBox()) && isEaten == false) {
		isEaten = true;
		
		score += 10;
		wordArray[1].setScore(score);
		
		if(playFoodSoundA) {
			Mix_PlayChannel(-1, gEatA, 0);
			playFoodSoundA = !playFoodSoundA;
			return;
		}
		else {
			Mix_PlayChannel(-1, gEatB, 0);
			playFoodSoundA = !playFoodSoundA;
			return;
		}
	}
}

void Food::render(int timeStep) {
	animation.animate(timeStep);
	int currentFrame = animation.getCurrentFrame();
	
	if(!isEaten) {
		if(getType() == TILE_POWER) {
			if(currentFrame == 0) {
				gSpriteSheetTexture.render(mPosX, mPosY, &gTileClips[mType]);
			}
			else {
				gSpriteSheetTexture.render(mPosX, mPosY, &gTileClips[TILE_EMPTY]);
			}
		}
		else {
			gSpriteSheetTexture.render(mPosX, mPosY, &gTileClips[mType]);
		}
	}
}
