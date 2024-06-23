#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESOS 10
#define PRIORIDAD_MAXIMA 5

typedef struct {
    int id;
    int prioridad;
} Proceso;

typedef struct Nodo {
    Proceso proceso;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* frente;
    Nodo* fin;
} ColaPrioridad;

void inicializar(ColaPrioridad* cola) {
    cola->frente = NULL;
    cola->fin = NULL;
}

void agregarProceso(ColaPrioridad* cola, Proceso proceso) {
    Nodo* nuevoNodo = malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        fprintf(stderr, "Error al asignar memoria para un nuevo nodo.\n");
        return;
    }
    nuevoNodo->proceso = proceso;
    nuevoNodo->siguiente = NULL;

    if (cola->frente == NULL || proceso.prioridad < cola->frente->proceso.prioridad) {
        nuevoNodo->siguiente = cola->frente;
        cola->frente = nuevoNodo;
    } else {
        Nodo* actual = cola->frente;
        while (actual->siguiente!= NULL && actual->siguiente->proceso.prioridad <= proceso.prioridad) {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
        if (nuevoNodo->siguiente == NULL) {
            cola->fin = nuevoNodo;
        }
    }
}

Proceso eliminarProceso(ColaPrioridad* cola) {
    if (cola->frente == NULL) {
        printf("La cola está vacía.\n");
        exit(1);
    }
    Proceso proceso = cola->frente->proceso;
    Nodo* nodoAEliminar = cola->frente;
    cola->frente = cola->frente->siguiente;
    free(nodoAEliminar);
    return proceso;
}

int estaVacia(ColaPrioridad* cola) {
    return cola->frente == NULL;
}

int main() {
    FILE* archivo = fopen("C:/Desarrollo/EDD_EX_001/procesos.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo.\n");
        return 0;
    }

    ColaPrioridad cola;
    inicializar(&cola);

    Proceso proceso;
    while (fscanf(archivo, "%d %d", &proceso.id, &proceso.prioridad) == 2) {
        agregarProceso(&cola, proceso);
    }

    while (!estaVacia(&cola)) {
        Proceso procesoEliminado = eliminarProceso(&cola);
        printf("ID: %d, Prioridad: %d\n", procesoEliminado.id, procesoEliminado.prioridad);
    }

    if (fclose(archivo)!= 0) {
        perror("Error al cerrar el archivo.");
    }

    return 0;
}
