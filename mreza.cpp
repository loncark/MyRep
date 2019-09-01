#include <iostream>

using namespace std;

int main()
{
    char opapira, oslike;
    float sirina, visina, redova, stupaca;

    cout<<"Program za racunanje mreze za precrtavanje."<<endl;
    cout<<"Dimenzije papira? (d za default, inace bilo sto) "; cin>>oslike;
    if(oslike!='d') {cout<<endl<<"Utipkaj custom dimenzije u mm, nebitan poredak: "; cin>>sirina>>visina;}
    else {visina=296; sirina=210;}

    cout<<"Zeljena orijentacija papira? (p/l) "; cin>>opapira;
    if(opapira=='p' && sirina>visina) swap(sirina, visina);
    if(opapira=='l' && sirina<visina) swap(sirina, visina);

    cout<<endl<<"Broj redova i stupaca slike? " ; cin>>redova>>stupaca;
    if(redova<stupaca) oslike='l';
     else oslike='p';

    // ako je slika orijetirana portrait, visina je dominanta i po njoj se racunaju dimenzije celija.
    float dimkv;
    cout<<"Sve moguce dimenzije kvadrata i margina: "<<endl;

    if(oslike=='p')
        {
            for(int margina=10; margina>=5; --margina)
                {
                   dimkv=(visina-2*margina)/redova;
                   cout<<"manja margina: "<<margina<<"mm, veca margina: "<<sirina-stupaca*dimkv-margina
                      <<"mm, dimkv: "<<dimkv<<"mm"<<endl;
                }
        }
    else{
            for(int margina=10; margina>=5; --margina)
                {
                   dimkv=(sirina-2*margina)/stupaca;
                   cout<<"manja margina: "<<margina<<"mm, veca margina: "<<visina-redova*dimkv-margina
                      <<"mm, dimkv: "<<dimkv<<"mm"<<endl;
                }
        }

    return 0;
}
