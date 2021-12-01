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
    s = fopen(nazev, "r");
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
int alloc_MnozinaPismena(Tmnozina *a, int radek)
{
    a->pole[radek] = (char*)malloc(sizeof(char));
    if (a->pole[radek] == NULL) return 0;
    return 1;
}

int realloc_MnozinaPismena(Tmnozina *a, int pocet, int radek)
{
    a->pole[radek] = (char*)realloc(a->pole[radek], pocet*(sizeof(char)));
    if (a->pole[radek] == NULL) return 0;
    return 1;
}

void nacteni_Moz(FILE *soub, Tdata *data);

void nacteni_Uni(FILE *soub, Tdata *data)
{
    char a;
    int r = 0, s = 0; //pocitadla na radky sloupce
    a = fgetc(soub);
    while (a != '\n')
    {
        printf("%c\n", a);
        if(a == ' ')
        {
            data->univerzum.pole[r][s] = '\0'; //kazde pole je ukonceno '\0'
            r++;
            s = 0;
            data->univerzum.pocet_prvku = r;
            realloc_Mnozina(&(data->univerzum), r+1);
            alloc_MnozinaPismena(&(data->univerzum),r);
        }
        else 
        {
            data->univerzum.pole[r][s] = a;
            s++;
            realloc_MnozinaPismena(&(data->univerzum), s+1, r); /****Pridat odladeni****/
        }
        a = fgetc(soub);
    }
    data->univerzum.pole[r][s] = '\0'; //kazde pole je ukonceno '\0'
    r++;
    s = 0;
    data->univerzum.pocet_prvku = r;
    realloc_Mnozina(&(data->univerzum), r+1);
    alloc_MnozinaPismena(&(data->univerzum),r);
    data->univerzum.pole[r] = NULL;
        
}


int nacti_Soubor(FILE *soub, Tdata *data, Toperace *operace)
{
    char a;
    int r = 0, s = 0; //pocitadla na radky sloupce
    while((a = fgetc(soub)) != EOF)
    {
        printf("%c\n", a);
        fgetc(soub);        //Po uvozovacim znaku U/C/R/S je mezera, timto ji preskocim
        switch (a)
        {
        case 'U': //nactitanni jednotlivych slov univerza
            nacteni_Uni(soub, data);
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

void tisk (Tdata a)
{
    for(int i = 0; i <a.univerzum.pocet_prvku; printf("%s\n", a.univerzum.pole[i++])){}
}


int main (int argc, char *argv[])
{
    FILE *soubor=fopen(argv[1], "r");
    Tdata data;
    Toperace *operace;
    int pocet_operaci;
    
    //oteri_soubor(soubor, argv[1]);  
      ///Ted se bude alokovat pamet jednotlivych dinamickych poli vsdy na 1 prvek
    alloc_Operace(operace);            
    alloc_Mnozina(&(data.univerzum));
    alloc_MnozinaPismena(&(data.univerzum),0);  /****Pridat odladeni****/
    nacti_Soubor(soubor,&data,operace);
    tisk(data);
    /*for(int i=0; i<1000; i++)
    {
        alloc_Mnozina(&(data.mnoziny[i]));
        alloc_MnozinaPismena(&(data.mnoziny[i]));
    }        */
    

    //fclose(soubor);
    return 0;
}