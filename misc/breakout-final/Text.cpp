#include "Text.hpp"
#include <iostream>

Text::Text(SDL_Renderer* renderer, const string &fontPath, int fontSize, const string &message, const SDL_Color &color)
{
	textTexture = loadFont(renderer, fontPath, fontSize, message, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::draw(SDL_Renderer* renderer, int x, int y)
{
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	SDL_DestroyTexture(textTexture);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const string &fontPath,
	int fontSize, const string &message, const SDL_Color &color)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) std::cerr << "Font nije ucitan u Text::loadFont()-u.\n";
	
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (!textSurface) std::cerr << "textSurface nije stvoren u Text::loadFont()-u.\n";

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture) {
		std::cerr << "textTexture nije stvoren u Text::loadFont()-u.\n";
		std::cout << SDL_GetError();
	}
	
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	
	return textTexture;
}