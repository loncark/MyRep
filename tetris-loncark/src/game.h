#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include "score.h"

class Game{
	public:
            Game();
	    void run();
	private:
            sf::RenderWindow mWindow;
            Board mBoard;
            Score mScore;

            //score.update() se treba dogoditi samo ako
            //board.update() uđe u if-petlju
            bool prolaz;
            bool mUpKeyPressed = false;
            bool mSpaceKeyPressed = false;
            bool mRightKeyPressed = false;
            bool mLeftKeyPressed = false;
       
	    void processEvents();
            void update();
            void render();
};




