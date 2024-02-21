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

    for (int i = 0; i < numarArticole; ++i)

    {

        afiseazaArticol(articole[i]);

    }

}



float calculeazaSumaTotala(struct Articol* articole, int numarArticole) {

    float sumaTotala = 0;

    for (int i = 0; i < numarArticole; ++i)

    {

        sumaTotala += articole[i].pret;

    }

    return sumaTotala;

}



void modificaPretArticol(struct Articol* articol, float nouPret) {

    articol->pret = nouPret;

}



//pt memoria dinamica

void elibereazaMemorie(struct Articol* articol) {

    free(articol->nume);

}



int main() {

    int numarArticole;

    printf("Introduceti numarul de articole: "); scanf("%d", &numarArticole);



    struct Articol* articole = (struct Articol*)malloc(numarArticole * sizeof(struct Articol));



    for (int i = 0; i < numarArticole; ++i)

    {

        articole[i] = citesteArticol();

        printf("\nInformatii despre articolul %d:\n", i + 1);

        afiseazaArticol(articole[i]);

    }



    for (int i = 0; i < numarArticole; ++i)

    {

        float nouPret;

        printf("Introduceti noul pret pentru articolul %d: ", i + 1); scanf("%f", &nouPret);

        modificaPretArticol(&articole[i], nouPret);

    }



    printf("\nInformatii actualizate despre articole:\n");

    afiseazaArticole(articole, numarArticole);



    printf("\nSuma preturilor pentru toate articolele: %.2f\n", calculeazaSumaTotala(articole, numarArticole));



    //eliberare memorie

    for (int i = 0; i < numarArticole; ++i) {

        elibereazaMemorie(&articole[i]);

    }

    free(articole);



    return 0;

}