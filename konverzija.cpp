#include<iostream>
#include<fstream>
#include<cctype>
#include<array>
using namespace std;

int fibonacci(char c)
{
    c=tolower(c);
    static array<int,35> fib;
    if(fib[1]==1) return fib[c-'a'];
    int sum=1;
    for(int i=1; i<35; ++i)
        {
            fib[i]=sum;
            sum=fib[i]+fib[i-1];
        }
    return fib[c-'a'];
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
                        if(isalpha(*s)) output<<to_string(fibonacci(*s));
                         else output<<*s;
                    }
                output<<'\n';
            }

        input.close();
        output.close();
    }

  else cout << "Jedan od fajlova se ne da otvorit";

  return 0;
}
