#include "Level.hpp"
#include "Text.hpp"
#include <iostream>
#include <new>  

Level::Level() 
{
	nonEmpties = 0;
	rowSpacing = 10;
	columnSpacing = rowSpacing;
	string backgroundTexture = "Textures/Boards/Board_01.dds";
	newLevel = true;
	gameWon = false;
}

Level::~Level() 
{
	delete[] Bricks;

	for (int i = 0; i < rowCount; ++i)
		delete[] brickSet[i];
	delete[] brickSet;
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

			brickSet = new BrickType * [rowCount];
			for (int i = 0; i < rowCount; ++i)
				brickSet[i] = new BrickType[columnCount];

			Bricks = new char[rowCount * columnCount];

			char temp[150] = {
			 '_','S','_','_','I','I','_','_','S','_',
			 'S','_','_','_','_','_','_','_','_','S',	//2
			 '_','_','H','_','_','_','_','H','_','_',
			 '_','_','_','_','I','I','_','_','_','_',	//4
			 'I','I','_','_','S','S','_','_','I','I',
			 '_','_','_','S','_','_','S','_','_','_',	//6
			 'S','_','_','S','_','_','S','_','_','S',
			 '_','_','_','_','S','S','_','_','_','_',	//7
			 'I','I','_','_','I','I','_','_','I','I',
			 '_','_','_','_','_','_','_','_','_','_',	//9
			 '_','_','H','_','M','M','_','H','_','_',
			 '_','_','_','_','_','_','_','_','_','_',	//10
			 '_','_','_','_','I','I','_','_','_','_'
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
		Text prvi(renderer, "assets/font.ttf", 90,
			"Breakout", { 255, 255, 255, 255 });
		
		prvi.draw(renderer, x, y);
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
	}

	Text text(renderer, "assets/font.ttf", 90,
		"Level " + to_string(n), { 255, 255, 255, 255 });

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	text.draw(renderer, x, y);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
}

void Level::draw(SDL_Renderer* renderer, SDL_Rect* frame)
{
	SDL_Rect cigla;

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