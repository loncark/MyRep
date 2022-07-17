#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <SFML/Window/Event.hpp>

#include "gamestate.h"
#include "board.h"
#include "score.h"

// Ovo je bivša klasa Game.

class PlayState : public GameState
{
public:
    PlayState(Game * pGame) : GameState(pGame) {}
    //pokreće novu igru
    void  start() override;
    int getScore() {return mScore.getScore();}
private:
    Board mBoard;
    Score mScore;

    bool prolaz;
    bool mUpKeyPressed = false;
    bool mSpaceKeyPressed = false;
    bool mRightKeyPressed = false;
    bool mLeftKeyPressed = false;

    virtual void handleEvents(sf::Event event) override;
    virtual void update() override;
    virtual void render() override;
};

#endif // PLAY_STATE_H
