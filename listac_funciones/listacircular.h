#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include <stdio.h>
#include <stdlib.h>

// Estructura "modelo" del nodo que se creará definido como "jugador"

typedef struct jugador_nodo {
    char nombre[50];
    int partidos_jugados;
    int sustituciones;
    int minutos;
    int goles;
    struct jugador_nodo *siguiente;
    struct jugador_nodo *anterior;
} jugador;


// Función para crear la lista de cada jugador

void crearjugador_lista(jugador **jugador_lista) {
    *jugador_lista = NULL;
}

// Función para insertar elementos dentro del nodo de cada jugador

void insertarElem(jugador *jugador_nodo_new, jugador **jugador_lista) {
    if (*jugador_lista == NULL) {
        jugador_nodo_new->siguiente = jugador_nodo_new->anterior = jugador_nodo_new;
        *jugador_lista = jugador_nodo_new;
    } else {
        jugador *ultimo = (*jugador_lista)->anterior;
        jugador_nodo_new->siguiente = *jugador_lista;
        jugador_nodo_new->anterior = ultimo;
        ultimo->siguiente = jugador_nodo_new;
        (*jugador_lista)->anterior = jugador_nodo_new;
    }
}

// Función que nos permite leer el archivo y crear la lista por Jugador

void leerArchivoYCrearLista(const char* filename, jugador **jugador_lista) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("No se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char linea[256];
    fgets(linea, sizeof(linea), file);

    while (fgets(linea, sizeof(linea), file)) {
        jugador *jugador_nodo_new = malloc(sizeof(jugador));
        if (!jugador_nodo_new) {
            perror("Error al asignar memoria para los datos del jugador");
            exit(EXIT_FAILURE);
        }

        sscanf(linea, "%[^,],%d,%d,%d,%d",
               jugador_nodo_new->nombre,
               &jugador_nodo_new->partidos_jugados,
               &jugador_nodo_new->sustituciones,
               &jugador_nodo_new->minutos,
               &jugador_nodo_new->goles);

        insertarElem(jugador_nodo_new, jugador_lista);
    }

    fclose(file);
}

// Función para liberar memoria de los nodos utilizados

void liberar_lista(jugador* cabeza) {
    if (cabeza == NULL) {
        return;
    }

    jugador* actual = cabeza;
    do {
        jugador* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    } while (actual!= cabeza);
}


#endif




