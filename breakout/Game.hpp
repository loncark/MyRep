#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#undef main
#include <iostream>
#include "Ball.hpp"
#include "Bar.hpp"
#include "Score.hpp"
#include "Level.hpp"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height);

	void handleEvents();
	void render();
	void update();
	void clean();

	bool isRunning() { return gameRunning; }
	int getWindowHeight() { return windowHeight; }
	int getWindowWidth() { return windowWidth; }
	void drawFrame(SDL_Renderer* renderer);

private:
	bool gameRunning = false;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int windowWidth = 0;
	int windowHeight = 0;

	bool leftKeyPressed = false;
	bool spaceKeyPressed = false;
	bool rightKeyPressed = false;

	SDL_Rect frame;		
	Ball ball;
	Bar bar;
	Score score;
	Level level;
};

#endif /* Game_hpp */