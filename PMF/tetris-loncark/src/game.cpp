#include "game.h"
#include <iostream>

Game::Game() : mWindow(sf::VideoMode(600,700), "Tetris")
{
    mWindow.setPosition(sf::Vector2i(200,200));
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
        if(mBoard.isGameOver()) break;
    }
    while(mWindow.isOpen()) {processEvents();}
}

void Game::processEvents()
{
    mUpKeyPressed = false;
    mSpaceKeyPressed = false;
    mRightKeyPressed = false;
    mLeftKeyPressed = false;
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;

            case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::Left) mLeftKeyPressed=true;
                if(event.key.code==sf::Keyboard::Right) mRightKeyPressed=true;
                if(event.key.code==sf::Keyboard::Space) mSpaceKeyPressed=true;
                if(event.key.code==sf::Keyboard::Up) mUpKeyPressed=true;
                break;

            case sf::Event::Resized:
                // Spriječi deformaciju objekata prilikom promjene veličine prozora
                sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
                mWindow.setView(sf::View(viewRect));
                break;
        }
    }
}

void Game::update()
{   //imamo spawnani tetrimino
    //ako je dovoljno vremena prošlo, spusti ga jedno polje nadolje
    //ako spuštanje nije moguće, napravi aktualizaciju scorea
    mBoard.update(prolaz, mLeftKeyPressed, mRightKeyPressed, mUpKeyPressed, mSpaceKeyPressed);
    if(prolaz) mScore.update(mBoard.getNoLinesCompleted(), mBoard.isGameOver());
}

void Game::render()
{
     mWindow.clear();

     mWindow.draw(mBoard);
     mWindow.draw(mScore);

     mWindow.display();
}
