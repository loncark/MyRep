#include "game.h"

void Ball::setOrigins()
{
    mCircle.setOrigin(mCircle.getLocalBounds().width/2,mCircle.getLocalBounds().height/2);
    mText.setOrigin(mText.getLocalBounds().width/2,mText.getLocalBounds().height/1.5);
}

Ball::Ball()
{
    mCircle.setFillColor(sf::Color::Green);
    if(!mFont.loadFromFile("Comfortaa-Bold.ttf"))
        {throw std::runtime_error("Ne mogu otvoriti font.");}
    mText.setFont(mFont);
    //mText.setCharacterSize(mRadius*1.5);  -- GREŠKA  Size je nula.
    mText.setCharacterSize(25);
    //mText.setFillColor(sf::Color::White);
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mCircle, states);
    target.draw(mText, states);
}

void Ball::ChangeVelocity(Ball &b1, Ball &b2)
{
    float x11, x21, x12, x22;
    float v11, v21, v12, v22;
    float nv11, nv12, nv21, nv22;

    v11=b1.mVelocity.x;
    v12=b1.mVelocity.y;
    v21=b2.mVelocity.x;
    v22=b2.mVelocity.y;

    x11=b1.getPosition().x;
    x12=b1.getPosition().y;
    x21=b2.getPosition().x;
    x22=b2.getPosition().y;

    nv11=v11 - ((v11-v21)*(x11-x21) + (v12-v22)*(x12-x22)) /
            ( (x11-x21)*(x11-x21) + (x12-x22)*(x12-x22) )
            * (x11-x21);

    nv12=v12 - ( (v11-v21)*(x11-x21) + (v12-v22)*(x12-x22) ) /
            ( (x11-x21)*(x11-x21) + (x12-x22)*(x12-x22) )
            * (x12-x22);
    //swap + isto to
    v11=b2.mVelocity.x;
    v12=b2.mVelocity.y;
    v21=b1.mVelocity.x;
    v22=b1.mVelocity.y;

    x11=b2.getPosition().x;
    x12=b2.getPosition().y;
    x21=b1.getPosition().x;
    x22=b1.getPosition().y;

    nv21=v11 - ( (v11-v21)*(x11-x21) + (v12-v22)*(x12-x22) ) /
            ( (x11-x21)*(x11-x21) + (x12-x22)*(x12-x22) )
            * (x11-x21);

    nv22=v12 - ( (v11-v21)*(x11-x21) + (v12-v22)*(x12-x22) ) /
            ( (x11-x21)*(x11-x21) + (x12-x22)*(x12-x22) )
            * (x12-x22);

    b1.mVelocity=sf::Vector2f(nv11,nv12);
    b2.mVelocity=sf::Vector2f(nv21,nv22);
}
