#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define NUM_CARTAS 30
#define CARTAS_POR_JUGADOR 3
#define RONDAS_PARA_GANAR 3

typedef struct carta {
    char pinta[4];
    char valor[4];
} Carta;

typedef struct {
    Carta cartas[CARTAS_POR_JUGADOR];
    int puntaje;
} Mano;

// Funciones de manejo de pila
void creaPila(Carta **pila, int *tamano);
void apilar(Carta **pila, Carta elem, int *tamano);
void desapilar(Carta **pila, Carta *elem, int *tamano);
bool esVacia(Carta *pila, int tamano);

void inicializarMazo(Carta mazo[NUM_CARTAS]) {
    char *pintas[] = {"GEN", "IFM", "PRO"};
    char *valores[] = {"CER", "DOS", "CUA", "SEI", "OCH", "DIE", "PHI", "CAR", "FEL", "HUG"};

    int indice = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            strcpy(mazo[indice].pinta, pintas[i]);
            strcpy(mazo[indice].valor, valores[j]);
            indice++;
        }
    }
}

void barajar(Carta mazo[NUM_CARTAS]) {
    srand(time(NULL));
    for (int i = 0; i < NUM_CARTAS; i++) {
        int j = rand() % NUM_CARTAS;
        Carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }
}

void robarCartas(Carta **pila, int *tamanoPila, Mano *mano) {
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        desapilar(pila, &mano->cartas[i], tamanoPila);
    }
}

int valorCarta(char valor[4]) {
    if (strcmp(valor, "CER") == 0) return 0;
    if (strcmp(valor, "DOS") == 0) return 2;
    if (strcmp(valor, "CUA") == 0) return 4;
    if (strcmp(valor, "SEI") == 0) return 6;
    if (strcmp(valor, "OCH") == 0) return 8;
    if (strcmp(valor, "DIE") == 0) return 10;
    if (strcmp(valor, "PHI") == 0) return 12;
    if (strcmp(valor, "CAR") == 0) return 14;
    if (strcmp(valor, "FEL") == 0) return 16;
    if (strcmp(valor, "HUG") == 0) return 18;
    return -1;
}

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
