#ifndef JUGAR_RONDA_H
#define JUGAR_RONDA_H

#include "pilas.h"
#include "calcular_puntaje.h"


void jugarRonda(Carta **pila, int *tamanoPila, int *ganador1, int *ganador2) {
    Mano mano1, mano2;
    robarCartas(pila, tamanoPila, &mano1);
    robarCartas(pila, tamanoPila, &mano2);

    mano1.puntaje = calcularPuntaje(&mano1);
    mano2.puntaje = calcularPuntaje(&mano2);

    printf("Jugador 1: ");
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        printf("%s de %s, ", mano1.cartas[i].valor, mano1.cartas[i].pinta);
    }
    printf("Puntaje: %d\n", mano1.puntaje);

    printf("Jugador 2: ");
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        printf("%s de %s, ", mano2.cartas[i].valor, mano2.cartas[i].pinta);
    }
    printf("Puntaje: %d\n", mano2.puntaje);

    if (mano1.puntaje > mano2.puntaje) {
        (*ganador1)++;
    } else if (mano2.puntaje > mano1.puntaje) {
        (*ganador2)++;
    } else {
        int max1 = valorCarta(mano1.cartas[0].valor);
        int max2 = valorCarta(mano2.cartas[0].valor);
        for (int i = 1; i < CARTAS_POR_JUGADOR; i++) {
            if (valorCarta(mano1.cartas[i].valor) > max1) {
                max1 = valorCarta(mano1.cartas[i].valor);
            }
            if (valorCarta(mano2.cartas[i].valor) > max2) {
                max2 = valorCarta(mano2.cartas[i].valor);
            }
        }
        if (max1 > max2) {
            (*ganador1)++;
        } else if (max2 > max1) {
            (*ganador2)++;
        }
    }

    printf("Puntajes: Jugador 1 = %d, Jugador 2 = %d\n", *ganador1, *ganador2);
    printf("\n");
}



#endif
