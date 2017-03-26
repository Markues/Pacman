#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <SDL2/SDL.h>
#include "constants.h"

using namespace std;

class LTexture {
public:
	// Initializes variables
	LTexture();
	
	// Deallocates memory
	~LTexture();
	
	// Loads image at specified path
	bool loadFromFile(string path);
	
#ifdef _SDL_TTF_H
	// Creates image from font string
	bool loadFromRenderedText(string textureText, SDL_Color textColor);
#endif
	
	// Deallocates texture
	void free();
	
	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	
	// Set blending
	void setBlendMode(SDL_BlendMode blending);
	
	// Set alpha modulation
	void setAlpha(Uint8 alpha);
	
	// Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	// Gets image dimensions
	int getWidth();
	int getHeight();
	
private:
	// The actual hardware texture
	SDL_Texture* mTexture;
	
	// Image dimensions
	int mWidth;
	int mHeight;
};

//The tile
class Tile {
public:
	//Initializes position and type
	Tile( int x, int y, int tileType );
	
	//Shows the tile
	void render();
	
	//Get the tile type
	int getType();
	
	//Get the collision box
	SDL_Rect getBox();
	
private:
	//The attributes of the tile
	SDL_Rect mBox;
	
	//The tile type
	int mType;
};

//The dot that will move around on the screen
class Dot {
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 16;
	static const int DOT_HEIGHT = 16;
	
	static const int COLL_BOX_OFFSET = 4;
	
	//Maximum axis velocity of the dot
	static const int DOT_VEL = 2;
	
	//Initializes the variables
	Dot(int startX, int startY);
	
	//Takes key presses and adjusts the dot's velocity
	void handleEvent( SDL_Event& e );
	
	//Moves the dot and check collision against tiles
	void move( Tile *tiles[] );
	
	//Shows the dot on the screen
	void render();
	
private:
	//Collision box of the dot
	SDL_Rect mBox;
	
	//The velocity of the dot
	int mVelX, mVelY;
};

#endif
