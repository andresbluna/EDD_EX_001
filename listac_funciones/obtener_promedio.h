#ifndef OBTENER_PROMEDIO_H
#define OBTENER_PROMEDIO_H

#include "contar_vocales.h"

// Función única que calcula el promedio de cualquier subnodo

float calcular_promedio(jugador* principal, int (*obtener_valor)(jugador*)) {
    if (principal == NULL) {
        return 0.0;
    }

    int total = 0;
    int count = 0;
    jugador* actual = principal;

    do {
        total += obtener_valor(actual);
        count++;
        actual = actual->siguiente;
    } while (actual != principal);

    return (count > 0) ? (total / (float)count) : 0.0;
}


// Función que utiliza función anterior 'calcular promedio'
// Obtiene el subnodo goles y los promedia

int obtener_goles(jugador* jugador) {
    return jugador->goles;
}

// Función que utiliza función anterior 'calcular promedio'
// Obtiene el subnodo sustituciones y los promedia

int obtener_sustituciones(jugador* jugador) {
    return jugador->sustituciones;
}

#endif