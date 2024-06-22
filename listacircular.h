#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct jugador_nodo {
    char nombre[50];
    int partidos_jugados;
    int sustituciones;
    int minutos;
    int goles;
    struct jugador_nodo *siguiente;
    struct jugador_nodo *anterior;
} jugador;

void crearjugador_lista(jugador **jugador_lista) {
    *jugador_lista = NULL;
}

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



double calcular_promedio(jugador* principal, int (*obtener_valor)(jugador*)) {
    if (principal == NULL) {
        return 0.0;
    }

    int total = 0;
    int count = 0;
    jugador* actual = principal;

    do {
        total += obtener_valor(actual);
        count++;
        actual = actual->siguiente;
    } while (actual != principal);

    return (count > 0) ? (total / (double)count) : 0.0;
}

int obtener_goles(jugador* jugador) {
    return jugador->goles;
}

int tamano_lista(jugador* principal) {
    if (principal == NULL) {
        return 0;
    }
    int tamano = 1;
    jugador* actual = principal->siguiente;
    while (actual != principal) {
        tamano++;
        actual = actual->siguiente;
    }
    return tamano;
}

void imprimir_muestra(jugador* principal, int indice) {
    if (principal == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    int tamano = tamano_lista(principal);
    if (indice < 0) {
        indice = tamano + indice;
    }

    indice %= tamano;

    jugador* actual = principal;
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }

    printf("Informacion del jugador en el indice %d:\n", indice);
    printf(" Nombre: %s, Partidos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
           actual->nombre, actual->partidos_jugados, actual->sustituciones, actual->minutos, actual->goles);
}

int obtener_valor(jugador* jugador, int parametro) {
    switch (parametro) {
        case 1: return jugador->partidos_jugados;
        case 2: return jugador->sustituciones;
        case 3: return jugador->minutos;
        case 4: return jugador->goles;
        default: return 0;
    }
}

void intercambiar_nodos(jugador* a, jugador* b) {
    if (a == b) return;

    char nombre_temp[50];
    int partidos_temp, sustituciones_temp, minutos_temp, goles_temp;

    strcpy(nombre_temp, a->nombre);
    partidos_temp = a->partidos_jugados;
    sustituciones_temp = a->sustituciones;
    minutos_temp = a->minutos;
    goles_temp = a->goles;

    strcpy(a->nombre, b->nombre);
    a->partidos_jugados = b->partidos_jugados;
    a->sustituciones = b->sustituciones;
    a->minutos = b->minutos;
    a->goles = b->goles;

    strcpy(b->nombre, nombre_temp);
    b->partidos_jugados = partidos_temp;
    b->sustituciones = sustituciones_temp;
    b->minutos = minutos_temp;
    b->goles = goles_temp;
}

void ordenar_lista(jugador** jugador_lista, int parametro) {
    if (*jugador_lista == NULL) {
        return;
    }

    int intercambiado;
    jugador* actual;
    jugador* siguiente;

    do {
        intercambiado = 0;
        actual = *jugador_lista;

        do {
            siguiente = actual->siguiente;
            if (siguiente != *jugador_lista && obtener_valor(actual, parametro) > obtener_valor(siguiente, parametro)) {
                intercambiar_nodos(actual, siguiente);
                intercambiado = 1;
            }
            actual = actual->siguiente;
        } while (actual->siguiente != *jugador_lista);
    } while (intercambiado);
}
