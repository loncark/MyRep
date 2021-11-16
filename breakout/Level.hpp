#ifndef Level_hpp
#define Level_hpp

#include "SDL.h"
#include "BrickType.hpp"
#include <string>
using namespace std;

class Level
{
private:
	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	string backgroundTexture;

	char* Bricks;					//definira konfiguraciju cigli na nivou
	BrickType** brickSet;			//polje cigli koje mi treba za azuriranje stanja igre
	int levelNo;
	int nonEmpties;					//prati koliko ima nepraznih cigli
	bool newLevel;					//daje gameu do znanja je li promijenjen level; stvoren kako ne bih morala renderer provlacit kroz argumente funkcija
	bool gameWon;					

public:
	Level();
	~Level();

	float getBrickWidth(SDL_Rect* frame);
	float getBrickHeight(SDL_Rect * frame) { return getBrickWidth(frame) / 3.0f; }
	int getRowCount() { return rowCount; }
	int getColumnCount() { return columnCount; }
	int getRowSpacing() { return rowSpacing; }
	int getColumnSpacing() { return columnSpacing; }
	int getLevelNo() { return levelNo; }
	void setLevel(int n);
	bool getNewLevel() { return newLevel; }
	void reverseNewLevel() { newLevel = !newLevel; }
	bool getGameWon() { return gameWon; }
	void reverseGameWon() { gameWon = !gameWon; }

	void draw(SDL_Renderer* renderer, SDL_Rect *frame);
	void drawScreens(int n, SDL_Renderer* renderer);
	
	friend class Ball;
};

#endif /* Level_hpp */