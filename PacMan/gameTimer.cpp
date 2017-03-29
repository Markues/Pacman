#include "classes.h"

GameTimer::GameTimer() {
	// Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;
	
	mPaused = false;
	mStarted = false;
}

void GameTimer::start() {
	// Start the timer
	mStarted = true;
	
	// Unpause the timer
	mPaused = false;
	
	// Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void GameTimer::stop() {
	// Stop the timer
	mStarted = false;
	
	// Unpause the timer
	mPaused = false;
	
	// Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void GameTimer::pause() {
	// If the timer is running and isn't already paused
	if(mStarted && !mPaused) {
		// Pause the timer
		mPaused = true;
		
		// Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void GameTimer::unpause() {
	// If the timer is running and paused
	if(mStarted && mPaused) {
		// Unpause the timer
		mPaused = false;
		
		// Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		
		// Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 GameTimer::getTicks() {
	// The actual timer time
	Uint32 time = 0;
	
	// If the timer is running
	if(mStarted) {
		// If the timer is paused
		if(mPaused) {
			// Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else {
			// Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	
	return time;
}

bool GameTimer::isStarted() {
	// Timer is running and paused or unpaused
	return mStarted;
}

bool GameTimer::isPaused() {
	// Timer is running and paused
	return mPaused && mStarted;
}