#include "playstate.h"
#include "game.h"

void PlayState::start()
{
    mBoard.clearState();
    mpGame->mGameScore=0;
    mScore.resetScore();
    mBoard.setSpeed(mpGame->mGameSpeed);
}

void PlayState::handleEvents(sf::Event event)
{
    switch(event.type)
        {
            case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::Left) mLeftKeyPressed=true;
                if(event.key.code==sf::Keyboard::Right) mRightKeyPressed=true;
                if(event.key.code==sf::Keyboard::Space) mSpaceKeyPressed=true;
                if(event.key.code==sf::Keyboard::Up) mUpKeyPressed=true;
                break;
        }
}

void PlayState::update()
{
    mBoard.update(prolaz, mLeftKeyPressed, mRightKeyPressed, mUpKeyPressed, mSpaceKeyPressed);
    mLeftKeyPressed=false;
    mRightKeyPressed=false;
    mUpKeyPressed=false;
    mSpaceKeyPressed=false;
    if(prolaz) mScore.update(mBoard.getNoLinesCompleted());
    if(mBoard.isGameOver()) {mpGame->mGameScore=getScore(); mpGame->setState(Speed);}
}

void PlayState::render()
{
     mpGame->getWindow()->clear();

     mpGame->getWindow()->draw(mBoard);
     mpGame->getWindow()->draw(mScore);

     mpGame->getWindow()->display();
}
