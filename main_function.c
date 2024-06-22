#include <stdio.h>
#include "listacircular.h"
#include "contar_vocales.h"


int main() {
    jugador *jugador_lista = NULL;
    crearjugador_lista(&jugador_lista);
    leerArchivoYCrearLista("datafutbol_process.csv", &jugador_lista);

    double porcentaje_vocales = calcular_porcentaje_vocales(jugador_lista);
    printf(" Porcentaje de vocales en los nombres de los jugadores: %.2f%%\n", porcentaje_vocales);

    double promedio_goles = calcular_promedio(jugador_lista, obtener_goles);
    printf(" Promedio de goles: %.2f\n", promedio_goles);

    int indice;
    printf(" Ingrese el indice del jugador que desea ver (puede ser negativo): ");
    scanf("%d", &indice);
    imprimir_muestra(jugador_lista, indice);

    int parametro;
    printf(" Ingrese el numero del parametro por el cual desea ordenar (1: Partidos Jugados, 2: Sustituciones, 3: Minutos, 4: Goles): ");
    scanf("%d", &parametro);
    ordenar_lista(&jugador_lista, parametro);
    printf("Lista ordenada.\n");

    jugador* actual = jugador_lista;
    do {
        printf(" Nombre: %s, Partidos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
               actual->nombre, actual->partidos_jugados, actual->sustituciones, actual->minutos, actual->goles);
        actual = actual->siguiente;
    } while (actual != jugador_lista);

    return 0;
}