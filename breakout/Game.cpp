#include "Game.hpp"
#include <iostream>
#include "Text.hpp"
using namespace std;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height)
	{
		this->windowHeight = height;
		this->windowWidth = width; 
		int flags = 0;
		
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			cout << "Prosao SDL_Init" << endl;

			window = SDL_CreateWindow(title, xpos, ypos, this->windowWidth, this->windowHeight, flags);
			if (window) cout << "Window stvoren" << endl;

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				cout << "Renderer stvoren" << endl;
			}
			gameRunning = true;
		}
		else { gameRunning = false; }

		if (TTF_Init() == -1) std::cout << "TTF nije ucitan.\n";

		level.setLevel(1);
	}

void Game::handleEvents()		
{
	leftKeyPressed = false;
	rightKeyPressed = false;

	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) { gameRunning = false; }
	 else if (event.type == SDL_KEYDOWN) 
		{ 
			if (event.key.keysym.sym == SDLK_LEFT) { leftKeyPressed = true; }
			if (event.key.keysym.sym == SDLK_RIGHT) { rightKeyPressed = true; }
			if (event.key.keysym.sym == SDLK_SPACE) { spaceKeyPressed = true; }
		}
}

void Game::drawFrame(SDL_Renderer* renderer)
{
	frame.x = 5 * this->getWindowHeight() / 80;
	frame.y = frame.x;
	frame.h = this->getWindowHeight() - 5 * frame.x;
	frame.w = this->getWindowWidth() - 2 * frame.x;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &frame);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawLine(renderer, frame.x, frame.y + frame.h - 1, frame.x + frame.w, frame.y + frame.h - 1); 
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	if (level.getNewLevel() == true)
		{
			level.reverseNewLevel();
			level.drawScreens(level.getLevelNo(), renderer);
		}

	//stuff to render
	drawFrame(renderer); 
	ball.draw(renderer);
	bar.draw(renderer, &frame);
	level.draw(renderer, &frame);
	score.draw(renderer, &frame);

	SDL_RenderPresent(renderer);
}

void Game::update()
{
	bar.update(leftKeyPressed, rightKeyPressed, &frame);
	ball.update(&spaceKeyPressed, &frame, &bar, &level, &score);
	if (level.getGameWon() == true)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			Text exit(renderer, "assets/font.ttf", 90,
				"You won.", { 255, 255, 255, 255 });

			exit.draw(renderer, windowWidth/4, windowHeight/2-40);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000);

			gameRunning = false;
		}
	
	if (score.isGameOver() == true) 
		{ 
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			Text exit(renderer, "assets/font.ttf", 90,
				"You lost.", { 255, 255, 255, 255 });

			exit.draw(renderer, windowWidth / 4, windowHeight/2 - 40);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000);

			gameRunning = false;
		}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	cout << "Igra terminirana." << endl;
}