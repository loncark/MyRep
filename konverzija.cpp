#include<iostream>
#include<fstream>
using namespace std;

char pretvori(char c)
{
    if (c=='a') {c='A'; return c;}
    if (c=='e') {c='E'; return c;}
    if (c=='i') {c='I'; return c;}
    if (c=='o') {c='O'; return c;}
    if (c=='u') {c='U'; return c;}
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
