#include "listacircular.h"

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