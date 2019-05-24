#include "score.h"
#include <cstdlib>
#include <iostream>

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf!" << std::endl;
        std::exit(1);
    }
    mScoreText.setFont(mFont);
    mScoreText.setPosition(380, 50);
    mScoreText.setCharacterSize(40);
    mScoreText.setString("Score: "+std::to_string(mScore));
}

void Score::addNoLinesCompleted(int n) {mScore+=n*10;}

void Score::update(int mNoLinesCompleted, bool mGameOver)
{
    addNoLinesCompleted(mNoLinesCompleted);
    if(mGameOver==true)
        {mScoreText.setString("Game over.\n  "+std::to_string(mScore));}
    //mScore se mijenja! Zato
    else mScoreText.setString("Score: "+std::to_string(mScore));
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
     target.draw(mScoreText, sf::RenderStates::Default);
}
