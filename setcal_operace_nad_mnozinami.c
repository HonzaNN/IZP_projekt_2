#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **pole;
    int pocet_prvku;
}Tmnozina;

typedef struct {
    Tmnozina *mnozina;
    int pocet;
}TmnozinaMnozin;

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
    TmnozinaMnozin *mnoziny;
    TmnozinaRelaci *relace;
    int pocet_mnozin, pocet_relaci;
}Tdata;

void tisk_mnoziny(char a[6][31], int pocet_prvku) {
    for (int i = 0; i < pocet_prvku; i++) {
        printf("%s ", a[i]);
    }
    printf("\n");
}

void prazdna_mnozina(Tmnozina a) {
    if(a.pocet_prvku == 0) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

void pocet_prvku(Tmnozina a) {
    printf("%d\n", a.pocet_prvku);
}

void doplnek(char a[6][31], char uni[6][31], int pocet_a, int pocet_uni) {
    int jeDoplnek = 1;

    printf("S");

    for (int i = 0; i < pocet_uni; i++) {
        jeDoplnek = 1;
        for (int j = 0; j < pocet_a; j++) {
            if(!strcmp(uni[i], a[j])) {
                jeDoplnek = 0;
                break;
            }
        }
        if(jeDoplnek) {
            printf(" %s", uni[i]);
        }
    }
    printf("\n");
}

void sjednoceni(char a[6][31], char b[6][31], int pocet_a, int pocet_b) {
    printf("S");

    for (int i = 0; i < pocet_a; i++) {
        printf(" %s", a[i]);
    }

    int jeDoplnek = 1;

    for (int i = 0; i < pocet_b; i++) {
        jeDoplnek = 1;
        for (int j = 0; j < pocet_a; j++) {
            if(!strcmp(b[i], a[j])) {
                jeDoplnek = 0;
                break;
            }
        }
        if(jeDoplnek) {
            printf(" %s", b[i]);
        }
    }
    printf("\n");
}

void prunik(char a[6][31], char b[6][31], int pocet_a, int pocet_b) {
    int jePrunik = 0;

    printf("S");

    for (int i = 0; i < pocet_a; i++) {
        jePrunik = 0;
        for (int j = 0; j < pocet_b; j++) {
            if(!strcmp(a[i], b[j])) {
                jePrunik = 1;
                break;
            }
        }
        if (jePrunik) {
            printf(" %s", a[i]);
        }
    }
    printf("\n");
}

void rozdil(char a[6][31], char b[6][31], int pocet_a, int pocet_b) {
    int jeRozdil = 0;

    printf("S");

    for (int i = 0; i < pocet_a; i++) {
        jeRozdil = 0;
        for (int j = 0; j < pocet_b; j++) {
            if(!strcmp(a[i], b[j])) {
                jeRozdil = 1;
                break;
            }
        }
        if (!jeRozdil) {
            printf(" %s", a[i]);
        }
    }
    printf("\n");
}

void podmnozina(char a[6][31], char b[6][31], int pocet_a, int pocet_b) {
    int jePodmnozina = 1;
    int jsouPodmnoziny[pocet_a];

    if (pocet_a > pocet_b) {
        printf("false\n");
    } else {

        for (int i = 0; i < pocet_a; i++) {
            jsouPodmnoziny[i] = 0;
        }

        for (int i = 0; i < pocet_a; i++) {
            for (int j = 0; j < pocet_b; j++) {
                if (!strcmp(a[i], b[j])) {
                    jsouPodmnoziny[i] = 1;
                }
            }
        }

        for (int i = 0; i < pocet_a; i++) {
            if (!jsouPodmnoziny[i]) {
                jePodmnozina = 0;
                break;
            }
        }

        if (jePodmnozina) printf("true\n");
        else printf("false\n");
    }
}

void vlastni_podmnozina(char a[6][31], char b[6][31], int pocet_a, int pocet_b) {
    if (pocet_a >= pocet_b) {
        printf("false\n");
    } else {
        podmnozina(a, b, pocet_a, pocet_b);
    }
}

void rovnost(char a[6][31], char b[6][31], int pocet_a, int pocet_b) {
    if (pocet_a != pocet_b) {
        printf("false\n");
    } else {
        podmnozina(a, b, pocet_a, pocet_b);
    }
}

int main() {

    char uni[6][31] = {"abc", "def", "ghi", "jkl", "mno", "pqr"};
    int pocet_uni = 6;

    char x[4][31] = {"abc", "def", "ghi", "jkl"};
    int pocet_x = 4;

    char y[3][31] = {"jkl", "mno", "pqr"};
    int pocet_y = 3;

    char z[4][31] = {"jkl", "abc", "ghi", "def"};
    int pocet_z = 4;

    /*tisk_mnoziny(uni);
    tisk_mnoziny(x);
    tisk_mnoziny(y);

    printf("\n");

    prazdna_mnozina(x);
    pocet_prvku(x);
    pocet_prvku(y);
    doplnek(x, uni);
    doplnek(y, uni);
    doplnek(uni, uni);*/

    tisk_mnoziny(uni, pocet_uni);
    tisk_mnoziny(x, pocet_x);
    tisk_mnoziny(y, pocet_y);
    tisk_mnoziny(z, pocet_z);

    printf("\n");

    doplnek(x, uni, pocet_x, pocet_uni);
    doplnek(y, uni, pocet_y, pocet_uni);
    doplnek(uni, uni, pocet_uni, pocet_uni);

    printf ("\n");

    prunik(x, uni, pocet_x, pocet_uni);
    prunik(y, uni, pocet_y, pocet_uni);
    prunik(x, y, pocet_x, pocet_y);

    printf ("\n");

    sjednoceni(x, y, pocet_x, pocet_y);
    sjednoceni(x, z, pocet_x, pocet_z);

    printf("\n");

    rozdil(x, y, pocet_x, pocet_y);
    rozdil(uni, y, pocet_uni, pocet_y);
    rozdil(x, z, pocet_x, pocet_z);
    rozdil(y, uni, pocet_y, pocet_uni);

    printf("\n");

    podmnozina(x, uni, pocet_x, pocet_uni);
    podmnozina(x, x, pocet_x, pocet_x);
    podmnozina(uni, x, pocet_uni, pocet_x);
    podmnozina(z, x, pocet_z, pocet_x);

    printf("\n");

    vlastni_podmnozina(x, uni, pocet_x, pocet_uni);
    vlastni_podmnozina(x, x, pocet_x, pocet_x);
    vlastni_podmnozina(uni, x, pocet_uni, pocet_x);
    vlastni_podmnozina(z, x, pocet_z, pocet_x);

    printf ("\n");

    rovnost(x, z, pocet_x, pocet_z);
    rovnost(x, y, pocet_x, pocet_y);
    rovnost(x, uni, pocet_x, pocet_uni);
    rovnost(x, x, pocet_x, pocet_x);
    rovnost(z, z, pocet_z, pocet_z);
    rovnost(uni, uni, pocet_uni, pocet_uni);
}
