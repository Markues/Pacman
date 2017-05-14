#ifndef GHOST_H
#define GHOST_H

#include "moveableEntity.h"
#include "tile.h"

class Ghost: public MoveableEntity {
public:
	enum GHOST_TYPE {
		BLINKY = 0,
		INKY = 1,
		PINKY = 2,
		CLYDE = 3
	};
	
	Ghost(int startX, int startY, GHOST_TYPE type):
	MoveableEntity(startX, startY) {
		init(type);
	};
	
	void update(Tile *tiles[], float timeStep);
	
	// @TODO Convert to AI Check function
	//void checkInput(Tile *tiles[]);
	
	void checkDirection(DIRECTION inputDirToTurn, Tile *tiles[]);
	
	void turn();
	
	void move(DIRECTION dirToMove);
	
	virtual void render(int timeStep);
	
private:
	const static int G_SPRITE_START_Y = 64;
	const static int G_DEATH_ANIM_START_Y = 128;
	const static int G_ANIM_FRAMERATE = 50;
	const static int G_TOTAL_SPRITES = 16;
	const static int G_SPRITES_PER_ROW = 8;
	const static int G_SPRITES_PER_COL = 1;
	const static int G_SPRITES_PER_DIR = 2;
	const static int G_NUM_RUNAWAY_SPRITES = 2;
	const static int G_NUM_RUNAWAY_END_SPRITES = 4;
	const static int G_NUM_DEATH_SPRITES = 4;
	const static int G_ANIM_MOVE_FRAMES = 2;
	
	enum GHOST_ANIM_STATE {
		G_ANIM_UP = 0,
		G_ANIM_DOWN = 1,
		G_ANIM_LEFT = 2,
		G_ANIM_RIGHT = 3,
		G_ANIM_RUNAWAY = 4,
		G_ANIM_RUNAWAY_END = 5,
		G_ANIM_DEAD_UP = 6,
		G_ANIM_DEAD_DOWN = 7,
		G_ANIM_DEAD_LEFT = 8,
		G_ANIM_DEAD_RIGHT = 9
	};
	
	GHOST_ANIM_STATE animState;
	
	void init(GHOST_TYPE type);
	
	SDL_Rect renderBoxes[G_TOTAL_SPRITES];
	
	DIRECTION currentDirection;
	DIRECTION directionToTurn;
	SDL_Point turningPoint;
	
	Tile *surroundingTiles[4];
};

#endif
