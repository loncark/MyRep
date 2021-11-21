#include "BrickType.hpp"

BrickType::BrickType() 
{
	texture = nullptr;
	surface = nullptr;
}

BrickType::~BrickType()
{
	if (texture) { SDL_DestroyTexture(texture); texture = nullptr; }
	if (surface) { SDL_FreeSurface(surface); surface = nullptr; }
}

void BrickType::setBrickType(char c)
{
	if (c == '_')
	{
		id = '_';
		hitPoints = 0;
		breakScore = 0;
		if (texture) { SDL_DestroyTexture(texture); texture = nullptr; }
		if (surface) { SDL_FreeSurface(surface); surface = nullptr; }
	}

	if (c=='S')
		{
			id = 'S';
			hitPoints = 1;
			breakScore = 5;
			texturePath = "x64/Debug/assets/soft.jpg";
			hitSound = "x64/Debug/assets/generalhit.wav";
			breakSound = "x64/Debug/assets/brickdown.wav";
		}

	if (c == 'M')
	{
		id = 'M';
		hitPoints = 2;
		breakScore = 10;
		texturePath = "x64/Debug/assets/medium.jpg";
		hitSound = "x64/Debug/assets/generalhit.wav";
		breakSound = "x64/Debug/assets/brickdown.wav";
	}

	if (c == 'H')
	{
		id = 'H';
		hitPoints = 3;
		breakScore = 15;
		texturePath = "x64/Debug/assets/hard.jpg";
		hitSound = "x64/Debug/assets/generalhit.wav";
		breakSound = "x64/Debug/assets/brickdown.wav";
	}

	if (c == 'I')
	{
		id = 'I';
		hitPoints = -1;
		breakScore = 0;
		texturePath = "x64/Debug/assets/infinite.jpg";
		hitSound = "x64/Debug/assets/infinite.wav";
	}
}

void BrickType::loadTexture(SDL_Renderer* renderer)
{
	surface = IMG_Load(texturePath.c_str());
	if (!surface) std::cerr << "BrickType::loadTexture() surface nije stvoren.\n";

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) std::cerr << "BrickType::loadTexture() texture nije stvoren.\n";
}
