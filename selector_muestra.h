#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listacircular.h"

int tamano_lista(jugador* principal) {
    if (principal == NULL) {
        return 0;
    }
    int tamano = 1;
    jugador* actual = principal->siguiente;
    while (actual != principal) {
        tamano++;
        actual = actual->siguiente;
    }
    return tamano;
}


void imprimir_muestra(jugador* principal, int indice) {
    if (principal == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    int tamano = tamano_lista(principal);
    if (indice < 0) {
        indice = tamano + indice;
    }

    indice %= tamano;

    jugador* actual = principal;
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }

    printf("Informacion del jugador en el indice %d:\n", indice);
    printf(" Nombre: %s, Partidos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
           actual->nombre, actual->partidos_jugados, actual->sustituciones, actual->minutos, actual->goles);
}

