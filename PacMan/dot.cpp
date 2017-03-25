#include "classes.h"
#include "globals.h"
#include "functions.h"

Dot::Dot()
{
	//Initialize the collision box
	mBox.x = 108;
	mBox.y = 208;
	mBox.w = DOT_WIDTH / 2;
	mBox.h = DOT_HEIGHT / 2;
	
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY += DOT_VEL; break;
			case SDLK_DOWN: mVelY -= DOT_VEL; break;
			case SDLK_LEFT: mVelX += DOT_VEL; break;
			case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}
	}
}

void Dot::move( Tile *tiles[] )
{
	//Move the dot left or right
	mBox.x += mVelX;
	
	//If the dot went too far to the left or right or touched a wall
	if(touchesWall(mBox, tiles))
	{
		//move back
		mBox.x -= mVelX;
	}
	
	if(mBox.x < 0 - DOT_WIDTH) {
		mBox.x = LEVEL_WIDTH;
	}
	
	if(mBox.x > LEVEL_WIDTH) {
		mBox.x = 0 - DOT_WIDTH;
	}
	
	//Move the dot up or down
	mBox.y += mVelY;
	
	//If the dot went too far up or down or touched a wall
	if(mBox.x < 0 || mBox.x + DOT_WIDTH / 2 > LEVEL_WIDTH || touchesWall(mBox, tiles))
	{
		//move back
		mBox.y -= mVelY;
	}
}

void Dot::render()
{
	//Show the dot
	gDotTexture.render(mBox.x - 4, mBox.y - 4);
}

