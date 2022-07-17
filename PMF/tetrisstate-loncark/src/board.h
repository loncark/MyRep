#ifndef BOARD_H
#define BOARD_H
#define EMPTY -1

#include <SFML/Graphics.hpp>
#include "tetrimino.h"
#include <random>
#include <iostream>

/** Klasa Board
 *  Klasa implementira svu logiku Tetris igre.
 */
class Board : public sf::Drawable, public sf::Transformable,
        public sf::NonCopyable {
public:
    Board();
    // Aktualizacija
    void update(bool& prolaz, bool mLeftKeyPressed, bool mRightKeyPressed, bool mUpKeyPressed, bool mSpaceKeyPressed);
    // Pozicioniraj novi tetrimino na ploči.
    void spawnPiece();
    // Vraća true ako je igra gotova, inače false
    bool isGameOver() const;
    // Broj obrisanih linija od zadnje aktualizacije scene.
    int getNoLinesCompleted() const {return mNoLinesCompleted;}
    void clearNoLinesCompleted() {mNoLinesCompleted=0;}

    //dodaci za tetrisstate
    void clearState();
    void  setSpeed(float speed) { mDt = 1.0f/speed;}
    float getSpeed() const { return 1.0f/mDt; }

    //debug tools
    void ispis();
    void ispis3();

private:
    static const int mCols = 10;       // Broj stupaca u mreži
    static const int mRows = 2* mCols; // Broj redaka u mreži

    //sf::VertexArray mGrid;           // Iscrtavanje ide preko mGridContent
    int mGridContent[mRows][mCols];    // Logički prikaz mreže

    // Dimenzije mreže
    float mLeftMargin = 50.f;
    float mTopMargin = 50.0f;
    float mWidth=280.f;
    float mHeight=2*mWidth;
    // Početak mreže --> definiran s mLeftmargin i mTopMargin

    // Dimenzija ćelija --> kvadratne ćelije
    float offset = mWidth/mCols;
    // Vremenski interval između propadanja tetrimina.
    float mDt = 0.3; // sekunde
    // Signalizacija da je igra završena
    bool mGameOver = false;
    // Broj linija obrisanih od jednom (0,1,2,3 ili 4)
    int mNoLinesCompleted = 0;

    // Komad koji pada
    Tetrimino mPiece;

    std::random_device mRD;
    std::uniform_int_distribution<int> mUniformDist; //za generiranje tetrimina

    // Iscrtavanje
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    // Smjesti mPiece na ploču. Pretpostavlja se da je checkSpace(piece) vratio true.
    bool placePiece();
    // Pomakni mPiece ako je moguće. Vrati true ako je pomak izvršen, inače false.
    bool movePiece(char c);
    bool rotatePiece();
    // teleportira mPiece na najnižu moguću poziciju (spacebar)
    void slide();
    // potvrdi promjenu (promijeni ploču prema promjeni mPiece-a)
    void StampIt();
    //briše mPiece s ploče kako bi se mogao premjestiti/rotirati
    void removePiece();
    // provjerava je li linija pogodna za brisanje
    bool checkLine(int i) const;

    // Eventualno vaše dodatne metode dolaze ovdje.

    // Obriši kompletne linije i aktualiziraj broj obrisanih linija
    void clearLines();
    // Provjera je li clock u mPiece-u prešao mDt, ako da, resetira ga
    bool checkClock();
    // briše i-tu liniju iz ploče
    void removeLine(int i);
    // provjera izlazi li dani tetrimino izvan granica ploče
    bool outOfBounds(Tetrimino const& piece);
    // provjera križa li se dani tetrimino s nekim drugim (NE ZOVE outOfBounds()!)
    bool intersectionCheck(Tetrimino const& piece);
};

#endif // BOARD_H
