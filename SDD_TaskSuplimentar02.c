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

    printf("Introduceti codul articolului: "); scanf("%d", &articol.cod);

    printf("Introduceti numele articolului: "); //pt nume alocare dinamica
    articol.nume = (char*)malloc(50 * sizeof(char)); scanf("%s", articol.nume);

    printf("Introduceti pretul articolului: "); scanf("%f", &articol.pret);

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

float calculeazaSumaTotala(struct Articol* articole, int numarArticole) {
    float sumaTotala = 0;
    for (int i = 0; i < numarArticole; ++i) {
        sumaTotala += articole[i].pret;
    }
    return sumaTotala;
}

void modificaPretArticol(struct Articol* articol, float nouPret) {
    articol->pret = nouPret;
}

// pt memoria dinamica
void elibereazaMemorie(struct Articol* articol) {
    free(articol->nume);
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

int main() {
    int numarArticole;
    printf("Introduceti numarul de articole: "); scanf("%d", &numarArticole);

    struct Articol* articole = (struct Articol*)malloc(numarArticole * sizeof(struct Articol));

    for (int i = 0; i < numarArticole; ++i) {
        articole[i] = citesteArticol();
        printf("\nInformatii despre articolul %d:\n", i + 1);
        afiseazaArticol(articole[i]);
    }

    for (int i = 0; i < numarArticole; ++i) {
        float nouPret;
        printf("Introduceti noul pret pentru articolul %d: ", i + 1); scanf("%f", &nouPret);
        modificaPretArticol(&articole[i], nouPret);
    }

    printf("\nInformatii actualizate despre articole:\n");
    afiseazaArticole(articole, numarArticole);

    printf("\nSuma preturilor pentru toate articolele: %.2f\n", calculeazaSumaTotala(articole, numarArticole));

    int numarArticoleNou1, numarArticoleNou2, numarArticoleNou3;
    struct Articol* articoleConditie1 = copiazaArticoleCuConditie(articole, numarArticole, 50.0, &numarArticoleNou1);
    struct Articol* articoleConditie2 = mutaArticoleCuConditie(articole, numarArticole, 30.0, &numarArticoleNou2);
    struct Articol* vectorConcatenat = concateneazaVectori(articoleConditie1, numarArticoleNou1, articoleConditie2, numarArticoleNou2, &numarArticoleNou3);

    printf("\nArticole cu pret mai mare decat 50:\n");
    if (numarArticoleNou1 > 0) {
        afiseazaArticole(articoleConditie1, numarArticoleNou1);
    }
    else {
        printf("Nu exista articole cu pret mai mare decat 50.\n");
    }


    printf("\nArticole cu pret mai mic decat 30:\n");
    if (numarArticoleNou2 > 0) {
        afiseazaArticole(articoleConditie2, numarArticoleNou2);
    }
    else {
        printf("Nu exista articole cu pret mai mic decat 30.\n");
    }

    printf("\nVector concatenat:\n");
    if (numarArticoleNou3 > 0) {
        afiseazaArticole(vectorConcatenat, numarArticoleNou3);
    }
    else {
        printf("Vectorul concatenat este gol.\n");
    }

    // eliberare memorie
    for (int i = 0; i < numarArticole; ++i) {
        elibereazaMemorie(&articole[i]);
    }

    free(articole);
    free(articoleConditie1);
    free(articoleConditie2);
    free(vectorConcatenat);

    return 0;
}
