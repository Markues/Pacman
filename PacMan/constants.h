#ifndef CONSTANTS_H
#define CONSTANTS_H

// Screen dimension constants
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

// The dimensions of the level
const int LEVEL_WIDTH = 224;
const int LEVEL_HEIGHT = 288;

const int SPRITE_WIDTH = 16;
const int SPRITE_HEIGHT = 16;
const int SPRITE_HITBOX_WIDTH = 8;
const int SPRITE_HITBOX_HEIGHT = 8;

enum DIRECTION {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	NONE = 4
};

enum GAMESTATE {
	LEVELSTART = 0,
	PLAYING = 1,
	PAUSED = 2,
	DEATH = 3,
	GAMEOVER = 4,
	LEVELCOMPLETE = 5
};

#endif
