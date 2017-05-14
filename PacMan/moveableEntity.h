#ifndef MOVEABLEENTITY_H
#define MOVEABLEENTITY_H

#include <SDL2/SDL.h>
#include "animation.h"
#include "constants.h"

class MoveableEntity {
public:
	static const int ENTITY_WIDTH = 16;
	static const int ENTITY_HEIGHT = 16;
	
	static const int COLL_BOX_OFFSET = 4;
	
	// Maximum axis velocity
	static const int ENTITY_VEL = 60;
	
	// Initializes the variables
	MoveableEntity(int startX, int startY);
	
	// Shows the entity on the screen
	virtual void render(int timeStep) = 0;
	
	// Get the collision box
	SDL_Rect getBox();
	
protected:
	// Collision box
	SDL_Rect mBox;
	
	Animation animation;
	
	float mPosX, mPosY;
	float mVelX, mVelY;
};

#endif
