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
	
	const static int LETTER_OFFSET = 65;
	const static int EXCLAMATION_OFFSET = 7;
	const static int COPYRIGHT_POSITION = 27;
	const static int NUMBER_OFFSET = 20;
	const static int SLASH_OFFSET = 9;
	const static int DASH_OFFSET = 6;
	const static int PERIOD_OFFSET = 6;
	const static int QUOTES_OFFSET = -7;
	const static int SELECTER_POSITION = 42;
	
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
