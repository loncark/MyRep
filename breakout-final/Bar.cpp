#include "Bar.hpp"
#include <iostream>

Bar::Bar() 
{
	barPosX = 0;
	barPosY = 0;
	barHeight = 0;
	barWidth = 0;
	barTexture = nullptr;
}

void Bar::reset()
{
	barPosX = 0;
	barPosY = 0;
	barHeight = 0;
	barWidth = 0;
}

Bar::~Bar() 
{
	if (barTexture)
	{
		SDL_DestroyTexture(barTexture);
		barTexture = nullptr;
	}
}

void Bar::update(bool leftKeyPressed, bool rightKeyPressed, SDL_Rect* frame)
{
	if (leftKeyPressed) { this->move(-step, frame); }
	if (rightKeyPressed) { this->move(step, frame); }
}

void Bar::update2(int mouseX, SDL_Rect* frame)
{
	this->move2(mouseX, frame);
}

void Bar::move(float step, SDL_Rect *frame)
{
	float temp = barPosX + barWidth/2.0f + step;
	if (temp < frame->x + frame->w + 1.0f && temp-barWidth > frame->x - 1.0f) 
		{ barPosX += step; } 
}

void Bar::move2(int mouseX, SDL_Rect* frame)
{
	float temp = mouseX + barWidth / 2.0f;
	if (temp < frame->x + frame->w + 1.0f && temp-barWidth > frame->x -1.0f)
		{ barPosX = mouseX; }
}

void Bar::draw(SDL_Renderer* renderer, SDL_Rect *frame)		//position tocka je na polovici donjeg brida bara
{
	if (barPosX == 0)
		{
			barPosX = frame->x + frame->w / 2.0f;
			barPosY = frame->y + frame->h - 10;
			barWidth = frame->w / 5.0f;
			barHeight = barWidth / 10.0f;
		}

	static SDL_Rect pad;
	pad.x = barPosX - barWidth / 2.0f;
	pad.y = barPosY - barHeight;
	pad.h = this->barHeight;
	pad.w = this->barWidth;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &pad);

	if (!barTexture) loadTexture(renderer);
	else SDL_RenderCopy(renderer, barTexture, nullptr, &pad);
}

void Bar::loadTexture(SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load("x64/Debug/assets/bar.jpg");
	if (!surface) std::cerr << "Ball::loadTexture() nije stvorio surface.\n";

	barTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!barTexture) std::cerr << "Ball::loadTexture() nije stvorio ballTexture.\n";

	SDL_FreeSurface(surface);
	surface = nullptr;
}