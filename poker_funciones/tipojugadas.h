#ifndef TIPOJUGADAS_H
#define TIPOJUGADAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "pilas.h"

// Función que define la mano de profesionales

int profesionales_para_todos(Mano *mano) {
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        if (strcmp(mano->cartas[i].valor, "PHI") != 0 && strcmp(mano->cartas[i].valor, "CAR") != 0 &&
            strcmp(mano->cartas[i].valor, "FEL") != 0 && strcmp(mano->cartas[i].valor, "HUG") != 0) {
            return 0;
            }
    }
    return 1;
}


// Función que definev la escala real de cada mano

int escala_real(Mano *mano) {
    int valores[CARTAS_POR_JUGADOR];
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        valores[i] = valor_cartas(mano->cartas[i].valor);
    }
    if (valores[0] == valores[1] - 2 && valores[1] == valores[2] - 2 &&
        strcmp(mano->cartas[0].pinta, mano->cartas[1].pinta) == 0 &&
        strcmp(mano->cartas[1].pinta, mano->cartas[2].pinta) == 0) {
        return 1;
        }
    return 0;
}

// Función que define cada mano falsa

int escala_falsa(Mano *mano) {
    int valores[CARTAS_POR_JUGADOR];
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        valores[i] = valor_cartas(mano->cartas[i].valor);
    }
    if (valores[0] == valores[1] - 2 && valores[1] == valores[2] - 2) {
        return 1;
    }
    return 0;
}

// Función que comprueba si hay tres cartas con el mismo valor

int trio(Mano *mano) {

    if (strcmp(mano->cartas[0].valor, mano->cartas[1].valor) == 0 &&
        strcmp(mano->cartas[1].valor, mano->cartas[2].valor) == 0) {
        return 1;
        }
    return 0;
}

// Función que comprueba si hay dos cartas con el mismo valor

int dos(Mano *mano) {
    if (valor_cartas(mano->cartas[0].valor) == valor_cartas(mano->cartas[1].valor) ||
        valor_cartas(mano->cartas[0].valor) == valor_cartas(mano->cartas[2].valor) ||
        valor_cartas(mano->cartas[1].valor) == valor_cartas(mano->cartas[2].valor)) {
        return 1;
        }
    return 0;
}

#endif
