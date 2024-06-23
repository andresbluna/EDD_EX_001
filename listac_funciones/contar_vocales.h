#ifndef CONTAR_VOCALES_H
#define CONTAR_VOCALES_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listacircular.h"

// Función para contar las vocales en la lista circular

int contar_vocales(const char* str) {
    int contador = 0;
    for (int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            contador++;
        }
    }
    return contador;
}

// Función para calcular el porcentaje de vocales de la lista circular

double calcular_porcentaje_vocales(jugador* principal) {
    if (principal == NULL) {
        return 0.0;
    }

    int total_caracteres = 0;
    int total_vocales = 0;
    jugador* actual = principal;

    do {
        total_caracteres += strlen(actual->nombre);
        total_vocales += contar_vocales(actual->nombre);
        actual = actual->siguiente;
    } while (actual != principal);

    return (total_vocales * 100.0) / total_caracteres;
}

#endif