#include <stdio.h>
#include "listac_funciones/contar_vocales.h"
#include "listac_funciones/obtener_promedio.h"
#include "listac_funciones/selector_muestra.h"
#include "listac_funciones/lista_menor_mayor.h"


int main() {
    jugador *jugador_lista = NULL;
    crearjugador_lista(&jugador_lista);
    leerArchivoYCrearLista("datafutbol_process.csv", &jugador_lista);

    double porcentaje_vocales = calcular_porcentaje_vocales(jugador_lista);
    printf("\nPorcentaje de vocales en los nombres de los jugadores: %.2f %%\n", porcentaje_vocales);

    double promedio_goles = calcular_promedio(jugador_lista, obtener_goles);
    printf("\nPromedio de goles: %.2f\n", promedio_goles);
    double promedio_sustituciones = calcular_promedio(jugador_lista, obtener_sustituciones);
    printf("Promedio sustituciones: %.2f\n", promedio_sustituciones);

    int indice;
    printf("\nIngrese el indice del jugador que desea ver (puede ser negativo): ");
    scanf("%d", &indice);
    imprimir_muestra(jugador_lista, indice);

    printf("Ingrese el indice de otro jugador que desea ver (puede ser negativo): ");
    scanf("%d", &indice);
    imprimir_muestra(jugador_lista, indice);

    int parametro1, parametro2;
    printf("\nIngrese el primer numero del parametro por el cual desea ordenar "
           "(1: Partidos Jugados, 2: Sustituciones, 3: Minutos, 4: Goles): ");
    scanf("%d", &parametro1);

    ordenar_lista(&jugador_lista, parametro1);
    printf("Lista ordenada por '%d'.\n", parametro1);

    jugador* actual = jugador_lista;
    do {
        printf("Nombre: %s, Partidos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
               actual->nombre, actual->partidos_jugados, actual->sustituciones, actual->minutos, actual->goles);
        actual = actual->siguiente;
    } while (actual!= jugador_lista);

    printf("\nIngrese el segundo numero del parametro por el cual desea ordenar "
           "(1: Partidos Jugados, 2: Sustituciones, 3: Minutos, 4: Goles): ");
    scanf("%d", &parametro2);

    ordenar_lista(&jugador_lista, parametro2);
    printf("Lista ordenada por '%d'.\n", parametro2);

    actual = jugador_lista;
    do {
        printf("Nombre: %s, Partidos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
               actual->nombre, actual->partidos_jugados, actual->sustituciones, actual->minutos, actual->goles);
        actual = actual->siguiente;
    } while (actual!= jugador_lista);

    return 0;
}
