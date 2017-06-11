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
	if(letterValue >= 65 && letterValue <= 90) { // Letters
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue - LETTER_OFFSET]);
	}
	else if(letterValue <= 57 && letterValue >= 48) { // Numbers
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue - NUMBER_OFFSET]);
	}
	else if(letterValue == 47) { // Slash
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue - SLASH_OFFSET]);
	}
	else if(letterValue == 46) { // Period
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue - PERIOD_OFFSET]);
	}
	else if(letterValue == 45) { // Dash
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue - DASH_OFFSET]);
	}
	else if(letterValue == 34) { // Quotes
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue - QUOTES_OFFSET]);
	}
	else if(letterValue == 33) { // Exclamation
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[letterValue - EXCLAMATION_OFFSET]);
	}
	else if(letterValue == 456) { // Copyright
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[COPYRIGHT_POSITION]);
	}
	else if(letterValue == 789) { // Selector
		gSpriteSheetTexture.render(mBox.x, mBox.y, &gLetterClips[SELECTER_POSITION]);
	}
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
