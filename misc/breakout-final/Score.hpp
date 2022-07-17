#ifndef Score_hpp
#define Score_hpp

#include "SDL.h"
#include "SDL_ttf.h"

class Score
{
private:
	int levelNo;
	int livesLeft;
	int scoreCount;

public:
	Score();
	~Score();

	void draw(SDL_Renderer* renderer, SDL_Rect* frame);

	bool isGameOver();
	int getLevelNo() { return levelNo; }
	void setLevelNo(int n) { levelNo = n; }
	void takeLife() { --livesLeft; }
	void increaseScoreBy(int s) { scoreCount += s; }
	int getScore() { return scoreCount; }

	void reset() { livesLeft = 3; levelNo = 1; scoreCount = 0; }
};

#endif /* Score_hpp */