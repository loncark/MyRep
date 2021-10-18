#include<iostream>
#include<fstream>
#include<cctype>
#include<array>
#include<WIndows.h>
#include<random>
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

void ispisi(string linija)
{
    static default_random_engine generator;
    static uniform_int_distribution<int> distribution(100,400);
    static int random;

    string::iterator s;
    for(s=linija.begin(); s!=linija.end(); ++s)
        {
            random=distribution(generator);
            Sleep(random);
            if(isalpha(*s)) cout<<to_string(fibonacci(*s));
             else cout<<*s;
        }
    cout<<'\n';
    return;
}


int main ()
{
  string linija;
  string::iterator s;
  ifstream input;
  ofstream output;
  default_random_engine generator;
  bernoulli_distribution Bdistribution(0.7);

  input.open("file.txt");
  output.open("izlaz.txt");

  if (input.is_open() && output.is_open())
    {
        while(getline(input,linija))
            {
                for(s=linija.begin(); s!=linija.end(); ++s)
                    {
                        if(*s==' ' && Bdistribution(generator))     //ne izlazi iz for petlje
                            {
                                do {output<<*s; ++s;} while(*s!=' ' && s!=linija.end());
                                if(*s==' ') {--s; continue;}
                                if (s==linija.end()) break;
                            }

                        if(isalpha(*s)) output<<to_string(fibonacci(*s));
                         else output<<*s;
                    }
                output<<'\n';
            }

        input.close();
        output.close();
    }

   else cout << "Jedan od fajlova se ne da otvorit";

  input.open("izlaz.txt");
  if (input.is_open())
    {
        while(getline(input,linija))
            {
                ispisi(linija);
            }

        input.close();
        output.close();
    }

   else cout << "Izlaz.txt se ne da otvorit";

  return 0;
}
