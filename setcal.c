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



void nacteni_Moz(FILE *soub, Tdata *data, int radek)
{
    char a;
    int r = 0, s = 0; //pocitadla na radky sloupce
    a = fgetc(soub);
    while (a != '\n')
    {
        printf("%c\n", a);
        if(a == ' ')
        {
            data->mnoziny[radek].pole[r][s] = '\0'; //kazde pole je ukonceno '\0'
            r++;
            s = 0;
            data->mnoziny[radek].pocet_prvku = r;
            realloc_Mnozina(&(data->mnoziny[radek]), r+1);
            alloc_MnozinaPismena(&(data->mnoziny[radek]),r);
        }
        else
        {
            data->mnoziny[radek].pole[r][s] = a;
            s++;
            realloc_MnozinaPismena(&(data->mnoziny[radek]), s+1, r); /****Pridat odladeni****/
        }
        a = fgetc(soub);
    }
    data->mnoziny[radek].pole[r][s] = '\0'; //kazde pole je ukonceno '\0'
    r++;
    s = 0;
    data->mnoziny[radek].pocet_prvku = r;
    realloc_Mnozina(&(data->mnoziny[radek]), r+1);
    alloc_MnozinaPismena(&(data->mnoziny[radek]),r);
    data->mnoziny[radek].pole[r] = NULL;
}


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
    int r = 0; //pocitadla na radky sloupce
    while((a = fgetc(soub)) != EOF)
    {
        printf("%c\n", a);
        fgetc(soub);        //Po uvozovacim znaku U/C/R/S je mezera, timto ji preskocim
        switch (a)
        {
            case 'U': //nactitanni jednotlivych slov univerza
                nacteni_Uni(soub, data);
                r++;
                break;

            case 'S':  //nactitanni jednotlivych slov mnozin
                alloc_Mnozina(&(data->mnoziny[r]));
                alloc_MnozinaPismena(&(data->mnoziny[r]),0);
                nacteni_Moz(soub,data,r);
                data->pocet_mnozin = r++;
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

void tisk (Tmnozina a)
{
    for(int i = 0; i <a.pocet_prvku; printf("%s ", a.pole[i++])){}
}

void prazdna_mnozina(Tdata *data, int radek) {
    if(data->mnoziny[radek-2].pocet_prvku == 0) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

void pocet_prvku(Tdata *data, int radek) {
    printf("%d\n", data->mnoziny[radek-2].pocet_prvku);
}
void doplnek(Tdata *data, int radek) {
    int jeDoplnek = 1;

    printf("S");

    for (int i = 0; i < data->univerzum.pocet_prvku; i++) {
        jeDoplnek = 1;
        for (int j = 0; j < data->mnoziny[radek-2].pocet_prvku; j++) {
            if(!strcmp(data->univerzum.pole[i], data->mnoziny[radek-2].pole[j])) {
                jeDoplnek = 0;
                break;
            }
        }
        if(jeDoplnek) {
            printf(" %s", data->univerzum.pole[i]);
        }
    }
    printf("\n");
}

void sjednoceni(Tdata *data, int radek1, int radek2) {
    printf("S");

    for (int i = 0; i < data->mnoziny[radek1-2].pocet_prvku; i++) {
        printf(" %s", data->mnoziny[radek1-2].pole[i]);
    }

    int jeDoplnek = 1;

    for (int i = 0; i < data->mnoziny[radek2-2].pocet_prvku; i++) {
        jeDoplnek = 1;
        for (int j = 0; j < data->mnoziny[radek1-2].pocet_prvku; j++) {
            if(!strcmp(data->mnoziny[radek2-2].pole[i], data->mnoziny[radek1-2].pole[j])) {
                jeDoplnek = 0;
                break;
            }
        }
        if(jeDoplnek) {
            printf(" %s", data->mnoziny[radek2-2].pole[i]);
        }
    }
    printf("\n");
}

void prunik(Tdata *data, int radek1, int radek2) {
    int jePrunik = 0;

    printf("S");

    for (int i = 0; i < data->mnoziny[radek1-2].pocet_prvku; i++) {
        jePrunik = 0;
        for (int j = 0; j < data->mnoziny[radek2-2].pocet_prvku; j++) {
            if(!strcmp(data->mnoziny[radek1-2].pole[i], data->mnoziny[radek2-2].pole[j])) {
                jePrunik = 1;
                break;
            }
        }
        if (jePrunik) {
            printf(" %s", data->mnoziny[radek1-2].pole[i]);
        }
    }
    printf("\n");
}

void rozdil(Tdata *data, int radek1, int radek2) {
    int jeRozdil = 0;

    printf("S");

    for (int i = 0; i < data->mnoziny[radek1-2].pocet_prvku; i++) {
        jeRozdil = 0;
        for (int j = 0; j < data->mnoziny[radek2-2].pocet_prvku; j++) {
            if(!strcmp(data->mnoziny[radek1-2].pole[i], data->mnoziny[radek2-2].pole[j])) {
                jeRozdil = 1;
                break;
            }
        }
        if (!jeRozdil) {
            printf(" %s", data->mnoziny[radek1-2].pole[i]);
        }
    }
    printf("\n");
}

void podmnozina(Tdata *data, int radek1, int radek2) {
    int jePodmnozina = 1;
    int jsouPodmnoziny[data->mnoziny[radek1-2].pocet_prvku];

    if (data->mnoziny[radek1-2].pocet_prvku > data->mnoziny[radek2-2].pocet_prvku) {
        printf("false\n");
    } else {

        for (int i = 0; i < data->mnoziny[radek1-2].pocet_prvku; i++) {
            jsouPodmnoziny[i] = 0;
        }

        for (int i = 0; i < data->mnoziny[radek1-2].pocet_prvku; i++) {
            for (int j = 0; j < data->mnoziny[radek2-2].pocet_prvku; j++) {
                if (!strcmp(data->mnoziny[radek1-2].pole[i], data->mnoziny[radek2-2].pole[j])) {
                    jsouPodmnoziny[i] = 1;
                }
            }
        }

        for (int i = 0; i < data->mnoziny[radek1-2].pocet_prvku; i++) {
            if (!jsouPodmnoziny[i]) {
                jePodmnozina = 0;
                break;
            }
        }

        if (jePodmnozina) printf("true\n");
        else printf("false\n");
    }
}

void vlastni_podmnozina(Tdata *data, int radek1, int radek2) {
    if (data->mnoziny[radek1-2].pocet_prvku >= data->mnoziny[radek2-2].pocet_prvku) {
        printf("false\n");
    } else {
        podmnozina(data, radek1, radek2);
    }
}

void rovnost(Tdata *data, int radek1, int radek2) {
    if (data->mnoziny[radek1-2].pocet_prvku != data->mnoziny[radek2-2].pocet_prvku) {
        printf("false\n");
    } else {
        podmnozina(data, radek1, radek2);
    }
}

void vypis_operace(Tdata *data, Toperace **mnozina_operaci, int pocet_operaci) {

    for (int i = 0; i < pocet_operaci; i++) {
        if (!strcmp(mnozina_operaci[i]->operace, "empty")) {
            prazdna_mnozina(data, mnozina_operaci[i]->a);
        } else if (!strcmp(mnozina_operaci[i]->operace, "card")) {
            pocet_prvku(data, mnozina_operaci[i]->a);
        } else if (!strcmp(mnozina_operaci[i]->operace, "complement")) {
            doplnek(data, mnozina_operaci[i]->a);
        } else if (!strcmp(mnozina_operaci[i]->operace, "union")) {
            sjednoceni(data, mnozina_operaci[i]->a, mnozina_operaci[i]->b);
        } else if (!strcmp(mnozina_operaci[i]->operace, "intersect")) {
            prunik(data, mnozina_operaci[i]->a, mnozina_operaci[i]->b);
        } else if (!strcmp(mnozina_operaci[i]->operace, "minus")) {
            rozdil(data, mnozina_operaci[i]->a, mnozina_operaci[i]->b);
        } else if (!strcmp(mnozina_operaci[i]->operace, "subseteq")) {
            podmnozina(data, mnozina_operaci[i]->a, mnozina_operaci[i]->b);
        } else if (!strcmp(mnozina_operaci[i]->operace, "subset")) {
            vlastni_podmnozina(data, mnozina_operaci[i]->a, mnozina_operaci[i]->b);
        } else if (!strcmp(mnozina_operaci[i]->operace, "equals")) {
            rovnost(data, mnozina_operaci[i]->a, mnozina_operaci[i]->b);
        } else if (!strcmp(mnozina_operaci[i]->operace, "reflexive")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "symmetric")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "antisymmetric")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "transitive")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "function")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "domain")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "codomain")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "injective")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "surjective")) {
            ;
        } else if (!strcmp(mnozina_operaci[i]->operace, "bijective")) {
            ;
        } else {
            printf("Neplatna operace!");
        }
    }
}

int main (int argc, char *argv[])
{
    FILE *soubor=fopen(argv[1], "r");
    Tdata data;
    data.pocet_mnozin = data.pocet_relaci = 0;
    Toperace *operace;
    int pocet_operaci;

    //oteri_soubor(soubor, argv[1]);
    ///Ted se bude alokovat pamet jednotlivych dinamickych poli vsdy na 1 prvek
    alloc_Operace(operace);
    alloc_Mnozina(&(data.univerzum));
    alloc_MnozinaPismena(&(data.univerzum),0);  /****Pridat odladeni****/
    nacti_Soubor(soubor,&data,operace);
    printf("\n");
    tisk(data.univerzum);
    printf("\n");
    for (int i = 0; i < data.pocet_mnozin+3; i++)
    {
        tisk(data.mnoziny[i]);
        printf("\n");
    }



    //fclose(soubor);
    return 0;
}