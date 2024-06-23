#include <stdio.h>
#include <stdlib.h>

#define MAX_TAMANO_COLA 10

typedef struct {
    int id;
    int prioridad;
} Proceso;

typedef struct {
    Proceso procesos[MAX_TAMANO_COLA];
    int tamano;
} ColaPrioridad;

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

void procesarCola(ColaPrioridad *cola) {
    while (cola->tamano > 0) {
        Proceso proceso = desencolar(cola);
        printf("se está desencolando el proceso -> id:%d prioridad:%d\n", proceso.id, proceso.prioridad);
    }
}

void leerProcesosDesdeArchivo(const char *nombreArchivo) {
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

        if (cola.tamano >= MAX_TAMANO_COLA) {
            printf("Se encuentra actualmente leyendo los procesos.....\n");
            procesarCola(&cola);
        }
    }

    if (cola.tamano > 0) {
        printf("Estado : 'Leyendo Procesos' ...\n");
        procesarCola(&cola);
    }

    fclose(archivo);
}

int main() {
    leerProcesosDesdeArchivo("procesos.txt");
    return 0;
}