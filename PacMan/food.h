#ifndef FOOD_H
#define FOOD_H

#include "tile.h"
#include "pacman.h"

class Food: private Tile {
public:
	const static int TOTAL_FOOD = 244;
	
	Food(int x, int y, int type):
	Tile(x, y, type) {
		init();
	};
	
	void update(Pacman* pacman);
	
	void render(int timeStep);
	
private:
	const static int FOOD_HITBOX_OFFSET_H = TILE_WIDTH / 2;
	const static int FOOD_HITBOX_OFFSET_V = TILE_HEIGHT / 2;
	const static int FOOD_HITBOX_WIDTH = 1;
	const static int FOOD_HITBOX_HEIGHT = 1;
	
	void init();
	
	int mPosX;
	int mPosY;
	
	Animation animation;
	
	bool isEaten;
	
	const int F_ANIM_FRAMERATE = 200;
};

#endif
