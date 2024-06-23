#ifndef PROCESAR_FUNCION_H
#define PROCESAR_FUNCION_H

#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

// Función que procesa la cola de prioridad, desencolando y mostrando información de cada proceso

void procesar_cola(ColaPrioridad *cola) {
    while (cola->tamano > 0) {
        Proceso proceso = desencolar(cola);
        printf("se está desencolando el proceso -> id:%d prioridad:%d\n", proceso.id, proceso.prioridad);
    }
}

// Función que lee procesos desde un archivo y los coloca en una cola de prioridad

void leer_proceso_desde_archivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("No se puede abrir el archivo");
        exit(EXIT_FAILURE);
    }

    ColaPrioridad cola = { .tamano = 0 };
    int id, prioridad;

    while (fscanf(archivo, "%d %d", &id, &prioridad) != EOF) {
        Proceso proceso = { .id = id, .prioridad = prioridad };
        encolar(&cola, proceso);

        // Realizamos las condiciones correspondientes

        if (cola.tamano >= MAX_TAMANO_COLA) {
            printf("Se encuentra actualmente leyendo los procesos.....\n");
            procesar_cola(&cola);
        }
    }

// Realizamos las condiciones correspondientes

    if (cola.tamano > 0) {
        printf("Estado : 'Leyendo Procesos' ...\n");
        procesar_cola(&cola);
    }

    fclose(archivo);
}

#endif
