#include<iostream>
#include<fstream>
#include<cctype>
using namespace std;

string pretvori(const char c)
{
    string s;
    if(!isalnum(c)) {s+=c; return s;}
    if (c=='a' || c=='A') {s="0"; return s;}
    if (c=='b' || c=='B') {s="1"; return s;}
    if (c=='c' || c=='C') {s="2"; return s;}
    if (c=='d' || c=='D') {s="3"; return s;}
    if (c=='e' || c=='E') {s="5"; return s;}
    if (c=='f' || c=='F') {s="8"; return s;}
    if (c=='g' || c=='G') {s="13"; return s;}
    if (c=='h' || c=='H') {s="21"; return s;}
    if (c=='i' || c=='I') {s="34"; return s;}
    if (c=='j' || c=='J') {s="55"; return s;}
    if (c=='k' || c=='K') {s="89"; return s;}
    if (c=='l' || c=='L') {s="144"; return s;}
    if (c=='m' || c=='M') {s="233"; return s;}
    if (c=='n' || c=='N') {s="377"; return s;}
    if (c=='o' || c=='O') {s="610"; return s;}
    if (c=='p' || c=='P') {s="987"; return s;}
    if (c=='q' || c=='Q') {s="1597"; return s;}
    if (c=='r' || c=='R') {s="2584"; return s;}
    if (c=='s' || c=='S') {s="4181"; return s;}
    if (c=='t' || c=='T') {s="6765"; return s;}
    if (c=='u' || c=='U') {s="10946"; return s;}
    if (c=='v' || c=='V') {s="17711"; return s;}
    if (c=='w' || c=='W') {s="28657"; return s;}
    if (c=='x' || c=='X') {s="46368"; return s;}
    if (c=='y' || c=='Y') {s="75025"; return s;}
    if (c=='z' || c=='Z') {s="121393"; return s;}
}

int main ()
{
  string linija;
  string::iterator s;
  ifstream input;
  ofstream output;
  input.open("file.txt");
  output.open("izlaz.txt");
  if (input.is_open() && output.is_open())
    {
        while(getline(input,linija))
            {
                for(s=linija.begin(); s!=linija.end(); ++s)
                    {
                        output<<pretvori(*s);
                    }
                output<<'\n';
            }

        input.close();
        output.close();
    }

  else cout << "Jedan od fajlova se ne da otvorit";

  return 0;
}
