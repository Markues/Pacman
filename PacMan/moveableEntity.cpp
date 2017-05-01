#include "classes.h"

MoveableEntity::MoveableEntity(int startX, int startY) {
	// Initialize the collision box
	mBox.x = startX + COLL_BOX_OFFSET;
	mBox.y = startY + COLL_BOX_OFFSET;
	mBox.w = SPRITE_HITBOX_WIDTH;
	mBox.h = SPRITE_HITBOX_HEIGHT;
	
	mPosX = startX;
	mPosY = startY;
	// Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

SDL_Rect MoveableEntity::getBox() {
	return mBox;
}
