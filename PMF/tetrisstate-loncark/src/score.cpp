#include "score.h"
#include <cstdlib>
#include <iostream>
#include <string>

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

void Score::update(int mNoLinesCompleted)
{
    addNoLinesCompleted(mNoLinesCompleted);
    mScoreText.setString("Score: "+std::to_string(mScore));
}

void Score::resetScore()
{
    mScore=0;
    mScoreText.setString("Score: 0");
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mScoreText, sf::RenderStates::Default);
}

