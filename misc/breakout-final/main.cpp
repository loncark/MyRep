#include "Game.hpp"

Game* game = nullptr;

int main(int argc, const char *argv[])
{
	game = new Game();
	game->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 1000);

	while (game->isRunning())
	{
		game->handleEvents();
		game->update(); 
		if (!game->isRunning()) break;
		game->render();
	}
	
	game->clean();
	
	return 0;
}