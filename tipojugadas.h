#ifndef TIPOJUGADAS_H
#define TIPOJUGADAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "pilas.h"


int esProfesionalesParaTodos(Mano *mano) {
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        if (strcmp(mano->cartas[i].valor, "PHI") != 0 && strcmp(mano->cartas[i].valor, "CAR") != 0 &&
            strcmp(mano->cartas[i].valor, "FEL") != 0 && strcmp(mano->cartas[i].valor, "HUG") != 0) {
            return 0;
            }
    }
    return 1;
}

int esEscalaReal(Mano *mano) {
    int valores[CARTAS_POR_JUGADOR];
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        valores[i] = valorCarta(mano->cartas[i].valor);
    }
    if (valores[0] == valores[1] - 2 && valores[1] == valores[2] - 2 &&
        strcmp(mano->cartas[0].pinta, mano->cartas[1].pinta) == 0 &&
        strcmp(mano->cartas[1].pinta, mano->cartas[2].pinta) == 0) {
        return 1;
        }
    return 0;
}

int esEscalaFalsa(Mano *mano) {
    int valores[CARTAS_POR_JUGADOR];
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        valores[i] = valorCarta(mano->cartas[i].valor);
    }
    if (valores[0] == valores[1] - 2 && valores[1] == valores[2] - 2) {
        return 1;
    }
    return 0;
}

int esTrio(Mano *mano) {
    // Comprobar si hay tres cartas con el mismo valor
    if (strcmp(mano->cartas[0].valor, mano->cartas[1].valor) == 0 &&
        strcmp(mano->cartas[1].valor, mano->cartas[2].valor) == 0) {
        return 1;
        }
    return 0;
}

int esDos(Mano *mano) {
    if (valorCarta(mano->cartas[0].valor) == valorCarta(mano->cartas[1].valor) ||
        valorCarta(mano->cartas[0].valor) == valorCarta(mano->cartas[2].valor) ||
        valorCarta(mano->cartas[1].valor) == valorCarta(mano->cartas[2].valor)) {
        return 1;
        }
    return 0;
}

#endif
