#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct Articol {
    int cod;
    char* nume;
    float pret;
};

struct Articol citesteArticol() {
    struct Articol articol;

    printf("Introduceti codul articolului: ");
    scanf("%d", &articol.cod);

    printf("Introduceti numele articolului: ");
    articol.nume = (char*)malloc(50 * sizeof(char));
    scanf("%s", articol.nume);

    printf("Introduceti pretul articolului: ");
    scanf("%f", &articol.pret);

    return articol;
}

void afiseazaArticol(struct Articol articol) {
    printf("Cod articol: %d\n", articol.cod);
    printf("Nume articol: %s\n", articol.nume);
    printf("Pret articol: %.2f\n", articol.pret);
}

void afiseazaArticole(struct Articol* articole, int numarArticole) {
    printf("\nInformatii despre toate articolele:\n");
    for (int i = 0; i < numarArticole; ++i) {
        afiseazaArticol(articole[i]);
    }
}

struct Articol* copiazaArticoleCuConditie(struct Articol* sursa, int numarArticole, float valoareConditie, int* numarArticoleNou) {
    struct Articol* destinatie = (struct Articol*)malloc(numarArticole * sizeof(struct Articol));
    *numarArticoleNou = 0;

    for (int i = 0; i < numarArticole; ++i) {
        if (sursa[i].pret > valoareConditie) {
            destinatie[*numarArticoleNou] = sursa[i];
            (*numarArticoleNou)++;
        }
    }

    return destinatie;
}

struct Articol* mutaArticoleCuConditie(struct Articol* sursa, int numarArticole, float valoareConditie, int* numarArticoleNou) {
    struct Articol* destinatie = (struct Articol*)malloc(numarArticole * sizeof(struct Articol));
    *numarArticoleNou = 0;

    for (int i = 0; i < numarArticole; ++i) {
        if (sursa[i].pret < valoareConditie) {
            destinatie[*numarArticoleNou] = sursa[i];
            (*numarArticoleNou)++;
        }
    }

    return destinatie;
}

struct Articol* concateneazaVectori(struct Articol* vector1, int numarArticole1, struct Articol* vector2, int numarArticole2, int* numarArticoleNou) {
    struct Articol* rezultat = (struct Articol*)malloc((numarArticole1 + numarArticole2) * sizeof(struct Articol));
    *numarArticoleNou = 0;

    for (int i = 0; i < numarArticole1; ++i) {
        rezultat[*numarArticoleNou] = vector1[i];
        (*numarArticoleNou)++;
    }

    for (int i = 0; i < numarArticole2; ++i) {
        rezultat[*numarArticoleNou] = vector2[i];
        (*numarArticoleNou)++;
    }

    return rezultat;
}

void dezalocaArticole(struct Articol* articole, int numarArticole) {
    for (int i = 0; i < numarArticole; ++i) {
        free(articole[i].nume);
    }
    free(articole);
}

void creareFisier(char* fisier_txt) {
    FILE* f = fopen(fisier_txt, "w");
    if (f) {
        for (int i = 0; i < 10; i++) {
            struct Articol articol;
            articol.cod = i + 1;
            articol.pret = (i + 1) * 10;
            articol.nume = (char*)malloc(50 * sizeof(char));
            sprintf(articol.nume, "Articol%d", i + 1);
            fprintf(f, "%d %s %.2f\n", articol.cod, articol.nume, articol.pret);

            free(articol.nume);
        }
        fclose(f);
    }
    else
        printf("\nEste o eroare la deschiderea fisierului. \n");
}

void preluareinFisier(struct Articol* articole, int* numarArticole, char* fisier_txt) {
    FILE* f = fopen(fisier_txt, "r");
    if (f) {
        *numarArticole = 0;
        while (fscanf(f, "%d", &articole[*numarArticole].cod) == 1) {
            articole[*numarArticole].nume = (char*)malloc(50 * sizeof(char));
            if (articole[*numarArticole].nume == NULL) {
                printf("A aparut o eroare la alocarea memoriei.");
                fclose(f);
                return;
            }
            fscanf(f, "%s %f", articole[*numarArticole].nume, &articole[*numarArticole].pret);
            (*numarArticole)++;
        }
        fclose(f);
    }
    else
        printf("\n Este o eroare la deschiderea fisierului.\n");
}

void salvareArticol(struct Articol articol, char* fisier_txt) {
    FILE* f = fopen(fisier_txt, "a"); //a => adaugare (append)
    if (f) {
        fprintf(f, "%d %s %.2f\n", articol.cod, articol.nume, articol.pret);
        fclose(f);
        printf("\nArticolul a fost salvat in fisierul %s .\n", fisier_txt);
    }
    else {
        printf("\n Este o eroare la deschiderea fisierului.\n");
    }
}

void salvareVector(struct Articol* articole, int numarArticole, char* fisier_txt) {
    FILE* f = fopen(fisier_txt, "w");
    if (f) {
        for (int i = 0; i < numarArticole; i++) {
            fprintf(f, "%d %s %.2f\n", articole[i].cod, articole[i].nume, articole[i].pret);
        }
        fclose(f);
        printf("\nVectorul de articole a fost salvat in fisierul %s .\n", fisier_txt);
    }
    else {
        printf("\nEste o eroare la deschiderea fisierului.\n");
    }
}

int main() {
    char fisier_txt[30];
    printf("Denumirea fisierului existent: ");
    scanf("%s", fisier_txt);

    creareFisier(fisier_txt);

    struct Articol articole[15];
    int nr;
    preluareinFisier(articole, &nr, fisier_txt);

    printf("\n\nArticolele citite din fisier:\n");
    for (int i = 0; i < nr; i++) {
        printf("Articol %d: Cod: %d, Nume: %s, Pret: %.2f\n", i + 1,
            articole[i].cod, articole[i].nume, articole[i].pret);
    }

    struct Articol a1;
    a1.cod = 11;
    a1.nume = "Articol11";
    a1.pret = 110;
    salvareArticol(a1, fisier_txt);

    preluareinFisier(articole, &nr, fisier_txt);
    printf("\n\nArticolele citite din fisier:\n");
    for (int i = 0; i < nr; i++) {
        printf("Articol %d: Cod: %d, Nume: %s, Pret: %.2f\n", i + 1,
            articole[i].cod, articole[i].nume, articole[i].pret);
    }
    salvareVector(articole, 11, "art.txt");

    dezalocaArticole(articole, nr);

    return 0;
}
