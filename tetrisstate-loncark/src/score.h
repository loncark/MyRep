#pragma once
#include <SFML/Graphics.hpp>

// Doraditi klasu ako je potrebno.
class Game;
class Score : public sf::Drawable, public sf::Transformable{
public:
    Score();
    void addNoLinesCompleted(int n);
    void update(int mNoLinesCompleted);
    int  getScore() const { return mScore; }
    void resetScore();
private:
    sf::Font mFont;
    sf::Text mScoreText;
    int mScore = 0;

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};
