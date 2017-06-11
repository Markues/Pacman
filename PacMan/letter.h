#ifndef LETTER_H
#define LETTER_H

#include <SDL2/SDL.h>
#include "constants.h"

class Letter {
public:
	const static int LETTER_WIDTH = 8;
	const static int LETTER_HEIGHT = 8;
	
	const static int LETTERS_PER_ROW = 16;
	const static int NUM_LETTER_ROWS = 3;
	const static int TOTAL_LETTER_SPRITES = 43;
	
	// Initializes position and value
	Letter(int x, int y, int letterVal);
	
	// Shows the letter
	void render();
	
	// Get the letter value
	int getValue();
	
	void setValue(int letterVal);
	
	// Get the border box
	SDL_Rect getBox();
	
protected:
	SDL_Rect mBox;
	
	// The letter value
	int letterValue;
};

#endif
