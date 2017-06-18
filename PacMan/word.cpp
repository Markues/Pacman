#include "word.h"
#include "globals.h"
#include <vector>
#include <string>

using namespace std;

string fillWithSpaces(string toFill) {
	int stringLength = (int)toFill.length();
	
	for(int i = 0; i < 7 - stringLength; i++) {
		toFill.insert(0, " ");
	}
	
	return toFill;
}

Word::Word() {
	posX = 0;
	posY = 0;
	
	theString = "";
}

Word::Word(int newScore) {
	posX = 0;
	posY = 8;
	
	theString = fillWithSpaces(newScore <= 0 ? "00" :to_string(newScore));
	for(int i = 0; i < theString.size(); i++) {
		letters.push_back((int)theString[i]);
	}
}

Word::Word(int x, int y, string newString) {
	posX = x;
	posY = y;
	
	theString = newString;
	
	for(int i = 0; i < theString.size(); i++) {
		letters.push_back((int)theString[i]);
	}
}

void Word::setWord(string newString) {
	theString = newString;
	
	letters.clear();
	for(int i = 0; i < theString.size(); i++) {
		letters.push_back((int)theString[i]);
	}
}

void Word::setWord(char newString[]) {
	setWord(string(newString));
}

void Word::setScore(int newScore) {
	setWord(fillWithSpaces(newScore <= 0 ? "00" :to_string(newScore)));
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
