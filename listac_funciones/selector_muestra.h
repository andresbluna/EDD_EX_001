#ifndef SELECTOR_MUESTRA_H
#define SELECTOR_MUESTRA_H

#include <stdio.h>
#include "listacircular.h"


// Función que permite medir el tamaño de la lista

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

// Función que permite imprimir la muestra seleccionada en el prompt

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


#endif
