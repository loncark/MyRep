#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    printf("Program za izracun dimenzija mreze za precrtavanje aka optimalno smjestanje pravokutnika na obicni papir.\n");

    char c;
    printf("Format papira? (s/n) ");
    scanf("%c", &c);

    float visina, sirina;
    if(c=='s') {visina=210; sirina=296;}
     else {
            printf("Unesi proizvoljne dimenzije (u mm): ");
            scanf("%f %f", &visina, &sirina);
          }

    int s, r, redaka, stupaca;
    printf("Unesi broj redaka i stupaca: ");
    scanf("%d%d", &redaka, &stupaca);

    //smjestam pravokutnik tako da je papir landscape orijentiran
    //dimenzije papira su spremljene u int visina i sirina, sirina>visina
    //broj redaka i stupaca spremljeni su u int r i s
    //sirina kvadratica je spremljena u kv

    float kv=0.0;
    if(redaka<=stupaca) {r=redaka; s=stupaca; c='l';}     //--> inverzija upucuje na portrait orijentaciju slike
     else {s=redaka; r=stupaca; c='p';}                  //postavljam vrijednosti tako da se papir iskoristi maksimalno
     
     if(c=='l' && visina>sirina) {float temp=visina; visina=sirina; sirina=temp;}
                                                        //r<s jer je papir po defaultu u racunu orijentiran landscape
    kv=ceil((visina-10.0)/r)-0.5;
    if((s*kv)<sirina-10) {printf("Gornja/donja margina: %.1fmm i %.1fmm\nLijeva/desna margina: %.1fmm \nSirina kvadratica: %.1f\n\n", (visina-r*kv)/2, sirina-s*kv-(visina-r*kv)/2, (visina-r*kv)/2, kv);}
     //slucajevi ovisno o tome izlazi li sirina slike izvan okvira papira

    kv=floor((visina-10.0)/r);
    if((s*kv)<sirina-10) {printf("Gornja/donja margina: %.1fmm i %.1fmm\nLijeva/desna margina: %.1fmm \nSirina kvadratica: %.1f\n", (visina-r*kv)/2, sirina-s*kv-(visina-r*kv)/2, (visina-r*kv)/2, kv);}

    else
        {
            while((s*kv)>=sirina-10) {kv-=0.5;}
            if(c=='l')
                printf("Gornja/donja margina: %.1fmm i %.1fmm\nLijeva/desna margina: %.1fmm \nSirina kvadratica: %.1f\n", (sirina-s*kv)/2, visina-r*kv-(sirina-s*kv)/2, (sirina-s*kv)/2, kv);
            else
                printf("Gornja/donja margina: %.1fmm \nLijeva/desna margina: %.1fmm i %.1fmm\nSirina kvadratica: %.1f\n", (sirina-s*kv)/2, (sirina-s*kv)/2, visina-r*kv-(sirina-s*kv)/2, kv);
        }
    printf("--> Gornje mjere vrijede za papir postavljen vodoravno! <--\n");
    return 0;
}
