#ifndef Text_hpp
#define Text_hpp

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;

class Text
{
private:
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect;

public:
	Text(SDL_Renderer* renderer, const string &fontPath, int fontSize, const string &message, const SDL_Color &color);
	
	void draw(SDL_Renderer* renderer, int x, int y);

	static SDL_Texture *loadFont(SDL_Renderer* renderer, const string &fontPath, 
		int fontSize, const string &message, const SDL_Color &color);
};

#endif /* Text_hpp */