#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    int pocet;
}Tdata;

typedef struct {
    char *operace;
    int a;
    int b;
}Toperace;

void tiskR (TmnozinaRelaci a);

int oteri_soubor(FILE **s, char *nazev)
{
    *s = fopen(nazev, "r");
    if( s == NULL) return 0;
    return 1;
}

void chybaOp()
{
    printf("V souboru na radku s operacemi se vyskytla chyba v zadani operace.\n");
}

void chybaRadek(int a)
{
    printf("V souboru na %d. radku se vyskytla chyba v zadani operace.\n", a);
}

//Alokace operaci
int alloc_Operace(Toperace **a)
{
    *a = (Toperace*)malloc(sizeof(Toperace));
    if (a == NULL) return 0;
    return 1;
}

int realloc_Operace(Toperace **a, int pocet)
{
    *a = (Toperace*)realloc(*a, pocet*(sizeof(Toperace)));
    if (a == NULL) return 0;
    return 1;
}

int alloc_OP(char **s)
{
    *s = (char*)malloc(sizeof(char));
    if (s == NULL) return 0;
    return 1;
}

int realloc_OP(char **s,int pocet)
{
    *s = (char*)realloc(*s, pocet*(sizeof(char)));
    if (s == NULL) return 0;
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

/////Alokace pameti pro prvky relaci
int alloc_RelAB(Trelace *s)
{
    s->a = (char*)malloc(sizeof(char));
    s->b = (char*)malloc(sizeof(char));
    if (s->a == NULL || s->b == NULL) return 0;
    return 1;
}

int realloc_RelAB(char **s, int pocet)
{
    *s = (char*)realloc(*s, pocet*(sizeof(char)));
    if (s == NULL) return 0;
    return 1;
}

/////Alokace pameti pro relace
int alloc_Relace(TmnozinaRelaci *s)
{
    s->relace = (Trelace*)malloc(sizeof(Trelace));
    if (s->relace == NULL) return 0;
    return 1;
}

int realloc_Relace(TmnozinaRelaci *s, int pocet)
{
    s->relace = (Trelace*)realloc(s->relace, pocet*sizeof(Trelace));
    if (s->relace == NULL) return 0;
    return 1;
}

void pT()
{
    printf("true\n");
}

void pF()
{
    printf("false\n");
}


int kontrolaR(Tdata *data, int radek)
{
    for(int i=0; i<data->relace[radek].pocet; i++){
        if(strcmp(data->relace[radek].relace[i].a, data->relace[radek].relace[i].b)!=0) // kontroluje jestli se prvky relace rovnaji
        {
            return 0;
        }

    }

    return 1;
}

void reflexivita(Tdata *data, int radek)
{
    if(kontrolaR(data, radek)==1)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

}

int kontrolaSy(Tdata *data, int radek, int start)
{
    char *a = data->relace[radek].relace[0].a;
    char *b = data->relace[radek].relace[0].b;
    for( int i = start; i < data->relace[radek].pocet; i++)
    {
        if(strcmp(a, data->relace[radek].relace[i].b) == 0 )
        {
            if(strcmp(b, data->relace[radek].relace[i].a) == 0 )
            {
                return 1;
            }

        }
    }
    return 0;
}

int symPom(Tdata *data, int radek)
{
    for (int  i = 0; i < data->relace[radek].pocet; i++)
    {
        if (kontrolaSy(data, radek, i) == 0) return 0;

    }
    return 1;

}

void symetricka(Tdata *data, int radek)
{

    if (symPom(data, radek))
    {
        pT();
        return;
    }
    pF();
}

void antisymetricka(Tdata *data, int radek)
{

    if (symPom(data, radek))
    {
        pF();
        return;
    }
    pT();
}


void nacteni_Moz(FILE *soub, Tdata *data, int radek)
{
    char a;
    int r = 0, s = 0; //pocitadla na radky sloupce
    a = fgetc(soub);
    while (a != '\n')
    {
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

void nacti_Rel(FILE *soub, Tdata *data, int radek)
{
    char a;
    int r = 0, s = 0;  //pocitadla na radky sloupce
    a = fgetc(soub);
    while (a != '\n')
    {
        a = fgetc(soub);
        if (a == '(') ///Otevreni relace
        {
            a = fgetc(soub);
            while (a != ')') ///Hlida ukonceni relace
            {
                while (a != ' ') /// Nacte prvni slovo
                {
                    data->relace[radek].relace[r].a[s] = a;
                    s++;
                    realloc_RelAB(&(data->relace[radek].relace[r].a), s+1); /****Pridat odladeni****/
                    a = fgetc(soub);
                }
                data->relace[radek].relace[r].a[s] = '\0'; //kazde pole je ukonceno '\0'
                s = 0;
                a = fgetc(soub);
                while (a != ')') ///Nacte druhe slovo
                {
                    data->relace[radek].relace[r].b[s] = a;
                    s++;
                    realloc_RelAB(&(data->relace[radek].relace[r].b), s+1); /****Pridat odladeni****/
                    a = fgetc(soub);
                }

                data->relace[radek].relace->b[s] = '\0'; //kazde pole je ukonceno '\0'
                s = 0;


            }
            r++;
            data->relace[radek].pocet = r;
            realloc_Relace(&(data->relace[radek]), r+1);///Priprava ppameti pro novou relaci
            alloc_RelAB(&(data->relace[radek].relace[r]));
            a = fgetc(soub);
        }
    }
    //data->relace[radek].relace = NULL;
}


int nacti_Ope(FILE *soub, Toperace operace[],  int radek)
{
    char a = 'z';
    int r = 0;  //pocitadla na radky sloupce
    a = fgetc(soub);
    while (a != ' ') /// Nacte prvni slovo
    {
        operace[radek].operace[r] = a;
        r++;
        realloc_OP(&(operace[radek].operace), r+1);
        printf("%s\n", operace[radek].operace);
        printf("%d..%c\n", __LINE__, a);
        a = fgetc(soub);
    }

    char pom[]= {fgetc(soub)}, *text;
    int b = 0, c;
    while (pom[0] != ' ')  //Nacte prvni cislo
    {
        printf("%dAA\n", __LINE__);
        c = (int)strtol(pom, &text, 10);
        if(strlen(text) != 0)
        {
            printf("%d\n", __LINE__);
            chybaOp();
            return -1;
        }
        b = b*10+c;
        pom[0] = fgetc(soub);
        if(pom[0] == EOF) {
            operace[radek].a = a;
            return 0;
        }
        if(pom[0] == '\n') {
            operace[radek].a = a;
            return 0;
        }
    }

    operace[radek].a = b;
    b = 0;
    pom[0] = fgetc(soub);
    while (pom[0] != '\n') //Nacte druhe cislo  pokud je
    {
        printf("%d\n", __LINE__);
        c = (int)strtol(pom, &text, 10);
        if(strlen(text) != 0)
        {
            printf("%d\n", __LINE__);
            chybaOp();
            return -1;
        }
        b = b*10+c;
        pom[0] = fgetc(soub);
        if(pom[0] == EOF) {
            operace[radek].b = b;
            return 0;
        }
    }
    operace[radek].b = b;
    return 1;
}

int nacti_OpePom(FILE *soub, Toperace operace[])
{
    char a = ' ';
    int i, pom;
    
    for (i = 0; a != EOF; i++)
    {   a = fgetc(soub);
        if (a == 'C') a = fgetc(soub);
        pom = nacti_Ope(soub, operace, i);
        printf("%d\n", __LINE__);
        //realloc_Operace(&operace, i+2);
        if( pom == -1) return -1;
        if( pom == 0) //kdy konci radkem s operaci
        {
            for (int j = 0; j < i+1; j++) 
            {
                printf(" %s %d %d\n", operace[j].operace, operace[j].a, operace[j].b);
            }
            printf("%p|KONEC|\n", operace);
            return i+1;
        }
        //realloc_Operace(&operace, i+2);
        alloc_OP(&(operace[i+1].operace));
        a = fgetc(soub);
    }
    for (int j = 0; j < i; j++) //kdyz soubor konci prazdnym radkem
    {
        printf(" %s %d %d\n", operace[j].operace, operace[j].a, operace[j].b);
    }
    printf("%p|KONEC|\n", operace);
    return i;
    
}

int nacti_Soubor(FILE *soub, Tdata *data, Toperace *operace, int *pocet_operaci)
{

    char a;
    int r = 0 , g; //pocitadla na radky sloupce
    while((a = fgetc(soub)) != EOF)
    {
               //Po uvozovacim znaku U/C/R/S je mezera, timto ji preskocim
        switch (a)
        {
        case 'U': //nactitanni jednotlivych slov univerza
            fgetc(soub); 
            alloc_Mnozina(&(data->univerzum));
            alloc_MnozinaPismena(&(data->univerzum),0);
            nacteni_Uni(soub, data);
            r++;
            data->pocet = r;
            break;
        
        case 'S':  //nactitanni jednotlivych slov mnozin
            fgetc(soub); 
            alloc_Mnozina(&(data->mnoziny[r]));
            alloc_MnozinaPismena(&(data->mnoziny[r]),0);
            nacteni_Moz(soub,data,r);
            r++;
            data->pocet = r;
            break;

        case 'R': //nactitanni jednotlivych relaci
            alloc_Relace(&(data->relace[r]));
            alloc_RelAB(&(data->relace[r].relace[0]));
            nacti_Rel(soub, data, r);
            r++;
            data->pocet = r;
            break;

        case 'C': //nactitanni jednotlivych operaci
            //alloc_Operace(&operace);
            printf("%p|PRED|\n", operace);
            alloc_OP(&(operace[0].operace));
            g = nacti_OpePom(soub, operace);
            printf("%p|PO|\n", operace);
            printf("A sem uz se posle prazdne pole operaci\n");
            printf("kontrola v souboru %s\n", operace[4].operace);
            printf("lf %ld\n", sizeof(operace[2]).operace);
            printf("%d", __LINE__);
            *pocet_operaci = g;
            if(*pocet_operaci == -1) return -1;
            return 1;
            break;
        default:
            chybaRadek(r);
            return -1;
            break;
        }
    }
    return 1;
}

void tiskM (Tmnozina a)
{
    for(int i = 0; i <a.pocet_prvku; printf("%s ", a.pole[i++])){}
}

void tiskR (TmnozinaRelaci a)
{
    for(int i = 0; i <a.pocet; i++){ printf("(%s, %s) ", a.relace[i].a,a.relace[i].b); }
}



// Funkce nad mnozinami
void prazdna_mnozina(Tdata *data, int radek) {
    if(data->mnoziny[radek-1].pocet_prvku == 0) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

void pocet_prvku(Tdata *data, int radek) {
    printf("%d\n", data->mnoziny[radek-1].pocet_prvku);
}

void doplnek(Tdata *data, int radek) {
    int jeDoplnek = 1;

    printf("S");

    // Projede prvky univerza a porovna je s prvky zadane mnoziny, podle toho je bud vypise a nebo ne
    for (int i = 0; i < data->univerzum.pocet_prvku; i++) {
        jeDoplnek = 1;
        for (int j = 0; j < data->mnoziny[radek-1].pocet_prvku; j++) {
            if(!strcmp(data->univerzum.pole[i], data->mnoziny[radek-1].pole[j])) {
                jeDoplnek = 0;
                break;
            }
        }
        if(jeDoplnek) {
            printf(" %s", data->univerzum.pole[i]); // Pokud patri dany prvek do doplnku, vypis jej
        }
    }
    printf("\n");
}

void sjednoceni(Tdata *data, int radek1, int radek2) {
    printf("S");

    // Vypise celou mnozinu na radku radek1, protoze ta bude soucasti sjednoceni vzdy
    for (int i = 0; i < data->mnoziny[radek1-1].pocet_prvku; i++) {
        printf(" %s", data->mnoziny[radek1-1].pole[i]);
    }

    int jeDoplnek = 1;
    // Opet hleda doplnek mnoziny na radku radek2 podle mnoziny na radku radek1 a podle toho jej vypise
    for (int i = 0; i < data->mnoziny[radek2-1].pocet_prvku; i++) {
        jeDoplnek = 1;
        for (int j = 0; j < data->mnoziny[radek1-1].pocet_prvku; j++) {
            if(!strcmp(data->mnoziny[radek2-1].pole[i], data->mnoziny[radek1-1].pole[j])) {
                jeDoplnek = 0;
                break;
            }
        }
        if(jeDoplnek) {
            printf(" %s", data->mnoziny[radek2-1].pole[i]);
        }
    }
    printf("\n");
}

void prunik(Tdata *data, int radek1, int radek2) {
    int jePrunik = 0;

    printf("S");

    // Postupne porovnava prvky z jedne mnoziny s prvky druhe mnoziny a podle toho nastavuje promennou jePrunik
    for (int i = 0; i < data->mnoziny[radek1-1].pocet_prvku; i++) {
        jePrunik = 0;
        for (int j = 0; j < data->mnoziny[radek2-1].pocet_prvku; j++) {
            if(!strcmp(data->mnoziny[radek1-1].pole[i], data->mnoziny[radek2-1].pole[j])) {
                jePrunik = 1;
                break;
            }
        }
        if (jePrunik) {
            printf(" %s", data->mnoziny[radek1-1].pole[i]); // Pokud je prvek v pruniku, vypis jej
        }
    }
    printf("\n");
}

void rozdil(Tdata *data, int radek1, int radek2) {
    int jeRozdil = 1;

    printf("S");

    // Postupne porovnava prvky z jedne mnoziny s prvky druhe mnoziny a podle toho nastavuje promennou jeRozdil
    for (int i = 0; i < data->mnoziny[radek1-1].pocet_prvku; i++) {
        jeRozdil = 1;
        for (int j = 0; j < data->mnoziny[radek2-1].pocet_prvku; j++) {
            if(!strcmp(data->mnoziny[radek1-1].pole[i], data->mnoziny[radek2-1].pole[j])) {
                jeRozdil = 0;
                break;
            }
        }
        if (jeRozdil) {
            printf(" %s", data->mnoziny[radek1-1].pole[i]); // Pokud prvek patri do rozdilu, vypis jej
        }
    }
    printf("\n");
}

void podmnozina(Tdata *data, int radek1, int radek2) {
    int jePodmnozina = 1;
    int jsouPodmnoziny[data->mnoziny[radek1-1].pocet_prvku]; // Pole integeru o delce poctu prvku prvni mnoziny

    if (data->mnoziny[radek1-1].pocet_prvku > data->mnoziny[radek2-1].pocet_prvku) {
        printf("false\n"); // Pokud ma prvni mnozina vic prvku, nez druha, nemuze byt jeji podmnozinou
    } else {

        // Naplni pole jsouPodmnoziny samymi nulami
        for (int i = 0; i < data->mnoziny[radek1-1].pocet_prvku; i++) {
            jsouPodmnoziny[i] = 0;
        }

        // Pro kazdy prvek prvni mnoziny zkontroluje, zda patri do druhe mnoziny a podle toho nastavi prislusnou hodnotu v poli jsouPodmnoziny
        for (int i = 0; i < data->mnoziny[radek1-1].pocet_prvku; i++) {
            for (int j = 0; j < data->mnoziny[radek2-1].pocet_prvku; j++) {
                if (!strcmp(data->mnoziny[radek1-1].pole[i], data->mnoziny[radek2-1].pole[j])) {
                    jsouPodmnoziny[i] = 1;
                }
            }
        }

        // Zkontroluje, zda je pole jsouPodmnoziny cele zaplnene jednickami, pokud ne, prvni mnozina neni podmnozinou druhe
        for (int i = 0; i < data->mnoziny[radek1-1].pocet_prvku; i++) {
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

    // Pokud je pocet prvku prvni mnoziny >= poctu prvku druhe mnoziny, prvni mnozina nemuze byt vlastni podmnozinou druhe
    if (data->mnoziny[radek1-1].pocet_prvku >= data->mnoziny[radek2-1].pocet_prvku) {
        printf("false\n");
    } else {
        // Potom uz jen staci zkontrolovat, zda je podmnozinou
        podmnozina(data, radek1, radek2);
    }
}

void rovnost(Tdata *data, int radek1, int radek2) {

    // Pokud se pocty prvku v mnozinach nerovnaji, nemohou se rovnat ani mnoziny
    if (data->mnoziny[radek1-1].pocet_prvku != data->mnoziny[radek2-1].pocet_prvku) {
        printf("false\n");
    } else {
        // Potom uz jen staci zkontolovat, zda je libovolna z mnozin podmnozinou te druhe
        podmnozina(data, radek1, radek2);
    }
}

void vypis_operace(Tdata *data, Toperace *mnozina_operaci, int pocet_operaci) {

    for (int i = 0; i < pocet_operaci; i++) {
        if (!strcmp(mnozina_operaci[i].operace, "empty")) {
            prazdna_mnozina(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "card")) {
            pocet_prvku(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "complement")) {
            doplnek(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "union")) {
            sjednoceni(data, mnozina_operaci[i].a, mnozina_operaci[i].b);
        } else if (!strcmp(mnozina_operaci[i].operace, "intersect")) {
            prunik(data, mnozina_operaci[i].a, mnozina_operaci[i].b);
        } else if (!strcmp(mnozina_operaci[i].operace, "minus")) {
            rozdil(data, mnozina_operaci[i].a, mnozina_operaci[i].b);
        } else if (!strcmp(mnozina_operaci[i].operace, "subseteq")) {
            podmnozina(data, mnozina_operaci[i].a, mnozina_operaci[i].b);
        } else if (!strcmp(mnozina_operaci[i].operace, "subset")) {
            vlastni_podmnozina(data, mnozina_operaci[i].a, mnozina_operaci[i].b);
        } else if (!strcmp(mnozina_operaci[i].operace, "equals")) {
            rovnost(data, mnozina_operaci[i].a, mnozina_operaci[i].b);
        } else if (!strcmp(mnozina_operaci[i].operace, "reflexive")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "symmetric")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "antisymmetric")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "transitive")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "function")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "domain")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "codomain")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "injective")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "surjective")) {
            ;
        } else if (!strcmp(mnozina_operaci[i].operace, "bijective")) {
            ;
        } else {
            printf("Neplatna operace!");
        }
    }
}

int main (int argc, char *argv[])
{
    argc = 0; // potrebuji se zbavit erroru unused argc xD

    FILE *soubor=fopen(argv[1], "r");
    Tdata data;
    data.pocet = argc;
    Toperace operace[50];
    int pocet_operaci;
    //oteri_soubor(soubor, argv[1]);  
    //alloc_Operace(&operace);
    //printf("%d\n", alloc_OP(&(operace[0].operace)));      
    nacti_Soubor(soubor,&data, operace, &pocet_operaci);
    printf("\n");
    tiskM(data.univerzum);
    printf("\n");
    
    for (int i = 0; i < data.pocet; i++)
    {
        tiskM(data.mnoziny[i]);
        printf("\n");
    }

    printf("%d\n", pocet_operaci);
    for (int i = 0; i < pocet_operaci; i++)
    {
        printf("%s %d %d\n", operace[i].operace, operace[i].a, operace[i].b);
        //printf("%d\n", operace[i].a);
    }
    printf("\n");printf("\n");printf("\n");
    vypis_operace(&data ,operace, pocet_operaci);
    //fclose(soubor);
    return 0;
}