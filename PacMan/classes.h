#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <SDL2/SDL.h>
#include "constants.h"

using namespace std;

class GameTexture {
public:
	// Initializes variables
	GameTexture();
	
	// Deallocates memory
	~GameTexture();
	
	// Loads image at specified path
	bool loadFromFile(string path);
	
#ifdef _SDL_TTF_H
	// Creates image from font string
	bool loadFromRenderedText(string textureText, SDL_Color textColor);
#endif
	
	// Creates blank texture
	bool createBlank(int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);
	
	// Deallocates texture
	void free();
	
	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	
	// Set blending
	void setBlendMode(SDL_BlendMode blending);
	
	// Set alpha modulation
	void setAlpha( Uint8 alpha );
	
	// Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	// Set self as render target
	void setAsRenderTarget();
	
	// Gets image dimensions
	int getWidth();
	int getHeight();
	
	// Pixel manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	void copyPixels(void* pixels);
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);
	
private:
	// The actual hardware texture
	SDL_Texture* mTexture;
	void* mPixels;
	int mPitch;
	
	// Image dimensions
	int mWidth;
	int mHeight;
};

// The application timer
class GameTimer {
public:
	// Initializes variables
	GameTimer();
	
	// The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();
	
	// Gets the timer's time
	Uint32 getTicks();
	
	// Checks the status of the timer
	bool isStarted();
	bool isPaused();
	
private:
	// The clock time when the timer started
	Uint32 mStartTicks;
	
	// The ticks stored when the timer was paused
	Uint32 mPausedTicks;
	
	// The timer status
	bool mPaused;
	bool mStarted;
};

// Animation class
class Animation {
public:
	int maxFrames;
	bool oscillate;
	
	Animation();
	void animate(int timeStep);
	
private:
	int currentFrame;
	int frameInc;
	int frameRate; // Milliseconds
	long oldTime;
 
public:
	void setFrameRate(int rate);
	void setCurrentFrame(int frame);
	int getCurrentFrame();
};

// The tile
class Tile {
public:
	// Initializes position and type
	Tile(int x, int y, int tileType);
	
	// Shows the tile
	void render();
	
	// Get the tile type
	int getType();
	
	void setType(int typeVal);
	
	// Get the collision box
	SDL_Rect getBox();
	
private:
	// The attributes of the tile
	SDL_Rect mBox;
	
	// The tile type
	int mType;
};

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
	
protected:
	// Collision box
	SDL_Rect mBox;
	
	Animation animation;
	
	float mPosX, mPosY;
	float mVelX, mVelY;
};

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
	
	virtual void render(int frame);
	
	void renderSurrs();
	
private:
	void init();
	
	SDL_Rect renderBoxes[P_TOTAL_SPRITES];
	
	DIRECTION currentDirection;
	DIRECTION directionToTurn;
	SDL_Point turningPoint;
	
	Tile *surroundingTiles[4];
	
	PACMAN_ANIM_STATE animState;
	
	const int SPRITE_START_Y = 144;
	const int DEATH_ANIM_START_X = 64;
};

#endif
