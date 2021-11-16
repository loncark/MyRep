#ifndef Bar_hpp
#define Bar_hpp

#include "SDL.h"

class Bar
{
private:
	float barPosX;
	float barPosY;
	float barHeight;
	float barWidth;
	float step = 30;

public:
	Bar();
	~Bar();
	
	void reset();
	void update(bool leftKeyPressed, bool rightKeyPressed, SDL_Rect* frame);
	void move(float step, SDL_Rect* frame);
	void draw(SDL_Renderer *renderer, SDL_Rect *frame);
	
	float getPosX() { return barPosX; }
	float getPosY() { return barPosY; }
	float getHeight() { return barHeight; }
	float getWidth() { return barWidth; }
};

#endif /* Bar_hpp */