#include "Bar.hpp"
#include <iostream>

Bar::Bar() 
{
	barPosX = 0;
	barPosY = 0;
	barHeight = 0;
	barWidth = 0;
}

void Bar::reset()
{
	barPosX = 0;
	barPosY = 0;
	barHeight = 0;
	barWidth = 0;
}

Bar::~Bar() {}

void Bar::update(bool leftKeyPressed, bool rightKeyPressed, SDL_Rect* frame)
{
	if (leftKeyPressed) { this->move(-step, frame); }
	if (rightKeyPressed) { this->move(step, frame); }
}

void Bar::move(float step, SDL_Rect *frame)
{
	float temp = barPosX + barWidth/2.0f + step;
	if (temp<frame->x+frame->w+1.0f && temp-barWidth>frame->x-1.0f) { barPosX += step; } 
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
}