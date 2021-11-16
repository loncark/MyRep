#ifndef Ball_hpp
#define Ball_hpp

#include "SDL.h"
#include "Bar.hpp"
#include "BrickType.hpp"
#include "Level.hpp"
#include "Score.hpp"

class Ball
{
private:
	float ballPosX;
	float ballPosY;
	float ballRadius;

	float dt;			
	float ballVelX;
	float ballVelY;

public:
	Ball();
	~Ball();

	void increaseVel() { ballVelX *= 1.025f; ballVelY *= 1.025f; }
	void reset();

	bool checkCollisionWithWalls(SDL_Rect *frame);		//vraca true ako smo pogodili donju granicu
	void checkCollisionWithBar(Bar* bar);
	bool checkCollisionWithBricks(Level* level, SDL_Rect* frame, Score* score);

	void update(bool* spaceKeyPressed, SDL_Rect* frame, Bar *bar, Level* level, Score* score);
	bool move(Level* level, SDL_Rect* frame, Bar *bar, Score* score);			//vraca 1 ako se u brickSetu unistila zadnja cigla
	void draw(SDL_Renderer* renderer);
};

#endif /* Ball_hpp */