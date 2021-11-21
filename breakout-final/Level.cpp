#include "Level.hpp"
#include "Text.hpp"
#include "SDL_image.h"
#include <iostream>
#include <new>  

Level::Level() 
{
	nonEmpties = 0;
	rowSpacing = 10;
	columnSpacing = rowSpacing;

	newLevel = true;
	gameWon = false;
}

Level::~Level() 
{
	delete[] Bricks;

	for (int i = 0; i < rowCount; ++i)
		delete[] brickSet[i];
	delete[] brickSet;

	Mix_FreeChunk(soundBit);
	soundBit = nullptr;

	if (texture) { SDL_DestroyTexture(texture); texture = nullptr; }
	if (surface) { SDL_FreeSurface(surface); surface = nullptr; }
}

float Level::getBrickWidth(SDL_Rect* frame)
{
	return ((frame->w - (columnCount + 1) * columnSpacing) / columnCount);
}

// Ideja je deklarirati jedan element tipa Level u Gameu
// i izmjenu levela u igri izvrsiti mijenjanjem njegovih elemenata.

void Level::setLevel(int n)
{
	this->~Level();
	nonEmpties = 0;

	if (n == 1)
	{
		levelNo = 1;
		rowCount = 4;
		columnCount = 10;
		backgroundTexture = "x64/Debug/assets/background.jpg";

		brickSet = new BrickType * [rowCount];
		for (int i = 0; i < rowCount; ++i)
			brickSet[i] = new BrickType[columnCount];

		Bricks = new char[rowCount * columnCount];

		char temp[100] = {
		 '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
		 'S', 'S', '_', '_', 'S', 'S', '_', '_', 'S', 'S', 
		 'M', 'S', '_', 'M', 'H', 'H', 'M', '_', 'S', 'M', 
		 'S', 'S', '_', '_', 'S', 'S', '_', '_', 'S', 'S' 
		};

		for (int i = 0; i < rowCount; ++i)
			for (int j = 0; j < columnCount; ++j)
			{
				Bricks[i * columnCount + j] = temp[i * columnCount + j];
				brickSet[i][j].setBrickType(Bricks[i * columnCount + j]);
				if (brickSet[i][j].getId() != '_' && brickSet[i][j].getId() != 'I') nonEmpties += 1;
			}
	}

	if (n == 2)
		{
			levelNo = 2;
			rowCount = 6;
			columnCount = 10;
			backgroundTexture = "x64/Debug/assets/background2.jpg";

			brickSet = new BrickType * [rowCount];
			for (int i = 0; i < rowCount; ++i)
				brickSet[i] = new BrickType[columnCount];

			Bricks = new char[rowCount * columnCount];

			char temp[150] = {
			 '_','_','_','_','_','_','_','_','_','_',
			 'S','S','S','S','S','S','S','S','S','S',
			 '_','_','_','_','_','_','_','_','_','_',
			 'M','I','M','_','H','H','_','M','I','M',
			 '_','_','_','_','_','_','_','_','_','_',
			 'S','S','S','S','S','S','S','S','S','S' 
			};

			for (int i = 0; i < rowCount; ++i)
				for (int j = 0; j < columnCount; ++j)
				{
					Bricks[i * columnCount + j] = temp[i * columnCount + j];
					brickSet[i][j].setBrickType(Bricks[i * columnCount + j]);
					if (brickSet[i][j].getId() != '_' && brickSet[i][j].getId() != 'I') nonEmpties += 1;
				}	
		}

	if (n == 3)
		{ 
			levelNo = 3;
			rowCount = 11;
			columnCount = 10;
			backgroundTexture = "x64/Debug/assets/background3.jpg";

			brickSet = new BrickType * [rowCount];
			for (int i = 0; i < rowCount; ++i)
				brickSet[i] = new BrickType[columnCount];

			Bricks = new char[rowCount * columnCount];

			char temp[150] = {
			 '_','S','_','_','H','H','_','_','S','_',
			 'S','_','_','_','_','_','_','_','_','S',	//2
			 '_','_','H','_','_','_','_','H','_','_',
			 '_','_','_','_','I','I','_','_','_','_',	//4
			 'I','I','_','_','S','S','_','_','I','I',
			 'S','_','_','S','_','_','S','_','_','S',	//6
			 'S','_','_','S','_','_','S','_','_','S',
			 'S','_','_','_','S','S','_','_','_','S',	//7
			 'I','I','_','_','I','I','_','_','I','I',
			 '_','_','_','_','_','_','_','_','_','_',	//9
			 '_','_','H','_','M','M','_','H','_','_',
			 '_','_','_','_','_','_','_','_','_','_',	//10
			 '_','S','S','_','I','I','_','S','S','_'
			 };

			for (int i = 0; i < rowCount; ++i)
				for (int j = 0; j < columnCount; ++j)
				{
					Bricks[i * columnCount + j] = temp[i * columnCount + j];
					brickSet[i][j].setBrickType(Bricks[i * columnCount + j]);
					if (brickSet[i][j].getId() != '_' && brickSet[i][j].getId() != 'I') nonEmpties += 1;
				}
		}
}

