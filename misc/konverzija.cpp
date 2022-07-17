#include<iostream>
#include<fstream>
#include<cctype>
#include<array>
#include<WIndows.h>
#include<random>
#include<chrono>
using namespace std;

int dignum(int a)
{
    if(a==0) return 1;
    int dig=0;
    while(a!=0) {a/=10; ++dig;}
    return dig;
}

int randomdigit(int broj)
{
    if(dignum(broj)==1) return broj;
    static default_random_engine generator;
    static uniform_int_distribution<int> distribution(1,dignum(broj));
    int dig=distribution(generator)-1;

    while(dig) {broj/=10; --dig;}
    dig=broj%10;

    return dig;
}

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
            cout<<*s;
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

  unsigned seed=chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  bernoulli_distribution Bdistribution(0.3);

  input.open("file.txt");
  output.open("izlaz.txt");

  if (input.is_open() && output.is_open())
    {
        while(getline(input,linija))
            {
                for(s=linija.begin(); s!=linija.end(); ++s)
                    {
                        if(*s==' ' && Bdistribution(generator))
                            {
                                do {output<<*s; ++s;} while(*s!=' ' && s!=linija.end());
                                if(*s==' ') {--s; continue;}
                                if (s==linija.end()) break;
                            }

                        if(isalpha(*s)) output<<to_string(randomdigit(fibonacci(*s)));
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
