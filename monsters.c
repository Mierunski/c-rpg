
#include "monsters.h"

struct potwor* wczytaj(int * liczba)
{
    FILE *fp;

    // sprawdzanie ilosci linii w pliku
    fp = fopen("monsters.txt", "r");
    int i, j = 2, liczbaPotworow;

    char *buf1, buf2[20];

    fgets(buf2, 20, fp);

    while(1)
    {
        buf1 = fgets(buf2, 20, fp);
        //printf("%s %s", buf1, buf2);
        if (buf1 != NULL)
        {
            if (feof(fp))
            {
                break;
            }
        }

        j++;
        //printf("%d %d\n", i,j);
    }


    //printf("\nIlosc linii: %d\n", j);
    fclose(fp);

    fp = fopen("monsters.txt", "r");
    liczbaPotworow = j/6;
    struct potwor *lista = malloc(liczbaPotworow*sizeof(struct potwor));
    int bufferD;
    for(i = 0; i < liczbaPotworow; i++)
    {
        fgets(buf1, 20, fp);
        for(j = 0; j < 20; j++) if(buf1[j] == '\n') buf1[j] = 0;
        sprintf(lista[i].nick, buf1);
        fgets(buf1, 20, fp);
        sscanf(buf1, "%d", &bufferD);
        lista[i].poziom = bufferD;
        fgets(buf1, 20, fp);
        sscanf(buf1, "%d", &bufferD);
        lista[i].atk = bufferD;
        fgets(buf1, 20, fp);
        sscanf(buf1, "%d", &bufferD);
        lista[i].def = bufferD;
        fgets(buf1, 20, fp);
        sscanf(buf1, "%d", &bufferD);
        lista[i].HP = bufferD;
        fgets(buf1, 20, fp);
        sscanf(buf1, "%d", &bufferD);
        lista[i].pozycja = bufferD;

    }

    /*for(i = 0; i < liczbaPotworow; i++){
        printf("%s%d\n", lista[i].nick, lista[i].poziom);
        printf("%d\n%d\n%d\n", lista[i].atk, lista[i].def, lista[i].HP);
    }*/
    *liczba = liczbaPotworow;
    fclose(fp);
    return lista;
}

// Losuje potwora
struct potwor * losujPotwora(int ilosc, struct potwor lista[], int reg)
{
    int x;
    struct potwor *potwor = malloc(sizeof(struct potwor));
    do
    {
        x = rand()%ilosc;

        potwor->atk = lista[x].atk/2 + rand()%lista[x].atk;
        potwor->def = lista[x].def/2 + rand()%lista[x].def;
        potwor->HP = lista[x].HP/2 + rand()%lista[x].HP;
        potwor->cHP = potwor->HP;
        potwor->poziom = lista[x].poziom;
        potwor->exp = (potwor->atk*3 + potwor->def*3 + potwor->HP/10 + lista[x].poziom*25)/2;
        if(potwor->atk >= lista[x].atk*1.2)
        {
            strcpy(potwor->nick, "Agresywny ");
            strcat(potwor->nick, lista[x].nick);
        }
        else if (potwor->HP >= lista[x].HP*1.2)
        {
            strcpy(potwor->nick, "Stary ");
            strcat(potwor->nick, lista[x].nick);
        }
        else if (potwor->HP <= lista[x].HP*0.8)
        {
            strcpy(potwor->nick, "Mlody ");
            strcat(potwor->nick, lista[x].nick);
        }
        else if (potwor->def >= lista[x].def*1.2)
        {
            strcpy(potwor->nick, "Pancerny ");
            strcat(potwor->nick, lista[x].nick);
        }
        else strcpy(potwor->nick, lista[x].nick);
        potwor->pozycja = lista[x].pozycja;
    }
    while(potwor->pozycja != reg);

    return potwor;
}