void Level::drawScreens(int n, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//radi jednostavnosti se ne referiraju se na velicinu windowa
	int x = 200, y = 450;

	if (n == 1)
	{
		Text prvi(renderer, "x64/Debug/assets/font.ttf", 90,
			"Breakout", { 255, 255, 255, 255 });
		
		prvi.draw(renderer, x, y);
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
	}

	Text text(renderer, "x64/Debug/assets/font.ttf", 90,
		"Level " + to_string(n), { 255, 255, 255, 255 });

	soundBit = Mix_LoadWAV("x64/Debug/assets/levelup.wav");;
	Mix_PlayChannel(-1, soundBit, 0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	text.draw(renderer, x, y);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
}

void Level::draw(SDL_Renderer* renderer, SDL_Rect* frame)
{
	static SDL_Rect cigla;

	cigla.w = getBrickWidth(frame);
	cigla.h = getBrickHeight(frame);
	cigla.x = frame->x + columnSpacing;
	cigla.y = frame->y + rowSpacing;	

	for(int i=0; i<rowCount; ++i)
		{
			for(int j=0; j<columnCount; ++j)
				{
					if (brickSet[i][j].getId()=='S')
						SDL_SetRenderDrawColor(renderer, 200, 0, 255, 0);
					else if (brickSet[i][j].getId() == 'M')
						SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
					else if (brickSet[i][j].getId() == 'H')
						SDL_SetRenderDrawColor(renderer, 0, 200, 25, 0);
					else if (brickSet[i][j].getId() == 'I')
						SDL_SetRenderDrawColor(renderer, 150, 0, 0, 150);
					else if (brickSet[i][j].getId() == '_')
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

					SDL_RenderDrawRect(renderer, &cigla);
					cigla.x += (cigla.w + columnSpacing);
				}
			
			cigla.x = frame->x + columnSpacing;
			cigla.y += (cigla.h + rowSpacing);
		}
}

void Level::loadTextures(SDL_Renderer* renderer, const string& path)
{
	surface = IMG_Load(path.c_str());
	if (!surface) std::cerr << "Level::loadTextures() surface nije stvoren.\n";

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) std::cerr << "Level::loadTextures() texture nije stvoren.\n";

	for (int i = 0; i < rowCount; ++i)
		for (int j = 0; j < columnCount; ++j)
			if(brickSet[i][j].getId() != '_') 
				brickSet[i][j].loadTexture(renderer);
	}

void Level::drawTextures(SDL_Renderer* renderer, SDL_Rect* frame)
{
	if (texture) SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	else std::cerr << "Level::drawTextures() izbacen iz RenderCopy()-ja.\n";

	static SDL_Rect brick;

	for (int i = 0; i < rowCount; ++i)
		for (int j = 0; j < columnCount; ++j)
		{
			if (brickSet[i][j].getId() == '_') continue;

			brick.w = getBrickWidth(frame);
			brick.h = getBrickHeight(frame);
			brick.x = frame->x + columnSpacing * (j + 1) + brick.w * j;
			brick.y = frame->y + rowSpacing * (i + 1) + brick.h * i;

			SDL_RenderCopy(renderer, brickSet[i][j].getTexturePointer(), 
				nullptr, &brick);
		}
}