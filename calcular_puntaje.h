#ifndef CALCULAR_PUNTAJE_H
#define CALCULAR_PUNTAJE_H

#include <stdio.h>
#include <stdlib.h>
#include "tipojugadas.h"

int calcularPuntaje(Mano *mano) {
    if (esProfesionalesParaTodos(mano)) {
        return 15;
    } else if (esEscalaReal(mano)) {
        return 10;
    } else if (esEscalaFalsa(mano)) {
        return 5;
    } else if (esTrio(mano)) {
        return 3;
    } else if (esDos(mano)) {
        return 2;
    } else {
        return 1;
    }
}

#endif
