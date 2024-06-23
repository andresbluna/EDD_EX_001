#ifndef CALCULAR_PUNTAJE_H
#define CALCULAR_PUNTAJE_H

#include "tipojugadas.h"

// Función que permite retornar el puntaje de la jugada

int calcular_puntaje(Mano *mano) {
    if (profesionales_para_todos(mano)) {
        return 15;
    } else if (escala_real(mano)) {
        return 10;
    } else if (escala_falsa(mano)) {
        return 5;
    } else if (trio(mano)) {
        return 3;
    } else if (dos(mano)) {
        return 2;
    } else {
        return 1;
    }
}

#endif
