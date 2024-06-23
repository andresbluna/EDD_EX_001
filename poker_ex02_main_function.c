#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "poker_funciones/pilas.h"
#include "poker_funciones/jugar_ronda.h"


int main() {
    Carta mazo[NUM_CARTAS];
    Carta *pila;
    int tamanoPila = 0;

    inicializar_mazo(mazo);
    barajar(mazo);

    crear_pila(&pila, &tamanoPila);
    for (int i = 0; i < NUM_CARTAS; i++) {
        apilar(&pila, mazo[i], &tamanoPila);
    }

    int ganador1 = 0, ganador2 = 0;
    int rondasJugadas = 0;

    while (ganador1 < RONDAS_PARA_GANAR && ganador2 < RONDAS_PARA_GANAR && !es_vacia(pila, tamanoPila)) {
        printf("Ronda %d\n", rondasJugadas + 1);
        jugar_ronda(&pila, &tamanoPila, &ganador1, &ganador2);
        rondasJugadas++;
    }

    if (ganador1 == RONDAS_PARA_GANAR) {
        printf("Jugador 1 gana el juego!!\n");
    } else if (ganador2 == RONDAS_PARA_GANAR) {
        printf("Jugador 2 gana el juego!!\n");
    } else {
        printf("Empate\n");
    }

    free(pila);

    return 0;
}

void crear_pila(Carta **pila, int *tamano) {
    *pila = (Carta *)malloc(NUM_CARTAS * sizeof(Carta));
    if (*pila == NULL) {
        perror("Error al asignar memoria para pila");
        exit(EXIT_FAILURE);
    }
    *tamano = 0;
}

void apilar(Carta **pila, Carta elem, int *tamano) {
    (*pila)[(*tamano)++] = elem;
}

void desapilar(Carta **pila, Carta *elem, int *tamano) {
    *elem = (*pila)[--(*tamano)];
}

bool es_vacia(Carta *pila, int tamano) {
    return tamano == 0;
}
