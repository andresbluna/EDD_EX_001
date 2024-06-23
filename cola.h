#ifndef COLA_H
#define COLA_H

#include <stdio.h>
#include <stdlib.h>


#define MAX_TAMANO_COLA 10

// Estructura "modelo" del nodo que se creará definido como "Procesos"

typedef struct {
    int id;
    int prioridad;
} Proceso;

// Estructura "modelo" que llama a la estructura
// "Proceso" con cola definida por prioridad

typedef struct {
    Proceso procesos[MAX_TAMANO_COLA];
    int tamano;
} ColaPrioridad;


// Función que permite encolar el modelo (struct)

void encolar(ColaPrioridad *cola, Proceso proceso) {
    if (cola->tamano >= MAX_TAMANO_COLA) {
        printf("La cola se encuentra llena, no se pueden encolar procesos: %d\n", proceso.id);
        return;
    }

    int i = cola->tamano - 1;
    while (i >= 0 && cola->procesos[i].prioridad > proceso.prioridad) {
        cola->procesos[i + 1] = cola->procesos[i];
        i--;
    }
    cola->procesos[i + 1] = proceso;
    cola->tamano++;
}

// Función que permite desencolar el modelo (struct)

Proceso desencolar(ColaPrioridad *cola) {
    if (cola->tamano == 0) {
        printf("Esta cola esta vacía, no se puede encolar\n");
        exit(EXIT_FAILURE);
    }

    Proceso proceso = cola->procesos[0];
    for (int i = 1; i < cola->tamano; i++) {
        cola->procesos[i - 1] = cola->procesos[i];
    }
    cola->tamano--;
    return proceso;
}

#endif
