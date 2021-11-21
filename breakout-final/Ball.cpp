#include "Ball.hpp"
#include "Bar.hpp"
#include "Level.hpp"
#include <iostream>
#include <math.h>
using namespace std;

Ball::Ball() 
{
	ballPosX = 0.0f;
	ballPosY = 0.0f;
	ballRadius = 6.0f;

	dt = 0.1f ;				
	ballVelX = 0.0f;
	ballVelY = -12.0f;

	ballTexture = nullptr;
}

void Ball::reset()
{
	ballPosX = 0.0f;
	ballPosY = 0.0f;
	ballRadius = 6.0f;

	dt = 0.1f;				
	ballVelX = 0.0f;
	ballVelY = -12.0f;
}

Ball::~Ball() 
{
	Mix_FreeChunk(soundBit);
	soundBit = nullptr;

	if (ballTexture) 
		{ 
			SDL_DestroyTexture(ballTexture); 
			ballTexture = nullptr; 
		}
}

void Ball::update(bool* spaceKeyPressed, SDL_Rect* frame, Bar* bar, Level* level, Score* score)
{
	if(!(*spaceKeyPressed))	//zalijepi se za bar
		{
			ballPosX = bar->getPosX();
			ballPosY = bar->getPosY() - bar->getHeight() - ballRadius - 1;
		}
	else {					//nastavi se kretati
			if (move(level, frame, bar, score) == true)
			{
				*spaceKeyPressed = false;
				bar->reset();
				reset();
			}
		}
}

bool Ball::checkCollisionWithWalls(SDL_Rect* frame)
{
	static float buducaPozX, buducaPozY;
	buducaPozX = ballPosX + ballVelX * dt;
	buducaPozY = ballPosY + ballVelY * dt;

	if ( buducaPozX + ballRadius > frame->x + frame->w 
		  || buducaPozX - ballRadius < frame->x ) { ballVelX = -ballVelX; }	 //sudar s lijevom/desnom granicom
	
	if ( buducaPozY - ballRadius < frame->y ) { ballVelY = -ballVelY; }		 //s gornjom
	
	if (buducaPozY + ballRadius > frame->y + frame->h)		//s donjom	
		{
			soundBit = Mix_LoadWAV("x64/Debug/assets/hitboundry.wav");
			Mix_PlayChannel(-1, soundBit, 0);

			SDL_Delay(1000);  
			return true;
		}
	 
	return false;
}

void Ball::checkCollisionWithBar(Bar* bar)
{
	static SDL_Rect kuglica, barTemp, temp;
	static float norma, jedinicni;

	//buduca pozicija kuglice
	kuglica.x = ballPosX + ballVelX * dt - ballRadius;
	kuglica.y = ballPosY + ballVelY * dt - ballRadius;
	kuglica.h = 2.0f * ballRadius;
	kuglica.w = kuglica.h;

	if (kuglica.y + 2.0f * ballRadius < bar->getPosY() - 10) return;

	barTemp.w = bar->getWidth();
	barTemp.h = bar->getHeight();
	barTemp.x = bar->getPosX() - barTemp.w / 2;
	barTemp.y = bar->getPosY() - barTemp.h;

	if (SDL_IntersectRect(&kuglica, &barTemp, &temp) == SDL_FALSE) return;

	if (temp.h > temp.w) { ballVelX = -ballVelX; }
	 else { 
				norma = sqrt(ballVelX * ballVelX + ballVelY * ballVelY);

				//uzimam u obzir domenu arccos()
				if(ballPosX >= bar->getPosX()+bar->getWidth()/2) jedinicni = sqrt(3.0f) / 6.0f;
				else if(ballPosX <= bar->getPosX() - bar->getWidth() / 2) jedinicni = 3.14f - sqrt(3.0f) / 6.0f;
				else jedinicni = acos((ballPosX - bar->getPosX()) / (bar->getWidth() / 2.0f));

				//da ne bude "prevodoravnih" odbijanja
				if (jedinicni < sqrt(3.0f) / 6.0f) jedinicni = sqrt(3.0f) / 6.0f;
				if (jedinicni > 3.14f - sqrt(3.0f) / 6.0f) jedinicni = 3.14f - sqrt(3.0f) / 6.0f;

				ballVelY = -sin(jedinicni) * norma;
				ballVelX = cos(jedinicni) * norma;
		  }
}

