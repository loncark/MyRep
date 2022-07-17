#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

//u slucaju da bude ikad bila potrebna razrada
char opapira(int visina, int sirina)
{
    char opapira;
    cout<<"Zeljena orijentacija papira? (p/l) "; cin>>opapira;
    if(opapira=='p' && sirina>visina) swap(sirina, visina);
    if(opapira=='l' && sirina<visina) swap(sirina, visina);
    return opapira;
}

//vraca 1 ako lufta ima dolje i 0 ako lufta ima lijevo-desno
//(duguljasta slika mora biti centrirana, zdepasta slika treba biti sto vise gore)
bool prostor(int visina, int sirina, int redova, int stupaca)
{
    float vis2=visina, sir2=sirina, red2=redova, stu2=stupaca;
    if(vis2/sir2>red2/stu2) return true;
    return false;
}

//vrti po cijelim dimenzijama kvadrata i racuna odgovarajuce margine
//prvi element tuplea je dimkv, drugi je dvostruka margina lijevo-desno-gore, a ekstra prostor je treci
void getdimkv(int visina, int sirina, int redova, int stupaca)
{
    // treba ustanoviti ima li 'portrait' slika praznog mjesta gore-dolje ili lijevo-desno
    bool luft=prostor(visina,sirina,redova,stupaca);
    vector<tuple<int,int,int> > dimenzije;
    vector<tuple<int,int,int> >::iterator it;
    tuple<int,int,int> temp;

    if(luft==true)  //zdepasta slika
        {
            //prva dimenzija koju gledamo je ona za marginu od 5mm
            //20mm je maksimalna dimenzija pogodna za precizno precrtavanje
            if((sirina-2*30)/stupaca>20) {cout<<"Pocetni dimkv>20mm."; return;}
            for(int dimkv=(sirina-2*30)/stupaca; dimkv<=20; ++dimkv)
                {
                    get<0>(temp)=dimkv;
                    get<1>(temp)=sirina-dimkv*stupaca;
                    if(get<1>(temp)<=5) continue;
                    get<2>(temp)=visina-dimkv*redova-get<1>(temp)/2;
                    dimenzije.push_back(temp);
                }

            //ispis
            cout<<"Dimkv, dvostruka margina lijevo-desno-gore, donji visak:"<<endl;
            for(it=dimenzije.begin(); it!=dimenzije.end(); ++it)
                {
                    cout<<get<0>(*it)<<"mm   "<<get<1>(*it)<<"mm   "<<get<2>(*it)<<"mm"<<endl;
                    //da ispisuje pregledno u grupama
                    if(get<0>(*it)%5==0) cout<<endl;
                }
        }

    else    //duguljasta slika, nije analogon gornjeg koda!
        {
            if((visina-2*30)/redova>20) {cout<<"Pocetni dimkv>20mm."; return;}
            for(int dimkv=(visina-2*30)/redova; dimkv<=20; ++dimkv)
                {
                    get<0>(temp)=dimkv;
                    get<1>(temp)=visina-dimkv*redova;
                    if(get<1>(temp)<=5) continue;
                    get<2>(temp)=sirina-dimkv*stupaca;
                    dimenzije.push_back(temp);
                }

            //ispis
            cout<<"Dimkv, dvostruka margina gore-dolje, dvostruka margina lijevo-desno:"<<endl;
            for(it=dimenzije.begin(); it!=dimenzije.end(); ++it)
                {
                    cout<<get<0>(*it)<<"mm   "<<get<1>(*it)<<"mm   "<<get<2>(*it)<<"mm"<<endl;
                    if(get<0>(*it)%5==0) cout<<endl;
                }
        }

    return;
}

int main()
{
    int sirina, visina, redova, stupaca; char oslike;

    cout<<"Program za racunanje mreze za precrtavanje."<<endl;
    cout<<"Dimenzije papira? (d za default A4, inace bilo sto) "; cin>>oslike;
    if(oslike!='d') {cout<<endl<<"Utipkaj custom dimenzije papira u mm bez decimala, nebitan poredak: "; cin>>sirina>>visina;}
    else {visina=296; sirina=210;}

    //smjestam portrait sliku na portrait papir
    if(sirina>visina) swap(sirina, visina);

    cout<<endl<<"Broj redova i stupaca slike? " ; cin>>redova>>stupaca;

    getdimkv(visina, sirina, redova, stupaca);

    return 0;
}
