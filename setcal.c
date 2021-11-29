#include <stdio.h>
#include <stdlib.h>

typedef struct {
     Char **pole;
    int pocet prvků
}Tmnozina;

typedef struct {
    char *a;
    char *b;
}Trelace;

typedef struct {
    Trelace *relace;
    int pocet;
}TmnozinaRelaci

typedef struct {
    Tstruktura univerzum;
    Tstruktura *mnoziny;
    TmnozinaRelaci *relace;
    int pocet_mnozin, pocet_relaci;
}Tdata
