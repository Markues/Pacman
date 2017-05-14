#ifndef PACMAN_H
#define PACMAN_H

#include "moveableEntity.h"
#include "tile.h"

class Pacman: public MoveableEntity {
public:
	Pacman(int startX, int startY):
	MoveableEntity(startX, startY) {
		init();
	};
	
	void update(Tile *tiles[], float timeStep);
	
	void checkInput(Tile *tiles[]);
	
	void checkDirection(DIRECTION inputDirToTurn, Tile *tiles[]);
	
	void turn();
	
	void move(DIRECTION dirToMove);
	
	virtual void render(int timeStep);
	
private:
	const static int P_SPRITE_START_Y = 144;
	const static int P_DEATH_ANIM_START_X = 64;
	const static int P_ANIM_FRAMERATE = 50;
	const static int P_TOTAL_SPRITES = 24;
	const static int P_SPRITES_PER_ROW = 4;
	const static int P_SPRITES_PER_COL = 3;
	const static int P_SPRITES_PER_DIR = 3;
	const static int P_NUM_DEATH_SPRITES = 12;
	const static int P_ANIM_MOVE_FRAMES = 3;
	const static int P_ANIM_DEATH_FRAMES = 12;
	
	enum PACMAN_ANIM_STATE {
		P_STATIC_NEUTRAL = 0,
		P_ANIM_RIGHT = 1,
		P_STATIC_RIGHT = 2,
		P_ANIM_LEFT = 3,
		P_STATIC_LEFT = 4,
		P_ANIM_UP = 5,
		P_STATIC_UP = 6,
		P_ANIM_DOWN = 7,
		P_STATIC_DOWN = 8,
		P_ANIM_DEATH = 9
	};
	
	PACMAN_ANIM_STATE animState;
	
	void init();
	
	SDL_Rect renderBoxes[P_TOTAL_SPRITES];
	
	DIRECTION currentDirection;
	DIRECTION directionToTurn;
	SDL_Point turningPoint;
	
	Tile *surroundingTiles[4];
};

#endif
