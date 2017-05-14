#ifndef ANIMATION_H
#define ANIMATION_H

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

#endif
