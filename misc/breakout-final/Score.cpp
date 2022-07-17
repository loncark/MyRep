#include "Score.hpp"
#include "Text.hpp"

Score::Score() 
{
	levelNo = 1;
	livesLeft = 3;
	scoreCount = 0;
}

Score::~Score() {}

bool Score::isGameOver()
{
	if (livesLeft == -1) return true; return false;
}

void Score::draw(SDL_Renderer* renderer, SDL_Rect *frame)
{
	int smallTextFont = 40, largeTextFont = 60;

	Text score(renderer, "x64/Debug/assets/font.ttf", largeTextFont, 
		"Score: "+to_string(scoreCount) , { 255, 255, 255, 255 });
	Text level(renderer, "x64/Debug/assets/font.ttf", smallTextFont, 
		"Level: "+to_string(levelNo), { 255, 255, 255, 255 });
	Text lives(renderer, "x64/Debug/assets/font.ttf", smallTextFont, 
		"Lives: "+to_string(livesLeft), { 255, 255, 255, 255 });

	int x, y;
	x = frame->x+50;
	y = frame->y + frame->h + 50;
	lives.draw(renderer, x, y);

	y +=  (smallTextFont + 20);
	level.draw(renderer, x, y);

	x += 250;
	y = frame->y + frame->h + 75;
	score.draw(renderer, x, y);

}