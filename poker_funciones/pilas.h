#ifndef PILAS_H
#define PILAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define NUM_CARTAS 30
#define CARTAS_POR_JUGADOR 3
#define RONDAS_PARA_GANAR 3

typedef struct carta {
    char pinta[4];
    char valor[4];
} Carta;

typedef struct {
    Carta cartas[CARTAS_POR_JUGADOR];
    int puntaje;
} Mano;

// Funciones de manejo de pila
void creaPila(Carta **pila, int *tamano);
void apilar(Carta **pila, Carta elem, int *tamano);
void desapilar(Carta **pila, Carta *elem, int *tamano);
bool esVacia(Carta *pila, int tamano);

void inicializarMazo(Carta mazo[NUM_CARTAS]) {
    char *pintas[] = {"GEN", "IFM", "PRO"};
    char *valores[] = {"CER", "DOS", "CUA", "SEI", "OCH", "DIE", "PHI", "CAR", "FEL", "HUG"};

    int indice = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            strcpy(mazo[indice].pinta, pintas[i]);
            strcpy(mazo[indice].valor, valores[j]);
            indice++;
        }
    }
}

void barajar(Carta mazo[NUM_CARTAS]) {
    srand(time(NULL));
    for (int i = 0; i < NUM_CARTAS; i++) {
        int j = rand() % NUM_CARTAS;
        Carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }
}

void robarCartas(Carta **pila, int *tamanoPila, Mano *mano) {
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        desapilar(pila, &mano->cartas[i], tamanoPila);
    }
}

int valorCarta(char valor[4]) {
    if (strcmp(valor, "CER") == 0) return 0;
    if (strcmp(valor, "DOS") == 0) return 2;
    if (strcmp(valor, "CUA") == 0) return 4;
    if (strcmp(valor, "SEI") == 0) return 6;
    if (strcmp(valor, "OCH") == 0) return 8;
    if (strcmp(valor, "DIE") == 0) return 10;
    if (strcmp(valor, "PHI") == 0) return 12;
    if (strcmp(valor, "CAR") == 0) return 14;
    if (strcmp(valor, "FEL") == 0) return 16;
    if (strcmp(valor, "HUG") == 0) return 18;
    return -1;
}

#endif
