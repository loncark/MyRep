#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Score : public sf::Drawable, public sf::Transformable{
public:
    Score();
    // Dodaj broj obrisanih linija i aktualiziraj rezultat.
    void addNoLinesCompleted(int n);
    // Aktualizacija ispisa
    void update (int mNoLinesCompleted, bool mGameOver);
private:
    sf::Font mFont;
    sf::Text mScoreText;

    int mScore = 0;
    // Eventualne dodatne varijable dolaze ovdje

    // Iscrtavanje.
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};
