#include "gamestate.h"
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <string>

/*Samo konstruktori primaju mpGame ponter jer klasa još
  nije stvorena pa taj pointer nije još naslijeđen.*/

//welcome
WelcomeState::WelcomeState(Game* pGame) : GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
            std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf!" << std::endl;
            std::exit(1);
    }
    mText1.setFont(mFont);
    mText2.setFont(mFont);
    mText1.setString("Tetris clone by K. Loncar");
    mText2.setString("Press any key to continue");
    mText2.setStyle(sf::Text::Italic);
    mText1.setCharacterSize(40);
    mText2.setCharacterSize(30);
    mText1.setOrigin(mText1.getLocalBounds().width/2, mText1.getLocalBounds().height/2);
    mText2.setOrigin(mText2.getLocalBounds().width/2, mText2.getLocalBounds().height/2);
    mText1.setPosition(mpGame->getWindow()->getSize().x/2, mpGame->getWindow()->getSize().y/2-40);
    mText2.setPosition(mpGame->getWindow()->getSize().x/2, mpGame->getWindow()->getSize().y/2-10);
}

void WelcomeState::handleEvents(sf::Event event)
{
    switch(event.type)
            {
                case sf::Event::KeyPressed:
                    mKeyPressed=true;
                    break;
            }
}

void WelcomeState::update()
{
    if(mKeyPressed) {mpGame->setState(Playing); mKeyPressed=false;}
}

void WelcomeState::render()
{
    mpGame->getWindow()->clear();

    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);

    mpGame->getWindow()->display();
}

//speed
SpeedState::SpeedState(Game *pGame) : GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
            std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf!" << std::endl;
            std::exit(1);
    }
    mText0.setFont(mFont);
    mText1.setFont(mFont);
    mText2.setFont(mFont);
    mText3.setFont(mFont);

    mText0.setString("Score: "+std::to_string(mpGame->mGameScore));
    mText1.setString("Current speed: "+std::to_string(mpGame->mGameSpeed));
    mText2.setString("Use keys Up and Down to change the speed.");
    mText3.setString("Press Enter to continue.");
    mText3.setStyle(sf::Text::Italic);

    mText0.setCharacterSize(30);
    mText1.setCharacterSize(30);
    mText2.setCharacterSize(30);
    mText3.setCharacterSize(30);

    mText0.setOrigin(mText0.getLocalBounds().width/2, mText0.getLocalBounds().height/2);
    mText1.setOrigin(mText1.getLocalBounds().width/2, mText1.getLocalBounds().height/2);
    mText2.setOrigin(mText2.getLocalBounds().width/2, mText2.getLocalBounds().height/2);
    mText3.setOrigin(mText3.getLocalBounds().width/2, mText3.getLocalBounds().height/2);

    mText0.setPosition(mpGame->getWindow()->getSize().x/2, mpGame->getWindow()->getSize().y/2-60);
    mText1.setPosition(mpGame->getWindow()->getSize().x/2, mpGame->getWindow()->getSize().y/2-20);
    mText2.setPosition(mpGame->getWindow()->getSize().x/2, mpGame->getWindow()->getSize().y/2+20);
    mText3.setPosition(mpGame->getWindow()->getSize().x/2, mpGame->getWindow()->getSize().y/2+60);
}

void SpeedState::handleEvents(sf::Event event)
{
    switch(event.type)
            {
                case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Return) mReturnKeyPressed=true;
                    if(event.key.code==sf::Keyboard::Up) mUpKeyPressed=true;
                    if(event.key.code==sf::Keyboard::Down) mDownKeyPressed=true;
                    break;
            }
}

void SpeedState::update()
{
    if(mUpKeyPressed) mpGame->mGameSpeed+=0.25;
    if(mDownKeyPressed)
        {
            mpGame->mGameSpeed-=0.25;
            if(mpGame->mGameSpeed<=0.f) mpGame->mGameSpeed=3.f;
        }

    mText0.setString("Score: "+std::to_string(mpGame->mGameScore));
    mText1.setString("Current speed: "+std::to_string(mpGame->mGameSpeed));
    if(mReturnKeyPressed) mpGame->setState(Playing);
    mUpKeyPressed=false;
    mReturnKeyPressed=false;
    mDownKeyPressed=false;

}

void SpeedState::render()
{
    mpGame->getWindow()->clear();

    mpGame->getWindow()->draw(mText0);
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(mText3);

    mpGame->getWindow()->display();
}
