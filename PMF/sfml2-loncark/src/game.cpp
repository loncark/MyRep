#include "game.h"
#include <iostream>
#include <chrono>
#include <cmath>

static sf::Time dt=sf::seconds(1.f/60.f);
static float p1, q1, p2, q2;

void Game::ispis(char c)
{
    if(c=='p') {
    std::cout<<"position: "<<mBall[0]->getPosition().x<<" "<<mBall[0]->getPosition().y<<std::endl;
    std::cout<<"origin: "<<mBall[0]->getOrigin().x<<" "<<mBall[0]->getOrigin().y<<std::endl<<std::endl;
    /*std::cout<<"cposition: "<<mBall[0]->mCircle.getPosition().x<<" "<<mBall[0]->mCircle.getPosition().y<<std::endl;
    std::cout<<"corigin: "<<mBall[0]->mCircle.getOrigin().x<<" "<<mBall[0]->mCircle.getOrigin().y<<std::endl;
    std::cout<<"tposition: "<<mBall[0]->mText.getPosition().x<<" "<<mBall[0]->mText.getPosition().y<<std::endl;
    std::cout<<"torigin: "<<mBall[0]->mText.getOrigin().x<<" "<<mBall[0]->mText.getOrigin().y<<std::endl;*/
                }
    if(c=='v') {
    std::cout<<"velocity: "<<mBall[0]->mVelocity.x<<" "<<mBall[0]->mVelocity.y<<std::endl;
    std::cout<<"dt: "<<dt.asSeconds()<<std::endl;
        }
}

double distance(Ball const& b1, Ball const& b2)
{
    p1=b1.getPosition().x;
    q1=b1.getPosition().y;
    p2=b2.getPosition().x;
    q2=b2.getPosition().y;
    return sqrt( (p1-p2)*(p1-p2) + (q1-q2)*(q1-q2) );
}

double distance(sf::Vector2f const& v1, sf::Vector2f const& v2)
{
    p1=v1.x;
    q1=v1.y;
    p2=v2.x;
    q2=v2.y;
    return sqrt( (p1-p2)*(p1-p2) + (q1-q2)*(q1-q2) );
}

bool Game::intersectionCheck(Ball const& b)
{
    for(auto it=mBall.begin(); (*it)!=NULL && it!=mBall.end(); ++it)
        {
            if(distance(b,**it)<=2*b.getRadius()) return true;
        }
    return false;
}

void Game::initPositions(std::size_t nBalls, float radius)
{
    if(mBall.capacity()<nBalls)
        {mBall.resize(nBalls);}
    for(int i=0; i<nBalls; ++i)
        {
            std::unique_ptr<Ball> b(new Ball);
            b->setRadius(radius);
            b->setChar('A'+i);
            b->setOrigins();
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine mRand(seed);

            sf::Vector2f poz; //(350,250);
            do {
            poz.x=mRand()%(int)(mRectangle.getSize().x -2*radius)
                   +(mWindow.getSize().x-mRectangle.getSize().x)/2
                   +radius;
            poz.y=mRand()%(int)(mRectangle.getSize().y -2*radius)
                   +(mWindow.getSize().y-mRectangle.getSize().y)/2
                   +radius;
            b->setPosition(poz);
            } while (intersectionCheck(*b));

            mBall[i]=std::move(b);
        }
}

void Game::initVelocity(float maxVel)
{
    for(auto it=mBall.begin(); (*it)!=NULL && it!=mBall.end(); ++it)
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine mRand(seed);

            std::normal_distribution<float> distribution (0.0,maxVel);

            (*it)->mVelocity.x=distribution(mRand);
            (*it)->mVelocity.y=distribution(mRand);
        }
}

void Game::checkForCollisionsWithWalls(Ball *pball, sf::Time dt) const
{
    static float lijevirub, desnirub, gornjirub, donjirub;
    if(!lijevirub)
        {
            lijevirub = mRectangle.getPosition().x
                -mRectangle.getSize().x/2 + pball->getRadius();
            desnirub = mRectangle.getPosition().x
                +mRectangle.getSize().x/2 - pball->getRadius();
            gornjirub = mRectangle.getPosition().y
                -mRectangle.getSize().y/2 + pball->getRadius();
            donjirub = mRectangle.getPosition().y
                +mRectangle.getSize().y/2 - pball->getRadius();
        }

    sf::Vector2f sljedecapoz(
                pball->getPosition().x + pball->mVelocity.x*dt.asSeconds(),
                pball->getPosition().y + pball->mVelocity.y*dt.asSeconds());
    if( sljedecapoz.x <= lijevirub || sljedecapoz.x >= desnirub)
        {pball->mVelocity.x = -pball->mVelocity.x;}
    if( sljedecapoz.y <= gornjirub || sljedecapoz.y >= donjirub)
        {pball->mVelocity.y = -pball->mVelocity.y;}
}

void Game::checkForCollisionsWithBalls(Ball *pball, sf::Time dt) const
{
    sf::Vector2f sljedecapoz(
                pball->getPosition().x + pball->mVelocity.x*dt.asSeconds(),
                pball->getPosition().y + pball->mVelocity.y*dt.asSeconds());

    for(auto it=mBall.begin(); (*it)!=NULL && it!=mBall.end(); ++it)
        {
            if((*it)->getChar()==pball->getChar()) continue;
            if(distance((*it)->getPosition(),sljedecapoz)<=2*pball->getRadius())
                {pball->ChangeVelocity(**it,*pball);}
        }
}

Game::Game() : mWindow(sf::VideoMode(700, 500), "Bouncy Balls")
{
    mWindow.setPosition(sf::Vector2i(400, 300));
    mRectangle.setSize(sf::Vector2f(600, 400));
    mRectangle.setOrigin(mRectangle.getSize().x/2,mRectangle.getSize().y/2);
    mRectangle.setPosition(sf::Vector2f(mWindow.getSize().x/2,mWindow.getSize().y/2));
    mRectangle.setFillColor(sf::Color::Transparent);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(4);

    initPositions(10,20.f);
    initVelocity(100);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time protekloVrijeme=sf::Time::Zero;

    while (mWindow.isOpen())
    {
        processEvents();

        protekloVrijeme+=clock.restart();
        while(protekloVrijeme>=dt) {protekloVrijeme-=dt; update(dt);}

        render();
    }

}

void Game::processEvents()
{
    // Process events
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if(event.type==sf::Event::Closed) mWindow.close();
    }
}

void Game::update(sf::Time dt)
{
    Ball *pball;
    for(auto it=mBall.begin(); (*it)!=NULL && it!=mBall.end(); ++it)
        {
            pball=it->get();
            checkForCollisionsWithBalls(pball,dt);
            checkForCollisionsWithWalls(pball,dt);

            sf::Vector2f translacija(pball->mVelocity.x*dt.asSeconds(),
                         pball->mVelocity.y*dt.asSeconds());
            translacija.x+=pball->getPosition().x;
            translacija.y+=pball->getPosition().y;
            pball->setPosition(translacija);
            pball->rotate(2);
        }
}

void Game::render()
{
    // Clear screen
    mWindow.clear();
    mWindow.draw(mRectangle);
    static sf::RenderStates states;
    for(auto it=mBall.begin(); (*it)!=NULL && it!=mBall.end(); ++it)
        {
            (*it)->draw(mWindow, (*it)->mState);
        }

    // Update mWindow
    mWindow.display();
}



