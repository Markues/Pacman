#include "letter.h"
#include "globals.h"

Letter::Letter(int x, int y, int letterVal) {
	// Get the offsets
	mBox.x = x;
	mBox.y = y;
	
	// Set the border box
	mBox.w = LETTER_WIDTH;
	mBox.h = LETTER_HEIGHT;
	
	// Get the letter value
	letterValue = letterVal;
}

void Letter::render() {
	// Show the letter
	gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue]);
}

int Letter::getValue() {
	return letterValue;
}

void Letter::setValue(int letterVal) {
	letterValue = letterVal;
}

SDL_Rect Letter::getBox() {
	return mBox;
}
