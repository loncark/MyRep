#include <iostream>
using namespace std;

struct tabla
{
    int polje[3][3];
    int unos;
    bool znak;
    int pobjednik;

    tabla();
    void ispisi();
    bool gameover();
    bool ponovo();
    void input();
    void reset();
};

tabla::tabla()  //nula je prazno mjesto, 1 je krizic, 2 kruzic
{
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
            polje[i][j]=0;
    unos=0;
    znak=1; //krizic pocinje
    pobjednik=0; //nema pobjednika
}

void tabla::reset()
{
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
            polje[i][j]=0;
    unos=0;
    znak=1;
    pobjednik=0;
}

void tabla::ispisi()
{
    for(int i=0; i<13; ++i)
        {
            if(i%4==0)
                {
                    for(int j=0; j<13; ++j)
                        cout<<"-";
                }

            else
                    {
                        cout<<"|";
                        for(int k=0; k<3; ++k)
                            {
                                cout<<" ";
                                if(polje[i/4][k] && i%4==2) {if(polje[i/4][k]==1) cout<<'X'; else cout<<'O';}
                                 else cout<<" ";
                                cout<<" |";
                            }
                    }
            cout<<endl;
        }

}

bool tabla::gameover()   //checkamo ima li pobjednika i, ako ga nema, jesu li sva polja popunjena
{
    for(int i=0; i<3; ++i)
        {
            if(polje[i][0]==polje[i][1] && polje[i][1]==polje[i][2] && polje[i][2]!=0)  //retci
                {pobjednik=polje[i][0]; return true;}
            if(polje[0][i]==polje[1][i] && polje[1][i]==polje[2][i] && polje[2][i]!=0)  //stupci
                {pobjednik=polje[0][i]; return true;}
        }
    if(polje[0][0]==polje[1][1] && polje[1][1]==polje[2][2] && polje[2][2]!=0)    //dijagonale
        {pobjednik=polje[0][0]; return true;}
    if(polje[0][2]==polje[1][1] && polje[1][1]==polje[2][0] && polje[2][0]!=0)
        {pobjednik=polje[0][2]; return true;}

    //pobjednika nema, jesu li sva polja popunjena?
    for(int i=0; i<3; ++i)
        {
            for(int j=0; j<3; ++j)
                if (polje[i][j]==0) {return false;}
        }

    return true;
}

bool tabla::ponovo()
{
    if(pobjednik==0) cout<<"Game over, no winner."<<endl;
    if(pobjednik==1) cout<<"Game over, X won."<<endl;
    if(pobjednik==2) cout<<"Game over, O won."<<endl;
    cout<<"Play again? (0/1) ";
    bool b; cin>>b;
    return b;
}

void tabla::input()  //unosi se dvoznamenkasti broj, prva znamenka je red, druga stupac
{
    if(znak==1) cout<<"X turn: "; else cout<<"O turn: ";
    cin>>unos; unos-=11;
    while (1)
        {
            if(unos/10<0 || unos/10>2 || unos%10<0 || unos%10>2 || unos/100>=1)
                {
                    cout<<endl<<"Faulty input. Two-digit number required "<<endl<<"with digits between 1 and 3. Repeat input: ";
                    cin>>unos; unos-=11;
                    continue;
                }
            if(polje[unos/10][unos%10]!=0)
                {
                    cout<<endl<<"Field taken. Choose an empty field: ";
                    cin>>unos; unos-=11;
                    continue;
                }
            break;
        }
    if(znak==1) polje[unos/10][unos%10]=1;
     else polje[unos/10][unos%10]=2;
    znak=!znak;

    return;
}

int main()
{
    cout<<"Tic-tac-toe in command prompt:"<<endl;
    tabla t;
    do  {
            t.reset();
            while(t.gameover()==false) {t.ispisi(); t. input();}
            t.ispisi();

        } while(t.ponovo()==1);

    return 0;
}
