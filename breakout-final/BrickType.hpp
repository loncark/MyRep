#ifndef BrickType_hpp
#define BrickType_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class BrickType
{
private:
	char id;
	int hitPoints;		//koliko je puta potrebno pogoditi ciglu
	int breakScore;		//bodovi za razbijanje
	
	string texturePath;
	string hitSound;
	string breakSound;
	
	SDL_Surface* surface;
	SDL_Texture* texture;
	
public:
	BrickType();
	~BrickType();

	char getId() { return id; }
	int getHitPoints() { return hitPoints; }
	void addToHitPoints(int n) { hitPoints += n; }
	int getBreakScore() { return breakScore; }
	void setBrickType(char c);
	string getBreakSound() { return breakSound; }
	string getHitSound() { return hitSound; }
	SDL_Texture* getTexturePointer() { return texture; }

	void loadTexture(SDL_Renderer* renderer);
};

#endif /* BrickType_hpp */