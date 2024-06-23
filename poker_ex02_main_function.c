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

    inicializarMazo(mazo);
    barajar(mazo);

    creaPila(&pila, &tamanoPila);
    for (int i = 0; i < NUM_CARTAS; i++) {
        apilar(&pila, mazo[i], &tamanoPila);
    }

    int ganador1 = 0, ganador2 = 0;
    int rondasJugadas = 0;

    while (ganador1 < RONDAS_PARA_GANAR && ganador2 < RONDAS_PARA_GANAR && !esVacia(pila, tamanoPila)) {
        printf("Ronda %d\n", rondasJugadas + 1);
        jugarRonda(&pila, &tamanoPila, &ganador1, &ganador2);
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

// Implementación de funciones de manejo de pila

void creaPila(Carta **pila, int *tamano) {
    *pila = (Carta *)malloc(NUM_CARTAS * sizeof(Carta));
    *tamano = 0;
}

void apilar(Carta **pila, Carta elem, int *tamano) {
    (*pila)[(*tamano)++] = elem;
}

void desapilar(Carta **pila, Carta *elem, int *tamano) {
    *elem = (*pila)[--(*tamano)];
}

bool esVacia(Carta *pila, int tamano) {
    return tamano == 0;
}
