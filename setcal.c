#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
     char **pole;
    int pocet_prvku;
}Tmnozina;

typedef struct {
    char *a;
    char *b;
}Trelace;

typedef struct {
    Trelace *relace;
    int pocet;
}TmnozinaRelaci;

typedef struct {
    Tmnozina univerzum;
    Tmnozina mnoziny[1000];
    TmnozinaRelaci relace[1000];
    int pocet_mnozin, pocet_relaci;
}Tdata;

typedef struct {
    char *operace;
    int a;
    int b;
}Toperace;

int oteri_soubor(FILE *s, char *nazev)
{
    s = fopen (nazev, "r");
    if( s == NULL) return 0;
    return 1;
}


//Alokace operaci
int alloc_Operace(Toperace *a)
{
    a = (Toperace*)malloc(sizeof(Toperace));
    if (a == NULL) return 0;
    return 1;
}

int realloc_Operace(Toperace *a, int pocet)
{
    a = (Toperace*)realloc(a, pocet*(sizeof(Toperace)));
    if (a == NULL) return 0;
    return 1;
}

/////Alokace pameti pro slova mnozin
int alloc_Mnozina(Tmnozina *a)
{
    a->pole = (char**)malloc(sizeof(char*));
    if (a->pole == NULL) return 0;
    return 1;
}

int realloc_Mnozina(Tmnozina *a, int pocet)
{
    a->pole = (char**)realloc(a->pole, pocet*(sizeof(char*)));
    if (a->pole == NULL) return 0;
    return 1;
}

/////Alokace pameti pro pismena mnozin
int alloc_MnozinaPismena(Tmnozina *a)
{
    a->pole[0] = (char*)malloc(sizeof(char));
    if (a->pole == NULL) return 0;
    return 1;
}

int realloc_MnozinaPismena(Tmnozina *a, int pocet, int radek)
{
    a->pole[radek] = (char*)realloc(a->pole[radek], pocet*(sizeof(char)));
    if (a->pole[radek] == NULL) return 0;
    return 1;
}




int nacti_Soubor(FILE *soub, Tdata *data, Toperace *operace)
{
    char *a, *nic;
    int r = 0, s = 0; //pocitadla na radky sloupce
    while((fgets(a,1,soub)) != NULL)
    {
        fgets(nic,1,soub); //Po uvozovacim znaku U/C/R/S je mezera, timto ji preskocim
        switch (a[0])
        {
        case 'U': //nactitanni jednotlivych slov univerza
            (fgets(a,1,soub)); 
            while (a[0] != '\n')
            {
                if(a[0] == ' ')
                {
                    data->univerzum.pole[r][s] = '\0'; //kazde pole je ukonceno '\0'
                    r++;
                    s = 0;
                    data->univerzum.pocet_prvku = r;
                    realloc_Mnozina(&(data->univerzum), r+1);
                    break;
                }
                data->univerzum.pole[r][s] = a[0];
                s++;
                realloc_MnozinaPismena(&(data->univerzum), s+1, r); /****Pridat odladeni****/
                (fgets(a,1,soub));
            }
            
            break;
        
        case 'S':  //nactitanni jednotlivych slov mnozin
            break;

        case 'R': //nactitanni jednotlivych relaci
            break;

        case 'C': //nactitanni jednotlivych operaci
            break;
        default:
            break;
        }
    }
    return 0;
}

int main (int argc, char *argv[])
{
    FILE *soubor;
    Tdata data;
    Toperace *operace;
    int pocet_operaci;

    oteri_soubor(soubor, argv[1]);    ///Ted se bude alokovat pamet jednotlivych dinamickych poli vsdy na 1 prvek
    alloc_Operace(operace);             
    alloc_Mnozina(&(data.univerzum));
    alloc_MnozinaPismena(&(data.univerzum));   /****Pridat odladeni****/
    for(int i=0; i<1000; i++)
    {
        alloc_Mnozina(&(data.mnoziny[i]));
        alloc_MnozinaPismena(&(data.mnoziny[i]));
    }        
    

    fclose(soubor);
    return 0;
}