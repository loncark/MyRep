#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>

class Ball : public sf::Drawable, public sf::Transformable {
public:
    Ball();
    sf::Vector2f mVelocity;     //brzina i smjer u stupnjevima
    void setRadius(float r) {mRadius = r; mCircle.setRadius(r); }
    void setChar(char c) {mChar = c; mText.setString(mChar);}
    float getRadius() const {return mRadius;}
    char getChar() {return mChar;}
    sf::Text getText() {return mText;}
    void ChangeVelocity(Ball& b1, Ball& b2);
    void setOrigins();

private:
    sf::CircleShape mCircle;
    sf::Font mFont;
    sf::Text mText;
    float mRadius;
    char mChar;
    sf::RenderStates mState;

    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
    friend class Game;
};