bool Ball::checkCollisionWithBricks(Level* level, SDL_Rect* frame, Score* score)
{
	if (ballPosY - ballRadius > (level->rowCount + 5) *
		(level->rowSpacing + level->getBrickHeight(frame))) return false; 
	
	SDL_Rect kuglica, brick, temp; bool nasao;

	kuglica.x = ballPosX + ballVelX * dt - ballRadius;
	kuglica.y = ballPosY + ballVelY * dt - ballRadius;
	kuglica.h = 2.0f * ballRadius;
	kuglica.w = kuglica.h;

	brick.w = level->getBrickWidth(frame);
	brick.h = level->getBrickHeight(frame);

	nasao = false;

	for (int i = 0; i < level->rowCount; ++i)
	{
		for (int j = 0; j < level->columnCount; ++j)
		{
			if (level->brickSet[i][j].getId() == '_') continue;

			brick.x = frame->x + level->columnSpacing*(j+1) + brick.w*j;
			brick.y = frame->y + level->rowSpacing*(i+1) + brick.h*i;

			if (SDL_IntersectRect(&kuglica, &brick, &temp) == SDL_FALSE) continue;
			
			nasao = true;		//postoji sudar
			
			if(level->brickSet[i][j].getId() == 'I')
			{
				soundBit = Mix_LoadWAV(
					level->brickSet[i][j].getHitSound().c_str());
				Mix_PlayChannel(-1, soundBit, 0);
			}

			if (level->brickSet[i][j].getHitPoints() > 0)
				{
					level->brickSet[i][j].addToHitPoints(-1);	
					increaseVel();
								
					if (level->brickSet[i][j].getHitPoints() == 0)
					{
						score->increaseScoreBy(level->brickSet[i][j].getBreakScore());
						level->brickSet[i][j].setBrickType('_');
						level->nonEmpties -= 1;

						if (level->nonEmpties == 0)
						{
							if (level->getLevelNo() == 3) level->reverseGameWon();

							score->setLevelNo((level->getLevelNo() + 1));
							level->setLevel(score->getLevelNo());
							level->reverseNewLevel();

							return true;	//reverses SpaceKeyPressed
						}
						else {
								soundBit = Mix_LoadWAV(
									level->brickSet[i][j].getBreakSound().c_str());
								Mix_PlayChannel(-1, soundBit, 0);
							 }
					}
					else {
							soundBit = Mix_LoadWAV(
								level->brickSet[i][j].getHitSound().c_str());
							Mix_PlayChannel(-1, soundBit, 0);
						 }
				}

			if (temp.h > temp.w) { ballVelX = -ballVelX; }
			 else { ballVelY = -ballVelY; }
			break;
		}
		
		if (nasao) break;
	}
	return false;
}

bool Ball::move(Level* level, SDL_Rect* frame, Bar *bar, Score* score)
{
	if (this->checkCollisionWithWalls(frame)) 
		{
			score->takeLife(); 
			return true;
		}
	
	this->checkCollisionWithBar(bar);
	
	if (this->checkCollisionWithBricks(level, frame, score) == true)
		return true;

	ballPosX = ballPosX + ballVelX * dt;		//ball koordinate nakon prolaska dt vremena
	ballPosY = ballPosY + ballVelY * dt;

	return false;
}

void Ball::draw(SDL_Renderer* renderer)
{
	static SDL_Rect temp;
	temp.x = ballPosX - ballRadius;
	temp.y = ballPosY - ballRadius;
	temp.h = temp.w = 2.0f * ballRadius;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &temp);

	if(!ballTexture) loadTexture(renderer);
	else SDL_RenderCopy(renderer, ballTexture, nullptr, &temp);
}

void Ball::loadTexture(SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load("x64/Debug/assets/ball.jpg");
	if (!surface) std::cerr << "Ball::loadTexture() nije stvorio surface.\n";

	ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!ballTexture) std::cerr << "Ball::loadTexture() nije stvorio ballTexture.\n";

	SDL_FreeSurface(surface);
	surface = nullptr;
}
