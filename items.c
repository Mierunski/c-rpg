#include "items.h"

struct przedmiot* wczytajPrzedmioty(int * liczba)
{
    FILE *fp;

    // sprawdzanie ilosci linii w pliku
    fp = fopen("items.txt", "r");
    int i, j = 1, liczbaP;

    char buf2[35], znak;

    while((znak = getc(fp)) != EOF)
    {
        if(znak == '\n') ++j;
        //printf("%c", znak);
    }

    //printf("\nIlosc linii: %d\n", j);
    fclose(fp);

    fp = fopen("items.txt", "r");
    liczbaP = j/4;
    struct przedmiot *lista = malloc(liczbaP*sizeof(struct przedmiot));
    int bufferD;
    for(i = 0; i < liczbaP; i++)
    {
        fgets(buf2, 35, fp);
        for(j = 0; j < 35; j++) if(buf2[j] == '\n') buf2[j] = 0;
        sprintf(lista[i].nazwa, buf2);
        fgets(buf2, 20, fp);
        sscanf(buf2, "%d", &bufferD);
        lista[i].stat = bufferD;
        fgets(buf2, 20, fp);
        sscanf(buf2, "%d", &bufferD);
        lista[i].typ = bufferD;
        fgets(buf2, 20, fp);
        sscanf(buf2, "%d", &bufferD);
        lista[i].poziom = bufferD;
    }


    *liczba = liczbaP;
    fclose(fp);
    return lista;
}


struct przedmiot losujPrzedmiot(int ilosc, struct przedmiot lista[], int reg)
{
    int x;
    struct przedmiot item;
    do
    {
        x = rand()%ilosc;

        item.stat = lista[x].stat;
        item.typ = lista[x].typ;
        item.poziom = lista[x].poziom;

        strcpy(item.nazwa, lista[x].nazwa);
    } while(item.poziom != reg);

    return item;

}
