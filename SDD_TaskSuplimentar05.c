#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Articol {
    int cod;
    char* nume;
    float pret;
};

struct Nod {
    struct Articol articol;
    struct Nod* urmator;
};

void adaugaNod(struct Nod** cap, struct Articol articol) {
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->articol = articol;
	nou->urmator = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		struct Nod* temp = *cap;
		while (temp->urmator != NULL) {
			temp = temp->urmator;
		}
		temp->urmator = nou;
	}
}

void afiseazaLista(struct Nod* cap) {
	struct Nod* temp = cap;
	while (temp != NULL) {
		printf("Cod: %d, Nume: %s, Pret: %.2f\n", temp->articol.cod, temp->articol.nume, temp->articol.pret);
		temp = temp->urmator;
	}
}

struct Nod* stergereElement(struct Nod* inceput, int pozitie) {
	if (inceput == NULL) {
		printf("Lista este goala.\n");
		return NULL;
	}
	if (pozitie == 0) {
		struct Nod* temp = inceput;
		inceput = inceput->urmator;
		free(temp->articol.nume);
		free(temp);
		return inceput;
	}
	struct Nod* temp = inceput;
	int index = 0;
	while (temp != NULL && index < pozitie - 1)
	{ 
		temp = temp->urmator;
		index++;
	}
	if (temp == NULL || temp->urmator == NULL) 
	{
		printf("Indexul depaseste lungimea listei.\n");
		return inceput;
	}
	struct Nod* nodDeSters = temp->urmator;
	temp->urmator = temp->urmator->urmator; 
	free(nodDeSters->articol.nume);
	free(nodDeSters);
	return inceput;
}

void sortareLista(struct Nod** cap) {
	if (*cap == NULL || (*cap)->urmator == NULL) {
		return;
	}

	struct Nod* sortat = NULL;
	struct Nod* current = *cap;
	struct Nod* nextNode = NULL;

	while (current != NULL) {
		nextNode = current->urmator;
		if (sortat == NULL || sortat->articol.pret >= current->articol.pret) 
		{
			current->urmator = sortat;
			sortat = current;
		}
		else 
		{
			struct Nod* temp = sortat;
			while (temp->urmator != NULL && temp->urmator->articol.pret < current->articol.pret) 
			{
				temp = temp->urmator;
			}
			current->urmator = temp->urmator;
			temp->urmator = current;
		}
		current = nextNode;
	}
	*cap = sortat;
}



void main() {
	FILE* f = fopen("articole.txt", "r");
	struct Nod* lista = NULL;
	if (f != NULL) 
	{

		int cod;
		char nume[100];
		float pret;

		while (fscanf(f, "%d,", &cod) == 1) 
		{
			char buffer[100];
			fgets(buffer, sizeof(buffer), f);

			sscanf(buffer, "%[^,],%f", nume, &pret);

			char* numeCuratat = nume;
			while (*numeCuratat == ' ' || *numeCuratat == '\t') 
			{
				numeCuratat++;
			}
			int lungimeNume = strlen(numeCuratat);
			while (lungimeNume > 0 && (numeCuratat[lungimeNume - 1] == ' ' || numeCuratat[lungimeNume - 1] == '\t' || numeCuratat[lungimeNume - 1] == '\n' || numeCuratat[lungimeNume - 1] == '\r')) 
			{
				numeCuratat[lungimeNume - 1] = '\0';
				lungimeNume--;
			}

			struct Articol articol;
			articol.cod = cod;
			articol.nume = (char*)malloc(strlen(numeCuratat) + 1);
			strcpy(articol.nume, numeCuratat);
			articol.pret = pret;
			adaugaNod(&lista, articol);
		}
		fclose(f);
	}
	else {
		printf("Eroare la deschidere");
	}
	printf("\nLista articolelor\n");
	afiseazaLista(lista);
	lista = stergereElement(lista, 2);
	printf("\nLista articolelor dupa stergere\n");
	afiseazaLista(lista);

	sortareLista(&lista);
	printf("\nLista articolelor dupa sortare\n");
	afiseazaLista(lista);
}

//in articole.txt
//1, Bluza, 20
//2, Blugi, 200
//3, Curea, 50
//4, Telefon, 3000
//5, Paine, 5

