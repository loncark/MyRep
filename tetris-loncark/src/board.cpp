#include "board.h"
void Board::ispis()
{
    for (int i=0; i<mRows; ++i)
    {for (int j=0; j<mCols; ++j)
            if(mGridContent[i][j]!=-1) std::cout<<mGridContent[i][j]<<" ";
             else std::cout<<"* ";
        std::cout<<std::endl;} std::cout<<std::endl;
}

void ispis2() {std::cout<<"PROSAO";}

void Board::ispis3()
{
    for(int i=0; i<4; ++i)
        {for(int j=0; j<4; ++j)
            std::cout<<mPiece.mDijelovi[mPiece.mRotacija]
                    [i][j]<<" "; std::cout<<std::endl;}
    std::cout<<std::endl;

}

Board::Board()
{
    for(int i=0; i<mRows; ++i)
        for(int j=0; j<mCols; ++j)
            mGridContent[i][j]=EMPTY;
    spawnPiece();
}

void Board::update(bool& prolaz, bool mLeftKeyPressed, bool mRightKeyPressed, bool mUpKeyPressed, bool mSpaceKeyPressed)
{
    if(mUpKeyPressed) rotatePiece();
    if(mRightKeyPressed) movePiece('r');
    if(mLeftKeyPressed) movePiece('l');
    if(mSpaceKeyPressed) slide();
    prolaz=false;

    if (!isGameOver() && checkClock() && !movePiece('d'))
        {
            prolaz=true;
            clearLines(); //očisti matricu i aktualiziraj mNoLinesCompleted
            spawnPiece(); //stvori novi tetrimino i aktualiziraj mGameOver
        }
}

void Board::spawnPiece()
{
    mPiece.mType=mPiece.intToTypes((mUniformDist(mRD))%7);
    mPiece.mRotacija=0;
    mPiece.move(-1, mCols/2-2);
    if(intersectionCheck(mPiece)) mGameOver=true;
     else StampIt();
    mPiece.mClock.restart();
}

bool Board::isGameOver() const {return mGameOver;}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const

{
    sf::RectangleShape polje;
    polje.setSize(sf::Vector2f(offset,offset));
    polje.setOutlineColor(sf::Color::White);
    polje.setOutlineThickness(1.f);
    polje.setFillColor(sf::Color::Black);
    //iscrtavanje polja red po red
    for (int i=0; i<mRows; ++i)
        for(int j=0; j<mCols; ++j)
            {
                polje.setPosition(sf::Vector2f(
                      mLeftMargin+j*offset, mTopMargin+i*offset));
                if(mGridContent[i][j]!=EMPTY) polje.setFillColor(mPiece.mColors[mGridContent[i][j]]);
                 else polje.setFillColor(sf::Color::Black);
                target.draw(polje, sf::RenderStates::Default);
            }
}

//Tetrimino stuff
void Board::removePiece()
{
    /*prođi po matrici tetrimina; tamo gdje naiđeš na ne-nul broj,
    konvertiraj u globalne koordinate mGridContenta (na temelju
    pozicije) i obriši iz ploče postavljanjem na EMPTY*/
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            {
                if(mPiece.mDijelovi
                   [mPiece.mType][mPiece.mRotacija][i][j]!=0)
                    mGridContent[mPiece.mXposition+i][mPiece.mYposition+j]=EMPTY;
            }
    return;
}

bool Board::outOfBounds(Tetrimino const& piece)
{
    /*prođi po matrici tetrimina; tamo gdje naiđeš na ne-nul broj,
    konvertiraj u globalne koordinate mGridContenta (na temelju
    pozicije) i provjeri izlazi li polje iz okvira ploče*/
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            {
                if(piece.mDijelovi
                   [piece.mType][piece.mRotacija][i][j]!=0)
                    {
                        if(piece.mXposition+i<0 ||
                           piece.mXposition+i>mRows-1)
                            return true;
                        if(piece.mYposition+j<0 ||
                           piece.mYposition+j>mCols-1)
                            return true;
                    }
            }
    return false;
}

bool Board::intersectionCheck(Tetrimino const& piece)
{
    /*prođi po matrici tetrimina; tamo gdje naiđeš na ne-nul broj,
    konvertiraj u globalne koordinate mGridContenta (na temelju
    pozicije) i provjeri je li na tom mjestu mGridContent EMPTY*/
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            {
                if(piece.mDijelovi
                   [piece.mType][piece.mRotacija][i][j]!=0)
                    {
                        if(mGridContent
                                [piece.mXposition+i]
                                [piece.mYposition+j]!=EMPTY)
                         return true;
                    }
            }
    return false;
}

void Board::StampIt()
{
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            {
                if(mPiece.mDijelovi
                   [mPiece.mType][mPiece.mRotacija][i][j]!=0)
                    mGridContent[mPiece.mXposition+i][mPiece.mYposition+j]=mPiece.mType;
            }
}

bool Board::movePiece(char c)
{
    /*Funkcija mPieceCanBeMoved() je izbačena jer se kopija
      mPiece-a koja se provjerava sudara sa njegovom sadašnjom pozicijom;
      dakle, mPiece se nužno mora maknuti.*/
    int x, y, xtemp=mPiece.mXposition, ytemp=mPiece.mYposition;
    if (c=='l') {x=mPiece.mXposition; y=mPiece.mYposition-1;}
    if (c=='r') {x=mPiece.mXposition; y=mPiece.mYposition+1;}
    if (c=='d') {x=mPiece.mXposition+1; y=mPiece.mYposition;}

    removePiece();
    mPiece.move(x,y);
    if(outOfBounds(mPiece) || intersectionCheck(mPiece))
        {mPiece.move(xtemp,ytemp); StampIt(); return false;}
     else {StampIt(); return true;}
}

bool Board::rotatePiece()
{
    removePiece();
    mPiece.rotate();
    if(outOfBounds(mPiece) || intersectionCheck(mPiece))
        {
            mPiece.rotate();
            mPiece.rotate();
            mPiece.rotate();
            StampIt();
            return false;
        }
     else {StampIt(); return true;}
}

bool Board::checkLine(int i) const
{
    for(int j=0; j<mCols; ++j)
        if(mGridContent[i][j]==EMPTY) return false;
    return true;
}

void Board::removeLine(int l)
{
    if(l==0)        //prvi red je iznimka
        {
            for(int j=0; j<mCols; ++j) mGridContent[0][j]=EMPTY;
            return;
        }
    for(int i=l; i>0; i--)
        for(int j=0; j<mCols; ++j)
             mGridContent[i][j]=mGridContent[i-1][j];

    for(int j=0; j<mCols; ++j) mGridContent[0][j]=EMPTY;
    return;
}

void Board::clearLines()
{
    clearNoLinesCompleted();
    for(int i=mRows-1; i>-1; --i)
        if(checkLine(i)) {removeLine(i++); ++mNoLinesCompleted;}
}

void Board::slide()
{
    while(movePiece('d')) {}
    return;
}

bool Board::checkClock()
{
    if(mPiece.mClock.getElapsedTime().asSeconds()>mDt) {mPiece.mClock.restart(); return true;}
    return false;
}
