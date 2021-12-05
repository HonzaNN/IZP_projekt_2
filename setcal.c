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
    int c;
}Toperace;

typedef struct obal{
    Toperace *operace;
}Tobal;


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

bool R(Tdata *data, int radek, int j)
{
    for(int i=0; i<data->relace[radek-1].pocet; i++){
        if(strcmp(data->relace[radek-1].relace[j].a, data->relace[radek-1].relace[i].b)==0) // kontroluje jestli se prvky relace rovnaji
        {
            return true;
        }

    }

    return false;
}

int kontrolaR(Tdata *data, int radek)
{
    for(int i=0; i<data->relace[radek-1].pocet; i++){
        if(!(R(data, radek, i))) // kontroluje jestli se prvky relace rovnaji
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
    char *a = data->relace[radek-1].relace[start].a;
    char *b = data->relace[radek-1].relace[start].b;
    for( int i = 0; i < data->relace[radek-1].pocet; i++)
    {
        if(strcmp(a, data->relace[radek-1].relace[i].b) == 0 )
        {
            if(strcmp(b, data->relace[radek-1].relace[i].a) == 0 )
            {
                return 1;
            }

        }
    }
    return 0;
}

int symPom(Tdata *data, int radek)
{
    for (int  i = 0; i < data->relace[radek-1].pocet; i++)
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

int kontrolaAs(Tdata *data, int radek, int start)
{
    char *a = data->relace[radek-1].relace[start].a;
    char *b = data->relace[radek-1].relace[start].b;
    for( int i = 0; i < data->relace[radek-1].pocet; i++)
    {
        if(strcmp(a, data->relace[radek-1].relace[i].b) == 0 )
        {
            if(strcmp(b, data->relace[radek-1].relace[i].a) == 0 )
            {
                return 0;
            }

        }
    }
    return 1;
}

int asPom(Tdata *data, int radek)
{
    for (int  i = 0; i < data->relace[radek-1].pocet; i++)
    {
        if (kontrolaAs(data, radek, i) == 0) return 0;

    }
    return 1;

}

void antisymetricka(Tdata *data, int radek)
{

    if (asPom(data, radek))
    {
        pT();
        return;
    }
    pF();
}

void Transitivni(Tdata *data, int radek)
{
    int RelaceJeTransitivni = 1;
    int TransitivniPole[data->relace[radek-1].pocet];  //Pocitadlo jakozto pole nul
    for(int i = 0; i < data->relace[radek-1].pocet; i++)
    {
        TransitivniPole[i] = 0;
    }

    for (int i = 0; i < data->relace[radek-1].pocet; i++) { //Projde kazdou dvojici v relaci
        int JeTranzitivni = 0;
        char *a = data->relace[radek-1].relace[i].a;
        char *b = data->relace[radek-1].relace[i].b;
        for (int j = 0; j < data->relace[radek-1].pocet; j++) { //Projde kazdou dvojici v relaci a hleda relaci jejimz
                                                              // prvnim prvkem je druhy prvek horni relace(z predchoziho loopu
            if(strcmp(data->relace[radek-1].relace[j].a, b) == 0) //Pokud takovouto relaci najdeme pokracujeme v procesu dale
            {
                char *c = data->relace[radek-1].relace[j].b; // C je druhy prvek nalezene relace
                for(int k = 0; k <data->relace[radek-1].pocet; k++) // Projde kazdou dvojici v relaci a hleda relaci 
                {
                    if((strcmp(data->relace[radek-1].relace[k].a, a) == 0 )&& (strcmp(data->relace[radek-1].relace[k].b, c) == 0))
                    {
                        JeTranzitivni = 1; //Pokud jsme takovou relaci nasli tak JeTranzitivni se rovna 1, pokud ne tak 0
                        break;             //a pokousime se najit dalsi takove dvojice(pokud existuji)
                    }
                    else
                    {
                        JeTranzitivni = 0;
                    }
                }
            }
            if(JeTranzitivni) //Pokud byla dvojice transitivni, tak prislusnou 0 v poli zmeni na 1
            {
                break;
            }
        }
        if(JeTranzitivni) //Pokud byla dvojice transitivni, tak prislusnou 0 v poli zmeni na 1
        {
            TransitivniPole[i] = 1;
        }
    }
    for(int i = 0; i < data->relace[radek-1].pocet; i++) //Pokud je v poli alespon jedna 0, tak RelaceJeTransitivni se rovna 0
    {
        if(TransitivniPole[i]==0)
        {
            RelaceJeTransitivni = 0;
        }
    }
    if(RelaceJeTransitivni == 0)
    {
        pF();
    }
    else
    {
        pT();
    }
}

int kontrolaFu(Tdata *data, int radek)
{
    for( int j = 0; j < data->relace[radek-1].pocet; j++ )//Cyklus pro prvni prvek relace s prvnim prvkem dalsich relaci
    {   char *a = data->relace[radek-1].relace[j].a;
        char *b = data->relace[radek-1].relace[j].b;
        for( int i = j+1; i < data->relace[radek-1].pocet; i++) //pro prvni relaci př.(1,2) (1,2) ################
        {
            if(strcmp(a, data->relace[radek-1].relace[i].a) == 0)
            {
                if(strcmp(b, data->relace[radek-1].relace[i].b) != 0)
                {
                    return 0; // Vraci 1 pokud jsou prvky funkci
                }
            
            }
           
        }
    }
    return 1;
}

void funkce(Tdata *data, int radek) //tiskne true nebo false, jestli je relace R funkcí.
{
   if(kontrolaFu(data, radek))
   {
       pT();
       return;
   }
   pF();
}


void domena(Tdata *data, int radek) //Tiskne unikatni prvni prvky dvojic relaci
{
    printf("S");
    int x=0;
    char z[data->univerzum.pocet_prvku][31];
    strcpy(z[0], data->relace[radek-1].relace[0].a);
    int poc = 1;
    for(int j = 1; j < data->relace[radek-1].pocet; j++)
    {
        for(int i = 0; i < poc; i++)
        {
            if(strcmp(data->relace[radek-1].relace[j].a, z[i]) != 0)
            {
                x++;
            }
            
        }
        if(x == poc)
        {
            strcpy(z[poc], data->relace[radek-1].relace[j].a);
            poc++;
        }
        x = 0;
    }

    for( int i = 0; i < poc ; i++)
    { 
        printf(" %s", z[i]);
    }
    printf("\n");
}

int codomProj(Tdata *data, int radek, int j, int pocet) //Projde prvni prvky relaci a zjisti jestli jsou nektere stejne
{
    for(int i = 0; i < pocet; i++)
    {
        if(strcmp(data->relace[radek-1].relace[j].b, data->relace[radek-1].relace[i].b) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void codomena(Tdata *data, int radek) //Tiskne unikatni druhe prvky dvojic relaci
{
    printf("S"); 
    char z[data->univerzum.pocet_prvku][31];
    int x=0;
    strcpy(z[0], data->relace[radek-1].relace[0].b);
    int poc = 1;
    for(int j = 1; j < data->relace[radek-1].pocet; j++)
    {
        for(int i = 0; i < poc; i++)
        {
            if(strcmp(data->relace[radek-1].relace[j].b, z[i]) != 0)
            {
                x++;
            }
            
        }
        if(x == poc)
        {
            strcpy(z[poc], data->relace[radek-1].relace[j].b);
            poc++;
        }
        x = 0;
    }
    
    for(int i = 0; i < poc ; i++)
    { 
        printf(" %s", z[i]);
    }
    printf("\n");
}



int injektivniPom(Tdata *data, int radek)
{
    for( int j = 0; j < data->relace[radek-1].pocet; j++ )//Cyklus pro poro
    { 
        char *b = data->relace[radek-1].relace[j].b;
        for( int i = 0; i < data->relace[radek-1].pocet; i++) //pro prvni relaci 
        {
            if (i == j) continue;
            if(strcmp(b, data->relace[radek-1].relace[i].b) == 0)
            {
                    return 0; //
            }
           
        }
    }
    return 1;
}

void injektivni(Tdata *data, int radek)
{
    if(kontrolaFu(data, radek))
    {
        if(injektivniPom(data, radek))
        {
            pT(); //Je relace a je injektivni
        }
        else
        {
            pF(); //Je relace ale neni injektivni
        }
    }
    else
    {
        pF(); //Relace není funkcí
    }

}

int surjektivniCheck(int surpol[], int delka)
{
    for(int i = 0; i < delka; i++ )
    {
        if(surpol[i]==0)
        {
            return 0;
        }
    }
    return 1;
}

int surjektivniPom(Tdata *data, int radek, int mnozB)
{
    int surpol[data->mnoziny[mnozB-1].pocet_prvku];
    for(int i = 0; i < data->mnoziny[mnozB-1].pocet_prvku; i++) //
    {
        surpol[i] = 0;
    }
    for(int j = 0; j < data->relace[radek-1].pocet; j++ )
    {
        char *b = data->relace[radek-1].relace[j].b;
        for( int i = 0; i < data->mnoziny[mnozB-1].pocet_prvku; i++ )
            {
                if(strcmp(b, data->mnoziny[mnozB-1].pole[i]) == 0)
                {
                surpol[i] = 1;
                }
            }
    }
    if(surjektivniCheck(surpol, data->mnoziny[mnozB-1].pocet_prvku))
    {
        return 1;
    }
    return 0;
}

void surjektivni(Tdata *data, int radek, int mnozB)
{
   
    if(kontrolaFu(data, radek)) //Kontorola jestli je relace funkci
    {
        if(surjektivniPom(data, radek, mnozB)) //Relace je funkci, kontrolujeme surjektivitu
        {
            pT();
        }
        else
        {
            pF();  
        }
    }
    else
    {
        pF(); //Relace neni funkci
    }
}

void bijektivni(Tdata *data, int radek, int mnozB) 
{
    if((kontrolaFu(data, radek)) && (injektivniPom(data, radek)) && (surjektivniPom(data, radek , mnozB)))
    {
        pT();
    }
    else
    {
        pF();
    }
}


void nacteni_Moz(FILE *soub, Tdata *data, int radek)
{
    char a;
    int r = 0, s = 0; //pocitadla na radky sloupce
    a = fgetc(soub);
    printf("%c", a);
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
        printf("%c", a);
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
    printf("%c", a);
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
        printf("%c", a);
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
    printf("%c", a);
    while (a != '\n')
    {
        a = fgetc(soub);
        printf("%c", a);
        if (a == '(') ///Otevreni relace
        {
            a = fgetc(soub);
            printf("%c", a);
            while (a != ')') ///Hlida ukonceni relace
            {
                while (a != ' ') /// Nacte prvni slovo
                {
                    data->relace[radek].relace[r].a[s] = a;
                    s++;
                    realloc_RelAB(&(data->relace[radek].relace[r].a), s+1); /****Pridat odladeni****/
                    a = fgetc(soub);
                    printf("%c", a);
                }
                data->relace[radek].relace[r].a[s] = '\0'; //kazde pole je ukonceno '\0'
                s = 0;
                a = fgetc(soub);
                printf("%c", a);
                while (a != ')') ///Nacte druhe slovo
                {
                    data->relace[radek].relace[r].b[s] = a;
                    s++;
                    realloc_RelAB(&(data->relace[radek].relace[r].b), s+1); /****Pridat odladeni****/
                    a = fgetc(soub);
                    printf("%c", a);
                }

                data->relace[radek].relace->b[s] = '\0'; //kazde pole je ukonceno '\0'
                s = 0;


            }
            r++;
            data->relace[radek].pocet = r;
            realloc_Relace(&(data->relace[radek]), r+1);///Priprava ppameti pro novou relaci
            alloc_RelAB(&(data->relace[radek].relace[r]));
            a = fgetc(soub);
            printf("%c", a);
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
        a = fgetc(soub);
    }

    char pom[]= {fgetc(soub)}, *text;
    int b = 0, c;
    while (pom[0] != ' ')  //Nacte prvni cislo
    {
        c = (int)strtol(pom, &text, 10);
        b = b*10+c;
        if((strlen(text) > 1))
        {
            chybaOp();
            return -1;
        }
        pom[0] = fgetc(soub);
        if(pom[0] == '\n') {
            operace[radek].a = b;
            return 1;
        }
        if(pom[0] == EOF) {
            operace[radek].a = b;
            return 0;
        }
    }

    operace[radek].a = b;
    b = 0;
    pom[0] = fgetc(soub);
    while (pom[0] != ' ')  //Nacte prvni cislo
    {
        c = (int)strtol(pom, &text, 10);
        b = b*10+c;
        if((strlen(text) > 1))
        {
            chybaOp();
            return -1;
        }
        pom[0] = fgetc(soub);
        if(pom[0] == '\n') {
            operace[radek].b = b;
            return 1;
        }
        if(pom[0] == EOF) {
            operace[radek].b = b;
            return 0;
        }
    }
    operace[radek].b = b;
    b = 0;
    pom[0] = fgetc(soub);
    while (pom[0] != ' ')  //Nacte treti cislo
    {
        c = (int)strtol(pom, &text, 10);
        b = b*10+c;
        if((strlen(text) > 1))
        {
            chybaOp();
            return -1;
        }
        pom[0] = fgetc(soub);
        if(pom[0] == '\n') {
            operace[radek].c = b;
            return 1;
        }
        if(pom[0] == EOF) {
            operace[radek].c = b;
            return 0;
        }
    }
    operace[radek].c = b;
    return 1;
}

int nacti_OpePom(FILE *soub, Tobal *obal)
{
    char a = ' ';
    int i, pom;
    
    for (i = 0; a != EOF; i++)
    {   a = fgetc(soub);
        if (a == 'C') a = fgetc(soub);
        pom = nacti_Ope(soub, obal->operace, i);
        //realloc_Operace(&operace, i+2);
        if( pom == -1) return -1;
        if( pom == 0) //kdy konci radkem s operaci
        {
            return i+1;
        }
        realloc_Operace(&(obal->operace), i+2);
        alloc_OP(&(obal->operace[i+1].operace));
        a = fgetc(soub);
    };
    return i;
    
}


int nacti_Soubor(FILE *soub, Tdata *data, Tobal *obal, int *pocet_operaci)
{

    char a;
    int r = 0 , g; //pocitadla na radky sloupce
    while((a = fgetc(soub)) != EOF)
    {
        if(a !='C') printf("%c", a);
               //Po uvozovacim znaku U/C/R/S je mezera, timto ji preskocim
        switch (a)
        {
        case 'U': //nactitanni jednotlivych slov univerza
            a = fgetc(soub); 
            printf("%c", a);
            alloc_Mnozina(&(data->univerzum));
            alloc_MnozinaPismena(&(data->univerzum),0);
            nacteni_Uni(soub, data);
            r++;
            data->pocet = r;
            break;
        
        case 'S':  //nactitanni jednotlivych slov mnozin
            alloc_Mnozina(&(data->mnoziny[r]));
            alloc_MnozinaPismena(&(data->mnoziny[r]),0);
            a = fgetc(soub);
            printf("%c", a);
            if (a!='\n'){ 
                nacteni_Moz(soub,data,r);
                
            }
            else{
                data->mnoziny[r].pocet_prvku=0;
            }
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
            alloc_OP(&(obal->operace[0].operace));
            g = nacti_OpePom(soub, obal);
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
    for(int i = 0; i <a.pocet_prvku; printf(" %s", a.pole[i++])){}
}

void tiskR (TmnozinaRelaci a)
{
    for(int i = 0; i <a.pocet; i++){ printf(" (%s, %s)", a.relace[i].a,a.relace[i].b); }
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
            reflexivita(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "symmetric")) {
            symetricka(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "antisymmetric")) {
            antisymetricka(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "transitive")) {
            Transitivni(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "function")) {
            funkce(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "domain")) {
           domena(data, mnozina_operaci[i].a) ;
        } else if (!strcmp(mnozina_operaci[i].operace, "codomain")) {
            codomena(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "injective")) {
            injektivni(data, mnozina_operaci[i].a);
        } else if (!strcmp(mnozina_operaci[i].operace, "surjective")) {
            surjektivni(data, mnozina_operaci[i].a, mnozina_operaci[i].c);
        } else if (!strcmp(mnozina_operaci[i].operace, "bijective")) {
            bijektivni(data, mnozina_operaci[i].a, mnozina_operaci[i].c);
        } else {
            printf("Neplatna operace!");
        }
    }
}

void freeUni(Tmnozina *a)
{
    for(int i = a->pocet_prvku; i != 0; i--)
    {
        free(a->pole[i]);
    }
    free(a->pole[0]);
    free(a->pole);
}

void freeMnoz(Tmnozina *a)
{
    for(int i = a->pocet_prvku; i != 0; i--)
    {
        free(a->pole[i]);
    }
    //free(a->pole[0]);
    free(a->pole);
}

void freeRel(TmnozinaRelaci *a)
{
    for(int i = a->pocet; i != 0; i--)
    {
        free(a->relace[i].a);
        free(a->relace[i].b);
    }
    free(a->relace);
}


void cisteni(Tdata *data, Tobal *obal, int poc)
{
    freeUni(&(data->univerzum));
    for(int i = data->pocet; i != 0 ; i--)
    {
        freeMnoz(&(data->mnoziny[i]));
        freeRel(&(data->relace[i]));
    }
    //free(data->mnoziny);
    for (int  i = poc-1; i != 0; i--)
    {
        free(obal->operace[i].operace);
        //free(obal->operace[i]);
    }
    free(obal->operace);
    //free(&(data->mnoziny));
    //free(&(data->relace));


}

int main (int argc, char *argv[])
{
    argc = 0; // potrebuji se zbavit erroru unused argc xD

    FILE *soubor=fopen(argv[1], "r");
    Tdata data;
    data.pocet = argc;
    Tobal obal;
    int pocet_operaci;
    //oteri_soubor(soubor, argv[1]);  
    alloc_Operace(&(obal.operace));
    //printf("%d\n", alloc_OP(&(operace[0].operace)));      
    nacti_Soubor(soubor,&data, &obal, &pocet_operaci);
    

    vypis_operace(&data ,obal.operace, pocet_operaci);
    
    fclose(soubor);
    cisteni(&data, &obal, pocet_operaci);
    return 0;
}