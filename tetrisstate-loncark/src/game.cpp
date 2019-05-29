#include "game.h"
#include "playstate.h"

#include <iostream>

void Game::ispis() {}

Game::Game() : mWindow(sf::VideoMode(600,700), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0)
{
    mWindow.setPosition(sf::Vector2i(200,200));
    mAllStates[0]= new WelcomeState(this);
    mAllStates[1]= new PlayState(this);
    mAllStates[2]= new SpeedState(this);

    mpGameState=mAllStates[0];
}

Game::~Game()
{
   delete(mAllStates[0]);
   delete(mAllStates[1]);
   delete(mAllStates[2]);
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow* Game::getWindow() {return &mWindow;}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {mpGameState->handleEvents(event); break;}
    }
}

void Game::update()
{
    mpGameState->update();
}

void Game::render()
{
     mpGameState->render();
}
