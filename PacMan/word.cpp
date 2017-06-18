#include "word.h"
#include "globals.h"
#include <vector>
#include <string>

using namespace std;

Word::Word(int x, int y, string newString) {
	posX = x;
	posY = y;
	
	theString = newString;
	
	for(int i = 0; i < theString.size(); i++) {
		letters.push_back((int)theString[i]);
	}
}

void Word::render() {
	for(int i = 0; i < letters.size(); i++) {
		// Show the letter
		if(letters[i] >= 65 && letters[i] <= 90) { // Letters
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[letters[i] - LETTER_OFFSET]);
		}
		else if(letters[i] <= 57 && letters[i] >= 48) { // Numbers
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[letters[i] - NUMBER_OFFSET]);
		}
		else if(letters[i] == 47) { // Slash
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[letters[i] - SLASH_OFFSET]);
		}
		else if(letters[i] == 46) { // Period
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[letters[i] - PERIOD_OFFSET]);
		}
		else if(letters[i] == 45) { // Dash
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[letters[i] - DASH_OFFSET]);
		}
		else if(letters[i] == 34) { // Quotes
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[letters[i] - QUOTES_OFFSET]);
		}
		else if(letters[i] == 33) { // Exclamation
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[letters[i] - EXCLAMATION_OFFSET]);
		}
		else if(letters[i] == 32) { // Space
			continue; // Iterate so the x-position increases
		}
		// @TODO Figure out how to get these working
		/*else if(letters[i] == 456) { // Copyright
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[COPYRIGHT_POSITION]);
		}
		else if(letters[i] == 789) { // Selector
			gSpriteSheetTexture.render(posX + (i * LETTER_WIDTH), posY, &gLetterClips[SELECTER_POSITION]);
		}*/
	}
}
